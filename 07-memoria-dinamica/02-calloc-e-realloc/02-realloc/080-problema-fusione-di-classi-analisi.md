# Analisi – 080-problema-fusione-di-classi.c

## 1. Problema

La 4A e la 4B vengono accorpate. Il programma legge i due elenchi in ordine alfabetico, ingrandisce con realloc il blocco della 4A fino a contenere anche la 4B e fonde i due elenchi partendo dal fondo, senza un terzo array e senza ordinare da capo.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Studente` | `cognome[20], classe[4]` | uno studente con la classe di provenienza |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `quarta_a`, `quarta_b` | `Studente *` | n_a, poi n_a + n_b; n_b (heap) | Le due classi |
| `n_a`, `n_b` | `int` | — | Studenti delle classi |
| `i`, `j`, `k` | `int` | — | Ultimo di a, ultimo di b, posizione da scrivere |

| Funzione | Compito |
|----------|---------|
| `leggi_classe(&elenco, &n, classe)` | Alloca e legge; controlla l'ordine alfabetico |
| `fondi(&a, n_a, b, n_b)` | realloc di a e fusione dal fondo; 0 se fallisce |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Fusione

**a) Input** – `4 Bassi Conti Ferri Rossi`, `3 Amato Galli Neri`

**b) Output** – 7 studenti in ordine, con la classe di provenienza; blocco da 96 a 168 byte

**c) Variabili di supporto** – `k`

**d) Vincoli** – al massimo 30 studenti per classe

**e) Assunzioni** – cognomi di una parola

**f) Algoritmo in linguaggio naturale** – finché restano elementi di b, il maggiore tra a[i] e b[j] va in a[k].

### Caso d'uso 2 – Elenco non in ordine

**a) Input** – `3 Bassi Ferri Conti`

**b) Output** – "Conti non e' in ordine dopo Ferri"

**c) Variabili di supporto** – —

**d) Vincoli** – ordine alfabetico

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – strcmp tra cognomi consecutivi.

### Caso d'uso 3 – Elementi di a già al posto giusto

**a) Input** – —

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – quando b finisce, gli elementi rimasti di a sono già nelle prime posizioni.
