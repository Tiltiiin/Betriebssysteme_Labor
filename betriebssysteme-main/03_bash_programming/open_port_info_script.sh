#!/bin/bash
#
# Skriptname: open_port_info_script.sh
#
# Beschreibung:
#   Dieses Skript listet alle offenen TCP-Ports auf, die auf dem System "LISTEN" sind, und gibt
#   für jeden Port die Prozessinformationen (PID) des Prozesses zurück, der den Port verwendet.
#
# Verwendung:
#   ./open_port_info_script.sh
#
# Optionen:
#   Keine.
#
# Beispiel:
#   Das Skript analysiert die Ausgaben von `netstat`, um alle offenen Ports zu finden, und verwendet
#   `fuser`, um die entsprechenden Prozessinformationen anzuzeigen.
#
# Voraussetzungen:
#   - Das Skript benötigt Root-Berechtigungen, um Prozessinformationen abzufragen.
#
# Exit-Status:
#   0 bei erfolgreichem Abschluss
#
# Autor:
#   [Dennis Grewe]
#
# Datum:
#   [09.10.2024]
#

# Schleife durch alle Ports, die auf "LISTEN" stehen
for PORT in `netstat -nat | grep -E 'LISTEN' | cut -f2-4 -d':' | cut -f1 -d' ' | sed -e 's/://g' | sort -nu`; 
do
  # Hole die Prozess-ID (PID), die den Port verwendet
  PID=`fuser -n tcp $PORT | cut -c1-6`
  
  # Ausgabe der Informationen zum offenen Port
  echo ""
  echo "INFORMATIONEN FÜR OFFENEN PORT $PORT:"
  echo "----------------------------"
  
  # Zeige detaillierte Prozessinformationen für die PID
  ps -f $PID
done