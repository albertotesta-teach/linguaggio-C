# Analisi – 050-problema-distribuzione-voti.c

## 1. Problema

Il coordinatore di classe vuole analizzare la distribuzione dei voti di un test
tra 20 studenti, suddividendoli in fasce di rendimento. Il programma legge i
voti da tastiera, conta quanti cadono in ciascuna fascia, mostra la distribuzione
con percentuali e istogramma e produce un riepilogo sui sufficienti e insufficienti.

---

## 2. Analisi generale e struttura dati

Il punto chiave è la **mappatura voto → indice fascia** tramite una catena
`if/else if`: il voto letto viene classificato e si incrementa direttamente
la cella corrispondente nell'array dei contatori. Non servono array paralleli
perché la classificazione è espressa dalla logica condizionale.

```
  Voto:    1-4   5     6     7     8    9-10
  Indice:  [0]   [1]   [2]   [3]   [4]  [5]
  Label:   Ins.  Med.  Suf.  Dis.  Buo. Ott.
```

| Variabile       | Tipo       | Dimensione | Motivazione                                         |
|-----------------|------------|------------|-----------------------------------------------------|
| `contatori`     | `int[]`    | 6          | Un contatore per ciascuna delle 6 fasce             |
| `etichette`     | `char[][]` | 6 × 15     | Stringhe descrittive, usate solo per la stampa      |
| `voto`          | `int`      | —          | Voto letto da tastiera (1–10)                       |
| `indice_fascia` | `int`      | —          | Fascia determinata dalla mappatura del voto         |
| `insufficienti` | `int`      | —          | Somma dei contatori delle fasce 0 e 1               |
| `sufficienti`   | `int`      | —          | `NUM_STUDENTI - insufficienti`                      |
| `valido`        | `int`      | —          | Flag per la validazione dell'input                  |
| `NUM_STUDENTI`  | `#define`  | 20         | Numero di voti da inserire                          |
| `NUM_FASCE`     | `#define`  | 6          | Numero di fasce di rendimento                       |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Acquisizione e classificazione dei voti

**a) Input**
20 valori interi inseriti da tastiera, ciascuno compreso tra 1 e 10.

**b) Output**
Prompt per ogni studente:
```
  Studente  1: 
  Studente  2: 
  ...
```

**c) Variabili di supporto**
- `voto` (`int`): valore letto.
- `indice_fascia` (`int`): risultato della mappatura.
- `valido` (`int`): flag per il ciclo di validazione.

**d) Vincoli**
- Solo valori in [1, 10] sono accettati.
- La mappatura `voto → indice_fascia` deve coprire tutti i valori validi
  senza sovrapposizioni e senza vuoti.
- `indice_fascia` è sempre nell'intervallo [0, NUM_FASCE - 1].

**e) Assunzioni**
- L'utente inserisce valori interi.
- Le fasce sono definite a priori e non cambiano durante l'esecuzione.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare contatori[0..5] = 0.
2. Per i da 0 a NUM_STUDENTI - 1:
   a. Inizializzare valido = 0.
   b. Mentre !valido: leggere voto, validare, impostare valido = 1 se corretto.
   c. Determinare indice_fascia con if/else if sul voto.
   d. contatori[indice_fascia] += 1.
```

---

### Caso d'uso 2 – Distribuzione con percentuale e istogramma

**a) Input**
Array `contatori` e `etichette`.

**b) Output**
```
=== DISTRIBUZIONE ===
  Fascia          | N. | %    | Grafico
  ----------------|----|----- |--------------------
  Insuff. (1-4)   |   3 | 15.0% | ***
  Mediocre (5)    |   2 | 10.0% | **
  Suffic.  (6)    |   5 | 25.0% | *****
  Discreto (7)    |   4 | 20.0% | ****
  Buono    (8)    |   4 | 20.0% | ****
  Ottimo (9-10)   |   2 | 10.0% | **
```

**c) Variabili di supporto**
- `percentuale` (`double`): `contatori[i] / NUM_STUDENTI * 100`.
- `j` (`int`): contatore per la stampa degli asterischi.

**d) Vincoli**
- La percentuale si calcola con divisione floating point.
- Il numero di asterischi è esattamente `contatori[i]`.

**e) Assunzioni**
- `NUM_STUDENTI > 0` per evitare divisione per zero.

**f) Algoritmo in linguaggio naturale**
```
1. Stampare intestazione della tabella.
2. Per i da 0 a NUM_FASCE - 1:
   a. percentuale = contatori[i] / NUM_STUDENTI * 100.
   b. Stampare etichette[i], contatori[i], percentuale.
   c. Per j da 0 a contatori[i] - 1: stampare "*".
```

---

### Caso d'uso 3 – Riepilogo sufficienti e insufficienti

**a) Input**
Array `contatori`.

**b) Output**
```
Studenti con voto insufficiente: 5 su 20 (25%)
Studenti con voto sufficiente  : 15 su 20 (75%)
```

**c) Variabili di supporto**
- `insufficienti` (`int`): `contatori[0] + contatori[1]` (fasce 1–4 e 5).
- `sufficienti` (`int`): `NUM_STUDENTI - insufficienti`.

**d) Vincoli**
- `insufficienti + sufficienti` deve essere sempre uguale a `NUM_STUDENTI`.
- La soglia di sufficienza è 6 (inclusa): le fasce 0 e 1 coprono i voti 1–5.

**e) Assunzioni**
- Tutti i voti sono stati correttamente registrati nei contatori.

**f) Algoritmo in linguaggio naturale**
```
1. insufficienti = contatori[0] + contatori[1].
2. sufficienti = NUM_STUDENTI - insufficienti.
3. Stampare insufficienti, sufficienti e le rispettive percentuali.
```
