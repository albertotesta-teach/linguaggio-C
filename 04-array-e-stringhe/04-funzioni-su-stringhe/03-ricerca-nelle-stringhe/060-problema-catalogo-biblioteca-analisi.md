# Analisi – 060-problema-catalogo-biblioteca.c

## 1. Problema

La biblioteca scolastica vuole una ricerca per parola chiave nel proprio
catalogo. La parola viene cercata nel titolo e nell'autore di ogni libro,
senza distinguere maiuscole e minuscole; per ogni libro trovato si mostrano
titolo, autore, anno e disponibilità. La ricerca si ripete finché l'utente
non inserisce una riga vuota.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `titoli` | `char[][]` | 8 × 40 | Titoli |
| `autori` | `char[][]` | 8 × 24 | Autori (parallelo) |
| `anni` | `int[]` | 8 | Anno di pubblicazione (parallelo) |
| `copie` | `int[]` | 8 | Copie disponibili (parallelo) |
| `chiave`, `chiave_min` | `char[]` | 40 | Parola cercata e sua copia in minuscolo |
| `trovati` | `int` | — | Risultati della ricerca corrente |

| Funzione | Compito |
|----------|---------|
| `in_minuscolo` | Copia in minuscolo |
| `contiene` | Converte un campo in minuscolo e lo cerca con `strstr` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ricerca per autore

**a) Input** – `calvino`

**b) Output** – i quattro libri di Italo Calvino, con "in prestito" per quello senza copie

**c) Variabili di supporto** – `chiave_min`, `trovati`

**d) Vincoli** – la chiave e il campo devono essere entrambi in minuscolo

**e) Assunzioni** – lettere senza accenti

**f) Algoritmo in linguaggio naturale**
1. Convertire la chiave in minuscolo.
2. Per ogni libro: se titolo o autore la contengono, stampare il libro e contarlo.
3. Stampare il numero di risultati o "Nessun libro trovato".

### Caso d'uso 2 – Ricerca per titolo in maiuscolo

**a) Input** – `PROMESSI`

**b) Output** – I promessi sposi, 1 risultato

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Parola contenuta in altre parole

**a) Input** – `il`

**b) Output** – anche "Le città invisibili", perché "invisibili" contiene "il"

**c) Variabili di supporto** – nessuna

**d) Vincoli** – `strstr` cerca una sequenza di caratteri, non una parola intera

**e) Assunzioni** – il comportamento è accettato per una ricerca semplice

**f) Algoritmo in linguaggio naturale** – come nel caso 1 (per la parola
intera si veda `030-conta-occorrenze.c`).

### Caso d'uso 4 – Nessun risultato

**a) Input** – `Eco`

**b) Output** – "Nessun libro trovato per "Eco"."

**c) Variabili di supporto** – `trovati` = 0

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – dopo lo scorrimento, se `trovati`
vale 0 si stampa il messaggio.
