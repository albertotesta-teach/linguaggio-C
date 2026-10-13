# Analisi – 060-problema-misure-ridotte.c

## 1. Problema

Il pluviometro della stazione meteo registra i millimetri di pioggia di ogni giorno; i valori negativi o sopra 300 mm sono errori. Il programma toglie le letture errate con un filtro sul posto (due indici, nessun secondo array), conserva il numero del giorno originale e riduce i blocchi con realloc; se non resta nessuna lettura i blocchi si liberano.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `pioggia` | `double *` | n, poi j (heap) | Letture valide |
| `giorno` | `int *` | n, poi j (heap) | Giorno originale di ogni lettura valida |
| `i`, `j` | `int` | — | Indice di lettura e di scrittura |
| `totale`, `piovoso` | `double`, `int` | — | Statistiche |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Due errori

**a) Input** – `10`, poi `0 2.5 -1 14.2 0 999 3.8 27.6 0 1.2`

**b) Output** – giorni 3 e 6 scartati; blocchi ridotti da 10 a 8; totale 49.3 mm, media 6.2; giorno più piovoso 8

**c) Variabili di supporto** – `j`

**d) Vincoli** – da 0 a 300 mm

**e) Assunzioni** – una lettura al giorno

**f) Algoritmo in linguaggio naturale** – j non supera mai i, quindi la copia pioggia[j] = pioggia[i] non perde dati.

### Caso d'uso 2 – Tutte errate

**a) Input** – `2`, poi `-1 500`

**b) Output** – "Letture: 2, valide: 0"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna realloc a 0: i blocchi si liberano con free.

### Caso d'uso 3 – Numero non valido

**a) Input** – `0`

**b) Output** – "Numero non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – da 1 a 366 giorni

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – —
