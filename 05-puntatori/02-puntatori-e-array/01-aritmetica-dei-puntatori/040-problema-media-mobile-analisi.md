# Analisi – 040-problema-media-mobile.c

## 1. Problema

Un sensore misura la CO2 in un'aula ogni 5 minuti a partire dalle 8:00.
Per non reagire a una singola lettura disturbata si calcola la media di 3
letture consecutive (media mobile) e si segnala quando supera 1000 ppm,
indicando l'orario del gruppo e il primo allarme.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `letture` | `int[12]` | 620, 700, 790, 880, 960, 1050, 1120, 1080, 870, 760, 820, 910 ppm, in ordine di tempo |

### Output

- Una riga per ogni gruppo di 3 letture consecutive: orario di inizio e
  fine, le tre letture e la media, con `<- aprire le finestre` se la media
  supera 1000 ppm.
- L'orario del primo gruppo oltre soglia e il numero di gruppi oltre
  soglia, oppure `Aria sempre sotto i 1000 ppm.`

### Vincoli

- L'array si scorre con un puntatore `finestra`; le tre letture del gruppo
  sono `*finestra`, `*(finestra + 1)`, `*(finestra + 2)`.
- `fine = &letture[0] + 12` punta subito dopo l'ultima lettura e non si
  dereferenzia; il gruppo non deve uscire dall'array, quindi l'ultima
  posizione di partenza è `fine − 3` (10 gruppi su 12 letture).
- La differenza `finestra − &letture[0]` è un numero di elementi e dà
  l'indice della lettura, da cui si ricava l'orario.
- La soglia si supera con media > 1000 (1000 esatto non è allarme).
- `primo_allarme` si assegna solo la prima volta (finché è `NULL`).

### Assunzioni

- Letture ogni 5 minuti dalle 8:00; media intera (troncata).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `fine` | `const int *` | Indirizzo subito dopo l'ultima lettura |
| `finestra` | `const int *` | Prima lettura del gruppo di 3 |
| `primo_allarme` | `const int *` | Primo gruppo oltre soglia, `NULL` se nessuno |
| `media`, `allarmi` | `int` | Media del gruppo, numero di gruppi oltre soglia |
| `LETTURE`, `LARGHEZZA`, `SOGLIA`, `INTERVALLO` | `#define` | 12, 3, 1000, 5 |

| Funzione | Compito |
|----------|---------|
| `stampa_orario` | Converte l'indice di una lettura in orario `hh:mm` |

### Algoritmo in linguaggio naturale

1. Porre `fine = &letture[0] + 12` e `primo_allarme = NULL`.
2. Per `finestra` da `&letture[0]` a `fine − 3`:
   1. calcolare la media delle tre letture;
   2. stampare l'orario della prima e della terza lettura, le letture e la
      media;
   3. se la media supera 1000 stampare l'avviso, contare l'allarme e, se è
      il primo, porre `primo_allarme = finestra`.
3. Se `primo_allarme` è `NULL` stampare che l'aria è sempre sotto soglia,
   altrimenti l'orario del primo allarme e il numero di allarmi.

## 3. Casi di test

### Test 1 – Letture del sorgente

- **Input:** nessuno.
- **Valori intermedi attesi:** gruppo che inizia all'indice 4:
  (960 + 1050 + 1120) / 3 = 1043.
- **Output atteso:**
  ```
  === MEDIA MOBILE DELLA CO2 (gruppi di 3 letture) ===
    08:00-08:10    620  700  790   media  703 ppm
    08:05-08:15    700  790  880   media  790 ppm
    08:10-08:20    790  880  960   media  876 ppm
    08:15-08:25    880  960 1050   media  963 ppm
    08:20-08:30    960 1050 1120   media 1043 ppm   <- aprire le finestre
    08:25-08:35   1050 1120 1080   media 1083 ppm   <- aprire le finestre
    08:30-08:40   1120 1080  870   media 1023 ppm   <- aprire le finestre
    08:35-08:45   1080  870  760   media  903 ppm
    08:40-08:50    870  760  820   media  816 ppm
    08:45-08:55    760  820  910   media  830 ppm

  Primo allarme sul gruppo che inizia alle 08:20 (3 gruppi oltre soglia).
  ```

### Test 2 – Nessun allarme

- **Cosa si verifica:** `primo_allarme` resta `NULL`.
- **Procedura:** nel sorgente sostituire 1050, 1120, 1080 con 950, 920,
  880, ricompilare ed eseguire.
- **Output atteso** (ultima riga): `Aria sempre sotto i 1000 ppm.`
