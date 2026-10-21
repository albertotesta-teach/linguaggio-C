# Analisi – 040-problema-equazione-secondo-grado.c

## 1. Problema

Risolvere l'equazione `a x² + b x + c = 0` con coefficienti interi letti da
tastiera, distinguendo tutti i casi possibili: due soluzioni reali distinte,
due soluzioni coincidenti, nessuna soluzione reale e, quando `a = 0`, i tre
casi dell'equazione di primo grado (determinata, impossibile, indeterminata).

## 2. Analisi

### Input

| Variabile     | Tipo  | Significato                                              |
|---------------|-------|----------------------------------------------------------|
| `a`, `b`, `c` | `int` | Coefficienti; interi per calcolare `delta` in modo esatto |

### Output
L'equazione ricostruita a partire dai coefficienti e, a seconda del caso:
- con `a ≠ 0`: il valore di `delta` e le soluzioni reali (due distinte, una
  doppia) oppure il messaggio "Nessuna soluzione reale";
- con `a = 0`: l'avviso che l'equazione è di primo grado e la soluzione
  unica, oppure "Equazione impossibile" o "Equazione indeterminata".

Le soluzioni sono stampate con quattro decimali.

### Vincoli
- Con `a = 0` la formula risolutiva dividerebbe per zero: il controllo su
  `a` va fatto prima di tutto
- `sqrt()` non deve mai essere chiamata con un argomento negativo: la radice
  si calcola solo nel ramo `delta > 0`
- Il denominatore `2a` va scritto tra parentesi e in forma reale
  (`2.0 * a`), altrimenti la divisione sarebbe intera

### Assunzioni
- L'utente inserisce tre numeri interi
- Si considerano solo le soluzioni reali

### Variabili di supporto

| Variabile  | Tipo     | Significato                         |
|------------|----------|-------------------------------------|
| `delta`    | `int`    | Discriminante `b² − 4ac`            |
| `x1`, `x2` | `double` | Soluzioni, in generale non intere   |

Con coefficienti interi il confronto `delta == 0` è esatto. Con coefficienti
reali bisognerebbe confrontare con una tolleranza, come mostrato in
`01-introduzione/02-variabili-e-tipi/020-tipi-reali.c`.

La radice quadrata si calcola con `sqrt()` di `<math.h>`; su Linux il
programma si compila con l'opzione `-lm`.

### Algoritmo in linguaggio naturale
1. Leggere `a`, `b`, `c` e stampare l'equazione.
2. Se `a` vale 0 (equazione di primo grado):
   a. se `b` è diverso da 0: `x1 = -c / b` (divisione reale), stamparla;
   b. altrimenti, se `c` è diverso da 0: l'equazione è impossibile;
   c. altrimenti: l'equazione è indeterminata.
3. Altrimenti calcolare `delta = b * b - 4 * a * c` e stamparlo:
   a. se `delta > 0`: calcolare `x1` e `x2` con la formula risolutiva e
      stamparle;
   b. altrimenti, se `delta == 0`: calcolare `x1 = -b / (2a)` e stamparla
      come soluzione doppia;
   c. altrimenti: stampare che non ci sono soluzioni reali.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso. Serve almeno un test per ciascun ramo
dell'algoritmo.

### Test 1 – Due soluzioni reali distinte
- **Input:** `a = 1`, `b = -3`, `c = 2`
- **Output atteso:** `delta = 1`, `x1 = 2.0000`, `x2 = 1.0000`

### Test 2 – Soluzioni coincidenti
- **Cosa si verifica:** il ramo `delta == 0`, che non calcola la radice
- **Input:** `a = 1`, `b = 2`, `c = 1`
- **Output atteso:** `delta = 0`, `x1 = x2 = -1.0000`

### Test 3 – Nessuna soluzione reale
- **Cosa si verifica:** `sqrt()` non viene chiamata con delta negativo
- **Input:** `a = 1`, `b = 1`, `c = 5`
- **Output atteso:** `delta = -19` e il messaggio "Nessuna soluzione reale"

### Test 4 – Primo grado determinata
- **Input:** `a = 0`, `b = 2`, `c = -4`
- **Output atteso:** "Soluzione unica: x = 2.0000"

### Test 5 – Primo grado impossibile
- **Input:** `a = 0`, `b = 0`, `c = 3`
- **Output atteso:** "Equazione impossibile"

### Test 6 – Primo grado indeterminata
- **Input:** `a = 0`, `b = 0`, `c = 0`
- **Output atteso:** "Equazione indeterminata"
