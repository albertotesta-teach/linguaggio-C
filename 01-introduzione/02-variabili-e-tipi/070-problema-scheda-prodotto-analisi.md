# Analisi – 070-problema-scheda-prodotto.c

## 1. Problema
L'utente inserisce i dati numerici di un prodotto a magazzino: codice,
prezzo unitario, quantità disponibile e percentuale di sconto. Il programma
calcola il prezzo scontato, il risparmio unitario e il valore totale del
magazzino, stampando una scheda prodotto formattata.

## 2. Analisi generale e struttura dati

| Variabile           | Tipo     | Significato                                     |
|---------------------|----------|-------------------------------------------------|
| `codice`            | `int`    | Codice numerico del prodotto                    |
| `prezzo_unitario`   | `double` | Prezzo senza sconto (EUR)                       |
| `quantita`          | `int`    | Pezzi disponibili in magazzino                  |
| `sconto_percento`   | `double` | Percentuale di sconto (es. 15.0)                |
| `fattore_sconto`    | `double` | Sconto espresso come frazione (es. 0.15)        |
| `risparmio`         | `double` | Risparmio per unità (EUR)                       |
| `prezzo_scontato`   | `double` | Prezzo dopo lo sconto (EUR)                     |
| `valore_magazzino`  | `double` | Prezzo pieno × quantità (EUR)                   |

Il cast `(double)quantita` nella moltiplicazione con `prezzo_unitario`
è una scelta difensiva per evitare overflow su interi grandi.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prodotto con sconto standard

**a) Input**
- codice = 1042, prezzo_unitario = 24.90, quantita = 100, sconto_percento = 10.0

**b) Output**
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

**c) Variabili di supporto**
- fattore_sconto = 10.0 / 100.0 = 0.10
- risparmio = 24.90 * 0.10 = 2.49
- prezzo_scontato = 24.90 - 2.49 = 22.41
- valore_magazzino = 24.90 * 100 = 2490.00

**d) Vincoli**
- `prezzo_unitario` > 0
- `quantita` >= 0
- `sconto_percento` compreso tra 0.0 e 100.0
  (non validati in questo esempio)

**e) Assunzioni**
- Il valore di magazzino è calcolato al prezzo pieno (valore contabile)
- I valori inseriti sono coerenti con la realtà

**f) Algoritmo in linguaggio naturale**
1. Acquisire codice, prezzo, quantità, percentuale di sconto
2. Calcolare fattore_sconto = sconto_percento / 100
3. Calcolare risparmio = prezzo * fattore_sconto
4. Calcolare prezzo_scontato = prezzo - risparmio
5. Calcolare valore_magazzino = prezzo * quantità
6. Stampare la scheda formattata

---

### Caso d'uso 2 – Nessuno sconto

**a) Input**
- codice = 5, prezzo_unitario = 9.99, quantita = 250, sconto_percento = 0.0

**b) Output**
```
  Sconto:             0.0 %
  Risparmio:          0.00 EUR
  Prezzo scontato:    9.99 EUR
  Valore magazzino: 2497.50 EUR
```

**c) Variabili di supporto**
- fattore_sconto = 0.0
- risparmio = 0.0
- prezzo_scontato = 9.99

**d) Vincoli**
- Con sconto 0 il prezzo scontato coincide con il prezzo pieno

**e) Assunzioni**
- Identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1; con sconto 0 i calcoli producono i valori corretti
  senza alcuna gestione speciale

---

### Caso d'uso 3 – Prodotto di alto valore, sconto elevato

**a) Input**
- codice = 99001, prezzo_unitario = 1299.00, quantita = 5, sconto_percento = 25.0

**b) Output**
```
  Codice:           099001
  Prezzo pieno:    1299.00 EUR
  Sconto:            25.0 %
  Risparmio:        324.75 EUR
  Prezzo scontato:  974.25 EUR
  Quantita':              5 pz
  Valore magazzino: 6495.00 EUR
```

**c) Variabili di supporto**
- fattore_sconto = 0.25
- risparmio = 1299.00 * 0.25 = 324.75
- prezzo_scontato = 1299.00 - 324.75 = 974.25
- valore_magazzino = 1299.00 * 5 = 6495.00

**d) Vincoli**
- Il cast `(double)quantita` garantisce che la moltiplicazione avvenga
  in virgola mobile anche con quantità grandi

**e) Assunzioni**
- Identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1
