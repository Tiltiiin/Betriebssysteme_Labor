#!/bin/bash
#
# Skriptname: switch_car_brand_script.sh
#
# Beschreibung:
#   Dieses Skript fragt den Benutzer nach einer Automarke und verwendet eine `case`-Anweisung,
#   um den Standort der Fabrik basierend auf der Eingabe anzuzeigen.
#
# Verwendung:
#   ./switch_car_brand_script.sh
#
# Optionen:
#   - Der Benutzer wird nach einer Automarke gefragt. Basierend auf der Eingabe gibt das Skript
#     den Standort der entsprechenden Autofabrik aus (z. B. USA oder Deutschland). Wenn die Marke
#     nicht erkannt wird, wird eine Meldung angezeigt, dass der Standort der Fabrik unbekannt ist.
#
# Beispiel:
#   Der Benutzer gibt "Tesla" ein, und das Skript zeigt an, dass die Fabrik in den USA ist.
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

# Benutzer nach einer Automarke fragen
read -p "Geben Sie eine Automarke ein: " car

# `case`-Anweisung, um den Standort der Fabrik basierend auf der Eingabe anzuzeigen
case $car in
  Tesla)
    # Ausgabe, wenn der Benutzer "Tesla" eingibt
    echo "${car} Fabrik ist in den USA."
    ;;
  BMW | Mercedes | Audi | VW | Porsche)
    # Ausgabe, wenn der Benutzer eine deutsche Automarke eingibt
    echo -n "${car} Fabrik ist in Deutschland."
    echo
    ;;
  *)
    # Ausgabe, wenn die Automarke unbekannt ist
    echo -n "Fabrik für ${car} ist unbekannt."
    echo
    ;;
esac