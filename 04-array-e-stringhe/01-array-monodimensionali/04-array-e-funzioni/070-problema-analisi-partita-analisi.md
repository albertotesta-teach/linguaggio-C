# Analisi – 070-problema-analisi-partita.c

## 1. Problema

Una squadra di calcio ha 8 giocatori. Il programma deve calcolare totale gol,
media, identificare il capocannoniere, contare i giocatori oltre una soglia e
stampare la classifica marcatori (top-5) in ordine decrescente.

---

## 2. Analisi generale e struttura dati

Ogni funzione ha una responsabilità unica. `media_gol` richiama `totale_gol`
per evitare duplicazione. `stampa_classifica` usa internamente la ricerca
ripetuta del massimo con array `selezionato[]`.

| Variabile    | Tipo         | Dimensione | Motivazione                                    |
|--------------|--------------|------------|------------------------------------------------|
| `nomi`       | `char[][]`   | 8 × 20     | Nome di ogni giocatore                         |
| `gol`        | `int[]`      | 8          | Gol segnati; parallelo a `nomi`                |
| `selezionato`| `int[]`      | 8          | Flag interno a `stampa_classifica`             |
| `GIOCATORI`  | `#define`    | 8          | Dimensione degli array e limite dei cicli      |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Statistiche aggregate

**a) Input** — Array `gol`.
**b) Output**
```
Capocannoniere      : Verdi Paolo (15 gol)
Totale gol squadra  : 69
Media per giocatore : 8.6
Giocatori > 8 gol   : 4 su 8
```
**c) Funzioni coinvolte**
- `totale_gol`: accumulatore semplice.
- `media_gol`: chiama `totale_gol` internamente.
- `capocannoniere`: pattern "ipotesi + smentita" che restituisce l'indice.
- `conta_sopra_soglia`: contatore con condizione.

**d) Vincoli**
- `capocannoniere` restituisce l'indice, non il valore: il `main` accede a
  `nomi[idx]` e `gol[idx]` separatamente.
- `media_gol` usa `(double)totale_gol(...)` per la divisione floating point.

---

### Caso d'uso 2 – Classifica top-5

**a) Input** — Array `nomi`, `gol`, intero `k = 5`.
**b) Output**
```
  Pos. | Giocatore          | Gol
  -----|--------------------|---------
     1  | Verdi Paolo        |  15
     2  | Rossi Marco        |  12
     3  | Conti Matteo       |  11
     4  | Russo Andrea       |   9
     5  | Greco Simone       |   8
```
**c) Funzione coinvolta**
`stampa_classifica`: alloca localmente `selezionato[]`, esegue `k` passaggi
di ricerca del massimo escludendo i già selezionati.

**d) Vincoli**
- `selezionato[]` è locale alla funzione: viene inizializzato a zero a ogni chiamata.
- `idx_max = -1` come sentinella prima di ogni passaggio interno.
- `k <= n` (garantito dalla chiamata nel `main`).

**f) Algoritmo in linguaggio naturale**
```
Inizializzare selezionato[0..n-1] = 0.
Per j da 1 a k:
  idx_max = -1.
  Per i da 0 a n-1:
    Se !selezionato[i] E (idx_max==-1 O gol[i]>gol[idx_max]): idx_max=i.
  selezionato[idx_max] = 1.
  Stampare j, nomi[idx_max], gol[idx_max].
```
