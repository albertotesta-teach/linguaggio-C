# 04 – Matrici e funzioni

## Concetto

Una matrice passata a una funzione **non viene copiata**: la funzione lavora
sulla memoria del chiamante, quindi può leggerla e modificarla.

Nel parametro va indicato il **numero di colonne**; il numero di righe si
passa a parte:

```c
void stampa(const int m[][COLONNE], int righe);
void raddoppia(int m[][COLONNE], int righe);

stampa(m, RIGHE);      /* nella chiamata si scrive solo il nome */
```

### Perché le colonne sono obbligatorie

La matrice è memorizzata riga dopo riga. Per raggiungere `m[r][c]` la
funzione calcola la posizione `r × COLONNE + c`: senza `COLONNE` non saprebbe
dove inizia ogni riga. Per lo stesso motivo una funzione accetta solo matrici
con esattamente quel numero di colonne.

### Una riga è un array

`m[r]` è un array di `COLONNE` elementi: si può passare a qualsiasi funzione
scritta per gli array monodimensionali.

```c
somma = somma_array(m[r], COLONNE);
```

### Funzioni di riga e di colonna

| Funzione | Parametri | Scorre |
|----------|-----------|--------|
| `somma_riga(m, r)` | matrice, riga | le colonne della riga r |
| `somma_colonna(m, n, c)` | matrice, numero di righe, colonna | le righe della colonna c |

### Più risultati: parametri OUT

Per restituire valore **e** posizione di un massimo si usano i parametri per
riferimento visti nel capitolo 03:

```c
int cerca_massimo(const int m[][C], int n, int *riga_max, int *colonna_max);
massimo = cerca_massimo(m, RIGHE, &r, &c);
```

### Dimensioni diverse con una sola funzione

Se una funzione deve lavorare su matrici di dimensioni diverse (es. il
prodotto tra matrici), si dichiarano tutte `MAX × MAX` e si passano righe e
colonne effettivamente usate.

### `const` con le matrici

`const` documenta che la funzione non modifica la matrice. Con
`gcc -Wall -Wextra` non produce avvisi; con l'opzione `-Wpedantic` gcc segnala
che, prima dello standard C23, il passaggio da `int m[][C]` a
`const int m[][C]` non è formalmente ammesso.

### Le matrici non si assegnano

`b = a;` è un errore di compilazione: si copia elemento per elemento con una
funzione `copia(dest, sorg)`.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-passaggio-matrice-a-funzione.c` | Stampa e modifica tramite funzione, prime righe soltanto, una riga passata come array |
| `020-funzioni-su-matrici.c` | Somma di riga e di colonna, conteggio, massimo con posizione tramite parametri OUT |
| `030-funzioni-che-modificano-matrici.c` | Riempi, copia, scala, trasposta sul posto, rotazione di 90 gradi |
| `040-problema-prodotto-matrici.c` | Ordini × prezzi: spesa, ricavo e margine; controllo delle dimensioni |
| `040-problema-prodotto-matrici-analisi.md` | Analisi di `040-problema-prodotto-matrici.c` |
| `050-problema-gioco-del-tris.c` | Tris per due giocatori con griglia di `char` e funzioni dedicate |
| `050-problema-gioco-del-tris-analisi.md` | Analisi di `050-problema-gioco-del-tris.c` |
| `060-problema-pagella-classe.c` | Scrutinio: medie, esiti, statistiche per materia con funzioni di riga e colonna |
| `060-problema-pagella-classe-analisi.md` | Analisi di `060-problema-pagella-classe.c` |
| `070-problema-inventario-negozi.c` | Inventario di 4 negozi con scorta per prodotto e trasferimenti |
| `070-problema-inventario-negozi-analisi.md` | Analisi di `070-problema-inventario-negozi.c` |
| `080-problema-turni-lavoro.c` | Turni di 5 dipendenti in 7 giorni: contratto, riposi, copertura |
| `080-problema-turni-lavoro-analisi.md` | Analisi di `080-problema-turni-lavoro.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-passaggio-matrice-a-funzione 010-passaggio-matrice-a-funzione.c
./010-passaggio-matrice-a-funzione

gcc -Wall -Wextra -o 020-funzioni-su-matrici 020-funzioni-su-matrici.c
./020-funzioni-su-matrici

gcc -Wall -Wextra -o 030-funzioni-che-modificano-matrici 030-funzioni-che-modificano-matrici.c
./030-funzioni-che-modificano-matrici

gcc -Wall -Wextra -o 040-problema-prodotto-matrici 040-problema-prodotto-matrici.c
./040-problema-prodotto-matrici

gcc -Wall -Wextra -o 050-problema-gioco-del-tris 050-problema-gioco-del-tris.c
./050-problema-gioco-del-tris

gcc -Wall -Wextra -o 060-problema-pagella-classe 060-problema-pagella-classe.c
./060-problema-pagella-classe

gcc -Wall -Wextra -o 070-problema-inventario-negozi 070-problema-inventario-negozi.c
./070-problema-inventario-negozi

gcc -Wall -Wextra -o 080-problema-turni-lavoro 080-problema-turni-lavoro.c
./080-problema-turni-lavoro
```

---

## Output atteso

### 010-passaggio-matrice-a-funzione
```
=== Matrice originale ===
    1    2    3    4
    5    6    7    8
    9   10   11   12

=== Dopo raddoppia(m, RIGHE) ===
    2    4    6    8
   10   12   14   16
   18   20   22   24

=== Solo le prime 2 righe ===
    2    4    6    8
   10   12   14   16

=== Somma di ogni riga con somma_array(m[r], COLONNE) ===
  riga 0: 20
  riga 1: 52
  riga 2: 84
```

### 020-funzioni-su-matrici
```
=== INCASSI PER CASSA E FASCIA ORARIA (euro) ===
          8-10 10-12 12-14 14-16 16-18   Totale
  Cassa 1   420   380   610   550   720     2680
  Cassa 2   300   450   580   690   640     2660
  Cassa 3   150   220   400   380   510     1660
  Totale    870  1050  1590  1620  1870

Incasso massimo: 720 euro (cassa 1, fascia 5)
Fasce con incasso oltre 500 euro: 7 su 15
```

### 030-funzioni-che-modificano-matrici
```
a originale:
    1    2    3
    4    5    6
    7    8    9

b = copia di a, poi scala(b, 10):
   10   20   30
   40   50   60
   70   80   90

a dopo le operazioni su b (invariata):
    1    2    3
    4    5    6
    7    8    9

trasposta di a:
    1    4    7
    2    5    8
    3    6    9

a ruotata di 90 gradi in senso orario:
    7    4    1
    8    5    2
    9    6    3

riempi(b, 0):
    0    0    0
    0    0    0
    0    0    0
```

### 040-problema-prodotto-matrici
```
=== ORDINI (negozi x articoli) ===
    10.00     5.00    20.00     0.00
     4.00    12.00     6.00     8.00
     0.00     3.00    15.00    10.00

=== PREZZI (articoli x listini: ingrosso, pubblico) ===
    12.50    19.90
     8.00    14.50
     3.20     5.90
    22.00    34.00

=== COSTI = ORDINI x PREZZI (negozi x listini) ===
   229.00   389.50
   341.20   561.00
   292.00   472.00

  Negozio   Spesa   Ricavo   Margine
        1  229.00   389.50    160.50
        2  341.20   561.00    219.80
        3  292.00   472.00    180.00

Prova: prezzi (4 x 2) x ordini (3 x 4)
  Dimensioni incompatibili: le colonne del primo (2) devono
  essere quante le righe del secondo (3).
```

### 050-problema-gioco-del-tris
*(output dipendente dall'input – esempio di partita con una mossa non valida)*
```
=== TRIS ===

     1   2   3
  1    |   |   
    ---+---+---
  2    |   |   
    ---+---+---
  3    |   |   

Giocatore X, riga e colonna (1-3): 2 2

     1   2   3
  1    |   |   
    ---+---+---
  2    | X |   
    ---+---+---
  3    |   |   

Giocatore O, riga e colonna (1-3): 1 1

     1   2   3
  1  O |   |   
    ---+---+---
  2    | X |   
    ---+---+---
  3    |   |   

Giocatore X, riga e colonna (1-3): 1 3

     1   2   3
  1  O |   | X 
    ---+---+---
  2    | X |   
    ---+---+---
  3    |   |   

Giocatore O, riga e colonna (1-3): 2 2
Mossa non valida: casella inesistente o occupata.
Giocatore O, riga e colonna (1-3): 3 3

     1   2   3
  1  O |   | X 
    ---+---+---
  2    | X |   
    ---+---+---
  3    |   | O 

Giocatore X, riga e colonna (1-3): 3 1

     1   2   3
  1  O |   | X 
    ---+---+---
  2    | X |   
    ---+---+---
  3  X |   | O 

Vince il giocatore X!
```

### 060-problema-pagella-classe
```
=== SCRUTINIO FINALE - CLASSE 4B ===

  Studente         Ita Mat Ing Inf Sis   Media  Esito
  Bianchi Sara       7   6   8   7   8    7.20  AMMESSO
  Colombo Luca       5   4   6   6   7    5.60  SOSPENSIONE (2)
  Esposito Ilaria    8   9   8   9   9    8.60  AMMESSO
  Ferri Matteo       5   4   5   6   6    5.20  NON AMMESSO
  Galli Chiara       6   6   7   5   7    6.20  SOSPENSIONE (1)
  Marini Davide      4   5   5   6   4    4.80  NON AMMESSO

  Materia         Media  Insufficienze
  Italiano         5.83              3
  Matematica       5.67              3
  Inglese          6.50              2
  Informatica      6.50              1
  Sistemi          6.83              1

Media piu' alta: Esposito Ilaria (8.60)
```

### 070-problema-inventario-negozi
```
=== INVENTARIO INIZIALE ===
  Negozio         Palloni  Racchette   Borracce      Zaini      Calze
  Alessandria          12          3         25          8         40
  Novi                  2         15         30         12         35
  Tortona               9          6          4         10         18
  Acqui                20          1         18          3         50
  Totale               43         25         77         33        143

=== RIASSORTIMENTO ===
Alessandria: Racchette sotto scorta (3, minimo 4). Trasferiti 1 da Novi.
Novi: Palloni sotto scorta (2, minimo 5). Trasferiti 3 da Acqui.
Tortona: Borracce sotto scorta (4, minimo 8). Trasferiti 4 da Novi.
Acqui: Racchette sotto scorta (1, minimo 4). Trasferiti 3 da Novi.
Acqui: Zaini sotto scorta (3, minimo 5). Trasferiti 2 da Novi.

=== INVENTARIO AGGIORNATO ===
  Negozio         Palloni  Racchette   Borracce      Zaini      Calze
  Alessandria          12          4         25          8         40
  Novi                  5         11         26         10         35
  Tortona               9          6          8         10         18
  Acqui                17          4         18          5         50
  Totale               43         25         77         33        143
```

### 080-problema-turni-lavoro
```
=== TURNI DELLA SETTIMANA (ore) ===

            Lun  Mar  Mer  Gio  Ven  Sab  Dom  Totale Contratto
  Marco       8    8    -    8    8    8    -      40        40
  Giulia      6    6    6    6    -    6    6      36        36
  Ahmed       -    4    4    4    -    8    8      28        30
  Sofia       8    8    8    8    8    4    4      48        40
  Luca        4    4    4    -    -    4    -      16        20

--- Verifica per dipendente ---
  Marco   ore in linea con il contratto, 2 giorni di riposo
  Giulia  ore in linea con il contratto, 1 giorno di riposo
  Ahmed   mancano 2 ore, 2 giorni di riposo
  Sofia   8 ore di straordinario, 0 giorni di riposo  <- NESSUN RIPOSO
  Luca    mancano 4 ore, 3 giorni di riposo

--- Copertura giornaliera (minimo 3 persone) ---
  Lun: 4 persone, 26 ore
  Mar: 5 persone, 30 ore
  Mer: 4 persone, 22 ore
  Gio: 4 persone, 26 ore
  Ven: 2 persone, 16 ore  <- SCOPERTO
  Sab: 5 persone, 30 ore
  Dom: 3 persone, 18 ore
```

---

## Errori comuni da evitare

**Colonne omesse nel parametro**
```c
void stampa(int m[][], int righe);       /* ERRORE di compilazione */
void stampa(int m[][COLONNE], int righe); /* corretto */
```

**Matrice con un numero di colonne diverso**
```c
int altra[3][5];
stampa(altra, 3);    /* stampa vuole COLONNE colonne: tipo incompatibile */
```

**Parentesi quadre nella chiamata**
```c
stampa(m[][], RIGHE);   /* ERRORE di sintassi */
stampa(m, RIGHE);       /* corretto */
```

**Assegnazione tra matrici**
```c
b = a;                  /* ERRORE: si usa una funzione copia() */
```

**Rotazione o trasposta scritte sulla stessa matrice**
```c
/* ruotare scrivendo nella sorgente sovrascrive valori non ancora copiati:
   serve una matrice di destinazione diversa */
ruota_destra(a, a);
```

---

## Concetti collegati

- `01-array-monodimensionali/04-array-e-funzioni` → passaggio di array a funzione
- `03-funzioni/03-passaggio-per-riferimento` → parametri OUT
- `03-operazioni-su-matrici` → gli stessi calcoli scritti nel main
- `05-griglie-di-caratteri` → funzioni su griglie di gioco
- `05-puntatori/02-puntatori-e-array` → che cosa riceve davvero la funzione

---

## Esercizi proposti

1. Scrivi `int e_simmetrica(const int m[][N])` che restituisce 1 se la matrice
   quadrata è simmetrica, con una sola `return`.

2. Aggiungi a `030-funzioni-che-modificano-matrici.c` la funzione
   `ruota_sinistra(dest, sorg)` e verifica che ruotare a destra e poi a
   sinistra restituisca la matrice originale.

3. In `050-problema-gioco-del-tris.c` aggiungi il conteggio delle mosse e,
   alla fine, stampa in quante mosse è terminata la partita.

4. In `060-problema-pagella-classe.c` scrivi la funzione
   `int materia_peggiore(const int voti[][MATERIE], int n)` che restituisce
   l'indice della materia con la media più bassa.

5. (Avanzato) In `040-problema-prodotto-matrici.c` aggiungi un terzo listino
   (prezzo scontato) e calcola il prodotto senza modificare la funzione
   `moltiplica`.
