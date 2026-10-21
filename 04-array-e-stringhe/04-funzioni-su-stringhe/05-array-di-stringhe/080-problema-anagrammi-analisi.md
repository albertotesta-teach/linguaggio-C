# Analisi – 080-problema-anagrammi.c

## 1. Problema

Per un gioco di parole bisogna trovare, in un elenco, gli anagrammi di una
parola data: parole con le stesse lettere ripetute lo stesso numero di
volte, in un altro ordine. Maiuscole e caratteri non alfabetici non contano;
la parola stessa non è considerata un suo anagramma.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `parola` | `char[30]` | Parola letta da tastiera; una riga vuota termina |
| `elenco` | `char[12][20]` | Parole tra cui cercare (nel sorgente) |

### Output

- Gli anagrammi trovati nell'elenco, uno per riga, scritti come nell'elenco.
- `-> N anagramma/anagrammi di "<parola>"`.

### Vincoli

- Due parole sono anagrammi se hanno la stessa "impronta": il numero di
  occorrenze di ciascuna delle 26 lettere.
- Si contano solo le lettere (`isalpha`), senza distinguere maiuscole e
  minuscole: la lettera `c` corrisponde alla cella `tolower(c) - 'a'`.
- La parola stessa (anche scritta con maiuscole diverse) non è un suo anagramma.
- Il confronto delle impronte si ferma alla prima cella diversa (flag `uguali`).

### Assunzioni

- Le parole non contengono lettere accentate.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `letta` | `int` | 1 se la lettura è riuscita |
| `k` | `int` | Indice della parola dell'elenco in esame |
| `trovati` | `int` | Anagrammi trovati |
| `conta_a`, `conta_b` | `int[26]` | In `sono_anagrammi`: impronte delle due parole |
| `uguali` | `int` | In `sono_anagrammi`: flag di impronte uguali |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Legge una riga e toglie il `'\n'` |
| `conta_lettere` | Azzera e riempie l'impronta con `isalpha` e `tolower` |
| `sono_anagrammi` | Confronta le impronte ed esclude la stessa parola |
| `uguali_senza_maiuscole` | Confronto di due stringhe con `tolower` |

### Algoritmo in linguaggio naturale

1. Leggere una parola.
2. Finché la lettura riesce e la parola non è vuota:
   1. azzerare `trovati`;
   2. per ogni parola dell'elenco: calcolare le due impronte, confrontarle
      cella per cella fermandosi alla prima diversa; se sono uguali e le due
      parole non coincidono (ignorando le maiuscole) stamparla e
      incrementare `trovati`;
   3. stampare il numero di anagrammi;
   4. leggere la parola successiva.

## 3. Casi di test

### Test 1 – Più anagrammi, anche con maiuscole

- **Cosa si verifica**: impronte uguali con lettere in ordine diverso e con
  maiuscole diverse (`Mora`).
- **Input**: `Roma`, poi riga vuota.
- **Valori intermedi attesi**: impronta con una sola occorrenza di a, m, o, r.
- **Output atteso**:
  ```
    amor
    ramo
    Mora
    orma
    armo
    -> 5 anagrammi di "Roma"
  ```

### Test 2 – La parola stessa

- **Cosa si verifica**: `tale` ha la stessa impronta di `Tale` ma è esclusa.
- **Input**: `Tale`, poi riga vuota.
- **Output atteso**:
  ```
    tela
    -> 1 anagramma di "Tale"
  ```

### Test 3 – Lettere ripetute

- **Cosa si verifica**: contano anche le ripetizioni (due `t`).
- **Input**: `attore`, poi riga vuota.
- **Output atteso**:
  ```
    teatro
    rotate
    -> 2 anagrammi di "attore"
  ```

### Test 4 – Nessun anagramma

- **Cosa si verifica**: una parola presente nell'elenco ma senza altri anagrammi.
- **Input**: `lieto`, poi riga vuota.
- **Valori intermedi attesi**: con `lieto` dell'elenco le impronte sono
  uguali ma la parola è la stessa; con `toilette` le impronte differiscono.
- **Output atteso**:
  ```
    -> 0 anagrammi di "lieto"
  ```

### Test 5 – Caratteri non alfabetici

- **Cosa si verifica**: lo spazio non conta nell'impronta.
- **Input**: `LA TTE`, poi `latte`, poi riga vuota.
- **Output atteso**:
  ```
    latte
    -> 1 anagramma di "LA TTE"
    -> 0 anagrammi di "latte"
  ```
- **Osservazione**: `LA TTE` e `latte` hanno la stessa impronta e il
  confronto che esclude la parola stessa li considera diversi per lo
  spazio, quindi `latte` è riportato come anagramma.
