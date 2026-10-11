# 04 – While e do-while

## Concetto

Un **ciclo** (struttura iterativa) ripete un blocco di istruzioni finché una
condizione resta vera. Il C ne offre tre: `while`, `do-while` e `for`
(sezione `05-for`).

### While: controllo in testa

```
          ┌──────────────┐
    ┌────►│  condizione? │── falsa ──► fine del ciclo
    │     └──────┬───────┘
    │          vera
    │     ┌──────▼───────┐
    └─────│    corpo     │
          └──────────────┘
```

```c
while (condizione) {
    corpo;
}
```

La condizione si valuta **prima** di ogni ripetizione: se è falsa già la
prima volta, il corpo non viene eseguito (**zero iterazioni**).

### Do-while: controllo in coda

```c
do {
    corpo;
} while (condizione);     /* punto e virgola obbligatorio */
```

Il corpo viene eseguito **almeno una volta**. È la scelta naturale per la
validazione dell'input e per i menu.

| | `while` | `do-while` |
|---|---------|------------|
| quando si controlla | prima del corpo | dopo il corpo |
| esecuzioni minime | 0 | 1 |
| uso tipico | numero di ripetizioni ignoto, anche nullo | validazione, menu |

### I tre elementi di un ciclo corretto

1. **Inizializzazione** della variabile di controllo, prima del ciclo.
2. **Condizione** che la controlla.
3. **Aggiornamento** nel corpo, che prima o poi rende falsa la condizione.

Se manca l'aggiornamento il ciclo è **infinito**.

### Schemi ricorrenti

- **Contatore**: `conta++` a ogni iterazione.
- **Accumulatore**: `somma = somma + valore`, con `somma` inizializzata a 0.
- **Sentinella**: un valore speciale segnala la fine dei dati. Si usa la
  *lettura anticipata*: una lettura prima del ciclo e una alla fine del corpo.
- **Flag**: una variabile booleana registra un evento (es. `indovinato`) e
  compare nella condizione del ciclo, al posto di un'uscita con `break`.

### Condizione di continuazione e De Morgan

La condizione del ciclo dice quando **continuare**. Se si conosce la
condizione di **arresto**, la si nega con De Morgan
(vedi `01-logica-booleana`):

```
  arresto:        indovinato || tentativi >= MAX
  continuazione:  !indovinato && tentativi <  MAX
```

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-while-base.c` | Conto alla rovescia, contatore e accumulatore, numero di ripetizioni non noto, zero iterazioni |
| `020-ciclo-con-sentinella.c` | Nota spese con sentinella 0: totale, media e spesa maggiore senza array |
| `030-do-while-validazione.c` | Validazione di un voto e ripetizione su richiesta dell'utente |
| `040-problema-cifre-di-un-numero.c` | Numero di cifre, somma delle cifre, numero inverso, palindromo |
| `040-problema-cifre-di-un-numero-analisi.md` | Analisi di `040-problema-cifre-di-un-numero.c` |
| `050-problema-mcd-euclide.c` | MCD con l'algoritmo di Euclide passo per passo e mcm |
| `050-problema-mcd-euclide-analisi.md` | Analisi di `050-problema-mcd-euclide.c` |
| `060-problema-indovina-numero.c` | Gioco con numero casuale, tentativi limitati e flag di vittoria |
| `060-problema-indovina-numero-analisi.md` | Analisi di `060-problema-indovina-numero.c` |
| `070-problema-bancomat.c` | Menu do-while con switch: saldo, prelievo con limiti, versamento |
| `070-problema-bancomat-analisi.md` | Analisi di `070-problema-bancomat.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-while-base 010-while-base.c
./010-while-base

gcc -Wall -Wextra -o 020-ciclo-con-sentinella 020-ciclo-con-sentinella.c
./020-ciclo-con-sentinella

gcc -Wall -Wextra -o 030-do-while-validazione 030-do-while-validazione.c
./030-do-while-validazione

gcc -Wall -Wextra -o 040-problema-cifre-di-un-numero 040-problema-cifre-di-un-numero.c
./040-problema-cifre-di-un-numero

gcc -Wall -Wextra -o 050-problema-mcd-euclide 050-problema-mcd-euclide.c
./050-problema-mcd-euclide

gcc -Wall -Wextra -o 060-problema-indovina-numero 060-problema-indovina-numero.c
./060-problema-indovina-numero

gcc -Wall -Wextra -o 070-problema-bancomat 070-problema-bancomat.c
./070-problema-bancomat
```

---

## Output atteso

### 010-while-base
```
=== Conto alla rovescia ===
5... 4... 3... 2... 1... partenza!

=== Somma dei numeri da 1 a 10 ===
Somma = 55
Dopo il ciclo numero vale 11: e' il primo valore che ha reso falsa la condizione.

=== Obiettivo di risparmio ===
Versando 35.00 euro a settimana, per arrivare a 500.00 euro
servono 15 settimane (risparmio finale: 525.00 euro).

=== Zero iterazioni ===
Bottiglie disponibili: 0, il ciclo non e' stato eseguito.
```

### 020-ciclo-con-sentinella
*(output dipendente dall'input – esempio con le spese 12.50, -3, 40, 7.80 e la sentinella 0)*
```
=== NOTA SPESE ===
Inserisci gli importi delle spese (0 per terminare).

Spesa: 12.50
Spesa: -3
  Importo negativo ignorato.
Spesa: 40
Spesa: 7.80
Spesa: 0

--- Riepilogo ---
Spese inserite : 3
Totale         : 60.30 euro
Media          : 20.10 euro
Spesa maggiore : 40.00 euro
```

### 030-do-while-validazione
*(output dipendente dall'input – esempio con i voti 7 e poi 12, 0, 8)*
```
=== REGISTRO VOTI ===
Voto dello studente 1 (1-10): 7
Inserire un altro voto? (s/n): s
Voto dello studente 2 (1-10): 12
  Voto non valido, riprova.
Voto dello studente 2 (1-10): 0
  Voto non valido, riprova.
Voto dello studente 2 (1-10): 8
  (voto accettato dopo 3 tentativi)
Inserire un altro voto? (s/n): n

Studenti: 2, media dei voti: 7.50
```

### 040-problema-cifre-di-un-numero
*(output dipendente dall'input – esempio con il numero 12321)*
```
Inserisci un numero intero non negativo: 12321

Cifre da destra a sinistra: 1 2 3 2 1 
Numero di cifre   : 5
Somma delle cifre : 9
Numero inverso    : 12321
12321 e' palindromo.
```

*(output dipendente dall'input – esempio con il numero 1203)*
```
Inserisci un numero intero non negativo: 1203

Cifre da destra a sinistra: 3 0 2 1 
Numero di cifre   : 4
Somma delle cifre : 6
Numero inverso    : 3021
1203 non e' palindromo.
```

### 050-problema-mcd-euclide
*(output dipendente dall'input – esempio con 84 e 60)*
```
=== MCD CON L'ALGORITMO DI EUCLIDE ===

Primo numero (positivo): 84
Secondo numero (positivo): 60

  Passo |     a |     b | a % b
  ------|-------|-------|------
      1 |    84 |    60 |    24
      2 |    60 |    24 |    12
      3 |    24 |    12 |     0

MCD(84, 60) = 12   (trovato in 3 passi)
mcm(84, 60) = 420
```

### 060-problema-indovina-numero
*(output dipendente dall'input – esempio di partita; il numero segreto cambia a ogni esecuzione)*
```
=== INDOVINA IL NUMERO ===
Ho pensato un numero tra 1 e 100. Hai 7 tentativi.

Tentativo 1: 150
  Inserisci un numero tra 1 e 100.
Tentativo 1: 50
  Troppo alto.
Tentativo 2: 25
  Troppo basso.
Tentativo 3: 37
  Troppo basso.
Tentativo 4: 43
  Troppo alto.
Tentativo 5: 40
  Troppo alto.
Tentativo 6: 38

Indovinato! Il numero era 38 (6 tentativi).
```

### 070-problema-bancomat
*(output dipendente dall'input – esempio di sessione)*
```
=== BANCOMAT ===

1 - Saldo   2 - Prelievo   3 - Versamento   0 - Esci
Scelta: 1
Saldo disponibile: 1250 euro

1 - Saldo   2 - Prelievo   3 - Versamento   0 - Esci
Scelta: 2
Importo da prelevare: 300
Ritirare 300 euro. Nuovo saldo: 950 euro

1 - Saldo   2 - Prelievo   3 - Versamento   0 - Esci
Scelta: 2
Importo da prelevare: 35
Importo non valido: multipli di 10 euro.

1 - Saldo   2 - Prelievo   3 - Versamento   0 - Esci
Scelta: 2
Importo da prelevare: 250
Limite giornaliero superato: puoi prelevare ancora 200 euro.

1 - Saldo   2 - Prelievo   3 - Versamento   0 - Esci
Scelta: 3
Importo da versare: 100
Versamento eseguito. Nuovo saldo: 1050 euro

1 - Saldo   2 - Prelievo   3 - Versamento   0 - Esci
Scelta: 7
Scelta non valida.

1 - Saldo   2 - Prelievo   3 - Versamento   0 - Esci
Scelta: 0
Operazioni eseguite: 3. Saldo finale: 1050 euro. Arrivederci.
```

---

## Errori comuni da evitare

**Aggiornamento dimenticato: ciclo infinito**
```c
i = 0;
while (i < 10) {
    printf("%d\n", i);    /* manca i++ */
}
```

**Punto e virgola dopo il while**
```c
while (i < 10);   /* ciclo vuoto: infinito se i < 10 */
{
    i++;
}
```

**Punto e virgola mancante nel do-while**
```c
do {
    ...
} while (x < 0)   /* ERRORE di compilazione: manca ; */
```

**Condizione di validità al posto di quella di ripetizione**
```c
do {
    scanf("%d", &voto);
} while (voto >= 1 && voto <= 10);   /* ERRATO: ripete quando il voto è giusto */
/* corretto: while (voto < 1 || voto > 10); */
```

**Sentinella elaborata come dato**
```c
while (spesa != 0) {
    scanf("%lf", &spesa);
    totale = totale + spesa;   /* somma anche lo 0 finale; e la prima volta
                                  spesa non è ancora stata letta */
}
```

**Accumulatore non inizializzato**
```c
int somma;            /* valore indefinito */
while (...) {
    somma = somma + x;
}
```

---

## Concetti collegati

- `01-logica-booleana` → negazione delle condizioni con De Morgan
- `03-switch` → lo switch dentro un ciclo per i menu
- `05-for` → il ciclo per un numero di ripetizioni noto
- `06-break-continue` → perché le uscite anticipate si sostituiscono con una variabile flag

---

## Esercizi proposti

1. Scrivi un programma che legga numeri interi fino allo 0 e stampi quanti
   sono pari e quanti dispari.

2. Modifica `020-ciclo-con-sentinella.c` per stampare anche la spesa minore.
   Perché non si può inizializzare il minimo a 0?

3. Scrivi un programma che calcoli in quanti anni un capitale raddoppia con
   un interesse annuo composto letto da tastiera (es. 3%).

4. Estendi `040-problema-cifre-di-un-numero.c` per stampare la cifra
   maggiore e quante volte compare.

5. (Avanzato) Aggiungi a `070-problema-bancomat.c` il PIN: all'avvio
   l'utente ha 3 tentativi per inserire il PIN corretto; se li esaurisce il
   menu non viene mostrato. Usa un flag, senza `break`.
