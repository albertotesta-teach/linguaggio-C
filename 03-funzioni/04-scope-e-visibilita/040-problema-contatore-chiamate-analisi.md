# Analisi – 040-problema-contatore-chiamate.c

## 1. Problema
Un sistema di diagnostica deve contare quante volte ciascuna funzione viene
invocata durante l'esecuzione del programma. I contatori devono persistere
tra le chiamate e essere accessibili da una funzione di riepilogo al termine.
Le variabili globali sono la soluzione naturale: non è necessario passarle
come parametri a ogni funzione, e la loro durata coincide con quella del
programma.

## 2. Analisi generale e struttura dati

| Variabile globale | Tipo | Descrizione |
|---|---|---|
| `chiamate_calcola_sconto` | int | Numero di invocazioni di `calcola_sconto` |
| `chiamate_calcola_iva` | int | Numero di invocazioni di `calcola_iva` |
| `chiamate_stampa_prezzo` | int | Numero di invocazioni di `stampa_prezzo` |

| Funzione | Firma | Descrizione |
|---|---|---|
| `calcola_sconto` | `double(double, int)` | Applica uno sconto percentuale; incrementa il proprio contatore |
| `calcola_iva` | `double(double)` | Aggiunge IVA al 22%; incrementa il proprio contatore |
| `stampa_prezzo` | `void(double, double)` | Stampa prezzo originale, finale e risparmio; incrementa il proprio contatore |
| `stampa_riepilogo_chiamate` | `void(void)` | Legge i tre contatori globali e stampa il riepilogo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prodotto con sconto singolo e IVA

**a) Input** – `prezzo = 150.00`, sconto 10%

**b) Output**
```
Prodotto A (sconto 10%, IVA 22%):
  Prezzo originale:   150.00 EUR
  Prezzo finale:      164.34 EUR
  Risparmio:          -14.34 EUR
```

**c) Variabili di supporto** – `prezzo`, `scontato`, `finale` (double, locali al main)

**d) Vincoli** – il contatore viene incrementato all'inizio di ogni funzione, prima di qualsiasi calcolo

**e) Assunzioni** – la percentuale di sconto è un intero tra 0 e 100

**f) Algoritmo in linguaggio naturale**
1. Chiamare `calcola_sconto(150.0, 10)` → incrementa contatore, calcola `150 - 15 = 135`
2. Chiamare `calcola_iva(135.0)` → incrementa contatore, calcola `135 * 1.22 = 164.70`
3. Chiamare `stampa_prezzo(150.0, 164.70)` → incrementa contatore, stampa le righe

### Caso d'uso 2 – Prodotto con doppio sconto in sequenza

**a) Input** – `prezzo = 300.00`, sconto 15% poi 5%

**b) Output** – prezzo finale con due sconti applicati in cascata; `chiamate_calcola_sconto` raggiunge 4 a fine programma

**c) Variabili di supporto** – `scontato` viene riusato dopo il secondo sconto

**d) Vincoli** – i due sconti non sono equivalenti a uno sconto del 20% (sono applicati in cascata)

**e) Assunzioni** – l'ordine degli sconti non importa per il risultato finale

**f) Algoritmo in linguaggio naturale**
1. `scontato = calcola_sconto(300.0, 15)` → 255.0
2. `scontato = calcola_sconto(255.0,  5)` → 242.25
3. `finale   = calcola_iva(242.25)` → 295.55
4. `stampa_prezzo(300.0, 295.55)`

### Caso d'uso 3 – Riepilogo delle chiamate

**a) Input** – nessuno (legge i contatori globali)

**b) Output**
```
=== Riepilogo chiamate ===
  calcola_sconto:  4
  calcola_iva:     4
  stampa_prezzo:   4
  Totale:          12
```

**c) Variabili di supporto** – nessuna (legge direttamente le variabili globali)

**d) Vincoli** – il riepilogo deve essere chiamato dopo tutte le operazioni

**e) Assunzioni** – i contatori non vengono azzerati tra un prodotto e l'altro (contano le chiamate totali)

**f) Algoritmo in linguaggio naturale**
1. Leggere i tre contatori globali
2. Calcolare e stampare il totale come loro somma
