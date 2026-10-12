# Analisi – 040-problema-rubrica-classe.c

## 1. Problema

Il rappresentante di classe cerca nella rubrica i contatti per inizio del cognome o per ruolo (studente, docente, genitore), oppure stampa l'elenco completo. Ogni ricerca indica quanti contatti ha trovato.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Contatto` | `cognome, nome, telefono, ruolo` | una voce della rubrica |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `rubrica` | `Contatto[]` | 8 | Contatti |
| `comando` | `char` | — | C, R, E o Q |
| `testo` | `char[]` | 20 | Testo da cercare |
| `trovati` | `int` | — | Risultati della ricerca |

| Funzione | Compito |
|----------|---------|
| `main` | Ricerca con strncmp sul cognome e strcmp sul ruolo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ricerca per cognome

**a) Input** – `C Ba`

**b) Output** – Barbieri, Bassi Andrea, Bassi Paola; trovati 3

**c) Variabili di supporto** – `trovati`

**d) Vincoli** – confronto sui primi strlen(testo) caratteri

**e) Assunzioni** – maiuscole come nella rubrica

**f) Algoritmo in linguaggio naturale** – strncmp(rubrica[i].cognome, testo, strlen(testo)) == 0.

### Caso d'uso 2 – Ricerca per ruolo

**a) Input** – `R docente`

**b) Output** – Benedetti, Fontana; trovati 2

**c) Variabili di supporto** – —

**d) Vincoli** – ruolo uguale

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – strcmp sul campo ruolo.

### Caso d'uso 3 – Nessun risultato

**a) Input** – `C Z`

**b) Output** – "Trovati: 0"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo non stampa nulla.
