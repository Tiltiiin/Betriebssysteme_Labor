#!/bin/bash
#
# Skriptname: function.sh
#
# Beschreibung:
#   Dieses einfache Skript definiert eine Funktion, die die Nachricht "Hallo BS Kurs" ausgibt,
#   und ruft diese Funktion auf.
#
# Verwendung:
#   ./function.sh
#
# Optionen:
#   Keine.
#
# Beispiel:
#   Beim Ausführen des Skripts wird die Nachricht "Hallo BS Kurs" auf der Konsole ausgegeben.
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

# Definition der Funktion 'hello', die eine Begrüßungsnachricht ausgibt
function hello() {
   echo "Hallo BS Kurs"
}

# Aufruf der Funktion 'hello'
hello