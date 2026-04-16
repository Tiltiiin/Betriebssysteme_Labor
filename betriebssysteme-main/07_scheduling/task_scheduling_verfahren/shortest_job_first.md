# Shortes-Job-First Task-Scheduling Verfahren


   +-------------------+         +-------------------+
   |  Task 1: 3 units  |         |  Task 3: 2 units  | 
   +-------------------+         +-------------------+
   |  Task 2: 6 units  |         |  Task 1: 3 units  | 
   +-------------------+  ==>    +-------------------+
   |  Task 3: 2 units  |         |  Task 2: 6 units  | 
   +-------------------+         +-------------------+
       Original Queue                Processed Queue
       (Arrival order)            (Shortest Job First)

1.	Original Queue (Eingangsreihenfolge):
	* In dieser Reihenfolge kommen die Tasks in die Warteschlange, basierend auf ihrer Ankunftszeit:
	* Task 1 benötigt 3 Zeiteinheiten.
	* Task 2 benötigt 6 Zeiteinheiten.
	* Task 3 benötigt 2 Zeiteinheiten.
2.	Processed Queue (Nach SJF-Verfahren):
	* Im Shortest Job First-Verfahren wird der Task mit der kürzesten Ausführungszeit zuerst verarbeitet:
	* Task 3 wird zuerst ausgeführt, da er nur 2 Zeiteinheiten benötigt.
	* Dann wird Task 1 ausgeführt, der 3 Zeiteinheiten benötigt.
	* Schließlich wird Task 2 ausgeführt, der 6 Zeiteinheiten benötigt.