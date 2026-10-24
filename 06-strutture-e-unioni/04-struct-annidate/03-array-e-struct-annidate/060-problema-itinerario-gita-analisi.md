# Analisi – 060-problema-itinerario-gita.c

## 1. Problema

Il docente organizzatore scrive l'itinerario della gita tappa per tappa.
`aggiungi_tappa` accetta una tappa solo se gli orari esistono, la partenza
non viene prima dell'arrivo e l'arrivo viene dopo la partenza dalla tappa
precedente; restituisce un codice usato come indice dei messaggi. Alla
fine si stampano soste, viaggi e totali. La `Gita` contiene un array di
`Tappa`, ognuna con due `Orario`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| tappa | una riga | `luogo hh:mm hh:mm` (arrivo e partenza); `FINE` termina |

### Output

- Per ogni tappa: `<luogo>: aggiunta`, `orari non validi`,
  `arrivo prima della partenza dalla tappa precedente`,
  `itinerario pieno`; oppure `Tappa non valida.`
- Alla fine: la meta, ogni tappa con la sosta, tra due tappe il viaggio, e
  i totali di tappe, viaggio e soste in ore e minuti.

### Vincoli

- Codici: 0 aggiunta, 1 orari non validi, 2 arrivo troppo presto, 3
  itinerario pieno (al massimo 6 tappe); la tabella `messaggi` li traduce.
- Orario valido: ore 0-23, minuti 0-59; partenza non prima dell'arrivo
  (sosta 0 ammessa).
- L'arrivo deve essere strettamente dopo la partenza dalla tappa
  precedente.
- Una tappa per riga; una riga non valida non interrompe l'inserimento. A
  fine input il programma termina come con `FINE`.

### Assunzioni

- Tutta la gita si svolge in un giorno.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Orario` | `typedef struct { int ore; int minuti; } Orario;` | Un orario |
| `Tappa` | `typedef struct { char luogo[16]; Orario arrivo; Orario partenza; } Tappa;` | Una tappa |
| `Gita` | `typedef struct { char meta[16]; Tappa tappe[6]; int n_tappe; } Gita;` | L'itinerario |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `gita` | `Gita` | Meta "Cinque Terre" e tappe |
| `nuova` | `Tappa` | Tappa letta |
| `esito` | `int` | Codice di `aggiungi_tappa` |
| `messaggi` | `const char *[4]` | Messaggi indicizzati dal codice |

| Funzione | Compito |
|----------|---------|
| `in_minuti(o)` | Minuti da mezzanotte |
| `orario_valido(o)` | Controllo dell'orario |
| `aggiungi_tappa(g, t)` | Controlla e aggiunge; restituisce il codice |
| `stampa_gita(g)` | Itinerario con soste, viaggi e totali |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché non si termina:
   1. leggere il luogo; con `FINE` o a fine input terminare;
   2. leggere i due orari; se mancano segnalare la tappa non valida;
   3. altrimenti chiamare `aggiungi_tappa` e stampare `messaggi[esito]`;
   4. scartare il resto della riga.
2. Stampare l'itinerario sommando viaggi (arrivo − partenza precedente) e
   soste (partenza − arrivo).

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Itinerario completo

- **Cosa si verifica:** tutti i codici di esito, la riga non valida, i
  totali.
- **Input:** `Alessandria 6:30 6:45`, `Genova 8:30 8:50`,
  `Levanto 10:00 9:30`, `Monterosso 9:45 13:30`, `Vernazza 14:00 15:30`,
  `Riomaggiore 25:00 16:00`, `Manarola x`, `Riomaggiore 16:00 17:00`,
  `Spezia 16:30 16:40`, `Alessandria 19:30 19:30`, `Asti 20:00 20:10`,
  `FINE`
- **Valori intermedi attesi:** viaggi 105 + 55 + 30 + 30 + 150 = 370
  minuti; soste 15 + 20 + 225 + 90 + 60 + 0 = 410 minuti.
- **Output atteso:**
  ```
    Alessandria: aggiunta
    Genova: aggiunta
    Levanto: orari non validi
    Monterosso: aggiunta
    Vernazza: aggiunta
    Riomaggiore: orari non validi
    Tappa non valida.
    Riomaggiore: aggiunta
    Spezia: arrivo prima della partenza dalla tappa precedente
    Alessandria: aggiunta
    Asti: itinerario pieno

  Gita: Cinque Terre
    06:30-06:45  Alessandria    sosta 15 min
          viaggio 105 min
    08:30-08:50  Genova         sosta 20 min
          viaggio 55 min
    09:45-13:30  Monterosso     sosta 225 min
          viaggio 30 min
    14:00-15:30  Vernazza       sosta 90 min
          viaggio 30 min
    16:00-17:00  Riomaggiore    sosta 60 min
          viaggio 150 min
    19:30-19:30  Alessandria    sosta 0 min
  Tappe 6, in viaggio 6 h 10 min, in sosta 6 h 50 min
  ```

### Test 2 – Una sola tappa

- **Input:** `Asti 8:00 8:10`, poi fine input.
- **Output atteso:** `Tappe 1, in viaggio 0 h 00 min, in sosta 0 h 10 min`.
