# Analisi – 060-problema-requisiti-concorso.c

## 1. Problema

Un concorso comunale ammette i candidati che soddisfano tre requisiti:
età tra 18 e 35 anni compresi, titolo di studio almeno pari al diploma e
superamento della prova preselettiva (almeno 60/100, oppure almeno 50/100
per i laureati). Il programma legge i dati di un candidato, verifica ogni
requisito separatamente e comunica l'esito. Dati non validi devono produrre
un esito specifico.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `eta` | `int` | Età del candidato in anni |
| `titolo` | `int` | Codice del titolo: 0 nessuno, 1 diploma, 2 laurea |
| `punteggio` | `int` | Punteggio della prova, da 0 a 100 |
| `dati_validi` | `int` (0/1) | Vero se tutti i dati sono nei valori ammessi |
| `requisito_eta` | `int` (0/1) | Età nell'intervallo richiesto |
| `requisito_titolo` | `int` (0/1) | Almeno il diploma |
| `requisito_prova` | `int` (0/1) | Prova superata in uno dei due modi |
| `ammesso` | `int` (0/1) | Tutti i requisiti veri e dati validi |

Costanti `#define`: `ETA_MIN`, `ETA_MAX`, `PUNTEGGIO_MIN`, `PUNTEGGIO_MIN_LAU`
e i codici `NESSUN_TITOLO`, `DIPLOMA`, `LAUREA`. Se il bando cambia si
modificano solo le costanti.

Il titolo è codificato con un numero perché le stringhe non sono ancora
disponibili. I codici sono ordinati, quindi "almeno il diploma" si scrive
`titolo >= DIPLOMA`.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Candidato con tutti i requisiti

**a) Input** – età 28, titolo 1 (diploma), punteggio 75

**b) Output** – riepilogo con quattro "SI'" ed esito "AMMESSO"

**c) Variabili di supporto** – le variabili booleane dei requisiti

**d) Vincoli** – `ammesso` è l'AND di tutte le condizioni: basta un
requisito falso per rendere falso l'esito

**e) Assunzioni** – l'utente inserisce numeri interi

**f) Algoritmo in linguaggio naturale**
1. Leggere età, titolo e punteggio.
2. Calcolare `dati_validi`: titolo in [0, 2], punteggio in [0, 100], età positiva.
3. Calcolare `requisito_eta`: età in [18, 35].
4. Calcolare `requisito_titolo`: titolo almeno pari a `DIPLOMA`.
5. Calcolare `requisito_prova`: punteggio almeno 60, oppure titolo uguale a
   `LAUREA` e punteggio almeno 50.
6. Calcolare `ammesso` come AND di `dati_validi` e dei tre requisiti.
7. Stampare il riepilogo e l'esito.

### Caso d'uso 2 – Laureato con punteggio tra 50 e 59

**a) Input** – età 28, titolo 2 (laurea), punteggio 55

**b) Output** – prova superata ed esito "AMMESSO"

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – il primo blocco dell'OR (`punteggio >= 60`) è falso, ma il
secondo (`titolo == LAUREA && punteggio >= 50`) è vero

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Candidato fuori età

**a) Input** – età 40, titolo 1, punteggio 75

**b) Output** – requisito età "NO" ed esito "NON AMMESSO"

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – gli altri requisiti veri non compensano quello falso

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 4 – Dati non validi

**a) Input** – per esempio titolo 5 oppure punteggio 120

**b) Output** – "Dati inseriti validi: NO" ed esito "DATI NON VALIDI"

**c) Variabili di supporto** – `dati_validi`

**d) Vincoli** – l'esito viene scelto con due operatori ternari annidati:
prima si valuta `dati_validi`, poi `ammesso`

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1; al passo 7 il
primo ternario seleziona il messaggio "DATI NON VALIDI".
