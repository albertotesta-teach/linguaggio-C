# Analisi – 070-problema-inventario-negozi.c

## 1. Problema

Una catena di 4 negozi vende 5 prodotti. Ogni prodotto ha una scorta minima
per negozio. Il programma deve stampare l'inventario, individuare i prodotti
sotto scorta in ogni negozio e riassortirli trasferendo i pezzi mancanti dal
negozio più fornito, purché questo resti almeno alla scorta minima; infine
stampa l'inventario aggiornato.

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile       | Tipo       | Dimensione | Descrizione                                 |
|-----------------|------------|------------|---------------------------------------------|
| `giacenze`      | `int[][]`  | 4 × 5      | Riga = negozio, colonna = prodotto          |
| `negozi`        | `char[][]` | 4 × 14     | Nomi, paralleli alle righe                  |
| `prodotti`      | `char[][]` | 5 × 14     | Nomi, paralleli alle colonne                |
| `scorta_minima` | `int[]`    | 5          | Soglia per prodotto, parallela alle colonne |

### Output
- L'inventario iniziale con il totale di ogni prodotto nella catena;
- per ogni prodotto sotto scorta in un negozio: giacenza e minimo, poi
  "Trasferiti N da …" oppure "Nessun negozio puo' cederli: da ordinare.";
- l'inventario aggiornato.

### Vincoli
- Un prodotto è sotto scorta in un negozio se la giacenza è **minore** della
  scorta minima di quel prodotto (soglia per **colonna**)
- I pezzi da trasferire sono quelli che mancano per tornare esattamente alla
  scorta minima
- Il fornitore è il negozio con più pezzi di quel prodotto (massimo della
  colonna); a parità il primo
- Il trasferimento avviene solo se il fornitore è un altro negozio e se,
  dopo aver ceduto i pezzi, resta almeno alla scorta minima; altrimenti la
  matrice non cambia
- I trasferimenti modificano la matrice durante la scansione: un negozio che
  ha ceduto merce può diventare il fornitore meno conveniente per i
  controlli successivi
- Il totale di ogni prodotto nella catena non cambia con i trasferimenti
- Nel parametro di una matrice di caratteri va indicata la seconda
  dimensione: `const char negozi[][LUNG]`

### Assunzioni
- Non si considerano costi o distanze tra i negozi

### Variabili di supporto

| Variabile   | Tipo  | Descrizione                                       |
|-------------|-------|---------------------------------------------------|
| `mancanti`  | `int` | Pezzi necessari per tornare alla scorta minima    |
| `fornitore` | `int` | Negozio più fornito del prodotto                  |

| Funzione | Descrizione |
|---|---|
| `int totale_prodotto(const int g[][PRODOTTI], int p)` | Somma della colonna p |
| `int negozio_piu_fornito(const int g[][PRODOTTI], int p)` | Indice del massimo della colonna p |
| `int trasferisci(int g[][PRODOTTI], int da, int a, int p, int pezzi, int minimo)` | 1 se il trasferimento è avvenuto |
| `void stampa_inventario(...)` | Tabella con riga dei totali |

### Algoritmo in linguaggio naturale
1. Stampare l'inventario iniziale.
2. Per ogni negozio e ogni prodotto sotto scorta:
   a. calcolare i pezzi mancanti e trovare il negozio più fornito;
   b. se il fornitore è un altro negozio e, dopo la cessione, gli restano
      almeno i pezzi della scorta minima, spostare i pezzi e stamparlo;
   c. altrimenti stampare che il prodotto va ordinato.
3. Stampare l'inventario aggiornato.

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il Test 3
richiede di modificare le scorte minime e ricompilare.

### Test 1 – Riassortimento
- **Output atteso:**
```
Alessandria: Racchette sotto scorta (3, minimo 4). Trasferiti 1 da Novi.
Novi: Palloni sotto scorta (2, minimo 5). Trasferiti 3 da Acqui.
Tortona: Borracce sotto scorta (4, minimo 8). Trasferiti 4 da Novi.
Acqui: Racchette sotto scorta (1, minimo 4). Trasferiti 3 da Novi.
Acqui: Zaini sotto scorta (3, minimo 5). Trasferiti 2 da Novi.
```

### Test 2 – Inventario aggiornato
- **Cosa si verifica:** ogni negozio ha raggiunto la scorta minima e i
  totali per prodotto sono invariati
- **Output atteso:**
```
  Alessandria          12          4         25          8         40
  Novi                  5         11         26         10         35
  Tortona               9          6          8         10         18
  Acqui                17          4         18          5         50
  Totale               43         25         77         33        143
```

### Test 3 – Trasferimento non possibile
- **Cosa si verifica:** il fornitore non può scendere sotto la scorta minima
- **Procedura:** portare la scorta minima dei palloni da 5 a 15
- **Output atteso:**
```
Alessandria: Palloni sotto scorta (12, minimo 15). Trasferiti 3 da Acqui.
Novi: Palloni sotto scorta (2, minimo 15). Nessun negozio puo' cederli: da ordinare.
Tortona: Palloni sotto scorta (9, minimo 15). Nessun negozio puo' cederli: da ordinare.
```
