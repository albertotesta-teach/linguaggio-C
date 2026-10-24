# Analisi – 040-problema-ricette-americane.c

## 1. Problema

Nel laboratorio di cucina le ricette americane usano tazze (cup),
cucchiai (tbsp), once (oz), libbre (lb) e gradi Fahrenheit (F). Lo
studente scrive la quantità e la sigla dell'unità; il programma risponde
con la quantità nel sistema metrico. Ogni conversione è una funzione e le
funzioni stanno in una tabella di tipo `Conversione`, parallela alle sigle.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `quantita` | `double` | Quantità da convertire; 0 termina |
| `sigla` | `char[10]` | Sigla dell'unità: `cup`, `tbsp`, `oz`, `lb`, `F` |

### Output

- L'elenco delle unità riconosciute.
- Per ogni riga: `Q sigla = R unità` con un decimale, oppure
  `Unita' "x" sconosciuta.` o `Quantita' non valida.`

### Vincoli

- `typedef double (*Conversione)(double);`
- Fattori: 1 cup = 236.6 ml, 1 tbsp = 14.8 ml, 1 oz = 28.35 g,
  1 lb = 453.6 g, C = (F − 32) × 5 / 9.
- La sigla si cerca con `strcmp` (maiuscole e minuscole contano); la sua
  posizione è l'indice della funzione da chiamare.
- La sigla si legge con `%9s`; il resto della riga viene scartato.
- Una quantità non numerica viene segnalata e la riga scartata; a fine
  input il programma termina come con 0.

### Assunzioni

- Le quantità negative sono ammesse (servono per i gradi Fahrenheit).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Conversione` | `typedef double (*Conversione)(double);` | Puntatore a una funzione di conversione |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `sigle`, `arrivo` | `const char *[5]` | Sigle e unità di arrivo |
| `converti` | `Conversione[5]` | Tabella delle funzioni |
| `letti` | `int` | Valore restituito da `scanf` |
| `k` | `int` | Indice della sigla trovata |

| Funzione | Compito |
|----------|---------|
| `da_tazze`, `da_cucchiai`, `da_once`, `da_libbre`, `da_fahrenheit` | Le cinque conversioni |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Stampare le unità riconosciute.
2. Finché la quantità non è 0:
   1. leggere la quantità (fine input → 0; testo → segnalare e scartare la
      riga);
   2. se diversa da 0 leggere la sigla e scartare il resto della riga;
   3. cercare la sigla: se trovata chiamare `converti[k](quantita)` e
      stampare il risultato, altrimenti segnalare l'unità sconosciuta.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Tutte le unità e gli errori

- **Cosa si verifica:** le cinque conversioni, una temperatura negativa,
  un'unità sconosciuta, una quantità non numerica, una sigla troppo lunga.
- **Input:** `2 cup`, `3 tbsp`, `8 oz`, `1.5 lb`, `350 F`, `-4 F`, `2 kg`,
  `abc`, `2 cupxxxxxxxxxxxxxxx`, `0`
- **Valori intermedi attesi:** (350 − 32) × 5 / 9 = 176.67;
  (−4 − 32) × 5 / 9 = −20.
- **Output atteso:**
  ```
  Unita' riconosciute: cup tbsp oz lb F
    2 cup = 473.2 ml
    3 tbsp = 44.4 ml
    8 oz = 226.8 g
    1.5 lb = 680.4 g
    350 F = 176.7 gradi C
    -4 F = -20.0 gradi C
    Unita' "kg" sconosciuta.
    Quantita' non valida.
    Unita' "cupxxxxxx" sconosciuta.
  ```
  (della sigla troppo lunga si leggono solo i primi 9 caratteri).

### Test 2 – Sigla con la maiuscola sbagliata

- **Input:** `2 CUP`, `0`
- **Output atteso:** `Unita' "CUP" sconosciuta.`
