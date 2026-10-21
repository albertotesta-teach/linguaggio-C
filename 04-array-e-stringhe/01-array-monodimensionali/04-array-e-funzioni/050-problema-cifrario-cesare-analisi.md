# Analisi – 050-problema-cifrario-cesare.c

## 1. Problema

Il cifrario di Cesare cifra un messaggio spostando ogni lettera di N posizioni
nell'alfabeto con avvolgimento circolare. Il programma deve cifrare e decifrare
un messaggio usando funzioni dedicate che modificano l'array di char in-place,
lasciando invariati spazi e punteggiatura.

---

## 2. Analisi

### Input
Nessun input da tastiera: i due messaggi sono fissi nel codice.

| Variabile   | Tipo     | Descrizione                                          |
|-------------|----------|------------------------------------------------------|
| `messaggio` | `char[]` | Primo messaggio, cifrato e poi decifrato             |
| `secondo`   | `char[]` | Secondo messaggio, cifrato con chiavi da 1 a 5       |

### Output
- Il primo messaggio originale, la sua lunghezza e il numero di lettere;
  poi il messaggio cifrato con chiave 3 e quello decifrato;
- il secondo messaggio cifrato con ciascuna chiave da 1 a 5.

### Vincoli
- Solo le lettere vengono spostate; spazi, cifre e punteggiatura restano
  invariati
- Maiuscole e minuscole restano tali: ognuna si sposta nel proprio alfabeto
- L'avvolgimento è circolare: dopo la z si torna alla a,
  `(c − 'a' + N) % 26`
- Nella decifratura si aggiunge 26 prima del modulo, perché in C il resto
  di un numero negativo è negativo: `(c − 'a' − N + 26) % 26`
- Decifrare un messaggio cifrato con la stessa chiave restituisce
  l'originale
- Il messaggio è dichiarato `char messaggio[]`, quindi è una copia
  modificabile; con `char *` punterebbe a una stringa letterale non
  modificabile
- Per il secondo messaggio si cifra una copia, così l'originale resta
  disponibile per la chiave successiva

### Assunzioni
- La codifica è ASCII, con lettere consecutive
- 0 ≤ spostamento ≤ 26

### Variabili di supporto

| Variabile     | Tipo      | Descrizione                                   |
|---------------|-----------|-----------------------------------------------|
| `copia`       | `char[50]`| Copia del secondo messaggio per ogni chiave   |
| `chiave`      | `int`     | Spostamento del secondo esempio (1–5)         |
| `SPOSTAMENTO` | `#define` | 3, la chiave usata da Cesare                  |

| Funzione | Descrizione |
|---|---|
| `void cifra(char msg[], int spostamento)` | Sposta in avanti le lettere, in-place |
| `void decifra(char msg[], int spostamento)` | Sposta indietro le lettere, in-place |
| `int lunghezza(const char msg[])` | Caratteri fino a `'\0'` |
| `int conta_lettere(const char msg[])` | Numero di lettere |

### Algoritmo in linguaggio naturale
Cifratura (per ogni carattere fino a `'\0'`):
1. Se è una minuscola: `c = 'a' + (c − 'a' + N) % 26`.
2. Altrimenti, se è una maiuscola: lo stesso con `'A'`.
3. Altrimenti lasciarlo invariato.

La decifratura è identica con `(c − 'a' − N + 26) % 26`.

Programma principale:
1. Stampare il primo messaggio con lunghezza e numero di lettere.
2. Cifrarlo e stamparlo, poi decifrarlo e stamparlo.
3. Per ogni chiave da 1 a 5: copiare il secondo messaggio carattere per
   carattere, cifrare la copia e stamparla.

---

## 3. Casi di test

I messaggi sono fissi nel codice: il Test 3 richiede di sostituire il primo
messaggio e ricompilare.

### Test 1 – Cifratura e decifratura con chiave 3
- **Output atteso:**
```
Messaggio originale  : Veni Vidi Vici
Lunghezza            : 14 caratteri (12 lettere)

Messaggio cifrato    : Yhql Ylgl Ylfl
Messaggio decifrato  : Veni Vidi Vici
```

### Test 2 – Chiavi diverse
- **Output atteso:**
```
  Chiave 1: Buubddp bmm bmcb
  Chiave 2: Cvvceeq cnn cndc
  Chiave 3: Dwwdffr doo doed
  Chiave 4: Exxeggs epp epfe
  Chiave 5: Fyyfhht fqq fqgf
```

### Test 3 – Avvolgimento e caratteri non alfabetici
- **Cosa si verifica:** la z diventa c, le maiuscole restano maiuscole,
  virgola, spazi e punto esclamativo restano invariati
- **Procedura:** sostituire il primo messaggio con `"Zebra xyz, ABC!"`
- **Output atteso:**
```
Messaggio originale  : Zebra xyz, ABC!
Lunghezza            : 15 caratteri (11 lettere)

Messaggio cifrato    : Cheud abc, DEF!
Messaggio decifrato  : Zebra xyz, ABC!
```
