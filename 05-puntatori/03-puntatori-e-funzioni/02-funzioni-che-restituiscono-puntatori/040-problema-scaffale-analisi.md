# Analisi – 040-problema-scaffale.c

## 1. Problema

Il magazzino del laboratorio di elettronica conserva componenti
identificati da un codice. Il tecnico registra carichi (`C codice n`) e
scarichi (`S codice n`); uno scarico è accettato solo se ci sono abbastanza
pezzi. Con `Q` si stampa l'inventario aggiornato.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `codici` | `int[]` | 5 | Codici dei componenti |
| `quantita` | `int[]` | 5 | Pezzi disponibili, parallelo a `codici` |
| `q` | `int *` | — | Quantità dell'articolo trovato, `NULL` se il codice non esiste |
| `comando`, `codice`, `n` | `char`, `int` | — | Movimento letto |

| Funzione | Compito |
|----------|---------|
| `quantita_di(codici, quantita, n, codice)` | Indirizzo della quantità dell'articolo, `NULL` se assente |
| `inventario(codici, quantita, n)` | Stampa codici e quantità |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Carico e scarico

**a) Input** – `S 2011 5`, `C 2011 50`

**b) Output** – "scaricati 5, ora 3 pezzi"; "caricati 50, ora 53 pezzi"

**c) Variabili di supporto** – `q`

**d) Vincoli** – il main non conosce la posizione dell'articolo: modifica
`*q`

**e) Assunzioni** – codici tutti diversi

**f) Algoritmo in linguaggio naturale**
1. Cercare il codice nell'array `codici`.
2. Restituire `quantita + i`, l'indirizzo dell'elemento parallelo.
3. Nel main aggiungere o togliere `n` da `*q`.

### Caso d'uso 2 – Scarico non possibile

**a) Input** – `S 2011 5` con 3 pezzi

**b) Output** – "solo 3 pezzi disponibili"

**c) Variabili di supporto** – `*q`

**d) Vincoli** – la quantità non diventa mai negativa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scaricare solo se `*q >= n`.

### Caso d'uso 3 – Codice inesistente o dati non validi

**a) Input** – `S 9999 1`; `C 1001 0`

**b) Output** – "Codice 9999 inesistente."; "Dati non validi." e fine

**c) Variabili di supporto** – `q` = `NULL`

**d) Vincoli** – `*q` non si usa se `q` è `NULL`

**e) Assunzioni** – quantità del movimento maggiore di zero

**f) Algoritmo in linguaggio naturale** – controllare `q == NULL` prima di
qualsiasi dereferenziazione.
