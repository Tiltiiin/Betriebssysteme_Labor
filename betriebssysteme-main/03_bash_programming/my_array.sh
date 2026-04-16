#!/bin/bash
#
# Skriptname: my_array.sh
#
# Beschreibung:
#   Dieses Skript definiert ein Array mit drei Zeichenketten ("Mein", "Name", "ist") und gibt
#   das zweite Element des Arrays auf der Konsole aus.
#
# Verwendung:
#   ./my_array.sh
#
# Optionen:
#   Keine.
#
# Beispiel:
#   Beim Ausführen des Skripts wird das zweite Element des Arrays ("Name") auf der Konsole ausgegeben.
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

# Definition eines Arrays mit drei Zeichenketten
my_array=("Mein" "Name" "ist")

# Ausgabe des zweiten Elements des Arrays (Index 1, da Arrays bei 0 beginnen)
echo ${my_array[1]}