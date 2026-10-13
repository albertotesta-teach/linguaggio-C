# Analisi – 080-problema-calcolatrice-unita.c

## 1. Problema

Nel laboratorio di scienze si convertono lunghezze, masse e temperature. L'unità è una union etichettata dalla dimensione: ogni dimensione ha il suo enum di unità. Una tabella associa sigla, unità e fattore verso l'unità base; le temperature passano per i gradi Celsius.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Unita` | `dimensione, union anonima {lunghezza, massa, temperatura}` | unità di misura |
| `Voce` | `sigla, unita, fattore` | riga della tabella |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `tabella` | `Voce[]` | 12 | Sigle, unità e fattori |
| `da`, `a`, `parola` | `char[]` | 8 | Sigle e valore letti |
| `valore`, `risultato` | `double` | — | Valore e conversione |
| `i`, `j` | `int` | — | Posizioni delle due sigle |

| Funzione | Compito |
|----------|---------|
| `cerca(tabella, sigla)` | Posizione della sigla o -1 |
| `in_celsius(valore, u), da_celsius(valore, u)` | Formule delle temperature |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Lunghezze e masse

**a) Input** – `12 km in m`; `5 lb in kg`; `2 mi in km`

**b) Output** – 12000 m; 2.26796 kg; 3.21869 km

**c) Variabili di supporto** – `risultato`

**d) Vincoli** – stessa dimensione

**e) Assunzioni** – fattori della tabella

**f) Algoritmo in linguaggio naturale** – valore × fattore di partenza / fattore di arrivo.

### Caso d'uso 2 – Temperature

**a) Input** – `100 F in C`; `300 K in C`

**b) Output** – 37.7778 C; 26.85 C

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – prima in Celsius, poi nell'unità di arrivo.

### Caso d'uso 3 – Dimensioni diverse

**a) Input** – `3 m in kg`

**b) Output** – "Non si converte una lunghezza in una massa."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confronto dei campi dimensione.

### Caso d'uso 4 – Sigla sconosciuta

**a) Input** – `4 yd in m`

**b) Output** – "Unita' sconosciuta: yd"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca restituisce -1.
