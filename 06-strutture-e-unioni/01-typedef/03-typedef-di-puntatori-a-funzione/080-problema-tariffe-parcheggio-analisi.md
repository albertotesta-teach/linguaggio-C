# Analisi – 080-problema-tariffe-parcheggio.c

## 1. Problema

Il parcheggio multipiano offre tre tariffe: oraria (1.50 euro per ora iniziata), prima ora gratis (poi 2.00 euro per ora iniziata) e giornaliera (9.00 euro fissi). Per ogni durata letta in minuti il programma stampa il costo con ogni tariffa e quella più conveniente; 0 termina.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Tariffa` | `typedef double (*Tariffa)(int minuti);` | funzione che calcola il costo di una sosta |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `const char *[]` | 3 | Nomi delle tariffe |
| `tariffe` | `const Tariffa[]` | 3 | Funzioni di calcolo |
| `migliore` | `Tariffa` | — | Tariffa restituita da piu_conveniente |
| `minuti` | `int` | — | Durata letta |

| Funzione | Compito |
|----------|---------|
| `oraria, prima_ora_gratis, giornaliera` | Costo di una sosta |
| `ore_iniziate(minuti)` | Ore arrotondate per eccesso |
| `piu_conveniente(minuti, tariffe, n)` | Restituisce la tariffa con il costo più basso |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Sosta breve

**a) Input** – `45`

**b) Output** – conviene "prima ora gratis" (0.00 euro)

**c) Variabili di supporto** – `migliore`

**d) Vincoli** – a parità vale la prima tariffa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – piu_conveniente confronta i costi e restituisce un puntatore a funzione.

### Caso d'uso 2 – Sosta lunga

**a) Input** – `500`

**b) Output** – conviene "giornaliera" (9.00 euro)

**c) Variabili di supporto** – `t`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il nome si trova confrontando migliore con gli elementi della tabella.

### Caso d'uso 3 – Durata non valida

**a) Input** – `-3`

**b) Output** – "Durata non valida."

**c) Variabili di supporto** – —

**d) Vincoli** – durata positiva

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il valore negativo non termina il programma.
