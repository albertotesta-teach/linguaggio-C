# Analisi – 070-problema-gioco-tris.c

## 1. Problema

Per la giornata delle STEM si gioca a tris. Ogni casella è un `enum`
(vuota, croce, cerchio), anche il turno è una `Casella`, e il risultato
della partita è un altro `enum`. `gioca` mette il segno e passa il turno;
`controlla` cerca tre segni uguali o la griglia piena.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga`, `colonna` | `int` | Casella da 1 a 3, sulla stessa riga |

### Output

- Dopo ogni mossa valida la griglia (`.` vuota, `X`, `O`).
- `Casella non valida o gia' occupata.`, `Mossa non valida.`
- `Vince X in N mosse!`, `Vince O in N mosse!`, `Pareggio.`, oppure
  `Partita interrotta.` a fine input.

### Vincoli

- Inizia la croce; il turno passa solo con una mossa valida.
- `controlla` verifica righe, colonne e diagonali, poi il pareggio a 9
  mosse; il risultato si stampa con uno `switch` su `Risultato`.
- Il tris su una diagonale passa sempre per il centro: il vincitore è
  `griglia[1][1]`.
- Una mossa non numerica viene scartata con il resto della riga.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Casella` | `typedef enum { VUOTA, CROCE, CERCHIO } Casella;` | Contenuto di una casella e turno |
| `Risultato` | `typedef enum { IN_CORSO, VINCE_CROCE, VINCE_CERCHIO, PAREGGIO } Risultato;` | Stato della partita |
| `Partita` | `typedef struct { Casella griglia[3][3]; Casella turno; int mosse; } Partita;` | La partita |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `partita` | `Partita` | Griglia vuota, turno della croce |
| `risultato` | `Risultato` | Controllo del ciclo |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `gioca(p, riga, colonna)` | Mette il segno se la casella è libera; 1 se valida |
| `controlla(p)` | Risultato della partita |
| `tris(a, b, c)` | 1 se tre caselle hanno lo stesso segno non vuoto |
| `stampa(p)` | Disegna la griglia |
| `simbolo(c)` | Carattere della casella |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché la partita è in corso:
   1. leggere la mossa (fine input → partita interrotta; testo → non
      valida);
   2. se `gioca` la rifiuta segnalarlo;
   3. altrimenti stampare la griglia, calcolare il risultato e, se la
      partita è finita, stamparlo.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Vittoria in diagonale

- **Input:** `2 2`, `2 2`, `1 4`, `ab`, `1 1`, `1 3`, `3 3`, `3 1`
- **Output atteso:** dopo la prima griglia
  ```
    Casella non valida o gia' occupata.
    Casella non valida o gia' occupata.
    Mossa non valida.
  ```
  e alla fine
  ```
      O . X
      . X .
      X . O
  Vince X in 5 mosse!
  ```

### Test 2 – Pareggio

- **Input:** `1 1`, `2 2`, `1 2`, `1 3`, `2 3`, `2 1`, `3 1`, `3 2`, `3 3`
- **Output atteso:**
  ```
      X X O
      O O X
      X O X
  Pareggio.
  ```

### Test 3 – Vittoria su una riga e interruzione

- **Input:** `1 1`, `2 1`, `1 2`, `2 2`, `1 3`; poi `1 1` e fine input
- **Output atteso:** `Vince X in 5 mosse!`; poi `Partita interrotta.`
