# Analisi – 060-problema-noleggio-bici.c

## 1. Problema

Il bike sharing comunale presta bici agli studenti con la tessera. Le funzioni di ricerca restituiscono il puntatore alla prima bici libera o alla bici di una tessera; noleggia e restituisci lavorano su una sola bici tramite il suo indirizzo. I primi 30 minuti sono gratuiti.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Bici` | `codice, noleggiata, tessera, inizio, minuti_totali` | bici del parco |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `parco` | `Bici[]` | 4 | Bici |
| `bici` | `Bici *` | — | Bici trovata |
| `tessera`, `ore`, `minuti` | `int` | — | Dati del comando |
| `uso` | `int` | — | Minuti di utilizzo |

| Funzione | Compito |
|----------|---------|
| `prima_libera(b, n)` | Puntatore alla prima bici libera |
| `bici_di(b, n, tessera)` | Puntatore alla bici della tessera |
| `noleggia(b, tessera, ora)` | Segna la bici come noleggiata |
| `restituisci(b, ora)` | Minuti di uso, -1 se l'ora è errata |
| `costo(minuti)` | 0.50 euro ogni 30 minuti iniziati dopo i primi 30 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Noleggio

**a) Input** – `N 3301 14:10`

**b) Output** – "Bici B-01 alla tessera 3301."

**c) Variabili di supporto** – `bici`

**d) Vincoli** – una bici per tessera

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – prima_libera, poi noleggia(bici, ...).

### Caso d'uso 2 – Restituzione

**a) Input** – `R 3301 15:25`

**b) Output** – "Bici B-01 restituita: 75 minuti, 1.00 euro."

**c) Variabili di supporto** – `uso`

**d) Vincoli** – —

**e) Assunzioni** – stessa giornata

**f) Algoritmo in linguaggio naturale** – bici_di trova la bici; restituisci aggiorna i minuti.

### Caso d'uso 3 – Errori

**a) Input** – `N 3301 14:20`; `R 3303 15:30`

**b) Output** – "ha gia' una bici"; "non ha bici"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – i puntatori NULL vengono controllati prima dell'uso.
