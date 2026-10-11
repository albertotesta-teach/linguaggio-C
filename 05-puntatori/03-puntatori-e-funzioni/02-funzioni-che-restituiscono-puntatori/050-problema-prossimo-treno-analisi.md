# Analisi – 050-problema-prossimo-treno.c

## 1. Problema

Gli orari dei treni per il capoluogo sono in ordine crescente. Lo studente
pendolare inserisce l'ora attuale e il programma mostra il prossimo treno e
i due successivi con l'attesa in minuti; dopo l'ultimo treno indica il
primo del giorno dopo.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `orari` | `int[]` | 9 | Partenze in minuti dalla mezzanotte, crescenti |
| `fine` | `const int *` | — | Subito dopo l'ultimo orario |
| `p` | `const int *` | — | Prossimo treno, `NULL` se finiti |
| `q` | `const int *` | — | Scorre i treni da mostrare |
| `adesso` | `int` | — | Ora attuale in minuti |

| Funzione | Compito |
|----------|---------|
| `prossimo(orari, n, adesso)` | Puntatore al primo orario non precedente all'ora attuale |
| `stampa_orario(minuti)` | Stampa hh:mm |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tre treni

**a) Input** – `7:20`

**b) Output** – 07:40 (tra 20 min), 08:25 (tra 65 min), 12:05 (tra 285 min)

**c) Variabili di supporto** – `p`, `q`

**d) Vincoli** – al massimo 3 treni

**e) Assunzioni** – orari già ordinati

**f) Algoritmo in linguaggio naturale**
1. `prossimo` avanza finché l'orario è minore di `adesso`.
2. Da `p` stampare i treni con `q` da `p` a `p + 3`, senza superare `fine`.

### Caso d'uso 2 – Fine della tabella

**a) Input** – `18:00`

**b) Output** – solo 21:10

**c) Variabili di supporto** – `fine`

**d) Vincoli** – `p + 1` e `p + 2` possono essere oltre la fine: il ciclo
controlla `q < fine`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la condizione del ciclo combina i
due limiti: `q < fine && q < p + 3`.

### Caso d'uso 3 – Nessun treno

**a) Input** – `22:15`

**b) Output** – "nessun treno fino a domani, primo alle 06:12"

**c) Variabili di supporto** – `p` = `NULL`

**d) Vincoli** – con `NULL` non si scorre nulla

**e) Assunzioni** – il primo treno del giorno dopo è uguale a quello di oggi

**f) Algoritmo in linguaggio naturale** – se `prossimo` arriva alla fine
restituisce `NULL`; il main stampa `orari[0]`.
