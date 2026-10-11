# Analisi – 050-problema-statistiche-facoltative.c

## 1. Problema

Il registro elettronico calcola minimo, massimo e media dei voti di una
verifica con un'unica funzione, ma non tutti i chiamanti hanno bisogno di
tutti i risultati. Chi non vuole un risultato passa `NULL` al posto
dell'indirizzo. Se non ci sono voti la funzione non calcola nulla e lo
segnala.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `verifica` | `int[]` | 8 | Voti |
| `minimo`, `massimo` | `int` | — | Risultati richiesti |
| `media` | `double` | — | Risultato richiesto |

| Funzione | Compito |
|----------|---------|
| `statistiche(voti, n, int *minimo, int *massimo, double *media)` | Calcola e scrive solo nei puntatori non `NULL`; 0 se `n` è 0 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tutti i risultati

**a) Input** – voti 7, 5, 8, 6, 9, 4, 7, 6 e tre indirizzi

**b) Output** – minimo 4, massimo 9, media 6.50

**c) Variabili di supporto** – `min`, `max`, `somma` locali

**d) Vincoli** – i calcoli si fanno sulle variabili locali; i risultati si
copiano nei parametri OUT alla fine

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Scorrere i voti aggiornando somma, minimo e massimo.
2. Per ogni puntatore diverso da `NULL` scrivere il risultato corrispondente.

### Caso d'uso 2 – Risultati parziali

**a) Input** – `NULL, NULL, &media`; poi `&minimo, NULL, NULL`

**b) Output** – solo la media; solo il minimo con il giudizio sulle insufficienze

**c) Variabili di supporto** – nessuna

**d) Vincoli** – mai scrivere tramite un puntatore `NULL`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1; i risultati non
richiesti non vengono scritti.

### Caso d'uso 3 – Nessun voto

**a) Input** – `n = 0`

**b) Output** – "statistiche non disponibili"

**c) Variabili di supporto** – `calcolato` = 0

**d) Vincoli** – la media di zero voti non esiste (divisione per zero)

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `n` non è positivo restituire 0
senza scrivere nulla.
