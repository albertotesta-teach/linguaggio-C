# Analisi – 050-problema-anagrafica-studenti.c

## 1. Problema

La segreteria organizza i pulmini per le uscite: cerca gli studenti per
comune o per CAP e conta quanti abitano in ogni provincia. L'indirizzo è
una struct `Indirizzo` dentro la struct `Studente`
(`elenco[i].residenza.comune`). Il comune può contenere spazi, quindi i
comandi si leggono a righe con `fgets`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[40]` | Comando: `C comune`, `Z cap`, `P` province, `Q` fine (lettera anche minuscola) |
| elenco | nel sorgente | 7 studenti di Alessandria, Novi Ligure, Ovada (AL) e Asti (AT) |

### Output

- Per `C`/`Z`: gli studenti trovati (nome, classe, indirizzo completo) e
  `Trovati: N`, oppure `Manca il comune o il CAP.`
- Per `P`: una riga `PR: N studenti` per ogni provincia, nell'ordine in
  cui compare.
- `Comando sconosciuto.`

### Vincoli

- L'argomento inizia dal terzo carattere della riga (`riga + 2`).
- Comune e CAP si confrontano con `strcmp`: maiuscole e minuscole
  contano.
- Il conteggio per provincia costruisce un elenco di province distinte
  con i contatori, senza conoscerle in anticipo.
- Una riga più lunga del buffer viene troncata e il resto scartato. A fine
  input il programma termina come con `Q`.

### Assunzioni

- Tra la lettera del comando e l'argomento c'è un solo spazio.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Indirizzo` | `typedef struct { char via[28]; char cap[6]; char comune[16]; char provincia[3]; } Indirizzo;` | Indirizzo di residenza |
| `Studente` | `typedef struct { char nome[20]; char classe[4]; Indirizzo residenza; } Studente;` | Studente con l'indirizzo annidato |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `elenco` | `Studente[7]` | Array di struct annidate |
| `province`, `conteggi` | `char[7][3]`, `int[7]` | Province distinte e contatori |
| `n_province` | `int` | Province trovate |
| `argomento` | `char *` | Inizio dell'argomento nella riga |
| `resto` | `int` | Caratteri scartati di una riga lunga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere una riga (fine input → `Q`), scartare il resto se troppo
      lunga, togliere l'a capo;
   2. il comando è la prima lettera in maiuscolo, l'argomento parte dal
      terzo carattere;
   3. `C`/`Z` senza argomento: segnalarlo; altrimenti stampare e contare
      gli studenti con comune o CAP uguale;
   4. `P`: per ogni studente cercare la provincia tra quelle già viste,
      aggiungerla se nuova, aumentarne il contatore; stampare;
   5. altro diverso da `Q`: comando sconosciuto.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Ricerche e province

- **Input:** `C Alessandria`, `c Novi Ligure`, `Z 14100`, `C Torino`, `C`,
  `P`, `X`, `C` seguito da 60 zeri, `Q`
- **Output atteso:**
  ```
    Rossi Elena  2A  via Marengo 12, 15121 Alessandria (AL)
    Costa Marta  3B  via Torino 31, 15121 Alessandria (AL)
    Trovati: 2
    Greco Paolo  2A  corso Italia 4, 15067 Novi Ligure (AL)
    Fabbri Ivo   4C  via Novi 5, 15067 Novi Ligure (AL)
    Trovati: 2
    Villa Sara   3B  piazza Duomo 2, 14100 Asti (AT)
    Conte Mattia 5A  corso Savona 9, 14100 Asti (AT)
    Trovati: 2
    Trovati: 0
    Manca il comune o il CAP.
    AL: 5 studenti
    AT: 2 studenti
    Comando sconosciuto.
    Trovati: 0
  ```
  (il comune con spazi `Novi Ligure` viene trovato perché la riga si legge
  per intero).
