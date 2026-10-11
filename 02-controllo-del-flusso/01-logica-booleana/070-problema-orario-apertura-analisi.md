# Analisi – 070-problema-orario-apertura.c

## 1. Problema

Una ferramenta è aperta dal lunedì al venerdì dalle 09:00 alle 12:30 e dalle
15:30 alle 19:30, il sabato dalle 09:00 alle 13:00 ed è chiusa la domenica.
Dati il giorno della settimana e un orario, il programma deve dire se il
negozio è aperto.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `giorno` | `int` | Giorno della settimana, da 1 (lunedì) a 7 (domenica) |
| `ore`, `minuti` | `int` | Orario letto da tastiera |
| `istante` | `int` | Orario in minuti dalla mezzanotte: `ore * 60 + minuti` |
| `dati_validi` | `int` (0/1) | Giorno, ore e minuti nei valori ammessi |
| `feriale`, `sabato` | `int` (0/1) | Tipo di giorno |
| `in_mattina`, `in_pomeriggio`, `in_mattina_sabato` | `int` (0/1) | Appartenenza alle fasce orarie |
| `aperto` | `int` (0/1) | Risultato finale |

Gli estremi delle fasce sono costanti `#define` già espresse in minuti
(es. `MATTINA_FINE` = `12 * 60 + 30`). Convertire l'orario in un solo numero
permette di confrontare "le 12:30" con un unico operatore, invece di
combinare confronti su ore e minuti.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Giorno feriale, fascia pomeridiana

**a) Input** – giorno 3, ora 15 45

**b) Output** – i valori delle condizioni e il messaggio
"Alle 15:45 del giorno 3 il negozio e' APERTO."

**c) Variabili di supporto** – `istante` = 945

**d) Vincoli** – ogni fascia è un intervallo chiuso a sinistra e aperto a
destra: `istante >= inizio && istante < fine`

**e) Assunzioni** – l'utente inserisce numeri interi

**f) Algoritmo in linguaggio naturale**
1. Leggere giorno, ore e minuti.
2. Calcolare `dati_validi`: giorno in [1, 7], ore in [0, 23], minuti in [0, 59].
3. Calcolare `istante = ore * 60 + minuti`.
4. Calcolare `feriale` (giorno in [1, 5]) e `sabato` (giorno uguale a 6).
5. Calcolare le tre fasce orarie come intervalli su `istante`.
6. Calcolare `aperto`: dati validi e (feriale e (mattina o pomeriggio)
   oppure sabato e mattina del sabato).
7. Stampare le condizioni intermedie e il messaggio finale.

### Caso d'uso 2 – Sabato pomeriggio

**a) Input** – giorno 6, ora 16 00

**b) Output** – "Alle 16:00 del giorno 6 il negozio e' CHIUSO."

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – `in_pomeriggio` è vero, ma il blocco dei giorni feriali è
falso perché `feriale` vale 0: la fascia pomeridiana non vale il sabato

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Orario esattamente sulla chiusura

**a) Input** – giorno 2, ora 12 30

**b) Output** – negozio "CHIUSO"

**c) Variabili di supporto** – `istante` = 750, uguale a `MATTINA_FINE`

**d) Vincoli** – il confronto con la fine della fascia usa `<` e non `<=`

**e) Assunzioni** – alle 12:30 il negozio ha già chiuso

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 4 – Domenica o dati non validi

**a) Input** – giorno 7 a qualsiasi ora, oppure ora 25 00

**b) Output** – "CHIUSO" per la domenica, "(dati non validi)" per l'orario
impossibile

**c) Variabili di supporto** – `dati_validi`

**d) Vincoli** – la domenica non compare nella regola: nessuno dei due
blocchi dell'OR può essere vero

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.
