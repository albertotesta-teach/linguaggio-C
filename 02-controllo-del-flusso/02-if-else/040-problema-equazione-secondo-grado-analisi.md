# Analisi – 040-problema-equazione-secondo-grado.c

## 1. Problema

Risolvere l'equazione `a x² + b x + c = 0` con coefficienti interi letti da
tastiera, distinguendo tutti i casi possibili: due soluzioni reali distinte,
due soluzioni coincidenti, nessuna soluzione reale e, quando `a = 0`, i tre
casi dell'equazione di primo grado (determinata, impossibile, indeterminata).

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `a`, `b`, `c` | `int` | Coefficienti; interi per calcolare `delta` in modo esatto |
| `delta` | `int` | Discriminante `b² − 4ac` |
| `x1`, `x2` | `double` | Soluzioni, in generale non intere |

Con coefficienti interi il confronto `delta == 0` è esatto. Con coefficienti
reali bisognerebbe confrontare con una tolleranza, come mostrato in
`01-introduzione/02-variabili-e-tipi/020-tipi-reali.c`.

La radice quadrata si calcola con `sqrt()` di `<math.h>`; su Linux il
programma si compila con l'opzione `-lm`.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Due soluzioni reali distinte

**a) Input** – `a = 1`, `b = -3`, `c = 2`

**b) Output** – `delta = 1`, `x1 = 2.0000`, `x2 = 1.0000`

**c) Variabili di supporto** – `delta`

**d) Vincoli** – il denominatore `2a` va scritto tra parentesi e in forma
reale (`2.0 * a`)

**e) Assunzioni** – l'utente inserisce tre numeri interi

**f) Algoritmo in linguaggio naturale**
1. Leggere `a`, `b`, `c` e stampare l'equazione.
2. Se `a` vale 0, passare al caso dell'equazione di primo grado (caso d'uso 4).
3. Altrimenti calcolare `delta = b * b - 4 * a * c`.
4. Se `delta > 0`: calcolare `x1` e `x2` con la formula risolutiva e stamparle.
5. Altrimenti, se `delta == 0`: calcolare `x1 = -b / (2a)` e stamparla come
   soluzione doppia.
6. Altrimenti: stampare che non ci sono soluzioni reali.

### Caso d'uso 2 – Soluzioni coincidenti

**a) Input** – `a = 1`, `b = 2`, `c = 1`

**b) Output** – `delta = 0`, `x1 = x2 = -1.0000`

**c) Variabili di supporto** – `delta`

**d) Vincoli** – il ramo `delta == 0` non calcola la radice

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 5.

### Caso d'uso 3 – Nessuna soluzione reale

**a) Input** – `a = 1`, `b = 1`, `c = 5`

**b) Output** – `delta = -19` e il messaggio "Nessuna soluzione reale"

**c) Variabili di supporto** – `delta`

**d) Vincoli** – `sqrt()` non viene mai chiamata con un argomento negativo

**e) Assunzioni** – si considerano solo le soluzioni reali

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 6.

### Caso d'uso 4 – Equazione di primo grado (a = 0)

**a) Input** – per esempio `0 2 -4`, `0 0 3`, `0 0 0`

**b) Output** – rispettivamente "Soluzione unica: x = 2.0000",
"Equazione impossibile", "Equazione indeterminata"

**c) Variabili di supporto** – `x1`

**d) Vincoli** – con `a = 0` la formula risolutiva dividerebbe per zero,
quindi il controllo su `a` va fatto prima di tutto

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale**
1. Se `b` è diverso da 0: `x1 = -c / b` (divisione reale), stamparla.
2. Altrimenti, se `c` è diverso da 0: l'equazione è impossibile.
3. Altrimenti: l'equazione è indeterminata.
