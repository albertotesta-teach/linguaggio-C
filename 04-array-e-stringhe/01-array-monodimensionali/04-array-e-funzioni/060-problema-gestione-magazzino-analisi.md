# Analisi – 060-problema-gestione-magazzino.c

## 1. Problema

Un magazzino gestisce 6 prodotti identificati da codice numerico e quantità.
Il programma deve permettere operazioni di carico e scarico tramite funzioni
dedicate, ricercare un prodotto per codice, stampare il prospetto e calcolare
la giacenza totale.

---

## 2. Analisi

### Input
Nessun input da tastiera: i prodotti e le operazioni sono fissi nel codice.

| Variabile  | Tipo       | Dimensione | Descrizione                             |
|------------|------------|------------|-----------------------------------------|
| `codici`   | `int[]`    | 6          | Codice numerico del prodotto            |
| `nomi`     | `char[][]` | 6 × 20     | Descrizione del prodotto                |
| `quantita` | `int[]`    | 6          | Pezzi disponibili                       |

Operazioni eseguite dal `main`: carico di 200 pezzi del codice 1003,
scarico di 150 pezzi del codice 1005, ricerca del codice 9999.

### Output
- Il prospetto iniziale con la giacenza totale;
- per ogni operazione l'esito: "OK" con la nuova quantità,
  "RIFIUTATO: quantita' insufficiente" oppure
  "ERRORE: prodotto non trovato";
- il prospetto finale con la nuova giacenza totale.

### Vincoli
- La ricerca restituisce l'indice del prodotto oppure -1 se il codice non
  esiste, e si ferma al primo trovato tramite un flag (niente `break`)
- L'aggiornamento somma una variazione (positiva per il carico, negativa per
  lo scarico) e non porta mai la quantità sotto zero: in quel caso
  l'operazione è rifiutata e la quantità resta invariata
- L'aggiornamento verifica che l'indice sia valido
- Ogni funzione ha una sola `return`
- Le funzioni che non modificano gli array li ricevono come `const`

### Assunzioni
- I codici sono univoci

### Variabili di supporto

| Variabile  | Tipo      | Descrizione                                       |
|------------|-----------|---------------------------------------------------|
| `indice`   | `int`     | Risultato di `trova_prodotto` (-1 se assente)     |
| `esito`    | `int`     | Risultato di `aggiorna_quantita` (1 OK, 0 rifiuto)|
| `PRODOTTI` | `#define` | 6                                                 |

| Funzione | Descrizione |
|---|---|
| `int trova_prodotto(const int codici[], int n, int codice_cercato)` | Indice del codice o -1 |
| `int aggiorna_quantita(int quantita[], int n, int indice, int delta)` | Applica la variazione se il risultato non è negativo |
| `int giacenza_totale(const int quantita[], int n)` | Somma delle quantità |
| `void stampa_magazzino(...)` | Prospetto con giacenza totale |

### Algoritmo in linguaggio naturale
Per ogni operazione:
1. Cercare il codice con `trova_prodotto`.
2. Se l'indice è -1 stampare che il prodotto non è stato trovato.
3. Altrimenti chiamare `aggiorna_quantita` con la variazione: se la nuova
   quantità sarebbe negativa l'operazione è rifiutata, altrimenti la
   quantità viene aggiornata. Stampare l'esito.

All'inizio e alla fine stampare il prospetto con la giacenza totale.

---

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il Test 3
richiede di modificare lo scarico e ricompilare.

### Test 1 – Carico, scarico e codice inesistente
- **Output atteso:**
```
Operazione: carico +200 di codice 1003
  OK: Rondella M4 -> nuova quantita': 800

Operazione: scarico -150 di codice 1005
  OK: Dado M6 -> nuova quantita': 160

Operazione: ricerca codice 9999 (inesistente)
  ERRORE: prodotto non trovato
```

### Test 2 – Giacenza totale
- **Cosa si verifica:** il prospetto riflette le operazioni
- **Output atteso:** `Giacenza totale: 2610 pezzi` nello stato iniziale,
  `Giacenza totale: 2660 pezzi` nello stato finale (+200 −150)

### Test 3 – Scarico superiore alla disponibilità
- **Cosa si verifica:** la quantità non va sotto zero
- **Procedura:** cambiare lo scarico del codice 1005 da -150 a -400
  (disponibili 310)
- **Output atteso:** `RIFIUTATO: quantita' insufficiente`; nello stato
  finale Dado M6 resta a 310
