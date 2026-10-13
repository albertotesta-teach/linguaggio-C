# Analisi – 080-problema-torneo.c

## 1. Problema

Il torneo di calcetto d'istituto ha un numero di squadre che cambia ogni anno. Il Torneo contiene un puntatore a un array di Squadra allocato da crea_torneo. Le partite aggiornano punti e gol; la classifica usa un array temporaneo di indici allocato e liberato dentro la funzione, senza riordinare l'array delle squadre.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Squadra` | `nome[16], punti, giocate, fatti, subiti` | una squadra |
| `Torneo` | `nome[24], n_squadre, squadre (Squadra *)` | il torneo con il suo array nello heap |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `t` | `Torneo *` | — | Torneo nello heap |
| `n` | `int` | — | Squadre (2-16) |
| `nome1`, `nome2`, `gol1`, `gol2` | `char[]`, `int` | 16 | Dati di una partita |
| `a`, `b` | `int` | — | Indici delle due squadre |
| `ordine` | `int *` | n_squadre (heap, in classifica) | Indici in ordine di classifica |

| Funzione | Compito |
|----------|---------|
| `crea_torneo(nome, n)` | Struct e array delle squadre azzerate |
| `distruggi_torneo(t)` | Libera l'array e poi la struct |
| `cerca_squadra(t, nome)` | Indice o -1 |
| `registra(&squadra, fatti, subiti)` | Giocate, gol e punti |
| `precede(a, b)` | Più punti, a parità differenza reti |
| `classifica(t)` | Ordina gli indici con la selection sort e stampa |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Iscrizione delle squadre

**a) Input** – `4`, poi `Leoni Falchi Leoni Squali`

**b) Output** – "nome mancante o ripetuto: uso S3"

**c) Variabili di supporto** – `t->squadre`

**d) Vincoli** – nomi diversi

**e) Assunzioni** – nomi di una parola

**f) Algoritmo in linguaggio naturale** – cerca_squadra(t, nome) deve restituire l'indice appena scritto.

### Caso d'uso 2 – Risultati

**a) Input** – `P Leoni 3 Falchi 1`, `P S3 2 Squali 2`

**b) Output** – "Leoni 3 - 1 Falchi registrata"

**c) Variabili di supporto** – `a`, `b`

**d) Vincoli** – gol non negativi, squadre diverse

**e) Assunzioni** – 3 punti alla vittoria, 1 al pareggio

**f) Algoritmo in linguaggio naturale** – registra per entrambe le squadre, con i gol scambiati.

### Caso d'uso 3 – Squadra sconosciuta

**a) Input** – `P Lupi 1 Falchi 0`

**b) Output** – "Squadre non valide."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca_squadra restituisce -1.

### Caso d'uso 4 – Classifica

**a) Input** – `C`

**b) Output** – Leoni 4, Falchi 3, S3 2, Squali 1, con G, GF, GS e DR

**c) Variabili di supporto** – `ordine`

**d) Vincoli** – —

**e) Assunzioni** – a parità di punti e differenza reti resta l'ordine di iscrizione

**f) Algoritmo in linguaggio naturale** – malloc degli indici, selection sort con precede, stampa, free.

### Caso d'uso 5 – Numero non valido

**a) Input** – `1`

**b) Output** – "Numero non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – da 2 a 16 squadre

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna allocazione; distruggi_torneo(NULL) non fa nulla.
