# Analisi – 060-problema-durata-lezioni.c

## 1. Problema

La segreteria inserisce inizio e fine di ogni lezione di una giornata. Il
programma controlla gli orari, calcola la durata in minuti, segnala le
lezioni più lunghe di 60 o più corte di 50 minuti e le sovrapposizioni con
la lezione precedente; alla fine stampa il numero di lezioni e il tempo
totale. Un inizio `0 0` termina. Gli orari sono struct `Orario`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `inizio` | `Orario` | Ore e minuti di inizio; `0 0` termina |
| `fine` | `Orario` | Ore e minuti di fine |

### Output

- Per ogni lezione valida: `HH:MM - HH:MM  N minuti` con le eventuali
  note `(troppo lunga)` / `(troppo corta)` e
  `(si sovrappone alla precedente)`.
- `Orario non valido.` o `La fine deve venire dopo l'inizio.` per le
  lezioni scartate.
- Alla fine: `Lezioni registrate: N, tempo totale H h MM min`.

### Vincoli

- Ore 0-23, minuti 0-59.
- I confronti si fanno sui minuti da mezzanotte (`ore * 60 + minuti`).
- La fine deve essere strettamente dopo l'inizio.
- Durata normale da 50 a 60 minuti compresi.
- Sovrapposizione: l'inizio viene prima della fine della lezione
  precedente valida.
- Una lezione scartata non viene numerata né sommata.
- Un orario non numerico viene scartato (resto della riga) e segnalato;
  a fine input il programma termina come con `0 0`.

### Assunzioni

- Le lezioni sono nella stessa giornata (nessuna attraversa la
  mezzanotte); per questo `0 0` può fare da terminatore.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Orario` | `typedef struct { int ore; int minuti; } Orario;` | Un orario della giornata |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `fine_precedente` | `Orario` | Fine dell'ultima lezione valida |
| `da_mezzanotte_inizio`, `da_mezzanotte_fine` | `int` | Orari in minuti |
| `durata`, `totale` | `int` | Durata della lezione e somma |
| `lezione` | `int` | Numero della prossima lezione |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `valido(ore, minuti)` | 1 se l'orario è nell'intervallo |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché l'inizio non è `0 0`:
   1. leggere l'inizio (fine input → `0 0`; testo → orario non valido);
   2. se non è `0 0` leggere la fine (testo o fine input → non valida);
   3. se un orario non è valido o la fine non viene dopo l'inizio,
      segnalarlo;
   4. altrimenti calcolare la durata, stamparla con le note, sommarla,
      ricordare la fine e passare alla lezione successiva.
2. Stampare il numero di lezioni e il totale in ore e minuti.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Giornata con lezioni scartate

- **Cosa si verifica:** note di durata, sovrapposizione, orari non validi e
  non numerici, fine prima dell'inizio.
- **Input:** `8 0` `8 55`, `9 0` `10 10`, `10 0` `10 40`, `abc`, `11 0`
  `xx`, `25 0` `11 0`, `11 0` `10 30`, `0 0`
- **Valori intermedi attesi:** 55 + 70 + 40 = 165 minuti; 10:00 viene prima
  della fine precedente 10:10.
- **Output atteso:**
  ```
    08:00 - 08:55  55 minuti
    09:00 - 10:10  70 minuti  (troppo lunga)
    10:00 - 10:40  40 minuti  (troppo corta)  (si sovrappone alla precedente)
    Orario non valido.
    Orario non valido.
    Orario non valido.
    La fine deve venire dopo l'inizio.
  Lezioni registrate: 3, tempo totale 2 h 45 min
  ```

### Test 2 – Nessuna lezione

- **Input:** `0 0`
- **Output atteso:** `Lezioni registrate: 0, tempo totale 0 h 00 min`.

### Test 3 – Fine input

- **Input:** `8 0` `9 0`, poi fine input.
- **Output atteso:** `Lezioni registrate: 1, tempo totale 1 h 00 min`.
