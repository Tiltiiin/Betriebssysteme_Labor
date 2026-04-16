# Round Robin Task-Scheduling Verfahren


    Time Slice = 4 units

    +-------------------+         +-------------------+
    |  Task 1: 10 units |         |  Task 1: 6 units  |
    +-------------------+         +-------------------+
    |  Task 2: 8 units  |         |  Task 2: 4 units  |
    +-------------------+  ==>    +-------------------+
    |  Task 3: 6 units  |         |  Task 3: 2 units  |
    +-------------------+         +-------------------+
       Initial Queue                After 1st Round
      (Arrival order)              (Each Task gets 4 units)

    +-------------------+         +-------------------+
    |  Task 1: 6 units  |         |  Task 1: 2 units  |
    +-------------------+         +-------------------+
    |  Task 2: 4 units  |         |  Task 2: Done     |
    +-------------------+  ==>    +-------------------+
    |  Task 3: 2 units  |         |  Task 3: Done     |
    +-------------------+         +-------------------+
       After 2nd Round               After 3rd Round
    (Each Task gets 4 units)       (Final Processing)

1.	Initial Queue (Anfangszustand):
	* Es gibt drei Tasks:
	* Task 1 benötigt 10 Zeiteinheiten.
	* Task 2 benötigt 8 Zeiteinheiten.
	* Task 3 benötigt 6 Zeiteinheiten.
	* Die Zeitscheibe (Time Slice) ist auf 4 Einheiten festgelegt.
2.	1. Runde:
	* Jeder Task erhält 4 Zeiteinheiten, um auszuführen:
	* Task 1 reduziert sich von 10 auf 6 Einheiten.
	* Task 2 reduziert sich von 8 auf 4 Einheiten.
	* Task 3 reduziert sich von 6 auf 2 Einheiten.
3.	2. Runde:
	* In der zweiten Runde erhält jeder verbleibende Task wieder 4 Einheiten:
	* Task 1 reduziert sich von 6 auf 2 Einheiten.
	* Task 2 wird fertig (4 Einheiten -> 0).
	* Task 3 wird ebenfalls fertig (2 Einheiten -> 0).
4.	3. Runde:
	* Task 1 benötigt noch 2 Einheiten und wird in dieser Runde vollständig verarbeitet.