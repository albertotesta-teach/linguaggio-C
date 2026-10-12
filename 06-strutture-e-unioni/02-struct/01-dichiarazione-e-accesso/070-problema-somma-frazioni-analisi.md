# Analisi – 070-problema-somma-frazioni.c

## 1. Problema

Nel laboratorio di cucina le dosi sono frazioni. Il programma legge coppie di frazioni nella forma a/b c/d, le somma, riduce il risultato ai minimi termini e, se supera l'unità, lo stampa anche come numero misto. 0/0 termina; denominatori non positivi e numeratori negativi sono rifiutati.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Frazione` | `num, den` | frazione numeratore/denominatore |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `prima`, `seconda` | `Frazione` | — | Frazioni lette |
| `somma` | `Frazione` | — | Risultato |
| `divisore` | `int` | — | MCD di numeratore e denominatore |

| Funzione | Compito |
|----------|---------|
| `mcd(a, b)` | Massimo comune divisore con l'algoritmo di Euclide |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Somma semplice

**a) Input** – `1/2 1/3`

**b) Output** – "1/2 + 1/3 = 5/6"

**c) Variabili di supporto** – `somma`

**d) Vincoli** – a/b + c/d = (ad + cb) / bd

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – calcolare i due campi della somma e dividerli per il loro MCD.

### Caso d'uso 2 – Numero misto

**a) Input** – `3/4 5/12`

**b) Output** – "= 7/6 = 1 e 1/6"

**c) Variabili di supporto** – —

**d) Vincoli** – parte intera num/den, resto num%den

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stampare la parte intera e la frazione rimasta.

### Caso d'uso 3 – Frazione non valida

**a) Input** – `1/0 1/2`

**b) Output** – "Frazioni non valide."

**c) Variabili di supporto** – —

**d) Vincoli** – denominatore positivo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la coppia viene scartata e si legge la successiva.
