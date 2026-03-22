# Analisi – 070-problema-inventario-magazzino.c

## 1. Problema

Un negozio vuole un programma che gestisca l'inventario di 6 prodotti. Il sistema
deve stampare un prospetto formattato con quantità e prezzi, segnalare i prodotti
in esaurimento sotto una soglia configurabile e calcolare la giacenza totale
e il valore complessivo del magazzino.

---

## 2. Analisi generale e struttura dati

Il magazzino è rappresentato da quattro array paralleli: per ogni indice `i`
si trovano il codice, il nome, la quantità e il prezzo dello stesso prodotto.
La soglia minima è definita come costante per permettere modifiche rapide.

| Variabile         | Tipo         | Dimensione | Motivazione                                       |
|-------------------|--------------|------------|---------------------------------------------------|
| `codici`          | `char[][]`   | 6 × 8      | Codice alfanumerico max 7 caratteri + `'\0'`      |
| `nomi`            | `char[][]`   | 6 × 25     | Nome prodotto max 24 caratteri + `'\0'`           |
| `quantita`        | `int[]`      | 6          | Numero di pezzi disponibili (intero)              |
| `prezzi`          | `double[]`   | 6          | Prezzo unitario in euro (decimale)                |
| `giacenza_totale` | `int`        | —          | Somma di tutti gli elementi di `quantita`         |
| `valore_totale`   | `double`     | —          | Somma di `quantita[i] * prezzi[i]` per ogni i    |
| `trovati`         | `int`        | —          | Contatore prodotti sotto soglia                   |
| `valore_riga`     | `double`     | —          | Valore del singolo prodotto (quantità × prezzo)   |
| `SOGLIA_MINIMA`   | `#define`    | 10         | Soglia di riordino, modificabile in un punto solo |
| `NUM_PRODOTTI`    | `#define`    | 6          | Dimensione degli array e limite dei cicli         |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Stampa del prospetto inventario

**a) Input**
Array `codici`, `nomi`, `quantita`, `prezzi` inizializzati staticamente.

**b) Output**
```
==========================================================
                  INVENTARIO MAGAZZINO
==========================================================
  Cod.  | Prodotto               | Qtà  | Prezzo | Valore
--------|------------------------|------|--------|--------
  P001  | Penna blu              |   45 |  0.80€ |  36.00€
  ...
```

**c) Variabili di supporto**
- `i` (`int`): indice del ciclo.
- `valore_riga` (`double`): prodotto quantità × prezzo calcolato per ogni riga.

**d) Vincoli**
- Tutti gli array devono avere la stessa dimensione `NUM_PRODOTTI`.
- Il valore di riga deve essere calcolato per ogni iterazione, non accumulato.

**e) Assunzioni**
- I dati sono statici e validi.
- I prezzi sono positivi e le quantità non negative.

**f) Algoritmo in linguaggio naturale**
```
1. Stampare intestazione e separatori della tabella.
2. Per i da 0 a NUM_PRODOTTI - 1:
   a. Calcolare valore_riga = quantita[i] * prezzi[i].
   b. Stampare codici[i], nomi[i], quantita[i], prezzi[i], valore_riga.
3. Stampare separatore finale.
```

---

### Caso d'uso 2 – Prodotti in esaurimento

**a) Input**
Array `quantita`, costante `SOGLIA_MINIMA`.

**b) Output**
```
Prodotti in esaurimento (quantita <= 10):
  [!] P002 - Quaderno A4: solo 8 pezzi
  [!] P004 - Gomma bianca: solo 6 pezzi
```

**c) Variabili di supporto**
- `trovati` (`int`): conta quanti prodotti sono sotto soglia.

**d) Vincoli**
- Il confronto usa `<=` (la soglia è inclusa nella condizione di esaurimento).
- Il messaggio finale deve comparire solo se `trovati == 0`.

**e) Assunzioni**
- `SOGLIA_MINIMA` è un valore di business configurabile, non hard-coded nel ciclo.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare trovati = 0.
2. Per i da 0 a NUM_PRODOTTI - 1:
   a. Se quantita[i] <= SOGLIA_MINIMA:
      - Stampare il prodotto in esaurimento.
      - Incrementare trovati.
3. Se trovati == 0: stampare messaggio "nessun prodotto".
```

---

### Caso d'uso 3 – Giacenza totale e valore magazzino

**a) Input**
Array `quantita` e `prezzi`.

**b) Output**
```
Giacenza totale    : 224 pezzi
Valore magazzino   : 149.10 euro
```

**c) Variabili di supporto**
- `giacenza_totale` (`int`): somma delle quantità.
- `valore_totale` (`double`): somma dei valori per prodotto.

**d) Vincoli**
- `giacenza_totale` è la somma degli interi: non c'è rischio di troncamento.
- `valore_totale` richiede `double` per non perdere i centesimi.

**e) Assunzioni**
- Le quantità sono sempre non negative.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare giacenza_totale = 0, valore_totale = 0.0.
2. Per i da 0 a NUM_PRODOTTI - 1:
   a. giacenza_totale += quantita[i].
   b. valore_totale += quantita[i] * prezzi[i].
3. Stampare giacenza_totale e valore_totale.
```
