# Analisi – 080-problema-ricerca-puntatore.c

## 1. Problema

Il tecnico del laboratorio cerca un computer per numero di inventario e registra guasti, riparazioni e aggiornamenti della RAM. cerca restituisce l'indirizzo della scheda trovata, o NULL: il chiamante modifica direttamente l'elemento dell'array con ->.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Computer` | `inventario, postazione, ram_gb, guasti, funzionante` | scheda di inventario |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `laboratorio` | `Computer[]` | 5 | Schede dei computer |
| `pc` | `Computer *` | — | Scheda trovata |
| `codice`, `ram` | `char[]`, `int` | 8, — | Dati del comando |

| Funzione | Compito |
|----------|---------|
| `cerca(elenco, n, inventario)` | Indirizzo dell'elemento, NULL se assente |
| `stampa(c)` | Riceve const Computer * |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Guasto

**a) Input** – `G PC-014`

**b) Output** – "Guasto registrato sulla postazione 3."

**c) Variabili di supporto** – `pc->guasti`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca restituisce &laboratorio[2]; pc->guasti++.

### Caso d'uso 2 – RAM

**a) Input** – `U PC-012 16`; `U PC-015 8`

**b) Output** – "PC-012 ora ha 16 GB."; "La RAM si puo' solo aumentare"

**c) Variabili di supporto** – `pc->ram_gb`

**d) Vincoli** – solo aumenti

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare il valore letto con il campo.

### Caso d'uso 3 – Codice assente

**a) Input** – `G PC-099`

**b) Output** – "PC-099 non e' nell'inventario."

**c) Variabili di supporto** – `pc` = NULL

**d) Vincoli** – con NULL non si usa ->

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllare il puntatore prima di usarlo.
