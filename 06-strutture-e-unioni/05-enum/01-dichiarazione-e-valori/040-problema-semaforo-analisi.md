# Analisi – 040-problema-semaforo.c

## 1. Problema

Il semaforo pedonale davanti alla scuola ripete il ciclo verde, giallo, rosso. Il programma legge un istante t in secondi e stampa tutti i cambi di colore da 0 a t, il colore all'istante t e quanto manca al cambio successivo. Il colore è un enum e le durate stanno in un array indicizzato dal colore.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Colore` | `VERDE, GIALLO, ROSSO, NUM_COLORI` | colore del semaforo; NUM_COLORI conta i colori |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `colore` | `Colore` | — | Colore attuale |
| `durata` | `int[]` | NUM_COLORI | Secondi di ogni colore |
| `nomi` | `const char *[]` | NUM_COLORI | Nome di ogni colore |
| `inizio` | `int` | — | Istante in cui è iniziato il colore attuale |
| `t` | `int` | — | Istante letto |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ciclo completo

**a) Input** – `100`

**b) Output** – cambi a 0, 40, 45, 90 s; "A 100 s il semaforo e' VERDE: cambia tra 30 s."

**c) Variabili di supporto** – `inizio`

**d) Vincoli** – t da 1 a 600

**e) Assunzioni** – il ciclo parte da VERDE all'istante 0

**f) Algoritmo in linguaggio naturale** – finché il colore attuale finisce entro t: aggiungere la sua durata a inizio e passare a (colore + 1) % NUM_COLORI.

### Caso d'uso 2 – Istante non valido

**a) Input** – `0`

**b) Output** – "Istante non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna simulazione.
