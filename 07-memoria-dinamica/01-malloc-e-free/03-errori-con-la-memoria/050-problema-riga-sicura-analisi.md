# Analisi – 050-problema-riga-sicura.c

## 1. Problema

La bacheca digitale della scuola mostra messaggi di al massimo 30
caratteri. Le righe si leggono con `fgets` in un buffer di 32 byte, che non
può traboccare; se la riga è più lunga il resto si consuma con `getchar` e
si conta, così il messaggio viene rifiutato con la sua lunghezza vera. I
messaggi accettati si copiano in blocchi di `strlen + 1` byte.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| riga | testo | Un messaggio per riga; `FINE` termina |

### Output

- `pubblicato (B byte)`, `troppo lungo: N caratteri, massimo 30`,
  `messaggio vuoto`, `Memoria insufficiente.`
- Alla fine la bacheca incorniciata con i messaggi pubblicati.

### Vincoli

- Buffer di 32 byte: 30 caratteri, l'a capo e il terminatore.
- Se nel buffer manca l'a capo, la riga è più lunga: i caratteri rimasti
  si leggono con `getchar` fino all'a capo e si contano.
- Ogni messaggio: `malloc((lunghezza + 1) * sizeof *messaggio)`, controllo
  di `NULL`, `free` dopo la stampa.
- Al massimo 5 messaggi. A fine input il programma termina come con
  `FINE`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `bacheca` | `char *[5]` | Messaggi pubblicati |
| `buffer` | `char[32]` | Riga letta |
| `messaggio` | `char *` | Copia nello heap |
| `lunghezza` | `int` | Lunghezza vera della riga |

| Funzione | Compito |
|----------|---------|
| `leggi_riga(buffer, dimensione, &lunghezza)` | Legge senza traboccare e misura la riga intera; 0 a fine input |

### Algoritmo in linguaggio naturale

1. Finché non si termina e c'è posto: leggere una riga; con `FINE` o a
   fine input terminare; se troppo lunga o vuota segnalarlo; altrimenti
   copiarla in un blocco della lunghezza giusta.
2. Stampare la bacheca liberando ogni blocco.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Messaggi della settimana

- **Input:** `Gita annullata`, `Compito di storia rinviato a luned`
  (34 caratteri), riga vuota, `Palestra chiusa`,
  `Assemblea d'istituto venerdi`, `Consiglio di classe ore 15`, `FINE`
- **Output atteso:**
  ```
  Messaggi per la bacheca (al massimo 30 caratteri, FINE per terminare)
  >   pubblicato (15 byte)
  >   troppo lungo: 34 caratteri, massimo 30
  >   messaggio vuoto
  >   pubblicato (16 byte)
  >   pubblicato (29 byte)
  >   pubblicato (27 byte)
  > 
  +--------------------------------+
  | Gita annullata                 |
  | Palestra chiusa                |
  | Assemblea d'istituto venerdi   |
  | Consiglio di classe ore 15     |
  +--------------------------------+
  ```

### Test 2 – Bacheca piena

- **Input:** `m1` ... `m6`
- **Output atteso:** cinque messaggi pubblicati; il sesto non viene letto.
