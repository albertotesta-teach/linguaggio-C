# Analisi – 040-problema-cifre-di-un-numero.c

## 1. Problema

Dato un numero intero non negativo, calcolare quante cifre ha, la somma delle
cifre e il numero scritto al contrario, e stabilire se è palindromo (uguale
al suo inverso). Il problema si risolve senza array, usando solo
l'aritmetica intera.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `numero` | `int` | Valore inserito, non viene modificato |
| `resto` | `int` | Copia di lavoro che perde una cifra a ogni iterazione |
| `cifra` | `int` | Ultima cifra estratta: `resto % 10` |
| `numero_cifre` | `int` | Contatore |
| `somma_cifre` | `int` | Accumulatore |
| `inverso` | `int` | Numero costruito al contrario: `inverso * 10 + cifra` |

`n % 10` restituisce l'ultima cifra e `n / 10` la elimina: ripetendo le due
operazioni si visitano tutte le cifre da destra a sinistra.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Numero palindromo

**a) Input** – 12321

**b) Output** – cifre "1 2 3 2 1", 5 cifre, somma 9, inverso 12321,
"12321 e' palindromo."

**c) Variabili di supporto** – `resto`, `cifra`

**d) Vincoli** – `numero` resta invariato per il confronto finale

**e) Assunzioni** – il numero sta in un `int`; l'inverso non supera il
limite di un `int`

**f) Algoritmo in linguaggio naturale**
1. Leggere il numero ripetendo la richiesta finché è negativo (do-while).
2. Contare le cifre: copiare il numero in `resto`; ripetere almeno una
   volta "conta una cifra, dividi `resto` per 10" finché `resto` è maggiore di 0.
3. Copiare di nuovo il numero in `resto`, azzerare somma e inverso.
4. Finché `resto` è maggiore di 0: estrarre la cifra, stamparla, sommarla,
   aggiungerla all'inverso (`inverso = inverso * 10 + cifra`), dividere
   `resto` per 10.
5. Stampare i risultati e confrontare `inverso` con `numero`.

### Caso d'uso 2 – Il numero zero

**a) Input** – 0

**b) Output** – 1 cifra, somma 0, inverso 0, palindromo

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – il conteggio usa un do-while: con un while lo 0 risulterebbe
avere zero cifre. Il ciclo del passo 4 non viene eseguito, quindi la cifra 0
si stampa a parte

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Numero con zeri

**a) Input** – 1203

**b) Output** – somma 6, inverso 3021, non palindromo

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – gli zeri iniziali dell'inverso non compaiono (l'inverso di
120 è 21)

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 4 – Numero negativo

**a) Input** – -5

**b) Output** – "Il numero deve essere >= 0." e nuova richiesta

**c) Variabili di supporto** – nessuna

**d) Vincoli** – la condizione di ripetizione è `numero < 0`

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 1.
