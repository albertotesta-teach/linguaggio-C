# Analisi – 050-problema-data-di-nascita.c

## 1. Problema

Nel modulo di iscrizione la data di nascita si scrive come testo nel
formato gg/mm/aaaa. Il programma deve ricavare giorno, mese e anno,
verificare che la data esista (mesi di 30 e 31 giorni, anni bisestili),
riscriverla per esteso e calcolare l'età compiuta alla data di riferimento
(11/10/2026).

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `riga` | `char[]` | 40 | Testo inserito |
| `per_esteso` | `char[]` | 40 | Data riscritta con `snprintf` |
| `nomi_mesi` | `char[][]` | 12 × 10 | Nomi dei mesi |
| `g`, `m`, `a` | `int` | — | Valori letti da `sscanf` |
| `letti` | `int` | — | Valori convertiti da `sscanf` |
| `resto` | `char` | — | Carattere dopo la data, se presente |
| `eta` | `int` | — | Età compiuta |

| Funzione | Compito |
|----------|---------|
| `bisestile` | 1 se l'anno è bisestile |
| `giorni_del_mese` | 28, 29, 30 o 31 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Data valida

**a) Input** – `12/05/2010`

**b) Output** – "Data valida: 12 maggio 2010, età 16 anni"

**c) Variabili di supporto** – `letti` = 3, `eta`

**d) Vincoli** – l'età diminuisce di 1 se il compleanno dell'anno di riferimento non è ancora arrivato

**e) Assunzioni** – riferimento fisso 11/10/2026

**f) Algoritmo in linguaggio naturale**
1. `sscanf(riga, "%d/%d/%d%c", ...)` deve restituire 3.
2. Controllare anno, mese e giorno.
3. Comporre il testo per esteso con `snprintf` e calcolare l'età.

### Caso d'uso 2 – Formato sbagliato o testo in più

**a) Input** – `12-05-2010`; `12/05/2010 ore 8`

**b) Output** – "Formato non valido"; "Testo in più dopo la data"

**c) Variabili di supporto** – `letti` = 1; `letti` = 4

**d) Vincoli** – il `%c` finale legge il primo carattere dopo l'anno, se esiste

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `letti < 3` il formato è errato;
se `letti == 4` dopo la data c'è altro testo.

### Caso d'uso 3 – Data inesistente

**a) Input** – `29/02/2023`; `31/04/2011`; `15/13/2009`; `03/02/1850`

**b) Output** – "febbraio 2023 ha 28 giorni"; "aprile 2011 ha 30 giorni"; "Il mese 13 non esiste"; anno fuori intervallo

**c) Variabili di supporto** – `giorni_del_mese(m, a)`

**d) Vincoli** – il mese va controllato prima del giorno, perché i giorni dipendono dal mese

**e) Assunzioni** – anni ammessi da 1900 all'anno corrente

**f) Algoritmo in linguaggio naturale** – controlli in sequenza: anno, mese,
giorno tra 1 e `giorni_del_mese(m, a)`.

### Caso d'uso 4 – Anno bisestile

**a) Input** – `29/02/2024`

**b) Output** – data valida

**c) Variabili di supporto** – `bisestile(2024)` = 1

**d) Vincoli** – divisibile per 4 e non per 100, oppure divisibile per 400

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per febbraio `giorni_del_mese`
restituisce 29 se l'anno è bisestile, altrimenti 28.
