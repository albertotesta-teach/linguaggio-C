# Analisi – 060-problema-anatomia-float.c

## 1. Problema

Nel laboratorio di informatica si osserva com'è fatto un float: 1 bit di segno, 8 di esponente, 23 di mantissa. Una union permette di leggere i bit del float come intero senza segno; spostamenti e maschere separano le tre parti.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Float` | `union: reale (float), bit (uint32_t)` | lo stesso numero in due forme |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `f` | `Float` | — | Union: reale e bit |
| `parola` | `char[]` | 32 | Numero letto come testo |
| `segno`, `esponente`, `mantissa` | `uint32_t` | — | Parti del numero |

| Funzione | Compito |
|----------|---------|
| `stampa_bit(bit)` | I 32 bit con uno spazio dopo il segno e dopo l'esponente |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Numero positivo

**a) Input** – `1`

**b) Output** – 0 01111111 000...0, esponente 127 - 127 = 0

**c) Variabili di supporto** – `esponente`

**d) Vincoli** – standard IEEE 754

**e) Assunzioni** – float a 32 bit

**f) Algoritmo in linguaggio naturale** – segno = bit >> 31; esponente = (bit >> 23) & 0xFF; mantissa = bit & 0x7FFFFF.

### Caso d'uso 2 – Negativo

**a) Input** – `-2.5`

**b) Output** – segno 1, esponente 128 - 127 = 1, mantissa 0x200000

**c) Variabili di supporto** – `segno`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – -2.5 = -1.01 (binario) × 2^1.

### Caso d'uso 3 – 0.1

**a) Input** – `0.1`

**b) Output** – 0.100000001, mantissa 0x4CCCCD

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – 0.1 in binario è periodico: il float ne conserva un'approssimazione.

### Caso d'uso 4 – Zero e testo

**a) Input** – `0`; `abc`

**b) Output** – "esponente 0 (zero)"; "Non e' un numero."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – esponente e mantissa nulli indicano lo zero.
