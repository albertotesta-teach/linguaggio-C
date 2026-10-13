# Analisi – 070-problema-registro-eventi.c

## 1. Problema

Il sistema di sicurezza della scuola registra porte, sensori di temperatura e badge, ognuno con i suoi dati in una union anonima. Il programma filtra gli eventi per tipo (scritto come parola) e trova le anomalie con una regola diversa per ogni tipo.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Evento` | `ora, tipo, union anonima {porta, sensore, badge}` | evento registrato |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `registro` | `Evento[]` | 8 | Eventi della giornata |
| `parola` | `char[]` | 12 | Tipo cercato |
| `tipo` | `TipoEvento` | — | Tipo convertito |
| `trovati` | `int` | — | Anomalie |

| Funzione | Compito |
|----------|---------|
| `tipo_da_testo(parola)` | Tabella dei nomi; TIPO_NON_VALIDO se manca |
| `anomalo(&e)` | Porta aperta fuori orario, temperatura oltre 30, badge non registrato |
| `stampa(&e)` | Switch sul tipo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Filtro

**a) Input** – `T PORTA`; `T BADGE`

**b) Output** – le tre porte; i tre badge, uno NON REGISTRATO

**c) Variabili di supporto** – `tipo`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confronto dell'etichetta con il tipo cercato.

### Caso d'uso 2 – Anomalie

**a) Input** – `A`

**b) Output** – porta ingresso 06:40, sensore server 31.2, badge 9999, porta magazzino 21:10: 4

**c) Variabili di supporto** – `trovati`

**d) Vincoli** – orario 7:00-19:00

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – switch sul tipo con una regola per ognuno.

### Caso d'uso 3 – Tipo sconosciuto

**a) Input** – `T AUTO`

**b) Output** – "Tipo sconosciuto: PORTA, SENSORE o BADGE."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – TIPO_NON_VALIDO sta dopo NUM_TIPI.
