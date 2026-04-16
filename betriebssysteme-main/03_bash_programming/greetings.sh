#!/bin/bash
#
# Skriptname: greetings.sh
#
# Beschreibung:
#   Dieses Skript fordert den Benutzer auf, einen Namen einzugeben. Wenn der Name leer bleibt, 
#   wird der Benutzer erneut zur Eingabe aufgefordert, bis ein gültiger Name eingegeben wird. 
#   Danach wird eine Begrüßungsnachricht mit dem eingegebenen Namen ausgegeben.
#
# Verwendung:
#   ./greetings.sh
#
# Optionen:
#   Keine.
#
# Beispiel:
#   Beim Ausführen des Skripts wird der Benutzer aufgefordert, einen Namen einzugeben.
#   Falls der Name leer ist, wird er erneut gefragt, bis eine gültige Eingabe erfolgt.
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

# Schleife, die überprüft, ob der Benutzer eine leere Eingabe gemacht hat
while [[ -z ${name} ]]
do
  # Warnung ausgeben, dass der Name nicht leer sein darf
  echo "Der Name darf nicht leer sein!!"
  # Benutzer erneut zur Eingabe eines Namens auffordern
  read -p "Geben Sie bitte erneut einen Namen ein: " name
done

# Begrüßungsnachricht mit dem eingegebenen Namen ausgeben
echo "Hallo ${name}"