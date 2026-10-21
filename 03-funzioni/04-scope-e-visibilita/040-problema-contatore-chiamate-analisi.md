# Analisi – 040-problema-contatore-chiamate.c

## 1. Problema
Un sistema di diagnostica deve contare quante volte ciascuna funzione viene
invocata durante l'esecuzione del programma. I contatori devono persistere
tra le chiamate e essere accessibili da una funzione di riepilogo al termine.
Le variabili globali sono la soluzione naturale: non è necessario passarle
come parametri a ogni funzione, e la loro durata coincide con quella del
programma.

## 2. Analisi

### Input
Nessun input da tastiera: prezzi e percentuali di sconto dei quattro
prodotti sono assegnati nel `main`.

| Prodotto | Prezzo | Operazioni |
|---|---|---|
| A | 150.00 | sconto 10%, IVA |
| B | 200.00 | sconto 20%, IVA |
| C | 80.00 | solo IVA |
| D | 300.00 | sconto 15%, poi sconto 5%, IVA |

### Output
Per ogni prodotto: prezzo originale, prezzo finale e differenza tra i due
(etichettata "Risparmio"). Al termine il riepilogo con il numero di
chiamate di ciascuna funzione e il totale.

### Vincoli
- Ogni funzione monitorata incrementa il proprio contatore all'inizio, prima
  di qualsiasi calcolo
- I contatori non vengono mai azzerati: contano le chiamate dell'intera
  esecuzione
- Due sconti in cascata non equivalgono alla somma delle percentuali:
  15% e poi 5% non è uno sconto del 20%
- Il riepilogo va chiamato dopo tutte le operazioni

### Assunzioni
- La percentuale di sconto è un intero tra 0 e 100
- L'IVA è fissa al 22%
- La riga "Risparmio" è `originale − finale`: diventa negativa quando
  l'IVA pesa più dello sconto

### Variabili di supporto

| Variabile globale | Tipo | Descrizione |
|---|---|---|
| `chiamate_calcola_sconto` | int | Invocazioni di `calcola_sconto` |
| `chiamate_calcola_iva` | int | Invocazioni di `calcola_iva` |
| `chiamate_stampa_prezzo` | int | Invocazioni di `stampa_prezzo` |

| Variabile locale al main | Tipo | Descrizione |
|---|---|---|
| `prezzo`, `scontato`, `finale` | double | Prezzo originale, dopo lo sconto, con IVA |

| Funzione | Firma | Descrizione |
|---|---|---|
| `calcola_sconto` | `double(double, int)` | Applica uno sconto percentuale |
| `calcola_iva` | `double(double)` | Aggiunge IVA al 22% |
| `stampa_prezzo` | `void(double, double)` | Stampa prezzo originale, finale e differenza |
| `stampa_riepilogo_chiamate` | `void(void)` | Legge i tre contatori e stampa il riepilogo |

### Algoritmo in linguaggio naturale
1. Per ogni prodotto: applicare gli sconti previsti con `calcola_sconto`
   (zero, una o due volte), poi l'IVA con `calcola_iva`, poi stampare con
   `stampa_prezzo`. Ogni chiamata incrementa il contatore della funzione.
2. Chiamare `stampa_riepilogo_chiamate`, che stampa i tre contatori e la
   loro somma.

## 3. Casi di test

Il programma esegue in sequenza i quattro prodotti e il riepilogo: si
esegue una volta e si confronta ogni blocco con l'output atteso.

### Test 1 – Prodotto A: sconto singolo
- **Valori intermedi attesi:** scontato = 150 − 15 = 135.00;
  finale = 135 × 1.22 = 164.70
- **Output atteso:**
```
Prodotto A (sconto 10%, IVA 22%):
  Prezzo originale:   150.00 EUR
  Prezzo finale:      164.70 EUR
  Risparmio:          -14.70 EUR
```

### Test 2 – Prodotto B: sconto che supera l'IVA
- **Cosa si verifica:** la differenza diventa positiva
- **Valori intermedi attesi:** scontato = 160.00; finale = 195.20
- **Output atteso:** prezzo finale 195.20, risparmio 4.80

### Test 3 – Prodotto C: nessuno sconto
- **Cosa si verifica:** `calcola_sconto` non viene chiamata
- **Output atteso:** prezzo finale 97.60, risparmio -17.60

### Test 4 – Prodotto D: due sconti in cascata
- **Valori intermedi attesi:** 300 → 255.00 (−15%) → 242.25 (−5%);
  finale = 242.25 × 1.22 = 295.545 → 295.55
- **Output atteso:** prezzo finale 295.55, risparmio 4.45 (con uno sconto
  unico del 20% il prezzo finale sarebbe 292.80)

### Test 5 – Riepilogo delle chiamate
- **Cosa si verifica:** i contatori globali sommano le chiamate di tutti i
  prodotti: `calcola_sconto` 1 + 1 + 0 + 2, `calcola_iva` e `stampa_prezzo`
  una volta per prodotto
- **Output atteso:**
```
=== Riepilogo chiamate ===
  calcola_sconto:  4
  calcola_iva:     4
  stampa_prezzo:   4
  Totale:          12
```
