# Analisi – 070-problema-modifiche-anagrafica.c

## 1. Problema

La segreteria aggiorna telefono, email e anno di corso di uno studente. Le modifiche si fanno su una copia della scheda; premendo solo Invio un campo resta invariato. Il programma elenca i campi cambiati e, con la conferma, copia la scheda modificata su quella ufficiale.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Anagrafica` | `cognome, nome, telefono, email, classe` | recapiti di uno studente |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `originale` | `Anagrafica` | — | Scheda ufficiale |
| `modificata` | `Anagrafica` | — | Copia di lavoro |
| `riga` | `char[]` | 80 | Riga letta |
| `cambiati` | `int` | — | Campi modificati |

| Funzione | Compito |
|----------|---------|
| `leggi_riga(riga, lunghezza)` | Legge una riga con fgets e toglie l'a capo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Modifica

**a) Input** – Invio, `fam.marino@scuola.it`, `4`

**b) Output** – email e classe cambiate, telefono invariato

**c) Variabili di supporto** – `modificata`

**d) Vincoli** – il testo deve stare nel campo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – copiare nella scheda di lavoro solo le righe non vuote e valide.

### Caso d'uso 2 – Conferma

**a) Input** – `S`

**b) Output** – "Scheda aggiornata."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – originale = modificata copia tutti i campi.

### Caso d'uso 3 – Nessuna modifica o annullamento

**a) Input** – tre Invio; oppure `N`

**b) Output** – "nessuna"; "Modifiche scartate."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il confronto campo per campo decide; con N la copia si ignora.
