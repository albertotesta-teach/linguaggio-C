# Analisi – 050-problema-copia-di-un-file.c

## 1. Problema

Prima di modificare il diario il coordinatore ne vuole una copia. Il programma chiede il nome del file da copiare e quello della copia, apre i due file insieme (origine in "r", copia in "w") e copia carattere per carattere, contando caratteri e righe. Rifiuta lo stesso nome per i due file e chiede conferma se la copia esiste già.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `origine`, `destinazione` | `FILE *` | — | I due file aperti insieme |
| `nome_origine`, `nome_copia` | `char[]` | 60 | Nomi letti da tastiera |
| `risposta` | `char` | — | Conferma per sovrascrivere |
| `c` | `int` | — | Carattere letto o EOF |
| `caratteri`, `righe` | `int` | — | Conteggi della copia |

| Funzione | Compito |
|----------|---------|
| `esiste(nome)` | 1 se il file si apre in lettura (e lo richiude subito) |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Stesso nome

**a) Input** – `diario.txt`, `diario.txt`

**b) Output** – "la copia deve avere un nome diverso", nuova domanda

**c) Variabili di supporto** – —

**d) Vincoli** – nomi diversi

**e) Assunzioni** – confronto esatto dei nomi

**f) Algoritmo in linguaggio naturale** – aprire in "w" il file da leggere lo svuoterebbe.

### Caso d'uso 2 – Copia

**a) Input** – `diario.txt`, `diario-copia.txt`

**b) Output** – "Copiati 98 caratteri e 3 righe"

**c) Variabili di supporto** – `c`

**d) Vincoli** – —

**e) Assunzioni** – file di testo

**f) Algoritmo in linguaggio naturale** – fgetc/fputc fino a EOF; c è un int.

### Caso d'uso 3 – Copia già presente

**a) Input** – `diario.txt`, `diario-copia.txt`, `n`

**b) Output** – "Copia annullata."

**c) Variabili di supporto** – `risposta`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la destinazione non viene aperta; si chiude solo l'origine.

### Caso d'uso 4 – Origine mancante

**a) Input** – `mancante.txt`

**b) Output** – "Impossibile leggere mancante.txt"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la copia non viene creata.
