# Analisi – 050-problema-campionato-calcetto.c

## 1. Problema

Nel torneo di calcetto il programma legge i risultati delle partite,
trova le due squadre con una ricerca che restituisce puntatori agli
elementi dell'array di struct `Squadra` e aggiorna punti e gol con una
funzione che riceve i due puntatori. Alla fine stampa la tabella, la
capolista e l'ultima senza ordinare l'array.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `nome_casa`, `gol_casa`, `nome_ospite`, `gol_ospite` | `char[12]`, `int`, `char[12]`, `int` | Un risultato per riga; `FINE` termina |
| squadre | nel sorgente | Fulmini, Tigri, Squali, Aquile, Lupi, tutte a zero |

### Output

- `Squadre non valide.` o `Risultato non valido.` per le righe scartate.
- La tabella: squadra, giocate, punti, gol fatti, subiti, differenza reti
  (con il segno).
- `Capolista: X (punti P)` e `Ultima: Y (punti P)`.

### Vincoli

- Vittoria 3 punti, pareggio 1, sconfitta 0.
- Le squadre devono esistere ed essere diverse (`casa != ospite`
  confronta i puntatori); i gol non negativi.
- `migliore(a, b)`: più punti o, a parità, differenza reti maggiore; a
  parità completa resta la squadra trovata prima.
- Una riga non valida viene scartata per intero senza interrompere
  l'inserimento; a fine input il programma termina come con `FINE`.

### Assunzioni

- I nomi delle squadre sono una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Squadra` | `typedef struct { char nome[12]; int giocate; int punti; int fatti; int subiti; } Squadra;` | Una squadra con le statistiche |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `torneo` | `Squadra[5]` | Array di struct |
| `casa`, `ospite` | `Squadra *` | Squadre trovate |
| `prima`, `ultima` | `int` | Indici di capolista e ultima |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `cerca(s, n, nome)` | Puntatore alla squadra, `NULL` se assente |
| `registra(casa, gol_casa, ospite, gol_ospite)` | Aggiorna giocate, gol e punti di entrambe |
| `migliore(a, b)` | 1 se `a` precede strettamente `b` |
| `stampa(s)` | Riga della tabella |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché non si termina:
   1. leggere la squadra di casa; con `FINE` o a fine input terminare;
   2. leggere gol, ospite e gol; se non validi scartare la riga e
      segnalarlo;
   3. cercare le due squadre; se mancano o coincidono segnalarlo,
      altrimenti registrare la partita.
2. Stampare la tabella aggiornando capolista e ultima con `migliore`.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Giornate del torneo

- **Cosa si verifica:** punti, differenza reti come spareggio, righe
  scartate.
- **Input:** `Fulmini 3 Tigri 1`, `Squali 2 Aquile 2`, `Lupi 0 Fulmini 2`,
  `Tigri 4 Squali 1`, `Aquile 1 Lupi 1`, `Tigri 2 Tigri 0`,
  `Orsi 1 Lupi 0`, `Squali x Lupi 1`, `Squali -1 Lupi 1`, `FINE`
- **Valori intermedi attesi:** Squali e Lupi hanno 1 punto; Squali −3,
  Lupi −2: ultima Squali.
- **Output atteso:**
  ```
    Squadre non valide.
    Squadre non valide.
    Risultato non valido.
    Risultato non valido.

    Squadra      G  Pt   GF  GS   DR
    Fulmini      2   6    5   1   +4
    Tigri        2   3    5   4   +1
    Squali       2   1    3   6   -3
    Aquile       2   2    3   3   +0
    Lupi         2   1    1   3   -2

  Capolista: Fulmini (punti 6)
  Ultima:    Squali (punti 1)
  ```

### Test 2 – Nessuna partita

- **Input:** `FINE`
- **Output atteso:** tutte le squadre a zero; capolista e ultima
  `Fulmini (punti 0)` (la prima a parità).
