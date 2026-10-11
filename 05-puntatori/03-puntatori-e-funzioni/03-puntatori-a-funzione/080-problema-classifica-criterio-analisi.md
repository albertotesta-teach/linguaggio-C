# Analisi – 080-problema-classifica-criterio.c

## 1. Problema

Al triathlon scolastico ogni atleta ha un punteggio in corsa, salto e
lancio. La giuria assegna tre premi: assoluto (totale più alto),
specialista (prova singola migliore) e regolarità (prova peggiore più
alta). Il programma stampa la tabella dei punteggi e i tre vincitori.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `char[][]` | 5 × 12 | Nomi degli atleti |
| `punti` | `int[][]` | 5 × 3 | Una riga per atleta, una colonna per prova |

| Funzione | Compito |
|----------|---------|
| `vincitore(punti, n, valuta)` | Indice dell'atleta con il valore più alto |
| `totale`, `prova_migliore`, `prova_peggiore` | Criteri `int (const int *)` sulla riga di un atleta |
| `premia(premio, nomi, punti, valuta)` | Stampa il vincitore di un premio |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Premio assoluto

**a) Input** – criterio `totale`

**b) Output** – Omar (227)

**c) Variabili di supporto** – `migliore`

**d) Vincoli** – `punti[i]` è una riga di 3 interi e arriva al criterio come
`const int *`

**e) Assunzioni** – a parità vince l'atleta che compare prima

**f) Algoritmo in linguaggio naturale** – per ogni atleta calcolare
`valuta(punti[i])` e tenere l'indice del valore più alto.

### Caso d'uso 2 – Premio specialista

**a) Input** – criterio `prova_migliore`

**b) Output** – Davide (95 nella corsa), anche se il suo totale è il più basso

**c) Variabili di supporto** – `max`

**d) Vincoli** – la funzione `vincitore` non cambia

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il criterio restituisce il massimo
della riga.

### Caso d'uso 3 – Premio regolarità

**a) Input** – criterio `prova_peggiore`

**b) Output** – Sara (68: nessuna prova sotto 68)

**c) Variabili di supporto** – `min`

**d) Vincoli** – si cerca il valore più ALTO del minimo di ogni atleta

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il criterio restituisce il minimo
della riga; `vincitore` sceglie il più alto tra i minimi.
