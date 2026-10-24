# Analisi – 050-problema-tabella-dei-voti.c

## 1. Problema

Il tabellone dello scrutinio ha una riga per studente e una colonna per
materia; il numero di righe e di colonne si sceglie all'avvio. Si alloca
un unico blocco di righe × colonne `double` con le righe una dopo
l'altra: l'elemento (r, c) sta in `tab[r * colonne + c]`. Il programma
stampa il tabellone con le medie per studente e per materia e lo studente
migliore.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `righe`, `colonne` | `int` | Studenti 1-30, materie 1-6 |
| voti | `double` | Un voto da 1 a 10 per ogni cella, riga per riga |

### Output

- `Blocco di R x C = N double (B byte)`.
- Il tabellone con le materie (ITA, MAT, ING, INF, STO, SCI), la media di
  ogni studente e la riga delle medie per materia.
- `Media piu' alta: studente S con M`.
- `Dimensioni non valide (...)`, `Memoria insufficiente.`,
  `Voti mancanti o non validi.`

### Vincoli

- Un solo `malloc(righe * colonne * sizeof *tab)` dentro `crea_tabella`,
  controllo di `NULL`, `free` nel `main`.
- Indice lineare `r * colonne + c` calcolato da `indice`.
- Al primo voto mancante, non numerico o fuori da 1-10 la lettura si
  ferma e il tabellone non viene stampato.
- A parità di media vale il primo studente.

### Assunzioni

- I voti di uno studente si scrivono sulla stessa riga.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `tab` | `double *` | Blocco unico della tabella |
| `righe`, `colonne` | `int` | Dimensioni |
| `media_migliore`, `migliore` | `double`, `int` | Studente migliore |

| Funzione | Compito |
|----------|---------|
| `crea_tabella(righe, colonne)` | Alloca il blocco |
| `indice(r, c, colonne)` | Posizione dell'elemento (r, c) |
| `leggi_tabella(tab, righe, colonne)` | Legge i voti; 0 se uno manca o non è valido |
| `stampa_tabella(tab, righe, colonne)` | Tabellone con medie |

### Algoritmo in linguaggio naturale

1. Leggere le dimensioni e controllarle.
2. Allocare il blocco e stamparne la dimensione.
3. Leggere i voti; se tutti validi stampare il tabellone con le medie per
   riga e per colonna e lo studente migliore.
4. Liberare il blocco.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Tre studenti, quattro materie

- **Input:** `3 4`, `7 8 6 9`, `5 6 5.5 7`, `8 9 9 10`
- **Valori intermedi attesi:** 12 double × 8 byte = 96 byte; media dello
  studente 2: 23.5 / 4 = 5.88.
- **Output atteso:**
  ```
  Blocco di 3 x 4 = 12 double (96 byte)

               ITA  MAT  ING  INF  media
  studente  1  7.0  8.0  6.0  9.0   7.50
  studente  2  5.0  6.0  5.5  7.0   5.88
  studente  3  8.0  9.0  9.0 10.0   9.00
  media        6.7  7.7  6.8  8.7

  Media piu' alta: studente 3 con 9.00
  ```

### Test 2 – Voto non valido

- **Input:** `2 2`, `7 8`, `5 11`
- **Output atteso:** `Voti mancanti o non validi.`

### Test 3 – Dimensioni non valide

- **Input:** `0 3`
- **Output atteso:** `Dimensioni non valide (studenti 1-30, materie 1-6).`
