# Analisi – 060-problema-itinerario-gita.c

## 1. Problema

Il docente organizzatore scrive l'itinerario della gita tappa per tappa. aggiungi_tappa accetta una tappa solo se gli orari esistono, la partenza non viene prima dell'arrivo e l'arrivo viene dopo la partenza dalla tappa precedente; restituisce un codice usato come indice dei messaggi. Alla fine si stampano soste, viaggi e totali.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Orario` | `ore, minuti` | ora del giorno |
| `Tappa` | `luogo, arrivo, partenza` | tappa con due Orario |
| `Gita` | `meta, tappe[], n_tappe` | itinerario |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `gita` | `Gita` | — | Meta e array di Tappa |
| `nuova` | `Tappa` | — | Tappa letta |
| `messaggi` | `const char *[]` | 4 | Messaggi per i codici di aggiungi_tappa |
| `esito` | `int` | — | Codice restituito |

| Funzione | Compito |
|----------|---------|
| `in_minuti(o)` | Minuti dalla mezzanotte |
| `orario_valido(o)` | Ore da 0 a 23, minuti da 0 a 59 |
| `aggiungi_tappa(g, t)` | 0 aggiunta, 1 orari non validi, 2 arrivo troppo presto, 3 piena |
| `stampa_gita(g)` | Programma della giornata con i totali |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tappa accettata

**a) Input** – `Riomaggiore 09:30 11:00`

**b) Output** – "Riomaggiore: aggiunta"

**c) Variabili di supporto** – `gita.n_tappe`

**d) Vincoli** – massimo 6 tappe

**e) Assunzioni** – orari dello stesso giorno

**f) Algoritmo in linguaggio naturale** – g->tappe[g->n_tappe] = *t.

### Caso d'uso 2 – Arrivo troppo presto

**a) Input** – `Vernazza 12:30 14:00` dopo Manarola 12:45

**b) Output** – "arrivo prima della partenza dalla tappa precedente"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confronto con g->tappe[g->n_tappe - 1].partenza.

### Caso d'uso 3 – Orari non validi

**a) Input** – `Monterosso 15:00 14:00`

**b) Output** – "Monterosso: orari non validi"

**c) Variabili di supporto** – —

**d) Vincoli** – partenza non prima dell'arrivo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – primo controllo di aggiungi_tappa.

### Caso d'uso 4 – Programma

**a) Input** – `FINE`

**b) Output** – 6 tappe, "in viaggio 5 h 55 min, in sosta 6 h 05 min"

**c) Variabili di supporto** – `viaggio`, `soste`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – viaggio tra la partenza di una tappa e l'arrivo alla successiva; sosta tra arrivo e partenza.
