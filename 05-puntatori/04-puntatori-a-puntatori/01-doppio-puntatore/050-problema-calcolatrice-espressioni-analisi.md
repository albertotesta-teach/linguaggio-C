# Analisi – 050-problema-calcolatrice-espressioni.c

## 1. Problema

Il tesoriere di classe scrive entrate e uscite della cassa come una sola
espressione di somme e sottrazioni (`150 + 35 - 48`). Il programma calcola
il risultato oppure mostra il punto in cui l'espressione è scritta male.
Una riga vuota termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[100]` | Espressione `numero (operatore numero)…`, letta con `fgets`; riga vuota per finire |

### Output

- `= N euro` per un'espressione corretta.
- Per un'espressione errata: l'espressione e, sotto, `^ errore qui` nella
  colonna in cui la lettura si è fermata.

### Vincoli

- Le funzioni di lettura ricevono l'indirizzo del puntatore di lettura
  (`const char **p`) e lo spostano oltre ciò che hanno letto: tutte
  avanzano lo stesso puntatore.
- `leggi_numero` legge le cifre e restituisce 1 se ne ha letta almeno una;
  `leggi_operatore` accetta solo `+` e `-`; entrambe saltano gli spazi
  iniziali.
- Il ciclo si ferma al primo errore; la posizione dell'errore è
  `p − testo`, dove la lettura si è fermata.
- `valuta` restituisce il risultato e la posizione dell'errore tramite due
  parametri di uscita.
- Una riga più lunga del buffer viene troncata e il resto si scarta; la fine
  dell'input termina come la riga vuota.

### Assunzioni

- Solo numeri interi non negativi e operatori `+` e `-`.
- Gli spazi sono il carattere spazio (non tabulazioni).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `risultato` | `int` | Valore calcolato (uscita di `valuta`) |
| `errore` | `int` | Posizione dell'errore (uscita di `valuta`) |
| `a_capo`, `c`, `continua` | `char *`, `int`, `int` | Lettura della riga |
| `p`, `valore`, `op` | `const char *`, `int`, `char` | In `valuta` |

| Funzione | Compito |
|----------|---------|
| `leggi_numero(&p, &n)` | Legge un numero e sposta `p` dopo l'ultima cifra |
| `leggi_operatore(&p, &op)` | Legge `+` o `-` e sposta `p` |
| `salta_spazi(&p)` | Sposta `p` oltre gli spazi |
| `valuta(testo, &risultato, &errore)` | 1 se l'espressione è corretta |

### Algoritmo in linguaggio naturale

1. Finché `continua`: leggere una riga (a fine input terminare), togliere il
   `'\n'` o scartare il resto della riga; se è vuota terminare, altrimenti
   valutarla e stampare il risultato o la posizione dell'errore.
2. In `valuta`: leggere il primo numero; finché la lettura è corretta e il
   testo non è finito, leggere un operatore e un numero e applicarli al
   risultato (se uno dei due manca l'espressione è errata); alla fine
   scrivere la posizione raggiunta.

## 3. Casi di test

Nell'output le espressioni inserite non compaiono (input da pipe).

### Test 1 – Espressione corretta

- **Input:** `150 + 35 - 48 + 20 - 12`
- **Output atteso:** `  = 145 euro`

### Test 2 – Errori

- **Cosa si verifica:** operatore mancante, operatore non previsto, numero
  finale mancante.
- **Input:** `150 + - 20`, `100 * 2`, `150 +`
- **Output atteso:**
  ```
    150 + - 20
          ^ errore qui
    100 * 2
        ^ errore qui
    150 +
         ^ errore qui
  ```

### Test 3 – Spazi iniziali e fine

- **Input:** `  7`, riga vuota
- **Output atteso:** `  = 7 euro`, poi il programma termina.
