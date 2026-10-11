# Analisi – 040-problema-validazione-email.c

## 1. Problema

Il modulo di iscrizione a una newsletter deve rifiutare gli indirizzi email
scritti male. Il controllo, semplificato, verifica cinque regole: nessuno
spazio, una sola `@`, almeno un carattere prima della `@`, almeno un punto
dopo la `@`, punto non subito dopo la `@` né in fondo. Per ogni indirizzo
rifiutato si indica la prima regola violata; alla fine si contano gli
indirizzi accettati e rifiutati.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `email` | `char[]` | 60 | Indirizzo letto |
| `messaggi` | `char[][]` | 6 × 44 | Testo associato a ogni esito (0 = valido) |
| `esito` | `int` | — | 0 oppure numero della regola violata |
| `valide`, `rifiutate` | `int` | — | Contatori |

| Funzione | Compito |
|----------|---------|
| `controlla_email` | Applica le regole nell'ordine e restituisce l'esito |
| `conta_carattere` | Numero di occorrenze di un carattere |
| `prima_posizione`, `ultima_posizione` | Indice della prima/ultima occorrenza, o -1 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Indirizzo valido

**a) Input** – `mario.rossi@gmail.com`

**b) Output** – "OK: indirizzo valido"

**c) Variabili di supporto** – `chiocciola` = 11, `ultimo_punto` = 17

**d) Vincoli** – nessuna regola violata

**e) Assunzioni** – lunghezza massima 59 caratteri

**f) Algoritmo in linguaggio naturale** – calcolare posizione della `@` e
dell'ultimo punto, poi verificare le regole in ordine; nessuna è violata.

### Caso d'uso 2 – Spazi o numero di `@` sbagliato

**a) Input** – `mario rossi@gmail.com`; `mario.rossigmail.com`; `mario@rossi@gmail.com`

**b) Output** – regola 1; regola 2; regola 2

**c) Variabili di supporto** – risultato di `strchr`, `conta_carattere`

**d) Vincoli** – `strchr` serve solo a sapere se il carattere è presente (`!= NULL`)

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `strchr(s, ' ')` non è `NULL`
regola 1; se manca la `@` o ce n'è più di una regola 2.

### Caso d'uso 3 – Posizione della `@` e del punto

**a) Input** – `@gmail.com`; `mario@gmail`; `mario@.com`; `mario@gmail.`

**b) Output** – regola 3; regola 4; regola 5; regola 5

**c) Variabili di supporto** – `chiocciola`, `ultimo_punto`, `lung`

**d) Vincoli** – il punto deve stare dopo la `@` (`ultimo_punto > chiocciola`)

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Se la `@` è in posizione 0 manca il nome: regola 3.
2. Se l'ultimo punto è prima della `@` (o non c'è): regola 4.
3. Se il carattere dopo la `@` è un punto o l'ultimo punto è l'ultimo carattere: regola 5.
