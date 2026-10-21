# Analisi – 040-problema-normalizzazione-misure.c

## 1. Problema

Un laboratorio ha acquisito 8 misurazioni di tensione elettrica in Volt.
Il programma deve normalizzarle nell'intervallo [0.0, 1.0], calcolare lo scarto
di ogni misurazione rispetto alla tensione nominale attesa e identificare le
misure fuori tolleranza.

---

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile       | Tipo       | Dimensione | Descrizione                               |
|-----------------|------------|------------|-------------------------------------------|
| `misure`        | `double[]` | 8          | Tensioni acquisite in Volt                |
| `valore_atteso` | `double`   | —          | Tensione nominale (4.50 V)                |
| `soglia_scarto` | `double`   | —          | Tolleranza massima (0.5 V)                |

### Output
- Una tabella con, per ogni misura, il valore originale, il valore
  normalizzato (quattro decimali) e lo scarto dal valore atteso;
- tensione massima, tensione media, valore atteso e scarto medio;
- il numero di misure fuori tolleranza.

### Vincoli
- Valore normalizzato = misura / massimo: il massimo diventa 1.0 e tutti i
  valori cadono in [0, 1] se le misure sono non negative
- Se il massimo è 0 la divisione non è possibile: tutti i valori
  normalizzati valgono 0
- Lo scarto è il valore assoluto di `misura − valore_atteso`
- Una misura è fuori tolleranza se lo scarto è **strettamente** maggiore
  della soglia: uno scarto di esattamente 0.5 V è accettato
- Le funzioni calcolano e riempiono gli array; la stampa dei risultati è
  separata dal calcolo
- Gli array di sola lettura sono passati come `const`

### Assunzioni
- Le misure sono non negative
- L'array contiene almeno un elemento

### Variabili di supporto

| Variabile          | Tipo       | Dimensione | Descrizione                               |
|--------------------|------------|------------|-------------------------------------------|
| `normalizzate`     | `double[]` | 8          | Riempito da `normalizza()`                |
| `scarti`           | `double[]` | 8          | Riempito da `calcola_scarti()`            |
| `fuori_tolleranza` | `int`      | —          | Misure con scarto oltre la soglia         |
| `MISURE`           | `#define`  | 8          | Numero di misure                          |

| Funzione | Descrizione |
|---|---|
| `double massimo(const double arr[], int n)` | Valore massimo |
| `double media(const double arr[], int n)` | Media aritmetica |
| `void normalizza(const double src[], double dst[], int n)` | Scrive in `dst` i valori divisi per il massimo |
| `void calcola_scarti(const double misure[], double scarti[], int n, double valore_atteso)` | Scrive in `scarti` gli scarti assoluti |
| `void stampa_tabella(...)` | Stampa i tre array affiancati |

### Algoritmo in linguaggio naturale
1. Chiamare `normalizza`: calcolare il massimo; se è 0 azzerare `dst`,
   altrimenti `dst[i] = src[i] / max`.
2. Chiamare `calcola_scarti`: `scarti[i] = |misure[i] − valore_atteso|`.
3. Stampare la tabella.
4. Stampare massimo e media delle misure, valore atteso e media degli
   scarti.
5. Contare gli scarti maggiori della soglia e stampare il conteggio.

---

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Normalizzazione e scarti
- **Cosa si verifica:** la misura massima (5.12 V) vale 1.0000
- **Output atteso:**
```
    1  |   3.210 V |  0.6270   |   1.290 V
    2  |   4.850 V |  0.9473   |   0.350 V
    3  |   2.970 V |  0.5801   |   1.530 V
    4  |   5.120 V |  1.0000   |   0.620 V
    5  |   4.430 V |  0.8652   |   0.070 V
    6  |   3.760 V |  0.7344   |   0.740 V
    7  |   5.000 V |  0.9766   |   0.500 V
    8  |   4.180 V |  0.8164   |   0.320 V
```

### Test 2 – Statistiche e tolleranza
- **Cosa si verifica:** la misura 7 ha scarto esattamente 0.5 V e non è
  contata fuori tolleranza
- **Output atteso:**
```
Tensione massima   : 5.120 V
Tensione media     : 4.190 V
Valore atteso      : 4.500 V
Scarto medio       : 0.677 V

Misure fuori tolleranza (scarto > 0.5 V): 4 su 8
```
