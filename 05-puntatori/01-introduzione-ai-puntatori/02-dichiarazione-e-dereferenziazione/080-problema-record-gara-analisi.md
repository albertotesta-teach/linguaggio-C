# Analisi – 080-problema-record-gara.c

## 1. Problema

Nella finale dei 50 metri stile libero dei giochi studenteschi i tempi
delle 6 corsie sono in un array (0 = squalificato o assente). Bisogna
trovare il vincitore e la sua corsia, segnalare se ha battuto il record dei
giochi (aggiornandolo) e gestire il caso in cui nessun atleta abbia concluso.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `finale_a`, `finale_b` | `int[]` | 6 | Tempi in centesimi di secondo |
| `record` | `int` | — | Record dei giochi |
| `migliore` | `int *` | — | Indirizzo dell'elemento con il tempo migliore, `NULL` se nessuno |
| `corsia` | `int` | — | Corsia del vincitore |

| Funzione | Compito |
|----------|---------|
| `esamina_finale(titolo, tempi, int *record)` | Trova il migliore e aggiorna il record |
| `stampa_tempo` | Stampa secondi e centesimi |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Vincitore e nuovo record

**a) Input** – tempi 3125, 2987, 0, 3010, 2955, 3102; record 2970

**b) Output** – "Vince la corsia 5 con 29"55: NUOVO RECORD!"

**c) Variabili di supporto** – `migliore`, `corsia`

**d) Vincoli** – i tempi 0 non partecipano al confronto

**e) Assunzioni** – non ci sono tempi uguali

**f) Algoritmo in linguaggio naturale**
1. `migliore = NULL`.
2. Per ogni tempo valido: se `migliore` è `NULL` o il tempo è minore di
   `*migliore`, `migliore = &tempi[k]`.
3. Trovare la corsia cercando `k` con `&tempi[k] == migliore`.
4. Se `*migliore < *record`, scrivere il nuovo record tramite il puntatore.

### Caso d'uso 2 – Nessun atleta all'arrivo

**a) Input** – tutti i tempi a 0

**b) Output** – "Nessun atleta ha concluso la gara."

**c) Variabili di supporto** – `migliore` resta `NULL`

**d) Vincoli** – non si dereferenzia `migliore`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – dopo lo scorrimento, se
`migliore == NULL` si stampa il messaggio.

### Caso d'uso 3 – Record aggiornato

**a) Input** – `&record` passato alla funzione

**b) Output** – "Record aggiornato: 29"55"

**c) Variabili di supporto** – `*record`

**d) Vincoli** – la funzione modifica la variabile del `main` tramite il puntatore

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il `main` stampa `record` dopo le
due chiamate.
