# Analisi – 050-problema-testo-che-si-allunga.c

## 1. Problema

Il segretario scrive il verbale del consiglio di classe una frase per riga. Il verbale è un unico blocco che a ogni frase si allunga con realloc esattamente della lunghezza della frase, più lo spazio di separazione; le frasi senza punto finale lo ricevono. Alla fine il verbale si stampa a righe di al massimo 60 caratteri senza spezzare le parole.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `verbale` | `char *` | lunghezza + 1 (heap) | Testo completo |
| `frase` | `char[]` | 200 | Frase letta |
| `nuova` | `size_t` | — | Nuova dimensione del blocco |
| `frasi` | `int` | — | Frasi aggiunte |

| Funzione | Compito |
|----------|---------|
| `stampa_a_righe(testo, larghezza)` | Va a capo prima della parola che supererebbe la larghezza |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Frasi

**a) Input** – quattro frasi, una riga vuota, `FINE`

**b) Output** – "blocco di 56 byte" ... "blocco di 213 byte"; verbale di 4 frasi e 212 caratteri

**c) Variabili di supporto** – `nuova`

**d) Vincoli** – —

**e) Assunzioni** – il blocco parte da 1 byte ("")

**f) Algoritmo in linguaggio naturale** – nuova = strlen(verbale) + spazio + lunghezza + 1; realloc; strcat.

### Caso d'uso 2 – Punto finale

**a) Input** – frase senza punto

**b) Output** – il punto viene aggiunto

**c) Variabili di supporto** – `lunghezza`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – fgets legge al massimo 198 caratteri, così c'è posto per il punto.

### Caso d'uso 3 – Riga vuota

**a) Input** – invio

**b) Output** – nessuna frase aggiunta

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – —

### Caso d'uso 4 – Stampa

**a) Input** – `FINE`

**b) Output** – righe di al massimo 60 caratteri

**c) Variabili di supporto** – `colonna`

**d) Vincoli** – —

**e) Assunzioni** – parole separate da spazi

**f) Algoritmo in linguaggio naturale** – a capo quando colonna + 1 + lunghezza supera 60.
