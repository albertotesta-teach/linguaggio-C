# Analisi – 050-problema-testo-che-si-allunga.c

## 1. Problema

Il segretario scrive il verbale del consiglio di classe una frase per
riga. Il verbale è un unico blocco che a ogni frase si allunga con
`realloc` esattamente della lunghezza della frase, più lo spazio di
separazione; le frasi senza punto finale lo ricevono. Alla fine il verbale
si stampa a righe di al massimo 60 caratteri senza spezzare le parole.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `frase` | `char[200]` | Una frase per riga; `FINE` termina |

### Output

- `blocco di B byte` dopo ogni frase aggiunta.
- `VERBALE (F frasi, C caratteri)` e il testo a righe di al massimo 60
  caratteri.
- `Memoria insufficiente...` se un'allocazione fallisce.

### Vincoli

- Il verbale parte da un blocco di 1 byte (stringa vuota).
- Nuova dimensione: lunghezza attuale + spazio (dalla seconda frase) +
  lunghezza della frase + terminatore; `realloc` in un puntatore
  temporaneo: se fallisce il verbale resta quello di prima.
- Le righe vuote si ignorano; una frase senza punto lo riceve.
- Una riga più lunga del buffer viene troncata e il resto scartato. A fine
  input il programma termina come con `FINE`.
- A capo prima della parola che farebbe superare 60 colonne.

### Assunzioni

- Nessuna parola supera i 60 caratteri.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `verbale`, `tmp` | `char *` | Blocco del verbale e risultato di `realloc` |
| `frase` | `char[200]` | Riga letta (con un byte libero per il punto) |
| `lunghezza`, `nuova` | `size_t` | Lunghezze |
| `frasi` | `int` | Frasi aggiunte |
| `resto` | `int` | Caratteri scartati di una riga lunga |

| Funzione | Compito |
|----------|---------|
| `stampa_a_righe(testo, larghezza)` | Stampa senza spezzare le parole |

### Algoritmo in linguaggio naturale

1. Allocare un blocco con la stringa vuota.
2. Per ogni riga fino a `FINE`: se non vuota aggiungere il punto se
   manca, allungare il blocco con `realloc`, accodare spazio e frase,
   stampare la nuova dimensione.
3. Stampare il verbale a righe e liberare il blocco.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Tre frasi

- **Input:** `Il consiglio si riunisce alle ore 15`,
  `Sono presenti tutti i docenti.`, riga vuota,
  `Si discute del comportamento della classe durante la gita a Torino`,
  `FINE`
- **Valori intermedi attesi:** 0 + 37 + 1 = 38 byte; 37 + 1 + 30 + 1 =
  69; 68 + 1 + 67 + 1 = 137.
- **Output atteso:**
  ```
  Frasi del verbale (FINE per terminare):
    blocco di 38 byte
    blocco di 69 byte
    blocco di 137 byte

  VERBALE (3 frasi, 136 caratteri)
  Il consiglio si riunisce alle ore 15. Sono presenti tutti i
  docenti. Si discute del comportamento della classe durante
  la gita a Torino.
  ```

### Test 2 – Verbale vuoto

- **Input:** `FINE`
- **Output atteso:** `VERBALE (0 frasi, 0 caratteri)` e una riga vuota.
