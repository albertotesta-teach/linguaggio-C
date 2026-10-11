# Analisi – 080-problema-limiti-di-sicurezza.c

## 1. Problema

Una pressa idraulica del laboratorio di meccanica è sorvegliata da un
programma che legge la pressione. Sopra 180 bar si segnala un allarme,
da 210 bar si esegue l'arresto di emergenza, dopo il quale la pressa resta
ferma. I limiti di sicurezza non devono poter essere modificati e il
sensore deve scrivere sempre nella stessa variabile. Alla fine si riportano
gli allarmi e la pressione massima.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `ALLARME`, `ARRESTO` | `const int` | — | Soglie in bar |
| `pressione` | `int` | — | Ultima lettura |
| `letture` | `int[]` | 10 | Letture simulate |
| `sensore` | `int *const` | — | Punta sempre a `pressione` |
| `soglia_allarme`, `soglia_arresto` | `const int *const` | — | Puntatori e valori costanti |
| `allarmi`, `massima`, `ferma` | `int` | — | Riepilogo e stato |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Letture normali e allarmi

**a) Input** – 120, 150, 175, 182, 168, 190, 205

**b) Output** – normale per i valori sotto 180, "allarme" per 182, 190, 205

**c) Variabili di supporto** – `allarmi`

**d) Vincoli** – il sensore scrive con `*sensore = letture[k]`; il puntatore
non può essere spostato

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni lettura confrontare la
pressione con `*soglia_arresto` e `*soglia_allarme`.

### Caso d'uso 2 – Arresto di emergenza

**a) Input** – 214

**b) Output** – "ARRESTO DI EMERGENZA"; le letture successive "(pressa ferma)"

**c) Variabili di supporto** – `ferma`

**d) Vincoli** – dopo l'arresto le letture non generano nuovi allarmi

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `ferma` è già 1 si registra solo
la lettura; se la pressione raggiunge la soglia di arresto si imposta `ferma`.

### Caso d'uso 3 – Riepilogo

**a) Input** – tutte le letture

**b) Output** – "Allarmi: 3, pressione massima: 214 bar, pressa in arresto"

**c) Variabili di supporto** – `massima`

**d) Vincoli** – la massima si aggiorna anche a pressa ferma

**e) Assunzioni** – letture positive

**f) Algoritmo in linguaggio naturale** – aggiornare `massima` a ogni lettura
e stampare il riepilogo.
