# Analisi – 060-problema-coppia-piu-vicina.c

## 1. Problema

Alla corsa campestre i tempi di arrivo sono registrati nell'ordine dei pettorali. Il giudice vuole i due atleti arrivati più vicini tra loro e il loro distacco; sotto i 2 decimi serve il fotofinish.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `tempi` | `int[]` | 8 | Tempi in decimi di secondo, per pettorale |
| `a`, `b` | `const int *` | — | I due tempi più vicini, ricevuti dalla funzione |
| `d` | `int` | — | Distacco minimo |

| Funzione | Compito |
|----------|---------|
| `coppia_piu_vicina(tempi, n, &a, &b)` | Restituisce la distanza minima e scrive i due puntatori |
| `distanza(x, y)` | Valore assoluto della differenza |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Coppia più vicina

**a) Input** – gli 8 tempi

**b) Output** – pettorali 1 e 4, distacco 0.1 s

**c) Variabili di supporto** – `p`, `q`, `minima`

**d) Vincoli** – la funzione scrive due puntatori del chiamante: parametri `const int **`

**e) Assunzioni** – a parità vale la prima coppia trovata

**f) Algoritmo in linguaggio naturale** – per ogni coppia (p, q) con q dopo p, se la distanza è minore di `minima` aggiornare `minima`, `*primo = p`, `*secondo = q`.

### Caso d'uso 2 – Dal puntatore al pettorale

**a) Input** – `a` punta a `tempi[0]`

**b) Output** – pettorale 1

**c) Variabili di supporto** – `a - tempi`

**d) Vincoli** – i puntatori restituiti puntano dentro l'array del main

**e) Assunzioni** – pettorali numerati da 1

**f) Algoritmo in linguaggio naturale** – pettorale = `a - tempi + 1`.

### Caso d'uso 3 – Fotofinish

**a) Input** – distacco 1 decimo

**b) Output** – "serve il fotofinish"

**c) Variabili di supporto** – `d`

**d) Vincoli** – soglia 2 decimi

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare il valore restituito con 2.
