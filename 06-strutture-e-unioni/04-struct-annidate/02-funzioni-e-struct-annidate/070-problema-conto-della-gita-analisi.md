# Analisi – 070-problema-conto-della-gita.c

## 1. Problema

Il docente organizzatore prepara il conto della gita: alcune voci sono a persona (albergo, ingressi), altre sono totali (pullman, guida). Gli accompagnatori partecipano ma non pagano; il totale si divide tra gli studenti con arrotondamento al centesimo superiore. Gli importi sono struct piccole passate per valore; la funzione sulla voce riceve const Voce * e passa v->costo alle funzioni sugli importi.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Importo` | `euro, centesimi` | somma di denaro |
| `Voce` | `descrizione, costo, a_persona` | voce di spesa con il suo Importo |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `voci` | `Voce[]` | 5 | Voci di spesa |
| `studenti`, `docenti`, `partecipanti` | `int` | — | Persone |
| `totale`, `parziale`, `quota`, `raccolto` | `Importo` | — | Importi calcolati |

| Funzione | Compito |
|----------|---------|
| `in_centesimi(a), da_centesimi(c)` | Conversioni per fare i conti in centesimi |
| `somma(a, b), per(a, volte)` | Operazioni sugli importi |
| `diviso_per_eccesso(a, parti)` | Quota arrotondata al centesimo superiore |
| `costo_voce(v, partecipanti)` | Costo moltiplicato se la voce è a persona |
| `stampa_importo(a)` | Euro e centesimi |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Conto

**a) Input** – `24 2`

**b) Output** – totale 3398.00 euro, quota 141.59 euro, avanzo 0.16 euro

**c) Variabili di supporto** – `totale`, `quota`

**d) Vincoli** – quota per eccesso

**e) Assunzioni** – prezzi della tabella

**f) Algoritmo in linguaggio naturale** – sommare costo_voce di ogni voce; quota = (totale + studenti - 1) / studenti in centesimi.

### Caso d'uso 2 – Accompagnatori insufficienti

**a) Input** – `40 2`

**b) Output** – "Servono almeno 3 accompagnatori per 40 studenti."

**c) Variabili di supporto** – —

**d) Vincoli** – uno ogni 15 studenti

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – docenti × 15 deve essere almeno studenti.

### Caso d'uso 3 – Dati non validi

**a) Input** – `8 1`

**b) Output** – "Dati non validi: da 10 a 50 studenti..."

**c) Variabili di supporto** – —

**d) Vincoli** – da 10 a 50 studenti

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessun calcolo.
