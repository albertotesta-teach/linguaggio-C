# Analisi – 060-problema-confronto-pagelle.c

## 1. Problema

Il coordinatore confronta le pagelle del primo e del secondo quadrimestre di uno studente. La seconda pagella nasce come copia della prima (secondo = primo) e si aggiornano quadrimestre e voti. Il programma stampa la variazione per materia, le materie migliorate e peggiorate, le due medie e le insufficienze recuperate.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Pagella` | `nome, quadrimestre, voti[5]` | voti di un quadrimestre |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `primo`, `secondo` | `Pagella` | — | Le due pagelle |
| `materie` | `const char *[]` | 5 | Nomi delle materie |
| `migliorate`, `peggiorate`, `recuperate` | `int` | — | Conteggi |
| `somma_primo`, `somma_secondo` | `int` | — | Per le medie |

| Funzione | Compito |
|----------|---------|
| `main` | Copia, lettura e confronto dei voti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Inserimento

**a) Input** – `6 8 6 5 12`

**b) Output** – il 12 non è valido: informatica resta 8

**c) Variabili di supporto** – `secondo.voti`

**d) Vincoli** – voto 1-10

**e) Assunzioni** – la pagella copiata ha già il nome

**f) Algoritmo in linguaggio naturale** – leggere ogni voto nella copia; un voto errato lascia quello copiato.

### Caso d'uso 2 – Confronto

**a) Input** – i voti del caso 1

**b) Output** – storia +1, inglese +1, matematica +1; 3 migliorate, 0 peggiorate

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare primo.voti[m] e secondo.voti[m].

### Caso d'uso 3 – Recuperi e medie

**a) Input** – i voti del caso 1

**b) Output** – media 6.00 -> 6.60; 1 insufficienza recuperata

**c) Variabili di supporto** – `recuperate`

**d) Vincoli** – recupero: da sotto 6 a 6 o più

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – contare le materie con primo < 6 e secondo >= 6.
