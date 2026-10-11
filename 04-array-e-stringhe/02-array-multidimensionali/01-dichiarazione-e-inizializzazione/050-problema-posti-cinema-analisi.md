# Analisi – 050-problema-posti-cinema.c

## 1. Problema

Una sala con 6 file (A-F) da 10 posti registra lo stato di ogni posto
(libero o occupato). Il programma deve disegnare la mappa, contare i posti
liberi per fila e in totale, calcolare il riempimento, indicare la fila più
libera e cercare 4 posti liberi consecutivi nella stessa fila.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `sala` | `int[][]` | 6 × 10 | 0 = libero, 1 = occupato |
| `liberi_fila`, `liberi_totali` | `int` | — | Contatori |
| `max_liberi`, `fila_max` | `int` | — | Fila con più posti liberi |
| `consecutivi` | `int` | — | Posti liberi di seguito nella fila corrente |
| `trovato_gruppo` | `int` (0/1) | — | Flag che ferma la ricerca |
| `fila_gruppo`, `posto_gruppo` | `int` | — | Posizione del gruppo trovato |

Costanti: `FILE_SALA`, `POSTI`, `LIBERO`, `OCCUPATO`, `GRUPPO`.
La lettera della fila si calcola come `'A' + fila`.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Mappa e conteggi

**a) Input** – matrice `sala` inizializzata nel codice

**b) Output** – mappa con O/X e posti liberi per fila; 34 liberi su 60,
riempimento 43,3%, fila più libera F

**c) Variabili di supporto** – `liberi_fila`, `liberi_totali`, `max_liberi`, `fila_max`

**d) Vincoli** – il riempimento si calcola sui posti occupati, in reale

**e) Assunzioni** – la matrice contiene solo 0 e 1

**f) Algoritmo in linguaggio naturale**
1. Per ogni fila: stampare la lettera, poi per ogni posto O se libero
   (contandolo) o X se occupato.
2. Stampare i liberi della fila, sommarli al totale, aggiornare la fila più libera.
3. Stampare totale, percentuale di riempimento e fila più libera.

### Caso d'uso 2 – Quattro posti vicini

**a) Input** – matrice `sala`

**b) Output** – "4 posti vicini disponibili: fila C, posti da 4 a 7"

**c) Variabili di supporto** – `consecutivi`, `trovato_gruppo`

**d) Vincoli** – il conteggio riparte da zero a ogni fila e a ogni posto
occupato; la ricerca termina al primo gruppo grazie al flag nelle condizioni
dei due cicli, senza `break`

**e) Assunzioni** – si propone il primo gruppo trovato partendo dalla fila A

**f) Algoritmo in linguaggio naturale**
1. Per ogni fila, finché non è trovato un gruppo: azzerare `consecutivi`.
2. Per ogni posto, finché non è trovato: se libero incrementare `consecutivi`;
   se arriva a 4, memorizzare fila e primo posto (`posto - 3`) e alzare il flag.
   Se occupato, azzerare `consecutivi`.
3. Stampare il gruppo (posti numerati da 1) oppure che non esiste.

### Caso d'uso 3 – Sala senza gruppi liberi

**a) Input** – una sala con al massimo 3 posti liberi consecutivi per fila

**b) Output** – "Nessun gruppo di 4 posti vicini disponibile."

**c) Variabili di supporto** – `trovato_gruppo` resta 0

**d) Vincoli** – nessuno in più

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 2.
