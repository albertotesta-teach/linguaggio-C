# Analisi – 050-problema-scontrino.c

## 1. Problema
L'utente inserisce prezzo unitario e quantità di tre articoli. Il programma
calcola subtotali, totale imponibile, IVA al 22% e totale ivato, stampando
uno scontrino formattato con colonne allineate e bordo ASCII.

## 2. Analisi

### Input

| Variabile       | Tipo     | Significato                               |
|-----------------|----------|-------------------------------------------|
| `prezzo1/2/3`   | `double` | Prezzo unitario di ciascun articolo (EUR) |
| `quantita1/2/3` | `int`    | Quantità acquistata di ciascun articolo   |

### Output
Uno scontrino con bordo ASCII: una riga per articolo con quantità e
importo, poi totale imponibile, IVA al 22% e totale, tutti con due
decimali e colonne allineate.

### Vincoli
- Prezzi e quantità non sono negativi (non verificato dal programma)
- Gli importi non superano 99999.99 EUR, la capienza della larghezza
  `%8.2f`

### Assunzioni
- Per un articolo non acquistato l'utente inserisce prezzo 0 e quantità 0:
  il subtotale risulta 0, comportamento corretto
- L'aliquota IVA è fissa al 22%

### Variabili di supporto

| Variabile           | Tipo     | Significato                              |
|---------------------|----------|------------------------------------------|
| `subtotale1/2/3`    | `double` | prezzo × quantità per ciascun articolo   |
| `totale_imponibile` | `double` | Somma dei tre subtotali                  |
| `importo_iva`       | `double` | totale_imponibile × 0.22                 |
| `totale_ivato`      | `double` | totale_imponibile + importo_iva          |

Costante: `IVA = 0.22`. Il cast `(double)quantita` garantisce che la
moltiplicazione avvenga in virgola mobile.

### Algoritmo in linguaggio naturale
1. Acquisire prezzo e quantità dei tre articoli.
2. Calcolare i tre subtotali.
3. Calcolare totale imponibile, IVA e totale ivato.
4. Stampare lo scontrino formattato.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Acquisto tipico
- **Input:** prezzo1 = 1.50, quantita1 = 3; prezzo2 = 4.90, quantita2 = 2;
  prezzo3 = 0.80, quantita3 = 5
- **Valori intermedi attesi:** subtotali 4.50, 9.80, 4.00;
  totale_imponibile = 18.30; importo_iva = 4.026 → 4.03;
  totale_ivato = 22.326 → 22.33
- **Output atteso:**
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

### Test 2 – Un solo articolo, gli altri a zero
- **Cosa si verifica:** prezzo 0 e quantità 0 producono subtotale 0
- **Input:** prezzo1 = 0.20, quantita1 = 100; prezzo2 = 0.00, quantita2 = 0;
  prezzo3 = 0.00, quantita3 = 0
- **Valori intermedi attesi:** subtotale1 = 20.00; importo_iva = 4.40
- **Output atteso (righe che cambiano):**
```
| Articolo 1          100      20.00  |
| Articolo 2            0       0.00  |
| Articolo 3            0       0.00  |
| Totale imponibile           20.00   |
| IVA 22%                      4.40   |
| TOTALE                      24.40   |
```

### Test 3 – Articoli di alto valore
- **Cosa si verifica:** importi a tre cifre e arrotondamento dell'IVA
- **Input:** prezzo1 = 299.99, quantita1 = 1; prezzo2 = 49.90, quantita2 = 2;
  prezzo3 = 9.99, quantita3 = 3
- **Valori intermedi attesi:** subtotali 299.99, 99.80, 29.97;
  totale_imponibile = 429.76; importo_iva = 94.5472 → 94.55;
  totale_ivato = 524.3072 → 524.31
- **Output atteso (righe che cambiano):**
```
| Articolo 1            1     299.99  |
| Articolo 2            2      99.80  |
| Articolo 3            3      29.97  |
| Totale imponibile          429.76   |
| IVA 22%                     94.55   |
| TOTALE                     524.31   |
```
