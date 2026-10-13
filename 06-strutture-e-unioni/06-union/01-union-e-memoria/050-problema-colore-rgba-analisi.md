# Analisi – 050-problema-colore-rgba.c

## 1. Problema

Per il sito della scuola si schiariscono, scuriscono e trasformano in grigio i colori RGBA. Il colore è una union: un codice a 32 bit 0xRRGGBBAA e un array di quattro canali indicizzato da un enum. L'enum elenca i canali nell'ordine in memoria di una macchina little-endian (ALFA, BLU, VERDE, ROSSO).

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Canale` | `ALFA, BLU, VERDE, ROSSO, NUM_CANALI` | indice del canale |
| `Colore` | `union: codice (uint32_t), canale[4] (uint8_t)` | colore RGBA |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `c` | `Colore` | — | Colore letto |
| `rgb` | `unsigned long` | — | Valore esadecimale RRGGBB |
| `percento` | `int` | — | Da 0 a 100 |

| Funzione | Compito |
|----------|---------|
| `schiarisci(c, p)` | Ogni canale si avvicina a 255 del p per cento |
| `scurisci(c, p)` | Ogni canale si avvicina a 0 |
| `grigio(c)` | Luminosità 0.299 R + 0.587 G + 0.114 B su tutti i canali |
| `stampa(nome, c)` | Codice e canali |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Schiarire

**a) Input** – `S 3366CC 40`

**b) Output** – #84A3E0FF: R 132, G 163, B 224

**c) Variabili di supporto** – `c.canale[k]`

**d) Vincoli** – alfa non cambia

**e) Assunzioni** – alfa letto come FF

**f) Algoritmo in linguaggio naturale** – canale + (255 - canale) × p / 100 per BLU, VERDE e ROSSO.

### Caso d'uso 2 – Scurire

**a) Input** – `D 3366CC 50`

**b) Output** – #1A3366FF

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – canale - canale × p / 100.

### Caso d'uso 3 – Grigio

**a) Input** – `G 3366CC`; `G FF0000`

**b) Output** – #626262FF; #4C4C4CFF

**c) Variabili di supporto** – —

**d) Vincoli** – arrotondamento all'intero più vicino

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stesso valore in rosso, verde e blu.

### Caso d'uso 4 – Codice e canali insieme

**a) Input** – qualsiasi

**b) Output** – il codice cambia quando cambiano i canali

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – macchina little-endian

**f) Algoritmo in linguaggio naturale** – codice e canali sono gli stessi 4 byte della union.
