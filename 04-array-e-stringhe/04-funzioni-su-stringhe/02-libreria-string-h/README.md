# 02 – La libreria string.h

## Concetto

Le funzioni scritte a mano nella sezione 01 esistono già nella libreria
standard. Per usarle si include l'header:

```c
#include <string.h>
```

| Funzione | Che cosa fa | Corrisponde a |
|----------|-------------|---------------|
| `strlen(s)` | lunghezza, `'\0'` escluso | `lunghezza(s)` |
| `strcpy(dest, sorg)` | copia | `copia(dest, sorg)` |
| `strncpy(dest, sorg, n)` | copia al massimo `n` caratteri | `copia_limitata` (quasi) |
| `strcat(dest, sorg)` | concatena | `concatena(dest, sorg)` |
| `strncat(dest, sorg, n)` | aggiunge al massimo `n` caratteri | `concatena_limitata` (quasi) |
| `strcmp(a, b)` | `< 0`, `0`, `> 0` | `confronta(a, b)` |
| `strncmp(a, b, n)` | confronta solo i primi `n` caratteri | — |

### `strlen` e `size_t`

`strlen` restituisce un `size_t`, un intero senza segno. Si stampa con `%zu`
oppure si converte in `int` con un cast:

```c
printf("%zu\n", strlen(s));
n = (int) strlen(s);
```

`strlen` e `sizeof` sono cose diverse: `strlen` conta i caratteri scritti,
`sizeof` dà le celle dell'array (e funziona solo dove l'array è dichiarato,
non su un parametro di funzione).

### `strcpy` e `strcat` non controllano lo spazio

Come le versioni scritte a mano, scrivono oltre la fine di `dest` se il testo
non entra. Le versioni con `n` aiutano, ma hanno regole diverse:

| Funzione | Significato di `n` | Aggiunge sempre `'\0'`? |
|----------|--------------------|------------------------|
| `strncpy` | massimo numero di caratteri copiati | **no**: se `sorg` è lunga va aggiunto a mano |
| `strncat` | massimo numero di caratteri **aggiunti** | sì |

```c
strncpy(dest, sorg, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';                          /* obbligatorio */

strncat(dest, sorg, sizeof(dest) - strlen(dest) - 1);   /* spazio libero */
```

### `strcmp`: conta solo il segno

Lo standard garantisce solo il segno del risultato: si confronta sempre con 0.

```c
if (strcmp(a, b) == 0)        /* uguali */
if (strcmp(a, b) < 0)         /* a viene prima */
if (strncmp(s, "+39", 3) == 0)   /* s inizia con "+39" */
```

Il C standard non ha un confronto che ignori le maiuscole.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-strlen-e-strcpy.c` | `strlen` e `sizeof`, `strcpy`, `strncpy` e il `'\0'` da aggiungere |
| `020-strcat-e-strncat.c` | `strcat`, `strncat` con il calcolo dello spazio libero |
| `030-strcmp-e-strncmp.c` | Uguaglianza, ordine alfabetico, prefisso con `strncmp` |
| `040-problema-indirizzo-postale.c` | Etichetta di spedizione con validazione di CAP e provincia |
| `040-problema-indirizzo-postale-analisi.md` | Analisi di `040-problema-indirizzo-postale.c` |
| `050-problema-cambio-password.c` | Cambio password: verifica, requisiti, conferma |
| `050-problema-cambio-password-analisi.md` | Analisi di `050-problema-cambio-password.c` |
| `060-problema-login.c` | Accesso con utenti e password in array paralleli e blocco dell'account |
| `060-problema-login-analisi.md` | Analisi di `060-problema-login.c` |
| `070-problema-prefissi-telefonici.c` | Costo delle chiamate per zona, con il prefisso più lungo |
| `070-problema-prefissi-telefonici-analisi.md` | Analisi di `070-problema-prefissi-telefonici.c` |
| `080-problema-elezione-rappresentanti.c` | Spoglio delle schede: valide, bianche, nulle, eletti |
| `080-problema-elezione-rappresentanti-analisi.md` | Analisi di `080-problema-elezione-rappresentanti.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-strlen-e-strcpy 010-strlen-e-strcpy.c
./010-strlen-e-strcpy

gcc -Wall -Wextra -o 020-strcat-e-strncat 020-strcat-e-strncat.c
./020-strcat-e-strncat

gcc -Wall -Wextra -o 030-strcmp-e-strncmp 030-strcmp-e-strncmp.c
./030-strcmp-e-strncmp

gcc -Wall -Wextra -o 040-problema-indirizzo-postale 040-problema-indirizzo-postale.c
./040-problema-indirizzo-postale

gcc -Wall -Wextra -o 050-problema-cambio-password 050-problema-cambio-password.c
./050-problema-cambio-password

gcc -Wall -Wextra -o 060-problema-login 060-problema-login.c
./060-problema-login

gcc -Wall -Wextra -o 070-problema-prefissi-telefonici 070-problema-prefissi-telefonici.c
./070-problema-prefissi-telefonici

gcc -Wall -Wextra -o 080-problema-elezione-rappresentanti 080-problema-elezione-rappresentanti.c
./080-problema-elezione-rappresentanti
```

---

## Output atteso

### 010-strlen-e-strcpy
```
=== strlen ===
strlen("Alessandria") = 11 caratteri
sizeof(citta)  = 12 celle (caratteri + '\0')
sizeof(copia)  = 30 celle, anche se ancora vuoto

=== strcpy ===
copia = "Alessandria"
dopo strcpy(copia, "Asti"): "Asti" (4 caratteri)

=== strncpy ===
sigla = "AL"
breve = "Alessan" (troncata a 7 caratteri)
Senza breve[7] = '\0' la stringa non avrebbe terminatore.
```

### 020-strcat-e-strncat
```
=== strcat ===
oggetto = "Classe 3B: Informatica" (22 su 39 caratteri)

=== strncat ===
Spazio libero prima: 17 caratteri
oggetto = "Classe 3B: Informatica, verifica scritt"
lunghezza 39 su 39: testo troncato
```

### 030-strcmp-e-strncmp
```
=== strcmp(codice, "ROMA-0412") ===
  ROMA-0412  -> uguale
  MILA-0398  -> diverso (viene prima)
  ROMA-0177  -> diverso (viene prima)
  NAPO-0250  -> diverso (viene prima)
  roma-0412  -> diverso (viene dopo)
  ROMA-0412  -> uguale

=== prenotazioni per ROMA (strncmp sui primi 4 caratteri) ===
  ROMA-0412
  ROMA-0177
  ROMA-0412

Primo codice in ordine alfabetico: MILA-0398
(le maiuscole vengono prima delle minuscole: "roma-0412" e' l'ultimo)
```

### 040-problema-indirizzo-postale
*(output dipendente dall'input – esempio con due dati da correggere e una riga troppo lunga)*
```
=== ETICHETTA DI SPEDIZIONE ===
Destinatario: Mario Rossi
Via e numero civico: Via Vittorio Emanuele II 12
CAP (5 cifre): 151
  CAP non valido.
CAP (5 cifre): 15020
Comune: San Giorgio Monferrato
Provincia (sigla di 2 lettere): ALE
  Sigla non valida.
Provincia (sigla di 2 lettere): AL

+--------------------------------+
| Mario Rossi                    |
| Via Vittorio Emanuele II 12    |
| 15020 San Giorgio Monferrato ( |
+--------------------------------+
Attenzione: 1 riga troppo lunga, controllare l'etichetta.
```

### 050-problema-cambio-password
*(output dipendente dall'input – esempio con errori in ogni fase)*
```
=== CAMBIO PASSWORD ===
Password attuale: sole2024
  Password errata (1 di 3 tentativi).
Password attuale: Sole2024
Nuova password (8-20 caratteri): abc
  Lunghezza non valida: 3 caratteri.
Nuova password (8-20 caratteri): Sole2024
  La nuova password deve essere diversa da quella attuale.
Nuova password (8-20 caratteri): Luna2025!
Conferma la nuova password: Luna2025
  Le due password non coincidono, ricomincia.
Nuova password (8-20 caratteri): Luna2025!
Conferma la nuova password: Luna2025!
Password cambiata (9 caratteri).
```

### 060-problema-login
*(output dipendente dall'input – esempio con un accesso riuscito e un account bloccato)*
```
=== GESTIONALE DEL LABORATORIO ===
Utente ("fine" per chiudere): mrossi
Password: Rossi#77
  Benvenuto, mrossi!
Utente ("fine" per chiudere): lbianchi
Password: bianchi99
  Credenziali non valide.
Utente ("fine" per chiudere): pippo
Password: x
  Credenziali non valide.
Utente ("fine" per chiudere): lbianchi
Password: Bianchi99
  Credenziali non valide.
Utente ("fine" per chiudere): lbianchi
Password: bianchi.99
  Credenziali non valide.
  Troppi errori: l'account lbianchi e' stato bloccato.
Utente ("fine" per chiudere): lbianchi
Password: Bianchi.99
  Account bloccato: rivolgersi al tecnico.
Utente ("fine" per chiudere): fine

Accessi riusciti: 1
Stato degli account:
  admin     attivo   (errori: 0)
  mrossi    attivo   (errori: 0)
  lbianchi  BLOCCATO (errori: 3)
  gverdi    attivo   (errori: 0)
```

### 070-problema-prefissi-telefonici
```
=== DETTAGLIO DELLE CHIAMATE ===
  Numero          Zona             Min     Costo
  +390131220145   Italia fisso      12      0.24
  +393471234567   Italia mobile      5      0.25
  +33142685300    Francia            8      0.72
  +41223456789    Svizzera          20      3.00
  +12125550198    USA/Canada        15      2.70
  +393289876543   Italia mobile      3      0.15
  +81312345678    ?                 10         -
  +4930123456     Germania           6      0.54
  +390112345678   Italia fisso      25      0.50

=== TOTALE PER ZONA ===
  Italia fisso     37 min    0.74 euro
  Italia mobile     8 min    0.40 euro
  Francia           8 min    0.72 euro
  Svizzera         20 min    3.00 euro
  Germania          6 min    0.54 euro
  USA/Canada       15 min    2.70 euro
  Totale da addebitare: 8.10 euro
  1 chiamata con prefisso non in tariffario: da verificare
```

### 080-problema-elezione-rappresentanti
```
=== SPOGLIO ===
  scheda  8 nulla: "neri giulia"
  scheda 16 nulla: "Verdi Paolo"
  scheda 20 nulla: "Neri Giula"
Schede: 20  valide: 15  bianche: 2  nulle: 3

=== RISULTATI ===
  Bianchi Luca    2 voti   13.3%
  Neri Giulia     5 voti   33.3%
  Russo Marco     4 voti   26.7%
  Gallo Sara      4 voti   26.7%

Eletto: Neri Giulia
Secondo posto con 4 voti: Russo Marco, Gallo Sara
Pareggio: serve un ballottaggio per il secondo rappresentante.
```

---

## Errori comuni da evitare

**Dimenticare `#include <string.h>`**
```c
n = strlen(s);     /* senza l'include: avviso o errore "implicit declaration" */
```

**`strncpy` senza terminatore**
```c
char sigla[4];
strncpy(sigla, "Alessandria", 4);    /* sigla = "Ales" senza '\0' */
```

**Passare a `strncat` la dimensione di `dest`**
```c
strncat(dest, sorg, sizeof(dest));                     /* SBAGLIATO */
strncat(dest, sorg, sizeof(dest) - strlen(dest) - 1);  /* corretto */
```

**Confrontare il risultato di `strcmp` con 1 o -1**
```c
if (strcmp(a, b) == -1)    /* può fallire: lo standard garantisce solo il segno */
if (strcmp(a, b) < 0)      /* corretto */
```

**Usare `strcmp` come valore vero/falso**
```c
if (strcmp(a, b))          /* vero quando sono DIVERSE */
```

**Assegnare una stringa con `=`**
```c
nome = "Mario";            /* errore: si usa strcpy(nome, "Mario") */
```

---

## Concetti collegati

- `01-funzioni-scritte-a-mano` → come funzionano internamente queste funzioni
- `03-ricerca-nelle-stringhe` → `strchr`, `strrchr`, `strstr`
- `05-array-di-stringhe` → `strcmp` e `strcpy` su elenchi di parole

---

## Esercizi proposti

1. In `010-strlen-e-strcpy.c` prova a togliere la riga `breve[7] = '\0';` e
   spiega perché il programma potrebbe stampare caratteri strani.

2. In `050-problema-cambio-password.c` aggiungi il requisito "almeno una
   cifra" scrivendo una funzione `contiene_cifra`.

3. In `060-problema-login.c` aggiungi il comando `sblocca` che, dopo la
   password di `admin`, azzera gli errori di un account.

4. In `070-problema-prefissi-telefonici.c` aggiungi uno scatto alla risposta
   di 10 centesimi per le chiamate verso i cellulari.

5. (Avanzato) In `080-problema-elezione-rappresentanti.c` accetta anche le
   schede con il cognome soltanto, quando un solo candidato ha quel cognome
   (suggerimento: `strncmp` e `strlen`).
