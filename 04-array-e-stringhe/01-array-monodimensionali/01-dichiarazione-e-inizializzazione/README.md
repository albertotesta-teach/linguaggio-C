# 01 – Dichiarazione e inizializzazione di array monodimensionali

## Concetto

Un **array monodimensionale** è una sequenza di variabili dello stesso tipo
disposte in posizioni di memoria **contigue**. Si dichiara indicando il tipo
degli elementi, il nome e il numero di celle tra parentesi quadre:

```c
int voti[5];          /* 5 interi contigui in memoria */
double temperature[7]; /* 7 double contigui in memoria */
```

Gli elementi sono accessibili tramite un **indice che parte da 0**:

```
  Dichiarazione:  int voti[5];

  Indice:    [0]  [1]  [2]  [3]  [4]
  Valore:     7    8    6    9    7

  Indice valido: da 0 a dimensione-1 (qui: 0..4)
  Indice 5 e oltre: FUORI LIMITE (comportamento indefinito)
```

### Modi di inizializzazione

```c
/* Lista completa */
int a[3] = {10, 20, 30};

/* Dimensione dedotta dal compilatore */
int b[] = {10, 20, 30};       /* il compilatore conta: 3 elementi */

/* Lista parziale: gli elementi rimanenti vengono azzerati */
int c[10] = {1, 2, 3};        /* c[3]..c[9] valgono 0 */

/* Tutto a zero */
int d[8] = {0};

/* Con costante simbolica */
#define N 5
int e[N] = {1, 2, 3, 4, 5};
```

### Struttura in memoria

Ogni elemento occupa `sizeof(tipo)` byte. Gli indirizzi sono consecutivi:

```
  int v[4]:  | v[0] | v[1] | v[2] | v[3] |
  Offset:    +0     +4     +8     +12    (con sizeof(int)=4)
```

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-dichiarazione-base.c` | Dichiarazione, assegnazione per indice, stampa diretta e con ciclo, `sizeof` |
| `020-inizializzazione.c` | Cinque modalità di inizializzazione: lista completa, dimensione dedotta, lista parziale, `{0}`, costante `#define` |
| `030-array-in-memoria.c` | Visualizzazione degli indirizzi di ogni cella, offset e dimensione in byte |
| `040-problema-registro-voti.c` | Registro voti di 8 studenti: stampa tabellare, media, minimo, massimo, promossi/bocciati |
| `040-problema-registro-voti-analisi.md` | Analisi di `040-problema-registro-voti.c`: variabili, casi d'uso, algoritmi |
| `050-problema-inventario-magazzino.c` | Inventario 6 prodotti: prospetto con valore per riga, prodotti in esaurimento, totali |
| `050-problema-inventario-magazzino-analisi.md` | Analisi di `050-problema-inventario-magazzino.c`: variabili, casi d'uso, algoritmi |
| `060-problema-temperature-settimanali.c` | Temperature 7 giorni: media, giorni sopra media, variazione giornaliera |
| `060-problema-temperature-settimanali-analisi.md` | Analisi di `060-problema-temperature-settimanali.c`: variabili, casi d'uso, algoritmi |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-dichiarazione-base 010-dichiarazione-base.c
./010-dichiarazione-base

gcc -Wall -Wextra -o 020-inizializzazione 020-inizializzazione.c
./020-inizializzazione

gcc -Wall -Wextra -o 030-array-in-memoria 030-array-in-memoria.c
./030-array-in-memoria

gcc -Wall -Wextra -o 040-problema-registro-voti 040-problema-registro-voti.c
./040-problema-registro-voti

gcc -Wall -Wextra -o 050-problema-inventario-magazzino 050-problema-inventario-magazzino.c
./050-problema-inventario-magazzino

gcc -Wall -Wextra -o 060-problema-temperature-settimanali 060-problema-temperature-settimanali.c
./060-problema-temperature-settimanali
```

---

## Output atteso

### 010-dichiarazione-base
```
Voti della classe:
  Studente 1: 7
  Studente 2: 8
  Studente 3: 6
  Studente 4: 9
  Studente 5: 7

Stessa stampa con ciclo for:
  voti[0] = 7
  voti[1] = 8
  voti[2] = 6
  voti[3] = 9
  voti[4] = 7

Dimensione di un elemento : 4 byte
Dimensione totale array   : 20 byte
Numero di elementi        : 5
```

### 020-inizializzazione
```
Modo 1 - lista completa:
  temperatura[0] = 18
  temperatura[1] = 21
  temperatura[2] = 23
  temperatura[3] = 20
  temperatura[4] = 17
  temperatura[5] = 15
  temperatura[6] = 19

Modo 2 - dimensione dedotta (5 elementi):
  altitudini[0] = 120
  altitudini[1] = 340
  altitudini[2] = 89
  altitudini[3] = 450
  altitudini[4] = 210

Modo 3 - inizializzazione parziale (10 elementi, 3 espliciti):
  punteggi[0] = 85
  punteggi[1] = 92
  punteggi[2] = 78
  punteggi[3] = 0
  punteggi[4] = 0
  punteggi[5] = 0
  punteggi[6] = 0
  punteggi[7] = 0
  punteggi[8] = 0
  punteggi[9] = 0

Modo 4 - tutti a zero ({0}):
  contatori[0] = 0
  ...
  contatori[7] = 0

Modo 5 - dimensione con costante #define (12 mesi):
  mese  1: 45 mm
  mese  2: 38 mm
  ...
  mese 12: 50 mm
```

### 030-array-in-memoria
```
Mappa in memoria dell'array 'misure':
---------------------------------------------------
  Indice  | Valore | Indirizzo       | Offset
---------------------------------------------------
  [0]     |   10   | 0x... | +0 byte
  [1]     |   20   | 0x... | +4 byte
  [2]     |   30   | 0x... | +8 byte
  [3]     |   40   | 0x... | +12 byte
  [4]     |   50   | 0x... | +16 byte
---------------------------------------------------

Distanza tra elementi consecutivi:
  &misure[1] - &misure[0] = 4 byte
  &misure[2] - &misure[1] = 4 byte
  &misure[3] - &misure[2] = 4 byte
  &misure[4] - &misure[3] = 4 byte

Riepilogo:
  sizeof(int)      = 4 byte
  sizeof(misure)   = 20 byte
  Numero elementi  = 5
```
*(Gli indirizzi esadecimali variano a ogni esecuzione.)*

### 040-problema-registro-voti
```
============================================
      REGISTRO VOTI - MATEMATICA
============================================
  N.  | Nome               | Voto
------|--------------------|------
   1  | Rossi Marco        |    7
   2  | Bianchi Sara       |    8
   3  | Verdi Luca         |    6
   4  | Ferrari Anna       |    9
   5  | Russo Pietro       |    5
   6  | Colombo Giulia     |    8
   7  | Marino Davide      |    7
   8  | Greco Elena        |   10
============================================

Media della classe : 7.5
Voto più basso     : 5 (Russo Pietro)
Voto più alto      : 10 (Greco Elena)

Studenti promossi  : 7 su 8
Studenti bocciati  : 1 su 8
```

### 050-problema-inventario-magazzino
```
==========================================================
                  INVENTARIO MAGAZZINO
==========================================================
  Cod.  | Prodotto               | Qtà  | Prezzo | Valore
--------|------------------------|------|--------|--------
  P001  | Penna blu              |   45 |  0.80€ |  36.00€
  P002  | Quaderno A4            |    8 |  1.50€ |  12.00€
  P003  | Matita HB              |  120 |  0.40€ |  48.00€
  P004  | Gomma bianca           |    6 |  0.60€ |   3.60€
  P005  | Righello 30cm          |   30 |  1.20€ |  36.00€
  P006  | Temperamatite          |   15 |  0.90€ |  13.50€
==========================================================

Prodotti in esaurimento (quantita <= 10):
  [!] P002 - Quaderno A4: solo 8 pezzi
  [!] P004 - Gomma bianca: solo 6 pezzi

Giacenza totale    : 224 pezzi
Valore magazzino   : 149.10 euro
```

### 060-problema-temperature-settimanali
```
=================================
  TEMPERATURE SETTIMANA CORRENTE
=================================
  Lunedi'     :  18.5 °C
  Martedi'    :  21.0 °C
  Mercoledi'  :  23.4 °C
  Giovedi'    :  22.1 °C
  Venerdi'    :  19.8 °C
  Sabato      :  17.5 °C
  Domenica    :  16.2 °C
=================================

Temperatura media : 19.8 °C

Giorni sopra la media (> 19.8 °C):
  Martedi': 21.0 °C (+1.2 rispetto alla media)
  Mercoledi': 23.4 °C (+3.6 rispetto alla media)
  Giovedi': 22.1 °C (+2.3 rispetto alla media)
Totale: 3 giorni su 7

Variazione giornaliera:
  Lunedi' -> Martedi': +2.5 °C (in salita)
  Martedi' -> Mercoledi': +2.4 °C (in salita)
  Mercoledi' -> Giovedi': -1.3 °C (in discesa)
  Giovedi' -> Venerdi': -2.3 °C (in discesa)
  Venerdi' -> Sabato: -2.3 °C (in discesa)
  Sabato -> Domenica: -1.3 °C (in discesa)
```

---

## Errori comuni da evitare

**Accedere a un indice fuori dai limiti**
```c
int v[5] = {1, 2, 3, 4, 5};
printf("%d\n", v[5]); /* ERRORE: indice valido è 0..4 */
printf("%d\n", v[-1]); /* ERRORE: indice negativo */
/* Il compilatore non segnala l'errore: comportamento indefinito a runtime */
```

**Non inizializzare un array prima di usarlo**
```c
int a[5];
printf("%d\n", a[0]); /* ERRORE: valore indeterminato (garbage) */
/* Soluzione: inizializzare sempre, ad esempio con {0} */
```

**Confondere la dimensione con l'indice massimo**
```c
int b[10];
for (int i = 0; i <= 10; i++) { /* ERRORE: i <= 10 supera i limiti */
    b[i] = 0;                    /* Corretto: i < 10 */
}
```

**Inizializzare con troppi valori**
```c
int c[3] = {1, 2, 3, 4}; /* ERRORE: 4 valori per un array da 3 celle */
```

---

## Concetti collegati

- `02-accesso-e-scorrimento` → lettura da tastiera e scorrimento avanzato
- `03-operazioni-su-array` → somma, ricerca, inversione
- `04-array-e-funzioni` → passare un array a una funzione
- `05-puntatori/02-puntatori-e-array` → il legame tra array e puntatori

---

## Esercizi proposti

1. Dichiara un array di 6 interi e inizializzalo con i voti di un tuo studente
   immaginario. Stampa la somma dei voti e la media con un decimale.

2. Modifica `020-inizializzazione.c` aggiungendo un sesto modo: dichiara un
   array `float` di 4 elementi senza inizializzarlo, poi assegna i valori
   manualmente in un ciclo `for` e stampali.

3. Crea un programma che dichiari un array di 12 interi rappresentante le
   precipitazioni mensili (mm). Calcola il mese con pioggia massima e minima
   e la precipitazione media annua.

4. Partendo da `050-problema-inventario-magazzino.c`, aggiungi la stampa del
   prodotto con il valore più alto in magazzino (quantità × prezzo massimo).

5. (Avanzato) Modifica `060-problema-temperature-settimanali.c` per trovare
   il giorno con la variazione di temperatura più alta in valore assoluto
   rispetto al giorno precedente.
