# Analisi – 060-problema-calcolatrice-operazioni.c

## 1. Problema

La calcolatrice del corso di recupero legge un'operazione scritta a parole e due interi. La parola diventa un enum con una tabella di nomi; calcola sceglie il calcolo con uno switch e restituisce 0 se l'operazione è impossibile.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Operazione` | `SOMMA ... POTENZA, NUM_OPERAZIONI, NON_VALIDA` | operazione richiesta |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `parola` | `char[]` | 16 | Operazione letta |
| `a`, `b`, `risultato` | `int` | — | Operandi e risultato |
| `op` | `Operazione` | — | Operazione riconosciuta |

| Funzione | Compito |
|----------|---------|
| `da_testo(parola)` | Costante corrispondente, NON_VALIDA se non esiste |
| `calcola(op, a, b, &risultato)` | switch; 0 per divisione per zero o esponente negativo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Operazioni

**a) Input** – `somma 12 30`; `quoziente 17 5`; `resto 17 5`; `potenza 2 10`

**b) Output** – 42; 3; 2; 1024

**c) Variabili di supporto** – `risultato`

**d) Vincoli** – quoziente intero

**e) Assunzioni** – interi senza overflow

**f) Algoritmo in linguaggio naturale** – QUOZIENTE e RESTO condividono il controllo b != 0 con due case consecutivi.

### Caso d'uso 2 – Impossibile

**a) Input** – `quoziente 4 0`; `potenza 2 -1`

**b) Output** – "impossibile."

**c) Variabili di supporto** – —

**d) Vincoli** – b diverso da 0, esponente non negativo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – calcola restituisce 0.

### Caso d'uso 3 – Parola sconosciuta

**a) Input** – `radice 9 2`

**b) Output** – "Operazione \"radice\" sconosciuta."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – da_testo restituisce NON_VALIDA, che sta dopo NUM_OPERAZIONI.
