# Analisi – 060-problema-scambio-studenti.c

## 1. Problema

Due studenti chiedono di passare l'uno nella sezione dell'altro. scambia_studenti riceve gli indirizzi delle due schede e scambia i nomi, lasciando ogni scheda nella sua sezione; lo scambio si fa solo se la seconda lingua è la stessa. Una versione per valore mostra che scambiare le copie non cambia nulla.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Scheda` | `nome, sezione, lingua` | studente e sezione |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `prima`, `seconda`, `terza` | `Scheda` | — | Schede degli studenti |
| `nome` | `char[]` | 24 | Appoggio per lo scambio (nella funzione) |

| Funzione | Compito |
|----------|---------|
| `scambia_studenti(a, b)` | Scambia i nomi; 0 se la lingua è diversa |
| `scambia_copie(a, b)` | Versione sbagliata per valore |
| `stampa(s)` | Riceve const Scheda * |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Scambio per valore

**a) Input** – `scambia_copie(prima, seconda)`

**b) Output** – nessun cambiamento nelle schede

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la funzione lavora su due copie.

### Caso d'uso 2 – Scambio riuscito

**a) Input** – Lorenzo (1A, tedesco) e Aurora (1B, tedesco)

**b) Output** – 1A: Aurora Neri; 1B: Lorenzo Fabbri

**c) Variabili di supporto** – `a->nome`, `b->nome`

**d) Vincoli** – stessa seconda lingua

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – tre strcpy con un array di appoggio.

### Caso d'uso 3 – Scambio rifiutato

**a) Input** – con Mattia (francese)

**b) Output** – "Scambio con Mattia Conte rifiutato"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la funzione restituisce 0 senza modificare nulla.
