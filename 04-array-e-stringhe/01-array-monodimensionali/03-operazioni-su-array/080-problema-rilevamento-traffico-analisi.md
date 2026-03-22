# Analisi – 080-problema-rilevamento-traffico.c

## 1. Problema

Un sistema di rilevamento monitora il traffico su 8 strade urbane nell'arco di
un'ora. Il programma deve stampare un riepilogo con lo stato di ogni strada,
identificare le strade congestioniate sopra una soglia, calcolare la densità
media e trovare le 3 strade più trafficate tramite ricerca ripetuta del massimo.

---

## 2. Analisi generale e struttura dati

Il punto tecnico più rilevante è la ricerca delle **top-3** senza algoritmo
di ordinamento: si eseguono 3 passaggi di ricerca del massimo, escludendo
ogni volta le strade già selezionate tramite un array di flag `selezionato`.
Questo anticipa concettualmente il selection sort del capitolo 11.

| Variabile          | Tipo       | Dimensione | Motivazione                                             |
|--------------------|------------|------------|---------------------------------------------------------|
| `nomi`             | `char[][]` | 8 × 25     | Nome di ogni strada                                     |
| `veicoli`          | `int[]`    | 8          | Veicoli rilevati in un'ora; parallelo a `nomi`          |
| `selezionato`      | `int[]`    | 8          | Flag: 1 se la strada è già stata inserita nel top-N     |
| `somma`            | `int`      | —          | Accumulatore per la media                               |
| `congestionate`    | `int`      | —          | Contatore strade sopra `SOGLIA_CONGESTIONE`             |
| `indice_max`       | `int`      | —          | Indice del massimo corrente nella ricerca ripetuta      |
| `SOGLIA_CONGESTIONE`| `#define` | 800        | Soglia veicoli/h oltre la quale una strada è congestionata |
| `TOP_N`            | `#define`  | 3          | Numero di strade da mostrare nella classifica           |
| `STRADE`           | `#define`  | 8          | Dimensione degli array e limite dei cicli               |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Riepilogo con stato per strada

**a) Input**
Array `nomi` e `veicoli`.

**b) Output**
```
=== RILEVAMENTO TRAFFICO URBANO ===
  Strada                 | Veicoli/h | Stato
  -----------------------|-----------|----------
  Via Roma               |     620   | SCORREVOLE
  Corso Italia           |     950   | CONGESTA
  ...
```

**c) Variabili di supporto**
- `stato` (`char[]`): stringa costruita manualmente per ogni strada.

**d) Vincoli**
- Il confronto usa `>` (la soglia esatta non è congestionata).
- La stringa `stato` deve terminare con `'\0'`.

**f) Algoritmo in linguaggio naturale**
```
Per i da 0 a STRADE - 1:
  Se veicoli[i] > SOGLIA_CONGESTIONE: stato = "CONGESTA".
  Altrimenti: stato = "SCORREVOLE".
  Stampare nomi[i], veicoli[i], stato.
```

---

### Caso d'uso 2 – Strade congestioniate e media

**a) Input**
Array `veicoli`.

**b) Output**
```
Strade congestioniate (> 800 veicoli/h):
  [!] Corso Italia       : 950 veicoli/h
  [!] Viale Europa       : 1120 veicoli/h
  [!] Corso Vittorio     : 870 veicoli/h
  [!] Piazza Duomo       : 1050 veicoli/h

Densita' media : 766 veicoli/h
Congestioniate : 4 su 8 strade
```

**c) Variabili di supporto**
- `somma` (`int`): calcolato nello stesso ciclo delle strade congestioniate.
- `congestionate` (`int`): contatore.

**d) Vincoli**
- Somma e conteggio vengono aggiornati nello stesso ciclo per efficienza.

**f) Algoritmo in linguaggio naturale**
```
somma = 0, congestionate = 0.
Per i da 0 a STRADE - 1:
  somma += veicoli[i].
  Se veicoli[i] > SOGLIA_CONGESTIONE: stampare e incrementare congestionate.
Stampare media e congestionate.
```

---

### Caso d'uso 3 – Top-N strade più trafficate

**a) Input**
Array `veicoli`, array `selezionato` (inizializzato a zero).

**b) Output**
```
Top-3 strade piu' trafficate:
  1° posto: Viale Europa          (1120 veicoli/h)
  2° posto: Piazza Duomo          (1050 veicoli/h)
  3° posto: Corso Italia          (950 veicoli/h)
```

**c) Variabili di supporto**
- `selezionato[i]` (`int`): 0 finché la strada non è stata scelta; poi 1.
- `indice_max` (`int`): indice del massimo corrente nel passaggio j-esimo.
- `j` (`int`): contatore del passaggio (1, 2, 3).

**d) Vincoli**
- `indice_max` viene inizializzato a -1 come sentinella prima di ogni passaggio
  interno, per poter gestire il caso in cui tutte le strade siano già selezionate.
- La condizione `!selezionato[i]` filtra le strade già scelte.
- Dopo ogni passaggio, `selezionato[indice_max] = 1` esclude quella strada dai
  passaggi successivi.

**e) Assunzioni**
- `TOP_N <= STRADE` (non si può chiedere più strade di quante ce ne siano).
- Non ci sono pareggi nel conteggio veicoli.

**f) Algoritmo in linguaggio naturale**
```
Inizializzare selezionato[0..STRADE-1] = 0.
Per j da 1 a TOP_N:
  indice_max = -1.
  Per i da 0 a STRADE - 1:
    Se !selezionato[i]:
      Se indice_max == -1 o veicoli[i] > veicoli[indice_max]: indice_max = i.
  selezionato[indice_max] = 1.
  Stampare j, nomi[indice_max], veicoli[indice_max].
```
