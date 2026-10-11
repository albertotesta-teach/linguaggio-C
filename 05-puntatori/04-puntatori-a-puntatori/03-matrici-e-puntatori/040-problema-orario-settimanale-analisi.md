# Analisi – 040-problema-orario-settimanale.c

## 1. Problema

L'orario settimanale della 3B è una matrice giorni × ore con il codice della materia in ogni cella. Lo studente chiede un giorno e il programma stampa le sei lezioni; alla fine stampa le ore settimanali di ogni materia.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `orario` | `int[][]` | 5 × 6 | Codice della materia per giorno e ora |
| `materie` | `const char *[]` | 7 | Nome della materia, l'indice è il codice |
| `giorni` | `const char *[]` | 5 | Nomi dei giorni |
| `g` | `int` | — | Giorno scelto |

| Funzione | Compito |
|----------|---------|
| `stampa_giorno(orario[g], ORE, materie)` | Stampa una riga ricevuta come `const int *` |
| `ore_settimanali(orario, GIORNI, m)` | Conta le celle della materia con un puntatore a riga |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Orario di un giorno

**a) Input** – `3`

**b) Output** – Mercoledì: Informatica (3 ore), Inglese, Ed. fisica (2 ore)

**c) Variabili di supporto** – `orario[g - 1]`

**d) Vincoli** – la riga di una matrice si passa come un array

**e) Assunzioni** – giorni numerati da 1

**f) Algoritmo in linguaggio naturale** – passare `orario[g - 1]` a `stampa_giorno`, che stampa `materie[ore[h]]`.

### Caso d'uso 2 – Ore per materia

**a) Input** – tutta la matrice

**b) Output** – Italiano 6, Matematica 5, Informatica 7, ...

**c) Variabili di supporto** – `riga`

**d) Vincoli** – la matrice arriva come `const int (*)[ORE]`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scorrere le righe con `riga++` e contare le celle uguali al codice.

### Caso d'uso 3 – Giorno non valido

**a) Input** – `6`

**b) Output** – "Giorno non valido."

**c) Variabili di supporto** – nessuna

**d) Vincoli** – la riga si usa solo con indice valido

**e) Assunzioni** – un input non numerico termina

**f) Algoritmo in linguaggio naturale** – controllare l'intervallo 1-5.
