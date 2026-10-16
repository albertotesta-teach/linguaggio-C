# Analisi – 070-problema-copie-di-sicurezza.c

## 1. Problema

Il verbale del consiglio di classe viene aggiornato più volte. Prima di ogni modifica il programma fa ruotare le copie di sicurezza (.bak3 rimossa, .bak2 → .bak3, .bak1 → .bak2) e copia l'originale in .bak1; poi aggiunge in fondo la riga scritta dall'utente e mostra quante righe ha ogni versione presente.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nome` | `char[]` | 40 | File da modificare |
| `riga` | `char[]` | 100 | Riga da aggiungere |
| `copia_nome`, `da`, `a` | `char[]` | 50 | Nomi delle copie |
| `f` | `FILE *` | — | Originale in "a" |
| `ok` | `int` | — | 1 se si può modificare |

| Funzione | Compito |
|----------|---------|
| `ruota_copie(nome)` | remove e rename dalla copia più vecchia, poi copia in .bak1 |
| `copia(da, a)` | Copia carattere per carattere; 0 se fallisce |
| `esiste(nome)` | 1 se il file si apre in lettura |
| `stampa_righe(nome)` | Numero di righe del file |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prima modifica

**a) Input** – `verbale.txt`, una riga

**b) Output** – solo verbale.txt (1 riga)

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – il file non esiste

**f) Algoritmo in linguaggio naturale** – nessuna copia: "a" crea il file.

### Caso d'uso 2 – Modifiche successive

**a) Input** – altre tre righe

**b) Output** – bak1, bak2, bak3 con 3, 2, 1 righe

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – remove e rename falliscono finché le copie non esistono: si ignora.

### Caso d'uso 3 – Quinta modifica

**a) Input** – un'altra riga

**b) Output** – bak3 ha 2 righe: la versione con 1 riga si è persa

**c) Variabili di supporto** – —

**d) Vincoli** – 3 copie al massimo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – remove(bak3) prima delle rename.

### Caso d'uso 4 – Copia fallita

**a) Input** – disco pieno

**b) Output** – "Copia di sicurezza non riuscita: modifica annullata."

**c) Variabili di supporto** – `ok`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – l'originale non viene toccato.
