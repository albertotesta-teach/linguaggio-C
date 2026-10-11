# 03 – Ricerca nelle stringhe

## Concetto

Cercare un carattere o una parola dentro un testo è una delle operazioni
più frequenti: validare un indirizzo email, filtrare commenti, cercare in un
catalogo.

### Le funzioni di `string.h`

| Funzione | Cerca | Se non trova |
|----------|-------|--------------|
| `strchr(s, c)` | la prima occorrenza del carattere `c` | `NULL` |
| `strrchr(s, c)` | l'ultima occorrenza del carattere `c` | `NULL` |
| `strstr(s, parola)` | la prima occorrenza della sottostringa | `NULL` |

Le tre funzioni restituiscono un **puntatore** al punto in cui si trova
l'occorrenza. I puntatori verranno trattati nel capitolo 05: per ora il
risultato si usa solo per sapere **se** c'è un'occorrenza.

```c
if (strchr(email, '@') != NULL)          /* contiene una '@' */
if (strstr(testo, "USB") == NULL)        /* non contiene "USB" */
```

### Quando serve la posizione: funzioni che restituiscono l'indice

Per sapere **dove** si trova un'occorrenza si usano funzioni scritte a mano
che restituiscono l'indice, oppure `-1`:

| Funzione | Restituisce |
|----------|-------------|
| `prima_posizione(s, c)` | indice della prima occorrenza di `c` |
| `ultima_posizione(s, c)` | indice dell'ultima occorrenza di `c` |
| `cerca_da(s, parola, da)` | indice della prima occorrenza di `parola` a partire da `da` |
| `copia_parte(dest, s, inizio, n)` | copia `n` caratteri da `inizio` (per estrarre un pezzo) |

`cerca_da` controlla per ogni posizione `i` se la parola "combacia" con i
caratteri che partono da `i`:

```c
while (parola[j] != '\0' && s[i + j] == parola[j]) {
    j++;
}
trovata = (parola[j] == '\0');
```

### Contare tutte le occorrenze

Si ripete la ricerca ripartendo subito dopo l'occorrenza trovata:

```c
posizione = cerca_da(testo, parola, 0);
while (posizione != -1) {
    conteggio++;
    posizione = cerca_da(testo, parola, posizione + 1);
}
```

### Maiuscole e parole intere

- La ricerca distingue maiuscole e minuscole: per ignorarle si cerca in una
  **copia in minuscolo** del testo. Le posizioni trovate valgono anche per
  l'originale, perché le due stringhe hanno la stessa lunghezza.
- `strstr` cerca una sequenza di caratteri: `"il"` si trova anche in
  `"invisibili"`. Per una parola intera bisogna controllare che prima e dopo
  l'occorrenza non ci sia un'altra lettera.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-strchr-e-strrchr.c` | Presenza di un carattere, prima e ultima posizione, estrazione dei pezzi di un codice |
| `020-strstr.c` | Ricerca di parole chiave nelle descrizioni di prodotti, `cerca_da` |
| `030-conta-occorrenze.c` | Occorrenze sovrapposte e separate, parole intere |
| `040-problema-validazione-email.c` | Controllo del formato di un indirizzo email con cinque regole |
| `040-problema-validazione-email-analisi.md` | Analisi di `040-problema-validazione-email.c` |
| `050-problema-filtro-commenti.c` | Parole vietate sostituite da asterischi, senza distinguere maiuscole |
| `050-problema-filtro-commenti-analisi.md` | Analisi di `050-problema-filtro-commenti.c` |
| `060-problema-catalogo-biblioteca.c` | Ricerca per parola chiave in titoli e autori |
| `060-problema-catalogo-biblioteca-analisi.md` | Analisi di `060-problema-catalogo-biblioteca.c` |
| `070-problema-nome-ed-estensione.c` | Cartella, nome ed estensione dei file e conteggio per tipo |
| `070-problema-nome-ed-estensione-analisi.md` | Analisi di `070-problema-nome-ed-estensione.c` |
| `080-problema-smistamento-messaggi.c` | Richieste smistate agli uffici in base alle parole chiave |
| `080-problema-smistamento-messaggi-analisi.md` | Analisi di `080-problema-smistamento-messaggi.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-strchr-e-strrchr 010-strchr-e-strrchr.c
./010-strchr-e-strrchr

gcc -Wall -Wextra -o 020-strstr 020-strstr.c
./020-strstr

gcc -Wall -Wextra -o 030-conta-occorrenze 030-conta-occorrenze.c
./030-conta-occorrenze

gcc -Wall -Wextra -o 040-problema-validazione-email 040-problema-validazione-email.c
./040-problema-validazione-email

gcc -Wall -Wextra -o 050-problema-filtro-commenti 050-problema-filtro-commenti.c
./050-problema-filtro-commenti

gcc -Wall -Wextra -o 060-problema-catalogo-biblioteca 060-problema-catalogo-biblioteca.c
./060-problema-catalogo-biblioteca

gcc -Wall -Wextra -o 070-problema-nome-ed-estensione 070-problema-nome-ed-estensione.c
./070-problema-nome-ed-estensione

gcc -Wall -Wextra -o 080-problema-smistamento-messaggi 080-problema-smistamento-messaggi.c
./080-problema-smistamento-messaggi
```

---

## Output atteso

### 010-strchr-e-strrchr
```
=== PRESENZA DEL TRATTINO (strchr) ===
  ELE-0042-A7    contiene '-'
  ALI-118        contiene '-'
  ABB0091B2      senza '-'
  ELE-0077-B1-R  contiene '-'
  ALI-0003-C4    contiene '-'

=== POSIZIONI DEL TRATTINO ===
  Codice          primo ultimo  Categoria / lotto
  ELE-0042-A7         3      8  ELE / A7
  ALI-118             3      3  manca il lotto
  ABB0091B2          -1     -1  formato non riconosciuto
  ELE-0077-B1-R       3     11  ELE / R
  ALI-0003-C4         3      8  ALI / C4

strrchr("ELE-0042-A7", 'Z') == NULL
```

### 020-strstr
```
=== Prodotti che contengono "USB" ===
  Cavo USB-C 2 metri                 posizione 5
  Mouse wireless con ricevitore USB  posizione 30
  Hub USB 4 porte con cavo USB-C     posizione 4

=== Prodotti che contengono "wireless" ===
  Mouse wireless con ricevitore USB  posizione 6
  Tastiera wireless italiana         posizione 9

=== Prodotti che contengono "usb" ===
  (nessuno: la ricerca distingue maiuscole e minuscole)

In "Hub USB 4 porte con cavo USB-C":
  prima occorrenza di USB  : 4
  seconda occorrenza di USB: 25
  terza occorrenza di USB  : -1
```

### 030-conta-occorrenze
```
Testo: "il re va al mare e vede le onde: il mare urla, il re ride e corre"

=== Occorrenze come gruppo di lettere ===
  "il"   : 3
  "re"   : 5
  "mare" : 2

=== Occorrenze come parola intera ===
  "il"   : 3
  "re"   : 2
  "mare" : 2

=== Sovrapposte o separate ===
  "aa" in "aaaa": sovrapposte 3, separate 2
```

### 040-problema-validazione-email
*(output dipendente dall'input – esempio con un indirizzo per ogni regola)*
```
=== ISCRIZIONE ALLA NEWSLETTER ===
Email ("fine" per terminare): mario.rossi@gmail.com
  OK: indirizzo valido
Email ("fine" per terminare): mario rossi@gmail.com
  Rifiutato (regola 1): contiene spazi
Email ("fine" per terminare): mario.rossigmail.com
  Rifiutato (regola 2): deve contenere una sola '@'
Email ("fine" per terminare): mario@rossi@gmail.com
  Rifiutato (regola 2): deve contenere una sola '@'
Email ("fine" per terminare): @gmail.com
  Rifiutato (regola 3): manca il nome prima della '@'
Email ("fine" per terminare): mario@gmail
  Rifiutato (regola 4): manca il '.' nel dominio dopo la '@'
Email ("fine" per terminare): mario@.com
  Rifiutato (regola 5): '.' in posizione non ammessa nel dominio
Email ("fine" per terminare): mario@gmail.
  Rifiutato (regola 5): '.' in posizione non ammessa nel dominio
Email ("fine" per terminare): a.b@scuola.edu.it
  OK: indirizzo valido
Email ("fine" per terminare): fine

Indirizzi accettati: 2, rifiutati: 7
```

### 050-problema-filtro-commenti
*(output dipendente dall'input – esempio con tre commenti)*
```
=== FORUM DELLA CLASSE ===
Commento (riga vuota per terminare): Che compito STUPIDO, sei proprio uno stupido
  Pubblicato con 2 parole oscurate: Che compito *******, sei proprio uno *******
Commento (riga vuota per terminare): Bella lezione oggi!
  Pubblicato: Bella lezione oggi!
Commento (riga vuota per terminare): Che schifo... non fare l'Idiota
  Pubblicato con 2 parole oscurate: Che ******... non fare l'******
Commento (riga vuota per terminare): 
Fine moderazione.
```

### 060-problema-catalogo-biblioteca
*(output dipendente dall'input – esempio con quattro ricerche)*
```
=== CATALOGO DELLA BIBLIOTECA (8 titoli) ===
Parola chiave (riga vuota per uscire): calvino
  Il barone rampante             Italo Calvino       1957  disponibile
  Le citta' invisibili           Italo Calvino       1972  in prestito
  Il sentiero dei nidi di ragno  Italo Calvino       1947  disponibile
  Marcovaldo                     Italo Calvino       1963  disponibile
  4 risultati
Parola chiave (riga vuota per uscire): PROMESSI
  I promessi sposi               Alessandro Manzoni  1840  disponibile
  1 risultato
Parola chiave (riga vuota per uscire): il
  Il barone rampante             Italo Calvino       1957  disponibile
  Le citta' invisibili           Italo Calvino       1972  in prestito
  Il sentiero dei nidi di ragno  Italo Calvino       1947  disponibile
  Il fu Mattia Pascal            Luigi Pirandello    1904  in prestito
  4 risultati
Parola chiave (riga vuota per uscire): Eco
  Nessun libro trovato per "Eco".
Parola chiave (riga vuota per uscire): 
Buona lettura!
```

### 070-problema-nome-ed-estensione
```
Cartella             Nome               Est.  Tipo
compiti/3B/rossi     relazione.finale   docx  documento
compiti/3B/rossi     grafico            png   immagine
compiti/3B/bianchi   esercizio1         c     codice
progetti/sito        index              html  codice
progetti/sito        logo               jpg   immagine
(radice)             README             -     altro
progetti             .gitignore         -     altro
compiti/4A/verdi     tesina             pdf   documento

Riepilogo:  documento 2  immagine 2  codice 2  altro 2
```

### 080-problema-smistamento-messaggi
```
"Vorrei prenotare un colloquio per parlare dei voti di mio figlio"
   parole trovate: didattica 2, amministrazione 0, servizi 0 -> Didattica

"Ho fatto il bonifico per la gita ma non vedo il pagamento"
   parole trovate: didattica 0, amministrazione 2, servizi 0 -> Amministrazione

"Lo SCUOLABUS di via Roma passa in ritardo"
   parole trovate: didattica 0, amministrazione 0, servizi 1 -> Servizi

"Chiedo il rimborso della mensa per i giorni di assenza"
   parole trovate: didattica 1, amministrazione 1, servizi 1 -> Segreteria generale

"Quando escono le pagelle del primo quadrimestre?"
   parole trovate: didattica 1, amministrazione 0, servizi 0 -> Didattica

"Buongiorno, a chi posso chiedere informazioni?"
   parole trovate: didattica 0, amministrazione 0, servizi 0 -> Segreteria generale

=== MESSAGGI PER UFFICIO ===
  Didattica            2
  Amministrazione      1
  Servizi              1
  Segreteria generale  2
```

---

## Errori comuni da evitare

**Usare il risultato di `strstr` come un numero**
```c
if (strstr(s, "USB") > 0)        /* SBAGLIATO: è un puntatore */
if (strstr(s, "USB") != NULL)    /* corretto */
```

**Dimenticare che non trovare restituisce `-1` (o `NULL`)**
```c
pos = prima_posizione(s, '@');
nome[pos] = '\0';                /* se pos vale -1 si scrive fuori dall'array */
```

**Ripartire dalla stessa posizione**
```c
posizione = cerca_da(testo, parola, posizione);   /* ciclo infinito */
posizione = cerca_da(testo, parola, posizione + 1);
```

**Confrontare testo e chiave con maiuscole diverse**
```c
strstr("Italo Calvino", "calvino")   /* NULL: 'C' e 'c' sono diversi */
```

**Cercare il primo punto per l'estensione**
```c
/* "relazione.finale.docx": l'estensione inizia dopo l'ULTIMO punto */
```

---

## Concetti collegati

- `02-libreria-string-h` → `strlen`, `strcmp`, `strncmp`
- `04-caratteri-e-conversioni` → `tolower` per le copie in minuscolo
- `05-puntatori` → che cosa restituiscono davvero `strchr` e `strstr`

---

## Esercizi proposti

1. Scrivi `int conta_parole(const char s[])` che conta le parole di una frase
   (sequenze di lettere separate da altri caratteri).

2. In `040-problema-validazione-email.c` aggiungi la regola: il dominio deve
   terminare con un'estensione di almeno 2 lettere (`.it`, `.com`).

3. In `050-problema-filtro-commenti.c` oscura solo le parole intere (vedi
   `030-conta-occorrenze.c`) e spiega con un esempio quando questa versione è
   migliore di quella attuale e quando è peggiore.

4. In `060-problema-catalogo-biblioteca.c` permetti di cercare anche per anno:
   se la chiave è un numero di 4 cifre, confrontala con `anni[]`.

5. (Avanzato) Scrivi `void sostituisci(char s[], const char vecchia[], const char nuova[])`
   che sostituisce tutte le occorrenze quando `vecchia` e `nuova` hanno la
   stessa lunghezza.
