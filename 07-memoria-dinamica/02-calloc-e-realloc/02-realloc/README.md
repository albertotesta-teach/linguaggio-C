# 02 – realloc

## Concetto

`realloc` cambia la dimensione di un blocco e ne conserva il contenuto
(fino alla dimensione minore tra la vecchia e la nuova):

```c
tmp = realloc(v, nuova_n * sizeof *v);
if (tmp == NULL) {
    /* v è ancora valido, con la dimensione vecchia */
} else {
    v = tmp;
    n = nuova_n;               /* la dimensione si aggiorna solo ora */
}
```

| Caso | Che cosa fa `realloc` |
|------|-----------------------|
| c'è spazio dopo il blocco | lo allunga sul posto: stesso indirizzo |
| non c'è spazio | alloca altrove, copia, libera il vecchio: indirizzo nuovo |
| riduzione | di solito sul posto; i dati oltre la nuova fine si perdono |
| memoria insufficiente | restituisce `NULL` e **non** libera il blocco vecchio |

Gli elementi aggiunti non sono inizializzati.

### Il puntatore temporaneo

```c
v = realloc(v, ...);           /* SBAGLIATO: se fallisce, v = NULL e il blocco è perso */
```

### Ridurre un blocco a zero

`realloc(v, 0)` va evitato: si scrive `free(v); v = NULL;`.

### Spostare i dati dopo realloc

In una matrice in un blocco, aggiungere una **colonna** cambia la
lunghezza delle righe: dopo la `realloc` i valori si spostano partendo
dall'ultimo, così nessuno viene sovrascritto prima di essere copiato.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-ingrandire-un-blocco.c` | Da 7 a 14 temperature: contenuto conservato, blocco spostato |
| `020-puntatore-temporaneo.c` | Una richiesta impossibile: il blocco vecchio resta valido |
| `030-rimpicciolire.c` | Blocco di 200 punteggi ridotto a quelli letti |
| `040-problema-posti-aggiuntivi.c` | Corso con posti aggiunti e tolti dalla segreteria |
| `040-problema-posti-aggiuntivi-analisi.md` | Analisi di `040-problema-posti-aggiuntivi.c` |
| `050-problema-testo-che-si-allunga.c` | Verbale che si allunga di una frase alla volta |
| `050-problema-testo-che-si-allunga-analisi.md` | Analisi di `050-problema-testo-che-si-allunga.c` |
| `060-problema-misure-ridotte.c` | Filtro sul posto delle letture del pluviometro e riduzione |
| `060-problema-misure-ridotte-analisi.md` | Analisi di `060-problema-misure-ridotte.c` |
| `070-problema-nuova-materia.c` | Una colonna in più nel tabellone, con spostamento dei voti |
| `070-problema-nuova-materia-analisi.md` | Analisi di `070-problema-nuova-materia.c` |
| `080-problema-fusione-di-classi.c` | Due elenchi ordinati fusi dal fondo in un blocco ingrandito |
| `080-problema-fusione-di-classi-analisi.md` | Analisi di `080-problema-fusione-di-classi.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-ingrandire-un-blocco 010-ingrandire-un-blocco.c
./010-ingrandire-un-blocco

gcc -Wall -Wextra -o 020-puntatore-temporaneo 020-puntatore-temporaneo.c
./020-puntatore-temporaneo

gcc -Wall -Wextra -o 030-rimpicciolire 030-rimpicciolire.c
./030-rimpicciolire

gcc -Wall -Wextra -o 040-problema-posti-aggiuntivi 040-problema-posti-aggiuntivi.c
./040-problema-posti-aggiuntivi

gcc -Wall -Wextra -o 050-problema-testo-che-si-allunga 050-problema-testo-che-si-allunga.c
./050-problema-testo-che-si-allunga

gcc -Wall -Wextra -o 060-problema-misure-ridotte 060-problema-misure-ridotte.c
./060-problema-misure-ridotte

gcc -Wall -Wextra -o 070-problema-nuova-materia 070-problema-nuova-materia.c
./070-problema-nuova-materia

gcc -Wall -Wextra -o 080-problema-fusione-di-classi 080-problema-fusione-di-classi.c
./080-problema-fusione-di-classi
```

Gli indirizzi stampati cambiano da un'esecuzione all'altra. Compilando
`020-puntatore-temporaneo.c` con `-fsanitize=address`, la richiesta
impossibile ferma il programma: per vedere il `NULL` restituito serve
`ASAN_OPTIONS=allocator_may_return_null=1`.

---

## Output atteso

### 010-ingrandire-un-blocco
```
7 giorni in 0x5581507d42a0:
 12.5 13.0 11.8 14.2 15.0 13.6 12.9

14 giorni in 0x5581507d5310 (blocco spostato)
i primi 7 valori sono stati conservati:
 12.5 13.0 11.8 14.2 15.0 13.6 12.9
dopo aver scritto la seconda settimana:
 12.5 13.0 11.8 14.2 15.0 13.6 12.9 14.1 15.3 16.0 15.8 14.4 13.9 15.2
```

### 020-puntatore-temporaneo
```
Richiesta: da 4 a 8 elementi... riuscita
Richiesta: da 8 a 16 elementi... riuscita
Richiesta: da 16 a 2305843009213693951 elementi... non riuscita, il blocco vecchio resta valido
Elementi disponibili: 16, primo 1001, ultimo 1016
```

### 030-rimpicciolire
*(output dipendente dall'input – quattro punteggi)*
```
Blocco iniziale: 200 punteggi, 800 byte
Punteggi delle squadre (-1 per terminare): 45 38 52 -3 41 -1
Blocco ridotto a 4 punteggi, 16 byte (restituiti 784 byte)
Punteggi: 45 38 52 41
Media: 44.0
```

### 040-problema-posti-aggiuntivi
*(output dipendente dall'input – esempio di sessione)*
```
Posti iniziali (da 1 a 60): 2
Comando (I, A, T, E, Q): I Marta 3B
  iscrizione di Marta (1/2)
Comando (I, A, T, E, Q): I Luca 2A
  iscrizione di Luca (2/2)
Comando (I, A, T, E, Q): I Sara 3B
  Corso pieno (2 posti): Sara in attesa.
Comando (I, A, T, E, Q): A 3
  Nuova capienza: 5 posti (120 byte)
Comando (I, A, T, E, Q): I Sara 3B
  iscrizione di Sara (3/5)
Comando (I, A, T, E, Q): T 4
  Posti liberi solo 2: non se ne possono togliere 4.
Comando (I, A, T, E, Q): T 2
  Nuova capienza: 3 posti (72 byte)
Comando (I, A, T, E, Q): E
   1. Marta        3B
   2. Luca         2A
   3. Sara         3B
  posti liberi: 0 su 3
Comando (I, A, T, E, Q): Q
```

### 050-problema-testo-che-si-allunga
*(output dipendente dall'input – verbale di quattro frasi)*
```
Frasi del verbale (FINE per terminare):
Il giorno 12 ottobre si riunisce il consiglio della 3B
  blocco di 56 byte
Sono presenti tutti i docenti e i rappresentanti dei genitori.
  blocco di 119 byte

Si discute del viaggio di istruzione a Torino
  blocco di 166 byte
La classe partecipera' al torneo di pallavolo
  blocco di 213 byte
FINE

VERBALE (4 frasi, 212 caratteri)
Il giorno 12 ottobre si riunisce il consiglio della 3B. Sono
presenti tutti i docenti e i rappresentanti dei genitori. Si
discute del viaggio di istruzione a Torino. La classe
partecipera' al torneo di pallavolo.
```

### 060-problema-misure-ridotte
*(output dipendente dall'input – dieci giorni con due errori)*
```
Numero di giorni (da 1 a 366): 10
Millimetri di pioggia: 0 2.5 -1 14.2 0 999 3.8 27.6 0 1.2
  giorno 3: -1.0 scartato
  giorno 6: 999.0 scartato
Letture: 10, valide: 8
Blocchi ridotti da 10 a 8 elementi
Totale 49.3 mm, media 6.2 mm al giorno
Giorno piu' piovoso: 8 con 27.6 mm
```

*(output dipendente dall'input – tutte errate)*
```
Numero di giorni (da 1 a 366): 2
Millimetri di pioggia: -1 500
  giorno 1: -1.0 scartato
  giorno 2: 500.0 scartato
Letture: 2, valide: 0
```

### 070-problema-nuova-materia
*(output dipendente dall'input – si aggiunge educazione civica)*
```
Studenti e materie: 3 3
Materie: ITA MAT ING
Voti dello studente 1: 7 6.5 8
Voti dello studente 2: 5 6 5.5
Voti dello studente 3: 8 9 7.5
Comando (M, S, Q): S
              ITA  MAT  ING  media
studente  1   7.0  6.5  8.0   7.17
studente  2   5.0  6.0  5.5   5.50
studente  3   8.0  9.0  7.5   8.17
Comando (M, S, Q): M CIV 8 6 9
  CIV aggiunta: tabellone 3 x 4
Comando (M, S, Q): S
              ITA  MAT  ING  CIV  media
studente  1   7.0  6.5  8.0  8.0   7.38
studente  2   5.0  6.0  5.5  6.0   5.62
studente  3   8.0  9.0  7.5  9.0   8.38
Comando (M, S, Q): M ab 7 7 7
  Nome della materia: 3 lettere.
Comando (M, S, Q): Q
```

### 080-problema-fusione-di-classi
*(output dipendente dall'input – 4A e 4B)*
```
Studenti della 4A e cognomi in ordine: 4 Bassi Conti Ferri Rossi
Studenti della 4B e cognomi in ordine: 3 Amato Galli Neri
Blocco della 4A: 4 studenti, 96 byte
Blocco ingrandito: 7 studenti, 168 byte

Nuova 4A:
   1. Amato        (da 4B)
   2. Bassi        (da 4A)
   3. Conti        (da 4A)
   4. Ferri        (da 4A)
   5. Galli        (da 4B)
   6. Neri         (da 4B)
   7. Rossi        (da 4A)
```

*(output dipendente dall'input – elenco non in ordine)*
```
Studenti della 4A e cognomi in ordine: 3 Bassi Ferri Conti
  Conti non e' in ordine dopo Ferri
Elenco della 4A non valido.
```

---

## Errori comuni da evitare

**Assegnare il risultato allo stesso puntatore**
```c
v = realloc(v, n * sizeof *v);           /* se fallisce, perdita di memoria */
tmp = realloc(v, n * sizeof *v);         /* corretto */
```

**Aggiornare la dimensione prima di sapere se realloc è riuscita**
```c
n = n + 5;
tmp = realloc(v, n * sizeof *v);         /* se fallisce, n è sbagliato */
```

**Usare il puntatore vecchio dopo realloc**
```c
tmp = realloc(v, ...);
v[0] = 1;                                /* v può puntare a un blocco liberato */
```

**Contare sugli zeri nella parte aggiunta**
```c
tmp = realloc(conta, 2 * n * sizeof *conta);
conta[n]++;                              /* valore non definito */
```

**Spostare le righe in avanti partendo dall'inizio**
```c
for (r = 0; r < righe; r++) ...          /* sovrascrive valori non ancora spostati */
for (r = righe - 1; r >= 0; r--) ...     /* corretto */
```

---

## Concetti collegati

- `01-calloc` → blocchi azzerati
- `01-malloc-e-free/02-funzioni-e-memoria-dinamica` → funzioni che ricevono `Tipo **`
- `03-realloc-in-pratica` → `realloc(NULL, ...)`, costo della crescita, indici
- `11-algoritmi` → la fusione di due sequenze ordinate (merge)

---

## Esercizi proposti

1. In `010-ingrandire-un-blocco.c` riduci il blocco a 3 giorni e stampa
   quello che resta.

2. In `040-problema-posti-aggiuntivi.c` aggiungi una lista d'attesa che
   entra automaticamente quando si aggiungono posti.

3. In `050-problema-testo-che-si-allunga.c` aggiungi il comando per
   togliere l'ultima frase, riducendo il blocco.

4. In `070-problema-nuova-materia.c` aggiungi il comando per togliere una
   materia (spostamento in avanti, poi riduzione).

5. (Avanzato) In `080-problema-fusione-di-classi.c` fondi tre classi,
   ingrandendo il blocco una volta sola.
