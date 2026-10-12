# Analisi – 080-problema-impedenze-circuito.c

## 1. Problema

Nel laboratorio di elettrotecnica si calcolano le impedenze di resistore, induttore e condensatore, l'impedenza del circuito serie RLC e del parallelo tra R e C, e la corrente con 230 V. Le impedenze sono numeri complessi e tutte le operazioni ricevono e restituiscono Complesso per valore.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Complesso` | `re, im` | numero complesso, impedenza in ohm |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `r`, `l`, `c`, `f` | `double` | — | Valori letti |
| `zr`, `zl`, `zc` | `Complesso` | — | Impedenze dei componenti |
| `serie` | `Complesso` | — | Somma delle tre impedenze |

| Funzione | Compito |
|----------|---------|
| `somma, prodotto, quoziente` | Operazioni sui complessi |
| `parallelo(a, b)` | a·b / (a+b) |
| `modulo(z), fase(z)` | |Z| e angolo in gradi |
| `stampa(nome, z)` | Forma a + jb con modulo e fase |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Circuito serie

**a) Input** – `100 0.5 0.00002 50`

**b) Output** – serie: Z = 100.00 - j2.08, |Z| = 100.02 ohm; corrente 2.300 A

**c) Variabili di supporto** – `serie`

**d) Vincoli** – XL = 2πfL, XC = 1/(2πfC)

**e) Assunzioni** – componenti ideali

**f) Algoritmo in linguaggio naturale** – somma delle tre impedenze; corrente = 230 / |Z|.

### Caso d'uso 2 – Parallelo

**a) Input** – stessi valori

**b) Output** – R parallelo C: Z = 71.70 - j45.05

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – parallelo usa prodotto, somma e quoziente.

### Caso d'uso 3 – Valori non validi

**a) Input** – un valore negativo o zero

**b) Output** – "Valori non validi."

**c) Variabili di supporto** – —

**d) Vincoli** – tutti i valori positivi

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessun calcolo.
