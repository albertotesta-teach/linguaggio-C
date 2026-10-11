# 01 – Dichiarazione e inizializzazione di array multidimensionali

## Concetto

Un **array bidimensionale** (matrice) è una tabella di elementi dello stesso
tipo, organizzati in **righe** e **colonne**. Si dichiara con due dimensioni:

```c
#define RIGHE   3
#define COLONNE 4

int m[RIGHE][COLONNE];
```

Ogni elemento si individua con due indici, **prima la riga e poi la colonna**,
entrambi a partire da 0:

```
               colonna 0  colonna 1  colonna 2  colonna 3
   riga 0    [  m[0][0]    m[0][1]    m[0][2]    m[0][3]  ]
   riga 1    [  m[1][0]    m[1][1]    m[1][2]    m[1][3]  ]
   riga 2    [  m[2][0]    m[2][1]    m[2][2]    m[2][3]  ]
```

### Inizializzazione

Si usano **graffe annidate**, una coppia per riga:

```c
int m[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
int parziale[3][4] = { {7}, {1, 2} };   /* il resto vale 0 */
int zeri[3][4] = {0};                    /* tutta a zero */
int dedotta[][4] = { {1, 2, 3, 4}, {5, 6, 7, 8} };   /* 2 righe dedotte */
```

La prima dimensione (righe) si può omettere se la matrice è inizializzata;
la seconda (colonne) **va sempre indicata**.

### Disposizione in memoria

La memoria è lineare: il C memorizza la matrice **riga dopo riga**
(*row-major*). L'elemento `[r][c]` è in posizione `r * COLONNE + c`:

```
  int m[2][3] = {{1, 2, 3}, {4, 5, 6}};

  memoria:  | 1 | 2 | 3 | 4 | 5 | 6 |
              riga 0      riga 1
```

Una matrice è un **array di array**: `m[0]` è la riga 0, cioè un array di
`COLONNE` elementi.

### L'elenco di nomi è una matrice di caratteri

Gli esempi degli array monodimensionali usavano elenchi come
`char nomi[GIOCATORI][20]` paralleli agli array di dati. È una matrice di
`char`: `nomi[i]` è la riga *i* (una parola), `nomi[i][j]` è un singolo
carattere. Le stringhe vengono trattate nella sezione `03-stringhe`.

### Array paralleli a righe e colonne

Con le matrici un array parallelo può descrivere le **righe**
(`studenti[s]` per la riga *s*) oppure le **colonne** (`materie[m]` per la
colonna *m*).

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-dichiarazione-base.c` | Dichiarazione con `#define`, riempimento con cicli annidati, stampa in tabella, accesso a singoli elementi |
| `020-inizializzazione.c` | Graffe annidate, inizializzazione parziale, `{0}`, numero di righe dedotto |
| `030-matrice-in-memoria.c` | `sizeof` di matrice, riga ed elemento; ordine in memoria; `char nomi[N][LEN]` come matrice di caratteri |
| `040-problema-orario-scolastico.c` | Orario 5 giorni × 6 ore con codici materia: stampa, ore per materia, giorno con più Informatica |
| `040-problema-orario-scolastico-analisi.md` | Analisi di `040-problema-orario-scolastico.c` |
| `050-problema-posti-cinema.c` | Mappa di una sala 6 × 10: posti liberi per fila, riempimento, 4 posti vicini |
| `050-problema-posti-cinema-analisi.md` | Analisi di `050-problema-posti-cinema.c` |
| `060-problema-temperature-settimana.c` | Temperature 7 giorni × 4 fasce con nomi di giorni e fasce: medie ed estremi |
| `060-problema-temperature-settimana-analisi.md` | Analisi di `060-problema-temperature-settimana.c` |
| `070-problema-voti-classe.c` | Tabellone 6 studenti × 4 materie con nomi: medie, debiti, insufficienze per materia |
| `070-problema-voti-classe-analisi.md` | Analisi di `070-problema-voti-classe.c` |
| `080-problema-vendite-trimestrali.c` | Vendite 5 prodotti × 3 mesi con codici e prezzi: totali, fatturato, prodotti in crescita |
| `080-problema-vendite-trimestrali-analisi.md` | Analisi di `080-problema-vendite-trimestrali.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-dichiarazione-base 010-dichiarazione-base.c
./010-dichiarazione-base

gcc -Wall -Wextra -o 020-inizializzazione 020-inizializzazione.c
./020-inizializzazione

gcc -Wall -Wextra -o 030-matrice-in-memoria 030-matrice-in-memoria.c
./030-matrice-in-memoria

gcc -Wall -Wextra -o 040-problema-orario-scolastico 040-problema-orario-scolastico.c
./040-problema-orario-scolastico

gcc -Wall -Wextra -o 050-problema-posti-cinema 050-problema-posti-cinema.c
./050-problema-posti-cinema

gcc -Wall -Wextra -o 060-problema-temperature-settimana 060-problema-temperature-settimana.c
./060-problema-temperature-settimana

gcc -Wall -Wextra -o 070-problema-voti-classe 070-problema-voti-classe.c
./070-problema-voti-classe

gcc -Wall -Wextra -o 080-problema-vendite-trimestrali 080-problema-vendite-trimestrali.c
./080-problema-vendite-trimestrali
```

---

## Output atteso

Nessun programma richiede input: l'output è sempre lo stesso.

### 010-dichiarazione-base
```
=== Matrice 3 x 4 ===
           col 0 col 1 col 2 col 3
  riga 0       0     1     2     3
  riga 1      10    11    12    13
  riga 2      20    21    22    23

=== Singoli elementi ===
m[0][0] = 0   (primo elemento)
m[1][2] = 12   (riga 1, colonna 2)
m[2][3] = 23   (ultimo elemento)
Dopo m[1][2] = 99: m[1][2] = 99

=== Dimensioni ===
Righe: 3, colonne: 4, elementi: 12
Indici di riga validi:    da 0 a 2
Indici di colonna validi: da 0 a 3
```

### 020-inizializzazione
```
=== 1. Completa ===
   1   2   3   4
   5   6   7   8
   9  10  11  12

=== 2. Parziale: {7}, {1, 2} ===
   7   0   0   0
   1   2   0   0
   0   0   0   0

=== 3. Tutta a zero: {0} ===
   0   0   0   0
   0   0   0   0
   0   0   0   0

=== 4. Righe dedotte dal compilatore: 2 ===
  10  20  30  40
  50  60  70  80
```

### 030-matrice-in-memoria
```
=== Dimensioni in byte ===
sizeof(m)       = 24 byte (tutta la matrice)
sizeof(m[0])    = 12 byte (una riga di 3 interi)
sizeof(m[0][0]) =  4 byte (un elemento)
Righe   = sizeof(m) / sizeof(m[0])       = 2
Colonne = sizeof(m[0]) / sizeof(m[0][0]) = 3

=== Ordine in memoria (riga per riga) ===
  Posizione | Elemento | Valore
  ----------|----------|-------
          0 | m[0][0]  |     1
          1 | m[0][1]  |     2
          2 | m[0][2]  |     3
          3 | m[1][0]  |     4
          4 | m[1][1]  |     5
          5 | m[1][2]  |     6

=== Matrice di caratteri char nomi[3][8] ===
  nomi[0] = Anna     caratteri: A n n a
  nomi[1] = Luca     caratteri: L u c a
  nomi[2] = Giulia   caratteri: G i u l i a
  nomi[2][0] = 'G'  (prima lettera della riga 2)
```

### 040-problema-orario-scolastico
```
=== ORARIO SETTIMANALE 3A INFORMATICA ===

          1a    2a    3a    4a    5a    6a
  Lun     ITA   ITA   MAT   INF   INF   STO 
  Mar     MAT   ING   SIS   SIS   ITA   MOT 
  Mer     INF   INF   INF   MAT   STO   ING 
  Gio     ITA   MAT   MAT   SIS   ING   MOT 
  Ven     SIS   INF   INF   ITA   MAT   STO 

--- Ore settimanali per materia ---
  Italiano        : 5 ore
  Matematica      : 6 ore
  Inglese         : 3 ore
  Informatica     : 7 ore
  Sistemi         : 4 ore
  Storia          : 3 ore
  Scienze motorie : 2 ore
  Totale          : 30 ore (5 giorni x 6 ore)

Giorno con piu' ore di Informatica: mercoledi' (3 ore)
```

### 050-problema-posti-cinema
```
=== SALA 2 - SPETTACOLO DELLE 21:00 ===

              SCHERMO
      1  2  3  4  5  6  7  8  9 10   liberi
  A   X  X  X  O  O  X  X  X  X  O     3
  B   X  X  X  X  X  X  X  O  X  X     1
  C   O  X  X  O  O  O  O  X  X  O     6
  D   O  O  X  X  O  X  O  O  X  O     6
  E   O  O  O  X  X  O  O  O  O  O     8
  F   O  O  O  O  O  O  O  O  O  O    10

Posti liberi : 34 su 60
Riempimento  : 43.3%
Fila piu' libera: F (10 posti)

4 posti vicini disponibili: fila C, posti da 4 a 7
```

### 060-problema-temperature-settimana
```
=== TEMPERATURE DELLA SETTIMANA (gradi C) ===

  Giorno           Notte    Mattina Pomeriggio       Sera    Media
  Lunedi'            8.5       13.0       17.5       12.0     12.8
  Martedi'           9.0       14.5       18.0       13.5     13.8
  Mercoledi'        10.5       15.0       19.5       14.0     14.8
  Giovedi'           7.0       11.5       15.0       10.5     11.0
  Venerdi'           6.5       10.0       13.5        9.0      9.8
  Sabato             8.0       14.0       20.5       15.5     14.5
  Domenica          11.0       16.5       21.0       16.0     16.1

Temperatura massima: 21.0 (Domenica, Pomeriggio)
Temperatura minima : 6.5 (Venerdi', Notte)

--- Media della settimana per fascia ---
  Notte      :   8.6
  Mattina    :  13.5
  Pomeriggio :  17.9
  Sera       :  12.9
```

### 070-problema-voti-classe
```
=== TABELLONE VOTI - CLASSE 3A ===

  Studente            Italiano  Matematica     Inglese Informatica   Media  Insuff.
  Bianchi Sara               7           6           8           9    7.50      0
  Colombo Luca               5           4           6           7    5.50      2   <- debito
  Esposito Ilaria            8           9           7           8    8.00      0
  Ferri Matteo               6           5           5           6    5.50      2   <- debito
  Galli Chiara               9           8           9          10    9.00      0
  Marini Davide              6           6           4           7    5.75      1   <- debito

Studenti con almeno un'insufficienza: 3 su 6

--- Insufficienze per materia ---
  Italiano    : 1
  Matematica  : 2
  Inglese     : 2
  Informatica : 0
```

### 080-problema-vendite-trimestrali
```
=== VENDITE PRIMO TRIMESTRE ===

  Codice |  Gen |  Feb |  Mar | Pezzi |   Prezzo | Fatturato
  -------|------|------|------|-------|----------|----------
    1101 |   42 |   38 |   51 |   131 |    19.90 |   2606.90
    1102 |   15 |   18 |   22 |    55 |   149.00 |   8195.00
    2201 |   60 |   55 |   48 |   163 |     9.50 |   1548.50
    3301 |    8 |   12 |   15 |    35 |   599.00 |  20965.00
    3302 |   25 |   25 |   30 |    80 |    79.90 |   6392.00
  -------|------|------|------|
  Totale |  150 |  148 |  166 |

Fatturato del trimestre: 39707.40 euro
Prodotto con il fatturato piu' alto: 3301 (20965.00 euro)

--- Prodotti con vendite in crescita ogni mese ---
  1102: 15 -> 18 -> 22
  3301: 8 -> 12 -> 15
```

---

## Errori comuni da evitare

**Indici separati da virgola**
```c
m[1, 2] = 5;     /* ERRATO: la virgola è un operatore, equivale a m[2] */
m[1][2] = 5;     /* corretto */
```

**Righe e colonne scambiate**
```c
int m[3][5];
m[4][1] = 0;     /* ERRATO: le righe vanno da 0 a 2 */
```

**Numero di colonne omesso**
```c
int m[][] = { {1, 2}, {3, 4} };   /* ERRORE di compilazione */
int m[][2] = { {1, 2}, {3, 4} };  /* corretto */
```

**Lista senza graffe interne**
```c
int m[2][3] = {1, 2, 3, 4, 5, 6};          /* compila, ma -Wextra segnala
                                              "missing braces" */
int m[2][3] = { {1, 2, 3}, {4, 5, 6} };    /* corretto e leggibile */
```

**Matrice non inizializzata letta come se fosse a zero**
```c
int conteggi[4][4];       /* valori casuali */
conteggi[0][0]++;         /* risultato imprevedibile */
int conteggi[4][4] = {0}; /* corretto */
```

---

## Concetti collegati

- `01-array-monodimensionali/01-dichiarazione-e-inizializzazione` → stesse regole su una sola dimensione
- `02-accesso-e-scorrimento` → cicli annidati per righe e per colonne, lettura da tastiera
- `03-stringhe` → l'elenco di nomi `char nomi[N][LEN]` come array di stringhe
- `05-puntatori/02-puntatori-e-array` → perché una matrice è un array di array

---

## Esercizi proposti

1. Dichiara e inizializza la tavola pitagorica 10 × 10 calcolando i valori
   con due cicli annidati, poi stampa solo la diagonale principale.

2. Modifica `050-problema-posti-cinema.c` per indicare, per ogni fila, il
   numero del primo posto libero (oppure "completa").

3. Aggiungi a `060-problema-temperature-settimana.c` l'escursione termica di
   ogni giorno (massimo meno minimo della riga) e il giorno con l'escursione
   maggiore.

4. In `070-problema-voti-classe.c` aggiungi la media di ogni materia e
   la materia con la media più bassa.

5. (Avanzato) In `080-problema-vendite-trimestrali.c` aggiungi un quarto mese
   e rendi la stampa del controllo di crescita indipendente dal numero di mesi
   (oggi stampa esplicitamente le tre colonne).
