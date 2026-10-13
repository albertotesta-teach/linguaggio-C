# Analisi – 070-problema-catalogo-media.c

## 1. Problema

La biblioteca scolastica ha libri, DVD e riviste nello stesso catalogo. Titolo e disponibilità sono campi comuni fuori dalla union, così ricerca e prestito non guardano il tipo; la stampa dei dettagli usa uno switch sull'etichetta. Le riviste non si prestano.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Media` | `tipo, titolo, disponibile, union info {libro, dvd, rivista}` | materiale della biblioteca |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `catalogo` | `Media[]` | 6 | Materiali |
| `parola` | `char[]` | 20 | Parola cercata |
| `n`, `trovati` | `int` | — | Numero del materiale e risultati |

| Funzione | Compito |
|----------|---------|
| `stampa(n, &m)` | Campi comuni e dettagli del tipo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Elenco

**a) Input** – `E`

**b) Output** – libro con autore e pagine, DVD con regista e minuti, rivista con numero e anno

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – switch su m->tipo per scegliere il campo della union.

### Caso d'uso 2 – Ricerca

**a) Input** – `C nome`

**b) Output** – il DVD e il libro "Il nome della rosa", "Trovati: 2"

**c) Variabili di supporto** – `trovati`

**d) Vincoli** – maiuscole e minuscole distinte

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – strstr sul titolo, campo comune.

### Caso d'uso 3 – Prestiti

**a) Input** – `P 4`; `P 2`; `P 3`

**b) Output** – "gia' in prestito"; "prestito registrato"; "Le riviste si consultano in biblioteca."

**c) Variabili di supporto** – `disponibile`

**d) Vincoli** – riviste escluse

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il controllo del tipo viene prima di quello della disponibilità.

### Caso d'uso 4 – Restituzioni

**a) Input** – `R 4`; `R 1`

**b) Output** – "restituito"; "non era in prestito"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – disponibile torna a 1.
