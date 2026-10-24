# Analisi – 040-problema-salvataggio-sicuro.c

## 1. Problema

La classe tiene in `libri.txt` l'elenco della biblioteca di classe, un
titolo per riga. Il programma carica il file carattere per carattere in un
array (che resta vuoto se il file non c'è), permette di aggiungere e
togliere titoli e salva in modo sicuro: scrive `libri.tmp`, lo chiude,
rimuove `libri.txt` e rinomina il temporaneo. Se si esce con modifiche non
salvate, lo segnala.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `libri.txt` | file di testo | Un titolo per riga, se esiste |
| `comando` | `char` | `A`, `R`, `E`, `S`, `Q` (anche minuscoli), uno per riga |
| titolo | testo | Dopo `A`: il resto della riga, fino a 59 caratteri |
| `numero` | `int` | Dopo `R`: posizione del titolo da togliere |

### Output

- `Libri caricati da libri.txt: N` all'avvio.
- `  aggiunto al numero N`, `  rimosso: TITOLO`, l'elenco numerato
  (`  elenco vuoto` se vuoto), `  salvati N titoli in libri.txt`.
- `  elenco pieno`, `  numero non valido`, `  comando sconosciuto`,
  `  salvataggio non riuscito: libri.txt non e' stato toccato`.
- All'uscita: `  attenzione: le ultime modifiche non sono state salvate`
  se ci sono modifiche dopo l'ultimo salvataggio.

### Vincoli

- Il salvataggio passa dal file temporaneo: se `fopen("libri.tmp", "w")`
  non riesce, `libri.txt` resta com'era. Solo dopo `fclose` si chiamano
  `remove` e `rename`, e il risultato di `rename` dice se il salvataggio è
  riuscito.
- Il caricamento legge con `fgetc` e chiude ogni titolo all'a capo; le
  righe vuote si saltano, un titolo più lungo di 59 caratteri si tronca,
  l'ultima riga senza a capo si carica lo stesso; al massimo 50 titoli.
- Un comando per riga: dopo ogni comando il resto della riga si scarta
  (anche la parte di un titolo oltre i 59 caratteri).
- Togliere un titolo sposta indietro di un posto quelli successivi.
- La fine dell'input vale come `Q`.

### Assunzioni

- Nessun altro programma modifica `libri.txt` mentre il programma è in
  esecuzione.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `titoli` | `char[50][60]` | Elenco in memoria |
| `n` | `int` | Titoli presenti |
| `modificato` | `int` | 1 se ci sono modifiche non salvate |
| `numero` | `int` | Titolo da togliere |
| `MAX_LIBRI`, `MAX_TITOLO` | `#define` | 50 titoli da 59 caratteri |

| Funzione | Compito |
|----------|---------|
| `carica(nome, titoli)` | Carica il file un carattere alla volta; restituisce i titoli letti (0 se manca) |
| `salva(nome, temporaneo, titoli, n)` | Salvataggio sicuro; 0 se non riesce |
| `elenco(titoli, n)` | Stampa l'elenco numerato |
| `svuota_riga` | Scarta il resto della riga del comando |

### Algoritmo in linguaggio naturale

1. Caricare `libri.txt` e stampare quanti titoli sono stati letti.
2. Ripetere fino a `Q`: leggere il comando in maiuscolo ed eseguirlo
   (`A` aggiunge, `R` toglie, `E` elenca, `S` salva e azzera
   `modificato`); poi scartare il resto della riga.
3. Con `Q`, se `modificato` vale 1, avvisare.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe). Si parte senza
`libri.txt`; i test vanno eseguiti in ordine.

### Test 1 – Prima esecuzione: il file non esiste

- **Input:** `A Il barone rampante`, `A Se questo e' un uomo`,
  `A La coscienza di Zeno`, `E`, `S`, `Q`
- **Output atteso:**
  ```
  Libri caricati da libri.txt: 0
  Comando (A, R, E, S, Q):   aggiunto al numero 1
  Comando (A, R, E, S, Q):   aggiunto al numero 2
  Comando (A, R, E, S, Q):   aggiunto al numero 3
  Comando (A, R, E, S, Q):    1. Il barone rampante
     2. Se questo e' un uomo
     3. La coscienza di Zeno
  Comando (A, R, E, S, Q):   salvati 3 titoli in libri.txt
  Comando (A, R, E, S, Q): 
  ```
- **Procedura:** dopo l'esecuzione esiste `libri.txt` e non esiste
  `libri.tmp`.

### Test 2 – Modifiche non salvate

- **Input:** `E`, `R 2`, `A Il sentiero dei nidi di ragno`, `R 9`, `E`,
  `Q`
- **Output atteso:**
  ```
  Libri caricati da libri.txt: 3
  Comando (A, R, E, S, Q):    1. Il barone rampante
     2. Se questo e' un uomo
     3. La coscienza di Zeno
  Comando (A, R, E, S, Q):   rimosso: Se questo e' un uomo
  Comando (A, R, E, S, Q):   aggiunto al numero 3
  Comando (A, R, E, S, Q):   numero non valido
  Comando (A, R, E, S, Q):    1. Il barone rampante
     2. La coscienza di Zeno
     3. Il sentiero dei nidi di ragno
  Comando (A, R, E, S, Q):   attenzione: le ultime modifiche non sono state salvate
  ```
- **Procedura:** `libri.txt` contiene ancora i 3 titoli del test 1.

### Test 3 – Minuscole, dati errati e titolo troppo lungo

- **Input:** `e`, `r x y`, `x altro`, `A` seguito da 70 `y`, `e`, `s`,
  poi fine input
- **Output atteso:** l'elenco di 3 titoli, `  numero non valido`,
  `  comando sconosciuto` (una sola volta), `  aggiunto al numero 4`,
  l'elenco con il quarto titolo di 59 `y`, `  salvati 4 titoli in
  libri.txt`.
