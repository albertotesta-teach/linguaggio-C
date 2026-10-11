# Analisi – 080-problema-scontrino-con-sconto.c

## 1. Problema

La cartoleria applica uno sconto del 10% sugli acquisti da almeno 50 euro e
assegna un punto fedeltà per ogni euro pagato. Una sola funzione calcola
totale, sconto e punti, ma la cassa li vuole tutti, il preventivo solo il
totale e la tessera solo i punti.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `prezzi`, `quantita` | `int[]` | 4 | Articoli dello scontrino, prezzi in centesimi |
| `totale`, `sconto`, `punti` | `int` | — | Risultati ricevuti dalla funzione |
| `articoli` | `int` | — | Numero di pezzi, restituito con `return` |

| Funzione | Compito |
|----------|---------|
| `calcola_scontrino(prezzi, quantita, n, &totale, &sconto, &punti)` | Calcola i tre valori, scrive solo nei puntatori non `NULL` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Cassa

**a) Input** – 4 articoli per 74.60 euro

**b) Output** – 10 articoli, sconto 7.46, da pagare 67.14 euro, 67 punti

**c) Variabili di supporto** – `lordo`, `riduzione`, `pezzi`

**d) Vincoli** – sconto solo da 50 euro in su

**e) Assunzioni** – sconto e punti arrotondati per difetto

**f) Algoritmo in linguaggio naturale**
1. Sommare prezzo × quantità e le quantità.
2. Calcolare lo sconto se il totale raggiunge la soglia.
3. Scrivere i tre risultati nei puntatori ricevuti.

### Caso d'uso 2 – Preventivo

**a) Input** – primi due articoli, `sconto` e `punti` = `NULL`

**b) Output** – 39.90 euro

**c) Variabili di supporto** – nessuna

**d) Vincoli** – la funzione non deve dereferenziare i puntatori `NULL`

**e) Assunzioni** – il valore di ritorno può essere ignorato

**f) Algoritmo in linguaggio naturale** – prima di ogni scrittura controllare
`if (puntatore != NULL)`.

### Caso d'uso 3 – Tessera

**a) Input** – tutti gli articoli, solo `&punti`

**b) Output** – 67 punti

**c) Variabili di supporto** – `riduzione`

**d) Vincoli** – i punti si calcolano sul prezzo scontato anche se lo sconto
non viene richiesto

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il calcolo è sempre completo;
cambia solo quali risultati vengono scritti.
