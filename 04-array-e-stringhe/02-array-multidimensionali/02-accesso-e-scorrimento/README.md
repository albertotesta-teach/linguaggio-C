# 02 – Accesso e scorrimento di array multidimensionali

## Concetto

Un elemento di una matrice si legge o si scrive indicando **riga e colonna**:

```c
valore = m[riga][colonna];     /* lettura */
m[riga][colonna] = valore;     /* scrittura */
```

Gli indici possono essere costanti, variabili o espressioni. Il C **non
controlla** che siano validi: prima di usare indici calcolati o letti da
tastiera vanno verificati **entrambi**:

```c
if (riga >= 0 && riga < RIGHE && colonna >= 0 && colonna < COLONNE) {
    ... m[riga][colonna] ...
}
```

### Celle vicine

```
                [r-1][c]
   [r][c-1]      [r][c]      [r][c+1]
                [r+1][c]
```

Sulle celle di bordo alcune vicine non esistono: si controllano gli indici.

### Scorrimento con cicli annidati

| Ordine | Ciclo esterno | Ciclo interno | Visita |
|--------|---------------|---------------|--------|
| per righe | righe | colonne | 1 2 3 4 / 5 6 7 8 / ... |
| per colonne | colonne | righe | 1 5 9 / 2 6 10 / ... |
| una riga | — (riga fissa) | colonne | solo la riga scelta |
| una colonna | — (colonna fissa) | righe | solo la colonna scelta |

Qualunque sia l'ordine dei cicli, l'accesso resta **`m[riga][colonna]`**.

```c
for (riga = 0; riga < RIGHE; riga++) {
    for (colonna = 0; colonna < COLONNE; colonna++) {
        printf("%4d", m[riga][colonna]);
    }
    printf("\n");          /* fine della riga */
}
```

### Lettura da tastiera

`scanf` riceve l'indirizzo della singola cella: `&m[riga][colonna]`.

### Da numero dell'utente a indice

L'utente conta da 1 (o usa lettere), la matrice da 0:

| Dato dell'utente | Indice |
|------------------|--------|
| posto 4 | `4 - 1 = 3` |
| fila `'C'` | `'C' - 'A' = 2` |

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-accesso-per-indici.c` | Lettura e scrittura di celle, celle vicine, accesso sicuro con controllo dei limiti |
| `020-scorrimento-righe-e-colonne.c` | Per righe, per colonne, all'indietro, una riga, una colonna, a serpente |
| `030-lettura-da-tastiera.c` | Punteggi di una giuria letti con validazione, totali per colonna |
| `040-problema-prenotazione-teatro.c` | Prenotazione con fila (lettera) e posto, proposta del primo posto libero |
| `040-problema-prenotazione-teatro-analisi.md` | Analisi di `040-problema-prenotazione-teatro.c` |
| `050-problema-parcheggio-multipiano.c` | Tessere su 3 piani × 6 posti: ingresso, uscita, stato |
| `050-problema-parcheggio-multipiano-analisi.md` | Analisi di `050-problema-parcheggio-multipiano.c` |
| `060-problema-registro-presenze.c` | Matrice di `char` P/A/R con nomi e giorni: riepiloghi e dettaglio |
| `060-problema-registro-presenze-analisi.md` | Analisi di `060-problema-registro-presenze.c` |
| `070-problema-stazioni-meteo.c` | Pioggia di 4 stazioni × 6 intervalli: totali, picchi, consultazione |
| `070-problema-stazioni-meteo-analisi.md` | Analisi di `070-problema-stazioni-meteo.c` |
| `080-problema-magazzino-scaffali.c` | Giacenze con soglia per scaffale, ripiani da rifornire, prelievi validati |
| `080-problema-magazzino-scaffali-analisi.md` | Analisi di `080-problema-magazzino-scaffali.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-accesso-per-indici 010-accesso-per-indici.c
./010-accesso-per-indici

gcc -Wall -Wextra -o 020-scorrimento-righe-e-colonne 020-scorrimento-righe-e-colonne.c
./020-scorrimento-righe-e-colonne

gcc -Wall -Wextra -o 030-lettura-da-tastiera 030-lettura-da-tastiera.c
./030-lettura-da-tastiera

gcc -Wall -Wextra -o 040-problema-prenotazione-teatro 040-problema-prenotazione-teatro.c
./040-problema-prenotazione-teatro

gcc -Wall -Wextra -o 050-problema-parcheggio-multipiano 050-problema-parcheggio-multipiano.c
./050-problema-parcheggio-multipiano

gcc -Wall -Wextra -o 060-problema-registro-presenze 060-problema-registro-presenze.c
./060-problema-registro-presenze

gcc -Wall -Wextra -o 070-problema-stazioni-meteo 070-problema-stazioni-meteo.c
./070-problema-stazioni-meteo

gcc -Wall -Wextra -o 080-problema-magazzino-scaffali 080-problema-magazzino-scaffali.c
./080-problema-magazzino-scaffali
```

---

## Output atteso

### 010-accesso-per-indici
```
=== Mappa delle altitudini (metri) ===
  120  135  150  140  130
  125  160  180  170  145
  130  170  210  190  150
  110  140  160  150  125

=== Accesso diretto ===
quote[0][0] = 120 (angolo in alto a sinistra)
quote[3][4] = 125 (angolo in basso a destra)
quote[riga][colonna] con riga = 2, colonna = 2: 210

=== Scrittura ===
Prima:  quote[1][3] = 170
Dopo +5: quote[1][3] = 175

=== Vicine della cella [2][2] (quota 210) ===
  sopra    [1][2] = 180
  sotto    [3][2] = 160
  sinistra [2][1] = 170
  destra   [2][3] = 190

=== Vicine della cella [0][4] con controllo dei limiti ===
  sopra    : fuori dalla mappa
  sotto    = 145
  sinistra = 140
  destra   : fuori dalla mappa
```

### 020-scorrimento-righe-e-colonne
```
Per righe:            1  2  3  4  5  6  7  8  9 10 11 12
Per colonne:          1  5  9  2  6 10  3  7 11  4  8 12
All'indietro:        12 11 10  9  8  7  6  5  4  3  2  1
Solo la riga 1:       5  6  7  8
Solo la colonna 2:    3  7 11
A serpente:           1  2  3  4  8  7  6  5  9 10 11 12

Come tabella:
   1   2   3   4
   5   6   7   8
   9  10  11  12
```

### 030-lettura-da-tastiera
*(output dipendente dall'input – esempio con un valore non valido)*
```
=== GARA DI CUCINA - INSERIMENTO PUNTEGGI ===

Giudice 1
  Punteggio al concorrente 1 (0-10): 7
  Punteggio al concorrente 2 (0-10): 8
  Punteggio al concorrente 3 (0-10): 6
  Punteggio al concorrente 4 (0-10): 9

Giudice 2
  Punteggio al concorrente 1 (0-10): 6
  Punteggio al concorrente 2 (0-10): 11
  Valore non valido.
  Punteggio al concorrente 2 (0-10): 7
  Punteggio al concorrente 3 (0-10): 8
  Punteggio al concorrente 4 (0-10): 5

Giudice 3
  Punteggio al concorrente 1 (0-10): 9
  Punteggio al concorrente 2 (0-10): 8
  Punteggio al concorrente 3 (0-10): 7
  Punteggio al concorrente 4 (0-10): 8

=== TABELLA DEI PUNTEGGI ===
                Conc.1  Conc.2  Conc.3  Conc.4
  Giudice 1          7       8       6       9
  Giudice 2          6       7       8       5
  Giudice 3          9       8       7       8
  Totale            22      23      21      22
```

### 040-problema-prenotazione-teatro
*(output dipendente dall'input – esempio di sessione)*
```
=== TEATRO COMUNALE - BIGLIETTERIA ===
File A-E, posti 1-8. Fila Z per terminare.

Fila e posto (es. C 4): C 4
  Prenotato: fila C, posto 4.
Fila e posto (es. C 4): C 2
  Occupato. Primo posto libero nella fila C: 1
Fila e posto (es. C 4): A 9
  Posto inesistente.
Fila e posto (es. C 4): B 3
  Occupato. La fila B e' completa.
Fila e posto (es. C 4): E 1
  Prenotato: fila E, posto 1.
Fila e posto (es. C 4): Z

=== MAPPA AGGIORNATA ===
        PALCO
      1 2 3 4 5 6 7 8
  A   X X . . X X . .
  B   X X X X X X X X
  C   . X X X . X X .
  D   . . . X X . . .
  E   X . . . . . . .

Posti prenotati in questa sessione: 2
```

### 050-problema-parcheggio-multipiano
*(output dipendente dall'input – esempio di sessione)*
```
=== PARCHEGGIO CENTRO - CASSA AUTOMATICA ===

1 - Ingresso   2 - Uscita   3 - Stato   0 - Fine
Scelta: 1
Numero tessera: 1500
Tessera 1500: piano 0, posto 3.

1 - Ingresso   2 - Uscita   3 - Stato   0 - Fine
Scelta: 2
Numero tessera: 1302
Uscita registrata: liberato piano 1, posto 3.

1 - Ingresso   2 - Uscita   3 - Stato   0 - Fine
Scelta: 2
Numero tessera: 999
Tessera 999 non presente nel parcheggio.

1 - Ingresso   2 - Uscita   3 - Stato   0 - Fine
Scelta: 3
  Piano 2 |  ----  ----  ----  ----  ----  ---- | liberi: 6
  Piano 1 |  1300  ----  ----  ----  ----  1310 | liberi: 4
  Piano 0 |  1201  1202  1500  1210  1215  1220 | liberi: 0

1 - Ingresso   2 - Uscita   3 - Stato   0 - Fine
Scelta: 0
Chiusura cassa.
```

### 060-problema-registro-presenze
*(output dipendente dall'input – esempio con lo studente 3)*
```
=== REGISTRO PRESENZE - SETTIMANA 12 ===

  Studente          Lun  Mar  Mer  Gio  Ven   Pres. Ass. Rit.
  Amato Elena         P    P    P    P    P       5    0    0
  Bruno Paolo         P    A    P    R    P       4    1    1
  Costa Marta         A    A    P    P    R       3    2    1  <- oltre il limite
  De Luca Ivan        P    P    R    R    P       5    0    2
  Fontana Rita        P    P    P    A    P       4    1    0
  Greco Omar          A    P    A    P    A       2    3    0  <- oltre il limite

  Presenti            4    4    5    5    5

Studenti:
  1 - Amato Elena
  2 - Bruno Paolo
  3 - Costa Marta
  4 - De Luca Ivan
  5 - Fontana Rita
  6 - Greco Omar
Numero dello studente (1-6): 3

Presenze di Costa Marta:
  Lun: assente
  Mar: assente
  Mer: presente
  Gio: presente
  Ven: presente (ritardo)
```

### 070-problema-stazioni-meteo
*(output dipendente dall'input – esempio con due consultazioni)*
```
=== PIOGGIA DEL 14 OTTOBRE (mm) ===

  Stazione       00-04  04-08  08-12  12-16  16-20  20-24  Totale  Picco
  Alessandria      0.0    1.2    4.8    6.5    2.0    0.4    14.9  12-16
  Acqui Terme      0.2    0.8    3.5    9.1    3.3    1.0    17.9  12-16
  Casale           0.0    0.3    2.9    2.1    0.9    0.0     6.2  08-12
  Ovada            1.1    2.4    7.2   12.6    5.8    2.2    31.3  12-16

Intervallo piu' piovoso sulla rete: 12-16 (media 7.57 mm)

Consultazione (stazione 0 per terminare)
Stazione (1-4): 4
Intervallo (1-6): 4
  Ovada, 12-16: 12.6 mm
Stazione (1-4): 2
Intervallo (1-6): 9
  Stazione o intervallo inesistente.
Stazione (1-4): 0
```

### 080-problema-magazzino-scaffali
*(output dipendente dall'input – esempio con tre prelievi)*
```
=== MAGAZZINO RICAMBI ===

  Scaffale  Rip.1 Rip.2 Rip.3 Rip.4 Rip.5  Totale  Scorta min.
  SC-A        40    12    35     8    50     145           10
  SC-B        15    22     4    30    18      89           10
  SC-C        60    55    70     9    65     259           20
  SC-D         5    10    14    20     3      52            6

--- Ripiani sotto la scorta minima ---
  SC-A ripiano 4: 8 pezzi (minimo 10)
  SC-B ripiano 3: 4 pezzi (minimo 10)
  SC-C ripiano 4: 9 pezzi (minimo 20)
  SC-D ripiano 1: 5 pezzi (minimo 6)
  SC-D ripiano 5: 3 pezzi (minimo 6)
  Totale ripiani da rifornire: 5

Registrazione prelievi (scaffale 0 per terminare)
Scaffale (1-4): 2
Ripiano (1-5): 1
Pezzi da prelevare: 10
  Prelievo registrato: SC-B ripiano 1, rimasti 5 (sotto scorta!)
Scaffale (1-4): 3
Ripiano (1-5): 4
Pezzi da prelevare: 20
  Giacenza insufficiente: disponibili 9.
Scaffale (1-4): 4
Ripiano (1-5): 5
Pezzi da prelevare: 3
  Prelievo registrato: SC-D ripiano 5, rimasti 0 (sotto scorta!)
Scaffale (1-4): 0

Pezzi prelevati in totale: 13
```

---

## Errori comuni da evitare

**Indici invertiti quando si invertono i cicli**
```c
for (colonna = 0; colonna < COLONNE; colonna++) {
    for (riga = 0; riga < RIGHE; riga++) {
        printf("%d", m[colonna][riga]);   /* ERRATO: sempre m[riga][colonna] */
    }
}
```

**Controllo di un solo indice**
```c
if (r < RIGHE) {
    m[r][c] = 0;     /* c può essere fuori dai limiti, o negativo */
}
```

**Indice negativo che "funziona"**
```c
m[1][-1]     /* non dà errore: legge l'ultima cella della riga 0,
                perché le righe sono contigue in memoria */
```

**A capo nel posto sbagliato**
```c
for (riga = 0; riga < RIGHE; riga++) {
    for (colonna = 0; colonna < COLONNE; colonna++) {
        printf("%4d\n", m[riga][colonna]);   /* un valore per riga */
    }
}
```

**`&` dimenticata in scanf**
```c
scanf("%d", m[i][j]);     /* ERRATO */
scanf("%d", &m[i][j]);    /* corretto */
```

---

## Concetti collegati

- `01-dichiarazione-e-inizializzazione` → dichiarazione e disposizione in memoria
- `03-operazioni-su-matrici` → somme, estremi e trasformazioni costruite su questi scorrimenti
- `02-controllo-del-flusso/05-for` → cicli annidati
- `05-griglie-di-caratteri` → celle vicine usate nei giochi su griglia

---

## Esercizi proposti

1. Scrivi un programma che stampi una matrice 5 × 5 per diagonali: prima
   l'elemento [0][0], poi [0][1] e [1][0], poi [0][2], [1][1], [2][0], ...

2. Modifica `040-problema-prenotazione-teatro.c` perché accetti anche le
   file in minuscolo.

3. In `050-problema-parcheggio-multipiano.c` aggiungi la ricerca di una
   tessera senza farla uscire (stampa solo piano e posto).

4. Estendi `060-problema-registro-presenze.c` indicando, per ogni studente,
   la sequenza più lunga di giorni consecutivi di presenza.

5. (Avanzato) In `080-problema-magazzino-scaffali.c` aggiungi l'operazione
   di rifornimento: tutti i ripiani sotto scorta vengono riportati al doppio
   della scorta minima, e il programma stampa quanti pezzi sono stati ordinati.
