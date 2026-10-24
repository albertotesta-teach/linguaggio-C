# Analisi – 080-problema-crivello-di-eratostene.c

## 1. Problema

Il programma trova i numeri primi fino a n con il crivello di Eratostene.
Serve un flag per ogni numero da 0 a n, all'inizio tutti a 0 (nessun
numero cancellato): `calloc` alloca e azzera n + 1 byte. Stampa quanti
primi ci sono, l'elenco (o i primi 10 e gli ultimi 10) e le coppie di
primi gemelli.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `n` | `int` | Limite, da 2 a 1000000 |

### Output

- `Flag allocati: B byte`.
- `Primi fino a n: P`.
- L'elenco dei primi se sono al massimo 30, altrimenti i primi 10, `...`
  e gli ultimi 10.
- `Coppie di primi gemelli: G`.
- `Numero non valido.`, `Memoria insufficiente.`

### Vincoli

- `composto = calloc(n + 1, sizeof *composto)`: un `char` per numero,
  tutti a 0.
- Crivello: per ogni p con p² ≤ n non cancellato, si cancellano i
  multipli da p² in poi.
- Primi gemelli: p e p + 2 entrambi primi e non oltre n.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `composto` | `char *` | Flag dei numeri cancellati |
| `p`, `m` | `int` | Primo corrente e suoi multipli |
| `primi`, `gemelli`, `contati` | `int` | Contatori |
| `MASSIMO` | `#define` | 1000000 |

### Algoritmo in linguaggio naturale

1. Leggere n e allocare i flag con `calloc`.
2. Applicare il crivello.
3. Contare primi e coppie di gemelli.
4. Stampare il conteggio e l'elenco (completo o abbreviato).
5. Liberare i flag.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Fino a 30

- **Input:** `30`
- **Output atteso:**
  ```
  Primi fino a (da 2 a 1000000): Flag allocati: 31 byte
  Primi fino a 30: 10
   2 3 5 7 11 13 17 19 23 29
  Coppie di primi gemelli: 4
  ```
  (gemelli: 3-5, 5-7, 11-13, 17-19).

### Test 2 – Elenco abbreviato

- **Input:** `1000`
- **Output atteso:**
  ```
  Primi fino a 1000: 168
   2 3 5 7 11 13 17 19 23 29 ... 937 941 947 953 967 971 977 983 991 997
  Coppie di primi gemelli: 35
  ```

### Test 3 – Limiti

- **Input:** `2`; poi `1`
- **Output atteso:** `Primi fino a 2: 1`, ` 2`, `Coppie di primi gemelli:
  0`; poi `Numero non valido.`
