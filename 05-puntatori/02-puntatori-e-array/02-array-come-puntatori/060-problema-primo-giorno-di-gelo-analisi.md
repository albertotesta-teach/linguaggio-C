# Analisi – 060-problema-primo-giorno-di-gelo.c

## 1. Problema

Un'azienda agricola conserva le temperature minime dei 30 giorni di
novembre. Per un periodo scelto dall'utente (dal giorno `a` al giorno `b`)
il programma indica la minima più bassa, il primo giorno sotto zero e il
numero di giorni di gelo. Con `0 0` termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `minime` | `int[]` | 30 | Minima di ogni giorno, il giorno 1 ha indice 0 |
| `a`, `b` | `int` | — | Primo e ultimo giorno del periodo |
| `inizio` | `const int *` | — | `minime + a - 1`, inizio del sottoarray |
| `n` | `int` | — | `b - a + 1`, giorni del periodo |
| `primo` | `int` | — | Posizione del primo gelo nel periodo, -1 se nessuno |

| Funzione | Compito |
|----------|---------|
| `primo_sotto_zero(t, n)` | Posizione della prima temperatura negativa |
| `conta_sotto_zero(t, n)` | Numero di temperature negative |
| `minima(t, n)` | Temperatura più bassa |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Periodo con gelo

**a) Input** – `20 25`

**b) Output** – minima −5; primo gelo giorno 23 (−1 gradi); 3 giorni di gelo

**c) Variabili di supporto** – `inizio = minime + 19`, `n = 6`, `primo = 3`

**d) Vincoli** – la posizione restituita è relativa al periodo: il giorno è
`a + primo`

**e) Assunzioni** – 0 gradi non è gelo

**f) Algoritmo in linguaggio naturale**
1. Calcolare `inizio` e `n`.
2. Chiamare le tre funzioni sul sottoarray.
3. Riportare la posizione al giorno del mese sommando `a`.

### Caso d'uso 2 – Periodo senza gelo

**a) Input** – `1 10`

**b) Output** – minima 0, "Nessun giorno di gelo."

**c) Variabili di supporto** – `primo` = -1

**d) Vincoli** – il ciclo di ricerca si ferma a `t + n`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il puntatore avanza finché non
trova un valore negativo o arriva alla fine; se è arrivato alla fine la
funzione restituisce -1.

### Caso d'uso 3 – Periodo non valido

**a) Input** – `25 20`

**b) Output** – "Periodo non valido: servono 1 <= a <= b <= 30."

**c) Variabili di supporto** – nessuna

**d) Vincoli** – un sottoarray non deve mai uscire dall'array

**e) Assunzioni** – un input non numerico termina il programma

**f) Algoritmo in linguaggio naturale** – controllare `a ≥ 1`, `b ≤ 30` e
`a ≤ b` prima di costruire il sottoarray.
