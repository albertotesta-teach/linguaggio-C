# Analisi – 060-problema-registro-degli-errori.c

## 1. Problema

La segreteria carica i voti della verifica di recupero, una riga "cognome voto" per studente. Le righe valide vanno in recupero.txt (aperto in "w"); quelle errate sono segnalate su stderr e aggiunte allo storico errori.txt (aperto in "a"). Una funzione con il flusso come parametro scrive lo stesso messaggio sui due flussi.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `validi` | `FILE *` | — | recupero.txt in "w" |
| `errori` | `FILE *` | — | errori.txt in "a" |
| `cognome`, `testo_voto` | `char[]` | 30, 16 | Riga letta |
| `voto`, `dopo` | `int`, `char` | — | Conversione con sscanf %d%c |
| `riga`, `caricati`, `scartati` | `int` | — | Conteggi |

| Funzione | Compito |
|----------|---------|
| `segnala(f, riga, cognome, motivo)` | Scrive il messaggio d'errore sul flusso f |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Voti con errori

**a) Input** – `Rossi 6`, `Bianchi sei`, `Verdi 7`, `Neri 11`, `Russo 5`, `FINE`

**b) Output** – 3 caricati, 2 scartati; errori per le righe 2 e 4

**c) Variabili di supporto** – `riga`

**d) Vincoli** – voto intero 1-10

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sscanf deve leggere solo il numero; poi controllo dell'intervallo.

### Caso d'uso 2 – Storico

**a) Input** – più esecuzioni

**b) Output** – errori.txt cresce, recupero.txt si rifà

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – "a" per lo storico, "w" per il file del giorno.

### Caso d'uso 3 – Secondo file non apribile

**a) Input** – errori.txt protetto

**b) Output** – messaggio su stderr

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – si chiude recupero.txt, già aperto.
