# Analisi – 080-problema-registro-presenze.c

## 1. Problema

Un ufficio HR monitora le presenze di 6 dipendenti su 22 giorni lavorativi.
Il programma deve stampare un prospetto con percentuale e stato, identificare
il più e meno presente e contare quanti dipendenti sono sotto la soglia dell'80%.

---

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile  | Tipo       | Dimensione | Descrizione                               |
|------------|------------|------------|-------------------------------------------|
| `nomi`     | `char[][]` | 6 × 20     | Cognome e nome del dipendente             |
| `presenze` | `int[]`    | 6          | Giorni di presenza, parallelo a `nomi`    |

### Output
- Il prospetto: nome, giorni di presenza, percentuale (un decimale) e stato
  "REGOLARE" o "ATTENZIONE";
- il dipendente più presente e quello meno presente, con giorni e
  percentuale;
- il numero di dipendenti sotto la soglia.

### Vincoli
- Percentuale = presenze / 22 × 100, con divisione reale
- Lo stato è "REGOLARE" se la percentuale è almeno l'80% (soglia inclusa),
  altrimenti "ATTENZIONE"
- Con 22 giorni l'80% corrisponde a 17.6 giorni: 18 giorni sono regolari,
  17 no
- A parità di presenze si sceglie il primo dipendente dell'array
- Lo stato si costruisce carattere per carattere con `'\0'` finale

### Assunzioni
- 0 ≤ presenze ≤ 22

### Variabili di supporto

| Variabile           | Tipo      | Descrizione                        |
|---------------------|-----------|------------------------------------|
| `perc`              | `double`  | Percentuale del dipendente         |
| `avviso`            | `char[15]`| "REGOLARE" o "ATTENZIONE"          |
| `idx`               | `int`     | Indice del dipendente trovato      |
| `GIORNI_LAVORATIVI` | `#define` | 22                                 |
| `SOGLIA_PRESENZA`   | `#define` | 80.0                               |
| `DIPENDENTI`        | `#define` | 6                                  |

| Funzione | Descrizione |
|---|---|
| `double percentuale_presenza(int giorni_presenti, int giorni_totali)` | Percentuale di un dipendente |
| `int dipendente_piu_presente(const int presenze[], int n)` | Indice del massimo |
| `int dipendente_meno_presente(const int presenze[], int n)` | Indice del minimo |
| `int conta_sotto_soglia(...)` | Dipendenti sotto la soglia |
| `void stampa_prospetto(...)` | Prospetto con stato |

### Algoritmo in linguaggio naturale
1. Per ogni dipendente calcolare la percentuale, scegliere lo stato e
   stampare la riga.
2. Trovare e stampare il più presente e il meno presente.
3. Contare e stampare i dipendenti con percentuale minore della soglia.

---

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Prospetto
- **Cosa si verifica:** 18 giorni (81.8%) è regolare, 17 giorni (77.3%) no
- **Output atteso:**
```
  Rossi Anna       |   22   | 100.0% | REGOLARE
  Bianchi Carlo    |   18   |  81.8% | REGOLARE
  Verdi Elena      |   20   |  90.9% | REGOLARE
  Ferrari Marco    |   15   |  68.2% | ATTENZIONE
  Russo Giulia     |   21   |  95.5% | REGOLARE
  Conti Pietro     |   17   |  77.3% | ATTENZIONE
```

### Test 2 – Estremi e conteggio
- **Output atteso:**
```
Piu' presente   : Rossi Anna (22 gg - 100.0%)
Meno presente   : Ferrari Marco (15 gg - 68.2%)
Sotto soglia    : 2 dipendenti su 6
```
