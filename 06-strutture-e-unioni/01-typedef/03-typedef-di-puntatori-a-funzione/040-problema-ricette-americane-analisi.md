# Analisi – 040-problema-ricette-americane.c

## 1. Problema

Nel laboratorio di cucina gli studenti convertono le unità delle ricette americane: scrivono quantità e sigla (cup, tbsp, oz, lb, F) e il programma risponde con la quantità nel sistema metrico. Una quantità 0 termina.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Conversione` | `typedef double (*Conversione)(double);` | funzione che converte una quantità |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `sigle`, `arrivo` | `const char *[]` | 5 | Sigla di partenza e unità di arrivo |
| `converti` | `Conversione[]` | 5 | Funzioni di conversione, parallele alle sigle |
| `sigla` | `char[]` | 10 | Sigla letta |
| `quantita` | `double` | — | Quantità letta |

| Funzione | Compito |
|----------|---------|
| `da_tazze, da_cucchiai` | Volume in ml |
| `da_once, da_libbre` | Peso in grammi |
| `da_fahrenheit` | Temperatura in gradi Celsius |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Conversione

**a) Input** – `2 cup`

**b) Output** – "2 cup = 473.2 ml"

**c) Variabili di supporto** – `k`

**d) Vincoli** – sigla tra quelle della tabella

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cercare la sigla con strcmp; chiamare converti[k](quantita).

### Caso d'uso 2 – Temperatura del forno

**a) Input** – `350 F`

**b) Output** – "350 F = 176.7 gradi C"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stessa chiamata: la tabella contiene funzioni con lo stesso prototipo.

### Caso d'uso 3 – Sigla sconosciuta

**a) Input** – `4 pinch`

**b) Output** – `Unita' "pinch" sconosciuta.`

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la ricerca arriva a UNITA senza trovare la sigla.
