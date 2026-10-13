# Analisi – 070-problema-posti-a-teatro.c

## 1. Problema

Per lo spettacolo di fine anno la sala ha righe e posti per riga letti all'avvio. La sala è una matrice in un solo blocco allocato con calloc (tutti i posti liberi, cioè 0); ogni posto prenotato contiene il codice della prenotazione. Il programma gestisce prenotazioni di posti vicini nella stessa riga, cancellazioni e la mappa della sala.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `sala` | `int *` | righe × posti (heap, calloc) | Codice della prenotazione o 0 |
| `righe`, `posti` | `int` | — | Dimensioni della sala |
| `codice`, `occupati` | `int` | — | Ultimo codice e posti occupati |
| `lettera`, `numero`, `quanti` | `char`, `int` | — | Dati del comando P |

| Funzione | Compito |
|----------|---------|
| `mappa(sala, righe, posti)` | Stampa la sala con . e # |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prenotazione

**a) Input** – `4 10`, poi `P A 3 4`

**b) Output** – "prenotazione 1: A3-A6"

**c) Variabili di supporto** – `codice`

**d) Vincoli** – righe 1-26, posti 1-40

**e) Assunzioni** – righe indicate con le lettere da A

**f) Algoritmo in linguaggio naturale** – controllare che tutti i posti siano liberi, poi scrivere il codice.

### Caso d'uso 2 – Posti occupati

**a) Input** – `P A 5 2`

**b) Output** – "Alcuni posti sono gia' occupati."

**c) Variabili di supporto** – `liberi`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessun posto viene scritto se uno solo è occupato.

### Caso d'uso 3 – Fuori dalla sala

**a) Input** – `P D 9 3`; `P E 1 1`

**b) Output** – "Posti non validi."

**c) Variabili di supporto** – —

**d) Vincoli** – l'ultimo posto deve esistere

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – numero + quanti - 1 ≤ posti; lettera < 'A' + righe.

### Caso d'uso 4 – Cancellazione e mappa

**a) Input** – `C 1`, `P A 5 2`, `C 7`, `M`

**b) Output** – posti liberati; "Prenotazione inesistente."; mappa con 5 posti occupati

**c) Variabili di supporto** – `occupati`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – si azzerano le celle con quel codice.
