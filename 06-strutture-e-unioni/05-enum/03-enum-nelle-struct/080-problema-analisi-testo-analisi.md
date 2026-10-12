# Analisi – 080-problema-analisi-testo.c

## 1. Problema

Per le statistiche dei temi il programma legge il testo un carattere alla volta e ricorda solo lo stato: fuori, dentro una parola o dentro un numero. Uno switch sullo stato applica le regole; una parola o un numero si contano quando iniziano, e un numero seguito da una lettera (3B) diventa una parola.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Stato` | `FUORI, IN_PAROLA, IN_NUMERO` | stato dell'automa |
| `Conteggi` | `parole, numeri, punteggiatura, righe` | risultati |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `conteggi` | `Conteggi` | — | Righe, parole, numeri, punteggiatura |
| `riga` | `char[]` | 120 | Riga letta |
| `stato` | `Stato` | — | Stato dell'automa (nella funzione) |

| Funzione | Compito |
|----------|---------|
| `analizza(riga, &conteggi)` | Automa su una riga, che riparte da FUORI |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Testo

**a) Input** – due righe di esempio, poi `FINE`

**b) Output** – "Righe 2, parole 16, numeri 4, segni di punteggiatura 5"

**c) Variabili di supporto** – `conteggi`

**d) Vincoli** – punteggiatura . , ; : ! ?

**e) Assunzioni** – lettere senza accenti

**f) Algoritmo in linguaggio naturale** – per ogni carattere: contare la punteggiatura, poi lo switch sullo stato.

### Caso d'uso 2 – Sigla

**a) Input** – "3B"

**b) Output** – una parola, nessun numero

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – da IN_NUMERO una lettera passa a IN_PAROLA: numeri-- e parole++.

### Caso d'uso 3 – Sigla con lettere e cifre

**a) Input** – "A4"

**b) Output** – una parola

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – in IN_PAROLA le cifre continuano la parola.
