# Analisi – 080-problema-copia-di-una-stringa.c

## 1. Problema

La segreteria scrive i nomi dei diplomati in modo disordinato. Il programma li normalizza (spazi singoli, iniziali maiuscole) e conserva ogni nome in un blocco dello heap lungo esattamente strlen + 1 byte, raggiunto da un array di puntatori. Alla fine stampa l'elenco, confronta i byte usati con quelli di una matrice di righe da 80 caratteri e libera i blocchi uno per uno.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `elenco` | `char *[]` | 50 puntatori | Un puntatore per nome |
| `riga` | `char[]` | 80 | Buffer di lettura |
| `copia` | `char *` | strlen + 1 byte (heap) | Blocco del nome corrente |
| `n`, `byte_usati` | `int`, `size_t` | — | Nomi e byte allocati |

| Funzione | Compito |
|----------|---------|
| `normalizza(testo)` | Toglie gli spazi in più e scrive le parole con l'iniziale maiuscola, nello stesso buffer |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Nomi disordinati

**a) Input** – `mARTA  bassi`, `LUCA FERRI`, `  anna maria   de luca `

**b) Output** – "Marta Bassi (12 byte)", "Luca Ferri (11 byte)", "Anna Maria De Luca (19 byte)"

**c) Variabili di supporto** – `copia`

**d) Vincoli** – nomi fino a 79 caratteri

**e) Assunzioni** – parole separate da spazi

**f) Algoritmo in linguaggio naturale** – normalizzare la riga, allocare strlen + 1 byte, copiare con strcpy, salvare il puntatore.

### Caso d'uso 2 – Riga vuota

**a) Input** – `   `

**b) Output** – nessun nome aggiunto

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – dopo la normalizzazione la riga è vuota.

### Caso d'uso 3 – Confronto con una matrice

**a) Input** – `FINE`

**b) Output** – "Byte nello heap: 53 (con una matrice char[4][80]: 320)"

**c) Variabili di supporto** – `byte_usati`

**d) Vincoli** – al massimo 50 nomi

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sommare strlen + 1 di ogni nome; liberare ogni elenco[i] con free.
