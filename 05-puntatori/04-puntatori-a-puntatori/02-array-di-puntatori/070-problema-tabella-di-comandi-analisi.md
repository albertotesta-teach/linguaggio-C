# Analisi – 070-problema-tabella-di-comandi.c

## 1. Problema

Un piccolo robot si muove su una griglia ricevendo sequenze di lettere: A avanti, I indietro, D gira a destra, S gira a sinistra. Le lettere sconosciute vengono ignorate. Dopo ogni sequenza il programma mostra posizione e direzione. Una riga vuota termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `comandi` | `void (*[])(int *, int *, int *)` | 4 | Tabella di puntatori a funzione |
| `lettere` | `char[]` | 5 | "AIDS": la posizione della lettera è l'indice del comando |
| `x`, `y`, `dir` | `int` | — | Posizione e direzione (0 nord … 3 ovest) |
| `trovata` | `const char *` | — | Lettera trovata con `strchr` |

| Funzione | Compito |
|----------|---------|
| `avanti`, `indietro`, `destra`, `sinistra` | Aggiornano posizione o direzione, stesso prototipo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Sequenza di comandi

**a) Input** – `AADA` partendo da (0, 0) verso nord

**b) Output** – (1, 2) verso est

**c) Variabili di supporto** – `trovata - lettere`

**d) Vincoli** – tutte le funzioni hanno lo stesso prototipo

**e) Assunzioni** – griglia senza limiti

**f) Algoritmo in linguaggio naturale** – per ogni lettera trovare l'indice in "AIDS" e chiamare `comandi[indice](&x, &y, &dir)`.

### Caso d'uso 2 – Rotazioni

**a) Input** – `SS` verso est

**b) Output** – verso ovest

**c) Variabili di supporto** – `*dir`

**d) Vincoli** – le rotazioni non usano x e y ma devono riceverli

**e) Assunzioni** – direzioni in senso orario

**f) Algoritmo in linguaggio naturale** – destra: `(dir + 1) % 4`; sinistra: `(dir + 3) % 4`.

### Caso d'uso 3 – Lettera sconosciuta

**a) Input** – `X`

**b) Output** – "'X' ignorato"

**c) Variabili di supporto** – `trovata` = `NULL`

**d) Vincoli** – un puntatore a funzione si chiama solo con un indice valido

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `strchr` restituisce `NULL` la lettera si salta.
