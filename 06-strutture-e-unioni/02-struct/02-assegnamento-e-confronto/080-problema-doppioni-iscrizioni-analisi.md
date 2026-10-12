# Analisi – 080-problema-doppioni-iscrizioni.c

## 1. Problema

Il modulo online dei corsi pomeridiani a volte invia due volte la stessa iscrizione. Ogni iscrizione si confronta con la precedente: se è identica è un doppione, se cambia solo il giorno è una correzione, altrimenti è nuova. FINE termina e il programma stampa i conteggi.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Iscrizione` | `cognome, corso, giorno` | una richiesta del modulo |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `precedente`, `corrente` | `Iscrizione` | — | Ultima accettata e appena letta |
| `giorni` | `const char *[]` | 6 | Nomi brevi dei giorni |
| `nuove`, `doppioni`, `correzioni` | `int` | — | Conteggi |

| Funzione | Compito |
|----------|---------|
| `main` | Confronto tra iscrizioni consecutive |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Doppione

**a) Input** – `Rossi robotica 2` due volte

**b) Output** – "Doppione scartato."

**c) Variabili di supporto** – `doppioni`

**d) Vincoli** – tutti i campi uguali

**e) Assunzioni** – i doppioni sono consecutivi

**f) Algoritmo in linguaggio naturale** – confrontare cognome e corso con strcmp e il giorno con ==.

### Caso d'uso 2 – Correzione

**a) Input** – `Bianchi teatro 4`, poi `Bianchi teatro 3`

**b) Output** – "Correzione: Bianchi passa da gio a mer."

**c) Variabili di supporto** – `correzioni`

**d) Vincoli** – stesso cognome e corso

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – precedente = corrente aggiorna l'ultima accettata.

### Caso d'uso 3 – Nuova iscrizione

**a) Input** – `Verdi coro 1`

**b) Output** – "Nuova iscrizione: Verdi, coro, lun."

**c) Variabili di supporto** – `nuove`

**d) Vincoli** – giorno 1-5

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – si conta e diventa la precedente.
