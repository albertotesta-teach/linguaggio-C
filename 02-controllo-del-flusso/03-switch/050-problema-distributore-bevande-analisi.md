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

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `codice` | `int` | Codice digitato |
| `prezzo` | `int` | Prezzo in centesimi |
| `importo` | `int` | Importo inserito in centesimi |
| `resto` | `int` | Differenza tra importo e prezzo |
| `prodotto_valido` | `int` (0/1) | Diventa 0 se il codice non esiste |

I prezzi sono costanti `#define` in centesimi. Si usano due `switch` sullo
stesso codice: il primo associa il nome (un ramo per codice), il secondo il
prezzo (codici raggruppati per fascia di prezzo).

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Acquisto con resto

**a) Input** – codice 21, importo 200

**b) Output** – "Selezionato: Te' al limone", prezzo 1,20 euro, resto 0,80 euro

**c) Variabili di supporto** – `prezzo`, `resto`

**d) Vincoli** – l'importo viene chiesto solo se il prodotto esiste

**e) Assunzioni** – l'utente inserisce numeri interi

**f) Algoritmo in linguaggio naturale**
1. Stampare il listino e leggere il codice.
2. Porre `prodotto_valido = 1` e `prezzo = 0`.
3. Primo `switch`: stampare il nome del prodotto o "Codice inesistente".
4. Secondo `switch`: assegnare il prezzo per fascia; nel `default` porre
   `prodotto_valido = 0`.
5. Se il prodotto è valido: stampare il prezzo e leggere l'importo; se
   l'importo è almeno pari al prezzo, calcolare e stampare il resto,
   altrimenti stampare quanto manca.
6. Se il prodotto non è valido, stampare "Nessuna erogazione".

### Caso d'uso 2 – Importo insufficiente

**a) Input** – codice 31, importo 100

**b) Output** – "Importo insufficiente: mancano 50 centesimi. Monete restituite."

**c) Variabili di supporto** – `prezzo`

**d) Vincoli** – nessuna erogazione se l'importo è minore del prezzo

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 5.

### Caso d'uso 3 – Codice inesistente

**a) Input** – codice 44

**b) Output** – "Codice 44 inesistente." e "Nessuna erogazione."

**c) Variabili di supporto** – `prodotto_valido`

**d) Vincoli** – l'importo non viene richiesto

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passi 3, 4 e 6.
