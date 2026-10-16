# Analisi – 080-problema-confronto-di-due-file.c

## 1. Problema

Il docente vuole verificare che nessuno abbia modificato il file di dati consegnato. Il programma apre due file insieme e li legge in parallelo, un carattere da ciascuno, tenendo il conto di riga e colonna. Si ferma alla prima differenza o alla fine dei file e dice se sono identici, se uno è più corto o dove differiscono.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `primo`, `secondo` | `FILE *` | — | I due file aperti insieme |
| `nome_primo`, `nome_secondo` | `char[]` | 60 | Nomi letti |
| `a`, `b` | `int` | — | Caratteri correnti o EOF |
| `riga`, `colonna` | `int` | — | Posizione corrente, da 1 |

| Funzione | Compito |
|----------|---------|
| `descrivi(c)` | Stampa il carattere, oppure "a capo" o "fine del file" |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – File identici

**a) Input** – `diario.txt`, `diario-copia.txt`

**b) Output** – "I file sono identici. Righe confrontate: 3"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo termina con a == b == EOF.

### Caso d'uso 2 – File diversi

**a) Input** – `diario.txt`, `presenze-16-10.txt`

**b) Output** – prima differenza alla riga 1, colonna 1: '1' e 'a'

**c) Variabili di supporto** – `riga`, `colonna`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo si ferma con a != b.

### Caso d'uso 3 – Uno più corto

**a) Input** – un file e il suo inizio

**b) Output** – uno dei due caratteri è "fine del file"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – EOF è diverso da ogni carattere.

### Caso d'uso 4 – Secondo mancante

**a) Input** – `diario.txt`, `mancante.txt`

**b) Output** – "Impossibile leggere mancante.txt"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – si chiude il primo file, già aperto.
