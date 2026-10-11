# Analisi – 070-problema-prefissi-telefonici.c

## 1. Problema

Il centralino di un'azienda registra le chiamate in uscita (numero in
formato internazionale e durata in minuti). Il tariffario associa a ogni
prefisso una zona e un costo al minuto. Il programma deve riconoscere la
zona di ogni chiamata, calcolarne il costo, sommare minuti e costi per zona
e segnalare le chiamate verso prefissi non in tariffario.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `prefissi` | `char[][]` | 8 × 6 | Prefissi del tariffario |
| `zone` | `char[][]` | 8 × 16 | Nome della zona (parallelo) |
| `tariffe` | `int[]` | 8 | Centesimi al minuto (parallelo) |
| `numeri` | `char[][]` | 9 × 20 | Numeri chiamati |
| `minuti` | `int[]` | 9 | Durate (parallelo a `numeri`) |
| `minuti_zona` | `int[]` | 8 | Minuti totali per zona (parallelo a `prefissi`) |
| `totale`, `sconosciute` | `int` | — | Costo totale in centesimi, chiamate non riconosciute |

| Funzione | Compito |
|----------|---------|
| `cerca_zona` | Indice del prefisso più lungo con cui inizia il numero, oppure -1 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prefisso semplice

**a) Input** – `+33142685300`, 8 minuti

**b) Output** – zona Francia, costo 0.72

**c) Variabili di supporto** – `z`, `costo`

**d) Vincoli** – i costi si calcolano in centesimi (interi) e si stampano in euro

**e) Assunzioni** – numeri senza spazi

**f) Algoritmo in linguaggio naturale**
1. Trovare la zona con `cerca_zona`.
2. Costo = minuti × tariffa; aggiornare `minuti_zona` e `totale`.

### Caso d'uso 2 – Prefissi sovrapposti

**a) Input** – `+393471234567`

**b) Output** – Italia mobile (non Italia fisso)

**c) Variabili di supporto** – `migliore`, `lung`

**d) Vincoli** – il numero inizia sia con `+39` sia con `+393`: vince il più lungo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Per ogni prefisso: se `strncmp(numero, prefisso, strlen(prefisso)) == 0`
   e il prefisso è più lungo del migliore trovato finora, ricordarlo.
2. Restituire l'indice del migliore (-1 se nessuno).

### Caso d'uso 3 – Prefisso sconosciuto

**a) Input** – `+81312345678`

**b) Output** – zona "?", costo "-", avviso finale

**c) Variabili di supporto** – `sconosciute`

**d) Vincoli** – la chiamata non entra nei totali

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `cerca_zona` restituisce -1 si
conta la chiamata tra quelle da verificare.

### Caso d'uso 4 – Totali per zona

**a) Input** – `minuti_zona`, `tariffe`

**b) Output** – solo le zone con almeno un minuto, poi il totale

**c) Variabili di supporto** – `costo`

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scorrere le zone e stampare quelle
con `minuti_zona[z] > 0` con il relativo costo.
