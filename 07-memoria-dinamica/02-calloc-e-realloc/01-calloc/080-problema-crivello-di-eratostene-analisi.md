# Analisi – 080-problema-crivello-di-eratostene.c

## 1. Problema

Il programma trova i numeri primi fino a n con il crivello di Eratostene. Serve un flag per ogni numero da 0 a n, all'inizio tutti a 0 (nessun numero cancellato): calloc alloca e azzera n + 1 byte. Stampa quanti primi ci sono, l'elenco (o i primi 10 e gli ultimi 10) e le coppie di primi gemelli.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `composto` | `char *` | n + 1 (heap, calloc) | 1 se il numero è composto |
| `n` | `int` | — | Limite (2-1000000) |
| `primi`, `gemelli`, `contati` | `int` | — | Conteggi e posizione nella stampa |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Primi fino a 100

**a) Input** – `100`

**b) Output** – 25 primi, elencati tutti; 8 coppie di gemelli

**c) Variabili di supporto** – `composto`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni p con p × p ≤ n non cancellato, cancellare i multipli da p × p.

### Caso d'uso 2 – Un milione

**a) Input** – `1000000`

**b) Output** – 78498 primi, i primi 10 ... gli ultimi 10; 8169 coppie

**c) Variabili di supporto** – —

**d) Vincoli** – al massimo 1000000

**e) Assunzioni** – circa 1 MB di flag

**f) Algoritmo in linguaggio naturale** – stampa ridotta se i primi sono più di 30.

### Caso d'uso 3 – Numero non valido

**a) Input** – `1`

**b) Output** – "Numero non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna allocazione.
