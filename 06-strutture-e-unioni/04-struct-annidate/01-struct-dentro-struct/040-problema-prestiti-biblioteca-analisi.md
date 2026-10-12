# Analisi – 040-problema-prestiti-biblioteca.c

## 1. Problema

La biblioteca scolastica registra per ogni prestito il libro, lo studente e tre date: inizio, scadenza e restituzione (anno zero se il libro non è tornato). Il programma legge la data di oggi, la controlla e stampa lo stato di ogni prestito: restituito (con l'eventuale ritardo), in corso con i giorni mancanti, oppure in ritardo con la multa di 0.20 euro al giorno, al massimo 5 euro.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Data` | `giorno, mese, anno` | data del calendario |
| `Prestito` | `titolo, studente, inizio, scadenza, restituzione` | prestito con tre Data |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `prestiti` | `Prestito[]` | 5 | Prestiti registrati |
| `oggi` | `Data` | — | Data letta |
| `giorni` | `int` | — | Differenza in giorni tra due date |

| Funzione | Compito |
|----------|---------|
| `bisestile(anno)` | 1 se l'anno è bisestile |
| `giorni_nel_mese(mese, anno)` | Giorni del mese, febbraio compreso |
| `data_valida(d)` | Data esistente dal 2000 in poi |
| `numero_giorno(d)` | Giorni trascorsi dal 1/1/2000 |
| `multa(giorni)` | 0.20 euro al giorno, al massimo 5 euro |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ritardi e multe

**a) Input** – `18/12/2025`

**b) Output** – Fahrenheit 451: "IN RITARDO di 8 giorni, multa 1.60 euro"; La luna e i falo': multa 5.00 euro

**c) Variabili di supporto** – `giorni`

**d) Vincoli** – multa massima 5 euro

**e) Assunzioni** – la data di oggi viene dopo l'inizio dei prestiti

**f) Algoritmo in linguaggio naturale** – per ogni prestito non restituito: numero_giorno(oggi) - numero_giorno(p.scadenza).

### Caso d'uso 2 – Prestiti restituiti

**a) Input** – stessa data

**b) Output** – "restituito il 05/12 con 4 giorni di ritardo"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – si confronta p.restituzione con p.scadenza: la data di oggi non serve.

### Caso d'uso 3 – In corso

**a) Input** – `16/12/2025`

**b) Output** – Io, robot: "in corso, manca 1 giorno"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – differenza negativa: si stampano i giorni che mancano, al singolare se è uno.

### Caso d'uso 4 – Data non valida

**a) Input** – `31/02/2026`

**b) Output** – "Data non valida."

**c) Variabili di supporto** – —

**d) Vincoli** – giorno compatibile con il mese e l'anno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – data_valida usa giorni_nel_mese con gli anni bisestili.
