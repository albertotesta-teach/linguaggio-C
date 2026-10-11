# 04 – Array e funzioni

## Concetto

Un array si passa a una funzione scrivendo il suo nome come argomento. A
differenza delle variabili scalari, **l'array non viene copiato**: la funzione
riceve l'indirizzo del primo elemento e lavora sulla memoria del chiamante.

```
  main                          funzione raddoppia(int arr[], int n)
  ┌─────────────────────┐
  │ valori: 3 7 1 9 4 6 │◄──────── arr punta qui: stessi dati, nessuna copia
  └─────────────────────┘
```

### Conseguenze pratiche

| Aspetto | Variabile scalare | Array |
|---------|-------------------|-------|
| Cosa riceve la funzione | una copia del valore | l'indirizzo del primo elemento |
| Le modifiche si vedono nel chiamante? | no | **sì** |
| Dimensione disponibile nella funzione | — | **no**: va passata come parametro `n` |

### La dimensione va sempre passata

Dentro la funzione `sizeof(arr)` restituisce la dimensione di un indirizzo
(tipicamente 8 byte), non quella dell'array. Per questo ogni funzione riceve
anche il numero di elementi:

```c
int somma(const int arr[], int n);
```

### Il qualificatore `const`

Una funzione che **legge** soltanto l'array dichiara il parametro `const`:
il compilatore segnala come errore qualsiasi tentativo di modificarlo e chi
legge il prototipo sa subito che i dati non verranno toccati.

```c
void stampa(const int arr[], int n);   /* sola lettura */
void raddoppia(int arr[], int n);      /* modifica in-place */
```

### Tre famiglie di funzioni su array

- **Aggregate**: restituiscono un valore calcolato (somma, media, indice del massimo).
- **Trasformazioni**: modificano l'array in-place (valore assoluto, inversione, azzeramento).
- **Costruttrici**: riempiono un array di output a partire da uno di input (copia, normalizzazione).

Il `main` coordina le chiamate e presenta i risultati; le funzioni non stampano
nulla se il loro compito è calcolare.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-passaggio-array-a-funzione.c` | Array modificato dalla funzione e scalare invariato; `sizeof` nel `main` e nella funzione; passaggio di una porzione con `&valori[i]` |
| `020-funzioni-su-array.c` | Funzioni aggregate: somma, media, indice di massimo e minimo, conteggio sopra soglia, ricerca |
| `030-funzioni-che-modificano-array.c` | Funzioni di trasformazione: valore assoluto, inversione, somma di una costante, azzeramento, copia, scarto dalla media |
| `040-problema-normalizzazione-misure.c` | Misure di tensione normalizzate in [0, 1], scarto dal valore atteso, misure fuori tolleranza |
| `040-problema-normalizzazione-misure-analisi.md` | Analisi di `040-problema-normalizzazione-misure.c` |
| `050-problema-cifrario-cesare.c` | Cifratura e decifratura in-place di un array di `char` con aritmetica modulare |
| `050-problema-cifrario-cesare-analisi.md` | Analisi di `050-problema-cifrario-cesare.c` |
| `060-problema-gestione-magazzino.c` | Ricerca per codice (indice o -1), carico e scarico, prospetto e giacenza totale |
| `060-problema-gestione-magazzino-analisi.md` | Analisi di `060-problema-gestione-magazzino.c` |
| `070-problema-analisi-partita.c` | Statistiche marcatori: totale, media, capocannoniere, classifica top 5 |
| `070-problema-analisi-partita-analisi.md` | Analisi di `070-problema-analisi-partita.c` |
| `080-problema-registro-presenze.c` | Percentuali di presenza, dipendente più e meno presente, avvisi sotto soglia 80% |
| `080-problema-registro-presenze-analisi.md` | Analisi di `080-problema-registro-presenze.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-passaggio-array-a-funzione 010-passaggio-array-a-funzione.c
./010-passaggio-array-a-funzione

gcc -Wall -Wextra -o 020-funzioni-su-array 020-funzioni-su-array.c
./020-funzioni-su-array

gcc -Wall -Wextra -o 030-funzioni-che-modificano-array 030-funzioni-che-modificano-array.c
./030-funzioni-che-modificano-array

gcc -Wall -Wextra -o 040-problema-normalizzazione-misure 040-problema-normalizzazione-misure.c
./040-problema-normalizzazione-misure

gcc -Wall -Wextra -o 050-problema-cifrario-cesare 050-problema-cifrario-cesare.c
./050-problema-cifrario-cesare

gcc -Wall -Wextra -o 060-problema-gestione-magazzino 060-problema-gestione-magazzino.c
./060-problema-gestione-magazzino

gcc -Wall -Wextra -o 070-problema-analisi-partita 070-problema-analisi-partita.c
./070-problema-analisi-partita

gcc -Wall -Wextra -o 080-problema-registro-presenze 080-problema-registro-presenze.c
./080-problema-registro-presenze
```


---

## Output atteso

Nessun programma richiede input: l'output è sempre lo stesso. Il valore
`8 byte` di `010-passaggio-array-a-funzione` vale per i sistemi a 64 bit.

### 010-passaggio-array-a-funzione
```
=== Passaggio per riferimento (array) ===
Prima di raddoppia(): [ 3 7 1 9 4 6 ]
Dopo  raddoppia(): [ 6 14 2 18 8 12 ]

=== Passaggio per valore (scalare) ===
Prima di tenta_modifica_scalare(): scalare = 42
Dentro la funzione:             x       = 999  (copia modificata)
Dopo  tenta_modifica_scalare(): scalare = 42  (invariato)

=== Dimensione dell'array ===
  sizeof(valori) nel main: 24 byte (6 elementi)
  n ricevuto come parametro : 6 elementi
  sizeof(&arr[0]) nella funzione: 8 byte (dimensione di un indirizzo)

=== Passaggio di una porzione dell'array ===
Ultimi 3 elementi: [ 18 8 12 ]
```

### 020-funzioni-su-array
```
Array:
  arr[0] = 14
  arr[1] = 7
  arr[2] = 23
  arr[3] = 5
  arr[4] = 18
  arr[5] = 23
  arr[6] = 9
  arr[7] = 31

Somma              : 130
Media              : 16.25
Massimo            : 31  (posizione 7)
Minimo             : 5  (posizione 3)
Elementi > 15      : 4
Valore 23 trovato  : posizione 2
Valore 99          : non presente
```

### 030-funzioni-che-modificano-array
```
Originale        : [    3  -5   8  -2  11  -7   4   6 ]
Valore assoluto  : [    3   5   8   2  11   7   4   6 ]
Invertito        : [    6   4  -7  11  -2   8  -5   3 ]
Somma +10        : [   13   5  18   8  21   3  14  16 ]
Azzerato         : [    0   0   0   0   0   0   0   0 ]
Originale (dopo) : [    3  -5   8  -2  11  -7   4   6 ]
Copia modificata : [  999  -5   8  -2  11  -7   4   6 ]

Media originale: 2.25
Scarto da media  : [    1   7   6   4   9   9   2   4 ]
```

### 040-problema-normalizzazione-misure
```
=== ANALISI MISURAZIONI TENSIONE ===

  Mis. | Originale | Normaliz. | Scarto da 4.5V
  -----|-----------|-----------|----------------
    1  |   3.210 V |  0.6270   |   1.290 V
    2  |   4.850 V |  0.9473   |   0.350 V
    3  |   2.970 V |  0.5801   |   1.530 V
    4  |   5.120 V |  1.0000   |   0.620 V
    5  |   4.430 V |  0.8652   |   0.070 V
    6  |   3.760 V |  0.7344   |   0.740 V
    7  |   5.000 V |  0.9766   |   0.500 V
    8  |   4.180 V |  0.8164   |   0.320 V

Tensione massima   : 5.120 V
Tensione media     : 4.190 V
Valore atteso      : 4.500 V
Scarto medio       : 0.677 V

Misure fuori tolleranza (scarto > 0.5 V): 4 su 8
```

### 050-problema-cifrario-cesare
```
=== CIFRARIO DI CESARE (spostamento: 3) ===

Messaggio originale  : Veni Vidi Vici
Lunghezza            : 14 caratteri (12 lettere)

Messaggio cifrato    : Yhql Ylgl Ylfl
Messaggio decifrato  : Veni Vidi Vici

Secondo messaggio: "Attacco all alba"

  Chiave 1: Buubddp bmm bmcb
  Chiave 2: Cvvceeq cnn cndc
  Chiave 3: Dwwdffr doo doed
  Chiave 4: Exxeggs epp epfe
  Chiave 5: Fyyfhht fqq fqgf
```

### 060-problema-gestione-magazzino
```
=== GESTIONE MAGAZZINO ===

--- Stato iniziale ---
  Cod.  | Prodotto           | Qty
  ------|--------------------|---------
  1001  | Vite M4x10         |   500
  1002  | Dado M4            |   480
  1003  | Rondella M4        |   600
  1004  | Vite M6x20         |   320
  1005  | Dado M6            |   310
  1006  | Rondella M6        |   400
  Giacenza totale: 2610 pezzi

Operazione: carico +200 di codice 1003
  OK: Rondella M4 -> nuova quantita': 800

Operazione: scarico -150 di codice 1005
  OK: Dado M6 -> nuova quantita': 160

Operazione: ricerca codice 9999 (inesistente)
  ERRORE: prodotto non trovato

--- Stato finale ---
  Cod.  | Prodotto           | Qty
  ------|--------------------|---------
  1001  | Vite M4x10         |   500
  1002  | Dado M4            |   480
  1003  | Rondella M4        |   800
  1004  | Vite M6x20         |   320
  1005  | Dado M6            |   160
  1006  | Rondella M6        |   400
  Giacenza totale: 2660 pezzi
```

### 070-problema-analisi-partita
```
=== ANALISI MARCATORI STAGIONE ===

Capocannoniere      : Verdi Paolo (15 gol)
Totale gol squadra  : 69
Media per giocatore : 8.6
Giocatori > 8 gol   : 4 su 8

--- Classifica marcatori (top 5) ---
  Pos. | Giocatore          | Gol
  -----|--------------------|---------
    1  | Verdi Paolo        |  15
    2  | Rossi Marco        |  12
    3  | Conti Matteo       |  11
    4  | Russo Andrea       |   9
    5  | Greco Simone       |   8
```

### 080-problema-registro-presenze
```
=== REGISTRO PRESENZE MENSILE ===
Giorni lavorativi: 22 | Soglia: 80%

  Dipendente       | Giorni | Perc.  | Stato
  -----------------|--------|--------|----------
  Rossi Anna       |   22   | 100.0% | REGOLARE
  Bianchi Carlo    |   18   |  81.8% | REGOLARE
  Verdi Elena      |   20   |  90.9% | REGOLARE
  Ferrari Marco    |   15   |  68.2% | ATTENZIONE
  Russo Giulia     |   21   |  95.5% | REGOLARE
  Conti Pietro     |   17   |  77.3% | ATTENZIONE

Piu' presente   : Rossi Anna (22 gg - 100.0%)
Meno presente   : Ferrari Marco (15 gg - 68.2%)
Sotto soglia    : 2 dipendenti su 6
```

---

## Errori comuni da evitare

**Calcolare la dimensione con `sizeof` dentro la funzione**
```c
int somma(int arr[]) {
    int n = sizeof(arr) / sizeof(arr[0]);   /* ERRORE: sizeof(arr) è la dimensione
                                              * di un indirizzo, non dell'array */
    ...
}
/* Corretto: int somma(const int arr[], int n) */
```

**Passare l'array con le parentesi quadre**
```c
stampa(valori[], 6);    /* ERRORE di sintassi */
stampa(valori[6], 6);   /* ERRORE: passa un singolo int (e fuori range) */
stampa(valori, 6);      /* corretto */
```

**Aspettarsi che la funzione lavori su una copia**
```c
void azzera(int arr[], int n) { ... }

azzera(valori, 6);
/* valori ora contiene solo zeri: l'originale è perso.
 * Se serve conservarlo, copiarlo prima in un secondo array. */
```

**Restituire un array locale**
```c
int[] crea(void) {        /* ERRORE: una funzione non può restituire un array */
    int risultato[5];
    ...
}
/* Corretto: il chiamante dichiara l'array e lo passa come parametro di output */
void crea(int risultato[], int n);
```

**Ricerca che usa più `return` o `break`**
```c
int cerca(const int arr[], int n, int x) {
    for (i = 0; i < n; i++) {
        if (arr[i] == x) return i;   /* vietato dalle convenzioni del corso */
    }
    return -1;
}
/* Corretto: variabile posizione = -1, ciclo con condizione
 * (i < n && posizione == -1), una sola return finale */
```

---

## Concetti collegati

- `03-funzioni/02-parametri-e-return` → passaggio per valore degli scalari
- `03-funzioni/03-passaggio-per-riferimento` → indirizzi e modifica dei dati del chiamante
- `03-operazioni-su-array` → gli stessi algoritmi scritti direttamente nel `main`
- `05-array-a-tappo` → funzioni su array che non ricevono la dimensione `n`
- `05-puntatori/02-puntatori-e-array` → perché un array passato a funzione è un indirizzo

---

## Esercizi proposti

1. Scrivi la funzione `int conta_pari(const int arr[], int n)` e usala per
   contare gli elementi pari di due array di dimensioni diverse.

2. Aggiungi a `030-funzioni-che-modificano-array.c` la funzione
   `void ruota_a_destra(int arr[], int n)`, che sposta ogni elemento di una
   posizione verso destra e porta l'ultimo in prima posizione.

3. Modifica `050-problema-cifrario-cesare.c` per gestire anche le cifre
   (da '0' a '9' con avvolgimento circolare), lasciando invariati gli altri caratteri.

4. Estendi `060-problema-gestione-magazzino.c` con una funzione che rifiuta
   uno scarico se la quantità richiesta supera la giacenza e lo segnala al `main`
   tramite un valore di ritorno.

5. (Avanzato) Scrivi una funzione `void unisci(const int a[], int na,
   const int b[], int nb, int risultato[])` che, dati due array già ordinati,
   costruisca un terzo array ordinato con tutti gli elementi.
