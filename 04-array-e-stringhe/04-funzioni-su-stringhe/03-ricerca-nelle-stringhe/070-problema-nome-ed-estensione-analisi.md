# Analisi – 070-problema-nome-ed-estensione.c

## 1. Problema

Il tecnico del laboratorio ha l'elenco dei file salvati dagli studenti con
il percorso completo. Per ogni file vuole sapere la cartella, il nome e
l'estensione, e ricondurre l'estensione a un tipo (documento, immagine,
codice, altro); alla fine vuole il numero di file per tipo.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `percorsi` | `char[8][50]` | Percorsi completi dei file (nel sorgente) |
| `estensioni` | `char[7][6]` | Estensioni conosciute: `docx`, `pdf`, `png`, `jpg`, `c`, `html`, `txt` |
| `tipo_di` | `int[7]` | Tipo di ogni estensione (parallelo): 0 documento, 1 immagine, 2 codice |
| `tipi` | `char[4][12]` | Nomi dei tipi; l'ultimo è `altro` |

I dati sono inizializzati nel sorgente: il programma non legge nulla da tastiera.

### Output

- Una riga per file: cartella (`(radice)` se il percorso non ha `/`),
  nome senza estensione, estensione (`-` se manca), tipo.
- Riepilogo con il numero di file per tipo.

### Vincoli

- La cartella è tutto ciò che precede l'**ultima** `/`; il nome è ciò che la segue.
- L'estensione è ciò che segue l'**ultimo** `.` del nome, purché il punto
  non sia il primo carattere (file nascosti come `.gitignore`).
- Il confronto delle estensioni è esatto (`strcmp`): maiuscole e minuscole contano.
- Un'estensione assente o sconosciuta conta come `altro`.

### Assunzioni

- I percorsi usano `/` come separatore e non terminano con `/`.
- Ogni percorso è lungo al massimo 49 caratteri.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `quanti` | `int[4]` | File per tipo (parallelo a `tipi`) |
| `cartella`, `nome`, `estensione` | `char[50]` | Parti del percorso corrente |
| `lung` | `int` | Lunghezza del percorso |
| `barra`, `punto` | `int` | Posizione dell'ultima `/` nel percorso e dell'ultimo `.` nel nome |
| `e` | `int` | Indice dell'estensione nell'elenco (-1 se sconosciuta) |
| `tipo` | `int` | Tipo del file corrente |

| Funzione | Compito |
|----------|---------|
| `ultima_posizione` | Indice dell'ultima occorrenza di un carattere, o -1 |
| `copia_parte` | Copia `n` caratteri a partire da un indice e chiude la stringa |
| `cerca` | Indice di una stringa in un elenco con `strcmp`, o -1 |

### Algoritmo in linguaggio naturale

1. Per ogni percorso:
   1. trovare `barra`, l'ultima `/`;
   2. se `barra` è -1 la cartella è `(radice)`, altrimenti copiare i
      caratteri da 0 a `barra - 1`;
   3. copiare in `nome` i caratteri da `barra + 1` alla fine;
   4. trovare `punto`, l'ultimo `.` del nome: se `punto > 0` copiare
      l'estensione e troncare il nome in `punto`, altrimenti l'estensione è vuota;
   5. cercare l'estensione nell'elenco: se non c'è il tipo è `altro`,
      altrimenti `tipo_di[e]`;
   6. incrementare `quanti[tipo]` e stampare la riga.
2. Stampare il riepilogo per tipo.

## 3. Casi di test

### Test 1 – Nome con più punti

- **Cosa si verifica**: l'estensione parte dall'ultimo punto, non dal primo.
- **Input**: `compiti/3B/rossi/relazione.finale.docx` (dati del sorgente).
- **Valori intermedi attesi**: `barra` = 16; nel nome `relazione.finale.docx` `punto` = 16.
- **Output atteso**:
  ```
  compiti/3B/rossi     relazione.finale   docx  documento
  ```

### Test 2 – File senza cartella e senza estensione

- **Cosa si verifica**: con `barra` = -1 il nome parte dall'indice 0; senza
  punto non c'è estensione.
- **Input**: `README`.
- **Valori intermedi attesi**: `barra` = -1, `punto` = -1, `e` = -1.
- **Output atteso**:
  ```
  (radice)             README             -     altro
  ```

### Test 3 – File nascosto

- **Cosa si verifica**: un punto in posizione 0 non introduce un'estensione.
- **Input**: `progetti/.gitignore`.
- **Valori intermedi attesi**: `punto` = 0, quindi estensione vuota.
- **Output atteso**:
  ```
  progetti             .gitignore         -     altro
  ```

### Test 4 – Esecuzione completa e riepilogo

- **Cosa si verifica**: classificazione di tutti i file e conteggio per tipo.
- **Input**: dati del sorgente.
- **Output atteso**:
  ```
  Cartella             Nome               Est.  Tipo
  compiti/3B/rossi     relazione.finale   docx  documento
  compiti/3B/rossi     grafico            png   immagine
  compiti/3B/bianchi   esercizio1         c     codice
  progetti/sito        index              html  codice
  progetti/sito        logo               jpg   immagine
  (radice)             README             -     altro
  progetti             .gitignore         -     altro
  compiti/4A/verdi     tesina             pdf   documento

  Riepilogo:  documento 2  immagine 2  codice 2  altro 2
  ```

### Test 5 – Estensione in maiuscolo

- **Cosa si verifica**: il confronto delle estensioni distingue maiuscole e minuscole.
- **Procedura**: nel sorgente sostituire `logo.jpg` con `logo.JPG`,
  ricompilare ed eseguire.
- **Output atteso** (righe interessate):
  ```
  progetti/sito        logo               JPG   altro
  Riepilogo:  documento 2  immagine 1  codice 2  altro 3
  ```
- **Osservazione**: per riconoscere anche `JPG` bisognerebbe convertire
  l'estensione in minuscolo prima della ricerca.
