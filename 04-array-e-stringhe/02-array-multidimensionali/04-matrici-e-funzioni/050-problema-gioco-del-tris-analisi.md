# Analisi – 050-problema-gioco-del-tris.c

## 1. Problema

Realizzare il gioco del tris per due giocatori sulla console. I giocatori
inseriscono a turno riga e colonna (da 1 a 3); il programma rifiuta le mosse
non valide, disegna la griglia dopo ogni mossa e termina con la vittoria di
un giocatore o con il pareggio a griglia piena.

## 2. Analisi

### Input

| Variabile         | Tipo  | Descrizione                                   |
|-------------------|-------|-----------------------------------------------|
| `riga`, `colonna` | `int` | Casella scelta dal giocatore di turno (1–3)   |

### Output
- La griglia vuota all'inizio e la griglia aggiornata dopo ogni mossa
  valida;
- "Mossa non valida: casella inesistente o occupata." per le mosse
  rifiutate;
- alla fine "Vince il giocatore X!" (o O) oppure "Pareggio.".

### Vincoli
- Una mossa è valida se riga e colonna sono tra 1 e 3 e la casella è vuota;
  grazie al corto circuito di `&&` la casella si legge solo se gli indici
  sono validi
- Dopo una mossa non valida il turno **non** passa all'altro giocatore
- Inizia sempre X; dopo ogni mossa valida il turno cambia
- Si vince con tre simboli uguali su una riga, una colonna o una diagonale;
  la vittoria si controlla dopo ogni mossa valida
- La partita termina appena c'è un vincitore oppure quando la griglia è
  piena: la condizione del ciclo contiene entrambi i casi (niente `break`)
- Ogni funzione ha una sola `return`
- Se la mossa non contiene due numeri il resto della riga si scarta e la
  mossa non è valida; a fine input (EOF) la partita si interrompe senza
  risultato

### Assunzioni
- Nessuna in particolare


### Variabili di supporto

| Variabile   | Tipo       | Dimensione | Descrizione                         |
|-------------|------------|------------|-------------------------------------|
| `griglia`   | `char[][]` | 3 × 3      | `' '` vuota, `'X'`, `'O'`           |
| `giocatore` | `char`     | —          | Simbolo del giocatore di turno      |
| `vince`     | `char`     | —          | Vincitore oppure `' '`              |
| `LATO`, `VUOTA` | `#define` | —       | 3 e `' '`                           |

| Funzione | Descrizione |
|---|---|
| `void svuota(char g[][LATO])` | Tutte le caselle a vuota |
| `void stampa(const char g[][LATO])` | Griglia con le coordinate |
| `int mossa_valida(const char g[][LATO], int r, int c)` | Indici nei limiti e casella vuota |
| `char vincitore(const char g[][LATO])` | Simbolo vincente oppure vuota |
| `int griglia_piena(const char g[][LATO])` | 1 se non ci sono caselle vuote |

### Algoritmo in linguaggio naturale
1. Svuotare e stampare la griglia; il primo giocatore è X.
2. Finché non c'è un vincitore e la griglia non è piena:
   a. leggere riga e colonna;
   b. se la mossa è valida scrivere il simbolo, stampare la griglia,
      calcolare il vincitore e passare il turno;
   c. altrimenti stampare il messaggio di errore.
3. Stampare il vincitore oppure il pareggio.

Vincitore: per ogni i controllare la riga i e la colonna i (caselle non
vuote e uguali); se non c'è un tris, e la casella centrale non è vuota,
controllare le due diagonali.

## 3. Casi di test

Ogni test è una partita: si inseriscono le mosse nell'ordine indicato
(riga colonna), alternando X e O.

### Test 1 – Vittoria su una riga
- **Input:** `1 1`, `2 1`, `1 2`, `2 2`, `1 3`
- **Output atteso:**
```
     1   2   3
  1  X | X | X 
    ---+---+---
  2  O | O |   
    ---+---+---
  3    |   |   

Vince il giocatore X!
```

### Test 2 – Mosse non valide e vittoria in diagonale
- **Cosa si verifica:** una casella occupata e una inesistente sono
  rifiutate senza cambiare turno; vittoria sulla diagonale secondaria
- **Input:** `1 1` (X), `2 2` (O), `1 1` e `4 1` (rifiutate, resta X),
  `1 2` (X), `1 3` (O), `3 3` (X), `3 1` (O)
- **Output atteso:** due volte
  `Mossa non valida: casella inesistente o occupata.`, poi
  `Vince il giocatore O!`

### Test 3 – Pareggio
- **Input:** `1 1`, `1 2`, `1 3`, `2 2`, `2 1`, `2 3`, `3 2`, `3 1`, `3 3`
- **Output atteso:**
```
     1   2   3
  1  X | O | X 
    ---+---+---
  2  X | O | O 
    ---+---+---
  3  O | X | X 

Pareggio.
```

### Test 4 – Mossa non numerica e fine dell'input
- **Cosa si verifica:** testo al posto dei numeri e chiusura senza ciclo infinito
- **Input:** `a b`, `2 2`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Giocatore X, riga e colonna (1-3): Mossa non valida: casella inesistente o occupata.
Giocatore X, riga e colonna (1-3): 
...
Giocatore O, riga e colonna (1-3): 

Input terminato: partita interrotta.
```
