# Analisi – 070-problema-campo-minato.c

## 1. Problema

Realizzare il campo minato su una griglia 6 × 8 con mine in posizioni fisse.
Il giocatore scopre una cella alla volta indicando riga e colonna (da 1).
Una cella sicura scoperta mostra quante mine ha intorno (spazio se nessuna);
le celle coperte sono mostrate con `#`. Il giocatore perde se scopre una mina
e vince quando ha scoperto tutte le celle sicure. Alla fine si mostra il
campo completo.

## 2. Analisi

### Input

| Variabile                         | Tipo  | Descrizione                    |
|-----------------------------------|-------|--------------------------------|
| `riga_utente`, `colonna_utente`   | `int` | Cella da scoprire (1–6, 1–8)   |

Il campo è inizializzato nel codice con 5 mine, quindi 43 celle sicure.

### Output
- All'inizio il numero di celle sicure e il campo tutto coperto (`#`);
- dopo ogni cella sicura scoperta il campo aggiornato; per le richieste non
  valide "Cella inesistente." oppure "Cella gia' scoperta.";
- alla fine "BOOM! Hai trovato una mina. Il campo era:" oppure
  "Complimenti, campo sminato!", seguito dal campo completo con mine (`*`) e
  numeri.

### Vincoli
- Il numero di una cella è quello delle mine nelle 8 celle intorno, esclusa
  la cella stessa e senza uscire dalla griglia
- I numeri si calcolano **una sola volta** all'inizio, in una matrice
  parallela, invece di ricontarli a ogni stampa
- Le tre matrici `mine`, `numeri` e `scoperte` sono parallele: la stessa
  coppia di indici descrive la stessa cella
- Una cella inesistente o già scoperta non cambia la partita
- La partita termina appena si scopre una mina oppure quando le celle sicure
  scoperte sono quante le celle sicure: entrambe le condizioni sono nel ciclo
- Una cella con 0 mine vicine si stampa come spazio
- Non c'è l'apertura automatica delle celle vicine alle celle con 0
- Se la mossa non contiene due numeri il resto della riga si scarta e la
  cella risulta inesistente; a fine input (EOF) la partita si interrompe
  senza risultato

### Assunzioni
- Nessuna in particolare


### Variabili di supporto

| Variabile   | Tipo       | Dimensione  | Descrizione                                   |
|-------------|------------|-------------|-----------------------------------------------|
| `mine`      | `char[][]` | 6 × (8 + 1) | Campo segreto: `'*'` mina, `'.'` sicura       |
| `numeri`    | `int[][]`  | 6 × 8       | Mine vicine a ogni cella                      |
| `scoperte`  | `int[][]`  | 6 × 8       | 1 se la cella è scoperta; inizializzata a 0   |
| `celle_sicure`, `scoperte_sicure` | `int` | — | Condizione di vittoria                |
| `esplosa`   | `int` (0/1)| —           | Condizione di sconfitta                       |

| Funzione | Descrizione |
|---|---|
| `int conta_mine_vicine(const char m[][COLONNE + 1], int r, int c)` | Mine nelle 8 celle intorno |
| `void stampa_campo(..., int mostra_mine)` | Celle coperte, numeri e, a fine partita, le mine |

### Algoritmo in linguaggio naturale
1. Per ogni cella calcolare il numero di mine vicine e contare le celle
   sicure; stampare il campo coperto.
2. Finché non è esplosa una mina e restano celle sicure da scoprire:
   a. leggere riga e colonna e ricavare gli indici;
   b. se la cella non esiste o è già scoperta stampare il messaggio;
   c. altrimenti segnarla come scoperta: se è una mina la partita è persa,
      altrimenti contarla e stampare il campo.
3. Stampare l'esito e il campo completo.

## 3. Casi di test

Si esegue il programma con la sequenza di celle indicata.

### Test 1 – Sconfitta
- **Cosa si verifica:** cella già scoperta, cella inesistente, mina
- **Input:** `3 3`, `3 3`, `7 1`, `2 2`
- **Output atteso:** dopo `3 3` il campo con la cella che mostra `2`; poi
  `Cella gia' scoperta.`, `Cella inesistente.` e infine
```
BOOM! Hai trovato una mina. Il campo era:

    1 2 3 4 5 6 7 8 
  1 1 1 1     1 * 1 
  2 1 * 1     1 1 1 
  3 1 1 2 1 1 1 1 1 
  4     1 * 1 1 * 1 
  5 1 1 1 1 1 1 1 1 
  6 * 1             
```

### Test 2 – Vittoria
- **Input:** le 43 celle sicure, in qualsiasi ordine
- **Output atteso:** `Complimenti, campo sminato!` e lo stesso campo
  completo del Test 1

### Test 3 – Mossa non numerica e fine dell'input
- **Cosa si verifica:** testo al posto dei numeri e chiusura senza ciclo infinito
- **Input:** `tre 4`, `1 1`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Riga e colonna (es. 3 4):   Cella inesistente.
Riga e colonna (es. 3 4): 
...
Riga e colonna (es. 3 4): 

Input terminato: partita interrotta.
```
