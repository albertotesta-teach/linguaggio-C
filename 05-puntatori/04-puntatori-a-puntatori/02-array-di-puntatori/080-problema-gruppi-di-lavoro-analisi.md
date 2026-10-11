# Analisi – 080-problema-gruppi-di-lavoro.c

## 1. Problema

Per il progetto di tecnologia la classe è divisa in quattro gruppi con un numero diverso di studenti. Il programma stampa voti e media di ogni gruppo, il gruppo con la media più alta e il voto più alto della classe con il gruppo di appartenenza.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `rossi`, `blu`, `verdi`, `gialli` | `int[]` | 3, 5, 4, 2 | Voti dei gruppi |
| `gruppi` | `int *[]` | 4 | Puntatori agli array dei gruppi |
| `studenti` | `int[]` | 4 | Dimensione di ogni gruppo |
| `voto_max` | `const int *` | — | Voto più alto trovato |

| Funzione | Compito |
|----------|---------|
| `media(voti, n)` | Media di un array di voti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Media di un gruppo

**a) Input** – gruppo Blu, 5 voti

**b) Output** – media 7.60

**c) Variabili di supporto** – `gruppi[g]`, `studenti[g]`

**d) Vincoli** – `gruppi[g]` si passa alla funzione come un normale array

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – chiamare `media(gruppi[g], studenti[g])`.

### Caso d'uso 2 – Gruppo migliore

**a) Input** – le quattro medie

**b) Output** – Gialli (9.00)

**c) Variabili di supporto** – `migliore`

**d) Vincoli** – a parità vale il primo gruppo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare la media di ogni gruppo con quella del migliore.

### Caso d'uso 3 – Voto più alto

**a) Input** – tutti i voti

**b) Output** – 10, nel gruppo Gialli

**c) Variabili di supporto** – `voto_max`, `gruppo_max`

**d) Vincoli** – `gruppi[g][i]` scorre righe di lunghezza diversa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – tenere il puntatore al voto massimo e l'indice del suo gruppo.
