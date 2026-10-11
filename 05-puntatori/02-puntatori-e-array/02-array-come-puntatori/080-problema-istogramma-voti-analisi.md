# Analisi – 080-problema-istogramma-voti.c

## 1. Problema

Il docente vuole vedere come si distribuiscono i 24 voti di una verifica in
cinque fasce (insufficiente, sufficiente, discreto, buono, ottimo): per
ogni fascia il numero di studenti, la percentuale e una barra di asterischi,
poi la fascia più numerosa e il numero di sufficienze.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `voti` | `int[]` | 24 | Voti da 1 a 10 |
| `nomi` | `char[][]` | 5 × 16 | Nomi delle fasce |
| `conteggi` | `int[]` | 5 | Studenti per fascia, riempito dalla funzione |
| `prevalente` | `int` | — | Indice della fascia più numerosa |

| Funzione | Compito |
|----------|---------|
| `indice_fascia(voto)` | Fascia 0-4 di un voto |
| `conta_fasce(voti, n, conteggi)` | Azzera e riempie l'array dei conteggi |
| `posizione_massimo(v, n)` | Posizione dell'elemento maggiore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Conteggio per fasce

**a) Input** – i 24 voti

**b) Output** – 5, 7, 6, 3, 3

**c) Variabili di supporto** – `p`, `f`

**d) Vincoli** – la funzione riceve `conteggi` come `int *` e lo modifica
nell'array del chiamante

**e) Assunzioni** – voti validi da 1 a 10

**f) Algoritmo in linguaggio naturale**
1. Azzerare `*(conteggi + f)` per ogni fascia.
2. Per ogni voto calcolare la fascia `f` e incrementare `*(conteggi + f)`.

### Caso d'uso 2 – Istogramma

**a) Input** – fascia "sufficiente" con 7 studenti su 24

**b) Output** – `sufficiente  7  29%  *******`

**c) Variabili di supporto** – `k`

**d) Vincoli** – percentuale intera: la somma può non fare 100

**e) Assunzioni** – un asterisco per studente

**f) Algoritmo in linguaggio naturale** – percentuale = conteggio × 100 / 24;
stampare tanti `*` quanti sono gli studenti.

### Caso d'uso 3 – Fascia più numerosa

**a) Input** – conteggi `{5, 7, 6, 3, 3}`

**b) Output** – "Fascia piu' numerosa: sufficiente (7 studenti)"

**c) Variabili di supporto** – `prevalente`

**d) Vincoli** – a parità vale la fascia più bassa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la funzione tiene un puntatore
all'elemento maggiore e restituisce `migliore - v`.
