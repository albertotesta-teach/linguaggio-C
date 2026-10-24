# Analisi – 040-problema-voti-della-verifica.c

## 1. Problema

Il professore inserisce il numero di studenti presenti alla verifica e i
loro voti. Il programma calcola la media, conta i voti sopra la media,
elenca le insufficienze e trova il voto più alto e il più basso. Per
confrontare ogni voto con la media servono due passate, quindi i voti
vanno conservati: l'array si alloca con `malloc` dopo aver letto n, grande
esattamente n voti.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `n` | `int` | Studenti presenti, da 1 a 40 |
| `voti[i]` | `double` | Voto di ogni studente, da 1 a 10, anche mezzo voto |

### Output

- `voto non valido (da 1 a 10, anche mezzi voti)` per ogni voto da
  ripetere.
- `Media della classe: M`, `Insufficienze:` con studente e voto (oppure
  `nessuna`), `Sopra la media: S su n`, `Voto piu' alto: A, piu' basso: B`.
- `Numero non valido.`, `Memoria insufficiente.`, oppure
  `Input terminato: mancano K voti.` (`manca 1 voto`).

### Vincoli

- `voti = malloc(n * sizeof *voti)`: la dimensione si conosce solo
  durante l'esecuzione; si controlla che `malloc` non restituisca `NULL`.
- Il blocco si libera con `free` in ogni caso (anche `free(NULL)` è
  corretto).
- Voto valido: da 1 a 10 e multiplo di 0.5 (`voto * 2` intero); un voto
  non numerico viene scartato con il resto della riga.
- Sopra la media: strettamente maggiore; insufficiente: minore di 6.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `voti` | `double *` | Blocco di n voti allocato dinamicamente |
| `letti` | `int` | Voti validi inseriti |
| `somma`, `media` | `double` | Prima passata |
| `sopra`, `insufficienti` | `int` | Contatori della seconda passata |
| `massimo`, `minimo` | `double` | Estremi |
| `MAX_STUDENTI` | `#define` | 40 |

| Funzione | Compito |
|----------|---------|
| `leggi_voto(studente, voto)` | Chiede il voto finché non è valido; 0 a fine input |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Leggere n; se non valido segnalarlo.
2. Allocare n `double`; se non riesce segnalarlo.
3. Leggere i voti sommandoli; se l'input finisce prima, dire quanti
   mancano.
4. Altrimenti calcolare la media e, in una seconda passata, contare i voti
   sopra la media, stampare le insufficienze e trovare massimo e minimo.
5. Liberare la memoria.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Sei studenti con voti da ripetere

- **Input:** `6`, `7`, `5.5`, `abc def`, `11`, `6.3`, `8`, `4`, `9.5`, `6`
- **Valori intermedi attesi:** voti 7, 5.5, 8, 4, 9.5, 6; somma 40, media
  6.67; sopra la media 7, 8, 9.5.
- **Output atteso:**
  ```
    voto non valido (da 1 a 10, anche mezzi voti)
    voto non valido (da 1 a 10, anche mezzi voti)
    voto non valido (da 1 a 10, anche mezzi voti)

  Media della classe: 6.67
  Insufficienze:
    studente  2: 5.5
    studente  4: 4.0
  Sopra la media: 3 su 6
  Voto piu' alto: 9.5, piu' basso: 4.0
  ```

### Test 2 – Input incompleto

- **Input:** `3`, `7`, `8`, poi fine input; poi `3`, `7`, fine input
- **Output atteso:** `Input terminato: manca 1 voto.`; poi
  `Input terminato: mancano 2 voti.`

### Test 3 – Numero non valido

- **Input:** `0` (poi `41`, `abc`)
- **Output atteso:** `Numero non valido.`
