# Analisi – 040-problema-pagella-a-video-e-su-file.c

## 1. Problema

A fine trimestre il coordinatore inserisce i voti di uno studente nelle sei materie. La pagella, con media e insufficienze, si vede a video e, dopo conferma, si salva in pagella-cognome.txt. Una sola funzione scrive la pagella sul flusso ricevuto, così le due copie sono identiche.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `materie` | `const char *[]` | 6 | Nomi delle materie |
| `voti` | `int[]` | 6 | Voti da 1 a 10 |
| `cognome`, `nome_file` | `char[]` | 30, 50 | Studente e file pagella-cognome.txt |
| `f` | `FILE *` | — | File della pagella |
| `risposta` | `char` | — | Conferma del salvataggio |

| Funzione | Compito |
|----------|---------|
| `stampa_pagella(f, cognome, materie, voti, n)` | Scrive la pagella sul flusso f con fprintf |
| `leggi_voto(materia)` | Voto da 1 a 10, ripetendo la domanda; 0 se l'input finisce |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Pagella salvata

**a) Input** – `Bianchi`, `7 5 otto 8 9 11 6 6`, `s`

**b) Output** – "otto" e 11 rifiutati; media 6.83; 1 insufficienza; pagella-Bianchi.txt

**c) Variabili di supporto** – `voti`

**d) Vincoli** – voti interi 1-10

**e) Assunzioni** – cognome senza spazi

**f) Algoritmo in linguaggio naturale** – stampa_pagella(stdout, ...), poi stampa_pagella(f, ...).

### Caso d'uso 2 – Non salvata

**a) Input** – ... `n`

**b) Output** – "Pagella non salvata."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il file non viene creato.

### Caso d'uso 3 – Input interrotto

**a) Input** – fine dell'input a metà

**b) Output** – "Dati incompleti."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – leggi_voto restituisce 0.
