# Analisi – 050-problema-targa.c

## 1. Problema

Un sistema di gestione di un parcheggio deve analizzare le targhe dei veicoli
in ingresso per estrarne le componenti (lettere iniziali, cifre centrali,
lettere finali) e verificare che il formato corrisponda allo standard italiano
attuale introdotto nel 1994 (es. `FL519RX`).

---

## 2. Analisi

### Input
Nessun input da tastiera: la targa è una stringa inizializzata nel codice.

| Variabile | Tipo     | Dimensione | Descrizione                      |
|-----------|----------|------------|----------------------------------|
| `targa`   | `char[]` | 8          | 7 caratteri della targa + `'\0'` |

### Output
- La targa e la sua lunghezza; se non è di 7 caratteri, un messaggio di
  errore e nient'altro;
- le tre componenti estratte;
- l'esito della verifica: "VALIDO", oppure l'errore sulle lettere e/o
  sulle cifre;
- per una targa valida: la serie (solo se inizia con F) e il codice ASCII
  delle prime due lettere.

Struttura della targa:
```
Indice:  0    1    2    3    4    5    6    7
         'F'  'L'  '5'  '1'  '9'  'R'  'X'  '\0'
        lett lett  cif  cif  cif lett lett
```

### Vincoli
- La lunghezza si conta fino a `'\0'`; con una lunghezza diversa da 7 non si
  procede con estrazione e verifica
- Le componenti si copiano carattere per carattere in array separati, a cui
  va aggiunto **esplicitamente** il terminatore `'\0'`
- Posizioni 0, 1, 5, 6: lettere maiuscole (`'A'`–`'Z'`); posizioni 2, 3, 4:
  cifre (`'0'`–`'9'`)
- I due errori (lettere e cifre) sono indipendenti e possono comparire
  entrambi

### Assunzioni
- La codifica è ASCII
- Non si verificano le combinazioni di lettere non ammesse dalla
  Motorizzazione

### Variabili di supporto

| Variabile          | Tipo     | Dimensione | Descrizione                           |
|--------------------|----------|------------|---------------------------------------|
| `lettere_iniziali` | `char[]` | 3          | 2 lettere + `'\0'`                    |
| `cifre`            | `char[]` | 4          | 3 cifre + `'\0'`                      |
| `lettere_finali`   | `char[]` | 3          | 2 lettere + `'\0'`                    |
| `lunghezza`        | `int`    | —          | Caratteri fino a `'\0'`               |
| `formato_valido`, `cifre_valide`, `lettere_valide` | `int` | — | Flag, inizialmente 1 |

### Algoritmo in linguaggio naturale
1. Stampare la targa e contarne i caratteri; se non sono 7, segnalare
   l'errore e porre `formato_valido = 0`.
2. Se la lunghezza è corretta:
   a. copiare le tre componenti nei rispettivi array con il terminatore e
      stamparle;
   b. verificare lettere e cifre nelle posizioni previste e stampare l'esito.
3. Se la targa è valida stampare le informazioni aggiuntive.

---

## 3. Casi di test

La targa è fissa nel codice: per ogni test si sostituisce la stringa e si
ricompila.

### Test 1 – Targa valida
- **Input:** `FL519RX`
- **Output atteso:**
```
Componenti estratte:
  Lettere iniziali : FL
  Cifre centrali   : 519
  Lettere finali   : RX

Verifica formato:
  Formato: VALIDO (targa italiana standard dal 1994)

Informazioni aggiuntive:
  Serie FL: sequenza civile normale.
  Valore ASCII 'F': 70
  Valore ASCII 'L': 76
```

### Test 2 – Lunghezza errata
- **Input:** `AB1234`
- **Output atteso:** `Lunghezza targa: 6 caratteri` e
  `ERRORE: la targa non ha il formato corretto (attesi 7 caratteri).`, senza
  componenti né verifica

### Test 3 – Cifra non numerica
- **Input:** `FL51ARX`
- **Output atteso:** `Cifre centrali   : 51A` e
  `ERRORE: le cifre centrali non sono tutte numeriche.`

### Test 4 – Lettere minuscole
- **Input:** `fl519rx`
- **Output atteso:** `ERRORE: le lettere non sono tutte maiuscole.`

### Test 5 – Targa valida che non inizia con F
- **Input:** `AB519CD`
- **Output atteso:** `Formato: VALIDO`, nessuna riga sulla serie, i codici
  ASCII 65 e 66
