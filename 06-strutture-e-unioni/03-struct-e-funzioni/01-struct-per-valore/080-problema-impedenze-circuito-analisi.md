# Analisi – 080-problema-impedenze-circuito.c

## 1. Problema

Nel laboratorio di elettrotecnica si calcolano le impedenze di resistore,
induttore e condensatore, l'impedenza del circuito serie RLC e del
parallelo tra R e C, e la corrente nel circuito serie con 230 V. Le
impedenze sono numeri complessi (struct `Complesso`) e tutte le
operazioni li ricevono e li restituiscono per valore.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `r` | `double` | Resistenza in ohm |
| `l` | `double` | Induttanza in henry |
| `c` | `double` | Capacità in farad |
| `f` | `double` | Frequenza in hertz |

### Output

- Per resistore, induttore, condensatore, serie RLC e R parallelo C: la
  forma algebrica `Z = a ± jb`, il modulo in ohm e la fase in gradi.
- `corrente serie: I A` con tre decimali.
- `Valori non validi.` se un valore manca o non è positivo.

### Vincoli

- Z_R = R; Z_L = j·2πfL; Z_C = −j / (2πfC).
- Serie: somma delle impedenze; parallelo: Z₁·Z₂ / (Z₁ + Z₂).
- Divisione tra complessi: moltiplicazione per il coniugato del
  denominatore e divisione per il suo modulo al quadrato.
- Modulo √(a² + b²); fase `atan2(b, a)` in gradi.
- Corrente = 230 / |Z serie|. Si compila con `-lm`.

### Assunzioni

- Componenti ideali.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Complesso` | `typedef struct { double re; double im; } Complesso;` | Un numero complesso |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `zr`, `zl`, `zc` | `Complesso` | Impedenze dei componenti |
| `serie` | `Complesso` | Impedenza del circuito serie |
| `PI`, `TENSIONE` | `#define` | π e 230 V |

| Funzione | Compito |
|----------|---------|
| `crea(re, im)` | Costruisce un `Complesso` |
| `somma`, `prodotto`, `quoziente` | Operazioni tra complessi |
| `parallelo(a, b)` | Impedenza di due elementi in parallelo |
| `modulo(z)`, `fase(z)` | Modulo e fase in gradi |
| `stampa(nome, z)` | Riga con forma algebrica, modulo e fase |

### Algoritmo in linguaggio naturale

1. Leggere R, L, C e f; se non validi stampare `Valori non validi.`
2. Calcolare e stampare le tre impedenze.
3. Calcolare e stampare la serie e la corrente.
4. Calcolare e stampare il parallelo tra R e C.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Circuito a 50 Hz

- **Input:** `100 0.5 0.0001 50`
- **Valori intermedi attesi:** X_L = 2π·50·0.5 = 157.08; X_C =
  1 / (2π·50·0.0001) = 31.83; serie 100 + j125.25, |Z| = 160.27;
  230 / 160.27 = 1.435 A.
- **Output atteso:**
  ```
    Resistore      Z =    100.00 + j     0.00   |Z| =    100.00 ohm   fase    0.00 gradi
    Induttore      Z =      0.00 + j   157.08   |Z| =    157.08 ohm   fase   90.00 gradi
    Condensatore   Z =      0.00 - j    31.83   |Z| =     31.83 ohm   fase  -90.00 gradi
    Serie RLC      Z =    100.00 + j   125.25   |Z| =    160.27 ohm   fase   51.40 gradi
    corrente serie: 1.435 A
    R parallelo C  Z =      9.20 - j    28.90   |Z| =     30.33 ohm   fase  -72.34 gradi
  ```

### Test 2 – Risonanza

- **Cosa si verifica:** alla frequenza di risonanza 1 / (2π√(LC)) le
  reattanze si annullano e la serie vale circa R.
- **Input:** `10 0.1 0.0001 50.33`
- **Output atteso:** induttore e condensatore con |Z| = 31.62; `Serie RLC
  Z = 10.00 + j 0.00` (fase circa 0); `corrente serie: 23.000 A`.

### Test 3 – Valori non validi

- **Input:** `100 0.5 0 50`
- **Output atteso:** `Valori non validi.`
