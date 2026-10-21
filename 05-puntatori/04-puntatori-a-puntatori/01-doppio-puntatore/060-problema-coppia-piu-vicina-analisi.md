# Analisi – 060-problema-coppia-piu-vicina.c

## 1. Problema

Alla corsa campestre i tempi di arrivo sono registrati nell'ordine dei
pettorali. Il giudice vuole i due atleti arrivati più vicini tra loro e il
loro distacco; con un distacco di 2 decimi o meno serve il fotofinish.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `tempi` | `int[8]` | 7342, 7120, 7865, 7343, 7240, 7461, 7228, 7980 decimi di secondo (per pettorale) |

### Output

- La tabella pettorali e tempi in secondi.
- I pettorali e i tempi dei due atleti più vicini e il distacco.
- Con distacco ≤ 2 decimi: `Distacco di 2 decimi o meno: serve il fotofinish.`

### Vincoli

- `coppia_piu_vicina` restituisce il distacco minimo con `return` e scrive
  due puntatori del chiamante: riceve i loro indirizzi (`const int **`).
- I puntatori restituiti puntano dentro l'array del `main`: il pettorale è
  `a − tempi + 1`.
- Si confrontano tutte le coppie (`q` parte da `p + 1`, così ogni coppia
  si esamina una volta).
- A parità di distacco vale la prima coppia trovata (confronto con `<`).

### Assunzioni

- Almeno due atleti; pettorali numerati da 1.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `a`, `b` | `const int *` | I due tempi più vicini, scritti dalla funzione |
| `d` | `int` | Distacco minimo |
| `p`, `q`, `minima` | `const int *`, `const int *`, `int` | Nella funzione |

| Funzione | Compito |
|----------|---------|
| `coppia_piu_vicina(tempi, n, &a, &b)` | Restituisce il distacco minimo e scrive i due puntatori |
| `distanza(x, y)` | Valore assoluto della differenza |

### Algoritmo in linguaggio naturale

1. Stampare pettorali e tempi.
2. In `coppia_piu_vicina`: partire dalla coppia dei primi due tempi; per
   ogni coppia `(p, q)` con `q` dopo `p`, se la distanza è minore della
   minima aggiornarla e scrivere `*primo = p`, `*secondo = q`.
3. Stampare pettorali, tempi e distacco; se ≤ 2 decimi segnalare il
   fotofinish.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Input:** nessuno.
- **Valori intermedi attesi:** |7342 − 7343| = 1 decimo, la distanza minima.
- **Output atteso:**
  ```
  Pettorale:      1      2      3      4      5      6      7      8
  Tempo (s):  734.2  712.0  786.5  734.3  724.0  746.1  722.8  798.0

  Arrivo piu' combattuto: pettorali 1 e 4 (734.2 s e 734.3 s), distacco 0.1 s
  Distacco di 2 decimi o meno: serve il fotofinish.
  ```

### Test 2 – Nessun fotofinish

- **Procedura:** nel sorgente impostare il tempo del pettorale 4 a 7400,
  ricompilare ed eseguire.
- **Output atteso:** la coppia più vicina diventa 5 e 7 (724.0 s e 722.8 s,
  distacco 1.2 s), senza la riga del fotofinish.
