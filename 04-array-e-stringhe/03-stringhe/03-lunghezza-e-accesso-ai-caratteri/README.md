# 03 – Lunghezza e accesso ai caratteri

## Concetto

Una stringa in C è un array di `char` terminato da `'\0'`. Questo significa
che ogni carattere è accessibile tramite il suo indice, esattamente come
negli array, e che la lunghezza non è memorizzata esplicitamente ma deve
essere calcolata scorrendo l'array fino al terminatore.

**Calcolo manuale della lunghezza:**
```
char s[] = "Ciao";   →  s[0]='C'  s[1]='i'  s[2]='a'  s[3]='o'  s[4]='\0'

int lung = 0;
while (s[lung] != '\0') {
    lung++;           →  lung = 4
}
```
L'indice del `'\0'` coincide con la lunghezza della stringa.

**Accesso per indice:**
```
s[0]        → legge il primo carattere
s[i] = 'X'  → modifica il carattere in posizione i
s[i] = '\0' → tronca la stringa in posizione i
```

**Pattern di scansione con while:**
```c
int i = 0;
while (s[i] != '\0') {
    /* elabora s[i] */
    i++;
}
```
Questo pattern è la base di qualsiasi elaborazione testuale in C
e viene usato in tutti i file di questa sezione.

**Classificazione dei caratteri tramite valori ASCII:**
```
Cifre:      '0'(48)  ... '9'(57)
Maiuscole:  'A'(65)  ... 'Z'(90)
Minuscole:  'a'(97)  ... 'z'(122)
Spazio:     ' '(32)
```

**Conversione maiuscola ↔ minuscola:**
La differenza ASCII tra la versione maiuscola e minuscola di una lettera
è sempre 32. Quindi: `'a' - 32 = 'A'` e `'A' + 32 = 'a'`.

---

## File dell'esempio

| File | Tipo | Contenuto |
|------|------|-----------|
| `010-lunghezza-manuale.c` | concetto | Calcolo lunghezza senza `strlen`, differenza lunghezza/dimensione, mappa caratteri |
| `020-accesso-per-indice.c` | concetto | Lettura, modifica, scambio e troncamento di caratteri per indice |
| `030-scansione-con-ciclo.c` | concetto | Pattern di scansione con `while`: conteggio vocali, consonanti, cifre, spazi |
| `040-confronto-carattere-per-carattere.c` | concetto | Confronto manuale tra due stringhe senza `strcmp`, ordine lessicografico |
| `050-problema-conta-occorrenze.c` | problema | Conteggio occorrenze di una lettera in un testo con spazi, distinzione case |
| `050-problema-conta-occorrenze-analisi.md` | analisi | Analisi dettagliata del problema conta occorrenze |
| `060-problema-conta-vocali.c` | problema | Conteggio e distribuzione delle 5 vocali in un testo con spazi |
| `060-problema-conta-vocali-analisi.md` | analisi | Analisi dettagliata del problema conta vocali |
| `070-problema-validazione-password.c` | problema | Verifica 5 requisiti di sicurezza password con flag booleani |
| `070-problema-validazione-password-analisi.md` | analisi | Analisi dettagliata del problema validazione password |
| `080-problema-analisi-testo.c` | problema | Statistiche testo: caratteri, parole, spazi, barra utilizzo |
| `080-problema-analisi-testo-analisi.md` | analisi | Analisi dettagliata del problema analisi testo |
| `090-problema-verifica-iban.c` | problema | Verifica formale IBAN italiano: lunghezza, 6 campi per posizione |
| `090-problema-verifica-iban-analisi.md` | analisi | Analisi dettagliata del problema verifica IBAN |
| `100-problema-censura-testo.c` | problema | Sostituzione di una parola vietata con `*`, modifica in place per indice |
| `100-problema-censura-testo-analisi.md` | analisi | Analisi dettagliata del problema censura testo |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-lunghezza-manuale 010-lunghezza-manuale.c
./010-lunghezza-manuale

gcc -Wall -Wextra -o 020-accesso-per-indice 020-accesso-per-indice.c
./020-accesso-per-indice

gcc -Wall -Wextra -o 030-scansione-con-ciclo 030-scansione-con-ciclo.c
./030-scansione-con-ciclo

gcc -Wall -Wextra -o 040-confronto-carattere-per-carattere 040-confronto-carattere-per-carattere.c
./040-confronto-carattere-per-carattere

gcc -Wall -Wextra -o 050-problema-conta-occorrenze 050-problema-conta-occorrenze.c
./050-problema-conta-occorrenze

gcc -Wall -Wextra -o 060-problema-conta-vocali 060-problema-conta-vocali.c
./060-problema-conta-vocali

gcc -Wall -Wextra -o 070-problema-validazione-password 070-problema-validazione-password.c
./070-problema-validazione-password

gcc -Wall -Wextra -o 080-problema-analisi-testo 080-problema-analisi-testo.c
./080-problema-analisi-testo

gcc -Wall -Wextra -o 090-problema-verifica-iban 090-problema-verifica-iban.c
./090-problema-verifica-iban

gcc -Wall -Wextra -o 100-problema-censura-testo 100-problema-censura-testo.c
./100-problema-censura-testo
```

---

## Output atteso

### 010-lunghezza-manuale
```
=== CALCOLO MANUALE DELLA LUNGHEZZA ===

Stringa   : "Buongiorno"
Lunghezza : 10 caratteri
Dimensione array: 50 celle
Celle usate: 10 (stringa) + 1 (terminatore) + 39 (libere)

Stringa   : "" (stringa vuota)
Lunghezza : 0 caratteri

Stringa   : "Via Roma 12"
Lunghezza : 11 caratteri (spazi inclusi)

Mappa carattere per carattere di "Buongiorno":
Indice Carattere ASCII
-------------------------
0      B          66
1      u          117
2      o          111
3      n          110
4      g          103
5      i          105
6      o          111
7      r          114
8      n          110
9      o          111
10     \0         0   ← terminatore
```

### 030-scansione-con-ciclo
*(testo: "Il C e' un linguaggio potente: usa 42 istruzioni!")*
```
Categoria       Numero Percent.
-------------------------------
Vocali               14      28%
Consonanti           22      44%
Cifre                 2       4%
Spazi                 7      14%
Altri                 5      10%
-------------------------------
Totale               50
```

### 050-problema-conta-occorrenze
*(testo: "Il mare è calmo e limpido", lettera: 'a')*
```
════════════════════════════════════
  RISULTATI ANALISI
════════════════════════════════════
  Testo     : "Il mare e calmo e limpido"
  Lettera   : 'a'
────────────────────────────────────
  Occorrenze esatte ('a')   : 2
  Occorrenze maiuscola ('A'): 0
  Occorrenze minuscola ('a'): 2
  Totale (case-insensitive)  : 2
════════════════════════════════════
```

### 060-problema-conta-vocali
*(testo: "Programmazione in C")*
```
  A/a :   3  [###]
  E/e :   2  [##]
  I/i :   3  [###]
  O/o :   2  [##]
  U/u :   0  []
--------------------------------------------
  Totale vocali    : 10 su 19 caratteri
  Densità vocalica : 52%
```

### 070-problema-validazione-password
*(password: "Sicuro42!")*
```
  Lunghezza (9 car.): OK
  Maiuscola         : OK
  Minuscola         : OK
  Cifra             : OK
  Carattere spec.   : OK
────────────────────────────────────────────
  Requisiti: 5/5 soddisfatti
────────────────────────────────────────────
  ESITO: PASSWORD ACCETTATA
```

*(password: "ciao")*
```
  Lunghezza (4 car.): INSUFFICIENTE (minimo 8)
  Maiuscola         : MANCANTE
  Minuscola         : OK
  Cifra             : MANCANTE
  Carattere spec.   : MANCANTE
────────────────────────────────────────────
  Requisiti: 1/5 soddisfatti
────────────────────────────────────────────
  ESITO: PASSWORD RIFIUTATA
```

### 100-problema-censura-testo
*(testo: "questo prodotto e' pessimo davvero", parola: "pessimo")*
```
  Parola censurata : "pessimo"
  Sostituzioni     : 1
  Testo moderato   :
  "questo prodotto e' ******* davvero"
```

---

## Errori comuni da evitare

**Dimenticare che `'\0'` non è contato nella lunghezza**
```c
char s[] = "Ciao";    /* dimensione array = 5, lunghezza = 4 */
char t[4] = "Ciao";   /* ERRORE: non c'è spazio per '\0' */
char t[5] = "Ciao";   /* CORRETTO */
```

**Accedere oltre la lunghezza della stringa**
```c
char s[] = "Ciao";
char c = s[10];  /* ERRORE: indice fuori dai limiti del contenuto */
```
Prima di accedere a una posizione, verificare che sia inferiore alla lunghezza.

**Troncamento con `'\0'`: i caratteri successivi rimangono in memoria**
```c
char s[] = "Buongiorno";
s[4] = '\0';          /* s diventa "Buon" per printf */
printf("%c", s[5]);   /* stampa 'g': il carattere è ancora in memoria */
```

**Confronto tra stringhe con `==`**
```c
char a[] = "Ciao";
char b[] = "Ciao";
if (a == b) { ... }   /* ERRORE: confronta gli indirizzi, non il contenuto */
```
Il confronto va fatto carattere per carattere (come in `040-confronto-carattere-per-carattere.c`)
oppure con `strcmp` della libreria `<string.h>`.

---

## Concetti collegati

- `01-dichiarazione-e-inizializzazione` → struttura interna delle stringhe
- `02-input-output-stringhe` → lettura di stringhe con `fgets` e `scanf`
- `04-funzioni-su-stringhe` → `strlen`, `strcpy`, `strcmp`, `strcat`

---

## Esercizi proposti

1. Modifica `010-lunghezza-manuale.c` per calcolare e stampare anche il
   numero di celle libere nell'array per ciascuna delle tre stringhe.

2. Modifica `050-problema-conta-occorrenze.c` per contare le occorrenze
   di una cifra (es. `'3'`) invece di una lettera, e verificare che
   funzioni correttamente su un testo con numeri e lettere miste.

3. Estendi `060-problema-conta-vocali.c` per mostrare anche quale vocale
   è la più frequente nel testo (gestendo il caso di parità).

4. Modifica `070-problema-validazione-password.c` per aggiungere un
   sesto requisito: la password non può iniziare con una cifra.

5. Estendi `080-problema-analisi-testo.c` per contare anche le frasi,
   definite come sequenze terminate da `.`, `!` o `?`.

6. Modifica `100-problema-censura-testo.c` per censurare la parola
   sia nella versione originale che in quella con prima lettera maiuscola
   (es. censuare sia "pessimo" che "Pessimo").
