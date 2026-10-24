# Analisi – 060-problema-unione-di-file.c

## 1. Problema

La segreteria vuole un unico file con gli elenchi di tutte le classi. Il
programma crea il file di destinazione e vi copia, uno alla volta, i file
indicati fino a FINE, ciascuno preceduto da un'intestazione. Salta con un
avviso i file mancanti e il file di destinazione stesso, e aggiunge l'a
capo finale ai file che non lo hanno.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `nome_destinazione` | testo | File da creare, fino a 59 caratteri |
| `nome` | testo | File da unire, uno alla volta, fino a `FINE` o alla fine dell'input |

### Output

- Il file di destinazione: per ogni file unito `=== NOME ===` e il suo
  contenuto.
- `  aggiunto NOME` per ogni file unito.
- Su `stderr`: `  NOME non trovato: saltato`,
  `  NOME e' il file di destinazione: saltato`,
  `Impossibile creare NOME`.
- `DEST: file uniti U, mancanti M, caratteri copiati C`, poi il contenuto
  del file di destinazione.

### Vincoli

- La destinazione si apre una volta in `"w"` e resta aperta; ogni file da
  unire si apre in `"r"` e si chiude subito dopo la copia: aperti insieme
  ci sono al massimo due file.
- La destinazione non si può unire a se stessa: si leggerebbe un file
  mentre ci si scrive.
- Se l'ultimo carattere copiato non è un a capo se ne aggiunge uno, così
  l'intestazione successiva inizia su una riga nuova.
- I caratteri copiati non comprendono intestazioni e a capo aggiunti.

### Assunzioni

- Due nomi diversi indicano file diversi.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `destinazione`, `origine` | `FILE *` | File di uscita e file in copia |
| `c`, `ultimo` | `int` | Carattere copiato e ultimo carattere del file |
| `uniti`, `mancanti`, `caratteri` | `int` | Contatori del riepilogo |
| `finito` | `int` | 1 a FINE, a fine input o se la destinazione non si crea |

| Funzione | Compito |
|----------|---------|
| `ricopia(nome)` | Stampa il contenuto di un file |

### Algoritmo in linguaggio naturale

1. Leggere il nome della destinazione e aprirla in `"w"`; se non si apre,
   segnalarlo e terminare.
2. Per ogni nome fino a `FINE`: se è la destinazione saltarlo; se non si
   apre segnalarlo e contarlo tra i mancanti; altrimenti scrivere
   l'intestazione, copiare il file carattere per carattere, aggiungere
   l'a capo mancante e chiuderlo.
3. Chiudere la destinazione, stampare il riepilogo e il suo contenuto.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe). Si usano i
file `classe-3A.txt`, `classe-4B.txt`, `classe-5C.txt` del test 1 di
`050`.

### Test 1 – Unione dei file delle classi

- **Input:** `iscritti.txt`, poi
  `classe-3A.txt classe-4B.txt classe-2D.txt iscritti.txt classe-5C.txt FINE`
- **Valori intermedi attesi:** caratteri copiati 18 + 14 + 11 = 43.
- **Output atteso:** su `stdout`
  ```
  File da creare: File da unire (FINE per terminare):
    aggiunto classe-3A.txt
    aggiunto classe-4B.txt
    aggiunto classe-5C.txt
  iscritti.txt: file uniti 3, mancanti 1, caratteri copiati 43
  === classe-3A.txt ===
  Rossi
  Verdi
  Gallo
  === classe-4B.txt ===
  Bianchi
  Russo
  === classe-5C.txt ===
  Neri
  Costa
  ```
  e su `stderr`
  ```
    classe-2D.txt non trovato: saltato
    iscritti.txt e' il file di destinazione: saltato
  ```

### Test 2 – File senza a capo finale

- **Input:** `unione.txt`, poi `senza-a-capo.txt classe-4B.txt FINE`, con
  `senza-a-capo.txt` che contiene `riga uno`, a capo, `riga due`
- **Output atteso:** `unione.txt: file uniti 2, mancanti 0, caratteri
  copiati 31`; nel file `riga due` è seguita da un a capo e
  `=== classe-4B.txt ===` inizia su una riga nuova.
