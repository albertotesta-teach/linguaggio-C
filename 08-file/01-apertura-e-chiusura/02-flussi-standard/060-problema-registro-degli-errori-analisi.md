# Analisi – 060-problema-registro-degli-errori.c

## 1. Problema

La segreteria carica i voti della verifica di recupero, una riga
`cognome voto` per studente. Le righe valide vanno in `recupero.txt`
(aperto in `"w"`); quelle errate sono segnalate su `stderr` e aggiunte
allo storico `errori.txt` (aperto in `"a"`). Una funzione che riceve il
flusso come parametro scrive lo stesso messaggio sui due flussi.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| riga | testo | `cognome voto`, una per studente, fino a `FINE` o alla fine dell'input |

### Output

- `recupero.txt`: una riga `cognome voto` per ogni voto valido (il file
  si riscrive a ogni esecuzione).
- Per ogni riga errata, su `stderr` e in fondo a `errori.txt`:
  `riga R (COGNOME): MOTIVO`, con motivo `manca il voto`,
  `dati in piu' dopo il voto`, `il voto non e' un numero intero` o
  `voto fuori dall'intervallo 1-10`.
- `Voti caricati in recupero.txt: N` e
  `Righe scartate (vedi errori.txt): K`.
- `Impossibile creare recupero.txt` o `Impossibile aprire errori.txt` su
  `stderr`.

### Vincoli

- I due file restano aperti insieme per tutto il caricamento; se il
  secondo non si apre, il primo si chiude subito.
- `"w"` per `recupero.txt` (solo il caricamento di oggi), `"a"` per
  `errori.txt` (lo storico non si perde).
- `segnala(f, ...)` scrive su qualunque flusso: si chiama una volta con
  `stderr` e una con `errori`.
- Ogni riga si legge con `fgets` (al massimo 99 caratteri, il resto si
  scarta) e si divide con `sscanf` in cognome (29), voto (15) e un
  eventuale carattere in più.
- Il voto deve essere un intero senza altri caratteri, da 1 a 10.
- Le righe di dati si numerano da 1; le righe vuote si ignorano e non si
  numerano. `FINE` va scritto in maiuscolo.

### Assunzioni

- Il cognome è una sola parola.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `validi`, `errori` | `FILE *` | I due file di uscita |
| `riga` | `char[100]` | Riga letta con `fgets` |
| `cognome`, `testo_voto` | `char[30]`, `char[16]` | Campi della riga |
| `campi` | `int` | Campi trovati da `sscanf` (3 = dati in più) |
| `altro`, `dopo` | `char` | Rilevano caratteri in più nella riga e nel voto |
| `motivo` | `const char *` | Motivo dello scarto, `NULL` se la riga è valida |
| `riga_n`, `caricati`, `scartati` | `int` | Contatori |
| `resto` | `int` | Carattere scartato da una riga troppo lunga |

| Funzione | Compito |
|----------|---------|
| `segnala(f, riga, cognome, motivo)` | Scrive il messaggio di errore sul flusso `f` |

### Algoritmo in linguaggio naturale

1. Aprire `recupero.txt` in `"w"` ed `errori.txt` in `"a"`; se uno non si
   apre, segnalarlo e chiudere l'altro.
2. Leggere una riga alla volta fino a `FINE` o alla fine dell'input;
   saltare le righe vuote.
3. Numerare la riga e cercare il primo motivo di scarto; se c'è,
   scriverlo su `stderr` e in `errori.txt`, altrimenti scrivere la riga in
   `recupero.txt`.
4. Chiudere i file e stampare i due conteggi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe); i messaggi di
`stderr` compaiono prima perché `stdout` verso una pipe è bufferizzato. Si
parte senza `errori.txt`.

### Test 1 – Voti con errori

- **Input:** `Rossi 6`, `Bianchi sei`, `Verdi 7`, `Neri 11`, `Russo 5`,
  `FINE`
- **Output atteso:**
  ```
  riga 2 (Bianchi): il voto non e' un numero intero
  riga 4 (Neri): voto fuori dall'intervallo 1-10
  Voti (cognome voto, FINE per terminare):
  Voti caricati in recupero.txt: 3
  Righe scartate (vedi errori.txt): 2
  ```
- **Procedura:** `recupero.txt` contiene `Rossi 6`, `Verdi 7`, `Russo 5`;
  `errori.txt` le due righe di errore.

### Test 2 – Righe incomplete; lo storico cresce

- **Cosa si verifica:** voto mancante, dati in più, voto decimale, riga
  vuota, ultima riga senza a capo e senza FINE.
- **Input:** `Gialli`, riga vuota, `Blu 7 8`, `Rosa 7.5`, `Viola 10`
  (senza a capo), poi fine input
- **Output atteso:**
  ```
  riga 1 (Gialli): manca il voto
  riga 2 (Blu): dati in piu' dopo il voto
  riga 3 (Rosa): il voto non e' un numero intero
  Voti (cognome voto, FINE per terminare):
  Voti caricati in recupero.txt: 1
  Righe scartate (vedi errori.txt): 3
  ```
- **Procedura:** eseguire dopo il test 1: `recupero.txt` contiene solo
  `Viola 10`, `errori.txt` ha 5 righe (le 2 del test 1 e le 3 nuove).
