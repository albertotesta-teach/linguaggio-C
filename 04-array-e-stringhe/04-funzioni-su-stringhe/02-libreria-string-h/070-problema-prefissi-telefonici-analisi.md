# Analisi – 070-problema-prefissi-telefonici.c

## 1. Problema

Il centralino di un'azienda registra le chiamate in uscita (numero in
formato internazionale e durata in minuti). Il tariffario associa a ogni
prefisso una zona e un costo al minuto. Il programma deve riconoscere la
zona di ogni chiamata, calcolarne il costo, sommare minuti e costi per zona
e segnalare le chiamate verso prefissi non in tariffario.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `prefissi` | `char[8][6]` | Prefissi del tariffario: `+39`, `+393`, `+33`, `+34`, `+41`, `+44`, `+49`, `+1` |
| `zone` | `char[8][16]` | Nome della zona di ogni prefisso (parallelo) |
| `tariffe` | `int[8]` | Costo in centesimi al minuto (parallelo) |
| `numeri` | `char[9][20]` | Numeri chiamati |
| `minuti` | `int[9]` | Durata di ogni chiamata (parallelo a `numeri`) |

I dati sono inizializzati nel sorgente: il programma non legge nulla da tastiera.

### Output

- Tabella di dettaglio: numero, zona, minuti e costo di ogni chiamata
  (zona `?` e costo `-` se il prefisso non è in tariffario).
- Totale minuti e costo per ogni zona con almeno una chiamata.
- Totale da addebitare in euro.
- Numero di chiamate con prefisso non in tariffario, da verificare.

### Vincoli

- I costi si calcolano in centesimi (interi) e si stampano in euro con due decimali.
- Il confronto del prefisso si fa con `strncmp` sui primi `strlen(prefisso)` caratteri.
- Se un numero inizia con più prefissi (es. `+39` e `+393`) vince il più lungo.
- Le chiamate non riconosciute non entrano nei totali.

### Assunzioni

- I numeri sono scritti senza spazi e iniziano con `+`.
- Nessun prefisso compare due volte nel tariffario.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `minuti_zona` | `int[8]` | Minuti totali per zona (parallelo a `prefissi`) |
| `totale` | `int` | Costo totale in centesimi |
| `sconosciute` | `int` | Chiamate con prefisso non in tariffario |
| `z` | `int` | Indice della zona della chiamata corrente (-1 se sconosciuta) |
| `costo` | `int` | Costo in centesimi della chiamata o della zona |
| `migliore`, `lung` | `int` | In `cerca_zona`: indice e lunghezza del prefisso più lungo trovato |

| Funzione | Compito |
|----------|---------|
| `cerca_zona` | Restituisce l'indice del prefisso più lungo con cui inizia il numero, oppure -1 |

### Algoritmo in linguaggio naturale

1. Azzerare `minuti_zona`, `totale` e `sconosciute`.
2. Per ogni chiamata:
   1. trovare la zona con `cerca_zona`: per ogni prefisso, se il numero
      inizia con quel prefisso ed esso è più lungo del migliore trovato
      finora, ricordarne indice e lunghezza;
   2. se la zona è -1, stampare `?` e `-` e incrementare `sconosciute`;
   3. altrimenti costo = minuti × tariffa, aggiungere i minuti a
      `minuti_zona[z]` e il costo a `totale`, stampare la riga.
3. Per ogni zona con `minuti_zona[z] > 0` stampare minuti e costo.
4. Stampare il totale in euro (`totale / 100.0`).
5. Se `sconosciute > 0` stampare l'avviso.

## 3. Casi di test

### Test 1 – Prefisso semplice

- **Cosa si verifica**: riconoscimento di un prefisso senza ambiguità e calcolo del costo.
- **Input**: chiamata `+33142685300`, 8 minuti (dati del sorgente).
- **Valori intermedi attesi**: `z` = indice di `+33` (Francia, 9 cent/min), `costo` = 8 × 9 = 72.
- **Output atteso**:
  ```
    +33142685300    Francia            8      0.72
  ```

### Test 2 – Prefissi sovrapposti

- **Cosa si verifica**: tra `+39` e `+393` viene scelto il prefisso più lungo.
- **Input**: chiamate `+393471234567` (5 min) e `+390131220145` (12 min).
- **Valori intermedi attesi**: per il primo numero entrambi i prefissi
  corrispondono, `lung` passa da 3 a 4 e `migliore` = indice di `+393`;
  per il secondo il quarto carattere è `0`, quindi solo `+39` corrisponde.
- **Output atteso**:
  ```
    +390131220145   Italia fisso      12      0.24
    +393471234567   Italia mobile      5      0.25
  ```

### Test 3 – Prefisso a una cifra

- **Cosa si verifica**: un prefisso corto (`+1`) viene riconosciuto senza confonderlo con altri.
- **Input**: chiamata `+12125550198`, 15 minuti.
- **Valori intermedi attesi**: `z` = indice di `+1` (18 cent/min), `costo` = 270.
- **Output atteso**:
  ```
    +12125550198    USA/Canada        15      2.70
  ```

### Test 4 – Prefisso sconosciuto

- **Cosa si verifica**: una chiamata verso un prefisso non in tariffario
  non entra nei totali e viene segnalata.
- **Input**: chiamata `+81312345678`, 10 minuti.
- **Valori intermedi attesi**: `cerca_zona` restituisce -1, `sconosciute` = 1.
- **Output atteso**:
  ```
    +81312345678    ?                 10         -
  ```
  e in fondo:
  ```
    1 chiamata con prefisso non in tariffario: da verificare
  ```

### Test 5 – Totali per zona ed esecuzione completa

- **Cosa si verifica**: somma per zona, esclusione delle zone senza chiamate
  (Spagna, Regno Unito) e totale generale.
- **Input**: dati del sorgente (9 chiamate).
- **Valori intermedi attesi**: `minuti_zona` di Italia fisso = 12 + 25 = 37;
  di Italia mobile = 5 + 3 = 8; `totale` = 810 centesimi.
- **Output atteso**:
  ```
    Numero          Zona             Min     Costo
    +390131220145   Italia fisso      12      0.24
    +393471234567   Italia mobile      5      0.25
    +33142685300    Francia            8      0.72
    +41223456789    Svizzera          20      3.00
    +12125550198    USA/Canada        15      2.70
    +393289876543   Italia mobile      3      0.15
    +81312345678    ?                 10         -
    +4930123456     Germania           6      0.54
    +390112345678   Italia fisso      25      0.50

  === TOTALE PER ZONA ===
    Italia fisso     37 min    0.74 euro
    Italia mobile     8 min    0.40 euro
    Francia           8 min    0.72 euro
    Svizzera         20 min    3.00 euro
    Germania          6 min    0.54 euro
    USA/Canada       15 min    2.70 euro
    Totale da addebitare: 8.10 euro
    1 chiamata con prefisso non in tariffario: da verificare
  ```
