# Analisi – 060-problema-requisiti-concorso.c

## 1. Problema

Un concorso comunale ammette i candidati che soddisfano tre requisiti:
età tra 18 e 35 anni compresi, titolo di studio almeno pari al diploma e
superamento della prova preselettiva (almeno 60/100, oppure almeno 50/100
per i laureati). Il programma legge i dati di un candidato, verifica ogni
requisito separatamente e comunica l'esito. Dati non validi devono produrre
un esito specifico.

## 2. Analisi

### Input

| Variabile   | Tipo  | Significato                                        |
|-------------|-------|----------------------------------------------------|
| `eta`       | `int` | Età del candidato in anni                          |
| `titolo`    | `int` | Codice del titolo: 0 nessuno, 1 diploma, 2 laurea  |
| `punteggio` | `int` | Punteggio della prova, da 0 a 100                  |

### Output
Un riepilogo con l'esito ("SI'"/"NO") della validità dei dati e di ciascun
requisito, seguito dall'esito finale: "AMMESSO", "NON AMMESSO" oppure
"DATI NON VALIDI".

### Vincoli
- Dati validi: titolo in [0, 2], punteggio in [0, 100], età positiva
- Requisito età: età in [18, 35], estremi compresi
- Requisito titolo: almeno il diploma (`titolo >= DIPLOMA`)
- Requisito prova: punteggio almeno 60, oppure titolo uguale a laurea e
  punteggio almeno 50
- L'ammissione è l'AND di tutte le condizioni: basta un requisito falso
  per rendere falso l'esito, e gli altri requisiti veri non lo compensano

### Assunzioni
- L'utente inserisce numeri interi
- Il titolo è codificato con un numero perché le stringhe non sono ancora
  disponibili; i codici sono ordinati, quindi "almeno il diploma" si
  esprime con `>=`

### Variabili di supporto

| Variabile          | Tipo        | Significato                                 |
|--------------------|-------------|---------------------------------------------|
| `dati_validi`      | `int` (0/1) | Vero se tutti i dati sono nei valori ammessi |
| `requisito_eta`    | `int` (0/1) | Età nell'intervallo richiesto               |
| `requisito_titolo` | `int` (0/1) | Almeno il diploma                           |
| `requisito_prova`  | `int` (0/1) | Prova superata in uno dei due modi          |
| `ammesso`          | `int` (0/1) | Tutti i requisiti veri e dati validi        |

Costanti `#define`: `ETA_MIN`, `ETA_MAX`, `PUNTEGGIO_MIN`, `PUNTEGGIO_MIN_LAU`
e i codici `NESSUN_TITOLO`, `DIPLOMA`, `LAUREA`. Se il bando cambia si
modificano solo le costanti.

### Algoritmo in linguaggio naturale
1. Leggere età, titolo e punteggio.
2. Calcolare `dati_validi`: titolo in [0, 2], punteggio in [0, 100], età positiva.
3. Calcolare `requisito_eta`: età in [18, 35].
4. Calcolare `requisito_titolo`: titolo almeno pari a `DIPLOMA`.
5. Calcolare `requisito_prova`: punteggio almeno 60, oppure titolo uguale a
   `LAUREA` e punteggio almeno 50.
6. Calcolare `ammesso` come AND di `dati_validi` e dei tre requisiti.
7. Stampare il riepilogo e l'esito, scelto con due operatori ternari
   annidati: prima si valuta `dati_validi`, poi `ammesso`.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Candidato con tutti i requisiti
- **Input:** età 28, titolo 1 (diploma), punteggio 75
- **Output atteso:** riepilogo con quattro "SI'" ed esito "AMMESSO"

### Test 2 – Laureato con punteggio tra 50 e 59
- **Cosa si verifica:** il secondo blocco dell'OR del requisito prova;
  il primo (`punteggio >= 60`) è falso, il secondo
  (`titolo == LAUREA && punteggio >= 50`) è vero
- **Input:** età 28, titolo 2 (laurea), punteggio 55
- **Output atteso:** prova superata ed esito "AMMESSO"

### Test 3 – Candidato fuori età
- **Cosa si verifica:** un solo requisito falso rende falso l'esito
- **Input:** età 40, titolo 1, punteggio 75
- **Output atteso:** requisito età "NO" ed esito "NON AMMESSO"

### Test 4 – Dati non validi
- **Cosa si verifica:** il primo ternario seleziona il messaggio
  "DATI NON VALIDI"
- **Input:** per esempio titolo 5, oppure punteggio 120
- **Output atteso:** "Dati inseriti validi: NO" ed esito "DATI NON VALIDI"
