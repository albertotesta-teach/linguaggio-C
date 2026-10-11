# Analisi – 050-problema-classifica-per-puntatori.c

## 1. Problema

Alla gara di orientamento la classifica provvisoria va corretta scambiando due concorrenti alla volta. Nomi e tempi restano nei loro array: la classifica è fatta di due array di puntatori paralleli, e ogni scambio scambia solo i puntatori. Dopo ogni scambio il programma controlla se i tempi sono in ordine.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `const char *[]` | 5 | Nomi nell'ordine di iscrizione |
| `tempi` | `int[]` | 5 | Tempi in secondi, parallelo a `nomi` |
| `nome_al_posto` | `const char *[]` | 5 | Nome alla posizione i della classifica |
| `tempo_al_posto` | `const int *[]` | 5 | Tempo alla posizione i, puntatore dentro `tempi` |

| Funzione | Compito |
|----------|---------|
| `scambia_nomi(&a, &b)`, `scambia_tempi(&a, &b)` | Scambiano due puntatori (parametri `**`) |
| `stampa(nomi, tempi, n)` | Classifica con controllo dell'ordine |
| `in_ordine(tempi, n)` | 1 se i tempi sono crescenti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Scambio di due posizioni

**a) Input** – `S 1 2`

**b) Output** – Alice prima, Pietro secondo

**c) Variabili di supporto** – `nome_al_posto`, `tempo_al_posto`

**d) Vincoli** – nomi e tempi si scambiano insieme; i dati originali non si spostano

**e) Assunzioni** – posizioni numerate da 1

**f) Algoritmo in linguaggio naturale** – scambiare gli elementi `a - 1` e `b - 1` dei due array di puntatori.

### Caso d'uso 2 – Controllo dell'ordine

**a) Input** – dopo `S 4 5`

**b) Output** – "Classifica in ordine di tempo."

**c) Variabili di supporto** – `ordinata`

**d) Vincoli** – si legge il tempo attraverso il puntatore: `*tempi[i]`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare ogni tempo con il successivo.

### Caso d'uso 3 – Posizioni non valide

**a) Input** – `S 0 9`

**b) Output** – "Posizioni non valide." e fine

**c) Variabili di supporto** – nessuna

**d) Vincoli** – un indice fuori dall'array non si usa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllare `1 ≤ a, b ≤ 5`.
