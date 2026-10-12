# Analisi – 050-problema-scontrino-mensa.c

## 1. Problema

Alla cassa della mensa l'operatore inserisce il codice di un prodotto del listino e la quantità; il codice 0 chiude lo scontrino. Con la tessera studenti si ha uno sconto del 10% se il totale supera 8 euro. Gli importi hanno il tipo `Euro`, le quantità il tipo `Quantita`.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Euro` | `typedef double Euro;` | prezzi e importi |
| `Quantita` | `typedef int Quantita;` | pezzi acquistati |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `const char *[]` | 6 | Nomi dei prodotti |
| `listino` | `Euro[]` | 6 | Prezzi; il codice è l'indice + 1 |
| `totale`, `riduzione` | `Euro` | — | Importo dello scontrino e dello sconto |
| `pezzi` | `Quantita` | — | Quantità letta |
| `codice`, `tessera` | `int`, `char` | — | Input dell'operatore |

| Funzione | Compito |
|----------|---------|
| `subtotale(prezzo, pezzi)` | Prezzo per quantità |
| `sconto(totale, percentuale)` | Importo dello sconto arrotondato al centesimo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Riga dello scontrino

**a) Input** – codice `1`, quantità `2`

**b) Output** – `2 x Primo piatto 6.40`

**c) Variabili di supporto** – `totale`

**d) Vincoli** – codice tra 1 e 6, quantità positiva

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sommare al totale il subtotale del prodotto e stampare la riga.

### Caso d'uso 2 – Input non valido

**a) Input** – codice `9`; quantità `0`

**b) Output** – "Codice inesistente."; "Quantita' non valida, prodotto non aggiunto."

**c) Variabili di supporto** – —

**d) Vincoli** – un errore non chiude lo scontrino

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se il codice è fuori listino non si chiede la quantità; una quantità non positiva non aggiunge nulla.

### Caso d'uso 3 – Chiusura con sconto

**a) Input** – `0`, poi `S` con totale 11.40

**b) Output** – sconto 1.14, da pagare 10.26

**c) Variabili di supporto** – `riduzione`

**d) Vincoli** – sconto solo con tessera e totale oltre 8 euro

**e) Assunzioni** – la risposta è una sola lettera maiuscola

**f) Algoritmo in linguaggio naturale** – calcolare lo sconto in centesimi arrotondati e sottrarlo dal totale.
