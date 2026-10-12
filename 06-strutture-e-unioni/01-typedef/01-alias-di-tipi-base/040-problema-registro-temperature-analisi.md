# Analisi – 040-problema-registro-temperature.c

## 1. Problema

La classe registra per sette giorni la temperatura minima e massima della serra. Il programma calcola l'escursione di ogni giorno, la media delle minime e delle massime, il giorno con l'escursione più ampia e i giorni con rischio di gelo (minima sotto 2 gradi). Tutte le temperature hanno il tipo `Gradi`.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Gradi` | `typedef double Gradi;` | temperatura in gradi Celsius |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `giorni` | `const char *[]` | 7 | Nomi dei giorni per la stampa |
| `minime`, `massime` | `Gradi[]` | 7 | Temperature registrate |
| `gelo` | `int` | — | Giorni con minima sotto la soglia |
| `ampia` | `int` | — | Indice del giorno con escursione massima |

| Funzione | Compito |
|----------|---------|
| `media(v, n)` | Media di n temperature |
| `escursione(minima, massima)` | Differenza massima - minima |
| `giorno_escursione_massima(minime, massime, n)` | Indice del primo giorno con l'escursione più ampia |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tabella dei giorni

**a) Input** – dati nel programma

**b) Output** – una riga per giorno con minima, massima, escursione e l'avviso "rischio gelo"

**c) Variabili di supporto** – `g`, `gelo`

**d) Vincoli** – soglia di gelo 2.0 gradi (`SOGLIA_GELO`)

**e) Assunzioni** – i dati sono già validi

**f) Algoritmo in linguaggio naturale** – per ogni giorno calcolare l'escursione, stamparla e contare il giorno se la minima è sotto la soglia.

### Caso d'uso 2 – Medie e giorno più variabile

**a) Input** – dati nel programma

**b) Output** – medie 2.43 e 13.27; escursione più ampia domenica (14.8)

**c) Variabili di supporto** – `ampia`

**d) Vincoli** – a parità vale il primo giorno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – media scorre l'array; giorno_escursione_massima confronta le escursioni e tiene l'indice migliore.
