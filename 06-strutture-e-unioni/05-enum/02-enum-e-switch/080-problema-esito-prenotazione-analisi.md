# Analisi – 080-problema-esito-prenotazione.c

## 1. Problema

Le classi prenotano l'aula magna per un'ora della settimana. prenota controlla giorno, ora, posti, ora occupata e prenotazione già fatta dalla classe, e restituisce un Esito con un valore per ogni motivo; il main stampa il messaggio con uno switch, senza conoscere le regole.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Esito` | `PRENOTATA, GIORNO_NON_VALIDO, ORA_NON_VALIDA, POSTI_INSUFFICIENTI, GIA_OCCUPATA, CLASSE_GIA_PRENOTATA` | risultato della prenotazione |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `aula` | `char[][][4]` | 5 × 6 | Classe prenotata in ogni ora, "" se libera |
| `classe`, `studenti`, `giorno`, `ora` | `char[]`, `int` | 8, — | Richiesta letta |

| Funzione | Compito |
|----------|---------|
| `prenota(aula, classe, studenti, giorno, ora)` | Controlli in ordine; registra se tutto va bene |
| `messaggio(e)` | switch su Esito |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prenotazioni

**a) Input** – `3B 24 2 3`; `4A 22 2 4`

**b) Output** – "Prenotazione registrata."

**c) Variabili di supporto** – `aula`

**d) Vincoli** – 120 posti

**e) Assunzioni** – una prenotazione per classe a settimana

**f) Algoritmo in linguaggio naturale** – strcpy della classe nella cella del giorno e dell'ora.

### Caso d'uso 2 – Ora occupata e classe già prenotata

**a) Input** – `4A 22 2 3`; `3B 25 5 1`

**b) Output** – "Ora gia' occupata..."; "La classe ha gia' una prenotazione..."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – si controlla la cella, poi tutte le celle con strcmp.

### Caso d'uso 3 – Valori non validi

**a) Input** – `5C 150 1 1`; `1A 20 6 1`; `1A 20 1 7`

**b) Output** – posti; giorno; ora non validi

**c) Variabili di supporto** – —

**d) Vincoli** – giorni 1-5, ore 1-6

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – un Esito diverso per ogni motivo.

### Caso d'uso 4 – Calendario

**a) Input** – `FINE`

**b) Output** – la griglia con 1A, 3B e 4A

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – "-" per le ore libere.
