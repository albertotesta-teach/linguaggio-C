# Analisi – 050-problema-magazzino-laboratorio.c

## 1. Problema

Il tecnico del laboratorio di elettronica registra carichi e prelievi di componenti identificati da un codice e stampa gli articoli sotto la scorta minima con la quantità da ordinare per tornare al doppio della scorta.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Articolo` | `codice, descrizione, quantita, scorta_minima` | componente del magazzino |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `magazzino` | `Articolo[]` | 6 | Articoli |
| `codice`, `pezzi` | `char[]`, `int` | 8, — | Dati del comando |
| `a` | `int` | — | Indice dell'articolo trovato |
| `sottoscorta` | `int` | — | Conteggio |

| Funzione | Compito |
|----------|---------|
| `main` | Ricerca del codice e aggiornamento della quantità |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prelievo

**a) Input** – `P LED-R 30`

**b) Output** – "LED rosso 5 mm: ora 34 pezzi." e avviso di scorta

**c) Variabili di supporto** – `magazzino[a].quantita`

**d) Vincoli** – non si preleva più del presente

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cercare il codice con strcmp e sottrarre.

### Caso d'uso 2 – Prelievo impossibile o codice errato

**a) Input** – `P BB400 12`; `P ABC 3`

**b) Output** – "disponibili solo 9 pezzi"; "Codice ABC sconosciuto."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la quantità non cambia.

### Caso d'uso 3 – Sottoscorta

**a) Input** – `S`

**b) Output** – LED-R ordinare 46, LED-V ordinare 45

**c) Variabili di supporto** – `sottoscorta`

**d) Vincoli** – da ordinare = 2 × scorta minima - quantità

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scorrere l'array e stampare gli articoli sotto la scorta.
