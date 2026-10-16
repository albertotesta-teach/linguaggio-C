# 02 – I flussi standard

## Concetto

Ogni programma C parte con tre `FILE *` già aperti, che non si aprono e
non si chiudono:

| Flusso | Nome | Di solito |
|--------|------|-----------|
| `stdin` | ingresso standard | la tastiera |
| `stdout` | uscita standard | lo schermo |
| `stderr` | uscita degli errori | lo schermo |

Le funzioni già note sono scorciatoie:

| Funzione | Equivale a |
|----------|------------|
| `printf(...)` | `fprintf(stdout, ...)` |
| `putchar(c)` | `fputc(c, stdout)` |
| `scanf(...)` | `fscanf(stdin, ...)` |
| `getchar()` | `fgetc(stdin)` |

### Una funzione per ogni flusso

Una funzione che riceve il `FILE *` scrive a video o su file a seconda di
chi la chiama:

```c
void stampa_pagella(FILE *f, ...);

stampa_pagella(stdout, ...);          /* a video */
stampa_pagella(file, ...);            /* nel file aperto con fopen */
```

### Redirezione

Chi esegue il programma decide da dove arriva `stdin` e dove vanno
`stdout` e `stderr`:

```bash
./programma < dati.txt          # stdin da file
./programma > risultati.txt     # stdout in un file
./programma 2> errori.txt       # stderr in un file
```

Gli errori vanno sempre su `stderr`: così, se `stdout` è rediretto in un
file, i messaggi restano a video e il file contiene solo i risultati. Da
tastiera la fine dei dati si segnala con **Ctrl+D** (Linux, macOS) o
**Ctrl+Z e Invio** (Windows).

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-stdin-stdout-stderr.c` | Età valide su `stdout`, scarti su `stderr` |
| `020-una-funzione-per-ogni-flusso.c` | Lo stesso orario a video e in `orario.txt` |
| `030-redirezione.c` | Conta caratteri, parole e righe di `stdin` fino a `EOF` |
| `040-problema-pagella-a-video-e-su-file.c` | Una funzione per la pagella a video e su file |
| `040-problema-pagella-a-video-e-su-file-analisi.md` | Analisi di `040-problema-pagella-a-video-e-su-file.c` |
| `050-problema-filtro-maiuscole.c` | Filtro da `stdin` a `stdout` in maiuscolo |
| `050-problema-filtro-maiuscole-analisi.md` | Analisi di `050-problema-filtro-maiuscole.c` |
| `060-problema-registro-degli-errori.c` | Dati validi in un file, errori su `stderr` e in uno storico |
| `060-problema-registro-degli-errori-analisi.md` | Analisi di `060-problema-registro-degli-errori.c` |
| `070-problema-numerazione-delle-righe.c` | Filtro che numera le righe non vuote |
| `070-problema-numerazione-delle-righe-analisi.md` | Analisi di `070-problema-numerazione-delle-righe.c` |
| `080-problema-rapporto-multiplo.c` | Rapporto a video, in un file nuovo e in coda a uno storico |
| `080-problema-rapporto-multiplo-analisi.md` | Analisi di `080-problema-rapporto-multiplo.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-stdin-stdout-stderr 010-stdin-stdout-stderr.c
./010-stdin-stdout-stderr

gcc -Wall -Wextra -o 020-una-funzione-per-ogni-flusso 020-una-funzione-per-ogni-flusso.c
./020-una-funzione-per-ogni-flusso

gcc -Wall -Wextra -o 030-redirezione 030-redirezione.c
./030-redirezione

gcc -Wall -Wextra -o 040-problema-pagella-a-video-e-su-file 040-problema-pagella-a-video-e-su-file.c
./040-problema-pagella-a-video-e-su-file

gcc -Wall -Wextra -o 050-problema-filtro-maiuscole 050-problema-filtro-maiuscole.c
./050-problema-filtro-maiuscole

gcc -Wall -Wextra -o 060-problema-registro-degli-errori 060-problema-registro-degli-errori.c
./060-problema-registro-degli-errori

gcc -Wall -Wextra -o 070-problema-numerazione-delle-righe 070-problema-numerazione-delle-righe.c
./070-problema-numerazione-delle-righe

gcc -Wall -Wextra -o 080-problema-rapporto-multiplo 080-problema-rapporto-multiplo.c
./080-problema-rapporto-multiplo
```

---

## Output atteso

Nei programmi che leggono `stdin` fino alla fine, le righe scritte da
tastiera compaiono nell'output prima di quelle elaborate.

### 010-stdin-stdout-stderr
*(output dipendente dall'input – eta' valide e scartate)*
```
Eta' dei partecipanti (0 per finire):
12 15 11 9 14 0
  iscritto: 12 anni
  scarto: 15 anni non e' tra 11 e 14
  iscritto: 11 anni
  scarto: 9 anni non e' tra 11 e 14
  iscritto: 14 anni
Iscritti: 3
Fine dell'elaborazione.
Eta' scartate: 2
```

### 020-una-funzione-per-ogni-flusso
```
A video:
Orario della classe 4B Informatica
       1^   2^   3^   4^   5^
Lun   Ita  Ita  Mat  Inf  Inf
Mar   Ing  Mat  Sto  Sis  Sis
Mer   Inf  Inf  Inf  Ita  Mot
Gio   Mat  Mat  Ing  Tps  Tps
Ven   Sis  Ita  Ing  Mat  Rel

Salvato in orario.txt; il file contiene:
Orario della classe 4B Informatica
       1^   2^   3^   4^   5^
Lun   Ita  Ita  Mat  Inf  Inf
Mar   Ing  Mat  Sto  Sis  Sis
Mer   Inf  Inf  Inf  Ita  Mot
Gio   Mat  Mat  Ing  Tps  Tps
Ven   Sis  Ita  Ing  Mat  Rel
```

### 030-redirezione
*(output dipendente dall'input – due righe da tastiera, poi Ctrl+D)*
```
Testo da contare (Ctrl+D per finire):
Il file si apre con fopen
e si chiude con fclose.

caratteri: 50
parole:    11
righe:     2
```

### 040-problema-pagella-a-video-e-su-file
*(output dipendente dall'input – pagella salvata)*
```
Cognome dello studente: Bianchi
  Italiano: 7
  Matematica: 5
  Inglese: otto
  voto da 1 a 10
  Inglese: 8
  Informatica: 9
  Sistemi e reti: 11
  voto da 1 a 10
  Sistemi e reti: 6
  Scienze motorie: 6

PAGELLA DEL PRIMO TRIMESTRE - Bianchi
----------------------------------
Italiano            7
Matematica          5  *
Inglese             8
Informatica         9
Sistemi e reti      6
Scienze motorie     6
----------------------------------
Media: 6.83
Insufficienze (*): 1

Salvare la pagella? (s/n) s
Pagella salvata in pagella-Bianchi.txt
```

### 050-problema-filtro-maiuscole
*(output dipendente dall'input – testo da tastiera, poi Ctrl+D)*
```
Open day: sabato 14 dicembre, ore 9-13
OPEN DAY: SABATO 14 DICEMBRE, ORE 9-13
Laboratori di informatica e di robotica
LABORATORI DI INFORMATICA E DI ROBOTICA

[filtro] caratteri letti: 79, lettere convertite: 56
```

### 060-problema-registro-degli-errori
*(output dipendente dall'input – voti con errori)*
```
Voti (cognome voto, FINE per terminare):
Rossi 6
Bianchi sei
riga 2 (Bianchi): il voto non e' un numero intero
Verdi 7
Neri 11
riga 4 (Neri): voto fuori dall'intervallo 1-10
Russo 5
FINE
Voti caricati in recupero.txt: 3
Righe scartate (vedi errori.txt): 2
```

### 070-problema-numerazione-delle-righe
*(output dipendente dall'input – una strofa con righe vuote, poi Ctrl+D)*
```
Nel mezzo del cammin di nostra vita
   1  Nel mezzo del cammin di nostra vita


mi ritrovai per una selva oscura,
   2  mi ritrovai per una selva oscura,
che' la diritta via era smarrita.
   3  che' la diritta via era smarrita.

[numerazione] righe numerate: 3, righe vuote: 1
```

### 080-problema-rapporto-multiplo
*(output dipendente dall'input – settimana 7)*
```
Settimana: 7
Classe e chili di carta (FINE per terminare):
3A 6.5 3B 11 4A 8.5 5C 5.5 FINE

Raccolta della carta - settimana 7
  3A        6.5 kg
  3B       11.0 kg
  4A        8.5 kg
  5C        5.5 kg
  Totale   31.5 kg (media 7.9 kg per classe)

Rapporto salvato in carta-settimana-07.txt
Storico aggiornato:
settimana 7: 4 classi, 31.5 kg, migliore 3B
```

*(output dipendente dall'input – settimana 8: lo storico cresce)*
```
Settimana: 8
Classe e chili di carta (FINE per terminare):
3A 7 3B 9.5 4A 10 FINE

Raccolta della carta - settimana 8
  3A        7.0 kg
  3B        9.5 kg
  4A       10.0 kg
  Totale   26.5 kg (media 8.8 kg per classe)

Rapporto salvato in carta-settimana-08.txt
Storico aggiornato:
settimana 7: 4 classi, 31.5 kg, migliore 3B
settimana 8: 3 classi, 26.5 kg, migliore 4A
```

### Uso con la redirezione

I file `saluto.txt` e `diario.txt` sono quelli creati in
`01-aprire-e-chiudere`.

```
$ ./030-redirezione < saluto.txt > conteggio.txt
Testo da contare (Ctrl+D per finire):
$ cat conteggio.txt
caratteri: 66
parole:    12
righe:     2

$ ./050-problema-filtro-maiuscole < diario.txt > stampa.txt
[filtro] caratteri letti: 98, lettere convertite: 63
$ cat stampa.txt
12/10 MUSEO EGIZIO DI TORINO
03/11 LABORATORIO DI CHIMICA ALL'UNIVERSITA'
20/11 BIBLIOTECA CIVICA

$ ./070-problema-numerazione-delle-righe < saluto.txt 2> /dev/null
   1  Benvenuti al corso di C!
   2  Lezione 1: apertura e chiusura dei file.

$ echo "12 15 11 0" | ./010-stdin-stdout-stderr > iscritti.txt
  scarto: 15 anni non e' tra 11 e 14
Eta' scartate: 1
$ cat iscritti.txt
Eta' dei partecipanti (0 per finire):
  iscritto: 12 anni
  iscritto: 11 anni
Iscritti: 2
Fine dell'elaborazione.
```

In ogni caso i messaggi di `stderr` restano a video, mentre il file
riceve solo `stdout`.

---

## Errori comuni da evitare

**Scrivere gli errori su stdout**
```c
printf("Errore: voto non valido\n");      /* finisce nel file dei risultati */
fprintf(stderr, "Errore: voto non valido\n");
```

**Usare printf dentro una funzione che riceve il flusso**
```c
void stampa(FILE *f) {
    printf("...");                         /* scrive sempre a video */
    fprintf(f, "...");                     /* corretto */
}
```

**Chiudere stdout o stdin**
```c
fclose(stdout);                            /* il programma non scrive più a video */
```

**Mettere il resoconto di un filtro su stdout**
```c
printf("convertite %d lettere\n", n);      /* finisce nel file prodotto */
```

**Aspettarsi che il filtro termini da solo**
```
Da tastiera la fine dei dati si segnala con Ctrl+D (Ctrl+Z su Windows).
```

---

## Concetti collegati

- `01-aprire-e-chiudere` → `fopen`, `fclose`, `fgetc`, `fputc`
- `03-file-in-pratica` → il buffer di `stdout` e `fflush`
- `05-gestione-errori` → `perror` e i messaggi d'errore del sistema
- `12-programmazione-avanzata/03-argomenti-da-linea-di-comando` → i nomi dei file da terminale

---

## Esercizi proposti

1. In `010-stdin-stdout-stderr.c` scrivi su `stderr` anche le letture non
   numeriche.

2. In `020-una-funzione-per-ogni-flusso.c` aggiungi una seconda classe e
   salva entrambi gli orari nello stesso file.

3. Scrivi un filtro che trasforma le maiuscole in minuscole e lascia le
   prime lettere di ogni frase maiuscole.

4. In `070-problema-numerazione-delle-righe.c` numera anche le righe
   vuote, ma in una colonna diversa.

5. (Avanzato) Scrivi un filtro che toglie i commenti `/* ... */` da un
   programma C letto da `stdin`.
