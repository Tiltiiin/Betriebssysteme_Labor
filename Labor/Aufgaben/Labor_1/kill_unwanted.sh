#!/bin/bash

etime_to_seconds(){
    local t="${1}"
    local days=0 hours=0 minutes=0 seconds=0
    if [[ "${t}" == *-* ]]; then
        days="${t%%-*}"
        t="${t#*-}"
    fi
    IFS=':' read -r -a parts <<< "${t}"
    if [ ${#parts[@]} -eq 3 ]; then
        hours="${parts[0]}"; minutes="${parts[1]}"; seconds="${parts[2]}"
    elif [ ${#parts[@]} -eq 2 ]; then
        minutes="${parts[0]}"; seconds="${parts[1]}"
    else
        seconds="${parts[0]}"
    fi
    echo $(( 10#${days} * 86400 + 10#${hours} * 3600 + 10#${minutes} * 60 + 10#${seconds} ))
}

# Standard-Grenzwerte: RAM in GB, CPU in %, Wartezeit in Sekunden
MEMORY=32
UTILIZATION=50
TIME=15
HARDTIME=15
declare -A map

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
        NAME=$(echo "${LINE}"         | tr -s ' ' ';' | cut -d';' -f5)
        TIME_ELAPSED=$(etime_to_seconds "$(echo "${LINE}" | awk '{print $NF}')")

    
        RAM_MB=$(( RAM / 1024 ))

        if [ "${USER}" = "root" ] || [ "${USER}" = "jhub" ] || [ "${USER}" = "nginx" ]; then
            continue
        fi
        if [ -n "${map[${PID}]}" ]; then
            elapsed=$(( $(date +%s) - ${map[${PID}]} ))
            if [ "${elapsed}" -gt "${HARDTIME}" ]; then
                echo "kill -SIGKILL ${PID}: reagiert nicht nach ${elapsed}s"
                unset map[${PID}]
            fi
        elif [ "${RAM_MB}" -gt "${MEMORY_MB}" ] && [ "${CPU}" -gt "${UTILIZATION}" ] && [ "${TIME_ELAPSED}" -gt "${TIME}" ]; then
            echo "kill -SIGTERM ${PID} (${NAME}): RAM $((RAM_MB / 1024))GB > ${MEMORY}GB, CPU ${CPU}% > ${UTILIZATION}%"
            map[${PID}]=$(date +%s)
        fi
    # Header-Zeile von ps überspringen mit tail -n +2
    done < <(ps -eo pid,user,rss,%cpu,args,etime | tail -n +2)
    echo "Warten bis zur nächsten Prüfung (${TIME}s)..."
    # Bis zur nächsten Prüfung warten (konfigurierbar via -t)
    sleep "${TIME}"
done