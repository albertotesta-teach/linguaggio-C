# Analisi – 050-problema-giocatore-di-turno.c

## 1. Problema

Due giocatori lanciano a turno un dado e sommano il risultato; chi
raggiunge per primo 20 punti vince. Se esce 1 il giocatore perde 3 punti,
senza scendere sotto zero. Le istruzioni di ogni turno sono le stesse per
i due giocatori: cambia solo quale punteggio aggiornare.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nome_1`, `nome_2` | `char[]` | 12 | Nomi dei giocatori |
| `punti_1`, `punti_2` | `int` | — | Punteggi |
| `lanci` | `int[]` | 16 | Lanci prestabiliti (partita ripetibile) |
| `punti_turno` | `int *` | — | Punteggio del giocatore di turno |
| `nome_turno` | `char *` | — | Primo carattere del nome del giocatore di turno |
| `vincitore` | `int` | — | Flag di fine partita |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Turno normale

**a) Input** – Anna lancia 4

**b) Output** – "punti 4 (Anna 4 - Bruno 0)"

**c) Variabili di supporto** – `punti_turno`

**d) Vincoli** – la modifica di `*punti_turno` cambia `punti_1` o `punti_2`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sommare il lancio alla variabile puntata.

### Caso d'uso 2 – Lancio di 1

**a) Input** – Bruno con 6 punti lancia 1

**b) Output** – punti 3

**c) Variabili di supporto** – `*punti_turno`

**d) Vincoli** – il punteggio non scende sotto 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sottrarre 3; se il risultato è
negativo riportarlo a 0.

### Caso d'uso 3 – Cambio turno e vittoria

**a) Input** – sequenza dei lanci

**b) Output** – "Vince Bruno con 21 punti!" al turno 12

**c) Variabili di supporto** – `punti_turno`, `nome_turno`, `vincitore`

**d) Vincoli** – il turno passa solo se non c'è un vincitore; il ciclo si
ferma con il flag

**e) Assunzioni** – i 16 lanci bastano a concludere la partita

**f) Algoritmo in linguaggio naturale**
1. Se `*punti_turno` raggiunge il traguardo, segnare il vincitore.
2. Altrimenti, se `punti_turno == &punti_1`, puntare al giocatore 2, e viceversa.
