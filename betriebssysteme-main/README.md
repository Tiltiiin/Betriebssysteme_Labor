# Vorlesung Betriebbssysteme

    Disclaimer: This repository contains example code as part of the operating systems module (IT 105 2004) at Esslingen University of Applied Sciences. All contents are for educational purposes only. I do not intend for the content to be a substitute for professional usage and do not provide any guarantee for completness of the code.

The following documentation is only available in German.

Dieses Programmcode Repository beinhaltet Programmbeispiele im Rahmen der Vorlesung "Betriebssysteme" 
(IT 105 2004) an der Hochschule Esslingen. Bitte beachten Sie folgende Ausschlussklausel:

    Ausschlussklausel: Alle Inhalte dienen ausschließlich Bildungszwecken. Der Inhalt ist nicht für die professionelle Nutzung gedacht und gibt keine Garantie auf Vollständigkeit oder Lauffähigkeit.

## Voraussetzungen

Bevor du das Projekt klonst und die notwendigen Abhängigkeiten installierst, stelle sicher, dass du die folgenden Voraussetzungen erfüllst:

* **Git**: Du benötigst Git, um das Repository zu klonen. Installiere Git, wenn es noch nicht auf deinem System verfügbar ist.
Nutze dazu den Linux Packetmanager *apt*.
  
  ```bash
  $ sudo apt update
  $ sudo apt install git
  # check, ob git installiert ist
  $ git -v
  ```

* **SSH-Schlüssel**: Um mit GitLab zu interagieren, Code herunterladen, hochladen, etc. ist es notwendig einen Zuganstoken (auch access token) genannt zu generiern. Dies kannst du über dein GitLab Profil nach dem Login erledigen:

  ```bash
  -> Gehe dazu auf deine Profilkachel im linken oberen Bereich von Gitlab und klicken Sie auf diese
  -> Gehe zu den "Benutzereinstellungen" / "Preferences"
  -> Gehe zu "SSH Schlüssel" / "SSH Keys"
  -> Füge einen neuen Token hinzu / "Add new key"
  -> Klicke auf "Mehr erfahren" / "Learn more" um Information zur Erzeugung eines SSH Schlüssels in deiner Linux VM zu erfahren.
  -> Nachdem du erfolgreich einen Schlüssel erzeugt hast, kopiere den **öffentlichen/public** Inhalt deines Schlüssels (Dateiendung *.pub) in das "Schlüssel" / "Key" Feld in Gitlab und speichere die Daten.
  ```

Anschließend kannst du mit der Interaktion des Repositories weiter machen.

## Repository clonen

Um eine lokale Kopie des Programmcodes in der Linux VM zu erhalten, führe bitte folgenden Befehl in einem Terminal aus:

```bash
$ git clone git@gitlab.hs-esslingen.de:dgrewe/betriebssysteme.git
```

## Beispiele ausführen

Nachdem du eine lokale Kopie des Repositories bei dir in der Linux VM erstellt hast (siehe `clone`-Abschnitt), kannst du über das Terminal in das Verzeichnis wechseln und die darin liegenden Skripte ausführen.

```bash
$ # wechsel in das code repository
$ cd betriebssysteme
$ # ausführen des beispielscript zum anlegen, darstellen und löschen von dateien
$ bash 03_bash_programming/file_mgmt.sh
$ # ... und weitere scripte die du ausführen möchtest
```

## Kontakt

Bei Fragen oder Anmerkungen bitte einfach eine kurze Mail mit den Informationen an:

* [Dennis Grewe](mailto:dennis.grewe@hs-esslingen.de) 