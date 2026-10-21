# Analisi – 080-problema-gruppi-di-lavoro.c

## 1. Problema

Per il progetto di tecnologia la classe è divisa in quattro gruppi con un
numero diverso di studenti. Il programma stampa voti e media di ogni
gruppo, il gruppo con la media più alta e il voto più alto della classe con
il gruppo di appartenenza.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `rossi` | `int[3]` | 7, 8, 6 |
| `blu` | `int[5]` | 9, 7, 8, 8, 6 |
| `verdi` | `int[4]` | 6, 6, 7, 5 |
| `gialli` | `int[2]` | 10, 8 |

### Output

- Per ogni gruppo: nome, numero di studenti, voti e media (colonna della
  media allineata).
- Il gruppo con la media più alta.
- Il voto più alto della classe e il suo gruppo.

### Vincoli

- `gruppi` è un array di puntatori ai quattro array di lunghezza diversa;
  `studenti` dice quanti elementi ha ciascuno.
- `gruppi[g][i]` scorre righe di lunghezza diversa; `gruppi[g]` si passa a
  `media` come un normale array.
- Il voto più alto si ricorda con un puntatore (`voto_max`) e il gruppo con
  un indice.
- A parità vale il primo gruppo trovato (confronto con `>`).

### Assunzioni

- Ogni gruppo ha almeno uno studente e al massimo 5 (per l'allineamento).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `gruppi` | `int *[4]` | Puntatori agli array dei gruppi |
| `studenti` | `int[4]` | Dimensione di ogni gruppo |
| `nomi` | `const char *[4]` | Nomi dei gruppi |
| `migliore`, `gruppo_max` | `int` | Gruppo con la media più alta, gruppo del voto massimo |
| `voto_max` | `const int *` | Voto più alto trovato |

| Funzione | Compito |
|----------|---------|
| `media(voti, n)` | Media di un array di voti |

### Algoritmo in linguaggio naturale

1. Per ogni gruppo: stampare i voti aggiornando `voto_max` e `gruppo_max`;
   stampare la media; se è maggiore di quella del migliore aggiornare
   `migliore`.
2. Stampare il gruppo migliore e il voto più alto.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Input:** nessuno.
- **Valori intermedi attesi:** Blu: 38 / 5 = 7.60; Gialli: 18 / 2 = 9.00.
- **Output atteso:**
  ```
    Rossi   (3)  voti:  7  8  6       media 7.00
    Blu     (5)  voti:  9  7  8  8  6 media 7.60
    Verdi   (4)  voti:  6  6  7  5    media 6.00
    Gialli  (2)  voti: 10  8          media 9.00

  Gruppo con la media piu' alta: Gialli (9.00)
  Voto piu' alto della classe: 10, nel gruppo Gialli
  ```
