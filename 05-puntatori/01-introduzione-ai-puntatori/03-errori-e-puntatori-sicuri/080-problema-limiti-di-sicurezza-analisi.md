# Analisi – 080-problema-limiti-di-sicurezza.c

## 1. Problema

Una pressa idraulica del laboratorio di meccanica è sorvegliata da un
programma che legge la pressione. Da 180 bar si segnala un allarme, da 210
bar si esegue l'arresto di emergenza, dopo il quale la pressa resta ferma.
I limiti di sicurezza non devono poter essere modificati e il sensore deve
scrivere sempre nella stessa variabile. Alla fine si riportano gli allarmi
e la pressione massima.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `ALLARME`, `ARRESTO` | `const int` | 180, 210 bar |
| `letture` | `int[10]` | 120, 150, 175, 182, 168, 190, 205, 214, 160, 140 (letture simulate) |

### Output

- Le soglie.
- Per ogni lettura: la pressione e `normale`, `allarme`,
  `ARRESTO DI EMERGENZA` oppure `(pressa ferma)`.
- Il riepilogo: numero di allarmi, pressione massima, stato della pressa.

### Vincoli

- `sensore` è un `int *const`: punta sempre a `pressione` e non può essere
  spostato (`sensore = &massima` non compila), ma può scrivere il valore.
- `soglia_allarme` e `soglia_arresto` sono `const int *const`: né il
  puntatore né il valore puntato possono cambiare.
- Le soglie si controllano dalla più alta: da 210 bar arresto, da 180 bar
  allarme.
- Dopo l'arresto le letture non generano nuovi allarmi; la pressione
  massima si aggiorna anche a pressa ferma.

### Assunzioni

- Le letture sono positive (la massima parte da 0).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `pressione` | `int` | Ultima lettura |
| `sensore` | `int *const` | Punta sempre a `pressione` |
| `soglia_allarme`, `soglia_arresto` | `const int *const` | Puntatori e valori costanti |
| `allarmi`, `massima` | `int` | Riepilogo |
| `ferma` | `int` | 1 dopo l'arresto di emergenza |
| `k` | `int` | Indice delle letture |

### Algoritmo in linguaggio naturale

1. Stampare le soglie.
2. Per ogni lettura:
   1. scriverla in `pressione` tramite `*sensore`; aggiornare la massima;
   2. se la pressa è ferma stampare `(pressa ferma)`;
   3. altrimenti, se la pressione è ≥ `*soglia_arresto`, porre `ferma = 1`
      e stampare l'arresto;
   4. altrimenti, se è ≥ `*soglia_allarme`, contare e stampare l'allarme;
   5. altrimenti stampare `normale`.
3. Stampare il riepilogo.

## 3. Casi di test

### Test 1 – Letture del sorgente

- **Cosa si verifica:** letture normali, allarmi, arresto e pressa ferma.
- **Input:** nessuno.
- **Output atteso:**
  ```
  Soglie: allarme 180 bar, arresto 210 bar
    lettura  1: 120 bar  normale
    lettura  2: 150 bar  normale
    lettura  3: 175 bar  normale
    lettura  4: 182 bar  allarme
    lettura  5: 168 bar  normale
    lettura  6: 190 bar  allarme
    lettura  7: 205 bar  allarme
    lettura  8: 214 bar  ARRESTO DI EMERGENZA
    lettura  9: 160 bar  (pressa ferma)
    lettura 10: 140 bar  (pressa ferma)

  Allarmi: 3, pressione massima: 214 bar, pressa in arresto
  ```

### Test 2 – Pressa sempre in funzione

- **Procedura:** nel sorgente sostituire la lettura 214 con 200,
  ricompilare ed eseguire.
- **Output atteso:** la lettura 8 dà `allarme`, le letture 9 e 10
  `normale`; riepilogo
  `Allarmi: 4, pressione massima: 205 bar, pressa in funzione`.

### Test 3 – Puntatori costanti

- **Cosa si verifica:** il compilatore impedisce le modifiche vietate.
- **Procedura:** togliere il commento a `sensore = &massima;` (oppure a
  `*soglia_arresto = 250;`) e ricompilare.
- **Output atteso:** errore di compilazione; ripristinare il commento.
