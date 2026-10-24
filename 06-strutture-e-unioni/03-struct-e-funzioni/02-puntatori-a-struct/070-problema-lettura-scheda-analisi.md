# Analisi – 070-problema-lettura-scheda.c

## 1. Problema

Il bibliotecario inserisce un nuovo libro. `leggi_libro` riempie la struct
`Libro` del chiamante tramite il puntatore e restituisce 1 solo se tutti i
campi sono validi, compreso il codice ISBN a 13 cifre con la cifra di
controllo. Si hanno al massimo tre tentativi.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| titolo | riga di testo | Non vuoto, al massimo 39 caratteri |
| autore | riga di testo | Non vuoto, al massimo 29 caratteri |
| anno e pagine | riga di testo | Due interi: anno 1450-2026, pagine 1-5000 |
| ISBN | riga di testo | 13 cifre con la cifra di controllo corretta |

### Output

- `--- Tentativo N ---` e le domande.
- Al primo campo non valido: `Titolo e autore non possono essere vuoti o
  troppo lunghi.`, `Anno (1450-2026) o pagine (1-5000) non validi.` oppure
  `ISBN non valido.`, e si passa al tentativo successivo.
- `Scheda inserita:` con il libro, oppure
  `Inserimento annullato dopo 3 tentativi.`

### Vincoli

- `leggi_libro(Libro *l)` scrive nei campi con `->`; `stampa` riceve
  `const Libro *`.
- La lettura di un tentativo si ferma al primo campo non valido (gli altri
  non vengono chiesti).
- ISBN-13: somma delle cifre con pesi alternati 1 e 3, multipla di 10.
- Le righe si leggono con `fgets`; una riga più lunga del buffer viene
  scartata per intero (e il campo è non valido). A fine input ogni campo è
  non valido.

### Assunzioni

- L'anno massimo 2026 è l'anno in corso.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Libro` | `typedef struct { char titolo[40]; char autore[30]; int anno; int pagine; char isbn[14]; } Libro;` | La scheda del libro |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `nuovo` | `Libro` | Scheda riempita da `leggi_libro` |
| `tentativo`, `valido` | `int` | Controllo dei tentativi |
| `riga` | `char[80]` | Riga con anno e pagine, analizzata con `sscanf` |

| Funzione | Compito |
|----------|---------|
| `leggi_libro(l)` | Legge e controlla i campi; 1 se tutti validi |
| `leggi_testo(domanda, dest, dimensione)` | Legge una riga non vuota che stia in `dest` |
| `isbn_valido(isbn)` | Controlla cifre, lunghezza e cifra di controllo |
| `stampa(l)` | Stampa la scheda |

### Algoritmo in linguaggio naturale

1. Finché la scheda non è valida e ci sono tentativi:
   1. leggere titolo e autore; se uno non è valido segnalarlo;
   2. altrimenti leggere anno e pagine e controllarli;
   3. altrimenti leggere l'ISBN e controllarlo.
2. Se valida stampare la scheda, altrimenti l'annullamento.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – ISBN corretto al terzo tentativo

- **Cosa si verifica:** cifra di controllo errata, carattere non numerico,
  ISBN corretto.
- **Input:** tre volte `Il barone rampante`, `Italo Calvino`, `1957 320`
  seguiti rispettivamente da `9788804668170`, `978880466817X`,
  `9788804668176`
- **Valori intermedi attesi:** per 9788804668176 la somma pesata è 150,
  multipla di 10; per 9788804668170 è 144.
- **Output atteso:**
  ```
  --- Tentativo 1 ---
  Titolo: Autore: Anno e pagine: ISBN (13 cifre):   ISBN non valido.
  --- Tentativo 2 ---
  Titolo: Autore: Anno e pagine: ISBN (13 cifre):   ISBN non valido.
  --- Tentativo 3 ---
  Titolo: Autore: Anno e pagine: ISBN (13 cifre): 
  Scheda inserita:
    Il barone rampante, Italo Calvino (1957), 320 pagine, ISBN 9788804668176
  ```

### Test 2 – Tre tentativi falliti

- **Cosa si verifica:** titolo troppo lungo (scartato per intero), anno
  fuori intervallo, titolo vuoto.
- **Input:** un titolo di 100 caratteri; `Il barone rampante`,
  `Italo Calvino`, `1300 320`; riga vuota
- **Output atteso:**
  ```
  --- Tentativo 1 ---
  Titolo:   Titolo e autore non possono essere vuoti o troppo lunghi.
  --- Tentativo 2 ---
  Titolo: Autore: Anno e pagine:   Anno (1450-2026) o pagine (1-5000) non validi.
  --- Tentativo 3 ---
  Titolo:   Titolo e autore non possono essere vuoti o troppo lunghi.

  Inserimento annullato dopo 3 tentativi.
  ```
