# Analisi – 050-problema-celle-foglio.c

## 1. Problema

Il foglio delle spese della gita ha 6 righe e 3 colonne; ogni cella è vuota, un numero o un testo. scrivi decide il tipo: numero se tutto il contenuto è un numero, altrimenti testo. La somma di una colonna usa uno switch sull'etichetta: somma i numeri e conta i testi ignorati.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Cella` | `tipo, union v {numero, testo[12]}` | cella del foglio |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `foglio` | `Cella[][]` | 6 × 3 | Celle del foglio |
| `contenuto` | `char[]` | 32 | Testo scritto nella cella |
| `somma`, `testi` | `double`, `int` | — | Risultato della somma di colonna |

| Funzione | Compito |
|----------|---------|
| `scrivi(&c, contenuto)` | NUMERO con sscanf("%lf %c") == 1, altrimenti TESTO troncato |
| `leggi_cella(&riga, &colonna)` | Cella come B3; 0 se fuori dal foglio |
| `stampa_foglio(foglio)` | Punto per le celle vuote, numeri a destra |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Somma di colonna

**a) Input** – `S B`

**b) Output** – "Somma colonna B: 1606.00 (celle di testo ignorate: 2)"

**c) Variabili di supporto** – `somma`, `testi`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni riga uno switch: NUMERO si somma, TESTO si conta, VUOTA si salta.

### Caso d'uso 2 – Scrittura

**a) Input** – `M B4 32.5`; `M C2 sconto 10%`

**b) Output** – "B4: numero"; "C2: testo"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – "32.5" è tutto un numero; "sconto 10%" no.

### Caso d'uso 3 – Svuotare e cella non valida

**a) Input** – `V A3`; `M D1 5`

**b) Output** – A3 vuota; "Cella non valida."

**c) Variabili di supporto** – —

**d) Vincoli** – colonne A-C, righe 1-6

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il resto della riga sbagliata si scarta con %*[^\n].
