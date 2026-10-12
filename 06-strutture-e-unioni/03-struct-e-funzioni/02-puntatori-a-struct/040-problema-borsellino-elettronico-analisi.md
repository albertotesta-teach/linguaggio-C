# Analisi – 040-problema-borsellino-elettronico.c

## 1. Problema

La tessera studente è un borsellino per i distributori: credito, spesa del giorno, limite giornaliero e blocco. Le funzioni che modificano la tessera ricevono Borsellino *, quella che la stampa const Borsellino *. acquista restituisce un codice di esito.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Borsellino` | `intestatario, credito, speso_oggi, limite_giornaliero, bloccata` | tessera dei distributori |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `tessera` | `Borsellino` | — | Borsellino dello studente |
| `esiti` | `const char *[]` | 4 | Messaggi per i codici di acquista |
| `comando`, `importo` | `char`, `double` | — | Comando letto |

| Funzione | Compito |
|----------|---------|
| `ricarica(b, euro)` | 0 se l'importo non è tra 1 e 50 euro |
| `acquista(b, prezzo)` | 0 riuscito, 1 credito, 2 limite, 3 bloccata |
| `nuovo_giorno(b)` | Azzera la spesa del giorno |
| `stampa(b)` | Riceve const Borsellino * |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Acquisti

**a) Input** – `A 1.20`, `A 1.50`, `A 0.80`

**b) Output** – riuscito, riuscito, "limite giornaliero superato"

**c) Variabili di supporto** – `tessera.speso_oggi`

**d) Vincoli** – limite 3 euro al giorno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – acquista controlla blocco, limite e credito in quest'ordine.

### Caso d'uso 2 – Credito

**a) Input** – `G`, poi `A 2.50`

**b) Output** – "credito insufficiente"

**c) Variabili di supporto** – `tessera.credito`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – dopo G la spesa è a zero, ma il credito resta 1.30.

### Caso d'uso 3 – Blocco

**a) Input** – `B`, `A 0.50`

**b) Output** – "tessera bloccata"

**c) Variabili di supporto** – `tessera.bloccata`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il main modifica il campo direttamente; la funzione lo legge tramite il puntatore.
