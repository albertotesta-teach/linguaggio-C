# Analisi – 080-problema-risultati-misure.c

## 1. Problema

Il voltmetro del laboratorio restituisce un valore grezzo; misura lo trasforma in un Risultato con tre esiti, ognuno con i suoi dati: valore e incertezza, fondo scala superato, codice di guasto. Il programma legge il fondo scala e le letture e alla fine stampa la media delle sole misure riuscite.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Risultato` | `esito, union dati {ok {valore, incertezza}, fondo_scala, codice}` | risultato di una misura |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `r` | `Risultato` | — | Esito di una lettura |
| `conteggi` | `int[]` | NUM_ESITI | Letture per esito |
| `somma` | `double` | — | Somma dei valori riusciti |
| `fondo_scala`, `letto` | `double` | — | Dati letti |

| Funzione | Compito |
|----------|---------|
| `misura(letto, fondo_scala)` | Costruisce il Risultato con l'etichetta giusta |
| `stampa(&r)` | Switch sull'esito |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Misure riuscite

**a) Input** – fondo scala `20`, letture `3.27`, `12.5`, `0.85`

**b) Output** – "(3.270 +/- 0.043) V", ...; media 5.540 V

**c) Variabili di supporto** – `somma`

**d) Vincoli** – incertezza 1% + 0.01 V

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – solo le misure MISURA_OK entrano nella media.

### Caso d'uso 2 – Fuori scala

**a) Input** – `21.4`

**b) Output** – "Fuori scala: oltre 20.0 V..."

**c) Variabili di supporto** – —

**d) Vincoli** – lettura ≤ fondo scala

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il risultato conserva il fondo scala superato.

### Caso d'uso 3 – Guasti

**a) Input** – `-1`; `-2`

**b) Output** – "cavo staccato"; "batteria scarica"

**c) Variabili di supporto** – —

**d) Vincoli** – letture negative = codici

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il codice è la parte intera della lettura.

### Caso d'uso 4 – Testo

**a) Input** – `abc`

**b) Output** – "Non e' un numero."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la lettura si scarta.
