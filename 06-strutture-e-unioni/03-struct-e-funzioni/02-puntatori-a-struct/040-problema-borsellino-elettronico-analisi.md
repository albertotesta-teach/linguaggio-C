# Analisi – 040-problema-borsellino-elettronico.c

## 1. Problema

La tessera studente è un borsellino per i distributori: credito, spesa del
giorno, limite giornaliero e blocco. Il programma esegue ricariche,
acquisti, il cambio di giornata, il blocco e la stampa della tessera. Le
funzioni che modificano la tessera ricevono `Borsellino *`, quella che la
stampa `const Borsellino *`; `acquista` restituisce un codice di esito.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `R euro` ricarica, `A prezzo` acquisto, `G` nuovo giorno, `B` blocca/sblocca, `S` stampa, `Q` fine (anche minuscoli) |
| `importo` | `double` | Euro della ricarica o prezzo dell'acquisto |
| `tessera` | `Borsellino` | Stato iniziale (nel sorgente): Galli Irene, credito 4.00, speso 0, limite 3.00, non bloccata |

### Output

- La tessera all'inizio e con `S`:
  `Galli Irene: credito C, speso oggi S su L` (con `(BLOCCATA)` se serve).
- Ricarica: `Ricarica di N euro.` o `Importo non valido (da 1 a 50 euro).`
- Acquisto: `acquisto riuscito`, `credito insufficiente`,
  `limite giornaliero superato`, `tessera bloccata`, oppure
  `Prezzo non valido.`
- `Nuovo giorno: spesa azzerata.`, `Tessera bloccata.` / `Tessera
  sbloccata.`, `Importo non valido.`, `Comando sconosciuto.`

### Vincoli

- Ai campi si accede con `->` nelle funzioni che ricevono il puntatore.
- Ricarica da 1 a 50 euro.
- Controlli dell'acquisto nell'ordine: tessera bloccata (esito 3), limite
  giornaliero superato (2), credito insufficiente (1); altrimenti esito 0
  e si aggiornano credito e spesa del giorno.
- Il prezzo deve essere positivo.
- Un comando per riga (il resto viene scartato); un importo non numerico
  non interrompe il programma. A fine input il programma termina come con
  `Q`.

### Assunzioni

- Gli importi hanno al massimo due decimali.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Borsellino` | `typedef struct { char intestatario[20]; double credito; double speso_oggi; double limite_giornaliero; int bloccata; } Borsellino;` | La tessera |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `esiti` | `const char *[4]` | Messaggi indicizzati dal codice di `acquista` |
| `comando` | `char` | Comando in maiuscolo |
| `importo` | `double` | Valore letto |

| Funzione | Compito |
|----------|---------|
| `ricarica(b, euro)` | Aggiunge il credito se l'importo è ammesso; 1 se riuscita |
| `acquista(b, prezzo)` | Esegue i controlli e restituisce l'esito 0-3 |
| `nuovo_giorno(b)` | Azzera la spesa del giorno |
| `stampa(b)` | Stampa la tessera senza modificarla |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Stampare la tessera.
2. Finché il comando non è `Q`:
   1. leggere il comando (fine input → `Q`) in maiuscolo;
   2. `R`/`A`: leggere l'importo; se non è un numero segnalarlo; con `R`
      chiamare `ricarica(&tessera, importo)`; con `A`, se il prezzo è
      positivo, stampare `esiti[acquista(&tessera, importo)]`;
   3. `G`, `B`, `S`: nuovo giorno, inversione del blocco, stampa;
   4. altro diverso da `Q`: comando sconosciuto;
   5. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Giornata completa

- **Cosa si verifica:** i quattro esiti, ricariche valide e non, blocco,
  importi non validi.
- **Input:** `A 1.20`, `a 1.50`, `A 0.50`, `A 0.50`, `G`, `A 2.50`,
  `R 60`, `R 10`, `A 2.50`, `B`, `A 1`, `b`, `A x`, `A -2`, `Z`, `S`, `Q`
- **Valori intermedi attesi:** dopo due acquisti credito 1.30 e spesa
  2.70; 2.70 + 0.50 supera 3.00; nuovo giorno: 2.50 supera il credito
  1.30; dopo la ricarica 11.30 − 2.50 = 8.80.
- **Output atteso:**
  ```
    Galli Irene: credito 4.00, speso oggi 0.00 su 3.00
    acquisto riuscito
    acquisto riuscito
    limite giornaliero superato
    limite giornaliero superato
    Nuovo giorno: spesa azzerata.
    credito insufficiente
    Importo non valido (da 1 a 50 euro).
    Ricarica di 10.00 euro.
    acquisto riuscito
    Tessera bloccata.
    tessera bloccata
    Tessera sbloccata.
    Importo non valido.
    Prezzo non valido.
    Comando sconosciuto.
    Galli Irene: credito 8.80, speso oggi 2.50 su 3.00
  ```

### Test 2 – Limite raggiunto esattamente

- **Input:** `A 1.20`, `A 1.50`, `A 0.30`, `S`
- **Output atteso:** tre `acquisto riuscito` e
  `Galli Irene: credito 1.00, speso oggi 3.00 su 3.00`.
