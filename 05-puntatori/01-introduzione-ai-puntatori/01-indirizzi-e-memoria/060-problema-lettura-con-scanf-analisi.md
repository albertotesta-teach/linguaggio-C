# Analisi – 060-problema-lettura-con-scanf.c

## 1. Problema

Il modulo di iscrizione a un torneo di scacchi chiede età, punteggio ELO,
categoria e nickname. Il programma legge i dati con `scanf`, ripete la
richiesta quando un numero non è valido e alla fine mostra l'indirizzo in
cui `scanf` ha scritto ciascun dato, per spiegare perché `scanf` riceve
indirizzi.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `eta`, `elo` | `int` | — | Dati numerici |
| `categoria` | `char` | — | `'U'` under 18, `'A'` adulti |
| `nickname` | `char[]` | 20 | Letto con `%19s` |
| `letti` | `int` | — | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento errato |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Numero non valido

**a) Input** – `abc`, poi `150`, poi `15`

**b) Output** – due volte "Valore non valido", poi si prosegue

**c) Variabili di supporto** – `letti`

**d) Vincoli** – se `scanf` non riesce a leggere un intero (`letti != 1`) i
caratteri restano nel buffer e vanno scartati

**e) Assunzioni** – età ammessa tra 6 e 99

**f) Algoritmo in linguaggio naturale** – finché la lettura fallisce o il
valore è fuori intervallo: svuotare la riga e richiedere.

### Caso d'uso 2 – Indirizzi passati a scanf

**a) Input** – dati validi

**b) Output** – tabella con valore e indirizzo di ogni dato

**c) Variabili di supporto** – nessuna

**d) Vincoli** – per le variabili si passa `&nome`; per l'array `nickname`
basta il nome, che indica già l'indirizzo del primo elemento

**e) Assunzioni** – nickname senza spazi, al massimo 19 caratteri

**f) Algoritmo in linguaggio naturale** – stampare `&eta`, `&elo`,
`&categoria` e `&nickname[0]` con `%p`.

### Caso d'uso 3 – Coerenza tra categoria ed età

**a) Input** – età 15, categoria `A`

**b) Output** – "Attenzione: la categoria non corrisponde all'età."

**c) Variabili di supporto** – nessuna

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – segnalare se `'U'` con età ≥ 18 o
`'A'` con età < 18.
