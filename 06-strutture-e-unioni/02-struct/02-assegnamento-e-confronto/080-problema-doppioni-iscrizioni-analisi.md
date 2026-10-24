# Analisi – 080-problema-doppioni-iscrizioni.c

## 1. Problema

Il modulo online dei corsi pomeridiani a volte invia due volte la stessa
iscrizione. Ogni iscrizione si confronta con la precedente: se è identica
è un doppione, se cambia solo il giorno è una correzione, altrimenti è una
nuova iscrizione. `FINE` termina e il programma stampa i conteggi. Le
iscrizioni sono struct `Iscrizione`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `corrente` | `Iscrizione` | Cognome, corso e giorno (1-5) sulla stessa riga; `FINE` termina |

### Output

- Per ogni riga: `Nuova iscrizione: cognome, corso, giorno.`,
  `Doppione scartato.`, `Correzione: cognome passa da g1 a g2.` oppure
  `Iscrizione non valida.`
- Alla fine: `Iscrizioni valide: N, doppioni scartati: D, correzioni: C`.

### Vincoli

- Le struct non si confrontano con `==`: si confrontano i campi
  (`strcmp` per le stringhe).
- Doppione: cognome, corso e giorno uguali alla precedente; correzione:
  cognome e corso uguali, giorno diverso.
- Solo le iscrizioni nuove e le correzioni diventano la nuova
  "precedente" (assegnamento tra struct).
- Il giorno si stampa con l'abbreviazione (`lun` ... `ven`).
- Un'iscrizione per riga: il resto della riga viene scartato; una riga non
  valida non interrompe l'inserimento. A fine input il programma termina.

### Assunzioni

- Il confronto è solo con l'iscrizione immediatamente precedente: un
  doppione non consecutivo viene contato come nuova iscrizione.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Iscrizione` | `typedef struct { char cognome[20]; char corso[16]; int giorno; } Iscrizione;` | Un'iscrizione inviata dal modulo |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `precedente` | `Iscrizione` | Ultima iscrizione accettata, inizialmente vuota |
| `giorni` | `const char *[6]` | Abbreviazioni, indice 1-5 |
| `stessa_persona_corso` | `int` | Cognome e corso coincidono |
| `letti` | `int` | Valore restituito da `scanf` |
| `nuove`, `doppioni`, `correzioni` | `int` | Contatori |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché non si termina:
   1. leggere il cognome; con `FINE` o a fine input terminare;
   2. leggere corso e giorno e scartare il resto della riga;
   3. se mancano o il giorno non è tra 1 e 5, segnalare l'iscrizione non
      valida;
   4. altrimenti confrontare con la precedente: doppione, correzione o
      nuova; nei due ultimi casi `precedente = corrente`.
2. Stampare i conteggi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Sequenza completa

- **Cosa si verifica:** i tre esiti, le righe non valide e il doppione non
  consecutivo.
- **Input:** `Rossi corsoA 2`, `Rossi teatro 2`, `Rossi teatro 2`,
  `Rossi teatro 4`, `Bianchi coro 9`, `Bianchi coro x`, `Bianchi coro 1`,
  `Rossi teatro 4`, `FINE`
- **Output atteso:**
  ```
    Nuova iscrizione: Rossi, corsoA, mar.
    Nuova iscrizione: Rossi, teatro, mar.
    Doppione scartato.
    Correzione: Rossi passa da mar a gio.
    Iscrizione non valida.
    Iscrizione non valida.
    Nuova iscrizione: Bianchi, coro, lun.
    Nuova iscrizione: Rossi, teatro, gio.
  Iscrizioni valide: 4, doppioni scartati: 1, correzioni: 1
  ```

### Test 2 – Riga incompleta a fine input

- **Input:** `Rossi teatro`, poi fine input.
- **Output atteso:** `Iscrizione non valida.` e
  `Iscrizioni valide: 0, doppioni scartati: 0, correzioni: 0`.
