# Analisi – 070-problema-visite-museo.c

## 1. Problema

Il museo civico ha una sola guida: le visite delle classi nello stesso
giorno non possono sovrapporsi. Il programma legge le richieste (classe,
docente, data, ora di inizio, durata), controlla durata, orario di
apertura e sovrapposizioni, registra le visite accettate e alla fine
stampa il calendario. La struct `Visita` contiene una `Data` e un
`Orario`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| richiesta | una riga | `classe docente gg/mm/aaaa hh:mm durata`; `FINE` termina |
| visite iniziali | nel sorgente | 3B Galli 12/3/2026 9:30 (90 min); 1A Ferri 12/3/2026 14:00 (60 min) |

### Output

- Per ogni richiesta: `Prenotata: <classe> con <docente>, fine alle
  HH:MM.`, oppure `Durata non ammessa (da 30 a 180 minuti).`,
  `Fuori dall'orario del museo (9:00-17:00).`,
  `Sovrapposta alla visita della X (HH:MM, N min).`,
  `Calendario pieno.`, `Classe X non valida.`, `Richiesta non valida.`
- Alla fine il calendario con tutte le visite in ordine di inserimento.

### Vincoli

- Durata da 30 a 180 minuti; la visita deve iniziare dalle 9:00 e finire
  entro le 17:00.
- Due visite dello stesso giorno si sovrappongono se
  inizio₁ < fine₂ e inizio₂ < fine₁ (una visita può iniziare quando
  l'altra finisce).
- Ordine dei controlli: durata, orario, sovrapposizione, posti.
- Al massimo 8 visite; la classe ha al massimo 3 caratteri.
- Mese 1-12, giorno 1-31, minuti 0-59.
- Una richiesta per riga: il resto viene scartato e una richiesta non
  valida non interrompe l'inserimento. A fine input il programma termina.

### Assunzioni

- La data non viene controllata rispetto ai giorni effettivi del mese.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Data` | `typedef struct { int giorno; int mese; int anno; } Data;` | Giorno della visita |
| `Orario` | `typedef struct { int ore; int minuti; } Orario;` | Ora di inizio |
| `Visita` | `typedef struct { char classe[4]; char docente[16]; Data giorno; Orario inizio; int durata; } Visita;` | Una visita con data e orario annidati |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `visite`, `n_visite` | `Visita[8]`, `int` | Calendario |
| `nuova` | `Visita` | Richiesta letta |
| `parola` | `char[8]` | Classe o `FINE` |
| `inizio`, `fine`, `altro_inizio`, `altra_fine` | `int` | Minuti da mezzanotte |
| `conflitto` | `int` | Visita sovrapposta (−1 = nessuna) |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché non si termina:
   1. leggere la classe; con `FINE` o a fine input terminare;
   2. leggere docente, data, ora e durata; se mancano o sono fuori
      intervallo, richiesta non valida;
   3. se la classe è troppo lunga segnalarla;
   4. altrimenti calcolare inizio e fine, cercare una visita dello stesso
      giorno sovrapposta, fare i controlli nell'ordine e, se tutto va
      bene, aggiungere la visita;
   5. scartare il resto della riga.
2. Stampare il calendario.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Richieste di prenotazione

- **Cosa si verifica:** ogni controllo e la visita che inizia quando
  l'altra finisce.
- **Input:**
  `2C Bassi 12/3/2026 10:30 60`, `4A Riva 12/3/2026 11:00 60`,
  `5B Testa 12/3/2026 16:30 60`, `2A Conte 12/3/2026 9:00 20`,
  `1C Leone 13/3/2026 9:00 120`, `3A Gatti 12/3/2026 abc`,
  `3A Gatti 12/13/2026 10:00 60`, `QUARTA Neri 14/3/2026 10:00 60`,
  `2B Mori 12/3/2026 15:00 120`, `FINE`
- **Output atteso:**
  ```
    Sovrapposta alla visita della 3B (09:30, 90 min).
    Prenotata: 4A con Riva, fine alle 12:00.
    Fuori dall'orario del museo (9:00-17:00).
    Durata non ammessa (da 30 a 180 minuti).
    Prenotata: 1C con Leone, fine alle 11:00.
    Richiesta non valida.
    Richiesta non valida.
    Classe QUARTA non valida.
    Prenotata: 2B con Mori, fine alle 17:00.

  Calendario delle visite
    12/03/2026  09:30   90 min  3B  Galli
    12/03/2026  14:00   60 min  1A  Ferri
    12/03/2026  11:00   60 min  4A  Riva
    13/03/2026  09:00  120 min  1C  Leone
    12/03/2026  15:00  120 min  2B  Mori
  ```
