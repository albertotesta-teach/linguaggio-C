# Analisi – 040-problema-ticket-assistenza.c

## 1. Problema

Il tecnico del laboratorio registra i guasti come ticket con due campi enum, priorità e stato. I cambi di stato permessi sono in una tabella permesso[da][a]; cambia_stato applica il cambio solo se la tabella lo consente. L'elenco mostra i ticket non chiusi dalla priorità più alta.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Priorita` | `BASSA, MEDIA, ALTA, NUM_PRIORITA` | urgenza |
| `Stato` | `APERTO, IN_LAVORAZIONE, CHIUSO, NUM_STATI` | fase del ticket |
| `Ticket` | `numero, pc, priorita, stato` | guasto |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `ticket` | `Ticket[]` | 8 | Ticket registrati |
| `n_ticket` | `int` | — | Ticket usati |
| `nuovo` | `Stato` | — | Stato richiesto dal comando |
| `lettera` | `char` | — | B, M o A |

| Funzione | Compito |
|----------|---------|
| `cambia_stato(t, nuovo)` | 1 se il cambio è permesso dalla tabella |
| `nome_stato(s), nome_priorita(p)` | Tabelle dei nomi |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Nuovo ticket

**a) Input** – `N PC-14 A`; `N PC-02 X`

**b) Output** – "Ticket 4 aperto."; "Priorita' non valida."

**c) Variabili di supporto** – `n_ticket`

**d) Vincoli** – priorità B, M, A

**e) Assunzioni** – al massimo 8 ticket

**f) Algoritmo in linguaggio naturale** – il nuovo ticket parte APERTO.

### Caso d'uso 2 – Ciclo di vita

**a) Input** – `L 1`, `C 1`

**b) Output** – in lavorazione, poi chiuso

**c) Variabili di supporto** – —

**d) Vincoli** – APERTO → IN_LAVORAZIONE → CHIUSO

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – permesso[t->stato][nuovo] decide.

### Caso d'uso 3 – Cambio non permesso

**a) Input** – `C 4` su un ticket aperto

**b) Output** – "da aperto a chiuso non e' permesso."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la tabella contiene 0 per quella coppia.

### Caso d'uso 4 – Elenco

**a) Input** – `E`

**b) Output** – ALTA prima, poi media e bassa, senza i chiusi

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ciclo sulle priorità da ALTA a BASSA, dentro un ciclo sui ticket.
