# Analisi – 050-problema-battaglia-navale.c

## 1. Problema

Realizzare una battaglia navale in solitario su una griglia 6 × 8. La flotta
è nascosta; il giocatore indica una cella con una lettera (riga A–F) e un
numero (colonna 1–8) e il programma risponde "Colpito" o "Acqua",
mostrando la griglia dei tiri. Il giocatore ha 20 colpi; una cella già colpita
o inesistente non consuma colpi. La partita termina quando tutte le parti di
nave sono state colpite o quando i colpi sono finiti.

## 2. Analisi

### Input

| Variabile        | Tipo   | Descrizione                       |
|------------------|--------|-----------------------------------|
| `lettera`        | `char` | Riga del colpo (A–F)              |
| `colonna_utente` | `int`  | Colonna del colpo (1–8)           |

La flotta è inizializzata nel codice: 11 parti di nave.

### Output
- All'inizio le parti di nave da colpire, i colpi disponibili e la griglia
  dei tiri tutta `?`;
- per ogni colpo "COLPITO!", "Acqua.", "Cella inesistente." oppure
  "Cella gia' colpita.", e la griglia aggiornata dopo ogni colpo valido;
- alla fine "Flotta affondata con N colpi!" oppure "Colpi esauriti: restano
  N parti di nave." seguito dalla flotta.

### Vincoli
- Le due griglie `flotta` e `tiri` hanno la stessa dimensione e sono
  **parallele**: la stessa coppia di indici descrive la stessa cella
- Indici: `r = lettera − 'A'`, `c = colonna_utente − 1`; le righe vanno
  scritte in maiuscolo
- Una cella inesistente o già colpita non consuma un colpo
- La partita termina quando le parti di nave da affondare arrivano a 0
  oppure quando i colpi arrivano a 0: entrambe le condizioni sono nel ciclo
- Ogni riga di `tiri` ha `COLONNE + 1` caratteri: `inizializza_tiri` scrive
  anche il `'\0'` finale
- Se il colpo non contiene una lettera e un numero il resto della riga si
  scarta e la cella risulta inesistente; a fine input (EOF) la partita si
  interrompe senza risultato

### Assunzioni
- Le parti di nave non sono raggruppate in navi: si contano singolarmente

### Variabili di supporto

| Variabile       | Tipo       | Dimensione  | Descrizione                                    |
|-----------------|------------|-------------|------------------------------------------------|
| `flotta`        | `char[][]` | 6 × (8 + 1) | Griglia segreta: `'N'` nave, `'.'` mare        |
| `tiri`          | `char[][]` | 6 × (8 + 1) | Griglia visibile: `'?'`, `'O'` acqua, `'X'` colpita |
| `r`, `c`        | `int`      | —           | Indici calcolati                               |
| `colpi_rimasti`, `da_affondare` | `int` | — | Condizioni di fine partita                 |
| `RIGHE`, `COLONNE`, `COLPI` | `#define` | — | 6, 8, 20                               |

| Funzione | Descrizione |
|---|---|
| `void inizializza_tiri(char t[][COLONNE + 1])` | Riempie di `'?'` e chiude ogni riga |
| `void stampa_griglia(const char g[][COLONNE + 1])` | Griglia con le coordinate |
| `int conta_celle(const char g[][COLONNE + 1], char simbolo)` | Celle con un simbolo |

### Algoritmo in linguaggio naturale
1. Inizializzare i tiri, contare le parti di nave e stampare la griglia.
2. Finché restano parti di nave e colpi:
   a. leggere lettera e numero e calcolare gli indici;
   b. se la cella non esiste, o è già stata colpita, stampare il messaggio
      senza consumare il colpo;
   c. altrimenti consumare il colpo; se c'è una nave segnare X e
      decrementare le parti da affondare, altrimenti segnare O; stampare la
      griglia.
3. Stampare la vittoria con i colpi usati, oppure le parti rimaste e la
   flotta.

## 3. Casi di test

Si esegue il programma con la sequenza di colpi indicata.

### Test 1 – Vittoria con colpi non validi
- **Cosa si verifica:** celle già colpite, inesistenti e in minuscolo non
  consumano colpi
- **Input:** `A 1`, `A 1`, `G 1`, `A 9`, `B 1`, `a 2`, `A 2`, `A 3`, `A 4`,
  `C 3`, `D 3`, `E 3`, `C 7`, `D 7`, `F 5`, `F 6`
- **Output atteso:** `COLPITO!` per A 1; `Cella gia' colpita.` per il
  secondo A 1; `Cella inesistente.` per G 1, A 9 e a 2; `Acqua.` per B 1;
  `COLPITO!` per le altre dieci celle; alla fine
  `Flotta affondata con 12 colpi!`

### Test 2 – Colpi esauriti
- **Input:** 20 colpi tutti in mare: A 5–8, B 1–8, C 1, 2, 4, 5, 6, 8, D 1,
  D 2
- **Output atteso:** `Colpi esauriti: restano 11 parti di nave.` e la flotta:
```
    1 2 3 4 5 6 7 8 
  A N N N N . . . . 
  B . . . . . . . . 
  C . . N . . . N . 
  D . . N . . . N . 
  E . . N . . . . . 
  F . . . . N N . . 
```

### Test 3 – Colpo non numerico e fine dell'input
- **Cosa si verifica:** testo al posto del numero e chiusura senza ciclo infinito
- **Input:** `C quattro`, `A 1`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Colpo (es. C 4), rimasti 20:   Cella inesistente.
Colpo (es. C 4), rimasti 20:   COLPITO!
...
Colpo (es. C 4), rimasti 19: 

Input terminato: partita interrotta.
```
