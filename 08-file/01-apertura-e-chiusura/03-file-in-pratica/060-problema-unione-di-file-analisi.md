# Analisi – 060-problema-unione-di-file.c

## 1. Problema

La segreteria vuole un unico file con gli elenchi di tutte le classi. Il programma crea il file di destinazione e vi copia, uno alla volta, i file indicati fino a FINE, ciascuno preceduto da un'intestazione. Salta con un avviso i file mancanti e il file di destinazione stesso; aggiunge l'a capo finale se un file non lo ha.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `destinazione` | `FILE *` | — | Aperto in "w" per tutta la durata |
| `origine` | `FILE *` | — | Un file da unire alla volta |
| `nome_destinazione`, `nome` | `char[]` | 60 | Nomi letti |
| `ultimo` | `int` | — | Ultimo carattere copiato |
| `uniti`, `mancanti`, `caratteri` | `int` | — | Riepilogo |

| Funzione | Compito |
|----------|---------|
| `ricopia(nome)` | Stampa il file risultante |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Unione

**a) Input** – `iscritti.txt`, poi `classe-3A.txt classe-4B.txt classe-2D.txt iscritti.txt classe-5C.txt FINE`

**b) Output** – 3 file uniti, 1 mancante, destinazione saltata; 43 caratteri copiati

**c) Variabili di supporto** – `ultimo`

**d) Vincoli** – nome della destinazione diverso dalle origini

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni origine: fopen, intestazione, copia, fclose.

### Caso d'uso 2 – Nessun file

**a) Input** – `vuoto.txt`, `FINE`

**b) Output** – file uniti 0

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la destinazione resta vuota.

### Caso d'uso 3 – Destinazione non creabile

**a) Input** – nome in cartella inesistente

**b) Output** – "Impossibile creare" su stderr

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – non si chiede nessun nome.
