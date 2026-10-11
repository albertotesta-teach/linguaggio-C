# Analisi – 040-problema-configurazione-sola-lettura.c

## 1. Problema

Una cassa audio per le aule ha tre impostazioni (volume, bassi, luminosità)
con valori massimi decisi dall'istituto. Le richieste degli utenti vengono
applicate una alla volta; un valore oltre il massimo viene ridotto al
massimo. La configurazione dei limiti non deve poter essere modificata dal
programma.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `max_volume`, `max_bassi`, `max_luce` | `const int` | — | Limiti dell'istituto |
| `volume`, `bassi`, `luce` | `int` | — | Impostazioni correnti |
| `tipi`, `valori` | `char[]`, `int[]` | 6 | Richieste (array paralleli) |
| `impostazione` | `int *` | — | Impostazione da modificare, `NULL` se il codice è sconosciuto |
| `massimo` | `const int *` | — | Limite corrispondente, di sola lettura |

| Funzione | Compito |
|----------|---------|
| `limita(int *valore, const int *massimo)` | Riduce il valore al massimo; 1 se ridotto |
| `stampa_impostazioni(const int *, …)` | Stampa senza poter modificare |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Richiesta entro i limiti

**a) Input** – `V 65`

**b) Output** – "applicata"

**c) Variabili di supporto** – `impostazione = &volume`, `massimo = &max_volume`

**d) Vincoli** – l'indirizzo di una `const int` si può assegnare solo a un `const int *`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scrivere il valore in
`*impostazione` e chiamare `limita`, che non lo modifica.

### Caso d'uso 2 – Richiesta oltre il massimo

**a) Input** – `B 12`, `V 90`

**b) Output** – "ridotta al massimo consentito (8)", "(70)"

**c) Variabili di supporto** – `*massimo`

**d) Vincoli** – `limita` legge `*massimo` ma non può scriverlo: un'istruzione
`*massimo = ...` non compilerebbe

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `*valore > *massimo`,
`*valore = *massimo` e restituire 1.

### Caso d'uso 3 – Codice sconosciuto

**a) Input** – `X 50`

**b) Output** – "impostazione sconosciuta, ignorata"

**c) Variabili di supporto** – `impostazione` resta `NULL`

**d) Vincoli** – non si scrive tramite un puntatore `NULL`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – i puntatori si azzerano a ogni
richiesta; se nessun codice corrisponde si scarta la richiesta.
