# Analisi – 060-problema-gestione-magazzino.c

## 1. Problema

Un magazzino gestisce 6 prodotti identificati da codice numerico e quantità.
Il programma deve permettere operazioni di carico e scarico tramite funzioni
dedicate, ricercare un prodotto per codice, stampare il prospetto e calcolare
la giacenza totale.

---

## 2. Analisi generale e struttura dati

La struttura è organizzata per **responsabilità separate**: ogni funzione
ha un compito preciso e il `main` si limita a coordinare le operazioni e
gestire i casi di errore (prodotto non trovato, quantità insufficiente).

| Variabile   | Tipo         | Dimensione | Motivazione                                          |
|-------------|--------------|------------|------------------------------------------------------|
| `codici`    | `int[]`      | 6          | Identificativo numerico di ogni prodotto             |
| `nomi`      | `char[][]`   | 6 × 20     | Descrizione del prodotto                             |
| `quantita`  | `int[]`      | 6          | Pezzi disponibili; modificato da `aggiorna_quantita` |
| `indice`    | `int`        | —          | Risultato di `trova_prodotto`; -1 se non trovato     |
| `esito`     | `int`        | —          | Risultato di `aggiorna_quantita`; 0 se rifiutato     |
| `PRODOTTI`  | `#define`    | 6          | Dimensione degli array e limite dei cicli            |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Ricerca per codice

**a) Input**
Array `codici`, intero `codice_cercato`.

**b) Output**
Restituisce l'indice del prodotto, oppure -1 se non trovato.

**c) Funzione coinvolta**
`trova_prodotto(codici, n, codice_cercato)`: scorrimento con flag `trovato`;
il ciclo si ferma alla prima corrispondenza (`&& !trovato`).

**d) Vincoli**
- Restituisce -1 come sentinella di "non trovato".
- Non usa `break`: la condizione `&& !trovato` nel `for` controlla l'uscita anticipata.
- Una sola `return` alla fine.

**f) Algoritmo in linguaggio naturale**
```
trovato = 0, risultato = -1.
Per i da 0 a n-1, finché !trovato:
  Se codici[i] == codice_cercato: trovato = 1, risultato = i.
return risultato.
```

---

### Caso d'uso 2 – Aggiornamento della quantità

**a) Input**
Array `quantita`, `indice` (da `trova_prodotto`), `delta` (positivo=carico, negativo=scarico).

**b) Output**
Restituisce 1 (operazione eseguita) o 0 (rifiutata perché porterebbe la quantità sotto zero).

**c) Funzione coinvolta**
`aggiorna_quantita(quantita, n, indice, delta)`.

**d) Vincoli**
- L'operazione viene rifiutata se `quantita[indice] + delta < 0`.
- L'indice deve essere valido (`>= 0 && < n`).
- Se rifiutata, l'array non viene modificato.

**f) Algoritmo in linguaggio naturale**
```
Se indice in [0, n-1]:
  nuova = quantita[indice] + delta.
  Se nuova >= 0: quantita[indice] = nuova, esito = 1.
  Altrimenti: esito = 0 (nessuna modifica).
return esito.
```

---

### Caso d'uso 3 – Stampa prospetto e giacenza totale

**a) Input**
Array `codici`, `nomi`, `quantita`.

**b) Output**
```
  Cod.  | Prodotto           | Qty
  ------|--------------------|---------
  1001  | Vite M4x10         |   500
  ...
  Giacenza totale: 2410 pezzi
```

**c) Funzione coinvolta**
`stampa_magazzino` chiama internamente `giacenza_totale` per il totale.

**d) Vincoli**
- `stampa_magazzino` non modifica nessun array (`const` su tutti i parametri di input).
- `giacenza_totale` viene riusata dentro `stampa_magazzino` senza duplicare codice.
