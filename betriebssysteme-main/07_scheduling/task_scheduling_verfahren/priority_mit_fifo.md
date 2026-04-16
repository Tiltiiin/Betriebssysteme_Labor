# Priority Task-Scheduling Verfahren mit FIFO


    Priorität (höchste zuerst)
    +-------------------+         +-------------------+
    |  Task 3: Prio 1    |         |  Task 3: Prio 1   | -> Wird als Erstes ausgeführt
    +-------------------+         +-------------------+
    |  Task 1: Prio 2    |         |  Task 1: Prio 2   | -> Wird als Zweites ausgeführt
    +-------------------+  ==>    +-------------------+
    |  Task 2: Prio 3    |         |  Task 2: Prio 3   | -> Wird als Letztes ausgeführt
    +-------------------+         +-------------------+
        Initial Queue                   Ausführungsreihenfolge
    (sortiert nach Priorität)          (FIFO innerhalb gleicher Priorität)      
                              

Erklärung:

1.	Initial Queue (Sortiert nach Priorität):
    * Die Tasks werden basierend auf ihrer Priorität sortiert. Die höchste Priorität (in diesem Fall Prio 1) wird zuerst ausgeführt, dann die niedrigere Priorität (Prio 2), und so weiter.
	* Task 3 hat die höchste Priorität (Prio 1).
	* Task 1 hat die zweitniedrigste Priorität (Prio 2).
	* Task 2 hat die niedrigste Priorität (Prio 3).
2.	FIFO innerhalb gleicher Priorität:
	* Falls mehrere Tasks dieselbe Priorität haben, wird das FIFO-Prinzip innerhalb dieser Prioritätsgruppe verwendet: Der zuerst eingetroffene Task wird zuerst ausgeführt.
	* In diesem Beispiel haben die Tasks unterschiedliche Prioritäten, daher gibt es keine Konflikte im FIFO.
3.	Ausführungsreihenfolge:
	* Task 3 (Prio 1) wird als erstes verarbeitet, da er die höchste Priorität hat.
	* Danach wird Task 1 (Prio 2) ausgeführt.
	* Zuletzt wird Task 2 (Prio 3) bearbeitet, da er die niedrigste Priorität hat.