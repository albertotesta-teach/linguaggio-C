# Analisi – 040-problema-controllo-accessi.c

## 1. Problema

All'ingresso del parcheggio della scuola una telecamera legge la targa e
il programma decide se alzare la sbarra. Una targa italiana ha il formato
AA000AA. Il programma legge una targa per riga fino a `FINE`, controlla il
formato e l'elenco delle targhe autorizzate, e alla fine conta gli
ingressi consentiti e negati. Le targhe hanno il tipo `Targa`, un array di
8 caratteri con nome.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[40]` | Targa letta con `fgets`; `FINE` termina |
| `elenco` | `const Targa[5]` | Targhe autorizzate (nel sorgente): EK301TZ, DM774PA, FH052LC, GB918RN, CX640MD |

### Output

- Per ogni riga: `Lettura non valida, ripetere.`, oppure
  `<targa>: accesso negato.`, oppure `<targa>: sbarra alzata.`
- Alla fine: `Ingressi consentiti: C, negati: N`.

### Vincoli

- `typedef char Targa[8];`: 7 caratteri più il terminatore.
- Formato AA000AA: due lettere maiuscole, tre cifre, due lettere
  maiuscole.
- La riga si copia nella `Targa` solo se è lunga esattamente 7 caratteri,
  così non si esce dai limiti dell'array.
- Una riga più lunga del buffer viene scartata per intero (il resto non
  diventa una nuova lettura).
- Le letture non valide non entrano nel conteggio.

### Assunzioni

- La telecamera fornisce le lettere in maiuscolo: una targa in minuscolo è
  una lettura non valida.
- A fine input il programma si comporta come con `FINE`.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Targa` | `typedef char Targa[LUNG_TARGA + 1];` | Una targa come stringa |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `targa` | `Targa` | Copia della riga validata |
| `a_capo` | `char *` | Posizione del `'\n'` da togliere |
| `resto` | `int` | Caratteri scartati di una riga troppo lunga |
| `fine` | `int` | Flag di uscita dal ciclo |
| `consentiti`, `negati` | `int` | Contatori |

| Funzione | Compito |
|----------|---------|
| `targa_valida(t)` | Controlla il formato AA000AA |
| `autorizzata(t, elenco, n)` | Ricerca lineare della targa nell'elenco |
| `lettera(c)`, `cifra(c)` | Classificano un carattere |

### Algoritmo in linguaggio naturale

1. Finché non si termina:
   1. leggere una riga (a fine input terminare);
   2. togliere il `'\n'`; se manca, scartare il resto della riga;
   3. se la riga è `FINE` terminare;
   4. se non ha 7 caratteri o non rispetta il formato, segnalare la
      lettura non valida;
   5. altrimenti cercarla nell'elenco: se c'è alzare la sbarra e contare
      un ingresso consentito, altrimenti contare un ingresso negato.
2. Stampare i contatori.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Targhe autorizzate, negate e non valide

- **Cosa si verifica:** le tre risposte, il controllo del formato e lo
  scarto di una riga lunga.
- **Input:** `EK301TZ`, `AB123CD`, `ek301tz`, `EK301T`, `EK3O1TZ` (lettera
  O al posto dello zero), `DM774PA` seguito da 60 `X`, `CX640MD`, `FINE`
- **Output atteso:**
  ```
    EK301TZ: sbarra alzata.
    AB123CD: accesso negato.
    Lettura non valida, ripetere.
    Lettura non valida, ripetere.
    Lettura non valida, ripetere.
    Lettura non valida, ripetere.
    CX640MD: sbarra alzata.

  Ingressi consentiti: 2, negati: 1
  ```

### Test 2 – Fine input senza FINE

- **Cosa si verifica:** la fine dell'input termina come `FINE`.
- **Input:** `EK301TZ` senza a capo finale.
- **Output atteso:** `EK301TZ: sbarra alzata.` e
  `Ingressi consentiti: 1, negati: 0`.

### Test 3 – Nessun ingresso

- **Input:** `FINE`
- **Output atteso:** `Ingressi consentiti: 0, negati: 0`.
