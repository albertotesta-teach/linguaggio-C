# Analisi – 070-problema-scambio-righe.c

## 1. Problema

Nel torneo di calcetto d'istituto ogni squadra ha una riga con vittorie, pareggi e sconfitte. Dopo ogni partita inserita si aggiorna la riga e la squadra sale in classifica finché ha più punti di chi la precede. La classifica è un array di puntatori alle righe.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `risultati` | `int[][]` | 5 × 3 | V, P, S di ogni squadra |
| `classifica` | `int *[]` | 5 | Puntatori alle righe in ordine di classifica |
| `nomi` | `const char *[]` | 5 | Nomi delle squadre |
| `squadra`, `esito` | `int`, `char` | — | Partita inserita |
| `k` | `int` | — | Posizione della squadra in classifica |

| Funzione | Compito |
|----------|---------|
| `punti(riga)` | 3 × vittorie + pareggi |
| `stampa(classifica, inizio, nomi)` | Classifica; il nome si ricava dal puntatore alla riga |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Sorpasso

**a) Input** – `4 V` due volte

**b) Output** – Aquile da 4ª a 3ª, poi a 1ª con 11 punti

**c) Variabili di supporto** – `k`, `temp`

**d) Vincoli** – si scambiano i puntatori; le righe della matrice restano ferme

**e) Assunzioni** – a parità di punti non si sorpassa

**f) Algoritmo in linguaggio naturale** – aggiornare la riga; trovare `k` con `classifica[k] == risultati[squadra - 1]`; finché ha più punti della precedente, scambiare `classifica[k]` e `classifica[k - 1]`.

### Caso d'uso 2 – Nessun sorpasso

**a) Input** – `3 P`

**b) Output** – Squali restano 4i con 7 punti

**c) Variabili di supporto** – nessuna

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo non esegue scambi.

### Caso d'uso 3 – Dal puntatore alla squadra

**a) Input** – `classifica[0]`

**b) Output** – Aquile

**c) Variabili di supporto** – `(classifica[k] - inizio) / 3`

**d) Vincoli** – le righe sono consecutive in memoria

**e) Assunzioni** – 3 colonne per riga

**f) Algoritmo in linguaggio naturale** – la distanza dal primo elemento divisa per 3 è il numero della squadra.
