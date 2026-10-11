# Analisi – 040-problema-calcolatrice.c

## 1. Problema

Per il laboratorio di fisica serve una calcolatrice che legge espressioni
`numero operatore numero` e stampa il risultato, con gli operatori
`+ - * / ^`. Gli operatori sconosciuti e la divisione per zero vanno
segnalati. Un input non numerico termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `a`, `b` | `double` | — | Operandi |
| `simbolo` | `char` | — | Operatore letto |
| `operazione` | `double (*)(double, double)` | — | Funzione scelta, `NULL` se l'operatore non esiste |

| Funzione | Compito |
|----------|---------|
| `scegli_operazione(simbolo)` | Restituisce il puntatore alla funzione dell'operatore |
| `somma`, `sottrai`, `moltiplica`, `dividi`, `potenza` | Le cinque operazioni, stesso prototipo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Calcolo

**a) Input** – `12.5 * 4`; `2 ^ 10`

**b) Output** – `12.5 * 4 = 50`; `2 ^ 10 = 1024`

**c) Variabili di supporto** – `operazione`

**d) Vincoli** – tutte le funzioni hanno prototipo `double (double, double)`

**e) Assunzioni** – la potenza usa la parte intera dell'esponente, non negativo

**f) Algoritmo in linguaggio naturale**
1. Leggere `a`, `simbolo`, `b`.
2. `operazione = scegli_operazione(simbolo)`.
3. Stampare `operazione(a, b)`.

### Caso d'uso 2 – Operatore sconosciuto

**a) Input** – `5 % 2`

**b) Output** – "Operatore '%' sconosciuto."

**c) Variabili di supporto** – `operazione` = `NULL`

**d) Vincoli** – un puntatore a funzione `NULL` non si chiama mai

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – `scegli_operazione` parte da `NULL`
e assegna una funzione solo per i simboli previsti.

### Caso d'uso 3 – Divisione per zero

**a) Input** – `8 / 0`

**b) Output** – "Divisione per zero."

**c) Variabili di supporto** – confronto `operazione == dividi`

**d) Vincoli** – il controllo avviene prima della chiamata

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – due puntatori a funzione si
confrontano con `==`: se la funzione scelta è `dividi` e `b` vale 0 non si
calcola.
