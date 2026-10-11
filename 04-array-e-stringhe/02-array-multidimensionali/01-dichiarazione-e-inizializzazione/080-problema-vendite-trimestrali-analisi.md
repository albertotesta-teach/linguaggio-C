# Analisi – 080-problema-vendite-trimestrali.c

## 1. Problema

Un negozio di elettronica ha i pezzi venduti di 5 prodotti in ciascuno dei
tre mesi del trimestre e il prezzo di ogni prodotto. Il programma deve
calcolare i totali per prodotto e per mese, il fatturato di ogni prodotto e
complessivo, il prodotto con il fatturato più alto e i prodotti con vendite
in crescita ogni mese.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `vendite` | `int[][]` | 5 × 3 | Riga = prodotto, colonna = mese |
| `codici` | `int[]` | 5 | Codice prodotto, parallelo alle righe |
| `prezzi` | `double[]` | 5 | Prezzo unitario, parallelo alle righe |
| `pezzi_prodotto`, `pezzi_mese` | `int` | — | Totali di riga e di colonna |
| `fatturato`, `fatturato_totale` | `double` | — | Fatturato del prodotto e complessivo |
| `fatturato_max`, `p_max` | `double`, `int` | — | Prodotto migliore |
| `in_crescita` | `int` (0/1) | — | Flag di verifica della crescita |

Gli array paralleli possono essere anche numerici: `codici` e `prezzi`
completano le informazioni di ogni riga della matrice.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Totali per prodotto e fatturato

**a) Input** – `vendite`, `codici`, `prezzi`

**b) Output** – tabella con pezzi per mese, pezzi totali, prezzo e fatturato;
fatturato del trimestre 39707.40 euro; migliore il prodotto 3301

**c) Variabili di supporto** – `pezzi_prodotto`, `fatturato`, `fatturato_max`, `p_max`

**d) Vincoli** – il fatturato è `pezzi_prodotto × prezzi[p]`; il massimo è
inizializzato dal primo prodotto

**e) Assunzioni** – prezzi costanti nel trimestre

**f) Algoritmo in linguaggio naturale**
1. Per ogni prodotto: sommare le vendite della riga stampandole.
2. Calcolare il fatturato, sommarlo al totale, stampare la riga.
3. Se è il primo prodotto o il fatturato supera il massimo, aggiornarlo.

### Caso d'uso 2 – Totali per mese

**a) Input** – `vendite`

**b) Output** – riga "Totale" con 150, 148, 166

**c) Variabili di supporto** – `pezzi_mese`

**d) Vincoli** – somma per colonne

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni mese sommare la colonna su
tutti i prodotti e stampare il risultato.

### Caso d'uso 3 – Prodotti in crescita

**a) Input** – `vendite`, `codici`

**b) Output** – 1102 (15 → 18 → 22) e 3301 (8 → 12 → 15)

**c) Variabili di supporto** – `in_crescita`

**d) Vincoli** – il confronto `<=` esclude i mesi uguali: 3302 (25, 25, 30)
non è in crescita; il ciclo interno si ferma al primo mese che smentisce
l'ipotesi grazie al flag nella condizione

**e) Assunzioni** – crescita stretta, mese per mese

**f) Algoritmo in linguaggio naturale**
1. Per ogni prodotto: ipotizzare `in_crescita = 1`.
2. Dal secondo mese, finché l'ipotesi regge: se le vendite non superano quelle
   del mese precedente, porre `in_crescita = 0`.
3. Se l'ipotesi è rimasta vera, stampare codice e vendite.
