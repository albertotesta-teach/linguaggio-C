# Analisi – 040-problema-rilevazioni-pluviometriche.c

## 1. Problema

Un ufficio meteorologico ha registrato le precipitazioni mensili di una città
per un anno intero. Il programma deve visualizzare un riepilogo grafico delle
precipitazioni mese per mese, calcolare la media annua e il totale, identificare
il mese più piovoso e quello più secco, e contare i mesi siccitosi sotto soglia.

---

## 2. Analisi generale e struttura dati

Il punto chiave è l'uso di **un solo array di dati** (`pioggia`): l'indice `i`
corrisponde direttamente al mese `i + 1`. I nomi dei mesi sono memorizzati in
un secondo array usato esclusivamente per la stampa; non costituiscono un dato
parallelo perché non vengono mai elaborati insieme ai valori numerici.

| Variabile         | Tipo         | Dimensione | Motivazione                                        |
|-------------------|--------------|------------|----------------------------------------------------|
| `pioggia`         | `double[]`   | 12         | Precipitazione in mm per ogni mese; indice = mese - 1 |
| `mesi`            | `char[][]`   | 12 × 12    | Nomi dei mesi, usati solo nella stampa             |
| `somma`           | `double`     | —          | Accumulatore per il totale annuo                   |
| `media`           | `double`     | —          | Media mensile (somma / NUM_MESI)                   |
| `mese_max`        | `int`        | —          | Indice del mese con precipitazione massima         |
| `mese_min`        | `int`        | —          | Indice del mese con precipitazione minima          |
| `siccitosi`       | `int`        | —          | Contatore mesi con precipitazione < SOGLIA_SICCITA |
| `SOGLIA_SICCITA`  | `#define`    | 30.0       | Soglia in mm sotto la quale un mese è siccitoso    |
| `NUM_MESI`        | `#define`    | 12         | Dimensione dell'array e limite dei cicli           |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Riepilogo grafico mensile

**a) Input**
Array `pioggia` inizializzato staticamente con i 12 valori annuali.

**b) Output**
```
=========================================
   PRECIPITAZIONI ANNUALI - RIEPILOGO
=========================================
  Gennaio    |  42.0 mm | ||||||||
  Febbraio   |  35.5 mm | |||||||
  Marzo      |  28.0 mm | |||||
  ...
=========================================
```

**c) Variabili di supporto**
- `i` (`int`): indice del mese corrente.
- `j` (`int`): contatore per la stampa della barra proporzionale.

**d) Vincoli**
- La barra è costruita con un simbolo `|` ogni 5 mm (`pioggia[i] / 5.0`).
- Il cast `(int)` tronca il risultato della divisione prima del ciclo interno.

**e) Assunzioni**
- I valori di `pioggia` sono non negativi.
- La barra può avere zero simboli per precipitazioni inferiori a 5 mm.

**f) Algoritmo in linguaggio naturale**
```
1. Stampare intestazione.
2. Per i da 0 a NUM_MESI - 1:
   a. Stampare mesi[i] e pioggia[i].
   b. Per j da 0 a (int)(pioggia[i] / 5.0) - 1: stampare "|".
   c. Andare a capo.
3. Stampare separatore finale.
```

---

### Caso d'uso 2 – Totale annuo e media mensile

**a) Input**
Array `pioggia`.

**b) Output**
```
Precipitazione totale annua : 503.0 mm
Precipitazione media mensile: 41.9 mm
```

**c) Variabili di supporto**
- `somma` (`double`): accumulatore.
- `media` (`double`): somma / NUM_MESI.

**d) Vincoli**
- La divisione è in virgola mobile: `double / int` produce `double`.

**e) Assunzioni**
- `NUM_MESI > 0` (garantito dalla costante).

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare somma = 0.0.
2. Per i da 0 a NUM_MESI - 1: somma += pioggia[i].
3. media = somma / NUM_MESI.
4. Stampare somma e media.
```

---

### Caso d'uso 3 – Mese più piovoso, più secco e conteggio siccitosi

**a) Input**
Array `pioggia`, costante `SOGLIA_SICCITA`.

**b) Output**
```
Mese piu' piovoso : Ottobre (75.0 mm)
Mese piu' secco   : Luglio (12.5 mm)

Mesi siccitosi (< 30 mm):
  Marzo: 28.0 mm
  Giugno: 18.0 mm
  Luglio: 12.5 mm
  Agosto: 22.0 mm

Totale mesi siccitosi: 4 su 12
```

**c) Variabili di supporto**
- `mese_max` (`int`): indice corrente del massimo.
- `mese_min` (`int`): indice corrente del minimo.
- `siccitosi` (`int`): contatore mesi sotto soglia.

**d) Vincoli**
- `mese_max` e `mese_min` si inizializzano a 0 (non al valore, ma all'indice),
  così `pioggia[mese_max]` e `pioggia[mese_min]` restano sempre accessibili.
- Il ciclo per min/max parte da `i = 1` perché l'indice 0 è già il riferimento iniziale.
- Il ciclo per i siccitosi è separato e scorre tutto l'array dall'inizio.

**e) Assunzioni**
- L'array contiene almeno un elemento.
- Se nessun mese è sotto soglia, si stampa un messaggio esplicito.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare mese_max = 0, mese_min = 0.
2. Per i da 1 a NUM_MESI - 1:
   a. Se pioggia[i] > pioggia[mese_max]: mese_max = i.
   b. Se pioggia[i] < pioggia[mese_min]: mese_min = i.
3. Stampare mesi[mese_max], pioggia[mese_max], mesi[mese_min], pioggia[mese_min].
4. Inizializzare siccitosi = 0.
5. Per i da 0 a NUM_MESI - 1:
   a. Se pioggia[i] < SOGLIA_SICCITA: stampare mese e valore, incrementare siccitosi.
6. Se siccitosi == 0: stampare "Nessun mese siccitoso".
7. Stampare totale siccitosi.
```
