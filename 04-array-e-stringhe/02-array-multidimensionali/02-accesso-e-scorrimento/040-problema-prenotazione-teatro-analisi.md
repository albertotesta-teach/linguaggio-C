# Analisi – 040-problema-prenotazione-teatro.c

## 1. Problema

Un teatro ha 5 file (A-E) da 8 posti, alcuni già venduti. L'operatore
inserisce richieste nella forma "fila posto" (es. `C 4`). Il programma deve
prenotare il posto se è libero, segnalare i posti inesistenti e, se il posto
è occupato, proporre il primo posto libero della stessa fila. Alla fine
stampa la mappa aggiornata e il numero di prenotazioni.

## 2. Analisi

### Input

| Variabile      | Tipo   | Descrizione                                      |
|----------------|--------|--------------------------------------------------|
| `lettera`      | `char` | Fila richiesta (A–E); `Z` termina l'inserimento  |
| `numero_posto` | `int`  | Posto richiesto (1–8)                            |

Lo stato iniziale della sala è inizializzato nel codice: la fila B è
completa, la fila E è vuota.

### Output
- Per ogni richiesta uno dei messaggi: "Prenotato", "Posto inesistente",
  "Occupato. Primo posto libero nella fila X: N" oppure
  "Occupato. La fila X e' completa.";
- alla fine la mappa della sala (`.` libero, `X` occupato) e il numero di
  posti prenotati nella sessione.

### Vincoli
- Fila e posto si convertono in indici: `riga = lettera − 'A'`,
  `colonna = numero_posto − 1`
- Una richiesta è valida solo se riga e colonna sono entro i limiti
  della matrice; altrimenti il posto è inesistente e la sala non cambia
- Le file vanno inserite in maiuscolo: una minuscola dà un indice fuori dai
  limiti ed è segnalata come posto inesistente
- Un posto occupato non viene mai sovrascritto: si propone il primo libero
  della stessa fila, cercato dal posto 1 e fermandosi al primo trovato con
  un flag nella condizione
- Si contano solo le prenotazioni effettivamente eseguite
- La sentinella `Z` termina l'inserimento e non richiede il numero del posto
- Se dopo la lettera non c'è un numero, il resto della riga si scarta e il
  posto risulta inesistente; a fine input (EOF) il programma si comporta
  come se fosse stata inserita la fila di fine

### Assunzioni
- La proposta del posto alternativo è solo un suggerimento: per prenotarlo
  serve una nuova richiesta

### Variabili di supporto

| Variabile         | Tipo      | Descrizione                                    |
|-------------------|-----------|------------------------------------------------|
| `sala`            | `int[][]` | 5 × 8: 0 = libero, 1 = occupato                |
| `riga`, `colonna` | `int`     | Indici ricavati dalla richiesta                |
| `alternativo`     | `int`     | Primo posto libero della fila, -1 se nessuno   |
| `prenotati`       | `int`     | Prenotazioni della sessione                    |
| `FILE_TEATRO`, `POSTI`, `LIBERO`, `OCCUPATO`, `FINE` | `#define` | 5, 8, 0, 1, 'Z' |

### Algoritmo in linguaggio naturale
1. Leggere la fila (lettura anticipata).
2. Finché la fila è diversa da `Z`:
   a. leggere il posto e calcolare riga e colonna;
   b. se sono fuori dai limiti stampare "Posto inesistente";
   c. altrimenti, se il posto è libero, occuparlo, contare la prenotazione
      e confermarla;
   d. altrimenti cercare il primo posto libero della riga e proporlo,
      oppure segnalare che la fila è completa;
   e. leggere la fila successiva.
3. Stampare la mappa e il numero di prenotazioni.

## 3. Casi di test

Si esegue il programma con la sequenza di richieste indicata, terminata da
`Z`, e si confronta l'output.

### Test 1 – Sessione completa
- **Input:** `A 3`, `A 1`, `B 4`, `F 2`, `C 9`, `c 1`, `E 8`, `Z`
- **Output atteso:**
  - `A 3` → `Prenotato: fila A, posto 3.`
  - `A 1` → `Occupato. Primo posto libero nella fila A: 4` (il posto 3 è
    stato appena prenotato)
  - `B 4` → `Occupato. La fila B e' completa.`
  - `F 2` (fila inesistente), `C 9` (posto inesistente), `c 1` (minuscola)
    → `Posto inesistente.`
  - `E 8` → `Prenotato: fila E, posto 8.`
- **Mappa finale attesa:**
```
      1 2 3 4 5 6 7 8
  A   X X X . X X . .
  B   X X X X X X X X
  C   . X X . . X X .
  D   . . . X X . . .
  E   . . . . . . . X

Posti prenotati in questa sessione: 2
```

### Test 2 – Fine immediata
- **Input:** `Z`
- **Output atteso:** la mappa iniziale invariata e
  `Posti prenotati in questa sessione: 0`

### Test 3 – Posto non numerico e fine dell'input
- **Cosa si verifica:** un posto scritto male non blocca il programma e la fine dell'input chiude la sessione
- **Input:** `C x`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Fila e posto (es. C 4):   Posto inesistente.
Fila e posto (es. C 4): 
=== MAPPA AGGIORNATA ===
...
Posti prenotati in questa sessione: 0
```
