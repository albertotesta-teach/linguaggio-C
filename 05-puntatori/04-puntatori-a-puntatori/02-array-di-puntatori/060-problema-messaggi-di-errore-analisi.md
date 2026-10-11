# Analisi – 060-problema-messaggi-di-errore.c

## 1. Problema

La stampante 3D del laboratorio registra gli errori come codici numerici. Il tecnico vuole il registro della settimana con la descrizione di ogni codice e il conteggio per tipo, compresi i codici che non hanno descrizione.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `descrizioni` | `const char *[]` | 6 | Testo dell'errore, l'indice è il codice |
| `registro` | `int[]` | 10 | Codici della settimana |
| `conteggi` | `int[]` | 6 | Eventi per codice |
| `sconosciuti` | `int` | — | Codici fuori tabella |

| Funzione | Compito |
|----------|---------|
| `descrizione(codice, descrizioni)` | Puntatore alla descrizione, o a "codice sconosciuto" |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Codice noto

**a) Input** – `1`

**b) Output** – "filamento esaurito"

**c) Variabili di supporto** – nessuna

**d) Vincoli** – il codice è l'indice dell'array

**e) Assunzioni** – codici da 0 a 5

**f) Algoritmo in linguaggio naturale** – restituire `descrizioni[codice]`.

### Caso d'uso 2 – Codice sconosciuto

**a) Input** – `9`

**b) Output** – "codice sconosciuto"

**c) Variabili di supporto** – `testo`

**d) Vincoli** – l'array non si legge mai fuori dai limiti

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se il codice è fuori intervallo la funzione restituisce il puntatore a un letterale di riserva.

### Caso d'uso 3 – Riepilogo

**a) Input** – 10 eventi

**b) Output** – 4x filamento esaurito, 2x piatto non livellato, ...

**c) Variabili di supporto** – `conteggi`

**d) Vincoli** – il codice 0 (nessun errore) non compare nel riepilogo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – incrementare `conteggi[codice]` per i codici validi, `sconosciuti` per gli altri.
