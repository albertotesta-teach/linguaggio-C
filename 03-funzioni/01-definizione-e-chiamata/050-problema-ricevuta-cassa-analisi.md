# Analisi – 050-problema-ricevuta-cassa.c

## 1. Problema
Un sistema di cassa deve stampare una ricevuta fiscale formattata. La ricevuta
ha una struttura standardizzata: intestazione del punto vendita, tabella dei
prodotti acquistati con quantità e prezzi, riepilogo con IVA e totale, piede
con numero scontrino e data. Ogni sezione è indipendente e può essere
aggiornata senza toccare le altre.

## 2. Analisi generale e struttura dati

I dati degli articoli e i totali sono fissi nel codice (versione semplificata
senza input utente). I valori numerici usano il tipo `double` per la gestione
delle cifre decimali nella valuta.

| Funzione | Tipo | Descrizione |
|---|---|---|
| `stampa_intestazione_negozio` | void | Ragione sociale, indirizzo, P.IVA |
| `stampa_separatore_ricevuta` | void | Riga di trattini per separare sezioni |
| `stampa_prodotti` | void | Tabella articoli con qta, prezzo unitario, totale riga |
| `stampa_riepilogo` | void | Subtotale, IVA, totale, metodo di pagamento |
| `stampa_piede_ricevuta` | void | Numero scontrino, data, ora, messaggio |
| `stampa_ricevuta` | void | Compositore: chiama tutte le sezioni in ordine |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Stampa ricevuta completa

**a) Input** – nessuno (dati fissi nel codice)

**b) Output**
```
        SUPERMERCATO BIANCHI
       Corso Italia 45 - Torino
       P.IVA 01234567890
       Tel. 011-9876543
------------------------------------
Prodotto             Qta Prezzo  Totale
------------------------------------
Latte intero 1L        2   1.35    2.70
...
------------------------------------
TOTALE:                       19.71
------------------------------------
  Scontrino N. 00247  Cassa: 03
  Data: 20/03/2024   Ora: 10:42
```

**c) Variabili di supporto**
- `subtotale`, `iva`, `totale`: double, calcolati manualmente per coerenza con i prodotti

**d) Vincoli**
- Le colonne della tabella prodotti devono essere allineate
- Il totale deve essere coerente con la somma dei prodotti

**e) Assunzioni**
- Un solo metodo di pagamento (carta)
- IVA al 5% applicata agli alimentari

**f) Algoritmo in linguaggio naturale**
1. Stampa intestazione negozio
2. Stampa separatore
3. Stampa tabella prodotti (intestazione colonne + righe articoli)
4. Stampa separatore
5. Calcola e stampa subtotale, IVA, totale
6. Stampa separatore
7. Stampa metodo di pagamento e resto
8. Stampa piede con numero scontrino e data

### Caso d'uso 2 – Verifica allineamento colonne

**a) Input** – nessuno

**b) Output** – colonne Prodotto, Qta, Prezzo, Totale perfettamente allineate

**c) Variabili di supporto** – larghezze di campo gestite da `printf` con `%-20s`, `%3d`, `%6.2f`, `%7.2f`

**d) Vincoli** – i nomi dei prodotti non devono superare 20 caratteri

**e) Assunzioni** – il terminale è largo almeno 40 caratteri

**f) Algoritmo in linguaggio naturale**
1. Stampare l'intestazione con gli stessi specificatori di formato delle righe dati
2. Per ogni prodotto usare `printf("%-20s %3d %6.2f %7.2f\n", ...)`

### Caso d'uso 3 – Riutilizzo del separatore

**a) Input** – nessuno

**b) Output** – riga di trattini identica in tutti i punti della ricevuta

**c) Variabili di supporto** – nessuna

**d) Vincoli** – il separatore deve essere lungo esattamente quanto le colonne

**e) Assunzioni** – la larghezza è fissa a 36 caratteri

**f) Algoritmo in linguaggio naturale**
1. Chiamare `stampa_separatore_ricevuta()` ogni volta che serve una riga di divisione
2. La funzione stampa sempre la stessa stringa di trattini
