# Analisi – 060-problema-pagamenti-bar.c

## 1. Problema

Il bar della scuola accetta contanti, carta e buoni pasto; ogni metodo ha dati diversi (somma consegnata, ultime 4 cifre, codice del buono). Il programma controlla ogni pagamento con uno switch sul metodo, stampa la ricevuta e alla fine i totali per metodo con array indicizzati dall'enum.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Metodo` | `CONTANTI, CARTA, BUONO, NUM_METODI` | metodo di pagamento |
| `Pagamento` | `metodo, importo, union dati {consegnato, ultime_cifre, codice_buono}` | pagamento |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `p` | `Pagamento` | — | Pagamento letto |
| `totali`, `quanti` | `double[]`, `int[]` | NUM_METODI | Incassi e numero di pagamenti per metodo |
| `esito` | `int` | — | Risultato della lettura |

| Funzione | Compito |
|----------|---------|
| `leggi_pagamento(&p)` | 1 letto, 0 FINE, -1 metodo sconosciuto |
| `valido(&p)` | Consegnato sufficiente, 4 cifre, buono BU- fino a 5 euro |
| `ricevuta(&p)` | Resto, carta mascherata o codice del buono |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Contanti

**a) Input** – `C 3.20 5`

**b) Output** – "3.20 euro in contanti, resto 1.80"

**c) Variabili di supporto** – `p.dati.consegnato`

**d) Vincoli** – consegnato ≥ importo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – resto = consegnato - importo.

### Caso d'uso 2 – Carta e buono

**a) Input** – `K 4.50 1234`; `B 2.80 BU-17`

**b) Output** – "con carta **** 1234"; "con buono BU-17"

**c) Variabili di supporto** – —

**d) Vincoli** – 4 cifre; buono fino a 5 euro

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ogni metodo legge solo il suo campo della union.

### Caso d'uso 3 – Rifiuti

**a) Input** – `C 2.00 1.50`; `K 1.00 12345`; `B 6.00 BU-18`

**b) Output** – "Pagamento rifiutato."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – più di 4 cifre lasciano il campo vuoto, che il controllo rifiuta.

### Caso d'uso 4 – Totali

**a) Input** – `FINE`

**b) Output** – contanti pagamenti 2, 4.50 euro; carta 1; buono 1

**c) Variabili di supporto** – `totali`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – totali[p.metodo] += p.importo.
