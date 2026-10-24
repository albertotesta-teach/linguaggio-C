# Analisi – 080-problema-copia-di-una-stringa.c

## 1. Problema

La segreteria scrive i nomi dei diplomati in modo disordinato. Il
programma li normalizza (spazi singoli, iniziali maiuscole) e conserva ogni
nome in un blocco dello heap lungo esattamente `strlen + 1` byte,
raggiunto da un array di puntatori. Alla fine stampa l'elenco, confronta i
byte usati con quelli di una matrice di righe da 80 caratteri e libera i
blocchi uno per uno.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[80]` | Un nome per riga; `FINE` termina |

### Output

- `Elenco per i diplomi:` con i nomi normalizzati numerati e i byte di
  ogni blocco.
- `Byte nello heap: B (con una matrice char[n][80]: M)`.
- `Memoria insufficiente.` se un'allocazione fallisce.

### Vincoli

- Ogni copia: `malloc((strlen(riga) + 1) * sizeof *copia)`, controllo di
  `NULL`, `strcpy`; alla fine un `free` per ogni blocco.
- Normalizzazione nello stesso array: spazi iniziali, finali e ripetuti
  eliminati, prima lettera di ogni parola maiuscola, le altre minuscole.
- Righe vuote (o di soli spazi) non vengono memorizzate.
- Al massimo 50 nomi; una riga più lunga di 79 caratteri viene troncata e
  il resto scartato. A fine input il programma termina come con `FINE`.

### Assunzioni

- I nomi non contengono lettere accentate.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `elenco` | `char *[50]` | Puntatori ai blocchi |
| `riga` | `char[80]` | Riga letta |
| `copia` | `char *` | Nuovo blocco |
| `byte_usati` | `size_t` | Somma delle dimensioni dei blocchi |
| `resto` | `int` | Caratteri scartati di una riga lunga |

| Funzione | Compito |
|----------|---------|
| `normalizza(testo)` | Sistema spazi e maiuscole nello stesso array |

### Algoritmo in linguaggio naturale

1. Finché non si termina e c'è posto: leggere una riga, scartare il resto
   se troppo lunga; con `FINE` terminare; normalizzarla; se non è vuota
   allocare un blocco della lunghezza giusta, copiarla e memorizzare il
   puntatore.
2. Stampare l'elenco e il confronto dei byte.
3. Liberare tutti i blocchi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Nomi disordinati

- **Input:** `  mario   ROSSI `, `ANNA maria   bianchi`, riga vuota,
  riga di soli spazi, `lUCA verdi`, `FINE`
- **Valori intermedi attesi:** "Mario Rossi" 11 caratteri → 12 byte.
- **Output atteso:**
  ```
  Nomi dei diplomati (FINE per terminare):

  Elenco per i diplomi:
     1. Mario Rossi              (12 byte)
     2. Anna Maria Bianchi       (19 byte)
     3. Luca Verdi               (11 byte)
  Byte nello heap: 42 (con una matrice char[3][80]: 240)
  ```

### Test 2 – Riga troppo lunga

- **Input:** una riga di 90 cifre, `FINE`
- **Output atteso:** un solo nome di 79 caratteri (80 byte): il resto
  della riga non diventa un secondo nome.
