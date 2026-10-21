# Analisi – 070-problema-scheda-prodotto.c

## 1. Problema
L'utente inserisce i dati numerici di un prodotto a magazzino: codice,
prezzo unitario, quantità disponibile e percentuale di sconto. Il programma
calcola il prezzo scontato, il risparmio unitario e il valore totale del
magazzino, stampando una scheda prodotto formattata.

## 2. Analisi

### Input

| Variabile         | Tipo     | Significato                          |
|-------------------|----------|--------------------------------------|
| `codice`          | `int`    | Codice numerico del prodotto         |
| `prezzo_unitario` | `double` | Prezzo senza sconto (EUR)            |
| `quantita`        | `int`    | Pezzi disponibili in magazzino       |
| `sconto_percento` | `double` | Percentuale di sconto (es. 15.0)     |

### Output
Una scheda prodotto con il codice su sei cifre, prezzo pieno, percentuale
di sconto, risparmio unitario, prezzo scontato, quantità e valore del
magazzino, con importi a due cifre decimali e colonne allineate.

### Vincoli
- `prezzo_unitario` > 0
- `quantita` >= 0
- `sconto_percento` compreso tra 0.0 e 100.0
- I vincoli non vengono verificati dal programma

### Assunzioni
- Il valore del magazzino è calcolato al prezzo pieno (valore contabile)
- I valori inseriti sono coerenti con la realtà
- Con sconto 0 i calcoli producono i valori corretti senza alcuna gestione
  speciale

### Variabili di supporto

| Variabile          | Tipo     | Significato                               |
|--------------------|----------|-------------------------------------------|
| `fattore_sconto`   | `double` | Sconto espresso come frazione (es. 0.15)  |
| `risparmio`        | `double` | Risparmio per unità (EUR)                 |
| `prezzo_scontato`  | `double` | Prezzo dopo lo sconto (EUR)               |
| `valore_magazzino` | `double` | Prezzo pieno × quantità (EUR)             |

Il cast `(double)quantita` nella moltiplicazione con `prezzo_unitario`
garantisce che il calcolo avvenga in virgola mobile anche con quantità
grandi, evitando l'overflow sugli interi.

### Algoritmo in linguaggio naturale
1. Acquisire codice, prezzo, quantità e percentuale di sconto.
2. Calcolare `fattore_sconto = sconto_percento / 100`.
3. Calcolare `risparmio = prezzo_unitario × fattore_sconto`.
4. Calcolare `prezzo_scontato = prezzo_unitario − risparmio`.
5. Calcolare `valore_magazzino = prezzo_unitario × quantita`.
6. Stampare la scheda formattata.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Prodotto con sconto standard (caso tipico)
- **Input:** codice = 1042, prezzo_unitario = 24.90, quantita = 100,
  sconto_percento = 10.0
- **Valori intermedi attesi:** fattore_sconto = 0.10; risparmio = 2.49;
  prezzo_scontato = 22.41; valore_magazzino = 2490.00
- **Output atteso:**
```
====================================
  SCHEDA PRODOTTO
====================================
  Codice:           001042
  Prezzo pieno:      24.90 EUR
  Sconto:            10.0 %
  Risparmio:          2.49 EUR
  Prezzo scontato:   22.41 EUR
------------------------------------
  Quantita':            100 pz
  Valore magazzino:  2490.00 EUR
====================================
```

### Test 2 – Nessuno sconto
- **Cosa si verifica:** con sconto 0 il prezzo scontato coincide con il
  prezzo pieno
- **Input:** codice = 5, prezzo_unitario = 9.99, quantita = 250,
  sconto_percento = 0.0
- **Valori intermedi attesi:** fattore_sconto = 0.0; risparmio = 0.0;
  prezzo_scontato = 9.99
- **Output atteso (righe che cambiano):**
```
  Sconto:             0.0 %
  Risparmio:          0.00 EUR
  Prezzo scontato:    9.99 EUR
  Valore magazzino: 2497.50 EUR
```

### Test 3 – Prodotto di alto valore con sconto elevato
- **Cosa si verifica:** importi a quattro cifre e codice a cinque cifre
- **Input:** codice = 99001, prezzo_unitario = 1299.00, quantita = 5,
  sconto_percento = 25.0
- **Valori intermedi attesi:** fattore_sconto = 0.25; risparmio = 324.75;
  prezzo_scontato = 974.25; valore_magazzino = 6495.00
- **Output atteso (righe che cambiano):**
```
  Codice:           099001
  Prezzo pieno:    1299.00 EUR
  Sconto:            25.0 %
  Risparmio:        324.75 EUR
  Prezzo scontato:  974.25 EUR
  Quantita':              5 pz
  Valore magazzino: 6495.00 EUR
```
