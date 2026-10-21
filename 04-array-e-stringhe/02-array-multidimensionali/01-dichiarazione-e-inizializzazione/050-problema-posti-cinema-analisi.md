# Analisi – 050-problema-posti-cinema.c

## 1. Problema

Una sala con 6 file (A-F) da 10 posti registra lo stato di ogni posto
(libero o occupato). Il programma deve disegnare la mappa, contare i posti
liberi per fila e in totale, calcolare il riempimento, indicare la fila più
libera e cercare 4 posti liberi consecutivi nella stessa fila.

## 2. Analisi

### Input
Nessun input da tastiera: lo stato della sala è inizializzato nel codice.

| Variabile | Tipo      | Dimensione | Descrizione                         |
|-----------|-----------|------------|-------------------------------------|
| `sala`    | `int[][]` | 6 × 10     | 0 = libero, 1 = occupato            |

### Output
- La mappa della sala: per ogni fila (A–F) i posti con O (libero) o
  X (occupato) e il numero di posti liberi;
- i posti liberi totali su 60 e la percentuale di riempimento;
- la fila con più posti liberi;
- la posizione del primo gruppo di 4 posti liberi consecutivi nella stessa
  fila, oppure il messaggio che non ce ne sono.

### Vincoli
- La lettera della fila si ricava dall'indice di riga: `'A' + fila`
- I posti sono numerati da 1 per lo spettatore, mentre gli indici partono
  da 0: la conversione avviene solo nella stampa
- Riempimento = posti occupati / posti totali × 100
- A parità di posti liberi la fila più libera è la prima
- I posti consecutivi devono essere nella stessa fila: il conteggio riparte
  da zero a ogni fila e a ogni posto occupato
- La ricerca si ferma al primo gruppo trovato, partendo dalla fila A,
  tramite un flag nella condizione di entrambi i cicli (niente `break`)

### Assunzioni
- Le file sono quelle della sala reale: la fila A è la più vicina allo
  schermo

### Variabili di supporto

| Variabile        | Tipo        | Descrizione                                     |
|------------------|-------------|-------------------------------------------------|
| `liberi_fila`, `liberi_totali` | `int` | Contatori                             |
| `max_liberi`, `fila_max` | `int` | Fila con più posti liberi                     |
| `consecutivi`    | `int`       | Posti liberi di seguito nella fila corrente     |
| `trovato_gruppo` | `int` (0/1) | Ferma la ricerca                                |
| `fila_gruppo`, `posto_gruppo` | `int` | Fila e primo posto del gruppo trovato  |
| `FILE_SALA`, `POSTI`, `LIBERO`, `OCCUPATO`, `GRUPPO` | `#define` | 6, 10, 0, 1, 4 |

### Algoritmo in linguaggio naturale
1. Per ogni fila: stampare O o X per ogni posto contando i liberi, stampare
   il conteggio, sommarlo al totale e aggiornare la fila più libera.
2. Stampare posti liberi totali, riempimento e fila più libera.
3. Per ogni fila, finché non si è trovato un gruppo:
   a. azzerare `consecutivi`;
   b. per ogni posto: se è libero incrementare `consecutivi` e, se arriva a
      4, memorizzare fila e primo posto del gruppo (`posto − 3`);
      se è occupato azzerare `consecutivi`.
4. Stampare il gruppo trovato oppure il messaggio di assenza.

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il Test 3
richiede di modificare la sala e ricompilare.

### Test 1 – Mappa e conteggi
- **Output atteso:**
```
  A   X  X  X  O  O  X  X  X  X  O     3
  B   X  X  X  X  X  X  X  O  X  X     1
  C   O  X  X  O  O  O  O  X  X  O     6
  D   O  O  X  X  O  X  O  O  X  O     6
  E   O  O  O  X  X  O  O  O  O  O     8
  F   O  O  O  O  O  O  O  O  O  O    10

Posti liberi : 34 su 60
Riempimento  : 43.3%
Fila piu' libera: F (10 posti)
```

### Test 2 – Primo gruppo di 4 posti vicini
- **Cosa si verifica:** la ricerca si ferma alla fila C, anche se le file E
  e F hanno gruppi più lunghi
- **Output atteso:** `4 posti vicini disponibili: fila C, posti da 4 a 7`

### Test 3 – Nessun gruppo di 4 posti
- **Cosa si verifica:** il messaggio alternativo
- **Procedura:** occupare il posto 7 delle file C ed E e i posti 1, 4, 7, 10
  della fila F, in modo che nessuna fila abbia più di 3 posti liberi di
  seguito
- **Output atteso:** `Posti liberi : 28 su 60`, `Riempimento  : 53.3%`,
  `Fila piu' libera: E (7 posti)` e
  `Nessun gruppo di 4 posti vicini disponibile.`
