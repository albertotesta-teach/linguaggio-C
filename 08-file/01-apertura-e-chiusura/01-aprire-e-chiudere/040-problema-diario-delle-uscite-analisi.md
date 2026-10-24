# Analisi – 040-problema-diario-delle-uscite.c

## 1. Problema

Il coordinatore annota nel file `diario.txt` le uscite didattiche della
classe man mano che si svolgono, una riga `gg/mm meta` per uscita. Ogni
esecuzione aggiunge le nuove voci senza cancellare quelle già scritte, per
questo il file si apre in modalità `"a"`. Alla fine il programma rilegge il
diario e lo stampa con le righe numerate.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| riga | testo | `gg/mm meta`, una uscita per riga; la meta può contenere spazi |
| `FINE` | testo | Riga che termina l'inserimento (anche la fine dell'input) |
| `diario.txt` | file di testo | Diario delle esecuzioni precedenti, se esiste |

### Output

- Nel file `diario.txt`, in fondo, una riga `gg/mm meta` per ogni voce
  valida, con giorno e mese su due cifre.
- `  manca la meta: D` per una riga che contiene solo la data,
  `  data non valida: D` per una data inesistente o scritta male.
- `Voci aggiunte: N`, poi `Diario delle uscite:` con tutte le righe del
  file numerate (`  1. ...`).
- `Impossibile aprire diario.txt` su `stderr` se il file non si può aprire.

### Vincoli

- Il file si apre con `fopen("diario.txt", "a")`: se non esiste viene
  creato, se esiste si scrive in fondo. Con `"w"` ogni esecuzione
  cancellerebbe il diario.
- Si controlla che `fopen` non restituisca `NULL`; il file si chiude con
  `fclose` prima di riaprirlo in lettura con `"r"`.
- Ogni riga si legge con `fgets` (al massimo 99 caratteri) e si divide con
  `sscanf` in data (15 caratteri) e meta (59 caratteri, il resto si
  perde); il resto di una riga troppo lunga si scarta.
- La data deve essere `g/m` senza altri caratteri e il giorno deve
  esistere nel mese (29 febbraio compreso).
- `FINE` va scritto in maiuscolo; una riga vuota si ignora.

### Assunzioni

- Le voci arrivano in ordine di data; il programma non le ordina.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `diario` | `FILE *` | File aperto in `"a"` |
| `riga` | `char[100]` | Riga letta con `fgets` |
| `data`, `meta` | `char[16]`, `char[60]` | Le due parti della riga |
| `campi` | `int` | Parti trovate da `sscanf` (0, 1 o 2) |
| `giorno`, `mese`, `extra` | `int`, `int`, `char` | Data convertita; `extra` rileva caratteri dopo il mese |
| `resto` | `int` | Carattere scartato da una riga troppo lunga |
| `aggiunte` | `int` | Voci scritte in questa esecuzione |
| `finito` | `int` | 1 a FINE, a fine input o se il file non si apre |

| Funzione | Compito |
|----------|---------|
| `data_valida(giorno, mese)` | 1 se il giorno esiste nel mese |
| `stampa_numerata(nome)` | Riapre il file in `"r"` e lo stampa con le righe numerate; 0 se non si apre |

### Algoritmo in linguaggio naturale

1. Aprire `diario.txt` in `"a"`; se non si apre, segnalarlo e terminare.
2. Leggere una riga alla volta fino a `FINE` o alla fine dell'input,
   scartando il resto delle righe troppo lunghe.
3. Dividere la riga in data e meta: senza meta segnalarlo; con una data
   non valida segnalarlo; altrimenti scrivere la voce in fondo al file e
   contarla.
4. Chiudere il file, stampare il numero di voci aggiunte e rileggere il
   diario stampandolo con le righe numerate.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe). Si parte da una
cartella senza `diario.txt`; i test vanno eseguiti in ordine.

### Test 1 – Prima esecuzione

- **Cosa si verifica:** il file viene creato; una data inesistente viene
  scartata.
- **Input:** `12/10 Museo Egizio di Torino`, `31/11 Gita sul Po`,
  `03/11 Laboratorio di chimica all'universita'`, `FINE`
- **Valori intermedi attesi:** 31/11 non esiste (novembre ha 30 giorni);
  `aggiunte` = 2.
- **Output atteso:**
  ```
  Uscite (gg/mm meta, FINE per terminare):
    data non valida: 31/11
  Voci aggiunte: 2

  Diario delle uscite:
    1. 12/10 Museo Egizio di Torino
    2. 03/11 Laboratorio di chimica all'universita'
  ```
- **Procedura:** eseguire il programma in una cartella vuota.

### Test 2 – Seconda esecuzione: le voci si aggiungono

- **Cosa si verifica:** `"a"` non cancella le voci precedenti.
- **Input:** `20/11 Biblioteca civica`, `FINE`
- **Output atteso:**
  ```
  Uscite (gg/mm meta, FINE per terminare):
  Voci aggiunte: 1

  Diario delle uscite:
    1. 12/10 Museo Egizio di Torino
    2. 03/11 Laboratorio di chimica all'universita'
    3. 20/11 Biblioteca civica
  ```
- **Procedura:** rieseguire il programma nella stessa cartella.

### Test 3 – Righe scritte male

- **Cosa si verifica:** la meta mancante, i caratteri dopo la data, il
  31 aprile e `fine` in minuscolo vengono segnalati senza scrivere nulla.
- **Input:** `25/11`, riga vuota, `12/10x Gita`, `31/04 Gita`, `fine`, poi
  fine input
- **Output atteso:**
  ```
  Uscite (gg/mm meta, FINE per terminare):
    manca la meta: 25/11
    data non valida: 12/10x
    data non valida: 31/04
    manca la meta: fine
  Voci aggiunte: 0
  ```
  seguito dal diario di 3 righe.

### Test 4 – File non apribile

- **Cosa si verifica:** con `fopen` che restituisce `NULL` non si legge
  nessuna voce.
- **Input:** `FINE`, in una cartella senza permesso di scrittura
- **Output atteso:** `Impossibile aprire diario.txt` (su `stderr`).
