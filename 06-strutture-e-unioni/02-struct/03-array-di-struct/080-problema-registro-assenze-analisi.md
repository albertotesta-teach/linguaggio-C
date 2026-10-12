# Analisi – 080-problema-registro-assenze.c

## 1. Problema

A fine gennaio il coordinatore controlla le ore di assenza di ogni studente da settembre a gennaio. Il programma calcola totale e percentuale sulle ore svolte e stima le assenze di fine anno proiettando la percentuale sul monte ore (1056 ore, limite 264). Segnala gli studenti a rischio e quelli da tenere d'occhio e il mese con più assenze.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Studente` | `nome, ore_assenza[5]` | assenze mensili di uno studente |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `classe` | `Studente[]` | 5 | Assenze mensili |
| `ore_svolte` | `int[]` | 5 | Ore di lezione di ogni mese |
| `per_mese` | `int[]` | 5 | Assenze della classe per mese |
| `percentuale`, `stima` | `double` | — | Calcoli per studente |

| Funzione | Compito |
|----------|---------|
| `main` | Tabella, stime e mese con più assenze |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Studente a rischio

**a) Input** – Bellini: 135 ore

**b) Output** – 26.2%, stima 276: "a rischio"

**c) Variabili di supporto** – `stima`

**d) Vincoli** – limite 264 ore

**e) Assunzioni** – l'andamento resta uguale

**f) Algoritmo in linguaggio naturale** – stima = percentuale × monte ore.

### Caso d'uso 2 – Attenzione

**a) Input** – Donati: 107 ore

**b) Output** – 20.7%, stima 219: "attenzione"

**c) Variabili di supporto** – —

**d) Vincoli** – oltre l'80% del limite

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare la stima con 0.8 × 264.

### Caso d'uso 3 – Mese peggiore

**a) Input** – dati nel programma

**b) Output** – ottobre (81 ore)

**c) Variabili di supporto** – `per_mese`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sommare le colonne e cercare il massimo.
