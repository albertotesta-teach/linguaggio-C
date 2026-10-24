# Analisi – 070-problema-somma-frazioni.c

## 1. Problema

Nel laboratorio di cucina le dosi sono frazioni. Il programma legge coppie
di frazioni nella forma `a/b c/d`, le somma, riduce il risultato ai minimi
termini e, se supera l'unità, lo stampa anche come numero misto (o come
intero). `0/0` termina. Ogni frazione è una struct `Frazione`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `prima`, `seconda` | `Frazione` | Due frazioni nella forma `a/b`; `0/0` come prima termina |

### Output

- `a/b + c/d = n/d` ridotta ai minimi termini, seguita da `= intero` se il
  risultato è intero oppure da `= k e r/d` se supera l'unità.
- `Frazioni non valide.` per denominatori non positivi, numeratori
  negativi o testo non nella forma `a/b`.
- `Seconda frazione mancante.` se l'input termina dopo la prima.

### Vincoli

- a/b + c/d = (a·d + c·b) / (b·d), poi divisione per l'MCD di numeratore
  e denominatore (algoritmo di Euclide).
- Denominatori positivi, numeratori non negativi.
- Un inserimento non nella forma `a/b` viene scartato (resto della riga) e
  segnalato; a fine input il programma termina come con `0/0`.

### Assunzioni

- I valori sono piccoli: i prodotti non superano il limite di `int`.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Frazione` | `typedef struct { int num; int den; } Frazione;` | Una frazione |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `somma` | `Frazione` | Risultato |
| `divisore` | `int` | MCD per la riduzione |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `mcd(a, b)` | Massimo comune divisore (con `b > 0`) |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché la prima frazione non è `0/0`:
   1. leggere la prima frazione (fine input → `0/0`; testo → non valida);
   2. se non è `0/0` leggere la seconda (fine input → mancante e fine;
      testo → non valide);
   3. se un denominatore non è positivo o un numeratore è negativo,
      segnalarlo;
   4. altrimenti calcolare la somma, ridurla con l'MCD e stamparla, con
      l'intero o il numero misto quando serve.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Somme e frazioni non valide

- **Cosa si verifica:** riduzione, numero misto, risultato intero e zero,
  rifiuto dei dati non validi.
- **Input:** `1/2 1/3`, `3/4 1/2`, `2/3 4/3`, `0/3 0/5`, `1/0 1/2`,
  `-1/2 1/2`, `abc`, `1/2 x`, `5/8 3/8`, `0/0`
- **Valori intermedi attesi:** 3/4 + 1/2 = 10/8, MCD 2 → 5/4; 0/3 + 0/5 =
  0/15, MCD 15 → 0/1.
- **Output atteso:**
  ```
    1/2 + 1/3 = 5/6
    3/4 + 1/2 = 5/4  = 1 e 1/4
    2/3 + 4/3 = 2/1  = 2
    0/3 + 0/5 = 0/1  = 0
    Frazioni non valide.
    Frazioni non valide.
    Frazioni non valide.
    Frazioni non valide.
    5/8 + 3/8 = 1/1  = 1
  ```

### Test 2 – Seconda frazione mancante

- **Input:** `1/2`, poi fine input.
- **Output atteso:** `Seconda frazione mancante.`
