# Analisi – 070-problema-numerazione-delle-righe.c

## 1. Problema

Per discutere in classe un testo serve poter citare le righe. Il filtro copia stdin su stdout mettendo il numero davanti a ogni riga non vuota; le righe vuote restano vuote e non consumano un numero. Il totale va su stderr.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `c` | `int` | — | Carattere letto o EOF |
| `inizio_riga` | `int` | — | 1 se il prossimo carattere apre una riga |
| `numero`, `vuote` | `int` | — | Righe numerate e righe vuote |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Strofa

**a) Input** – tre versi con una riga vuota, poi Ctrl+D

**b) Output** – versi numerati 1, 2, 3; "righe numerate: 3, righe vuote: 1"

**c) Variabili di supporto** – `inizio_riga`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se inizio_riga e c != '\n' si stampa il numero.

### Caso d'uso 2 – Con redirezione

**a) Input** – `< saluto.txt`

**b) Output** – le due righe numerate

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il totale su stderr non entra nel file.

### Caso d'uso 3 – Testo vuoto

**a) Input** – solo Ctrl+D

**b) Output** – righe numerate: 0

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo non parte.
