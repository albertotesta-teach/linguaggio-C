# Analisi – 050-problema-scontrino.c

## 1. Problema
L'utente inserisce prezzo unitario e quantità di tre articoli. Il programma
calcola subtotali, totale imponibile, IVA al 22% e totale ivato, stampando
uno scontrino formattato con colonne allineate e bordo ASCII.

## 2. Analisi generale e struttura dati

| Variabile             | Tipo     | Significato                               |
|-----------------------|----------|-------------------------------------------|
| `prezzo1/2/3`         | `double` | Prezzo unitario di ciascun articolo (EUR) |
| `quantita1/2/3`       | `int`    | Quantità acquistata di ciascun articolo   |
| `subtotale1/2/3`      | `double` | prezzo × quantità per ciascun articolo    |
| `totale_imponibile`   | `double` | Somma dei tre subtotali                   |
| `importo_iva`         | `double` | totale_imponibile × 0.22                  |
| `totale_ivato`        | `double` | totale_imponibile + importo_iva           |

Costante: `IVA = 0.22`

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Acquisto tipico

**a) Input**
- prezzo1 = 1.50, quantita1 = 3
- prezzo2 = 4.90, quantita2 = 2
- prezzo3 = 0.80, quantita3 = 5

**b) Output**
```
+-------------------------------------+
|        SCONTRINO FISCALE            |
+-------------------------------------+
| Articolo           Qta'   Importo   |
+-------------------------------------+
| Articolo 1            3      4.50   |
| Articolo 2            2      9.80   |
| Articolo 3            5      4.00   |
+-------------------------------------+
| Totale imponibile           18.30   |
| IVA 22%                      4.03   |
+-------------------------------------+
| TOTALE                      22.33   |
+-------------------------------------+
```

**c) Variabili di supporto**
- subtotale1 = 1.50 × 3 = 4.50
- subtotale2 = 4.90 × 2 = 9.80
- subtotale3 = 0.80 × 5 = 4.00
- totale_imponibile = 18.30
- importo_iva = 18.30 × 0.22 = 4.026 → 4.03
- totale_ivato = 22.326 → 22.33

**d) Vincoli**
- I prezzi devono essere positivi (non validati)
- Le quantità devono essere positive (non validate)

**e) Assunzioni**
- Il cast `(double)quantita` garantisce che la moltiplicazione
  avvenga in virgola mobile

**f) Algoritmo in linguaggio naturale**
1. Acquisire prezzo e quantità di tre articoli
2. Calcolare i tre subtotali
3. Calcolare totale imponibile, IVA e totale ivato
4. Stampare lo scontrino formattato

---

### Caso d'uso 2 – Un solo articolo con quantità alta

**a) Input**
- prezzo1 = 0.20, quantita1 = 100
- prezzo2 = 0.00, quantita2 = 0
- prezzo3 = 0.00, quantita3 = 0

**b) Output**
```
| Articolo 1          100      20.00  |
| Articolo 2            0       0.00  |
| Articolo 3            0       0.00  |
| Totale imponibile           20.00   |
| IVA 22%                      4.40   |
| TOTALE                      24.40   |
```

**c) Variabili di supporto**
- subtotale1 = 0.20 × 100 = 20.00

**d) Vincoli**
- Quantità 0 e prezzo 0 producono subtotale 0, comportamento corretto

**e) Assunzioni**
- L'utente può inserire 0 per articoli non presenti

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1

---

### Caso d'uso 3 – Articoli di alto valore

**a) Input**
- prezzo1 = 299.99, quantita1 = 1
- prezzo2 = 49.90, quantita2 = 2
- prezzo3 = 9.99, quantita3 = 3

**b) Output**
```
| Articolo 1            1     299.99  |
| Articolo 2            2      99.80  |
| Articolo 3            3      29.97  |
| Totale imponibile          429.76   |
| IVA 22%                     94.55   |
| TOTALE                     524.31   |
```

**c) Variabili di supporto**
- subtotale1 = 299.99
- subtotale2 = 99.80
- subtotale3 = 29.97
- totale_imponibile = 429.76
- importo_iva = 429.76 × 0.22 = 94.5472 → 94.55
- totale_ivato = 524.3072 → 524.31

**d) Vincoli**
- La larghezza `%8.2f` è sufficiente per importi fino a 99999.99 EUR

**e) Assunzioni**
- Identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1
