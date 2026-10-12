# Analisi – 070-problema-lettura-scheda.c

## 1. Problema

Il bibliotecario inserisce un nuovo libro. leggi_libro riempie la struct del chiamante tramite il puntatore e restituisce 1 solo se tutti i campi sono validi, compreso il codice ISBN a 13 cifre con la cifra di controllo. Si hanno al massimo tre tentativi.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Libro` | `titolo, autore, anno, pagine, isbn` | scheda di catalogo |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nuovo` | `Libro` | — | Scheda da riempire |
| `tentativo`, `valido` | `int` | — | Ciclo dei tentativi |
| `riga` | `char[]` | 80 | Riga letta |

| Funzione | Compito |
|----------|---------|
| `leggi_libro(l)` | Riempie *l; 0 al primo campo non valido |
| `leggi_testo(domanda, dest, dimensione)` | Riga non vuota che stia nel campo |
| `isbn_valido(isbn)` | 13 cifre, pesi 1 e 3, somma multipla di 10 |
| `stampa(l)` | Riceve const Libro * |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Titolo vuoto

**a) Input** – riga vuota

**b) Output** – "Titolo e autore non possono essere vuoti o troppo lunghi."

**c) Variabili di supporto** – `valido`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il tentativo fallisce e si ricomincia.

### Caso d'uso 2 – Scheda valida

**a) Input** – `Il nome della rosa`, `Umberto Eco`, `1980 503`, `9788845292613`

**b) Output** – "Scheda inserita" con tutti i campi

**c) Variabili di supporto** – `nuovo`

**d) Vincoli** – anno 1450-2026, pagine 1-5000

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ogni campo si scrive con l->campo.

### Caso d'uso 3 – ISBN errato

**a) Input** – `9788845292614`

**b) Output** – "ISBN non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – cifra di controllo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la somma pesata non è multipla di 10.
