# Analisi – 040-problema-istogramma-dei-voti.c

## 1. Problema

Ogni docente usa la sua scala di voti, con i mezzi voti. Il programma
legge il voto minimo e il massimo, alloca con `calloc` un contatore per
ogni voto possibile ((massimo − minimo) × 2 + 1 contatori, già a zero),
conta i voti letti fino a `FINE` e stampa l'istogramma dal voto più alto,
il voto più frequente e la percentuale di sufficienze.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `minimo`, `massimo` | `int` | Scala dei voti, 1 ≤ minimo < massimo ≤ 10 |
| voti | parole | Voti nella scala, multipli di 0.5; `FINE` termina |

### Output

- `N contatori azzerati da calloc`.
- `X scartato` per ogni voto non valido.
- L'istogramma con un asterisco per voto, dal più alto al più basso.
- `Voti: T, piu' frequente: V (K volte), sufficienze: P%` (`volta` al
  singolare), se ci sono voti.
- `Scala non valida.`, `Memoria insufficiente.`

### Vincoli

- `conta = calloc(categorie, sizeof *conta)`: i contatori partono da 0
  senza un ciclo di azzeramento; `free` alla fine.
- Indice del voto: (voto − minimo) × 2.
- Voto valido: un numero e nient'altro (`%lf%c` legge un solo campo),
  nella scala, multiplo di 0.5.
- A parità di frequenza vale il voto più alto.
- Sufficiente da 6 in su. A fine input il conteggio termina come con
  `FINE`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `conta` | `int *` | Contatori allocati con `calloc` |
| `categorie` | `int` | Numero di voti possibili |
| `totale`, `sufficienti` | `int` | Contatori |
| `moda` | `int` | Indice del voto più frequente |
| `parola`, `dopo` | `char[16]`, `char` | Lettura e controllo del voto |

| Funzione | Compito |
|----------|---------|
| `indice(voto, minimo)` | Posizione del contatore |

### Algoritmo in linguaggio naturale

1. Leggere la scala e controllarla; allocare i contatori con `calloc`.
2. Leggere le parole fino a `FINE`: se è un voto valido aumentare il suo
   contatore e i totali, altrimenti scartarla.
3. Stampare l'istogramma dal voto più alto aggiornando la moda; stampare il
   riepilogo; liberare i contatori.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Scala da 4 a 8

- **Input:** `4 8`, `6 6.5 7 5 4 8 6 7.5 3 9 6.3 sei 7`, `FINE`
- **Valori intermedi attesi:** 9 contatori; 9 voti validi, 7 sufficienti
  (78%); 6 e 7 compaiono due volte: vale il 7.
- **Output atteso:**
  ```
  9 contatori azzerati da calloc
  Voti (FINE per terminare):
    3 scartato
    9 scartato
    6.3 scartato
    sei scartato

   8.0 | *
   7.5 | *
   7.0 | * *
   6.5 | *
   6.0 | * *
   5.5 |
   5.0 | *
   4.5 |
   4.0 | *
  Voti: 9, piu' frequente: 7.0 (2 volte), sufficienze: 78%
  ```

### Test 2 – Singolare

- **Input:** `4 8`, `4 8`, `FINE`
- **Output atteso:** `Voti: 2, piu' frequente: 8.0 (1 volta), sufficienze: 50%`.

### Test 3 – Nessun voto e scala non valida

- **Input:** `1 10`, `FINE`; poi `8 4`
- **Output atteso:** l'istogramma vuoto senza riepilogo; poi
  `Scala non valida.`
