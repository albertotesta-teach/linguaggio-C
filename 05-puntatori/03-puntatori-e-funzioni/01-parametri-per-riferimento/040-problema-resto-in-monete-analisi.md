# Analisi – 040-problema-resto-in-monete.c

## 1. Problema

Il distributore di bevande della scuola ha una scorta limitata di monete
per ogni taglio. Per ogni acquisto (prezzo e importo inserito, in
centesimi) calcola il resto usando prima le monete più grandi, senza
superare quelle disponibili. Se non riesce a dare il resto esatto annulla
la vendita. Dopo ogni operazione mostra la scorta. Con `0 0` termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `prezzo`, `inserito` | `int` | Prezzo e importo inserito in centesimi; `0 0` per finire |
| `tagli` | `int[6]` | 200, 100, 50, 20, 10, 5 centesimi (nel sorgente, dal più grande) |
| `scorta` | `int[6]` | Monete disponibili: 2, 3, 1, 4, 5, 2 (nel sorgente) |

### Output

- `Resto X.XX euro:` con le monete usate per taglio, oppure
  `Importo esatto: nessun resto.`, oppure
  `Resto non disponibile (mancano N cent): vendita annullata.`
- Dopo ogni vendita (riuscita o annullata) la scorta di ogni taglio.
- `Importo non valido.` se il prezzo è negativo, l'importo inserito è
  minore del prezzo o i dati non sono due numeri.

### Vincoli

- `eroga_resto` riceve `tagli` e `scorta` come `const int *` (solo
  lettura), scrive le monete da dare in `usate` e i centesimi scoperti in
  `*mancante` (parametri di uscita) e restituisce 1 se il resto è esatto.
- Per ogni taglio, dal più grande, si usano `resto / taglio` monete, ma non
  più di quelle in scorta.
- La scorta si aggiorna solo se il resto è esatto: con una vendita
  annullata non cambia.
- Un input che non contiene due numeri si scarta (resto della riga) e vale
  come importo non valido; a fine input il programma termina come con `0 0`.

### Assunzioni

- Si usa sempre la moneta più grande possibile: questo metodo può fallire
  anche quando una combinazione diversa di monete darebbe il resto esatto.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `usate` | `int[6]` | Monete da dare per taglio (uscita della funzione) |
| `mancante` | `int` | Centesimi che non si riescono a dare (uscita) |
| `letti` | `int` | Valore restituito da `scanf` |
| `t`, `n` | `int` | Indice del taglio, monete di quel taglio |

| Funzione | Compito |
|----------|---------|
| `eroga_resto(resto, tagli, scorta, usate, &mancante)` | Calcola le monete; restituisce 1 se il resto è esatto |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché il prezzo non è 0:
   1. leggere prezzo e importo (a fine input porre il prezzo a 0; se non
      sono due numeri scartare la riga e considerarli non validi);
   2. se non validi segnalarlo; se l'importo è uguale al prezzo dire che
      non c'è resto;
   3. altrimenti chiamare `eroga_resto` sul resto: se è esatto stampare le
      monete e toglierle dalla scorta, altrimenti stampare quanto manca;
      poi stampare la scorta.
2. In `eroga_resto`, per ogni taglio: `n = resto / taglio`, al massimo la
   scorta; scrivere `usate[t] = n` e togliere dal resto; alla fine scrivere
   il resto scoperto in `*mancante`.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe). I test sono in
sequenza: la scorta risente degli acquisti precedenti.

### Test 1 – Resto esatto

- **Input:** `130 500`
- **Valori intermedi attesi:** resto 370 = 200 + 100 + 50 + 20.
- **Output atteso:**
  ```
    Resto 3.70 euro:  1 x 200 cent  1 x 100 cent  1 x 50 cent  1 x 20 cent
    Scorta:  200 cent: 1  100 cent: 2  50 cent: 0  20 cent: 3  10 cent: 5  5 cent: 2
  ```

### Test 2 – Moneta da 50 finita

- **Input:** `120 200`
- **Output atteso:**
  ```
    Resto 0.80 euro:  3 x 20 cent  2 x 10 cent
    Scorta:  200 cent: 1  100 cent: 2  50 cent: 0  20 cent: 0  10 cent: 3  5 cent: 2
  ```

### Test 3 – Resto impossibile

- **Cosa si verifica:** la vendita è annullata e la scorta non cambia.
- **Input:** `30 100`
- **Valori intermedi attesi:** resto 70: nessuna moneta da 50 e da 20, tre
  da 10 → restano 40, con le due da 5 → restano 30.
- **Output atteso:**
  ```
    Resto non disponibile (mancano 30 cent): vendita annullata.
    Scorta:  200 cent: 1  100 cent: 2  50 cent: 0  20 cent: 0  10 cent: 3  5 cent: 2
  ```

### Test 4 – Importi non validi, importo esatto e fine

- **Input:** `50 40`, `abc`, `100 100`, `0 0`
- **Output atteso:** due volte `  Importo non valido.`, poi
  `  Importo esatto: nessun resto.`; il programma termina.
