# Analisi – 080-problema-livelli-di-log.c

## 1. Problema

Il server del laboratorio scrive messaggi di livello diverso. Il livello è un enum ordinato dal meno al più grave, quindi due livelli si confrontano con >=. Il programma legge la soglia, stampa i messaggi con livello almeno pari alla soglia e conta i messaggi di ogni livello.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Livello` | `DEBUG, INFO, AVVISO, ERRORE, NUM_LIVELLI` | gravità del messaggio |
| `Messaggio` | `ora, livello, testo` | riga del registro |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `registro` | `Messaggio[]` | 8 | Messaggi della mattina |
| `nomi` | `const char *[]` | NUM_LIVELLI | Etichette dei livelli |
| `conteggi` | `int[]` | NUM_LIVELLI | Messaggi per livello |
| `soglia`, `mostrati` | `int` | — | Soglia letta e messaggi stampati |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Filtro

**a) Input** – `2`

**b) Output** – i 4 messaggi AVVISO ed ERRORE; "Mostrati 4 messaggi su 8"

**c) Variabili di supporto** – `mostrati`

**d) Vincoli** – livello >= soglia

**e) Assunzioni** – le costanti sono in ordine di gravità

**f) Algoritmo in linguaggio naturale** – per ogni messaggio aggiornare il conteggio e stamparlo se registro[i].livello >= soglia.

### Caso d'uso 2 – Conteggi

**a) Input** – stesso input

**b) Output** – DEBUG 1, INFO 3, AVVISO 2, ERRORE 2

**c) Variabili di supporto** – `conteggi`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – conteggi[registro[i].livello]++: il livello è l'indice.

### Caso d'uso 3 – Soglia non valida

**a) Input** – `7`

**b) Output** – "Soglia non valida."

**c) Variabili di supporto** – —

**d) Vincoli** – da DEBUG a ERRORE

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllo prima di ogni confronto.
