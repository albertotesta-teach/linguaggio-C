# Analisi – 040-problema-configurazione-sola-lettura.c

## 1. Problema

Una cassa audio per le aule ha tre impostazioni (volume, bassi, luminosità)
con valori massimi decisi dall'istituto. Le richieste degli utenti vengono
applicate una alla volta; un valore oltre il massimo viene ridotto al
massimo. La configurazione dei limiti non deve poter essere modificata dal
programma.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `max_volume`, `max_bassi`, `max_luce` | `const int` | 70, 8, 100 (limiti dell'istituto) |
| `volume`, `bassi`, `luce` | `int` | 40, 5, 60 (impostazioni iniziali) |
| `tipi` | `char[6]` | `V B V L B X` (codice dell'impostazione richiesta) |
| `valori` | `int[6]` | 65, 12, 90, 80, 3, 50 (valore richiesto, parallelo) |

### Output

- I limiti e le impostazioni iniziali.
- Per ogni richiesta: `applicata`, `ridotta al massimo consentito (N)`
  oppure `impostazione sconosciuta, ignorata`.
- Le impostazioni finali.

### Vincoli

- I limiti sono `const int`: il loro indirizzo si può assegnare solo a un
  `const int *`, attraverso il quale si legge ma non si scrive.
- `limita` riceve il valore da correggere come `int *` e il massimo come
  `const int *`: un'istruzione `*massimo = ...` non verrebbe compilata.
- `stampa_impostazioni` riceve `const int *`: può solo leggere.
- Con un codice sconosciuto `impostazione` resta `NULL` e non si scrive
  tramite di esso.
- Un valore uguale al massimo è ammesso; uno maggiore viene ridotto.

### Assunzioni

- I valori richiesti non sono negativi (il minimo non viene controllato).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `impostazione` | `int *` | Impostazione da modificare, `NULL` se il codice è sconosciuto |
| `massimo` | `const int *` | Limite corrispondente, di sola lettura |
| `k` | `int` | Indice della richiesta |
| `RICHIESTE` | `#define` | 6 |

| Funzione | Compito |
|----------|---------|
| `limita(int *valore, const int *massimo)` | Riduce `*valore` al massimo; restituisce 1 se l'ha ridotto |
| `stampa_impostazioni(const int *, const int *, const int *)` | Stampa le impostazioni senza poterle modificare |

### Algoritmo in linguaggio naturale

1. Stampare limiti e impostazioni iniziali.
2. Per ogni richiesta:
   1. porre `impostazione` e `massimo` a `NULL`; secondo il codice (`V`,
      `B`, `L`) farli puntare all'impostazione e al limite corrispondenti;
   2. se `impostazione` è `NULL` segnalare il codice sconosciuto;
   3. altrimenti scrivere il valore in `*impostazione` e chiamare `limita`:
      se `*impostazione > *massimo` la riporta al massimo; stampare l'esito.
3. Stampare le impostazioni finali.

## 3. Casi di test

### Test 1 – Richieste del sorgente

- **Cosa si verifica:** richieste entro i limiti, oltre il massimo e con
  codice sconosciuto.
- **Input:** nessuno (richieste del sorgente).
- **Output atteso:**
  ```
  Limiti dell'istituto: volume 70, bassi 8, luce 100
  Impostazioni attuali: volume 40, bassi 5, luce 60%
  Richiesta V = 65: applicata
  Richiesta B = 12: ridotta al massimo consentito (8)
  Richiesta V = 90: ridotta al massimo consentito (70)
  Richiesta L = 80: applicata
  Richiesta B = 3: applicata
  Richiesta X = 50: impostazione sconosciuta, ignorata
  Impostazioni attuali: volume 70, bassi 3, luce 80%
  ```

### Test 2 – Valore uguale al massimo

- **Cosa si verifica:** il caso limite è ammesso (confronto con `>`).
- **Procedura:** nel sorgente sostituire il primo valore (65) con 70,
  ricompilare ed eseguire.
- **Output atteso:** `Richiesta V = 70: applicata`

### Test 3 – Tentativo di modificare un limite

- **Cosa si verifica:** il `const` è controllato dal compilatore.
- **Procedura:** in `limita` togliere il commento all'istruzione
  `*massimo = *valore;` e ricompilare.
- **Output atteso:** errore di compilazione (assegnamento a una posizione
  di sola lettura); ripristinare il commento.
