# Analisi – 040-problema-calcolatrice-frazioni.c

## 1. Problema

La calcolatrice legge espressioni con due frazioni e un operatore (`+`,
`-`, `*`, `:`) e stampa il risultato con il segno al numeratore e ridotto
ai minimi termini. Ogni operazione riceve due `Frazione` per valore e
restituisce una `Frazione` nuova. Denominatori nulli e divisioni per zero
sono segnalati; `0/0` termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `a`, `b` | `Frazione` | Operandi nella forma `n/d`; `0/0` come primo operando termina |
| `operatore` | `char` | `+`, `-`, `*` oppure `:` |

### Output

- `a op b = risultato`, con il risultato ridotto, il segno al numeratore e
  il solo numeratore se il denominatore è 1.
- `Denominatore nullo.`, `Divisione per zero.`, `Operatore X non
  previsto.`, `Espressione non valida.`, `Espressione incompleta.`

### Vincoli

- Le funzioni ricevono le struct per valore: gli operandi del chiamante
  non vengono modificati (si stampano come inseriti).
- a/b ± c/d = (a·d ± c·b) / (b·d); a/b · c/d = (a·c) / (b·d); dividere
  per c/d significa moltiplicare per d/c.
- `normalizza`: se il denominatore è negativo si cambiano i segni di
  entrambi, poi si divide per l'MCD dei valori assoluti.
- Un'espressione non nella forma prevista viene scartata (resto della
  riga) e segnalata; a fine input il programma termina.

### Assunzioni

- I valori sono piccoli: i prodotti non superano il limite di `int`.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Frazione` | `typedef struct { int num; int den; } Frazione;` | Una frazione |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `risultato` | `Frazione` | Valore restituito dall'operazione |
| `continua` | `int` | Flag di uscita |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `crea(num, den)` | Costruisce e restituisce una `Frazione` |
| `somma`, `differenza`, `prodotto`, `quoziente` | Le quattro operazioni |
| `normalizza(f)` | Segno al numeratore e riduzione |
| `mcd(a, b)` | Massimo comune divisore |
| `stampa(f)` | Stampa `n/d` oppure `n` |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché si continua:
   1. leggere il primo operando (fine input o `0/0` → fine; testo → non
      valida);
   2. leggere operatore e secondo operando (fine input → incompleta e
      fine; testo → non valida);
   3. controllare nell'ordine: denominatori nulli, divisione per zero,
      operatore;
   4. altrimenti calcolare con la funzione dell'operatore, normalizzare e
      stampare l'espressione con il risultato.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Operazioni ed errori

- **Cosa si verifica:** le quattro operazioni, segno negativo, divisore
  negativo, risultato intero e nullo, tutti i messaggi di errore.
- **Input:** `1/2 + 1/3`, `3/4 - 5/4`, `2/3 * 9/4`, `1/2 : 3/4`,
  `6/8 : -3/4`, `1/0 + 1/2`, `1/2 : 0/5`, `1/2 ^ 1/3`, `abc`, `1/2 + x`,
  `1/3 - 1/3`, `0/0`
- **Valori intermedi attesi:** 6/8 : −3/4 = 6/8 · 4/−3 = 24/−24 →
  −24/24 → −1.
- **Output atteso:**
  ```
    1/2 + 1/3 = 5/6
    3/4 - 5/4 = -1/2
    2/3 * 9/4 = 3/2
    1/2 : 3/4 = 2/3
    6/8 : -3/4 = -1
    Denominatore nullo.
    Divisione per zero.
    Operatore ^ non previsto.
    Espressione non valida.
    Espressione non valida.
    1/3 - 1/3 = 0
  ```

### Test 2 – Espressione troncata

- **Input:** `1/2 +`, poi fine input.
- **Output atteso:** `Espressione non valida.` (manca la seconda frazione).
