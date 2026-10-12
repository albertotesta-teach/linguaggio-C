# Analisi – 080-problema-tratte-ferroviarie.c

## 1. Problema

Per la gita a Milano si cerca il collegamento che arriva prima partendo non prima di un orario dato: una tratta diretta oppure due tratte con un cambio, con almeno 5 minuti tra arrivo e partenza. A pari arrivo vince il collegamento più breve. Le struct hanno tre livelli: t.partenza.ora.ore.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Orario` | `ore, minuti` | ora del giorno |
| `Fermata` | `stazione, ora` | stazione con il suo orario |
| `Tratta` | `treno, partenza, arrivo` | tratta come due Fermata |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `orario` | `Tratta[]` | 7 | Tratte del mattino |
| `da`, `a` | `char[]` | 16 | Stazioni richieste |
| `dalle` | `Orario` | — | Orario minimo di partenza |
| `migliore_primo`, `migliore_secondo` | `int` | — | Tratte della soluzione (-1 se nessuna) |
| `arrivo_migliore`, `partenza_migliore` | `int` | — | Minuti della soluzione migliore |

| Funzione | Compito |
|----------|---------|
| `in_minuti(o)` | Minuti dalla mezzanotte |
| `migliore(arrivo, partenza, ...)` | 1 se arriva prima o, a pari arrivo, parte dopo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Con un cambio

**a) Input** – `Alessandria Milano 07:00`

**b) Output** – R 10201 fino a Tortona, RV 2201 fino a Milano: arrivo 08:30, durata 1 h 25 min

**c) Variabili di supporto** – `migliore_primo`, `migliore_secondo`

**d) Vincoli** – cambio di almeno 5 minuti

**e) Assunzioni** – orari dello stesso giorno

**f) Algoritmo in linguaggio naturale** – per ogni tratta da Alessandria provare la tratta diretta e ogni seconda tratta che parte dalla stazione di arrivo della prima.

### Caso d'uso 2 – Pari arrivo

**a) Input** – `Alessandria Milano 06:45`

**b) Output** – il percorso via Tortona (1 h 25 min) invece di quello via Pavia (1 h 40 min)

**c) Variabili di supporto** – `partenza_migliore`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – migliore preferisce la partenza più tarda quando l'arrivo è uguale.

### Caso d'uso 3 – Diretto

**a) Input** – `Tortona Milano 08:00`

**b) Output** – RV 2203, "diretto"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la tratta diretta arriva prima di ogni combinazione.

### Caso d'uso 4 – Nessun collegamento

**a) Input** – `Alessandria Genova 07:00`

**b) Output** – "Nessun collegamento da Alessandria a Genova dopo le 07:00."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – migliore_primo resta -1.
