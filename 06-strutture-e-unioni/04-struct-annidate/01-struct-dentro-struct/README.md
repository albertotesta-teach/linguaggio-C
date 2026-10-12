# 01 – Struct dentro struct

## Concetto

Un tipo già definito si può usare per il campo di un altro tipo. Lo
studente ha una data di nascita, non tre interi sparsi:

```c
typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char nome[20];
    char classe[4];
    Data nascita;          /* campo di tipo Data */
} Studente;

s.nascita              /* la Data dello studente */
s.nascita.anno         /* l'anno: i punti si leggono da sinistra a destra */
```

Il tipo interno va definito **prima** del tipo che lo usa, e la struct
interna occupa memoria dentro quella esterna: `sizeof(Studente)` comprende
`sizeof(Data)`.

### Inizializzazione

| Forma | Esempio |
|-------|---------|
| in ordine, con le graffe interne | `{"Rossi Elena", "2A", {12, 3, 2010}}` |
| con il nome della parte | `{.nome = "Costa Marta", .nascita = {5, 7, 2010}}` |
| con il nome di un campo interno | `{.nome = "Villa Sara", .nascita.anno = 2009}` |
| tutto a zero | `{0}` |

### Copia e confronto

| Operazione | Struct annidate |
|------------|-----------------|
| copia di tutto | `b = a;` copia anche le struct interne |
| copia di una parte | `b.ora = a.ora;` se la parte ha lo stesso tipo |
| confronto | mai con `==`, nemmeno tra le parti: si scende fino ai campi semplici |

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-campo-struct.c` | `Data` dentro `Studente`: punti in catena e `sizeof` |
| `020-inizializzazione-annidata.c` | Graffe interne, campi con nome e `{0}` per gli iscritti a un corso |
| `030-copia-e-confronto-annidati.c` | Copia di un colloquio, copia di una parte e confronto campo per campo |
| `040-problema-prestiti-biblioteca.c` | Tre `Data` in ogni prestito: giorni di ritardo e multa |
| `040-problema-prestiti-biblioteca-analisi.md` | Analisi di `040-problema-prestiti-biblioteca.c` |
| `050-problema-anagrafica-studenti.c` | `Indirizzo` dentro `Studente`: ricerca per comune e CAP, conteggio per provincia |
| `050-problema-anagrafica-studenti-analisi.md` | Analisi di `050-problema-anagrafica-studenti.c` |
| `060-problema-pianta-del-laboratorio.c` | Banchi come due `Punto`: area, centro, distanza dalla porta |
| `060-problema-pianta-del-laboratorio-analisi.md` | Analisi di `060-problema-pianta-del-laboratorio.c` |
| `070-problema-visite-museo.c` | `Visita` con `Data` e `Orario`: controllo delle sovrapposizioni |
| `070-problema-visite-museo-analisi.md` | Analisi di `070-problema-visite-museo.c` |
| `080-problema-tratte-ferroviarie.c` | Tre livelli (`Tratta`, `Fermata`, `Orario`): collegamenti con un cambio |
| `080-problema-tratte-ferroviarie-analisi.md` | Analisi di `080-problema-tratte-ferroviarie.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-campo-struct 010-campo-struct.c
./010-campo-struct

gcc -Wall -Wextra -o 020-inizializzazione-annidata 020-inizializzazione-annidata.c
./020-inizializzazione-annidata

gcc -Wall -Wextra -o 030-copia-e-confronto-annidati 030-copia-e-confronto-annidati.c
./030-copia-e-confronto-annidati

gcc -Wall -Wextra -o 040-problema-prestiti-biblioteca 040-problema-prestiti-biblioteca.c
./040-problema-prestiti-biblioteca

gcc -Wall -Wextra -o 050-problema-anagrafica-studenti 050-problema-anagrafica-studenti.c
./050-problema-anagrafica-studenti

gcc -Wall -Wextra -o 060-problema-pianta-del-laboratorio 060-problema-pianta-del-laboratorio.c -lm
./060-problema-pianta-del-laboratorio

gcc -Wall -Wextra -o 070-problema-visite-museo 070-problema-visite-museo.c
./070-problema-visite-museo

gcc -Wall -Wextra -o 080-problema-tratte-ferroviarie 080-problema-tratte-ferroviarie.c
./080-problema-tratte-ferroviarie
```

---

## Output atteso

### 010-campo-struct
```
Rossi Elena  2A  nascita 12/03/2010
Greco Paolo  2A  nascita 30/11/2009
Il piu' giovane: Rossi Elena

sizeof(Data)         = 12 byte
sizeof(elena.nascita) = 12 byte
sizeof(Studente)     = 36 byte (20 + 4 + 12)
```

### 020-inizializzazione-annidata
```
Corso di robotica
  Rossi Elena  nascita 12/03/2010   iscrizione 15/09/2025
  Costa Marta  nascita 05/07/2010   iscrizione: non ancora
  Villa Sara   nascita --/--/2009   iscrizione 02/10/2025
  (posto libero)
```

### 030-copia-e-confronto-annidati
```
Originale: prof. Galli, fam. Ferri, 20/11 alle 16:30
Spostato:  prof. Galli, fam. Ferri, 20/11 alle 17:10
(l'originale non cambia: la copia e' indipendente)

fam. Ferri e fam. Riva con prof. Galli alla stessa ora? si', conflitto
```

### 040-problema-prestiti-biblioteca
*(output dipendente dall'input – ritardi e multe)*
```
Data di oggi (gg/mm/aaaa): 18/12/2025
Il barone rampante    Rossi Elena  scad. 03/12  restituito il 28/11
Fahrenheit 451        Greco Paolo  scad. 10/12  IN RITARDO di 8 giorni, multa 1.60 euro
Io, robot             Costa Marta  scad. 17/12  IN RITARDO di 1 giorno, multa 0.20 euro
La luna e i falo'     Villa Sara   scad. 19/11  IN RITARDO di 29 giorni, multa 5.00 euro
Se questo e' un uomo  Neri Luca    scad. 01/12  restituito il 05/12 con 4 giorni di ritardo
```

*(output dipendente dall'input – un giorno alla scadenza)*
```
Data di oggi (gg/mm/aaaa): 16/12/2025
Il barone rampante    Rossi Elena  scad. 03/12  restituito il 28/11
Fahrenheit 451        Greco Paolo  scad. 10/12  IN RITARDO di 6 giorni, multa 1.20 euro
Io, robot             Costa Marta  scad. 17/12  in corso, manca 1 giorno
La luna e i falo'     Villa Sara   scad. 19/11  IN RITARDO di 27 giorni, multa 5.00 euro
Se questo e' un uomo  Neri Luca    scad. 01/12  restituito il 05/12 con 4 giorni di ritardo
```

*(output dipendente dall'input – data non valida)*
```
Data di oggi (gg/mm/aaaa): 31/02/2026
Data non valida.
```

### 050-problema-anagrafica-studenti
*(output dipendente dall'input – esempio di sessione)*
```
Comando (C comune, Z cap, P, Q): C Alessandria
  Rossi Elena  2A  via Marengo 12, 15121 Alessandria (AL)
  Costa Marta  3B  via Torino 31, 15121 Alessandria (AL)
  Trovati: 2
Comando (C comune, Z cap, P, Q): C Novi Ligure
  Greco Paolo  2A  corso Italia 4, 15067 Novi Ligure (AL)
  Fabbri Ivo   4C  via Novi 5, 15067 Novi Ligure (AL)
  Trovati: 2
Comando (C comune, Z cap, P, Q): Z 14100
  Villa Sara   3B  piazza Duomo 2, 14100 Asti (AT)
  Conte Mattia 5A  corso Savona 9, 14100 Asti (AT)
  Trovati: 2
Comando (C comune, Z cap, P, Q): C Tortona
  Trovati: 0
Comando (C comune, Z cap, P, Q): P
  AL: 5 studenti
  AT: 2 studenti
Comando (C comune, Z cap, P, Q): C
  Manca il comune o il CAP.
Comando (C comune, Z cap, P, Q): Q
```

### 060-problema-pianta-del-laboratorio
*(output dipendente dall'input – tre postazioni)*
```
Banco  Area (cm2)  Centro       Distanza dalla porta
B1          19200  (220, 140)     596.7 cm
B2          19200  (220, 340)     672.3 cm
B3          19200  (620, 140)     228.0 cm
B4          19200  (620, 340)     384.7 cm
Kit di primo soccorso sul banco B3.

Postazione (x y, -1 -1 per finire): 120 150
  (120, 150): banco B1
Postazione (x y, -1 -1 per finire): 400 150
  (400, 150): corridoio
Postazione (x y, -1 -1 per finire): 700 350
  (700, 350): banco B4
Postazione (x y, -1 -1 per finire): -1 -1
```

### 070-problema-visite-museo
*(output dipendente dall'input – esempio di sessione)*
```
Visita (classe docente gg/mm/aaaa hh:mm durata, FINE): 2C Bruni 12/03/2026 11:00 90
  Prenotata: 2C con Bruni, fine alle 12:30.
Visita (classe docente gg/mm/aaaa hh:mm durata, FINE): 4A Sala 12/03/2026 10:30 60
  Sovrapposta alla visita della 2C (11:00, 90 min).
Visita (classe docente gg/mm/aaaa hh:mm durata, FINE): 5B Riva 12/03/2026 16:00 90
  Fuori dall'orario del museo (9:00-17:00).
Visita (classe docente gg/mm/aaaa hh:mm durata, FINE): 2C Bruni 13/03/2026 9:00 200
  Durata non ammessa (da 30 a 180 minuti).
Visita (classe docente gg/mm/aaaa hh:mm durata, FINE): FINE

Calendario delle visite
  12/03/2026  09:30   90 min  3B  Galli
  12/03/2026  14:00   60 min  1A  Ferri
  12/03/2026  11:00   90 min  2C  Bruni
```

### 080-problema-tratte-ferroviarie
*(output dipendente dall'input – esempio di sessione)*
```
Viaggio (partenza destinazione hh:mm, FINE): Alessandria Milano 07:00
  R 10201  Alessandria 07:05 -> Tortona 07:25
  RV 2201  Tortona 07:32 -> Milano 08:30
  Arrivo alle 08:30, durata 1 h 25 min, con un cambio
Viaggio (partenza destinazione hh:mm, FINE): Alessandria Milano 07:30
  R 10203  Alessandria 07:40 -> Tortona 08:00
  RV 2203  Tortona 08:10 -> Milano 09:05
  Arrivo alle 09:05, durata 1 h 25 min, con un cambio
Viaggio (partenza destinazione hh:mm, FINE): Alessandria Milano 06:45
  R 10201  Alessandria 07:05 -> Tortona 07:25
  RV 2201  Tortona 07:32 -> Milano 08:30
  Arrivo alle 08:30, durata 1 h 25 min, con un cambio
Viaggio (partenza destinazione hh:mm, FINE): Tortona Milano 08:00
  RV 2203  Tortona 08:10 -> Milano 09:05
  Arrivo alle 09:05, durata 0 h 55 min, diretto
Viaggio (partenza destinazione hh:mm, FINE): Alessandria Genova 07:00
  Nessun collegamento da Alessandria a Genova dopo le 07:00.
Viaggio (partenza destinazione hh:mm, FINE): FINE
```

---

## Errori comuni da evitare

**Saltare un livello**
```c
s.anno = 2010;            /* errore: anno è un campo di Data, non di Studente */
s.nascita.anno = 2010;    /* corretto */
```

**Usare il nome del campo come se fosse una variabile**
```c
nascita.anno = 2010;      /* errore: nascita esiste solo dentro uno Studente */
```

**Definire il tipo interno dopo quello esterno**
```c
typedef struct { char nome[20]; Data nascita; } Studente;   /* Data non è ancora definito */
typedef struct { int giorno; int mese; int anno; } Data;
```

**Omettere le graffe interne nella lista**
```c
Studente s = {"Rossi Elena", "2A", 12, 3, 2010};      /* compila, ma -Wmissing-braces */
Studente s = {"Rossi Elena", "2A", {12, 3, 2010}};    /* corretto */
```

**Confrontare le parti con ==**
```c
if (a.giorno == b.giorno)                         /* errore: giorno è una Data */
if (a.giorno.giorno == b.giorno.giorno && ...)    /* corretto: campo per campo */
```

---

## Concetti collegati

- `02-struct` → dichiarazione, inizializzazione, copia e confronto
- `03-struct-e-funzioni` → funzioni che ricevono e restituiscono struct
- `02-funzioni-e-struct-annidate` → passare a una funzione solo la parte interna
- `03-array-e-struct-annidate` → array dentro le struct e struct dentro gli array

---

## Esercizi proposti

1. In `010-campo-struct.c` aggiungi allo studente il campo `Data iscrizione`
   e stampa da quanti anni ognuno è iscritto alla scuola.

2. In `040-problema-prestiti-biblioteca.c` stampa anche il totale delle
   multe da riscuotere.

3. In `060-problema-pianta-del-laboratorio.c` segnala le coppie di banchi
   che distano meno di 100 cm in orizzontale (il passaggio è troppo stretto).

4. In `070-problema-visite-museo.c` stampa il calendario in ordine di data
   e ora.

5. (Avanzato) In `080-problema-tratte-ferroviarie.c` permetti anche due
   cambi, cioè tre tratte.
