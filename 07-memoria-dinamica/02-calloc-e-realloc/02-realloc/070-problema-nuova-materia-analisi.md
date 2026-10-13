# Analisi – 070-problema-nuova-materia.c

## 1. Problema

A metà anno il tabellone dei voti riceve una materia in più. Il tabellone è un blocco con le righe una dopo l'altra: aggiungere una colonna cambia la lunghezza di ogni riga, quindi dopo la realloc i voti si spostano nelle nuove posizioni, partendo dall'ultimo per non sovrascrivere nulla, e poi si scrive la nuova colonna.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `tab` | `double *` | righe × colonne (heap) | Voti; (r, c) in tab[r × colonne + c] |
| `materie` | `char[][4]` | 8 × 4 | Nomi delle materie |
| `righe`, `colonne` | `int` | — | Studenti e materie |

| Funzione | Compito |
|----------|---------|
| `aggiungi_colonna(&tab, righe, colonne)` | realloc e spostamento all'indietro; 0 se fallisce |
| `stampa(tab, righe, colonne, materie)` | Tabellone con le medie |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Nuova materia

**a) Input** – `3 3`, `ITA MAT ING`, tre righe di voti, poi `M CIV 8 6 9`

**b) Output** – "CIV aggiunta: tabellone 3 x 4" e medie ricalcolate

**c) Variabili di supporto** – `tmp`

**d) Vincoli** – al massimo 8 materie

**e) Assunzioni** – nomi di 3 lettere

**f) Algoritmo in linguaggio naturale** – tmp[r × (colonne + 1) + c] = tmp[r × colonne + c] per r e c decrescenti.

### Caso d'uso 2 – Stampa

**a) Input** – `S`

**b) Output** – tabellone con le medie per studente

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – —

### Caso d'uso 3 – Nome non valido

**a) Input** – `M ab 7 7 7`

**b) Output** – "Nome della materia: 3 lettere."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna realloc.
