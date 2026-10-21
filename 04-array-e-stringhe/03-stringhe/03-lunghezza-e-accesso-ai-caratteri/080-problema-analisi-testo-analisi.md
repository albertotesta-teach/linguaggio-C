# Analisi – 080-problema-analisi-testo.c

## 1. Problema

Un editor di testo minimalista deve mostrare le statistiche di un testo
inserito dall'utente: numero di caratteri totali, parole, spazi e caratteri
rimanenti rispetto a un limite massimo di 280. Le parole vengono conteggiate
rilevando le transizioni da spazio a non-spazio con una variabile di stato.

---

## 2. Analisi

### Input

| Variabile | Tipo     | Dimensione | Descrizione                                     |
|-----------|----------|------------|-------------------------------------------------|
| `testo`   | `char[]` | 283        | Testo con spazi (280 + `'\n'` + `'\0'`)         |

### Output
- Caratteri totali sul limite, parole, spazi e caratteri rimasti (o in
  eccesso);
- una barra di utilizzo di 20 celle con la percentuale;
- lo stato: "Testo nel limite consentito.", "Limite raggiunto esattamente."
  oppure "ATTENZIONE: testo troppo lungo di N caratteri.".

### Vincoli
- I caratteri totali comprendono gli spazi
- Una parola inizia con un carattere non-spazio preceduto da uno spazio o
  all'inizio del testo: la variabile di stato `precedente_era_spazio` parte
  da 1 (spazio "virtuale" iniziale)
- Più spazi consecutivi non creano parole vuote
- Si considera separatore solo lo spazio (non la tabulazione)
- Barra e percentuale usano la divisione intera
- `fgets(testo, 283, stdin)` legge al massimo 282 caratteri: se il buffer
  si riempie senza il `'\n'`, i caratteri rimasti nell'input si leggono con
  `getchar` e si contano con le stesse regole, così si misura la lunghezza
  reale del testo
- La barra ha al massimo 20 simboli anche se il testo supera il limite

### Assunzioni
- I caratteri sono a un byte

### Variabili di supporto

| Variabile               | Tipo      | Descrizione                             |
|-------------------------|-----------|-----------------------------------------|
| `num_caratteri`, `num_parole`, `num_spazi` | `int` | Contatori            |
| `precedente_era_spazio` | `int`     | 1 se il carattere precedente era spazio |
| `rimanenti`             | `int`     | `LIMITE_MAX − num_caratteri`            |
| `c`, `i`                | `char`, `int` | Carattere corrente e indice         |
| `oltre_buffer`          | `int`     | 1 se la riga non è entrata nel buffer   |
| `ch`                    | `int`     | Carattere letto con `getchar`           |
| `LIMITE_MAX`            | `#define` | 280                                     |

### Algoritmo in linguaggio naturale
1. Leggere il testo e rimuovere il `'\n'`; se il buffer è pieno senza
   `'\n'` ricordarlo in `oltre_buffer`.
2. Porre `precedente_era_spazio = 1`; per ogni carattere: contarlo; se è
   uno spazio contarlo tra gli spazi e porre lo stato a 1; altrimenti, se lo
   stato è 1, contare una nuova parola, e porre lo stato a 0.
   Se `oltre_buffer` vale 1, fare lo stesso con i caratteri letti con
   `getchar` fino a `'\n'` o EOF.
3. Calcolare i caratteri rimanenti e stampare le statistiche.
4. Stampare la barra e lo stato rispetto al limite.

---

## 3. Casi di test

Per ogni caso si inserisce il testo indicato.

### Test 1 – Testo con spazi multipli
- **Cosa si verifica:** tre spazi consecutivi non creano parole in più
- **Input:** `Domani   si parte per il mare`
- **Output atteso:**
```
  Caratteri totali  : 29 / 280
  Parole            : 6
  Spazi             : 7
  Caratteri rimasti : 251

  Utilizzo: [##..................] 10%
```
  e `Testo nel limite consentito.`

### Test 2 – Testo vuoto
- **Input:** solo Invio
- **Output atteso:** `Caratteri totali  : 0 / 280`, `Parole            : 0`

### Test 3 – Esattamente 280 caratteri
- **Input:** 280 caratteri
- **Output atteso:** `Limite raggiunto esattamente.`

### Test 4 – Testo oltre il limite e oltre il buffer
- **Cosa si verifica:** anche i caratteri che non entrano nel buffer sono contati
- **Input:** 300 lettere `a`
- **Output atteso:**
```
  Caratteri totali  : 300 / 280
  Parole            : 1
  Spazi             : 0
  Caratteri in eccesso: 20

  Utilizzo: [####################] 107%
```
  e `ATTENZIONE: testo troppo lungo di 20 caratteri.`

### Test 5 – Parole e spazi oltre il buffer
- **Cosa si verifica:** parole e spazi si contano anche nella parte letta con `getchar`
- **Input:** 300 caratteri formati ripetendo `ciao ` (60 volte)
- **Output atteso:** `Caratteri totali  : 300 / 280`, `Parole            : 60`,
  `Spazi             : 60`

### Test 6 – Un solo carattere oltre il limite
- **Cosa si verifica:** il caso limite che sta ancora nel buffer
- **Input:** 281 caratteri
- **Output atteso:** `Caratteri totali  : 281 / 280` e
  `ATTENZIONE: testo troppo lungo di 1 carattere.`
