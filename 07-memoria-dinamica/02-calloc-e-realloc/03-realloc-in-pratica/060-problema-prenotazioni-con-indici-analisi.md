# Analisi – 060-problema-prenotazioni-con-indici.c

## 1. Problema

Il laboratorio di informatica riceve nuove postazioni durante l'anno: il blocco delle postazioni si ingrandisce con realloc e può spostarsi. Le prenotazioni ricordano la postazione con il suo indice, non con un puntatore, così restano valide. Se una postazione si guasta, le sue prenotazioni passano alla prima postazione libera.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Postazione` | `codice[16], funzionante` | un computer del laboratorio |
| `Prenotazione` | `studente[20], postazione (indice)` | una prenotazione |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `pc` | `Postazione *` | n_pc (heap) | Postazioni |
| `pren` | `Prenotazione *` | n_pren (heap) | Prenotazioni, crescono da NULL |
| `scelta` | `int` | — | Indice della postazione libera o -1 |

| Funzione | Compito |
|----------|---------|
| `nuove_postazioni(&pc, &n_pc, k)` | realloc e codici PC-01, PC-02, ...; 0 se fallisce |
| `libera(pc, n_pc, pren, n_pren)` | Prima postazione funzionante non prenotata |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Laboratorio pieno

**a) Input** – `2`, poi `P Marta`, `P Luca`, `P Sara`

**b) Output** – "Nessuna postazione libera."

**c) Variabili di supporto** – `scelta`

**d) Vincoli** – al massimo 40 postazioni

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – libera restituisce -1.

### Caso d'uso 2 – Nuove postazioni

**a) Input** – `N 2`, `P Sara`

**b) Output** – "postazioni: 4 (blocco in ...)"; "Sara: PC-03"

**c) Variabili di supporto** – `pc`

**d) Vincoli** – —

**e) Assunzioni** – il blocco può spostarsi

**f) Algoritmo in linguaggio naturale** – le prenotazioni usano indici: nessuna va aggiornata dopo la realloc.

### Caso d'uso 3 – Guasto

**a) Input** – `G 1`, `G 2`

**b) Output** – "prenotazione di Marta spostata su PC-04"; "Luca resta senza postazione"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni prenotazione sulla postazione guasta, nuova scelta con libera.

### Caso d'uso 4 – Elenco

**a) Input** – `E`

**b) Output** – prenotazioni con il codice della postazione

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – pc[pren[i].postazione].codice.
