# Analisi – 070-problema-prenotazione-aule.c

## 1. Problema

Tre aule informatiche si prenotano ora per ora. Il programma accetta una prenotazione se l'aula è libera e ha abbastanza postazioni, elenca le aule libere in un'ora e stampa la tabella della giornata.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Aula` | `nome, postazioni, prenotata[6][4]` | un'aula e le sue prenotazioni |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `aule` | `Aula[]` | 3 | Aule con la matrice delle prenotazioni |
| `a`, `ora`, `studenti` | `int` | — | Dati del comando |
| `classe` | `char[]` | 4 | Classe che prenota |
| `libere` | `int` | — | Conteggio |

| Funzione | Compito |
|----------|---------|
| `main` | Comandi P, L, T, Q |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prenotazione

**a) Input** – `P 3 2 1D 15`

**b) Output** – "Prenotato: Lab Gamma, 2a ora, 1D."

**c) Variabili di supporto** – `aule[a-1].prenotata[ora-1]`

**d) Vincoli** – aula libera, postazioni sufficienti

**e) Assunzioni** – aula 1-3, ora 1-6

**f) Algoritmo in linguaggio naturale** – strcpy della classe nella cella dell'ora.

### Caso d'uso 2 – Prenotazione rifiutata

**a) Input** – `P 1 1 2C 20`; `P 3 2 1D 22`

**b) Output** – "gia' della 3A"; "ha solo 16 postazioni"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllare prima la cella e poi le postazioni.

### Caso d'uso 3 – Aule libere e tabella

**a) Input** – `L 4`; `T`

**b) Output** – Lab Beta e Lab Gamma; tabella con -- per le ore libere

**c) Variabili di supporto** – `libere`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – una cella vuota ha il primo carattere '\0'.
