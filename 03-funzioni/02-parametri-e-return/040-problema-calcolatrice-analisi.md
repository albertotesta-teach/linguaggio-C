# Analisi – 040-problema-calcolatrice.c

## 1. Problema
Una calcolatrice a riga di comando legge dall'utente due operandi reali e un
operatore aritmetico (`+`, `-`, `*`, `/`) e stampa il risultato. Tutte le
funzioni di calcolo hanno la stessa struttura: ricevono due `double` e
restituiscono un `double`. La stampa è responsabilità esclusiva del main.
La divisione per zero restituisce 0.0 come valore convenzionale.

## 2. Analisi

### Input

| Variabile | Tipo | Descrizione |
|---|---|---|
| `a`, `b` | double | Operandi |
| `operatore` | char | Simbolo dell'operazione |

I tre valori si inseriscono su una riga nel formato `numero operatore numero`
(es. `12.5 + 7.3`).

### Output
La riga `a op b = risultato`, con operandi e risultato a due decimali, oppure
il messaggio `Operatore 'x' non riconosciuto.`

### Vincoli
- L'operatore è uno tra `+`, `-`, `*`, `/`; ogni altro carattere cade nel
  ramo `else` finale
- Con `b == 0.0` la divisione non viene eseguita: `op_quoziente` restituisce
  0.0, un valore che il chiamante non può distinguere da un risultato
  legittimo
- Le funzioni di calcolo non stampano nulla: la stampa è affidata a
  `stampa_risultato`

### Assunzioni
- L'utente inserisce il formato `numero operatore numero` correttamente
- L'operatore è un solo carattere
- La limitazione della divisione per zero è accettata in questa versione:
  tecniche più robuste arrivano nei capitoli successivi

### Variabili di supporto

| Variabile | Tipo | Descrizione |
|---|---|---|
| `risultato` | double | Valore restituito dalla funzione di calcolo |

| Funzione | Firma | Descrizione |
|---|---|---|
| `op_somma` | `double(double, double)` | Addizione |
| `op_differenza` | `double(double, double)` | Sottrazione |
| `op_prodotto` | `double(double, double)` | Moltiplicazione |
| `op_quoziente` | `double(double, double)` | Divisione; restituisce 0.0 se b == 0.0 |
| `stampa_risultato` | `void(double, char, double, double)` | Formattazione e stampa |

Tutte le funzioni di calcolo hanno la stessa firma `double(double, double)`,
che rende il codice uniforme e prevedibile.

### Algoritmo in linguaggio naturale
1. Leggere `a`, `operatore`, `b`.
2. Se l'operatore è `+`, `-` o `*`: chiamare la funzione corrispondente e
   stampare il risultato con `stampa_risultato`.
3. Altrimenti, se è `/`: chiamare `op_quoziente`, che restituisce `a / b`
   se `b` è diverso da 0.0 e 0.0 altrimenti; stampare il risultato.
4. Altrimenti stampare che l'operatore non è riconosciuto.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Somma
- **Input:** `12.5 + 7.3`
- **Output atteso:** `12.50 + 7.30 = 19.80`

### Test 2 – Prodotto con operando negativo
- **Input:** `6 * -1.5`
- **Output atteso:** `6.00 * -1.50 = -9.00`

### Test 3 – Divisione valida
- **Input:** `10.0 / 4.0`
- **Output atteso:** `10.00 / 4.00 = 2.50`

### Test 4 – Divisione per zero
- **Cosa si verifica:** il valore convenzionale 0.0
- **Input:** `8.0 / 0.0`
- **Output atteso:** `8.00 / 0.00 = 0.00`

### Test 5 – Operatore non riconosciuto
- **Cosa si verifica:** il ramo `else` finale
- **Input:** `5.0 ^ 2.0`
- **Output atteso:** `Operatore '^' non riconosciuto.`
