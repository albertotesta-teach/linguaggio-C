# Analisi – 040-problema-validazione-email.c

## 1. Problema

Il modulo di iscrizione a una newsletter deve rifiutare gli indirizzi email
scritti male. Il controllo, semplificato, verifica cinque regole: nessuno
spazio, una sola `@`, almeno un carattere prima della `@`, almeno un punto
dopo la `@`, punto non subito dopo la `@` né in fondo. Per ogni indirizzo
rifiutato si indica la prima regola violata; alla fine si contano gli
indirizzi accettati e rifiutati.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `email` | `char[60]` | Indirizzo letto da tastiera, uno per riga; la parola `fine` termina |

### Output

- Per ogni indirizzo: `OK: indirizzo valido` oppure
  `Rifiutato (regola N): <messaggio>` con la prima regola violata.
- Alla fine: numero di indirizzi accettati e rifiutati.

### Vincoli

- Le regole si controllano nell'ordine 1 → 5; si segnala solo la prima violata.
  1. nessuno spazio;
  2. esattamente una `@`;
  3. almeno un carattere prima della `@`;
  4. almeno un `.` dopo la `@`;
  5. il `.` non può seguire subito la `@` né essere l'ultimo carattere.
- La riga letta viene ripulita dal `'\n'`; i caratteri oltre la dimensione
  del buffer vengono scartati.
- A fine input (EOF) il programma si comporta come se fosse stato scritto `fine`.

### Assunzioni

- L'indirizzo non contiene caratteri accentati o tabulazioni.
- Il controllo è volutamente semplificato: non verifica, ad esempio, i
  caratteri ammessi nel nome o due punti consecutivi.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `messaggi` | `char[6][44]` | Testo associato a ogni esito (indice 0 = valido) |
| `esito` | `int` | 0 oppure numero della regola violata |
| `valide`, `rifiutate` | `int` | Contatori |
| `chiocciola`, `ultimo_punto`, `lung` | `int` | In `controlla_email`: posizione della `@`, dell'ultimo `.` e lunghezza |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Legge una riga, toglie il `'\n'`, scarta l'eccedenza |
| `controlla_email` | Applica le regole nell'ordine e restituisce l'esito |
| `conta_carattere` | Numero di occorrenze di un carattere |
| `prima_posizione`, `ultima_posizione` | Indice della prima/ultima occorrenza, o -1 |

### Algoritmo in linguaggio naturale

1. Leggere un indirizzo.
2. Finché l'indirizzo è diverso da `fine`:
   1. calcolare lunghezza, posizione della `@` e dell'ultimo `.`;
   2. se c'è uno spazio (`strchr`) → regola 1;
   3. altrimenti se non c'è `@` o ce n'è più di una → regola 2;
   4. altrimenti se la `@` è in posizione 0 → regola 3;
   5. altrimenti se l'ultimo `.` precede la `@` (o manca) → regola 4;
   6. altrimenti se il carattere dopo la `@` è `.` o l'ultimo `.` è in fondo → regola 5;
   7. aggiornare il contatore e stampare il messaggio; leggere l'indirizzo successivo.
3. Stampare i totali.

## 3. Casi di test

### Test 1 – Indirizzo valido

- **Cosa si verifica**: un indirizzo corretto supera tutte le regole.
- **Input**: `mario.rossi@scuola.it`, poi `fine`.
- **Valori intermedi attesi**: `chiocciola` = 11, `ultimo_punto` = 18, `esito` = 0.
- **Output atteso**:
  ```
    OK: indirizzo valido
  Indirizzi accettati: 1, rifiutati: 0
  ```

### Test 2 – Spazi e numero di `@`

- **Cosa si verifica**: regole 1 e 2 (nessuna `@` oppure due `@`).
- **Input**: `mario rossi@scuola.it`, `marioscuola.it`, `mario@@scuola.it`, `fine`.
- **Output atteso**:
  ```
    Rifiutato (regola 1): contiene spazi
    Rifiutato (regola 2): deve contenere una sola '@'
    Rifiutato (regola 2): deve contenere una sola '@'
  ```

### Test 3 – Nome mancante e punto mancante nel dominio

- **Cosa si verifica**: regola 3 e regola 4, anche quando c'è un punto ma
  solo prima della `@`.
- **Input**: `@scuola.it`, `mario@scuola`, `m.rossi@scuola`, `fine`.
- **Valori intermedi attesi**: per `m.rossi@scuola` `ultimo_punto` = 1 < `chiocciola` = 7.
- **Output atteso**:
  ```
    Rifiutato (regola 3): manca il nome prima della '@'
    Rifiutato (regola 4): manca il '.' nel dominio dopo la '@'
    Rifiutato (regola 4): manca il '.' nel dominio dopo la '@'
  ```

### Test 4 – Punto in posizione non ammessa

- **Cosa si verifica**: regola 5 nei suoi due casi.
- **Input**: `mario@.scuola.it`, `mario@scuola.it.`, `fine`.
- **Output atteso**:
  ```
    Rifiutato (regola 5): '.' in posizione non ammessa nel dominio
    Rifiutato (regola 5): '.' in posizione non ammessa nel dominio
  ```

### Test 5 – Riepilogo finale

- **Cosa si verifica**: conteggio di accettati e rifiutati su una sessione completa.
- **Input**: tutti gli indirizzi dei test 1–4 in sequenza, poi `fine`.
- **Output atteso** (ultima riga):
  ```
  Indirizzi accettati: 1, rifiutati: 8
  ```
