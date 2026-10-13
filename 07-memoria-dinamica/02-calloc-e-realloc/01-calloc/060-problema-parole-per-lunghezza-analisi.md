# Analisi – 060-problema-parole-per-lunghezza.c

## 1. Problema

Per valutare la leggibilità di un testo il programma conta le parole per lunghezza. L'insegnante sceglie la lunghezza massima da distinguere: calloc alloca massimo + 1 contatori, e le parole più lunghe finiscono nell'ultimo. Alla fine stampa la distribuzione con le percentuali, la lunghezza media e la parola più lunga.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `conta` | `int *` | massimo + 1 (heap, calloc) | conta[k]: parole di k lettere, conta[massimo]: massimo o più |
| `riga` | `char[]` | 200 | Riga letta |
| `piu_lunga` | `char[]` | 40 | Parola più lunga trovata |
| `parole`, `lettere_totali` | `int` | — | Per la media |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Testo scientifico

**a) Input** – `8`, poi due righe sulla fotosintesi, `FINE`

**b) Output** – 16 parole; 8+ lettere: 7 (43.8%); media 6.3; più lunga "clorofilliana"

**c) Variabili di supporto** – `conta`

**d) Vincoli** – massimo da 2 a 30

**e) Assunzioni** – una parola è una sequenza di lettere

**f) Algoritmo in linguaggio naturale** – per ogni parola conta[min(lunghezza, massimo)]++.

### Caso d'uso 2 – Apostrofo

**a) Input** – `l'energia`

**b) Output** – due parole: "l" e "energia"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – l'apostrofo separa

**f) Algoritmo in linguaggio naturale** – il carattere non alfabetico chiude la parola.

### Caso d'uso 3 – Valore non valido

**a) Input** – `1`

**b) Output** – "Valore non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna allocazione.
