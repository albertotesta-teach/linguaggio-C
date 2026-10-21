# Analisi – 040-problema-scaffale.c

## 1. Problema

Il magazzino del laboratorio di elettronica conserva componenti
identificati da un codice. Il tecnico registra carichi (`C codice n`) e
scarichi (`S codice n`); uno scarico è accettato solo se ci sono abbastanza
pezzi. Con `Q` si stampa l'inventario aggiornato.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `C` carico, `S` scarico, `Q` fine |
| `codice`, `n` | `int` | Codice del componente e pezzi del movimento (positivo) |
| `codici`, `quantita` | `int[5]` | Inventario iniziale (nel sorgente): 1001: 40, 1002: 25, 2010: 120, 2011: 8, 3050: 15 |

### Output

- L'inventario iniziale e finale.
- Per ogni movimento: la nuova quantità, oppure `solo N pezzi disponibili`,
  `Codice N inesistente.`, `Dati non validi.`, `Comando sconosciuto.`

### Vincoli

- `quantita_di` restituisce l'indirizzo della quantità dell'articolo
  (`quantita + i`) oppure `NULL` se il codice non c'è: il `main` non
  conosce la posizione dell'articolo e modifica la quantità tramite il
  puntatore ricevuto.
- `codici` e `quantita` sono paralleli: la posizione trovata in `codici`
  vale anche per `quantita`.
- `*q` non si usa se `q` è `NULL`.
- La quantità non diventa mai negativa: lo scarico si rifiuta se i pezzi
  non bastano.
- Codice e pezzi devono essere due numeri con pezzi > 0, altrimenti il
  movimento è rifiutato (la riga si scarta) e il programma continua; a
  fine input si comporta come `Q`.

### Assunzioni

- I codici sono tutti diversi; i comandi sono maiuscoli.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `q` | `int *` | Quantità dell'articolo trovato, `NULL` se il codice non esiste |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `quantita_di(codici, quantita, n, codice)` | Indirizzo della quantità dell'articolo, `NULL` se assente |
| `inventario(codici, quantita, n)` | Stampa codici e quantità |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Stampare l'inventario.
2. Finché il comando non è `Q`:
   1. leggere il comando (a fine input `Q`);
   2. per `C` o `S` leggere codice e pezzi; se non validi segnalarlo;
      altrimenti cercare la quantità: se `NULL` segnalare il codice
      inesistente; con `C` aggiungere i pezzi a `*q`; con `S` toglierli se
      bastano, altrimenti segnalare i pezzi disponibili;
   3. ogni altro comando diverso da `Q` è sconosciuto.
3. Stampare l'inventario aggiornato.

## 3. Casi di test

Nell'output i movimenti inseriti non compaiono (input da pipe).

### Test 1 – Sessione completa

- **Input:** `S 2011 5`, `S 2011 5`, `C 2011 50`, `S 9999 1`, `C 1001 0`,
  `C abc`, `X`, `Q`
- **Output atteso:**
  ```
  Inventario:  1001: 40  1002: 25  2010: 120  2011: 8  3050: 15
    Codice 2011: scaricati 5, ora 3 pezzi
    Codice 2011: solo 3 pezzi disponibili
    Codice 2011: caricati 50, ora 53 pezzi
    Codice 9999 inesistente.
    Dati non validi.
    Dati non validi.
    Comando sconosciuto.
  Inventario:  1001: 40  1002: 25  2010: 120  2011: 53  3050: 15
  ```

### Test 2 – Scarico di tutti i pezzi

- **Input:** `S 3050 15`, `Q`
- **Output atteso:** `  Codice 3050: scaricati 15, ora 0 pezzi`
