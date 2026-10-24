# Analisi – 060-problema-filtra-misure.c

## 1. Problema

Un sensore misura la CO2 in aula; alcune letture sono errori (sotto 300 o
sopra 5000 ppm) e da 1000 ppm in su bisogna aprire le finestre. La
funzione `filtra` restituisce un nuovo array, allocato con `malloc`, con
le sole misure in un intervallo e ne comunica la lunghezza con un
parametro di uscita. Il programma filtra due volte e libera i tre blocchi.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `n` | `int` | Numero di letture, da 1 a 144 |
| `letture[i]` | `double` | Valori in ppm |

### Output

- Tre righe `titolo (N): valori  media M` (oppure `nessuna`): tutte le
  letture, quelle valide, quelle da almeno 1000 ppm.
- `Scartate per errore del sensore: K`.
- `Numero non valido.`, `Memoria insufficiente.`,
  `Letture mancanti: ne servono N.`

### Vincoli

- `filtra` conta prima gli elementi da tenere, poi alloca esattamente
  quel numero; con 0 elementi restituisce `NULL` e lunghezza 0 (non è un
  errore di memoria).
- Valide: da 300 a 5000 ppm compresi; finestre: da 1000 a 5000.
- Il secondo filtro lavora sull'array delle valide.
- I tre blocchi si liberano alla fine (`free(NULL)` è ammesso).

### Assunzioni

- Le letture sono separate da spazi o a capo.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `letture`, `valide`, `alte` | `double *` | I tre blocchi |
| `n`, `n_valide`, `n_alte` | `int` | Lunghezze |
| `letti` | `int` | Letture inserite |

| Funzione | Compito |
|----------|---------|
| `filtra(misure, n, minimo, massimo, &quante)` | Nuovo array con i valori nell'intervallo |
| `stampa(titolo, v, n)` | Valori e media |

### Algoritmo in linguaggio naturale

1. Leggere n e allocare le letture; leggerle (se mancano segnalarlo).
2. Stampare tutte le letture; filtrare le valide e stamparle con il numero
   di scartate; filtrare le valide da almeno 1000 ppm e stamparle.
3. Liberare i tre blocchi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Mattina in aula

- **Input:** `8`, `450 1200 250 980 1500 6200 1000 720`
- **Output atteso:**
  ```
  Numero di letture (da 1 a 144): Letture in ppm: Tutte le letture (8): 450 1200 250 980 1500 6200 1000 720  media 1538
  Letture valide (6): 450 1200 980 1500 1000 720  media 975
  Scartate per errore del sensore: 2
  Almeno 1000 ppm (aprire le finestre) (3): 1200 1500 1000  media 1233
  ```

### Test 2 – Nessuna lettura valida

- **Input:** `3`, `200 100 6000`
- **Output atteso:** `Letture valide (0): nessuna`, scartate 3,
  `Almeno 1000 ppm (aprire le finestre) (0): nessuna`.

### Test 3 – Letture mancanti

- **Input:** `3`, `400 x`
- **Output atteso:** `Letture mancanti: ne servono 3.`
