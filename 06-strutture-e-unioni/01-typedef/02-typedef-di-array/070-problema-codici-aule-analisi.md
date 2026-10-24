# Analisi – 070-problema-codici-aule.c

## 1. Problema

Ogni aula ha un codice di 5 caratteri nel formato EP-NN (edificio, piano,
trattino, numero su due cifre). Il programma compone i codici a partire
dai dati della segreteria e li stampa; poi, per ogni codice letto, indica
edificio, piano, numero e capienza, oppure segnala un codice non valido o
un'aula inesistente. I codici hanno il tipo `Codice`, un array di 6
caratteri con nome.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[40]` | Codice da cercare, letto con `fgets`; `FINE` termina |
| `edifici`, `piani`, `numeri`, `capienza` | array paralleli di 6 elementi | Dati delle aule (nel sorgente) |

### Output

- L'elenco dei codici composti con i posti di ogni aula.
- Per ogni codice cercato: `Edificio E, piano P, aula N: C posti.`,
  `Edificio E, piano P, aula N: aula inesistente.` oppure
  `Codice non valido.`

### Vincoli

- `typedef char Codice[6];`: 5 caratteri più il terminatore.
- Formato: lettera maiuscola, cifra, `-`, due cifre; il numero ha sempre
  due cifre (zero iniziale).
- La riga si copia nel `Codice` solo se è lunga esattamente 5 caratteri.
- Una riga più lunga del buffer viene scartata per intero.

### Assunzioni

- Piano da 0 a 9, numero da 0 a 99.
- A fine input il programma si comporta come con `FINE`.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Codice` | `typedef char Codice[6];` | Codice di un'aula come stringa |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `codici` | `Codice[6]` | Codici composti |
| `richiesto` | `Codice` | Codice letto e validato in lunghezza |
| `edificio`, `piano`, `numero` | `char`, `int`, `int` | Parti del codice letto |
| `a_capo`, `resto` | `char *`, `int` | Gestione del `'\n'` e delle righe lunghe |
| `a` | `int` | Indice di ricerca |

| Funzione | Compito |
|----------|---------|
| `componi(c, edificio, piano, numero)` | Scrive il codice nel `Codice` del chiamante |
| `scomponi(c, &edificio, &piano, &numero)` | 1 se il formato è valido, con le parti nei parametri di uscita |

### Algoritmo in linguaggio naturale

1. Comporre e stampare i codici delle sei aule.
2. Finché non si termina:
   1. leggere una riga, togliere il `'\n'` o scartare il resto della riga;
   2. con `FINE` (o a fine input) terminare;
   3. se la lunghezza non è 5 o il formato è errato, segnalare il codice
      non valido;
   4. altrimenti cercare il codice tra quelli composti e stampare le parti
      con la capienza o `aula inesistente`.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Elenco e ricerche

- **Cosa si verifica:** composizione dei codici, ricerca riuscita, codici
  errati, aula assente, riga troppo lunga.
- **Input:** `B2-07`, `B2_07`, `C0-1`, `A1-15`, `b2-07`, `A0-03` seguito da
  50 `X`, `C0-01`, `FINE`
- **Output atteso:**
  ```
  Codici delle aule:
    A0-03  (28 posti)
    A1-12  (30 posti)
    A1-14  (24 posti)
    B2-07  (26 posti)
    B2-09  (32 posti)
    C0-01  (60 posti)
    Edificio B, piano 2, aula 7: 26 posti.
    Codice non valido.
    Codice non valido.
    Edificio A, piano 1, aula 15: aula inesistente.
    Codice non valido.
    Codice non valido.
    Edificio C, piano 0, aula 1: 60 posti.
  ```
  (`b2-07` non è valido: l'edificio è una lettera maiuscola).

### Test 2 – Solo l'elenco

- **Input:** `FINE`
- **Output atteso:** l'elenco dei sei codici e nessuna ricerca.
