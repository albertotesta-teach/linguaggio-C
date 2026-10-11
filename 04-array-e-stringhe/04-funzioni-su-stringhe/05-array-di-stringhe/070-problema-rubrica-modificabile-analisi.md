# Analisi – 070-problema-rubrica-modificabile.c

## 1. Problema

Il cellulare di servizio di un'associazione sportiva ha una rubrica di al
massimo 5 contatti. Da un menu numerico si possono aggiungere contatti (non
duplicati e solo se c'è posto), cercarli per una parte del nome, cancellarli
ed elencarli.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `nomi` | `char[][]` | 5 × 24 | Nomi dei contatti |
| `numeri` | `char[][]` | 5 × 24 | Numeri di telefono (parallelo) |
| `n` | `int` | — | Contatti presenti: array a tappo |
| `scelta` | `int` | — | Voce del menu (letta con `sscanf`) |
| `nome`, `numero` | `char[]` | 40 | Dati inseriti |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Lettura con `fgets` |
| `cerca_esatto` | Indice del nome con `strcmp`, oppure -1 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Aggiunta

**a) Input** – `1`, `Medico sociale`, `340 1112223`; poi `Magazzino`; poi rubrica piena

**b) Output** – "Aggiunto."; "Magazzino è già in rubrica."; "Rubrica piena…"

**c) Variabili di supporto** – `n`

**d) Vincoli** – `n < MAX`; nome non presente; campi non vuoti

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se c'è posto e il nome non esiste,
copiare nome e numero nella riga `n` con `strcpy` e incrementare `n`.

### Caso d'uso 2 – Ricerca

**a) Input** – `2`, `M`

**b) Output** – tutti i contatti il cui nome contiene "M"

**c) Variabili di supporto** – `trovati`

**d) Vincoli** – si scorrono solo le prime `n` righe

**e) Assunzioni** – la ricerca distingue le maiuscole

**f) Algoritmo in linguaggio naturale** – stampare i contatti con
`strstr(nomi[k], testo) != NULL`.

### Caso d'uso 3 – Cancellazione

**a) Input** – `3`, `Magazzino`

**b) Output** – "Cancellato."; nell'elenco i contatti successivi salgono di una posizione

**c) Variabili di supporto** – `pos`

**d) Vincoli** – le righe si spostano dalla posizione cancellata verso la fine

**e) Assunzioni** – nomi unici

**f) Algoritmo in linguaggio naturale**
1. Trovare la posizione del nome; se -1 segnalarlo.
2. Per `k` da `pos` a `n - 2` copiare la riga `k + 1` nella riga `k` (nome e numero).
3. Decrementare `n`.

### Caso d'uso 4 – Scelta non valida e uscita

**a) Input** – `7`; `0`

**b) Output** – "Scelta non valida."; "Rubrica chiusa con 4 contatti."

**c) Variabili di supporto** – `scelta`

**d) Vincoli** – se la riga non contiene un numero `scelta` vale -1; a fine input vale 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo continua finché `scelta`
è diversa da 0.
