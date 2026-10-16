# 01 – Aprire e chiudere un file

## Concetto

Un programma lavora su un file tramite un **puntatore a `FILE`**,
restituito da `fopen` e liberato da `fclose`:

```c
FILE *f = fopen("saluto.txt", "w");      /* nome e modalità */

if (f == NULL) {
    fprintf(stderr, "Impossibile creare saluto.txt\n");
} else {
    fputs("Benvenuti al corso di C!\n", f);
    fclose(f);                           /* sempre, una volta sola */
}
```

`fopen` restituisce `NULL` quando il file non si può aprire: file
inesistente in lettura, cartella sbagliata, permessi. Il controllo è
obbligatorio, come per `malloc`.

### Le modalità di apertura

| Modalità | File esistente | File inesistente | Operazioni |
|----------|----------------|------------------|------------|
| `"r"` | letto dall'inizio | `NULL` | lettura |
| `"w"` | **svuotato** | creato | scrittura |
| `"a"` | scrittura in fondo | creato | scrittura |
| `"r+"` | letto dall'inizio | `NULL` | lettura e scrittura |
| `"w+"` | **svuotato** | creato | lettura e scrittura |
| `"a+"` | scrittura in fondo | creato | lettura e scrittura |

### Leggere e scrivere un carattere alla volta

| Funzione | Compito |
|----------|---------|
| `fputc(c, f)` | scrive un carattere |
| `fputs(s, f)` | scrive una stringa (senza aggiungere `'\n'`) |
| `fprintf(f, formato, ...)` | come `printf`, ma sul file |
| `fgetc(f)` | legge un carattere, `EOF` alla fine del file |

```c
int c;                       /* int, non char: deve poter valere EOF */

c = fgetc(f);
while (c != EOF) {
    putchar(c);
    c = fgetc(f);
}
```

Le righe intere (`fgets`) e la lettura formattata (`fscanf`) sono in
`02-lettura-e-scrittura-testo`.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-fopen-e-fclose.c` | Scrivere `saluto.txt`, chiuderlo e rileggerlo con `fgetc` |
| `020-modalita-di-apertura.c` | `"w"` svuota, `"a"` aggiunge, `"r"` su un file mancante dà `NULL` |
| `030-file-che-non-esiste.c` | Nome chiesto all'utente, fino a tre tentativi |
| `040-problema-diario-delle-uscite.c` | Diario delle uscite didattiche in modalità `"a"` |
| `040-problema-diario-delle-uscite-analisi.md` | Analisi di `040-problema-diario-delle-uscite.c` |
| `050-problema-copia-di-un-file.c` | Copia carattere per carattere con due file aperti |
| `050-problema-copia-di-un-file-analisi.md` | Analisi di `050-problema-copia-di-un-file.c` |
| `060-problema-registro-del-giorno.c` | Nome del file costruito dalla data, aggiungere o sovrascrivere |
| `060-problema-registro-del-giorno-analisi.md` | Analisi di `060-problema-registro-del-giorno.c` |
| `070-problema-statistiche-di-un-testo.c` | Lettere, cifre, righe e riga più lunga in una sola lettura |
| `070-problema-statistiche-di-un-testo-analisi.md` | Analisi di `070-problema-statistiche-di-un-testo.c` |
| `080-problema-confronto-di-due-file.c` | Prima differenza tra due file, con riga e colonna |
| `080-problema-confronto-di-due-file-analisi.md` | Analisi di `080-problema-confronto-di-due-file.c` |

---

## Compilazione ed esecuzione

I programmi creano e leggono i file nella cartella da cui vengono
eseguiti. Alcuni usano i file creati dai precedenti: `030` legge
`saluto.txt` (creato da `010`), `050`, `070` e `080` usano `diario.txt`
(creato da `040`). Conviene eseguirli nell'ordine.

```bash
gcc -Wall -Wextra -o 010-fopen-e-fclose 010-fopen-e-fclose.c
./010-fopen-e-fclose

gcc -Wall -Wextra -o 020-modalita-di-apertura 020-modalita-di-apertura.c
./020-modalita-di-apertura

gcc -Wall -Wextra -o 030-file-che-non-esiste 030-file-che-non-esiste.c
./030-file-che-non-esiste

gcc -Wall -Wextra -o 040-problema-diario-delle-uscite 040-problema-diario-delle-uscite.c
./040-problema-diario-delle-uscite

gcc -Wall -Wextra -o 050-problema-copia-di-un-file 050-problema-copia-di-un-file.c
./050-problema-copia-di-un-file

gcc -Wall -Wextra -o 060-problema-registro-del-giorno 060-problema-registro-del-giorno.c
./060-problema-registro-del-giorno

gcc -Wall -Wextra -o 070-problema-statistiche-di-un-testo 070-problema-statistiche-di-un-testo.c
./070-problema-statistiche-di-un-testo

gcc -Wall -Wextra -o 080-problema-confronto-di-due-file 080-problema-confronto-di-due-file.c
./080-problema-confronto-di-due-file
```

---

## Output atteso

### 010-fopen-e-fclose
```
Scritto saluto.txt
Contenuto di saluto.txt:
Benvenuti al corso di C!
Lezione 1: apertura e chiusura dei file.
Caratteri letti: 66
```

### 020-modalita-di-apertura
```
1. fopen("modalita.txt", "w") e scrittura di "prima riga"
   contenuto:
     | prima riga
2. fopen("modalita.txt", "w") e scrittura di "seconda riga"
   contenuto:
     | seconda riga
3. fopen("modalita.txt", "a") e scrittura di "terza riga"
   contenuto:
     | seconda riga
     | terza riga
4. fopen("mancante.txt", "r")
   NULL: in lettura il file deve esistere
```

### 030-file-che-non-esiste
*(output dipendente dall'input – due nomi sbagliati, poi quello giusto)*
```
Nome del file (tentativo 1 di 3): programma.txt
  programma.txt non esiste o non si puo' leggere
Nome del file (tentativo 2 di 3): saluto.tx
  saluto.tx non esiste o non si puo' leggere
Nome del file (tentativo 3 di 3): saluto.txt
--- saluto.txt ---
Benvenuti al corso di C!
Lezione 1: apertura e chiusura dei file.
--- righe: 2 ---
```

### 040-problema-diario-delle-uscite
*(output dipendente dall'input – prima esecuzione)*
```
Uscite (gg/mm meta, FINE per terminare):
12/10 Museo Egizio di Torino
31/11 Gita sul Po
  data non valida: 31/11
03/11 Laboratorio di chimica all'universita'
FINE
Voci aggiunte: 2

Diario delle uscite:
  1. 12/10 Museo Egizio di Torino
  2. 03/11 Laboratorio di chimica all'universita'
```

*(output dipendente dall'input – seconda esecuzione: le voci si aggiungono)*
```
Uscite (gg/mm meta, FINE per terminare):
20/11 Biblioteca civica
FINE
Voci aggiunte: 1

Diario delle uscite:
  1. 12/10 Museo Egizio di Torino
  2. 03/11 Laboratorio di chimica all'universita'
  3. 20/11 Biblioteca civica
```

### 050-problema-copia-di-un-file
*(output dipendente dall'input – copia del diario)*
```
File da copiare: diario.txt
Nome della copia: diario.txt
  la copia deve avere un nome diverso
Nome della copia: diario-copia.txt
Copiati 98 caratteri e 3 righe da diario.txt a diario-copia.txt
```

*(output dipendente dall'input – la copia esiste gia')*
```
File da copiare: diario.txt
Nome della copia: diario-copia.txt
diario-copia.txt esiste gia': sovrascrivere? (s/n) n
Copia annullata.
```

### 060-problema-registro-del-giorno
*(output dipendente dall'input – primo registro del giorno)*
```
Data (gg mm): 16 10
Assenti (FINE per terminare): Rossi Bianchi FINE
Assenti registrati in presenze-16-10.txt: 2
--- presenze-16-10.txt ---
assente: Rossi
assente: Bianchi
```

*(output dipendente dall'input – il file esiste: si aggiunge)*
```
Data (gg mm): 16 10
presenze-16-10.txt esiste gia': A aggiungere, S sovrascrivere, N annullare? A
Assenti (FINE per terminare): Verdi FINE
Assenti registrati in presenze-16-10.txt: 1
--- presenze-16-10.txt ---
assente: Rossi
assente: Bianchi
assente: Verdi
```

### 070-problema-statistiche-di-un-testo
*(output dipendente dall'input – statistiche del diario)*
```
File da analizzare: diario.txt
Statistiche di diario.txt
  lettere              68
  cifre                12
  spazi                10
  altri caratteri       5
  righe                 3
  riga piu' lunga: la 2, con 44 caratteri
  righe oltre 80 caratteri: 0
```

### 080-problema-confronto-di-due-file
*(output dipendente dall'input – il diario e la sua copia)*
```
Primo file: diario.txt
Secondo file: diario-copia.txt
I file sono identici. Righe confrontate: 3
```

*(output dipendente dall'input – due file diversi)*
```
Primo file: diario.txt
Secondo file: presenze-16-10.txt
Prima differenza alla riga 1, colonna 1:
  diario.txt           '1'
  presenze-16-10.txt   'a'
```

---

## Errori comuni da evitare

**Non controllare il risultato di fopen**
```c
FILE *f = fopen("dati.txt", "r");
c = fgetc(f);                       /* f può essere NULL */
```

**Mettere il risultato di fgetc in un char**
```c
char c = fgetc(f);                  /* EOF non si distingue da un carattere */
int c = fgetc(f);                   /* corretto */
```

**Aprire in "w" un file da conservare**
```c
fopen("diario.txt", "w");           /* il diario precedente è cancellato */
fopen("diario.txt", "a");           /* aggiunge in fondo */
```

**Chiamare fclose su NULL o due volte**
```c
if (f != NULL) {
    fclose(f);                      /* solo se è stato aperto, una volta */
}
```

**Usare il FILE * dopo fclose**
```c
fclose(f);
fputs("ancora", f);                 /* il flusso non esiste più */
```

**Copiare un file su se stesso**
```c
origine = fopen("a.txt", "r");
copia = fopen("a.txt", "w");        /* svuota il file prima di leggerlo */
```

---

## Concetti collegati

- `02-flussi-standard` → `stdin`, `stdout`, `stderr` e la redirezione
- `03-file-in-pratica` → più file aperti, buffer, `remove` e `rename`
- `02-lettura-e-scrittura-testo` → `fgets`, `fscanf`, righe e campi
- `07-memoria-dinamica/01-malloc-e-free` → lo stesso schema: richiedere, controllare `NULL`, restituire

---

## Esercizi proposti

1. In `010-fopen-e-fclose.c` conta anche le vocali del file.

2. In `040-problema-diario-delle-uscite.c` rifiuta una data già presente
   nel diario.

3. In `050-problema-copia-di-un-file.c` copia il file eliminando le righe
   vuote.

4. In `070-problema-statistiche-di-un-testo.c` conta anche le parole.

5. (Avanzato) In `080-problema-confronto-di-due-file.c` continua dopo la
   prima differenza e conta quante righe sono diverse.
