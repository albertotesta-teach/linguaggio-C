# Analisi – 050-problema-misure-del-laboratorio.c

## 1. Problema

Ogni gruppo di fisica misura più volte il periodo di un pendolo. Il numero di misure cambia da gruppo a gruppo: l'array si alloca dopo averlo letto. Il programma calcola media e scarto quadratico medio, segnala le misure che distano dalla media più di due scarti e ricalcola la media senza di esse.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `periodo` | `double *` | n elementi (heap) | Misure in secondi |
| `n`, `letti` | `int` | — | Misure previste e inserite |
| `media`, `scarto` | `double` | — | Statistiche |
| `somma_valide`, `valide` | `double`, `int` | — | Media senza anomalie |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Una misura anomala

**a) Input** – `10` misure, tra cui `1.68`

**b) Output** – media 1.438 s, scarto 0.086 s, misura 7 anomala, media senza anomalie 1.411 s

**c) Variabili di supporto** – `somma_quadrati`

**d) Vincoli** – almeno 3 misure

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – s = radice di somma (x - media)² / (n - 1); anomala se |x - media| > 2 s.

### Caso d'uso 2 – Nessuna anomalia

**a) Input** – misure vicine tra loro

**b) Output** – "nessuna"

**c) Variabili di supporto** – `valide`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – valide resta uguale a n.

### Caso d'uso 3 – Misura non valida

**a) Input** – `4`, poi `1.4 1.5 -2`

**b) Output** – "Misura 3 non valida: inserimento interrotto."

**c) Variabili di supporto** – `letti`

**d) Vincoli** – misure positive

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo di lettura si ferma; il blocco si libera senza calcoli.
