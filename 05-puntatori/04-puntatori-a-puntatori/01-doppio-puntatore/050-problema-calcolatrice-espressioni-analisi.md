# Analisi – 050-problema-calcolatrice-espressioni.c

## 1. Problema

Il tesoriere di classe scrive entrate e uscite della cassa come una sola espressione di somme e sottrazioni (`150 + 35 - 48`). Il programma calcola il risultato oppure mostra il punto in cui l'espressione è scritta male. Una riga vuota termina.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `riga` | `char[]` | 100 | Espressione letta |
| `p` | `const char *` | — | Puntatore di lettura dentro `valuta` |
| `risultato` | `int` | — | Valore calcolato (uscita) |
| `errore` | `int` | — | Posizione dell'errore (uscita) |

| Funzione | Compito |
|----------|---------|
| `leggi_numero(&p, &n)` | Legge un numero e sposta `p` dopo l'ultima cifra |
| `leggi_operatore(&p, &op)` | Legge `+` o `-` e sposta `p` |
| `salta_spazi(&p)` | Sposta `p` oltre gli spazi |
| `valuta(testo, &risultato, &errore)` | 1 se l'espressione è corretta |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Espressione corretta

**a) Input** – `150 + 35 - 48 + 20 - 12`

**b) Output** – = 145 euro

**c) Variabili di supporto** – `p`, `valore`, `op`

**d) Vincoli** – tutte le funzioni di lettura avanzano lo stesso puntatore

**e) Assunzioni** – solo interi non negativi, operatori + e -

**f) Algoritmo in linguaggio naturale** – leggere un numero; poi, finché il testo non è finito, leggere un operatore e un numero e applicarli al risultato.

### Caso d'uso 2 – Operatore mancante

**a) Input** – `150 + - 20`

**b) Output** – freccia sotto il `-`

**c) Variabili di supporto** – `errore = p - testo`

**d) Vincoli** – la posizione dell'errore è dove la lettura si è fermata

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `leggi_operatore` o `leggi_numero` falliscono, `valuta` restituisce 0.

### Caso d'uso 3 – Operatore non previsto

**a) Input** – `100 * 2`

**b) Output** – freccia sotto il `*`

**c) Variabili di supporto** – `corretta`

**d) Vincoli** – il ciclo si ferma al primo errore

**e) Assunzioni** – la moltiplicazione non è prevista

**f) Algoritmo in linguaggio naturale** – `leggi_operatore` accetta solo `+` e `-`.
