# Analisi – 070-problema-analisi-partita.c

## 1. Problema

Una squadra di calcio ha 8 giocatori. Il programma deve calcolare totale gol,
media, identificare il capocannoniere, contare i giocatori oltre una soglia e
stampare la classifica marcatori (top-5) in ordine decrescente.

---

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile | Tipo       | Dimensione | Descrizione                              |
|-----------|------------|------------|------------------------------------------|
| `nomi`    | `char[][]` | 8 × 20     | Cognome e nome del giocatore             |
| `gol`     | `int[]`    | 8          | Gol segnati, parallelo a `nomi`          |

### Output
- Il capocannoniere con i suoi gol;
- il totale dei gol della squadra e la media per giocatore (un decimale);
- il numero di giocatori con più di 8 gol;
- la classifica dei 5 migliori marcatori in ordine decrescente.

### Vincoli
- Un giocatore supera la soglia se ha **strettamente** più gol: con 8 gol
  non è contato
- A parità di gol vince il giocatore che compare prima nell'array, sia per
  il capocannoniere sia in classifica
- La classifica non ordina l'array: cerca il massimo `k` volte, escludendo
  a ogni passo i giocatori già selezionati
- La media riusa `totale_gol` invece di ripetere la somma
- Gli array sono passati come `const`: nessuna funzione li modifica

### Assunzioni
- `k` non supera il numero di giocatori

### Variabili di supporto

| Variabile     | Tipo      | Dimensione | Descrizione                                     |
|---------------|-----------|------------|-------------------------------------------------|
| `selezionato` | `int[]`   | 8          | Locale a `stampa_classifica`: 1 se già in classifica |
| `idx`         | `int`     | —          | Indice del giocatore trovato                    |
| `GIOCATORI`   | `#define` | 8          | Numero di giocatori                             |

| Funzione | Descrizione |
|---|---|
| `int totale_gol(const int gol[], int n)` | Somma dei gol |
| `double media_gol(const int gol[], int n)` | `totale_gol / n` |
| `int capocannoniere(const int gol[], int n)` | Indice del massimo |
| `int conta_sopra_soglia(const int gol[], int n, int soglia)` | Giocatori con gol > soglia |
| `void stampa_classifica(const char nomi[][20], const int gol[], int n, int k)` | Primi k marcatori |

### Algoritmo in linguaggio naturale
1. Cercare l'indice del capocannoniere e stamparlo.
2. Stampare totale, media e numero di giocatori sopra la soglia di 8 gol.
3. Classifica: azzerare i flag; per j da 1 a k cercare il giocatore con più
   gol tra quelli non selezionati, segnarlo e stamparlo in posizione j.

---

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il Test 2
richiede di modificare i gol e ricompilare.

### Test 1 – Statistiche e classifica
- **Input:** gol 12, 7, 15, 3, 9, 11, 4, 8
- **Output atteso:**
```
Capocannoniere      : Verdi Paolo (15 gol)
Totale gol squadra  : 69
Media per giocatore : 8.6
Giocatori > 8 gol   : 4 su 8

--- Classifica marcatori (top 5) ---
  Pos. | Giocatore          | Gol
  -----|--------------------|---------
    1  | Verdi Paolo        |  15
    2  | Rossi Marco        |  12
    3  | Conti Matteo       |  11
    4  | Russo Andrea       |   9
    5  | Greco Simone       |   8
```
- **Osservazione:** Greco Simone, con 8 gol, è in classifica ma non è
  contato tra i giocatori sopra la soglia

### Test 2 – Due giocatori a pari gol
- **Cosa si verifica:** a parità precede chi compare prima nell'array
- **Procedura:** dare 15 gol anche a Rossi Marco (primo dell'array)
- **Output atteso:** `Capocannoniere      : Rossi Marco (15 gol)`, totale 72,
  media 9.0; in classifica Rossi Marco 1° e Verdi Paolo 2°, entrambi con 15
