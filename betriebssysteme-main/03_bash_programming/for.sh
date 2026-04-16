#!/bin/bash
#
# Skriptname: for.sh
#
# Beschreibung:
#   Dieses einfache Skript durchläuft eine Liste von Benutzernummern (1-5) und gibt jede Nummer auf der Konsole aus.
#
# Verwendung:
#   ./for.sh
#
# Optionen:
#   Keine.
#
# Beispiel:
#   Beim Ausführen des Skripts werden die Nummern 1 bis 5 nacheinander ausgegeben.
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

# Definieren einer Liste von Benutzernummern
users="John Maggie Darek Judy Vincent"

# Schleife, um durch jede Benutzernummer zu iterieren
for number in ${users}
do
  # Ausgabe der aktuellen Benutzernummer
  echo "${number}"
done