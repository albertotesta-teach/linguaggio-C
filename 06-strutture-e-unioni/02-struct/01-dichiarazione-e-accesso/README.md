# 01 – Dichiarazione e accesso

## Concetto

Una **struct** raggruppa in una sola variabile dati di tipo diverso che
descrivono la stessa cosa. Ogni dato è un **campo** (membro).

```c
struct studente {           /* dichiarazione del tipo */
    char nome[20];
    char classe[4];
    double media;
};                          /* punto e virgola obbligatorio */

struct studente s;          /* una variabile del nuovo tipo */
strcpy(s.nome, "Giulia");   /* operatore punto: accesso a un campo */
s.media = 7.8;
```

Un campo si usa come una variabile del suo tipo: `s.nome` è un array di
`char`, `s.media` un `double`.

### Inizializzazione

| Forma | Esempio | Campi non indicati |
|-------|---------|--------------------|
| in ordine | `{1024, "Bianchi Sara", 12, 25.50}` | a zero |
| con il nome | `{.numero = 1025, .credito = 10.00}` | a zero |
| tutto a zero | `{0}` | — |

La lista tra graffe vale solo nella dichiarazione; dopo si assegna un campo
alla volta.

### typedef e struct: un tipo davvero nuovo

```c
typedef struct {
    double valore;
} Euro;

typedef struct {
    double valore;
} Chilometri;

Euro prezzo = {1.79};
Chilometri distanza = {290};
prezzo = distanza;      /* errore: tipi incompatibili */
```

Nel sottocapitolo `01-typedef` `Euro` e `Chilometri` erano due nomi dello
stesso `double`. Ogni `struct` invece è un tipo diverso da tutti gli altri,
anche con gli stessi campi. Da qui in poi il corso usa la forma
`typedef struct { ... } Nome;`, con l'iniziale maiuscola.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-tipo-con-campi.c` | `struct studente`, operatore punto, `sizeof` dei campi e della struct |
| `020-inizializzazione.c` | Inizializzazione in ordine, con il nome dei campi e a zero |
| `030-typedef-struct.c` | `Euro` e `Chilometri` come struct: l'assegnamento tra tipi diversi non compila |
| `040-problema-scheda-libro.c` | Prestiti e restituzioni sulla scheda di un libro |
| `040-problema-scheda-libro-analisi.md` | Analisi di `040-problema-scheda-libro.c` |
| `050-problema-distanza-gps.c` | Distanza tra due `Punto` GPS e tempo a piedi |
| `050-problema-distanza-gps-analisi.md` | Analisi di `050-problema-distanza-gps.c` |
| `060-problema-durata-lezioni.c` | Durata e controlli delle lezioni con due `Orario` |
| `060-problema-durata-lezioni-analisi.md` | Analisi di `060-problema-durata-lezioni.c` |
| `070-problema-somma-frazioni.c` | Somma di due `Frazione` ridotta ai minimi termini |
| `070-problema-somma-frazioni-analisi.md` | Analisi di `070-problema-somma-frazioni.c` |
| `080-problema-carta-imbarco.c` | Controllo di una `CartaImbarco` rispetto al `Volo` della classe |
| `080-problema-carta-imbarco-analisi.md` | Analisi di `080-problema-carta-imbarco.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-tipo-con-campi 010-tipo-con-campi.c
./010-tipo-con-campi

gcc -Wall -Wextra -o 020-inizializzazione 020-inizializzazione.c
./020-inizializzazione

gcc -Wall -Wextra -o 030-typedef-struct 030-typedef-struct.c
./030-typedef-struct

gcc -Wall -Wextra -o 040-problema-scheda-libro 040-problema-scheda-libro.c
./040-problema-scheda-libro

gcc -Wall -Wextra -o 050-problema-distanza-gps 050-problema-distanza-gps.c -lm
./050-problema-distanza-gps

gcc -Wall -Wextra -o 060-problema-durata-lezioni 060-problema-durata-lezioni.c
./060-problema-durata-lezioni

gcc -Wall -Wextra -o 070-problema-somma-frazioni 070-problema-somma-frazioni.c
./070-problema-somma-frazioni

gcc -Wall -Wextra -o 080-problema-carta-imbarco 080-problema-carta-imbarco.c
./080-problema-carta-imbarco
```

---

## Output atteso

### 010-tipo-con-campi
```
=== I CAMPI ===
  Giulia Ferri   classe 3B  media 7.8
  Marco Riva     classe 3B  media 6.4

Dopo il recupero: Marco Riva ha media 6.9
Iniziale del nome di Giulia Ferri: G

=== DIMENSIONI ===
  sizeof(primo.nome)   = 20
  sizeof(primo.classe) = 4
  sizeof(primo.media)  = 8
  sizeof(struct studente) = 32  (somma dei campi piu' eventuale spazio di allineamento)
```

### 020-inizializzazione
```
  Numero  Intestatario    Pasti  Credito
    1024  Bianchi Sara       12    25.50
    1025                      0    10.00   <- intestatario vuoto, pasti 0
       0                      0     0.00   <- tutto a zero

Dopo gli assegnamenti: tessera 2000, credito 5.00
```

### 030-typedef-struct
```
Gita a Genova per 46 studenti (stesso tipo: Genova, 46)
Distanza 290 km, consumo 3.5 km/l, gasolio 1.79 euro/l
Costo del carburante: 148.31 euro
Per persona: 3.22 euro

Euro, Chilometri e KmPerLitro hanno lo stesso campo double,
ma sono tre tipi diversi: assegnarne uno a un altro e' un errore.
```

### 040-problema-scheda-libro
*(output dipendente dall'input – esempio di sessione)*
```
Scheda aperta: Il sentiero dei nidi di ragno
Comando (P prestito, R restituzione, S scheda, Q fine): S
  Titolo:      Il sentiero dei nidi di ragno
  Autore:      Italo Calvino (1947)
  Copie:       3, in prestito 1, disponibili 2
Comando (P prestito, R restituzione, S scheda, Q fine): P
  Prestito registrato. Copie disponibili: 1
Comando (P prestito, R restituzione, S scheda, Q fine): P
  Prestito registrato. Copie disponibili: 0
Comando (P prestito, R restituzione, S scheda, Q fine): P
  Nessuna copia disponibile.
Comando (P prestito, R restituzione, S scheda, Q fine): R
  Restituzione registrata. Copie disponibili: 1
Comando (P prestito, R restituzione, S scheda, Q fine): S
  Titolo:      Il sentiero dei nidi di ragno
  Autore:      Italo Calvino (1947)
  Copie:       3, in prestito 2, disponibili 1
Comando (P prestito, R restituzione, S scheda, Q fine): Q
Prestiti registrati in questa sessione: 2
```

### 050-problema-distanza-gps
*(output dipendente dall'input – dalla scuola al museo)*
```
Partenza (latitudine longitudine): 44.9126 8.6157
Arrivo   (latitudine longitudine): 44.9070 8.6040

Da (44.9126, 8.6157) a (44.9070, 8.6040)
Distanza in linea d'aria: 1.11 km
Tempo a piedi stimato:    0 h 19 min
```

*(output dipendente dall'input – coordinate non valide)*
```
Partenza (latitudine longitudine): 95 10
Arrivo   (latitudine longitudine): 44.9 8.6
Coordinate non valide.
```

### 060-problema-durata-lezioni
*(output dipendente dall'input – esempio di sessione)*
```
Lezione 1 - inizio (ore minuti, 0 0 per finire): 8 0
Lezione 1 - fine   (ore minuti): 8 55
  08:00 - 08:55  55 minuti
Lezione 2 - inizio (ore minuti, 0 0 per finire): 8 55
Lezione 2 - fine   (ore minuti): 9 50
  08:55 - 09:50  55 minuti
Lezione 3 - inizio (ore minuti, 0 0 per finire): 9 45
Lezione 3 - fine   (ore minuti): 11 0
  09:45 - 11:00  75 minuti  (troppo lunga)  (si sovrappone alla precedente)
Lezione 4 - inizio (ore minuti, 0 0 per finire): 11 0
Lezione 4 - fine   (ore minuti): 10 30
  La fine deve venire dopo l'inizio.
Lezione 4 - inizio (ore minuti, 0 0 per finire): 12 0
Lezione 4 - fine   (ore minuti): 12 40
  12:00 - 12:40  40 minuti  (troppo corta)
Lezione 5 - inizio (ore minuti, 0 0 per finire): 25 0
Lezione 5 - fine   (ore minuti): 13 0
  Orario non valido.
Lezione 5 - inizio (ore minuti, 0 0 per finire): 0 0
Lezioni registrate: 4, tempo totale 3 h 45 min
```

### 070-problema-somma-frazioni
*(output dipendente dall'input – esempio di sessione)*
```
Due frazioni (a/b c/d, 0/0 per finire): 1/2 1/3
  1/2 + 1/3 = 5/6
Due frazioni (a/b c/d, 0/0 per finire): 3/4 5/12
  3/4 + 5/12 = 7/6  = 1 e 1/6
Due frazioni (a/b c/d, 0/0 per finire): 2/3 4/3
  2/3 + 4/3 = 2/1  = 2
Due frazioni (a/b c/d, 0/0 per finire): 1/0 1/2
  Frazioni non valide.
Due frazioni (a/b c/d, 0/0 per finire): 0/0
```

### 080-problema-carta-imbarco
*(output dipendente dall'input – esempio di sessione)*
```
Volo FR1452, gate 14, chiusura imbarco 09:35
Cognome (FINE per terminare): Rossi
Ora attuale, volo e posto (hh mm volo posto): 9 10 FR1452 12A
  Rossi: passa, posto 12A.
Cognome (FINE per terminare): Bianchi
Ora attuale, volo e posto (hh mm volo posto): 9 12 FR1425 14C
  Bianchi: volo sbagliato (FR1425 invece di FR1452).
Cognome (FINE per terminare): Verdi
Ora attuale, volo e posto (hh mm volo posto): 9 20 FR1452 15F
  Verdi: passa, posto 15F.
Cognome (FINE per terminare): Neri
Ora attuale, volo e posto (hh mm volo posto): 9 36 FR1452 16B
  Neri: imbarco chiuso.
Cognome (FINE per terminare): FINE
Studenti imbarcati: 2
```

---

## Errori comuni da evitare

**Dimenticare il punto e virgola dopo la dichiarazione**
```c
struct studente {
    char nome[20];
}                       /* errore: manca ; */
```

**Usare il nome del tipo al posto della variabile**
```c
Studente.media = 7;     /* errore: Studente è un tipo */
s.media = 7;            /* corretto */
```

**Assegnare una stringa a un campo array con =**
```c
s.nome = "Giulia";          /* errore: nome è un array */
strcpy(s.nome, "Giulia");   /* corretto */
```

**Usare la lista tra graffe dopo la dichiarazione**
```c
Orario o;
o = {8, 30};            /* errore */
o.ore = 8;              /* corretto: un campo alla volta */
o.minuti = 30;
```

**Leggere una struct non inizializzata**
```c
Orario fine;            /* campi con valori casuali */
Orario fine = {0, 0};   /* corretto se un campo potrebbe non essere letto */
```

---

## Concetti collegati

- `01-typedef` → typedef sui tipi base: un nome, non un tipo nuovo
- `02-assegnamento-e-confronto` → copiare e confrontare struct intere
- `03-array-di-struct` → tabelle di record
- `03-struct-e-funzioni` → struct come parametri e puntatori a struct

---

## Esercizi proposti

1. In `010-tipo-con-campi.c` aggiungi il campo `int assenze` e stampa gli
   studenti con più di 10 assenze.

2. In `040-problema-scheda-libro.c` aggiungi il comando `A n` per
   acquistare n nuove copie.

3. In `060-problema-durata-lezioni.c` stampa anche l'orario di inizio della
   lezione più lunga.

4. In `070-problema-somma-frazioni.c` aggiungi la differenza e il prodotto
   delle due frazioni.

5. (Avanzato) In `050-problema-distanza-gps.c` leggi un terzo punto e
   calcola la lunghezza del percorso partenza → tappa → arrivo.
