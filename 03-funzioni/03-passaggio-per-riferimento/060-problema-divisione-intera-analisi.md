# Analisi – 060-problema-divisione-intera.c

## 1. Problema
Due conversioni pratiche producono ciascuna due risultati interi che derivano
dalla stessa divisione e non possono essere separati in chiamate distinte senza
inefficienza. Il passaggio per riferimento permette a ciascuna funzione di
scrivere entrambi i risultati direttamente nelle variabili del chiamante.

- Conversione 1: secondi totali → ore, minuti e secondi residui
- Conversione 2: importo in centesimi → euro e centesimi residui

## 2. Analisi

### Input
Nessun input da tastiera: i valori da convertire sono passati come argomenti
a `stampa_durata` e `stampa_importo` nel `main`.

| Parametro | Tipo | Descrizione |
|---|---|---|
| `secondi_tot` | int | Durata totale in secondi |
| `centesimi_tot` | int | Importo totale in centesimi |

### Output
Una riga per ogni valore convertito:
- durate nel formato `secondi  →  Hh MMm SSs` (minuti e secondi su due cifre);
- importi nel formato `centesimi →  E EUR e CC cent` (centesimi su due cifre).

### Vincoli
- `secondi_tot >= 0` e `centesimi_tot >= 0`; i valori negativi non sono
  gestiti
- Le componenti rispettano i loro intervalli: minuti e secondi tra 0 e 59,
  centesimi residui tra 0 e 99
- Le componenti ricompongono il valore iniziale:
  `ore × 3600 + minuti × 60 + sec = secondi_tot` e
  `euro × 100 + centesimi = centesimi_tot`

### Assunzioni
- I valori sono interi; non vengono validati

### Variabili di supporto

| Variabile | Tipo | Descrizione |
|---|---|---|
| `ore`, `minuti`, `sec` | int | Componenti del tempo, locali a `stampa_durata` |
| `euro`, `centesimi` | int | Componenti dell'importo, locali a `stampa_importo` |

| Funzione | Firma | Descrizione |
|---|---|---|
| `secondi_in_hms` | `void(int, int*, int*, int*)` | Converte secondi in h, min, sec |
| `centesimi_in_euro` | `void(int, int*, int*)` | Converte centesimi in euro e resto |
| `stampa_durata` | `void(int)` | Stampa secondi e forma ore/minuti/secondi |
| `stampa_importo` | `void(int)` | Stampa centesimi e forma euro/centesimi |

### Algoritmo in linguaggio naturale
Durata:
1. `*ore = secondi_tot / 3600` (divisione intera).
2. `*minuti = (secondi_tot % 3600) / 60`.
3. `*sec = secondi_tot % 60`.

Importo:
1. `*euro = centesimi_tot / 100`.
2. `*centesimi = centesimi_tot % 100`.

## 3. Casi di test

Il `main` esegue tutte le conversioni in sequenza: si esegue il programma
una volta e si confronta ogni riga con l'output atteso.

### Test 1 – Durate tipiche
- **Input:** 3725, 7384
- **Output atteso:**
```
   3725 secondi  →  1h 02m 05s
   7384 secondi  →  2h 03m 04s
```

### Test 2 – Durate ai confini delle unità
- **Cosa si verifica:** il passaggio da secondi a minuti e da minuti a ore
- **Input:** 59, 60, 3600
- **Output atteso:**
```
     59 secondi  →  0h 00m 59s
     60 secondi  →  0h 01m 00s
   3600 secondi  →  1h 00m 00s
```

### Test 3 – Durate limite
- **Cosa si verifica:** lo zero e l'ultimo secondo della giornata
- **Input:** 0, 86399
- **Output atteso:**
```
      0 secondi  →  0h 00m 00s
  86399 secondi  →  23h 59m 59s
```

### Test 4 – Importi
- **Input:** 1275, 9999, 25000
- **Output atteso:**
```
   1275 centesimi →  12 EUR e 75 cent
   9999 centesimi →  99 EUR e 99 cent
  25000 centesimi →  250 EUR e 00 cent
```

### Test 5 – Importi limite
- **Cosa si verifica:** importi sotto l'euro e cifra tonda
- **Input:** 0, 99, 100
- **Output atteso:**
```
      0 centesimi →  0 EUR e 00 cent
     99 centesimi →  0 EUR e 99 cent
    100 centesimi →  1 EUR e 00 cent
```
