# Analisi – 040-problema-semaforo.c

## 1. Problema

Il semaforo pedonale davanti alla scuola ripete il ciclo verde, giallo,
rosso. Il programma legge un istante t in secondi e stampa tutti i cambi
di colore da 0 a t, il colore all'istante t e quanto manca al cambio
successivo. Il colore è un `enum` e le durate stanno in un array
indicizzato dal colore.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `t` | `int` | Istante in secondi, da 1 a 600 |

### Output

- Una riga `S s  COLORE` per ogni cambio da 0 a t (compreso).
- `A t s il semaforo e' COLORE: cambia tra N s.`
- `Istante non valido.`

### Vincoli

- `typedef enum { VERDE, GIALLO, ROSSO, NUM_COLORI } Colore;`:
  `NUM_COLORI` vale 3 e dimensiona gli array.
- Durate: verde 40 s, giallo 5 s, rosso 45 s (ciclo di 90 s); gli array
  usano inizializzatori designati (`[VERDE] = 40`).
- Colore successivo: `(colore + 1) % NUM_COLORI`.
- All'istante esatto di un cambio vale già il nuovo colore.

### Assunzioni

- A t = 0 il semaforo diventa verde.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Colore` | `typedef enum { VERDE, GIALLO, ROSSO, NUM_COLORI } Colore;` | Colore del semaforo |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `nomi` | `const char *[3]` | Nomi indicizzati dal colore |
| `durata` | `int[3]` | Durate indicizzate dal colore |
| `colore` | `Colore` | Colore corrente |
| `inizio` | `int` | Istante di inizio del colore corrente |
| `MASSIMO` | `#define` | 600 secondi |

### Algoritmo in linguaggio naturale

1. Leggere t; se fuori intervallo segnalarlo.
2. Stampare il verde a 0 s.
3. Finché il colore corrente termina entro t: avanzare `inizio` della sua
   durata, passare al colore successivo e stampare il cambio.
4. Stampare il colore a t e i secondi mancanti
   (`inizio + durata[colore] − t`).

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Secondo ciclo

- **Input:** `100`
- **Output atteso:**
  ```
  Istante (secondi, da 1 a 600):     0 s  VERDE
     40 s  GIALLO
     45 s  ROSSO
     90 s  VERDE
  A 100 s il semaforo e' VERDE: cambia tra 30 s.
  ```

### Test 2 – Istante di un cambio

- **Input:** `40`; poi `90`
- **Output atteso:** `A 40 s il semaforo e' GIALLO: cambia tra 5 s.`;
  `A 90 s il semaforo e' VERDE: cambia tra 40 s.`

### Test 3 – Primo secondo

- **Input:** `1`
- **Output atteso:** solo `0 s  VERDE` e
  `A 1 s il semaforo e' VERDE: cambia tra 39 s.`

### Test 4 – Istante non valido

- **Input:** `0` (poi `601`, `abc`)
- **Output atteso:** `Istante non valido.`
