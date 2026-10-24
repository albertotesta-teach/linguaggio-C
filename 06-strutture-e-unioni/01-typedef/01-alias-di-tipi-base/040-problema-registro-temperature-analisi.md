# Analisi – 040-problema-registro-temperature.c

## 1. Problema

La classe registra per sette giorni la temperatura minima e massima della
serra. Il programma calcola l'escursione di ogni giorno, la media delle
minime e delle massime, il giorno con l'escursione più ampia e i giorni con
rischio di gelo (minima sotto 2 gradi). Tutte le temperature hanno il tipo
`Gradi`.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `minime` | `Gradi[7]` | 3.5, 1.2, −0.8, 2.4, 4.1, 5.0, 1.6 |
| `massime` | `Gradi[7]` | 12.0, 14.5, 11.2, 9.8, 13.3, 15.7, 16.4 |
| `giorni` | `const char *[7]` | Nomi dei giorni da lunedì a domenica |

### Output

- Una riga per giorno: minima, massima, escursione e `rischio gelo` se la
  minima è sotto 2 gradi.
- La media delle minime e delle massime, il giorno con l'escursione più
  ampia e il numero di giorni con rischio di gelo.

### Vincoli

- Tutte le temperature hanno il tipo `Gradi` (`typedef double Gradi;`): il
  nome dice che cosa rappresenta il valore.
- Escursione = massima − minima.
- Rischio di gelo con minima strettamente minore di 2.0 gradi
  (`SOGLIA_GELO`).
- A parità di escursione vale il primo giorno (confronto con `>`).

### Assunzioni

- Le temperature sono già valide (massima ≥ minima).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Gradi` | `typedef double Gradi;` | Temperatura in gradi Celsius |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `g` | `int` | Indice del giorno |
| `gelo` | `int` | Giorni con minima sotto la soglia |
| `ampia` | `int` | Indice del giorno con escursione massima |
| `GIORNI`, `SOGLIA_GELO` | `#define` | 7, 2.0 |

| Funzione | Compito |
|----------|---------|
| `media(v, n)` | Media di n temperature |
| `escursione(minima, massima)` | Differenza massima − minima |
| `giorno_escursione_massima(minime, massime, n)` | Indice del primo giorno con l'escursione più ampia |

### Algoritmo in linguaggio naturale

1. Per ogni giorno stampare minima, massima ed escursione; se la minima è
   sotto la soglia aggiungere l'avviso e contare il giorno.
2. Trovare il giorno con l'escursione più ampia.
3. Stampare le due medie, il giorno più variabile e i giorni di gelo.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Input:** nessuno.
- **Valori intermedi attesi:** somma delle minime 17.0 → media 2.43;
  escursione di domenica 16.4 − 1.6 = 14.8.
- **Output atteso:**
  ```
    Giorno      Minima  Massima  Escursione
    lunedi        3.5     12.0         8.5
    martedi       1.2     14.5        13.3   rischio gelo
    mercoledi    -0.8     11.2        12.0   rischio gelo
    giovedi       2.4      9.8         7.4
    venerdi       4.1     13.3         9.2
    sabato        5.0     15.7        10.7
    domenica      1.6     16.4        14.8   rischio gelo

  Media delle minime:  2.43 gradi
  Media delle massime: 13.27 gradi
  Escursione piu' ampia: domenica (14.8 gradi)
  Giorni con rischio di gelo: 3
  ```
