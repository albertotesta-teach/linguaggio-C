# 03 – Enum nelle struct

## Concetto

Lo stato di un oggetto è spesso uno tra pochi valori: è il caso tipico di
un **campo enum** dentro una struct.

```c
typedef enum { DISPONIBILE, IN_PRESTITO, IN_RIPARAZIONE, NUM_STATI } Stato;

typedef struct {
    char titolo[28];
    Stato stato;
} Libro;

if (libri[i].stato == IN_PRESTITO) ...
conteggi[libri[i].stato]++;               /* lo stato è anche un indice */
```

Un solo campo enum ammette un solo stato alla volta; due campi `int`
(`prestato`, `rovinato`) potrebbero contraddirsi.

### Macchine a stati

Una macchina a stati passa da uno stato all'altro in risposta agli eventi.
Le regole si possono scrivere in una **tabella delle transizioni**:

```c
Stato transizioni[NUM_STATI][NUM_EVENTI] = {
    /*              PERSONA      FINE_CORSA  TEMPO_SCADUTO */
    [CHIUSA] =     {IN_APERTURA, CHIUSA,     CHIUSA},
    ...
};

stato = transizioni[stato][evento];
```

oppure con uno `switch` sullo stato, quando ogni passo fa anche altro
(spostare l'ascensore di un piano, contare una parola).

### Tabelle di struct indicizzate dall'enum

```c
Tariffa tariffe[NUM_CATEGORIE] = {
    [STUDENTE] = {"studente", 3.00, 6},
    [DOCENTE] = {"docente", 0.00, 2},
    ...
};

prezzo = tariffe[b.categoria].prezzo;
```

Una tabella sola al posto di uno switch per ogni informazione.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-campo-enum.c` | `Libro` con un campo `Stato`: conteggi e filtri per stato |
| `020-macchina-a-stati.c` | Porta automatica con la tabella delle transizioni |
| `030-tabella-indicizzata-da-enum.c` | Tariffe dello spettacolo indicizzate dalla categoria |
| `040-problema-ticket-assistenza.c` | Priorità e stato dei ticket, cambi di stato permessi da una tabella |
| `040-problema-ticket-assistenza-analisi.md` | Analisi di `040-problema-ticket-assistenza.c` |
| `050-problema-ascensore.c` | Macchina a stati dell'ascensore con uno switch |
| `050-problema-ascensore-analisi.md` | Analisi di `050-problema-ascensore.c` |
| `060-problema-tessere-mensa.c` | Fascia ISEE come campo enum e tabella dei prezzi |
| `060-problema-tessere-mensa-analisi.md` | Analisi di `060-problema-tessere-mensa.c` |
| `070-problema-gioco-tris.c` | Griglia di `Casella`, turni e `Risultato` |
| `070-problema-gioco-tris-analisi.md` | Analisi di `070-problema-gioco-tris.c` |
| `080-problema-analisi-testo.c` | Automa che conta parole, numeri e punteggiatura |
| `080-problema-analisi-testo-analisi.md` | Analisi di `080-problema-analisi-testo.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-campo-enum 010-campo-enum.c
./010-campo-enum

gcc -Wall -Wextra -o 020-macchina-a-stati 020-macchina-a-stati.c
./020-macchina-a-stati

gcc -Wall -Wextra -o 030-tabella-indicizzata-da-enum 030-tabella-indicizzata-da-enum.c
./030-tabella-indicizzata-da-enum

gcc -Wall -Wextra -o 040-problema-ticket-assistenza 040-problema-ticket-assistenza.c
./040-problema-ticket-assistenza

gcc -Wall -Wextra -o 050-problema-ascensore 050-problema-ascensore.c
./050-problema-ascensore

gcc -Wall -Wextra -o 060-problema-tessere-mensa 060-problema-tessere-mensa.c
./060-problema-tessere-mensa

gcc -Wall -Wextra -o 070-problema-gioco-tris 070-problema-gioco-tris.c
./070-problema-gioco-tris

gcc -Wall -Wextra -o 080-problema-analisi-testo 080-problema-analisi-testo.c
./080-problema-analisi-testo
```

---

## Output atteso

### 010-campo-enum
```
  disponibili     2
  in prestito     3
  in riparazione  1
Disponibili:
  Il barone rampante
  La luna e i falo'

"Io, robot" torna dalla riparazione.
  disponibili     3
  in prestito     3
  in riparazione  0
```

### 020-macchina-a-stati
```
Stato iniziale: CHIUSA
  tempo scaduto  CHIUSA       -> CHIUSA  (nessun cambiamento)
  persona        CHIUSA       -> IN_APERTURA
  fine corsa     IN_APERTURA  -> APERTA
  persona        APERTA       -> APERTA  (nessun cambiamento)
  tempo scaduto  APERTA       -> IN_CHIUSURA
  persona        IN_CHIUSURA  -> IN_APERTURA
  fine corsa     IN_APERTURA  -> APERTA
  tempo scaduto  APERTA       -> IN_CHIUSURA
  fine corsa     IN_CHIUSURA  -> CHIUSA
```

### 030-tabella-indicizzata-da-enum
```
Categoria   Prezzo  Venduti  Riservati
studente     3.00        4          6
docente      0.00        2          2
familiare    5.00        4          3  OLTRE I POSTI RISERVATI
esterno      8.00        2          1  OLTRE I POSTI RISERVATI
Incasso: 48.00 euro
```

### 040-problema-ticket-assistenza
*(output dipendente dall'input – esempio di sessione)*
```
Comando (N pc B/M/A, L n, C n, R n, E, Q): E
  2  PC-11  ALTA   in lavorazione
  1  PC-03  media  aperto
Comando (N pc B/M/A, L n, C n, R n, E, Q): N PC-14 A
  Ticket 4 aperto.
Comando (N pc B/M/A, L n, C n, R n, E, Q): N PC-02 X
  Priorita' non valida.
Comando (N pc B/M/A, L n, C n, R n, E, Q): L 1
  Ticket 1: in lavorazione
Comando (N pc B/M/A, L n, C n, R n, E, Q): C 1
  Ticket 1: chiuso
Comando (N pc B/M/A, L n, C n, R n, E, Q): C 4
  Ticket 4: da aperto a chiuso non e' permesso.
Comando (N pc B/M/A, L n, C n, R n, E, Q): L 4
  Ticket 4: in lavorazione
Comando (N pc B/M/A, L n, C n, R n, E, Q): C 4
  Ticket 4: chiuso
Comando (N pc B/M/A, L n, C n, R n, E, Q): R 3
  Ticket 3: aperto
Comando (N pc B/M/A, L n, C n, R n, E, Q): C 3
  Ticket 3: da aperto a chiuso non e' permesso.
Comando (N pc B/M/A, L n, C n, R n, E, Q): E
  2  PC-11  ALTA   in lavorazione
  3  PC-07  bassa  aperto
Comando (N pc B/M/A, L n, C n, R n, E, Q): Q
```

### 050-problema-ascensore
*(output dipendente dall'input – tre chiamate)*
```
Chiamata al piano (0-3, -1 per finire): 2
  piano 0  porte chiuse
  piano 0  in salita
  piano 1  in salita
  piano 2  porte aperte
  Arrivato in 4 passi.
Chiamata al piano (0-3, -1 per finire): 0
  piano 2  porte chiuse
  piano 2  in discesa
  piano 1  in discesa
  piano 0  porte aperte
  Arrivato in 4 passi.
Chiamata al piano (0-3, -1 per finire): 3
  piano 0  porte chiuse
  piano 0  in salita
  piano 1  in salita
  piano 2  in salita
  piano 3  porte aperte
  Arrivato in 5 passi.
Chiamata al piano (0-3, -1 per finire): 3
  Gia' al piano 3 con le porte aperte.
Chiamata al piano (0-3, -1 per finire): 5
  Il piano 5 non esiste.
Chiamata al piano (0-3, -1 per finire): -1
```

### 060-problema-tessere-mensa
*(output dipendente dall'input – esempio di sessione)*
```
Comando (P numero, S numero, R, Q): S 102
  102 Corti Ugo   fascia C, 4.80 euro a pasto, pasti 0: 0.00 euro
Comando (P numero, S numero, R, Q): P 102
  102 Corti Ugo   fascia C, 4.80 euro a pasto, pasti 1: 4.80 euro
Comando (P numero, S numero, R, Q): P 102
  102 Corti Ugo   fascia C, 4.80 euro a pasto, pasti 2: 9.60 euro
Comando (P numero, S numero, R, Q): P 104
  104 Elia Gino   fascia B, 3.50 euro a pasto, pasti 2: 7.00 euro
Comando (P numero, S numero, R, Q): S 104
  104 Elia Gino   fascia B, 3.50 euro a pasto, pasti 2: 7.00 euro
Comando (P numero, S numero, R, Q): S 999
  Tessera 999 inesistente.
Comando (P numero, S numero, R, Q): R
  fascia A: tessere 1, pasti  3,   6.00 euro
  fascia B: tessere 2, pasti  2,   7.00 euro
  fascia C: tessere 1, pasti  2,   9.60 euro
  fascia D: tessere 1, pasti  2,  11.80 euro
  totale 34.40 euro
Comando (P numero, S numero, R, Q): Q
```

### 070-problema-gioco-tris
*(output dipendente dall'input – vittoria di X)*
```
Mossa di X (riga colonna): 1 1
    X . .
    . . .
    . . .
Mossa di O (riga colonna): 2 2
    X . .
    . O .
    . . .
Mossa di X (riga colonna): 1 2
    X X .
    . O .
    . . .
Mossa di O (riga colonna): 3 3
    X X .
    . O .
    . . O
Mossa di X (riga colonna): 1 3
    X X X
    . O .
    . . O
Vince X in 5 mosse!
```

*(output dipendente dall'input – pareggio con due mosse sbagliate)*
```
Mossa di X (riga colonna): 2 2
    . . .
    . X .
    . . .
Mossa di O (riga colonna): 1 1
    O . .
    . X .
    . . .
Mossa di X (riga colonna): 1 3
    O . X
    . X .
    . . .
Mossa di O (riga colonna): 3 1
    O . X
    . X .
    O . .
Mossa di X (riga colonna): 2 1
    O . X
    X X .
    O . .
Mossa di O (riga colonna): 2 1
  Casella non valida o gia' occupata.
Mossa di O (riga colonna): 4 4
  Casella non valida o gia' occupata.
Mossa di O (riga colonna): 2 3
    O . X
    X X O
    O . .
Mossa di X (riga colonna): 1 2
    O X X
    X X O
    O . .
Mossa di O (riga colonna): 3 2
    O X X
    X X O
    O O .
Mossa di X (riga colonna): 3 3
    O X X
    X X O
    O O X
Pareggio.
```

### 080-problema-analisi-testo
*(output dipendente dall'input – due righe)*
```
Testo (FINE su una riga per terminare):
La 3B va in gita il 12 aprile: partenza alle 7.
Costo 45 euro, A4 per i moduli; 2 accompagnatori!
FINE
Righe 2, parole 16, numeri 4, segni di punteggiatura 5
```

---

## Errori comuni da evitare

**Usare più campi int per uno stato solo**
```c
int prestato;
int in_riparazione;          /* possono valere 1 entrambi */
Stato stato;                 /* corretto: un solo stato alla volta */
```

**Cambiare stato senza controllare se il cambio è permesso**
```c
t->stato = CHIUSO;                       /* anche da APERTO? */
if (permesso[t->stato][CHIUSO]) ...      /* corretto */
```

**Dimenticare una riga o una colonna nella tabella delle transizioni**
```c
Stato transizioni[NUM_STATI][NUM_EVENTI] = {[CHIUSA] = {...}};   /* le altre righe valgono 0 */
```

**Confondere lo stato con l'evento**
```c
transizioni[evento][stato]        /* indici scambiati */
transizioni[stato][evento]        /* corretto */
```

**Usare una costante di un enum in un campo di un altro enum**
```c
t.priorita = CHIUSO;      /* avviso -Wenum-conversion: è uno Stato, non una Priorita */
```

---

## Concetti collegati

- `02-struct` → struct e array di struct
- `02-enum-e-switch` → switch su enum e conversioni
- `04-array-e-stringhe/02-array-multidimensionali` → tabelle a due indici
- `06-union` → una union scelta da un campo enum

---

## Esercizi proposti

1. In `010-campo-enum.c` aggiungi lo stato `PERSO` e un comando per
   segnalare un libro smarrito.

2. In `020-macchina-a-stati.c` aggiungi l'evento `OSTACOLO`: la porta in
   chiusura si riapre.

3. In `040-problema-ticket-assistenza.c` permetti di chiudere direttamente
   un ticket aperto a bassa priorità.

4. In `050-problema-ascensore.c` conta i piani percorsi in tutta la
   sessione.

5. (Avanzato) In `070-problema-gioco-tris.c` fai giocare `O` al computer:
   sceglie la prima casella che gli dà la vittoria, altrimenti quella che
   blocca `X`, altrimenti la prima libera.
