# 02 – Array come puntatori

## Concetto

In quasi tutte le espressioni il **nome di un array** diventa l'indirizzo
del suo primo elemento. Per questo indici e aritmetica dei puntatori sono
due modi di scrivere la stessa cosa.

| Scrittura con indici | Scrittura con puntatori |
|----------------------|-------------------------|
| `&v[0]` | `v` |
| `&v[i]` | `v + i` |
| `v[i]` | `*(v + i)` |

```c
int liberi[5] = {14, 3, 0, 22, 9};
int *p = liberi;          /* come p = &liberi[0] */

p[2] = 1;                 /* come liberi[2] = 1 */
```

### Array e puntatore non sono la stessa cosa

| | `int v[5]` | `int *p = v` |
|-|-----------|--------------|
| `sizeof` | 20 byte: tutto l'array | 8 byte: un indirizzo |
| si può spostare? | no: `v++` è un errore | sì: `p++` |
| contiene | 5 interi | un indirizzo |

### Un array passato a una funzione arriva come puntatore

Alla funzione non arriva una copia dell'array ma l'indirizzo del primo
elemento. Come parametro, le due scritture sono equivalenti:

```c
int totale(const int v[], int n);
int totale(const int *v, int n);
```

Per questo la funzione può modificare l'array del chiamante e non conosce la
dimensione: `n` va sempre passato a parte.

### Passare solo una parte di un array

Basta passare l'indirizzo da cui partire e il numero di elementi:

```c
totale(incassi, 5);         /* lunedì-venerdì */
totale(incassi + 5, 2);     /* sabato e domenica */
```

Dentro la funzione il sottoarray si usa con gli indici da 0. Una posizione
restituita dalla funzione è **relativa** al sottoarray: il chiamante la
riporta all'array completo aggiungendo lo scostamento.

Un intervallo si può indicare anche con due puntatori, `inizio` incluso e
`fine` escluso: `occupa(posti + i, posti + i + k)`.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-nome-array-e-indirizzo.c` | `v` e `&v[0]`, quattro modi di leggere un elemento, `sizeof` di array e puntatore |
| `020-parametri-array-e-puntatori.c` | `int v[]` e `int *v` come parametri, modifica dell'array del chiamante |
| `030-sottoarray.c` | `somma(v + 3, 3)` e intervalli `[inizio, fine)` |
| `040-problema-vendite-settimanali.c` | Le stesse funzioni su feriali (`incassi`, 5) e fine settimana (`incassi + 5`, 2) |
| `040-problema-vendite-settimanali-analisi.md` | Analisi di `040-problema-vendite-settimanali.c` |
| `050-problema-posti-sul-treno.c` | Ricerca di k posti liberi vicini e prenotazione di un intervallo |
| `050-problema-posti-sul-treno-analisi.md` | Analisi di `050-problema-posti-sul-treno.c` |
| `060-problema-primo-giorno-di-gelo.c` | Ricerca su un periodo scelto, passato come sottoarray |
| `060-problema-primo-giorno-di-gelo-analisi.md` | Analisi di `060-problema-primo-giorno-di-gelo.c` |
| `070-problema-backup-registro.c` | Copia di un blocco con due puntatori, confronto e ripristino |
| `070-problema-backup-registro-analisi.md` | Analisi di `070-problema-backup-registro.c` |
| `080-problema-istogramma-voti.c` | Array dei conteggi riempito da una funzione tramite `int *` |
| `080-problema-istogramma-voti-analisi.md` | Analisi di `080-problema-istogramma-voti.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-nome-array-e-indirizzo 010-nome-array-e-indirizzo.c
./010-nome-array-e-indirizzo

gcc -Wall -Wextra -o 020-parametri-array-e-puntatori 020-parametri-array-e-puntatori.c
./020-parametri-array-e-puntatori

gcc -Wall -Wextra -o 030-sottoarray 030-sottoarray.c
./030-sottoarray

gcc -Wall -Wextra -o 040-problema-vendite-settimanali 040-problema-vendite-settimanali.c
./040-problema-vendite-settimanali

gcc -Wall -Wextra -o 050-problema-posti-sul-treno 050-problema-posti-sul-treno.c
./050-problema-posti-sul-treno

gcc -Wall -Wextra -o 060-problema-primo-giorno-di-gelo 060-problema-primo-giorno-di-gelo.c
./060-problema-primo-giorno-di-gelo

gcc -Wall -Wextra -o 070-problema-backup-registro 070-problema-backup-registro.c
./070-problema-backup-registro

gcc -Wall -Wextra -o 080-problema-istogramma-voti 080-problema-istogramma-voti.c
./080-problema-istogramma-voti
```

---

## Output atteso

> Gli indirizzi stampati cambiano a ogni esecuzione.

### 010-nome-array-e-indirizzo
```
=== IL NOME DELL'ARRAY ===
  liberi     = 0x7ffef398c630
  &liberi[0] = 0x7ffef398c630   (stesso indirizzo)
  p          = 0x7ffef398c630

=== QUATTRO MODI DI LEGGERE LO STESSO ELEMENTO ===
  aula    liberi[i] *(liberi + i)   p[i]   *(p + i)
  1              14            14     14         14
  2               3             3      3          3
  3               0             0      0          0
  4              22            22     22         22
  5               9             9      9          9

=== ARRAY E PUNTATORE NON SONO LA STESSA COSA ===
  sizeof(liberi) = 20 byte  (tutto l'array: 5 int)
  sizeof(p)      =  8 byte  (un indirizzo)
  Numero di aule calcolato: sizeof(liberi) / sizeof(liberi[0]) = 5

Dopo p++: p[0] = 3 (aula 2), liberi[0] = 14 (sempre aula 1)
```

### 020-parametri-array-e-puntatori
```
Indirizzo dell'array nel main:  0x7ffc928022c0
Dimensione dell'array nel main: 28 byte

Indirizzo ricevuto dalla funzione: 0x7ffc928022c0
sizeof(v) nella funzione:          8 byte (solo l'indirizzo)

Misure mancanti sostituite con 0: 2
Pioggia totale: 46 mm
Giorno piu' piovoso: 27 mm
```

### 030-sottoarray
```
Ingressi nell'anno:    7300

=== TRIMESTRI: somma(ingressi + 3 * t, 3) ===
  trimestre 1 (gen-mar):  2490
  trimestre 2 (apr-giu):  1540
  trimestre 3 (lug-set):   950
  trimestre 4 (ott-dic):  2320

Estate (giu-ago): somma(ingressi + 5, 3) = 740

=== SECONDO SEMESTRE: stampa(ingressi + 6, ingressi + 12, ...) ===
  lug  210
  ago  150
  set  590
  ott  780
  nov  850
  dic  690
```

### 040-problema-vendite-settimanali
```
=== INCASSI DELLA SETTIMANA ===

Feriali (lunedi-venerdi)
  totale  3605 euro, media  721 euro
  giorno migliore: venerdi con 980 euro

Fine settimana (sabato-domenica)
  totale  2680 euro, media 1340 euro
  giorno migliore: sabato con 1420 euro

Un giorno del fine settimana incassa in media 619 euro in piu' (+85%).
Incasso della settimana: 6285 euro
```

### 050-problema-posti-sul-treno
*(output dipendente dall'input – esempio di sessione)*
```
=== PRENOTAZIONE POSTI VICINI ===
  [ 1][XX][XX][ 4][ 5][ 6][XX][ 8][ 9][XX][XX][XX][13][14][15][16][XX][18][XX][XX]
  Posti liberi: 11 su 20

Persone nel gruppo (0 per finire): 2
  Prenotati i posti dal 4 al 5.
  [ 1][XX][XX][XX][XX][ 6][XX][ 8][ 9][XX][XX][XX][13][14][15][16][XX][18][XX][XX]
  Posti liberi: 9 su 20

Persone nel gruppo (0 per finire): 3
  Prenotati i posti dal 13 al 15.
  [ 1][XX][XX][XX][XX][ 6][XX][ 8][ 9][XX][XX][XX][XX][XX][XX][16][XX][18][XX][XX]
  Posti liberi: 6 su 20

Persone nel gruppo (0 per finire): 4
  Nessun gruppo di 4 posti vicini libero.

Persone nel gruppo (0 per finire): 25
  Numero non valido.

Persone nel gruppo (0 per finire): 1
  Prenotato il posto 1.
  [XX][XX][XX][XX][XX][ 6][XX][ 8][ 9][XX][XX][XX][XX][XX][XX][16][XX][18][XX][XX]
  Posti liberi: 5 su 20

Persone nel gruppo (0 per finire): 0
```

### 060-problema-primo-giorno-di-gelo
*(output dipendente dall'input – esempio di sessione)*
```
=== GELATE DI NOVEMBRE ===

Periodo, dal giorno al giorno (0 0 per finire): 1 10
  Giorni 1-10 (10 giorni), minima piu' bassa 0 gradi
  Nessun giorno di gelo.

Periodo, dal giorno al giorno (0 0 per finire): 1 30
  Giorni 1-30 (30 giorni), minima piu' bassa -5 gradi
  Primo gelo: giorno 11 (-1 gradi), giorni di gelo: 9

Periodo, dal giorno al giorno (0 0 per finire): 20 25
  Giorni 20-25 (6 giorni), minima piu' bassa -5 gradi
  Primo gelo: giorno 23 (-1 gradi), giorni di gelo: 3

Periodo, dal giorno al giorno (0 0 per finire): 25 20
  Periodo non valido: servono 1 <= a <= b <= 30.

Periodo, dal giorno al giorno (0 0 per finire): 0 0
```

### 070-problema-backup-registro
*(output dipendente dall'input – correzioni confermate)*
```
=== REGISTRO (copia di sicurezza eseguita) ===
  1. Bianchi     6
  2. Colombo     7
  3. Ferrari     5
  4. Galli       8
  5. Marino      4
  6. Ricci       9
  7. Russo       6
  8. Villa       7
Studente (1-8) e nuovo voto, 0 0 per finire: 3 8
Studente (1-8) e nuovo voto, 0 0 per finire: 6 5
Studente (1-8) e nuovo voto, 0 0 per finire: 3 7
Studente (1-8) e nuovo voto, 0 0 per finire: 9 6
  Studente inesistente.
Studente (1-8) e nuovo voto, 0 0 per finire: 2 11
  Il voto deve essere tra 1 e 10.
Studente (1-8) e nuovo voto, 0 0 per finire: 0 0

=== MODIFICHE RISPETTO ALLA COPIA ===
  Ferrari     5 ->  7
  Ricci       9 ->  5
Voti modificati: 2. Confermi? (S/N): S
Modifiche confermate.

=== REGISTRO FINALE ===
  1. Bianchi     6
  2. Colombo     7
  3. Ferrari     7
  4. Galli       8
  5. Marino      4
  6. Ricci       5
  7. Russo       6
  8. Villa       7
```

*(output dipendente dall'input – correzione annullata)*
```
=== REGISTRO (copia di sicurezza eseguita) ===
  1. Bianchi     6
  2. Colombo     7
  3. Ferrari     5
  4. Galli       8
  5. Marino      4
  6. Ricci       9
  7. Russo       6
  8. Villa       7
Studente (1-8) e nuovo voto, 0 0 per finire: 1 4
Studente (1-8) e nuovo voto, 0 0 per finire: 0 0

=== MODIFICHE RISPETTO ALLA COPIA ===
  Bianchi     6 ->  4
Voti modificati: 1. Confermi? (S/N): N
Modifiche annullate: voti ripristinati dalla copia.

=== REGISTRO FINALE ===
  1. Bianchi     6
  2. Colombo     7
  3. Ferrari     5
  4. Galli       8
  5. Marino      4
  6. Ricci       9
  7. Russo       6
  8. Villa       7
```

### 080-problema-istogramma-voti
```
=== ESITI DELLA VERIFICA (24 studenti) ===
  insufficiente   5   20%  *****
  sufficiente     7   29%  *******
  discreto        6   25%  ******
  buono           3   12%  ***
  ottimo          3   12%  ***

Fascia piu' numerosa: sufficiente (7 studenti)
Sufficienti o meglio: 19 su 24
```

---

## Errori comuni da evitare

**Calcolare la dimensione dell'array dentro la funzione**
```c
int totale(const int v[])
{
    int n = sizeof(v) / sizeof(v[0]);   /* 8 / 4 = 2: sizeof di un indirizzo */
    ...
}
```
Il numero di elementi va passato come parametro.

**Spostare il nome dell'array**
```c
int v[5];
v++;              /* errore di compilazione */
```

**Dimenticare lo scostamento del sottoarray**
```c
pos = posizione_massimo(incassi + 5, 2);
printf("%s", giorni[pos]);        /* sbagliato: lunedì o martedì */
printf("%s", giorni[5 + pos]);    /* corretto: sabato o domenica */
```

**Sottoarray che esce dall'array**
```c
somma(ingressi + 10, 5);   /* 12 mesi: gli ultimi 3 elementi non esistono */
```

**Credere che la funzione lavori su una copia**
```c
void azzera(int *v, int n);   /* modifica l'array del chiamante */
```
Se la funzione non deve modificare l'array, il parametro si dichiara `const`.

---

## Concetti collegati

- `01-aritmetica-dei-puntatori` → `p + i`, `p++`, differenza tra puntatori
- `03-stringhe-e-puntatori` → una stringa è un array di `char`
- `04-array-e-stringhe/01-array-monodimensionali` → array come parametri
- `03-puntatori-e-funzioni` → parametri per riferimento e funzioni che restituiscono puntatori

---

## Esercizi proposti

1. In `030-sottoarray.c` stampa i due semestri usando `stampa` con
   `ingressi` e `ingressi + 6`.

2. In `040-problema-vendite-settimanali.c` aggiungi una funzione
   `posizione_minimo` e stampa anche il giorno peggiore di ogni gruppo.

3. In `050-problema-posti-sul-treno.c` aggiungi la cancellazione di una
   prenotazione: dati il primo posto e il numero di posti, libera
   l'intervallo.

4. In `060-problema-primo-giorno-di-gelo.c` trova anche l'ultimo giorno di
   gelo del periodo, scorrendo il sottoarray dalla fine.

5. (Avanzato) In `070-problema-backup-registro.c` aggiungi il comando per
   ripristinare dalla copia il voto di un solo studente.
