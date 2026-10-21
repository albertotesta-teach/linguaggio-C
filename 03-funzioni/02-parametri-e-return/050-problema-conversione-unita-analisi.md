# Analisi – 050-problema-conversione-unita.c

## 1. Problema
Un convertitore di unità di misura propone un menu con 10 conversioni tra
unità comuni di lunghezza, massa e temperatura. L'utente sceglie il tipo di
conversione e inserisce il valore; il programma stampa il risultato usando la
funzione di conversione appropriata.

## 2. Analisi

### Input

| Variabile | Tipo | Descrizione |
|---|---|---|
| `scelta` | int | Numero della conversione nel menu (1–10) |
| `valore` | double | Quantità da convertire |

### Output
Il menu delle conversioni e, dopo l'inserimento, la riga
`valore unità = risultato unità`: con quattro decimali per lunghezze e masse
(scelte 1–7), con due decimali per le temperature (scelte 8–10). Per una
scelta fuori intervallo: `Scelta non valida.`

### Vincoli
- `scelta` è compresa tra 1 e 10
- Il valore viene richiesto prima di controllare la scelta: anche con una
  scelta non valida l'utente deve inserirlo
- Una temperatura convertita in Kelvin non può essere negativa (sotto lo
  zero assoluto); il programma non lo verifica

### Assunzioni
- L'utente inserisce valori numerici validi
- I fattori di conversione sono approssimati alle cifre indicate nelle
  costanti

### Variabili di supporto

| Variabile | Tipo | Descrizione |
|---|---|---|
| `risultato` | double | Valore convertito restituito dalla funzione |

| Costante | Valore | Descrizione |
|---|---|---|
| `KM_PER_MIGLIO` | 1.60934 | Chilometri in un miglio |
| `CM_PER_POLLICE` | 2.54 | Centimetri in un pollice |
| `KG_PER_LIBBRA` | 0.453592 | Chilogrammi in una libbra |
| `G_PER_ONCIA` | 28.3495 | Grammi in un'oncia |

Le dieci funzioni di conversione hanno tutte la stessa firma: ricevono un
`double` e restituiscono un `double`. Lo schema uniforme rende il codice
prevedibile e facile da estendere.

### Algoritmo in linguaggio naturale
1. Stampare il menu e leggere la scelta.
2. Leggere il valore da convertire.
3. In base alla scelta (catena `if/else if`), chiamare la funzione di
   conversione corrispondente, assegnare il risultato e stamparlo.
4. Se la scelta non corrisponde a nessuna conversione, stampare
   `Scelta non valida.`

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Lunghezza (km → miglia)
- **Input:** scelta `1`, valore `100`
- **Valori intermedi attesi:** 100 / 1.60934 = 62.13727…
- **Output atteso:** `100.0000 km = 62.1373 miglia`

### Test 2 – Temperatura (Celsius → Fahrenheit)
- **Input:** scelta `8`, valore `100`
- **Output atteso:** `100.00 C = 212.00 F`

### Test 3 – Temperatura (Celsius → Kelvin) allo zero assoluto
- **Cosa si verifica:** il caso limite inferiore della scala Kelvin
- **Input:** scelta `10`, valore `-273.15`
- **Output atteso:** `-273.15 C = 0.00 K`

### Test 4 – Scelta non valida
- **Cosa si verifica:** il ramo `else` finale; il valore viene chiesto
  comunque
- **Input:** scelta `11` (oppure `0`), valore qualsiasi
- **Output atteso:** `Scelta non valida.`
