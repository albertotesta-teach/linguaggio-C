# Analisi – 070-problema-catalogo-media.c

## 1. Problema

La biblioteca scolastica ha libri, DVD e riviste nello stesso catalogo.
Titolo e disponibilità sono campi comuni fuori dalla `union`, così ricerca
e prestito non guardano il tipo; la stampa dei dettagli usa uno `switch`
sull'etichetta. Le riviste non si prestano.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `E` elenco, `C parola` cerca nel titolo, `P n` prestito, `R n` restituzione, `Q` fine (anche minuscoli) |
| `parola`, `n` | `char[20]`, `int` | Argomenti |
| catalogo | nel sorgente | 6 materiali (vedi elenco del test) |

### Output

- `E`/`C`: righe `n  titolo  tipo  dettagli` con `(in prestito)` se serve;
  per `C` anche `Trovati: N`.
- `P`/`R`: `"titolo": prestito registrato` / `restituito`, oppure
  `"titolo" e' gia' in prestito.`, `"titolo" non era in prestito.`,
  `Le riviste si consultano in biblioteca.`, `Materiale N inesistente.`,
  `Numero non valido.`
- `Comando sconosciuto.`

### Vincoli

- I campi comuni (`tipo`, `titolo`, `disponibile`) sono fuori dalla union;
  i dettagli specifici dentro.
- L'inizializzazione usa i designatori dei membri della union
  (`{.dvd = {...}}`).
- La ricerca usa `strstr` (la parola può stare in qualsiasi punto del
  titolo; maiuscole e minuscole contano).
- Un comando per riga; i dati non validi non interrompono il programma. A
  fine input termina come con `Q`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `TipoMedia` | `typedef enum { LIBRO, DVD, RIVISTA } TipoMedia;` | Etichetta |
| `Libro`, `Dvd`, `Rivista` | struct | Dettagli specifici |
| `Media` | struct con `tipo`, `titolo`, `disponibile` e `union { Libro libro; Dvd dvd; Rivista rivista; } info` | Un materiale |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `catalogo` | `Media[6]` | Il catalogo |
| `trovati` | `int` | Risultati della ricerca |

| Funzione | Compito |
|----------|---------|
| `stampa(n, m)` | Riga del materiale con `switch` sul tipo |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `E`: stampare tutto; `C`: stampare i titoli che contengono la parola
      e contarli;
   3. `P`/`R`: controllare numero, tipo e disponibilità e aggiornare
      `disponibile`;
   4. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Ricerche e prestiti

- **Input:** `E`, `C rosa`, `c sistema`, `P 1`, `P 4`, `P 3`, `R 2`, `r 1`,
  `P 9`, `P x`, `X`, `E`, `Q`
- **Output atteso** (dopo il primo elenco):
  ```
    2  Il nome della rosa    DVD      J.-J. Annaud, 130 minuti
    4  Il nome della rosa    libro    Umberto Eco, 503 pagine  (in prestito)
    Trovati: 2
    1  Il sistema periodico  libro    Primo Levi, 240 pagine
    5  Il sistema solare     DVD      BBC, 58 minuti
    Trovati: 2
    "Il sistema periodico": prestito registrato
    "Il nome della rosa" e' gia' in prestito.
    Le riviste si consultano in biblioteca.
    "Il nome della rosa" non era in prestito.
    "Il sistema periodico": restituito
    Materiale 9 inesistente.
    Numero non valido.
    Comando sconosciuto.
  ```
  e l'elenco finale uguale a quello iniziale:
  ```
    1  Il sistema periodico  libro    Primo Levi, 240 pagine
    2  Il nome della rosa    DVD      J.-J. Annaud, 130 minuti
    3  Le Scienze            rivista  n. 687, 2025
    4  Il nome della rosa    libro    Umberto Eco, 503 pagine  (in prestito)
    5  Il sistema solare     DVD      BBC, 58 minuti
    6  Fahrenheit 451        libro    Ray Bradbury, 176 pagine
  ```
