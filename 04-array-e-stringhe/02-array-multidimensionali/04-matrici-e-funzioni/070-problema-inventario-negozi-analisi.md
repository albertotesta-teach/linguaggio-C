# Analisi – 070-problema-inventario-negozi.c

## 1. Problema

Una catena di 4 negozi vende 5 prodotti. Ogni prodotto ha una scorta minima
per negozio. Il programma deve stampare l'inventario, individuare i prodotti
sotto scorta in ogni negozio e riassortirli trasferendo i pezzi mancanti dal
negozio più fornito, purché questo resti almeno alla scorta minima; infine
stampa l'inventario aggiornato.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `giacenze` | `int[][]` | 4 × 5 | Riga = negozio, colonna = prodotto |
| `negozi` | `char[][]` | 4 × 14 | Nomi, paralleli alle righe |
| `prodotti` | `char[][]` | 5 × 14 | Nomi, paralleli alle colonne |
| `scorta_minima` | `int[]` | 5 | Soglia per prodotto, parallela alle colonne |
| `mancanti` | `int` | — | Pezzi necessari per tornare alla scorta minima |
| `fornitore` | `int` | — | Negozio più fornito del prodotto |

| Funzione | Compito |
|----------|---------|
| `totale_prodotto(g, p)` | Somma della colonna p |
| `negozio_piu_fornito(g, p)` | Indice del massimo nella colonna p |
| `trasferisci(g, da, a, p, pezzi, minimo)` | Sposta i pezzi se possibile; 1/0 |
| `stampa_inventario(g, negozi, prodotti)` | Tabella con riga dei totali |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Riassortimento riuscito

**a) Input** – Novi ha 2 palloni (minimo 5); il più fornito è Acqui con 20

**b) Output** – "Novi: Palloni sotto scorta (2, minimo 5). Trasferiti 3 da Acqui."

**c) Variabili di supporto** – `mancanti`, `fornitore`

**d) Vincoli** – il negozio fornitore deve restare almeno alla scorta minima;
i totali per prodotto non cambiano dopo i trasferimenti

**e) Assunzioni** – i negozi si esaminano nell'ordine; un trasferimento può
cambiare il fornitore migliore per le richieste successive

**f) Algoritmo in linguaggio naturale**
1. Per ogni negozio e prodotto: se la giacenza è sotto la scorta minima,
   calcolare i mancanti e il negozio più fornito.
2. Se il fornitore è un altro negozio e `trasferisci` riesce, stampare il
   trasferimento; altrimenti indicare che il prodotto va ordinato.

### Caso d'uso 2 – Trasferimento impossibile

**a) Input** – un prodotto sotto scorta per cui il negozio più fornito
scenderebbe sotto il minimo (o il più fornito è lo stesso negozio)

**b) Output** – "Nessun negozio puo' cederli: da ordinare."

**c) Variabili di supporto** – esito di `trasferisci`

**d) Vincoli** – la matrice resta invariata

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 2.
