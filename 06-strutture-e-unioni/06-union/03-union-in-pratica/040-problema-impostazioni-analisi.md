# Analisi – 040-problema-impostazioni.c

## 1. Problema

Il server del registro di classe legge un file di impostazioni chiave=valore. Una tabella dice il tipo previsto di ogni chiave; il valore si converte secondo il tipo in una union anonima. Righe vuote e commenti si ignorano; chiavi sconosciute e valori non validi si segnalano con il numero di riga.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Impostazione` | `chiave, tipo, union anonima {intero, reale, si_no, testo}` | impostazione |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `config` | `Impostazione[]` | 4 | Chiavi con tipo e valore predefinito |
| `riga` | `char[]` | 64 | Riga letta |
| `uguale` | `char *` | — | Posizione di '=' |
| `numero_riga`, `trovata` | `int` | — | Contatore e chiave trovata |

| Funzione | Compito |
|----------|---------|
| `leggi_valore(&imp, testo)` | Switch sul tipo previsto; 0 se il valore non è valido |
| `stampa(&imp)` | Switch sul tipo |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Valori validi

**a) Input** – `porta=8080`, `timeout=2.5`, `server=registro.lan`

**b) Output** – configurazione aggiornata

**c) Variabili di supporto** – `config`

**d) Vincoli** – porta 1-65535, timeout > 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – *uguale = '\0' divide la riga in chiave e valore.

### Caso d'uso 2 – Valore non valido

**a) Input** – `registro=forse`; `timeout=-1`

**b) Output** – "riga 4: valore non valido per registro"

**c) Variabili di supporto** – —

**d) Vincoli** – si/no; reale positivo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il valore precedente resta.

### Caso d'uso 3 – Errori di forma

**a) Input** – `colore=blu`; `porta 99`

**b) Output** – "chiave sconosciuta"; "manca '='"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ricerca della chiave nella tabella.

### Caso d'uso 4 – Commenti e righe vuote

**a) Input** – `# configurazione...`; riga vuota

**b) Output** – nessun messaggio

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – si ignorano ma contano nel numero di riga.
