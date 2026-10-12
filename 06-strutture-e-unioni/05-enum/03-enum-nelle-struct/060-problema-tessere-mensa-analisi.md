# Analisi – 060-problema-tessere-mensa.c

## 1. Problema

Il prezzo del pasto in mensa dipende dalla fascia ISEE della famiglia. Ogni fascia ha nome, tetto ISEE e prezzo in una tabella indicizzata dall'enum; all'avvio la fascia di ogni tessera si calcola dall'ISEE. I comandi registrano pasti, mostrano una tessera o riepilogano l'incasso per fascia.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Fascia` | `FASCIA_A ... FASCIA_D, NUM_FASCE` | fascia ISEE |
| `Tariffa` | `nome, isee_massimo, prezzo_pasto` | dati di una fascia |
| `Tessera` | `numero, nome, isee, fascia, pasti` | tessera mensa |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `tariffe` | `Tariffa[]` | NUM_FASCE | Tetto e prezzo per fascia |
| `tessere` | `Tessera[]` | 5 | Tessere |
| `t` | `Tessera *` | — | Tessera trovata |
| `quante`, `pasti`, `incasso` | `int`, `double` | — | Riepilogo di una fascia |

| Funzione | Compito |
|----------|---------|
| `da_isee(isee, tariffe)` | Prima fascia con il tetto non superato |
| `cerca(t, n, numero)` | Puntatore alla tessera o NULL |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Fasce

**a) Input** – avvio

**b) Output** – Corti Ugo (18200) fascia C; Elia Gino (15000) fascia B

**c) Variabili di supporto** – `tessere[i].fascia`

**d) Vincoli** – tetto compreso nella fascia

**e) Assunzioni** – l'ultima fascia non ha tetto

**f) Algoritmo in linguaggio naturale** – scorrere le fasce finché l'ISEE supera il tetto.

### Caso d'uso 2 – Pasti

**a) Input** – `P 102`

**b) Output** – "fascia C, 4.80 euro a pasto, pasti 1: 4.80 euro"

**c) Variabili di supporto** – `t->pasti`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – prezzo = tariffe[t->fascia].prezzo_pasto.

### Caso d'uso 3 – Riepilogo

**a) Input** – `R`

**b) Output** – una riga per fascia e "totale 34.40 euro"

**c) Variabili di supporto** – `incasso`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni fascia sommare i pasti delle sue tessere.

### Caso d'uso 4 – Tessera inesistente

**a) Input** – `S 999`

**b) Output** – "Tessera 999 inesistente."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca restituisce NULL.
