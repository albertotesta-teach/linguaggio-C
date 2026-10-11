# 01 – Indirizzi e memoria

## Concetto

La memoria del computer è una sequenza di celle da 1 byte, ciascuna
identificata da un numero: il suo **indirizzo**. Ogni variabile occupa
alcune celle consecutive; il suo indirizzo è quello della prima.

### L'operatore `&`

```c
int eta = 17;
printf("%p\n", (void *) &eta);   /* stampa l'indirizzo di eta */
```

| Elemento | Significato |
|----------|-------------|
| `&x` | indirizzo della variabile `x` |
| `%p` | specifica di `printf` per gli indirizzi (in esadecimale) |
| `(void *)` | conversione richiesta da `%p`: è l'unico uso di `void *` nel capitolo |

L'operatore `&` è già noto: `scanf("%d", &n)` passa a `scanf` l'indirizzo di
`n`, così che `scanf` possa scrivere il valore letto in quella variabile.

### Quanto occupa una variabile: `sizeof`

`sizeof` restituisce i byte occupati da un tipo, da una variabile o da un
intero array (tipo `size_t`, si stampa con `%zu`):

| Tipo | Byte tipici (sistema a 64 bit) |
|------|--------------------------------|
| `char` | 1 (garantito) |
| `short` | 2 |
| `int`, `float` | 4 |
| `long`, `double`, indirizzo | 8 |

```c
n = sizeof(v) / sizeof(v[0]);    /* numero di elementi di un array */
```

### Variabili e array in memoria

- Variabili diverse hanno indirizzi diversi, ma il loro **ordine** in memoria
  è scelto dal compilatore.
- Gli elementi di un **array** sono sempre **consecutivi**: in un array di
  `int` gli indirizzi crescono di 4 in 4, in un array di `double` di 8 in 8.
- Il nome di un array (`nickname` in `scanf("%19s", nickname)`) indica già
  l'indirizzo del primo elemento: per questo non serve `&`.

### Valore e indirizzo sono cose diverse

```c
tessera_1 == tessera_3      /* stesso valore? */
&tessera_1 == &tessera_3    /* stessa variabile? */
```

> **Nota sull'output.** Gli indirizzi cambiano a ogni esecuzione, perché il
> sistema operativo colloca il programma in punti diversi della memoria.
> Gli indirizzi riportati qui sotto sono solo un esempio.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-indirizzo-di-una-variabile.c` | `&`, `%p`, indirizzo costante al cambiare del valore, `scanf` |
| `020-sizeof-e-tipi.c` | Dimensione dei tipi, di array e stringhe e degli indirizzi |
| `030-variabili-e-array-in-memoria.c` | Elementi consecutivi in array di `int` e di `double` |
| `040-problema-mappa-memoria.c` | Mappa della memoria di una scheda studente |
| `040-problema-mappa-memoria-analisi.md` | Analisi di `040-problema-mappa-memoria.c` |
| `050-problema-memoria-datalogger.c` | Scelta dei tipi per la memoria di una stazione meteo |
| `050-problema-memoria-datalogger-analisi.md` | Analisi di `050-problema-memoria-datalogger.c` |
| `060-problema-lettura-con-scanf.c` | Modulo di iscrizione: perché `scanf` vuole gli indirizzi |
| `060-problema-lettura-con-scanf-analisi.md` | Analisi di `060-problema-lettura-con-scanf.c` |
| `070-problema-salvataggio-partita.c` | Dimensione del salvataggio di una partita |
| `070-problema-salvataggio-partita-analisi.md` | Analisi di `070-problema-salvataggio-partita.c` |
| `080-problema-trasferimento-tra-conti.c` | Riconoscere la stessa variabile confrontando gli indirizzi |
| `080-problema-trasferimento-tra-conti-analisi.md` | Analisi di `080-problema-trasferimento-tra-conti.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-indirizzo-di-una-variabile 010-indirizzo-di-una-variabile.c
./010-indirizzo-di-una-variabile

gcc -Wall -Wextra -o 020-sizeof-e-tipi 020-sizeof-e-tipi.c
./020-sizeof-e-tipi

gcc -Wall -Wextra -o 030-variabili-e-array-in-memoria 030-variabili-e-array-in-memoria.c
./030-variabili-e-array-in-memoria

gcc -Wall -Wextra -o 040-problema-mappa-memoria 040-problema-mappa-memoria.c
./040-problema-mappa-memoria

gcc -Wall -Wextra -o 050-problema-memoria-datalogger 050-problema-memoria-datalogger.c
./050-problema-memoria-datalogger

gcc -Wall -Wextra -o 060-problema-lettura-con-scanf 060-problema-lettura-con-scanf.c
./060-problema-lettura-con-scanf

gcc -Wall -Wextra -o 070-problema-salvataggio-partita 070-problema-salvataggio-partita.c
./070-problema-salvataggio-partita

gcc -Wall -Wextra -o 080-problema-trasferimento-tra-conti 080-problema-trasferimento-tra-conti.c
./080-problema-trasferimento-tra-conti
```

---

## Output atteso

### 010-indirizzo-di-una-variabile
*(output dipendente dall'input – esempio con la nuova eta' 18)*
```
=== VALORE E INDIRIZZO ===
  eta     = 17      indirizzo 0x7ffc5a26c45c
  media   = 7.25    indirizzo 0x7ffc5a26c460
  sezione = B       indirizzo 0x7ffc5a26c45b

Dopo eta = 18:
  eta     = 18      indirizzo 0x7ffc5a26c45c (lo stesso)

Nuova eta': 18
  scanf ha scritto 18 all'indirizzo 0x7ffc5a26c45c
```

### 020-sizeof-e-tipi
```
=== DIMENSIONE DEI TIPI ===
  char         1 byte
  short        2 byte
  int          4 byte
  long         8 byte
  long long    8 byte
  float        4 byte
  double       8 byte

=== DIMENSIONE DI ARRAY E STRINGHE ===
  double temperature[10]   80 byte (10 x 8)
  char sigla[] = "AL"       3 byte (2 lettere + '\0')
  elementi di temperature: 10

=== DIMENSIONE DI UN INDIRIZZO ===
  &quanti         8 byte
  &temperature[0] 8 byte
  Un indirizzo ha la stessa dimensione qualunque sia il tipo.
```

### 030-variabili-e-array-in-memoria
```
=== ARRAY DI int (4 byte per elemento) ===
  voti[0] = 7   indirizzo 0x7ffed9882fb0
  voti[1] = 8   indirizzo 0x7ffed9882fb4
  voti[2] = 6   indirizzo 0x7ffed9882fb8
  voti[3] = 9   indirizzo 0x7ffed9882fbc
  voti[4] = 7   indirizzo 0x7ffed9882fc0

=== ARRAY DI double (8 byte per elemento) ===
  pesi[0] = 1.0 indirizzo 0x7ffed9882fd0
  pesi[1] = 1.5 indirizzo 0x7ffed9882fd8
  pesi[2] = 1.0 indirizzo 0x7ffed9882fe0
  pesi[3] = 2.0 indirizzo 0x7ffed9882fe8
  pesi[4] = 1.0 indirizzo 0x7ffed9882ff0

Gli indirizzi di voti[] sono crescenti: si'
L'array occupa 20 byte consecutivi a partire da 0x7ffed9882fb0
Osserva le ultime cifre: crescono di 4 per voti[] e di 8 per pesi[].
```

### 040-problema-mappa-memoria
```
=== MAPPA DELLA MEMORIA: Giulia Ferri ===
  Dato         Tipo      Indirizzo        Byte
  matricola    long      0x7ffeac1f1f68   8
  eta          int       0x7ffeac1f1f60   4
  sezione      char      0x7ffeac1f1f5f   1
  media        double    0x7ffeac1f1f70   8
  nome         char[20]  0x7ffeac1f1fa0   20
  voti         int[6]    0x7ffeac1f1f80   24

Dettaglio dell'array voti (elementi consecutivi):
    voti[0] = 7  0x7ffeac1f1f80
    voti[1] = 8  0x7ffeac1f1f84
    voti[2] = 6  0x7ffeac1f1f88
    voti[3] = 8  0x7ffeac1f1f8c
    voti[4] = 7  0x7ffeac1f1f90
    voti[5] = 8  0x7ffeac1f1f94

Byte occupati da una scheda: 65
Per 1000 schede servirebbero circa 65000 byte (63.5 KB)
```

### 050-problema-memoria-datalogger
```
=== DIMENSIONAMENTO DEL DATALOGGER ===
Memoria disponibile: 32768 byte, una misura ogni 10 minuti

  Ver. Tipi                                Byte  Misure  Giorni
  A    double, double, double                24    1365     9.5
  B    float, float, float                   12    2730    19.0
  C    short (decimi), char (%), short        5    6553    45.5

Esempio di misura nella versione C: 215 decimi = 21.5 gradi, 45%, 1013 hPa
Con gli interi si perde poco in precisione e si registra molto piu' a lungo.
```

### 060-problema-lettura-con-scanf
*(output dipendente dall'input – esempio con due valori non validi)*
```
=== ISCRIZIONE AL TORNEO ===
Eta': abc
  Valore non valido. Eta': 150
  Valore non valido. Eta': 15
Punteggio ELO: 1420
Categoria (U = under 18, A = adulti): A
Nickname: Cavallo_Nero

=== DATI REGISTRATI ===
  Dato       Valore        scritto da scanf all'indirizzo
  eta        15            0x7fffd1dc4564
  elo        1420          0x7fffd1dc4568
  categoria  A             0x7fffd1dc4563
  nickname   Cavallo_Nero  0x7fffd1dc4570  (= &nickname[0])
Attenzione: la categoria non corrisponde all'eta'.
```

### 070-problema-salvataggio-partita
```
=== STATO DELLA PARTITA ===
  Variabile        Tipo      Indirizzo         Byte
  vite             int       0x7fff484cde94       4
  punteggio        long      0x7fff484cde98       8
  livello          short     0x7fff484cde92       2
  tempo_gioco      double    0x7fff484cdea0       8
  personaggio      char      0x7fff484cde91       1
  completati_int   int[40]   0x7fff484cdec0     160
  completati_char  char[40]  0x7fff484cdf60      40

=== DIMENSIONE DEL SALVATAGGIO ===
  livelli come int  :  183 byte ->  5 slot in 1024 byte
  livelli come char :   63 byte -> 16 slot in 1024 byte
  Usare char per i livelli fa risparmiare 120 byte a salvataggio.
  (Partita di esempio: vite 3, livello 12, punteggio 125400, personaggio M, 5424 s)
```

### 080-problema-trasferimento-tra-conti
```
Indirizzi: tessera_1 0x7ffc444d1970, tessera_2 0x7ffc444d1974, tessera_3 0x7ffc444d1978
Crediti: tessera 1 15.00  tessera 2 4.00  tessera 3 15.00 euro
tessera_1 e tessera_3 hanno lo stesso credito (tessera_1 == tessera_3)? si'
Sono la stessa tessera (&tessera_1 == &tessera_3)? no

Da 1 a 2, 6.00 euro: eseguito
Crediti: tessera 1 9.00  tessera 2 10.00  tessera 3 15.00 euro

Da 2 a 2, 2.00 euro: stessa tessera
Da 2 a 3, 50.00 euro: credito insufficiente
Da 3 a 1, -1.00 euro: importo non valido
Crediti: tessera 1 9.00  tessera 2 10.00  tessera 3 15.00 euro
```

---

## Errori comuni da evitare

**Dimenticare `&` in `scanf`**
```c
scanf("%d", eta);       /* passa il valore: scrive in una posizione casuale */
scanf("%d", &eta);      /* corretto */
```

**Stampare un indirizzo con `%d`**
```c
printf("%d", &eta);             /* tipo sbagliato: avviso del compilatore */
printf("%p", (void *) &eta);    /* corretto */
```

**Supporre l'ordine delle variabili in memoria**
```c
/* che eta venga prima di media in memoria non è garantito */
```

**Supporre la dimensione dei tipi**
```c
byte = 4 * n;               /* e se int non fosse di 4 byte? */
byte = sizeof(int) * n;     /* corretto */
```

**Confondere uguaglianza di valori e di indirizzi**
```c
if (a == b)       /* stesso valore */
if (&a == &b)     /* stessa variabile */
```

---

## Concetti collegati

- `03-funzioni/03-passaggio-per-riferimento` → `&` e `*` nei parametri
- `02-dichiarazione-e-dereferenziazione` → variabili che contengono indirizzi
- `02-puntatori-e-array` → calcoli sugli indirizzi degli elementi di un array

---

## Esercizi proposti

1. In `020-sizeof-e-tipi.c` aggiungi `unsigned int`, `long double` e
   `unsigned char` e confronta le dimensioni.

2. In `030-variabili-e-array-in-memoria.c` dichiara un array di `char` e uno
   di `short` e verifica di quanto crescono gli indirizzi.

3. In `050-problema-memoria-datalogger.c` aggiungi una quarta grandezza, la
   velocità del vento, e ricalcola i giorni per le tre versioni.

4. In `080-problema-trasferimento-tra-conti.c` aggiungi una commissione di
   10 centesimi a carico della tessera di origine.

5. (Avanzato) Scrivi una funzione `int stessa_variabile(int *a, int *b)` e
   usala per impedire lo scambio di una variabile con se stessa.
