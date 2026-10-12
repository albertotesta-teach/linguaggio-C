# Analisi – 080-problema-carta-imbarco.c

## 1. Problema

Al gate del viaggio d'istruzione un accompagnatore controlla la carta d'imbarco di ogni studente: il volo deve essere quello della classe e l'imbarco non deve essere chiuso. Due tipi diversi descrivono il volo e la carta. Il cognome FINE termina e il programma stampa gli studenti imbarcati.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Volo` | `codice, gate, chiusura_ore, chiusura_minuti` | volo della classe |
| `CartaImbarco` | `cognome, volo, posto` | carta di uno studente |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `classe` | `Volo` | — | Volo della classe |
| `carta` | `CartaImbarco` | — | Carta dello studente |
| `ore`, `minuti` | `int` | — | Ora attuale |
| `passati` | `int` | — | Studenti imbarcati |

| Funzione | Compito |
|----------|---------|
| `main` | Controllo campo per campo tra le due struct |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Studente in regola

**a) Input** – `Rossi`, `9 10 FR1452 12A`

**b) Output** – "Rossi: passa, posto 12A."

**c) Variabili di supporto** – `passati`

**d) Vincoli** – volo uguale, ora prima della chiusura

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare carta.volo e classe.codice con strcmp e l'ora con la chiusura.

### Caso d'uso 2 – Volo sbagliato

**a) Input** – `Bianchi`, `9 12 FR1425 14C`

**b) Output** – "volo sbagliato (FR1425 invece di FR1452)"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il primo controllo è sul codice del volo.

### Caso d'uso 3 – Imbarco chiuso

**a) Input** – `Neri`, `9 36 FR1452 16B`

**b) Output** – "Neri: imbarco chiuso."

**c) Variabili di supporto** – —

**d) Vincoli** – chiusura alle 9:35

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare i minuti dalla mezzanotte.
