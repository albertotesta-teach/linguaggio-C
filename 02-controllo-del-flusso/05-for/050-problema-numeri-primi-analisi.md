# Analisi – 050-problema-numeri-primi.c

## 1. Problema

Verificare se un numero intero n ≥ 2 è primo, indicando il primo divisore
trovato quando non lo è, e stampare l'elenco di tutti i numeri primi fino a
un limite scelto dall'utente, dieci per riga.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `n` | `int` | Numero da verificare |
| `d` | `int` | Possibile divisore |
| `primo` | `int` (0/1) | Flag: vale 1 finché non si trova un divisore |
| `divisore_trovato` | `int` | Primo divisore di `n`, se esiste |
| `limite` | `int` | Limite superiore dell'elenco |
| `numero` | `int` | Numero esaminato nell'elenco |
| `conta_primi` | `int` | Contatore, usato anche per andare a capo |

Basta cercare divisori fino alla radice quadrata di n: se `n = a × b`
almeno uno dei due fattori è ≤ √n. La condizione si scrive `d * d <= n`,
senza bisogno di `<math.h>`.

La ricerca si ferma al primo divisore grazie al flag nella condizione del
`for` (`d * d <= n && primo`), senza `break`.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Numero composto

**a) Input** – 221

**b) Output** – "221 non e' primo: e' divisibile per 13 (221 = 13 x 17)."

**c) Variabili di supporto** – `primo`, `divisore_trovato`

**d) Vincoli** – il ciclo termina subito dopo aver trovato 13, perché
`primo` diventa 0

**e) Assunzioni** – l'utente inserisce numeri interi

**f) Algoritmo in linguaggio naturale**
1. Leggere n ripetendo la richiesta finché è minore di 2.
2. Porre `primo = 1`.
3. Per d da 2, finché `d * d <= n` e `primo` vale 1: se n è divisibile per
   d, porre `primo = 0` e memorizzare d.
4. Stampare l'esito; se non è primo stampare anche la scomposizione.

### Caso d'uso 2 – Numero primo

**a) Input** – 97

**b) Output** – "97 e' primo."

**c) Variabili di supporto** – `primo`

**d) Vincoli** – il ciclo prova i divisori da 2 a 9 (10 × 10 > 97)

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Elenco dei primi fino a 100

**a) Input** – limite 100

**b) Output** – 25 numeri primi su tre righe e "Tra 2 e 100 ci sono 25
numeri primi."

**c) Variabili di supporto** – `numero`, `conta_primi`

**d) Vincoli** – a capo ogni 10 numeri (`conta_primi % 10 == 0`) e un a capo
finale solo se l'ultima riga è incompleta

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale**
1. Leggere il limite ripetendo finché è minore di 2.
2. Per ogni `numero` da 2 al limite: ripetere la verifica del caso 1; se è
   primo stamparlo, contarlo e andare a capo ogni 10 numeri.
3. Stampare il numero totale di primi.

### Caso d'uso 4 – Valore minore di 2

**a) Input** – 1

**b) Output** – la richiesta viene ripetuta

**c) Variabili di supporto** – nessuna

**d) Vincoli** – 0 e 1 non sono né primi né composti

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 1.
