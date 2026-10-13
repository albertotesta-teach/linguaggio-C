# 03 – realloc in pratica

## Concetto

### realloc con NULL

`realloc(NULL, byte)` si comporta come `malloc(byte)`. Un elenco può
partire vuoto e crescere sempre con `realloc`, senza un caso speciale:

```c
char **parole = NULL;
int n = 0;

tmp = realloc(parole, (n + 1) * sizeof *parole);   /* anche la prima volta */
```

Per svuotarlo si usa `free` e si rimette il puntatore a `NULL` (mai
`realloc(p, 0)`).

### Il costo della crescita

Ogni `realloc` che sposta il blocco copia tutti gli elementi. Crescendo
di un elemento alla volta, per n elementi si copiano nel caso peggiore
n (n - 1) / 2 elementi:

| elementi | crescita | realloc | copie (caso peggiore) |
|----------|----------|---------|-----------------------|
| 10 000 | +1 | 10 000 | 49 995 000 |
| 10 000 | +16 | 625 | 3 120 000 |

`03-array-dinamici` mostra una strategia con un costo molto più basso.

### Indici, non puntatori

```c
Studente *capoclasse = &classe[2];     /* dopo realloc può essere pendente */
int capoclasse = 2;                    /* classe[capoclasse] è sempre corretto */
```

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-realloc-casi-limite.c` | Elenco che parte da `NULL`, svuotato con `free` e ripreso |
| `020-quanto-costa-crescere.c` | realloc e copie crescendo di 1 e di 16 elementi |
| `030-puntatori-invalidati.c` | Il capoclasse ricordato con l'indice dopo una realloc |
| `040-problema-riga-di-lunghezza-qualsiasi.c` | Risposte del questionario lette con `getchar` in un blocco che cresce |
| `040-problema-riga-di-lunghezza-qualsiasi-analisi.md` | Analisi di `040-problema-riga-di-lunghezza-qualsiasi.c` |
| `050-problema-elenco-di-parole.c` | Parole distinte di un tema e ripetizioni |
| `050-problema-elenco-di-parole-analisi.md` | Analisi di `050-problema-elenco-di-parole.c` |
| `060-problema-prenotazioni-con-indici.c` | Postazioni che aumentano e prenotazioni con indici |
| `060-problema-prenotazioni-con-indici-analisi.md` | Analisi di `060-problema-prenotazioni-con-indici.c` |
| `070-problema-registro-che-cresce.c` | Righe del registro aggiunte e tolte |
| `070-problema-registro-che-cresce-analisi.md` | Analisi di `070-problema-registro-che-cresce.c` |
| `080-problema-archivio-dei-sensori.c` | Un blocco di letture per sensore, ridimensionato con il periodo |
| `080-problema-archivio-dei-sensori-analisi.md` | Analisi di `080-problema-archivio-dei-sensori.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-realloc-casi-limite 010-realloc-casi-limite.c
./010-realloc-casi-limite

gcc -Wall -Wextra -o 020-quanto-costa-crescere 020-quanto-costa-crescere.c
./020-quanto-costa-crescere

gcc -Wall -Wextra -o 030-puntatori-invalidati 030-puntatori-invalidati.c
./030-puntatori-invalidati

gcc -Wall -Wextra -o 040-problema-riga-di-lunghezza-qualsiasi 040-problema-riga-di-lunghezza-qualsiasi.c
./040-problema-riga-di-lunghezza-qualsiasi

gcc -Wall -Wextra -o 050-problema-elenco-di-parole 050-problema-elenco-di-parole.c
./050-problema-elenco-di-parole

gcc -Wall -Wextra -o 060-problema-prenotazioni-con-indici 060-problema-prenotazioni-con-indici.c
./060-problema-prenotazioni-con-indici

gcc -Wall -Wextra -o 070-problema-registro-che-cresce 070-problema-registro-che-cresce.c
./070-problema-registro-che-cresce

gcc -Wall -Wextra -o 080-problema-archivio-dei-sensori 080-problema-archivio-dei-sensori.c
./080-problema-archivio-dei-sensori
```

Gli indirizzi stampati cambiano da un'esecuzione all'altra.

---

## Output atteso

### 010-realloc-casi-limite
```
Elenco vuoto: puntatore NULL, n = 0
aggiunto "Il barone rampante" (titoli: 1)
aggiunto "Marcovaldo" (titoli: 2)
aggiunto "Lessico famigliare" (titoli: 3)
  1. Il barone rampante
  2. Marcovaldo
  3. Lessico famigliare

Elenco svuotato con free: n = 0
Si riparte da NULL (titoli: 1)
  1. Il giornalino di Gian Burrasca
```

### 020-quanto-costa-crescere
```
elementi  crescita      realloc    copie (max)
     100  +1                100           4950
     100  +16                 7            336
    1000  +1               1000         499500
    1000  +16                63          31248
   10000  +1              10000       49995000
   10000  +16               625        3120000
```

### 030-puntatori-invalidati
```
Capoclasse: Sara, elemento 2, in 0x55a1e380f2d0
Dopo realloc l'elemento 2 sta in 0x55a1e3810350
Il blocco si e' spostato: un puntatore salvato prima sarebbe pendente.
Con l'indice: capoclasse Sara, voto 8.0
```

### 040-problema-riga-di-lunghezza-qualsiasi
*(output dipendente dall'input – tre risposte)*
```
Risposte (FINE per terminare):
Piu' laboratori.
  16 caratteri, ingrandimenti del blocco: 1
Vorrei che le ore di informatica fossero di piu' e che si facessero progetti di gruppo con una consegna finale, come nelle aziende.
  131 caratteri, ingrandimenti del blocco: 8

Niente da aggiungere
  20 caratteri, ingrandimenti del blocco: 1
FINE

Risposte raccolte: 3
  1. ( 16) Piu' laboratori.
  2. (131) Vorrei che le ore di informati...
  3. ( 20) Niente da aggiungere
La piu' lunga per intero:
  Vorrei che le ore di informatica fossero di piu' e che si facessero progetti di gruppo con una consegna finale, come nelle aziende.
```

### 050-problema-elenco-di-parole
*(output dipendente dall'input – tema sulla gita)*
```
Testo del tema (FINE per terminare):
La gita a Torino e' stata molto bella. Abbiamo visto il museo egizio,
che e' molto grande, e poi il museo del cinema, molto bello.
La sera siamo tornati molto stanchi ma felici: e' stata una bella gita.
FINE

Parole: 38, distinte: 26
Ripetute almeno 3 volte:
  e            4
  molto        4
```

### 060-problema-prenotazioni-con-indici
*(output dipendente dall'input – esempio di sessione)*
```
Postazioni iniziali: 2
Comando (N, G, P, E, Q): P Marta
  Marta: PC-01
Comando (N, G, P, E, Q): P Luca
  Luca: PC-02
Comando (N, G, P, E, Q): P Sara
  Nessuna postazione libera.
Comando (N, G, P, E, Q): N 2
  postazioni: 4 (blocco in 0x55f47bb09b30)
Comando (N, G, P, E, Q): P Sara
  Sara: PC-03
Comando (N, G, P, E, Q): G 1
  PC-01 guasta
  prenotazione di Marta spostata su PC-04
Comando (N, G, P, E, Q): G 2
  PC-02 guasta
  Luca resta senza postazione
Comando (N, G, P, E, Q): E
  Marta      PC-04
  Luca       (nessuna)
  Sara       PC-03
  postazioni: 4, prenotazioni: 3
Comando (N, G, P, E, Q): Q
```

### 070-problema-registro-che-cresce
*(output dipendente dall'input – esempio di sessione)*
```
Comando (A, T, S, Q): S
  registro vuoto
Comando (A, T, S, Q): A Marta 7 6.5 8
  ingresso di Marta: righe 1, 24 byte di voti
Comando (A, T, S, Q): A Luca 5 6 5.5
  ingresso di Luca: righe 2, 48 byte di voti
Comando (A, T, S, Q): A Sara 8 9 7.5
  ingresso di Sara: righe 3, 72 byte di voti
Comando (A, T, S, Q): A Luca 6 6 6
  Luca e' gia' nel registro.
Comando (A, T, S, Q): T Luca
  uscita di Luca: righe 2
Comando (A, T, S, Q): T Paolo
  Paolo non e' nel registro.
Comando (A, T, S, Q): S
              ITA  MAT  ING  media
  Marta       7.0  6.5  8.0   7.17
  Sara        8.0  9.0  7.5   8.17
Comando (A, T, S, Q): T Marta
  uscita di Marta: righe 1
Comando (A, T, S, Q): T Sara
  uscita di Sara: righe 0
Comando (A, T, S, Q): S
  registro vuoto
Comando (A, T, S, Q): Q
```

### 080-problema-archivio-dei-sensori
*(output dipendente dall'input – due aule)*
```
Numero di sensori e nomi delle aule: 2 LAB1 3B
Comando (P, L, M, Q): L LAB1 1 20
  Periodo non ancora impostato (comando P).
Comando (P, L, M, Q): P 4
  periodo di 4 ore: 32 byte per sensore
Comando (P, L, M, Q): L LAB1 1 19.5
  LAB1, ora 1: 19.5 gradi
Comando (P, L, M, Q): L LAB1 2 21
  LAB1, ora 2: 21.0 gradi
Comando (P, L, M, Q): L 3B 4 23.5
  3B, ora 4: 23.5 gradi
Comando (P, L, M, Q): L 3B 5 22
  Ora fuori dal periodo (1-4).
Comando (P, L, M, Q): L 4C 1 20
  Aula sconosciuta.
Comando (P, L, M, Q): M
  LAB1     letture 2 su 4, media 20.2, min 19.5, max 21.0
  3B       letture 1 su 4, media 23.5, min 23.5, max 23.5
Comando (P, L, M, Q): P 2
  periodo di 2 ore: 16 byte per sensore
Comando (P, L, M, Q): M
  LAB1     letture 2 su 2, media 20.2, min 19.5, max 21.0
  3B       letture 0 su 2
Comando (P, L, M, Q): P 6
  periodo di 6 ore: 48 byte per sensore
Comando (P, L, M, Q): M
  LAB1     letture 2 su 6, media 20.2, min 19.5, max 21.0
  3B       letture 0 su 6
Comando (P, L, M, Q): Q
```

---

## Errori comuni da evitare

**Chiamare realloc con dimensione zero**
```c
v = realloc(v, 0);                 /* comportamento non portabile */
free(v); v = NULL; n = 0;          /* corretto */
```

**Tenere un puntatore a un elemento di un blocco che cresce**
```c
Postazione *mia = &pc[3];
nuove_postazioni(&pc, &n_pc, 2);   /* mia può essere pendente */
```

**Far crescere i due array di un elenco in modo incoerente**
```c
/* se la seconda realloc fallisce, il primo array ha già un elemento in più:
   n si incrementa solo quando entrambe sono riuscite */
```

**Svuotare l'array di puntatori senza liberare i blocchi**
```c
free(parole);                      /* le singole parole restano allocate */
for (i = 0; i < n; i++) { free(parole[i]); }  free(parole);   /* corretto */
```

---

## Concetti collegati

- `02-realloc` → puntatore temporaneo e riduzione
- `01-calloc` → array di struct con puntatori a `NULL`
- `03-array-dinamici` → crescita efficiente e un tipo riutilizzabile
- `10-strutture-dati` → strutture che crescono un nodo alla volta

---

## Esercizi proposti

1. In `010-realloc-casi-limite.c` aggiungi una funzione che toglie
   l'ultimo titolo riducendo il blocco (e lo libera quando resta vuoto).

2. In `020-quanto-costa-crescere.c` aggiungi la crescita a blocchi di 100
   e confronta i numeri.

3. In `050-problema-elenco-di-parole.c` stampa le parole in ordine
   alfabetico scambiando i puntatori.

4. In `070-problema-registro-che-cresce.c` aggiungi il comando per
   modificare un voto di uno studente cercato per nome.

5. (Avanzato) In `080-problema-archivio-dei-sensori.c` aggiungi un
   sensore nuovo durante il programma, ingrandendo l'array dei sensori.
