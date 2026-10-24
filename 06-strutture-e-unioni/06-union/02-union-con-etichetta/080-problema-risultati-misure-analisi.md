# Analisi – 080-problema-risultati-misure.c

## 1. Problema

Il voltmetro del laboratorio restituisce un valore grezzo; `misura` lo
trasforma in un `Risultato` con tre esiti, ognuno con i suoi dati in una
`union`: valore e incertezza, fondo scala superato, codice di guasto. Il
programma legge il fondo scala e le letture e alla fine stampa la media
delle sole misure riuscite.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `fondo_scala` | `double` | Portata in volt, positiva |
| `parola` | `char[16]` | Lettura grezza; `FINE` termina |

### Output

- Per ogni lettura: `(V +/- I) V`, `Fuori scala: oltre F V, ...`,
  `Guasto: <descrizione> (codice C)`, oppure `Non e' un numero.`
- `Media delle misure riuscite: M V` (se ce ne sono).
- `Riuscite R, fuori scala F, guasti G`.
- `Fondo scala non valido.`

### Vincoli

- Lettura negativa = guasto con codice intero (−1 cavo staccato, −2
  batteria scarica, altri: errore sconosciuto).
- Lettura oltre il fondo scala = fuori scala; altrimenti misura riuscita
  con incertezza 1% + 0.01 V.
- `stampa` usa uno `switch` sull'esito e legge solo il membro della union
  corrispondente.
- I conteggi sono indicizzati dall'esito.
- A fine input il programma termina come con `FINE`.

### Assunzioni

- Il valore 0 è una misura valida.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Esito` | `typedef enum { MISURA_OK, FUORI_SCALA, GUASTO, NUM_ESITI } Esito;` | Etichetta |
| `Risultato` | struct con `esito` e `union { struct { double valore; double incertezza; } ok; double fondo_scala; int codice; } dati` | Risultato della misura |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `conteggi` | `int[3]` | Risultati per esito |
| `somma` | `double` | Somma delle misure riuscite |
| `r` | `Risultato` | Ultima misura |

| Funzione | Compito |
|----------|---------|
| `misura(letto, fondo_scala)` | Costruisce il risultato |
| `stampa(r)` | Stampa con `switch` sull'esito |

### Algoritmo in linguaggio naturale

1. Leggere il fondo scala; se non valido segnalarlo e non leggere misure.
2. Finché non si termina: leggere una parola; se non è un numero
   segnalarlo; altrimenti costruire il risultato, stamparlo, contarlo e,
   se riuscito, sommarlo.
3. Stampare la media (se ci sono misure riuscite) e i conteggi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Serie di letture

- **Input:** `20`, `12.5`, `3`, `25`, `-1`, `-2`, `-7`, `volt`, `0`, `FINE`
- **Valori intermedi attesi:** incertezza di 12.5: 0.125 + 0.01 = 0.135;
  media (12.5 + 3 + 0) / 3 = 5.167.
- **Output atteso:**
  ```
    (12.500 +/- 0.135) V
    (3.000 +/- 0.040) V
    Fuori scala: oltre 20.0 V, scegliere una portata piu' alta.
    Guasto: cavo staccato (codice -1)
    Guasto: batteria scarica (codice -2)
    Guasto: errore sconosciuto (codice -7)
    Non e' un numero.
    (0.000 +/- 0.010) V
  Media delle misure riuscite: 5.167 V
  Riuscite 3, fuori scala 1, guasti 3
  ```

### Test 2 – Nessuna misura riuscita

- **Input:** `20`, `30`, poi fine input
- **Output atteso:** nessuna media; `Riuscite 0, fuori scala 1, guasti 0`.

### Test 3 – Fondo scala non valido

- **Input:** `0`
- **Output atteso:** `Fondo scala non valido.` e
  `Riuscite 0, fuori scala 0, guasti 0`.
