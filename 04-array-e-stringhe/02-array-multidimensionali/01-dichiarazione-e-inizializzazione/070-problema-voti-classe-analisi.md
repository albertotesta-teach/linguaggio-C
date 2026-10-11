# Analisi – 070-problema-voti-classe.c

## 1. Problema

Per lo scrutinio il coordinatore prepara il tabellone dei voti di 6 studenti
in 4 materie. Il programma deve stampare il tabellone con media e numero di
insufficienze di ogni studente, segnalare chi ha almeno un debito e contare
gli insufficienti di ogni materia.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `voti` | `int[][]` | 6 × 4 | Riga = studente, colonna = materia |
| `studenti` | `char[][]` | 6 × 16 | Nome dello studente, parallelo alle righe |
| `materie` | `char[][]` | 4 × 12 | Nome della materia, parallelo alle colonne |
| `somma`, `insufficienze` | `int` | — | Accumulatore e contatore della riga corrente |
| `studenti_con_debito` | `int` | — | Contatore globale |
| `insufficienti_materia` | `int` | — | Contatore della colonna corrente |

Costante `SUFFICIENZA` = 6.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tabellone con media e insufficienze

**a) Input** – matrici `voti`, `studenti`, `materie`

**b) Output** – una riga per studente con i 4 voti, la media con due
decimali, il numero di insufficienze e la segnalazione "<- debito"

**c) Variabili di supporto** – `somma`, `insufficienze`

**d) Vincoli** – la media si calcola con il cast `(double) somma / MATERIE`

**e) Assunzioni** – voti interi da 1 a 10

**f) Algoritmo in linguaggio naturale**
1. Stampare l'intestazione con i nomi delle materie.
2. Per ogni studente: azzerare somma e insufficienze, stampare il nome.
3. Per ogni materia: stampare il voto, sommarlo, contarlo se minore di 6.
4. Stampare media e insufficienze; se ce ne sono, segnalare il debito e
   incrementare `studenti_con_debito`.
5. Stampare quanti studenti hanno almeno un debito.

### Caso d'uso 2 – Insufficienze per materia

**a) Input** – matrice `voti`

**b) Output** – per ogni materia il numero di studenti insufficienti
(es. Matematica: 2)

**c) Variabili di supporto** – `insufficienti_materia`

**d) Vincoli** – scorrimento per colonne: esterno sulle materie, interno sugli studenti

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Per ogni materia: azzerare il contatore.
2. Per ogni studente: se il voto in quella materia è minore di 6, contarlo.
3. Stampare nome della materia e conteggio.
