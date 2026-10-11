# Analisi – 070-problema-consumi-condominio.c

## 1. Problema

L'amministratore di un condominio ha i consumi mensili di riscaldamento
(kWh) di 6 appartamenti da ottobre a marzo. Vuole il consumo stagionale di
ogni appartamento e la sua quota, il totale di ogni mese con il mese di
picco, gli appartamenti oltre il 120% della media e il mese di massimo
consumo di ciascuno.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `consumi` | `int[][]` | 6 × 6 | Riga = appartamento, colonna = mese |
| `interni` | `int[]` | 6 | Numero di interno, parallelo alle righe |
| `mesi` | `char[][]` | 6 × 4 | Sigla del mese, parallela alle colonne |
| `stagione` | `int[]` | 6 | Totali di riga, riusati per quote e soglia |
| `totale_condominio` | `int` | — | Totale generale |
| `max_mese`, `m_picco` | `int` | — | Colonna con il totale più alto |
| `m_max_app` | `int` | — | Mese di massimo della riga corrente |
| `media` | `double` | — | Consumo medio stagionale |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Totali e mese di picco

**a) Input** – `consumi`, `interni`, `mesi`

**b) Output** – tabella con stagione per appartamento e totali per mese;
totale 18800 kWh; "Mese di picco: Gen (4470 kWh)"

**c) Variabili di supporto** – `stagione`, `totale_mese`, `max_mese`, `m_picco`

**d) Vincoli** – il totale generale deve coincidere con la somma dei totali di colonna

**e) Assunzioni** – letture intere

**f) Algoritmo in linguaggio naturale**
1. Per ogni appartamento sommare la riga in `stagione[a]` e nel totale generale.
2. Per ogni mese sommare la colonna e aggiornare il massimo.

### Caso d'uso 2 – Quote, mese massimo e consumi elevati

**a) Input** – `consumi`, `stagione`, totale generale

**b) Output** – per ogni interno quota percentuale e mese di massimo; il 3 è
segnalato come consumo elevato

**c) Variabili di supporto** – `media`, `m_max_app`

**d) Vincoli** – il confronto con il 120% si fa in reale:
`stagione[a] * 100.0 > media * 120`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Calcolare la media stagionale per appartamento.
2. Per ogni appartamento: cercare l'indice del mese massimo nella riga,
   stampare quota e mese, segnalare se supera la soglia.
