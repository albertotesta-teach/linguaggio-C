# Analisi – 080-problema-rilevamento-traffico.c

## 1. Problema

Un sistema di rilevamento monitora il traffico su 8 strade urbane nell'arco di
un'ora. Il programma deve stampare un riepilogo con lo stato di ogni strada,
identificare le strade congestionate sopra una soglia, calcolare la densità
media e trovare le 3 strade più trafficate tramite ricerca ripetuta del massimo.

---

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile | Tipo       | Dimensione | Descrizione                                |
|-----------|------------|------------|--------------------------------------------|
| `nomi`    | `char[][]` | 8 × 25     | Nome della strada                          |
| `veicoli` | `int[]`    | 8          | Veicoli rilevati in un'ora, parallelo a `nomi` |

### Output
- Il riepilogo: nome, veicoli/h e stato ("CONGESTA" o "SCORREVOLE") di ogni
  strada;
- l'elenco delle strade congestionate, oppure
  "Nessuna strada congestionata.";
- la densità media (senza decimali) e il numero di strade congestionate;
- le 3 strade più trafficate in ordine decrescente.

### Vincoli
- Una strada è congestionata se i veicoli sono **strettamente** più di
  `SOGLIA_CONGESTIONE` (800): una strada con 800 veicoli è scorrevole
- La classifica si costruisce senza ordinare l'array: si cerca il massimo
  `TOP_N` volte, escludendo a ogni passo le strade già selezionate
- A parità di veicoli precede la strada che compare prima nell'array
- Lo stato si costruisce carattere per carattere con `'\0'` finale

### Assunzioni
- `TOP_N` non supera il numero di strade

### Variabili di supporto

| Variabile            | Tipo      | Dimensione | Descrizione                                  |
|----------------------|-----------|------------|----------------------------------------------|
| `stato`              | `char[]`  | 15         | "CONGESTA" o "SCORREVOLE"                    |
| `somma`              | `int`     | —          | Veicoli totali                               |
| `congestionate`      | `int`     | —          | Numero di strade sopra soglia                |
| `selezionato`        | `int[]`   | 8          | 1 se la strada è già in classifica           |
| `indice_max`         | `int`     | —          | Massimo della ricerca corrente (-1 se nessuno) |
| `SOGLIA_CONGESTIONE` | `#define` | 800        | Soglia in veicoli/h                          |
| `TOP_N`              | `#define` | 3          | Strade in classifica                         |
| `STRADE`             | `#define` | 8          | Numero di strade                             |

La ricerca ripetuta del massimo anticipa l'idea del selection sort
(capitolo 11).

### Algoritmo in linguaggio naturale
1. Per ogni strada costruire lo stato e stampare la riga del riepilogo.
2. Sommare i veicoli; stampare le strade sopra soglia e contarle; se non ce
   ne sono stampare il messaggio. Stampare media e numero di congestionate.
3. Per j da 1 a `TOP_N`:
   a. cercare la strada con più veicoli tra quelle non ancora selezionate;
   b. segnarla come selezionata e stamparla in posizione j.

---

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il Test 3
richiede di modificare i veicoli e ricompilare.

### Test 1 – Strade congestionate e media
- **Input:** veicoli 620, 950, 430, 1120, 780, 870, 310, 1050
- **Output atteso:**
```
Strade congestionate (> 800 veicoli/h):
  [!] Corso Italia           : 950 veicoli/h
  [!] Viale Europa           : 1120 veicoli/h
  [!] Corso Vittorio         : 870 veicoli/h
  [!] Piazza Duomo           : 1050 veicoli/h

Densita' media : 766 veicoli/h
Congestionate  : 4 su 8 strade
```

### Test 2 – Classifica delle 3 strade più trafficate
- **Output atteso:**
```
Top-3 strade piu' trafficate:
  1° posto: Viale Europa           (1120 veicoli/h)
  2° posto: Piazza Duomo           (1050 veicoli/h)
  3° posto: Corso Italia           (950 veicoli/h)
```

### Test 3 – Nessuna strada congestionata e valore sulla soglia
- **Cosa si verifica:** 800 non supera la soglia e il messaggio alternativo
- **Procedura:** porre i veicoli a `{620, 700, 430, 500, 800, 650, 310, 750}`
- **Output atteso:** Via Mazzini (800) `SCORREVOLE`;
  `Nessuna strada congestionata.`, `Densita' media : 595 veicoli/h`,
  `Congestionate  : 0 su 8 strade`; classifica Via Mazzini, Piazza Duomo,
  Corso Italia
