# 03 – Operazioni su matrici

## Concetto

I pattern visti sugli array (accumulatore, ipotesi e smentita, ricerca con
flag, conteggio) si estendono alle matrici. La novità è che ogni operazione
può riguardare **tutta la matrice**, **una riga** o **una colonna**.

### Totali di riga, di colonna e generale

```
              Lun  Mar  Mer  Gio  Ven  │ Totale riga
  Reparto 1     2    0    3    1    4  │   10
  Reparto 2     5    6    2    4    3  │   20
  ─────────────────────────────────────┼─────────────
  Totale col.   7    6    5    5    7  │   30   ← totale generale
```

L'accumulatore di riga si azzera **dentro il ciclo esterno, prima di quello
interno**; per i totali di colonna si invertono i cicli.

### Estremi e ricerca

- **Massimo/minimo**: si memorizzano **riga e colonna**, partendo da `[0][0]`.
- **Massimo di ogni riga**: l'ipotesi riparte per ogni riga da `[r][0]`.
- **Ricerca**: il flag `trovato` va nella condizione di **entrambi** i cicli,
  così si fermano tutti e due.

```c
for (r = 0; r < RIGHE && !trovato; r++) {
    for (c = 0; c < COLONNE && !trovato; c++) {
        if (m[r][c] == cercato) {
            trovato = 1;
            r_trovato = r;
            c_trovato = c;
        }
    }
}
```

### Matrici quadrate

| Elemento | Condizione | Esempio (N = 4) |
|----------|------------|-----------------|
| diagonale principale | `riga == colonna` | `[0][0] [1][1] [2][2] [3][3]` |
| diagonale secondaria | `riga + colonna == N - 1` | `[0][3] [1][2] [2][1] [3][0]` |
| sopra la diagonale | `colonna > riga` | ogni coppia una volta sola |

- **Trasposta**: `t[j][i] = m[i][j]` (una R × C diventa C × R).
- **Simmetrica**: `m[i][j] == m[j][i]`; basta controllare le celle con `j > i`.
- **Trasposta sul posto** (solo quadrate): si scambiano le coppie con `j > i`.

### Array paralleli e risultati di riga

Quando i totali di riga servono più volte (prospetto e classifica, quota e
soglia) si salvano in un array parallelo alle righe (`totale[s]`).

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-somme-per-riga-e-colonna.c` | Tabella con totali di riga, di colonna e generale; verifica di coerenza |
| `020-massimo-minimo-e-ricerca.c` | Estremi con posizione, ricerca con flag nei due cicli, conteggio, massimo di riga |
| `030-diagonali-e-trasposta.c` | Diagonali, trasposta rettangolare, verifica di simmetria, trasposta sul posto |
| `040-problema-quadrato-magico.c` | Verifica del quadrato di Dürer e di una variante non magica |
| `040-problema-quadrato-magico-analisi.md` | Analisi di `040-problema-quadrato-magico.c` |
| `050-problema-immagine-grigi.c` | Immagine 6 × 10 in scala di grigi: visualizzazione, media, negativo, soglia, specchio |
| `050-problema-immagine-grigi-analisi.md` | Analisi di `050-problema-immagine-grigi.c` |
| `060-problema-campionato.c` | Punti di 6 squadre in 5 giornate: prospetto, classifica, imbattute, esiti per giornata |
| `060-problema-campionato-analisi.md` | Analisi di `060-problema-campionato.c` |
| `070-problema-consumi-condominio.c` | Consumi di 6 appartamenti in 6 mesi: totali, picco, quote, consumi elevati |
| `070-problema-consumi-condominio-analisi.md` | Analisi di `070-problema-consumi-condominio.c` |
| `080-problema-distanze-citta.c` | Tabella delle distanze: verifica, città più vicina, coppia più lontana, itinerario |
| `080-problema-distanze-citta-analisi.md` | Analisi di `080-problema-distanze-citta.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-somme-per-riga-e-colonna 010-somme-per-riga-e-colonna.c
./010-somme-per-riga-e-colonna

gcc -Wall -Wextra -o 020-massimo-minimo-e-ricerca 020-massimo-minimo-e-ricerca.c
./020-massimo-minimo-e-ricerca

gcc -Wall -Wextra -o 030-diagonali-e-trasposta 030-diagonali-e-trasposta.c
./030-diagonali-e-trasposta

gcc -Wall -Wextra -o 040-problema-quadrato-magico 040-problema-quadrato-magico.c
./040-problema-quadrato-magico

gcc -Wall -Wextra -o 050-problema-immagine-grigi 050-problema-immagine-grigi.c
./050-problema-immagine-grigi

gcc -Wall -Wextra -o 060-problema-campionato 060-problema-campionato.c
./060-problema-campionato

gcc -Wall -Wextra -o 070-problema-consumi-condominio 070-problema-consumi-condominio.c
./070-problema-consumi-condominio

gcc -Wall -Wextra -o 080-problema-distanze-citta 080-problema-distanze-citta.c
./080-problema-distanze-citta
```

---

## Output atteso

Nessun programma richiede input: l'output è sempre lo stesso.

### 010-somme-per-riga-e-colonna
```
=== ORE DI STRAORDINARIO PER REPARTO ===

              Lun  Mar  Mer  Gio  Ven   Totale
  Reparto 1      2    0    3    1    4       10
  Reparto 2      5    6    2    4    3       20
  Reparto 3      0    1    0    2    1        4
  Reparto 4      3    2    4    5    6       20
  ---------------------------------------------
  Totale        10    9    9   12   14       54

Somma dei totali di riga    : 54
Somma dei totali di colonna : 54
Totale generale             : 54
Media per reparto al giorno : 2.70 ore
```

### 020-massimo-minimo-e-ricerca
```
=== TORNEO DI GIOCHI LOGICI ===
             P1  P2  P3  P4  P5  P6
  Squadra 1  12  15   9  18  14  11
  Squadra 2   8  20  13  10  16  20
  Squadra 3  17  11  19   7  12  15
  Squadra 4  10  14  16  13   9  18

Punteggio piu' alto : 20 (squadra 2, prova 2)
Punteggio piu' basso: 7 (squadra 3, prova 4)

Primo punteggio 13: squadra 2, prova 3
Prove con almeno 15 punti: 10 su 24

Miglior prova di ogni squadra:
  Squadra 1: 18
  Squadra 2: 20
  Squadra 3: 19
  Squadra 4: 18
```

### 030-diagonali-e-trasposta
```
=== Diagonali della matrice 4 x 4 ===
Principale:   1  6 11 16   somma = 34
Secondaria:   4  7 10 13   somma = 34

=== Trasposta ===
Originale 2 x 3:      Trasposta 3 x 2:
  1  2  3              1  4
  4  5  6              2  5
                       3  6

=== Simmetria ===
La matrice s e' simmetrica.
La matrice q non e' simmetrica.

=== q trasposta sul posto ===
   1   5   9  13
   2   6  10  14
   3   7  11  15
   4   8  12  16
```

### 040-problema-quadrato-magico
```
=== Quadrato 1 ===
  16   3   2  13
   5  10  11   8
   9   6   7  12
   4  15  14   1
Numeri da 1 a 16 presenti una volta: si'
Costante magica attesa: 34
Esito: QUADRATO MAGICO

=== Quadrato 2 ===
  16   3   2  13
   5  10  11   8
   9   7   6  12
   4  15  14   1
Numeri da 1 a 16 presenti una volta: si'
Costante magica attesa: 34
  colonna 2: somma 35
  colonna 3: somma 33
  diagonale principale: somma 33
  diagonale secondaria: somma 35
Esito: non e' un quadrato magico
```

### 050-problema-immagine-grigi
```
Originale:
  |          OO        |
  |          @@OO      |
  |..........@@@@@@    |
  |..........@@@@@@    |
  |          @@OO      |
  |          OO        |
Luminosita' media: 74.0

Negativo:
  |@@@@@@@@@@..@@@@@@@@|
  |@@@@@@@@@@  ..@@@@@@|
  |oooooooooo      @@@@|
  |oooooooooo      @@@@|
  |@@@@@@@@@@  ..@@@@@@|
  |@@@@@@@@@@..@@@@@@@@|

Soglia 128 (bianco/nero):
  |          @@        |
  |          @@@@      |
  |          @@@@@@    |
  |          @@@@@@    |
  |          @@@@      |
  |          @@        |

Specchio orizzontale:
  |        OO          |
  |      OO@@          |
  |    @@@@@@..........|
  |    @@@@@@..........|
  |      OO@@          |
  |        OO          |
```

### 060-problema-campionato
```
=== TORNEO CALCIO A 5 - DOPO 5 GIORNATE ===

  Squadra          G1 G2 G3 G4 G5   Punti
  Atletico Volta    V  P  V  S  V      10
  Real Tortona      P  P  V  V  S       8
  Sporting Novi     S  V  S  P  S       4
  Dinamo Acqui      V  V  P  V  V      13
  Olimpia Ovada     S  S  P  S  V       4
  Union Casale      P  S  S  P  S       2

--- Classifica ---
  1. Dinamo Acqui      13 punti
  2. Atletico Volta    10 punti
  3. Real Tortona       8 punti
  4. Sporting Novi      4 punti
  5. Olimpia Ovada      4 punti
  6. Union Casale       2 punti

--- Squadre imbattute ---
  Dinamo Acqui

--- Esiti per giornata ---
  Giornata 1: 2 vittorie, 1 pareggio
  Giornata 2: 2 vittorie, 1 pareggio
  Giornata 3: 2 vittorie, 1 pareggio
  Giornata 4: 2 vittorie, 1 pareggio
  Giornata 5: 3 vittorie, 0 pareggi
```

### 070-problema-consumi-condominio
```
=== CONSUMI RISCALDAMENTO (kWh) ===

  Interno   Ott   Nov   Dic   Gen   Feb   Mar  Stagione
        1   310   520   780   820   650   400      3480
        2   280   450   700   760   590   350      3130
        3   450   690   980  1050   860   560      4590
        4   150   260   450   430   330   200      1820
        5   300   500   750   800   620   390      3360
        6   200   360   540   560   610   270      2540
  Totale   1690  2780  4200  4420  3660  2170     18920

Mese di picco: Gen (4420 kWh)

Consumo medio per appartamento: 3153 kWh
Soglia di attenzione (120% della media): 3784 kWh

  Interno   Quota   Mese max
        1   18.4%   Gen
        2   16.5%   Gen
        3   24.3%   Gen   <- consumo elevato
        4    9.6%   Dic
        5   17.8%   Gen
        6   13.4%   Feb
```

### 080-problema-distanze-citta
```
=== TABELLA DISTANZE (km) ===
Diagonale nulla e simmetria: verificate

--- Citta' piu' vicina ---
  Alessandria  -> Asti           37 km
  Asti         -> Alessandria    37 km
  Genova       -> Alessandria    80 km
  Milano       -> Pavia          38 km
  Torino       -> Asti           60 km
  Pavia        -> Milano         38 km

Coppia piu' lontana: Genova - Torino (170 km)

--- Itinerario ---
  Alessandria  -> Pavia          63 km
  Pavia        -> Milano         38 km
  Milano       -> Asti          125 km
  Asti         -> Torino         60 km
  Totale: 286 km
```

---

## Errori comuni da evitare

**Accumulatore di riga azzerato una sola volta**
```c
totale = 0;                          /* ERRATO: fuori dal ciclo esterno */
for (r = 0; r < RIGHE; r++) {
    for (c = 0; c < COLONNE; c++) {
        totale = totale + m[r][c];
    }
    printf("%d\n", totale);          /* somma cumulativa, non della riga */
}
```

**Ricerca che ferma solo il ciclo interno**
```c
for (r = 0; r < RIGHE; r++) {                     /* manca && !trovato */
    for (c = 0; c < COLONNE && !trovato; c++) { ... }
}
/* il ciclo esterno prosegue inutilmente fino all'ultima riga */
```

**Minimo di riga che include la diagonale**
```c
/* distanze: [i][i] vale 0 e sarebbe sempre il minimo */
if (distanze[i][j] < distanze[i][min])      /* manca j != i */
```

**Trasposta sul posto su tutta la matrice**
```c
for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {       /* ERRATO: ogni coppia scambiata due volte */
        scambia m[i][j] e m[j][i]
    }
}
/* corretto: j parte da i + 1 */
```

**Diagonale secondaria con l'indice sbagliato**
```c
m[i][N - i]        /* ERRATO: per i = 0 è fuori dai limiti */
m[i][N - 1 - i]    /* corretto */
```

---

## Concetti collegati

- `01-array-monodimensionali/03-operazioni-su-array` → gli stessi pattern su una dimensione
- `02-accesso-e-scorrimento` → scorrimento per righe e per colonne
- `04-matrici-e-funzioni` → le stesse operazioni raccolte in funzioni riusabili
- `11-algoritmi` → ordinamento, qui anticipato con la ricerca ripetuta del massimo

---

## Esercizi proposti

1. Scrivi un programma che verifichi se una matrice quadrata è **triangolare
   superiore** (tutti zeri sotto la diagonale principale).

2. In `020-massimo-minimo-e-ricerca.c` stampa tutte le posizioni in cui compare
   il punteggio massimo, non solo la prima.

3. Aggiungi a `050-problema-immagine-grigi.c` lo specchio verticale (scambio
   delle righe) e l'aumento di luminosità di 50, senza superare 255.

4. In `060-problema-campionato.c` a parità di punti metti prima la squadra con
   più vittorie.

5. (Avanzato) In `080-problema-distanze-citta.c` costruisci un itinerario
   "goloso": partendo da Alessandria, vai ogni volta alla città più vicina non
   ancora visitata, finché le hai visitate tutte. Stampa il percorso e i km.
