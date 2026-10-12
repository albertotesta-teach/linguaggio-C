# Analisi – 050-problema-giorni-di-lezione.c

## 1. Problema

Il coordinatore inserisce le ore di lezione di una classe dal lunedì al sabato. Il programma richiede i valori non validi, poi stampa il totale (il biennio prevede 32 ore), il giorno con più ore e i giorni liberi. I giorni sono un enum usato come indice dell'array delle ore.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Giorno` | `LUNEDI ... SABATO, NUM_GIORNI` | giorno della settimana |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `ore` | `int[]` | NUM_GIORNI | Ore di ogni giorno |
| `nomi` | `const char *[]` | NUM_GIORNI | Nomi dei giorni |
| `massimo` | `Giorno` | — | Giorno con più ore |
| `totale`, `liberi` | `int` | — | Somma e giorni senza lezione |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Inserimento

**a) Input** – `6 6 x 9 6 6 8 0`

**b) Output** – "Scrivi un numero.", "Da 0 a 8 ore.", poi "Totale: 32 ore (corretto)"

**c) Variabili di supporto** – `ore`

**d) Vincoli** – da 0 a 8 ore

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni giorno ripetere la lettura finché il valore è valido; scanf("%*s") scarta il testo.

### Caso d'uso 2 – Giorno più lungo

**a) Input** – stesso input

**b) Output** – "Giorno piu' lungo: venerdi con 8 ore"

**c) Variabili di supporto** – `massimo`

**d) Vincoli** – a parità vince il primo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confronto con > durante la lettura.

### Caso d'uso 3 – Giorni liberi

**a) Input** – stesso input

**b) Output** – "Giorni liberi: sabato"

**c) Variabili di supporto** – `liberi`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stampare i giorni con 0 ore, oppure "nessuno".
