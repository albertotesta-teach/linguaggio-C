# Analisi – 060-problema-scontrino.c

## 1. Problema

La cassa di una cartoleria deve preparare lo scontrino come una serie di
righe di testo di 36 caratteri da inviare alla stampante. Per ogni articolo
la riga riporta descrizione (troncata se troppo lunga), quantità e importo;
seguono subtotale, eventuale sconto del 10% oltre 20 euro e totale.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `descrizioni` | `char[][]` | 6 × 30 | Nome degli articoli |
| `prezzi` | `int[]` | 6 | Prezzo unitario in centesimi (parallelo) |
| `quantita` | `int[]` | 6 | Pezzi acquistati (parallelo) |
| `righe` | `char[][]` | 14 × 64 | Righe dello scontrino già composte |
| `euro` | `char[]` | 16 | Importo trasformato in testo |
| `n_righe` | `int` | — | Righe composte finora |
| `totale`, `sconto`, `pezzi` | `int` | — | Importi in centesimi, pezzi totali |

| Funzione | Compito |
|----------|---------|
| `formatta_euro` | Da centesimi a testo "euro.centesimi", con il segno per gli sconti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Riga di un articolo

**a) Input** – "Calcolatrice scientifica", 1590 centesimi, 1 pezzo

**b) Output** – `Calcolatrice scien   1 x     15.90`

**c) Variabili di supporto** – `importo`, `euro`

**d) Vincoli** – `%-18.18s` tronca la descrizione a 18 caratteri; `snprintf`
con `sizeof(righe[n_righe])` non supera mai l'array

**e) Assunzioni** – prezzi in centesimi interi, per evitare errori di arrotondamento

**f) Algoritmo in linguaggio naturale**
1. Importo = prezzo × quantità; aggiornare totale e pezzi.
2. Trasformare l'importo in testo con `formatta_euro`.
3. Comporre la riga con `snprintf` e incrementare `n_righe`.

### Caso d'uso 2 – Sconto

**a) Input** – subtotale 3700 centesimi

**b) Output** – riga "Sconto 10%  -3.70" e "TOTALE EURO 33.30"

**c) Variabili di supporto** – `sconto`

**d) Vincoli** – lo sconto si applica solo oltre 2000 centesimi

**e) Assunzioni** – sconto arrotondato per difetto al centesimo

**f) Algoritmo in linguaggio naturale** – se il totale supera la soglia,
`sconto = totale / 10`; la riga mostra l'importo negativo.

### Caso d'uso 3 – Importi negativi

**a) Input** – `formatta_euro(euro, 16, -370)`

**b) Output** – `"-3.70"`

**c) Variabili di supporto** – nessuna

**d) Vincoli** – con `-370 / 100` e `-370 % 100` si otterrebbe "-3.-70": si
lavora sul valore positivo e si scrive il segno a parte

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se i centesimi sono negativi si
scrive `"-"` seguito da euro e centesimi del valore opposto.
