# Analisi – 050-problema-copia-di-un-file.c

## 1. Problema

Prima di modificare il diario il coordinatore ne vuole una copia. Il
programma chiede il nome del file da copiare e quello della copia, apre i
due file insieme (l'origine in `"r"`, la copia in `"w"`) e copia carattere
per carattere, contando caratteri e righe. Rifiuta lo stesso nome per i due
file e, se la copia esiste già, chiede conferma prima di sovrascriverla.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `nome_origine` | testo | Nome del file da copiare, senza spazi, fino a 59 caratteri |
| `nome_copia` | testo | Nome della copia, diverso dall'origine |
| `risposta` | `char` | `s` o `n` (anche maiuscole), solo se la copia esiste già |
| file di origine | file di testo | Contenuto da copiare |

### Output

- Il file copia, identico all'origine.
- `  la copia deve avere un nome diverso` finché i due nomi coincidono.
- `Copiati C caratteri e R righe da ORIGINE a COPIA`, oppure
  `Copia annullata.` se la risposta non è `s`.
- Su `stderr`: `Impossibile leggere ORIGINE` o `Impossibile creare COPIA`.

### Vincoli

- Si controlla il risultato di ogni `fopen`; ogni file aperto si chiude
  con `fclose`, anche quando la copia viene annullata.
- `"w"` cancella un file esistente: per questo si controlla prima se la
  copia esiste (aprendola in `"r"` e richiudendola subito).
- La copia usa `fgetc`/`fputc` e il ciclo termina quando `fgetc`
  restituisce `EOF` (per questo `c` è `int`).
- Le righe sono i caratteri `'\n'`, più l'ultima riga se il file non
  finisce con un a capo.
- Qualunque risposta diversa da `s`/`S` (o la fine dell'input) annulla.

### Assunzioni

- Due nomi diversi indicano file diversi (non si considerano percorsi come
  `./diario.txt`).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `origine`, `destinazione` | `FILE *` | I due file aperti insieme; `NULL` se non aperti |
| `letti` | `int` | Risultato degli `scanf` dei nomi |
| `c`, `ultimo` | `int` | Carattere copiato e ultimo carattere del file |
| `caratteri`, `righe` | `int` | Contatori |

| Funzione | Compito |
|----------|---------|
| `esiste(nome)` | 1 se il file si può aprire in lettura |

### Algoritmo in linguaggio naturale

1. Leggere i due nomi; finché coincidono, chiedere di nuovo la copia.
2. Aprire l'origine in `"r"`; se non si apre, segnalarlo.
3. Se la copia esiste già, chiedere se sovrascriverla.
4. Con la conferma (o se la copia non esiste) aprire la copia in `"w"`.
5. Copiare un carattere alla volta contando caratteri e a capo; contare
   l'ultima riga se manca l'a capo finale; chiudere e stampare il
   riepilogo, altrimenti stampare `Copia annullata.`.
6. Chiudere l'origine.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe). Si usa il
`diario.txt` di 3 righe e 98 caratteri prodotto dai test 1 e 2 di `040`.

### Test 1 – Copia del diario

- **Cosa si verifica:** lo stesso nome viene rifiutato; la copia conta
  caratteri e righe.
- **Input:** `diario.txt`, `diario.txt`, `diario-copia.txt`
- **Output atteso:**
  ```
  File da copiare: Nome della copia:   la copia deve avere un nome diverso
  Nome della copia: Copiati 98 caratteri e 3 righe da diario.txt a diario-copia.txt
  ```

### Test 2 – La copia esiste già

- **Cosa si verifica:** senza conferma il file esistente non viene
  toccato.
- **Input:** `diario.txt`, `diario-copia.txt`, `N`
- **Output atteso:**
  ```
  File da copiare: Nome della copia: diario-copia.txt esiste gia': sovrascrivere? (s/n) Copia annullata.
  ```
- **Procedura:** eseguire dopo il test 1.

### Test 3 – Ultima riga senza a capo e conferma maiuscola

- **Cosa si verifica:** l'ultima riga senza `'\n'` viene contata; `S`
  vale come `s`.
- **Input:** un file `senza-a-capo.txt` con `riga uno`, a capo,
  `riga due` (17 caratteri); `senza-a-capo.txt`, `copia2.txt` (che
  esiste già), `S`
- **Output atteso:** `Copiati 17 caratteri e 2 righe da senza-a-capo.txt
  a copia2.txt`

### Test 4 – Origine mancante

- **Input:** `nessuno.txt`, `x.txt`
- **Output atteso:** `Impossibile leggere nessuno.txt` (su `stderr`); non
  viene creato nessun file.
