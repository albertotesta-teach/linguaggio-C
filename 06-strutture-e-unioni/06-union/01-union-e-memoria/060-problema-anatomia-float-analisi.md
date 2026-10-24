# Analisi – 060-problema-anatomia-float.c

## 1. Problema

Nel laboratorio di informatica si osserva com'è fatto un `float`: 1 bit di
segno, 8 di esponente, 23 di mantissa. Una `union` permette di leggere i
bit del float come intero senza segno; spostamenti e maschere separano le
tre parti.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `parola` | `char[32]` | Un numero reale; `FINE` termina |

### Output

- Il valore memorizzato (`%.9g`, che mostra l'approssimazione).
- I 32 bit con uno spazio dopo il segno e dopo l'esponente.
- `segno S (positivo/negativo), esponente E - 127 = e, mantissa 0xMMMMMM`;
  per l'esponente 0 con mantissa 0 `(zero)`, per l'esponente 255
  `(infinito o NaN)`.
- `Non e' un numero.`

### Vincoli

- Segno = bit 31; esponente = bit 30-23 (`(bit >> 23) & 0xFF`);
  mantissa = bit 22-0 (`bit & 0x7FFFFF`).
- L'esponente è memorizzato con un eccesso di 127.
- Si scrive il campo `reale` della union e si legge il campo `bit`.

### Assunzioni

- `float` in formato IEEE 754 a 32 bit.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Float` | `typedef union { float reale; uint32_t bit; } Float;` | Lo stesso float visto come numero e come bit |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `f` | `Float` | Numero letto |
| `segno`, `esponente`, `mantissa` | `uint32_t` | Le tre parti |

| Funzione | Compito |
|----------|---------|
| `stampa_bit(bit)` | Stampa i 32 bit raggruppati |

### Algoritmo in linguaggio naturale

1. Finché non si termina: leggere una parola (fine input o `FINE` →
   fine); convertirla con `sscanf`; se non è un numero segnalarlo;
   altrimenti estrarre le tre parti e stamparle.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Numeri caratteristici

- **Input:** `1`, `-2.5`, `0.1`, `0`, `abc`, `1e40`, `FINE`
- **Valori intermedi attesi:** −2.5 = −1.25 × 2¹; 0.1 non è
  rappresentabile esattamente (0.100000001).
- **Output atteso:**
  ```
    1
    0 01111111 00000000000000000000000
    segno 0 (positivo), esponente 127 - 127 = 0, mantissa 0x000000
    -2.5
    1 10000000 01000000000000000000000
    segno 1 (negativo), esponente 128 - 127 = 1, mantissa 0x200000
    0.100000001
    0 01111011 10011001100110011001101
    segno 0 (positivo), esponente 123 - 127 = -4, mantissa 0x4CCCCD
    0
    0 00000000 00000000000000000000000
    segno 0 (positivo), esponente 0 (zero), mantissa 0x000000
    Non e' un numero.
    inf
    0 11111111 00000000000000000000000
    segno 0 (positivo), esponente 255 (infinito o NaN), mantissa 0x000000
  ```
  (1e40 supera il massimo di un `float` e diventa infinito).

### Test 2 – Zero negativo

- **Input:** `-0`, `FINE`
- **Output atteso:** `segno 1 (negativo), esponente 0 (zero), mantissa
  0x000000`.
