# Analisi – 060-problema-conta-vocali.c

## 1. Problema

Un'applicazione di analisi linguistica riceve un testo in input e calcola
la distribuzione delle vocali (a, e, i, o, u), contando le occorrenze di
ciascuna indipendentemente dal case, e mostra una barra di distribuzione
testuale e la densità vocalica percentuale.

---

## 2. Analisi generale e struttura dati

| Variabile          | Tipo     | Dimensione | Motivazione                                          |
|--------------------|----------|------------|------------------------------------------------------|
| `testo`            | `char[]` | 201        | Testo con spazi, max 200 caratteri + `'\0'`          |
| `conta_a`..`conta_u`| `int`  | —          | Un contatore per ciascuna delle 5 vocali             |
| `totale_vocali`    | `int`    | —          | Somma di tutti i contatori vocali                    |
| `totale_caratteri` | `int`    | —          | Numero totale di caratteri nel testo                 |
| `c`                | `char`   | —          | Carattere corrente durante la scansione              |
| `i`                | `int`    | —          | Indice per scorrere il testo                         |
| `barra`            | `int`    | —          | Contatore per il ciclo della barra di distribuzione  |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Lettura del testo

**a) Input**
Testo con spazi, punteggiatura e lettere (max 200 caratteri).

**b) Output**
Nessun output diretto: testo memorizzato in `testo` senza `'\n'`.

**c) Variabili di supporto**
- `i` (`int`): indice per rimozione `'\n'`.

**d) Vincoli**
- `fgets` è usato per permettere spazi nel testo.
- Il `'\n'` finale va rimosso prima della scansione.

**e) Assunzioni**
- Non sono gestite lettere accentate (à, è, ecc.).
- Il testo può contenere cifre, punteggiatura e spazi.

**f) Algoritmo in linguaggio naturale**
```
1. Leggere il testo con fgets(testo, 201, stdin).
2. Scorrere con while finché non si trova '\n' o '\0'.
3. Sostituire il carattere corrente con '\0'.
```

---

### Caso d'uso 2 – Scansione e conteggio vocali

**a) Input**
La stringa `testo` dopo la pulizia.

**b) Output**
Nessun output diretto: aggiorna i contatori delle vocali e il totale.

**c) Variabili di supporto**
- `c` (`char`): carattere corrente.
- `i` (`int`): indice di scansione.
- `conta_a`, `conta_e`, `conta_i`, `conta_o`, `conta_u` (`int`).
- `totale_vocali`, `totale_caratteri` (`int`).

**d) Vincoli**
- Il ciclo si ferma al `'\0'` terminatore.
- Ogni carattere incrementa sempre `totale_caratteri`.
- Solo le vocali (maiuscole o minuscole) incrementano il contatore
  specifico e `totale_vocali`.

**e) Assunzioni**
- Le vocali considerate sono solo a, e, i, o, u senza accenti.
- Maiuscole e minuscole sono conteggiate nello stesso contatore.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare tutti i contatori a 0 e i a 0.
2. Finché testo[i] non è '\0':
   a. c = testo[i]; incrementare totale_caratteri.
   b. Se c è 'a' o 'A': incrementare conta_a e totale_vocali.
   c. Altrimenti se c è 'e' o 'E': incrementare conta_e e totale_vocali.
   d. Altrimenti se c è 'i' o 'I': incrementare conta_i e totale_vocali.
   e. Altrimenti se c è 'o' o 'O': incrementare conta_o e totale_vocali.
   f. Altrimenti se c è 'u' o 'U': incrementare conta_u e totale_vocali.
   g. Incrementare i.
```

---

### Caso d'uso 3 – Output con barra di distribuzione

**a) Input**
I cinque contatori, `totale_vocali`, `totale_caratteri`.

**b) Output**
```
════════════════════════════════════════════
  DISTRIBUZIONE VOCALI
════════════════════════════════════════════
Vocale Num.  Distribuzione
--------------------------------------------
  A/a :   3  [###]
  E/e :   5  [#####]
  I/i :   2  [##]
  O/o :   4  [####]
  U/u :   1  [#]
--------------------------------------------
  Totale vocali    : 15 su 42 caratteri
  Densità vocalica : 35%
════════════════════════════════════════════
```

**c) Variabili di supporto**
- `barra` (`int`): contatore per il ciclo `while` che stampa i `'#'`.

**d) Vincoli**
- La barra viene generata con un ciclo `while` su `putchar('#')`.
- La percentuale è calcolata solo se `totale_caratteri > 0`
  per evitare divisione per zero.

**e) Assunzioni**
- Non c'è un limite massimo alla lunghezza della barra
  (rispecchia il conteggio reale senza normalizzazione).

**f) Algoritmo in linguaggio naturale**
```
1. Per ogni vocale (A, E, I, O, U):
   a. Stampare il nome della vocale e il contatore.
   b. Inizializzare barra a 0.
   c. Finché barra < contatore: stampare '#'; incrementare barra.
   d. Chiudere la barra con ']'.
2. Stampare totale vocali e totale caratteri.
3. Se totale_caratteri > 0: stampare la densità percentuale.
```
