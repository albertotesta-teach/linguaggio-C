# Analisi – 060-problema-conto-attivo.c

## 1. Problema

Il tesoriere dell'associazione dei genitori gestisce quattro salvadanai
(gita, biblioteca, sport, festa). Seleziona un salvadanaio con il comando
`N k` e poi registra versamenti (`V importo`) e prelievi (`P importo`) su
quello selezionato. Il prelievo è rifiutato se il saldo non basta. Alla
fine viene stampato il riepilogo, indicando l'ultimo salvadanaio selezionato.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[40]` | Comando letto con `fgets`: `N k` (seleziona il salvadanaio k, da 1 a 4), `V importo`, `P importo`, `F` (fine) |
| `nomi` | `char[4][12]` | Gita, Biblioteca, Sport, Festa (nel sorgente) |
| `saldi` | `int[4]` | Saldi iniziali in euro: 350, 120, 80, 0 (nel sorgente) |

### Output

- Per ogni comando: il salvadanaio selezionato con il saldo, il nuovo saldo
  dopo un'operazione, oppure un messaggio di errore (`Nessun salvadanaio
  selezionato.`, `Numero di salvadanaio non valido.`, `Importo non valido.`,
  `Saldo insufficiente in ...`, `Comando sconosciuto.`, `Comando vuoto.`).
- Il riepilogo dei quattro saldi, con `<- ultimo selezionato` accanto al
  salvadanaio selezionato per ultimo.

### Vincoli

- La riga si scompone con `sscanf(riga, " %c %d", ...)`: il numero di
  elementi letti dice se l'importo o il numero sono presenti.
- `attivo` contiene l'indirizzo dell'elemento selezionato di `saldi` ed è
  `NULL` finché non si seleziona nulla: non si dereferenzia mai `NULL`.
- L'utente conta i salvadanai da 1, l'array da 0: `attivo = &saldi[k - 1]`.
- Gli importi devono essere positivi; il saldo non può diventare negativo.
- Nel riepilogo il salvadanaio selezionato si riconosce confrontando gli
  indirizzi: `&saldi[k] == attivo`.
- A fine input (EOF) il programma si comporta come il comando `F`.

### Assunzioni

- Importi interi in euro; comandi in maiuscolo.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `attivo` | `int *` | Indirizzo del saldo selezionato, `NULL` all'inizio |
| `indice_attivo` | `int` | Indice selezionato, per stampare il nome |
| `comando`, `valore` | `char`, `int` | Parti del comando lette da `sscanf` |
| `letti` | `int` | Elementi convertiti da `sscanf` |
| `k` | `int` | Indice del riepilogo |

### Algoritmo in linguaggio naturale

1. Porre `attivo = NULL`.
2. Finché il comando non è `F`:
   1. leggere la riga (a fine input usare `F`) e scomporla con `sscanf`;
   2. riga vuota → `Comando vuoto.`;
   3. `N`: se c'è un numero tra 1 e 4 far puntare `attivo` a quel saldo e
      stamparlo, altrimenti segnalare l'errore;
   4. `V` o `P`: se `attivo` è `NULL` segnalarlo; se l'importo manca o non è
      positivo segnalarlo; se è un prelievo superiore a `*attivo` segnalare
      il saldo insufficiente; altrimenti aggiornare `*attivo` e stamparlo;
   5. ogni altro comando diverso da `F` è sconosciuto.
3. Stampare il riepilogo marcando il saldo il cui indirizzo è `attivo`.

## 3. Casi di test

Nell'output i comandi non compaiono (input da pipe); ogni risposta segue il
prompt `Comando (N k | V euro | P euro | F): `.

### Test 1 – Sessione completa

- **Input:** `V 50`, `N 2`, `V 30`, `P 200`, `N 9`, `N 4`, `V 75`, `P 20`,
  `P 0`, `X`, riga vuota, `F`
- **Output atteso** (risposte nell'ordine e riepilogo):
  ```
    Nessun salvadanaio selezionato.
    Selezionato Biblioteca (saldo 120 euro)
    Biblioteca: nuovo saldo 150 euro
    Saldo insufficiente in Biblioteca: 150 euro.
    Numero di salvadanaio non valido.
    Selezionato Festa (saldo 0 euro)
    Festa: nuovo saldo 75 euro
    Festa: nuovo saldo 55 euro
    Importo non valido.
    Comando sconosciuto.
    Comando vuoto.

  === RIEPILOGO ===
    Gita          350 euro
    Biblioteca    150 euro
    Sport          80 euro
    Festa          55 euro   <- ultimo selezionato
  ```

### Test 2 – Fine dell'input senza F

- **Cosa si verifica:** a fine input il programma stampa il riepilogo.
- **Input:** `N 1`, `V 5`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso** (riepilogo):
  ```
    Gita          355 euro   <- ultimo selezionato
    Biblioteca    120 euro
    Sport          80 euro
    Festa           0 euro
  ```

### Test 3 – Nessuna selezione

- **Cosa si verifica:** senza selezioni nessun salvadanaio è marcato.
- **Input:** `F`
- **Output atteso:** il riepilogo con i saldi iniziali e nessuna freccia.
