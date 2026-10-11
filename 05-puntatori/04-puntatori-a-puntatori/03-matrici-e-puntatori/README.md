# 03 – Matrici e puntatori

## Concetto

Una matrice `int m[R][C]` è un array di `R` righe, ognuna un array di `C`
`int`. In memoria le righe sono **consecutive**: tutta la riga 0, poi tutta
la riga 1, e così via.

| Espressione | Significato |
|-------------|-------------|
| `m[i]` | la riga `i`, un array di `C` int (indirizzo `&m[i][0]`) |
| `m + i` | indirizzo della riga `i`: avanza di una riga intera |
| `*(*(m + i) + j)` | l'elemento `m[i][j]` |
| `&m[0][0] + i * C + j` | lo stesso elemento contato dall'inizio |

### Tre modi di scorrere una matrice

**Puntatore a riga**: il nome della matrice diventa un puntatore a un array
di `C` int.

```c
int (*riga)[MESI];

for (riga = vendite; riga < vendite + NEGOZI; riga++) {
    totale = totale_riga(riga);      /* (*riga)[j] è l'elemento j */
}
```

`int (*riga)[C]` è un puntatore a una riga; `int *riga[C]` è un array di
puntatori: le parentesi cambiano tutto.

**Una riga alla volta come array**: `m[i]` si passa a una funzione che
riceve un `int *`.

```c
stampa_giorno(orario[g], ORE, materie);
media(serra[f], SETTORI);
```

**Blocco unico**: quando la riga non conta, tutta la matrice si scorre come
un array di `R * C` elementi.

```c
const int *p;

for (p = &m[0][0]; p < &m[0][0] + R * C; p++) { ... }
/* posizione k = p - &m[0][0]:  riga k / C, colonna k % C */
```

### Righe di lunghezza diversa

Quando le righe hanno lunghezze diverse (una tabella triangolare) ogni
riga è un array a sé e un array di puntatori le raccoglie:

```c
int r1[1], r2[2], r3[3], r4[4];
const int *righe[5] = {NULL, r1, r2, r3, r4};

righe[3][1]      /* riga 3, elemento 1 */
```

### Scambiare righe

Con un array di puntatori alle righe, riordinare significa scambiare
puntatori: le righe della matrice non si spostano.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-matrice-in-memoria.c` | Indirizzi consecutivi, `sizeof` di matrice e riga, `*(*(m + i) + j)` |
| `020-puntatore-a-riga.c` | `int (*riga)[MESI]` e `riga++` sulle vendite di quattro negozi |
| `030-matrice-come-blocco-unico.c` | `&m[0][0]` e un solo ciclo; riga e colonna da `k` |
| `040-problema-orario-settimanale.c` | Riga del giorno come `const int *`, matrice come `const int (*)[ORE]` |
| `040-problema-orario-settimanale-analisi.md` | Analisi di `040-problema-orario-settimanale.c` |
| `050-problema-statistiche-griglia.c` | Le stesse funzioni su tutta la serra (blocco) e su una fila (riga) |
| `050-problema-statistiche-griglia-analisi.md` | Analisi di `050-problema-statistiche-griglia.c` |
| `060-problema-triangolo-distanze.c` | Tabella triangolare con righe di lunghezza diversa |
| `060-problema-triangolo-distanze-analisi.md` | Analisi di `060-problema-triangolo-distanze.c` |
| `070-problema-scambio-righe.c` | Classifica come array di puntatori alle righe, sorpassi con scambi |
| `070-problema-scambio-righe-analisi.md` | Analisi di `070-problema-scambio-righe.c` |
| `080-problema-immagine-in-scala-di-grigi.c` | Capovolgimento con due puntatori a riga, negativo come blocco unico |
| `080-problema-immagine-in-scala-di-grigi-analisi.md` | Analisi di `080-problema-immagine-in-scala-di-grigi.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-matrice-in-memoria 010-matrice-in-memoria.c
./010-matrice-in-memoria

gcc -Wall -Wextra -o 020-puntatore-a-riga 020-puntatore-a-riga.c
./020-puntatore-a-riga

gcc -Wall -Wextra -o 030-matrice-come-blocco-unico 030-matrice-come-blocco-unico.c
./030-matrice-come-blocco-unico

gcc -Wall -Wextra -o 040-problema-orario-settimanale 040-problema-orario-settimanale.c
./040-problema-orario-settimanale

gcc -Wall -Wextra -o 050-problema-statistiche-griglia 050-problema-statistiche-griglia.c
./050-problema-statistiche-griglia

gcc -Wall -Wextra -o 060-problema-triangolo-distanze 060-problema-triangolo-distanze.c
./060-problema-triangolo-distanze

gcc -Wall -Wextra -o 070-problema-scambio-righe 070-problema-scambio-righe.c
./070-problema-scambio-righe

gcc -Wall -Wextra -o 080-problema-immagine-in-scala-di-grigi 080-problema-immagine-in-scala-di-grigi.c
./080-problema-immagine-in-scala-di-grigi
```

---

## Output atteso

> Gli indirizzi stampati cambiano a ogni esecuzione.

### 010-matrice-in-memoria
```
=== INDIRIZZI DEGLI ELEMENTI (ordine per righe) ===
  riga 0:  0x7fff350a4280  0x7fff350a4284  0x7fff350a4288  0x7fff350a428c
  riga 1:  0x7fff350a4290  0x7fff350a4294  0x7fff350a4298  0x7fff350a429c
  riga 2:  0x7fff350a42a0  0x7fff350a42a4  0x7fff350a42a8  0x7fff350a42ac
Ogni elemento e' 4 byte dopo il precedente, anche da una riga alla successiva.

=== DIMENSIONI ===
  sizeof(prenotazioni)    = 48 byte (tutta la matrice)
  sizeof(prenotazioni[0]) = 16 byte (una riga)
  prenotazioni     = 0x7fff350a4280   (riga 0)
  prenotazioni + 1 = 0x7fff350a4290   (riga 1: 16 byte dopo)

=== TRE MODI DI LEGGERE LA FILA 3, BANCO 3 (indici 2 e 2) ===
  prenotazioni[2][2]            = 7
  *(*(prenotazioni + 2) + 2)    = 7
  *(&prenotazioni[0][0] + 2 * 4 + 2) = 7
```

### 020-puntatore-a-riga
```
=== SCORRIMENTO PER RIGHE CON riga++ ===
  Centro        120   95  140  160  110  180   totale  805
  Stazione       80   70   90   85  100  120   totale  545
  Universita'   200  180  210  190  230  260   totale 1270
  Periferia      60   65   70   50   55   90   totale  390

Negozio con piu' vendite: Universita' (1270 pezzi)
sizeof(*riga) = 24 byte: riga++ avanza di una riga intera.
```

### 030-matrice-come-blocco-unico
```
Posti: 24, mai occupati: 6, occupati almeno 240 minuti: 12
Occupazione media: 167.9 minuti
Posto piu' occupato: fila 1, posto 5 (310 minuti)
```

### 040-problema-orario-settimanale
*(output dipendente dall'input – esempio di sessione)*
```
Giorno (1-5, 0 per finire): 3
  Mercoledi:
    1a ora  Informatica
    2a ora  Informatica
    3a ora  Informatica
    4a ora  Inglese
    5a ora  Ed. fisica
    6a ora  Ed. fisica
Giorno (1-5, 0 per finire): 6
  Giorno non valido.
Giorno (1-5, 0 per finire): 0

Ore settimanali per materia:
  Italiano     6
  Matematica   5
  Informatica  7
  Inglese      3
  Sistemi      4
  Ed. fisica   2
  Storia       3
```

### 050-problema-statistiche-griglia
```
Temperatura media della serra: 26.32 gradi
Settore piu' caldo: fila 2, settore 5 (29.4 gradi)
Settori oltre 28.0 gradi: 4 su 20

Fila 1: media 25.92, massima 27.2, oltre soglia 0
Fila 2: media 27.44, massima 29.4, oltre soglia 2
Fila 3: media 26.96, massima 28.9, oltre soglia 2
Fila 4: media 24.96, massima 26.1, oltre soglia 0
```

### 060-problema-triangolo-distanze
```
Tabella delle distanze (km):
             Scuola    Borgo  Collina    Ponte     Lago
Scuola            0        7       12        9       14
Borgo             7        0        6       15       10
Collina          12        6        0       18        8
Ponte             9       15       18        0       21
Lago             14       10        8       21        0

Giro del mattino:   Scuola -> Ponte -> Borgo -> Collina -> Lago  = 38 km
Giro alternativo:   Scuola -> Borgo -> Collina -> Lago -> Ponte  = 42 km
```

### 070-problema-scambio-righe
*(output dipendente dall'input – esempio di sessione)*
```
  Pos Squadra   V P S  Punti
   1. Fulmini   3 1 0   10
   2. Tigri     2 2 0    8
   3. Squali    2 0 2    6
   4. Aquile    1 2 1    5
   5. Lupi      0 1 3    1
Squadra (1-5) ed esito V/P/S, 0 per finire: 4 V
  Pos Squadra   V P S  Punti
   1. Fulmini   3 1 0   10
   2. Tigri     2 2 0    8
   3. Aquile    2 2 1    8
   4. Squali    2 0 2    6
   5. Lupi      0 1 3    1
Squadra (1-5) ed esito V/P/S, 0 per finire: 4 V
  Pos Squadra   V P S  Punti
   1. Aquile    3 2 1   11
   2. Fulmini   3 1 0   10
   3. Tigri     2 2 0    8
   4. Squali    2 0 2    6
   5. Lupi      0 1 3    1
Squadra (1-5) ed esito V/P/S, 0 per finire: 3 P
  Pos Squadra   V P S  Punti
   1. Aquile    3 2 1   11
   2. Fulmini   3 1 0   10
   3. Tigri     2 2 0    8
   4. Squali    2 1 2    7
   5. Lupi      0 1 3    1
Squadra (1-5) ed esito V/P/S, 0 per finire: 0
```

### 080-problema-immagine-in-scala-di-grigi
```
Originale:
  |    @@    |
  |   @@@@   |
  |  @@@@@@  |
  |    **    |
  |    **    |
  |----------|

Capovolta:
  |----------|
  |    **    |
  |    **    |
  |  @@@@@@  |
  |   @@@@   |
  |    @@    |

Negativo:
  |**********|
  |@@@@--@@@@|
  |@@@@--@@@@|
  |@@      @@|
  |@@@    @@@|
  |@@@@  @@@@|
```

---

## Errori comuni da evitare

**Dimenticare le parentesi nel puntatore a riga**
```c
int *riga[MESI] = vendite;     /* errore: array di puntatori */
int (*riga)[MESI] = vendite;   /* corretto */
```

**Usare `riga[j]` invece di `(*riga)[j]`**
```c
riga[j]        /* la riga j-esima dopo quella puntata, non l'elemento j */
(*riga)[j]     /* elemento j della riga puntata */
```

**Passare la matrice dove serve un `int *`**
```c
media(serra, 20);            /* avviso: double (*)[5] invece di double * */
media(&serra[0][0], 20);     /* corretto: primo elemento */
```

**Contare riga e colonna con la dimensione sbagliata**
```c
riga = k / FILE;       /* sbagliato */
riga = k / COLONNE;    /* corretto: si divide per la lunghezza di una riga */
```

**Dereferenziare una riga `NULL`**
```c
righe[0][0]            /* la riga 0 della tabella triangolare non esiste */
```

---

## Concetti collegati

- `04-array-e-stringhe/02-array-multidimensionali` → matrici con gli indici
- `02-puntatori-e-array` → aritmetica dei puntatori e sottoarray
- `02-array-di-puntatori` → array di puntatori a righe di lunghezza diversa
- `06-memoria-dinamica/03-array-dinamici` → matrici con dimensioni decise durante l'esecuzione

---

## Esercizi proposti

1. In `020-puntatore-a-riga.c` stampa anche il mese con le vendite più alte
   di ogni negozio.

2. In `030-matrice-come-blocco-unico.c` conta i posti occupati meno di
   un'ora in ogni fila, passando le righe come array.

3. In `060-problema-triangolo-distanze.c` aggiungi un sesto paese con una
   riga `r5[5]`.

4. In `070-problema-scambio-righe.c` fai scendere in classifica una squadra
   che perde (scambi verso il basso).

5. (Avanzato) In `080-problema-immagine-in-scala-di-grigi.c` scrivi
   `specchia`, che capovolge l'immagine da sinistra a destra con due
   puntatori su ogni riga.
