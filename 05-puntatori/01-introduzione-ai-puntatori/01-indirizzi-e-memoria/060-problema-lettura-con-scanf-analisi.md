# Analisi – 060-problema-lettura-con-scanf.c

## 1. Problema

Il modulo di iscrizione a un torneo di scacchi chiede età, punteggio ELO,
categoria e nickname. Il programma legge i dati con `scanf`, ripete la
richiesta quando un dato non è valido e alla fine mostra l'indirizzo in
cui `scanf` ha scritto ciascun dato, per spiegare perché `scanf` riceve
indirizzi.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `eta` | `int` | Età del giocatore, tra 6 e 99 |
| `elo` | `int` | Punteggio ELO, non negativo |
| `categoria` | `char` | `U` (under 18) o `A` (adulti), anche in minuscolo |
| `nickname` | `char[20]` | Nome di gioco senza spazi |

### Output

- Per ogni dato non valido: `Valore non valido.` (età, ELO) oppure
  `Categoria non valida.`, seguito dalla nuova richiesta.
- La tabella dei dati registrati: nome, valore e indirizzo in cui `scanf`
  ha scritto il dato.
- `Attenzione: la categoria non corrisponde all'eta'.` se la categoria non
  è coerente con l'età.
- Se l'input termina prima della fine: `Input terminato: iscrizione annullata.`

### Vincoli

- A `scanf` si passa l'indirizzo della variabile (`&eta`); per l'array
  `nickname` basta il nome, che indica l'indirizzo del primo elemento.
- Si controlla il valore restituito da `scanf`: se non vale 1 il dato non è
  stato letto. Con 0 (input non del tipo giusto) i caratteri rimasti sulla
  riga si scartano con `svuota_riga` e si ripete la richiesta; con EOF
  l'iscrizione viene annullata.
- La categoria si porta in maiuscolo con `toupper` e deve essere `U` o `A`.
- Il nickname si legge con `%19s`, che non supera il buffer.

### Assunzioni

- Il nickname non contiene spazi; se supera 19 caratteri vengono tenuti i
  primi 19.
- Gli indirizzi cambiano a ogni esecuzione.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `letti` | `int` | Valore restituito da `scanf` (1, 0 o EOF) |
| `fine_input` | `int` | 1 se l'input termina prima della fine |
| `LUNG_NICK` | `#define` | 20 celle per il nickname |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti sulla riga dopo un inserimento errato |

### Algoritmo in linguaggio naturale

1. Leggere l'età; finché la lettura non è riuscita o l'età è fuori da
   6-99: se l'input è terminato porre `fine_input = 1`, altrimenti scartare
   la riga, segnalare l'errore e rileggere.
2. Se l'input non è terminato, leggere l'ELO allo stesso modo (deve essere
   ≥ 0).
3. Se l'input non è terminato, leggere la categoria, portarla in maiuscolo
   e ripetere finché non è `U` o `A`.
4. Se l'input non è terminato, leggere il nickname con `%19s`.
5. Se l'input è terminato stampare l'annullamento; altrimenti stampare la
   tabella con valori e indirizzi e, se la categoria non è coerente con
   l'età (`U` con età ≥ 18 o `A` con età < 18), l'avviso.

## 3. Casi di test

Gli indirizzi stampati cambiano a ogni esecuzione.

### Test 1 – Età non valida e categoria incoerente

- **Cosa si verifica:** un testo e un numero fuori intervallo vengono
  rifiutati; la categoria in minuscolo è accettata; l'avviso di incoerenza.
- **Input:** `abc`, `150`, `15`, `1450`, `a`, `Kasparov_99`
- **Output atteso** (indirizzi variabili):
  ```
  Eta': abc
    Valore non valido. Eta': 150
    Valore non valido. Eta': 15
  Punteggio ELO: 1450
  Categoria (U = under 18, A = adulti): a
  Nickname: Kasparov_99

  === DATI REGISTRATI ===
    Dato       Valore        scritto da scanf all'indirizzo
    eta        15            0x…
    elo        1450          0x…
    categoria  A             0x…
    nickname   Kasparov_99   0x…  (= &nickname[0])
  Attenzione: la categoria non corrisponde all'eta'.
  ```

### Test 2 – ELO negativo e categoria non valida

- **Cosa si verifica:** la validazione dell'ELO e della categoria.
- **Input:** `20`, `-5`, `1200`, `x`, `U`, `Re_Nero`
- **Output atteso** (righe significative):
  ```
  Punteggio ELO: -5
    Valore non valido. Punteggio ELO: 1200
  Categoria (U = under 18, A = adulti): x
    Categoria non valida. Categoria (U/A): U
  ```
  e alla fine `Attenzione: la categoria non corrisponde all'eta'.`

### Test 3 – Dati coerenti

- **Input:** `30`, `1800`, `A`, `Magnus`
- **Output atteso:** la tabella dei dati senza l'avviso di incoerenza.

### Test 4 – Fine dell'input

- **Cosa si verifica:** se l'input termina il programma si chiude invece di
  ripetere la richiesta all'infinito.
- **Input:** `15`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
  ```
  === ISCRIZIONE AL TORNEO ===
  Eta': Punteggio ELO: 

  Input terminato: iscrizione annullata.
  ```

### Test 5 – Nickname troppo lungo

- **Cosa si verifica:** `%19s` non supera il buffer.
- **Input:** `30`, `1800`, `A`, `Magnus_Carlsen_Fan_Club_2026`
- **Output atteso:** `nickname   Magnus_Carlsen_Fan_ 0x…` (primi 19 caratteri).
