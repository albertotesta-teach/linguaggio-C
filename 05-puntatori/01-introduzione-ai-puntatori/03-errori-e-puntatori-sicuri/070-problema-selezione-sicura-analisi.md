# Analisi – 070-problema-selezione-sicura.c

## 1. Problema

Il pannello di una lavatrice permette di cambiare temperatura, centrifuga
e durata scrivendo un codice e un valore ("T 40", "C 1200"). Ogni
impostazione ha un intervallo ammesso. Le richieste con codice sconosciuto
o senza valore sono scartate, i valori fuori intervallo rifiutati. Una riga
vuota avvia il lavaggio con le impostazioni finali.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `temperatura`, `centrifuga`, `durata` | `int` | — | Impostazioni |
| `limiti_temp`, `limiti_centr`, `limiti_durata` | `const int[]` | 2 | Minimo e massimo |
| `valore` | `int *` | — | Impostazione da modificare |
| `minimo`, `massimo` | `const int *` | — | Limiti, di sola lettura |
| `riga`, `codice`, `nuovo` | — | — | Richiesta letta con `fgets` e `sscanf` |

| Funzione | Compito |
|----------|---------|
| `imposta(valore, minimo, massimo, nuovo)` | Controlla i puntatori e i limiti, poi scrive |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Richiesta valida

**a) Input** – `T 40`; `C 1200`; `D 90`

**b) Output** – "impostato 40", "impostato 1200", "impostato 90"

**c) Variabili di supporto** – i tre puntatori

**d) Vincoli** – `&limiti_temp[0]` è l'indirizzo di un elemento `const`: si
memorizza in un `const int *`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – in base al codice far puntare
`valore`, `minimo` e `massimo` alle variabili giuste e chiamare `imposta`.

### Caso d'uso 2 – Fuori limiti

**a) Input** – `C 1600`

**b) Output** – "valore fuori dai limiti 400-1400"

**c) Variabili di supporto** – `*minimo`, `*massimo`

**d) Vincoli** – l'impostazione non cambia

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `nuovo` è fuori intervallo la
funzione restituisce `FUORI_LIMITI`.

### Caso d'uso 3 – Richiesta non valida

**a) Input** – `Z 5`; `D` (senza valore)

**b) Output** – "richiesta non valida"

**c) Variabili di supporto** – puntatori `NULL`, `nuovo` = 0

**d) Vincoli** – `imposta` controlla che nessun puntatore sia `NULL` prima di usarli

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `sscanf` non legge due valori o
il codice è sconosciuto i puntatori restano `NULL` e la funzione restituisce
`NON_VALIDO`.
