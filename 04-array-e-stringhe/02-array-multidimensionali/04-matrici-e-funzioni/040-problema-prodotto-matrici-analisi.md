# Analisi – 040-problema-prodotto-matrici.c

## 1. Problema

Tre negozi ordinano quattro articoli a un grossista che ha due listini
(ingrosso e prezzo al pubblico). Moltiplicando la matrice degli ordini
(negozi × articoli) per quella dei prezzi (articoli × listini) si ottiene,
per ogni negozio, la spesa e il ricavo previsto. Il programma deve calcolare
il prodotto, il margine di ogni negozio e rifiutare un prodotto con
dimensioni incompatibili.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `ordini` | `double[][]` | 5 × 5, usata 3 × 4 | Pezzi ordinati |
| `prezzi` | `double[][]` | 5 × 5, usata 4 × 2 | Prezzo per articolo e listino |
| `costi` | `double[][]` | 5 × 5, usata 3 × 2 | Risultato del prodotto |
| `esito` | `int` (0/1) | — | Prodotto possibile o no |

Tutte le matrici sono dichiarate `MAX × MAX` e usate solo in parte: così una
sola funzione può lavorare su dimensioni diverse, ricevendo righe e colonne
effettive come parametri.

Formula: `costi[i][j] = Σk ordini[i][k] · prezzi[k][j]`, possibile solo se
le colonne della prima matrice sono quante le righe della seconda.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prodotto possibile

**a) Input** – ordini 3 × 4 e prezzi 4 × 2

**b) Output** – matrice dei costi 3 × 2 e tabella con spesa, ricavo e margine
(negozio 1: 229.00, 389.50, 160.50)

**c) Variabili di supporto** – nella funzione: `i`, `j`, `k`, `possibile`

**d) Vincoli** – ogni elemento del risultato si azzera prima di accumulare

**e) Assunzioni** – dimensioni non superiori a `MAX`

**f) Algoritmo in linguaggio naturale**
1. Verificare `colonne_a == righe_b`.
2. Se possibile, per ogni riga i di a e colonna j di b: azzerare
   `risultato[i][j]` e sommare i prodotti `a[i][k] · b[k][j]` per k.
3. Restituire l'esito; il main stampa costi e margini (ricavo − spesa).

### Caso d'uso 2 – Dimensioni incompatibili

**a) Input** – prezzi (4 × 2) per ordini (3 × 4)

**b) Output** – messaggio che spiega la condizione non rispettata (2 ≠ 3)

**c) Variabili di supporto** – `esito`

**d) Vincoli** – la matrice risultato non viene modificata

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 1: la
funzione restituisce 0 senza calcolare nulla.
