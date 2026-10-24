# Analisi – 060-problema-calcolatrice-operazioni.c

## 1. Problema

La calcolatrice del corso di recupero legge un'operazione scritta a parole
e due interi. La parola diventa un `Operazione` (enum) cercandola in una
tabella di nomi; `calcola` sceglie il calcolo con uno `switch` e
restituisce 0 se l'operazione è impossibile.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `parola` | `char[16]` | `somma`, `differenza`, `prodotto`, `quoziente`, `resto`, `potenza`; `FINE` termina |
| `a`, `b` | `int` | Operandi |

### Output

- `operazione di a e b = risultato`, oppure
  `operazione di a e b: impossibile.`,
  `Operazione "x" sconosciuta.`, `Servono due numeri interi.`

### Vincoli

- `NON_VALIDA` sta dopo `NUM_OPERAZIONI`: non ha un nome nella tabella e
  indica una parola non trovata.
- Quoziente e resto sono interi; impossibili con b = 0 (i due `case`
  condividono il codice).
- Potenza con esponente non negativo, calcolata con moltiplicazioni
  ripetute.
- La parola si confronta con `strcmp`: va scritta in minuscolo.
- Un'operazione per riga; una riga non valida non interrompe il
  programma. A fine input termina come con `FINE`.

### Assunzioni

- I risultati stanno in un `int`.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Operazione` | `typedef enum { SOMMA, DIFFERENZA, PRODOTTO, QUOZIENTE, RESTO, POTENZA, NUM_OPERAZIONI, NON_VALIDA } Operazione;` | Operazione richiesta |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `parola` | `char[16]` | Nome letto |
| `op` | `Operazione` | Operazione trovata |
| `risultato` | `int` | Parametro di uscita di `calcola` |
| `finito` | `int` | Flag di uscita |

| Funzione | Compito |
|----------|---------|
| `da_testo(parola)` | Costante corrispondente, o `NON_VALIDA` |
| `calcola(op, a, b, &risultato)` | Calcolo con `switch`; 0 se impossibile |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché non si termina:
   1. leggere la parola; con `FINE` o a fine input terminare;
   2. leggere i due numeri; se mancano segnalarlo;
   3. convertire la parola; se non valida segnalarla;
   4. altrimenti calcolare e stampare il risultato o l'impossibilità;
   5. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Tutte le operazioni

- **Input:** `somma 7 5`, `differenza 3 10`, `prodotto -4 6`,
  `quoziente 17 5`, `resto 17 5`, `quoziente 3 0`, `potenza 2 10`,
  `potenza 2 -1`, `media 3 4`, `somma 3 x`, `Somma 1 1`, `FINE`
- **Output atteso:**
  ```
    somma di 7 e 5 = 12
    differenza di 3 e 10 = -7
    prodotto di -4 e 6 = -24
    quoziente di 17 e 5 = 3
    resto di 17 e 5 = 2
    quoziente di 3 e 0: impossibile.
    potenza di 2 e 10 = 1024
    potenza di 2 e -1: impossibile.
    Operazione "media" sconosciuta.
    Servono due numeri interi.
    Operazione "Somma" sconosciuta.
  ```
