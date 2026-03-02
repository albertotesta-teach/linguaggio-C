# Analisi – 060-problema-messaggio-sms.c

## 1. Problema

Un sistema di messaggistica permette di inviare messaggi con un limite
massimo di 160 caratteri. Il programma legge il testo del messaggio da
tastiera, rimuove il `'\n'` finale, conta i caratteri usati senza `strlen`,
e visualizza il messaggio formattato con le statistiche di utilizzo.

---

## 2. Analisi generale e struttura dati

| Variabile            | Tipo     | Dimensione | Motivazione                                              |
|----------------------|----------|------------|----------------------------------------------------------|
| `mittente`           | `char[]` | 12         | Nome mittente preimpostato + `'\0'`                      |
| `destinatario`       | `char[]` | 13         | Nome destinatario preimpostato + `'\0'`                  |
| `messaggio`          | `char[]` | 162        | 160 caratteri + 1 per `'\n'` di fgets + 1 per `'\0'`    |
| `num_caratteri`      | `int`    | —          | Numero di caratteri del messaggio (calcolato manualmente)|
| `caratteri_rimasti`  | `int`    | —          | LIMITE_CARATTERI - num_caratteri                         |
| `i`                  | `int`    | —          | Indice per scorrere il buffer (rimozione '\n' e conteggio)|
| `LIMITE_CARATTERI`   | `#define`| —          | Costante: limite massimo di 160 caratteri                |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Lettura e pulizia del messaggio

**a) Input**
Testo digitato dall'utente da tastiera, max 160 caratteri visibili.

**b) Output**
Nessun output diretto: il testo viene memorizzato in `messaggio`
senza il `'\n'` finale.

**c) Variabili di supporto**
- `i` (`int`): scorre la stringa per trovare `'\n'` e simultaneamente
  conta i caratteri.

**d) Vincoli**
- `fgets` è chiamata con dimensione 162 per garantire che non si superi
  mai il buffer anche nel caso peggiore (160 caratteri + `'\n'` + `'\0'`).
- Il ciclo si ferma al primo `'\n'` o `'\0'`.

**e) Assunzioni**
- L'input proviene da `stdin`.
- Se l'utente digita più di 160 caratteri, `fgets` tronca automaticamente.

**f) Algoritmo in linguaggio naturale**
```
1. Mostrare il prompt di inserimento.
2. Leggere il messaggio con fgets(messaggio, 162, stdin).
3. Inizializzare i a 0.
4. Finché messaggio[i] non è '\n' e non è '\0':
   a. Incrementare i.
5. Impostare messaggio[i] a '\0'.
6. Assegnare i a num_caratteri (l'indice del terminatore = lunghezza).
```

---

### Caso d'uso 2 – Calcolo statistiche di utilizzo

**a) Input**
`num_caratteri` e la costante `LIMITE_CARATTERI`.

**b) Output**
Nessun output diretto: calcola `caratteri_rimasti`.

**c) Variabili di supporto**
- `caratteri_rimasti` (`int`): differenza tra limite e caratteri usati.

**d) Vincoli**
- `caratteri_rimasti` non può essere negativo grazie al limite di `fgets`.

**e) Assunzioni**
- `num_caratteri` è già stato calcolato correttamente nel caso d'uso 1.

**f) Algoritmo in linguaggio naturale**
```
1. Calcolare caratteri_rimasti = LIMITE_CARATTERI - num_caratteri.
```

---

### Caso d'uso 3 – Visualizzazione messaggio e statistiche

**a) Input**
`messaggio`, `mittente`, `destinatario`, `num_caratteri`,
`caratteri_rimasti`, `LIMITE_CARATTERI`.

**b) Output**
Anteprima del messaggio formattata, statistiche e barra di utilizzo:
```
══════════════════════════════════════════════
  ANTEPRIMA MESSAGGIO
══════════════════════════════════════════════
  Da  : Mario Rossi
  A   : Anna Bianchi
  Msg : Ciao Anna, ci vediamo domani alle 10?
══════════════════════════════════════════════

Caratteri usati      : 41 / 160
Caratteri rimanenti  : 119

Utilizzo: [##........] 25%

Messaggio pronto per l'invio.
```

**c) Variabili di supporto**
- `i` (`int`): riutilizzato per scorrere le 10 posizioni della barra.

**d) Vincoli**
- La barra di utilizzo ha sempre 10 celle, ognuna rappresenta 16 caratteri.
- Il messaggio di stato finale dipende da `num_caratteri`.

**e) Assunzioni**
- La divisione intera `num_caratteri / 16` determina le celle `'#'` della barra.
- La percentuale è calcolata con aritmetica intera (troncata, non arrotondata).

**f) Algoritmo in linguaggio naturale**
```
1. Stampare la scheda con mittente, destinatario e testo del messaggio.
2. Stampare il numero di caratteri usati e quelli rimasti.
3. Stampare la barra di utilizzo:
   a. Inizializzare i a 0.
   b. Finché i < 10:
      - Se i < num_caratteri / 16: stampare '#'.
      - Altrimenti: stampare '.'.
      - Incrementare i.
4. Stampare la percentuale di utilizzo.
5. Stampare il messaggio di stato:
   - Se num_caratteri è 0: "messaggio vuoto".
   - Altrimenti: "pronto per l'invio".
```
