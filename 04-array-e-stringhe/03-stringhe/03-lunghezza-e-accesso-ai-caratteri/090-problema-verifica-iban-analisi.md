# Analisi – 090-problema-verifica-iban.c

## 1. Problema

Un'applicazione bancaria deve verificare il formato formale di un IBAN
italiano prima di procedere con una transazione. La verifica controlla:
lunghezza (27 caratteri), country code ("IT"), check digits (2 cifre),
CIN (1 lettera), ABI (5 cifre), CAB (5 cifre), BBAN (12 alfanumerici).

---

## 2. Analisi

### Input

| Variabile | Tipo     | Dimensione | Descrizione                        |
|-----------|----------|------------|------------------------------------|
| `iban`    | `char[]` | 28         | IBAN senza spazi (27 + `'\0'`)     |

### Output
- Per ogni campo l'esito `[OK]` con il valore, oppure `[!!]` con il motivo;
  se la lunghezza è sbagliata si stampa solo l'esito della lunghezza;
- l'esito finale "FORMATO VALIDO" oppure "FORMATO NON VALIDO (n errore/i)".

Struttura dell'IBAN italiano (indici):
```
 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15..26
 I  T  0  0  A  0  0  0  0  0  0  0  0  0  0  000000000000
|CT |CD |CI|    ABI    |    CAB    |       BBAN         |
```

### Vincoli
- La lunghezza deve essere esattamente 27; con una lunghezza diversa gli
  altri controlli non si eseguono, perché gli indici potrebbero cadere fuori
  dal contenuto
- Country code: `'I'` e `'T'` maiuscole; check digits: due cifre; CIN: una
  lettera maiuscola; ABI e CAB: cinque cifre; BBAN: dodici caratteri tra
  cifre e lettere maiuscole
- Ogni segmento si verifica con un ciclo che si ferma al primo carattere non
  valido (flag `segmento_ok`)
- Tutti gli errori vengono contati e segnalati, non solo il primo
- La verifica è solo **formale**: non controlla il checksum
- `scanf("%27s")` legge al massimo 27 caratteri: quelli in eccesso restano
  nell'input, quindi si leggono con `getchar` fino a spazio, a capo o EOF e
  si aggiungono alla lunghezza; un IBAN troppo lungo è stampato con `...`
- Se l'input termina senza IBAN, l'IBAN è vuoto (lunghezza 0)

### Assunzioni
- L'IBAN si inserisce in forma compatta, senza spazi

### Variabili di supporto

| Variabile      | Tipo  | Descrizione                                   |
|----------------|-------|-----------------------------------------------|
| `lunghezza`    | `int` | Caratteri fino a `'\0'` più quelli eccedenti  |
| `eccedenti`    | `int` | Caratteri oltre i 27 rimasti nell'input       |
| `c`            | `int` | Carattere letto con `getchar`                 |
| `lunghezza_ok`, `country_ok`, `checkdigit_ok`, `cin_ok`, `abi_ok`, `cab_ok`, `bban_ok` | `int` | Flag dei controlli |
| `segmento_ok`  | `int` | Flag temporaneo per un segmento               |
| `errori`       | `int` | Errori trovati                                |
| `i`            | `int` | Indice dei cicli                              |

### Algoritmo in linguaggio naturale
1. Leggere l'IBAN (al massimo 27 caratteri), contare con `getchar` i
   caratteri rimasti oltre il buffer e calcolare la lunghezza totale.
2. Se la lunghezza è 27: verificare country code, check digits e CIN con
   confronti diretti; verificare ABI, CAB e BBAN scorrendo le rispettive
   posizioni e fermandosi al primo carattere non valido.
3. Stampare l'esito della lunghezza e, se corretta, quello di ogni campo,
   contando gli errori.
4. Stampare l'esito finale.

---

## 3. Casi di test

Per ogni caso si inserisce l'IBAN indicato.

### Test 1 – IBAN valido
- **Input:** `IT60X0542811101000000123456`
- **Output atteso:**
```
  [OK] Lunghezza    : 27 caratteri
  [OK] Country code : IT
  [OK] Check digits : 60
  [OK] CIN          : X
  [OK] ABI          : 05428
  [OK] CAB          : 11101
  [OK] Conto (BBAN) : 000000123456
  ESITO: FORMATO VALIDO
```

### Test 2 – Lunghezza errata
- **Input:** `IT60X054281110100000012345` (26 caratteri)
- **Output atteso:** `[!!] Lunghezza    : 26 caratteri (richiesti 27)` e
  `ESITO: FORMATO NON VALIDO (1 errore/i)`, senza gli altri controlli

### Test 3 – Un solo campo errato
- **Input:** `it60X0542811101000000123456` (country code minuscolo) e
  `IT6AX0542811101000000123456` (check digit non numerico)
- **Output atteso:** rispettivamente
  `[!!] Country code : it (richiesto IT)` e
  `[!!] Check digits : devono essere due cifre`, con 1 errore

### Test 4 – Più campi errati
- **Cosa si verifica:** tutti gli errori sono contati
- **Input:** `DE6A1054281A101000000123-56`
- **Output atteso:** errori su country code, check digits, CIN, CAB e BBAN;
  `[OK] ABI          : 05428`; `ESITO: FORMATO NON VALIDO (5 errore/i)`

### Test 5 – IBAN troppo lungo
- **Cosa si verifica:** i caratteri oltre il 27° sono contati e l'IBAN è rifiutato
- **Input:** `IT60X0542811101000000123456Z` (28 caratteri)
- **Output atteso:**
```
  RISULTATO VERIFICA: IT60X0542811101000000123456...
════════════════════════════════════════════
  [!!] Lunghezza    : 28 caratteri (richiesti 27)
────────────────────────────────────────────
  ESITO: FORMATO NON VALIDO (1 errore/i)
```
