# Analisi – 080-problema-risparmio-memoria.c

## 1. Problema

L'inventario del laboratorio contiene componenti, strumenti e manuali, ognuno con dati diversi. Il programma confronta una struct con tutti i campi e una struct con i dati specifici in una union, e calcola la memoria occupata e risparmiata per il numero di articoli letto.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `ArticoloCompleto` | `codice, tipo, componente, strumento, manuale` | tutti i campi |
| `ArticoloCompatto` | `codice, tipo, union dati {componente, strumento, manuale}` | alternative sovrapposte |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `esempio` | `ArticoloCompatto` | — | Articolo inizializzato come componente |
| `articoli` | `long` | — | Numero letto |
| `completa`, `compatta` | `long` | — | Byte occupati nelle due soluzioni |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Dimensioni

**a) Input** – avvio

**b) Output** – ArticoloCompleto 96 byte, ArticoloCompatto 48 byte

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – dimensioni di un PC a 64 bit

**f) Algoritmo in linguaggio naturale** – sizeof di ogni tipo: la union occupa quanto la sua alternativa più grande (Strumento, 32 byte).

### Caso d'uso 2 – Risparmio

**a) Input** – `500`

**b) Output** – 48000 e 24000 byte, risparmio 24000 byte (50%)

**c) Variabili di supporto** – `completa`, `compatta`

**d) Vincoli** – da 1 a 100000 articoli

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – articoli × sizeof di ciascuna soluzione.

### Caso d'uso 3 – Numero non valido

**a) Input** – `0`

**b) Output** – "Numero non valido (da 1 a 100000)."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessun calcolo.
