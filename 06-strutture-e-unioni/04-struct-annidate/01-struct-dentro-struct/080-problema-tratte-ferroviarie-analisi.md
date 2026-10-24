# Analisi – 080-problema-tratte-ferroviarie.c

## 1. Problema

Per la gita a Milano si cerca il collegamento che arriva prima partendo
non prima di un orario dato: una tratta diretta oppure due tratte con un
cambio, con almeno 5 minuti tra arrivo e partenza. A pari arrivo vince il
collegamento che parte più tardi (quindi il più breve). Le struct hanno
tre livelli: `orario[i].partenza.ora.ore`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `da`, `a` | `char[16]` | Stazioni di partenza e di arrivo; `FINE` termina |
| `dalle` | `Orario` | Partenza non prima di `hh:mm` |

Tratte (nel sorgente):

| Treno | Da | Partenza | A | Arrivo |
|-------|----|----------|---|--------|
| R 10301 | Alessandria | 6:50 | Pavia | 7:45 |
| R 10201 | Alessandria | 7:05 | Tortona | 7:25 |
| RV 2201 | Tortona | 7:32 | Milano | 8:30 |
| R 2405 | Pavia | 7:55 | Milano | 8:30 |
| R 10203 | Alessandria | 7:40 | Tortona | 8:00 |
| RV 2203 | Tortona | 8:10 | Milano | 9:05 |
| RV 2101 | Alessandria | 8:15 | Milano | 9:30 |

### Output

- Una o due righe `treno stazione HH:MM -> stazione HH:MM` e
  `Arrivo alle HH:MM, durata H h MM min, diretto` (o `con un cambio`).
- `Nessun collegamento da X a Y dopo le HH:MM.`
- `Richiesta non valida.`

### Vincoli

- Si considerano solo prime tratte che partono da `da` non prima di
  `dalle`; per il cambio la seconda tratta parte dalla stazione di arrivo
  della prima almeno 5 minuti dopo.
- Criterio: arrivo più presto; a pari arrivo, partenza più tardi.
- Ora 0-23, minuti 0-59. Una richiesta per riga; una richiesta non valida
  non interrompe il programma. A fine input termina.

### Assunzioni

- Tutti i viaggi si svolgono nella stessa mattina.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Orario` | `typedef struct { int ore; int minuti; } Orario;` | Un orario |
| `Fermata` | `typedef struct { char stazione[16]; Orario ora; } Fermata;` | Stazione con orario |
| `Tratta` | `typedef struct { char treno[10]; Fermata partenza; Fermata arrivo; } Tratta;` | Un treno da una fermata a un'altra |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `orario` | `Tratta[7]` | Tutte le tratte |
| `primo`, `secondo` | `int` | Indici delle tratte esaminate |
| `migliore_primo`, `migliore_secondo` | `int` | Soluzione migliore (−1 = nessuna / diretto) |
| `arrivo_migliore`, `partenza_migliore` | `int` | Minuti della soluzione migliore |

| Funzione | Compito |
|----------|---------|
| `in_minuti(o)` | Minuti da mezzanotte |
| `migliore(arrivo, partenza, arrivo_migliore, partenza_migliore)` | 1 se il nuovo collegamento è preferibile |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché non si termina:
   1. leggere partenza (con `FINE` o a fine input terminare),
      destinazione e ora;
   2. per ogni tratta che parte da `da` non prima dell'ora: se arriva a
      destinazione confrontarla come diretta; per ogni seconda tratta che
      parte dalla stazione di arrivo almeno 5 minuti dopo e arriva a
      destinazione, confrontare il collegamento con un cambio;
   3. stampare la soluzione migliore o l'assenza di collegamenti;
   4. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Ricerche da Alessandria

- **Cosa si verifica:** spareggio a pari arrivo (via Pavia 6:50 o via
  Tortona 7:05, entrambi alle 8:30), cambio, diretto, nessun
  collegamento, partenza da Tortona, richieste non valide.
- **Input:** `Alessandria Milano 6:30`, `Alessandria Milano 7:00`,
  `Alessandria Milano 7:30`, `Alessandria Milano 8:00`,
  `Alessandria Milano 8:30`, `Tortona Milano 7:30`,
  `Alessandria Genova 7:00`, `Alessandria Milano 25:00`,
  `Alessandria Milano x`, `FINE`
- **Output atteso:**
  ```
    R 10201  Alessandria 07:05 -> Tortona 07:25
    RV 2201  Tortona 07:32 -> Milano 08:30
    Arrivo alle 08:30, durata 1 h 25 min, con un cambio
    R 10201  Alessandria 07:05 -> Tortona 07:25
    RV 2201  Tortona 07:32 -> Milano 08:30
    Arrivo alle 08:30, durata 1 h 25 min, con un cambio
    R 10203  Alessandria 07:40 -> Tortona 08:00
    RV 2203  Tortona 08:10 -> Milano 09:05
    Arrivo alle 09:05, durata 1 h 25 min, con un cambio
    RV 2101  Alessandria 08:15 -> Milano 09:30
    Arrivo alle 09:30, durata 1 h 15 min, diretto
    Nessun collegamento da Alessandria a Milano dopo le 08:30.
    RV 2201  Tortona 07:32 -> Milano 08:30
    Arrivo alle 08:30, durata 0 h 58 min, diretto
    Nessun collegamento da Alessandria a Genova dopo le 07:00.
    Richiesta non valida.
    Richiesta non valida.
  ```
