# Analisi – 070-problema-riordino-scorte.c

## 1. Problema

Il tecnico del distributore automatico ha 5 confezioni da 12 pezzi e le
assegna una alla volta al prodotto (acqua, succhi, snack) che in quel
momento ha la scorta più bassa. Il programma mostra a ogni giro il prodotto
rifornito e le scorte aggiornate.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `acqua`, `succhi`, `snack` | `int` | 14, 6, 9 pezzi |
| `CONFEZIONI`, `DIM_CONFEZIONE` | `#define` | 5 confezioni da 12 pezzi |

### Output

- Le scorte iniziali.
- Per ogni confezione: il prodotto rifornito e le tre scorte aggiornate.
- Una nota sul comportamento in caso di parità.

### Vincoli

- Il minimo si cerca confrontando i valori (`succhi < *minimo`) ma si
  ricorda l'indirizzo della variabile (`minimo = &succhi`), così il
  rifornimento `*minimo = *minimo + 12` modifica proprio quella scorta.
- Il nome del prodotto rifornito si ricava confrontando il puntatore con gli
  indirizzi delle variabili (`minimo == &acqua`).
- Il confronto usa `<`: a parità resta il primo prodotto controllato
  (acqua, poi succhi, poi snack).

### Assunzioni

- Le confezioni sono tutte uguali e si possono assegnare a qualsiasi prodotto.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `minimo` | `int *` | Indirizzo della scorta più bassa |
| `giro` | `int` | Confezione corrente (1-5) |

### Algoritmo in linguaggio naturale

1. Stampare le scorte iniziali.
2. Per ogni confezione:
   1. porre `minimo = &acqua`; se `succhi < *minimo` porre
      `minimo = &succhi`; se `snack < *minimo` porre `minimo = &snack`;
   2. aggiungere 12 a `*minimo`;
   3. stampare il nome del prodotto (confrontando `minimo` con gli
      indirizzi) e le scorte.
3. Stampare la nota sulla parità.

## 3. Casi di test

### Test 1 – Rifornimento con i dati del sorgente

- **Input:** nessuno.
- **Valori intermedi attesi:** giro 1: minimo succhi (6) → 18; giro 2:
  snack (9) → 21; giro 3: acqua (14) → 26.
- **Output atteso:**
  ```
  Confezione 1 -> succhi   scorte: acqua 14, succhi 18, snack  9
  Confezione 2 -> snack    scorte: acqua 14, succhi 18, snack 21
  Confezione 3 -> acqua    scorte: acqua 26, succhi 18, snack 21
  Confezione 4 -> succhi   scorte: acqua 26, succhi 30, snack 21
  Confezione 5 -> snack    scorte: acqua 26, succhi 30, snack 33
  ```

### Test 2 – Parità

- **Cosa si verifica:** a parità viene rifornito il primo prodotto controllato.
- **Procedura:** nel sorgente impostare `acqua = 6`, ricompilare ed eseguire.
- **Valori intermedi attesi:** al giro 1 acqua e succhi valgono 6: con `<`
  resta `minimo = &acqua`.
- **Output atteso** (prime righe):
  ```
  Confezione 1 -> acqua    scorte: acqua 18, succhi  6, snack  9
  Confezione 2 -> succhi   scorte: acqua 18, succhi 18, snack  9
  ```
