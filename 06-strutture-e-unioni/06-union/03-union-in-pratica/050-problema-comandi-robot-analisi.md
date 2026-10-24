# Analisi – 050-problema-comandi-robot.c

## 1. Problema

Il robot del laboratorio esegue un programma scritto a righe (`MUOVI`,
`RUOTA`, `DI`). In una prima fase ogni riga diventa un `Comando`, una
union etichettata con i dati del suo tipo; le righe sbagliate si scartano.
Nella seconda fase uno `switch` sull'etichetta esegue i comandi
aggiornando posizione e orientamento.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[64]` | `MUOVI dx dy`, `RUOTA gradi`, `DI testo`; `FINE` esegue |

### Output

- `riga N scartata: "..."` per le righe non valide.
- `Esecuzione di N comandi` e una riga per comando eseguito.
- `Posizione finale (x, y), orientamento G gradi`.

### Vincoli

- `RUOTA` accetta solo multipli di 90 (anche negativi); l'orientamento
  resta tra 0 e 359 (`((d + g) % 360 + 360) % 360`).
- `DI` richiede un testo non vuoto di al massimo 31 caratteri.
- Al massimo 10 comandi: raggiunto il limite la lettura si ferma.
- Le parole chiave vanno in maiuscolo.
- Una riga più lunga del buffer viene troncata e il resto scartato. A fine
  input si esegue come con `FINE`.

### Assunzioni

- Il robot parte da (0, 0) orientato a 0 gradi.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `TipoComando` | `typedef enum { MUOVI, RUOTA, DI } TipoComando;` | Etichetta |
| `Comando` | struct con `tipo` e union anonima `{ struct { int dx; int dy; } muovi; int gradi; char testo[32]; }` | Un comando |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `programma`, `n` | `Comando[10]`, `int` | Comandi validi |
| `x`, `y`, `direzione` | `int` | Stato del robot |
| `numero_riga`, `resto` | `int` | Messaggi e righe lunghe |

| Funzione | Compito |
|----------|---------|
| `analizza(riga, c)` | Trasforma una riga in un `Comando`; 0 se non valida |

### Algoritmo in linguaggio naturale

1. Fase 1: finché non si termina e c'è posto, leggere una riga, contarla e
   analizzarla; memorizzare il comando o segnalare la riga scartata.
2. Fase 2: per ogni comando applicare con uno `switch` lo spostamento, la
   rotazione o la frase.
3. Stampare posizione e orientamento finali.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Programma con errori

- **Input:** `MUOVI 3 2`, `RUOTA 90`, `DI ciao a tutti`, `RUOTA 45`,
  `SALTA 2`, `MUOVI 1`, `RUOTA -180`, `MUOVI -1 -1`, `DI`, `FINE`
- **Valori intermedi attesi:** 90 − 180 = −90 → 270 gradi.
- **Output atteso:**
  ```
  Programma del robot (FINE per eseguire):
    riga 4 scartata: "RUOTA 45"
    riga 5 scartata: "SALTA 2"
    riga 6 scartata: "MUOVI 1"
    riga 9 scartata: "DI"

  Esecuzione di 5 comandi
    muove di (3, 2): ora in (3, 2)
    ruota di 90 gradi: ora orientato a 90 gradi
    dice: "ciao a tutti"
    ruota di -180 gradi: ora orientato a 270 gradi
    muove di (-1, -1): ora in (2, 1)
  Posizione finale (2, 1), orientamento 270 gradi
  ```
