# Analisi – 050-problema-ascensore.c

## 1. Problema

L'ascensore della scuola serve i piani da 0 a 3. È una macchina a stati:
`passo` fa avanzare l'ascensore di un passo con uno `switch` sullo stato
(porte aperte, porte chiuse, in salita, in discesa). Per ogni chiamata il
programma stampa i passi fino all'apertura delle porte al piano chiamato.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `chiamata` | `int` | Piano da 0 a 3; −1 termina |

### Output

- Per ogni passo: `piano P  stato`; alla fine `Arrivato in N passi.`
- `Gia' al piano P con le porte aperte.`
- `Il piano P non esiste.`, `Chiamata non valida.`

### Vincoli

- Transizioni: porte aperte → porte chiuse se la destinazione è un altro
  piano; porte chiuse → in salita, in discesa o porte aperte; in salita /
  in discesa: un piano per passo e porte aperte all'arrivo.
- Il ciclo continua finché l'ascensore non è al piano chiamato con le
  porte aperte.
- `passo` riceve `Ascensore *` e modifica piano e stato.
- Una chiamata non numerica viene scartata con il resto della riga; a fine
  input il programma termina.

### Assunzioni

- Le chiamate si servono una alla volta.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Stato` | `typedef enum { PORTE_APERTE, PORTE_CHIUSE, IN_SALITA, IN_DISCESA } Stato;` | Stato della macchina |
| `Ascensore` | `typedef struct { int piano; int destinazione; Stato stato; } Ascensore;` | L'ascensore |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `ascensore` | `Ascensore` | Piano 0, porte aperte all'inizio |
| `passi` | `int` | Passi della chiamata |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `passo(a)` | Una transizione della macchina a stati |
| `nome(s)` | Nome dello stato |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché la chiamata non è −1:
   1. leggere la chiamata (fine input → −1; testo → non valida);
   2. se il piano non esiste segnalarlo;
   3. altrimenti impostare la destinazione; se l'ascensore è già lì con le
      porte aperte dirlo; ripetere `passo` stampando ogni stato finché non
      arriva con le porte aperte; stampare i passi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Chiamate

- **Input:** `2`, `2`, `0`, `5`, `x`, `3`, `-1`
- **Output atteso:**
  ```
    piano 0  porte chiuse
    piano 0  in salita
    piano 1  in salita
    piano 2  porte aperte
    Arrivato in 4 passi.
    Gia' al piano 2 con le porte aperte.
    piano 2  porte chiuse
    piano 2  in discesa
    piano 1  in discesa
    piano 0  porte aperte
    Arrivato in 4 passi.
    Il piano 5 non esiste.
    Chiamata non valida.
    piano 0  porte chiuse
    piano 0  in salita
    piano 1  in salita
    piano 2  in salita
    piano 3  porte aperte
    Arrivato in 5 passi.
  ```
