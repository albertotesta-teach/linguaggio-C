# Analisi – 070-problema-statistiche-di-un-testo.c

## 1. Problema

Prima di consegnare la relazione di laboratorio gli studenti controllano il testo. Il programma legge il file una sola volta, carattere per carattere, e conta lettere, cifre, spazi, altri caratteri e righe; trova la riga più lunga e segnala quante righe superano gli 80 caratteri.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `f` | `FILE *` | — | File da analizzare |
| `nome` | `char[]` | 60 | Nome letto |
| `lettere`, `cifre`, `spazi`, `altri` | `int` | — | Conteggi per tipo di carattere |
| `righe`, `lunghezza` | `int` | — | Righe e lunghezza della riga corrente |
| `massima`, `riga_massima`, `troppo_lunghe` | `int` | — | Statistiche sulle righe |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Diario

**a) Input** – `diario.txt`

**b) Output** – 68 lettere, 12 cifre, 10 spazi, 5 altri; 3 righe; la più lunga è la 2 (44 caratteri)

**c) Variabili di supporto** – `lunghezza`

**d) Vincoli** – —

**e) Assunzioni** – le lettere accentate sono "altri caratteri"

**f) Algoritmo in linguaggio naturale** – a ogni '\n' si confronta lunghezza con il massimo e la si azzera.

### Caso d'uso 2 – Ultima riga senza a capo

**a) Input** – file che non termina con '\n'

**b) Output** – l'ultima riga è contata

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – dopo il ciclo, se lunghezza > 0 si conta un'altra riga.

### Caso d'uso 3 – File mancante

**a) Input** – `relazione.txt`

**b) Output** – "Impossibile leggere" su stderr

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna statistica.
