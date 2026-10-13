# Analisi – 080-problema-archivio-dei-sensori.c

## 1. Problema

Nelle aule ci sono sensori di temperatura; ogni sensore ha un blocco con una lettura per ogni ora del periodo di osservazione. L'array dei sensori si alloca con calloc (blocchi a NULL, ore a 0). Quando il periodo cambia ogni blocco si ridimensiona con realloc; le ore nuove sono MANCANTE. Ogni sensore tiene la sua dimensione, così un fallimento non rende incoerenti gli altri.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Sensore` | `aula[12], ore, letture (double *)` | un sensore con il suo blocco |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `sensori` | `Sensore *` | n (heap, calloc) | Sensori delle aule |
| `ore`, `ora` | `int` | — | Periodo e ora della lettura |
| `gradi` | `double` | — | Temperatura letta |
| `trovato` | `int` | — | Sensore dell'aula indicata |

| Funzione | Compito |
|----------|---------|
| `cambia_periodo(&sensore, ore)` | realloc del blocco; ore nuove MANCANTE; 0 se fallisce |
| `riepilogo(&sensore)` | Letture valide, media, minimo e massimo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Periodo non impostato

**a) Input** – `2 LAB1 3B`, poi `L LAB1 1 20`

**b) Output** – "Periodo non ancora impostato (comando P)."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ore vale 0 dopo calloc.

### Caso d'uso 2 – Letture

**a) Input** – `P 4`, `L LAB1 1 19.5`, `L LAB1 2 21`, `L 3B 4 23.5`, `L 3B 5 22`

**b) Output** – letture registrate; "Ora fuori dal periodo (1-4)."

**c) Variabili di supporto** – `letture`

**d) Vincoli** – ore da 1 a 168

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – realloc(NULL, ...) al primo periodo.

### Caso d'uso 3 – Periodo più corto

**a) Input** – `P 2`, `M`

**b) Output** – 3B: letture 0 su 2 (la lettura dell'ora 4 si perde)

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – realloc riduce il blocco.

### Caso d'uso 4 – Periodo più lungo

**a) Input** – `P 6`, `M`

**b) Output** – LAB1: letture 2 su 6

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – le ore da 3 a 6 diventano MANCANTE.

### Caso d'uso 5 – Fine

**a) Input** – `Q`

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – free di ogni blocco di letture, poi dell'array.
