# FIFO Task-Scheduling Verfahren


    Enqueue (Insert)          Queue (FIFO)                    Dequeue (Remove)        
                          +-------------------+   process   +----------+
                          |   Task 1 (First)   ----------->            |
                          +-------------------+             +----------+
                          |   Task 2          |
                          +-------------------+
                          |   Task 3          |
    +----------------+    +-------------------+
    | Task 4 (Last)  | -------->              |
    +----------------+    +-------------------+                          
                              

Erklärung:

1. Enqueue (Einfügen) erfolgt am unteren Ende der Warteschlange:
    * Neue Tasks (z.B. Task 4) werden am unteren Ende der Warteschlange hinzugefügt.
2. Warteschlange:
    * Die Tasks werden in der Reihenfolge, in der sie eintreffen, in die Warteschlange gestellt, von oben nach unten. Task 1 kommt zuerst, dann Task 2 und schließlich Task 3.
3.	Dequeue (Entfernen) erfolgt am oberen Ende der Warteschlange:
    * Tasks werden vom oberen Ende entfernt. Task 1, der als Erster eingetroffen ist, wird zuerst verarbeitet und entfernt, gefolgt von Task 2 und schließlich Task 3.