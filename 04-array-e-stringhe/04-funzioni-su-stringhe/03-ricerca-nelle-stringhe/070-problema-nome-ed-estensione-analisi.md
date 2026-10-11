# Analisi – 070-problema-nome-ed-estensione.c

## 1. Problema

Il tecnico del laboratorio ha l'elenco dei file salvati dagli studenti con
il percorso completo. Per ogni file vuole sapere la cartella, il nome e
l'estensione, e ricondurre l'estensione a un tipo (documento, immagine,
codice, altro); alla fine vuole il numero di file per tipo.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `percorsi` | `char[][]` | 8 × 50 | Percorsi completi |
| `estensioni` | `char[][]` | 7 × 6 | Estensioni conosciute |
| `tipo_di` | `int[]` | 7 | Tipo di ogni estensione (parallelo) |
| `tipi` | `char[][]` | 4 × 12 | Nomi dei tipi; l'ultimo è "altro" |
| `quanti` | `int[]` | 4 | File per tipo (parallelo a `tipi`) |
| `cartella`, `nome`, `estensione` | `char[]` | 50 | Parti del percorso corrente |
| `barra`, `punto` | `int` | — | Posizioni dell'ultima `/` e dell'ultimo `.` |

| Funzione | Compito |
|----------|---------|
| `ultima_posizione` | Indice dell'ultima occorrenza di un carattere |
| `copia_parte` | Copia `n` caratteri a partire da un indice |
| `cerca` | Indice di una stringa in un elenco con `strcmp` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Nome con più punti

**a) Input** – `compiti/3B/rossi/relazione.finale.docx`

**b) Output** – `compiti/3B/rossi`, `relazione.finale`, `docx`, documento

**c) Variabili di supporto** – `barra` = 16, `punto` nel nome

**d) Vincoli** – conta l'ULTIMO punto del nome, non il primo

**e) Assunzioni** – percorsi con la barra `/`

**f) Algoritmo in linguaggio naturale**
1. Cartella = caratteri prima dell'ultima `/`; nome completo = caratteri dopo.
2. Nel nome cercare l'ultimo `.`: se è oltre la posizione 0, l'estensione
   sono i caratteri successivi e il nome si tronca scrivendo `'\0'` al posto del punto.
3. Cercare l'estensione tra quelle conosciute e ricavarne il tipo.

### Caso d'uso 2 – File senza cartella o senza estensione

**a) Input** – `README`

**b) Output** – `(radice)`, `README`, `-`, altro

**c) Variabili di supporto** – `barra` = -1, `punto` = -1

**d) Vincoli** – con `barra` = -1 il nome parte dall'indice 0 (`barra + 1`)

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – senza `/` la cartella è "(radice)";
senza `.` l'estensione è vuota e il tipo è "altro".

### Caso d'uso 3 – File nascosto

**a) Input** – `progetti/.gitignore`

**b) Output** – nome `.gitignore`, nessuna estensione, altro

**c) Variabili di supporto** – `punto` = 0

**d) Vincoli** – un punto in posizione 0 non introduce un'estensione

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – l'estensione si estrae solo se `punto > 0`.

### Caso d'uso 4 – Riepilogo per tipo

**a) Input** – `quanti[]`

**b) Output** – documento 2, immagine 2, codice 2, altro 2

**c) Variabili di supporto** – `tipo`

**d) Vincoli** – un'estensione sconosciuta conta come "altro"

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – a ogni file si incrementa
`quanti[tipo]`; alla fine si stampa l'array.
