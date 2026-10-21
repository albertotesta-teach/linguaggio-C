# Analisi – 070-problema-stazioni-meteo.c

## 1. Problema

Quattro stazioni meteo misurano la pioggia in sei intervalli di 4 ore. Il
programma deve stampare la tabella con il totale e l'intervallo più piovoso
di ogni stazione, trovare l'intervallo con la media più alta sulla rete e
permettere di consultare singole misure indicando stazione e intervallo.

## 2. Analisi

### Input

| Variabile           | Tipo  | Descrizione                                       |
|---------------------|-------|---------------------------------------------------|
| `scelta_stazione`   | `int` | Stazione da consultare (1–4); 0 termina           |
| `scelta_intervallo` | `int` | Intervallo da consultare (1–6)                    |

Le misure e i nomi delle stazioni sono inizializzati nel codice.

### Output
- La tabella: per ogni stazione la pioggia dei sei intervalli, il totale e
  l'intervallo di picco (nel formato `hh-hh`);
- l'intervallo con la pioggia media più alta sull'intera rete, con la media;
- per ogni consultazione la misura richiesta, oppure
  "Stazione o intervallo inesistente.".

### Vincoli
- Totale e picco di una stazione si calcolano su una **riga**; la media di
  un intervallo su una **colonna**
- L'etichetta dell'intervallo non è memorizzata: si calcola dall'indice
  (`in × 4` e `(in + 1) × 4`)
- A parità resta il primo intervallo trovato, sia per il picco sia per la
  media massima
- Nella consultazione stazione e intervallo si inseriscono da 1; gli indici
  ricavati si controllano **prima** di accedere alla matrice
- La consultazione termina con la stazione 0, letta in anticipo (lettura
  anticipata), quindi l'intervallo non viene chiesto
- Una stazione o un intervallo non numerici si scartano e risultano
  inesistenti; a fine input (EOF) il programma si comporta come la
  stazione 0

### Assunzioni
- Le misure sono in mm e non negative

### Variabili di supporto

| Variabile   | Tipo         | Dimensione | Descrizione                           |
|-------------|--------------|------------|---------------------------------------|
| `pioggia`   | `double[][]` | 4 × 6      | Riga = stazione, colonna = intervallo |
| `stazioni`  | `char[][]`   | 4 × 16     | Nomi, paralleli alle righe            |
| `totale`, `media` | `double` | —        | Accumulatore e media                  |
| `in_max`    | `int`        | —          | Intervallo di picco della riga        |
| `media_max`, `in_media_max` | `double`, `int` | — | Colonna con la media più alta |
| `STAZIONI`, `INTERVALLI`, `ORE_INTERVALLO` | `#define` | — | 4, 6, 4      |

### Algoritmo in linguaggio naturale
1. Stampare l'intestazione con le etichette degli intervalli.
2. Per ogni stazione sommare la riga, cercare l'intervallo di picco e
   stampare la riga con totale e picco.
3. Per ogni intervallo calcolare la media della colonna e aggiornare il
   massimo; stampare l'intervallo più piovoso.
4. Leggere la stazione; finché è diversa da 0: leggere l'intervallo,
   ricavare gli indici, stampare la misura se sono validi oppure il
   messaggio di errore, e leggere la stazione successiva.

## 3. Casi di test

Le misure sono fisse nel codice; i dati letti sono le consultazioni.

### Test 1 – Tabella e intervallo più piovoso
- **Input:** `0` (nessuna consultazione)
- **Output atteso:**
```
  Alessandria      0.0    1.2    4.8    6.5    2.0    0.4    14.9  12-16
  Acqui Terme      0.2    0.8    3.5    9.1    3.3    1.0    17.9  12-16
  Casale           0.0    0.3    2.9    2.1    0.9    0.0     6.2  08-12
  Ovada            1.1    2.4    7.2   12.6    5.8    2.2    31.3  12-16

Intervallo piu' piovoso sulla rete: 12-16 (media 7.57 mm)
```
- **Osservazione:** Casale ha il picco in un intervallo diverso dalle altre
  stazioni

### Test 2 – Consultazioni valide e non valide
- **Input:** `4 4`, `3 6`, `5 1`, `2 0`, `0`
- **Output atteso:** `Ovada, 12-16: 12.6 mm`, `Casale, 20-24: 0.0 mm`, poi
  due volte `Stazione o intervallo inesistente.` (stazione 5, intervallo 0)

### Test 3 – Dati non numerici e fine dell'input
- **Cosa si verifica:** testo al posto dei numeri non blocca la consultazione
- **Input:** `abc`, `2`, `x`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Stazione (1-4): Intervallo (1-6):   Stazione o intervallo inesistente.
Stazione (1-4): Intervallo (1-6):   Stazione o intervallo inesistente.
Stazione (1-4): 
```
- **Nota:** dopo una stazione non valida il programma chiede comunque
  l'intervallo (come per un numero di stazione fuori intervallo), quindi
  `2` viene letto come intervallo.
