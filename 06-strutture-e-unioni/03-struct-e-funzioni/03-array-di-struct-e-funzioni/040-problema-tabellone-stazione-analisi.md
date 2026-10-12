# Analisi – 040-problema-tabellone-stazione.c

## 1. Problema

Il tabellone della stazione mostra le partenze della mattina. Il programma registra ritardi e soppressioni tramite una funzione che modifica l'elemento giusto dell'array, cerca il prossimo treno per una destinazione restituendo un puntatore e stampa il tabellone.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Partenza` | `numero, destinazione, partenza, ritardo, binario` | riga del tabellone |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `tabellone` | `Partenza[]` | 6 | Partenze |
| `treno` | `const Partenza *` | — | Treno restituito da prossima |
| `numero`, `destinazione` | `char[]` | 8, 16 | Dati del comando |

| Funzione | Compito |
|----------|---------|
| `stampa_tabellone(t, n)` | Stato di ogni treno |
| `prossima(t, n, ora, dest)` | Primo treno utile, NULL se nessuno |
| `registra_ritardo(t, n, numero, minuti)` | Modifica l'elemento; 0 se assente |
| `stampa_ora(minuti)` | Formato hh:mm |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ritardi

**a) Input** – `R R10220 12`, `S R10222`

**b) Output** – "R10220 aggiornato."; tabellone con "ritardo 12'" e "SOPPRESSO"

**c) Variabili di supporto** – `tabellone[i].ritardo`

**d) Vincoli** – ritardo non negativo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cercare il numero e scrivere nel campo.

### Caso d'uso 2 – Prossimo treno

**a) Input** – `P 07:10 Genova`

**b) Output** – "Prossimo per Genova: R10220, binario 2, parte alle 07:17"

**c) Variabili di supporto** – `treno`

**d) Vincoli** – si conta il ritardo, i soppressi si saltano

**e) Assunzioni** – orari della stessa giornata

**f) Algoritmo in linguaggio naturale** – il primo con partenza + ritardo >= ora.

### Caso d'uso 3 – Nessun treno

**a) Input** – `P 07:20 Genova`

**b) Output** – "Nessun treno per Genova."

**c) Variabili di supporto** – `treno` = NULL

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – l'R10222 è soppresso.
