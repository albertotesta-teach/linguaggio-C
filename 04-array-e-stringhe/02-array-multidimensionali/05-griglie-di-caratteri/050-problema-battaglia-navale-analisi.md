# Analisi – 050-problema-battaglia-navale.c

## 1. Problema

Realizzare una battaglia navale in solitario su una griglia 6 × 8. La flotta
è nascosta; il giocatore indica una cella con una lettera (riga A–F) e un
numero (colonna 1–8) e il programma risponde "Colpito" o "Acqua",
mostrando la griglia dei tiri. Il giocatore ha 20 colpi; una cella già colpita
o inesistente non consuma colpi. La partita termina quando tutte le parti di
nave sono state colpite o quando i colpi sono finiti.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `flotta` | `char[][]` | 6 × (8 + 1) | Griglia segreta: `'N'` nave, `'.'` mare |
| `tiri` | `char[][]` | 6 × (8 + 1) | Griglia visibile: `'?'`, `'O'` acqua, `'X'` colpita |
| `lettera`, `colonna_utente` | `char`, `int` | — | Coordinate inserite |
| `r`, `c` | `int` | — | Indici calcolati: `lettera - 'A'`, `colonna_utente - 1` |
| `colpi_rimasti`, `da_affondare` | `int` | — | Condizioni di fine partita |

Le due griglie hanno la stessa dimensione e sono **parallele**: la stessa
coppia di indici descrive la stessa cella in entrambe.

| Funzione | Compito |
|----------|---------|
| `inizializza_tiri` | Riempie `tiri` di `'?'` e scrive il `'\0'` di ogni riga |
| `stampa_griglia` | Stampa una griglia con lettere e numeri delle coordinate |
| `conta_celle` | Conta le celle che contengono un simbolo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tiro valido

**a) Input** – una cella non ancora colpita, es. `C 3`

**b) Output** – "COLPITO!" oppure "Acqua." e la griglia dei tiri

**c) Variabili di supporto** – `r`, `c`

**d) Vincoli** – il colpo si consuma solo qui

**e) Assunzioni** – la lettera è maiuscola

**f) Algoritmo in linguaggio naturale**
1. Convertire la lettera in indice di riga (`lettera - 'A'`) e il numero in
   indice di colonna (`numero - 1`).
2. Decrementare `colpi_rimasti`.
3. Se `flotta[r][c]` è una nave: scrivere `'X'` in `tiri` e decrementare
   `da_affondare`; altrimenti scrivere `'O'`.

### Caso d'uso 2 – Cella inesistente o già colpita

**a) Input** – `Z 3` oppure una cella già tentata

**b) Output** – "Cella inesistente." / "Cella gia' colpita."

**c) Variabili di supporto** – `tiri[r][c] != '?'`

**d) Vincoli** – il controllo dei limiti precede l'accesso a `tiri`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessun colpo consumato, si chiede
un nuovo tiro.

### Caso d'uso 3 – Fine partita

**a) Input** – ultima parte di nave colpita, oppure ultimo colpo sparato

**b) Output** – "Flotta affondata con n colpi!" oppure "Colpi esauriti" e la
griglia della flotta

**c) Variabili di supporto** – `da_affondare`, `colpi_rimasti`

**d) Vincoli** – il ciclo termina quando una delle due variabili arriva a 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Se `da_affondare == 0` stampare la vittoria con i colpi usati.
2. Altrimenti stampare le parti rimaste e rivelare la flotta.
