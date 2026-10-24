# Analisi – 070-problema-registro-eventi.c

## 1. Problema

Il sistema di sicurezza della scuola registra porte, sensori di
temperatura e badge, ognuno con i suoi dati in una `union` anonima
dentro la struct `Evento`. Il programma filtra gli eventi per tipo
(scritto come parola) e trova le anomalie con una regola diversa per ogni
tipo.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `T tipo` filtro, `A` anomalie, `Q` fine (anche minuscoli) |
| `parola` | `char[12]` | `PORTA`, `SENSORE` o `BADGE` (in maiuscolo) |
| registro | nel sorgente | 8 eventi della giornata |

### Output

- `T`: gli eventi del tipo, oppure
  `Tipo sconosciuto: PORTA, SENSORE o BADGE.`, `Manca il tipo.`
- `A`: gli eventi anomali e `Anomalie: N`.
- `Comando sconosciuto.`

### Vincoli

- Anomalie: porta aperta fuori dall'orario 7:00-19:00 (19:00 escluso);
  sensore oltre 30 gradi; badge senza titolare.
- `TIPO_NON_VALIDO` sta dopo `NUM_TIPI` e indica una parola non trovata.
- `anomalo` e `stampa` sono `switch` sul tipo e leggono solo il membro
  corrispondente della union.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Orario` | `typedef struct { int ore; int minuti; } Orario;` | Ora dell'evento |
| `TipoEvento` | `typedef enum { PORTA, SENSORE, BADGE, NUM_TIPI, TIPO_NON_VALIDO } TipoEvento;` | Etichetta |
| `Evento` | struct con `ora`, `tipo` e union anonima di `porta`, `sensore`, `badge` | Un evento |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `registro` | `Evento[8]` | Eventi |
| `tipo` | `TipoEvento` | Filtro |
| `trovati` | `int` | Anomalie |

| Funzione | Compito |
|----------|---------|
| `tipo_da_testo(parola)` | Costante del tipo, o `TIPO_NON_VALIDO` |
| `anomalo(e)` | Regola del tipo |
| `stampa(e)` | Riga dell'evento |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`: leggere il comando in maiuscolo; con `T`
   convertire la parola e stampare gli eventi di quel tipo; con `A`
   stampare e contare gli eventi anomali; scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Filtri e anomalie

- **Input:** `T PORTA`, `t BADGE`, `T SENSORE`, `T porta`, `A`, `X`, `Q`
- **Output atteso:**
  ```
    06:40  porta ingresso     aperta
    18:30  porta palestra     chiusa
    21:10  porta magazzino    aperta
    06:42  badge 1047         Ferri (bidello)
    07:55  badge 2210         prof. Galli
    14:05  badge 9999         NON REGISTRATO
    10:15  sensore lab-chimica 24.5 gradi
    13:30  sensore server     31.2 gradi
    Tipo sconosciuto: PORTA, SENSORE o BADGE.
    06:40  porta ingresso     aperta
    13:30  sensore server     31.2 gradi
    14:05  badge 9999         NON REGISTRATO
    21:10  porta magazzino    aperta
    Anomalie: 4
    Comando sconosciuto.
  ```
  (la palestra alle 18:30 è chiusa: nessuna anomalia).
