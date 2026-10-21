# Analisi – 050-problema-numeri-primi.c

## 1. Problema

Verificare se un numero intero n ≥ 2 è primo, indicando il primo divisore
trovato quando non lo è, e stampare l'elenco di tutti i numeri primi fino a
un limite scelto dall'utente, dieci per riga.

## 2. Analisi

### Input

| Variabile | Tipo  | Significato                      |
|-----------|-------|----------------------------------|
| `n`       | `int` | Numero da verificare             |
| `limite`  | `int` | Limite superiore dell'elenco     |

### Output
- Per la verifica: "n e' primo." oppure "n non e' primo: e' divisibile per d
  (n = d x q)."
- Per l'elenco: i numeri primi da 2 al limite, dieci per riga, e il loro
  numero totale.

### Vincoli
- `n >= 2` e `limite >= 2`: la richiesta si ripete finché non è rispettato
  (0 e 1 non sono né primi né composti)
- Basta cercare divisori fino alla radice quadrata di n: se `n = a × b`
  almeno uno dei due fattori è ≤ √n
- La ricerca si ferma al primo divisore trovato, tramite la condizione del
  `for`, senza `break`
- Nell'elenco si va a capo ogni 10 numeri e si aggiunge un a capo finale
  solo se l'ultima riga è incompleta

### Assunzioni
- L'utente inserisce numeri interi

### Variabili di supporto

| Variabile          | Tipo        | Significato                                  |
|--------------------|-------------|----------------------------------------------|
| `d`                | `int`       | Possibile divisore                           |
| `primo`            | `int` (0/1) | Flag: vale 1 finché non si trova un divisore |
| `divisore_trovato` | `int`       | Primo divisore di `n`, se esiste             |
| `numero`           | `int`       | Numero esaminato nell'elenco                 |
| `conta_primi`      | `int`       | Contatore, usato anche per andare a capo     |

La condizione `d * d <= n` evita di usare `<math.h>`; la condizione completa
del ciclo è `d * d <= n && primo`.

### Algoritmo in linguaggio naturale
Verifica di un numero:
1. Leggere n ripetendo la richiesta finché è minore di 2.
2. Porre `primo = 1`.
3. Per d da 2, finché `d * d <= n` e `primo` vale 1: se n è divisibile per
   d, porre `primo = 0` e memorizzare d.
4. Stampare l'esito; se non è primo stampare anche la scomposizione.

Elenco dei primi:
1. Leggere il limite ripetendo finché è minore di 2.
2. Per ogni `numero` da 2 al limite: ripetere la verifica precedente; se è
   primo stamparlo, contarlo e andare a capo ogni 10 numeri
   (`conta_primi % 10 == 0`).
3. Stampare il numero totale di primi.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Numero composto
- **Cosa si verifica:** il ciclo termina subito dopo aver trovato 13, perché
  `primo` diventa 0
- **Input:** 221
- **Output atteso:** "221 non e' primo: e' divisibile per 13 (221 = 13 x 17)."

### Test 2 – Numero primo
- **Cosa si verifica:** il ciclo prova i divisori da 2 a 9 (10 × 10 > 97)
- **Input:** 97
- **Output atteso:** "97 e' primo."

### Test 3 – Elenco dei primi fino a 100
- **Cosa si verifica:** l'a capo ogni 10 numeri e quello finale sulla riga
  incompleta
- **Input:** limite 100
- **Output atteso:** 25 numeri primi su tre righe (10, 10, 5) e
  "Tra 2 e 100 ci sono 25 numeri primi."

### Test 4 – Valore minore di 2
- **Input:** 1
- **Output atteso:** la richiesta viene ripetuta
