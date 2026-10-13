# Analisi – 060-problema-scheda-studente.c

## 1. Problema

La segreteria inserisce uno studente per riga (cognome, nome, classe e tre voti). Per ogni riga il programma alloca una struct Studente, la fa riempire da leggi_studente che riceve l'indirizzo del blocco, stampa la scheda con media ed esito e libera la struct prima della riga successiva.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Studente` | `cognome[20], nome[20], classe[4], voti[3]` | scheda di uno studente |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `s` | `Studente *` | 1 struct (heap) | Scheda dello studente corrente |
| `esito` | `int` | — | 1 riga corretta, 0 errore, -1 FINE |
| `schede`, `scartate` | `int` | — | Contatori finali |

| Funzione | Compito |
|----------|---------|
| `leggi_studente(s)` | Scrive nei campi di *s; controlla voti e classe |
| `stampa_scheda(s)` | Riquadro con voti, media ed esito |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Studente promosso

**a) Input** – `Bassi Marta 3B 7 8.5 6`

**b) Output** – scheda con media 7.17, "esito: promosso"

**c) Variabili di supporto** – `s`

**d) Vincoli** – voti da 1 a 10

**e) Assunzioni** – una parola per cognome e nome

**f) Algoritmo in linguaggio naturale** – malloc, leggi_studente(s), stampa_scheda(s), free.

### Caso d'uso 2 – Insufficienze

**a) Input** – `Ferri Luca 3A 5 6 4.5`; `Neri Paolo 3C 6 5.5 8`

**b) Output** – "esito: 2 insufficienze"; "esito: 1 insufficienza"

**c) Variabili di supporto** – `insufficienti`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – contare i voti sotto 6.

### Caso d'uso 3 – Riga non valida

**a) Input** – `Conti Sara 3B 11 7 7`

**b) Output** – "Riga non valida: scheda non creata."

**c) Variabili di supporto** – `scartate`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – leggi_studente restituisce 0; il blocco si libera lo stesso.

### Caso d'uso 4 – Fine

**a) Input** – `FINE`

**b) Output** – "Schede stampate: 3, righe scartate: 1"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – esito -1: il ciclo termina dopo aver liberato l'ultima struct.
