# Analisi – 040-problema-scambio-posti.c

## 1. Problema

In laboratorio due studenti devono scambiarsi la postazione. Il programma mostra che scambiare le intere struct (nome compreso) non sposta nessuno, mentre lo scambio corretto riguarda solo i campi fila e pc. Due studenti con la stessa postazione sono segnalati.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Postazione` | `nome, fila, pc` | studente e postazione assegnata |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `primo`, `secondo` | `Postazione` | — | Schede lette |
| `sbagliato_primo`, `sbagliato_secondo`, `temp` | `Postazione` | — | Scambio delle schede intere |
| `appoggio` | `int` | — | Scambio dei singoli campi |

| Funzione | Compito |
|----------|---------|
| `main` | Scambio con variabile di appoggio |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Scambio

**a) Input** – `Sofia 2 5`, `Luca 3 1`

**b) Output** – scambio sbagliato: ognuno al suo posto; corretto: Sofia fila 3 pc 1, Luca fila 2 pc 5

**c) Variabili di supporto** – `appoggio`

**d) Vincoli** – il nome non si scambia

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scambiare fila e pc con una variabile int di appoggio.

### Caso d'uso 2 – Stessa postazione

**a) Input** – due studenti con `2 5`

**b) Output** – "I due studenti hanno gia' la stessa postazione"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare i campi fila e pc.

### Caso d'uso 3 – Dati errati

**a) Input** – fila non positiva

**b) Output** – "Dati non validi."

**c) Variabili di supporto** – —

**d) Vincoli** – fila > 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuno scambio.
