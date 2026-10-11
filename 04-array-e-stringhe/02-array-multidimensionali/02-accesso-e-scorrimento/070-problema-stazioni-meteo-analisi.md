# Analisi – 070-problema-stazioni-meteo.c

## 1. Problema

Quattro stazioni meteo misurano la pioggia in sei intervalli di 4 ore. Il
programma deve stampare la tabella con il totale e l'intervallo più piovoso
di ogni stazione, trovare l'intervallo con la media più alta sulla rete e
permettere di consultare singole misure indicando stazione e intervallo.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `pioggia` | `double[][]` | 4 × 6 | Riga = stazione, colonna = intervallo |
| `stazioni` | `char[][]` | 4 × 16 | Nomi, paralleli alle righe |
| `totale`, `media` | `double` | — | Accumulatore e media |
| `in_max` | `int` | — | Intervallo più piovoso della riga corrente |
| `media_max`, `in_media_max` | `double`, `int` | — | Colonna con la media più alta |
| `scelta_stazione`, `scelta_intervallo` | `int` | — | Richieste dell'utente |

L'etichetta di un intervallo non è memorizzata: si calcola dall'indice
(`in * 4` e `(in + 1) * 4`).

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tabella, totali e picchi

**a) Input** – matrici `pioggia` e `stazioni`

**b) Output** – una riga per stazione con le sei misure, il totale e il picco
(es. Casale 6.2 mm, picco 08-12)

**c) Variabili di supporto** – `totale`, `in_max`

**d) Vincoli** – il picco si cerca per indice, partendo dalla colonna 0

**e) Assunzioni** – misure non negative

**f) Algoritmo in linguaggio naturale**
1. Stampare l'intestazione calcolando le etichette degli intervalli.
2. Per ogni stazione: sommare la riga e cercare l'indice del massimo.
3. Stampare totale ed etichetta del picco.

### Caso d'uso 2 – Intervallo più piovoso sulla rete

**a) Input** – matrice `pioggia`

**b) Output** – "Intervallo piu' piovoso sulla rete: 12-16 (media 7.57 mm)"

**c) Variabili di supporto** – `media`, `media_max`, `in_media_max`

**d) Vincoli** – scorrimento per colonne; il primo intervallo inizializza il massimo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni intervallo calcolare la media
della colonna e aggiornare il massimo.

### Caso d'uso 3 – Consultazione di una misura

**a) Input** – coppie stazione/intervallo numerate da 1, terminate da stazione 0

**b) Output** – "Ovada, 12-16: 12.6 mm" oppure "Stazione o intervallo inesistente."

**c) Variabili di supporto** – `st`, `in`

**d) Vincoli** – entrambi gli indici vengono controllati prima dell'accesso

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Leggere la stazione; finché non è 0: leggere l'intervallo.
2. Convertire in indici (meno 1) e verificarli.
3. Stampare la misura o l'errore; leggere la stazione successiva.
