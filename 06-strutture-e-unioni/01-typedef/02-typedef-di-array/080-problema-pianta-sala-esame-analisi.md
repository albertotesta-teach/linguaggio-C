# Analisi – 080-problema-pianta-sala-esame.c

## 1. Problema

L'aula magna ha 5 file da 8 banchi. Per la prova scritta i candidati si siedono a scacchiera (un banco è occupabile se fila + banco è pari) e alcuni banchi sono rotti. Il programma legge il numero di candidati, li dispone in ordine, stampa la pianta e indica quanti candidati vanno in una seconda aula.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Pianta` | `typedef char Pianta[5][8];` | un carattere per ogni banco |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `aula` | `Pianta` | 5 × 8 | '.' libero, '#' rotto, 'C' candidato |
| `candidati` | `int` | — | Numero letto |
| `sistemati` | `int` | — | Candidati effettivamente disposti |

| Funzione | Compito |
|----------|---------|
| `occupabile(p, f, b)` | 1 se il banco è a scacchiera e non rotto |
| `capienza(p)` | Numero di banchi occupabili |
| `disponi(p, candidati)` | Scrive 'C' nei banchi e restituisce quanti ne ha usati |
| `stampa(p)` | Disegna la pianta con la legenda |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Posti sufficienti

**a) Input** – `12`

**b) Output** – pianta con 12 'C', "Candidati sistemati: 12"

**c) Variabili di supporto** – `aula`

**d) Vincoli** – nessun candidato ha un vicino davanti, dietro o di lato

**e) Assunzioni** – i banchi rotti sono fissati nel programma

**f) Algoritmo in linguaggio naturale** – disponi scorre file e banchi finché ci sono candidati e posti.

### Caso d'uso 2 – Posti insufficienti

**a) Input** – `20`

**b) Output** – 17 sistemati; "Serve una seconda aula per 3 candidati."

**c) Variabili di supporto** – `sistemati`

**d) Vincoli** – capienza 17

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – disponi si ferma quando finiscono i banchi; la differenza va nella seconda aula.

### Caso d'uso 3 – Input non valido

**a) Input** – `-4`

**b) Output** – "Valore non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – non si dispone nessun candidato.
