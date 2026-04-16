# Completly Fair Scheduling (CFS) Verfahren

CFS versucht, die CPU-Zeit fair zu verteilen, indem Threads mit geringer virtueller Laufzeit bevorzugt behandelt werden. Dieses Prinzip sorgt dafür, dass jeder Thread eine ähnliche Menge an CPU-Zeit erhält, wodurch der Scheduler “completely fair” wird.

        +---------------------------------------------------------------------------------------+
        | Ready Queue (RB Tree)                                                                 |
        |                                                                                       |
        |  +-------------+     +-------------+     +-------------+     +-------------+          |
        |  | Thread 1    |     | Thread 2    |     | Thread 3    |     | Thread 4    |          |
        |  | Virtual     |     | Virtual     |     | Virtual     |     | Virtual     |          |
        |  | Runtime: 10 |     | Runtime: 20 |     | Runtime: 30 |     | Runtime: 5  |          |
        |  +-------------+     +-------------+     +-------------+     +-------------+          |
        |                                                                                       |
        +---------------------------------------------------------------------------------------+
                                            |
                                            |
                                        Pick Process with
                                    smallest virtual runtime
                                            |
                                            v
                                    +-----------------------+
                                    |    Context Switch     |
                                    |  (Switch to chosen    |
                                    |      process)         |
                                    +-----------------------+
                                            |
                                            v
                                    +-----------------------+
                                    |   Run Process (e.g.,  |
                                    |   Thread 4 with       |
                                    |   increased virtual   |
                                    |   runtime)            |
                                    +-----------------------+
                                            |
                                            v
                                    +-----------------------+
                                    |                       |
                                    |  Add New Process to   |
                                    |       Ready Queue     |
                                    |       (RB Tree)       |
                                    +-----------------------+

Erklärung der Schritte mit virtuellen Laufzeiten:

1. `Ready Queue (RB Tree)` mit Threads und virtuellen Laufzeiten:
    * Die Threads befinden sich in einem Red-Black-Tree (RB Tree) und sind nach ihrer virtuellen Laufzeit sortiert. Die virtuelle Laufzeit ist ein Maß für die CPU-Zeit, die ein Thread bereits genutzt hat. Threads mit kürzerer virtueller Laufzeit werden bevorzugt.
	Beispiel:
	    * Thread 4 hat die geringste virtuelle Laufzeit von 5, daher wird er zuerst ausgewählt.
	    * Die anderen Threads (Thread 1, 2 und 3) haben höhere virtuelle Laufzeiten.
2. `Pick Process with smallest “virtual runtime”`:
    * Der Scheduler durchsucht den RB Tree und wählt den Thread mit der kleinsten virtuellen Laufzeit (hier Thread 4) aus.
3. `Context Switch`:
    * Ein Kontextwechsel wird durchgeführt, um den ausgewählten Thread (Thread 4) auf der CPU auszuführen.
4. `Run Process (Increase virtual runtime)`:
    * Der ausgewählte Thread (Thread 4) wird auf der CPU ausgeführt, und seine virtuelle Laufzeit wird während der Ausführung erhöht. Wenn Thread 4 mehr CPU-Zeit erhält, wird seine virtuelle Laufzeit im RB Tree entsprechend angepasst, was möglicherweise dazu führt, dass er bei der nächsten Auswahl nicht mehr bevorzugt wird.
5. `Add New Process to Ready Queue (RB Tree)`:
    * Falls ein neuer Thread oder Prozess erstellt wird, wird er basierend auf einer fairen Startlaufzeit dem RB Tree hinzugefügt.

