# Analisi – 060-problema-inverti-percorso.c

## 1. Problema

Una gita in bicicletta attraversa 5 località con 4 tratti, di cui sono note
lunghezza e dislivello. Per il ritorno bisogna preparare la tabella dei
tratti in ordine inverso, con i dislivelli di segno opposto, e calcolare
chilometri e metri di salita di andata e ritorno.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `localita` | `char[5][16]` | Paese, Mulino, Cascina, Belvedere, Santuario (ordine di andata) |
| `distanze` | `int[4]` | 52, 38, 61, 27 (decimi di km) |
| `dislivelli` | `int[4]` | 40, −15, 120, 85 (metri, positivi in salita) |

### Output

- La tabella dell'andata: per ogni tratto partenza, arrivo, km e
  dislivello con segno; totale km e metri di salita.
- La stessa tabella per il ritorno.

### Vincoli

- `inverti` riceve l'intervallo `[inizio, fine)` (fine esclusa) e scambia gli
  elementi a coppie con due puntatori che si avvicinano dagli estremi; si
  ferma quando `sinistra` non è più minore di `destra`, quindi l'elemento
  centrale di un intervallo dispari resta al suo posto.
- `cambia_segno` modifica l'array sul posto scorrendolo con un puntatore.
- Nel ritorno le località si leggono all'indietro (non si invertono).
- Nei totali si sommano solo i dislivelli positivi.

### Assunzioni

- L'intervallo passato alle funzioni non è vuoto.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `sinistra`, `destra`, `scambio` | `int *`, `int *`, `int` | In `inverti`: estremi che si avvicinano, valore di appoggio |
| `p` | `int *` | In `cambia_segno`: puntatore di scorrimento |
| `da`, `a`, `km`, `salita` | `int` | In `stampa_tappe`: località del tratto, totali |

| Funzione | Compito |
|----------|---------|
| `inverti(int *inizio, int *fine)` | Inverte gli elementi di `[inizio, fine)` |
| `cambia_segno(int *inizio, int *fine)` | Cambia il segno degli elementi di `[inizio, fine)` |
| `stampa_tappe` | Stampa la tabella e i totali, leggendo le località in avanti o all'indietro |

### Algoritmo in linguaggio naturale

1. Stampare la tabella dell'andata.
2. Invertire `distanze` e `dislivelli` con `inverti(&a[0], &a[0] + 4)`.
3. Cambiare il segno dei dislivelli.
4. Stampare la tabella del ritorno, con le località da `Santuario` a `Paese`.
5. In `inverti`: porre `sinistra = inizio`, `destra = fine − 1`; finché
   `sinistra < destra` scambiare `*sinistra` e `*destra`, avanzare
   `sinistra` e arretrare `destra`.

## 3. Casi di test

### Test 1 – Andata

- **Input:** nessuno (dati del sorgente).
- **Output atteso:**
  ```
  === ANDATA ===
    Paese      -> Mulino       5.2 km    +40 m
    Mulino     -> Cascina      3.8 km    -15 m
    Cascina    -> Belvedere    6.1 km   +120 m
    Belvedere  -> Santuario    2.7 km    +85 m
    Totale 17.8 km, 245 m di salita
  ```

### Test 2 – Inversione e cambio di segno

- **Cosa si verifica:** `distanze` diventa {27, 61, 38, 52}, `dislivelli`
  diventa {85, 120, −15, 40} e poi {−85, −120, 15, −40}.
- **Input:** nessuno.
- **Output atteso:**
  ```
  === RITORNO ===
    Santuario  -> Belvedere    2.7 km    -85 m
    Belvedere  -> Cascina      6.1 km   -120 m
    Cascina    -> Mulino       3.8 km    +15 m
    Mulino     -> Paese        5.2 km    -40 m
    Totale 17.8 km, 15 m di salita
  ```
