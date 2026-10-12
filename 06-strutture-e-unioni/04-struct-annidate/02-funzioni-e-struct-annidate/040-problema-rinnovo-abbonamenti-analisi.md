# Analisi – 040-problema-rinnovo-abbonamenti.c

## 1. Problema

La segreteria gestisce gli abbonamenti al bus: rinnovi da 1 a 12 mesi e avvisi per gli abbonamenti scaduti o in scadenza entro 15 giorni. Le funzioni sulle date ricevono l'indirizzo di una Data, che può essere la data di oggi o la scadenza dentro un abbonamento (&ab->scadenza).

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Data` | `giorno, mese, anno` | data del calendario |
| `Abbonamento` | `numero, intestatario, linea, scadenza` | abbonamento al bus |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `elenco` | `Abbonamento[]` | 4 | Abbonamenti |
| `oggi` | `Data` | — | Data letta all'inizio |
| `numero`, `mesi` | `char[]`, `int` | 8, — | Argomenti del rinnovo |

| Funzione | Compito |
|----------|---------|
| `numero_giorno(d)` | Giorni dal 1/1/2000 |
| `giorni_tra(da, a)` | Positivo se a viene dopo da |
| `aggiungi_mesi(d, mesi)` | Modifica la Data; giorno limitato all'ultimo del mese |
| `rinnova(ab, mesi, oggi)` | Da oggi se scaduto, altrimenti dalla vecchia scadenza |
| `stampa(ab, oggi)` | Stato: scaduto, in scadenza o valido |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Avvisi

**a) Input** – oggi `20/01/2026`, `A`

**b) Output** – A-1001 in scadenza tra 11 giorni, A-1002 SCADUTO da 5 giorni, A-1004 tra 13 giorni

**c) Variabili di supporto** – —

**d) Vincoli** – preavviso di 15 giorni

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stampare gli abbonamenti con giorni_tra(&oggi, &scadenza) ≤ 15.

### Caso d'uso 2 – Rinnovo da valido

**a) Input** – `R A-1001 1`

**b) Output** – scadenza 28/02/2026

**c) Variabili di supporto** – `elenco[0].scadenza`

**d) Vincoli** – il 31 febbraio non esiste

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – aggiungi_mesi porta il mese a 2 e riduce il giorno a 28.

### Caso d'uso 3 – Rinnovo da scaduto

**a) Input** – `R A-1002 3`

**b) Output** – scadenza 20/04/2026

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la scadenza riparte da oggi: ab->scadenza = *oggi, poi tre mesi.

### Caso d'uso 4 – Errori

**a) Input** – `R A-1009 1`; `R A-1003 13`

**b) Output** – "inesistente"; "Durata non valida"

**c) Variabili di supporto** – —

**d) Vincoli** – da 1 a 12 mesi

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – rinnova restituisce 0 e non modifica nulla.
