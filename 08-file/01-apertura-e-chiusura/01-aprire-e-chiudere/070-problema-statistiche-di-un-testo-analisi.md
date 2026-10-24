# Analisi – 070-problema-statistiche-di-un-testo.c

## 1. Problema

Prima di consegnare la relazione di laboratorio gli studenti controllano
il testo. Il programma legge il file una sola volta, carattere per
carattere, e conta lettere, cifre, spazi, altri caratteri e righe; trova
la riga più lunga e dice quante righe superano gli 80 caratteri.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `nome` | testo | Nome del file, senza spazi, fino a 59 caratteri |
| file | file di testo | Testo da analizzare |

### Output

- `Statistiche di NOME` con i conteggi di lettere, cifre, spazi, altri
  caratteri e righe, incolonnati su 6 cifre.
- `riga piu' lunga: la R, con L caratteri` (solo se il file ha almeno una
  riga) e `righe oltre 80 caratteri: K`.
- `Impossibile leggere "NOME"` su `stderr`.

### Vincoli

- Il file si legge una sola volta con `fgetc`, fino a `EOF`.
- L'a capo chiude una riga e non si conta tra i caratteri; un'ultima
  riga senza a capo si conta lo stesso.
- Lettere e cifre si riconoscono con `isalpha` e `isdigit`; spazi sono
  `' '` e `'\t'`; tutto il resto è "altro".
- A parità di lunghezza resta la prima riga più lunga; "oltre 80" vuol
  dire più di 80 caratteri.

### Assunzioni

- Il testo è ASCII: una lettera accentata in UTF-8 occupa due byte e
  viene contata tra gli altri caratteri.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `f` | `FILE *` | File aperto in `"r"` |
| `c` | `int` | Carattere letto, può valere `EOF` |
| `lettere`, `cifre`, `spazi`, `altri`, `righe` | `int` | Contatori |
| `lunghezza` | `int` | Caratteri della riga in corso |
| `massima`, `riga_massima` | `int` | Riga più lunga trovata finora |
| `troppo_lunghe` | `int` | Righe oltre il limite |
| `LIMITE` | `#define` | 80 |

### Algoritmo in linguaggio naturale

1. Leggere il nome e aprire il file; se non si apre, segnalarlo.
2. Per ogni carattere: se è un a capo, chiudere la riga (contarla,
   aggiornare la più lunga e quelle oltre il limite, azzerare la
   lunghezza); altrimenti aumentare la lunghezza e il contatore della sua
   categoria.
3. A fine file chiudere l'eventuale ultima riga senza a capo.
4. Stampare le statistiche.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Statistiche del diario

- **Cosa si verifica:** i conteggi sul `diario.txt` di 3 righe prodotto
  da `040`.
- **Input:** `diario.txt`
- **Valori intermedi attesi:** righe di 28, 44 e 23 caratteri; la più
  lunga è la seconda.
- **Output atteso:**
  ```
  File da analizzare: Statistiche di diario.txt
    lettere              68
    cifre                12
    spazi                10
    altri caratteri       5
    righe                 3
    riga piu' lunga: la 2, con 44 caratteri
    righe oltre 80 caratteri: 0
  ```

### Test 2 – Ultima riga senza a capo

- **Input:** `senza-a-capo.txt` (`riga uno`, a capo, `riga due`)
- **Output atteso:** lettere 14, spazi 2, righe 2,
  `riga piu' lunga: la 1, con 8 caratteri`.

### Test 3 – File vuoto

- **Input:** un file `vuoto.txt` di 0 byte
- **Output atteso:** tutti i conteggi a 0, nessuna riga "piu' lunga",
  `righe oltre 80 caratteri: 0`.

### Test 4 – File mancante

- **Input:** `nessuno.txt`
- **Output atteso:** `Impossibile leggere "nessuno.txt"` (su `stderr`).
