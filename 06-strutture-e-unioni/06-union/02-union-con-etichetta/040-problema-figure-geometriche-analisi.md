# Analisi – 040-problema-figure-geometriche.c

## 1. Problema

Per la verifica di geometria il programma legge cerchi, rettangoli e
triangoli, li controlla e ne calcola area e perimetro; alla fine indica la
figura con l'area maggiore. Una `Figura` contiene un'etichetta (`enum`) e
una `union` delle tre alternative; `area`, `perimetro` e `valida` sono
`switch` sull'etichetta.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| figura | una riga | `C r`, `R b h`, `T a b c`; `FINE` termina |

### Output

- Per ogni figura valida: `nome: area A, perimetro P` (due decimali).
- `Misure non valide per un <figura>.`, `Figura non riconosciuta.`,
  `Misure mancanti.`
- Alla fine, se ci sono figure: `Area maggiore: figura N (nome), A`.

### Vincoli

- L'etichetta dice quale membro della union è valido: ogni funzione legge
  solo quello.
- Cerchio e rettangolo con misure positive; triangolo con la
  disuguaglianza triangolare stretta (ogni lato minore della somma degli
  altri due).
- Area del triangolo con la formula di Erone; π = 3.14159265358979.
- Al massimo 8 figure; le figure non valide non sono memorizzate.
- A parità di area vale la prima figura.
- Una figura per riga: il resto viene scartato. A fine input il programma
  termina come con `FINE`.

### Assunzioni

- Lettera e misure stanno sulla stessa riga (`scanf` cercherebbe le misure
  mancanti nella riga successiva).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `TipoFigura` | `typedef enum { CERCHIO, RETTANGOLO, TRIANGOLO } TipoFigura;` | Etichetta |
| `Cerchio`, `Rettangolo`, `Triangolo` | struct | Misure di ogni figura |
| `Figura` | `typedef struct { TipoFigura tipo; union { Cerchio cerchio; Rettangolo rettangolo; Triangolo triangolo; } dati; } Figura;` | Union etichettata |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `figure`, `n` | `Figura[8]`, `int` | Figure valide |
| `esito` | `int` | 1 letta, 0 fine, −1 lettera sconosciuta, −2 misure mancanti |
| `massima` | `int` | Indice dell'area maggiore |

| Funzione | Compito |
|----------|---------|
| `leggi_figura(f)` | Legge lettera e misure |
| `valida(f)`, `area(f)`, `perimetro(f)`, `nome(f)` | `switch` sull'etichetta |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché non si termina e c'è posto:
   1. leggere la figura e scartare il resto della riga;
   2. segnalare lettera sconosciuta, misure mancanti o non valide;
   3. altrimenti stampare area e perimetro e memorizzarla.
2. Se ci sono figure, trovare e stampare quella con l'area maggiore.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Figure miste

- **Input:** `C 2`, `R 3 4`, `T 3 4 5`, `T 1 2 5`, `C -1`, `Q 3`, `C abc`,
  `R 10 10`, `FINE`
- **Valori intermedi attesi:** cerchio π·4 = 12.57; triangolo 3-4-5:
  p = 6, √(6·3·2·1) = 6.
- **Output atteso:**
  ```
    cerchio: area 12.57, perimetro 12.57
    rettangolo: area 12.00, perimetro 14.00
    triangolo: area 6.00, perimetro 12.00
    Misure non valide per un triangolo.
    Misure non valide per un cerchio.
    Figura non riconosciuta.
    Misure mancanti.
    rettangolo: area 100.00, perimetro 40.00
  Area maggiore: figura 4 (rettangolo), 100.00
  ```

### Test 2 – Nessuna figura

- **Input:** `FINE`
- **Output atteso:** nessuna riga oltre la richiesta.
