# Analisi – 070-problema-cronometro.c

## 1. Problema

Alla gara dei 100 metri stile libero il cronometrista inserisce per ogni atleta minuti, secondi e decimi. Il programma trasforma ogni tempo in decimi di secondo (tipo `Decimi`), trova il vincitore e stampa il distacco di ogni atleta dal migliore nel formato m'ss"d.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Decimi` | `typedef int Decimi;` | tempo in decimi di secondo |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `const char *[]` | 5 | Atleti in ordine di corsia |
| `tempi` | `Decimi[]` | 5 | Tempi convertiti |
| `minuti`, `secondi`, `decimi` | `int` | — | Tempo letto |
| `migliore` | `int` | — | Indice del tempo più basso |

| Funzione | Compito |
|----------|---------|
| `in_decimi(minuti, secondi, decimi)` | Converte in decimi di secondo |
| `stampa_tempo(t)` | Stampa nel formato 1'05"3 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tempo valido

**a) Input** – `1 5 3`

**b) Output** – tempo memorizzato come 653 decimi

**c) Variabili di supporto** – `tempi[a]`

**d) Vincoli** – secondi 0-59, decimi 0-9

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – (minuti * 60 + secondi) * 10 + decimi.

### Caso d'uso 2 – Tempo non valido

**a) Input** – `1 70 2`

**b) Output** – "Tempo non valido, ripetere."

**c) Variabili di supporto** – —

**d) Vincoli** – l'atleta non avanza finché il tempo non è valido

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllare gli intervalli prima di convertire.

### Caso d'uso 3 – Classifica dei distacchi

**a) Input** – cinque tempi validi

**b) Output** – vincitore e distacco di ognuno (+0'00"0 per il vincitore)

**c) Variabili di supporto** – `migliore`

**d) Vincoli** – il distacco è tempi[a] - tempi[migliore]

**e) Assunzioni** – a parità vince il primo inserito

**f) Algoritmo in linguaggio naturale** – il migliore si aggiorna a ogni inserimento; la differenza in decimi si stampa con stampa_tempo.
