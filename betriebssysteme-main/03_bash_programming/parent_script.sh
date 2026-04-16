#!/bin/bash
#
# Skriptname: parent_script.sh
#
# Beschreibung:
#   Dieses Skript führt ein anderes Skript namens "function.sh" im Debug-Modus aus.
#   Der Debug-Modus (`-x`) zeigt jeden Befehl und seine Argumente an, bevor er ausgeführt wird.
#
# Verwendung:
#   ./parent_script.sh
#
# Optionen:
#   Keine.
#
# Beispiel:
#   Das Skript ruft "function.sh" auf und führt es im Debug-Modus aus, was nützlich ist,
#   um zu sehen, welche Befehle ausgeführt werden und wie sie ausgeführt werden.
#
# Exit-Status:
#   0 bei erfolgreichem Abschluss
#
# Autor:
#   [Dennis Grewe]
#
# Datum:
#   [08.10.2024]
#

# Ausführung des Skripts "function.sh" im Debug-Modus
bash -x ./function.sh