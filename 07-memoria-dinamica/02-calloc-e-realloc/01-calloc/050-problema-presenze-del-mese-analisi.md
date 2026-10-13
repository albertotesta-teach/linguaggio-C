# Analisi – 050-problema-presenze-del-mese.c

## 1. Problema

Il coordinatore riporta le assenze di un mese. Il programma legge il numero di studenti e di giorni, alloca con calloc una matrice giorni × studenti in un solo blocco (tutti presenti, cioè 0) e per ogni giorno segna gli assenti. Stampa la tabella del mese, le assenze di ogni studente con un avviso oltre il 25% e il giorno con più assenti.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `assente` | `int *` | giorni × studenti (heap, calloc) | 1 = assente; elemento (g, s) in assente[g × studenti + s] |
| `studenti`, `giorni` | `int` | — | Dimensioni lette |
| `numero` | `int` | — | Studente assente letto (0 termina il giorno) |
| `peggiore`, `assenti_peggiore` | `int` | — | Giorno con più assenti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Mese di 8 giorni

**a) Input** – `5 8`, poi per ogni giorno gli assenti terminati da 0

**b) Output** – tabella con A e .; studente 2 con 4 assenze "oltre il 25%"; giorno 6 con 3 assenti

**c) Variabili di supporto** – `assente`

**d) Vincoli** – studenti 1-30, giorni 1-25

**e) Assunzioni** – numeri degli studenti da 1

**f) Algoritmo in linguaggio naturale** – calloc della matrice; assente[g × studenti + numero - 1] = 1; somme per colonna e per riga.

### Caso d'uso 2 – Studente inesistente

**a) Input** – `9 0` con 5 studenti

**b) Output** – "studente 9 inesistente"

**c) Variabili di supporto** – —

**d) Vincoli** – numero da 1 a studenti

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il numero non viene segnato.

### Caso d'uso 3 – Soglia

**a) Input** – 4 assenze su 8 giorni

**b) Output** – "oltre il 25%"

**c) Variabili di supporto** – `conta`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – conta × 4 > giorni, senza divisioni.
