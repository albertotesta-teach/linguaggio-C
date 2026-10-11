# Analisi – 070-problema-riordino-scorte.c

## 1. Problema

Il tecnico del distributore automatico ha 5 confezioni da 12 pezzi e le
assegna una alla volta al prodotto (acqua, succhi, snack) che in quel
momento ha la scorta più bassa. Il programma mostra a ogni giro il prodotto
rifornito e le scorte aggiornate.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `acqua`, `succhi`, `snack` | `int` | — | Scorte dei tre prodotti |
| `minimo` | `int *` | — | Indirizzo della scorta più bassa |
| `giro` | `int` | — | Confezione corrente |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Scelta della scorta minima

**a) Input** – acqua 14, succhi 6, snack 9

**b) Output** – "Confezione 1 -> succhi", succhi 18

**c) Variabili di supporto** – `minimo`

**d) Vincoli** – il confronto avviene tra i valori (`succhi < *minimo`), ma si
memorizza l'indirizzo (`minimo = &succhi`)

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. `minimo = &acqua`.
2. Se `succhi < *minimo`, `minimo = &succhi`; se `snack < *minimo`, `minimo = &snack`.
3. `*minimo = *minimo + 12`.

### Caso d'uso 2 – Nome del prodotto rifornito

**a) Input** – `minimo`

**b) Output** – "acqua", "succhi" o "snack"

**c) Variabili di supporto** – nessuna

**d) Vincoli** – si confronta il puntatore con gli indirizzi delle variabili

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `minimo == &acqua` stampare
"acqua", e così via.

### Caso d'uso 3 – Parità

**a) Input** – due scorte uguali e minime

**b) Output** – viene rifornito il primo prodotto controllato

**c) Variabili di supporto** – nessuna

**d) Vincoli** – il confronto usa `<`: un valore uguale non sostituisce il minimo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1.
