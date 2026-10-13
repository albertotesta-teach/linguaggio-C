# Analisi – 080-problema-archivio-foto.c

## 1. Problema

L'archivio fotografico del giornalino contiene foto con anno, autore e didascalia. Ogni foto è una struct allocata e la didascalia è un secondo blocco della lunghezza esatta. Si libera prima la didascalia e poi la struct; per cambiare una didascalia si alloca il blocco nuovo prima di liberare il vecchio; per eliminare una foto si spostano indietro i puntatori.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Foto` | `anno, autore[16], didascalia (char *)` | una foto con la didascalia nello heap |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `archivio` | `Foto *[]` | 10 puntatori | Foto in ordine di inserimento |
| `testo` | `char[]` | 80 | Didascalia letta |
| `autore` | `char[]` | 16 | Autore |
| `n`, `anno`, `numero` | `int` | — | Foto presenti e dati dei comandi |

| Funzione | Compito |
|----------|---------|
| `copia_testo(testo)` | Blocco di strlen + 1 con il testo |
| `crea_foto(anno, autore, didascalia)` | Struct e didascalia; NULL senza perdite se una malloc fallisce |
| `distruggi_foto(f)` | Libera la didascalia e poi la struct |
| `cambia_didascalia(f, nuova)` | Nuovo blocco, poi free del vecchio; 0 se manca memoria |
| `leggi_resto(testo)` | Resto della riga senza spazi iniziali e finali |
| `mostra(archivio, n)` | Elenco delle foto |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Aggiunta

**a) Input** – `A 2024 Marta Festa di fine anno in cortile`

**b) Output** – "foto 1 aggiunta (didascalia di 30 byte)"

**c) Variabili di supporto** – `archivio[n]`

**d) Vincoli** – anno da 1900 a 2100, al massimo 10 foto

**e) Assunzioni** – autore di una parola

**f) Algoritmo in linguaggio naturale** – crea_foto: malloc della struct, copia_testo della didascalia.

### Caso d'uso 2 – Dati mancanti

**a) Input** – `A 2023 Sara`; `A 1800 Sara vecchia`

**b) Output** – "Manca la didascalia."; "Dati non validi."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna allocazione.

### Caso d'uso 3 – Cambio didascalia

**a) Input** – `C 2 Primo posto alla gara di robotica`

**b) Output** – "didascalia della foto 2 cambiata"

**c) Variabili di supporto** – `copia`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – prima la nuova copia, poi free della vecchia: se la malloc fallisce la vecchia resta.

### Caso d'uso 4 – Eliminazione

**a) Input** – `D 1`

**b) Output** – "foto 1 eliminata"; le foto successive scalano

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – distruggi_foto e spostamento indietro dei puntatori.

### Caso d'uso 5 – Fine

**a) Input** – `Q`

**b) Output** – "Archivio chiuso: foto liberate 2, blocchi liberati 4"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – distruggi_foto per ogni foto rimasta.
