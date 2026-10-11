# Analisi – 060-problema-conto-attivo.c

## 1. Problema

Il tesoriere dell'associazione dei genitori gestisce quattro salvadanai
(gita, biblioteca, sport, festa). Seleziona un salvadanaio con il comando
`N k` e poi registra versamenti (`V importo`) e prelievi (`P importo`) su
quello selezionato. Il prelievo è rifiutato se il saldo non basta. Alla
fine viene stampato il riepilogo, indicando l'ultimo salvadanaio selezionato.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `char[][]` | 4 × 12 | Nomi dei salvadanai |
| `saldi` | `int[]` | 4 | Saldi in euro (parallelo) |
| `attivo` | `int *` | — | Indirizzo dell'elemento selezionato di `saldi`, `NULL` all'inizio |
| `indice_attivo` | `int` | — | Indice selezionato, per stampare il nome |
| `riga`, `comando`, `valore`, `letti` | — | — | Lettura del comando con `fgets` e `sscanf` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Operazione senza selezione

**a) Input** – `V 50`

**b) Output** – "Nessun salvadanaio selezionato."

**c) Variabili di supporto** – `attivo` = `NULL`

**d) Vincoli** – mai dereferenziare `NULL`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllare `attivo` prima di ogni operazione.

### Caso d'uso 2 – Selezione e versamento

**a) Input** – `N 2`, `V 30`

**b) Output** – "Selezionato Biblioteca (saldo 120 euro)"; "nuovo saldo 150 euro"

**c) Variabili di supporto** – `attivo = &saldi[1]`

**d) Vincoli** – l'utente conta da 1, l'array da 0

**e) Assunzioni** – importi interi in euro

**f) Algoritmo in linguaggio naturale** – con `N k` valido assegnare
`attivo = &saldi[k - 1]`; con `V` sommare a `*attivo`.

### Caso d'uso 3 – Prelievo

**a) Input** – `P 200` con saldo 150; `P 20` con saldo 75

**b) Output** – "Saldo insufficiente"; "nuovo saldo 55 euro"

**c) Variabili di supporto** – `*attivo`

**d) Vincoli** – il saldo non può diventare negativo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se l'importo supera `*attivo`
rifiutare, altrimenti sottrarre.

### Caso d'uso 4 – Riepilogo

**a) Input** – `F`

**b) Output** – i quattro saldi, con "<- ultimo selezionato" accanto a Festa

**c) Variabili di supporto** – `k`

**d) Vincoli** – il salvadanaio selezionato si riconosce con `&saldi[k] == attivo`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scorrere i saldi confrontando
l'indirizzo di ogni elemento con `attivo`.
