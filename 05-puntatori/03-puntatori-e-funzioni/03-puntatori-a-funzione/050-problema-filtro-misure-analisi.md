# Analisi – 050-problema-filtro-misure.c

## 1. Problema

Un fonometro misura ogni 10 minuti il rumore nella mensa durante la pausa
pranzo. Il referente per la sicurezza vuole contare ed elencare con
l'orario le misure oltre 80 dB, quelle tra 60 e 80 dB e quelle sotto
60 dB.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `db` | `int[]` | 12 | Misure in decibel dalle 12:30 |

| Funzione | Compito |
|----------|---------|
| `conta_se(v, n, condizione)` | Conta gli elementi che soddisfano la condizione |
| `elenca_se(v, n, condizione)` | Stampa orario e valore degli elementi che la soddisfano |
| `rumorosa`, `normale`, `tranquilla` | Le tre condizioni: `int (int)` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Misure oltre soglia

**a) Input** – condizione `rumorosa`

**b) Output** – 3 misure: 13:00 84, 13:10 88, 13:20 82

**c) Variabili di supporto** – `conteggio`

**d) Vincoli** – la soglia è esclusa (80 non è "rumorosa")

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scorrere le misure e contare quelle
per cui `condizione(*p)` vale 1.

### Caso d'uso 2 – Fascia intermedia

**a) Input** – condizione `normale`

**b) Output** – 7 misure da 60 a 80 dB

**c) Variabili di supporto** – nessuna

**d) Vincoli** – le tre condizioni insieme coprono tutte le misure una sola
volta (3 + 7 + 2 = 12)

**e) Assunzioni** – estremi 60 e 80 inclusi

**f) Algoritmo in linguaggio naturale** – la stessa `conta_se` con un'altra
funzione: il ciclo non cambia.

### Caso d'uso 3 – Orario delle misure

**a) Input** – misura di indice 3

**b) Output** – 13:00

**c) Variabili di supporto** – `minuti`

**d) Vincoli** – una misura ogni 10 minuti dalle 12:30

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – minuti = 12 × 60 + 30 + i × 10;
stampare ore e minuti.
