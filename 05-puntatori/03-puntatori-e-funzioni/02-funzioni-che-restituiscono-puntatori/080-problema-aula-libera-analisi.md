# Analisi – 080-problema-aula-libera.c

## 1. Problema

Al primo piano della scuola ci sono 10 aule in fila lungo un corridoio.
Quando un docente chiede un'aula, se è libera gli viene assegnata;
altrimenti riceve la libera più vicina (a parità di distanza quella con il
numero più basso). Se sono tutte occupate lo si segnala. Con 0 termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `occupata` | `int[]` | 10 | 1 occupata, 0 libera; l'aula `i + 1` ha indice `i` |
| `richiesta` | `int` | — | Numero dell'aula chiesta |
| `aula` | `int *` | — | Elemento dell'aula assegnata, `NULL` se nessuna |

| Funzione | Compito |
|----------|---------|
| `piu_vicina(occupata, n, richiesta)` | Puntatore all'aula libera più vicina |
| `stampa_corridoio(occupata, n)` | Mappa delle aule |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Aula richiesta libera

**a) Input** – `2`

**b) Output** – "Assegnata l'aula 2."

**c) Variabili di supporto** – `aula`

**d) Vincoli** – a distanza 0 si controlla l'aula stessa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la funzione restituisce l'indirizzo
dell'elemento; il main scrive `*aula = 1` e calcola il numero con
`aula - occupata + 1`.

### Caso d'uso 2 – Aula vicina

**a) Input** – `5` (occupata), poi ancora `5`

**b) Output** – assegnata la 6, poi la 9

**c) Variabili di supporto** – `centro`, `d`

**d) Vincoli** – a ogni distanza prima a sinistra, poi a destra; gli
indici si controllano prima di costruire il puntatore

**e) Assunzioni** – il corridoio è dritto: la distanza è la differenza dei
numeri

**f) Algoritmo in linguaggio naturale**
1. Per `d` da 0 a n − 1, finché non si è trovato nulla:
2. se `centro - d ≥ 0` e quell'aula è libera, sceglierla;
3. altrimenti se `centro + d < n` e quell'aula è libera, sceglierla.

### Caso d'uso 3 – Tutte occupate o numero non valido

**a) Input** – `10` a corridoio pieno; `12`

**b) Output** – "Nessuna aula libera."; "Aula inesistente."

**c) Variabili di supporto** – `aula` = `NULL`

**d) Vincoli** – con `NULL` non si scrive nulla

**e) Assunzioni** – un input non numerico termina

**f) Algoritmo in linguaggio naturale** – il numero si controlla prima della
ricerca; il risultato `NULL` si controlla prima della scrittura.
