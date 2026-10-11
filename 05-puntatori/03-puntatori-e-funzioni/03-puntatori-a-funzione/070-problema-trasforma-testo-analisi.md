# Analisi – 070-problema-trasforma-testo.c

## 1. Problema

Il club di informatica vuole uno strumento per i messaggi del giornalino:
dato un testo, ne mostra la versione in maiuscolo, quella cifrata con il
cifrario di Cesare (spostamento 3) e quella con le cifre sostituite da
asterischi. Una riga vuota termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `messaggio` | `char[]` | 100 | Testo letto con `fgets` |
| `copia` | `char[]` | 100 | Copia su cui si applica una trasformazione |
| `a_capo` | `char *` | — | `'\n'` da togliere |

| Funzione | Compito |
|----------|---------|
| `trasforma(testo, regola)` | Applica `regola` a ogni carattere |
| `mostra(titolo, originale, regola)` | Copia, trasforma e stampa |
| `maiuscolo`, `cesare`, `oscura_cifre` | Regole `char (char)` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Cifrario di Cesare

**a) Input** – `Ciao Zeno, chiamami al 333 1234567`

**b) Output** – `Fldr Chqr, fkldpdpl do 333 1234567`

**c) Variabili di supporto** – `risultato`

**d) Vincoli** – dopo la z si ricomincia dalla a; maiuscole e minuscole
restano tali

**e) Assunzioni** – alfabeto inglese di 26 lettere, senza accenti

**f) Algoritmo in linguaggio naturale** – per una lettera minuscola:
`'a' + (c - 'a' + 3) % 26`; analogamente per le maiuscole; gli altri
caratteri restano uguali.

### Caso d'uso 2 – Cifre oscurate

**a) Input** – lo stesso messaggio

**b) Output** – `Ciao Zeno, chiamami al *** *******`

**c) Variabili di supporto** – nessuna

**d) Vincoli** – il messaggio originale non cambia

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – `mostra` copia l'originale con
`strcpy` e solo la copia viene trasformata.

### Caso d'uso 3 – Un solo ciclo per tutte le regole

**a) Input** – tre chiamate a `mostra`

**b) Output** – tre righe trasformate

**c) Variabili di supporto** – `p` dentro `trasforma`

**d) Vincoli** – le regole hanno tutte prototipo `char (char)`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – `trasforma` scorre la stringa fino
a `'\0'` e scrive `*p = regola(*p)`.
