# Analisi – 060-problema-scontrino.c

## 1. Problema

La cassa di una cartoleria deve preparare lo scontrino come una serie di
righe di testo di 36 caratteri da inviare alla stampante. Per ogni articolo
la riga riporta descrizione (troncata se troppo lunga), quantità e importo;
seguono subtotale, eventuale sconto del 10% oltre 20 euro e totale.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `descrizioni` | `char[6][30]` | Nome degli articoli |
| `prezzi` | `int[6]` | Prezzo unitario in centesimi (parallelo) |
| `quantita` | `int[6]` | Pezzi acquistati (parallelo) |

I dati sono inizializzati nel sorgente: il programma non legge nulla da tastiera.

### Output

- Il numero di righe composte e la larghezza.
- Le righe dello scontrino racchiuse tra `|`: intestazione, separatore, una
  riga per articolo (descrizione, quantità, importo), separatore,
  subtotale con il numero di pezzi, eventuale sconto, totale.

### Vincoli

- Gli importi si calcolano in centesimi (interi) e si trasformano in testo
  con `formatta_euro` (`euro.centesimi`, due cifre per i centesimi).
- Ogni riga si compone in memoria con `snprintf` prima di essere stampata.
- La descrizione si tronca a 18 caratteri con `%-18.18s`.
- Lo sconto del 10% (arrotondato per difetto al centesimo) si applica solo
  se il subtotale supera 2000 centesimi.
- Un importo negativo si formatta lavorando sul valore assoluto e
  aggiungendo il segno: con `-370 / 100` e `-370 % 100` si otterrebbe `-3.-70`.

### Assunzioni

- Gli importi stanno nelle 9 colonne riservate.
- Le righe sono al massimo `ARTICOLI + 8`.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `righe` | `char[14][64]` | Righe dello scontrino già composte |
| `euro` | `char[16]` | Importo trasformato in testo |
| `n_righe` | `int` | Righe composte finora |
| `importo` | `int` | Importo dell'articolo corrente in centesimi |
| `totale`, `sconto` | `int` | Subtotale/totale e sconto in centesimi |
| `pezzi` | `int` | Pezzi totali |

| Funzione | Compito |
|----------|---------|
| `formatta_euro` | Da centesimi a testo `euro.centesimi`, con il segno per gli sconti |

### Algoritmo in linguaggio naturale

1. Comporre intestazione e separatore.
2. Per ogni articolo: importo = prezzo × quantità; aggiornare totale e
   pezzi; comporre la riga con la descrizione troncata.
3. Comporre separatore e riga del subtotale.
4. Se il totale supera 2000 centesimi: sconto = totale / 10, comporre la
   riga dello sconto con l'importo negativo.
5. Totale = totale − sconto; comporre la riga del totale.
6. Stampare il numero di righe e ogni riga tra `|`, allargata a 36 caratteri.

## 3. Casi di test

### Test 1 – Scontrino completo con sconto

- **Cosa si verifica**: troncamento delle descrizioni, importi, subtotale,
  sconto e totale.
- **Input**: dati del sorgente.
- **Valori intermedi attesi**: subtotale 1000 + 540 + 240 + 1590 + 140 + 190 = 3700
  centesimi, `pezzi` = 13, `sconto` = 370, totale 3330.
- **Output atteso**:
  ```
  Righe da stampare: 12 (larghezza 36 caratteri)

  |      CARTOLERIA IL QUADERNO        |
  |------------------------------------|
  |Quaderno a quadret   4 x     10.00  |
  |Penna gel blu        3 x      5.40  |
  |Evidenziatore        2 x      2.40  |
  |Calcolatrice scien   1 x     15.90  |
  |Righello 30 cm       1 x      1.40  |
  |Colla stick          2 x      1.90  |
  |------------------------------------|
  |SUBTOTALE           13       37.00  |
  |Sconto 10%                   -3.70  |
  |TOTALE EURO                  33.30  |
  ```

### Test 2 – Sconto con arrotondamento

- **Cosa si verifica**: lo sconto è calcolato con la divisione intera.
- **Procedura**: nel sorgente portare a 0 la quantità della calcolatrice
  (`{4, 3, 2, 0, 1, 2}`), ricompilare ed eseguire.
- **Valori intermedi attesi**: subtotale 2110, `sconto` = 211.
- **Output atteso** (righe finali):
  ```
  |Calcolatrice scien   0 x      0.00  |
  ...
  |SUBTOTALE           12       21.10  |
  |Sconto 10%                   -2.11  |
  |TOTALE EURO                  18.99  |
  ```

### Test 3 – Subtotale esattamente uguale alla soglia

- **Cosa si verifica**: con 20.00 euro esatti lo sconto **non** si applica
  (la condizione è "oltre 20 euro") e lo scontrino ha una riga in meno.
- **Procedura**: nel sorgente impostare le quantità a `{0, 3, 2, 1, 1, 2}` e
  il prezzo della calcolatrice a `890`, ricompilare ed eseguire.
- **Valori intermedi attesi**: subtotale 2000, `sconto` = 0, `n_righe` = 11.
- **Output atteso** (righe finali):
  ```
  |SUBTOTALE            9       20.00  |
  |TOTALE EURO                  20.00  |
  ```

### Test 4 – Formattazione di un importo negativo

- **Cosa si verifica**: `formatta_euro` con un valore negativo.
- **Input**: `formatta_euro(euro, 16, -370)` (chiamata eseguita dal programma per lo sconto del Test 1).
- **Output atteso**: la stringa `-3.70` (e non `-3.-70`).
