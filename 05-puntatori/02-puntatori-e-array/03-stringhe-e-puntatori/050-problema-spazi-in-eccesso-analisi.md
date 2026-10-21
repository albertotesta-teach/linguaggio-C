# Analisi – 050-problema-spazi-in-eccesso.c

## 1. Problema

I testi inseriti nei moduli online arrivano con spazi in eccesso. Prima di
salvarli il programma li normalizza: nessuno spazio all'inizio e alla fine,
un solo spazio tra le parole, nessuno spazio prima della punteggiatura. La
correzione avviene nello stesso array e il programma indica quanti
caratteri ha tolto.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `testi` | `char[4][80]` | `"   Mario    Rossi   "`, `"Via Roma ,  12"`, `"Allergie :  nessuna ."`, `"Sport preferiti:calcio ,   nuoto , tennis"` |

### Output

- Per ogni testo: il testo prima e dopo la normalizzazione, tra parentesi
  quadre, e il numero di caratteri tolti.

### Vincoli

- La correzione avviene sul posto con due puntatori sullo stesso array:
  `lettura` esamina ogni carattere, `scrittura` indica dove copiare il
  prossimo carattere tenuto. `scrittura` non supera mai `lettura`, quindi
  non si sovrascrive un carattere non ancora letto.
- Uno spazio non si copia subito: diventa "in sospeso" e si scrive solo
  prima del carattere successivo, se questo non è punteggiatura
  (`, . ; : ! ?`). Così si eliminano gli spazi finali, quelli ripetuti e
  quelli prima della punteggiatura.
- Gli spazi iniziali si ignorano finché non è stato scritto nulla
  (`scrittura == testo`).
- La nuova lunghezza è `scrittura − testo`; i caratteri tolti sono la
  differenza con la lunghezza iniziale.

### Assunzioni

- Si considera solo il carattere spazio (non le tabulazioni).
- Dopo la punteggiatura lo spazio non viene aggiunto se manca
  (`preferiti:calcio` resta così).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `lettura` | `const char *` | Carattere esaminato |
| `scrittura` | `char *` | Posizione in cui copiare il prossimo carattere tenuto |
| `spazio_in_sospeso` | `int` | 1 se è stato letto uno spazio non ancora scritto |
| `lunghezza_iniziale` | `int` | Per calcolare i caratteri tolti |

| Funzione | Compito |
|----------|---------|
| `normalizza(testo)` | Corregge gli spazi sul posto, restituisce i caratteri tolti |
| `punteggiatura(c)` | 1 se `c` è tra `, . ; : ! ?` |

### Algoritmo in linguaggio naturale

1. Per ogni testo stampare il prima, normalizzarlo e stampare il dopo con i
   caratteri tolti.
2. In `normalizza`, per ogni carattere letto:
   1. se è uno spazio e qualcosa è già stato scritto, porre lo spazio in
      sospeso;
   2. altrimenti, se c'è uno spazio in sospeso e il carattere non è
      punteggiatura, scrivere uno spazio; poi scrivere il carattere e
      annullare lo spazio in sospeso.
3. Chiudere il testo con `'\0'` e restituire la differenza di lunghezza.

## 3. Casi di test

### Test 1 – Testi del sorgente

- **Cosa si verifica:** spazi iniziali, finali, ripetuti e prima della
  punteggiatura.
- **Input:** nessuno.
- **Valori intermedi attesi:** `"Via Roma ,  12"` (14 caratteri) diventa
  `"Via Roma, 12"` (12): 2 tolti.
- **Output atteso:**
  ```
  === NORMALIZZAZIONE DEGLI SPAZI ===
    prima: [   Mario    Rossi   ]
    dopo:  [Mario Rossi]   (9 caratteri tolti)

    prima: [Via Roma ,  12]
    dopo:  [Via Roma, 12]   (2 caratteri tolti)

    prima: [Allergie :  nessuna .]
    dopo:  [Allergie: nessuna.]   (3 caratteri tolti)

    prima: [Sport preferiti:calcio ,   nuoto , tennis]
    dopo:  [Sport preferiti:calcio, nuoto, tennis]   (4 caratteri tolti)
  ```
