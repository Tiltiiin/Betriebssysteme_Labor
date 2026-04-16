#!/bin/bash
#
# Skriptname: file_mgmt_script.sh aus der Vorlesung
#
# Beschreibung:
#   Dieses Skript bietet ein einfaches Dateimanagementsystem mit den folgenden Optionen:
#   1) Datei erstellen
#   2) Dateiinhalte anzeigen
#   3) Datei löschen
#   4) Skript beenden
#
# Verwendung:
#   ./file_mgmt_script.sh
#
# Optionen:
#   Der Benutzer wird aufgefordert, eine der obigen Optionen auszuwählen.
#
# Beispiel:
#   Nach dem Start des Skripts gibt der Benutzer eine Zahl (1-4) ein, um die entsprechende Aktion auszuführen.
#
# Exit-Status:
#   0 bei erfolgreichem Beenden des Programms
#   andere Werte bei Fehlern (nicht explizit behandelt)
#
# Autor:
#   [Dein Name]
#
# Datum:
#   [Datum der Erstellung]
#

# Variable zur Speicherung der Benutzerauswahl
choice=0

# Funktion zur Anzeige des Menüs
show_menu() {
    echo "======= DATEI-MANAGEMENT-SKRIPT ======"
    echo "1) Datei erstellen"
    echo "2) Dateiinhalte anzeigen"
    echo "3) Datei löschen"
    echo "4) Skript beenden"
}

# == HAUPTPROGRAMM ==
# Das Skript startet mit einer Schleife, die mehrere Benutzereingaben ermöglicht.
# Die Schleife läuft solange, bis die Eingabe 4 (Skript beenden) erfolgt.
while [[ ${choice} != 4 ]]; do
    # Menü dem Benutzer anzeigen
    show_menu
    # Benutzer nach der Auswahl fragen
    read -p "Wählen Sie eine Option (1-4): " choice 

    # Verarbeitung der Benutzereingabe
    case $choice in
        1)
        # Datei erstellen
        read -p "Bitte geben Sie einen Namen für die zu erstellende Datei an: " file_name
        touch $file_name  # Datei erstellen
        # Benutzer nach dem Inhalt der Datei fragen
        echo "Bitte geben Sie den Inhalt der Datei ein (CTRL-D zum Beenden):"
        cat > "$file_name"  # Inhalt in die Datei schreiben
        echo "Inhalt zur Datei '$file_name' hinzugefügt."
        sleep 3  # kurze Pause zur besseren Benutzererfahrung
        ;;
        2)
        # Dateiinhalte anzeigen
        read -p "Bitte geben Sie den Namen der Datei an, deren Inhalt angezeigt werden soll: " file_name
        cat $file_name  # Dateiinhalt anzeigen
        echo
        ;;
        3)
        # Datei löschen
        read -p "Bitte geben Sie den Namen der zu löschenden Datei an: " file_name
        rm $file_name  # Datei löschen
        ;;
        4)
        # Skript beenden
        echo "Programm wird beendet..."
        exit 0  # Exit-Status 0 = Programm wurde erfolgreich beendet
        ;;
        *)
        # Ungültige Auswahl
        echo "Ungültige Option, bitte erneut versuchen."
        ;;
    esac
done