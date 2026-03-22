# Analisi – 050-problema-contatore-caratteri.c

## 1. Problema

Un programma di analisi testuale deve contare le occorrenze di ogni lettera
dell'alfabeto in un testo, visualizzare la distribuzione con percentuale e
istogramma, identificare la lettera più e meno frequente e contare quante
lettere distinte sono presenti.

---

## 2. Analisi generale e struttura dati

Il punto chiave è la **conversione carattere → indice**: sottraendo il codice
ASCII di `'a'` da una lettera minuscola si ottiene un indice nell'intervallo
[0, 25], che punta direttamente alla cella dell'array da incrementare.
È lo stesso pattern dell'array dado, applicato a dati testuali.

```
  Carattere:  'a'   'b'   'c'  ...  'z'
  Indice:      0     1     2   ...   25
  Formula:     c - 'a'
```

| Variabile         | Tipo      | Dimensione | Motivazione                                              |
|-------------------|-----------|------------|----------------------------------------------------------|
| `testo`           | `char[]`  | variabile  | Stringa da analizzare, terminata da `'\0'`               |
| `frequenze`       | `int[]`   | 26         | `frequenze[i]` conta le occorrenze della lettera `'a'+i` |
| `totale_lettere`  | `int`     | —          | Totale caratteri alfabetici trovati (per le percentuali) |
| `indice_max`      | `int`     | —          | Indice della lettera più frequente                       |
| `indice_min`      | `int`     | —          | Indice della lettera meno frequente (tra quelle presenti)|
| `lettere_distinte`| `int`     | —          | Contatore celle con `frequenze[i] > 0`                   |
| `LETTERE`         | `#define` | 26         | Dimensione dell'array (lettere dell'alfabeto)            |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Scansione del testo e conteggio

**a) Input**
Stringa `testo` inizializzata staticamente nel codice.

**b) Output**
Nessun output durante la scansione; i risultati vengono stampati nei casi d'uso successivi.

**c) Variabili di supporto**
- `c` (`char`): carattere corrente, eventualmente convertito in minuscolo.
- `i` (`int`): indice di scorrimento della stringa.

**d) Vincoli**
- Il ciclo scorre fino al terminatore `'\0'` (condizione `testo[i] != '\0'`).
- Le maiuscole vengono convertite in minuscole aggiungendo 32 (differenza ASCII).
- Spazi, apostrofi e qualsiasi carattere non alfabetico vengono ignorati.
- L'aggiornamento usa `frequenze[c - 'a'] += 1`, dove `c - 'a'` è sempre in [0, 25].

**e) Assunzioni**
- Il testo contiene solo caratteri ASCII standard (nessun carattere accentato).
- Le apostrofi nel testo (come nell'esempio "dell'impero") non sono lettere e vengono ignorati.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare frequenze[0..25] = 0, totale_lettere = 0.
2. Per i da 0 finché testo[i] != '\0':
   a. c = testo[i].
   b. Se c è maiuscola: c += 32 (conversione in minuscola).
   c. Se c è minuscola (a..z):
      - frequenze[c - 'a'] += 1.
      - totale_lettere += 1.
```

---

### Caso d'uso 2 – Tabella delle frequenze con istogramma

**a) Input**
Array `frequenze`, variabile `totale_lettere`.

**b) Output**
```
=== ANALISI FREQUENZA LETTERE ===

  Lettera | Freq. | Percentuale | Istogramma
  --------|-------|-------------|--------------------
    a     |   18  |   14.8%     | ******************
    c     |    5  |    4.1%     | *****
  ...
```

**c) Variabili di supporto**
- `perc` (`double`): percentuale sul totale.
- `j` (`int`): contatore per la stampa degli asterischi.

**d) Vincoli**
- Si stampano solo le lettere con `frequenze[i] > 0`.
- Il carattere stampato si ricava con `'a' + i` (inverso della conversione).
- La percentuale usa divisione floating point.

**e) Assunzioni**
- `totale_lettere > 0` (il testo contiene almeno una lettera).

**f) Algoritmo in linguaggio naturale**
```
1. Per i da 0 a LETTERE - 1:
   a. Se frequenze[i] > 0:
      - perc = frequenze[i] / totale_lettere * 100.
      - Stampare 'a'+i, frequenze[i], perc.
      - Per j da 0 a frequenze[i]-1: stampare "*".
```

---

### Caso d'uso 3 – Lettera più e meno frequente, lettere distinte

**a) Input**
Array `frequenze`.

**b) Output**
```
Lettera piu' frequente : 'a'  (18 occorrenze)
Lettera meno frequente : 'b'  (1 occorrenza/e)
Lettere distinte usate : 19 su 26
```

**c) Variabili di supporto**
- `indice_max` (`int`): inizializzato a 0; aggiornato se `frequenze[i] > frequenze[indice_max]`.
- `indice_min` (`int`): inizializzato a -1 (sentinella); aggiornato solo su celle > 0.

**d) Vincoli**
- Il minimo deve ignorare le celle con `frequenze[i] == 0`, altrimenti le lettere
  assenti sarebbero sempre "le meno frequenti".
- La sentinella `indice_min = -1` segnala che ancora non è stata trovata nessuna
  lettera presente; va gestita prima di usare l'indice.

**e) Assunzioni**
- Il testo contiene almeno una lettera (altrimenti `indice_min` resterebbe -1).

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare indice_max = 0, indice_min = -1.
2. Per i da 0 a LETTERE - 1:
   a. Se frequenze[i] > frequenze[indice_max]: indice_max = i.
   b. Se frequenze[i] > 0 E (indice_min == -1 O frequenze[i] < frequenze[indice_min]):
      indice_min = i.
3. Stampare 'a'+indice_max e 'a'+indice_min con le rispettive frequenze.
4. Contare le celle con frequenze[i] > 0 e stampare il risultato.
```
