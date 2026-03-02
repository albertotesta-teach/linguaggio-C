# Analisi – 100-problema-censura-testo.c

## 1. Problema

Una piattaforma di messaggistica deve censurare automaticamente una parola
non consentita in un messaggio, sostituendo ogni carattere della parola
con `'*'`. La sostituzione avviene direttamente nella stringa modificando
i caratteri per indice. Il programma conta anche il numero di sostituzioni
effettuate.

---

## 2. Analisi generale e struttura dati

| Variabile       | Tipo     | Dimensione | Motivazione                                              |
|-----------------|----------|------------|----------------------------------------------------------|
| `testo`         | `char[]` | 201        | Messaggio con spazi, max 200 caratteri + `'\0'`          |
| `vietata`       | `char[]` | 31         | Parola da censurare, senza spazi, max 30 caratteri + `'\0'` |
| `lung_vietata`  | `int`    | —          | Lunghezza della parola vietata, calcolata con ciclo while |
| `sostituzioni`  | `int`    | —          | Contatore delle occorrenze censurate                     |
| `i`             | `int`    | —          | Posizione corrente nel testo durante la scansione        |
| `j`             | `int`    | —          | Indice per scorrere la parola vietata nel confronto      |
| `k`             | `int`    | —          | Indice per sovrascrivere i caratteri con `'*'`           |
| `corrispondenza`| `int`    | —          | Flag: 1 se la parola vietata inizia in posizione `i`     |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Lettura del testo e della parola vietata

**a) Input**
Testo con spazi (max 200 caratteri) e parola vietata senza spazi (max 30 caratteri).

**b) Output**
Nessun output diretto: i valori sono memorizzati in `testo` e `vietata`.

**c) Variabili di supporto**
- `i` (`int`): indice per rimozione `'\n'` da `fgets`.

**d) Vincoli**
- Il testo viene letto con `fgets` per permettere spazi.
- La parola vietata viene letta con `scanf` (singola parola, senza spazi).
- Il `'\n'` lasciato da `fgets` nel testo va rimosso prima della scansione.

**e) Assunzioni**
- La parola vietata non contiene spazi.
- La ricerca è case-sensitive.

**f) Algoritmo in linguaggio naturale**
```
1. Leggere il testo con fgets; rimuovere '\n'.
2. Leggere la parola vietata con scanf("%30s", vietata).
```

---

### Caso d'uso 2 – Calcolo della lunghezza della parola vietata

**a) Input**
La stringa `vietata`.

**b) Output**
Nessun output diretto: imposta `lung_vietata`.

**c) Variabili di supporto**
- `j` (`int`): indice del ciclo di conteggio.

**d) Vincoli**
- La lunghezza è necessaria per sapere quanti caratteri confrontare
  e quanti sostituire con `'*'` ad ogni corrispondenza.

**e) Assunzioni**
- La parola vietata non è vuota (nessuna verifica esplicita).

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare lung_vietata a 0 e j a 0.
2. Finché vietata[j] non è '\0': incrementare lung_vietata e j.
```

---

### Caso d'uso 3 – Scansione, confronto e sostituzione

**a) Input**
`testo`, `vietata`, `lung_vietata`.

**b) Output**
Nessun output diretto: modifica `testo` in place sostituendo le
occorrenze con `'*'`, aggiorna `sostituzioni`.

**c) Variabili di supporto**
- `i` (`int`): posizione corrente nel testo (avanza di 1 o di `lung_vietata`).
- `j` (`int`): indice per il confronto carattere per carattere.
- `k` (`int`): indice per la sostituzione con `'*'`.
- `corrispondenza` (`int`): flag che assume 1 all'inizio di ogni tentativo
  e viene impostato a 0 al primo carattere diverso.

**d) Vincoli**
- Il ciclo esterno scorre tutto il testo fino a `'\0'`.
- Il ciclo interno di confronto si ferma se `j` raggiunge `lung_vietata`
  (corrispondenza trovata) oppure se un carattere è diverso.
- Dopo una sostituzione, `i` avanza di `lung_vietata` per evitare di
  rianalizzare i caratteri appena censurati.
- L'accesso `testo[i + j]` è sicuro perché il ciclo controlla anche
  `testo[i + j] == '\0'` prima di confrontare.

**e) Assunzioni**
- La ricerca è case-sensitive.
- Parole parzialmente sovrapposte non vengono gestite
  (es. "aabaa" con vietata "aa": censura solo la prima occorrenza
  non sovrapposta).

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare i a 0.
2. Finché testo[i] non è '\0':
   a. Inizializzare j a 0 e corrispondenza a 1.
   b. Finché j < lung_vietata e corrispondenza è 1:
      - Se testo[i+j] è '\0' o diverso da vietata[j]:
        corrispondenza = 0.
      - Incrementare j.
   c. Se corrispondenza è 1:
      - Inizializzare k a 0.
      - Finché k < lung_vietata: testo[i+k] = '*'; incrementare k.
      - Incrementare sostituzioni.
      - i += lung_vietata.
   d. Altrimenti:
      - Incrementare i.
```

---

### Caso d'uso 4 – Output del testo moderato

**a) Input**
`testo` (modificato), `vietata`, `sostituzioni`.

**b) Output**
```
════════════════════════════════════════════
  RISULTATO MODERAZIONE
════════════════════════════════════════════
  Parola censurata : "pessimo"
  Sostituzioni     : 1
  Testo moderato   :
  "questo prodotto e' ******* davvero"
════════════════════════════════════════════

Testo modificato: 1 occorrenza/e censurata/e.
```

**c) Variabili di supporto**
Nessuna variabile aggiuntiva.

**d) Vincoli**
- Il messaggio finale distingue il caso "nessuna occorrenza" dal caso
  con sostituzioni effettuate.

**e) Assunzioni**
- Il testo modificato viene stampato direttamente dalla variabile `testo`
  che è stata modificata in place.

**f) Algoritmo in linguaggio naturale**
```
1. Stampare la parola censurata, il numero di sostituzioni e il testo moderato.
2. Se sostituzioni == 0: stampare "messaggio approvato".
3. Altrimenti: stampare il numero di occorrenze censurate.
```
