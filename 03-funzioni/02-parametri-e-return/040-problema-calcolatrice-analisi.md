# Analisi – 040-problema-calcolatrice.c

## 1. Problema
Una calcolatrice a riga di comando legge dall'utente due operandi reali e un
operatore aritmetico (`+`, `-`, `*`, `/`) e stampa il risultato. Tutte le
funzioni di calcolo hanno la stessa struttura: ricevono due `double` e
restituiscono un `double`. La stampa è responsabilità esclusiva del main.
La divisione per zero restituisce 0.0 come valore convenzionale.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Descrizione |
|---|---|---|
| `a`, `b` | double | Operandi letti dall'utente |
| `operatore` | char | Simbolo dell'operazione (+, -, *, /) |
| `risultato` | double | Valore restituito dalla funzione di calcolo |

| Funzione | Firma | Descrizione |
|---|---|---|
| `op_somma` | `double(double, double)` | Addizione |
| `op_differenza` | `double(double, double)` | Sottrazione |
| `op_prodotto` | `double(double, double)` | Moltiplicazione |
| `op_quoziente` | `double(double, double)` | Divisione; restituisce 0.0 se b == 0.0 |
| `stampa_risultato` | `void(double, char, double, double)` | Formattazione e stampa |

Tutte le funzioni di calcolo seguono la stessa firma `double(double, double)`,
rendendo il codice uniforme e prevedibile.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Operazione valida (somma, differenza, prodotto)

**a) Input** – `12.5 + 7.3`

**b) Output** – `12.50 + 7.30 = 19.80`

**c) Variabili di supporto** – `risultato` riceve il valore restituito dalla funzione

**d) Vincoli** – l'operatore deve essere uno dei quattro riconosciuti

**e) Assunzioni** – l'utente inserisce il formato `numero operatore numero` correttamente

**f) Algoritmo in linguaggio naturale**
1. Leggere `a`, `operatore`, `b` con `scanf`
2. Chiamare la funzione corrispondente all'operatore
3. Chiamare `stampa_risultato` con operandi, operatore e risultato

### Caso d'uso 2 – Divisione valida

**a) Input** – `10.0 / 4.0`

**b) Output** – `10.00 / 4.00 = 2.50`

**c) Variabili di supporto** – `risultato` (double, locale a `op_quoziente`)

**d) Vincoli** – `b != 0.0`

**e) Assunzioni** – il divisore è un numero reale diverso da zero

**f) Algoritmo in linguaggio naturale**
1. `op_quoziente` verifica che `b != 0.0`
2. Calcola e restituisce `a / b`
3. Il main chiama `stampa_risultato` con il valore ottenuto

### Caso d'uso 3 – Divisione per zero

**a) Input** – `8.0 / 0.0`

**b) Output** – `8.00 / 0.00 = 0.00`

**c) Variabili di supporto** – nessuna aggiuntiva

**d) Vincoli** – il valore 0.0 restituito non è distinguibile da un risultato legittimo

**e) Assunzioni** – questa limitazione è accettata in questa versione del programma; tecniche più robuste verranno introdotte nei capitoli successivi

**f) Algoritmo in linguaggio naturale**
1. `op_quoziente` rileva che `b == 0.0`
2. Restituisce 0.0 come valore convenzionale
3. Il main chiama `stampa_risultato` e stampa il risultato convenzionale

### Caso d'uso 4 – Operatore non riconosciuto

**a) Input** – `5.0 ^ 2.0`

**b) Output** – `Operatore '^' non riconosciuto.`

**c) Variabili di supporto** – nessuna

**d) Vincoli** – tutti gli operatori diversi da +, -, *, / devono cadere nel ramo else

**e) Assunzioni** – l'utente inserisce un solo carattere come operatore

**f) Algoritmo in linguaggio naturale**
1. Nessuna condizione `if/else if` corrisponde all'operatore letto
2. Il ramo `else` finale stampa il messaggio di operatore non riconosciuto
