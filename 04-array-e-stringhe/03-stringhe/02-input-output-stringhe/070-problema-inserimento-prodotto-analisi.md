# Analisi – 070-problema-inserimento-prodotto.c

## 1. Problema

Un operatore di magazzino usa un terminale per inserire nuovi prodotti
nell'archivio. Il programma legge codice, nome (con possibili spazi),
categoria, prezzo e quantità, verifica che i campi obbligatori non siano
vuoti e stampa la scheda prodotto pronta per l'archiviazione.

---

## 2. Analisi

### Input

| Variabile       | Tipo     | Dimensione | Descrizione                                       |
|-----------------|----------|------------|---------------------------------------------------|
| `codice`        | `char[]` | 10         | Codice senza spazi (es. ELE-042), max 9 caratteri |
| `nome_prodotto` | `char[]` | 81         | Nome con spazi, max 80 caratteri                  |
| `categoria`     | `char[]` | 21         | Categoria con spazi, max 20 caratteri             |
| `prezzo`        | `char[]` | 10         | Prezzo come testo (es. 12.50), max 9 caratteri    |
| `quantita`      | `int`    | —          | Pezzi disponibili                                 |

### Output
- Se nome e categoria non sono vuoti e la quantità è valida, la scheda
  prodotto con tutti i campi e "Prodotto inserito correttamente nell'archivio.";
- altrimenti "ERRORE: campi obbligatori mancanti o non validi.", l'elenco
  dei campi errati e "Inserimento annullato.".

### Vincoli
- Codice e prezzo non contengono spazi: si leggono con `scanf("%9s")`, che
  limita i caratteri alla dimensione del buffer
- Nome e categoria possono contenere spazi: si leggono con `fgets`, poi si
  sostituisce il `'\n'` finale con `'\0'`
- Se `fgets` riempie il buffer senza leggere il `'\n'`, il campo era troppo
  lungo: si tiene la parte che sta nel buffer (80 o 20 caratteri) e si
  scarta il resto della riga, che altrimenti finirebbe nel campo successivo
- Dopo una `scanf` resta un `'\n'` nel buffer: prima della `fgets` va
  consumato, altrimenti la `fgets` leggerebbe una riga vuota
- Nome e categoria sono obbligatori: un campo è vuoto se il primo carattere
  è `'\0'`; si segnalano tutti i campi vuoti, non solo il primo
- La quantità deve essere un intero non negativo: si controlla il valore
  restituito da `scanf` (`quantita` parte da 0)
- Il prezzo è conservato come testo, quindi non è validato come numero

### Assunzioni
- Codice e prezzo non superano i 9 caratteri

### Variabili di supporto

| Variabile          | Tipo  | Descrizione                       |
|--------------------|-------|-----------------------------------|
| `i`                | `int` | Indice per trovare il `'\n'`      |
| `c`                | `int` | Carattere scartato dal buffer     |
| `nome_valido`, `categoria_valida`, `quantita_valida` | `int` | Flag di validità dei campi |

### Algoritmo in linguaggio naturale
1. Leggere il codice con `scanf` e scartare il resto della riga.
2. Leggere nome e categoria con `fgets`; per ciascuno cercare il `'\n'`:
   se non c'è e il buffer è pieno scartare il resto della riga; scrivere
   `'\0'` nella posizione trovata.
3. Leggere il prezzo con `scanf`; leggere la quantità e controllare che la
   lettura sia riuscita e il valore non sia negativo.
4. Verificare che nome e categoria non siano vuoti.
5. Se tutti i campi sono validi stampare la scheda, altrimenti l'errore con
   i campi errati.

---

## 3. Casi di test

Per ogni caso si inseriscono i cinque campi nell'ordine: codice, nome,
categoria, prezzo, quantità.

### Test 1 – Inserimento corretto
- **Input:** `ELE-042`, `Cavo HDMI 2m`, `Elettronica`, `12.50`, `35`
- **Output atteso:**
```
  Codice      : ELE-042
  Nome        : Cavo HDMI 2m
  Categoria   : Elettronica
  Prezzo      : 12.50 EUR
  Disponibile : 35 pz
════════════════════════════════════════════════

Prodotto inserito correttamente nell'archivio.
```

### Test 2 – Campi obbligatori vuoti
- **Cosa si verifica:** sono segnalati entrambi i campi
- **Input:** `ELE-042`, Invio, Invio, `12.50`, `35`
- **Output atteso:**
```
ERRORE: campi obbligatori mancanti o non validi.
  - Il nome del prodotto non può essere vuoto.
  - La categoria non può essere vuota.
Inserimento annullato.
```

### Test 3 – Categoria più lunga del buffer
- **Cosa si verifica:** il campo troppo lungo viene troncato e il resto
  della riga non finisce nei campi successivi
- **Input:** `ELE-042`, `Cavo`, `Elettronica di consumo varia` (28
  caratteri), `12.50`, `35`
- **Output atteso:**
```
  Categoria   : Elettronica di consu
  Prezzo      : 12.50 EUR
  Disponibile : 35 pz
```

### Test 4 – Quantità non valida
- **Cosa si verifica:** una quantità non numerica o negativa annulla l'inserimento
- **Input:** `ELE-042`, `Mouse`, `Accessori`, `9.90`, `abc` (e, in una
  seconda esecuzione, `-2`)
- **Output atteso:**
```
ERRORE: campi obbligatori mancanti o non validi.
  - La quantità deve essere un numero intero non negativo.
Inserimento annullato.
```
