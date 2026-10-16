# Analisi – 050-problema-divisione-per-classe.c

## 1. Problema

Gli iscritti al corso di primo soccorso arrivano in un unico elenco "classe cognome", in ordine sparso. Il programma tiene aperti insieme i file di tutte le classi incontrate (classe-3A.txt, ...): per ogni riga cerca la classe, apre il suo file se è nuova e vi scrive il cognome. Alla fine chiude tutti i file e ne stampa il contenuto.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `classi` | `char[][8]` | 8 | Classi incontrate |
| `file` | `FILE *[]` | 8 | Un file aperto per classe |
| `conta` | `int[]` | 8 | Iscritti per classe |
| `classe`, `cognome`, `nome_file` | `char[]` | 8, 30, 30 | Riga letta e nome del file |
| `n`, `scartati` | `int` | — | Classi aperte e righe scartate |

| Funzione | Compito |
|----------|---------|
| `cerca(classi, n, classe)` | Indice della classe o -1 |
| `ricopia(nome)` | Stampa un file a video |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Corso di primo soccorso

**a) Input** – 7 iscritti di 3A, 4B e 5C, poi `FINE`

**b) Output** – 3 file; 3A con 3 iscritti, 4B e 5C con 2

**c) Variabili di supporto** – `file`

**d) Vincoli** – al massimo 8 classi

**e) Assunzioni** – classi senza spazi

**f) Algoritmo in linguaggio naturale** – cerca; se -1 fopen "w" e nuova classe; fprintf nel file della classe.

### Caso d'uso 2 – Troppe classi

**a) Input** – una nona classe

**b) Output** – "scartato ..." su stderr

**c) Variabili di supporto** – `scartati`

**d) Vincoli** – MAX_CLASSI e FOPEN_MAX

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuno spazio nell'array: la riga si scarta.

### Caso d'uso 3 – Chiusura

**a) Input** – —

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – fclose di tutti gli n file prima di rileggerli.
