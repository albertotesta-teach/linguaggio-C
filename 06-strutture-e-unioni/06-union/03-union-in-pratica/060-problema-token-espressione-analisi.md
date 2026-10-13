# Analisi – 060-problema-token-espressione.c

## 1. Problema

La calcolatrice divide un'espressione in token (numeri, operatori, parentesi) e la calcola rispettando precedenza e parentesi con tre funzioni ricorsive: espressione, termine e fattore. Ogni token è una union etichettata; le funzioni avanzano un indice comune e segnalano gli errori in *ok.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Token` | `tipo, union anonima {numero, simbolo}` | elemento dell'espressione |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `token` | `Token[]` | 40 | Token dell'espressione |
| `riga` | `char[]` | 80 | Espressione letta |
| `n`, `pos`, `ok` | `int` | — | Numero di token, posizione, esito |

| Funzione | Compito |
|----------|---------|
| `dividi_in_token(testo, token, massimo)` | Numero di token, -1 per un carattere non ammesso |
| `espressione(...)` | termine {(+|-) termine} |
| `termine(...)` | fattore {(*|/) fattore} |
| `fattore(...)` | numero oppure ( espressione ) |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Precedenza e parentesi

**a) Input** – `2 * (3 + 4.5) - 1`; `1 + 2 * 3`; `(1 + 2) * 3`

**b) Output** – 14 (9 token); 7; 9

**c) Variabili di supporto** – `pos`

**d) Vincoli** – moltiplicazioni prima delle somme

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ogni livello chiama quello di precedenza più alta.

### Caso d'uso 2 – Errori

**a) Input** – `10 / (5 - 5)`; `(2 + 3`

**b) Output** – "Espressione non valida."

**c) Variabili di supporto** – `ok`

**d) Vincoli** – divisore non nullo, parentesi chiuse

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la funzione che trova l'errore azzera *ok.

### Caso d'uso 3 – Carattere non ammesso

**a) Input** – `7 % 2`

**b) Output** – "Espressione non valida."

**c) Variabili di supporto** – `n`

**d) Vincoli** – solo cifre, punto, + - * / ( ) e spazi

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – dividi_in_token restituisce -1.
