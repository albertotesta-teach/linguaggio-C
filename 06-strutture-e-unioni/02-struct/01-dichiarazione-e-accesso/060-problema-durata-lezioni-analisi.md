# Analisi – 060-problema-durata-lezioni.c

## 1. Problema

La segreteria inserisce inizio e fine di ogni lezione di una giornata. Il programma controlla gli orari, calcola la durata in minuti, segnala lezioni più lunghe di 60 o più corte di 50 minuti e sovrapposizioni con la lezione precedente; alla fine stampa il tempo totale. Un inizio 0 0 termina.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Orario` | `ore, minuti` | un'ora del giorno |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `inizio`, `fine` | `Orario` | — | Orari della lezione |
| `fine_precedente` | `Orario` | — | Fine dell'ultima lezione accettata |
| `durata`, `totale` | `int` | — | Minuti |
| `lezione` | `int` | — | Numero della lezione |

| Funzione | Compito |
|----------|---------|
| `valido(ore, minuti)` | 1 se ore 0-23 e minuti 0-59 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Lezione regolare

**a) Input** – `8 0`, `8 55`

**b) Output** – "08:00 - 08:55  55 minuti"

**c) Variabili di supporto** – `durata`

**d) Vincoli** – fine dopo l'inizio

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – durata = (ore*60+minuti) della fine - quella dell'inizio.

### Caso d'uso 2 – Anomalie

**a) Input** – `9 45`, `11 0` dopo una lezione finita alle 9:50

**b) Output** – "75 minuti (troppo lunga) (si sovrappone alla precedente)"

**c) Variabili di supporto** – `fine_precedente`

**d) Vincoli** – durata 50-60 minuti

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare l'inizio con la fine precedente, copiata campo per campo.

### Caso d'uso 3 – Orario errato

**a) Input** – `11 0`, `10 30`; `25 0`

**b) Output** – "La fine deve venire dopo l'inizio."; "Orario non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – la lezione non viene contata

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la lezione si ripete con lo stesso numero.
