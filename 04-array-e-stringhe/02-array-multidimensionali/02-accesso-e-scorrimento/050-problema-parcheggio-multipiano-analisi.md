# Analisi – 050-problema-parcheggio-multipiano.c

## 1. Problema

Un parcheggio di 3 piani da 6 posti registra in ogni posto il numero di
tessera dell'auto, oppure 0 se il posto è libero. Da un menu ripetuto si
gestiscono ingressi (assegnazione del primo posto libero), uscite (ricerca
della tessera e liberazione del posto) e la visualizzazione dello stato.

## 2. Analisi

### Input

| Variabile | Tipo  | Descrizione                                               |
|-----------|-------|-----------------------------------------------------------|
| `scelta`  | `int` | Voce del menu: 1 ingresso, 2 uscita, 3 stato, 0 fine      |
| `tessera` | `int` | Tessera dell'auto in ingresso o in uscita                 |

Lo stato iniziale è inizializzato nel codice: piano 0 con un posto libero,
piano 1 con tre posti liberi, piano 2 vuoto.

### Output
- Ingresso: il piano e il posto assegnati, oppure "Parcheggio completo.";
- uscita: il piano e il posto liberati, oppure "Tessera N non presente nel
  parcheggio.";
- stato: per ogni piano, dall'alto verso il basso, le tessere (`----` per i
  posti liberi) e il numero di posti liberi;
- "Scelta non valida." per voci non previste, "Chiusura cassa." alla fine.

### Vincoli
- La matrice contiene dati (le tessere), non solo uno stato: il valore 0
  indica il posto libero, quindi la tessera 0 non è ammessa
- All'ingresso si assegna il **primo** posto libero, cercando dal piano
  terra verso l'alto e, in ogni piano, dal posto 1 in avanti
- Entrambe le ricerche si fermano al primo risultato tramite un flag nella
  condizione dei due cicli annidati (niente `break`)
- All'uscita la tessera 0 è sempre rifiutata, anche se esistono posti con
  valore 0: altrimenti "libererebbe" un posto già libero
- I piani sono numerati da 0, i posti si stampano da 1
- Il menu si ripete finché la scelta è diversa da 0 (`do-while` con
  `switch`); il `break` di ogni `case` chiude il `case`, non il ciclo
- Il valore restituito da `scanf` si controlla: una scelta non numerica è
  una scelta non valida, una tessera non numerica (o non positiva) in
  ingresso è una tessera non valida; il resto della riga si scarta con
  `getchar`. A fine input (EOF) il programma si comporta come la scelta 0

### Assunzioni
- Il programma non controlla che una tessera in ingresso sia già presente

### Variabili di supporto

| Variabile        | Tipo      | Descrizione                                  |
|------------------|-----------|----------------------------------------------|
| `parcheggio`     | `int[][]` | 3 × 6: tessera dell'auto o `LIBERO` (0)      |
| `trovato`        | `int` (0/1) | Ferma le ricerche                          |
| `piano_trovato`, `posto_trovato` | `int` | Posizione individuata         |
| `liberi_piano`   | `int`     | Posti liberi del piano, per lo stato         |
| `PIANI`, `POSTI`, `LIBERO` | `#define` | 3, 6, 0                         |

### Algoritmo in linguaggio naturale
Ripetere: mostrare il menu, leggere la scelta ed eseguire il ramo
corrispondente, finché la scelta è diversa da 0.
1. Ingresso: leggere la tessera; scorrere piani e posti finché non si trova
   una cella libera; se trovata scrivervi la tessera e stamparne la
   posizione, altrimenti segnalare il parcheggio completo.
2. Uscita: leggere la tessera; cercarla allo stesso modo; se trovata e
   diversa da 0 liberare il posto e stamparlo, altrimenti segnalare che la
   tessera non è presente.
3. Stato: per ogni piano dal più alto al piano terra stampare le celle e
   contare i posti liberi.
4. 0: stampare la chiusura. Altro: "Scelta non valida."

## 3. Casi di test

Il programma è interattivo: ogni test è una sequenza di scelte in una nuova
sessione, che parte dallo stato iniziale e termina con 0.

### Test 1 – Ingressi
- **Cosa si verifica:** il primo posto libero si cerca dal piano terra
- **Input:** `1 1401`, poi `1 1402`
- **Output atteso:** `Tessera 1401: piano 0, posto 3.` e
  `Tessera 1402: piano 1, posto 2.`

### Test 2 – Uscite
- **Input:** `2 1302`, poi `2 9999`, poi `2 0`
- **Output atteso:** `Uscita registrata: liberato piano 1, posto 3.`;
  `Tessera 9999 non presente nel parcheggio.`;
  `Tessera 0 non presente nel parcheggio.`

### Test 3 – Stato dopo i test 1 e 2
- **Input:** le operazioni dei test 1 e 2 nella stessa sessione, poi `3`
- **Output atteso:**
```
  Piano 2 |  ----  ----  ----  ----  ----  ---- | liberi: 6
  Piano 1 |  1300  1402  ----  ----  ----  1310 | liberi: 3
  Piano 0 |  1201  1202  1401  1210  1215  1220 | liberi: 0
```

### Test 4 – Scelta non valida
- **Input:** `7`, poi `0`
- **Output atteso:** `Scelta non valida.`, poi `Chiusura cassa.`

### Test 5 – Parcheggio completo
- **Procedura:** inizializzare la matrice senza celle a 0, poi chiedere un
  ingresso
- **Output atteso:** `Parcheggio completo.`

### Test 6 – Dati non numerici e fine dell'input
- **Cosa si verifica:** la gestione di testo al posto dei numeri e la chiusura senza ciclo infinito
- **Input:** `uno`, `1`, `abc`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Scelta: Scelta non valida.

1 - Ingresso   2 - Uscita   3 - Stato   0 - Fine
Scelta: Numero tessera: Tessera non valida.

1 - Ingresso   2 - Uscita   3 - Stato   0 - Fine
Scelta: Chiusura cassa.
```
