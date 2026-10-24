# Analisi – 060-problema-scheda-studente.c

## 1. Problema

La segreteria inserisce uno studente per riga (cognome, nome, classe e tre
voti). Per ogni riga il programma alloca una struct `Studente` con
`malloc`, la fa riempire da `leggi_studente`, che riceve l'indirizzo del
blocco, stampa la scheda con media ed esito e libera la struct prima della
riga successiva.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| riga | testo | `cognome nome classe voto voto voto`; `FINE` termina |

### Output

- Per ogni riga valida una scheda incorniciata con i voti di italiano,
  matematica, inglese, la media e l'esito (`promosso`,
  `1 insufficienza`, `N insufficienze`).
- `Riga non valida: scheda non creata.`
- Alla fine: `Schede stampate: S, righe scartate: R`.
- `Memoria insufficiente.` se `malloc` fallisce.

### Vincoli

- Un blocco `malloc(sizeof *s)` per ogni riga, liberato con `free` prima
  della successiva: in memoria c'è sempre al massimo una scheda.
- Voti da 1 a 10; classe al massimo 3 caratteri; il resto della riga
  viene scartato.
- Insufficienza: voto minore di 6.
- A fine input il programma termina come con `FINE`.

### Assunzioni

- Cognome e nome sono una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Studente` | `typedef struct { char cognome[20]; char nome[20]; char classe[4]; double voti[3]; } Studente;` | La scheda |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `s` | `Studente *` | Blocco allocato per la riga corrente |
| `esito` | `int` | 1 valida, 0 non valida, −1 fine |
| `schede`, `scartate` | `int` | Contatori |

| Funzione | Compito |
|----------|---------|
| `leggi_studente(s)` | Riempie la struct puntata e controlla i dati |
| `stampa_scheda(s)` | Stampa la scheda con media ed esito |

### Algoritmo in linguaggio naturale

1. Finché non si termina: allocare una struct (se fallisce terminare);
   leggere la riga; se valida stampare la scheda, se non valida
   segnalarla; liberare la struct.
2. Stampare i contatori.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Schede e righe scartate

- **Input:** `Rossi Elena 3B 7 8 6.5`, `Bianchi Luca 3B 5 6 4`,
  `Verdi Anna 3B 5.5 7 8`, `Neri Paolo 3B 7 11 6`,
  `Gialli Sara QUARTA 6 6 6`, `Blu Ugo 3B sette 6 6`, `FINE`
- **Output atteso:**
  ```
    +--------------------------------+
    | Rossi      Elena      3B       |
    |   italiano       7.0           |
    |   matematica     8.0           |
    |   inglese        6.5           |
    |   media         7.17           |
    |   esito: promosso              |
    +--------------------------------+
    +--------------------------------+
    | Bianchi    Luca       3B       |
    |   italiano       5.0           |
    |   matematica     6.0           |
    |   inglese        4.0           |
    |   media         5.00           |
    |   esito: 2 insufficienze       |
    +--------------------------------+
    +--------------------------------+
    | Verdi      Anna       3B       |
    |   italiano       5.5           |
    |   matematica     7.0           |
    |   inglese        8.0           |
    |   media         6.83           |
    |   esito: 1 insufficienza       |
    +--------------------------------+
    Riga non valida: scheda non creata.
    Riga non valida: scheda non creata.
    Riga non valida: scheda non creata.

  Schede stampate: 3, righe scartate: 3
  ```
