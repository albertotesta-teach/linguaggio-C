# Analisi – 040-problema-calcolatrice-frazioni.c

## 1. Problema

La calcolatrice legge espressioni con due frazioni e un operatore (+, -, *, :) e stampa il risultato con il segno al numeratore e ridotto ai minimi termini. Ogni operazione riceve due Frazione per valore e restituisce una Frazione nuova. Denominatori nulli e divisioni per zero sono segnalati; 0/0 termina.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Frazione` | `num, den` | frazione con segno |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `a`, `b` | `Frazione` | — | Operandi letti |
| `operatore` | `char` | — | +, -, * oppure : |
| `risultato` | `Frazione` | — | Valore restituito dall'operazione |

| Funzione | Compito |
|----------|---------|
| `somma, differenza, prodotto, quoziente` | Restituiscono la Frazione risultato |
| `normalizza(f)` | Segno al numeratore e minimi termini |
| `mcd(a, b)` | Algoritmo di Euclide |
| `stampa(f)` | Scrive a/b, o solo a se il denominatore è 1 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Operazioni

**a) Input** – `3/4 + 1/6`; `3/4 - 5/4`

**b) Output** – `11/12`; `-1/2`

**c) Variabili di supporto** – `risultato`

**d) Vincoli** – il risultato si normalizza

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – chiamare la funzione dell'operatore e stampare normalizza(risultato).

### Caso d'uso 2 – Divisione

**a) Input** – `3/4 : 0/5`

**b) Output** – "Divisione per zero."

**c) Variabili di supporto** – —

**d) Vincoli** – il divisore non può valere 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – quoziente moltiplica per il reciproco: si controlla prima il numeratore del divisore.

### Caso d'uso 3 – Errori di input

**a) Input** – `1/0 + 1/2`; `2/3 ^ 1/2`

**b) Output** – "Denominatore nullo."; "Operatore ^ non previsto."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – l'espressione si scarta e si legge la successiva.
