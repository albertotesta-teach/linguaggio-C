# Analisi – 060-problema-inverti-percorso.c

## 1. Problema

Una gita in bicicletta attraversa 5 località con 4 tratti, di cui sono note
lunghezza e dislivello. Per il ritorno bisogna preparare la tabella dei
tratti in ordine inverso, con i dislivelli di segno opposto, e calcolare
chilometri e metri di salita di andata e ritorno.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `localita` | `char[][]` | 5 × 16 | Nomi delle località in ordine di andata |
| `distanze` | `int[]` | 4 | Lunghezza dei tratti in decimi di km |
| `dislivelli` | `int[]` | 4 | Metri, positivi in salita |
| `sinistra`, `destra` | `int *` | — | Estremi che si avvicinano durante l'inversione |

| Funzione | Compito |
|----------|---------|
| `inverti` | Inverte gli elementi tra `inizio` (incluso) e `fine` (escluso) |
| `cambia_segno` | Cambia il segno degli elementi di un intervallo |
| `stampa_tappe` | Stampa la tabella e i totali |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Inversione con due puntatori

**a) Input** – `{52, 38, 61, 27}`

**b) Output** – `{27, 61, 38, 52}`

**c) Variabili di supporto** – `sinistra`, `destra`, `scambio`

**d) Vincoli** – ci si ferma quando `sinistra` non è più minore di `destra`;
con un numero dispari di elementi quello centrale resta al suo posto

**e) Assunzioni** – intervallo non vuoto

**f) Algoritmo in linguaggio naturale**
1. `sinistra = inizio`, `destra = fine - 1`.
2. Finché `sinistra < destra`: scambiare `*sinistra` e `*destra`, poi
   `sinistra++` e `destra--`.

### Caso d'uso 2 – Dislivelli del ritorno

**a) Input** – dislivelli invertiti `{85, 120, -15, 40}`

**b) Output** – `{-85, -120, 15, -40}`

**c) Variabili di supporto** – `p`

**d) Vincoli** – si modifica l'array sul posto

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni `p` da `inizio` a `fine`
escluso, `*p = -*p`.

### Caso d'uso 3 – Totali

**a) Input** – tabelle di andata e ritorno

**b) Output** – 17.8 km in entrambi i casi; 245 m di salita all'andata, 15 m
al ritorno

**c) Variabili di supporto** – `km`, `salita`

**d) Vincoli** – si sommano solo i dislivelli positivi

**e) Assunzioni** – le località del ritorno si leggono all'indietro

**f) Algoritmo in linguaggio naturale** – sommare tutte le distanze e i
dislivelli maggiori di zero.
