# Analisi – 060-problema-registro-del-giorno.c

## 1. Problema

Il docente della prima ora registra gli assenti in un file per giorno, il cui nome si costruisce dalla data con sprintf (presenze-16-10.txt). Se il file esiste già, il programma chiede se aggiungere ("a"), sovrascrivere ("w") o annullare. Poi scrive una riga per assente fino a FINE e ristampa il file.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `registro` | `FILE *` | — | File del giorno, in "a" o "w" |
| `nome` | `char[]` | 40 | Nome costruito con sprintf |
| `giorno`, `mese` | `int` | — | Data letta |
| `scelta` | `char` | — | A, S o N |
| `cognome`, `assenti` | `char[]`, `int` | 30 | Assente letto e conteggio |

| Funzione | Compito |
|----------|---------|
| `esiste(nome)` | Prova ad aprire in "r" e richiude |
| `stampa(nome)` | Ricopia il file a video |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Primo registro

**a) Input** – `16 10`, `Rossi Bianchi FINE`

**b) Output** – presenze-16-10.txt con 2 righe

**c) Variabili di supporto** – `nome`

**d) Vincoli** – giorno 1-31, mese 1-12

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sprintf del nome; il file non esiste: "w".

### Caso d'uso 2 – File già presente

**a) Input** – `16 10`, `A`, `Verdi FINE`

**b) Output** – il file ha 3 righe

**c) Variabili di supporto** – `scelta`

**d) Vincoli** – A, S o N

**e) Assunzioni** – un collega ha già scritto

**f) Algoritmo in linguaggio naturale** – "a" aggiunge dopo le righe esistenti.

### Caso d'uso 3 – Sovrascrivere

**a) Input** – `16 10`, `S`, ...

**b) Output** – il file contiene solo i nuovi assenti

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – "w" svuota il file.

### Caso d'uso 4 – Data errata

**a) Input** – `32 10`

**b) Output** – "Data non valida."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessun file aperto.
