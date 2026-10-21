# Analisi – 050-problema-memoria-datalogger.c

## 1. Problema

Una stazione meteo didattica usa un microcontrollore con 32 KB di memoria
per le misure. Ogni misura comprende temperatura, umidità e pressione ed
è presa ogni 10 minuti. Bisogna scegliere i tipi delle variabili
confrontando tre versioni (tutto `double`, tutto `float`, interi piccoli)
in base a quante misure entrano in memoria e per quanti giorni si può
registrare.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore | Significato |
|------|------|--------|-------------|
| `t_a`, `u_a`, `p_a` | `double` | 21.5, 45.0, 1013.2 | Versione A |
| `t_b`, `u_b`, `p_b` | `float` | 21.5, 45.0, 1013.2 | Versione B |
| `t_c` | `short` | 215 | Versione C: temperatura in decimi di grado |
| `u_c` | `char` | 45 | Versione C: umidità in % (0-100) |
| `p_c` | `short` | 1013 | Versione C: pressione in hPa |
| `MEMORIA_DATI` | `#define` | 32768 | Byte disponibili (32 KB) |
| `INTERVALLO` | `#define` | 10 | Minuti tra due misure |

### Output

- Una riga per versione: tipi usati, byte per misura, numero di misure che
  entrano in memoria e giorni di registrazione.
- Un esempio di misura nella versione C, con la temperatura convertita in
  gradi per la stampa.

### Vincoli

- I byte per misura si ricavano con `sizeof`, non si scrivono a mano.
- Il numero di misure è intero: `MEMORIA_DATI / byte_misura` con divisione
  intera.
- Giorni = misure × 10 / 1440 (minuti in un giorno), calcolati in `double`.
- Nella versione C la temperatura è memorizzata in decimi di grado; la
  conversione in gradi (`t_c / 10.0`) si fa solo per la stampa.

### Assunzioni

- Dimensioni tipiche dei tipi: `double` 8, `float` 4, `short` 2, `char` 1 byte.
- Una precisione di un decimo di grado e di 1 hPa è sufficiente.
- L'umidità (0-100) sta in un `char`.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `misure` | `int` | In `stampa_versione`: misure che entrano in memoria |
| `giorni` | `double` | In `stampa_versione`: giorni di registrazione |
| `MINUTI_GIORNO` | `#define` | 24 × 60 = 1440 |

| Funzione | Compito |
|----------|---------|
| `stampa_versione` | Calcola misure e giorni per una dimensione data e stampa la riga |

### Algoritmo in linguaggio naturale

1. Stampare memoria disponibile e intervallo di misura.
2. Per ciascuna versione calcolare i byte per misura come somma delle
   `sizeof` delle tre variabili e chiamare `stampa_versione`, che:
   1. calcola le misure con la divisione intera;
   2. calcola i giorni come misure × 10 / 1440;
   3. stampa la riga della tabella.
3. Stampare l'esempio di misura della versione C.

## 3. Casi di test

### Test 1 – Byte per misura

- **Cosa si verifica:** le dimensioni ricavate con `sizeof`.
- **Input:** nessuno (dati del sorgente).
- **Valori intermedi attesi:** A = 8 + 8 + 8 = 24; B = 4 + 4 + 4 = 12;
  C = 2 + 1 + 2 = 5.
- **Output atteso:** colonna `Byte` con 24, 12 e 5.

### Test 2 – Misure e giorni di registrazione

- **Cosa si verifica:** divisione intera per le misure e calcolo dei giorni.
- **Input:** nessuno.
- **Valori intermedi attesi:** A: 32768 / 24 = 1365 misure,
  1365 × 10 / 1440 = 9.48 giorni; C: 32768 / 5 = 6553 misure, 45.5 giorni.
- **Output atteso:**
  ```
  === DIMENSIONAMENTO DEL DATALOGGER ===
  Memoria disponibile: 32768 byte, una misura ogni 10 minuti

    Ver. Tipi                                Byte  Misure  Giorni
    A    double, double, double                24    1365     9.5
    B    float, float, float                   12    2730    19.0
    C    short (decimi), char (%), short        5    6553    45.5
  ```

### Test 3 – Rappresentazione con interi

- **Cosa si verifica:** la conversione dei decimi di grado solo in stampa.
- **Input:** nessuno (`t_c` = 215).
- **Output atteso:**
  ```
  Esempio di misura nella versione C: 215 decimi = 21.5 gradi, 45%, 1013 hPa
  Con gli interi si perde poco in precisione e si registra molto piu' a lungo.
  ```

### Test 4 – Memoria diversa

- **Cosa si verifica:** il calcolo dipende solo da `MEMORIA_DATI`.
- **Procedura:** nel sorgente impostare `MEMORIA_DATI` a `65536` (64 KB),
  ricompilare ed eseguire.
- **Valori intermedi attesi:** A: 2730 misure; B: 5461; C: 13107.
- **Output atteso:** i giorni raddoppiano circa: 19.0, 37.9, 91.0.
