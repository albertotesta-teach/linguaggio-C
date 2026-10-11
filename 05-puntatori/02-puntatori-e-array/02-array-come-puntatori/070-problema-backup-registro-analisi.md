# Analisi – 070-problema-backup-registro.c

## 1. Problema

Prima che il docente corregga i voti di una verifica, il registro ne fa una
copia di sicurezza. Il docente inserisce le correzioni (numero dello
studente e nuovo voto) fino a `0 0`; il programma mostra i voti cambiati
rispetto alla copia e chiede conferma. Senza conferma i voti si ripristinano
dalla copia.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `char[][]` | 8 × 12 | Cognomi degli studenti |
| `voti` | `int[]` | 8 | Voti attuali |
| `backup` | `int[]` | 8 | Copia di sicurezza |
| `studente`, `voto` | `int` | — | Correzione letta |
| `risposta` | `char` | — | Conferma S/N |

| Funzione | Compito |
|----------|---------|
| `copia_blocco(dest, sorgente, n)` | Copia `n` interi con due puntatori |
| `mostra_differenze(attuali, backup, n, nomi)` | Stampa e conta i voti cambiati |
| `stampa_registro(voti, n, nomi)` | Elenco numerato dei voti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Correzioni confermate

**a) Input** – `3 8`, `6 5`, `3 7`, `0 0`, `S`

**b) Output** – Ferrari 5 → 7, Ricci 9 → 5; "Modifiche confermate."

**c) Variabili di supporto** – `cambiati` = 2

**d) Vincoli** – la seconda correzione dello studente 3 sostituisce la prima:
conta il voto finale

**e) Assunzioni** – voti interi da 1 a 10

**f) Algoritmo in linguaggio naturale**
1. `copia_blocco(backup, voti, 8)` all'inizio.
2. Applicare le correzioni a `voti`.
3. Confrontare i due array con due puntatori che avanzano insieme.

### Caso d'uso 2 – Correzioni annullate

**a) Input** – `1 4`, `0 0`, `N`

**b) Output** – "Modifiche annullate", registro finale uguale a quello iniziale

**c) Variabili di supporto** – `backup`

**d) Vincoli** – il ripristino usa la stessa funzione con gli argomenti
scambiati: `copia_blocco(voti, backup, 8)`

**e) Assunzioni** – qualsiasi risposta diversa da S/s annulla

**f) Algoritmo in linguaggio naturale** – se la risposta non è S, copiare
`backup` in `voti`.

### Caso d'uso 3 – Input non valido

**a) Input** – `9 6`; `2 11`

**b) Output** – "Studente inesistente."; "Il voto deve essere tra 1 e 10."

**c) Variabili di supporto** – nessuna

**d) Vincoli** – un indice fuori dall'array non si usa mai

**e) Assunzioni** – un input non numerico chiude l'inserimento

**f) Algoritmo in linguaggio naturale** – controllare studente e voto prima di
scrivere `voti[studente - 1]`.
