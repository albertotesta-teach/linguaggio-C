# Analisi – 050-problema-spazi-in-eccesso.c

## 1. Problema

I testi inseriti nei moduli online arrivano con spazi in eccesso. Prima di
salvarli il programma li normalizza: nessuno spazio all'inizio e alla fine,
un solo spazio tra le parole, nessuno spazio prima della punteggiatura. La
correzione avviene nello stesso array e il programma indica quanti
caratteri ha tolto.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `testi` | `char[][]` | 4 × 80 | Testi di prova, modificabili |
| `lettura` | `const char *` | — | Carattere esaminato |
| `scrittura` | `char *` | — | Posizione in cui copiare il prossimo carattere tenuto |
| `spazio_in_sospeso` | `int` | — | 1 se è stato letto uno spazio non ancora scritto |
| `lunghezza_iniziale` | `int` | — | Per calcolare i caratteri tolti |

| Funzione | Compito |
|----------|---------|
| `normalizza(testo)` | Corregge gli spazi sul posto, restituisce i caratteri tolti |
| `punteggiatura(c)` | 1 se `c` è tra `, . ; : ! ?` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Spazi all'inizio, alla fine e ripetuti

**a) Input** – `"   Mario    Rossi   "`

**b) Output** – `"Mario Rossi"`, 9 caratteri tolti

**c) Variabili di supporto** – `lettura`, `scrittura`, `spazio_in_sospeso`

**d) Vincoli** – `scrittura` non supera mai `lettura`: si copia solo verso
sinistra

**e) Assunzioni** – solo il carattere spazio (non tabulazioni)

**f) Algoritmo in linguaggio naturale**
1. Uno spazio non si copia: se `scrittura > testo` si ricorda in
   `spazio_in_sospeso`.
2. Un altro carattere: se c'è uno spazio in sospeso si scrive prima uno
   spazio, poi il carattere.
3. Alla fine si scrive `'\0'` in `*scrittura`: lo spazio finale in sospeso
   non viene mai scritto.

### Caso d'uso 2 – Spazio prima della punteggiatura

**a) Input** – `"Allergie :  nessuna ."`

**b) Output** – `"Allergie: nessuna."`

**c) Variabili di supporto** – `spazio_in_sospeso`

**d) Vincoli** – lo spazio in sospeso si scarta se il carattere successivo
è punteggiatura

**e) Assunzioni** – dopo la punteggiatura lo spazio resta com'è

**f) Algoritmo in linguaggio naturale** – al punto 2 del caso 1 si scrive lo
spazio solo se `punteggiatura(*lettura)` vale 0.

### Caso d'uso 3 – Caratteri tolti

**a) Input** – `"Via Roma ,  12"` (14 caratteri)

**b) Output** – `"Via Roma, 12"` (12 caratteri), 2 tolti

**c) Variabili di supporto** – `lunghezza_iniziale`

**d) Vincoli** – la nuova lunghezza è `scrittura - testo`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – restituire `lunghezza_iniziale -
(scrittura - testo)`.
