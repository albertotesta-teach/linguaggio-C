# Analisi – 080-problema-scontrino-con-sconto.c

## 1. Problema

La cartoleria applica uno sconto del 10% sugli acquisti da almeno 50 euro e
assegna un punto fedeltà per ogni euro pagato. Una sola funzione calcola
totale, sconto e punti, ma la cassa li vuole tutti, il preventivo solo il
totale e la tessera solo i punti.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `prezzi` | `int[4]` | 1890, 350, 1240, 990 centesimi |
| `quantita` | `int[4]` | 1, 6, 2, 1 |

### Output

- Cassa: numero di articoli, totale, sconto, importo da pagare e punti.
- Preventivo: il totale dei primi due articoli.
- Tessera: i punti caricati.

### Vincoli

- `calcola_scontrino` restituisce il numero di pezzi con `return` e totale,
  sconto e punti tramite tre puntatori; scrive solo nei puntatori diversi
  da `NULL`, così chi non vuole un risultato passa `NULL`.
- Sconto del 10% solo se il totale è almeno 5000 centesimi (50 euro).
- Punti = euro pagati dopo lo sconto, arrotondati per difetto; anche lo
  sconto è arrotondato per difetto (divisione intera).
- I punti si calcolano sul prezzo scontato anche se lo sconto non è
  richiesto dal chiamante.
- Il valore restituito può essere ignorato (preventivo e tessera).

### Assunzioni

- Gli importi sono in centesimi interi.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `totale`, `sconto`, `punti` | `int` | Risultati ricevuti dalla funzione |
| `articoli` | `int` | Numero di pezzi, restituito con `return` |
| `lordo`, `pezzi`, `riduzione` | `int` | Nella funzione: calcoli locali |
| `SOGLIA_SCONTO`, `PERCENTUALE` | `#define` | 5000, 10 |

| Funzione | Compito |
|----------|---------|
| `calcola_scontrino(prezzi, quantita, n, &totale, &sconto, &punti)` | Calcola i tre valori, scrive solo nei puntatori non `NULL`; restituisce i pezzi |

### Algoritmo in linguaggio naturale

1. In `calcola_scontrino`: sommare prezzo × quantità e le quantità; se il
   lordo è almeno 5000 calcolare lo sconto del 10%; scrivere totale,
   sconto e punti (`(lordo − sconto) / 100`) solo nei puntatori non `NULL`;
   restituire i pezzi.
2. Nel `main` chiamare la funzione tre volte: con tutti i puntatori (cassa),
   con i primi due articoli e solo `&totale` (preventivo), con tutti gli
   articoli e solo `&punti` (tessera).

## 3. Casi di test

### Test 1 – Chiamate del sorgente

- **Input:** nessuno.
- **Valori intermedi attesi:** lordo = 1890 + 2100 + 2480 + 990 = 7460;
  sconto = 746; punti = 6714 / 100 = 67; preventivo 1890 + 2100 = 3990.
- **Output atteso:**
  ```
  === CASSA ===
    10 articoli, totale 74.60, sconto 7.46, da pagare 67.14 euro, 67 punti

  === PREVENTIVO (solo il totale) ===
    primi due articoli: 39.90 euro

  === TESSERA (solo i punti) ===
    punti caricati: 67
  ```

### Test 2 – Sotto la soglia di sconto

- **Procedura:** nel sorgente impostare tutte le quantità a 1, ricompilare
  ed eseguire.
- **Output atteso** (cassa):
  `  4 articoli, totale 44.70, sconto 0.00, da pagare 44.70 euro, 44 punti`
