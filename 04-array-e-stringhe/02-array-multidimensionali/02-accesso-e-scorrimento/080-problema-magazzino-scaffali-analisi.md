# Analisi – 080-problema-magazzino-scaffali.c

## 1. Problema

Un magazzino di ricambi ha 4 scaffali da 5 ripiani; ogni ripiano contiene un
articolo in una certa quantità. Ogni scaffale ha un codice e una propria
scorta minima. Il programma deve mostrare la situazione, elencare i ripiani
da rifornire e registrare una serie di prelievi controllandone la validità.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `quantita` | `int[][]` | 4 × 5 | Pezzi per scaffale e ripiano |
| `codici` | `char[][]` | 4 × 6 | Codice dello scaffale, parallelo alle righe |
| `scorta_minima` | `int[]` | 4 | Soglia dello scaffale, parallela alle righe |
| `totale`, `sotto_scorta`, `prelevati` | `int` | — | Accumulatori e contatori |
| `scelta_scaffale`, `scelta_ripiano`, `pezzi` | `int` | — | Dati di un prelievo |

Ogni cella si confronta con la soglia della **sua riga**:
`quantita[sc][rp] < scorta_minima[sc]`.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Situazione e ripiani da rifornire

**a) Input** – matrici e array inizializzati

**b) Output** – tabella con totali per scaffale; 5 ripiani sotto scorta

**c) Variabili di supporto** – `totale`, `sotto_scorta`

**d) Vincoli** – la soglia cambia da riga a riga

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Per ogni scaffale stampare codice, quantità, totale e scorta minima.
2. Per ogni cella: se è sotto la soglia del suo scaffale, stamparla e contarla.

### Caso d'uso 2 – Prelievo valido

**a) Input** – scaffale 2, ripiano 1, 10 pezzi

**b) Output** – "Prelievo registrato: SC-B ripiano 1, rimasti 5 (sotto scorta!)"

**c) Variabili di supporto** – `prelevati`

**d) Vincoli** – dopo il prelievo si ricontrolla la scorta minima

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Leggere lo scaffale; finché non è 0 leggere ripiano e pezzi.
2. Verificare in ordine: posizione esistente, quantità positiva, giacenza sufficiente.
3. Se tutto è valido sottrarre i pezzi, aggiornare il totale prelevato,
   segnalare se il ripiano è sceso sotto scorta.

### Caso d'uso 3 – Prelievo rifiutato

**a) Input** – scaffale 3, ripiano 4, 20 pezzi (ne restano 9)

**b) Output** – "Giacenza insufficiente: disponibili 9."

**c) Variabili di supporto** – nessuna

**d) Vincoli** – la matrice non viene modificata

**e) Assunzioni** – un prelievo parziale non è ammesso

**f) Algoritmo in linguaggio naturale** – come nel caso 2, passo 2.
