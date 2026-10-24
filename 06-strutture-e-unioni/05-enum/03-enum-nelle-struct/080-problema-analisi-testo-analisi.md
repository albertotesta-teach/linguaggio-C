# Analisi – 080-problema-analisi-testo.c

## 1. Problema

Per le statistiche dei temi il programma legge il testo un carattere alla
volta e ricorda solo lo stato: fuori, dentro una parola o dentro un
numero. Uno `switch` sullo stato applica le regole; una parola o un
numero si contano quando iniziano, e un numero seguito da una lettera
(3B) diventa una parola. I risultati sono in una struct `Conteggi`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[120]` | Righe di testo; `FINE` su una riga termina |

### Output

- `Righe R, parole P, numeri N, segni di punteggiatura S`.

### Vincoli

- Stati: `FUORI` → lettera: `IN_PAROLA` (una parola in più); cifra:
  `IN_NUMERO` (un numero in più). `IN_PAROLA` → resta finché il carattere
  è alfanumerico. `IN_NUMERO` → lettera: diventa parola (un numero in
  meno, una parola in più); altro non cifra: `FUORI`.
- Ogni riga parte nello stato `FUORI`; anche una riga vuota è contata.
- Punteggiatura: `. , ; : ! ?`.
- Una riga più lunga di 119 caratteri si analizza troncata: il resto è
  scartato. A fine input il programma termina come con `FINE`.

### Assunzioni

- Testo senza lettere accentate (l'apostrofo separa le parole).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Stato` | `typedef enum { FUORI, IN_PAROLA, IN_NUMERO } Stato;` | Stato della lettura |
| `Conteggi` | `typedef struct { int parole; int numeri; int punteggiatura; int righe; } Conteggi;` | Risultati |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `conteggi` | `Conteggi` | Totali, aggiornati da `analizza` tramite puntatore |
| `stato` | `Stato` | Stato corrente nella riga |
| `resto` | `int` | Caratteri scartati di una riga lunga |

| Funzione | Compito |
|----------|---------|
| `analizza(riga, c)` | Applica la macchina a stati a una riga |

### Algoritmo in linguaggio naturale

1. Finché non si termina: leggere una riga (fine input → fine), scartare
   il resto se troppo lunga, togliere l'a capo; con `FINE` terminare,
   altrimenti analizzarla.
2. `analizza`: contare la riga; per ogni carattere contare la
   punteggiatura e applicare le transizioni dello stato.
3. Stampare i conteggi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Testo con numeri e sigle

- **Input:** `Ciao, siamo la 3B: oggi 25 studenti!`,
  `Il 2026 e' l'anno; 4x4 = 16.`, riga vuota, `FINE`
- **Valori intermedi attesi:** parole Ciao, siamo, la, 3B, oggi, studenti,
  Il, e, l, anno, 4x4 = 11; numeri 25, 2026, 16 = 3; punteggiatura
  `, : ! ; .` = 5.
- **Output atteso:**
  ```
  Testo (FINE su una riga per terminare):
  Righe 3, parole 11, numeri 3, segni di punteggiatura 5
  ```

### Test 2 – Riga troppo lunga

- **Input:** una riga di 200 cifre, poi fine input
- **Output atteso:** `Righe 1, parole 0, numeri 1, segni di
  punteggiatura 0` (il resto della riga non diventa una seconda riga).
