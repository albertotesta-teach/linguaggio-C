# Analisi – 040-problema-controllo-accessi.c

## 1. Problema

La telecamera all'ingresso del parcheggio legge una targa per riga. Il programma controlla il formato AA000AA e decide se alzare la sbarra in base all'elenco delle targhe autorizzate. FINE termina e stampa il numero di ingressi consentiti e negati.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Targa` | `typedef char Targa[8];` | 7 caratteri più il terminatore |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `elenco` | `const Targa[]` | 5 | Targhe autorizzate |
| `riga` | `char[]` | 40 | Riga letta con fgets |
| `targa` | `Targa` | 8 | Targa da controllare |
| `consentiti`, `negati` | `int` | — | Contatori |

| Funzione | Compito |
|----------|---------|
| `targa_valida(t)` | 1 se il formato è AA000AA |
| `autorizzata(t, elenco, n)` | 1 se la targa è nell'elenco |
| `lettera(c)` | 1 se c è una lettera maiuscola |
| `cifra(c)` | 1 se c è una cifra |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Targa autorizzata

**a) Input** – `EK301TZ`

**b) Output** – "EK301TZ: sbarra alzata."

**c) Variabili di supporto** – `consentiti`

**d) Vincoli** – la riga deve avere esattamente 7 caratteri

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – copiare la riga nella Targa, controllare il formato e cercarla con strcmp nell'elenco.

### Caso d'uso 2 – Targa non autorizzata

**a) Input** – `AB123CD`

**b) Output** – "AB123CD: accesso negato."

**c) Variabili di supporto** – `negati`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – formato valido ma assente dall'elenco.

### Caso d'uso 3 – Lettura non valida

**a) Input** – `ab123cd`, `DM774PAX`

**b) Output** – "Lettura non valida, ripetere."

**c) Variabili di supporto** – —

**d) Vincoli** – minuscole e righe troppo lunghe sono scartate

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se la lunghezza non è 7 la riga non viene copiata nella Targa, evitando di uscire dall'array.
