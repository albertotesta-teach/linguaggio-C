# Analisi – 060-problema-messaggio-sms.c

## 1. Problema

Un sistema di messaggistica permette di inviare messaggi con un limite
massimo di 160 caratteri. Il programma legge il testo del messaggio da
tastiera, rimuove il `'\n'` finale, conta i caratteri usati senza `strlen`,
e visualizza il messaggio formattato con le statistiche di utilizzo.

---

## 2. Analisi

### Input

| Variabile   | Tipo     | Dimensione | Descrizione                                         |
|-------------|----------|------------|-----------------------------------------------------|
| `messaggio` | `char[]` | 162        | Testo del messaggio (160 + `'\n'` + `'\0'`)         |

Mittente e destinatario sono preimpostati nel codice.

### Output
- L'anteprima: mittente, destinatario e testo;
- i caratteri usati su 160 e quelli rimanenti;
- una barra di utilizzo di 10 simboli (`#` usati, `.` liberi) con la
  percentuale;
- lo stato: "Messaggio pronto per l'invio." oppure
  "ATTENZIONE: messaggio vuoto, invio annullato.".

### Vincoli
- Il `'\n'` lasciato da `fgets` si sostituisce con `'\0'`; nello stesso ciclo
  si contano i caratteri: alla fine l'indice del terminatore è la lunghezza
- Il conteggio non usa `strlen`
- La barra ha un `#` ogni 16 caratteri (160 / 10), con divisione intera; la
  percentuale è `caratteri × 100 / 160`, anch'essa intera
- Un messaggio vuoto non viene inviato
- `fgets(messaggio, 162, stdin)` legge al massimo 161 caratteri: se il
  messaggio supera i 160 caratteri si tronca a 160 e si avvisa l'utente; i
  caratteri rimasti nell'input oltre il buffer vengono scartati con `getchar`
- Se l'input termina senza testo il messaggio è vuoto

### Assunzioni
- I caratteri sono a un byte (niente lettere accentate o emoji, che in UTF-8
  occupano più byte)

### Variabili di supporto

| Variabile           | Tipo      | Descrizione                              |
|---------------------|-----------|------------------------------------------|
| `num_caratteri`     | `int`     | Caratteri del messaggio                  |
| `caratteri_rimasti` | `int`     | `LIMITE_CARATTERI − num_caratteri`       |
| `i`                 | `int`     | Indice di scorrimento e della barra      |
| `c`                 | `int`     | Carattere scartato oltre il buffer       |
| `troncato`          | `int`     | 1 se il messaggio è stato accorciato     |
| `LIMITE_CARATTERI`  | `#define` | 160                                      |

### Algoritmo in linguaggio naturale
1. Stampare intestazione, mittente, destinatario e limite.
2. Leggere il messaggio con `fgets`.
3. Scorrere fino a `'\n'` o `'\0'`; se il buffer è pieno senza `'\n'`,
   scartare il resto della riga; scrivere `'\0'` nella posizione raggiunta,
   che è il numero di caratteri.
4. Se i caratteri sono più di 160, troncare il messaggio a 160 e
   ricordarlo in `troncato`.
5. Stampare l'anteprima, i caratteri usati e quelli rimanenti; se il
   messaggio è stato troncato, avvisare.
6. Stampare la barra e la percentuale.
7. Se il messaggio è vuoto annullare l'invio, altrimenti dichiararlo pronto.

---

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato.

### Test 1 – Messaggio breve
- **Input:** `Ci vediamo alle 18 in piazza`
- **Output atteso:**
```
Caratteri usati      : 28 / 160
Caratteri rimanenti  : 132

Utilizzo: [#.........] 17%

Messaggio pronto per l'invio.
```

### Test 2 – Messaggio vuoto
- **Input:** solo Invio
- **Output atteso:** `Utilizzo: [..........] 0%` e
  `ATTENZIONE: messaggio vuoto, invio annullato.`

### Test 3 – Esattamente 160 caratteri
- **Cosa si verifica:** il caso limite ammesso
- **Input:** 160 caratteri
- **Output atteso:** `Caratteri usati      : 160 / 160`,
  `Caratteri rimanenti  : 0`, `Utilizzo: [##########] 100%`,
  `Messaggio pronto per l'invio.`

### Test 4 – Messaggio oltre il limite
- **Cosa si verifica:** il troncamento a 160 caratteri e lo scarto del testo in eccesso
- **Input:** 200 caratteri
- **Output atteso:**
```
Caratteri usati      : 160 / 160
Caratteri rimanenti  : 0
Il testo superava il limite: messaggio troncato a 160 caratteri.

Utilizzo: [##########] 100%

Messaggio pronto per l'invio.
```

### Test 5 – Un solo carattere oltre il limite
- **Cosa si verifica:** con 161 caratteri `fgets` riempie il buffer senza
  leggere il `'\n'`, che va scartato; il messaggio viene comunque troncato
- **Input:** 161 caratteri
- **Output atteso:** come nel Test 4
