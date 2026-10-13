# Analisi – 070-problema-registro-che-cresce.c

## 1. Problema

Durante l'anno arrivano studenti nuovi e altri si trasferiscono. Il registro ha due blocchi che partono da NULL: i nomi e il tabellone dei voti (una riga per studente). Aggiungere uno studente significa aggiungere una riga in fondo; toglierlo significa far salire le righe successive e ridurre i blocchi, liberandoli quando restano vuoti.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Nome` | `testo[20]` | nome di uno studente |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `Nome *` | studenti (heap) | Nomi in ordine di arrivo |
| `voti` | `double *` | studenti × 3 (heap) | Voti di ITA, MAT, ING |
| `studenti` | `int` | — | Righe del registro |
| `posizione` | `int` | — | Riga dello studente cercato |

| Funzione | Compito |
|----------|---------|
| `aggiungi(&nomi, &voti, studenti, nome, v)` | realloc dei due blocchi e scrittura della riga nuova |
| `togli(&nomi, &voti, studenti, posizione)` | Righe successive su di una, poi realloc o free |
| `cerca(nomi, studenti, nome)` | Riga o -1 |
| `stampa(nomi, voti, studenti)` | Tabellone con le medie |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Arrivi

**a) Input** – `A Marta 7 6.5 8`, `A Luca 5 6 5.5`, `A Sara 8 9 7.5`

**b) Output** – "ingresso di Marta: righe 1, 24 byte di voti" ...

**c) Variabili di supporto** – `studenti`

**d) Vincoli** – nomi diversi

**e) Assunzioni** – 3 materie fisse

**f) Algoritmo in linguaggio naturale** – realloc(NULL, ...) al primo studente.

### Caso d'uso 2 – Doppione

**a) Input** – `A Luca 6 6 6`

**b) Output** – "Luca e' gia' nel registro."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca prima di aggiungere.

### Caso d'uso 3 – Trasferimenti

**a) Input** – `T Luca`, `T Paolo`

**b) Output** – "uscita di Luca: righe 2"; "Paolo non e' nel registro."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – le righe dopo Luca salgono; realloc a 2 righe.

### Caso d'uso 4 – Registro vuoto

**a) Input** – `T Marta`, `T Sara`, `S`

**b) Output** – "registro vuoto"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – con 0 studenti free e puntatori a NULL, niente realloc a 0.
