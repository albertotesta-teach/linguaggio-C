# Analisi – 060-problema-triangolo-distanze.c

## 1. Problema

Il pulmino della scuola collega cinque paesi. Le distanze sono simmetriche
e nulle sulla diagonale, quindi si memorizza solo la metà della tabella
sotto la diagonale, con righe di lunghezza diversa. Il programma stampa la
tabella completa e la lunghezza di due giri.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `paesi` | `const char *[5]` | Scuola, Borgo, Collina, Ponte, Lago |
| `r1` … `r4` | `int[1]` … `int[4]` | Distanze dal paese `i` ai paesi 0 … `i − 1`: {7}, {12, 6}, {9, 15, 18}, {14, 10, 8, 21} |
| `giro_mattina`, `giro_alternativo` | `int[5]` | Sequenze di tappe: 0 3 1 2 4 e 0 1 2 4 3 |

### Output

- La tabella completa 5 × 5 delle distanze.
- Ciascun giro con le tappe e la lunghezza in km.

### Vincoli

- `righe` è un array di puntatori a righe di lunghezza diversa (tabella
  triangolare); la riga 0 non ha elementi ed è `NULL`.
- `distanza(a, b)` legge sempre `righe[maggiore][minore]` (le distanze sono
  simmetriche) e restituisce 0 se `a == b`: la riga 0 non si dereferenzia
  mai, perché il primo indice è sempre il maggiore.
- La lunghezza di un giro è la somma delle distanze tra tappe consecutive;
  il giro non torna alla scuola.

### Assunzioni

- Distanze simmetriche in km interi.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `righe` | `const int *[5]` | Puntatori alle righe (`NULL` per il paese 0) |
| `i`, `j` | `int` | Indici della tabella e delle tappe |

| Funzione | Compito |
|----------|---------|
| `distanza(righe, a, b)` | Legge `righe[maggiore][minore]`, 0 se `a == b` |
| `lunghezza_giro(righe, giro, tappe)` | Somma delle distanze tra tappe consecutive |

### Algoritmo in linguaggio naturale

1. Stampare l'intestazione e, per ogni coppia `(i, j)`, `distanza(i, j)`.
2. Per ogni giro stampare le tappe separate da `->` e la lunghezza.

## 3. Casi di test

### Test 1 – Tabella e giri

- **Input:** nessuno.
- **Valori intermedi attesi:** Borgo (1) – Ponte (3): `righe[3][1]` = 15;
  giro del mattino 9 + 15 + 6 + 8 = 38.
- **Output atteso:**
  ```
  Tabella delle distanze (km):
               Scuola    Borgo  Collina    Ponte     Lago
  Scuola            0        7       12        9       14
  Borgo             7        0        6       15       10
  Collina          12        6        0       18        8
  Ponte             9       15       18        0       21
  Lago             14       10        8       21        0

  Giro del mattino:   Scuola -> Ponte -> Borgo -> Collina -> Lago  = 38 km
  Giro alternativo:   Scuola -> Borgo -> Collina -> Lago -> Ponte  = 42 km
  ```
