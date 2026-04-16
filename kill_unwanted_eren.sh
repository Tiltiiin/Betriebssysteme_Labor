#!/bin/bash

# ============================================================
# kill_unwanted.sh
# Überwacht laufende Prozesse und beendet solche, die zu viel
# RAM, CPU und zu lange laufen.
#
# Ablauf:
#  1. Parameter einlesen (RAM-Limit, CPU-Limit, Zeitgrenzen)
#  2. Alle TIME Sekunden eine Momentaufnahme aller Prozesse machen
#  3. System- und Dienst-User überspringen (root, jhub, nginx)
#  4. Prozesse, die alle drei Limits überschreiten → SIGTERM senden
#  5. Wenn der Prozess nach HARDTIME Sekunden immer noch läuft → SIGKILL
# ============================================================

# Standard-Grenzwerte: RAM in GB, CPU in %, Wartezeiten in Sekunden
MEMORY=32
UTILIZATION=50
TIME=15
HARDTIME=15

# Assoziatives Array: speichert den Timestamp, wann SIGTERM an einen PID gesendet wurde
declare -A map

# --- Kommandozeilenparameter einlesen ---
while [ "x${1}x" != "xx" ]; do
    case "${1}" in
        -m|--memory)
            MEMORY="${2}"
            shift 2
            ;;
        -t|--time)
            TIME="${2}"
            shift 2
            ;;
        -u|--utilization)
            UTILIZATION="${2}"
            shift 2
            ;;
        --help)
            echo "Verwendung: kill_unwanted.sh [-m GB] [-t Sekunden] [-u Prozent] [-h Sekunden]"
            echo "  -m|--memory       RAM-Limit in GB (Default: 32)"
            echo "  -t|--time         Zeit in Sekunden, ab der ein Prozess als Langläufer gilt (Default: 15)"
            echo "  -u|--utilization  CPU-Auslastung in % als Grenzwert (Default: 50)"
            echo "  -h|--hardtime     Sekunden nach dem SIGTERM, nach denen SIGKILL gesendet wird (Default: 15)"
            echo "  --help            Diese Hilfe anzeigen"
            exit 0
            ;;
        -h|--hardtime)
            HARDTIME="${2}"
            shift 2
            ;;
        *)
            echo "Unbekannter Parameter: ${1}"
            exit 1
            ;;
    esac
done

# --- Hauptschleife: läuft endlos, prüft alle TIME Sekunden ---
while true; do

    # RAM-Limit einmalig von GB in KB umrechnen (ps liefert RSS in KB)
    MEMORY_KB=$(( MEMORY * 1024 * 1024))

    # `ps` liefert eine Zeile pro Prozess: PID, USER, RAM(KB), CPU(%), Befehl, Laufzeit(s)
    # `tail -n +2` überspringt die Header-Zeile
    while read LINE; do

        # Felder aus der Zeile extrahieren:
        # tr -s ' ' ';'  → mehrfache Leerzeichen durch ';' ersetzen (einfacheres Splitten)
        # cut -d';' -fN  → N-tes Feld auswählen
        PID=$(echo "${LINE}"  | tr -s ' ' ';' | cut -d';' -f1)
        USER=$(echo "${LINE}" | tr -s ' ' ';' | cut -d';' -f2)
        RAM=$(echo "${LINE}"  | tr -s ' ' ';' | cut -d';' -f3)
        CPU=$(echo "${LINE}"  | tr -s ' ' ';' | cut -d';' -f4 | cut -d'.' -f1)  # Nachkommastellen abschneiden
        NAME=$(echo "${LINE}" | tr -s ' ' ';' | cut -d';' -f5)
        TIME_ELAPSED=$(echo "${LINE}" | awk '{print $NF}')  # letztes Feld = Laufzeit in Sekunden

        # Systemprozesse und Dienst-User werden nie beendet
        if [ "${USER}" = "root" ] || [ "${USER}" = "jhub" ] || [ "${USER}" = "nginx" ]; then
            continue
        fi

        # Prüfen ob dieser PID bereits im map steht (= SIGTERM wurde schon gesendet)
        if [ -n "${map[${PID}]}" ]; then
            # Wie viele Sekunden ist es her, seit SIGTERM gesendet wurde?
            elapsed=$(( $(date +%s) - ${map[${PID}]} ))
            if [ "${elapsed}" -gt "${HARDTIME}" ]; then
                # Prozess reagiert immer noch nicht → SIGKILL (sofortiger Abbruch)
                echo "kill -SIGKILL ${PID}: reagiert nicht nach ${elapsed}s"
                unset map[${PID}]
            fi

        # Prozess überschreitet alle drei Limits gleichzeitig → SIGTERM senden
        elif [ "${RAM}" -gt "${MEMORY_KB}" ] && [ "${CPU}" -gt "${UTILIZATION}" ] && [ "${TIME_ELAPSED}" -gt "${TIME}" ]; then
            echo "kill -SIGTERM ${PID}: RAM ${RAM}KB größer als ${MEMORY}GB, CPU ${CPU}% größer als ${UTILIZATION}%"
            # Timestamp merken, damit wir wissen wann SIGTERM gesendet wurde
            map[${PID}]=$(date +%s)
        fi

    done < <(ps -eo pid,user,rss,%cpu,args,etimes | tail -n +2)

    # Bis zur nächsten Prüfung warten
    sleep "${TIME}"
done
