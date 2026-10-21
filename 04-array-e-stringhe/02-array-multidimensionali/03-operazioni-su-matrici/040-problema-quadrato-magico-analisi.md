# Analisi – 040-problema-quadrato-magico.c

## 1. Problema

Verificare se una matrice 4 × 4 è un quadrato magico: deve contenere i numeri
da 1 a 16 una sola volta e ogni riga, colonna e diagonale deve avere somma
pari alla costante magica `N (N² + 1) / 2 = 34`. Il programma verifica il
quadrato di Dürer (magico) e una sua variante con due numeri scambiati (non
magica), stampando le somme che non tornano.

## 2. Analisi

### Input
Nessun input da tastiera: i due quadrati sono inizializzati nel codice.

| Variabile  | Tipo        | Dimensione | Descrizione                                     |
|------------|-------------|------------|-------------------------------------------------|
| `quadrati` | `int[][][]` | 2 × 4 × 4  | I due quadrati; `quadrati[k]` è la matrice k    |

### Output
Per ogni quadrato:
- la matrice;
- se i numeri da 1 a 16 compaiono una volta sola ("si'" / "no");
- la costante magica attesa;
- le righe, colonne e diagonali la cui somma è diversa dalla costante, con
  la somma trovata;
- l'esito: "QUADRATO MAGICO" oppure "non e' un quadrato magico".

### Vincoli
- La costante si calcola dalla formula `N × (N² + 1) / 2`, non è scritta a
  mano
- Il controllo dei numeri usa un array di contatori indicizzato dal valore:
  un valore fuori da 1–16 o un contatore diverso da 1 rendono il quadrato
  non valido
- Si controllano tutte le N righe, le N colonne e le due diagonali; la
  diagonale secondaria usa la colonna `N − 1 − i`
- Il quadrato è magico solo se entrambi i controlli sono superati
- Si stampano tutte le somme sbagliate, non solo la prima, per mostrare
  dove fallisce
- I contatori si azzerano prima di verificare ogni quadrato

### Assunzioni
- Le matrici sono quadrate di ordine `N`

### Variabili di supporto

| Variabile        | Tipo        | Dimensione | Descrizione                                |
|------------------|-------------|------------|--------------------------------------------|
| `conteggio`      | `int[]`     | 17         | Presenze di ogni valore (indice = valore)  |
| `costante`       | `int`       | —          | Somma attesa                               |
| `somma`          | `int`       | —          | Accumulatore per righe, colonne, diagonali |
| `numeri_validi`, `somme_corrette` | `int` (0/1) | — | Esito dei due controlli      |
| `N`, `MAX_VALORE`| `#define`   | —          | 4 e 16                                     |

### Algoritmo in linguaggio naturale
Per ciascuno dei due quadrati:
1. Stampare la matrice.
2. Azzerare i contatori; per ogni cella, se il valore è fuori da 1–16
   segnare i numeri come non validi, altrimenti incrementarne il contatore;
   poi verificare che ogni contatore da 1 a 16 valga 1.
3. Per ogni riga, ogni colonna e le due diagonali calcolare la somma e, se
   diversa dalla costante, stamparla e segnare le somme come non corrette.
4. Stampare l'esito.

## 3. Casi di test

Il programma non legge dati: si esegue con i due quadrati del codice; il
Test 3 richiede di modificare il primo quadrato e ricompilare.

### Test 1 – Quadrato di Dürer
- **Output atteso:**
```
Numeri da 1 a 16 presenti una volta: si'
Costante magica attesa: 34
Esito: QUADRATO MAGICO
```

### Test 2 – Due numeri scambiati
- **Cosa si verifica:** i numeri sono ancora tutti presenti, ma le somme di
  due colonne e delle diagonali cambiano; le righe restano corrette
- **Output atteso:**
```
Numeri da 1 a 16 presenti una volta: si'
Costante magica attesa: 34
  colonna 2: somma 35
  colonna 3: somma 33
  diagonale principale: somma 33
  diagonale secondaria: somma 35
Esito: non e' un quadrato magico
```

### Test 3 – Numero ripetuto
- **Cosa si verifica:** il controllo dei numeri fallisce
- **Procedura:** nel primo quadrato sostituire l'ultimo valore (1) con 16
- **Output atteso:** `Numeri da 1 a 16 presenti una volta: no`; le somme
  sbagliate `riga 4: somma 49`, `colonna 4: somma 49`,
  `diagonale principale: somma 49`; esito non magico
