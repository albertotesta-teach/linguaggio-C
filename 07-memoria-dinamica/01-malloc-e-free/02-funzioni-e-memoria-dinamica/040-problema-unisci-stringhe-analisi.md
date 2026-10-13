# Analisi – 040-problema-unisci-stringhe.c

## 1. Problema

Il laboratorio di informatica crea gli indirizzi email degli studenti nuovi unendo nome e cognome (nome.cognome@studenti.scuola.it), in minuscolo e senza caratteri che non sono lettere. Se l'indirizzo esiste già si aggiunge un numero a partire da 2. La funzione crea_email calcola la lunghezza esatta, alloca il blocco e lo restituisce; il chiamante conserva i puntatori e alla fine li libera.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `elenco` | `char *[]` | 30 puntatori | Indirizzi creati, uno per blocco |
| `nome`, `cognome` | `char[]` | 24 | Parole lette |
| `email` | `char *` | lunghezza esatta + 1 (heap) | Indirizzo appena creato |
| `numero` | `int` | — | 0, poi 2, 3, ... per i doppioni |

| Funzione | Compito |
|----------|---------|
| `crea_email(nome, cognome, numero)` | Alloca e riempie nome.cognome[numero]@dominio; NULL se la memoria non basta |
| `lettere(testo)` | Quante lettere contiene il testo |
| `cifre(numero)` | Quante cifre ha il numero |
| `presente(elenco, n, email)` | 1 se l'indirizzo è già nell'elenco |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Indirizzo nuovo

**a) Input** – `Marta Bassi`; `Luca D'Amico`

**b) Output** – marta.bassi@studenti.scuola.it (30 caratteri); luca.damico@...

**c) Variabili di supporto** – `email`

**d) Vincoli** – nomi e cognomi di una parola

**e) Assunzioni** – solo lettere ASCII

**f) Algoritmo in linguaggio naturale** – lunghezza = lettere(nome) + 1 + lettere(cognome) + lunghezza del dominio; malloc(lunghezza + 1).

### Caso d'uso 2 – Indirizzo già presente

**a) Input** – `Marta Bassi` e poi `MARTA bassi`

**b) Output** – marta.bassi2@..., marta.bassi3@...

**c) Variabili di supporto** – `numero`

**d) Vincoli** – —

**e) Assunzioni** – maiuscole e minuscole sono equivalenti

**f) Algoritmo in linguaggio naturale** – se presente, free del blocco e nuovo tentativo con il numero successivo.

### Caso d'uso 3 – Nome senza lettere

**a) Input** – `123 456`

**b) Output** – "Nome o cognome senza lettere."

**c) Variabili di supporto** – —

**d) Vincoli** – almeno una lettera

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna allocazione.

### Caso d'uso 4 – Fine

**a) Input** – `FINE`

**b) Output** – elenco degli account; ogni blocco liberato dopo la stampa

**c) Variabili di supporto** – `n`

**d) Vincoli** – al massimo 30 studenti

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni elenco[i]: stampa e free.
