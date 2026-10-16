# Analisi – 040-problema-salvataggio-sicuro.c

## 1. Problema

La classe tiene in libri.txt l'elenco della biblioteca di classe, un titolo per riga. Il programma carica il file carattere per carattere in un array (vuoto se il file non c'è), permette di aggiungere e togliere titoli e salva con il salvataggio sicuro: scrive libri.tmp, lo chiude, rimuove libri.txt e rinomina il temporaneo. Avvisa se si esce con modifiche non salvate.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `titoli` | `char[][60]` | 50 | Elenco in memoria |
| `n` | `int` | — | Titoli presenti |
| `comando`, `numero` | `char`, `int` | — | Comando e titolo da rimuovere |
| `modificato` | `int` | — | 1 se ci sono modifiche non salvate |

| Funzione | Compito |
|----------|---------|
| `carica(nome, titoli)` | Legge un titolo per riga con fgetc; restituisce quanti |
| `salva(nome, temporaneo, titoli, n)` | Scrive il temporaneo, remove, rename; 0 se non riesce |
| `elenco(titoli, n)` | Stampa i titoli numerati |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prima esecuzione

**a) Input** – `A ...` tre volte, `E`, `S`, `Q`

**b) Output** – 0 libri caricati; 3 salvati

**c) Variabili di supporto** – `modificato`

**d) Vincoli** – titoli fino a 59 caratteri

**e) Assunzioni** – un titolo per riga

**f) Algoritmo in linguaggio naturale** – carica restituisce 0 se il file non c'è.

### Caso d'uso 2 – Seconda esecuzione

**a) Input** – `E`, `R 2`, `A ...`, `R 9`, `E`, `Q`

**b) Output** – 3 caricati; "numero non valido"; avviso di modifiche non salvate

**c) Variabili di supporto** – —

**d) Vincoli** – numero 1-n

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la rimozione sposta indietro i titoli successivi.

### Caso d'uso 3 – Temporaneo non creabile

**a) Input** – cartella protetta

**b) Output** – "salvataggio non riuscito: libri.txt non e' stato toccato"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – remove e rename non vengono eseguite.
