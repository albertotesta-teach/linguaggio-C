# Analisi – 070-problema-paghe-dipendenti.c

## 1. Problema

Un'azienda con 6 dipendenti deve calcolare le paghe lorde mensili moltiplicando
ore lavorate per tariffa oraria, stampare il prospetto completo, calcolare il
totale del costo aziendale e la media, identificare il dipendente più e meno
pagato e confrontare ogni paga con la media.

---

## 2. Analisi generale e struttura dati

Il punto chiave è la presenza di un **array calcolato** (`paghe`) costruito
a partire da due array di input (`ore` e `tariffe`). Questo pattern — produrre
un array di risultati da array di dati grezzi — è molto comune nella pratica.

| Variabile    | Tipo         | Dimensione | Motivazione                                          |
|--------------|--------------|------------|------------------------------------------------------|
| `nomi`       | `char[][]`   | 6 × 20     | Nome e cognome di ogni dipendente                    |
| `ore`        | `int[]`      | 6          | Ore lavorate nel mese per ogni dipendente            |
| `tariffe`    | `double[]`   | 6          | Tariffa oraria in euro per ogni dipendente           |
| `paghe`      | `double[]`   | 6          | Paga lorda calcolata: `paghe[i] = ore[i] * tariffe[i]` |
| `totale`     | `double`     | —          | Somma di tutte le paghe (costo aziendale totale)     |
| `media`      | `double`     | —          | `totale / DIPENDENTI`                                |
| `indice_max` | `int`        | —          | Indice del dipendente con paga massima               |
| `indice_min` | `int`        | —          | Indice del dipendente con paga minima                |
| `DIPENDENTI` | `#define`    | 6          | Dimensione degli array e limite dei cicli            |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Calcolo paghe e prospetto

**a) Input**
Array `ore` e `tariffe` inizializzati staticamente.

**b) Output**
```
=======================================================
              PROSPETTO PAGHE MENSILI
=======================================================
  Dipendente       | Ore  | Tariffa | Paga lorda
  -----------------|------|---------|------------
  Rossi Anna       | 168  |  12.50€ |   2100.00€
  Bianchi Carlo    | 152  |  15.00€ |   2280.00€
  ...
```

**c) Variabili di supporto**
- `paghe[i]` (`double`): calcolato nel primo ciclo, usato in tutti gli altri.

**d) Vincoli**
- L'array `paghe` deve essere popolato completamente prima di qualsiasi
  altra elaborazione (media, estremi, confronto).
- La moltiplicazione `ore[i] * tariffe[i]` produce un `double` perché
  `tariffe[i]` è `double` (promozione automatica del tipo).

**e) Assunzioni**
- Le ore sono positive e le tariffe maggiori di zero.

**f) Algoritmo in linguaggio naturale**
```
1. Per i da 0 a DIPENDENTI - 1: paghe[i] = ore[i] * tariffe[i].
2. Stampare intestazione tabella.
3. Per i da 0 a DIPENDENTI - 1: stampare nomi[i], ore[i], tariffe[i], paghe[i].
```

---

### Caso d'uso 2 – Totale e paga media

**a) Input**
Array `paghe`.

**b) Output**
```
Totale costo aziendale : 13056.00€
Paga media mensile     : 2176.00€
```

**c) Variabili di supporto**
- `totale` (`double`): accumulatore.
- `media` (`double`): `totale / DIPENDENTI`.

**d) Vincoli**
- `media` deve essere calcolata e disponibile prima del caso d'uso 4.

**f) Algoritmo in linguaggio naturale**
```
1. totale = 0.0. Per i da 0 a DIPENDENTI-1: totale += paghe[i].
2. media = totale / DIPENDENTI.
```

---

### Caso d'uso 3 – Paga più alta e più bassa

**a) Input**
Array `paghe`.

**b) Output**
```
Paga piu' alta  : Ferrari Marco (2880.00€)
Paga piu' bassa : Russo Giulia (1900.80€)
```

**c) Variabili di supporto**
- `indice_max`, `indice_min` (`int`): inizializzati a 0, aggiornati con pattern "ipotesi + smentita".

**d) Vincoli**
- Entrambi i cicli partono da `i = 1` perché `i = 0` è già il riferimento iniziale.

**f) Algoritmo in linguaggio naturale**
```
1. indice_max = indice_min = 0.
2. Per i da 1 a DIPENDENTI - 1:
   a. Se paghe[i] > paghe[indice_max]: indice_max = i.
   b. Se paghe[i] < paghe[indice_min]: indice_min = i.
3. Stampare nomi[indice_max], paghe[indice_max], nomi[indice_min], paghe[indice_min].
```

---

### Caso d'uso 4 – Confronto con la media

**a) Input**
Array `paghe`, variabile `media`.

**b) Output**
```
Confronto con la media (2176.00€):
  Rossi Anna       : -76.00€ sotto la media
  Bianchi Carlo    : +104.00€ sopra la media
  ...
```

**c) Variabili di supporto**
- `diff` (`double`): `paghe[i] - media`, può essere positiva, negativa o zero.

**d) Vincoli**
- I tre casi (sopra, sotto, nella media) producono messaggi distinti.
- Il confronto `diff == 0.0` su double è tecnicamente fragile, ma corretto
  per questo scenario didattico con valori interi × double semplici.

**f) Algoritmo in linguaggio naturale**
```
1. Per i da 0 a DIPENDENTI - 1:
   a. diff = paghe[i] - media.
   b. Se diff > 0: stampare "+diff sopra la media".
   c. Se diff < 0: stampare "diff sotto la media".
   d. Altrimenti: stampare "nella media".
```
