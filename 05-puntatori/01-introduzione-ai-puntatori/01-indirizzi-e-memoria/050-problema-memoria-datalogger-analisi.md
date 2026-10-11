# Analisi – 050-problema-memoria-datalogger.c

## 1. Problema

Una stazione meteo didattica usa un microcontrollore con 32 KB di memoria
per le misure. Ogni misura comprende temperatura, umidità e pressione ed
è presa ogni 10 minuti. Bisogna scegliere i tipi delle variabili
confrontando tre versioni (tutto `double`, tutto `float`, interi piccoli)
in base a quante misure entrano in memoria e per quanti giorni si può
registrare.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `t_a`, `u_a`, `p_a` | `double` | — | Versione A |
| `t_b`, `u_b`, `p_b` | `float` | — | Versione B |
| `t_c` | `short` | — | Versione C: temperatura in decimi di grado |
| `u_c` | `char` | — | Versione C: umidità in % (0-100) |
| `p_c` | `short` | — | Versione C: pressione in hPa |

| Funzione | Compito |
|----------|---------|
| `stampa_versione` | Calcola misure e giorni per una dimensione data e stampa la riga |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Byte per misura

**a) Input** – le tre variabili di ogni versione

**b) Output** – 24, 12 e 5 byte

**c) Variabili di supporto** – nessuna

**d) Vincoli** – le dimensioni si ricavano con `sizeof`, non si scrivono a mano

**e) Assunzioni** – dimensioni tipiche: `double` 8, `float` 4, `short` 2, `char` 1

**f) Algoritmo in linguaggio naturale** – per ogni versione sommare le
`sizeof` delle tre variabili.

### Caso d'uso 2 – Misure e giorni di registrazione

**a) Input** – byte per misura

**b) Output** – A: 1365 misure, 9.5 giorni; B: 2730, 19.0; C: 6553, 45.5

**c) Variabili di supporto** – `misure`, `giorni`

**d) Vincoli** – le misure sono un numero intero (divisione intera)

**e) Assunzioni** – una misura ogni 10 minuti, 1440 minuti al giorno

**f) Algoritmo in linguaggio naturale**
1. Misure = memoria / byte per misura.
2. Giorni = misure × intervallo / minuti in un giorno.

### Caso d'uso 3 – Rappresentazione con interi

**a) Input** – `t_c` = 215

**b) Output** – "215 decimi = 21.5 gradi"

**c) Variabili di supporto** – nessuna

**d) Vincoli** – la conversione in gradi si fa solo per la stampa (`t_c / 10.0`)

**e) Assunzioni** – precisione di un decimo di grado sufficiente

**f) Algoritmo in linguaggio naturale** – dividere per 10.0 per ottenere i gradi.
