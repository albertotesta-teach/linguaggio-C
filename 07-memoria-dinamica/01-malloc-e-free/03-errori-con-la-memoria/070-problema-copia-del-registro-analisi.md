# Analisi – 070-problema-copia-del-registro.c

## 1. Problema

Prima dello scrutinio il coordinatore prova delle modifiche ai voti su una copia del registro. Il Registro contiene un puntatore all'array dei voti: l'assegnamento tra struct copia il puntatore (copia superficiale) e le due struct condividono i voti; duplica alloca un nuovo blocco e copia i voti (copia profonda).

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Registro` | `classe[4], n, voti (double *)` | registro con i voti nello heap |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `originale`, `superficiale`, `profonda` | `Registro` | — | Registro e due copie |
| `posizioni`, `nuovi` | `int[]`, `double[]` | 10 | Modifiche da provare |
| `modifiche`, `letti` | `int` | — | Modifiche e voti inseriti |

| Funzione | Compito |
|----------|---------|
| `duplica(da, a)` | Copia profonda: nuovo blocco con gli stessi voti; 0 se manca memoria |
| `applica(r, posizioni, nuovi, quante)` | Scrive le modifiche nei voti di r |
| `stampa(titolo, r)` | Classe e voti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Copia profonda

**a) Input** – `4B 5`, voti `6 5.5 7 4 8`, modifiche `2 6`, `4 6`

**b) Output** – copia 6.0 6.0 7.0 6.0 8.0, originale invariato; blocchi con indirizzi diversi

**c) Variabili di supporto** – `profonda`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – malloc di un nuovo array, copia dei voti, modifiche sulla copia, free della copia.

### Caso d'uso 2 – Copia superficiale

**a) Input** – stesse modifiche

**b) Output** – copia e originale entrambi 6.0 6.0 7.0 6.0 8.0; stesso indirizzo

**c) Variabili di supporto** – `superficiale`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – superficiale = originale copia il puntatore: le modifiche arrivano all'originale.

### Caso d'uso 3 – Modifica non valida

**a) Input** – `9 7` con 5 voti

**b) Output** – "modifica non valida"

**c) Variabili di supporto** – —

**d) Vincoli** – posizioni da 1 a n

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la modifica non viene registrata.

### Caso d'uso 4 – Liberare una volta

**a) Input** – fine del programma

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – superficiale.voti e originale.voti sono lo stesso blocco: una sola free.
