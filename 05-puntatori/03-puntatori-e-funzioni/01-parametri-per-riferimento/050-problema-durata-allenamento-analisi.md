# Analisi – 050-problema-durata-allenamento.c

## 1. Problema

Durante un allenamento in pista l'allenatore inserisce il tempo di ogni
giro (minuti:secondi). Il programma mostra dopo ogni giro la durata totale
in ore, minuti e secondi, segnala quando un giro è il più veloce finora e
alla fine stampa numero di giri, durata e giro migliore. `0:00` termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `m`, `s` | `int` | Tempo del giro nel formato `mm:ss`; `0:00` per finire |

### Output

- Dopo ogni giro valido: `totale h:mm:ss`, con `nuovo giro migliore` se è
  il più veloce finora.
- `Tempo non valido.` per un tempo negativo, con secondi oltre 59 o non nel
  formato `mm:ss`.
- Alla fine, se c'è almeno un giro: numero di giri, durata totale e giro
  migliore.

### Vincoli

- Ore, minuti e secondi della durata sono parametri di ingresso e uscita:
  `aggiungi_giro` e `normalizza` li ricevono per indirizzo e li modificano.
- `normalizza` riporta i secondi oltre 59 nei minuti e i minuti oltre 59
  nelle ore.
- `aggiorna_migliore` modifica `*migliore` (in secondi, -1 = nessun giro)
  solo se il giro è più veloce, e restituisce 1 in quel caso; a parità di
  tempo il record non cambia.
- Un tempo non valido non viene contato.
- Un input non nel formato `mm:ss` si scarta (resto della riga); a fine
  input il programma termina come con `0:00`.

### Assunzioni

- I minuti di un giro possono superare 59 (es. `75:00`); vengono riportati
  nelle ore della durata totale.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `ore`, `minuti`, `secondi` | `int` | Durata totale, aggiornata dalle funzioni |
| `migliore` | `int` | Giro più veloce in secondi, -1 se nessuno |
| `giri` | `int` | Giri validi inseriti |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `aggiungi_giro(&ore, &minuti, &secondi, m, s)` | Somma un giro alla durata |
| `normalizza(&ore, &minuti, &secondi)` | Riporta secondi e minuti oltre 59 |
| `aggiorna_migliore(&migliore, m, s)` | Aggiorna il giro migliore; 1 se cambiato |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché il tempo non è `0:00`:
   1. leggere `m:s` (a fine input usare `0:00`; se non è nel formato
      scartare la riga e considerarlo non valido);
   2. se non valido segnalarlo;
   3. altrimenti, se non è `0:00`: contare il giro, aggiungerlo alla durata,
      stampare il totale e, se `aggiorna_migliore` restituisce 1, segnalare
      il nuovo giro migliore.
2. Se c'è almeno un giro stampare il riepilogo.

## 3. Casi di test

Nell'output i tempi inseriti non compaiono (input da pipe).

### Test 1 – Allenamento con tempi non validi

- **Input:** `5:42`, `5:18`, `6:05`, `5:61`, `x`, `5:09`, `0:00`
- **Valori intermedi attesi:** dopo il secondo giro 42 + 18 = 60 secondi
  → riporto: 0:11:00.
- **Output atteso** (risposte nell'ordine):
  ```
    totale 0:05:42   nuovo giro migliore
    totale 0:11:00   nuovo giro migliore
    totale 0:17:05
    Tempo non valido.
    Tempo non valido.
    totale 0:22:14   nuovo giro migliore

  4 giri in 0:22:14, giro migliore 5:09
  ```

### Test 2 – Riporto nelle ore

- **Input:** `59:30`, `1:00`, poi fine dell'input
- **Output atteso:**
  ```
    totale 0:59:30   nuovo giro migliore
    totale 1:00:30   nuovo giro migliore

  2 giri in 1:00:30, giro migliore 1:00
  ```

### Test 3 – Nessun giro

- **Input:** `0:00`
- **Output atteso:** nessun riepilogo.
