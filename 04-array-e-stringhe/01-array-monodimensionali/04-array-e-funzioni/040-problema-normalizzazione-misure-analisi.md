# Analisi – 040-problema-normalizzazione-misure.c

## 1. Problema

Un laboratorio ha acquisito 8 misurazioni di tensione elettrica in Volt.
Il programma deve normalizzarle nell'intervallo [0.0, 1.0], calcolare lo scarto
di ogni misurazione rispetto alla tensione nominale attesa e identificare le
misure fuori tolleranza.

---

## 2. Analisi generale e struttura dati

Il punto chiave è la **separazione tra elaborazione e presentazione**: le funzioni
calcolano e costruiscono i dati, il `main` si occupa solo di coordinarle e
stampare i risultati. L'array `normalizzate` è costruito da `normalizza()` a
partire da `misure`; `scarti` è costruito da `calcola_scarti()`.

| Variabile        | Tipo        | Dimensione | Motivazione                                            |
|------------------|-------------|------------|--------------------------------------------------------|
| `misure`         | `double[]`  | 8          | Tensioni acquisite in Volt                             |
| `normalizzate`   | `double[]`  | 8          | Output di `normalizza()`: valori in [0.0, 1.0]         |
| `scarti`         | `double[]`  | 8          | Output di `calcola_scarti()`: differenza da nominale   |
| `valore_atteso`  | `double`    | —          | Tensione nominale fornita dal tecnico (4.50 V)         |
| `soglia_scarto`  | `double`    | —          | Tolleranza massima accettabile (0.5 V)                 |
| `fuori_tolleranza`| `int`      | —          | Contatore misure con scarto > soglia                   |
| `MISURE`         | `#define`   | 8          | Dimensione degli array e limite dei cicli              |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Normalizzazione nell'intervallo [0.0, 1.0]

**a) Input**
Array `misure`.

**b) Output**
Colonna `Normaliz.` nella tabella:
```
   1  |   3.210 V |   0.6270  |  ...
   5  |   5.120 V |   1.0000  |  ...
```

**c) Funzione coinvolta**
`normalizza(src, dst, n)`: trova il massimo con `massimo()`, poi divide ogni
elemento per esso. Gestisce il caso degenere massimo = 0.

**d) Vincoli**
- Il valore massimo deve essere calcolato prima di iniziare la divisione.
- `dst[i] = src[i] / max` produce sempre un valore in [0.0, 1.0].
- L'elemento con valore massimo ottiene esattamente 1.0.

**e) Assunzioni**
- Tutte le misure sono non negative (tensioni).
- Il massimo è sempre > 0 in condizioni normali.

**f) Algoritmo in linguaggio naturale**
```
1. max = massimo(src, n).
2. Se max == 0.0: dst[i] = 0.0 per tutti i.
   Altrimenti: per i da 0 a n-1: dst[i] = src[i] / max.
```

---

### Caso d'uso 2 – Calcolo degli scarti dal valore atteso

**a) Input**
Array `misure`, scalare `valore_atteso`.

**b) Output**
Colonna `Scarto da 4.5V` nella tabella:
```
   1  |   3.210 V |  ...  |   1.290 V
   4  |   5.120 V |  ...  |   0.620 V
```

**c) Funzione coinvolta**
`calcola_scarti(misure, scarti, n, valore_atteso)`: per ogni elemento calcola
il valore assoluto della differenza.

**d) Vincoli**
- Lo scarto è sempre non negativo (valore assoluto).
- `diff = misure[i] - valore_atteso` può essere positiva o negativa.

**f) Algoritmo in linguaggio naturale**
```
Per i da 0 a n-1:
  diff = misure[i] - valore_atteso.
  scarti[i] = |diff|.
```

---

### Caso d'uso 3 – Misure fuori tolleranza

**a) Input**
Array `scarti`, scalare `soglia_scarto`.

**b) Output**
```
Misure fuori tolleranza (scarto > 0.5 V): 2 su 8
```

**c) Variabili di supporto**
- `fuori_tolleranza` (`int`): contatore misure con `scarti[i] > soglia_scarto`.

**d) Vincoli**
- Il confronto avviene su `scarti[]` (già valori assoluti), non su `misure[]`.
- La soglia è definita come variabile scalare nel `main`, non come `#define`,
  perché potrebbe variare da campagna di misura a campagna di misura.

**f) Algoritmo in linguaggio naturale**
```
fuori_tolleranza = 0.
Per i da 0 a MISURE - 1:
  Se scarti[i] > soglia_scarto: fuori_tolleranza++.
Stampare fuori_tolleranza.
```
