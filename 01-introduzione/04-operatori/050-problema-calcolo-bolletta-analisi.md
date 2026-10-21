# Analisi – 050-problema-calcolo-bolletta.c

## 1. Problema
L'utente inserisce le letture del contatore elettrico, la potenza impegnata
e la fascia oraria. Il programma calcola i kWh consumati, il costo energia,
la quota fissa e il totale con IVA al 10%. Il prezzo per fascia viene
selezionato con l'operatore ternario annidato, senza if/else.

## 2. Analisi

### Input

| Variabile            | Tipo     | Significato                              |
|----------------------|----------|------------------------------------------|
| `lettura_precedente` | `int`    | Lettura precedente del contatore (kWh)   |
| `lettura_attuale`    | `int`    | Lettura attuale del contatore (kWh)      |
| `potenza_kw`         | `double` | Potenza impegnata (kW)                   |
| `fascia`             | `int`    | Fascia oraria: 1=F1, 2=F2, 3=F3          |

### Output
Il dettaglio della bolletta: consumo in kWh, fascia, prezzo al kWh (quattro
decimali), costo energia, quota fissa, imponibile, IVA al 10% e totale
(due decimali).

### Vincoli
- `lettura_attuale >= lettura_precedente` (non verificato dal programma)
- `fascia` vale 1, 2 o 3; per qualsiasi altro valore il ternario annidato
  seleziona il prezzo della fascia F3

### Assunzioni
- I prezzi sono indicativi e non corrispondono a tariffe ufficiali aggiornate
- La quota fissa è proporzionale alla potenza impegnata

### Variabili di supporto

| Variabile       | Tipo     | Significato                                |
|-----------------|----------|--------------------------------------------|
| `kwh_consumati` | `int`    | lettura_attuale − lettura_precedente       |
| `prezzo_kwh`    | `double` | Prezzo selezionato con operatore ternario  |
| `costo_energia` | `double` | kwh_consumati × prezzo_kwh                 |
| `quota_fissa`   | `double` | potenza_kw × QUOTA_FISSA_PER_KW            |
| `imponibile`    | `double` | costo_energia + quota_fissa                |
| `importo_iva`   | `double` | imponibile × IVA_DOMESTICA                 |
| `totale`        | `double` | imponibile + importo_iva                   |

Costanti: `PREZZO_F1=0.28`, `PREZZO_F2=0.22`, `PREZZO_F3=0.18`,
`QUOTA_FISSA_PER_KW=10.50`, `IVA_DOMESTICA=0.10`

### Algoritmo in linguaggio naturale
1. Acquisire le due letture, la potenza e la fascia.
2. Calcolare `kwh_consumati = lettura_attuale − lettura_precedente`.
3. Selezionare il prezzo con l'operatore ternario annidato sulla fascia.
4. Calcolare costo energia, quota fissa, imponibile, IVA e totale.
5. Stampare la bolletta formattata.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso. Serve almeno un test per ciascuna fascia.

### Test 1 – Consumo medio in fascia F1
- **Input:** lettura_precedente = 1000, lettura_attuale = 1180,
  potenza_kw = 3.0, fascia = 1
- **Valori intermedi attesi:** kwh_consumati = 180; prezzo_kwh = 0.28;
  costo_energia = 50.40; quota_fissa = 31.50; imponibile = 81.90;
  importo_iva = 8.19; totale = 90.09
- **Output atteso:**
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

### Test 2 – Consumo basso in fascia F3
- **Input:** lettura_precedente = 500, lettura_attuale = 560,
  potenza_kw = 1.5, fascia = 3
- **Valori intermedi attesi:** kwh_consumati = 60; prezzo_kwh = 0.18
- **Output atteso (righe che cambiano):**
```
  Consumo:                60 kWh
  Prezzo/kWh:          0.1800 EUR
  Costo energia:       10.80 EUR
  Quota fissa:         15.75 EUR
  Imponibile:          26.55 EUR
  IVA 10%:              2.66 EUR
  TOTALE:              29.21 EUR
```

### Test 3 – Consumo elevato in fascia F2
- **Input:** lettura_precedente = 200, lettura_attuale = 600,
  potenza_kw = 6.0, fascia = 2
- **Valori intermedi attesi:** kwh_consumati = 400; prezzo_kwh = 0.22;
  costo_energia = 88.00; quota_fissa = 63.00
- **Output atteso (righe che cambiano):**
```
  Consumo:               400 kWh
  Prezzo/kWh:          0.2200 EUR
  Costo energia:       88.00 EUR
  Quota fissa:         63.00 EUR
  Imponibile:         151.00 EUR
  IVA 10%:             15.10 EUR
  TOTALE:             166.10 EUR
```
