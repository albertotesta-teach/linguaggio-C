# Analisi – 060-problema-pianta-del-laboratorio.c

## 1. Problema

Sulla pianta del laboratorio di fisica ogni banco è un rettangolo dato da
due struct `Punto`, gli angoli opposti, dentro la struct `Banco`. Il
programma calcola area, centro e distanza dalla porta di ogni banco e
sceglie il banco più vicino alla porta per il kit di primo soccorso; poi
dice su quale banco cade ogni postazione letta, oppure se è nel corridoio.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `postazione` | `Punto` | Coordinate x y in cm; `-1 -1` termina |
| banchi | nel sorgente | B1 (100,100)-(340,180), B2 (100,300)-(340,380), B3 (500,100)-(740,180), B4 (500,300)-(740,380) |
| `porta` | `Punto` | (800, 0) |

### Output

- Una tabella con banco, area, centro e distanza del centro dalla porta.
- `Kit di primo soccorso sul banco X.`
- Per ogni postazione: `(x, y): banco X` oppure `(x, y): corridoio`, o
  `Postazione non valida.`

### Vincoli

- Ai campi annidati si accede con due punti:
  `banchi[i].alto_destra.x`.
- Area = (x₂ − x₁) × (y₂ − y₁); centro con la divisione intera.
- Distanza euclidea tra centro e porta; a parità vale il primo banco.
- Un punto sul bordo appartiene al banco.
- Una postazione non numerica viene scartata e segnalata; a fine input il
  programma termina.

### Assunzioni

- I banchi non si sovrappongono.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Punto` | `typedef struct { int x; int y; } Punto;` | Un punto sulla pianta |
| `Banco` | `typedef struct { char nome[8]; Punto basso_sinistra; Punto alto_destra; } Banco;` | Un banco come rettangolo |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `banchi` | `Banco[4]` | Array di struct annidate |
| `centro` | `Punto` | Centro del banco |
| `distanza`, `minima` | `double` | Distanze dalla porta |
| `vicino` | `int` | Banco più vicino alla porta |
| `trovato` | `int` | Banco che contiene la postazione (−1 = corridoio) |
| `letti` | `int` | Valore restituito da `scanf` |

### Algoritmo in linguaggio naturale

1. Per ogni banco calcolare area, centro e distanza, stamparli e
   aggiornare il più vicino; stampare il banco del kit.
2. Finché la postazione non è `-1 -1`:
   1. leggere la postazione (fine input → fine; testo → non valida);
   2. cercare il primo banco che la contiene e stampare il banco o
      `corridoio`.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Pianta e postazioni

- **Cosa si verifica:** calcoli della tabella, punto interno, punto nel
  corridoio, punto sul bordo, postazione non valida.
- **Input:** `200 150`, `600 350`, `400 250`, `340 180`, `abc`, `0 0`,
  `-1 -1`
- **Valori intermedi attesi:** B3 ha centro (620, 140):
  √(180² + 140²) ≈ 228.0 cm.
- **Output atteso:**
  ```
  Banco  Area (cm2)  Centro       Distanza dalla porta
  B1          19200  (220, 140)     596.7 cm
  B2          19200  (220, 340)     672.3 cm
  B3          19200  (620, 140)     228.0 cm
  B4          19200  (620, 340)     384.7 cm
  Kit di primo soccorso sul banco B3.

    (200, 150): banco B1
    (600, 350): banco B4
    (400, 250): corridoio
    (340, 180): banco B1
    Postazione non valida.
    (0, 0): corridoio
  ```
