# Analisi – 050-problema-calcolo-bolletta.c

## 1. Problema
L'utente inserisce le letture del contatore elettrico, la potenza impegnata
e la fascia oraria. Il programma calcola i kWh consumati, il costo energia,
la quota fissa e il totale con IVA al 10%. Il prezzo per fascia viene
selezionato con l'operatore ternario annidato, senza if/else.

## 2. Analisi generale e struttura dati

| Variabile             | Tipo     | Significato                                   |
|-----------------------|----------|-----------------------------------------------|
| `lettura_precedente`  | `int`    | Lettura precedente del contatore (kWh)        |
| `lettura_attuale`     | `int`    | Lettura attuale del contatore (kWh)           |
| `potenza_kw`          | `double` | Potenza impegnata (kW)                        |
| `fascia`              | `int`    | Fascia oraria: 1=F1, 2=F2, 3=F3              |
| `kwh_consumati`       | `int`    | lettura_attuale − lettura_precedente          |
| `prezzo_kwh`          | `double` | Prezzo selezionato con operatore ternario     |
| `costo_energia`       | `double` | kwh_consumati × prezzo_kwh                   |
| `quota_fissa`         | `double` | potenza_kw × QUOTA_FISSA_PER_KW              |
| `imponibile`          | `double` | costo_energia + quota_fissa                  |
| `importo_iva`         | `double` | imponibile × IVA_DOMESTICA                   |
| `totale`              | `double` | imponibile + importo_iva                     |

Costanti: `PREZZO_F1=0.28`, `PREZZO_F2=0.22`, `PREZZO_F3=0.18`,
`QUOTA_FISSA_PER_KW=10.50`, `IVA_DOMESTICA=0.10`

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Consumo medio fascia F1

**a) Input**
- lettura_precedente = 1000, lettura_attuale = 1180
- potenza_kw = 3.0, fascia = 1

**b) Output**
```
  Consumo:               180 kWh
  Fascia:                  1
  Prezzo/kWh:          0.2800 EUR
  Costo energia:       50.40 EUR
  Quota fissa:         31.50 EUR
  Imponibile:          81.90 EUR
  IVA 10%:              8.19 EUR
  TOTALE:              90.09 EUR
```

**c) Variabili di supporto**
- kwh_consumati = 1180 − 1000 = 180
- prezzo_kwh = PREZZO_F1 = 0.28
- costo_energia = 180 × 0.28 = 50.40
- quota_fissa = 3.0 × 10.50 = 31.50
- imponibile = 81.90, IVA = 8.19, totale = 90.09

**d) Vincoli**
- `lettura_attuale >= lettura_precedente` (non validato)
- `fascia` ∈ {1, 2, 3}: per valori diversi viene usato il prezzo F3

**e) Assunzioni**
- I tassi sono indicativi e non corrispondono a tariffe ufficiali aggiornate

**f) Algoritmo in linguaggio naturale**
1. Acquisire letture, potenza, fascia
2. Calcolare consumo = lettura_attuale − lettura_precedente
3. Selezionare prezzo con operatore ternario annidato su fascia
4. Calcolare costo energia, quota fissa, IVA, totale
5. Stampare la bolletta formattata

---

### Caso d'uso 2 – Consumo basso fascia F3

**a) Input**
- lettura_precedente = 500, lettura_attuale = 560
- potenza_kw = 1.5, fascia = 3

**b) Output**
```
  Consumo:                60 kWh
  Prezzo/kWh:          0.1800 EUR
  Costo energia:       10.80 EUR
  Quota fissa:         15.75 EUR
  Imponibile:          26.55 EUR
  IVA 10%:              2.66 EUR
  TOTALE:              29.21 EUR
```

**c) Variabili di supporto**
- prezzo_kwh = PREZZO_F3 = 0.18

**d) Vincoli** — identici al caso d'uso 1

**e) Assunzioni** — identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale** — identico al caso d'uso 1

---

### Caso d'uso 3 – Consumo elevato fascia F2

**a) Input**
- lettura_precedente = 200, lettura_attuale = 600
- potenza_kw = 6.0, fascia = 2

**b) Output**
```
  Consumo:               400 kWh
  Prezzo/kWh:          0.2200 EUR
  Costo energia:       88.00 EUR
  Quota fissa:         63.00 EUR
  Imponibile:         151.00 EUR
  IVA 10%:             15.10 EUR
  TOTALE:             166.10 EUR
```

**c) Variabili di supporto**
- prezzo_kwh = PREZZO_F2 = 0.22
- costo_energia = 400 × 0.22 = 88.00
- quota_fissa = 6.0 × 10.50 = 63.00

**d) Vincoli** — identici al caso d'uso 1

**e) Assunzioni** — identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale** — identico al caso d'uso 1
