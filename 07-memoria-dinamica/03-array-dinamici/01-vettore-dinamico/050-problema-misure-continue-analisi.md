# Analisi – 050-problema-misure-continue.c

## 1. Problema

Una centralina misura il rumore della mensa ogni minuto finché il
responsabile scrive `STOP`. Le letture vanno in un vettore dinamico di
`double`. Alla fine il programma stampa il massimo con il suo minuto, la
media mobile su 5 minuti (dal quinto minuto in poi) e quanti minuti hanno
media mobile sopra 80 dB.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| letture | parole | Valori in dB, non negativi; `STOP` termina |

### Output

- `X scartata` per ogni lettura non valida.
- `Letture: N`, `Massimo: V dB al minuto M` (se ci sono letture).
- `Media mobile su 5 minuti:` con una riga per minuto dal quinto, con
  `troppo rumore` oltre 80 dB; oppure `servono almeno 5 letture`.
- `Minuti sopra 80 dB (media mobile): K`.

### Vincoli

- Vettore `{double *dati; int n; int capacita;}` con capacità iniziale 8
  e raddoppio; il `main` usa solo le funzioni del vettore.
- Lettura valida: un numero e nient'altro (`%lf%c`), non negativo.
- Media mobile al minuto m: media delle letture da m − 4 a m.
- Sopra soglia: strettamente maggiore di 80.
- A parità vale il primo minuto con il massimo. A fine input il programma
  termina come con `STOP`.

### Assunzioni

- Una lettura per minuto, senza buchi.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Serie` | `typedef struct { double *dati; int n; int capacita; } Serie;` | Vettore dinamico di letture |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `rumore` | `Serie *` | Le letture |
| `massimo` | `int` | Indice della lettura massima |
| `media`, `sopra` | `double`, `int` | Media mobile e minuti sopra soglia |

| Funzione | Compito |
|----------|---------|
| `crea_serie`, `distruggi_serie` | Allocazione e liberazione |
| `aggiungi`, `lunghezza`, `elemento` | Uso del vettore |
| `media_mobile(s, fine)` | Media delle 5 letture che finiscono in `fine` |

### Algoritmo in linguaggio naturale

1. Leggere le letture fino a `STOP` aggiungendole al vettore.
2. Trovare e stampare il massimo.
3. Per ogni minuto dal quinto calcolare e stampare la media mobile,
   contando quelle sopra soglia.
4. Distruggere il vettore.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Pranzo rumoroso

- **Input:** `72 75 78 85 90`, `88 rumore 79 -5 70 65`, `STOP`
- **Valori intermedi attesi:** minuto 6: (75 + 78 + 85 + 90 + 88) / 5 =
  83.2.
- **Output atteso:**
  ```
  Letture in dB (STOP per terminare):
    rumore scartata
    -5 scartata

  Letture: 9
  Massimo: 90.0 dB al minuto 5
  Media mobile su 5 minuti:
    minuto  5:  80.0
    minuto  6:  83.2  troppo rumore
    minuto  7:  84.0  troppo rumore
    minuto  8:  82.4  troppo rumore
    minuto  9:  78.4
  Minuti sopra 80 dB (media mobile): 3
  ```
  (80.0 esatto non è sopra la soglia).

### Test 2 – Poche letture

- **Input:** `70 72`, `STOP`
- **Output atteso:** `Massimo: 72.0 dB al minuto 2`,
  `servono almeno 5 letture`, `Minuti sopra 80 dB (media mobile): 0`.
