# Analisi – 080-problema-anagrammi.c

## 1. Problema

Per un gioco di parole bisogna trovare, in un elenco, gli anagrammi di una
parola data: parole con le stesse lettere ripetute lo stesso numero di
volte, in un altro ordine. Maiuscole e caratteri non alfabetici non contano;
la parola stessa non è considerata un suo anagramma.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `elenco` | `char[][]` | 12 × 20 | Parole tra cui cercare |
| `parola` | `char[]` | 30 | Parola inserita |
| `conta_a`, `conta_b` | `int[]` | 26 | "Impronta": occorrenze di ogni lettera |
| `trovati` | `int` | — | Anagrammi trovati |

| Funzione | Compito |
|----------|---------|
| `conta_lettere` | Riempie l'impronta con `isalpha` e `tolower` |
| `sono_anagrammi` | Confronta le impronte ed esclude la stessa parola |
| `uguali_senza_maiuscole` | Confronto con `tolower` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Più anagrammi, con maiuscole

**a) Input** – `Roma`

**b) Output** – amor, ramo, Mora, orma, armo (5 anagrammi)

**c) Variabili di supporto** – `conta_a`, `conta_b`

**d) Vincoli** – la lettera `c` corrisponde alla cella `tolower(c) - 'a'`

**e) Assunzioni** – lettere senza accenti

**f) Algoritmo in linguaggio naturale**
1. Calcolare l'impronta della parola inserita e di ogni parola dell'elenco.
2. Se le 26 celle coincidono e le parole non sono uguali, è un anagramma.

### Caso d'uso 2 – La parola stessa

**a) Input** – `Tale`

**b) Output** – solo `tela`: `tale` è esclusa perché è la stessa parola

**c) Variabili di supporto** – esito di `uguali_senza_maiuscole`

**d) Vincoli** – il confronto che esclude la parola ignora le maiuscole

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1, con la condizione aggiuntiva.

### Caso d'uso 3 – Nessun anagramma

**a) Input** – `lieto`

**b) Output** – "0 anagrammi"

**c) Variabili di supporto** – `trovati`

**d) Vincoli** – il confronto delle impronte si ferma alla prima cella diversa (flag)

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1; nessuna parola
supera il controllo.
