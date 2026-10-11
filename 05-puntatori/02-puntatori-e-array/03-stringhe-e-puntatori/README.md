# 03 – Stringhe e puntatori

## Concetto

Una stringa è un array di `char` terminato da `'\0'`: tutto ciò che vale per
array e puntatori vale anche per le stringhe. Il ciclo tipico scorre la
stringa con un puntatore fino al terminatore:

```c
const char *p = testo;

while (*p != '\0') {
    /* ... lavora su *p ... */
    p++;
}
/* ora p punta al '\0': la lunghezza è p - testo */
```

Ogni `char` occupa un byte: gli indirizzi dei caratteri crescono di 1.

| Espressione | Significato |
|-------------|-------------|
| `*p` | il carattere puntato |
| `p - testo` | posizione del carattere puntato |
| `testo + k` | la parte di stringa che inizia dalla posizione `k` |
| `printf("%s", testo + k)` | stampa dalla posizione `k` alla fine |
| `printf("%.*s", n, p)` | stampa al massimo `n` caratteri a partire da `p` |

### Array di `char` e puntatore a un letterale

| | `char giorno[] = "lunedi";` | `const char *stato = "APERTO";` |
|-|-----------------------------|---------------------------------|
| che cos'è | un array con una copia del testo | un puntatore a un testo costante |
| `sizeof` | 7 (6 lettere + `'\0'`) | 8 (un indirizzo) |
| modificare i caratteri | sì: `giorno[0] = 'L'` | no: il letterale è di sola lettura |
| cambiare testo | solo copiando carattere per carattere | sì: `stato = "CHIUSO";` |

### Il puntatore restituito da `strchr` e `strstr`

Nel sottocapitolo `04-funzioni-su-stringhe` il risultato di `strchr` e
`strstr` si usava solo nel confronto con `NULL`. Ora si può usare per
davvero:

```c
const char *chiocciola = strchr(email, '@');

if (chiocciola != NULL) {
    posizione = chiocciola - email;          /* 12 */
    printf("%s", chiocciola + 1);            /* scuola.it */
}
```

Anche il `'\n'` lasciato da `fgets` si toglie con un puntatore:

```c
char *a_capo = strchr(riga, '\n');
if (a_capo != NULL) {
    *a_capo = '\0';
}
```

### Due puntatori sulla stessa stringa

Per correggere una stringa **sul posto** si usano un puntatore di lettura e
uno di scrittura: quello di scrittura non supera mai quello di lettura,
quindi non si sovrascrive nulla che debba ancora essere letto.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-scorrere-una-stringa.c` | `while (*p != '\0')`, lunghezza `p - s`, stampa da un punto qualsiasi e al contrario |
| `020-letterali-e-array-di-char.c` | `char s[]` e `const char *s`, `sizeof`, scelta di un messaggio senza copiarlo |
| `030-funzioni-con-puntatori.c` | lunghezza, copia e confronto con i puntatori; uso del puntatore di `strchr` |
| `040-problema-sigle.c` | Sigla di un ente dalle iniziali delle parole lunghe |
| `040-problema-sigle-analisi.md` | Analisi di `040-problema-sigle.c` |
| `050-problema-spazi-in-eccesso.c` | Normalizzazione degli spazi sul posto con lettura e scrittura |
| `050-problema-spazi-in-eccesso-analisi.md` | Analisi di `050-problema-spazi-in-eccesso.c` |
| `060-problema-campi-csv.c` | Scomposizione di righe `cognome;nome;classe;voto` |
| `060-problema-campi-csv-analisi.md` | Analisi di `060-problema-campi-csv.c` |
| `070-problema-parola-piu-lunga.c` | Parola più lunga di un titolo, stampata con `%.*s` |
| `070-problema-parola-piu-lunga-analisi.md` | Analisi di `070-problema-parola-piu-lunga.c` |
| `080-problema-filtro-chat.c` | Parole vietate trovate con `strstr` e sostituite con asterischi |
| `080-problema-filtro-chat-analisi.md` | Analisi di `080-problema-filtro-chat.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-scorrere-una-stringa 010-scorrere-una-stringa.c
./010-scorrere-una-stringa

gcc -Wall -Wextra -o 020-letterali-e-array-di-char 020-letterali-e-array-di-char.c
./020-letterali-e-array-di-char

gcc -Wall -Wextra -o 030-funzioni-con-puntatori 030-funzioni-con-puntatori.c
./030-funzioni-con-puntatori

gcc -Wall -Wextra -o 040-problema-sigle 040-problema-sigle.c
./040-problema-sigle

gcc -Wall -Wextra -o 050-problema-spazi-in-eccesso 050-problema-spazi-in-eccesso.c
./050-problema-spazi-in-eccesso

gcc -Wall -Wextra -o 060-problema-campi-csv 060-problema-campi-csv.c
./060-problema-campi-csv

gcc -Wall -Wextra -o 070-problema-parola-piu-lunga 070-problema-parola-piu-lunga.c
./070-problema-parola-piu-lunga

gcc -Wall -Wextra -o 080-problema-filtro-chat 080-problema-filtro-chat.c
./080-problema-filtro-chat
```

---

## Output atteso

> Gli indirizzi stampati cambiano a ogni esecuzione.

### 010-scorrere-una-stringa
```
=== CARATTERE PER CARATTERE ===
  0x7ffeec9dfd70  'T'
  0x7ffeec9dfd71  'r'
  0x7ffeec9dfd72  'e'
  0x7ffeec9dfd73  'n'
  0x7ffeec9dfd74  'o'
  0x7ffeec9dfd75  ' '
  0x7ffeec9dfd76  '2'
  0x7ffeec9dfd77  '0'
  0x7ffeec9dfd78  '4'
  0x7ffeec9dfd79  '9'
  0x7ffeec9dfd7a  ' '
  0x7ffeec9dfd7b  'p'
  0x7ffeec9dfd7c  'e'
  0x7ffeec9dfd7d  'r'
  0x7ffeec9dfd7e  ' '
  0x7ffeec9dfd7f  'T'
  0x7ffeec9dfd80  'o'
  0x7ffeec9dfd81  'r'
  0x7ffeec9dfd82  'i'
  0x7ffeec9dfd83  'n'
  0x7ffeec9dfd84  'o'
  0x7ffeec9dfd85  '\0'  <- p si ferma qui

Lunghezza: p - annuncio = 21 caratteri
Lettere 14, cifre 4, spazi 3

annuncio + 15 = "Torino"
Al contrario:   "oniroT rep 9402 onerT"
```

### 020-letterali-e-array-di-char
```
=== ARRAY E PUNTATORE ===
  sizeof(giorno) = 7 byte  (6 lettere + '\0')
  sizeof(stato)  = 8 byte  (un indirizzo)

Dopo giorno[0] = 'L': Lunedi

=== CARTELLO (Lunedi) ===
  ore  8:00  CHIUSO   (stato = 0x55d70afdf0c8)
  ore 11:00  APERTO   (stato = 0x55d70afdf008)
  ore 19:00  CHIUSO   (stato = 0x55d70afdf0c8)
  ore 21:00  CHIUSO   (stato = 0x55d70afdf0c8)
```

### 030-funzioni-con-puntatori
```
Indirizzo:  giulia.rossi@scuola.it
Lunghezza:  22 (strlen: 22)
Copia:      giulia.rossi@scuola.it
confronta(email, copia_email) = 0
confronta("andrea", "anna") = -10  (negativo: andrea viene prima)

'@' in posizione chiocciola - email = 12
Dominio:    chiocciola + 1 = "scuola.it"
Utente:     i primi 12 caratteri = "giulia.rossi"
```

### 040-problema-sigle
*(output dipendente dall'input – esempio di sessione)*
```
=== GENERATORE DI SIGLE ===
Nome dell'ente (riga vuota per finire): Istituto Tecnico Industriale Statale
  Sigla: ITIS
Nome dell'ente (riga vuota per finire): Ufficio Relazioni con il Pubblico
  Sigla: URP
Nome dell'ente (riga vuota per finire): Azienda sanitaria locale
  Sigla: ASL
Nome dell'ente (riga vuota per finire): Ente Nazionale per l'Aviazione Civile
  Sigla: ENAC
Nome dell'ente (riga vuota per finire): Comitato Olimpico Nazionale Italiano
  Sigla: CONI
Nome dell'ente (riga vuota per finire): 
```

### 050-problema-spazi-in-eccesso
```
=== NORMALIZZAZIONE DEGLI SPAZI ===
  prima: [   Mario    Rossi   ]
  dopo:  [Mario Rossi]   (9 caratteri tolti)

  prima: [Via Roma ,  12]
  dopo:  [Via Roma, 12]   (2 caratteri tolti)

  prima: [Allergie :  nessuna .]
  dopo:  [Allergie: nessuna.]   (3 caratteri tolti)

  prima: [Sport preferiti:calcio ,   nuoto , tennis]
  dopo:  [Sport preferiti:calcio, nuoto, tennis]   (4 caratteri tolti)
```

### 060-problema-campi-csv
```
=== IMPORTAZIONE VOTI ===
  Cognome    Nome     Classe Voto
  Rossi      Mario    4B     7.50
  Bianchi    Laura    4B     8.00
  riga 3 scartata: 3 campi invece di 4  [Verdi;Paolo;4B]
  riga 4 scartata: voto non valido "sei"
  Esposito   Luca     4B     6.25
  riga 6 scartata: 5 campi invece di 4  [Gallo;Anna;4B;9;assente]

Righe importate: 3 su 6
Media dei voti: 7.25
```

### 070-problema-parola-piu-lunga
```
=== CONTROLLO TITOLI (limite 12 lettere per parola) ===

  "Torneo di pallavolo: vince la 4B"
  parole: 6, la piu' lunga: "pallavolo" (9 lettere, dalla posizione 10)

  "Intervista alla dirigente scolastica"
  parole: 4, la piu' lunga: "Intervista" (10 lettere, dalla posizione 0)

  "Laboratorio di elettrotecnica aperto al pomeriggio"
  parole: 6, la piu' lunga: "elettrotecnica" (14 lettere, dalla posizione 15)  <- troppo lunga per la colonna

  "Gita a Torino, si parte lunedi"
  parole: 6, la piu' lunga: "Torino" (6 lettere, dalla posizione 7)
```

### 080-problema-filtro-chat
*(output dipendente dall'input – esempio di sessione)*
```
=== CHAT DELLA 3A ===
Messaggio (riga vuota per finire): Domani verifica di matematica
  pubblicato: Domani verifica di matematica
Messaggio (riga vuota per finire): Sei proprio uno SCEMO, anzi uno scemo stupido
  pubblicato: Sei proprio uno *****, anzi uno ***** *******   (3 parole filtrate)
Messaggio (riga vuota per finire): Che idiota quel compito
  pubblicato: Che ****** quel compito   (1 parola filtrata)
Messaggio (riga vuota per finire): Ciao a tutti
  pubblicato: Ciao a tutti
Messaggio (riga vuota per finire): 
Parole filtrate nella sessione: 4
```

---

## Errori comuni da evitare

**Modificare un letterale**
```c
char *stato = "APERTO";
stato[0] = 'a';           /* il programma può interrompersi */
```
Un puntatore a letterale si dichiara `const char *`: l'errore diventa di
compilazione.

**Usare `strchr` senza controllare `NULL`**
```c
printf("%s", strchr(email, '@') + 1);   /* se manca '@': NULL + 1 */
```

**Dimenticare il terminatore nella copia**
```c
while (*s != '\0') {
    *d = *s;
    d++;
    s++;
}
/* manca *d = '\0'; */
```

**Leggere il carattere prima dell'inizio**
```c
if (!isalpha(*(p - 1)))   /* se p == testo esce dall'array */
```

**Confondere `sizeof` e lunghezza**
```c
const char *stato = "APERTO";
sizeof(stato);            /* 8: la dimensione del puntatore, non 6 */
```

---

## Concetti collegati

- `04-array-e-stringhe/03-stringhe` → `'\0'` e array di `char`
- `04-array-e-stringhe/04-funzioni-su-stringhe` → `string.h` e `ctype.h`
- `02-array-come-puntatori` → il nome dell'array come indirizzo
- `04-puntatori-a-puntatori` → array di puntatori a stringhe

---

## Esercizi proposti

1. In `010-scorrere-una-stringa.c` conta le vocali scorrendo la stringa con
   il puntatore.

2. In `040-problema-sigle.c` aggiungi un punto dopo ogni lettera della
   sigla (I.T.I.S.).

3. In `050-problema-spazi-in-eccesso.c` aggiungi uno spazio dopo la
   punteggiatura quando manca ("preferiti:calcio").

4. In `060-problema-campi-csv.c` accetta anche la virgola come separatore
   decimale del voto.

5. (Avanzato) In `080-problema-filtro-chat.c` filtra la parola solo se è
   una parola intera: prima e dopo l'occorrenza non devono esserci lettere.
