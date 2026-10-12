# Analisi – 070-problema-gioco-tris.c

## 1. Problema

Per la giornata delle STEM si gioca a tris. Ogni casella è un enum (vuota, croce, cerchio), anche il turno è una Casella, e il risultato della partita è un altro enum. gioca mette il segno e passa il turno; controlla cerca tre segni uguali o la griglia piena.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Casella` | `VUOTA, CROCE, CERCHIO` | contenuto di una casella |
| `Risultato` | `IN_CORSO, VINCE_CROCE, VINCE_CERCHIO, PAREGGIO` | stato della partita |
| `Partita` | `griglia[3][3], turno, mosse` | partita in corso |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `partita` | `Partita` | — | Griglia, turno e mosse |
| `risultato` | `Risultato` | — | Stato della partita |
| `riga`, `colonna` | `int` | — | Mossa letta |

| Funzione | Compito |
|----------|---------|
| `gioca(p, riga, colonna)` | 0 se la casella non esiste o è occupata |
| `controlla(p)` | Righe, colonne e diagonali |
| `tris(a, b, c)` | Tre segni uguali non vuoti |
| `stampa(p), simbolo(c)` | Griglia con X, O e punti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Vittoria

**a) Input** – `1 1`, `2 2`, `1 2`, `3 3`, `1 3`

**b) Output** – "Vince X in 5 mosse!"

**c) Variabili di supporto** – `risultato`

**d) Vincoli** – tre segni uguali in fila

**e) Assunzioni** – X muove per primo

**f) Algoritmo in linguaggio naturale** – dopo ogni mossa controllare righe, colonne e diagonali.

### Caso d'uso 2 – Pareggio

**a) Input** – partita con 9 mosse senza tris

**b) Output** – "Pareggio."

**c) Variabili di supporto** – `partita.mosse`

**d) Vincoli** – griglia piena

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – mosse == 9 senza vincitore.

### Caso d'uso 3 – Mossa non valida

**a) Input** – `2 1` occupata; `4 4`

**b) Output** – "Casella non valida o gia' occupata."

**c) Variabili di supporto** – —

**d) Vincoli** – righe e colonne da 1 a 3

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il turno non cambia.
