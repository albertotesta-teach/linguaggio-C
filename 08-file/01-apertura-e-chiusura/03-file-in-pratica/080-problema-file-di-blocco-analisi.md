# Analisi – 080-problema-file-di-blocco.c

## 1. Problema

Più docenti prenotano l'aula informatica con lo stesso programma. Un file di blocco, aula.lock, dice con la sua sola esistenza che l'aula è occupata e contiene il cognome di chi l'ha prenotata. Prenotare crea il file e aggiunge una riga a prenotazioni.txt; liberare lo rimuove, ma solo se lo chiede chi ha prenotato.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `comando` | `char` | — | P, L, S, R o Q |
| `cognome` | `char[]` | 30 | Docente che fa la richiesta |
| `occupante` | `char[]` | 30 | Cognome letto dal file di blocco |

| Funzione | Compito |
|----------|---------|
| `leggi_occupante(occupante, dimensione)` | 1 se aula.lock esiste; legge il cognome con fgetc |
| `prenota(cognome)` | Crea aula.lock, aggiunge la riga al registro; 0 se non riesce |
| `ricopia(nome)` | Stampa il registro |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prenotazione

**a) Input** – `S`, `P Rossi`

**b) Output** – "libera", "aula prenotata da Rossi"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il file di blocco non esiste: si crea con il cognome.

### Caso d'uso 2 – Aula occupata

**a) Input** – `P Bianchi`, `L Bianchi`

**b) Output** – "aula occupata da Rossi", "solo Rossi puo' liberare l'aula"

**c) Variabili di supporto** – `occupante`

**d) Vincoli** – solo chi ha prenotato libera

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il cognome nel file decide.

### Caso d'uso 3 – Liberazione e registro

**a) Input** – `L Rossi`, `P Bianchi`, `R`, `L Bianchi`

**b) Output** – aula liberata, poi prenotata da Bianchi; registro con 2 righe

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – remove("aula.lock").

### Caso d'uso 4 – Due programmi insieme

**a) Input** – —

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – uso non contemporaneo

**f) Algoritmo in linguaggio naturale** – il controllo e la creazione non sono un'unica operazione indivisibile.
