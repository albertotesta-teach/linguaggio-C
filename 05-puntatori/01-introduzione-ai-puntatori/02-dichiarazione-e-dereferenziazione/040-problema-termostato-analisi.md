# Analisi – 040-problema-termostato.c

## 1. Problema

Il termostato di un appartamento regola la temperatura desiderata di tre
zone (soggiorno, camera, bagno) con un solo paio di tasti + e −, che
agiscono sulla zona selezionata. Ogni pressione cambia la temperatura di
mezzo grado, entro i limiti di 16 e 26 gradi. Senza una zona selezionata i
tasti non hanno effetto.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `soggiorno`, `camera`, `bagno` | `int` | — | Temperature in decimi di grado |
| `zona_attiva` | `int *` | — | Indirizzo della temperatura selezionata, `NULL` all'inizio |
| `comando` | `char` | — | Tasto premuto |

| Funzione | Compito |
|----------|---------|
| `stampa_stato` | Stampa le tre temperature in gradi |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tasto senza zona selezionata

**a) Input** – `+` come primo comando

**b) Output** – "Seleziona prima una zona."

**c) Variabili di supporto** – `zona_attiva` = `NULL`

**d) Vincoli** – un puntatore `NULL` non si dereferenzia mai

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `zona_attiva == NULL` si segnala
e non si modifica nulla.

### Caso d'uso 2 – Selezione e regolazione

**a) Input** – `S`, `+`, `+`; `C`, `-`

**b) Output** – soggiorno 21.0, 21.5; camera 18.5

**c) Variabili di supporto** – `zona_attiva`

**d) Vincoli** – la stessa istruzione `*zona_attiva = *zona_attiva + PASSO`
serve per tutte le zone

**e) Assunzioni** – una lettera per comando

**f) Algoritmo in linguaggio naturale**
1. Con S, C, B assegnare a `zona_attiva` l'indirizzo della temperatura.
2. Con + e − modificare la variabile puntata.

### Caso d'uso 3 – Limiti

**a) Input** – `B` e nove volte `+`

**b) Output** – il bagno arriva a 26.0, poi "Massimo raggiunto (26.0 gradi)."

**c) Variabili di supporto** – `*zona_attiva`

**d) Vincoli** – il controllo avviene prima della modifica

**e) Assunzioni** – limiti 160 e 260 decimi

**f) Algoritmo in linguaggio naturale** – se il nuovo valore supererebbe il
limite si stampa il messaggio senza cambiare la temperatura.
