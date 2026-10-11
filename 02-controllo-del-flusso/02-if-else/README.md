# 02 – If-else

## Concetto

Un programma senza strutture di controllo esegue tutte le istruzioni in
sequenza. L'istruzione `if` introduce la **selezione**: un blocco viene
eseguito solo se una condizione è vera.

> L'`if/else` è già comparso nel capitolo 01, prima di essere spiegato:
> - `01-introduzione/02-variabili-e-tipi/060-problema-calcolo-area.c` lo usa
>   per scegliere la figura geometrica (catena `if` / `else if`);
> - `01-introduzione/02-variabili-e-tipi/020-tipi-reali.c` lo cita nei commenti
>   sul confronto tra numeri reali.
>
> Questa sezione presenta il costrutto in modo completo.

### Le tre forme

```
  if (cond) {          if (cond) {          if (c1) {
      A                    A                    A
  }                    } else {             } else if (c2) {
                           B                    B
                       }                    } else {
                                                C
                                            }

  A solo se cond       A oppure B           il primo ramo con condizione
  è vera               (mai entrambi)       vera; C se nessuna lo è
```

### Catena else-if

Le condizioni si valutano **dall'alto in basso** e si esegue solo il primo
ramo con condizione vera. Grazie all'ordine, ogni condizione può dare per
scontato che le precedenti siano false: si parte quindi dal caso più
restrittivo.

```c
if (punteggio >= 90) {          /* qui punteggio >= 90          */
    ...
} else if (punteggio >= 70) {   /* qui 70 <= punteggio < 90     */
    ...
} else {                        /* qui punteggio < 70           */
    ...
}
```

### If annidati

Un `if` dentro un ramo di un altro `if` serve quando una domanda ha senso
solo dopo aver risposto alla precedente (esiste l'utente? → il PIN è
corretto?). Due `if` annidati **senza else** equivalgono a un solo `if` con `&&`.

### Le graffe si scrivono sempre

Senza graffe l'`if` controlla una sola istruzione, e un `else` si associa
all'`if` **più vicino** ancora senza `else` (*dangling else*), qualunque sia
l'indentazione. Nel corso le graffe si scrivono sempre.

### If-else o operatore ternario?

| Serve... | Si usa |
|----------|--------|
| scegliere tra due **valori** | `cond ? valore1 : valore2` |
| eseguire **istruzioni** diverse | `if-else` |

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-if-semplice.c` | If con un solo ramo: allerta, modifica di un valore di default, condizione salvata in un flag |
| `020-if-else.c` | Due alternative: pari/dispari, maggiore tra due numeri, prelievo consentito o rifiutato, confronto con il ternario |
| `030-if-annidati-e-catene.c` | Catena else-if, if annidati, annidamento e `&&`, dangling else |
| `040-problema-equazione-secondo-grado.c` | Equazione di secondo grado con tutti i casi, compreso a = 0 |
| `040-problema-equazione-secondo-grado-analisi.md` | Analisi di `040-problema-equazione-secondo-grado.c` |
| `050-problema-tariffa-biglietto.c` | Tariffa di un museo per età e tessera, sconto del martedì |
| `050-problema-tariffa-biglietto-analisi.md` | Analisi di `050-problema-tariffa-biglietto.c` |
| `060-problema-classificazione-triangolo.c` | Validità del triangolo, classificazione per lati, triangolo rettangolo |
| `060-problema-classificazione-triangolo-analisi.md` | Analisi di `060-problema-classificazione-triangolo.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-if-semplice 010-if-semplice.c
./010-if-semplice

gcc -Wall -Wextra -o 020-if-else 020-if-else.c
./020-if-else

gcc -Wall -Wextra -o 030-if-annidati-e-catene 030-if-annidati-e-catene.c
./030-if-annidati-e-catene

gcc -Wall -Wextra -o 040-problema-equazione-secondo-grado 040-problema-equazione-secondo-grado.c -lm
./040-problema-equazione-secondo-grado

gcc -Wall -Wextra -o 050-problema-tariffa-biglietto 050-problema-tariffa-biglietto.c
./050-problema-tariffa-biglietto

gcc -Wall -Wextra -o 060-problema-classificazione-triangolo 060-problema-classificazione-triangolo.c
./060-problema-classificazione-triangolo
```

`040-problema-equazione-secondo-grado.c` usa `sqrt()` di `<math.h>`: su Linux
richiede l'opzione `-lm` (su macOS non serve, ma non dà fastidio).

---

## Output atteso

### 010-if-semplice
```
=== Allerta caldo ===
Temperatura: 33 gradi
ATTENZIONE: temperatura sopra i 30 gradi, bere molta acqua.
Fine del bollettino.

=== Sconto sulla spesa ===
Spesa: 64.80 euro
Sconto: 6.48 euro
Da pagare: 58.32 euro

=== Programma fedelta' ===
Punti accumulati: 120
Livello ORO raggiunto: spedizione gratuita.
```

### 020-if-else
```
=== Pari o dispari ===
37 e' dispari

=== Maggiore tra due numeri ===
Tra 14 e 21 il maggiore e' 21

=== Prelievo ===
Saldo: 120.00 euro, prelievo richiesto: 200.00 euro
Prelievo rifiutato: saldo insufficiente.

=== Ternario e if-else a confronto ===
Con il ternario: minorenne
Con if-else:     minorenne, potra' votare tra 2 anni.
```

### 030-if-annidati-e-catene
```
=== Catena else-if ===
Punteggio: 78/100
Fascia: BUONO

=== If annidati ===
Utente 1042 riconosciuto.
PIN corretto.
Mancano 20 punti al premio.

=== Annidamento e && ===
Accesso consentito (if annidati)
Accesso consentito (condizione con &&)

=== Graffe ed else ===
x = 5
(con le graffe x = 5 non stampa nulla: e' positivo ma non grande)
```

### 040-problema-equazione-secondo-grado
*(output dipendente dall'input – esempio con a = 1, b = -3, c = 2)*
```
=== EQUAZIONE DI SECONDO GRADO: a x^2 + b x + c = 0 ===

Coefficiente a: 1
Coefficiente b: -3
Coefficiente c: 2

Equazione: 1 x^2 + (-3) x + (2) = 0
Discriminante: delta = 1
Due soluzioni reali distinte:
  x1 = 2.0000
  x2 = 1.0000
```

*(output dipendente dall'input – esempio con a = 0, b = 0, c = 3)*
```
=== EQUAZIONE DI SECONDO GRADO: a x^2 + b x + c = 0 ===

Coefficiente a: 0
Coefficiente b: 0
Coefficiente c: 3

Equazione: 0 x^2 + (0) x + (3) = 0
a = 0: l'equazione e' di primo grado.
Equazione impossibile: nessuna soluzione.
```

### 050-problema-tariffa-biglietto
*(output dipendente dall'input – esempio con età 22, tessera, martedì)*
```
=== MUSEO CIVICO - BIGLIETTERIA ===

Eta' del visitatore: 22
Tessera universitaria (1 = si', 0 = no): 1
Giorno della visita (1 = lunedi' ... 7 = domenica): 2

Tariffa: studenti universitari
Sconto del martedi': -2,00 euro
Prezzo da pagare: 5,00 euro
```

*(output dipendente dall'input – esempio con età 4, martedì)*
```
=== MUSEO CIVICO - BIGLIETTERIA ===

Eta' del visitatore: 4
Tessera universitaria (1 = si', 0 = no): 0
Giorno della visita (1 = lunedi' ... 7 = domenica): 2

Tariffa: bambini (gratis)
Prezzo da pagare: 0,00 euro
```

### 060-problema-classificazione-triangolo
*(output dipendente dall'input – esempio con i lati 3 4 5)*
```
=== CLASSIFICAZIONE DI UN TRIANGOLO ===

Lunghezza dei tre lati in cm (es. 3 4 5): 3 4 5

I lati 3, 4, 5 formano un triangolo.
Classificazione per lati: SCALENO
Il triangolo e' RETTANGOLO.
Perimetro: 12 cm
```

*(output dipendente dall'input – esempio con i lati 10 2 3)*
```
=== CLASSIFICAZIONE DI UN TRIANGOLO ===

Lunghezza dei tre lati in cm (es. 3 4 5): 10 2 3

Con i lati 10, 2, 3 non si puo' costruire un triangolo:
un lato e' maggiore o uguale alla somma degli altri due.
```

---

## Errori comuni da evitare

**Punto e virgola dopo la condizione**
```c
if (x > 0);        /* ERRATO: if con istruzione vuota */
{
    printf("positivo\n");   /* eseguito sempre */
}
```

**Graffe omesse**
```c
if (spesa >= 50)
    sconto = 5;
    printf("Sconto applicato\n");   /* ERRATO: eseguito sempre */
```

**Assegnazione al posto del confronto**
```c
if (punti = 100)   /* ERRATO: assegna 100, condizione sempre vera */
if (punti == 100)  /* corretto */
```

**Catena nell'ordine sbagliato**
```c
if (voto >= 6) {
    printf("sufficiente\n");
} else if (voto >= 9) {      /* ERRATO: mai raggiunto */
    printf("ottimo\n");
}
```

**Due if al posto di un if-else**
```c
if (prelievo <= saldo) {
    saldo = saldo - prelievo;
}
if (prelievo > saldo) {      /* ERRATO: valuta il saldo GIÀ modificato */
    printf("rifiutato\n");
}
/* Corretto: usare else, così le due alternative si escludono */
```

---

## Concetti collegati

- `01-logica-booleana` → come costruire la condizione di un `if`
- `03-switch` → alternativa alla catena else-if quando si confronta un valore con costanti
- `01-introduzione/04-operatori` → operatore ternario
- `01-introduzione/02-variabili-e-tipi/060-problema-calcolo-area.c` → primo uso di `if/else` nel corso

---

## Esercizi proposti

1. Scrivi un programma che legga tre numeri interi e stampi il maggiore,
   usando solo `if-else` (senza `&&`).

2. Modifica `020-if-else.c` perché il prelievo sia consentito anche oltre il
   saldo, fino a un fido di 500 euro, segnalando quando il conto va in rosso.

3. Estendi `050-problema-tariffa-biglietto.c` con la tariffa famiglia: con
   la tessera "famiglia" (nuovo dato in ingresso) gli adulti pagano 9 euro.
   Dove va inserito il controllo nella catena?

4. Modifica `060-problema-classificazione-triangolo.c` per classificare il
   triangolo anche rispetto agli angoli: acutangolo, rettangolo o ottusangolo
   (suggerimento: confronta il quadrato del lato maggiore con la somma dei
   quadrati degli altri due).

5. (Avanzato) Scrivi un programma che, dati giorno, mese e anno, verifichi se
   la data è valida, tenendo conto dei mesi da 30 e 31 giorni e degli anni
   bisestili (vedi `01-logica-booleana/050-problema-anno-bisestile.c`).
