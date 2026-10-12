# Analisi – 070-problema-mesi-e-stagioni.c

## 1. Problema

Per il calendario delle attività all'aperto il programma legge mese e anno e stampa il nome del mese, i giorni (con febbraio bisestile) e la stagione meteorologica. Mese parte da GENNAIO = 1 come il numero scritto dall'utente; il numero si controlla prima di assegnarlo a una variabile Mese.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Mese` | `GENNAIO = 1 ... DICEMBRE` | mese dell'anno |
| `Stagione` | `INVERNO, PRIMAVERA, ESTATE, AUTUNNO, NUM_STAGIONI` | stagione |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `numero`, `anno` | `int` | — | Valori letti |
| `mese` | `Mese` | — | Mese valido |
| `stagione` | `Stagione` | — | Stagione calcolata |
| `nomi_mesi`, `nomi_stagioni` | `const char *[]` | 12, NUM_STAGIONI | Nomi da stampare |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Febbraio bisestile

**a) Input** – `2 2028`

**b) Output** – "febbraio 2028: 29 giorni, inverno"

**c) Variabili di supporto** – `giorni`

**d) Vincoli** – anni bisestili

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – febbraio: 29 se l'anno è bisestile; aprile, giugno, settembre, novembre: 30; gli altri 31.

### Caso d'uso 2 – Stagioni

**a) Input** – `4 2026`; `12 2025`; `7 2026`

**b) Output** – primavera; inverno; estate

**c) Variabili di supporto** – `stagione`

**d) Vincoli** – stagioni meteorologiche

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – dicembre o fino a febbraio inverno, fino a maggio primavera, fino ad agosto estate, altrimenti autunno.

### Caso d'uso 3 – Mese non valido

**a) Input** – `13 2026`

**b) Output** – "13 non e' un mese."

**c) Variabili di supporto** – —

**d) Vincoli** – da GENNAIO a DICEMBRE

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il controllo avviene prima di assegnare il valore all'enum.

### Caso d'uso 4 – Indice della tabella

**a) Input** – —

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nomi_mesi[mese - GENNAIO]: la tabella parte da 0, il mese da 1.
