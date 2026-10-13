# Analisi – 040-problema-istogramma-dei-voti.c

## 1. Problema

Ogni docente usa la sua scala di voti, con i mezzi voti. Il programma legge il voto minimo e il massimo, alloca con calloc un contatore per ogni voto possibile ((massimo - minimo) × 2 + 1 contatori, già a zero), conta i voti letti fino a FINE e stampa l'istogramma dal voto più alto, il voto più frequente e la percentuale di sufficienze.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `conta` | `int *` | categorie (heap, calloc) | Un contatore per voto, a zero |
| `minimo`, `massimo`, `categorie` | `int` | — | Scala e numero di contatori |
| `totale`, `sufficienti`, `moda` | `int` | — | Statistiche |
| `parola`, `dopo` | `char[]`, `char` | 16 | Voto letto come testo e controllo dei caratteri in più |

| Funzione | Compito |
|----------|---------|
| `indice(voto, minimo)` | Posizione del contatore: (voto - minimo) × 2 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Istogramma

**a) Input** – `3 10`, poi `6 7.5 5 6.5 8 6 4.5 11 6 7.3 9 6.5 FINE`

**b) Output** – righe da 10.0 a 3.0 con un asterisco per voto; più frequente 6.0, sufficienze 80%

**c) Variabili di supporto** – `conta`

**d) Vincoli** – scala tra 1 e 10, minimo < massimo

**e) Assunzioni** – mezzi voti

**f) Algoritmo in linguaggio naturale** – calloc(categorie); per ogni voto valido conta[indice]++; stampa all'indietro.

### Caso d'uso 2 – Voti scartati

**a) Input** – `11`, `7.3`, `6.5x`

**b) Output** – "11 scartato", "7.3 scartato"

**c) Variabili di supporto** – `dopo`

**d) Vincoli** – voto nella scala e multiplo di 0.5

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sscanf con %lf%c deve leggere un solo valore.

### Caso d'uso 3 – Scala non valida

**a) Input** – `8 5`

**b) Output** – "Scala non valida."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna allocazione.
