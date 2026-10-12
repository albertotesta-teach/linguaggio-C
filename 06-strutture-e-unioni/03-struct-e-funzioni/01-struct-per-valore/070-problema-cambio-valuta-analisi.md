# Analisi – 070-problema-cambio-valuta.c

## 1. Problema

Durante lo scambio culturale gli studenti annotano le spese in valuta locale. Il programma converte ogni spesa in euro con una tabella di cambi e stampa il totale del viaggio. Un importo è una struct con valore e valuta; converti la riceve per valore e restituisce un Importo nuovo.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Importo` | `valore, valuta` | somma di denaro con la sua valuta |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `spesa`, `in_euro` | `Importo` | — | Spesa letta e convertita |
| `totale` | `Importo` | — | Somma in euro |
| `ok` | `int` | — | Esito della conversione |

| Funzione | Compito |
|----------|---------|
| `crea_importo(valore, valuta)` | Costruisce un Importo |
| `converti(i, verso, &ok)` | Restituisce l'importo nella valuta richiesta passando per l'euro |
| `cambio(valuta, &ok)` | Unità per 1 euro dalla tabella |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Conversione

**a) Input** – `12.50 GBP`

**b) Output** – "12.50 GBP = 14.53 EUR"

**c) Variabili di supporto** – `in_euro`

**d) Vincoli** – cambi indicativi della tabella

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – valore / cambio di partenza × cambio di arrivo.

### Caso d'uso 2 – Valuta sconosciuta

**a) Input** – `15 JPY`

**b) Output** – "Valuta JPY non in tabella."

**c) Variabili di supporto** – `ok`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cambio scrive 0 in *ok e la spesa non entra nel totale.

### Caso d'uso 3 – Totale

**a) Input** – `0`

**b) Output** – "Totale del viaggio: 42.96 EUR"

**c) Variabili di supporto** – `totale`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sommare i valori convertiti.
