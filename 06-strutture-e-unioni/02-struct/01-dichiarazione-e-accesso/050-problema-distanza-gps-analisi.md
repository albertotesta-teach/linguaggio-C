# Analisi – 050-problema-distanza-gps.c

## 1. Problema

Per l'uscita didattica si leggono le coordinate di partenza e di arrivo
(latitudine e longitudine in gradi decimali) e si calcola la distanza in
linea d'aria con la formula dell'emisenoverso. Il programma stima anche il
tempo a piedi, maggiorando la distanza del 30% per le strade e camminando
a 4.5 km/h. Ogni coppia di coordinate è una struct `Punto`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `partenza` | `Punto` | Latitudine e longitudine di partenza |
| `arrivo` | `Punto` | Latitudine e longitudine di arrivo |

### Output

- I due punti con quattro decimali.
- `Distanza in linea d'aria: K km` con due decimali.
- `Tempo a piedi stimato: H h MM min`.
- `Coordinate non valide.` se una coordinata è fuori intervallo o non
  numerica.

### Vincoli

- Latitudine tra −90 e 90, longitudine tra −180 e 180.
- Formula dell'emisenoverso, con le differenze in radianti:
  a = sin²(Δlat/2) + cos(lat₁) · cos(lat₂) · sin²(Δlon/2),
  distanza = 2 · R · asin(√a), con R = 6371 km.
- Minuti a piedi = distanza × 1.3 / 4.5 × 60, arrotondati all'intero.
- Si compila con `-lm`.

### Assunzioni

- La Terra è considerata una sfera.
- Un inserimento non numerico rende non valido il punto (nel campo
  latitudine si mette 100, fuori intervallo).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Punto` | `typedef struct { double latitudine; double longitudine; } Punto;` | Una posizione GPS |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `dlat`, `dlon` | `double` | Differenze in radianti |
| `a` | `double` | Termine intermedio della formula |
| `km` | `double` | Distanza |
| `minuti` | `int` | Tempo a piedi arrotondato |
| `RAGGIO_TERRA`, `PI`, `VELOCITA`, `FATTORE_STRADA` | `#define` | 6371, π, 4.5 km/h, 1.3 |

| Funzione | Compito |
|----------|---------|
| `radianti(gradi)` | Conversione da gradi a radianti |

### Algoritmo in linguaggio naturale

1. Leggere partenza e arrivo; se la lettura fallisce rendere il punto non
   valido.
2. Se una coordinata è fuori intervallo, stampare `Coordinate non valide.`
3. Altrimenti calcolare le differenze in radianti, il termine `a` e la
   distanza; calcolare i minuti a piedi e stampare punti, distanza e tempo
   in ore e minuti.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Milano Duomo → Monza

- **Cosa si verifica:** calcolo della distanza e del tempo.
- **Input:** `45.4642 9.1900`, `45.5845 9.2744`
- **Valori intermedi attesi:** 14.91 km; 14.91 × 1.3 / 4.5 × 60 ≈ 258
  minuti.
- **Output atteso:**
  ```
  Da (45.4642, 9.1900) a (45.5845, 9.2744)
  Distanza in linea d'aria: 14.91 km
  Tempo a piedi stimato:    4 h 18 min
  ```

### Test 2 – Stesso punto

- **Input:** `45.0703 7.6869`, `45.0703 7.6869`
- **Output atteso:** `Distanza in linea d'aria: 0.00 km` e
  `Tempo a piedi stimato:    0 h 00 min`.

### Test 3 – Grande distanza

- **Cosa si verifica:** le ore oltre le 24 non vengono convertite in
  giorni.
- **Input:** `41.9028 12.4964` (Roma), `45.4642 9.1900` (Milano)
- **Output atteso:** `Distanza in linea d'aria: 476.88 km` e
  `Tempo a piedi stimato:    137 h 46 min`.

### Test 4 – Coordinate non valide

- **Input:** `95 10`, `45 9` (poi `abc`, `45 9`)
- **Output atteso:** `Coordinate non valide.`
