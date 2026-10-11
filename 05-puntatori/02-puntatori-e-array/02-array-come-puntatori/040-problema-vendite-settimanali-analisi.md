# Analisi – 040-problema-vendite-settimanali.c

## 1. Problema

Il gestore di un bar registra l'incasso di ogni giorno della settimana e
vuole confrontare i giorni feriali con il fine settimana: totale, media e
giorno migliore di ciascun gruppo, la differenza tra le medie e l'incasso
complessivo.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `incassi` | `int[]` | 7 | Euro incassati da lunedì a domenica |
| `giorni` | `char[][]` | 7 × 10 | Nomi dei giorni |
| `media_feriali`, `media_festivi` | `int` | — | Medie dei due gruppi |

| Funzione | Compito |
|----------|---------|
| `totale(v, n)` | Somma degli `n` elementi da `v` |
| `posizione_massimo(v, n)` | Posizione del massimo dentro l'intervallo |
| `riepilogo(...)` | Stampa totale, media e giorno migliore di un gruppo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Giorni feriali

**a) Input** – `riepilogo("Feriali", incassi, 5, 0, giorni)`

**b) Output** – totale 3605, media 721, giorno migliore venerdì (980)

**c) Variabili di supporto** – `somma`, `migliore`

**d) Vincoli** – la funzione vede solo i 5 elementi ricevuti

**e) Assunzioni** – media intera

**f) Algoritmo in linguaggio naturale** – chiamare `totale` e
`posizione_massimo` sull'intervallo; il nome del giorno è
`giorni[primo + migliore]`.

### Caso d'uso 2 – Fine settimana come sottoarray

**a) Input** – `riepilogo("Fine settimana", incassi + 5, 2, 5, giorni)`

**b) Output** – totale 2680, media 1340, giorno migliore sabato (1420)

**c) Variabili di supporto** – `primo` = 5

**d) Vincoli** – dentro la funzione `v[0]` è il sabato: la posizione
restituita (0) si somma a `primo`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – lo stesso del caso 1: cambia solo
l'indirizzo di partenza passato alla funzione.

### Caso d'uso 3 – Confronto tra le medie

**a) Input** – medie 721 e 1340

**b) Output** – "619 euro in piu' (+85%)"

**c) Variabili di supporto** – `media_feriali`, `media_festivi`

**d) Vincoli** – percentuale intera

**e) Assunzioni** – la media dei feriali è maggiore di zero

**f) Algoritmo in linguaggio naturale** – differenza = festivi − feriali;
percentuale = differenza × 100 / feriali.
