# Analisi – 040-problema-cifre-di-un-numero.c

## 1. Problema

Dato un numero intero non negativo, calcolare quante cifre ha, la somma delle
cifre e il numero scritto al contrario, e stabilire se è palindromo (uguale
al suo inverso). Il problema si risolve senza array, usando solo
l'aritmetica intera.

## 2. Analisi

### Input

| Variabile | Tipo  | Significato                                  |
|-----------|-------|----------------------------------------------|
| `numero`  | `int` | Valore inserito, non viene modificato        |

### Output
Le cifre del numero da destra a sinistra, il numero di cifre, la somma delle
cifre, l'inverso e l'esito del controllo di palindromia. Se il numero è
negativo, un messaggio di errore e una nuova richiesta.

### Vincoli
- `numero >= 0`: la richiesta si ripete finché il valore è negativo
- `numero` resta invariato, perché serve per il confronto finale con
  l'inverso
- Lo 0 ha una cifra: per questo il conteggio usa un do-while (con un while
  lo 0 risulterebbe avere zero cifre)

### Assunzioni
- Il numero e il suo inverso stanno in un `int`
- Gli zeri iniziali dell'inverso non compaiono (l'inverso di 120 è 21)

### Variabili di supporto

| Variabile      | Tipo  | Significato                                              |
|----------------|-------|----------------------------------------------------------|
| `resto`        | `int` | Copia di lavoro che perde una cifra a ogni iterazione    |
| `cifra`        | `int` | Ultima cifra estratta: `resto % 10`                      |
| `numero_cifre` | `int` | Contatore                                                |
| `somma_cifre`  | `int` | Accumulatore                                             |
| `inverso`      | `int` | Numero costruito al contrario: `inverso * 10 + cifra`    |

`n % 10` restituisce l'ultima cifra e `n / 10` la elimina: ripetendo le due
operazioni si visitano tutte le cifre da destra a sinistra.

### Algoritmo in linguaggio naturale
1. Leggere il numero ripetendo la richiesta finché è negativo (do-while).
2. Contare le cifre: copiare il numero in `resto`; ripetere almeno una
   volta "conta una cifra, dividi `resto` per 10" finché `resto` è maggiore di 0.
3. Copiare di nuovo il numero in `resto`, azzerare somma e inverso.
4. Finché `resto` è maggiore di 0: estrarre la cifra, stamparla, sommarla,
   aggiungerla all'inverso (`inverso = inverso * 10 + cifra`), dividere
   `resto` per 10. Con il numero 0 il ciclo non viene eseguito, quindi la
   cifra 0 si stampa a parte.
5. Stampare i risultati e confrontare `inverso` con `numero`.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Numero palindromo
- **Input:** 12321
- **Output atteso:** cifre "1 2 3 2 1", 5 cifre, somma 9, inverso 12321,
  "12321 e' palindromo."

### Test 2 – Il numero zero
- **Cosa si verifica:** il caso limite che giustifica il do-while nel
  conteggio
- **Input:** 0
- **Output atteso:** 1 cifra, somma 0, inverso 0, palindromo

### Test 3 – Numero con zeri
- **Cosa si verifica:** le cifre 0 nel mezzo e in fondo al numero
- **Input:** 1203
- **Output atteso:** somma 6, inverso 3021, non palindromo

### Test 4 – Numero negativo
- **Cosa si verifica:** la validazione con la condizione `numero < 0`
- **Input:** -5
- **Output atteso:** "Il numero deve essere >= 0." e nuova richiesta
