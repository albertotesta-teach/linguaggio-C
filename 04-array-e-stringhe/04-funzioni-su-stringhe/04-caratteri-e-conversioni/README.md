# 04 – Caratteri e conversioni

## Concetto

Due librerie completano gli strumenti per lavorare sul testo:

- `<ctype.h>` per riconoscere e convertire il **singolo carattere**;
- `<stdlib.h>` e `<stdio.h>` per passare da **testo a numero** e viceversa.

### Classificare un carattere: `ctype.h`

| Funzione | Vero se `c` è… |
|----------|----------------|
| `isalpha(c)` | una lettera |
| `isdigit(c)` | una cifra da 0 a 9 |
| `isalnum(c)` | una lettera o una cifra |
| `isupper(c)` / `islower(c)` | una lettera maiuscola / minuscola |
| `isspace(c)` | spazio, tabulazione, a capo |
| `ispunct(c)` | un segno di punteggiatura |

"Vero" significa **diverso da 0**, non necessariamente 1: si scrive
`if (isdigit(c))`, mai `if (isdigit(c) == 1)`.

### Convertire maiuscole e minuscole

`toupper(c)` e `tolower(c)` restituiscono il carattere convertito (o quello
originale, se non è una lettera). Per una stringa serve un ciclo:

```c
while (s[i] != '\0') {
    s[i] = (char) toupper((unsigned char) s[i]);
    i++;
}
```

Il cast `(unsigned char)` è una precauzione: le funzioni di `ctype.h`
accettano solo valori di `unsigned char` (o `EOF`), mentre in alcune
codifiche le lettere accentate sono `char` negativi.

### Da testo a numero

| Funzione | Esempio | Problema |
|----------|---------|----------|
| `atoi(s)` | `"42"` → 42 | `"abc"` → 0, `"12abc"` → 12: nessun errore segnalato |
| `atof(s)` | `"3.75"` → 3.75 | come `atoi` |
| `sscanf(s, formato, …)` | come `scanf`, ma legge da una stringa | restituisce quanti valori ha convertito |

`sscanf` permette di **controllare** l'input:

```c
letti = sscanf(riga, "%d/%d/%d%c", &g, &m, &a, &resto);
/* 3 = data corretta, 4 = testo in più, < 3 = formato sbagliato */
```

Una cifra si converte nel suo valore anche con `c - '0'`.

### Da numero a testo

`snprintf(dest, dim, formato, …)` funziona come `printf` ma scrive in una
stringa di `dim` celle, senza mai superarla. Restituisce la lunghezza che il
testo **avrebbe** avuto: se è `>= dim` il testo è stato troncato.
`sprintf`, che non riceve la dimensione, ha lo stesso rischio di `strcpy`.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-classificazione-caratteri.c` | Funzioni `is…` su una frase e conteggio per categoria |
| `020-maiuscole-e-minuscole.c` | `toupper`, `tolower`, iniziali maiuscole, confronto senza maiuscole |
| `030-conversioni-testo-numero.c` | `atoi`, `atof`, controllo con `sscanf`, `snprintf` e troncamento |
| `040-problema-codice-fiscale.c` | Formato del codice fiscale, sesso e data di nascita |
| `040-problema-codice-fiscale-analisi.md` | Analisi di `040-problema-codice-fiscale.c` |
| `050-problema-data-di-nascita.c` | Data gg/mm/aaaa letta con `sscanf`, validata, scritta per esteso |
| `050-problema-data-di-nascita-analisi.md` | Analisi di `050-problema-data-di-nascita.c` |
| `060-problema-scontrino.c` | Righe di uno scontrino composte con `snprintf` |
| `060-problema-scontrino-analisi.md` | Analisi di `060-problema-scontrino.c` |
| `070-problema-comandi-magazzino.c` | Comandi testuali scomposti con `sscanf` |
| `070-problema-comandi-magazzino-analisi.md` | Analisi di `070-problema-comandi-magazzino.c` |
| `080-problema-cifrario-vigenere.c` | Cifratura e decifratura con una parola chiave |
| `080-problema-cifrario-vigenere-analisi.md` | Analisi di `080-problema-cifrario-vigenere.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-classificazione-caratteri 010-classificazione-caratteri.c
./010-classificazione-caratteri

gcc -Wall -Wextra -o 020-maiuscole-e-minuscole 020-maiuscole-e-minuscole.c
./020-maiuscole-e-minuscole

gcc -Wall -Wextra -o 030-conversioni-testo-numero 030-conversioni-testo-numero.c
./030-conversioni-testo-numero

gcc -Wall -Wextra -o 040-problema-codice-fiscale 040-problema-codice-fiscale.c
./040-problema-codice-fiscale

gcc -Wall -Wextra -o 050-problema-data-di-nascita 050-problema-data-di-nascita.c
./050-problema-data-di-nascita

gcc -Wall -Wextra -o 060-problema-scontrino 060-problema-scontrino.c
./060-problema-scontrino

gcc -Wall -Wextra -o 070-problema-comandi-magazzino 070-problema-comandi-magazzino.c
./070-problema-comandi-magazzino

gcc -Wall -Wextra -o 080-problema-cifrario-vigenere 080-problema-cifrario-vigenere.c
./080-problema-cifrario-vigenere
```

---

## Output atteso

### 010-classificazione-caratteri
```
Frase: "Lezione 3: il C e' nato nel 1972, ok?"

Car. alpha digit upper space punct
 'L'      1     0     1     0     0
 'e'      1     0     0     0     0
 'z'      1     0     0     0     0
 'i'      1     0     0     0     0
 'o'      1     0     0     0     0
 'n'      1     0     0     0     0
 'e'      1     0     0     0     0
 ' '      0     0     0     1     0
 '3'      0     1     0     0     0
 ':'      0     0     0     0     1
...

Riepilogo su 37 caratteri:
  lettere        20 (di cui maiuscole 2)
  cifre           5
  spazi           8
  punteggiatura   4
```

### 020-maiuscole-e-minuscole
```
toupper('b') = 'B', toupper('B') = 'B', toupper('7') = '7'

Codice prima : rss mra 85t10 a944s
Codice dopo  : RSS MRA 85T10 A944S

Nome prima   : aNNA mARIA de LUCA
Nome dopo    : Anna Maria De Luca

"Alessandria" e "ALESSANDRIA": stessa citta'
```

### 030-conversioni-testo-numero
```
=== atoi e atof ===
  [42]     atoi =  42   atof = 42.00
  [3.75]   atoi =   3   atof =  3.75
  [12abc]  atoi =  12   atof = 12.00
  [abc]    atoi =   0   atof =  0.00
  [  7]    atoi =   7   atof =  7.00

=== sscanf(s, "%d%c") ===
  [42]: numero intero valido: 42
  [3.75]: dopo il numero 3 c'e' altro testo
  [12abc]: dopo il numero 12 c'e' altro testo
  [abc]: non e' un numero
  [  7]: numero intero valido: 7

=== snprintf ===
  etichetta = "Aula 12 - piano 2"
  etichetta = "Laboratorio 3 - pia" (troncata: servivano 23 caratteri)
```

### 040-problema-codice-fiscale
*(output dipendente dall'input – esempio con due codici corretti e tre errati)*
```
=== CONTROLLO CODICE FISCALE ===
Codice fiscale (riga vuota per terminare): rssmra85t10a944s
  RSSMRA85T10A944S: formato corretto
    sesso M, nato il 10 dicembre '85
Codice fiscale (riga vuota per terminare): BNCLRA92M52F205X
  BNCLRA92M52F205X: formato corretto
    sesso F, nata il 12 agosto '92
Codice fiscale (riga vuota per terminare): RSSMRA85T10A94
  RSSMRA85T10A94: deve avere 16 caratteri, ne ha 14
Codice fiscale (riga vuota per terminare): RSSMR485T10A944S
  RSSMR485T10A944S: in posizione 6 serve una lettera
Codice fiscale (riga vuota per terminare): RSSMRA85Z10A944S
  RSSMRA85Z10A944S: la lettera del mese 'Z' non esiste
Codice fiscale (riga vuota per terminare): 
```

### 050-problema-data-di-nascita
*(output dipendente dall'input – esempio con date valide e non valide)*
```
=== DATA DI NASCITA (riferimento 11/10/2026) ===
Data gg/mm/aaaa (riga vuota per terminare): 12/05/2010
  Data valida: 12 maggio 2010, eta' 16 anni
Data gg/mm/aaaa (riga vuota per terminare): 29/02/2023
  febbraio 2023 ha 28 giorni
Data gg/mm/aaaa (riga vuota per terminare): 29/02/2024
  Data valida: 29 febbraio 2024, eta' 2 anni
Data gg/mm/aaaa (riga vuota per terminare): 31/04/2011
  aprile 2011 ha 30 giorni
Data gg/mm/aaaa (riga vuota per terminare): 15/13/2009
  Il mese 13 non esiste
Data gg/mm/aaaa (riga vuota per terminare): 12-05-2010
  Formato non valido: usare gg/mm/aaaa
Data gg/mm/aaaa (riga vuota per terminare): 12/05/2010 ore 8
  Testo in piu' dopo la data
Data gg/mm/aaaa (riga vuota per terminare): 25/12/2009
  Data valida: 25 dicembre 2009, eta' 16 anni
Data gg/mm/aaaa (riga vuota per terminare): 03/02/1850
  Anno 1850 fuori dall'intervallo 1900-2026
Data gg/mm/aaaa (riga vuota per terminare): 
```

### 060-problema-scontrino
```
Righe da stampare: 12 (larghezza 36 caratteri)

|      CARTOLERIA IL QUADERNO        |
|------------------------------------|
|Quaderno a quadret   4 x     10.00  |
|Penna gel blu        3 x      5.40  |
|Evidenziatore        2 x      2.40  |
|Calcolatrice scien   1 x     15.90  |
|Righello 30 cm       1 x      1.40  |
|Colla stick          2 x      1.90  |
|------------------------------------|
|SUBTOTALE           13       37.00  |
|Sconto 10%                   -3.70  |
|TOTALE EURO                  33.30  |
```

### 070-problema-comandi-magazzino
*(output dipendente dall'input – esempio di sessione)*
```
=== MAGAZZINO FERRAMENTA ===
Comandi: CARICO art n | SCARICO art n | STATO [art] | FINE
> stato
  viti       200
  dadi       150
  chiodi     500
  tasselli    80
  rondelle   300
> carico VITI 50
  viti: +50 -> 250 pezzi
> Scarico dadi 200
  Disponibili solo 150 dadi.
> SCARICO dadi 20
  dadi: -20 -> 130 pezzi
> carico bulloni 10
  Articolo "bulloni" sconosciuto.
> carico viti
  Uso: CARICO articolo quantita' (positiva)
> stato viti
  viti: 250 pezzi
> ordina
  Comando "ORDINA" sconosciuto.
> 
  Scrivi un comando.
> FINE
Sessione chiusa.
```

### 080-problema-cifrario-vigenere
*(output dipendente dall'input – esempio con una chiave non valida e due messaggi)*
```
=== CIFRARIO DI VIGENERE ===
Chiave (solo lettere): luna 2
  Chiave non valida.
Chiave (solo lettere): luna
Chiave in uso: LUNA
Messaggio (riga vuota per terminare): CIAO MONDO
  cifrato  : NCNO XIADZ
  decifrato: CIAO MONDO  (uguale all'originale)
Messaggio (riga vuota per terminare): Ci vediamo alle 16, in biblioteca!
  cifrato  : Nc ieocnmz uylp 16, ca btvyiznrcl!
  decifrato: Ci vediamo alle 16, in biblioteca!  (uguale all'originale)
Messaggio (riga vuota per terminare): 
```

---

## Errori comuni da evitare

**Confrontare il risultato di `isdigit` con 1**
```c
if (isdigit(c) == 1)    /* può essere falso anche per una cifra */
if (isdigit(c))         /* corretto */
```

**Pensare che `toupper` modifichi la stringa**
```c
toupper(s[i]);              /* il risultato va perso */
s[i] = (char) toupper((unsigned char) s[i]);
```

**Fidarsi di `atoi` per validare un numero**
```c
n = atoi("abc");        /* 0: indistinguibile da "0" */
```

**Confondere la cifra con il suo valore**
```c
anno = cf[6] * 10 + cf[7];                  /* usa i codici ASCII (54, 55...) */
anno = (cf[6] - '0') * 10 + (cf[7] - '0');  /* corretto */
```

**`sprintf` senza limite**
```c
sprintf(riga, "%s ...", descrizione);              /* può superare l'array */
snprintf(riga, sizeof(riga), "%s ...", descrizione);
```

---

## Concetti collegati

- `01-funzioni-scritte-a-mano` → le stesse conversioni fatte con i codici ASCII
- `03-stringhe/02-input-output-stringhe` → `fgets` e `scanf`
- `05-array-di-stringhe` → elenchi di parole da confrontare e convertire

---

## Esercizi proposti

1. In `010-classificazione-caratteri.c` aggiungi il conteggio delle vocali
   (maiuscole e minuscole) con `tolower` e `strchr("aeiou", c)`.

2. In `040-problema-codice-fiscale.c` verifica che il giorno sia valido
   (1-31 per i maschi, 41-71 per le femmine).

3. In `050-problema-data-di-nascita.c` accetta anche le date con il trattino
   (`12-05-2010`) provando un secondo formato di `sscanf`.

4. In `070-problema-comandi-magazzino.c` aggiungi il comando
   `NUOVO articolo quantità` che inserisce un articolo (array a tappo).

5. (Avanzato) In `080-problema-cifrario-vigenere.c` cifra anche le cifre
   0-9, spostandole di `spostamento % 10`.
