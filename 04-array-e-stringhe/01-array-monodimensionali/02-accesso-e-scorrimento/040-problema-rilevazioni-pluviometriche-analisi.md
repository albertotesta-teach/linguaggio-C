# Analisi – 040-problema-rilevazioni-pluviometriche.c

## 1. Problema

Un ufficio meteorologico ha registrato le precipitazioni mensili di una città
per un anno intero. Il programma deve visualizzare un riepilogo grafico delle
precipitazioni mese per mese, calcolare la media annua e il totale, identificare
il mese più piovoso e quello più secco, e contare i mesi siccitosi sotto soglia.

---

## 2. Analisi

### Input
Nessun input da tastiera: le precipitazioni sono inizializzate nel codice.

| Variabile | Tipo       | Dimensione | Descrizione                                   |
|-----------|------------|------------|-----------------------------------------------|
| `pioggia` | `double[]` | 12         | Precipitazione in mm; indice `i` = mese `i+1` |

### Output
- Per ogni mese: nome, precipitazione con un decimale e una barra di `|`
  (un simbolo ogni 5 mm, parte intera);
- il totale annuo e la media mensile;
- il mese più piovoso e quello più secco;
- l'elenco dei mesi siccitosi e il loro numero, oppure
  "Nessun mese siccitoso.".

### Vincoli
- Un mese è siccitoso se la precipitazione è **strettamente** minore di
  `SOGLIA_SICCITA` (30 mm)
- La lunghezza della barra è `(int)(pioggia[i] / 5.0)`: il cast tronca, e
  sotto i 5 mm la barra è vuota
- Massimo e minimo si cercano memorizzando l'**indice**, inizializzato a 0,
  e partendo dal secondo mese; in caso di parità resta il primo mese trovato
- La media si calcola con una divisione reale

### Assunzioni
- Le precipitazioni sono non negative
- L'array contiene almeno un elemento

### Variabili di supporto

Il punto chiave è l'uso di **un solo array di dati**: l'indice corrisponde al
mese. L'array `mesi` serve solo a stampare il nome.

| Variabile        | Tipo       | Dimensione | Descrizione                                  |
|------------------|------------|------------|----------------------------------------------|
| `mesi`           | `char[][]` | 12 × 12    | Nomi dei mesi, usati solo nella stampa       |
| `somma`, `media` | `double`   | —          | Totale annuo e media mensile                 |
| `mese_max`, `mese_min` | `int` | —         | Indici del mese più piovoso e più secco      |
| `siccitosi`      | `int`      | —          | Numero di mesi sotto soglia                  |
| `SOGLIA_SICCITA` | `#define`  | 30.0       | Soglia in mm                                 |
| `NUM_MESI`       | `#define`  | 12         | Dimensione dell'array                        |

### Algoritmo in linguaggio naturale
1. Per ogni mese stampare nome, precipitazione e `(int)(pioggia[i] / 5.0)`
   simboli `|`.
2. Sommare le precipitazioni, calcolare `media = somma / 12` e stampare
   totale e media.
3. Porre `mese_max = mese_min = 0`; per i mesi da 1 a 11 aggiornare l'indice
   del massimo se la precipitazione è maggiore e quello del minimo se è
   minore. Stampare i due mesi.
4. Per ogni mese con precipitazione minore della soglia stamparlo e
   contarlo; se non ce ne sono stampare il messaggio; stampare il totale.

---

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il test 3
richiede di modificare l'array e ricompilare.

### Test 1 – Riepilogo grafico
- **Cosa si verifica:** la barra è troncata (42.0 / 5 = 8.4 → 8 simboli)
- **Output atteso (prime righe):**
```
  Gennaio    |  42.0 mm | ||||||||
  Febbraio   |  35.5 mm | |||||||
  Marzo      |  28.0 mm | |||||
```

### Test 2 – Statistiche annuali
- **Output atteso:**
```
Precipitazione totale annua : 503.0 mm
Precipitazione media mensile: 41.9 mm

Mese piu' piovoso : Ottobre (75.0 mm)
Mese piu' secco   : Luglio (12.5 mm)

Mesi siccitosi (< 30 mm):
  Marzo: 28.0 mm
  Giugno: 18.0 mm
  Luglio: 12.5 mm
  Agosto: 22.0 mm

Totale mesi siccitosi: 4 su 12
```

### Test 3 – Nessun mese siccitoso e mese esattamente sulla soglia
- **Cosa si verifica:** la soglia è esclusa (30.0 non è siccitoso) e il
  messaggio alternativo
- **Procedura:** porre a 30.0 i valori di marzo, giugno, luglio e agosto
- **Output atteso:** `Nessun mese siccitoso.` e
  `Totale mesi siccitosi: 0 su 12`
