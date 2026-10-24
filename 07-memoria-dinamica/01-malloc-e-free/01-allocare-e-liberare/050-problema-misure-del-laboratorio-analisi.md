# Analisi – 050-problema-misure-del-laboratorio.c

## 1. Problema

Ogni gruppo di fisica misura più volte il periodo di un pendolo. Il numero
di misure cambia da gruppo a gruppo: l'array si alloca con `malloc` dopo
averlo letto. Il programma calcola media e scarto quadratico medio,
segnala le misure che distano dalla media più di due scarti e ricalcola la
media senza di esse.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `n` | `int` | Numero di misure, da 3 a 1000 |
| `periodo[i]` | `double` | Periodi in secondi, positivi, separati da spazi o a capo |

### Output

- `misura K non valida, ripetere` per ogni valore da ripetere.
- `Media: M s   scarto: S s`.
- `Misure anomale (oltre 2S s dalla media):` con le misure anomale oppure
  `nessuna`; se ce ne sono, `Media senza anomalie: M' s (V misure)`.
- `Numero non valido.`, `Memoria insufficiente.`,
  `Input terminato: mancano K misure.` (`manca 1 misura`).

### Vincoli

- `periodo = malloc(n * sizeof *periodo)`, con controllo di `NULL` e
  `free` finale.
- Scarto quadratico medio campionario: √(Σ(xᵢ − media)² / (n − 1)).
- Anomala: |xᵢ − media| > 2 scarti.
- Una parola non numerica o un valore non positivo vengono scartati e la
  stessa misura viene richiesta (le altre misure sulla riga restano
  valide).
- Si compila con `-lm`.

### Assunzioni

- Le misure appartengono allo stesso pendolo.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `periodo` | `double *` | Blocco di n misure |
| `letti` | `int` | Misure valide |
| `esito`, `fine` | `int` | Lettura e fine input |
| `somma`, `somma_quadrati`, `somma_valide` | `double` | Accumulatori |
| `media`, `scarto` | `double` | Statistiche |
| `valide` | `int` | Misure non anomale |

### Algoritmo in linguaggio naturale

1. Leggere n e allocare l'array.
2. Leggere le misure, ripetendo quelle non valide; a fine input segnalare
   quante mancano.
3. Calcolare la media, poi lo scarto con una seconda passata.
4. Stampare le misure anomale e, se ci sono, la media delle altre.
5. Liberare la memoria.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Una misura anomala

- **Input:** `8`, poi `2.01 1.98 2.03`, `2.00 abc 1.99`,
  `2.45 -1 2.02 1.97`
- **Valori intermedi attesi:** media 16.45 / 8 = 2.056; scarto 0.160;
  |2.45 − 2.056| = 0.394 > 0.321.
- **Output atteso:**
  ```
  Numero di misure (da 3 a 1000): Periodi misurati in secondi:
    misura 5 non valida, ripetere
    misura 7 non valida, ripetere

  Media: 2.056 s   scarto: 0.160 s
  Misure anomale (oltre 0.321 s dalla media):
    misura 6: 2.450 s
  Media senza anomalie: 2.000 s (7 misure)
  ```

### Test 2 – Misure identiche

- **Input:** `5`, `2.0 2.0 2.0 2.0 2.0`
- **Output atteso:** scarto 0.000 e `nessuna` misura anomala.

### Test 3 – Input incompleto e numero non valido

- **Input:** `4`, `2 2`, fine input; poi `2`
- **Output atteso:** `Input terminato: mancano 2 misure.`; poi
  `Numero non valido.`
