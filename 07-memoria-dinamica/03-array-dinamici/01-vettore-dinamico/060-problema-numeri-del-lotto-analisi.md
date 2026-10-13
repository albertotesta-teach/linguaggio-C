# Analisi – 060-problema-numeri-del-lotto.c

## 1. Problema

La classe raccoglie le estrazioni di una ruota del lotto (5 numeri diversi da 1 a 90) per un'unità di statistica. Le estrazioni vanno in un vettore dinamico di struct `Estrazione`. Alla fine si calcolano per ogni numero la frequenza e il ritardo (estrazioni passate dall'ultima uscita, -1 se mai uscito) e si stampano i 5 più frequenti e i 5 più in ritardo tra quelli usciti, con il richiamo all'indipendenza delle estrazioni.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Estrazione` | `numeri[5]` | una estrazione |
| `Archivio` | `dati (Estrazione *), n, capacita` | vettore dinamico di estrazioni |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `archivio` | `Archivio *` | struct + blocco di n Estrazione (heap) | Tutte le estrazioni |
| `e` | `Estrazione` | — | Estrazione letta |
| `frequenza`, `ritardo` | `int[]` | 91 | Statistiche per numero (indice 1-90) |
| `parola`, `letti` | `char[]`, `int` | 16 | Primo numero o FINE; numeri letti |

| Funzione | Compito |
|----------|---------|
| `valida(&e)` | 5 numeri tra 1 e 90, tutti diversi |
| `stampa_primi(titolo, valore)` | I 5 numeri con valore più alto (esclusi i -1) |
| `crea_archivio, aggiungi, lunghezza, elemento, distruggi_archivio` | Funzioni del vettore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Sette estrazioni valide

**a) Input** – 9 righe di 5 numeri, poi `FINE`

**b) Output** – 7 estrazioni; più frequenti 12 (4) e 45 (4); più in ritardo 3, 67, 88 (6)

**c) Variabili di supporto** – `frequenza`, `ritardo`

**d) Vincoli** – numeri 1-90 tutti diversi

**e) Assunzioni** – ordine cronologico

**f) Algoritmo in linguaggio naturale** – per ogni estrazione i: frequenza[x]++ e ritardo[x] = n - 1 - i.

### Caso d'uso 2 – Estrazioni scartate

**a) Input** – `12 12 4 5 6`, `91 2 3 4 5`

**b) Output** – "estrazione non valida" (due volte)

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – valida controlla intervallo e doppioni.

### Caso d'uso 3 – Numeri mai usciti

**a) Input** – —

**b) Output** – esclusi dalla classifica dei ritardi

**c) Variabili di supporto** – —

**d) Vincoli** – ritardo -1

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stampa_primi ignora i valori -1.
