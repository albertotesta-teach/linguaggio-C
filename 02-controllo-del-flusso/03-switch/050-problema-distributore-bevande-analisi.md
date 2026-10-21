# Analisi – 050-problema-distributore-bevande.c

## 1. Problema

Un distributore automatico vende cinque prodotti identificati da un codice
numerico. L'utente digita il codice; se il prodotto esiste, il distributore
mostra il prezzo, riceve l'importo e, se è sufficiente, eroga il prodotto e
calcola il resto. Altrimenti restituisce le monete.

| Codice | Prodotto | Prezzo |
|--------|----------|--------|
| 11 | Acqua naturale | 0,60 € |
| 12 | Acqua frizzante | 0,60 € |
| 21 | Tè al limone | 1,20 € |
| 22 | Succo di frutta | 1,20 € |
| 31 | Caffè freddo | 1,50 € |

## 2. Analisi

### Input

| Variabile | Tipo  | Significato                                           |
|-----------|-------|-------------------------------------------------------|
| `codice`  | `int` | Codice digitato                                       |
| `importo` | `int` | Importo inserito in centesimi (solo se il codice esiste) |

### Output
Il listino; poi il nome del prodotto selezionato e il prezzo, seguiti
dall'erogazione con il resto oppure dal messaggio di importo insufficiente
con i centesimi mancanti. Per un codice inesistente: "Codice N inesistente."
e "Nessuna erogazione."

### Vincoli
- Il codice deve essere uno dei cinque del listino
- L'importo viene chiesto solo se il prodotto esiste
- Il prodotto viene erogato solo se l'importo è almeno pari al prezzo

### Assunzioni
- L'utente inserisce numeri interi
- L'importo è espresso in centesimi

### Variabili di supporto

| Variabile         | Tipo        | Significato                         |
|-------------------|-------------|-------------------------------------|
| `prezzo`          | `int`       | Prezzo in centesimi                 |
| `resto`           | `int`       | Differenza tra importo e prezzo     |
| `prodotto_valido` | `int` (0/1) | Diventa 0 se il codice non esiste   |

I prezzi sono costanti `#define` in centesimi. Si usano due `switch` sullo
stesso codice: il primo associa il nome (un ramo per codice), il secondo il
prezzo (codici raggruppati per fascia di prezzo).

### Algoritmo in linguaggio naturale
1. Stampare il listino e leggere il codice.
2. Porre `prodotto_valido = 1` e `prezzo = 0`.
3. Primo `switch`: stampare il nome del prodotto o "Codice inesistente".
4. Secondo `switch`: assegnare il prezzo per fascia; nel `default` porre
   `prodotto_valido = 0`.
5. Se il prodotto è valido: stampare il prezzo e leggere l'importo; se
   l'importo è almeno pari al prezzo, calcolare e stampare il resto,
   altrimenti stampare quanto manca.
6. Se il prodotto non è valido, stampare "Nessuna erogazione".

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Acquisto con resto
- **Input:** codice 21, importo 200
- **Valori intermedi attesi:** prezzo = 120, resto = 80
- **Output atteso:** "Selezionato: Te' al limone", prezzo 1,20 euro,
  resto 0,80 euro

### Test 2 – Importo insufficiente
- **Cosa si verifica:** nessuna erogazione se l'importo è minore del prezzo
- **Input:** codice 31, importo 100
- **Output atteso:** "Importo insufficiente: mancano 50 centesimi. Monete restituite."

### Test 3 – Codice inesistente
- **Cosa si verifica:** il ramo `default`; l'importo non viene richiesto
- **Input:** codice 44
- **Output atteso:** "Codice 44 inesistente." e "Nessuna erogazione."
