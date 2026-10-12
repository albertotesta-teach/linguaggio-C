# Analisi – 040-problema-distributore-bevande.c

## 1. Problema

Il distributore di bevande calde ha quattro bevande e accetta monete da 5 a 200 centesimi. prezzo e nome sono switch sulla Bevanda; eroga controlla scorte e credito e restituisce un Esito, il cui messaggio è un altro switch. Tutti gli importi sono in centesimi.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Bevanda` | `CAFFE, CAPPUCCINO, TE, CIOCCOLATA, NUM_BEVANDE` | bevanda |
| `Esito` | `EROGATA, CREDITO_INSUFFICIENTE, ESAURITA` | risultato della scelta |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `scorte` | `int[]` | NUM_BEVANDE | Bevande disponibili |
| `credito` | `int` | — | Centesimi inseriti |
| `scelta` | `Bevanda` | — | Numero letto meno uno |
| `esito` | `Esito` | — | Risultato dell'erogazione |

| Funzione | Compito |
|----------|---------|
| `prezzo(b), nome(b)` | switch su Bevanda |
| `eroga(b, &credito, scorte)` | ESAURITA, CREDITO_INSUFFICIENTE oppure EROGATA scalando credito e scorta |
| `messaggio(e)` | switch su Esito |
| `moneta_valida(c)` | 5, 10, 20, 50, 100 o 200 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Credito insufficiente

**a) Input** – `M 50`, `B 2`

**b) Output** – "cappuccino (0.70 euro): credito insufficiente"

**c) Variabili di supporto** – `credito`

**d) Vincoli** – prezzo in centesimi

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – eroga confronta il credito con prezzo(b) e non modifica nulla.

### Caso d'uso 2 – Erogazione

**a) Input** – `M 20`, `B 2`

**b) Output** – "erogata, buona pausa", credito 0.00

**c) Variabili di supporto** – `scorte`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – credito e scorta diminuiscono.

### Caso d'uso 3 – Esaurita

**a) Input** – `B 3`

**b) Output** – "te' (0.60 euro): esaurita"

**c) Variabili di supporto** – —

**d) Vincoli** – la scorta si controlla prima del credito

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scorte[TE] vale 0.

### Caso d'uso 4 – Errori e resto

**a) Input** – `M 30`; `B 5`; `M 100`, `B 1`, `R`

**b) Output** – "Moneta rifiutata."; "Scelta non valida."; "Resto: 0.50 euro"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il resto azzera il credito.
