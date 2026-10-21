# Analisi – 080-problema-cifrario-vigenere.c

## 1. Problema

Due studenti vogliono scambiarsi messaggi cifrati con il cifrario di
Vigenère. Ogni lettera del messaggio viene spostata in avanti nell'alfabeto
del valore della lettera corrispondente della chiave (A = 0, … Z = 25), che
si ripete ciclicamente. Le lettere mantengono maiuscola o minuscola, gli
altri caratteri restano invariati. Il programma cifra ogni frase e, come
verifica, la decifra di nuovo.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `chiave` | `char[20]` | Parola chiave, richiesta finché non è valida |
| `messaggio` | `char[80]` | Frase da cifrare, una per riga; una riga vuota termina |

### Output

- `Chiave non valida.` per ogni chiave rifiutata, poi `Chiave in uso: <CHIAVE>` in maiuscolo;
  se l'input termina prima di una chiave valida,
  `Nessuna chiave valida inserita: programma terminato.`
- Per ogni messaggio: il testo cifrato e il testo decifrato, con
  l'indicazione `(uguale all'originale)` oppure `(ERRORE)`.

### Vincoli

- La chiave deve essere non vuota e contenere solo lettere (`isalpha`);
  viene portata in maiuscolo.
- Lettera cifrata = `base + (c - base + spostamento + 26) % 26`, con
  `base` = `'A'` o `'a'` a seconda della lettera e
  `spostamento` = `(chiave[k] - 'A') × verso` (`verso` = 1 cifra, -1 decifra).
- Sottraendo si può scendere sotto 0: si aggiunge 26 prima del `% 26`.
- L'indice `k` della chiave avanza solo sulle lettere: spazi, cifre e
  punteggiatura non consumano la chiave e restano invariati.

### Assunzioni

- Il messaggio non contiene lettere accentate.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `cifrato`, `decifrato` | `char[80]` | Risultati |
| `letta` | `int` | 1 se la lettura del messaggio è riuscita |
| `fine_input` | `int` | 1 se l'input termina prima di una chiave valida |
| `i` | `int` | Indice per la conversione della chiave |
| `k` | `int` | In `vigenere`: lettere cifrate finora (posizione nella chiave = `k % lung_chiave`) |
| `base`, `spostamento` | `char`, `int` | In `vigenere`: inizio dell'alfabeto e spostamento della lettera corrente |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Legge una riga e toglie il `'\n'`; a fine input restituisce una stringa vuota |
| `chiave_valida` | Chiave non vuota con sole lettere (`isalpha`) |
| `vigenere` | Cifra (`verso` = 1) o decifra (`verso` = -1) |

### Algoritmo in linguaggio naturale

1. Ripetere la lettura della chiave finché non è valida o l'input termina,
   segnalando ogni chiave rifiutata; se l'input è terminato, avvisare e
   non leggere messaggi.
2. Convertire la chiave in maiuscolo e stamparla.
3. Leggere un messaggio; finché la lettura riesce e il messaggio non è vuoto:
   1. cifrarlo con `verso` = 1 e decifrare il risultato con `verso` = -1;
   2. stampare cifrato e decifrato e confrontare il decifrato con l'originale;
   3. leggere il messaggio successivo.
4. In `vigenere`, per ogni carattere: se è una lettera spostarla del valore
   della lettera `k % lung_chiave` della chiave e incrementare `k`,
   altrimenti copiarlo invariato.

## 3. Casi di test

### Test 1 – Chiave non valida

- **Cosa si verifica**: chiave con caratteri non alfabetici e chiave vuota
  vengono rifiutate; la chiave valida è portata in maiuscolo.
- **Input**: `luna 2`, riga vuota, `luna`.
- **Output atteso**:
  ```
  Chiave (solo lettere):   Chiave non valida.
  Chiave (solo lettere):   Chiave non valida.
  Chiave (solo lettere): Chiave in uso: LUNA
  ```

### Test 2 – Cifratura

- **Cosa si verifica**: spostamenti della chiave e lo spazio che non la consuma.
- **Input**: chiave `luna`, messaggio `CIAO MONDO`, poi riga vuota.
- **Valori intermedi attesi**: spostamenti L = 11, U = 20, N = 13, A = 0;
  `C` + 11 = `N`, `I` + 20 = 28 % 26 = 2 → `C`; dopo lo spazio la chiave
  riparte da `L` (`k` = 4): `M` + 11 = `X`.
- **Output atteso**:
  ```
    cifrato  : NCNO XIADZ
    decifrato: CIAO MONDO  (uguale all'originale)
  ```

### Test 3 – Maiuscole, minuscole e caratteri non alfabetici

- **Cosa si verifica**: le lettere conservano il caso, cifre e punteggiatura restano invariate.
- **Input**: chiave `luna`, messaggio `Ci vediamo alle 16, in biblioteca!`
- **Output atteso**:
  ```
    cifrato  : Nc ieocnmz uylp 16, ca btvyiznrcl!
    decifrato: Ci vediamo alle 16, in biblioteca!  (uguale all'originale)
  ```

### Test 4 – Giro dell'alfabeto

- **Cosa si verifica**: il `% 26` riporta all'inizio dell'alfabeto in cifratura
  e il `+ 26` evita valori negativi in decifratura.
- **Input**: chiave `luna`, messaggio `zzz`.
- **Valori intermedi attesi**: `z` (25) + 11 = 36 % 26 = 10 → `k`;
  in decifratura `k` (10) − 11 + 26 = 25 → `z`.
- **Output atteso**:
  ```
    cifrato  : ktm
    decifrato: zzz  (uguale all'originale)
  ```

### Test 5 – Fine dell'input durante la richiesta della chiave
- **Cosa si verifica:** se l'input termina prima di una chiave valida il
  programma si chiude invece di ripetere la richiesta all'infinito.
- **Input:** `luna 2`, poi fine dell'input (Ctrl+D, o input da pipe).
- **Output atteso:**
  ```
  Chiave (solo lettere):   Chiave non valida.
  Chiave (solo lettere): 
  Nessuna chiave valida inserita: programma terminato.
  ```
