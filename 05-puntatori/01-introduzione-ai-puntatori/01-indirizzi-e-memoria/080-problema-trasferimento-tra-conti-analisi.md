# Analisi – 080-problema-trasferimento-tra-conti.c

## 1. Problema

Il bar della scuola gestisce tre tessere prepagate. La funzione
`trasferisci` sposta credito da una tessera a un'altra ricevendone gli
indirizzi. Deve rifiutare il trasferimento verso la stessa tessera, gli
importi non positivi e quelli superiori al credito disponibile.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore | Significato |
|------|------|--------|-------------|
| `tessera_1`, `tessera_2`, `tessera_3` | `int` | 1500, 400, 1500 | Credito in centesimi |
| trasferimenti | — | 1→2 600; 2→2 200; 2→3 5000; 3→1 −100 | Operazioni richieste nel `main` |

### Output

- Gli indirizzi delle tre tessere e i crediti iniziali in euro.
- Il confronto tra `tessera_1` e `tessera_3`: stesso credito, ma non la
  stessa tessera.
- Per ogni trasferimento l'esito (`eseguito`, `stessa tessera`,
  `credito insufficiente`, `importo non valido`) e i crediti aggiornati.

### Vincoli

- `trasferisci` riceve gli indirizzi delle tessere e modifica i crediti
  tramite `*da` e `*a`.
- Confrontare i valori (`tessera_1 == tessera_3`) è diverso dal confrontare
  gli indirizzi (`&tessera_1 == &tessera_3`): due variabili diverse possono
  avere lo stesso valore.
- I controlli seguono l'ordine: stessa tessera (`da == a`), importo non
  positivo, credito insufficiente; il credito si sposta solo se tutti i
  controlli sono superati.
- `trasferisci` ha una sola `return`.

### Assunzioni

- Gli importi sono in centesimi interi; i crediti non sono mai negativi.
- Gli indirizzi cambiano a ogni esecuzione.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `esiti` | `char[4][32]` | Testo di ogni codice di esito |
| `esito` | `int` | Codice restituito da `trasferisci` |
| `OK`, `STESSA_TESSERA`, `CREDITO_BASSO`, `IMPORTO_ERRATO` | `#define` | Codici di esito 0-3 |

| Funzione | Compito |
|----------|---------|
| `trasferisci(int *da, int *a, int importo)` | Controlli e spostamento del credito; restituisce il codice di esito |
| `stampa_tessere` | Stampa i tre crediti in euro |

### Algoritmo in linguaggio naturale

1. Stampare indirizzi e crediti iniziali.
2. Confrontare i valori e gli indirizzi di `tessera_1` e `tessera_3`.
3. Per ogni trasferimento chiamare `trasferisci`, che:
   1. se `da == a` restituisce `STESSA_TESSERA`;
   2. altrimenti se l'importo è ≤ 0 restituisce `IMPORTO_ERRATO`;
   3. altrimenti se `*da` è minore dell'importo restituisce `CREDITO_BASSO`;
   4. altrimenti toglie l'importo da `*da`, lo aggiunge ad `*a` e
      restituisce `OK`.
4. Stampare l'esito e, dove previsto, i crediti.

## 3. Casi di test

### Test 1 – Stesso valore, variabili diverse

- **Cosa si verifica:** confronto tra valori e tra indirizzi.
- **Input:** nessuno (dati del sorgente).
- **Output atteso:**
  ```
  Crediti: tessera 1 15.00  tessera 2 4.00  tessera 3 15.00 euro
  tessera_1 e tessera_3 hanno lo stesso credito (tessera_1 == tessera_3)? si'
  Sono la stessa tessera (&tessera_1 == &tessera_3)? no
  ```

### Test 2 – Trasferimento valido

- **Input:** da tessera 1 a tessera 2, 600 centesimi.
- **Valori intermedi attesi:** `*da` passa da 1500 a 900, `*a` da 400 a 1000.
- **Output atteso:**
  ```
  Da 1 a 2, 6.00 euro: eseguito
  Crediti: tessera 1 9.00  tessera 2 10.00  tessera 3 15.00 euro
  ```

### Test 3 – Trasferimenti rifiutati

- **Cosa si verifica:** i tre controlli; i crediti non cambiano.
- **Input:** da 2 a 2 (200); da 2 a 3 (5000); da 3 a 1 (−100).
- **Output atteso:**
  ```
  Da 2 a 2, 2.00 euro: stessa tessera
  Da 2 a 3, 50.00 euro: credito insufficiente
  Da 3 a 1, -1.00 euro: importo non valido
  Crediti: tessera 1 9.00  tessera 2 10.00  tessera 3 15.00 euro
  ```

### Test 4 – Trasferimento dell'intero credito

- **Cosa si verifica:** il caso limite importo = credito è ammesso.
- **Procedura:** nel sorgente cambiare il primo trasferimento in
  `trasferisci(&tessera_1, &tessera_2, 1500)`, ricompilare ed eseguire.
- **Output atteso:**
  ```
  Da 1 a 2, 6.00 euro: eseguito
  Crediti: tessera 1 0.00  tessera 2 19.00  tessera 3 15.00 euro
  ```
  (il testo "6.00 euro" è fisso nel `printf`).
