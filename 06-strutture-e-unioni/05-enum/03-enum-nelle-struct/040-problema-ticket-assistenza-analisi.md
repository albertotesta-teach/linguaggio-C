# Analisi – 040-problema-ticket-assistenza.c

## 1. Problema

Il tecnico del laboratorio registra i guasti come ticket con due campi
`enum`, priorità e stato. I cambi di stato permessi sono in una tabella
`permesso[da][a]`; `cambia_stato` applica il cambio solo se la tabella lo
consente. L'elenco mostra i ticket non chiusi dalla priorità più alta.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `N pc B/M/A` nuovo ticket, `L n` in lavorazione, `C n` chiudi, `R n` riapri, `E` elenco, `Q` fine (anche minuscoli) |
| `lettera` | `char` | Priorità bassa, media, alta (anche minuscola) |
| `numero` | `int` | Numero del ticket |
| ticket iniziali | nel sorgente | 1 PC-03 media aperto; 2 PC-11 alta in lavorazione; 3 PC-07 bassa chiuso |

### Output

- `Ticket N aperto.`, `Ticket N: <stato>`,
  `Ticket N: da <stato> a <stato> non e' permesso.`
- `Priorita' non valida.`, `Ticket N inesistente.`, `Troppi ticket.`,
  `Dati incompleti.`, `Numero non valido.`, `Comando sconosciuto.`
- `E`: i ticket non chiusi, prima quelli ad alta priorità.

### Vincoli

- Cambi permessi: aperto → in lavorazione; in lavorazione → aperto o
  chiuso; chiuso → aperto. Il passaggio a uno stesso stato non è
  permesso.
- Al massimo 8 ticket; i numeri sono progressivi.
- L'elenco scorre le priorità da `ALTA` a `BASSA` e per ognuna i ticket in
  ordine di numero.
- Un comando per riga (il resto viene scartato); i dati non validi non
  interrompono il programma. A fine input termina come con `Q`.

### Assunzioni

- Comando e argomenti stanno sulla stessa riga.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Priorita` | `typedef enum { BASSA, MEDIA, ALTA, NUM_PRIORITA } Priorita;` | Urgenza |
| `Stato` | `typedef enum { APERTO, IN_LAVORAZIONE, CHIUSO, NUM_STATI } Stato;` | Avanzamento |
| `Ticket` | `typedef struct { int numero; char pc[8]; Priorita priorita; Stato stato; } Ticket;` | Un ticket |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `ticket`, `n_ticket` | `Ticket[8]`, `int` | Ticket registrati |
| `nuovo` | `Stato` | Stato richiesto |
| `permesso` (in `cambia_stato`) | `int[3][3]` | Tabella dei cambi ammessi |

| Funzione | Compito |
|----------|---------|
| `cambia_stato(t, nuovo)` | Cambia lo stato se permesso; 1 se riuscito |
| `nome_stato(s)`, `nome_priorita(p)` | Nomi |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `N`: se c'è posto leggere pc e priorità, controllarla e aprire il
      ticket;
   3. `L`/`C`/`R`: leggere il numero, scegliere lo stato richiesto con uno
      `switch` e chiamare `cambia_stato`;
   4. `E`: stampare i ticket non chiusi per priorità decrescente;
   5. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Ciclo di vita dei ticket

- **Input:** `E`, `N PC-05 a`, `N PC-09 X`, `L 1`, `l 1`, `C 2`, `C 3`,
  `R 3`, `C 1`, `R 4`, `L 9`, `L x`, `E`, `Q`
- **Output atteso:**
  ```
    2  PC-11  ALTA   in lavorazione
    1  PC-03  media  aperto
    Ticket 4 aperto.
    Priorita' non valida.
    Ticket 1: in lavorazione
    Ticket 1: da in lavorazione a in lavorazione non e' permesso.
    Ticket 2: chiuso
    Ticket 3: da chiuso a chiuso non e' permesso.
    Ticket 3: aperto
    Ticket 1: chiuso
    Ticket 4: da aperto a aperto non e' permesso.
    Ticket 9 inesistente.
    Numero non valido.
    4  PC-05  ALTA   aperto
    3  PC-07  bassa  aperto
  ```

### Test 2 – Ticket esauriti

- **Input:** sei volte `N <pc> b`
- **Output atteso:** `Ticket 4 aperto.` ... `Ticket 8 aperto.`, poi
  `Troppi ticket.`
