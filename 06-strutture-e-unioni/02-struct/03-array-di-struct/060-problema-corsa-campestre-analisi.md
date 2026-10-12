# Analisi – 060-problema-corsa-campestre.c

## 1. Problema

Alla campestre corrono allievi e juniores. Il programma trova il podio di ogni categoria senza ordinare l'array: cerca tre volte il tempo minimo tra gli atleti non ancora premiati della categoria. Gli atleti ritirati (tempo 0) non entrano in classifica. Stampa anche il distacco dal primo.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Atleta` | `nome, classe, categoria, tempo` | risultato di un atleta |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `atleti` | `Atleta[]` | 10 | Risultati |
| `premiato` | `int[]` | 10 | 1 se l'atleta è già sul podio |
| `migliore` | `int` | — | Indice del più veloce trovato |
| `tempo_primo`, `arrivati` | `int` | — | Distacchi e conteggio |

| Funzione | Compito |
|----------|---------|
| `main` | Tre ricerche del minimo per categoria |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Podio

**a) Input** – dati nel programma

**b) Output** – ALLIEVI: Pellegrini, Testa (+7 s), Rinaldi (+14 s)

**c) Variabili di supporto** – `premiato`

**d) Vincoli** – solo la categoria richiesta

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni posto cercare il minimo con !premiato[i] e segnarlo.

### Caso d'uso 2 – Ritirati

**a) Input** – Serra e Riva con tempo 0

**b) Output** – non compaiono; 4 arrivati per categoria

**c) Variabili di supporto** – `arrivati`

**d) Vincoli** – tempo > 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la condizione tempo > 0 li esclude.

### Caso d'uso 3 – Categoria con meno di tre arrivati

**a) Input** – ad esempio 2 arrivati

**b) Output** – podio di due posti

**c) Variabili di supporto** – —

**d) Vincoli** – posto <= arrivati

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo del podio si ferma al numero di arrivati.
