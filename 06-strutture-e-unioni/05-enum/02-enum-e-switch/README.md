# 02 – Enum e switch

## Concetto

Un enum elenca tutti i valori possibili, quindi uno `switch` su un enum
ha un `case` per ognuno:

```c
switch (f) {
case CERCHIO:
    area = PI_GRECO * r * r;
    break;
case QUADRATO:
    area = l * l;
    break;
case TRIANGOLO:
    area = sqrt(3.0) / 4 * l * l;
    break;
}
```

Con `-Wall` il compilatore controlla lo switch: se manca il `case` di una
costante e non c'è `default`, avverte.

```
warning: enumeration value 'TRIANGOLO' not handled in switch
```

Per questo sugli enum si elencano tutti i case e non si mette `default`:
quando si aggiunge una costante, il compilatore indica gli switch da
aggiornare. Anche la costante di conteggio (`NUM_...`) ha il suo case,
vuoto.

### Funzioni con enum

```c
Esito valuta(double media, int insufficienze);   /* invece di restituire 0, 1, 2 */
const char *descrizione(Esito e);                /* switch su e */

if (valuta(m, n) == SOSPESO) ...
```

### Da testo a enum

| Direzione | Come |
|-----------|------|
| enum → testo | `nomi[m]` |
| testo → enum | si cerca la parola in `nomi`; la posizione è la costante |
| parola sconosciuta | un valore dopo `NUM_...`, per esempio `MATERIA_NON_VALIDA` |

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-switch-su-enum.c` | Area delle figure con uno switch completo e l'avviso di `-Wswitch` |
| `020-funzioni-con-enum.c` | `Esito valuta(...)` per lo scrutinio e `descrizione(e)` |
| `030-da-testo-a-enum.c` | Ore per materia: `da_testo` e `a_testo` con una tabella sola |
| `040-problema-distributore-bevande.c` | Prezzo con uno switch, `Esito` dell'erogazione |
| `040-problema-distributore-bevande-analisi.md` | Analisi di `040-problema-distributore-bevande.c` |
| `050-problema-giudizio-sintetico.c` | Dal voto al giudizio e istogramma per giudizio |
| `050-problema-giudizio-sintetico-analisi.md` | Analisi di `050-problema-giudizio-sintetico.c` |
| `060-problema-calcolatrice-operazioni.c` | Operazione scritta a parole e switch del calcolo |
| `060-problema-calcolatrice-operazioni-analisi.md` | Analisi di `060-problema-calcolatrice-operazioni.c` |
| `070-problema-direzioni-robot.c` | Direzioni in ordine orario: rotazioni con il modulo |
| `070-problema-direzioni-robot-analisi.md` | Analisi di `070-problema-direzioni-robot.c` |
| `080-problema-esito-prenotazione.c` | Un `Esito` per ogni motivo di errore e messaggio con uno switch |
| `080-problema-esito-prenotazione-analisi.md` | Analisi di `080-problema-esito-prenotazione.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-switch-su-enum 010-switch-su-enum.c -lm
./010-switch-su-enum

gcc -Wall -Wextra -o 020-funzioni-con-enum 020-funzioni-con-enum.c
./020-funzioni-con-enum

gcc -Wall -Wextra -o 030-da-testo-a-enum 030-da-testo-a-enum.c
./030-da-testo-a-enum

gcc -Wall -Wextra -o 040-problema-distributore-bevande 040-problema-distributore-bevande.c
./040-problema-distributore-bevande

gcc -Wall -Wextra -o 050-problema-giudizio-sintetico 050-problema-giudizio-sintetico.c
./050-problema-giudizio-sintetico

gcc -Wall -Wextra -o 060-problema-calcolatrice-operazioni 060-problema-calcolatrice-operazioni.c
./060-problema-calcolatrice-operazioni

gcc -Wall -Wextra -o 070-problema-direzioni-robot 070-problema-direzioni-robot.c
./070-problema-direzioni-robot

gcc -Wall -Wextra -o 080-problema-esito-prenotazione 080-problema-esito-prenotazione.c
./080-problema-esito-prenotazione
```

---

## Output atteso

### 010-switch-su-enum
```
cerchio    misura  2.0  area  12.57
quadrato   misura  3.0  area   9.00
triangolo  misura  4.0  area   6.93
cerchio    misura  0.5  area   0.79
```

### 020-funzioni-con-enum
```
  Bassi Rita  media 7.4, 0 insuff.  promosso/a
  Corti Ugo   media 5.9, 2 insuff.  giudizio sospeso
  Dini Ada    media 8.1, 0 insuff.  promosso/a
  Elia Gino   media 4.8, 5 insuff.  non ammesso/a
  Fumo Pia    media 6.3, 1 insuff.  giudizio sospeso
Promossi 2, sospesi 2, non ammessi 1
```

### 030-da-testo-a-enum
*(output dipendente dall'input – esempio di sessione)*
```
Materia (FINE per terminare): matematica
Materia (FINE per terminare): italiano
Materia (FINE per terminare): matematica
Materia (FINE per terminare): storia
  "storia" non e' una materia.
Materia (FINE per terminare): informatica
Materia (FINE per terminare): Matematica
  "Matematica" non e' una materia.
Materia (FINE per terminare): FINE
Ore svolte:
  italiano     1
  matematica   2
  inglese      0
  informatica  1
```

### 040-problema-distributore-bevande
*(output dipendente dall'input – esempio di sessione)*
```
Credito 0.00 euro. Comando (M centesimi, B 1-4, R, Q): M 50
Credito 0.50 euro. Comando (M centesimi, B 1-4, R, Q): B 2
  cappuccino (0.70 euro): credito insufficiente
Credito 0.50 euro. Comando (M centesimi, B 1-4, R, Q): M 20
Credito 0.70 euro. Comando (M centesimi, B 1-4, R, Q): B 2
  cappuccino (0.70 euro): erogata, buona pausa
Credito 0.00 euro. Comando (M centesimi, B 1-4, R, Q): B 3
  te' (0.60 euro): esaurita
Credito 0.00 euro. Comando (M centesimi, B 1-4, R, Q): M 30
  Moneta rifiutata.
Credito 0.00 euro. Comando (M centesimi, B 1-4, R, Q): B 5
  Scelta non valida.
Credito 0.00 euro. Comando (M centesimi, B 1-4, R, Q): M 100
Credito 1.00 euro. Comando (M centesimi, B 1-4, R, Q): B 1
  caffe' (0.50 euro): erogata, buona pausa
Credito 0.50 euro. Comando (M centesimi, B 1-4, R, Q): R
  Resto: 0.50 euro
Credito 0.00 euro. Comando (M centesimi, B 1-4, R, Q): Q
```

### 050-problema-giudizio-sintetico
*(output dipendente dall'input – dieci voti)*
```
Voto (-1 per finire): 4
  4.0: gravemente insufficiente
Voto (-1 per finire): 5.5
  5.5: insufficiente
Voto (-1 per finire): 6
  6.0: sufficiente
Voto (-1 per finire): 6.5
  6.5: sufficiente
Voto (-1 per finire): 7
  7.0: discreto
Voto (-1 per finire): 7.5
  7.5: discreto
Voto (-1 per finire): 8
  8.0: buono
Voto (-1 per finire): 9.5
  9.5: ottimo
Voto (-1 per finire): 10
  10.0: ottimo
Voto (-1 per finire): 3.5
  3.5: gravemente insufficiente
Voto (-1 per finire): 11
  Voto non valido.
Voto (-1 per finire): -1

Giudizi della classe (10 studenti)
  gravemente insufficiente   ** 2
  insufficiente              * 1
  sufficiente                ** 2
  discreto                   ** 2
  buono                      * 1
  ottimo                     ** 2
```

### 060-problema-calcolatrice-operazioni
*(output dipendente dall'input – esempio di sessione)*
```
Operazione e due numeri (FINE): somma 12 30
  somma di 12 e 30 = 42
Operazione e due numeri (FINE): differenza 5 9
  differenza di 5 e 9 = -4
Operazione e due numeri (FINE): quoziente 17 5
  quoziente di 17 e 5 = 3
Operazione e due numeri (FINE): resto 17 5
  resto di 17 e 5 = 2
Operazione e due numeri (FINE): quoziente 4 0
  quoziente di 4 e 0: impossibile.
Operazione e due numeri (FINE): potenza 2 10
  potenza di 2 e 10 = 1024
Operazione e due numeri (FINE): potenza 2 -1
  potenza di 2 e -1: impossibile.
Operazione e due numeri (FINE): radice 9 2
  Operazione "radice" sconosciuta.
Operazione e due numeri (FINE): FINE
```

### 070-problema-direzioni-robot
*(output dipendente dall'input – esempio di sessione)*
```
Comando (A n, S, D, P, Q): A 3
  Robot in (0, 3) verso nord
Comando (A n, S, D, P, Q): D
  Robot in (0, 3) verso est
Comando (A n, S, D, P, Q): A 10
  Bordo raggiunto dopo 7 passi.
  Robot in (7, 3) verso est
Comando (A n, S, D, P, Q): S
  Robot in (7, 3) verso nord
Comando (A n, S, D, P, Q): S
  Robot in (7, 3) verso ovest
Comando (A n, S, D, P, Q): A 1
  Robot in (6, 3) verso ovest
Comando (A n, S, D, P, Q): P
  Robot in (6, 3) verso ovest
Comando (A n, S, D, P, Q): Q
```

### 080-problema-esito-prenotazione
*(output dipendente dall'input – esempio di sessione)*
```
Prenotazione (classe studenti giorno ora, FINE): 3B 24 2 3
  Prenotazione registrata.
Prenotazione (classe studenti giorno ora, FINE): 4A 22 2 3
  Ora gia' occupata da un'altra classe.
Prenotazione (classe studenti giorno ora, FINE): 4A 22 2 4
  Prenotazione registrata.
Prenotazione (classe studenti giorno ora, FINE): 3B 25 5 1
  La classe ha gia' una prenotazione questa settimana.
Prenotazione (classe studenti giorno ora, FINE): 5C 150 1 1
  L'aula magna ha solo 120 posti.
Prenotazione (classe studenti giorno ora, FINE): 1A 20 6 1
  Giorno non valido: da 1 (lunedi') a 5 (venerdi').
Prenotazione (classe studenti giorno ora, FINE): 1A 20 1 7
  Ora non valida: dalla 1a alla 6a.
Prenotazione (classe studenti giorno ora, FINE): 1A 20 1 1
  Prenotazione registrata.
Prenotazione (classe studenti giorno ora, FINE): FINE

      lun  mar  mer  gio  ven 
  1a  1A   -    -    -    -   
  2a  -    -    -    -    -   
  3a  -    3B   -    -    -   
  4a  -    4A   -    -    -   
  5a  -    -    -    -    -   
  6a  -    -    -    -    -   
```

---

## Errori comuni da evitare

**Mettere default su uno switch che dovrebbe coprire tutto**
```c
default: testo = "?";     /* nasconde l'avviso quando si aggiunge una costante */
```

**Dimenticare il break**
```c
case CAFFE:
    centesimi = 50;       /* senza break prosegue nel case successivo */
case CAPPUCCINO:
    centesimi = 70;
```

**Restituire numeri magici**
```c
int valuta(...);              /* 0, 1 o 2: cosa significano? */
Esito valuta(...);            /* corretto: NON_AMMESSO, SOSPESO, PROMOSSO */
```

**Usare il valore "non valido" come indice**
```c
ore[da_testo(parola)]++;      /* MATERIA_NON_VALIDA è fuori dall'array */
```

**Confrontare il testo invece della costante dopo la conversione**
```c
if (strcmp(parola, "somma") == 0) ...    /* ripetuto ovunque */
if (op == SOMMA) ...                     /* corretto, dopo da_testo */
```

---

## Concetti collegati

- `02-controllo-del-flusso/02-switch` → la sintassi dello switch
- `01-dichiarazione-e-valori` → costanti, valori e tabelle dei nomi
- `03-enum-nelle-struct` → stati e transizioni
- `04-array-e-stringhe/04-funzioni-su-stringhe` → `strcmp` per la conversione da testo

---

## Esercizi proposti

1. In `010-switch-su-enum.c` aggiungi `ESAGONO` all'enum, compila e
   correggi gli switch indicati dal compilatore.

2. In `030-da-testo-a-enum.c` accetta le materie anche con le maiuscole
   (`Matematica`).

3. In `040-problema-distributore-bevande.c` aggiungi l'esito
   `MONETA_RIFIUTATA` e usalo al posto del messaggio scritto nel main.

4. In `070-problema-direzioni-robot.c` aggiungi il comando `I` per
   tornare indietro di un passo senza girarsi.

5. (Avanzato) In `080-problema-esito-prenotazione.c` aggiungi il comando
   `A classe` che annulla la prenotazione e restituisce un `Esito`.
