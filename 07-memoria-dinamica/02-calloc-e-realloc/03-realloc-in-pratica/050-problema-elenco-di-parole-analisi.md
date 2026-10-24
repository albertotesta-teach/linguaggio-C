# Analisi – 050-problema-elenco-di-parole.c

## 1. Problema

Per aiutare a variare il lessico di un tema il programma conta le parole
distinte. Due array crescono di un elemento a ogni parola nuova, partendo
da `NULL`: uno di puntatori alle parole (ognuna in un blocco della sua
lunghezza) e uno di contatori. Alla fine stampa le parole ripetute almeno
3 volte e libera prima le parole e poi gli array.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| testo | righe | Il tema; `FINE` da solo su una riga termina |

### Output

- `Parole: T, distinte: D`.
- `Ripetute almeno 3 volte:` con le parole e il numero di ripetizioni,
  nell'ordine in cui sono comparse.
- `Memoria insufficiente.` se un'allocazione fallisce.

### Vincoli

- Una parola è una sequenza di lettere, convertita in minuscolo (al
  massimo 30 lettere conservate).
- `aggiungi` riceve `char ***` e `int **` per allungare i due array con
  `realloc` (partendo da `NULL`, che equivale a `malloc`); ogni
  `realloc` va in un temporaneo e, se fallisce, gli array restano validi
  con n elementi.
- Ogni parola: `malloc((strlen + 1) * sizeof *copia)`.
- Liberazione: prima le parole, poi i due array.
- A fine input il conteggio termina come con `FINE`.

### Assunzioni

- Righe al massimo di 199 caratteri; testo senza lettere accentate.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `parole` | `char **` | Array dinamico di puntatori alle parole |
| `conta` | `int *` | Array dinamico dei contatori |
| `parola` | `char[31]` | Parola corrente |
| `n`, `totale` | `int` | Parole distinte e totali |

| Funzione | Compito |
|----------|---------|
| `cerca(parole, n, parola)` | Posizione della parola, −1 se nuova |
| `aggiungi(&parole, &conta, n, parola)` | Allunga gli array e copia la parola; 0 se manca memoria |

### Algoritmo in linguaggio naturale

1. Per ogni riga fino a `FINE`: estrarre le parole in minuscolo; se già
   presente aumentarne il contatore, altrimenti aggiungerla.
2. Stampare totali e parole ripetute almeno 3 volte.
3. Liberare le parole e gli array.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Un tema ripetitivo

- **Input:**
  `La gita a Torino e stata bella. La guida ci ha mostrato il Museo Egizio,`,
  `poi la Mole: la vista dalla Mole era bella e la giornata era bella!`,
  `FINE`
- **Output atteso:**
  ```
  Testo del tema (FINE per terminare):

  Parole: 29, distinte: 20
  Ripetute almeno 3 volte:
    la           5
    bella        3
  ```
  (`La` e `la` sono la stessa parola).
