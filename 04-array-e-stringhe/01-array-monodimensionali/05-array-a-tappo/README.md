# 05 – Array a tappo

## Concetto

In un **array a tappo** (o array con sentinella) la fine dei dati validi è
segnata da un valore speciale, il **tappo**, scritto subito dopo l'ultimo
elemento. Non serve memorizzare né passare il numero di elementi: il ciclo
si ferma quando incontra il tappo.

```
  #define TAPPO -1
  #define MAX   10

  indice:   0    1    2    3    4    5    6    7    8    9
          ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
  prezzi: │ 149│ 299│  89│ 450│  -1│  ? │  ? │  ? │  ? │  ? │
          └────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
            dati validi          ↑     spazio libero
                               tappo
```

### Scelta del tappo

Il tappo deve essere un valore **impossibile** come dato valido:

| Dati | Tappo tipico |
|------|--------------|
| interi non negativi (prezzi, durate, ID) | `-1` |
| interi strettamente positivi (codici evento) | `0` |
| caratteri | `'\0'` → è esattamente una **stringa C** |

### Il ciclo cambia forma

```c
/* dimensione nota */               /* array a tappo */
for (i = 0; i < n; i++) {           i = 0;
    ...                             while (arr[i] != TAPPO) {
}                                       ...
                                        i++;
                                    }
```

### Inserire e rimuovere

- **Aggiunta in fondo**: si scrive il nuovo valore al posto del tappo e si
  rimette il tappo nella cella successiva, solo se c'è ancora spazio.
- **Rimozione o inserimento in mezzo**: si spostano gli elementi (shift)
  all'indietro o in avanti, **tappo compreso**.
- **Array paralleli a tappo**: tutti gli array devono avere il tappo nella
  stessa posizione; ogni operazione li aggiorna insieme.

La capacità `MAX` deve sempre includere la cella del tappo: al massimo
`MAX - 1` dati validi.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-introduzione-al-tappo.c` | Somma con array a dimensione fissa e con array a tappo; aggiunta di un elemento; la stringa come array di `char` con tappo `'\0'` |
| `020-operazioni-con-tappo.c` | Lunghezza, ricerca, inserimento in fondo, rimozione per posizione, riempimento progressivo di un array vuoto |
| `030-tappo-su-array-di-char.c` | Versioni didattiche di `strlen`, `strcpy`, `strcmp`, `strcat` e inversione di una stringa |
| `040-problema-lista-della-spesa.c` | Prezzi in centesimi con tappo -1: totale, articolo più caro, aggiunta di articoli |
| `040-problema-lista-della-spesa-analisi.md` | Analisi di `040-problema-lista-della-spesa.c` |
| `050-problema-log-eventi.c` | Codici evento con tappo 0: classificazione INFO/WARNING/ERROR, percentuali, ultimo evento per tipo |
| `050-problema-log-eventi-analisi.md` | Analisi di `050-problema-log-eventi.c` |
| `060-problema-coda-prenotazioni.c` | Array paralleli ID/orario: aggiunta in fondo e rimozione in testa (coda FIFO), orari in formato HH:MM |
| `060-problema-coda-prenotazioni-analisi.md` | Analisi di `060-problema-coda-prenotazioni.c` |
| `070-problema-sensori-attivi.c` | Registro dei sensori attivi: aggiunta senza duplicati, rimozione per ID, media delle letture |
| `070-problema-sensori-attivi-analisi.md` | Analisi di `070-problema-sensori-attivi.c` |
| `080-problema-playlist-musicale.c` | Playlist ID/durata: inserimento in posizione intermedia, rimozione per ID, durate in MM:SS |
| `080-problema-playlist-musicale-analisi.md` | Analisi di `080-problema-playlist-musicale.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-introduzione-al-tappo 010-introduzione-al-tappo.c
./010-introduzione-al-tappo

gcc -Wall -Wextra -o 020-operazioni-con-tappo 020-operazioni-con-tappo.c
./020-operazioni-con-tappo

gcc -Wall -Wextra -o 030-tappo-su-array-di-char 030-tappo-su-array-di-char.c
./030-tappo-su-array-di-char

gcc -Wall -Wextra -o 040-problema-lista-della-spesa 040-problema-lista-della-spesa.c
./040-problema-lista-della-spesa

gcc -Wall -Wextra -o 050-problema-log-eventi 050-problema-log-eventi.c
./050-problema-log-eventi

gcc -Wall -Wextra -o 060-problema-coda-prenotazioni 060-problema-coda-prenotazioni.c
./060-problema-coda-prenotazioni

gcc -Wall -Wextra -o 070-problema-sensori-attivi 070-problema-sensori-attivi.c
./070-problema-sensori-attivi

gcc -Wall -Wextra -o 080-problema-playlist-musicale 080-problema-playlist-musicale.c
./080-problema-playlist-musicale
```

---

## Output atteso

Nessun programma richiede input: l'output è sempre lo stesso.

### 010-introduzione-al-tappo
```
=== Array a dimensione fissa ===
Elementi: 5
Somma: 150

=== Array a tappo (TAPPO = -1) ===
[ 10 20 30 40 50 ] (tappo in posizione 5)
Lunghezza: 5
Somma: 150

=== Confronto: array con diversi riempimenti ===
Stato iniziale  : [ 5 12 8 ] (tappo in posizione 3)
Somma: 25

Dopo aggiunta 25: [ 5 12 8 25 ] (tappo in posizione 4)
Somma: 50

=== Collegamento con le stringhe C ===
Stringa come array di char con tappo '\0':
  parola[0] = 'c'  (ASCII 99)
  parola[1] = 'i'  (ASCII 105)
  parola[2] = 'a'  (ASCII 97)
  parola[3] = 'o'  (ASCII 111)
  parola[4] = '\0' (ASCII 0) <- tappo
Lunghezza: 4 caratteri
```

### 020-operazioni-con-tappo
```
=== OPERAZIONI SU ARRAY A TAPPO ===

Array iniziale : [ 7 3 15 9 22 5 ]
Lunghezza      : 6 elementi

Ricerca 9: trovato in posizione 3
Ricerca 99: non trovato

Inserimento di 42 in fondo:
  OK -> [ 7 3 15 9 22 5 42 ]

Rimozione dell'elemento in posizione 2 (valore 15):
  OK -> [ 7 3 9 22 5 42 ]

Riempimento progressivo di un array vuoto:
  Dopo inserimento 10: [ 10 ]
  Dopo inserimento 20: [ 10 20 ]
  Dopo inserimento 30: [ 10 20 30 ]
  Dopo inserimento 40: [ 10 20 30 40 ]
  Dopo inserimento 50: [ 10 20 30 40 50 ]
```

### 030-tappo-su-array-di-char
```
=== ARRAY DI CHAR CON TAPPO '\0' ===

Struttura di "ciao" in memoria:
  Indice | Char | ASCII
  -------|------|------
    0    |  c   |   99
    1    |  i   |  105
    2    |  a   |   97
    3    |  o   |  111
    4    |  \0  |    0  <- tappo

lunghezza_stringa("programmazione") = 14
lunghezza_stringa("C")             = 1

copia_stringa: "programmazione" -> "programmazione"

confronta("mela", "mela") = 0  (uguali)
confronta("mela", "pera") = -3  (diverse)

Dopo concatena: "linguaggio C"

Prima inversione : "abcdef"
Dopo inversione  : "fedcba"

=== CONFRONTO TAPPI ===
  Array int a tappo : while (arr[i] != -1)  { ... i++; }
  Stringa C         : while (str[i] != '\0') { ... i++; }
  Stesso pattern, tappo diverso.
```

### 040-problema-lista-della-spesa
```
=== LISTA DELLA SPESA ===

Lista attuale:
  N. | Prezzo
  ---|--------
   1 |   1,49 euro
   2 |   2,99 euro
   3 |   0,89 euro
   4 |   4,50 euro
   5 |   1,99 euro

Articoli     : 5
Totale       : 11,86 euro
Articolo piu' caro: n.4 (4,50 euro)

Aggiunta articolo da 2,50 euro (250 centesimi):
  OK -> ora 6 articoli
Aggiunta articolo da 0,75 euro (75 centesimi):
  OK -> ora 7 articoli

Lista aggiornata:
  N. | Prezzo
  ---|--------
   1 |   1,49 euro
   2 |   2,99 euro
   3 |   0,89 euro
   4 |   4,50 euro
   5 |   1,99 euro
   6 |   2,50 euro
   7 |   0,75 euro

Nuovo totale : 15,11 euro
```

### 050-problema-log-eventi
```
=== ANALISI LOG DI SISTEMA ===

  Pos. | Codice | Categoria
  -----|--------|----------
    1  |  101   | INFO   
    2  |  102   | INFO   
    3  |  201   | WARNING
    4  |  103   | INFO   
    5  |  301   | ERROR  
    6  |  202   | WARNING
    7  |  104   | INFO   
    8  |  302   | ERROR  
    9  |  105   | INFO   
   10  |  203   | WARNING
   11  |  303   | ERROR  
   12  |  106   | INFO   

Totale eventi : 12
INFO          : 6  (50%)
WARNING       : 3  (25%)
ERROR         : 3  (25%)

Ultimo ERROR  : posizione 11, codice 303
Ultimo WARNING: posizione 10, codice 203

CRITICO: errori superiori al 20% del log.
```

### 060-problema-coda-prenotazioni
```
=== CODA PRENOTAZIONI MEDICHE ===

Stato iniziale (4 prenotazioni):
  Pos. | ID paz. | Orario
  -----|---------|-------
    1  |   1042  | 09:00
    2  |   2387  | 09:30
    3  |   1905  | 10:00
    4  |   3201  | 10:30

Aggiunta paziente 4455 alle 11:00 (660 minuti):
  OK -> 5 prenotazioni in coda

Paziente 1042 visitato - rimozione dalla coda:
  OK -> 4 prenotazioni rimanenti

Stato finale:
  Pos. | ID paz. | Orario
  -----|---------|-------
    1  |   2387  | 09:30
    2  |   1905  | 10:00
    3  |   3201  | 10:30
    4  |   4455  | 11:00
```

### 070-problema-sensori-attivi
```
=== REGISTRO SENSORI ATTIVI ===

Stato iniziale (4 sensori):
  ID    | Lettura
  ------|--------
  S101  |  23.5 °C
  S102  |  31.2 °C
  S103  |  19.8 °C
  S105  |  28.4 °C
Media letture: 25.7 °C

Aggiunta sensore S104 (lettura 25.0 °C):
  OK -> 5 sensori attivi

Aggiunta sensore S102 (gia' presente):
  RIFIUTATO: sensore gia' presente

Rimozione sensore S103:
  OK -> 4 sensori attivi

Stato finale:
  ID    | Lettura
  ------|--------
  S101  |  23.5 °C
  S102  |  31.2 °C
  S105  |  28.4 °C
  S104  |  25.0 °C
Media letture: 27.0 °C
```

### 080-problema-playlist-musicale
```
=== GESTIONE PLAYLIST ===

Playlist iniziale:
  N. | ID    | Durata
  ---|-------|-------
   1 |  1001 | 03:33
   2 |  1002 | 03:07
   3 |  1003 | 04:05
   4 |  1004 | 03:18
   5 |  1005 | 03:41
  Durata totale: 17:44
Brano piu' lungo: ID 1003 (245 secondi)

Inserimento brano 1006 (230 sec) in posizione 2:
  OK -> 6 brani in playlist

  N. | ID    | Durata
  ---|-------|-------
   1 |  1001 | 03:33
   2 |  1002 | 03:07
   3 |  1006 | 03:50
   4 |  1003 | 04:05
   5 |  1004 | 03:18
   6 |  1005 | 03:41
  Durata totale: 21:34

Rimozione brano 1003:
  OK -> 5 brani rimanenti

Playlist finale:
  N. | ID    | Durata
  ---|-------|-------
   1 |  1001 | 03:33
   2 |  1002 | 03:07
   3 |  1006 | 03:50
   4 |  1004 | 03:18
   5 |  1005 | 03:41
  Durata totale: 17:29
```

---

## Errori comuni da evitare

**Dimenticare di rimettere il tappo dopo un'aggiunta**
```c
arr[lunghezza] = nuovo;    /* il tappo è stato sovrascritto */
/* ERRORE: manca arr[lunghezza + 1] = TAPPO;
 * il prossimo scorrimento esce dai dati validi */
```

**Non lasciare spazio per il tappo**
```c
#define MAX 5
int arr[MAX] = {10, 20, 30, 40, 50};   /* ERRORE: nessuna cella per il tappo */
/* Con MAX celle si possono memorizzare al massimo MAX - 1 dati */
```

**Aggiungere senza controllare la capacità**
```c
arr[lunghezza] = nuovo;
arr[lunghezza + 1] = TAPPO;   /* ERRORE se lunghezza + 1 >= MAX: scrittura fuori array */
/* Corretto: aggiungere solo se lunghezza < MAX - 1 */
```

**Scegliere un tappo che può essere un dato valido**
```c
#define TAPPO 0
int temperature[MAX] = {12, 0, -3, TAPPO};   /* ERRORE: 0 °C è una lettura valida,
                                               * lo scorrimento si ferma al secondo dato */
```

**Shift nella direzione sbagliata durante l'inserimento**
```c
/* Inserimento in posizione p: ERRORE partire da sinistra */
for (i = p; i < lunghezza; i++) {
    arr[i + 1] = arr[i];   /* copia lo stesso valore in tutte le celle */
}
/* Corretto: partire dal tappo e scorrere verso p (da destra a sinistra) */
```

**Array paralleli con tappi disallineati**
```c
/* rimozione in testa eseguita solo su id[], non su orari[] */
/* ERRORE: da questo punto ID e orari non corrispondono più */
```

---

## Concetti collegati

- `02-accesso-e-scorrimento` → scorrimento con `while`
- `04-array-e-funzioni` → funzioni che ricevono la dimensione `n` (qui non serve)
- `03-stringhe/01-dichiarazione-e-inizializzazione` → la stringa come array di `char` terminato da `'\0'`
- `03-stringhe/03-lunghezza-e-accesso-ai-caratteri` → scorrimento di una stringa fino al terminatore
- `10-strutture-dati/03-code-queue` → la coda FIFO realizzata con strutture dinamiche

---

## Esercizi proposti

1. Scrivi una funzione che conti gli elementi pari di un array a tappo di interi
   non negativi, senza ricevere la dimensione come parametro.

2. Aggiungi a `020-operazioni-con-tappo.c` la rimozione di **tutte** le
   occorrenze di un valore, compattando l'array e spostando il tappo.

3. Modifica `040-problema-lista-della-spesa.c` per rifiutare l'aggiunta di un
   articolo quando la lista è piena, stampando un messaggio di errore.

4. Estendi `060-problema-coda-prenotazioni.c` con una funzione che rinvia di
   30 minuti tutte le prenotazioni successive a un orario dato.

5. (Avanzato) Scrivi una funzione che, dati due array a tappo già ordinati,
   costruisca un terzo array a tappo ordinato con tutti gli elementi di entrambi.
