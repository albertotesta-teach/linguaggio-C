# Analisi – 050-problema-conversione-unita.c

## 1. Problema
Un convertitore di unità di misura propone un menu con 10 conversioni tra
unità comuni di lunghezza, massa e temperatura. L'utente sceglie il tipo di
conversione e inserisce il valore; il programma stampa il risultato usando la
funzione di conversione appropriata.

## 2. Analisi generale e struttura dati

| Costante | Valore | Descrizione |
|---|---|---|
| `KM_PER_MIGLIO` | 1.60934 | Fattore km → miglia |
| `CM_PER_POLLICE` | 2.54 | Fattore cm → pollici |
| `KG_PER_LIBBRA` | 0.453592 | Fattore kg → libbre |
| `G_PER_ONCIA` | 28.3495 | Fattore g → once |

| Variabile | Tipo | Descrizione |
|---|---|---|
| `scelta` | int | Numero del menu scelto dall'utente |
| `valore` | double | Quantità da convertire |
| `risultato` | double | Valore convertito restituito dalla funzione |

Le funzioni di conversione seguono tutte la stessa firma: ricevono un `double`
e restituiscono un `double`. Questo schema uniforme rende il codice prevedibile
e facilmente estendibile.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Conversione di lunghezza (km → miglia)

**a) Input** – scelta `1`, valore `100.0`

**b) Output** – `100.0000 km = 62.1371 miglia`

**c) Variabili di supporto** – `risultato = km_in_miglia(valore)`

**d) Vincoli** – il valore deve essere un numero reale positivo (assunto per semplicità)

**e) Assunzioni** – l'utente inserisce valori numerici validi

**f) Algoritmo in linguaggio naturale**
1. Leggere `scelta`
2. Leggere `valore`
3. Chiamare `km_in_miglia(valore)` e assegnare il risultato
4. Stampare con quattro cifre decimali

### Caso d'uso 2 – Conversione di temperatura (Celsius → Kelvin)

**a) Input** – scelta `10`, valore `-273.15`

**b) Output** – `-273.15 C = 0.00 K`

**c) Variabili di supporto** – `risultato = celsius_in_kelvin(valore)`

**d) Vincoli** – il risultato non deve essere inferiore a 0 K (zero assoluto); controllo non implementato in questa versione

**e) Assunzioni** – l'utente conosce i limiti fisici della conversione

**f) Algoritmo in linguaggio naturale**
1. Leggere scelta `10` e valore
2. Chiamare `celsius_in_kelvin(valore)`: aggiunge 273.15
3. Stampare il risultato con due cifre decimali

### Caso d'uso 3 – Scelta non valida

**a) Input** – scelta `0` o `11`

**b) Output** – `Scelta non valida.`

**c) Variabili di supporto** – nessuna

**d) Vincoli** – qualsiasi valore di `scelta` fuori dall'intervallo 1–10 deve produrre il messaggio di errore

**e) Assunzioni** – l'utente inserisce un intero

**f) Algoritmo in linguaggio naturale**
1. Nessuno dei blocchi `if/else if` corrisponde alla scelta
2. Il ramo `else` finale stampa `Scelta non valida.`
