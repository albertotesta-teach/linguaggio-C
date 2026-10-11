# Analisi – 070-problema-serie-di-vittorie.c

## 1. Problema

I risultati di una squadra di pallavolo sono memorizzati giornata per
giornata come caratteri `V`, `P`, `S`. Si vogliono i punti in classifica
(3 per vittoria, 1 per pareggio) e la serie più lunga di vittorie
consecutive, con la prima e l'ultima giornata.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `risultati` | `char[]` | 15 | Un carattere per giornata (non è una stringa) |
| `p` | `const char *` | — | Giornata esaminata |
| `inizio_serie` | `const char *` | — | Prima giornata della serie in corso, `NULL` se non c'è |
| `migliore` | `const char *` | — | Inizio della serie più lunga |
| `lunghezza_max`, `punti` | `int` | — | Lunghezza della serie migliore, punti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Punti in classifica

**a) Input** – 11 vittorie, 2 pareggi, 2 sconfitte

**b) Output** – 35 punti

**c) Variabili di supporto** – `punti`

**d) Vincoli** – nessuno

**e) Assunzioni** – solo i caratteri `V`, `P`, `S`

**f) Algoritmo in linguaggio naturale** – per ogni giornata aggiungere 3 se
`*p == 'V'`, 1 se `*p == 'P'`.

### Caso d'uso 2 – Serie che si interrompe

**a) Input** – `V V V V P` dalle giornate 8-12

**b) Output** – serie di 4, dalla giornata 8 alla 11

**c) Variabili di supporto** – `inizio_serie`, `migliore`, `lunghezza_max`

**d) Vincoli** – la lunghezza è `p - inizio_serie`, con `p` sulla prima
giornata non vinta

**e) Assunzioni** – a parità di lunghezza vale la serie più vecchia

**f) Algoritmo in linguaggio naturale**
1. Con una vittoria, se `inizio_serie` è `NULL`, assegnargli `p`.
2. Con un altro risultato, se c'è una serie in corso, confrontarne la
   lunghezza con `lunghezza_max`; poi porre `inizio_serie = NULL`.

### Caso d'uso 3 – Serie aperta all'ultima giornata

**a) Input** – `... S V V` alla fine

**b) Output** – la serie di 2 viene considerata (qui non supera la migliore)

**c) Variabili di supporto** – `fine`

**d) Vincoli** – dopo il ciclo la lunghezza è `fine - inizio_serie`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se dopo il ciclo `inizio_serie` non
è `NULL`, confrontare `fine - inizio_serie` con `lunghezza_max`.
