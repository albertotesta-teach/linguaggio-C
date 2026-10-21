# Analisi – 080-problema-questionario.c

## 1. Problema

Un sistema di correzione automatica gestisce un questionario a risposta multipla
di 10 domande (opzioni A/B/C/D). Il programma raccoglie le risposte dello
studente con validazione, le confronta con la chiave, mostra il dettaglio
domanda per domanda e calcola il punteggio finale.

---

## 2. Analisi

### Input

| Variabile  | Tipo     | Dimensione | Descrizione                                  |
|------------|----------|------------|----------------------------------------------|
| `risposte` | `char[]` | 10         | Risposta dello studente (A, B, C o D)        |

La chiave di correzione è fissa nel codice: A C B D A C B A D C.

### Output
- La tabella di correzione: numero della domanda, risposta data, risposta
  corretta, esito "OK" o "ERRATA";
- il numero di risposte corrette ed errate, il punteggio percentuale e
  l'esito "PROMOSSO" o "NON PROMOSSO".

### Vincoli
- Sono accettate solo le lettere A, B, C, D; le minuscole a–d vengono
  convertite in maiuscole (sottraendo 32); ogni altro carattere viene
  segnalato e richiesto di nuovo
- La lettura usa `" %c"`: lo spazio scarta gli a capo rimasti nel buffer
- corrette + errate = 10
- Il punteggio si calcola con una divisione reale
- Si è promossi con un punteggio di almeno il 60% (soglia inclusa)
- L'esito si costruisce carattere per carattere con `'\0'` finale
- Se l'input termina prima dell'ultima domanda (`scanf` restituisce EOF) la
  correzione viene annullata

### Assunzioni
- La codifica dei caratteri è ASCII, in cui maiuscola e minuscola
  differiscono di 32

### Variabili di supporto

| Variabile     | Tipo      | Dimensione | Descrizione                           |
|---------------|-----------|------------|---------------------------------------|
| `chiave`      | `char[]`  | 10         | Risposta corretta di ogni domanda     |
| `valido`      | `int`     | —          | Flag del ciclo di validazione         |
| `corrette`, `errate` | `int` | —      | Contatori                             |
| `esito`       | `char[]`  | 10         | "OK" o "ERRATA"                       |
| `punteggio`   | `double`  | —          | Percentuale di risposte corrette      |
| `NUM_DOMANDE` | `#define` | 10         | Numero di domande                     |

### Algoritmo in linguaggio naturale
1. Per ogni domanda ripetere: leggere un carattere, convertirlo in
   maiuscolo se è tra a e d, accettarlo se è A, B, C o D, altrimenti
   segnalare l'errore.
2. Per ogni domanda confrontare risposta e chiave: se coincidono esito "OK"
   e incrementare `corrette`, altrimenti "ERRATA" e incrementare `errate`;
   stampare la riga.
3. Calcolare `punteggio = corrette / 10 × 100` e stampare il riepilogo.
4. Se il punteggio è almeno 60 stampare PROMOSSO, altrimenti NON PROMOSSO.

---

## 3. Casi di test

Per ogni caso si esegue il programma con le 10 risposte indicate e si
confronta quanto stampato con l'output atteso.

### Test 1 – Tutte corrette
- **Input:** A C B D A C B A D C
- **Output atteso:**
```
  Risposte corrette : 10 su 10
  Risposte errate   : 0 su 10
  Punteggio         : 100%
  Esito             : PROMOSSO
```

### Test 2 – Punteggio esattamente sulla soglia
- **Cosa si verifica:** il 60% è promosso
- **Input:** A C B D A C A C A A
- **Output atteso:** `Risposte corrette : 6 su 10`, `Punteggio         : 60%`,
  `Esito             : PROMOSSO`

### Test 3 – Minuscole, caratteri non validi e non promosso
- **Cosa si verifica:** la conversione in maiuscolo, la validazione e il
  ramo NON PROMOSSO
- **Input:** a, x, E, c, b, d, a, b, c, d, a, b
- **Output atteso:** due volte `Risposta non valida. Inserire A, B, C o D.`
  (per x ed E, alla domanda 2); poi
```
    1  |    A     |    A     | OK
    2  |    C     |    C     | OK
    3  |    B     |    B     | OK
    4  |    D     |    D     | OK
    5  |    A     |    A     | OK
    6  |    B     |    C     | ERRATA
    7  |    C     |    B     | ERRATA
    8  |    D     |    A     | ERRATA
    9  |    A     |    D     | ERRATA
   10  |    B     |    C     | ERRATA
```
  e `Punteggio         : 50%`, `Esito             : NON PROMOSSO`

### Test 4 – Fine dell'input prima dell'ultima domanda
- **Cosa si verifica:** la chiusura senza ciclo infinito quando mancano risposte
- **Input:** `A`, `C`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
  Domanda  1:   Domanda  2:   Domanda  3: 

Input terminato prima di aver risposto a tutte le domande.
```
