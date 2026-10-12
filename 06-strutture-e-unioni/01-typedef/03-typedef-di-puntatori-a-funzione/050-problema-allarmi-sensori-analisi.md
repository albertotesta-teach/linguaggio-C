# Analisi – 050-problema-allarmi-sensori.c

## 1. Problema

Il laboratorio di chimica ha quattro sensori (temperatura, umidità, CO2, rumore), letti ogni ora dalle 8 alle 13. Ogni sensore ha la propria regola di allarme. Il programma stampa ora per ora i sensori in allarme e, per ogni sensore, quante volte è scattato l'allarme.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Regola` | `typedef int (*Regola)(double valore);` | funzione che decide se un valore è un allarme |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `letture` | `double[][]` | 4 × 6 | Una riga per sensore, una colonna per ora |
| `regole` | `Regola[]` | 4 | Regola di allarme di ogni sensore |
| `nomi` | `const char *[]` | 4 | Nomi dei sensori |
| `in_allarme` | `int` | — | Almeno un allarme nell'ora |

| Funzione | Compito |
|----------|---------|
| `temperatura_fuori, umidita_alta, co2_alta, rumore_alto` | 1 se il valore è in allarme |
| `conta_allarmi(serie, n, r)` | Quante letture della serie fanno scattare la regola r |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ora per ora

**a) Input** – dati nel programma

**b) Output** – ore 11: umidità (72) e CO2 (1240)

**c) Variabili di supporto** – `in_allarme`

**d) Vincoli** – soglie: 16-28 gradi, 70%, 1000 ppm, 80 dB

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni ora chiamare regole[s] sulla lettura del sensore s.

### Caso d'uso 2 – Conteggio per sensore

**a) Input** – dati nel programma

**b) Output** – CO2 3 su 6, gli altri 2 su 6

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – passare la riga letture[s] e regole[s] a conta_allarmi.

### Caso d'uso 3 – Ora senza allarmi

**a) Input** – una colonna con tutti i valori nella norma

**b) Output** – "tutto regolare"

**c) Variabili di supporto** – `in_allarme`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se nessuna regola scatta si stampa il messaggio.
