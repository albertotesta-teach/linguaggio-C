# Analisi – 060-problema-correzione-errori.c

## 1. Problema

Il programma di una palestra calcola il prezzo dell'abbonamento in base
agli anni di iscrizione del socio: sconto del 10% da 2 anni, del 20% da 5
anni, ulteriori 15 euro di promozione da 10 anni; chi non è ancora socio
paga il prezzo pieno. La versione dello studente conteneva quattro errori
con i puntatori, che vanno riconosciuti e corretti.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `anni` | `int` | — | Anni di iscrizione letti con `scanf` |
| `sconto` | `int` | — | Percentuale di sconto |
| `prezzo` | `int` | — | Prezzo finale in euro |
| `percentuale` | `int *` | — | Punta a `sconto` |
| `da_applicare` | `int *` | — | Sconto da applicare, `NULL` per chi non è socio |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Errori 1 e 2: scanf e puntatore non inizializzato

**a) Input** – `3`

**b) Output** – "Socio da 3 anni: sconto 10%, prezzo 360 euro"

**c) Variabili di supporto** – `&anni`, `percentuale = &sconto`

**d) Vincoli** – `scanf` riceve l'indirizzo; il puntatore si inizializza prima di `*percentuale = ...`

**e) Assunzioni** – numero intero non negativo (altrimenti 0)

**f) Algoritmo in linguaggio naturale** – leggere gli anni, far puntare
`percentuale` a `sconto` e scrivervi la percentuale.

### Caso d'uso 2 – Errore 3: NULL per chi non è socio

**a) Input** – `0`

**b) Output** – "sconto 0%, prezzo 400 euro"

**c) Variabili di supporto** – `da_applicare` resta `NULL`

**d) Vincoli** – si dereferenzia `da_applicare` solo se diverso da `NULL`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `da_applicare` è `NULL` il prezzo
è quello base, altrimenti si applica la percentuale puntata.

### Caso d'uso 3 – Errore 4: variabile che non esiste più

**a) Input** – `12`

**b) Output** – "sconto 20%, prezzo 305 euro (compresa la promozione fedeltà)"

**c) Variabili di supporto** – nessuna

**d) Vincoli** – l'indirizzo di una variabile dichiarata in un blocco `{ }`
non è valido dopo la fine del blocco

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la promozione si applica
direttamente con il suo valore, senza puntare a una variabile temporanea.
