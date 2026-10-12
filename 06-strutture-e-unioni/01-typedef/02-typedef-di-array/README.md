# 02 – Typedef di array

## Concetto

`typedef` può dare un nome a un **array di dimensione fissa**. La regola è
la stessa: la dichiarazione di una variabile con `typedef` davanti.

```c
typedef char Targa[8];          /* 7 caratteri + '\0' */
typedef int Settimana[7];       /* un valore per giorno */

Targa auto_preside = "GA482KM";      /* come char auto_preside[8] */
Settimana ingressi = {84, 91, 88, 79, 73, 12, 0};
```

Una variabile `Targa` è un vero array: `sizeof(Targa)` vale 8, si
inizializza con un letterale e si legge con l'indice. Valgono tutte le
regole degli array:

| Operazione | Con un tipo array |
|------------|-------------------|
| copiare | `strcpy(a, b)` o un ciclo, mai `a = b` |
| confrontare | `strcmp(a, b)` o un ciclo, mai `a == b` |
| passare a una funzione | arriva l'indirizzo del primo elemento |

### Il tipo array come parametro

```c
int totale(const Settimana s);      /* equivale a const int *s */
void azzera_festivi(Settimana s);   /* modifica l'array del chiamante */
```

Il nome rende leggibile il prototipo e scrive la dimensione in un solo
punto, ma dentro la funzione `s` è un puntatore: `sizeof(s)` darebbe 8
(gcc e clang lo segnalano con un avviso). Il numero di elementi si prende
dalla costante usata nella typedef.

### Tipi costruiti su altri tipi

```c
typedef int Settimana[GIORNI];
typedef Settimana Mese[SETTIMANE];      /* come int[SETTIMANE][GIORNI] */

Targa riservati[4];                      /* come char[4][8] */
typedef char Griglia[3][3];              /* matrice con un nome */
```

Ogni riga di un `Mese` è una `Settimana`: si passa a `totale(mese[s])`.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-tipo-array.c` | `Targa` e `Settimana`: inizializzazione, `sizeof`, copia con `strcpy` |
| `020-array-come-parametro.c` | `const Settimana` e `Settimana` come parametri; la funzione modifica il chiamante |
| `030-matrici-con-nome.c` | `typedef Settimana Prestiti[3]` e un array di `Targa` |
| `040-problema-controllo-accessi.c` | Sbarra del parcheggio: formato e autorizzazione della `Targa` |
| `040-problema-controllo-accessi-analisi.md` | Analisi di `040-problema-controllo-accessi.c` |
| `050-problema-presenze-palestra.c` | Presenze di un mese: `Mese` di `Settimana` e totali per giorno |
| `050-problema-presenze-palestra-analisi.md` | Analisi di `050-problema-presenze-palestra.c` |
| `060-problema-tris.c` | Partita a tris su una `Griglia` 3 × 3 |
| `060-problema-tris-analisi.md` | Analisi di `060-problema-tris.c` |
| `070-problema-codici-aule.c` | Comporre e scomporre i `Codice` delle aule |
| `070-problema-codici-aule-analisi.md` | Analisi di `070-problema-codici-aule.c` |
| `080-problema-pianta-sala-esame.c` | Candidati a scacchiera in una `Pianta` dell'aula magna |
| `080-problema-pianta-sala-esame-analisi.md` | Analisi di `080-problema-pianta-sala-esame.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-tipo-array 010-tipo-array.c
./010-tipo-array

gcc -Wall -Wextra -o 020-array-come-parametro 020-array-come-parametro.c
./020-array-come-parametro

gcc -Wall -Wextra -o 030-matrici-con-nome 030-matrici-con-nome.c
./030-matrici-con-nome

gcc -Wall -Wextra -o 040-problema-controllo-accessi 040-problema-controllo-accessi.c
./040-problema-controllo-accessi

gcc -Wall -Wextra -o 050-problema-presenze-palestra 050-problema-presenze-palestra.c
./050-problema-presenze-palestra

gcc -Wall -Wextra -o 060-problema-tris 060-problema-tris.c
./060-problema-tris

gcc -Wall -Wextra -o 070-problema-codici-aule 070-problema-codici-aule.c
./070-problema-codici-aule

gcc -Wall -Wextra -o 080-problema-pianta-sala-esame 080-problema-pianta-sala-esame.c
./080-problema-pianta-sala-esame
```

---

## Output atteso

### 010-tipo-array
```
=== TARGHE ===
  Preside:     GA482KM  (prima lettera G, 7 caratteri)
  Vicepreside: FT109RS
  sizeof(Targa) = 8 byte

=== INGRESSI DELLA SETTIMANA ===
    84  91  88  79  73  12   0
  Totale: 427 ingressi
  sizeof(Settimana) = 28 byte = 7 x sizeof(int)
```

### 020-array-come-parametro
```
Orario proposto:
  L  M  M  G  V  S  D
  6  8  6  7  5  4  2   totale 38 ore
  sizeof nel main: 28 byte; nelle funzioni s e' un indirizzo da 8 byte

Dopo azzera_festivi:
  L  M  M  G  V  S  D
  6  8  6  7  5  4  0   totale 36 ore
```

### 030-matrici-con-nome
```
=== PRESTITI DELLA SETTIMANA ===
  sizeof(Settimana) = 28, sizeof(Prestiti) = 84 byte
  Narrativa    90 prestiti
  Saggistica   33 prestiti
  Fumetti      80 prestiti

=== POSTI RISERVATI ===
  posto 1: EK301TZ
  posto 2: DM774PA
  posto 3: FH052LC
  posto 4: GB918RN
  DM774PA ha il posto 2
```

### 040-problema-controllo-accessi
*(output dipendente dall'input – esempio di sessione)*
```
Targa letta (FINE per terminare): EK301TZ
  EK301TZ: sbarra alzata.
Targa letta (FINE per terminare): AB123CD
  AB123CD: accesso negato.
Targa letta (FINE per terminare): ab123cd
  Lettura non valida, ripetere.
Targa letta (FINE per terminare): DM774PAX
  Lettura non valida, ripetere.
Targa letta (FINE per terminare): GB918RN
  GB918RN: sbarra alzata.
Targa letta (FINE per terminare): FINE

Ingressi consentiti: 2, negati: 1
```

### 050-problema-presenze-palestra
```
  Settimana   lun  mar  mer  gio  ven  sab  Totale
          1    34   41   28   39   45   18     205
          2    31   44   30   42   47   22     216
          3    29   39   33   40   51   15     207
          4    36   46   27   43   49   20     221
       Mese   130  170  118  164  192   75     849

Settimana piu' frequentata: la 4 (221 presenze)
Giorno della settimana con piu' presenze nel mese: ven (192)
Giorno piu' affollato del mese: ven della settimana 3 (51 presenze)
```

### 060-problema-tris
*(output dipendente dall'input – partita vinta da X)*
```
     |   |  
  ---+---+---
     |   |  
  ---+---+---
     |   |  
Giocatore X, riga e colonna: 2 2
     |   |  
  ---+---+---
     | X |  
  ---+---+---
     |   |  
Giocatore O, riga e colonna: 1 1
   O |   |  
  ---+---+---
     | X |  
  ---+---+---
     |   |  
Giocatore X, riga e colonna: 2 2
  Casella occupata, ripetere.
Giocatore X, riga e colonna: 1 3
   O |   | X
  ---+---+---
     | X |  
  ---+---+---
     |   |  
Giocatore O, riga e colonna: 4 1
  Fuori dalla griglia, ripetere.
Giocatore O, riga e colonna: 1 2
   O | O | X
  ---+---+---
     | X |  
  ---+---+---
     |   |  
Giocatore X, riga e colonna: 3 1
   O | O | X
  ---+---+---
     | X |  
  ---+---+---
   X |   |  
Tris! Vince il giocatore X.
```

### 070-problema-codici-aule
*(output dipendente dall'input – esempio di sessione)*
```
Codici delle aule:
  A0-03  (28 posti)
  A1-12  (30 posti)
  A1-14  (24 posti)
  B2-07  (26 posti)
  B2-09  (32 posti)
  C0-01  (60 posti)
Codice da cercare (FINE per terminare): B2-07
  Edificio B, piano 2, aula 7: 26 posti.
Codice da cercare (FINE per terminare): A1-14
  Edificio A, piano 1, aula 14: 24 posti.
Codice da cercare (FINE per terminare): A1-15
  Edificio A, piano 1, aula 15: aula inesistente.
Codice da cercare (FINE per terminare): B2_07
  Codice non valido.
Codice da cercare (FINE per terminare): C0-1
  Codice non valido.
Codice da cercare (FINE per terminare): FINE
```

### 080-problema-pianta-sala-esame
*(output dipendente dall'input – 12 candidati)*
```
Banchi disponibili a scacchiera: 17
Numero di candidati: 12

         CATTEDRA
  fila 1 C . C . C . C . 
  fila 2 . C . # . C . C 
  fila 3 C . C . # . C . 
  fila 4 . C . C . . . . 
  fila 5 # . . . . . . . 
  C = candidato, . = libero, # = banco rotto

Candidati sistemati: 12
```

*(output dipendente dall'input – 20 candidati)*
```
Banchi disponibili a scacchiera: 17
Numero di candidati: 20

         CATTEDRA
  fila 1 C . C . C . C . 
  fila 2 . C . # . C . C 
  fila 3 C . C . # . C . 
  fila 4 . C . C . C . C 
  fila 5 # . C . C . C . 
  C = candidato, . = libero, # = banco rotto

Candidati sistemati: 17
Serve una seconda aula per 3 candidati.
```

---

## Errori comuni da evitare

**Mettere la dimensione dalla parte sbagliata**
```c
typedef char[8] Targa;      /* errore di sintassi */
typedef char Targa[8];      /* corretto: la dimensione segue il nome */
```

**Assegnare un tipo array con =**
```c
Targa a = "AB123CD";
Targa b;
b = a;                      /* errore: un array non si assegna */
strcpy(b, a);               /* corretto */
```

**Usare sizeof sul parametro**
```c
int totale(const Settimana s)
{
    int n = sizeof(s) / sizeof(s[0]);   /* sbagliato: s è un puntatore */
    ...
}
```

**Dimenticare lo spazio per il terminatore**
```c
typedef char Targa[7];      /* "AB123CD" ha 7 lettere: manca il posto per '\0' */
typedef char Targa[8];      /* corretto */
```

**Copiare in una Targa una stringa troppo lunga**
```c
strcpy(targa, riga);                    /* pericoloso se riga ha più di 7 caratteri */
if (strlen(riga) == 7) {                /* corretto: prima si controlla */
    strcpy(targa, riga);
}
```

---

## Concetti collegati

- `04-array-e-stringhe` → array, matrici e stringhe a cui si dà un nome
- `05-puntatori/02-puntatori-e-array` → perché un array arriva alla funzione come indirizzo
- `01-alias-di-tipi-base` → typedef sui tipi base
- `02-struct` → raggruppare dati diversi, non solo elementi dello stesso tipo

---

## Esercizi proposti

1. In `010-tipo-array.c` aggiungi `typedef char CodiceFiscale[17];` e
   stampa la `sizeof`.

2. In `040-problema-controllo-accessi.c` accetta anche le targhe scritte in
   minuscolo, convertendole prima del controllo.

3. In `050-problema-presenze-palestra.c` scrivi
   `double media(const Settimana s)` e stampa la media giornaliera di ogni
   settimana.

4. In `060-problema-tris.c` impedisci la partita su una griglia già usata:
   scrivi `void svuota(Griglia g)`.

5. (Avanzato) In `080-problema-pianta-sala-esame.c` aggiungi una seconda
   `Pianta` per l'aula di riserva e disponi lì i candidati rimasti.
