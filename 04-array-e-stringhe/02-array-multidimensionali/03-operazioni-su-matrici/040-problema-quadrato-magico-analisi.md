# Analisi – 040-problema-quadrato-magico.c

## 1. Problema

Verificare se una matrice 4 × 4 è un quadrato magico: deve contenere i numeri
da 1 a 16 una sola volta e ogni riga, colonna e diagonale deve avere somma
pari alla costante magica `N (N² + 1) / 2 = 34`. Il programma verifica il
quadrato di Dürer (magico) e una sua variante con due numeri scambiati (non
magica), stampando le somme che non tornano.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `quadrati` | `int[][][]` | 2 × 4 × 4 | I due quadrati da verificare, uno dopo l'altro |
| `conteggio` | `int[]` | 17 | Quante volte compare ogni valore (indice = valore) |
| `costante` | `int` | — | Somma attesa, calcolata dalla formula |
| `somma` | `int` | — | Accumulatore riutilizzato per righe, colonne, diagonali |
| `numeri_validi`, `somme_corrette` | `int` (0/1) | — | Esito dei due controlli |

`quadrati` ha tre dimensioni solo per verificare due esempi con lo stesso
codice: `quadrati[k]` è la matrice *k*.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Quadrato magico

**a) Input** – il quadrato di Dürer

**b) Output** – "Numeri da 1 a 16 presenti una volta: si'" ed
"Esito: QUADRATO MAGICO"

**c) Variabili di supporto** – `conteggio`, `somma`

**d) Vincoli** – entrambi i controlli devono riuscire

**e) Assunzioni** – N = 4

**f) Algoritmo in linguaggio naturale**
1. Azzerare `conteggio`; per ogni cella: se il valore è fuori da [1, 16]
   segnare l'errore, altrimenti incrementare `conteggio[valore]`.
2. Verificare che ogni `conteggio[v]` con v da 1 a 16 valga 1.
3. Per ogni riga, ogni colonna e le due diagonali calcolare la somma; se è
   diversa dalla costante, stamparla e segnare l'errore.
4. Stampare l'esito.

### Caso d'uso 2 – Quadrato non magico

**a) Input** – lo stesso quadrato con 6 e 7 scambiati nella terza riga

**b) Output** – colonne 2 e 3 e le due diagonali con somma 33 o 35; esito negativo

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – i numeri sono ancora tutti presenti: fallisce solo il controllo
delle somme. Le righe restano corrette perché lo scambio avviene nella stessa riga

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1.
