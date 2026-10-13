# Analisi – 050-problema-coda-della-mensa.c

## 1. Problema

Gli studenti si mettono in fila in fondo e vengono serviti dal primo. La fila è un vettore dinamico di `Studente`: entrare costa una scrittura, essere serviti significa rimuovere la posizione 0 e spostare tutti gli altri. Il programma conta gli spostamenti per mostrare il costo di questa scelta; uno studente può anche lasciare la fila prima del suo turno.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Studente` | `nome[20]` | uno studente in fila |
| `Fila` | `dati (Studente *), n, capacita` | vettore dinamico in ordine di arrivo |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `fila` | `Fila *` | struct + blocco di n Studente (heap) | Ordine di arrivo |
| `s` | `Studente` | — | Studente letto o uscito |
| `spostamenti` | `long` | — | Elementi spostati da rimuovi |
| `serviti`, `posizione` | `int` | — | Contatore e indice di chi lascia |

| Funzione | Compito |
|----------|---------|
| `aggiungi(f, s)` | In fondo, raddoppia se pieno |
| `rimuovi(f, posizione, &uscito, &spostamenti)` | Toglie, sposta a sinistra e somma gli spostamenti |
| `cerca(f, nome)` | Posizione o -1 |
| `crea_fila, lunghezza, elemento, distruggi_fila` | Funzioni del vettore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Pranzo

**a) Input** – `E Anna` … `E Sara`, `S`, `S`, `L Paolo`, `E Teo`, quattro `S`

**b) Output** – serviti in ordine Anna, Luca, Marta, Sara, Teo; "Fila vuota." all'ultimo S; 5 serviti, 11 spostamenti

**c) Variabili di supporto** – `spostamenti`

**d) Vincoli** – nomi senza spazi

**e) Assunzioni** – nessun nome ripetuto

**f) Algoritmo in linguaggio naturale** – S = rimuovi(0); E = aggiungi; L = cerca e rimuovi.

### Caso d'uso 2 – Chi non c'è

**a) Input** – `L Gianni`

**b) Output** – "Non e' in fila."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca restituisce -1.

### Caso d'uso 3 – Costo

**a) Input** – fila di n studenti

**b) Output** – servire il primo costa n - 1 spostamenti

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – anticipa la coda circolare del capitolo 10.
