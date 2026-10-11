# 01 – Funzioni scritte a mano

## Concetto

Prima di usare la libreria `string.h` conviene scrivere da sé le funzioni di
base sulle stringhe: così si capisce che cosa fanno davvero e perché hanno
certi limiti.

### Una stringa come parametro

Una stringa si passa a una funzione come qualsiasi array di `char`:

```c
int lunghezza(const char s[]);            /* const: la funzione non la modifica */
void copia(char dest[], const char sorg[]);

n = lunghezza(nome);                      /* nella chiamata solo il nome */
```

La funzione **non riceve la dimensione** dell'array: la fine della stringa si
riconosce dal terminatore `'\0'`. Per questo i cicli hanno la forma:

```c
i = 0;
while (s[i] != '\0') {
    /* elabora s[i] */
    i++;
}
```

### Lunghezza, copia, concatenazione, confronto

| Funzione | Che cosa fa | Attenzione |
|----------|-------------|------------|
| `lunghezza(s)` | conta i caratteri fino a `'\0'` | il `'\0'` non si conta |
| `copia(dest, sorg)` | copia `sorg` in `dest` | va copiato anche il `'\0'` |
| `concatena(dest, sorg)` | aggiunge `sorg` in coda a `dest` | si parte dal `'\0'` di `dest` |
| `confronta(a, b)` | `< 0`, `0`, `> 0` in ordine alfabetico | ordine dei codici ASCII |

### La destinazione deve essere abbastanza grande

`copia` e `concatena` scrivono in `dest` senza sapere quanto è grande. Se
`dest` è troppo piccola si scrive oltre la fine dell'array e si sovrascrivono
altre variabili. Le versioni **limitate** ricevono anche la dimensione e
troncano il testo, terminandolo sempre con `'\0'`:

```c
copia_limitata(corta, originale, DIM_PICCOLA);   /* al massimo DIM_PICCOLA - 1 caratteri */
```

### Le stringhe non si confrontano con `==`

`a == b` confronta gli **indirizzi** dei due array, non il loro contenuto: vale
0 anche quando il testo è lo stesso. Il confronto si fa carattere per
carattere:

```c
while (a[i] == b[i] && a[i] != '\0') {
    i++;
}
return a[i] - b[i];          /* differenza dei primi caratteri diversi */
```

Nell'ordine ASCII le maiuscole vengono prima delle minuscole (`'Z'` = 90,
`'a'` = 97) e una stringa che è l'inizio di un'altra viene prima (`"Mar"` <
`"Mario"`), perché il suo `'\0'` vale 0.

### Lavorare sul singolo carattere

Senza `ctype.h` (che arriva nella sezione 04) le lettere si riconoscono e si
convertono con i codici ASCII:

```c
if (c >= 'A' && c <= 'Z') {
    c = c + ('a' - 'A');     /* da maiuscola a minuscola */
}
```

### Leggere una riga con `fgets`

Nei programmi interattivi la funzione `leggi_riga(s, dim)` legge una riga con
`fgets`, toglie il `'\n'` finale e, se la riga era più lunga dell'array,
scarta i caratteri rimasti nel buffer.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-lunghezza-e-copia.c` | `lunghezza`, `copia` con il `'\0'`, copia indipendente, `copia_limitata` |
| `020-concatenazione.c` | Composizione di un messaggio con `concatena` e `concatena_limitata` |
| `030-confronto.c` | `confronta` in ordine alfabetico, confronto senza maiuscole, `==` sugli array |
| `040-problema-palindromo.c` | Frasi palindrome: pulizia, inversione e confronto |
| `040-problema-palindromo-analisi.md` | Analisi di `040-problema-palindromo.c` |
| `050-problema-normalizza-nome.c` | Nomi con spazi e maiuscole irregolari portati a un formato unico |
| `050-problema-normalizza-nome-analisi.md` | Analisi di `050-problema-normalizza-nome.c` |
| `060-problema-username.c` | Username da nomi e cognomi in array paralleli, con gestione degli omonimi |
| `060-problema-username-analisi.md` | Analisi di `060-problema-username.c` |
| `070-problema-email-istituzionale.c` | Indirizzi email di studenti e docenti e liste di distribuzione |
| `070-problema-email-istituzionale-analisi.md` | Analisi di `070-problema-email-istituzionale.c` |
| `080-problema-rubrica-cognome.c` | Ricerca in rubrica per inizio del cognome, senza distinguere le maiuscole |
| `080-problema-rubrica-cognome-analisi.md` | Analisi di `080-problema-rubrica-cognome.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-lunghezza-e-copia 010-lunghezza-e-copia.c
./010-lunghezza-e-copia

gcc -Wall -Wextra -o 020-concatenazione 020-concatenazione.c
./020-concatenazione

gcc -Wall -Wextra -o 030-confronto 030-confronto.c
./030-confronto

gcc -Wall -Wextra -o 040-problema-palindromo 040-problema-palindromo.c
./040-problema-palindromo

gcc -Wall -Wextra -o 050-problema-normalizza-nome 050-problema-normalizza-nome.c
./050-problema-normalizza-nome

gcc -Wall -Wextra -o 060-problema-username 060-problema-username.c
./060-problema-username

gcc -Wall -Wextra -o 070-problema-email-istituzionale 070-problema-email-istituzionale.c
./070-problema-email-istituzionale

gcc -Wall -Wextra -o 080-problema-rubrica-cognome 080-problema-rubrica-cognome.c
./080-problema-rubrica-cognome
```

---

## Output atteso

### 010-lunghezza-e-copia
```
=== LUNGHEZZA ===
"Programmazione" ha 14 caratteri
"" (stringa vuota) ha 0 caratteri
Lo spazio occupato e' 15 celle: i caratteri piu' il '\0'

=== COPIA ===
duplicato = "Programmazione"
Celle di duplicato (codice ASCII):
  80 114 111 103 114 97 109 109 97 122 105 111 110 101 0 
  l'ultimo 0 e' il terminatore copiato da copia()
Dopo duplicato[0] = 'p':
  originale = "Programmazione"
  duplicato = "programmazione"

=== COPIA LIMITATA (dest di 8 celle) ===
corta = "Program" (7 caratteri + '\0')
La stringa e' stata troncata ma resta una stringa valida.
Con copia(corta, originale) si sarebbe scritto oltre la fine
dell'array, sovrascrivendo altre variabili.
```

### 020-concatenazione
```
=== COMPOSIZIONE DEL MESSAGGIO ===
  passo 1: "Ciao "
  passo 2: "Ciao Giulia"
  passo 3: "Ciao Giulia, tavolo prenotato per "
  finale : "Ciao Giulia, tavolo prenotato per venerdi' alle 20:30"
  lunghezza 53, spazio disponibile 60 celle

=== VERSIONE BREVE (massimo 24 caratteri) ===
  "Ciao Giulia, tavolo pren" (24 caratteri)
  Il testo e' stato troncato: concatena() avrebbe scritto
  oltre la fine dell'array sms.
```

### 030-confronto
```
=== CONFRONTO (maiuscole e minuscole distinte) ===
  Mario  vs Mario  ->    0  uguali
  Anna   vs Bruno  ->   -1  "Anna" viene prima
  Mar    vs Mario  -> -105  "Mar" viene prima
  Zeta   vs alfa   ->   -7  "Zeta" viene prima
  rossi  vs Rossi  ->   32  "rossi" viene dopo
  Rossi  vs Rosso  ->   -6  "Rossi" viene prima

=== CONFRONTO IGNORANDO LE MAIUSCOLE ===
  Zeta   vs alfa   ->   25
  rossi  vs Rossi  ->    0
  Rossi  vs Rosso  ->   -6

Attenzione: prima[0] == seconda[0] vale 0, anche se il testo e'
lo stesso: == confronta gli indirizzi, non i caratteri.
```

### 040-problema-palindromo
*(output dipendente dall'input – esempio con quattro frasi)*
```
=== RICONOSCIMENTO DI PALINDROMI ===
Frase ("fine" per terminare): Anna
  solo lettere : anna
  al contrario : anna
  -> PALINDROMA
Frase ("fine" per terminare): I topi non avevano nipoti
  solo lettere : itopinonavevanonipoti
  al contrario : itopinonavevanonipoti
  -> PALINDROMA
Frase ("fine" per terminare): Programmare in C
  solo lettere : programmareinc
  al contrario : cnierammargorp
  -> non palindroma
Frase ("fine" per terminare): ?!
  solo lettere : 
  al contrario : 
  nessuna lettera da esaminare
Frase ("fine" per terminare): fine

Frasi esaminate: 4, palindrome: 2
```

### 050-problema-normalizza-nome
*(output dipendente dall'input – esempio con tre nomi)*
```
=== NORMALIZZAZIONE DEI NOMI ===
Nome e cognome (riga vuota per terminare):   mARIO   de  ROSSI 
  inserito : [  mARIO   de  ROSSI ]
  archivio : [Mario De Rossi]  (3 parole)
Nome e cognome (riga vuota per terminare): anna-maria d'angelo
  inserito : [anna-maria d'angelo]
  archivio : [Anna-Maria D'Angelo]  (2 parole)
Nome e cognome (riga vuota per terminare): GIUSEPPE verdi
  inserito : [GIUSEPPE verdi]
  archivio : [Giuseppe Verdi]  (2 parole)
Nome e cognome (riga vuota per terminare): 
Fine inserimento.
```

### 060-problema-username
```
=== CREAZIONE DEGLI ACCOUNT ===
  Nome         Cognome        Username
  Mario        Rossi          mrossi
  Marco        Rossi          mrossi2
  Anna Maria   De Luca        adeluca
  Giuseppe     D'Amico        gdamico
  Laura        Bianchi        lbianchi
  Francesca    Santangelo     fsantang
  Mattia       Santangelini   msantang
  Mirko        Rossi          mrossi3

Account creati: 8, di cui 2 con cifra aggiunta
```

### 070-problema-email-istituzionale
```
=== INDIRIZZI EMAIL ISTITUZIONALI ===
  Luca            Ferrari             S  luca.ferrari@studenti.scuola.edu.it
  Maria Grazia    D'Angelo            D  mariagrazia.dangelo@scuola.edu.it
  Paolo           Esposito            S  paolo.esposito@studenti.scuola.edu.it
  Maria Vittoria  Dell'Acqua Bianchi  S  m.dellacquabianchi@studenti.scuola.edu.it
  Sara            Colombo             D  sara.colombo@scuola.edu.it
  Giovanni        La Rosa             S  giovanni.larosa@studenti.scuola.edu.it
  Elena           Ricci               D  elena.ricci@scuola.edu.it

Lista docenti:
  mariagrazia.dangelo@scuola.edu.it
  sara.colombo@scuola.edu.it
  elena.ricci@scuola.edu.it
Lista studenti:
  luca.ferrari@studenti.scuola.edu.it
  paolo.esposito@studenti.scuola.edu.it
  m.dellacquabianchi@studenti.scuola.edu.it
  giovanni.larosa@studenti.scuola.edu.it
```

### 080-problema-rubrica-cognome
*(output dipendente dall'input – esempio con cinque ricerche)*
```
=== RUBRICA DELL'UFFICIO (8 contatti) ===
Cognome o sua parte iniziale ("fine" per uscire): ross
  Rossi      Mario    0131 220145
  Rossetti   Paolo    0131 220102
  Rossi      Anna     0131 220133
  3 contatti
Cognome o sua parte iniziale ("fine" per uscire): Rossi
  Rossi      Mario    0131 220145  (esatto)
  Rossi      Anna     0131 220133  (esatto)
  2 contatti
Cognome o sua parte iniziale ("fine" per uscire): BIANC
  Bianchi    Lucia    0131 220178
  Bianco     Stefano  0131 220166
  Bianchini  Davide   0131 220155
  3 contatti
Cognome o sua parte iniziale ("fine" per uscire): Gialli
  Nessun contatto trovato.
Cognome o sua parte iniziale ("fine" per uscire): 
  Scrivi almeno una lettera.
Cognome o sua parte iniziale ("fine" per uscire): fine
Arrivederci.
```

---

## Errori comuni da evitare

**Dimenticare il terminatore nella copia**
```c
while (sorg[i] != '\0') {
    dest[i] = sorg[i];
    i++;
}
/* manca dest[i] = '\0'; : dest non è una stringa */
```

**Destinazione troppo piccola**
```c
char corta[8];
copia(corta, "Programmazione");   /* 15 celle necessarie: scrive oltre la fine */
```

**Confrontare con `==`**
```c
if (nome == "fine")                  /* confronta indirizzi: sempre falso */
if (confronta(nome, "fine") == 0)    /* corretto */
```

**Usare `sizeof` dentro la funzione per avere la lunghezza**
```c
int f(char s[])
{
    return sizeof(s);    /* dimensione di un puntatore, non della stringa */
}
```

**Lasciare il `'\n'` letto da `fgets`**
```c
fgets(s, DIM, stdin);    /* "fine\n" non è uguale a "fine" */
```

---

## Concetti collegati

- `03-stringhe/03-lunghezza-e-accesso-ai-caratteri` → scansione di una stringa nel `main`
- `01-array-monodimensionali/04-array-e-funzioni` → passaggio di array a funzione
- `02-libreria-string-h` → le stesse operazioni con `strlen`, `strcpy`, `strcat`, `strcmp`
- `04-caratteri-e-conversioni` → `ctype.h` al posto dei confronti sui codici ASCII

---

## Esercizi proposti

1. Scrivi `void inverti_sul_posto(char s[])` che inverte la stringa senza un
   secondo array, scambiando il primo carattere con l'ultimo, il secondo con
   il penultimo e così via.

2. Scrivi `int conta_carattere(const char s[], char c)` e usala per contare
   le vocali di una frase letta da tastiera.

3. In `040-problema-palindromo.c` considera anche le cifre: "1 2 3 2 1" deve
   risultare palindroma.

4. In `060-problema-username.c` usa due cifre quando gli omonimi sono più di
   nove (`mrossi10`).

5. (Avanzato) Scrivi `int confronta_limitata(const char a[], const char b[], int n)`
   che confronta solo i primi `n` caratteri e usala al posto di `inizia_con`
   in `080-problema-rubrica-cognome.c`.
