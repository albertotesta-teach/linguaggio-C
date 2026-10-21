# Analisi – 060-problema-cerca-parola.c

## 1. Problema

Il rappresentante degli studenti vuole sapere quante volte alcune parole
compaiono in un articolo del regolamento d'istituto e dove compaiono la
prima volta, con un po' di testo intorno. La ricerca usa una versione di
`strstr` scritta a mano.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `articolo` | `const char *` | Testo dell'articolo 7 sul telefono (letterale stringa) |
| `cercate` | `char[4][16]` | `telefono`, `docente`, `divieto`, `intervallo` |

### Output

- Il testo dell'articolo.
- Per ogni parola: numero di occorrenze, posizione della prima e il
  contesto (fino a 12 caratteri prima e dopo) tra `...`; oppure
  `non presente`.

### Vincoli

- `trova` restituisce un puntatore alla prima occorrenza della parola nel
  testo, oppure `NULL`; il risultato si controlla prima di usarlo.
- `inizia_con` confronta carattere per carattere avanzando due puntatori.
- `conta` cerca le occorrenze successive ripartendo da `trovato + 1`.
- La posizione è `trovato − articolo`; il contesto parte 12 caratteri prima,
  ma non prima dell'inizio del testo (`da` non scende sotto 0), e si stampa
  con `%.*s` senza copiarlo; se la fine del contesto supera il testo,
  `printf` si ferma al `'\0'`.
- La ricerca distingue maiuscole e minuscole.

### Assunzioni

- Le parole cercate non sono vuote.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `trovato` | `const char *` | Prima occorrenza nel testo, `NULL` se assente |
| `posizione`, `da` | `int` | Indice dell'occorrenza e inizio del contesto |
| `n` | `int` | Numero di occorrenze |
| `CONTESTO` | `#define` | 12 caratteri |

| Funzione | Compito |
|----------|---------|
| `trova(testo, parola)` | Puntatore alla prima occorrenza, `NULL` se assente |
| `inizia_con(testo, parola)` | 1 se `testo` comincia con `parola` |
| `conta(testo, parola)` | Numero di occorrenze |

### Algoritmo in linguaggio naturale

1. Stampare l'articolo.
2. Per ogni parola:
   1. `trovato = trova(articolo, parola)`;
   2. se `NULL` stampare `non presente`;
   3. altrimenti calcolare posizione e inizio del contesto, contare le
      occorrenze e stampare numero, posizione e contesto.
3. In `trova`: avanzare `p` finché non si arriva alla fine del testo o il
   testo da `p` inizia con la parola.

## 3. Casi di test

### Test 1 – Parole del sorgente

- **Cosa si verifica:** più occorrenze, occorrenza unica, contesto che
  arriva alla fine del testo, parola assente.
- **Input:** nessuno.
- **Output atteso** (dopo il testo):
  ```
  "telefono": 3 volte, la prima in posizione 17: "...7 - Uso del telefono. Durante le..."
  "docente": 1 volta, la prima in posizione 130: "...ermesso del docente. In laborat..."
  "divieto": 1 volta, la prima in posizione 169: "...e lo stesso divieto...."
  "intervallo": non presente
  ```
