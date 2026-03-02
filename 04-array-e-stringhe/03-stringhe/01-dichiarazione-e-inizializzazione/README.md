# 01 – Dichiarazione e inizializzazione di stringhe

## Concetto

In C non esiste un tipo di dato `string` come in altri linguaggi. Una stringa è un **array di caratteri (`char`)** terminato dal carattere speciale `'\0'` (null terminator, ASCII 0). Senza questo terminatore, il programma non sa dove finisce la stringa in memoria.

```
char nome[] = "Mario";

 Indice:  0     1     2     3     4     5
          'M'   'a'   'r'   'i'   'o'   '\0'
```

Ogni carattere occupa **1 byte**. La dimensione dell'array deve sempre includere il posto per `'\0'`.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-stringa-base.c` | Dichiarazione esplicita carattere per carattere, stampa con `%s`, accesso ai singoli caratteri |
| `020-inizializzazione.c` | I quattro modi di inizializzare una stringa: array di char, stringa letterale, array sovradimensionato, assegnazione manuale |
| `030-memoria-e-terminatore.c` | Visualizzazione cella per cella della memoria: indice, carattere e valore ASCII |
| `040-problema-codice-fiscale.c` | Scenario reale: scheda anagrafica studente, estrazione di informazioni dal codice fiscale |
| `040-problema-codice-fiscale-analisi.md` | Analisi dettagliata di `040-problema-codice-fiscale.c`: casi d'uso, variabili, vincoli, algoritmi |
| `050-problema-targa.c` | Scenario reale: analisi e verifica del formato di una targa automobilistica italiana |
| `050-problema-targa-analisi.md` | Analisi dettagliata di `050-problema-targa.c`: casi d'uso, variabili, vincoli, algoritmi |
| `060-problema-codice-prodotto.c` | Scenario reale: estrazione componenti e confronto categorie di codici prodotto di magazzino |
| `060-problema-codice-prodotto-analisi.md` | Analisi dettagliata di `060-problema-codice-prodotto.c`: casi d'uso, variabili, vincoli, algoritmi |

---

## Compilazione ed esecuzione

Ogni file si compila e si esegue in modo indipendente.

```bash
gcc -Wall -o 010-stringa-base 010-stringa-base.c
./010-stringa-base

gcc -Wall -o 020-inizializzazione 020-inizializzazione.c
./020-inizializzazione

gcc -Wall -o 030-memoria-e-terminatore 030-memoria-e-terminatore.c
./030-memoria-e-terminatore

gcc -Wall -o 040-problema-codice-fiscale 040-problema-codice-fiscale.c
./040-problema-codice-fiscale

gcc -Wall -o 050-problema-targa 050-problema-targa.c
./050-problema-targa

gcc -Wall -o 060-problema-codice-prodotto 060-problema-codice-prodotto.c
./060-problema-codice-prodotto
```

---

## Output atteso

### 010-stringa-base
```
Nome: Mario
Primo carattere : M
Secondo carattere: a
Terminatore (ASCII): 0
La stringa termina correttamente con il carattere nullo.
```

### 020-inizializzazione
```
Modo 1 - carattere per carattere: Torino
Modo 2 - stringa letterale, dimensione automatica: Milano
Modo 3 - array sovradimensionato: Roma
         (le celle da 4 a 49 contengono \0)
Modo 4 - assegnazione manuale: Genova
```

### 030-memoria-e-terminatore
```
Codice prodotto: AX-2024

Mappa in memoria della stringa "AX-2024":
Indice     Carattere    Valore ASCII
----------------------------------
0          A            65
1          X            88
2          -            45
3          2            50
4          0            48
5          2            50
6          4            52
7          \0 (fine)    0

Modifica: cambio il carattere in posizione 1 da 'X' a 'Z'
Codice modificato: AZ-2024
```

### 040-problema-codice-fiscale
```
========================================
        SCHEDA STUDENTE
========================================
Nome             : Giovanni
Cognome          : Ferrero
Codice fiscale   : FRRGNN05A15L219X
Classe           : 4B
Indirizzo        : Via Roma 12, Torino
========================================

Informazioni estratte dal codice fiscale:
  Sigla cognome  : FRR
  Anno di nascita: 2005
  Giorno nascita : 15
  Codice comune  : L219

Lunghezza codice fiscale: 16 caratteri (corretta)
```

### 050-problema-targa
```
=== SISTEMA DI GESTIONE PARCHEGGIO ===
Targa rilevata: FL519RX

Lunghezza targa: 7 caratteri

Componenti estratte:
  Lettere iniziali : FL
  Cifre centrali   : 519
  Lettere finali   : RX

Verifica formato:
  Formato: VALIDO (targa italiana standard dal 1994)

Informazioni aggiuntive:
  Serie FL: sequenza civile normale.
  Valore ASCII 'F': 70
  Valore ASCII 'L': 76

=== FINE ANALISI ===
```

### 060-problema-codice-prodotto
```
=== SISTEMA DI GESTIONE MAGAZZINO ===

Prodotti in archivio:
  Prodotto 1: ELE-042-BL
  Prodotto 2: ELE-107-RO
  Prodotto 3: ALI-003-VE

Analisi Prodotto 1 (ELE-042-BL):
  Categoria   : ELE
  Progressivo : 042
  Variante    : BL

Confronto categorie:
  ELE-042-BL e ELE-107-RO: STESSA categoria (ELE)
  ELE-042-BL e ALI-003-VE: categorie DIVERSE

Verifica integrità formato ELE-042-BL:
  Separatori '-' in posizione corretta: formato VALIDO

=== FINE ANALISI ===
```

---

## Errori comuni da evitare

**Dimenticare il terminatore `'\0'`**
```c
char errata[5];
errata[0] = 'C';
errata[1] = 'i';
errata[2] = 'a';
errata[3] = 'o';
/* manca errata[4] = '\0' → comportamento indefinito! */
printf("%s\n", errata); /* stampa caratteri casuali */
```

**Dimensione insufficiente dell'array**
```c
char nome[5] = "Mario"; /* ERRORE: serve [6] per includere '\0' */
```

**Usare `=` per copiare stringhe dopo la dichiarazione**
```c
char s[10] = "ciao"; /* OK: inizializzazione */
s = "hello";         /* ERRORE: non si può assegnare un array così */
/* Usare invece strcpy(s, "hello"); */
```

---

## Concetti collegati

- `02-input-output-stringhe` → come leggere stringhe da tastiera
- `03-lunghezza-e-accesso-ai-caratteri` → calcolare la lunghezza senza `strlen`
- `05-puntatori/09-stringhe-e-puntatori` → differenza tra `char[]` e `char *`

---

## Esercizi proposti

1. Dichiara una stringa che contenga la tua via e numero civico. Stampa separatamente la via e il numero, ipotizzando di conoscere la posizione del separatore (spazio).
2. Crea un array di 20 celle inizializzato a `'\0'` e scrivi manualmente le lettere del tuo nome. Verifica che la stampa con `%s` funzioni correttamente.
3. Modifica `03-memoria-e-terminatore.c` per stampare anche il valore esadecimale di ogni carattere (suggerimento: usa il formato `%x` in `printf`).
4. Nel file `04-problema-reale.c`, aggiungi la verifica del sesso dello studente leggendo il giorno di nascita dal codice fiscale: se il valore è maggiore di 40, lo studente è di sesso femminile.
