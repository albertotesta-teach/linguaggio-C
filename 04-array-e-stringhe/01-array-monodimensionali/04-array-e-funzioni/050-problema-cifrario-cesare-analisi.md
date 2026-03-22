# Analisi – 050-problema-cifrario-cesare.c

## 1. Problema

Il cifrario di Cesare cifra un messaggio spostando ogni lettera di N posizioni
nell'alfabeto con avvolgimento circolare. Il programma deve cifrare e decifrare
un messaggio usando funzioni dedicate che modificano l'array di char in-place,
lasciando invariati spazi e punteggiatura.

---

## 2. Analisi generale e struttura dati

Il punto chiave è l'**aritmetica modulare per l'avvolgimento circolare**:
la formula `(c - 'a' + N) % 26` trasforma ogni lettera in un indice [0,25],
applica lo spostamento e riporta al codice ASCII. Per la decifratura si aggiunge
26 prima del modulo per evitare valori negativi.

| Variabile     | Tipo      | Dimensione | Motivazione                                              |
|---------------|-----------|------------|----------------------------------------------------------|
| `messaggio`   | `char[]`  | variabile  | Array modificabile; dichiarato con `char[]`, non `char*` |
| `SPOSTAMENTO` | `#define` | 3          | Chiave del cifrario; modifica unica per cambiare chiave  |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Cifratura

**a) Input**
Array `msg[]`, intero `spostamento`.

**b) Output**
Il messaggio viene modificato in-place:
```
Messaggio originale  : Veni Vidi Vici
Messaggio cifrato    : Yhql Ylgl Ylfl
```

**c) Funzione coinvolta**
`cifra(msg, spostamento)`: scorre fino a `'\0'`, applica la formula separatamente
per minuscole e maiuscole, ignora tutto il resto.

**d) Vincoli**
- Formula minuscole: `'a' + (c - 'a' + spostamento) % 26`.
- Formula maiuscole: `'A' + (c - 'A' + spostamento) % 26`.
- Il modulo 26 garantisce che dopo 'z' si torni ad 'a' (avvolgimento).
- Spazi, numeri e punteggiatura non vengono modificati.

**e) Assunzioni**
- Il messaggio contiene solo caratteri ASCII standard.
- `spostamento` è compreso tra 1 e 25.

**f) Algoritmo in linguaggio naturale**
```
Per i da 0 finché msg[i] != '\0':
  Se msg[i] è minuscola: msg[i] = 'a' + (msg[i] - 'a' + spostamento) % 26.
  Se msg[i] è maiuscola: msg[i] = 'A' + (msg[i] - 'A' + spostamento) % 26.
  Altrimenti: invariato.
```

---

### Caso d'uso 2 – Decifratura

**a) Input**
Array `msg[]` già cifrato, intero `spostamento`.

**b) Output**
Il messaggio viene riportato all'originale:
```
Messaggio decifrato  : Veni Vidi Vici
```

**c) Funzione coinvolta**
`decifra(msg, spostamento)`: applica lo spostamento inverso con `- spostamento + 26`
prima del modulo per evitare risultati negativi.

**d) Vincoli**
- Formula: `(c - 'a' - spostamento + 26) % 26`. Il `+ 26` è essenziale:
  senza di esso, con `spostamento = 3` e `c = 'a'`, si otterrebbe `(0 - 3) % 26 = -3`
  che è un indice non valido.
- `decifra(cifra(msg, N), N)` deve riprodurre esattamente il messaggio originale.

**f) Algoritmo in linguaggio naturale**
```
Per i da 0 finché msg[i] != '\0':
  Se minuscola: msg[i] = 'a' + (msg[i] - 'a' - spostamento + 26) % 26.
  Se maiuscola: msg[i] = 'A' + (msg[i] - 'A' - spostamento + 26) % 26.
```

---

### Caso d'uso 3 – Dimostrazione con chiavi diverse

**a) Input**
Stringa `secondo`, chiavi da 1 a 5.

**b) Output**
```
  Chiave 1: Buubddb bmm bmcb
  Chiave 2: Cvvceec cnn cncb
  ...
```

**c) Variabili di supporto**
- `copia` (`char[]`): copia manuale del messaggio originale prima di cifrare,
  per non modificare `secondo` a ogni iterazione del ciclo.

**d) Vincoli**
- La copia viene fatta elemento per elemento con un ciclo fino a `'\0'`.
- Il terminatore `'\0'` deve essere copiato esplicitamente dopo il ciclo.
- Ogni iterazione del ciclo esterno parte dal messaggio originale,
  non dal risultato della cifratura precedente.

**f) Algoritmo in linguaggio naturale**
```
Per chiave da 1 a 5:
  Copiare secondo[] in copia[] (incluso '\0').
  cifra(copia, chiave).
  Stampare chiave e copia.
```
