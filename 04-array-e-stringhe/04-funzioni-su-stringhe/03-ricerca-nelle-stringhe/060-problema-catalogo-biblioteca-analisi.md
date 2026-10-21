# Analisi – 060-problema-catalogo-biblioteca.c

## 1. Problema

La biblioteca scolastica vuole una ricerca per parola chiave nel proprio
catalogo. La parola viene cercata nel titolo e nell'autore di ogni libro,
senza distinguere maiuscole e minuscole; per ogni libro trovato si mostrano
titolo, autore, anno e disponibilità. La ricerca si ripete finché l'utente
non inserisce una riga vuota.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `chiave` | `char[40]` | Parola chiave letta da tastiera; una riga vuota termina |
| `titoli` | `char[8][40]` | Titoli del catalogo (nel sorgente) |
| `autori` | `char[8][24]` | Autori (parallelo) |
| `anni` | `int[8]` | Anno di pubblicazione (parallelo) |
| `copie` | `int[8]` | Copie disponibili (parallelo) |

### Output

- Per ogni libro trovato: titolo, autore, anno e `disponibile` (copie > 0)
  oppure `in prestito`.
- Il numero di risultati (`1 risultato` / `N risultati`), oppure
  `Nessun libro trovato per "<chiave>".`
- Alla fine: `Buona lettura!`

### Vincoli

- La ricerca non distingue maiuscole e minuscole: chiave e campo vengono
  entrambi convertiti in minuscolo prima di usare `strstr`.
- Un libro compare una sola volta anche se la chiave è sia nel titolo sia nell'autore.
- La copia in minuscolo del campo è grande quanto il campo più lungo (`LUNG_TITOLO`).

### Assunzioni

- Titoli e autori non contengono lettere accentate (si usa l'apostrofo, es. `citta'`).
- `strstr` cerca una sequenza di caratteri, non una parola intera: la chiave
  può essere trovata anche dentro un'altra parola (vedi Test 3).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `chiave_min` | `char[40]` | Chiave convertita in minuscolo |
| `letta` | `int` | 1 se la lettura è riuscita |
| `k` | `int` | Indice del libro in esame |
| `trovati` | `int` | Libri trovati per la chiave corrente |
| `testo_min` | `char[40]` | In `contiene`: copia in minuscolo del campo |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Legge una riga e toglie il `'\n'` |
| `in_minuscolo` | Copia convertendo le maiuscole |
| `contiene` | 1 se il campo (convertito in minuscolo) contiene la chiave |

### Algoritmo in linguaggio naturale

1. Leggere la chiave.
2. Finché la lettura riesce e la chiave non è vuota:
   1. convertire la chiave in minuscolo e azzerare `trovati`;
   2. per ogni libro, se il titolo o l'autore contengono la chiave,
      stampare la riga del libro e incrementare `trovati`;
   3. se `trovati` è 0 stampare il messaggio di nessun risultato,
      altrimenti il numero di risultati;
   4. leggere la chiave successiva.
3. Stampare il saluto finale.

## 3. Casi di test

### Test 1 – Ricerca per autore

- **Cosa si verifica**: la chiave in minuscolo trova l'autore scritto con
  l'iniziale maiuscola; un libro senza copie risulta in prestito.
- **Input**: `calvino`, poi riga vuota.
- **Output atteso**:
  ```
    Il barone rampante             Italo Calvino       1957  disponibile
    Le citta' invisibili           Italo Calvino       1972  in prestito
    Il sentiero dei nidi di ragno  Italo Calvino       1947  disponibile
    Marcovaldo                     Italo Calvino       1963  disponibile
    4 risultati
  ```

### Test 2 – Chiave scritta in maiuscolo

- **Cosa si verifica**: anche la chiave viene convertita; singolare di "risultato".
- **Input**: `PROMESSI`, poi riga vuota.
- **Output atteso**:
  ```
    I promessi sposi               Alessandro Manzoni  1840  disponibile
    1 risultato
  ```

### Test 3 – Chiave contenuta in altre parole

- **Cosa si verifica**: `strstr` trova la sequenza anche dentro una parola
  ("invisibili" contiene "il").
- **Input**: `il`, poi riga vuota.
- **Output atteso**:
  ```
    Il barone rampante             Italo Calvino       1957  disponibile
    Le citta' invisibili           Italo Calvino       1972  in prestito
    Il sentiero dei nidi di ragno  Italo Calvino       1947  disponibile
    Il fu Mattia Pascal            Luigi Pirandello    1904  in prestito
    4 risultati
  ```

### Test 4 – Chiave presente in più autori

- **Cosa si verifica**: la ricerca sull'autore trova autori diversi con lo stesso nome.
- **Input**: `Italo`, poi riga vuota.
- **Valori intermedi attesi**: `trovati` = 5 (quattro libri di Calvino e uno di Svevo).
- **Output atteso** (ultima riga): `  5 risultati`

### Test 5 – Nessun risultato

- **Cosa si verifica**: messaggio quando nessun libro corrisponde; nel
  messaggio la chiave è stampata come è stata scritta.
- **Input**: `Eco`, poi riga vuota.
- **Output atteso**:
  ```
    Nessun libro trovato per "Eco".
  Parola chiave (riga vuota per uscire): Buona lettura!
  ```
