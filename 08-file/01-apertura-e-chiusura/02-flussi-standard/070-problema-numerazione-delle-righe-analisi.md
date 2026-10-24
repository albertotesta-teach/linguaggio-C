# Analisi – 070-problema-numerazione-delle-righe.c

## 1. Problema

Per discutere in classe un testo serve poter citare le righe. Il filtro
copia `stdin` su `stdout` mettendo il numero davanti a ogni riga non
vuota; le righe vuote restano vuote e non consumano un numero. Il totale
va su `stderr`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| testo | flusso `stdin` | Qualunque testo, fino alla fine dell'input |

### Output

- Su `stdout` il testo con `%4d` e due spazi davanti a ogni riga non
  vuota.
- Su `stderr`: `[numerazione] righe numerate: N, righe vuote: V`.

### Vincoli

- Lettura con `fgetc(stdin)` fino a `EOF`, scrittura con `fputc` su
  `stdout`.
- Una riga è vuota se il suo primo carattere è l'a capo; una riga di soli
  spazi si numera.
- Il numero si stampa all'inizio di ogni riga non vuota, anche l'ultima
  senza a capo.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `c` | `int` | Carattere letto, può valere `EOF` |
| `inizio_riga` | `int` | 1 se il prossimo carattere apre una riga |
| `numero`, `vuote` | `int` | Righe numerate e righe vuote |

### Algoritmo in linguaggio naturale

1. Leggere un carattere alla volta fino a `EOF`.
2. All'inizio di una riga: se il carattere non è un a capo, aumentare il
   numero e stamparlo; altrimenti contare una riga vuota.
3. Copiare il carattere e ricordare se era un a capo.
4. A fine input stampare il totale su `stderr`.

## 3. Casi di test

### Test 1 – Una strofa con una riga vuota

- **Input:** `Nel mezzo del cammin di nostra vita`, riga vuota,
  `mi ritrovai per una selva oscura,`,
  `che' la diritta via era smarrita.`
- **Output atteso:**
  ```
     1  Nel mezzo del cammin di nostra vita

     2  mi ritrovai per una selva oscura,
     3  che' la diritta via era smarrita.
  [numerazione] righe numerate: 3, righe vuote: 1
  ```

### Test 2 – Redirezione con stderr scartato

- **Input:** `saluto.txt` creato da `01-aprire-e-chiudere/010`
- **Output atteso:**
  ```
     1  Benvenuti al corso di C!
     2  Lezione 1: apertura e chiusura dei file.
  ```
- **Procedura:** `./070-problema-numerazione-delle-righe < saluto.txt
  2> /dev/null`: il totale non compare.

### Test 3 – Input vuoto

- **Input:** nessun carattere
- **Output atteso:** `[numerazione] righe numerate: 0, righe vuote: 0`
