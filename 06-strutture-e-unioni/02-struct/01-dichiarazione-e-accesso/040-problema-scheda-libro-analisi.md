# Analisi – 040-problema-scheda-libro.c

## 1. Problema

La biblioteca apre la scheda di un libro (titolo, autore, anno, copie
possedute, copie in prestito) e registra prestiti e restituzioni. Un
prestito è possibile solo se c'è una copia disponibile, una restituzione
solo se c'è una copia in prestito. Alla fine il programma stampa quanti
prestiti sono stati registrati nella sessione. La scheda è una variabile
di tipo struct `Libro`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `P` prestito, `R` restituzione, `S` scheda, `Q` fine (anche minuscoli) |
| `libro` | `Libro` | Scheda iniziale (nel sorgente): "Il sentiero dei nidi di ragno", Italo Calvino, 1947, 3 copie, 1 in prestito |

### Output

- `Scheda aperta: <titolo>`.
- Per ogni comando: `Prestito registrato. Copie disponibili: N`,
  `Nessuna copia disponibile.`, `Restituzione registrata. Copie
  disponibili: N`, `Nessuna copia risulta in prestito.`, la scheda
  completa, oppure `Comando sconosciuto.`
- Alla fine: `Prestiti registrati in questa sessione: N`.

### Vincoli

- I campi si raggiungono con l'operatore punto (`libro.copie`).
- Copie disponibili = `copie - in_prestito`, sempre tra 0 e `copie`.
- Si legge un comando per riga: il resto della riga viene scartato.
- A fine input il programma termina come con `Q`.

### Assunzioni

- La scheda iniziale è coerente (`in_prestito` ≤ `copie`).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Libro` | `typedef struct { char titolo[40]; char autore[30]; int anno; int copie; int in_prestito; } Libro;` | Scheda di un libro |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `libro` | `Libro` | La scheda aperta |
| `comando` | `char` | Comando letto, convertito in maiuscolo |
| `prestiti_oggi` | `int` | Prestiti della sessione |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Stampare il titolo della scheda aperta.
2. Finché il comando non è `Q`:
   1. leggere il comando (fine input → `Q`), scartare il resto della riga
      e convertirlo in maiuscolo;
   2. `P`: se ci sono copie disponibili aumentare `in_prestito` e i
      prestiti della sessione, altrimenti segnalarlo;
   3. `R`: se ci sono copie in prestito diminuire `in_prestito`,
      altrimenti segnalarlo;
   4. `S`: stampare la scheda;
   5. altro diverso da `Q`: comando sconosciuto.
3. Stampare i prestiti della sessione.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Sessione completa

- **Cosa si verifica:** prestiti fino all'esaurimento delle copie,
  restituzioni fino a nessuna copia in prestito, minuscole, comandi errati
  e parole intere.
- **Input:** `S`, `P`, `p`, `P`, `R`, `r`, `R`, `X`, `prestito`, `S`, `Q`
- **Output atteso:**
  ```
  Scheda aperta: Il sentiero dei nidi di ragno
    Titolo:      Il sentiero dei nidi di ragno
    Autore:      Italo Calvino (1947)
    Copie:       3, in prestito 1, disponibili 2
    Prestito registrato. Copie disponibili: 1
    Prestito registrato. Copie disponibili: 0
    Nessuna copia disponibile.
    Restituzione registrata. Copie disponibili: 1
    Restituzione registrata. Copie disponibili: 2
    Restituzione registrata. Copie disponibili: 3
    Comando sconosciuto.
    Prestito registrato. Copie disponibili: 2
    Titolo:      Il sentiero dei nidi di ragno
    Autore:      Italo Calvino (1947)
    Copie:       3, in prestito 1, disponibili 2
  Prestiti registrati in questa sessione: 3
  ```
  (`prestito` vale come un solo comando `P`).

### Test 2 – Restituzione senza prestiti

- **Input:** `R`, `R`, `Q`
- **Output atteso:** `Restituzione registrata. Copie disponibili: 3`, poi
  `Nessuna copia risulta in prestito.`; `Prestiti registrati in questa
  sessione: 0`.

### Test 3 – Fine input

- **Input:** `P`, poi fine input.
- **Output atteso:** `Prestiti registrati in questa sessione: 1`.
