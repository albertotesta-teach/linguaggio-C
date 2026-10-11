# 03 – Errori e puntatori sicuri

## Concetto

Gli errori con i puntatori sono insidiosi: spesso il programma **non** si
ferma subito, ma scrive in un punto sbagliato della memoria e il problema
si manifesta più tardi, in un'altra parte del codice.

### I quattro errori tipici

| Errore | Codice sbagliato | Conseguenza |
|--------|------------------|-------------|
| Puntatore non inizializzato | `int *p; *p = 5;` | scrittura in un punto casuale |
| Dereferenziazione di `NULL` | `int *p = NULL; *p = 5;` | interruzione del programma |
| `scanf` senza `&` | `scanf("%d", n);` | scrittura in un punto casuale |
| Variabile che non esiste più | `{ int t; p = &t; }  *p = 1;` | l'indirizzo non è più valido |

### Due regole

1. Ogni puntatore si **inizializza** alla dichiarazione: con un indirizzo
   valido oppure con `NULL`.
2. Una funzione che riceve un puntatore che può essere `NULL` lo **controlla**
   prima di usarlo.

```c
int incrementa(int *contatore)
{
    int fatto = 0;
    if (contatore != NULL) {
        *contatore = *contatore + 1;
        fatto = 1;
    }
    return fatto;
}
```

`NULL` è utile anche come scelta voluta: un parametro OUT facoltativo
(`statistiche(v, n, NULL, NULL, &media)`) o una selezione non valida.

### Il tipo del puntatore

`*p` legge `sizeof(*p)` byte e li interpreta secondo il tipo: per questo un
`int *` non può puntare a un `double`. Copiare **valori** tra tipi diversi
(`*pd = *pi`) è invece una normale conversione.

### `const` con i puntatori

| Dichiarazione | Si può cambiare `*p`? | Si può cambiare `p`? |
|---------------|-----------------------|----------------------|
| `const int *p` | no | sì |
| `int *const p = &x` | sì | no |
| `const int *const p = &x` | no | no |

Nei parametri, `const int *` dice che la funzione **legge** la variabile del
chiamante ma non la modifica: se per errore provasse a farlo, il
compilatore lo segnalerebbe.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-non-inizializzato-e-null.c` | Regole di inizializzazione e controllo di `NULL` (tornelli) |
| `020-tipi-dei-puntatori.c` | Che cosa legge `*p` in base al tipo; copia di valori tra tipi |
| `030-puntatori-const.c` | `const int *`, `int *const`, `const int *const`, parametri `const` |
| `040-problema-configurazione-sola-lettura.c` | Limiti di una cassa audio passati come `const int *` |
| `040-problema-configurazione-sola-lettura-analisi.md` | Analisi di `040-problema-configurazione-sola-lettura.c` |
| `050-problema-statistiche-facoltative.c` | Parametri OUT facoltativi: `NULL` = risultato non richiesto |
| `050-problema-statistiche-facoltative-analisi.md` | Analisi di `050-problema-statistiche-facoltative.c` |
| `060-problema-correzione-errori.c` | I quattro errori tipici riconosciuti e corretti |
| `060-problema-correzione-errori-analisi.md` | Analisi di `060-problema-correzione-errori.c` |
| `070-problema-selezione-sicura.c` | Impostazioni di una lavatrice con puntatori e limiti controllati |
| `070-problema-selezione-sicura-analisi.md` | Analisi di `070-problema-selezione-sicura.c` |
| `080-problema-limiti-di-sicurezza.c` | Pressa industriale: puntatori costanti e soglie di sola lettura |
| `080-problema-limiti-di-sicurezza-analisi.md` | Analisi di `080-problema-limiti-di-sicurezza.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-non-inizializzato-e-null 010-non-inizializzato-e-null.c
./010-non-inizializzato-e-null

gcc -Wall -Wextra -o 020-tipi-dei-puntatori 020-tipi-dei-puntatori.c
./020-tipi-dei-puntatori

gcc -Wall -Wextra -o 030-puntatori-const 030-puntatori-const.c
./030-puntatori-const

gcc -Wall -Wextra -o 040-problema-configurazione-sola-lettura 040-problema-configurazione-sola-lettura.c
./040-problema-configurazione-sola-lettura

gcc -Wall -Wextra -o 050-problema-statistiche-facoltative 050-problema-statistiche-facoltative.c
./050-problema-statistiche-facoltative

gcc -Wall -Wextra -o 060-problema-correzione-errori 060-problema-correzione-errori.c
./060-problema-correzione-errori

gcc -Wall -Wextra -o 070-problema-selezione-sicura 070-problema-selezione-sicura.c
./070-problema-selezione-sicura

gcc -Wall -Wextra -o 080-problema-limiti-di-sicurezza 080-problema-limiti-di-sicurezza.c
./080-problema-limiti-di-sicurezza
```

---

## Output atteso

### 010-non-inizializzato-e-null
```
Evento I: registrato (ingressi 1, uscite 0)
Evento I: registrato (ingressi 2, uscite 0)
Evento U: registrato (ingressi 2, uscite 1)
Evento I: registrato (ingressi 3, uscite 1)
Evento ?: non registrato: puntatore NULL
Evento I: registrato (ingressi 4, uscite 1)
Evento U: registrato (ingressi 4, uscite 2)

Presenti nell'edificio: 2
```

### 020-tipi-dei-puntatori
```
=== Che cosa legge *p ===
  *pi = 8      legge sizeof(*pi) = 4 byte
  *pd = 7.50   legge sizeof(*pd) = 8 byte
  *pc = B      legge sizeof(*pc) = 1 byte
  ma i puntatori occupano tutti 8 byte

=== Copiare valori tra tipi diversi ===
  *pd = *pi  -> media = 8.00
  *pi = (int) *pd con *pd = 6.75 -> voto = 6
```

### 030-puntatori-const
```
sola_lettura -> 215
sola_lettura -> 87 (ora punta a esterna)
esterna = 92 (scritta tramite sensore)
limite -> 300

Funzione con parametro const int *:
  21.5 gradi
  9.2 gradi
```

### 040-problema-configurazione-sola-lettura
```
Limiti dell'istituto: volume 70, bassi 8, luce 100
Impostazioni attuali: volume 40, bassi 5, luce 60%
Richiesta V = 65: applicata
Richiesta B = 12: ridotta al massimo consentito (8)
Richiesta V = 90: ridotta al massimo consentito (70)
Richiesta L = 80: applicata
Richiesta B = 3: applicata
Richiesta X = 50: impostazione sconosciuta, ignorata
Impostazioni attuali: volume 70, bassi 3, luce 80%
```

### 050-problema-statistiche-facoltative
```
Verifica completa: minimo 4, massimo 9, media 6.50
Per la pagella serve solo la media: 6.50
Controllo insufficienze: voto minimo 4 -> ci sono insufficienze
Verifica senza voti: statistiche non disponibili
```

### 060-problema-correzione-errori
*(output dipendente dall'input – socio da 12 anni)*
```
Anni di iscrizione: 12
Socio da 12 anni: sconto 20%, prezzo 305 euro
(compresa la promozione fedelta' di 15 euro)
```

*(output dipendente dall'input – nuovo iscritto)*
```
Anni di iscrizione: 0
Socio da 0 anni: sconto 0%, prezzo 400 euro
```

### 070-problema-selezione-sicura
*(output dipendente dall'input – esempio di sessione)*
```
=== LAVATRICE ===
Impostazione (T gradi | C giri | D minuti), riga vuota per avviare: T 40
  impostato 40
Impostazione: C 1600
  valore fuori dai limiti 400-1400
Impostazione: C 1200
  impostato 1200
Impostazione: Z 5
  richiesta non valida
Impostazione: D
  richiesta non valida
Impostazione: D 90
  impostato 90
Impostazione: 

Avvio: 40 gradi, 1200 giri, 90 minuti
```

### 080-problema-limiti-di-sicurezza
```
Soglie: allarme 180 bar, arresto 210 bar
  lettura  1: 120 bar  normale
  lettura  2: 150 bar  normale
  lettura  3: 175 bar  normale
  lettura  4: 182 bar  allarme
  lettura  5: 168 bar  normale
  lettura  6: 190 bar  allarme
  lettura  7: 205 bar  allarme
  lettura  8: 214 bar  ARRESTO DI EMERGENZA
  lettura  9: 160 bar  (pressa ferma)
  lettura 10: 140 bar  (pressa ferma)

Allarmi: 3, pressione massima: 214 bar, pressa in arresto
```

---

## Errori comuni da evitare

**Usare un puntatore prima di assegnarlo**
```c
int *p;
if (*p > 0)          /* p non punta a nulla */
```

**Controllare `NULL` dopo averlo già usato**
```c
x = *p;
if (p != NULL)       /* troppo tardi */
```

**Restituire o conservare l'indirizzo di una variabile temporanea**
```c
{
    int t = 5;
    p = &t;
}
x = *p;              /* t non esiste più */
```

**Togliere `const` per "far compilare"**
```c
const int massimo = 70;
int *p = &massimo;   /* avviso: si perde la protezione */
```

**Leggere `const int *p` come "puntatore costante"**
```c
const int *p;        /* è il VALORE puntato a essere costante, non p */
```

---

## Concetti collegati

- `02-dichiarazione-e-dereferenziazione` → `NULL` come "nessuna selezione"
- `03-funzioni/04-scope-e-visibilita` → quando una variabile smette di esistere
- `03-puntatori-e-funzioni/02-funzioni-che-restituiscono-puntatori` → mai restituire l'indirizzo di una variabile locale

---

## Esercizi proposti

1. In `010-non-inizializzato-e-null.c` aggiungi un terzo contatore per gli
   accessi del personale (`P`).

2. In `050-problema-statistiche-facoltative.c` aggiungi un quarto parametro
   facoltativo `int *insufficienti` che conta i voti sotto il 6.

3. In `070-problema-selezione-sicura.c` aggiungi il programma "eco" che
   imposta insieme i tre valori al minimo consentito.

4. In `080-problema-limiti-di-sicurezza.c` aggiungi una soglia minima
   (pressione troppo bassa) con un puntatore `const int *const`.

5. (Avanzato) Scrivi `void scambia_sicuro(int *a, int *b)` che non fa nulla
   se uno dei due puntatori è `NULL` o se puntano alla stessa variabile.
