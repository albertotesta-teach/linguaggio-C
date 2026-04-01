# Analisi – 070-problema-cambio-valuta.c

## 1. Problema
L'utente inserisce un importo in EUR e sceglie la valuta di destinazione
(USD, GBP, JPY, CHF). Il tasso di cambio viene selezionato con l'operatore
ternario annidato. Il programma calcola l'importo convertito, la commissione
(1.5%) e l'importo netto, stampando il dettaglio della transazione.

## 2. Analisi generale e struttura dati

| Variabile               | Tipo     | Significato                                   |
|-------------------------|----------|-----------------------------------------------|
| `importo_eur`           | `double` | Importo da convertire in EUR                  |
| `scelta`                | `int`    | Valuta scelta: 1=USD, 2=GBP, 3=JPY, 4=CHF    |
| `tasso`                 | `double` | Tasso selezionato con operatore ternario      |
| `importo_convertito`    | `double` | importo_eur × tasso                          |
| `importo_commissione`   | `double` | importo_convertito × COMMISSIONE             |
| `importo_netto`         | `double` | importo_convertito − importo_commissione     |

Costanti: `TASSO_USD=1.085`, `TASSO_GBP=0.857`, `TASSO_JPY=161.5`,
`TASSO_CHF=0.963`, `COMMISSIONE=0.015`

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Conversione in USD

**a) Input**
- importo_eur = 200.00, scelta = 1

**b) Output**
```
  Importo originale:     200.00 EUR
  Valuta:                   USD
  Tasso di cambio:       1.0850
  Importo convertito:   217.00
  Commissione (1.5%):     3.26
  Importo netto:        213.75
```

**c) Variabili di supporto**
- tasso = TASSO_USD = 1.085
- importo_convertito = 200.00 × 1.085 = 217.00
- importo_commissione = 217.00 × 0.015 = 3.255 → 3.26
- importo_netto = 217.00 − 3.255 = 213.745 → 213.74

**d) Vincoli**
- `importo_eur > 0` (non validato)
- Per scelta diversa da 1/2/3 viene usato il tasso CHF

**e) Assunzioni**
- I tassi sono indicativi e non aggiornati in tempo reale

**f) Algoritmo in linguaggio naturale**
1. Acquisire importo e scelta della valuta
2. Selezionare il tasso con operatore ternario annidato
3. Calcolare importo convertito = importo × tasso
4. Calcolare commissione = convertito × COMMISSIONE (con *=)
5. Calcolare netto = convertito − commissione
6. Stampare il dettaglio con il simbolo valuta selezionato via ternario

---

### Caso d'uso 2 – Conversione in JPY (valuta a tasso alto)

**a) Input**
- importo_eur = 50.00, scelta = 3

**b) Output**
```
  Valuta:                   JPY
  Tasso di cambio:     161.5000
  Importo convertito: 8075.00
  Commissione (1.5%):  121.13
  Importo netto:      7953.88
```

**c) Variabili di supporto**
- tasso = TASSO_JPY = 161.5
- importo_convertito = 50.00 × 161.5 = 8075.00
- importo_commissione = 8075.00 × 0.015 = 121.125 → 121.13

**d) Vincoli** — identici al caso d'uso 1

**e) Assunzioni** — identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale** — identico al caso d'uso 1

---

### Caso d'uso 3 – Conversione in CHF

**a) Input**
- importo_eur = 1000.00, scelta = 4

**b) Output**
```
  Valuta:                   CHF
  Tasso di cambio:       0.9630
  Importo convertito:   963.00
  Commissione (1.5%):    14.45
  Importo netto:        948.56
```

**c) Variabili di supporto**
- tasso = TASSO_CHF = 0.963
- importo_convertito = 1000.00 × 0.963 = 963.00
- importo_commissione = 963.00 × 0.015 = 14.445 → 14.45
- importo_netto = 963.00 − 14.445 = 948.555 → 948.56

**d) Vincoli** — identici al caso d'uso 1

**e) Assunzioni** — identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale** — identico al caso d'uso 1
