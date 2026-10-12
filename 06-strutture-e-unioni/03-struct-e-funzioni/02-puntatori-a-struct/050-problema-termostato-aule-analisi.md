# Analisi – 050-problema-termostato-aule.c

## 1. Problema

Ogni aula ha un termostato che riceve una misura ogni 15 minuti e accende o spegne il termosifone con un'isteresi di mezzo grado. La stessa funzione aggiorna lavora sui termostati di due aule ricevendone l'indirizzo; riepilogo li legge con const Termostato *.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Termostato` | `aula, obiettivo, ultima, minima, massima, acceso, accensioni` | stato del termostato di un'aula |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `a12`, `lab` | `Termostato` | — | Termostati delle due aule |
| `misure_a12`, `misure_lab` | `double[]` | 8 | Misure della mattina |

| Funzione | Compito |
|----------|---------|
| `aggiorna(t, misura)` | Registra la misura, aggiorna minima e massima, decide lo stato |
| `riepilogo(t)` | Obiettivo, minima, massima, accensioni |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Accensione

**a) Input** – 17.8 in A1-12 (obiettivo 20)

**b) Output** – acceso

**c) Variabili di supporto** – `t->acceso`, `t->accensioni`

**d) Vincoli** – si accende sotto obiettivo - 0.5

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se spento e misura < 19.5 accendere e contare.

### Caso d'uso 2 – Isteresi

**a) Input** – 20.2 e 19.6 dopo lo spegnimento

**b) Output** – resta spento

**c) Variabili di supporto** – —

**d) Vincoli** – tra 19.5 e 20.5 lo stato non cambia

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna delle due condizioni è vera.

### Caso d'uso 3 – Riepilogo

**a) Input** – fine della mattina

**b) Output** – A1-12: minima 17.8, massima 20.6, accensioni 2

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – riepilogo legge i campi con ->.
