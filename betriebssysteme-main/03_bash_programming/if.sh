#!/bin/bash
#
# Skriptname: if.sh
#
# Beschreibung:
#   Dieses Skript fordert den Benutzer auf, einen Namen einzugeben. Wenn der Name leer ist,
#   wird der Benutzer aufgefordert, einen Namen anzugeben. Wenn ein Name eingegeben wird,
#   gibt das Skript eine Begrüßungsnachricht aus.
#
# Verwendung:
#   ./if.sh
#
# Optionen:
#   Keine.
#
# Beispiel:
#   Beim Ausführen des Skripts wird der Benutzer nach seinem Namen gefragt. Falls der Benutzer
#   keinen Namen eingibt, wird eine Fehlermeldung angezeigt. Wenn ein Name eingegeben wird,
#   erfolgt eine Begrüßung.
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

# Benutzer nach einem Namen fragen und in der Variable 'name' speichern
read -p "Wie ist Ihr Name? " name

# Überprüfung, ob der Name leer ist
if [[ -z ${name} ]]
then
  # Fehlermeldung, wenn kein Name eingegeben wurde
  echo "Bitte geben Sie einen Namen an.";
  # Hier können weitere Anweisungen eingefügt werden
else
  # Begrüßungsnachricht mit dem eingegebenen Namen ausgeben
  echo "Hallo ${name}";
fi