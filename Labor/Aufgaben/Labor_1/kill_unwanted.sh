#!/bin/bash

# Standard-Grenzwerte: RAM in GB, CPU in %, Wartezeit in Sekunden
MEMORY=32
UTILIZATION=50
TIME=15

# Kommandozeilenparameter verarbeiten
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
        -h|--help)
            echo "Verwendung: kill_unwanted.sh [-m GB] [-t Sekunden] [-u Prozent]"
            echo "  -m|--memory       RAM-Limit in GB (Default: 32)"
            echo "  -t|--time         Zeit in Sekunden (Default: 15)"
            echo "  -u|--utilization  CPU-Auslastung in % (Default: 50)"
            echo "  -h|--help         Diese Hilfe anzeigen"
            exit 0
            ;;
        *)
            echo "Unbekannter Parameter: ${1}"
            exit 1
            ;;
    esac
done

# Dauerhaft alle TIME Sekunden die laufenden Prozesse prüfen
while true; do
    # Speicherlimit einmalig in MB umrechnen
    MEMORY_MB=$(( MEMORY * 1024 ))

    # Jeden laufenden Prozess einzeln auswerten
    while read LINE; do
        # Prozessinformationen aus der ps-Ausgabe extrahieren
        PID=$(echo "${LINE}"  | tr -s ' ' ';' | cut -d';' -f1)
        USER=$(echo "${LINE}" | tr -s ' ' ';' | cut -d';' -f2)
        RAM=$(echo "${LINE}"  | tr -s ' ' ';' | cut -d';' -f3)
        CPU=$(echo "${LINE}"  | tr -s ' ' ';' | cut -d';' -f4 | cut -d'.' -f1)
        name=$(echo "${LINE}"  | tr -s ' ' ';' | cut -d';' -f5)

        # RAM von KB in MB umrechnen
        RAM_MB=$(( RAM / 1024 ))

        # Systemprozesse niemals beenden
        if [ "${USER}" = "root" ] || [ "${USER}" = "jhub" ] || [ "${USER}" = "nginx" ]; then
            continue
        fi

        # Prozess beenden wenn RAM und CPU gleichzeitig die Grenzwerte überschreiten
        if [ "${RAM_MB}" -gt "${MEMORY_MB}" ] && [ "${CPU}" -gt "${UTILIZATION}" ]; then
            echo "kill -SIGTERM ${PID}(${name}): RAM usage $((RAM_MB / 1024))GB is bigger than ${MEMORY}GB and CPU usage ${CPU}% is bigger than ${UTILIZATION}%"
        #elif [ "${RAM_MB}" -gt "${MEMORY_MB}" ]; then
            #echo "kill -SIGTERM ${PID}: RAM usage ${RAM_MB} is bigger than ${MEMORY}"
        #elif [ "${CPU}" -gt "${UTILIZATION}" ]; then
            #echo "kill -SIGTERM ${PID}: CPU usage ${CPU}% is bigger than ${UTILIZATION}%"
        fi

    # Header-Zeile von ps überspringen mit tail -n +2
    done < <(ps -eo pid,user,rss,%cpu,args | tail -n +2)
    echo "Warten bis zur nächsten Schleife!"
    # Bis zur nächsten Prüfung warten
    sleep ${TIME}
done