# Analisi – 050-problema-filtro-misure.c

## 1. Problema

Un fonometro misura ogni 10 minuti il rumore nella mensa durante la pausa
pranzo. Il referente per la sicurezza vuole contare ed elencare con
l'orario le misure oltre 80 dB, quelle tra 60 e 80 dB e quelle sotto
60 dB.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `db` | `int[12]` | 62, 71, 78, 84, 88, 82, 76, 69, 58, 55, 66, 73 dB, dalle 12:30 |

### Output

- Per ciascuna fascia (oltre 80, da 60 a 80, sotto 60 dB): il numero di
  misure e l'elenco con orario e valore.

### Vincoli

- `conta_se` ed `elenca_se` sono generiche: ricevono la condizione come
  puntatore a funzione `int (*)(int)` e la chiamano su ogni misura.
- Le tre condizioni hanno lo stesso prototipo `int (int)`; insieme coprono
  tutte le misure, ciascuna una sola volta: oltre 80 (80 escluso), da 60 a
  80 (estremi inclusi), sotto 60.
- Orario della misura di indice `i`: 12:30 + 10 × `i` minuti.

### Assunzioni

- Una misura ogni 10 minuti dalle 12:30.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `n` | `int` | Numero di misure della fascia (per singolare e plurale) |
| `p`, `conteggio` | `const int *`, `int` | In `conta_se` |
| `i`, `minuti` | `int` | In `elenca_se`: indice e orario |
| `ATTENZIONE`, `QUIETE` | `#define` | 80, 60 dB |

| Funzione | Compito |
|----------|---------|
| `conta_se(v, n, condizione)` | Conta gli elementi che soddisfano la condizione |
| `elenca_se(v, n, condizione)` | Stampa orario e valore degli elementi che la soddisfano |
| `rumorosa`, `normale`, `tranquilla` | Le tre condizioni: `int (int)` |

### Algoritmo in linguaggio naturale

1. Per ciascuna delle tre condizioni chiamare `conta_se` e stampare il
   numero, poi `elenca_se` con la stessa condizione.
2. In `conta_se`: scorrere le misure e contare quelle per cui
   `condizione(*p)` vale 1.
3. In `elenca_se`: per ogni misura che soddisfa la condizione calcolare
   l'orario e stamparlo con il valore.

## 3. Casi di test

### Test 1 – Misure del sorgente

- **Cosa si verifica:** le tre fasce coprono tutte le 12 misure
  (3 + 7 + 2).
- **Input:** nessuno.
- **Output atteso:**
  ```
  === RUMORE IN MENSA (una misura ogni 10 minuti dalle 12:30) ===
  Oltre 80 dB:    3 misure ->  13:00 84  13:10 88  13:20 82
  Da 60 a 80 dB:  7 misure ->  12:30 62  12:40 71  12:50 78  13:30 76  13:40 69  14:10 66  14:20 73
  Sotto 60 dB:    2 misure ->  13:50 58  14:00 55
  ```

### Test 2 – Valori sulle soglie

- **Cosa si verifica:** 80 e 60 appartengono alla fascia intermedia.
- **Procedura:** nel sorgente sostituire 84 con 80 e 58 con 60,
  ricompilare ed eseguire.
- **Output atteso:** `Oltre 80 dB:    2 misure`, `Da 60 a 80 dB:  9 misure`,
  `Sotto 60 dB:    1 misura` (al singolare).
