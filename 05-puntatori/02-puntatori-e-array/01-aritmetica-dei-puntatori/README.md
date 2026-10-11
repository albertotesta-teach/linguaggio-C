# 01 – Aritmetica dei puntatori

## Concetto

Quando un puntatore indica un elemento di un array, si può **spostare** sugli
altri elementi con le operazioni dell'aritmetica dei puntatori.

```c
int v[5] = {12, 0, 7, 25, 3};
int *p = &v[0];

*(p + 2) = 9;        /* v[2] vale 9 */
p++;                 /* p punta a v[1] */
```

| Espressione | Significato |
|-------------|-------------|
| `p + i` | indirizzo dell'elemento `i` posizioni dopo quello puntato da `p` |
| `*(p + i)` | l'elemento stesso, in lettura e scrittura |
| `p++`, `p--` | `p` passa all'elemento successivo o precedente |
| `q - p` | numero di elementi tra `p` e `q` |
| `p < q`, `p == q` | confronto di posizione nello stesso array |

### L'indirizzo cresce di `sizeof(*p)` byte

`p + 1` non è l'indirizzo successivo di un byte: è l'indirizzo
dell'**elemento** successivo. Il compilatore moltiplica per la dimensione
del tipo puntato.

| Puntatore | `p` | `p + 1` | `p + 2` |
|-----------|-----|---------|---------|
| `int *p` | `...ba0` | `...ba4` | `...ba8` |
| `double *q` | `...bb0` | `...bb8` | `...bc0` |

Gli indirizzi sono in esadecimale e abbreviati alle ultime cifre: dopo
`...ba9` vengono `...baa`, `...bab`, `...bac`.

### Scorrere un array con un puntatore

```c
const int *fine = &v[0] + N;     /* subito dopo l'ultimo elemento */
const int *p;

for (p = &v[0]; p < fine; p++) {
    printf("%d\n", *p);
}
```

`fine` si può calcolare e confrontare, ma **non si dereferenzia mai**: dopo
l'ultimo elemento non c'è nulla che appartenga all'array.

### Differenza: dall'indirizzo all'indice

`p - &v[0]` è l'**indice** dell'elemento puntato. È il modo per sapere *in
che posizione* si trova l'elemento trovato da un puntatore: l'ora di punta,
il km della cima, la giornata di inizio di una serie.

Sottrarre o confrontare puntatori ha senso solo se puntano allo **stesso
array**.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-somma-di-un-intero.c` | `p + i` e `*(p + i)` con array di `int` e di `double` |
| `020-incremento-e-scorrimento.c` | Scorrimento con `p++` fino a `fine`, all'indietro con `p--` |
| `030-differenza-e-confronto.c` | `q - p`, `p < q`, `p == q` sul profilo di un sentiero |
| `040-problema-media-mobile.c` | Media mobile della CO2 in aula con un puntatore alla finestra di 3 letture |
| `040-problema-media-mobile-analisi.md` | Analisi di `040-problema-media-mobile.c` |
| `050-problema-ora-di-punta.c` | Puntatore al consumo massimo e fascia di alto consumo |
| `050-problema-ora-di-punta-analisi.md` | Analisi di `050-problema-ora-di-punta.c` |
| `060-problema-inverti-percorso.c` | Inversione di un array con due puntatori agli estremi |
| `060-problema-inverti-percorso-analisi.md` | Analisi di `060-problema-inverti-percorso.c` |
| `070-problema-serie-di-vittorie.c` | Puntatore all'inizio della serie in corso, serie più lunga |
| `070-problema-serie-di-vittorie-analisi.md` | Analisi di `070-problema-serie-di-vittorie.c` |
| `080-problema-classifica-unita.c` | Fusione di due elenchi ordinati con tre puntatori |
| `080-problema-classifica-unita-analisi.md` | Analisi di `080-problema-classifica-unita.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-somma-di-un-intero 010-somma-di-un-intero.c
./010-somma-di-un-intero

gcc -Wall -Wextra -o 020-incremento-e-scorrimento 020-incremento-e-scorrimento.c
./020-incremento-e-scorrimento

gcc -Wall -Wextra -o 030-differenza-e-confronto 030-differenza-e-confronto.c
./030-differenza-e-confronto

gcc -Wall -Wextra -o 040-problema-media-mobile 040-problema-media-mobile.c
./040-problema-media-mobile

gcc -Wall -Wextra -o 050-problema-ora-di-punta 050-problema-ora-di-punta.c
./050-problema-ora-di-punta

gcc -Wall -Wextra -o 060-problema-inverti-percorso 060-problema-inverti-percorso.c
./060-problema-inverti-percorso

gcc -Wall -Wextra -o 070-problema-serie-di-vittorie 070-problema-serie-di-vittorie.c
./070-problema-serie-di-vittorie

gcc -Wall -Wextra -o 080-problema-classifica-unita 080-problema-classifica-unita.c
./080-problema-classifica-unita
```

---

## Output atteso

> Gli indirizzi stampati cambiano a ogni esecuzione.

### 010-somma-di-un-intero
```
=== p + i CON UN ARRAY DI int (4 byte per elemento) ===
  p + 0 = 0x7fffa78d7930   *(p + 0) = 12 posti liberi al piano 0
  p + 1 = 0x7fffa78d7934   *(p + 1) =  0 posti liberi al piano 1
  p + 2 = 0x7fffa78d7938   *(p + 2) =  7 posti liberi al piano 2
  p + 3 = 0x7fffa78d793c   *(p + 3) = 25 posti liberi al piano 3

=== q + i CON UN ARRAY DI double (8 byte per elemento) ===
  q + 0 = 0x7fffa78d7940   *(q + 0) = 1.50 euro/ora
  q + 1 = 0x7fffa78d7948   *(q + 1) = 1.80 euro/ora
  q + 2 = 0x7fffa78d7950   *(q + 2) = 2.00 euro/ora
  q + 3 = 0x7fffa78d7958   *(q + 3) = 2.50 euro/ora

Dopo *(p + 1) = *(p + 1) + 3:  liberi[1] = 3

*(p + 2) =  7   elemento di indice 2
*p + 2   = 14   valore di liberi[0] piu' 2
```

### 020-incremento-e-scorrimento
```
=== CONTAPASSI: SCORRIMENTO CON p++ ===
  giorno 1   p = 0x7fff5d06d640   *p =  6420
  giorno 2   p = 0x7fff5d06d644   *p =  8150   obiettivo raggiunto
  giorno 3   p = 0x7fff5d06d648   *p =  4980
  giorno 4   p = 0x7fff5d06d64c   *p = 10230   obiettivo raggiunto
  giorno 5   p = 0x7fff5d06d650   *p =  7600
  giorno 6   p = 0x7fff5d06d654   *p = 12890   obiettivo raggiunto
  giorno 7   p = 0x7fff5d06d658   *p =  3150
Totale 53420 passi, media 7631 al giorno, obiettivo raggiunto 3 volte su 7

=== ULTIMI 3 GIORNI, DAL PIU' RECENTE (p--) ===
  giorno 7:  3150 passi
  giorno 6: 12890 passi
  giorno 5:  7600 passi
```

### 030-differenza-e-confronto
```
=== PROFILO DEL SENTIERO ===
Punti misurati: fine - inizio = 8
Cima: 2390 m al km 6   (cima - inizio = 6)
Dopo la cima il sentiero continua per 1 km.
Oltre il bosco (2000 m) dal km 4
Si esce dal bosco 2 km prima della cima.
```

### 040-problema-media-mobile
```
=== MEDIA MOBILE DELLA CO2 (gruppi di 3 letture) ===
  08:00-08:10    620  700  790   media  703 ppm
  08:05-08:15    700  790  880   media  790 ppm
  08:10-08:20    790  880  960   media  876 ppm
  08:15-08:25    880  960 1050   media  963 ppm
  08:20-08:30    960 1050 1120   media 1043 ppm   <- aprire le finestre
  08:25-08:35   1050 1120 1080   media 1083 ppm   <- aprire le finestre
  08:30-08:40   1120 1080  870   media 1023 ppm   <- aprire le finestre
  08:35-08:45   1080  870  760   media  903 ppm
  08:40-08:50    870  760  820   media  816 ppm
  08:45-08:55    760  820  910   media  830 ppm

Primo allarme sul gruppo che inizia alle 08:20 (3 gruppi oltre soglia).
```

### 050-problema-ora-di-punta
```
=== CONSUMI ORARI (un # ogni 5 kWh) ===
  00:00   8 #
  01:00   8 #
  02:00   7 #
  03:00   7 #
  04:00   7 #
  05:00   8 #
  06:00  12 ##
  07:00  25 #####
  08:00  48 #########
  09:00  62 ############
  10:00  66 #############
  11:00  70 ##############  <- ora di punta
  12:00  58 ###########
  13:00  52 ##########
  14:00  64 ############
  15:00  61 ############
  16:00  45 #########
  17:00  30 ######
  18:00  18 ###
  19:00  14 ##
  20:00  12 ##
  21:00  10 ##
  22:00   9 #
  23:00   8 #

Consumo totale: 709 kWh
Ora di punta: 11:00-12:00 con 70 kWh
Alto consumo (almeno 56 kWh, 80% del massimo): dalle 09:00 alle 16:00, 7 ore
```

### 060-problema-inverti-percorso
```
=== ANDATA ===
  Paese      -> Mulino       5.2 km    +40 m
  Mulino     -> Cascina      3.8 km    -15 m
  Cascina    -> Belvedere    6.1 km   +120 m
  Belvedere  -> Santuario    2.7 km    +85 m
  Totale 17.8 km, 245 m di salita

=== RITORNO ===
  Santuario  -> Belvedere    2.7 km    -85 m
  Belvedere  -> Cascina      6.1 km   -120 m
  Cascina    -> Mulino       3.8 km    +15 m
  Mulino     -> Paese        5.2 km    -40 m
  Totale 17.8 km, 15 m di salita
```

### 070-problema-serie-di-vittorie
```
=== RISULTATI ===
  V V P V V V S V V V V P S V V 

Punti in classifica: 35 in 15 giornate
Serie piu' lunga: 4 vittorie consecutive, dalla giornata 8 alla 11
```

### 080-problema-classifica-unita
```
=== CLASSIFICA FINALE 100 METRI ===
  1. 11.79 s   batteria B   medaglia
  2. 11.85 s   batteria A   medaglia
  3. 12.12 s   batteria A   medaglia
  4. 12.26 s   batteria B
  5. 12.38 s   batteria B
  6. 12.40 s   batteria A
  7. 12.90 s   batteria B
  8. 13.01 s   batteria A
  9. 13.55 s   batteria A
Posizioni scritte: pc - &classifica[0] = 9
```

---

## Errori comuni da evitare

**Dimenticare le parentesi**
```c
x = *p + 2;       /* valore puntato più 2 */
x = *(p + 2);     /* elemento due posizioni più avanti */
```

**Dereferenziare `fine`**
```c
const int *fine = &v[0] + N;
x = *fine;        /* fuori dall'array: valore casuale o interruzione */
```

**Uscire dall'array con lo spostamento**
```c
for (f = &v[0]; f < fine; f++) {
    media = (*f + *(f + 1) + *(f + 2)) / 3;   /* gli ultimi due gruppi escono */
}
/* corretto: f <= fine - 3 */
```

**Pensare che `p + 1` aggiunga un byte**
```c
double *q = &prezzi[0];
q + 1;            /* 8 byte più avanti, non 1 */
```

**Confrontare puntatori ad array diversi**
```c
if (&a[2] < &b[0])   /* nessun significato: dipende da dove sono gli array */
```

---

## Concetti collegati

- `01-introduzione-ai-puntatori` → `&`, `*`, `NULL`, `const`
- `02-array-come-puntatori` → il nome dell'array come indirizzo del primo elemento
- `03-stringhe-e-puntatori` → scorrere una stringa fino a `'\0'`

---

## Esercizi proposti

1. In `020-incremento-e-scorrimento.c` stampa i giorni pari (2, 4, 6)
   spostando il puntatore di due posizioni alla volta.

2. In `040-problema-media-mobile.c` porta la finestra a 4 letture usando un
   ciclo interno al posto delle tre somme scritte a mano.

3. In `050-problema-ora-di-punta.c` trova anche l'ora con il consumo minimo
   tra le 8:00 e le 18:00.

4. In `070-problema-serie-di-vittorie.c` trova anche la serie più lunga di
   partite senza sconfitte (`V` o `P`).

5. (Avanzato) In `080-problema-classifica-unita.c` aggiungi una terza
   batteria e fondi i tre elenchi.
