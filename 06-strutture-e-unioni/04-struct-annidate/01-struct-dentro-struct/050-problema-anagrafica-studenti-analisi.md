# Analisi – 050-problema-anagrafica-studenti.c

## 1. Problema

La segreteria organizza i pulmini per le uscite e cerca gli studenti per comune o per CAP, e conta quanti abitano in ogni provincia. L'indirizzo è una struct dentro lo studente: elenco[i].residenza.comune. Il comune può contenere spazi, quindi i comandi si leggono a righe con fgets.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Indirizzo` | `via, cap, comune, provincia` | residenza |
| `Studente` | `nome, classe, residenza` | studente con il suo Indirizzo |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `elenco` | `Studente[]` | 7 | Studenti con l'indirizzo |
| `riga` | `char[]` | 40 | Comando letto |
| `argomento` | `char *` | — | Testo dopo la lettera del comando |
| `province`, `conteggi` | `char[][3]`, `int[]` | 7 | Province trovate e quanti studenti in ognuna |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ricerca per comune

**a) Input** – `C Novi Ligure`

**b) Output** – Greco Paolo e Fabbri Ivo, "Trovati: 2"

**c) Variabili di supporto** – `trovati`

**d) Vincoli** – confronto esatto con strcmp

**e) Assunzioni** – maiuscole come nell'archivio

**f) Algoritmo in linguaggio naturale** – per ogni studente confrontare elenco[i].residenza.comune con l'argomento.

### Caso d'uso 2 – Ricerca per CAP

**a) Input** – `Z 14100`

**b) Output** – Villa Sara e Conte Mattia

**c) Variabili di supporto** – —

**d) Vincoli** – il CAP è una stringa di 5 cifre

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stesso ciclo sul campo residenza.cap.

### Caso d'uso 3 – Province

**a) Input** – `P`

**b) Output** – "AL: 5 studenti", "AT: 2 studenti"

**c) Variabili di supporto** – `province`, `conteggi`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni studente cercare la provincia tra quelle già viste; se manca aggiungerla con conteggio zero, poi incrementare.

### Caso d'uso 4 – Argomento mancante

**a) Input** – `C`

**b) Output** – "Manca il comune o il CAP."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – una riga di meno di tre caratteri non ha l'argomento.
