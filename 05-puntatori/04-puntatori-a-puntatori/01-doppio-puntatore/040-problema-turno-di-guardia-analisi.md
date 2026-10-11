# Analisi – 040-problema-turno-di-guardia.c

## 1. Problema

Lo sportello pomeridiano di tutoraggio è coperto a rotazione da cinque docenti. Il programma indica chi è di turno; con `T` il docente svolge un'ora e il turno passa al successivo, con `S` il docente è assente e il turno passa senza ore. Con `Q` stampa le ore svolte da ciascuno.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `char[][]` | 5 × 12 | Cognomi dei docenti |
| `ore` | `int[]` | 5 | Ore svolte, parallelo a `nomi` |
| `turno` | `int *` | — | Elemento del docente di turno |
| `comando` | `char` | — | T, S o Q |

| Funzione | Compito |
|----------|---------|
| `passa_turno(&turno, ore, n)` | Sposta il puntatore del main all'elemento successivo, con ritorno al primo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ora svolta

**a) Input** – `T` con Rossi di turno

**b) Output** – "Rossi ha svolto la sua 1a ora", poi di turno Bianco

**c) Variabili di supporto** – `*turno`, `turno - ore`

**d) Vincoli** – il nome si ricava dalla posizione del puntatore

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – incrementare `*turno`, stampare `nomi[turno - ore]` e chiamare `passa_turno(&turno, ...)`.

### Caso d'uso 2 – Rotazione

**a) Input** – sei comandi T/S di fila

**b) Output** – dopo Conti il turno torna a Rossi

**c) Variabili di supporto** – `*turno` dentro la funzione

**d) Vincoli** – la funzione cambia il puntatore del chiamante: riceve `int **`

**e) Assunzioni** – cinque docenti in ordine fisso

**f) Algoritmo in linguaggio naturale** – se `*turno` è l'ultimo elemento, `*turno = ore`; altrimenti `(*turno)++`.

### Caso d'uso 3 – Assenza

**a) Input** – `S` con Greco di turno

**b) Output** – "Greco assente, turno al successivo"; ore di Greco invariate

**c) Variabili di supporto** – nessuna

**d) Vincoli** – il valore puntato non cambia, cambia solo il puntatore

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – chiamare solo `passa_turno`.
