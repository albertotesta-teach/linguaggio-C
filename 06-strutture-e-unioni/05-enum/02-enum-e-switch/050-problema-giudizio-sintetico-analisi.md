# Analisi – 050-problema-giudizio-sintetico.c

## 1. Problema

Dopo la verifica di storia il docente scrive accanto a ogni voto il giudizio sintetico. da_voto trasforma il voto in un Giudizio con una catena di if; nome restituisce il testo con uno switch. Alla fine un istogramma mostra quanti studenti hanno ogni giudizio.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Giudizio` | `GRAV_INSUFFICIENTE ... OTTIMO, NUM_GIUDIZI` | giudizio sintetico |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `voto` | `double` | — | Voto letto |
| `conteggi` | `int[]` | NUM_GIUDIZI | Studenti per giudizio |
| `g` | `Giudizio` | — | Giudizio del voto |
| `studenti` | `int` | — | Voti validi |

| Funzione | Compito |
|----------|---------|
| `da_voto(voto)` | Fascia del voto |
| `nome(g)` | Testo del giudizio |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Giudizi

**a) Input** – `4` ... `10`

**b) Output** – "4.0: gravemente insufficiente", "7.5: discreto", "10.0: ottimo"

**c) Variabili di supporto** – `g`

**d) Vincoli** – sotto 5, 6, 7, 8, 9; da 9 ottimo

**e) Assunzioni** – voti da 1 a 10

**f) Algoritmo in linguaggio naturale** – da_voto confronta con le soglie in ordine crescente.

### Caso d'uso 2 – Istogramma

**a) Input** – fine dell'input

**b) Output** – "discreto ** 2"

**c) Variabili di supporto** – `conteggi`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – conteggi[g]++ e poi un asterisco per studente.

### Caso d'uso 3 – Voto non valido

**a) Input** – `11`

**b) Output** – "Voto non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – da 1 a 10

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il voto non entra nelle statistiche.
