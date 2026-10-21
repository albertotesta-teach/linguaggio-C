# Analisi – 070-problema-orario-apertura.c

## 1. Problema

Una ferramenta è aperta dal lunedì al venerdì dalle 09:00 alle 12:30 e dalle
15:30 alle 19:30, il sabato dalle 09:00 alle 13:00 ed è chiusa la domenica.
Dati il giorno della settimana e un orario, il programma deve dire se il
negozio è aperto.

## 2. Analisi

### Input

| Variabile       | Tipo  | Significato                                          |
|-----------------|-------|------------------------------------------------------|
| `giorno`        | `int` | Giorno della settimana, da 1 (lunedì) a 7 (domenica) |
| `ore`, `minuti` | `int` | Orario letto da tastiera                             |

### Output
I valori (0/1) delle condizioni intermedie e il messaggio finale
"Alle hh:mm del giorno g il negozio e' APERTO/CHIUSO", oppure l'indicazione
"(dati non validi)".

### Vincoli
- Dati validi: giorno in [1, 7], ore in [0, 23], minuti in [0, 59]
- Ogni fascia oraria è un intervallo chiuso a sinistra e aperto a destra:
  `istante >= inizio && istante < fine`
- La fascia pomeridiana vale solo nei giorni feriali, la fascia del sabato
  solo il sabato
- La domenica non compare nella regola: nessuno dei due blocchi dell'OR
  può essere vero

### Assunzioni
- L'utente inserisce numeri interi
- All'orario esatto di chiusura il negozio ha già chiuso

### Variabili di supporto

| Variabile                                          | Tipo        | Significato                                        |
|----------------------------------------------------|-------------|----------------------------------------------------|
| `istante`                                          | `int`       | Orario in minuti dalla mezzanotte: `ore * 60 + minuti` |
| `dati_validi`                                      | `int` (0/1) | Giorno, ore e minuti nei valori ammessi            |
| `feriale`, `sabato`                                | `int` (0/1) | Tipo di giorno                                     |
| `in_mattina`, `in_pomeriggio`, `in_mattina_sabato` | `int` (0/1) | Appartenenza alle fasce orarie                     |
| `aperto`                                           | `int` (0/1) | Risultato finale                                   |

Gli estremi delle fasce sono costanti `#define` già espresse in minuti
(es. `MATTINA_FINE` = `12 * 60 + 30`). Convertire l'orario in un solo numero
permette di confrontare "le 12:30" con un unico operatore, invece di
combinare confronti su ore e minuti.

### Algoritmo in linguaggio naturale
1. Leggere giorno, ore e minuti.
2. Calcolare `dati_validi`: giorno in [1, 7], ore in [0, 23], minuti in [0, 59].
3. Calcolare `istante = ore * 60 + minuti`.
4. Calcolare `feriale` (giorno in [1, 5]) e `sabato` (giorno uguale a 6).
5. Calcolare le tre fasce orarie come intervalli su `istante`.
6. Calcolare `aperto`: dati validi e (feriale e (mattina o pomeriggio)
   oppure sabato e mattina del sabato).
7. Stampare le condizioni intermedie e il messaggio finale.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Giorno feriale, fascia pomeridiana
- **Input:** giorno 3, ora 15 45
- **Valori intermedi attesi:** `istante` = 945; feriale = 1; in_pomeriggio = 1
- **Output atteso:** "Alle 15:45 del giorno 3 il negozio e' APERTO."

### Test 2 – Sabato pomeriggio
- **Cosa si verifica:** `in_pomeriggio` è vero, ma il blocco dei giorni
  feriali è falso perché `feriale` vale 0
- **Input:** giorno 6, ora 16 00
- **Output atteso:** "Alle 16:00 del giorno 6 il negozio e' CHIUSO."

### Test 3 – Orario esattamente sulla chiusura
- **Cosa si verifica:** il confronto con la fine della fascia usa `<` e non `<=`
- **Input:** giorno 2, ora 12 30
- **Valori intermedi attesi:** `istante` = 750, uguale a `MATTINA_FINE`
- **Output atteso:** negozio "CHIUSO"

### Test 4 – Domenica
- **Input:** giorno 7, a qualsiasi ora (es. 10 00)
- **Output atteso:** negozio "CHIUSO"

### Test 5 – Orario non valido
- **Cosa si verifica:** il ruolo di `dati_validi` nella regola
- **Input:** per esempio giorno 2, ora 25 00
- **Output atteso:** "(dati non validi)"
