# 05 – Griglie di caratteri

## Concetto

Mappe, labirinti, campi da gioco e simulazioni si rappresentano bene con una
**matrice di `char`**: ogni cella contiene un simbolo che ne descrive il
contenuto.

```c
#define RIGHE   4
#define COLONNE 6

char mappa[RIGHE][COLONNE + 1] = {
    "..^^~~",
    ".^^.~~",
    "..#...",
    "C....."
};
```

### Perché `COLONNE + 1`

Scrivere ogni riga come stringa tra virgolette è comodo, ma una stringa
termina con il carattere `'\0'`, che occupa una cella in più. Le celle "vere"
restano `COLONNE` e i cicli scorrono solo quelle:

```c
for (c = 0; c < COLONNE; c++) {
    printf("%c", mappa[r][c]);
}
```

Se una griglia viene riempita da programma (non con le stringhe), conviene
scrivere comunque `'\0'` in `[r][COLONNE]`, così ogni riga resta una stringa
corretta.

### Le 8 celle vicine: spostamenti `dr`, `dc`

Invece di scrivere otto controlli separati si usano due cicli sugli
spostamenti di riga e di colonna, che valgono -1, 0, +1:

```c
for (dr = -1; dr <= 1; dr++) {
    for (dc = -1; dc <= 1; dc++) {
        rv = r + dr;
        cv = c + dc;
        if (!(dr == 0 && dc == 0)
            && rv >= 0 && rv < RIGHE && cv >= 0 && cv < COLONNE
            && g[rv][cv] == SIMBOLO) {
            n++;
        }
    }
}
```

Il controllo dei limiti viene **prima** dell'accesso `g[rv][cv]`: grazie alla
valutazione da sinistra a destra di `&&` la cella fuori dalla griglia non
viene mai letta. Lo stesso schema, con un solo `dr`/`dc` scelto da uno
`switch`, sposta un personaggio nelle 4 direzioni.

### Aggiornare tutta la griglia insieme: due matrici

Nelle simulazioni (incendio, gioco della vita) il nuovo stato di ogni cella
dipende dallo stato **attuale** delle vicine. Se si modifica la griglia
mentre la si scorre, le celle successive vedono valori già cambiati e il
risultato è sbagliato. La regola è:

1. leggere solo da `attuale`;
2. scrivere solo in `nuova`;
3. alla fine copiare `nuova` in `attuale`.

### Griglie parallele

Più matrici della stessa dimensione possono descrivere aspetti diversi delle
stesse celle: nella battaglia navale `flotta` (segreta) e `tiri` (visibile);
nel campo minato `mine`, `numeri` e `scoperte`.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-griglia-di-caratteri.c` | Mappa inizializzata con stringhe, stampa con coordinate, conteggio dei simboli, ricerca su riga e colonna |
| `020-vicini-di-una-cella.c` | Conteggio delle 8 vicine con `dr`, `dc`: mappa del rischio di un frutteto |
| `030-aggiornamento-in-due-griglie.c` | Propagazione di un incendio: aggiornamento sul posto (sbagliato) e con due griglie (corretto) |
| `040-problema-robot-magazzino.c` | Robot guidato con N S E O che raccoglie pacchi evitando gli scaffali |
| `040-problema-robot-magazzino-analisi.md` | Analisi di `040-problema-robot-magazzino.c` |
| `050-problema-battaglia-navale.c` | Battaglia navale in solitario con griglia segreta e griglia dei tiri |
| `050-problema-battaglia-navale-analisi.md` | Analisi di `050-problema-battaglia-navale.c` |
| `060-problema-gioco-della-vita.c` | Gioco della vita di Conway: aliante e lampeggiatore per 4 generazioni |
| `060-problema-gioco-della-vita-analisi.md` | Analisi di `060-problema-gioco-della-vita.c` |
| `070-problema-campo-minato.c` | Campo minato con matrice dei numeri calcolata una sola volta |
| `070-problema-campo-minato-analisi.md` | Analisi di `070-problema-campo-minato.c` |
| `080-problema-mappa-del-tesoro.c` | Percorso su un'isola guidato da due array paralleli (direzioni e passi) |
| `080-problema-mappa-del-tesoro-analisi.md` | Analisi di `080-problema-mappa-del-tesoro.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-griglia-di-caratteri 010-griglia-di-caratteri.c
./010-griglia-di-caratteri

gcc -Wall -Wextra -o 020-vicini-di-una-cella 020-vicini-di-una-cella.c
./020-vicini-di-una-cella

gcc -Wall -Wextra -o 030-aggiornamento-in-due-griglie 030-aggiornamento-in-due-griglie.c
./030-aggiornamento-in-due-griglie

gcc -Wall -Wextra -o 040-problema-robot-magazzino 040-problema-robot-magazzino.c
./040-problema-robot-magazzino

gcc -Wall -Wextra -o 050-problema-battaglia-navale 050-problema-battaglia-navale.c
./050-problema-battaglia-navale

gcc -Wall -Wextra -o 060-problema-gioco-della-vita 060-problema-gioco-della-vita.c
./060-problema-gioco-della-vita

gcc -Wall -Wextra -o 070-problema-campo-minato 070-problema-campo-minato.c
./070-problema-campo-minato

gcc -Wall -Wextra -o 080-problema-mappa-del-tesoro 080-problema-mappa-del-tesoro.c
./080-problema-mappa-del-tesoro
```

---

## Output atteso

### 010-griglia-di-caratteri
```
=== MAPPA DEL TERRITORIO ===
   012345678901
 0 ..^^^...~~..
 1 .^^^....~~..
 2 ......C.~~~.
 3 ##.......~~.
 4 ###..^^...~.
 5 ##..^^^^....

Prato  ('.'): 42 celle
Bosco  ('^'): 12 celle
Acqua  ('~'): 10 celle
Roccia ('#'):  7 celle
Totale      : 72 celle

Casa in riga 2, colonna 6
Acqua raggiungibile in linea retta: si'
```

### 020-vicini-di-una-cella
```
Frutteto (X = albero malato):    Alberi malati vicini:
  o . o . o . o .                 1 1 1 0 0 0 1 1 
  o X o . o . o X                 1 0 2 1 1 0 1 0 
  o . o X o . o .                 1 1 2 0 1 0 1 1 
  o . o . o . o .                 1 1 1 1 1 0 1 1 
  X . o . o . o X                 0 1 0 0 0 0 1 0 

Vicini della cella [0][0] (angolo): 1
Vicini della cella [2][2]: 2
```

### 030-aggiornamento-in-due-griglie
```
=== Aggiornamento sul posto (SBAGLIATO) ===
passo 0
  ^^^^^^^^^^
  *^^^^^^^^^
  ^^^^^^^^^^
passo 1
  **********
  **********
  **********
In un solo passo il fuoco ha raggiunto tutto il bosco.

=== Aggiornamento con due griglie (CORRETTO) ===
passo 0
  ^^^^^^^^^^
  *^^^^^^^^^
  ^^^^^^^^^^
passo 1
  *^^^^^^^^^
  **^^^^^^^^
  *^^^^^^^^^
passo 2
  **^^^^^^^^
  ***^^^^^^^
  **^^^^^^^^
passo 3
  ***^^^^^^^
  ****^^^^^^
  ***^^^^^^^
```

### 040-problema-robot-magazzino
*(output dipendente dall'input – esempio con uno scaffale, un comando sconosciuto e un pacco raccolto)*
```
=== MAGAZZINO AUTOMATICO ===
Pacchi da raccogliere: 3

  R...#....P
  .##.#.##..
  .#P...#...
  .#.##.#.##
  ...P..#...
  ####......

Comando (N S E O, Q = fine): E
Comando (N S E O, Q = fine): E
Comando (N S E O, Q = fine): E
Comando (N S E O, Q = fine): E
  Scaffale: movimento annullato.
Comando (N S E O, Q = fine): X
  Comando sconosciuto.
Comando (N S E O, Q = fine): S
Comando (N S E O, Q = fine): S
Comando (N S E O, Q = fine): O
  Pacco raccolto! (1)
Comando (N S E O, Q = fine): Q

  ....#....P
  .##.#.##..
  .#R...#...
  .#.##.#.##
  ...P..#...
  ####......

Mosse eseguite: 6, pacchi raccolti: 1, rimasti: 2
```

### 050-problema-battaglia-navale
*(output dipendente dall'input – esempio con COLPI impostato a 5 per accorciare la partita)*
```
=== BATTAGLIA NAVALE ===
Parti di nave da colpire: 11, colpi disponibili: 5

    1 2 3 4 5 6 7 8 
  A ? ? ? ? ? ? ? ? 
  B ? ? ? ? ? ? ? ? 
  C ? ? ? ? ? ? ? ? 
  D ? ? ? ? ? ? ? ? 
  E ? ? ? ? ? ? ? ? 
  F ? ? ? ? ? ? ? ? 

Colpo (es. C 4), rimasti 5: A 1
  COLPITO!

    1 2 3 4 5 6 7 8 
  A X ? ? ? ? ? ? ? 
  B ? ? ? ? ? ? ? ? 
  C ? ? ? ? ? ? ? ? 
  D ? ? ? ? ? ? ? ? 
  E ? ? ? ? ? ? ? ? 
  F ? ? ? ? ? ? ? ? 

Colpo (es. C 4), rimasti 4: B 2
  Acqua.

    1 2 3 4 5 6 7 8 
  A X ? ? ? ? ? ? ? 
  B ? O ? ? ? ? ? ? 
  C ? ? ? ? ? ? ? ? 
  D ? ? ? ? ? ? ? ? 
  E ? ? ? ? ? ? ? ? 
  F ? ? ? ? ? ? ? ? 

Colpo (es. C 4), rimasti 3: A 1
  Cella gia' colpita.
Colpo (es. C 4), rimasti 3: Z 3
  Cella inesistente.
Colpo (es. C 4), rimasti 3: C 3
  COLPITO!

    1 2 3 4 5 6 7 8 
  A X ? ? ? ? ? ? ? 
  B ? O ? ? ? ? ? ? 
  C ? ? X ? ? ? ? ? 
  D ? ? ? ? ? ? ? ? 
  E ? ? ? ? ? ? ? ? 
  F ? ? ? ? ? ? ? ? 

Colpo (es. C 4), rimasti 2: F 6
  COLPITO!

    1 2 3 4 5 6 7 8 
  A X ? ? ? ? ? ? ? 
  B ? O ? ? ? ? ? ? 
  C ? ? X ? ? ? ? ? 
  D ? ? ? ? ? ? ? ? 
  E ? ? ? ? ? ? ? ? 
  F ? ? ? ? ? X ? ? 

Colpo (es. C 4), rimasti 1: D 5
  Acqua.

    1 2 3 4 5 6 7 8 
  A X ? ? ? ? ? ? ? 
  B ? O ? ? ? ? ? ? 
  C ? ? X ? ? ? ? ? 
  D ? ? ? ? O ? ? ? 
  E ? ? ? ? ? ? ? ? 
  F ? ? ? ? ? X ? ? 

Colpi esauriti: restano 8 parti di nave.
La flotta era:

    1 2 3 4 5 6 7 8 
  A N N N N . . . . 
  B . . . . . . . . 
  C . . N . . . N . 
  D . . N . . . N . 
  E . . N . . . . . 
  F . . . . N N . . 
```

### 060-problema-gioco-della-vita
```
=== GIOCO DELLA VITA ===

Generazione 0 (celle vive: 8)
  .#..........
  ..#.........
  ###.........
  ............
  ............
  ........###.
  ............
  ............

Generazione 1 (celle vive: 8)
  ............
  #.#.........
  .##.........
  .#..........
  .........#..
  .........#..
  .........#..
  ............

Generazione 2 (celle vive: 8)
  ............
  ..#.........
  #.#.........
  .##.........
  ............
  ........###.
  ............
  ............

Generazione 3 (celle vive: 8)
  ............
  .#..........
  ..##........
  .##.........
  .........#..
  .........#..
  .........#..
  ............

Generazione 4 (celle vive: 8)
  ............
  ..#.........
  ...#........
  .###........
  ............
  ........###.
  ............
  ............
Dopo 4 generazioni l'aliante si e' spostato di una cella
in basso a destra; il lampeggiatore e' tornato orizzontale.
```

### 070-problema-campo-minato
*(output dipendente dall'input – esempio che termina su una mina)*
```
=== CAMPO MINATO ===
Celle sicure da scoprire: 43

    1 2 3 4 5 6 7 8 
  1 # # # # # # # # 
  2 # # # # # # # # 
  3 # # # # # # # # 
  4 # # # # # # # # 
  5 # # # # # # # # 
  6 # # # # # # # # 

Riga e colonna (es. 3 4): 1 1

    1 2 3 4 5 6 7 8 
  1 1 # # # # # # # 
  2 # # # # # # # # 
  3 # # # # # # # # 
  4 # # # # # # # # 
  5 # # # # # # # # 
  6 # # # # # # # # 

Riga e colonna (es. 3 4): 6 8

    1 2 3 4 5 6 7 8 
  1 1 # # # # # # # 
  2 # # # # # # # # 
  3 # # # # # # # # 
  4 # # # # # # # # 
  5 # # # # # # # # 
  6 # # # # # # #   

Riga e colonna (es. 3 4): 3 3

    1 2 3 4 5 6 7 8 
  1 1 # # # # # # # 
  2 # # # # # # # # 
  3 # # 2 # # # # # 
  4 # # # # # # # # 
  5 # # # # # # # # 
  6 # # # # # # #   

Riga e colonna (es. 3 4): 9 9
  Cella inesistente.
Riga e colonna (es. 3 4): 3 3
  Cella gia' scoperta.
Riga e colonna (es. 3 4): 4 4
BOOM! Hai trovato una mina. Il campo era:

    1 2 3 4 5 6 7 8 
  1 1 1 1     1 * 1 
  2 1 * 1     1 1 1 
  3 1 1 2 1 1 1 1 1 
  4     1 * 1 1 * 1 
  5 1 1 1 1 1 1 1 1 
  6 * 1             
```

### 080-problema-mappa-del-tesoro
```
=== ISOLA DEL TESORO ===
  ~~~~~~~~~~~~~~
  ~~X......~~~~~
  ~~...^^^..~~~~
  ~~..^^#^^..~~~
  ~~~..^^^$..~~~
  ~~~.......~~~~
  ~~~~~...~~~~~~
  ~~~~~~~~~~~~~~
Partenza dal relitto in riga 1, colonna 2

Tratto 1: 5 passi verso E
Tratto 2: 4 passi verso S
Tratto 3: 1 passo verso E
Tratto 4: 1 passo verso N

Posizione finale: riga 4, colonna 8
TESORO TROVATO!
  ~~~~~~~~~~~~~~
  ~~Xooooo.~~~~~
  ~~...^^o..~~~~
  ~~..^^#o^..~~~
  ~~~..^^o$..~~~
  ~~~....oo.~~~~
  ~~~~~...~~~~~~
  ~~~~~~~~~~~~~~
```

---

## Errori comuni da evitare

**Dimenticare lo spazio per `'\0'`**
```c
char riga[2][4] = { "ABCD", "EFGH" };   /* "ABCD" richiede 5 caratteri:
                                           il terminatore non entra */
char riga[2][4 + 1] = { "ABCD", "EFGH" };  /* corretto */
```

**Cicli che arrivano a `COLONNE + 1`**
```c
for (c = 0; c <= COLONNE; c++)   /* stampa anche il '\0' */
for (c = 0; c < COLONNE; c++)    /* corretto */
```

**Leggere la cella prima di controllare i limiti**
```c
if (g[r + dr][c + dc] != '#' && r + dr >= 0 ...)   /* accesso fuori dalla matrice */
if (r + dr >= 0 && ... && g[r + dr][c + dc] != '#') /* corretto */
```

**Aggiornare la griglia mentre la si legge**
```c
/* il nuovo stato va scritto in un'altra matrice, non in quella che si sta
   esaminando: vedi 030-aggiornamento-in-due-griglie.c */
```

**Confondere `'.'` e `"."`**
```c
mappa[r][c] = ".";   /* ERRORE: "." è una stringa, non un carattere */
mappa[r][c] = '.';   /* corretto */
```

**Coordinate dell'utente usate senza conversione**
```c
r = lettera - 'A';      /* 'A' -> 0, 'B' -> 1, ... */
c = numero - 1;         /* l'utente conta da 1, gli indici da 0 */
```

---

## Concetti collegati

- `01-dichiarazione-e-inizializzazione` → `char nomi[N][LEN]` e il terminatore
- `04-matrici-e-funzioni` → passaggio della griglia a funzione (`[][COLONNE + 1]`)
- `02-controllo-del-flusso/03-switch` → scelta della direzione
- `02-controllo-del-flusso/01-logica-booleana` → valutazione a corto circuito di `&&`
- `03-stringhe` → la stringa come array di `char` terminato da `'\0'`

---

## Esercizi proposti

1. In `010-griglia-di-caratteri.c` aggiungi una funzione che conta quante
   celle d'acqua `'~'` confinano (nelle 4 direzioni) con la casa.

2. In `040-problema-robot-magazzino.c` aggiungi una batteria: ogni mossa
   consuma 1 unità, si parte da 25 e la sessione termina quando la batteria
   si esaurisce.

3. In `070-problema-campo-minato.c` aggiungi le bandierine: il comando
   `0 r c` segna o toglie una bandierina (`'F'`) su una cella coperta, che
   non può più essere scoperta finché la bandierina è presente.

4. In `060-problema-gioco-della-vita.c` rendi il mondo "toroidale": una cella
   sul bordo destro ha come vicine quelle sul bordo sinistro (suggerimento:
   `(c + dc + COLONNE) % COLONNE`).

5. (Avanzato) In `080-problema-mappa-del-tesoro.c` leggi da tastiera le
   istruzioni (numero di tratti, poi direzione e passi di ciascuno) e
   verifica se portano al tesoro.
