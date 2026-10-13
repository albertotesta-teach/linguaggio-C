# Analisi – 070-problema-posti-della-gita.c

## 1. Problema

Per la gita di fine anno si iscrivono gli studenti sui posti del pullman. La capienza dipende dal pullman prenotato: si legge all'inizio e l'elenco dei partecipanti si alloca con malloc. Il programma registra acconti, versamenti e autorizzazioni e indica chi non può ancora partire.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Partecipante` | `nome[20], classe[4], versato, autorizzazione` | un posto del pullman |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `posti` | `Partecipante *` | capienza elementi (heap) | Elenco dei partecipanti |
| `capienza`, `iscritti` | `int` | — | Posti del pullman e posti occupati |
| `posto`, `euro` | `int`, `double` | — | Dati dei comandi |
| `nome`, `classe` | `char[]` | 20, 8 | Dati letti prima della copia |

| Funzione | Compito |
|----------|---------|
| `elenco(posti, iscritti)` | Quanto manca alla quota e autorizzazione |
| `riepilogo(posti, iscritti, capienza)` | Posti liberi, chi non può partire, soldi raccolti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Iscrizioni

**a) Input** – `3`, poi `I Marta 3B 40`, `I Luca 3A 85`

**b) Output** – "Marta al posto 1", "Luca al posto 2"

**c) Variabili di supporto** – `iscritti`

**d) Vincoli** – acconto da 0 a 85 euro, classe fino a 3 caratteri

**e) Assunzioni** – quota 85 euro

**f) Algoritmo in linguaggio naturale** – copiare i dati in posti[iscritti] e incrementare iscritti.

### Caso d'uso 2 – Pullman pieno

**a) Input** – quarta iscrizione con 3 posti

**b) Output** – "Pullman pieno: Sara non iscritto."

**c) Variabili di supporto** – —

**d) Vincoli** – iscritti non supera capienza

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllare iscritti == capienza prima di scrivere.

### Caso d'uso 3 – Versamenti e autorizzazioni

**a) Input** – `V 1 45`, `A 1`, `A 5`

**b) Output** – "Marta: versati 85.00 euro", "Posto non valido."

**c) Variabili di supporto** – `posto`

**d) Vincoli** – il totale non supera la quota

**e) Assunzioni** – posti numerati da 1

**f) Algoritmo in linguaggio naturale** – l'indice dell'array è posto - 1.

### Caso d'uso 4 – Riepilogo

**a) Input** – `R`

**b) Output** – posti liberi, chi non può partire, raccolti 230.00 euro su 255.00

**c) Variabili di supporto** – `pronti`, `raccolto`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – parte chi ha versato tutta la quota e ha l'autorizzazione.
