# Analisi – 050-problema-statistiche-griglia.c

## 1. Problema

La serra dell'istituto agrario è divisa in 4 × 5 settori con un sensore di
temperatura ciascuno. Il responsabile vuole la media della serra, il
settore più caldo, il numero di settori oltre 28 gradi e le stesse
informazioni per ogni fila.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `serra` | `double[4][5]` | Temperature dei settori, una riga per fila |

### Output

- Media della serra, settore più caldo (fila e settore) e numero di settori
  oltre 28 gradi su 20.
- Per ogni fila: media, massima e settori oltre soglia.

### Vincoli

- Le righe di una matrice sono consecutive in memoria: `&serra[0][0]` è
  l'inizio di un blocco di 20 `double` che le funzioni scorrono come un
  unico array.
- Le stesse funzioni ricevono anche una sola riga (`serra[f]`, 5 elementi).
- `massimo` restituisce un puntatore all'elemento più alto (il primo a
  parità); la posizione nel blocco è `k = caldo − tutto`, da cui fila
  `k / 5 + 1` e settore `k % 5 + 1`.
- La soglia è esclusa: 28.0 non è "oltre".

### Assunzioni

- Le temperature sono in gradi Celsius.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `tutto` | `const double *` | `&serra[0][0]`, la matrice come blocco unico |
| `n` | `int` | 20 settori |
| `caldo` | `const double *` | Settore più caldo |
| `k`, `f` | `int` | Posizione nel blocco, indice della fila |
| `SOGLIA` | `#define` | 28.0 |

| Funzione | Compito |
|----------|---------|
| `media(v, n)` | Media di n valori consecutivi |
| `massimo(v, n)` | Puntatore al valore più alto |
| `conta_oltre(v, n, soglia)` | Valori oltre la soglia |

### Algoritmo in linguaggio naturale

1. Calcolare media, massimo e conteggio sull'intero blocco di 20 valori;
   ricavare fila e settore del massimo dalla sua posizione; stamparli.
2. Per ogni fila calcolare media, massima e conteggio sulla riga e
   stamparli.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Input:** nessuno.
- **Valori intermedi attesi:** il massimo 29.4 è in posizione `k` = 9:
  fila 9 / 5 + 1 = 2, settore 9 % 5 + 1 = 5.
- **Output atteso:**
  ```
  Temperatura media della serra: 26.32 gradi
  Settore piu' caldo: fila 2, settore 5 (29.4 gradi)
  Settori oltre 28.0 gradi: 4 su 20

  Fila 1: media 25.92, massima 27.2, oltre soglia 0
  Fila 2: media 27.44, massima 29.4, oltre soglia 2
  Fila 3: media 26.96, massima 28.9, oltre soglia 2
  Fila 4: media 24.96, massima 26.1, oltre soglia 0
  ```
