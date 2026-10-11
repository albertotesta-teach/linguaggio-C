# Analisi – 070-problema-nome-file.c

## 1. Problema

I compiti consegnati sulla piattaforma della scuola hanno percorsi come
`4B/informatica/verifica-3.c`. Per l'archivio servono cartella, nome ed
estensione separati, segnalando i file senza cartella o senza estensione.
La ricerca usa una versione di `strrchr` scritta a mano.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `percorsi` | `char[][]` | 5 × 40 | Percorsi da esaminare |
| `barra` | `const char *` | — | Ultima `/` del percorso, `NULL` se assente |
| `nome` | `const char *` | — | Inizio del nome del file |
| `punto` | `const char *` | — | Ultimo `.` del nome, `NULL` se assente |

| Funzione | Compito |
|----------|---------|
| `ultimo(s, c)` | Puntatore all'ultima occorrenza di `c`, `NULL` se assente |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Percorso completo

**a) Input** – `4B/informatica/relazione.lab.pdf`

**b) Output** – cartella `4B/informatica`, nome `relazione.lab`, estensione
`pdf`

**c) Variabili di supporto** – `barra`, `nome`, `punto`

**d) Vincoli** – conta l'ULTIMO punto e l'ULTIMA barra

**e) Assunzioni** – il separatore delle cartelle è `/`

**f) Algoritmo in linguaggio naturale**
1. `barra = ultimo(percorso, '/')`; il nome inizia da `barra + 1`.
2. `punto = ultimo(nome, '.')`.
3. Cartella: `barra - percorso` caratteri; nome: `punto - nome` caratteri;
   estensione: da `punto + 1`.

### Caso d'uso 2 – Punto nella cartella

**a) Input** – `5A/sistemi/v1.2/schema`

**b) Output** – estensione "(nessuna)"

**c) Variabili di supporto** – `punto` cercato in `nome`

**d) Vincoli** – il punto di `v1.2` non deve essere preso come estensione

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il punto si cerca a partire da
`nome`, non dall'inizio del percorso.

### Caso d'uso 3 – Senza cartella e file nascosto

**a) Input** – `appunti.txt`; `4B/storia/.nascosto`

**b) Output** – cartella "(nessuna)"; nome `.nascosto` senza estensione

**c) Variabili di supporto** – `barra` = `NULL`, `punto == nome`

**d) Vincoli** – un punto all'inizio del nome non indica un'estensione

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `barra` è `NULL` il nome è
tutto il percorso; se `punto` è `NULL` o coincide con `nome` non c'è
estensione.
