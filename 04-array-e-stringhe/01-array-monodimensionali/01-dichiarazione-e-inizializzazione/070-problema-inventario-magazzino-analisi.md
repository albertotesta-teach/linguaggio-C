# Analisi – 070-problema-inventario-magazzino.c

## 1. Problema

Un negozio vuole un programma che gestisca l'inventario di 6 prodotti. Il sistema
deve stampare un prospetto formattato con quantità e prezzi, segnalare i prodotti
in esaurimento sotto una soglia configurabile e calcolare la giacenza totale
e il valore complessivo del magazzino.

---

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice in quattro
array paralleli, in cui l'indice `i` identifica lo stesso prodotto.

| Variabile  | Tipo       | Dimensione | Descrizione                                 |
|------------|------------|------------|---------------------------------------------|
| `codici`   | `char[][]` | 6 × 8      | Codice del prodotto (max 7 caratteri)       |
| `nomi`     | `char[][]` | 6 × 25     | Nome del prodotto (max 24 caratteri)        |
| `quantita` | `int[]`    | 6          | Pezzi disponibili                           |
| `prezzi`   | `double[]` | 6          | Prezzo unitario in euro                     |

### Output
- Il prospetto dell'inventario: codice, nome, quantità, prezzo e valore
  (quantità × prezzo) di ogni prodotto;
- l'elenco dei prodotti in esaurimento, oppure il messaggio
  "Nessun prodotto in esaurimento.";
- la giacenza totale (somma dei pezzi) e il valore del magazzino in euro.

### Vincoli
- Tutti gli array hanno la stessa dimensione `NUM_PRODOTTI`
- Un prodotto è in esaurimento se la quantità è **minore o uguale** a
  `SOGLIA_MINIMA`: la soglia è inclusa
- Il messaggio "Nessun prodotto in esaurimento." compare solo se nessun
  prodotto è sotto soglia
- Il valore del magazzino è in `double` per non perdere i centesimi

### Assunzioni
- Prezzi positivi e quantità non negative
- La soglia è una costante modificabile in un solo punto

### Variabili di supporto

| Variabile         | Tipo      | Descrizione                                  |
|-------------------|-----------|----------------------------------------------|
| `valore_riga`     | `double`  | Quantità × prezzo del singolo prodotto       |
| `trovati`         | `int`     | Numero di prodotti sotto soglia              |
| `giacenza_totale` | `int`     | Somma delle quantità                         |
| `valore_totale`   | `double`  | Somma dei valori dei prodotti                |
| `SOGLIA_MINIMA`   | `#define` | 10                                           |
| `NUM_PRODOTTI`    | `#define` | 6                                            |

### Algoritmo in linguaggio naturale
1. Stampare l'intestazione e, per ogni prodotto, codice, nome, quantità,
   prezzo e `valore_riga = quantita[i] × prezzi[i]`.
2. Porre `trovati = 0`; per ogni prodotto con quantità ≤ soglia stamparlo
   e incrementare `trovati`.
3. Se `trovati` vale 0 stampare che non ci sono prodotti in esaurimento.
4. Sommare quantità e valori di tutti i prodotti e stampare giacenza totale
   e valore del magazzino.

---

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; i test 2 e 3
richiedono di modificare l'array `quantita` e ricompilare.

### Test 1 – Inventario con i dati del programma
- **Input:** quantità 45, 8, 120, 6, 30, 15
- **Output atteso:**
```
  P001  | Penna blu              |   45 |  0.80€ |  36.00€
  P002  | Quaderno A4            |    8 |  1.50€ |  12.00€
  P003  | Matita HB              |  120 |  0.40€ |  48.00€
  P004  | Gomma bianca           |    6 |  0.60€ |   3.60€
  P005  | Righello 30cm          |   30 |  1.20€ |  36.00€
  P006  | Temperamatite          |   15 |  0.90€ |  13.50€
==========================================================

Prodotti in esaurimento (quantita <= 10):
  [!] P002 - Quaderno A4: solo 8 pezzi
  [!] P004 - Gomma bianca: solo 6 pezzi

Giacenza totale    : 224 pezzi
Valore magazzino   : 149.10 euro
```

### Test 2 – Quantità esattamente uguale alla soglia
- **Cosa si verifica:** la soglia è inclusa (`<=`), 11 non lo è
- **Procedura:** porre le quantità a `{45, 10, 120, 11, 30, 15}`
- **Output atteso:** un solo prodotto in esaurimento,
  `[!] P002 - Quaderno A4: solo 10 pezzi`

### Test 3 – Nessun prodotto in esaurimento
- **Cosa si verifica:** il messaggio alternativo
- **Procedura:** porre le quantità a `{45, 18, 120, 16, 30, 15}`
- **Output atteso:** `Nessun prodotto in esaurimento.`
