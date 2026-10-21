# Analisi – 070-problema-paghe-dipendenti.c

## 1. Problema

Un'azienda con 6 dipendenti deve calcolare le paghe lorde mensili moltiplicando
ore lavorate per tariffa oraria, stampare il prospetto completo, calcolare il
totale del costo aziendale e la media, identificare il dipendente più e meno
pagato e confrontare ogni paga con la media.

---

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice in tre array
paralleli.

| Variabile | Tipo       | Dimensione | Descrizione                         |
|-----------|------------|------------|-------------------------------------|
| `nomi`    | `char[][]` | 6 × 20     | Cognome e nome del dipendente       |
| `ore`     | `int[]`    | 6          | Ore lavorate nel mese               |
| `tariffe` | `double[]` | 6          | Tariffa oraria in euro              |

### Output
- Il prospetto: nome, ore, tariffa e paga lorda di ogni dipendente;
- il costo aziendale totale e la paga media;
- il dipendente con la paga più alta e quello con la più bassa;
- per ogni dipendente la differenza dalla media ("sopra", "sotto" o "nella
  media").

### Vincoli
- `paghe[i] = ore[i] × tariffe[i]`: l'array delle paghe si calcola prima di
  ogni altra elaborazione
- Massimo e minimo si cercano per indice, partendo dal primo dipendente; in
  caso di parità resta il primo trovato
- La differenza dalla media ha il segno "+" solo se positiva

### Assunzioni
- Ore e tariffe sono positive
- Le paghe sono lorde: niente trattenute

### Variabili di supporto

Il punto chiave è l'**array calcolato** `paghe`, costruito da due array di
dati: un pattern molto comune nella pratica.

| Variabile    | Tipo       | Dimensione | Descrizione                              |
|--------------|------------|------------|------------------------------------------|
| `paghe`      | `double[]` | 6          | Paga lorda di ogni dipendente            |
| `totale`, `media` | `double` | —       | Costo aziendale e paga media             |
| `indice_max`, `indice_min` | `int` | — | Dipendenti più e meno pagati             |
| `diff`       | `double`   | —          | Paga − media                             |
| `DIPENDENTI` | `#define`  | 6          | Numero di dipendenti                     |

### Algoritmo in linguaggio naturale
1. Per ogni dipendente calcolare `paghe[i] = ore[i] × tariffe[i]`.
2. Stampare il prospetto.
3. Sommare le paghe, calcolare la media e stampare entrambe.
4. Cercare gli indici della paga massima e minima e stamparli.
5. Per ogni dipendente calcolare `diff = paghe[i] − media` e stampare
   "sopra", "sotto" o "nella media".

---

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Prospetto paghe
- **Output atteso:**
```
  Rossi Anna       | 168  |  12.50€ |   2100.00€
  Bianchi Carlo    | 152  |  15.00€ |   2280.00€
  Verdi Elena      | 176  |  11.80€ |   2076.80€
  Ferrari Marco    | 160  |  18.00€ |   2880.00€
  Russo Giulia     | 144  |  13.20€ |   1900.80€
  Conti Pietro     | 168  |  16.50€ |   2772.00€
```

### Test 2 – Totali ed estremi
- **Output atteso:**
```
Totale costo aziendale : 14009.60€
Paga media mensile     : 2334.93€

Paga piu' alta  : Ferrari Marco (2880.00€)
Paga piu' bassa : Russo Giulia (1900.80€)
```

### Test 3 – Confronto con la media
- **Output atteso:**
```
  Rossi Anna       : -234.93€ sotto la media
  Bianchi Carlo    : -54.93€ sotto la media
  Verdi Elena      : -258.13€ sotto la media
  Ferrari Marco    : +545.07€ sopra la media
  Russo Giulia     : -434.13€ sotto la media
  Conti Pietro     : +437.07€ sopra la media
```
