# Analisi – 050-problema-elenco-di-parole.c

## 1. Problema

Per aiutare a variare il lessico di un tema il programma conta le parole distinte. Due array crescono di un elemento a ogni parola nuova, partendo da NULL: uno di puntatori alle parole (ognuna in un blocco della sua lunghezza) e uno di contatori. Alla fine stampa le parole ripetute almeno 3 volte e libera prima le parole e poi gli array.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `parole` | `char **` | n puntatori (heap) | Parole distinte in minuscolo |
| `conta` | `int *` | n (heap) | Ripetizioni di ogni parola |
| `parola` | `char[]` | 31 | Parola corrente |
| `totale`, `n` | `int` | — | Parole e parole distinte |

| Funzione | Compito |
|----------|---------|
| `cerca(parole, n, parola)` | Indice della parola o -1 |
| `aggiungi(&parole, &conta, n, parola)` | Allunga i due array e copia la parola; 0 se un'allocazione fallisce |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tema sulla gita

**a) Input** – tre righe, `FINE`

**b) Output** – "Parole: 38, distinte: 26"; "e 4", "molto 4"

**c) Variabili di supporto** – `conta`

**d) Vincoli** – parole fino a 30 lettere

**e) Assunzioni** – maiuscole e minuscole uguali

**f) Algoritmo in linguaggio naturale** – se la parola c'è si incrementa il contatore, altrimenti aggiungi.

### Caso d'uso 2 – Parola nuova

**a) Input** – prima occorrenza

**b) Output** – i due array crescono di un elemento

**c) Variabili di supporto** – `tmp_parole`, `tmp_conta`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – realloc(NULL, ...) alla prima parola funziona come malloc.

### Caso d'uso 3 – Liberazione

**a) Input** – fine

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – free di ogni parole[i], poi di parole e conta.
