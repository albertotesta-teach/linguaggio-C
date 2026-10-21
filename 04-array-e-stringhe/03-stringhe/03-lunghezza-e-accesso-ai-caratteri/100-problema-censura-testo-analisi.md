# Analisi – 100-problema-censura-testo.c

## 1. Problema

Una piattaforma di messaggistica deve censurare automaticamente una parola
non consentita in un messaggio, sostituendo ogni carattere della parola
con `'*'`. La sostituzione avviene direttamente nella stringa modificando
i caratteri per indice. Il programma conta anche il numero di sostituzioni
effettuate.

---

## 2. Analisi

### Input

| Variabile | Tipo     | Dimensione | Descrizione                                    |
|-----------|----------|------------|------------------------------------------------|
| `testo`   | `char[]` | 201        | Messaggio con spazi, max 200 caratteri         |
| `vietata` | `char[]` | 31         | Parola da censurare, senza spazi, max 30       |

### Output
- La parola censurata, il numero di sostituzioni e il testo moderato;
- "Nessuna occorrenza trovata: messaggio approvato." oppure
  "Testo modificato: N occorrenza/e censurata/e.".

### Vincoli
- Per ogni posizione del testo si confrontano i caratteri successivi con la
  parola vietata; il confronto si ferma alla prima differenza o alla fine
  del testo (flag `corrispondenza`)
- Ogni occorrenza trovata è sostituita da tanti `*` quanti sono i suoi
  caratteri, quindi la lunghezza del testo non cambia
- Dopo una sostituzione si riparte dal carattere successivo alla parola
  censurata, per non ricontare caratteri già sostituiti
- Il confronto distingue maiuscole e minuscole
- Si cerca la sequenza di caratteri, non la parola intera: anche una parte
  di parola viene censurata (vedi Test 3)

### Assunzioni
- La parola vietata non è vuota

### Variabili di supporto

| Variabile        | Tipo  | Descrizione                                       |
|------------------|-------|---------------------------------------------------|
| `lung_vietata`   | `int` | Lunghezza della parola vietata                    |
| `sostituzioni`   | `int` | Occorrenze censurate                              |
| `i`, `j`, `k`    | `int` | Posizione nel testo, nella parola, nella sostituzione |
| `corrispondenza` | `int` | 1 se la parola inizia in posizione `i`            |

### Algoritmo in linguaggio naturale
1. Leggere il testo con `fgets` e rimuovere il `'\n'`; leggere la parola con
   `scanf` e contarne i caratteri.
2. Per ogni posizione i del testo:
   a. confrontare i `lung_vietata` caratteri da i con la parola, fermandosi
      alla prima differenza o al terminatore;
   b. se coincidono sostituirli con `*`, contare la sostituzione e saltare
      alla fine della parola; altrimenti avanzare di un carattere.
3. Stampare il risultato e il messaggio finale.

---

## 3. Casi di test

Per ogni caso si inseriscono il messaggio e la parola indicati.

### Test 1 – Due occorrenze
- **Input:** `questo prodotto e' pessimo, davvero pessimo`, `pessimo`
- **Output atteso:**
```
  Sostituzioni     : 2
  Testo moderato   :
  "questo prodotto e' *******, davvero *******"
```
  e `Testo modificato: 2 occorrenza/e censurata/e.`

### Test 2 – Nessuna occorrenza
- **Input:** `ciao a tutti`, `brutto`
- **Output atteso:** `Nessuna occorrenza trovata: messaggio approvato.`

### Test 3 – Maiuscole e parti di parola
- **Cosa si verifica:** il confronto distingue le maiuscole e trova anche
  sequenze dentro altre parole
- **Input:** `Male male`, `male` e poi `fa male, anzi malefico`, `male`
- **Output atteso:** `"Male ****"` con 1 sostituzione;
  `"fa ****, anzi ****fico"` con 2 sostituzioni
