# Analisi – 060-problema-conta-vocali.c

## 1. Problema

Un'applicazione di analisi linguistica riceve un testo in input e calcola
la distribuzione delle vocali (a, e, i, o, u), contando le occorrenze di
ciascuna indipendentemente dal case, e mostra una barra di distribuzione
testuale e la densità vocalica percentuale.

---

## 2. Analisi

### Input

| Variabile | Tipo     | Dimensione | Descrizione                          |
|-----------|----------|------------|--------------------------------------|
| `testo`   | `char[]` | 201        | Testo con spazi, max 200 caratteri   |

### Output
- Il testo analizzato;
- per ogni vocale il numero di occorrenze e una barra con un `#` per
  occorrenza;
- il totale delle vocali sul totale dei caratteri e la densità vocalica in
  percentuale (intera), solo se il testo non è vuoto.

### Vincoli
- Maiuscole e minuscole della stessa vocale si contano insieme
- Il totale dei caratteri comprende anche spazi e punteggiatura
- La densità è `vocali × 100 / caratteri` con divisione intera, e si calcola
  solo se i caratteri sono più di 0, per evitare la divisione per zero
- Le cinque condizioni si escludono a vicenda (`else if`): un carattere
  incrementa al massimo un contatore

### Assunzioni
- Le vocali accentate (à, è, …) non sono contate

### Variabili di supporto

| Variabile            | Tipo   | Descrizione                         |
|----------------------|--------|-------------------------------------|
| `conta_a` … `conta_u`| `int`  | Un contatore per vocale             |
| `totale_vocali`, `totale_caratteri` | `int` | Totali              |
| `c`                  | `char` | Carattere corrente                  |
| `i`, `barra`         | `int`  | Indici di scorrimento e della barra |

### Algoritmo in linguaggio naturale
1. Leggere il testo e rimuovere il `'\n'`.
2. Per ogni carattere: contarlo nel totale; se è una vocale (maiuscola o
   minuscola) incrementarne il contatore e il totale delle vocali.
3. Per ogni vocale stampare il conteggio e tanti `#` quanto vale.
4. Stampare i totali e, se il testo non è vuoto, la densità.

---

## 3. Casi di test

Per ogni caso si inserisce il testo indicato.

### Test 1 – Frase tipica
- **Input:** `Il gatto mangia la pizza`
- **Output atteso:**
```
  A/a :   5  [#####]
  E/e :   0  []
  I/i :   3  [###]
  O/o :   1  [#]
  U/u :   0  []
--------------------------------------------
  Totale vocali    : 9 su 24 caratteri
  Densità vocalica : 37%
```
- **Osservazione:** la "I" maiuscola iniziale è contata con le minuscole

### Test 2 – Testo senza vocali
- **Input:** `Psst, brr!`
- **Output atteso:** `Totale vocali    : 0 su 10 caratteri` e
  `Densità vocalica : 0%`

### Test 3 – Testo vuoto
- **Cosa si verifica:** la densità non viene calcolata
- **Input:** solo Invio
- **Output atteso:** `Totale vocali    : 0 su 0 caratteri`, senza la riga
  della densità
