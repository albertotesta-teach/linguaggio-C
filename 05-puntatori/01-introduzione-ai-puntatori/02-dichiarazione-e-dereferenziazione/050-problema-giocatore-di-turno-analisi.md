# Analisi – 050-problema-giocatore-di-turno.c

## 1. Problema

Due giocatori lanciano a turno un dado e sommano il risultato; chi
raggiunge per primo 20 punti vince. Se esce 1 il giocatore perde 3 punti,
senza scendere sotto zero. Le istruzioni di ogni turno sono le stesse per
i due giocatori: cambia solo quale punteggio aggiornare.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `nome_1`, `nome_2` | `char[12]` | `"Anna"`, `"Bruno"` |
| `lanci` | `int[16]` | 4, 6, 5, 1, 6, 3, 2, 5, 1, 6, 4, 4, 6, 2, 3, 5 (partita ripetibile) |

### Output

- Una riga per turno: numero del turno, giocatore, lancio, punti del
  giocatore e punteggio dei due.
- `Vince <nome> con N punti!` quando un giocatore raggiunge il traguardo,
  oppure `Lanci finiti: ...` se i lanci si esauriscono prima.

### Vincoli

- Le istruzioni del turno usano solo `*punti_turno` e `nome_turno`: il
  giocatore di turno è deciso da dove puntano i due puntatori.
- Modificare `*punti_turno` cambia `punti_1` o `punti_2`.
- Con un lancio di 1 si tolgono 3 punti, ma il punteggio non scende sotto 0.
- Il turno passa all'altro giocatore solo se non c'è un vincitore; per
  sapere chi è di turno si confronta `punti_turno` con `&punti_1`.
- Il ciclo termina quando c'è un vincitore o i lanci sono finiti (flag, senza
  `break`).

### Assunzioni

- Traguardo 20 punti; gioca per primo `nome_1`.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `punti_1`, `punti_2` | `int` | Punteggi dei due giocatori |
| `punti_turno` | `int *` | Indirizzo del punteggio del giocatore di turno |
| `nome_turno` | `char *` | Indirizzo del primo carattere del nome del giocatore di turno |
| `k` | `int` | Indice del lancio |
| `vincitore` | `int` | Flag di fine partita |
| `TRAGUARDO`, `LANCI`, `LUNG` | `#define` | 20, 16, 12 |

### Algoritmo in linguaggio naturale

1. Far puntare `punti_turno` a `punti_1` e `nome_turno` a `nome_1`.
2. Finché ci sono lanci e non c'è un vincitore:
   1. se il lancio è 1 togliere 3 a `*punti_turno` (minimo 0), altrimenti
      aggiungere il lancio;
   2. stampare la riga del turno;
   3. se `*punti_turno` ≥ 20 porre `vincitore = 1` e stampare il vincitore;
      altrimenti far puntare `punti_turno` e `nome_turno` all'altro
      giocatore;
   4. passare al lancio successivo.
3. Se non c'è un vincitore stampare il punteggio finale.

## 3. Casi di test

### Test 1 – Partita completa

- **Cosa si verifica:** turni alternati, lancio di 1 e vittoria.
- **Input:** nessuno (lanci del sorgente).
- **Valori intermedi attesi:** al turno 4 Bruno ha 6 punti e lancia 1:
  6 − 3 = 3; al turno 12 Bruno arriva a 17 + 4 = 21.
- **Output atteso:**
  ```
  === GARA DI DADI (traguardo 20 punti) ===
  Turno  1 - Anna   lancia 4: punti  4   (Anna 4 - Bruno 0)
  Turno  2 - Bruno  lancia 6: punti  6   (Anna 4 - Bruno 6)
  Turno  3 - Anna   lancia 5: punti  9   (Anna 9 - Bruno 6)
  Turno  4 - Bruno  lancia 1: punti  3   (Anna 9 - Bruno 3)
  Turno  5 - Anna   lancia 6: punti 15   (Anna 15 - Bruno 3)
  Turno  6 - Bruno  lancia 3: punti  6   (Anna 15 - Bruno 6)
  Turno  7 - Anna   lancia 2: punti 17   (Anna 17 - Bruno 6)
  Turno  8 - Bruno  lancia 5: punti 11   (Anna 17 - Bruno 11)
  Turno  9 - Anna   lancia 1: punti 14   (Anna 14 - Bruno 11)
  Turno 10 - Bruno  lancia 6: punti 17   (Anna 14 - Bruno 17)
  Turno 11 - Anna   lancia 4: punti 18   (Anna 18 - Bruno 17)
  Turno 12 - Bruno  lancia 4: punti 21   (Anna 18 - Bruno 21)

  Vince Bruno con 21 punti!
  ```

### Test 2 – Lancio di 1 con punteggio basso

- **Cosa si verifica:** il punteggio non scende sotto 0.
- **Procedura:** nel sorgente sostituire il primo lancio (4) con 1,
  ricompilare ed eseguire.
- **Output atteso** (primo turno):
  ```
  Turno  1 - Anna   lancia 1: punti  0   (Anna 0 - Bruno 0)
  ```

### Test 3 – Lanci finiti senza vincitore

- **Cosa si verifica:** il ramo in cui nessuno raggiunge il traguardo.
- **Procedura:** nel sorgente impostare tutti i 16 lanci a 2, ricompilare ed
  eseguire.
- **Output atteso** (ultime righe):
  ```
  Turno 16 - Bruno  lancia 2: punti 16   (Anna 16 - Bruno 16)

  Lanci finiti: Anna 16 - Bruno 16
  ```
