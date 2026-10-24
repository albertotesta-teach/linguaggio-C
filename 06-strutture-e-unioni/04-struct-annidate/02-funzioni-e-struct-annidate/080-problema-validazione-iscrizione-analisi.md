# Analisi – 080-problema-validazione-iscrizione.c

## 1. Problema

La segreteria inserisce le iscrizioni al primo anno. `leggi_iscrizione`
riempie la struct `Iscrizione` del chiamante e delega ogni parte a una
funzione che riceve solo l'indirizzo di quella parte (`&s->nascita`,
`&s->residenza`); restituisce 0 se tutto è corretto oppure il numero della
parte sbagliata, che il `main` usa come indice di una tabella di
messaggi. Si hanno 3 tentativi.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| nome e cognome | riga di testo | Non vuoto, al massimo 23 caratteri |
| data di nascita | riga `gg/mm/aaaa` | Anno da 2011 a 2013, data esistente |
| via, CAP, comune | tre righe | Non vuote; CAP di 5 cifre |

### Output

- `--- Tentativo N ---`, le domande e, in caso di errore,
  `Errore nella parte: nome.` / `data di nascita.` / `indirizzo.`
- `Iscrizione registrata:` con i dati, oppure
  `Iscrizione non registrata.`

### Vincoli

- Codici di esito: 0 corretto, 1 nome, 2 data, 3 indirizzo; la tabella
  `parti` traduce il codice in messaggio.
- Il nome si controlla prima della data, la data prima dell'indirizzo: al
  primo errore il tentativo finisce.
- L'indirizzo legge sempre le tre righe e poi le controlla.
- Anno bisestile: divisibile per 4 (sufficiente per 2011-2013).
- Le righe si leggono con `fgets`; di una riga più lunga del buffer si
  scarta il resto. A fine input ogni risposta è non valida.

### Assunzioni

- Gli iscritti al primo anno sono nati tra il 2011 e il 2013.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Data` | `typedef struct { int giorno; int mese; int anno; } Data;` | Data di nascita |
| `Indirizzo` | `typedef struct { char via[28]; char cap[6]; char comune[16]; } Indirizzo;` | Residenza |
| `Iscrizione` | `typedef struct { char nome[24]; Data nascita; Indirizzo residenza; } Iscrizione;` | Iscrizione completa |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `parti` | `const char *[4]` | Messaggi indicizzati dall'esito |
| `nuova` | `Iscrizione` | Struct riempita da `leggi_iscrizione` |
| `tentativo`, `esito` | `int` | Controllo dei tentativi |

| Funzione | Compito |
|----------|---------|
| `leggi_testo(domanda, dest, dimensione)` | Legge una riga non vuota che stia in `dest` |
| `leggi_data(d)` | Legge e controlla la data |
| `leggi_indirizzo(i)` | Legge e controlla le tre righe dell'indirizzo |
| `leggi_iscrizione(s)` | Riempie l'iscrizione e restituisce l'esito |
| `stampa(s)` | Stampa l'iscrizione |
| `scarta_resto(riga)` | Scarta il resto di una riga troppo lunga |

### Algoritmo in linguaggio naturale

1. Finché l'esito non è 0 e ci sono tentativi:
   1. chiamare `leggi_iscrizione(&nuova)`;
   2. se l'esito non è 0 stampare `parti[esito]`.
2. Stampare l'iscrizione o il mancato inserimento.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Registrazione al terzo tentativo

- **Cosa si verifica:** 29 febbraio in un anno non bisestile e in uno
  bisestile, CAP con lettere.
- **Input:** `Anna Bianchi`, `29/2/2011`; `Anna Bianchi`, `29/2/2012`,
  `via Roma 1`, `151AB`, `Alessandria`; `Anna Bianchi`, `29/2/2012`,
  `via Roma 1`, `15121`, `Alessandria`
- **Output atteso:** `Errore nella parte: data di nascita.`, poi
  `Errore nella parte: indirizzo.`, poi
  ```
  Iscrizione registrata:
    Anna Bianchi, nato/a il 29/02/2012
    via Roma 1, 15121 Alessandria
  ```

### Test 2 – Tre tentativi falliti

- **Cosa si verifica:** nome troppo lungo (il resto della riga non diventa
  la risposta successiva), anno fuori intervallo, nome vuoto.
- **Input:** un nome di 50 caratteri; `Anna Bianchi`, `1/1/2010`; riga
  vuota
- **Output atteso:** `Errore nella parte: nome.`,
  `Errore nella parte: data di nascita.`, `Errore nella parte: nome.` e
  `Iscrizione non registrata.`
