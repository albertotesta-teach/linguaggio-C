# Analisi – 050-problema-statistiche-griglia.c

## 1. Problema

La serra dell'istituto agrario è divisa in 4 × 5 settori con un sensore di temperatura ciascuno. Il responsabile vuole la media della serra, il settore più caldo, il numero di settori oltre 28 gradi e le stesse informazioni per ogni fila.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `serra` | `double[][]` | 4 × 5 | Temperature dei settori |
| `tutto` | `const double *` | — | `&serra[0][0]`, la matrice come blocco unico |
| `caldo` | `const double *` | — | Settore più caldo |
| `k` | `int` | — | Posizione del più caldo nel blocco |

| Funzione | Compito |
|----------|---------|
| `media(v, n)` | Media di n valori consecutivi |
| `massimo(v, n)` | Puntatore al valore più alto |
| `conta_oltre(v, n, soglia)` | Valori oltre la soglia |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tutta la serra

**a) Input** – `media(&serra[0][0], 20)`

**b) Output** – media 26.32, più caldo fila 2 settore 5 (29.4)

**c) Variabili di supporto** – `tutto`, `k`

**d) Vincoli** – le righe sono consecutive: 20 elementi da scorrere

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – passare il primo elemento e il numero totale; fila = k / 5 + 1, settore = k % 5 + 1.

### Caso d'uso 2 – Una fila

**a) Input** – `media(serra[1], 5)`

**b) Output** – Fila 2: media 27.44, massima 29.4, 2 oltre soglia

**c) Variabili di supporto** – `serra[f]`

**d) Vincoli** – la stessa funzione riceve una riga

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni fila passare `serra[f]` e 5.

### Caso d'uso 3 – Soglia

**a) Input** – soglia 28.0

**b) Output** – 4 settori su 20

**c) Variabili di supporto** – `conteggio`

**d) Vincoli** – soglia esclusa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – contare i valori maggiori della soglia.
