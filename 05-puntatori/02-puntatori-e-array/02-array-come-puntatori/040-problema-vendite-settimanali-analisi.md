# Analisi – 040-problema-vendite-settimanali.c

## 1. Problema

Il gestore di un bar registra l'incasso di ogni giorno della settimana e
vuole confrontare i giorni feriali con il fine settimana: totale, media e
giorno migliore di ciascun gruppo, la differenza tra le medie e l'incasso
complessivo.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `incassi` | `int[7]` | 640, 585, 710, 690, 980, 1420, 1260 euro (da lunedì a domenica) |
| `giorni` | `char[7][10]` | Nomi dei giorni |

### Output

- Per i giorni feriali e per il fine settimana: intervallo dei giorni,
  totale, media e giorno migliore con il suo incasso.
- Quanto incassa in più, in media, un giorno del fine settimana (euro e
  percentuale).
- L'incasso della settimana.

### Vincoli

- Le funzioni ricevono un puntatore al primo elemento e il numero di
  elementi: passando `incassi + 5` si passa il sottoarray del fine
  settimana, e la funzione vede solo i 2 elementi ricevuti.
- Dentro la funzione `v[0]` è il primo elemento del sottoarray: la
  posizione restituita da `posizione_massimo` è relativa al gruppo, e per
  il nome del giorno si aggiunge l'indice `primo` del gruppo nella
  settimana.
- `posizione_massimo` restituisce `migliore − v`, differenza tra puntatori.
- Medie e percentuale sono intere (divisione intera).

### Assunzioni

- La media dei feriali è maggiore di zero (serve per la percentuale).
- A parità di incasso vale il primo giorno del gruppo.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `media_feriali`, `media_festivi` | `int` | Medie dei due gruppi |
| `p`, `migliore` | `const int *` | Nelle funzioni: puntatore di scorrimento, elemento massimo |
| `GIORNI`, `FERIALI`, `LUNG` | `#define` | 7, 5, 10 |

| Funzione | Compito |
|----------|---------|
| `totale(v, n)` | Somma degli `n` elementi da `v` |
| `posizione_massimo(v, n)` | Posizione del massimo dentro l'intervallo |
| `riepilogo(titolo, v, n, primo, giorni)` | Stampa totale, media e giorno migliore di un gruppo |

### Algoritmo in linguaggio naturale

1. Chiamare `riepilogo` per i feriali (`incassi`, 5 giorni, primo 0) e per
   il fine settimana (`incassi + 5`, 2 giorni, primo 5).
2. In `riepilogo`: calcolare totale e posizione del massimo nel gruppo;
   stampare il primo e l'ultimo giorno del gruppo, totale, media e giorno
   migliore (`giorni[primo + migliore]`, `v[migliore]`).
3. Calcolare le due medie, stampare la differenza e la percentuale
   `differenza × 100 / media_feriali`.
4. Stampare il totale dei 7 giorni.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Input:** nessuno.
- **Valori intermedi attesi:** feriali 3605 / 5 = 721; fine settimana
  2680 / 2 = 1340; nel sottoarray `posizione_massimo` restituisce 0
  (sabato), cioè il giorno 5 + 0 della settimana; (1340 − 721) × 100 / 721
  = 85.
- **Output atteso:**
  ```
  === INCASSI DELLA SETTIMANA ===

  Feriali (lunedi-venerdi)
    totale  3605 euro, media  721 euro
    giorno migliore: venerdi con 980 euro

  Fine settimana (sabato-domenica)
    totale  2680 euro, media 1340 euro
    giorno migliore: sabato con 1420 euro

  Un giorno del fine settimana incassa in media 619 euro in piu' (+85%).
  Incasso della settimana: 6285 euro
  ```
