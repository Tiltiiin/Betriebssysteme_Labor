#!/bin/bash
#
# Skriptname: file_management_script.sh
#
# Musterlösung
#
# Beschreibung:
#   Dieses Skript bietet grundlegende Dateimanagement-Funktionen. Der Benutzer kann eine Datei erstellen,
#   den Inhalt einer Datei anzeigen, eine Datei löschen oder das Skript beenden.
#
# Verwendung:
#   ./file_management_script.sh
#
# Optionen:
#   - Der Benutzer wird aufgefordert, eine der folgenden Optionen auszuwählen:
#     1) Datei erstellen und Inhalt hinzufügen
#     2) Datei anzeigen
#     3) Datei löschen
#     4) Skript beenden
#
# Beispiel:
#   Der Benutzer gibt nach dem Start des Skripts eine Zahl (1-4) ein, um die entsprechende Aktion auszuführen.
#
# Exit-Status:
#   0 bei erfolgreichem Beenden des Programms
#   andere Werte bei Fehlern (nicht explizit behandelt)
#
# Autor:
#   [Dennis Grewe]
#
# Datum:
#   [08.10.2024]
#

# Funktion zur Anzeige des Menüs
show_menu() {
    echo "===== Dateiverwaltungsskript ====="
    echo "1) Datei erstellen und Inhalt hinzufügen"
    echo "2) Datei anzeigen"
    echo "3) Datei löschen"
    echo "4) Beenden"
}

# Funktion zum Erstellen einer Datei und Hinzufügen von Inhalt
create_file() {
    read -p "Geben Sie den Namen der zu erstellenden Datei ein: " filename
    # Überprüfen, ob die Datei bereits existiert
    if [[ -f $filename ]]; then
        echo "Fehler: Datei '$filename' existiert bereits!"
    else
        touch "$filename"
        echo "Datei '$filename' erfolgreich erstellt."

        # Benutzer nach dem Inhalt der Datei fragen
        echo "Geben Sie den Inhalt der Datei ein (Drücken Sie Strg+D zum Speichern und Beenden):"
        cat > "$filename"  # Inhalt in die Datei schreiben
        echo "Inhalt zu '$filename' hinzugefügt."
    fi
}

# Funktion zur Anzeige des Dateiinhalts
view_file() {
    read -p "Geben Sie den Namen der Datei an, die Sie anzeigen möchten: " filename
    # Überprüfen, ob die Datei existiert
    if [[ -f $filename ]]; then
        echo "===== Inhalt von $filename ====="
        cat "$filename"  # Dateiinhalt anzeigen
        echo "================================="
    else
        echo "Fehler: Datei '$filename' existiert nicht!"
    fi
}

# Funktion zum Löschen einer Datei
delete_file() {
    read -p "Geben Sie den Namen der zu löschenden Datei ein: " filename
    # Überprüfen, ob die Datei existiert
    if [[ -f $filename ]]; then
        rm "$filename"  # Datei löschen
        echo "Datei '$filename' erfolgreich gelöscht."
    else
        echo "Fehler: Datei '$filename' existiert nicht!"
    fi
}

# Hauptprogramm
# Endlosschleife für das Menü, bis der Benutzer das Skript beendet
while true; do
    show_menu  # Menü anzeigen
    read -p "Wählen Sie eine Option (1-4): " choice

    # Überprüfung der Benutzereingabe und entsprechende Aktion ausführen
    case $choice in
        1)
            create_file  # Datei erstellen und Inhalt hinzufügen
            ;;
        2)
            view_file  # Datei anzeigen
            ;;
        3)
            delete_file  # Datei löschen
            ;;
        4)
            echo "Programm wird beendet..."
            exit 0  # Programm beenden mit Status 0 (erfolgreich)
            ;;
        *)
            # Ungültige Option behandeln
            echo "Ungültige Option, bitte versuchen Sie es erneut."
            ;;
    esac
done