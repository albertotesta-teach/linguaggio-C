# Analisi – 070-problema-elenco-iscritti.c

## 1. Problema

La scuola organizza i corsi pomeridiani di robotica e di teatro, con un numero di posti deciso all'avvio. Ogni corso è un Elenco con un puntatore a un array di Iscritto allocato da crea_elenco e liberato da distruggi_elenco; le funzioni iscrivi, ritira e stampa non toccano mai malloc e free.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Iscritto` | `nome[20], classe[4]` | uno studente |
| `Elenco` | `corso[16], capienza, n, iscritti (Iscritto *)` | un corso con il suo array nello heap |
| `Esito` | `ISCRITTO, CORSO_PIENO, GIA_ISCRITTO` | risultato di iscrivi |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `corsi` | `Elenco *[]` | 2 | I due corsi |
| `posti` | `int[]` | 2 | Capienza scelta |
| `e` | `Elenco *` | — | Corso indicato nel comando |
| `corso`, `nome`, `classe` | `char[]` | 16, 20, 8 | Dati letti |

| Funzione | Compito |
|----------|---------|
| `crea_elenco(corso, capienza)` | Struct e array degli iscritti; NULL se una malloc fallisce |
| `distruggi_elenco(e)` | Libera l'array e poi la struct |
| `iscrivi(e, nome, classe)` | Esito: ISCRITTO, CORSO_PIENO, GIA_ISCRITTO |
| `ritira(e, nome)` | Toglie lo studente e sposta indietro i successivi |
| `cerca(e, nome)` | Posizione o -1 |
| `trova_corso(corsi, corso)` | Elenco con quel nome o NULL |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Iscrizioni

**a) Input** – `2 3`, poi `I robotica Marta 3B`, `I robotica Luca 2A`

**b) Output** – "Iscrizione di Marta a robotica (1/2)"

**c) Variabili di supporto** – `e->n`

**d) Vincoli** – posti da 1 a 30

**e) Assunzioni** – nomi di una parola

**f) Algoritmo in linguaggio naturale** – cercare il corso, controllare doppioni e capienza, copiare nell'ultima posizione.

### Caso d'uso 2 – Corso pieno e doppione

**a) Input** – `I robotica Sara 3B`; `I teatro Marta 3B` due volte

**b) Output** – "Il corso di robotica e' pieno."; "Marta e' gia' tra gli iscritti a teatro."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – uno studente può seguire entrambi i corsi

**f) Algoritmo in linguaggio naturale** – switch sull'Esito restituito da iscrivi.

### Caso d'uso 3 – Ritiro

**a) Input** – `R robotica Marta`

**b) Output** – "Ritiro di Marta da robotica."; il posto si libera per Sara

**c) Variabili di supporto** – `posizione`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – spostare indietro di un posto gli iscritti successivi e decrementare n.

### Caso d'uso 4 – Elenco

**a) Input** – `E`

**b) Output** – i due corsi con gli iscritti in ordine di iscrizione

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stampa per ogni corso.

### Caso d'uso 5 – Fine

**a) Input** – `Q`

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – distruggi_elenco per entrambi i corsi.
