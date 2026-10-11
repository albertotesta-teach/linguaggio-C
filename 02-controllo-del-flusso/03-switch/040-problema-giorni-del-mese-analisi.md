# Analisi – 040-problema-giorni-del-mese.c

## 1. Problema

Dati un mese (numero da 1 a 12) e un anno, stampare il nome del mese e il
numero dei suoi giorni, tenendo conto degli anni bisestili per febbraio.
La regola è quella della filastrocca: novembre, aprile, giugno e settembre
hanno 30 giorni, febbraio 28 (29 negli anni bisestili), tutti gli altri 31.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `mese` | `int` | Mese da 1 a 12 |
| `anno` | `int` | Anno, serve solo per febbraio |
| `giorni` | `int` | Risultato |
| `bisestile` | `int` (0/1) | Regola gregoriana dell'anno bisestile |
| `mese_valido` | `int` (0/1) | Diventa 0 nel ramo `default` |

Il valore del mese è un intero con pochi valori possibili: lo `switch` è la
struttura naturale. I mesi con lo stesso numero di giorni si raggruppano in
`case` consecutivi.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Mese da 30 giorni

**a) Input** – mese 11, anno 2025

**b) Output** – "Novembre 2025 ha 30 giorni."

**c) Variabili di supporto** – `mese_valido`

**d) Vincoli** – ogni gruppo di `case` termina con `break`

**e) Assunzioni** – l'utente inserisce numeri interi

**f) Algoritmo in linguaggio naturale**
1. Leggere mese e anno.
2. Calcolare `bisestile` con la regola gregoriana.
3. Porre `mese_valido = 1`.
4. Primo `switch`: stampare il nome del mese (o "Mese N" se non valido).
5. Secondo `switch`: mesi 4, 6, 9, 11 → 30 giorni; mese 2 → 29 se
   bisestile, altrimenti 28; mesi 1, 3, 5, 7, 8, 10, 12 → 31;
   `default` → `mese_valido = 0`.
6. Se il mese è valido stampare anno e giorni, altrimenti un messaggio di errore.

### Caso d'uso 2 – Febbraio di un anno bisestile

**a) Input** – mese 2, anno 2024

**b) Output** – "Febbraio 2024 ha 29 giorni."

**c) Variabili di supporto** – `bisestile`

**d) Vincoli** – il ramo di febbraio contiene un `if-else` e termina con `break`

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Febbraio di un anno secolare

**a) Input** – mese 2, anno 1900

**b) Output** – "Febbraio 1900 ha 28 giorni."

**c) Variabili di supporto** – `bisestile`

**d) Vincoli** – 1900 è divisibile per 4 ma anche per 100, e non per 400

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 4 – Mese non valido

**a) Input** – mese 13

**b) Output** – "Mese 13: non e' un mese valido (inserire un numero da 1 a 12)."

**c) Variabili di supporto** – `mese_valido`

**d) Vincoli** – entrambi gli `switch` hanno un ramo `default`

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passi 4–6.
