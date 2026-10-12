# Analisi – 070-problema-codici-aule.c

## 1. Problema

Ogni aula ha un codice di 5 caratteri nel formato E P-NN (edificio, piano, trattino, numero su due cifre). Il programma compone i codici a partire dai dati della segreteria, li stampa e poi, per ogni codice letto, indica edificio, piano, numero e capienza, oppure segnala un codice non valido o un'aula inesistente.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Codice` | `typedef char Codice[6];` | 5 caratteri più il terminatore |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `edifici`, `piani`, `numeri`, `capienza` | array paralleli | 6 | Dati delle aule |
| `codici` | `Codice[]` | 6 | Codici composti |
| `richiesto` | `Codice` | 6 | Codice letto |
| `edificio`, `piano`, `numero` | `char`, `int`, `int` | — | Parti del codice letto |

| Funzione | Compito |
|----------|---------|
| `componi(c, edificio, piano, numero)` | Scrive il codice nella Codice del chiamante |
| `scomponi(c, &edificio, &piano, &numero)` | 1 se il formato è valido, con le parti nei parametri di uscita |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Elenco dei codici

**a) Input** – dati nel programma

**b) Output** – A0-03, A1-12, A1-14, B2-07, B2-09, C0-01

**c) Variabili di supporto** – `codici`

**d) Vincoli** – numero su due cifre con lo zero iniziale

**e) Assunzioni** – piano da 0 a 9, numero da 0 a 99

**f) Algoritmo in linguaggio naturale** – componi scrive carattere per carattere e chiude con '\0'.

### Caso d'uso 2 – Ricerca riuscita

**a) Input** – `B2-07`

**b) Output** – "Edificio B, piano 2, aula 7: 26 posti."

**c) Variabili di supporto** – `edificio`, `piano`, `numero`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scomponi valida il formato; la ricerca con strcmp tra i codici trova la capienza.

### Caso d'uso 3 – Codice errato o assente

**a) Input** – `B2_07`, `C0-1`; `A1-15`

**b) Output** – "Codice non valido."; "aula inesistente."

**c) Variabili di supporto** – —

**d) Vincoli** – righe di lunghezza diversa da 5 non sono copiate nella Codice

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – un formato valido ma non presente nell'elenco dà comunque le sue parti.
