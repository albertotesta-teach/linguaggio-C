# Analisi – 080-problema-vendite-trimestrali.c

## 1. Problema

Un negozio di elettronica ha i pezzi venduti di 5 prodotti in ciascuno dei
tre mesi del trimestre e il prezzo di ogni prodotto. Il programma deve
calcolare i totali per prodotto e per mese, il fatturato di ogni prodotto e
complessivo, il prodotto con il fatturato più alto e i prodotti con vendite
in crescita ogni mese.

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile | Tipo       | Dimensione | Descrizione                                |
|-----------|------------|------------|--------------------------------------------|
| `vendite` | `int[][]`  | 5 × 3      | Riga = prodotto, colonna = mese            |
| `codici`  | `int[]`    | 5          | Codice del prodotto, parallelo alle righe  |
| `prezzi`  | `double[]` | 5          | Prezzo unitario, parallelo alle righe      |

### Output
- La tabella: per ogni prodotto codice, pezzi dei tre mesi, pezzi totali,
  prezzo e fatturato;
- i pezzi totali di ogni mese;
- il fatturato del trimestre e il prodotto con il fatturato più alto;
- l'elenco dei prodotti con vendite in crescita ogni mese.

### Vincoli
- Fatturato di un prodotto = pezzi totali × prezzo
- Totale di prodotto = somma di una **riga**; totale di mese = somma di una
  **colonna**
- Un prodotto è in crescita se ogni mese vende **strettamente** più del
  mese precedente: vendite uguali in due mesi non sono una crescita
- La verifica della crescita parte dall'ipotesi vera e si ferma al primo
  mese che la smentisce, tramite il flag nella condizione (niente `break`)
- Il massimo del fatturato è inizializzato con il primo prodotto
  (`p == 0`); a parità resta il primo
- Se nessun prodotto è in crescita, l'elenco resta vuoto senza messaggi

### Assunzioni
- Pezzi e prezzi sono non negativi

### Variabili di supporto

| Variabile                     | Tipo     | Descrizione                         |
|-------------------------------|----------|-------------------------------------|
| `pezzi_prodotto`, `pezzi_mese`| `int`    | Totali di riga e di colonna         |
| `fatturato`, `fatturato_totale` | `double` | Fatturato del prodotto e complessivo |
| `fatturato_max`, `p_max`      | `double`, `int` | Prodotto migliore            |
| `in_crescita`                 | `int` (0/1) | Esito della verifica di crescita |
| `PRODOTTI`, `MESI`            | `#define` | 5, 3                               |

### Algoritmo in linguaggio naturale
1. Per ogni prodotto: stampare codice e pezzi dei tre mesi sommandoli;
   calcolare il fatturato, sommarlo al totale e aggiornare il massimo;
   stampare pezzi, prezzo e fatturato.
2. Per ogni mese sommare la colonna e stampare il totale.
3. Stampare il fatturato del trimestre e il prodotto migliore.
4. Per ogni prodotto porre `in_crescita = 1` e, dal secondo mese, finché
   resta vero, azzerarlo se le vendite non superano il mese precedente;
   se alla fine vale 1 stampare il prodotto con le tre vendite.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Tabella e totali
- **Output atteso:**
```
    1101 |   42 |   38 |   51 |   131 |    19.90 |   2606.90
    1102 |   15 |   18 |   22 |    55 |   149.00 |   8195.00
    2201 |   60 |   55 |   48 |   163 |     9.50 |   1548.50
    3301 |    8 |   12 |   15 |    35 |   599.00 |  20965.00
    3302 |   25 |   25 |   30 |    80 |    79.90 |   6392.00
  -------|------|------|------|
  Totale |  150 |  148 |  166 |

Fatturato del trimestre: 39707.40 euro
Prodotto con il fatturato piu' alto: 3301 (20965.00 euro)
```
- **Osservazione:** il prodotto più venduto per pezzi (2201) è quello con
  il fatturato più basso

### Test 2 – Prodotti in crescita
- **Cosa si verifica:** 3302 (25 → 25 → 30) non è in crescita perché i
  primi due mesi sono uguali; 1101 cala a febbraio
- **Output atteso:**
```
--- Prodotti con vendite in crescita ogni mese ---
  1102: 15 -> 18 -> 22
  3301: 8 -> 12 -> 15
```
