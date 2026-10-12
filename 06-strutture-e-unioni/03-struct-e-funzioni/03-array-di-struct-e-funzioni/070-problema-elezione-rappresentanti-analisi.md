# Analisi – 070-problema-elezione-rappresentanti.c

## 1. Problema

Lo spoglio delle schede per i rappresentanti d'istituto conta le schede valide, bianche e nulle. Ogni voto valido incrementa il campo voti del candidato trovato con un puntatore. Una funzione trova i due più votati senza ordinare l'array; se il secondo posto è conteso serve il ballottaggio.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Candidato` | `numero, nome, classe, voti` | candidato in lista |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `lista` | `Candidato[]` | 5 | Candidati |
| `votato` | `Candidato *` | — | Candidato della scheda |
| `bianche`, `nulle`, `valide` | `int` | — | Conteggi |
| `primo`, `secondo` | `int` | — | Indici dei più votati |

| Funzione | Compito |
|----------|---------|
| `cerca(c, n, numero)` | Puntatore al candidato, NULL se il numero non esiste |
| `classifica_primi(c, n, &primo, &secondo)` | I due più votati in una passata |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Spoglio

**a) Input** – 13 schede di prova

**b) Output** – valide 10, bianche 1, nulle 1

**c) Variabili di supporto** – `votato->voti`

**d) Vincoli** – 0 bianca, numero inesistente nulla

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca e incremento tramite il puntatore.

### Caso d'uso 2 – Ballottaggio

**a) Input** – Marchetti, Sanna e Ferri a 2 voti

**b) Output** – "serve il ballottaggio"

**c) Variabili di supporto** – `pari_merito`

**d) Vincoli** – eletti i primi due

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – contare gli altri candidati con gli stessi voti del secondo.

### Caso d'uso 3 – Eletti

**a) Input** – secondo posto non conteso

**b) Output** – "Secondo eletto: ..."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stampa diretta dei due indici.
