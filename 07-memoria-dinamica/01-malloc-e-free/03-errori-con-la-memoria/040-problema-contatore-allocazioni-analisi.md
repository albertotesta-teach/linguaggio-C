# Analisi – 040-problema-contatore-allocazioni.c

## 1. Problema

Nel progetto di gruppo nessuno sa più quali blocchi sono stati liberati. Invece di chiamare direttamente malloc e free, le varie parti del programma usano registra_malloc e registra_free, che annotano ogni blocco in un registro: indirizzo, byte, uso e stato. Un secondo free dello stesso blocco viene segnalato e non eseguito; a fine programma il rapporto mostra i blocchi che sarebbero andati persi.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Voce` | `indirizzo (void *), byte, uso[24], attivo` | un blocco annotato |
| `Registro` | `voci[20], n, byte_attivi, picco` | il registro delle allocazioni |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `registro` | `Registro` | 20 voci | Blocchi allocati, byte attivi e picco |
| `byte` | `long` | — | Dimensione richiesta (1-100000) |
| `uso` | `char[]` | 24 | A che cosa serve il blocco |
| `numero`, `esito` | `int` | — | Numero del blocco e risultato di registra_free |

| Funzione | Compito |
|----------|---------|
| `registra_malloc(r, byte, uso)` | malloc e annotazione; numero del blocco o 0 |
| `registra_free(r, numero)` | 1 liberato, 0 già liberato (doppio free evitato), -1 inesistente |
| `rapporto(r)` | Blocchi ancora attivi e byte attivi |
| `libera_tutto(r)` | registra_free di ogni blocco |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Allocazioni

**a) Input** – `A 400 elenco-studenti`, `A 2000 tabella-voti`, `A 64 nome-classe`

**b) Output** – "blocco 1: 400 byte per elenco-studenti" ...

**c) Variabili di supporto** – `r->voci`

**d) Vincoli** – al massimo 20 blocchi

**e) Assunzioni** – l'uso è una parola

**f) Algoritmo in linguaggio naturale** – malloc(byte); se riesce si annotano indirizzo, byte, uso e attivo = 1; si aggiorna il picco.

### Caso d'uso 2 – Doppio free

**a) Input** – `L 2` due volte

**b) Output** – "blocco 2 liberato", poi "blocco 2 gia' liberato: doppio free evitato"

**c) Variabili di supporto** – `attivo`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – free solo se la voce è attiva; dopo free indirizzo = NULL e attivo = 0.

### Caso d'uso 3 – Blocco inesistente

**a) Input** – `L 9`

**b) Output** – "blocco 9 inesistente"

**c) Variabili di supporto** – —

**d) Vincoli** – numeri da 1 a n

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – registra_free restituisce -1.

### Caso d'uso 4 – Rapporto finale

**a) Input** – `Q`

**b) Output** – blocchi 1, 3 e 4 ancora attivi (592 byte), "li libera il registro", picco 2464 byte

**c) Variabili di supporto** – `byte_attivi`, `picco`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – rapporto, poi libera_tutto: nessun blocco resta allocato.
