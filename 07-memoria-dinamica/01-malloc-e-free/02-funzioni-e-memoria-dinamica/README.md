# 02 – Funzioni e memoria dinamica

## Concetto

Un blocco ottenuto con `malloc` non appartiene alla funzione che lo ha
allocato: resta valido fino alla `free`. Una funzione può quindi creare un
blocco e restituirne l'indirizzo.

```c
int *crea_tabellina(int numero, int n)
{
    int *v = malloc(n * sizeof *v);
    ...
    return v;                      /* il blocco sopravvive alla funzione */
}

int *t = crea_tabellina(7, 10);
if (t != NULL) {
    ...
    free(t);                       /* lo libera chi lo ha ricevuto */
}
```

### Non restituire un array locale

```c
char *etichetta(...)
{
    char testo[16];
    ...
    return testo;                  /* SBAGLIATO: testo sparisce */
}
```

| Chi fornisce la memoria | Prototipo | Chi libera |
|-------------------------|-----------|------------|
| il chiamante | `void scrivi(char testo[], ...)` | nessuno (array locale del chiamante) |
| la funzione | `char *crea(...)` | il chiamante, con `free` |

### Coppie crea/distruggi

Quando una struct contiene un puntatore a un altro blocco, le allocazioni
e le liberazioni stanno in due funzioni:

```c
Registro *crea_registro(const char *classe, int capienza);   /* 2 malloc */
void distruggi_registro(Registro *r);    /* free(r->voti), poi free(r) */
```

Chi usa il registro non chiama mai `malloc` o `free` sui suoi pezzi.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-funzione-che-alloca.c` | `crea_tabellina` restituisce il blocco, il chiamante lo libera |
| `020-non-restituire-un-locale.c` | Buffer del chiamante oppure blocco allocato dalla funzione |
| `030-chi-libera.c` | `crea_registro` e `distruggi_registro`: struct con un array nello heap |
| `040-problema-unisci-stringhe.c` | Indirizzi email creati in blocchi della lunghezza esatta |
| `040-problema-unisci-stringhe-analisi.md` | Analisi di `040-problema-unisci-stringhe.c` |
| `050-problema-tabella-dei-voti.c` | Matrice studenti × materie in un solo blocco |
| `050-problema-tabella-dei-voti-analisi.md` | Analisi di `050-problema-tabella-dei-voti.c` |
| `060-problema-filtra-misure.c` | Nuovo array con le sole letture valide e lunghezza in uscita |
| `060-problema-filtra-misure-analisi.md` | Analisi di `060-problema-filtra-misure.c` |
| `070-problema-elenco-iscritti.c` | `Elenco` dei corsi pomeridiani con crea e distruggi |
| `070-problema-elenco-iscritti-analisi.md` | Analisi di `070-problema-elenco-iscritti.c` |
| `080-problema-torneo.c` | Torneo con l'array delle squadre e classifica con indici temporanei |
| `080-problema-torneo-analisi.md` | Analisi di `080-problema-torneo.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-funzione-che-alloca 010-funzione-che-alloca.c
./010-funzione-che-alloca

gcc -Wall -Wextra -o 020-non-restituire-un-locale 020-non-restituire-un-locale.c
./020-non-restituire-un-locale

gcc -Wall -Wextra -o 030-chi-libera 030-chi-libera.c
./030-chi-libera

gcc -Wall -Wextra -o 040-problema-unisci-stringhe 040-problema-unisci-stringhe.c
./040-problema-unisci-stringhe

gcc -Wall -Wextra -o 050-problema-tabella-dei-voti 050-problema-tabella-dei-voti.c
./050-problema-tabella-dei-voti

gcc -Wall -Wextra -o 060-problema-filtra-misure 060-problema-filtra-misure.c
./060-problema-filtra-misure

gcc -Wall -Wextra -o 070-problema-elenco-iscritti 070-problema-elenco-iscritti.c
./070-problema-elenco-iscritti

gcc -Wall -Wextra -o 080-problema-torneo 080-problema-torneo.c
./080-problema-torneo
```

Gli indirizzi stampati cambiano da un'esecuzione all'altra.

---

## Output atteso

### 010-funzione-che-alloca
```
Tabellina del 7 (5 righe, blocco in 0x562336d442a0): 7 14 21 28 35
Tabellina del 9 (10 righe, blocco in 0x562336d452d0): 9 18 27 36 45 54 63 72 81 90
Tabellina del 12 (3 righe, blocco in 0x562336d442a0): 12 24 36
```

### 020-non-restituire-un-locale
```
1. Memoria del chiamante (un solo buffer):
  LAB1-01 all'indirizzo 0x7ffe84af79d0
  LAB1-02 all'indirizzo 0x7ffe84af79d0
  LAB1-03 all'indirizzo 0x7ffe84af79d0

2. Memoria allocata dalla funzione (un blocco per etichetta):
  LAB2-01 all'indirizzo 0x55fbf30b82b0
  LAB2-02 all'indirizzo 0x55fbf30b82d0
  LAB2-03 all'indirizzo 0x55fbf30b82f0
```

### 030-chi-libera
```
Registro della 4A pieno: voto 9 non inserito.
3B (2/4 voti): 7.5 6.0
4A (2/2 voti): 8.0 5.5
```

### 040-problema-unisci-stringhe
*(output dipendente dall'input – sei studenti)*
```
Nome e cognome (FINE per terminare): Marta Bassi
  marta.bassi@studenti.scuola.it (30 caratteri)
Nome e cognome (FINE per terminare): Luca D'Amico
  luca.damico@studenti.scuola.it (30 caratteri)
Nome e cognome (FINE per terminare): Marta Bassi
  marta.bassi2@studenti.scuola.it (31 caratteri)
Nome e cognome (FINE per terminare): MARTA bassi
  marta.bassi3@studenti.scuola.it (31 caratteri)
Nome e cognome (FINE per terminare): Anna-Maria Rossi
  annamaria.rossi@studenti.scuola.it (34 caratteri)
Nome e cognome (FINE per terminare): 123 456
  Nome o cognome senza lettere.
Nome e cognome (FINE per terminare): FINE

Account da creare: 5
  marta.bassi@studenti.scuola.it
  luca.damico@studenti.scuola.it
  marta.bassi2@studenti.scuola.it
  marta.bassi3@studenti.scuola.it
  annamaria.rossi@studenti.scuola.it
```

### 050-problema-tabella-dei-voti
*(output dipendente dall'input – 3 studenti, 4 materie)*
```
Studenti e materie: 3 4
Blocco di 3 x 4 = 12 double (96 byte)
Voti dello studente 1: 7 6.5 8 9
Voti dello studente 2: 5 6 5.5 7
Voti dello studente 3: 8 9 7.5 10

             ITA  MAT  ING  INF  media
studente  1  7.0  6.5  8.0  9.0   7.62
studente  2  5.0  6.0  5.5  7.0   5.88
studente  3  8.0  9.0  7.5 10.0   8.62
media        6.7  7.2  7.0  8.7

Media piu' alta: studente 3 con 8.62
```

*(output dipendente dall'input – voto non valido)*
```
Studenti e materie: 2 2
Blocco di 2 x 2 = 4 double (32 byte)
Voti dello studente 1: 7 12
Voti mancanti o non validi.
```

### 060-problema-filtra-misure
*(output dipendente dall'input – letture con errori)*
```
Numero di letture (da 1 a 144): 8
Letture in ppm: 620 845 9999 1020 1180 0 960 1310
Tutte le letture (8): 620 845 9999 1020 1180 0 960 1310  media 1992
Letture valide (6): 620 845 1020 1180 960 1310  media 989
Scartate per errore del sensore: 2
Almeno 1000 ppm (aprire le finestre) (3): 1020 1180 1310  media 1170
```

*(output dipendente dall'input – aria buona)*
```
Numero di letture (da 1 a 144): 3
Letture in ppm: 500 600 700
Tutte le letture (3): 500 600 700  media 600
Letture valide (3): 500 600 700  media 600
Scartate per errore del sensore: 0
Almeno 1000 ppm (aprire le finestre) (0): nessuna
```

### 070-problema-elenco-iscritti
*(output dipendente dall'input – esempio di sessione)*
```
Posti di robotica e di teatro: 2 3
Comando (I, R, E, Q): I robotica Marta 3B
  Iscrizione di Marta a robotica (1/2)
Comando (I, R, E, Q): I robotica Luca 2A
  Iscrizione di Luca a robotica (2/2)
Comando (I, R, E, Q): I robotica Sara 3B
  Il corso di robotica e' pieno.
Comando (I, R, E, Q): I teatro Marta 3B
  Iscrizione di Marta a teatro (1/3)
Comando (I, R, E, Q): I teatro Marta 3B
  Marta e' gia' tra gli iscritti a teatro.
Comando (I, R, E, Q): I musica Paolo 1C
  Corso sconosciuto: musica
Comando (I, R, E, Q): R robotica Marta
  Ritiro di Marta da robotica.
Comando (I, R, E, Q): I robotica Sara 3B
  Iscrizione di Sara a robotica (2/2)
Comando (I, R, E, Q): R teatro Luca
  Luca non e' tra gli iscritti a teatro.
Comando (I, R, E, Q): E
  robotica: iscritti 2 su 2 posti
    1. Luca         2A
    2. Sara         3B
  teatro: iscritti 1 su 3 posti
    1. Marta        3B
Comando (I, R, E, Q): Q
```

### 080-problema-torneo
*(output dipendente dall'input – quattro squadre)*
```
Numero di squadre (da 2 a 16): 4
Squadra 1: Leoni
Squadra 2: Falchi
Squadra 3: Leoni
  nome mancante o ripetuto: uso S3
Squadra 4: Squali
Comando (P, C, Q): P Leoni 3 Falchi 1
  Leoni 3 - 1 Falchi registrata
Comando (P, C, Q): P S3 2 Squali 2
  S3 2 - 2 Squali registrata
Comando (P, C, Q): P Falchi 4 Squali 0
  Falchi 4 - 0 Squali registrata
Comando (P, C, Q): P Leoni 1 S3 1
  Leoni 1 - 1 S3 registrata
Comando (P, C, Q): P Lupi 1 Falchi 0
  Squadre non valide.
Comando (P, C, Q): C
  Calcetto d'istituto
     squadra       G  GF  GS  DR  punti
   1 Leoni         2   4   2  +2     4
   2 Falchi        2   5   3  +2     3
   3 S3            2   3   3  +0     2
   4 Squali        2   2   6  -4     1
Comando (P, C, Q): Q
```

---

## Errori comuni da evitare

**Restituire l'indirizzo di una variabile locale**
```c
char testo[16];
return testo;                      /* puntatore pendente */
```

**Non dire al chiamante quanto è lungo il blocco**
```c
double *filtra(const double v[], int n);                /* quanti elementi? */
double *filtra(const double v[], int n, int *quante);   /* corretto */
```

**Liberare la struct prima del blocco che contiene**
```c
free(r);
free(r->voti);                     /* r non si può più leggere */
```

**Perdere la prima allocazione se fallisce la seconda**
```c
r->voti = malloc(...);
if (r->voti == NULL) { return NULL; }          /* r resta allocata */
if (r->voti == NULL) { free(r); r = NULL; }    /* corretto */
```

**Sbagliare l'indice di una matrice in un solo blocco**
```c
tab[r * righe + c]                 /* si moltiplica per le colonne */
tab[r * colonne + c]               /* corretto */
```

---

## Concetti collegati

- `03-funzioni/03-passaggio-per-riferimento` → parametri di uscita
- `04-array-e-stringhe/02-array-multidimensionali` → righe consecutive in memoria
- `01-allocare-e-liberare` → `malloc`, `free` e controllo di `NULL`
- `03-errori-con-la-memoria` → che cosa succede quando le regole non si rispettano

---

## Esercizi proposti

1. In `010-funzione-che-alloca.c` scrivi `int *crea_quadrati(int n)` con i
   quadrati da 1 a n.

2. In `040-problema-unisci-stringhe.c` aggiungi una funzione che crea
   anche il nome utente (iniziale del nome e cognome, `mbassi`).

3. In `050-problema-tabella-dei-voti.c` stampa per ogni materia lo
   studente con il voto più alto.

4. In `070-problema-elenco-iscritti.c` aggiungi un terzo corso, scacchi,
   senza modificare le funzioni.

5. (Avanzato) In `080-problema-torneo.c` scrivi una funzione che
   restituisce un nuovo array con le sole squadre senza sconfitte.
