# Analisi – 080-problema-rapporto-multiplo.c

## 1. Problema

Ogni venerdì le classi pesano la carta raccolta. Il referente inserisce la settimana e i chili di ogni classe; il rapporto va a video e in carta-settimana-NN.txt (stessa funzione, due flussi), mentre una riga di riepilogo compatta si aggiunge in fondo a storico-carta.txt. Alla fine il programma ristampa lo storico.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `classi` | `char[][8]` | 10 | Nomi delle classi |
| `kg` | `double[]` | 10 | Chili per classe |
| `rapporto`, `storico` | `FILE *` | — | File della settimana ("w") e storico ("a") |
| `nome_file` | `char[]` | 40 | carta-settimana-NN.txt |
| `totale`, `migliore` | `double`, `int` | — | Totale e classe migliore |

| Funzione | Compito |
|----------|---------|
| `stampa_rapporto(f, settimana, classi, kg, n)` | Rapporto completo sul flusso f |
| `ricopia(nome)` | Stampa un file a video |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Settimana 7

**a) Input** – `7`, `3A 6.5 3B 11 4A 8.5 5C 5.5 FINE`

**b) Output** – totale 31.5 kg, media 7.9; storico di 1 riga

**c) Variabili di supporto** – `totale`

**d) Vincoli** – settimana 1-53, kg >= 0

**e) Assunzioni** – classi senza spazi

**f) Algoritmo in linguaggio naturale** – stampa_rapporto due volte; fprintf della riga compatta sullo storico.

### Caso d'uso 2 – Settimana 8

**a) Input** – `8`, `3A 7 3B 9.5 4A 10 FINE`

**b) Output** – lo storico ha 2 righe

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – "a" aggiunge senza cancellare.

### Caso d'uso 3 – Nessuna classe

**a) Input** – `9`, `FINE`

**b) Output** – "Nessuna classe inserita."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessun file scritto.
