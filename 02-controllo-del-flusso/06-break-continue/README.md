# 06 – Break e continue

## Concetto

Il C offre due istruzioni per alterare il flusso di un ciclo dall'interno
del corpo:

| Istruzione | Effetto |
|------------|---------|
| `break` | termina **subito** il ciclo più interno che la contiene; l'esecuzione riprende dopo il ciclo |
| `continue` | salta il resto del corpo e passa **subito** all'iterazione successiva (nel `for` esegue prima l'aggiornamento) |

```c
for (i = 51; i <= 100; i++) {          for (i = 1; i <= 10; i++) {
    if (i % 7 == 0) {                      if (i % 2 == 0) {
        break;      /* esce */                 continue;  /* salta */
    }                                      }
}                                          somma = somma + i;
                                       }
```

### Perché nel corso si evitano

Un ciclo dovrebbe dichiarare **nella sua intestazione** quando termina e
quali iterazioni elabora. `break` e `continue` introducono punti di uscita e
di salto **non evidenti**, nascosti nel corpo:

- per capire quando il ciclo finisce bisogna leggerlo tutto, riga per riga;
- dopo il ciclo non è chiaro *perché* è terminato (condizione o `break`?);
- modificando il corpo è facile spostare o dimenticare un'uscita;
- `break` esce da un solo ciclo: con cicli annidati il comportamento
  sorprende;
- `continue` in un `while` può saltare l'aggiornamento e creare un ciclo
  infinito.

Per questi motivi le convenzioni del corso vietano `break` fuori dallo
`switch` e `continue` (vedi `CONVENZIONI.md`, sezione 6). Il `break` dello
`switch` è un'altra cosa: fa parte della sintassi dello `switch` e chiude il
`case`.

### Come evitarli

**Al posto di `break`: un flag nella condizione**

```c
trovato = 0;
for (i = 51; i <= 100 && !trovato; i++) {
    if (i % 7 == 0) {
        trovato = 1;
        numero = i;
    }
}
```

Tutte le ragioni di terminazione compaiono nell'intestazione. Spesso basta
scrivere la condizione "vera" al posto di `while (1)` + `break`.

**Al posto di `continue`: un if con la condizione opposta**

```c
for (i = 1; i <= 10; i++) {
    if (i % 2 != 0) {          /* opposto di: i % 2 == 0 */
        somma = somma + i;
    }
}
```

La condizione opposta si ricava con De Morgan (`01-logica-booleana`); se per
i valori scartati serve fare qualcosa, si usa il ramo `else`.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-break-e-continue.c` | Funzionamento di break e continue, break in cicli annidati. **Unico file del corso** con break nei cicli e continue nel codice eseguibile, segnalati come "DA NON IMITARE" |
| `020-evitare-break.c` | Ricerca con flag, condizione naturale al posto di `while (1)`, uscita da due cicli annidati |
| `030-evitare-continue.c` | Filtro con if, più condizioni di scarto con De Morgan, if-else al posto del salto |
| `040-problema-primo-divisore.c` | Primo divisore con flag e scomposizione in fattori primi |
| `040-problema-primo-divisore-analisi.md` | Analisi di `040-problema-primo-divisore.c` |
| `050-problema-verifica-pin.c` | PIN con 3 tentativi: flag di successo, formato errato gestito senza continue |
| `050-problema-verifica-pin-analisi.md` | Analisi di `050-problema-verifica-pin.c` |
| `060-problema-somma-solo-positivi.c` | Letture di un contatore con sentinella: valori anomali scartati nel ramo else |
| `060-problema-somma-solo-positivi-analisi.md` | Analisi di `060-problema-somma-solo-positivi.c` |

Nei file dei problemi la versione con `break` o `continue` è riportata nei
commenti, per confronto.

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-break-e-continue 010-break-e-continue.c
./010-break-e-continue

gcc -Wall -Wextra -o 020-evitare-break 020-evitare-break.c
./020-evitare-break

gcc -Wall -Wextra -o 030-evitare-continue 030-evitare-continue.c
./030-evitare-continue

gcc -Wall -Wextra -o 040-problema-primo-divisore 040-problema-primo-divisore.c
./040-problema-primo-divisore

gcc -Wall -Wextra -o 050-problema-verifica-pin 050-problema-verifica-pin.c
./050-problema-verifica-pin

gcc -Wall -Wextra -o 060-problema-somma-solo-positivi 060-problema-somma-solo-positivi.c
./060-problema-somma-solo-positivi
```

---

## Output atteso

### 010-break-e-continue
```
=== break ===
Primo multiplo di 7 dopo 50: 56
Il ciclo si e' fermato con i = 56 (non a 101)

=== continue ===
sommo 1
sommo 3
sommo 5
sommo 7
sommo 9
Somma dei dispari: 25

=== break in cicli annidati ===
(1,1) (1,2) <- fine riga 1
(2,1) (2,2) <- fine riga 2
(3,1) (3,2) <- fine riga 3
```

### 020-evitare-break
```
=== 1. Primo multiplo di 7 dopo 50 ===
Trovato: 56

=== 2. Mesi per estinguere un debito ===
Con rate da 250.00 euro servono 8 mesi (ultima rata parziale).

=== 3. Ricerca in una griglia ===
Prima casella con prodotto 12: riga 3, colonna 4
```

### 030-evitare-continue
```
=== 1. Somma dei dispari da 1 a 10 ===
Somma: 25

=== 2. Da 1 a 30, esclusi multipli di 3 e numeri che finiscono per 5 ===
1 2 4 7 8 10 11 13 14 16 17 19 20 22 23 26 28 29 
Stampati: 18, esclusi: 12

=== 3. Conteggio da 1 a 20 con segnalazione delle decine ===
1 2 3 4 5 6 7 8 9 [10] 11 12 13 14 15 16 17 18 19 [20] 
```

### 040-problema-primo-divisore
*(output dipendente dall'input – esempio con 360)*
```
=== PRIMO DIVISORE E FATTORI PRIMI ===

Numero intero (>= 2): 360

Primo divisore maggiore di 1: 2
360 = 2 x 180

Scomposizione: 360 = 2^3 x 3^2 x 5
```

*(output dipendente dall'input – esempio con 97)*
```
=== PRIMO DIVISORE E FATTORI PRIMI ===

Numero intero (>= 2): 97

Primo divisore maggiore di 1: 97
97 e' un numero primo.

Scomposizione: 97 = 97
```

### 050-problema-verifica-pin
*(output dipendente dall'input – esempio con un formato errato, un PIN sbagliato e quello giusto)*
```
=== TERMINALE POS ===
Importo: 42,50 euro

Inserire il PIN (5 cifre): 1234
  Formato non valido: il PIN ha 5 cifre.
Inserire il PIN (5 cifre): 11111
  PIN errato. Tentativi rimasti: 2
Inserire il PIN (5 cifre): 27183

PIN corretto. Pagamento autorizzato.
```

*(output dipendente dall'input – esempio con tre PIN sbagliati)*
```
=== TERMINALE POS ===
Importo: 42,50 euro

Inserire il PIN (5 cifre): 11111
  PIN errato. Tentativi rimasti: 2
Inserire il PIN (5 cifre): 22222
  PIN errato. Tentativi rimasti: 1
Inserire il PIN (5 cifre): 33333
  PIN errato. Tentativi rimasti: 0

Carta BLOCCATA: troppi tentativi errati.
```

### 060-problema-somma-solo-positivi
*(output dipendente dall'input – esempio con due letture anomale)*
```
=== CONTATORE ELETTRICO - LETTURE ORARIE ===
Inserire le letture in Wh (-999 per terminare).

Lettura 1: 420
Lettura 2: 380
Lettura 3: -15
  Lettura 3 anomala (-15 Wh): scartata.
Lettura 4: 0
Lettura 5: 510
Lettura 6: -3
  Lettura 6 anomala (-3 Wh): scartata.
Lettura 7: 465
Lettura 8: -999

--- Riepilogo ---
Letture ricevute : 7
Letture valide   : 5
Letture scartate : 2
Consumo totale   : 1775 Wh (1.775 kWh)
Consumo medio    : 355.0 Wh per lettura
Lettura massima  : 510 Wh
```

---

## Errori comuni da evitare

**Credere che break esca da tutti i cicli**
```c
for (r = 1; r <= 3; r++) {
    for (c = 1; c <= 5; c++) {
        if (c == 3) {
            break;          /* esce solo dal ciclo su c */
        }
    }
}                           /* il ciclo su r continua */
```

**continue che salta l'aggiornamento in un while**
```c
i = 0;
while (i < 10) {
    if (i % 2 == 0) {
        continue;           /* i++ non viene mai raggiunto: ciclo infinito */
    }
    i++;
}
```

**Valore della variabile di un for dopo la ricerca con flag**
```c
for (i = 51; i <= 100 && !trovato; i++) {
    if (i % 7 == 0) {
        trovato = 1;
    }
}
printf("%d", i);   /* stampa 57, non 56: il for incrementa i
                      prima di ricontrollare la condizione */
/* Corretto: salvare il valore in una variabile quando lo si trova */
```

**Decidere l'esito senza il flag**
```c
/* dopo un ciclo PIN con break */
if (tentativi < 3) { ... }   /* un PIN giusto al terzo tentativo
                                risulta "carta bloccata" */
```

---

## Concetti collegati

- `01-logica-booleana` → De Morgan per scrivere la condizione opposta
- `03-switch` → l'unico uso ammesso di `break`
- `04-while-do-while/060-problema-indovina-numero.c` → ciclo con due motivi di terminazione
- `05-for/050-problema-numeri-primi.c` → ricerca con flag nella condizione del for

---

## Esercizi proposti

1. Riscrivi senza `break` questo ciclo:
   ```c
   while (1) {
       scanf("%d", &x);
       if (x == 0) {
           break;
       }
       somma = somma + x;
   }
   ```

2. Riscrivi senza `continue` un ciclo che stampa i numeri da 1 a 50 saltando
   i multipli di 4 e di 6.

3. Modifica `050-problema-verifica-pin.c` perché dopo il blocco della carta
   venga chiesto il PUK (8 cifre, 10 tentativi). Usa un flag per ogni ciclo.

4. Scrivi un programma che cerchi, tra i numeri da 1 a 1000, il primo che sia
   multiplo sia di 7 sia di 13 e che abbia la somma delle cifre pari. Usa un
   solo ciclo con flag.

5. (Avanzato) Trova un ciclo con `break` o `continue` in un programma che hai
   scritto (o in un esempio online), riscrivilo secondo le convenzioni e
   verifica con alcuni input che il comportamento sia identico.
