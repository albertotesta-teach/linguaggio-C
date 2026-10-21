# Analisi – 040-problema-prodotto-matrici.c

## 1. Problema

Tre negozi ordinano quattro articoli a un grossista che ha due listini
(ingrosso e prezzo al pubblico). Moltiplicando la matrice degli ordini
(negozi × articoli) per quella dei prezzi (articoli × listini) si ottiene,
per ogni negozio, la spesa e il ricavo previsto. Il programma deve calcolare
il prodotto, il margine di ogni negozio e rifiutare un prodotto con
dimensioni incompatibili.

## 2. Analisi

### Input
Nessun input da tastiera: le due matrici sono inizializzate nel codice.

| Variabile | Tipo         | Dimensione            | Descrizione                         |
|-----------|--------------|-----------------------|-------------------------------------|
| `ordini`  | `double[][]` | 5 × 5, usata 3 × 4    | Pezzi ordinati: negozi × articoli   |
| `prezzi`  | `double[][]` | 5 × 5, usata 4 × 2    | Prezzi: articoli × listini          |

### Output
- Le matrici degli ordini e dei prezzi;
- la matrice dei costi (negozi × listini) e, per ogni negozio, spesa
  all'ingrosso, ricavo al pubblico e margine;
- l'esito del prodotto nell'ordine inverso (prezzi × ordini), rifiutato per
  dimensioni incompatibili.

### Vincoli
- Il prodotto A × B esiste solo se le **colonne di A** sono quante le
  **righe di B**; il risultato ha le righe di A e le colonne di B
- `costi[i][j] = Σk ordini[i][k] × prezzi[k][j]`: riga i della prima per
  colonna j della seconda; ogni cella va azzerata prima di accumulare
- Se le dimensioni sono incompatibili la funzione restituisce 0 e non tocca
  il risultato
- Il prodotto tra matrici non è commutativo: ordini × prezzi esiste,
  prezzi × ordini no
- Margine = ricavo − spesa
- Nel parametro di una matrice il numero di colonne è fisso: per lavorare
  con dimensioni diverse tutte le matrici sono dichiarate `MAX × MAX`,
  usate in parte, e le dimensioni effettive si passano come parametri

### Assunzioni
- Le dimensioni effettive non superano `MAX`

### Variabili di supporto

| Variabile | Tipo         | Dimensione         | Descrizione                    |
|-----------|--------------|--------------------|--------------------------------|
| `costi`   | `double[][]` | 5 × 5, usata 3 × 2 | Risultato del prodotto         |
| `esito`   | `int` (0/1)  | —                  | Prodotto possibile o no        |
| `MAX`, `NEGOZI`, `ARTICOLI`, `LISTINI` | `#define` | — | 5, 3, 4, 2       |

| Funzione | Descrizione |
|---|---|
| `void stampa_matrice(const double m[][MAX], int righe, int colonne)` | Stampa la parte usata |
| `int moltiplica(a, righe_a, colonne_a, b, righe_b, colonne_b, risultato)` | 1 se il prodotto è possibile, 0 altrimenti |

### Algoritmo in linguaggio naturale
1. Stampare ordini e prezzi.
2. `moltiplica`: se `colonne_a ≠ righe_b` restituire 0; altrimenti, per ogni
   riga i di A e colonna j di B, azzerare `risultato[i][j]` e sommarvi
   `a[i][k] × b[k][j]` per k da 0 a `colonne_a − 1`; restituire 1.
3. Se il prodotto è riuscito stampare i costi e, per ogni negozio, spesa,
   ricavo e margine.
4. Provare il prodotto inverso e stampare il motivo del rifiuto.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Prodotto e margini
- **Valori intermedi attesi:** negozio 1, ingrosso:
  10 × 12.50 + 5 × 8.00 + 20 × 3.20 + 0 × 22.00 = 229.00
- **Output atteso:**
```
=== COSTI = ORDINI x PREZZI (negozi x listini) ===
   229.00   389.50
   341.20   561.00
   292.00   472.00

  Negozio   Spesa   Ricavo   Margine
        1  229.00   389.50    160.50
        2  341.20   561.00    219.80
        3  292.00   472.00    180.00
```

### Test 2 – Dimensioni incompatibili
- **Cosa si verifica:** il prodotto nell'ordine inverso è rifiutato
- **Output atteso:**
```
Prova: prezzi (4 x 2) x ordini (3 x 4)
  Dimensioni incompatibili: le colonne del primo (2) devono
  essere quante le righe del secondo (3).
```
