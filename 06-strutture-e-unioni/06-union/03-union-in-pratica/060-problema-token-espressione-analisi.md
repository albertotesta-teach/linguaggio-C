# Analisi – 060-problema-token-espressione.c

## 1. Problema

La calcolatrice divide un'espressione in token (numeri, operatori,
parentesi) e la calcola rispettando precedenza e parentesi con tre
funzioni ricorsive: `espressione`, `termine` e `fattore`. Ogni token è una
union etichettata; le funzioni avanzano un indice comune e segnalano gli
errori in `*ok`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[80]` | Espressione con numeri (anche decimali), `+ - * /`, parentesi e spazi; `FINE` termina |

### Output

- `= R  (N token)` con il risultato (`%g`) e il numero di token.
- `Espressione non valida.`

### Vincoli

- Grammatica: espressione = termine { (+|−) termine }; termine = fattore
  { (*|/) fattore }; fattore = numero | ( espressione ).
- Moltiplicazione e divisione hanno la precedenza; a parità si calcola da
  sinistra.
- Non valida: carattere non ammesso, punto senza cifre, più di 40 token,
  divisione per zero, parentesi non chiusa, token avanzati (es. `2 3`).
- Non ci sono numeri negativi: il segno meno è sempre un operatore.
- Una riga più lunga del buffer viene troncata e il resto scartato. A fine
  input il programma termina come con `FINE`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `TipoToken` | `typedef enum { NUMERO, OPERATORE, PARENTESI } TipoToken;` | Etichetta |
| `Token` | struct con `tipo` e union anonima `{ double numero; char simbolo; }` | Un token |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `token`, `n` | `Token[40]`, `int` | Token della riga (−1 = errore) |
| `pos` | `int` | Indice del prossimo token, comune alle funzioni |
| `ok` | `int` | Validità, azzerata al primo errore |
| `resto` | `int` | Caratteri scartati di una riga lunga |

| Funzione | Compito |
|----------|---------|
| `dividi_in_token(testo, token, massimo)` | Analisi lessicale |
| `espressione`, `termine`, `fattore` | Calcolo ricorsivo |

### Algoritmo in linguaggio naturale

1. Finché non si termina: leggere una riga; con `FINE` terminare;
   dividerla in token; calcolare `espressione` partendo da `pos = 0`; se
   `ok` e tutti i token sono stati usati stampare il risultato, altrimenti
   l'errore.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Espressioni

- **Input:** `2+3*4`, `(2+3)*4`, `10/4-1`, `7/(3-3)`, `2*(3+`, `2 3`,
  `2^3`, `.`, `((1.5))`, `1+1+...+1` (30 uni, 59 token), `FINE`
- **Output atteso:**
  ```
    = 14  (5 token)
    = 20  (7 token)
    = 1.5  (5 token)
    Espressione non valida.
    Espressione non valida.
    Espressione non valida.
    Espressione non valida.
    Espressione non valida.
    = 1.5  (5 token)
    Espressione non valida.
  ```
