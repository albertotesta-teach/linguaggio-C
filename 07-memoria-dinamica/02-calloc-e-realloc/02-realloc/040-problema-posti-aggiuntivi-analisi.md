# Analisi – 040-problema-posti-aggiuntivi.c

## 1. Problema

Il corso pomeridiano di fotografia parte con un certo numero di posti; la segreteria può aggiungerne o toglierne. Il blocco degli iscritti cambia dimensione con realloc dentro cambia_capienza, che aggiorna puntatore e capienza solo se realloc riesce. Non si possono togliere posti già occupati.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Iscritto` | `nome[20], classe[4]` | un iscritto al corso |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `iscritti` | `Iscritto *` | capienza (heap) | Iscritti in ordine di iscrizione |
| `capienza`, `n` | `int` | — | Posti e iscritti |
| `k` | `int` | — | Posti da aggiungere o togliere |

| Funzione | Compito |
|----------|---------|
| `cambia_capienza(&iscritti, &capienza, nuova)` | realloc con puntatore temporaneo; 0 se fallisce |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Corso pieno

**a) Input** – `2`, poi tre iscrizioni

**b) Output** – "Corso pieno (2 posti): Sara in attesa."

**c) Variabili di supporto** – `n`

**d) Vincoli** – al massimo 60 posti

**e) Assunzioni** – nomi di una parola

**f) Algoritmo in linguaggio naturale** – iscrivere solo se n < capienza.

### Caso d'uso 2 – Aggiunta di posti

**a) Input** – `A 3`

**b) Output** – "Nuova capienza: 5 posti (120 byte)"

**c) Variabili di supporto** – `tmp`

**d) Vincoli** – capienza + k ≤ 60

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – tmp = realloc(...); se non è NULL si aggiornano puntatore e capienza.

### Caso d'uso 3 – Togliere posti

**a) Input** – `T 4` con 3 iscritti su 5; `T 2`

**b) Output** – "Posti liberi solo 2..."; "Nuova capienza: 3 posti"

**c) Variabili di supporto** – —

**d) Vincoli** – capienza - k ≥ n e ≥ 1

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ridurre solo la parte libera.

### Caso d'uso 4 – Elenco

**a) Input** – `E`

**b) Output** – iscritti e posti liberi

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – —
