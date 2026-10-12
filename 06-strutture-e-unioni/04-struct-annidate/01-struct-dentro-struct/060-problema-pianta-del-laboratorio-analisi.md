# Analisi – 060-problema-pianta-del-laboratorio.c

## 1. Problema

Sulla pianta del laboratorio di fisica ogni banco è un rettangolo dato da due Punto, gli angoli opposti. Il programma calcola area, centro e distanza dalla porta di ogni banco e sceglie il banco più vicino alla porta per il kit di primo soccorso; poi dice su quale banco cade ogni postazione letta, oppure se è nel corridoio.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Punto` | `x, y` | punto sulla pianta |
| `Banco` | `nome, basso_sinistra, alto_destra` | banco come due Punto |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `banchi` | `Banco[]` | 4 | Banchi sulla pianta |
| `porta`, `postazione`, `centro` | `Punto` | — | Punti usati nei calcoli |
| `distanza`, `minima` | `double` | — | Distanza dalla porta e minimo trovato |
| `vicino`, `trovato` | `int` | — | Indici del banco più vicino e del banco trovato |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Banchi e porta

**a) Input** – nessun input

**b) Output** – tabella con area 19200 cm2 per banco; "Kit di primo soccorso sul banco B3."

**c) Variabili di supporto** – `centro`, `distanza`

**d) Vincoli** – coordinate in centimetri

**e) Assunzioni** – banchi con i lati paralleli alle pareti

**f) Algoritmo in linguaggio naturale** – area = (alto_destra.x - basso_sinistra.x) × (alto_destra.y - basso_sinistra.y); distanza con sqrt.

### Caso d'uso 2 – Postazione su un banco

**a) Input** – `120 150`

**b) Output** – "(120, 150): banco B1"

**c) Variabili di supporto** – `trovato`

**d) Vincoli** – bordo compreso

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cercare il primo banco con basso_sinistra ≤ punto ≤ alto_destra su x e su y.

### Caso d'uso 3 – Corridoio

**a) Input** – `400 150`

**b) Output** – "(400, 150): corridoio"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessun banco contiene il punto.

### Caso d'uso 4 – Fine

**a) Input** – `-1 -1`

**b) Output** – il programma termina

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la coppia -1 -1 chiude il ciclo.
