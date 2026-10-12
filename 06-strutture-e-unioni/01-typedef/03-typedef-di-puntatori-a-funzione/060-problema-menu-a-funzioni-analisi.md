# Analisi – 060-problema-menu-a-funzioni.c

## 1. Problema

Il totem della mensa gestisce il credito della tessera di uno studente, in centesimi. Il menu ha quattro voci (ricarica, paga il pasto, paga la merenda, mostra il saldo) e 0 per uscire. Ogni voce è una funzione con lo stesso prototipo, chiamata attraverso una tabella.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Azione` | `typedef void (*Azione)(int *credito);` | funzione di una voce del menu |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `voci` | `const char *[]` | 4 | Testo delle voci |
| `azioni` | `Azione[]` | 4 | Funzioni del menu |
| `credito` | `int` | — | Credito in centesimi |
| `scelta` | `int` | — | Voce scelta |

| Funzione | Compito |
|----------|---------|
| `ricarica(credito)` | Legge un importo da 5 a 50 euro e lo aggiunge |
| `paga_pasto, paga_merenda` | Pagano 5.20 e 1.50 euro tramite paga |
| `mostra_saldo(credito)` | Stampa il credito |
| `paga(credito, importo, cosa)` | Scala l'importo se il credito basta |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Voce del menu

**a) Input** – `4`

**b) Output** – "Saldo: 8.30 euro"

**c) Variabili di supporto** – `credito`

**d) Vincoli** – voce tra 1 e 4

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – chiamare azioni[scelta - 1](&credito).

### Caso d'uso 2 – Credito insufficiente

**a) Input** – `2` con 3.10 euro

**b) Output** – "Credito insufficiente per pasto: servono 5.20 euro."

**c) Variabili di supporto** – —

**d) Vincoli** – il credito non diventa mai negativo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – paga confronta credito e importo prima di scalare.

### Caso d'uso 3 – Ricarica

**a) Input** – `1`, poi `20`; `1`, poi `100`

**b) Output** – "Ricarica di 20 euro eseguita."; "Importo non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – importo da 5 a 50 euro

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la funzione legge l'importo e modifica *credito.
