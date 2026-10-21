# Analisi – 070-problema-cambio-valuta.c

## 1. Problema
L'utente inserisce un importo in EUR e sceglie la valuta di destinazione
(USD, GBP, JPY, CHF). Il tasso di cambio viene selezionato con l'operatore
ternario annidato. Il programma calcola l'importo convertito, la commissione
(1.5%) e l'importo netto, stampando il dettaglio della transazione.

## 2. Analisi

### Input

| Variabile     | Tipo     | Significato                                 |
|---------------|----------|---------------------------------------------|
| `importo_eur` | `double` | Importo da convertire in EUR                |
| `scelta`      | `int`    | Valuta scelta: 1=USD, 2=GBP, 3=JPY, 4=CHF   |

### Output
Il dettaglio della transazione: importo originale, sigla della valuta,
tasso di cambio (quattro decimali), importo convertito, commissione e
importo netto (due decimali).

### Vincoli
- `importo_eur > 0` (non verificato dal programma)
- `scelta` vale 1, 2, 3 o 4; per qualsiasi valore diverso da 1, 2 e 3 il
  ternario annidato seleziona il tasso CHF

### Assunzioni
- I tassi sono indicativi e non aggiornati in tempo reale
- La commissione è calcolata sull'importo convertito

### Variabili di supporto

| Variabile             | Tipo     | Significato                                |
|-----------------------|----------|--------------------------------------------|
| `tasso`               | `double` | Tasso selezionato con operatore ternario   |
| `importo_convertito`  | `double` | importo_eur × tasso                        |
| `importo_commissione` | `double` | importo_convertito × COMMISSIONE           |
| `importo_netto`       | `double` | importo_convertito − importo_commissione   |

Costanti: `TASSO_USD=1.085`, `TASSO_GBP=0.857`, `TASSO_JPY=161.5`,
`TASSO_CHF=0.963`, `COMMISSIONE=0.015`

### Algoritmo in linguaggio naturale
1. Acquisire l'importo e la scelta della valuta.
2. Selezionare il tasso con l'operatore ternario annidato.
3. Calcolare `importo_convertito = importo_eur × tasso`.
4. Calcolare la commissione moltiplicando per `COMMISSIONE` (con `*=`).
5. Calcolare `importo_netto = importo_convertito − importo_commissione`.
6. Stampare il dettaglio con la sigla della valuta, scelta anch'essa con
   il ternario.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Conversione in USD
- **Input:** importo_eur = 200.00, scelta = 1
- **Valori intermedi attesi:** tasso = 1.085; importo_convertito = 217.00;
  importo_commissione = 3.255; importo_netto = 213.745
- **Output atteso:**
```
Importo originale:       200.00 EUR
Valuta:                     USD
Tasso di cambio:         1.0850
Importo convertito:      217.00
Commissione (1.5%):       3.25
------------------------------
Importo netto:           213.75
```
- **Nota:** la commissione vale 3.255, ma viene stampata 3.25 e non 3.26:
  in binario 3.255 non è rappresentabile esattamente e il `double` contiene
  3.25499999…, che `%.2f` arrotonda per difetto. Per lo stesso motivo
  213.745 diventa 213.75. Con gli importi in denaro conviene lavorare in
  centesimi interi (vedi i capitoli successivi).

### Test 2 – Conversione in JPY (valuta a tasso alto)
- **Cosa si verifica:** importi convertiti a quattro cifre
- **Input:** importo_eur = 50.00, scelta = 3
- **Valori intermedi attesi:** tasso = 161.5; importo_convertito = 8075.00;
  importo_commissione = 121.125
- **Output atteso (righe che cambiano):**
```
Valuta:                     JPY
Tasso di cambio:       161.5000
Importo convertito:     8075.00
Commissione (1.5%):     121.12
------------------------------
Importo netto:          7953.88
```
- **Nota:** 121.125 è rappresentabile esattamente in binario: è un caso
  "a metà" e `printf` lo arrotonda alla cifra pari, quindi stampa 121.12.

### Test 3 – Conversione in CHF
- **Cosa si verifica:** l'ultimo ramo del ternario annidato
- **Input:** importo_eur = 1000.00, scelta = 4
- **Valori intermedi attesi:** tasso = 0.963; importo_convertito = 963.00;
  importo_commissione = 14.445; importo_netto = 948.555
- **Output atteso (righe che cambiano):**
```
Valuta:                     CHF
Tasso di cambio:         0.9630
Importo convertito:      963.00
Commissione (1.5%):      14.45
------------------------------
Importo netto:           948.55
```
- **Nota:** 948.555 è memorizzato come 948.55499…, quindi viene stampato
  948.55.
