# Analisi – 050-problema-riga-sicura.c

## 1. Problema

La bacheca digitale della scuola mostra messaggi di al massimo 30 caratteri. Le righe si leggono con fgets in un buffer di 32 byte, che non può traboccare; se la riga è più lunga il resto si consuma con getchar e si conta, così il messaggio viene rifiutato con la sua lunghezza vera. I messaggi accettati si copiano in blocchi di strlen + 1 byte.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `bacheca` | `char *[]` | 5 puntatori | Messaggi pubblicati |
| `buffer` | `char[]` | 32 | Riga letta |
| `messaggio` | `char *` | lunghezza + 1 (heap) | Copia del messaggio |
| `lunghezza` | `int` | — | Lunghezza vera della riga |

| Funzione | Compito |
|----------|---------|
| `leggi_riga(buffer, dimensione, &lunghezza)` | fgets senza overflow; consuma e conta il resto della riga; 0 a fine input |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Messaggio accettato

**a) Input** – `Assemblea di istituto venerdi`

**b) Output** – "pubblicato (30 byte)"

**c) Variabili di supporto** – `messaggio`

**d) Vincoli** – al massimo 30 caratteri

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – malloc(lunghezza + 1) e strcpy dal buffer.

### Caso d'uso 2 – Riga troppo lunga

**a) Input** – una riga di 64 caratteri

**b) Output** – "troppo lungo: 64 caratteri, massimo 30"

**c) Variabili di supporto** – `lunghezza`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessun '\n' nel buffer: getchar fino a '\n' contando i caratteri.

### Caso d'uso 3 – Al limite

**a) Input** – 30 caratteri; 31 caratteri

**b) Output** – pubblicato (31 byte); troppo lungo: 31 caratteri

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – con 31 caratteri il '\n' non entra nel buffer.

### Caso d'uso 4 – Riga vuota

**a) Input** – invio

**b) Output** – "messaggio vuoto"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – lunghezza 0: nessuna allocazione.

### Caso d'uso 5 – Fine

**a) Input** – `FINE`

**b) Output** – la bacheca con i messaggi pubblicati

**c) Variabili di supporto** – —

**d) Vincoli** – al massimo 5 messaggi

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stampa e free di ogni messaggio.
