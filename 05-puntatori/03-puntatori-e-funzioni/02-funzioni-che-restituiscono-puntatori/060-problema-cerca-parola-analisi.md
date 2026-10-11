# Analisi – 060-problema-cerca-parola.c

## 1. Problema

Il rappresentante degli studenti vuole sapere quante volte alcune parole
compaiono in un articolo del regolamento d'istituto e dove compaiono la
prima volta, con un po' di testo intorno. La ricerca usa una versione di
`strstr` scritta a mano.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `articolo` | `const char *` | — | Testo dell'articolo (letterale) |
| `cercate` | `char[][]` | 4 × 16 | Parole da cercare |
| `trovato` | `const char *` | — | Prima occorrenza nel testo, `NULL` se assente |
| `posizione`, `da` | `int` | — | Indice dell'occorrenza e inizio del contesto |

| Funzione | Compito |
|----------|---------|
| `trova(testo, parola)` | Puntatore alla prima occorrenza, `NULL` se assente |
| `inizia_con(testo, parola)` | 1 se `testo` comincia con `parola` |
| `conta(testo, parola)` | Numero di occorrenze |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prima occorrenza con contesto

**a) Input** – parola "telefono"

**b) Output** – 3 volte, prima in posizione 17, contesto "7 - Uso del
telefono. Durante le"

**c) Variabili di supporto** – `posizione = trovato - articolo`, `da`

**d) Vincoli** – il contesto non inizia prima del testo: `da` non scende
sotto 0

**e) Assunzioni** – 12 caratteri di contesto per lato

**f) Algoritmo in linguaggio naturale**
1. `trova` avanza `p` finché il testo da `p` non inizia con la parola.
2. Nel main stampare con `%.*s` a partire da `articolo + da`.

### Caso d'uso 2 – Conteggio

**a) Input** – parola "telefono"

**b) Output** – 3 occorrenze

**c) Variabili di supporto** – `trovato`, `volte`

**d) Vincoli** – la ricerca successiva riparte da `trovato + 1`

**e) Assunzioni** – si distinguono maiuscole e minuscole

**f) Algoritmo in linguaggio naturale** – finché `trova` non restituisce
`NULL`, contare e ripartire dal carattere dopo l'occorrenza.

### Caso d'uso 3 – Parola assente

**a) Input** – "intervallo"

**b) Output** – "non presente"

**c) Variabili di supporto** – `trovato` = `NULL`

**d) Vincoli** – il risultato si controlla prima di usarlo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `trova` arriva al `'\0'`
restituisce `NULL`.
