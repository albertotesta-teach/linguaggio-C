# 01 – Parametri per riferimento

## Concetto

Una funzione riceve **copie** dei suoi argomenti. Per modificare una
variabile del chiamante deve riceverne l'**indirizzo**: è il passaggio per
riferimento, già visto in `03-funzioni/03-passaggio-per-riferimento`.

```c
void scambia(int *a, int *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}

scambia(&primo, &secondo);       /* si passano gli indirizzi */
```

Una funzione che ha già ricevuto un puntatore lo passa ad altre funzioni
**senza `&`**: è già un indirizzo.

```c
void ordina_tre(int *a, int *b, int *c)
{
    if (*a > *b) {
        scambia(a, b);           /* non &a: a è già un indirizzo */
    }
    ...
}
```

### Tre usi di un parametro puntatore

| Uso | Esempio | La funzione |
|-----|---------|-------------|
| uscita | `scomponi(8130, &h, &m, &s)` | scrive un risultato |
| ingresso e uscita | `preleva(&saldo, 550)` | legge il valore e lo aggiorna |
| uscita facoltativa | `calcola(..., &totale, NULL, NULL)` | scrive solo se il puntatore non è `NULL` |

### `return` per l'esito, puntatori per i risultati

Una convenzione molto diffusa: i risultati escono dai parametri puntatore,
mentre `return` comunica se l'operazione è riuscita.

```c
if (preleva(&saldo, PASTO)) {
    printf("pagato\n");
} else {
    printf("credito insufficiente\n");
}
```

In caso di insuccesso la funzione **non modifica** le variabili del
chiamante: il controllo si fa prima di scrivere.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-scambio-e-ordine.c` | Copie e indirizzi, `scambia`, `ordina_tre` che passa i puntatori senza `&` |
| `020-parametri-in-out.c` | Saldo in ingresso e uscita, `return` 1/0 per l'esito |
| `030-piu-risultati.c` | Secondi scomposti in ore, minuti e secondi; giorni con `return` |
| `040-problema-resto-in-monete.c` | Resto con scorta limitata: esito, array delle monete e importo mancante |
| `040-problema-resto-in-monete-analisi.md` | Analisi di `040-problema-resto-in-monete.c` |
| `050-problema-durata-allenamento.c` | Durata totale con riporto e giro migliore in ingresso e uscita |
| `050-problema-durata-allenamento-analisi.md` | Analisi di `050-problema-durata-allenamento.c` |
| `060-problema-lettura-data.c` | Lettura di una data con esito a tre valori e giorno successivo |
| `060-problema-lettura-data-analisi.md` | Analisi di `060-problema-lettura-data.c` |
| `070-problema-batteria-drone.c` | Carica e minuti di volo aggiornati solo se la manovra è possibile |
| `070-problema-batteria-drone-analisi.md` | Analisi di `070-problema-batteria-drone.c` |
| `080-problema-scontrino-con-sconto.c` | Totale, sconto e punti come uscite facoltative |
| `080-problema-scontrino-con-sconto-analisi.md` | Analisi di `080-problema-scontrino-con-sconto.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-scambio-e-ordine 010-scambio-e-ordine.c
./010-scambio-e-ordine

gcc -Wall -Wextra -o 020-parametri-in-out 020-parametri-in-out.c
./020-parametri-in-out

gcc -Wall -Wextra -o 030-piu-risultati 030-piu-risultati.c
./030-piu-risultati

gcc -Wall -Wextra -o 040-problema-resto-in-monete 040-problema-resto-in-monete.c
./040-problema-resto-in-monete

gcc -Wall -Wextra -o 050-problema-durata-allenamento 050-problema-durata-allenamento.c
./050-problema-durata-allenamento

gcc -Wall -Wextra -o 060-problema-lettura-data 060-problema-lettura-data.c
./060-problema-lettura-data

gcc -Wall -Wextra -o 070-problema-batteria-drone 070-problema-batteria-drone.c
./070-problema-batteria-drone

gcc -Wall -Wextra -o 080-problema-scontrino-con-sconto 080-problema-scontrino-con-sconto.c
./080-problema-scontrino-con-sconto
```

---

## Output atteso

### 010-scambio-e-ordine
```
Tempi iniziali:          412 398 405
  dentro scambia_copie:  a = 398, b = 412
Dopo scambia_copie:      412 398 405   (nulla e' cambiato)
Dopo scambia(&p, &s):    398 412 405
Dopo ordina_tre:         398 405 412
```

### 020-parametri-in-out
```
Saldo: 12.00 euro
Giorno 1, pasto da 5.50 euro: pagato. Saldo: 6.50 euro
Giorno 2, pasto da 5.50 euro: pagato. Saldo: 1.00 euro
Giorno 3, pasto da 5.50 euro: credito insufficiente. Saldo: 1.00 euro
Ricarica di 20 euro: eseguita. Saldo: 21.00 euro
Ricarica di 40 euro: rifiutata, il massimo e' 50.00 euro. Saldo: 21.00 euro
```

### 030-piu-risultati
```
=== DURATA DELLE REGISTRAZIONI ===
    8130 s =   2 h 15 min 30 s
      59 s =   0 h  0 min 59 s
  200000 s =  55 h 33 min 20 s

Controllo: 2 h 15 min 30 s = 8130 s
200000 s = 2 giorni, 7 h 33 min 20 s
```

### 040-problema-resto-in-monete
*(output dipendente dall'input – esempio di sessione)*
```
=== DISTRIBUTORE: RESTO IN MONETE ===

Prezzo e importo inserito in centesimi (0 0 per finire): 130 500
  Resto 3.70 euro:  1 x 200 cent  1 x 100 cent  1 x 50 cent  1 x 20 cent
  Scorta:  200 cent: 1  100 cent: 2  50 cent: 0  20 cent: 3  10 cent: 5  5 cent: 2

Prezzo e importo inserito in centesimi (0 0 per finire): 120 200
  Resto 0.80 euro:  3 x 20 cent  2 x 10 cent
  Scorta:  200 cent: 1  100 cent: 2  50 cent: 0  20 cent: 0  10 cent: 3  5 cent: 2

Prezzo e importo inserito in centesimi (0 0 per finire): 65 100
  Resto 0.35 euro:  3 x 10 cent  1 x 5 cent
  Scorta:  200 cent: 1  100 cent: 2  50 cent: 0  20 cent: 0  10 cent: 0  5 cent: 1

Prezzo e importo inserito in centesimi (0 0 per finire): 30 100
  Resto non disponibile (mancano 65 cent): vendita annullata.
  Scorta:  200 cent: 1  100 cent: 2  50 cent: 0  20 cent: 0  10 cent: 0  5 cent: 1

Prezzo e importo inserito in centesimi (0 0 per finire): 15 100
  Resto non disponibile (mancano 80 cent): vendita annullata.
  Scorta:  200 cent: 1  100 cent: 2  50 cent: 0  20 cent: 0  10 cent: 0  5 cent: 1

Prezzo e importo inserito in centesimi (0 0 per finire): 0 0
```

### 050-problema-durata-allenamento
*(output dipendente dall'input – esempio di sessione)*
```
=== ALLENAMENTO IN PISTA ===
Tempo del giro 1 (mm:ss, 0:00 per finire): 5:42
  totale 0:05:42   nuovo giro migliore
Tempo del giro 2 (mm:ss, 0:00 per finire): 5:18
  totale 0:11:00   nuovo giro migliore
Tempo del giro 3 (mm:ss, 0:00 per finire): 6:05
  totale 0:17:05
Tempo del giro 4 (mm:ss, 0:00 per finire): 5:61
  Tempo non valido.
Tempo del giro 4 (mm:ss, 0:00 per finire): 5:09
  totale 0:22:14   nuovo giro migliore
Tempo del giro 5 (mm:ss, 0:00 per finire): 0:00

4 giri in 0:22:14, giro migliore 5:09
```

### 060-problema-lettura-data
*(output dipendente dall'input – esempio di sessione)*
```
=== PRENOTAZIONE PALESTRA ===
Data (gg/mm/aaaa, riga vuota per finire): 15/03/2026
  Prenotazione per il 15/03/2026, scade il 16/03/2026
Data (gg/mm/aaaa, riga vuota per finire): 31/12/2026
  Prenotazione per il 31/12/2026, scade il 01/01/2027
Data (gg/mm/aaaa, riga vuota per finire): 29/02/2026
  Data non valida.
Data (gg/mm/aaaa, riga vuota per finire): 28/02/2028
  Prenotazione per il 28/02/2028, scade il 29/02/2028
Data (gg/mm/aaaa, riga vuota per finire): 31/04/2026
  Data non valida.
Data (gg/mm/aaaa, riga vuota per finire): ciao
  Data non valida.
Data (gg/mm/aaaa, riga vuota per finire): 
```

### 070-problema-batteria-drone
*(output dipendente dall'input – esempio di sessione)*
```
=== DRONE DEL LABORATORIO ===
Carica 64%, autonomia 22 minuti
Comando (V n, R n, Q): V 10
  Volo di 10 minuti eseguito. Carica 44%, autonomia 12 minuti
Comando (V n, R n, Q): V 15
  Volo rifiutato: la carica scenderebbe sotto il 20%. Carica 44%, autonomia 12 minuti
Comando (V n, R n, Q): R 8
  Ricaricati 24 punti. Carica 68%, autonomia 24 minuti
Comando (V n, R n, Q): V 15
  Volo di 15 minuti eseguito. Carica 38%, autonomia 9 minuti
Comando (V n, R n, Q): X
  Comando sconosciuto.
Comando (V n, R n, Q): Q
Minuti di volo totali: 25, carica finale 38%
```

### 080-problema-scontrino-con-sconto
```
=== CASSA ===
  10 articoli, totale 74.60, sconto 7.46, da pagare 67.14 euro, 67 punti

=== PREVENTIVO (solo il totale) ===
  primi due articoli: 39.90 euro

=== TESSERA (solo i punti) ===
  punti caricati: 67
```

---

## Errori comuni da evitare

**Passare il valore invece dell'indirizzo**
```c
scambia(primo, secondo);     /* avviso: int passato al posto di int * */
scambia(&primo, &secondo);   /* corretto */
```

**Aggiungere `&` a un puntatore**
```c
void ordina_tre(int *a, int *b, int *c)
{
    scambia(&a, &b);         /* &a è l'indirizzo del puntatore: tipo int ** */
    scambia(a, b);           /* corretto */
}
```

**Modificare il puntatore invece della variabile puntata**
```c
void azzera(int *x)
{
    x = 0;                   /* cambia la copia del puntatore */
    *x = 0;                  /* corretto: cambia la variabile del chiamante */
}
```

**Scrivere nelle uscite anche quando l'operazione fallisce**
```c
*saldo = *saldo - importo;   /* prima del controllo: il saldo diventa negativo */
if (*saldo < 0) { ... }
```

**Dereferenziare un'uscita facoltativa senza controllo**
```c
*sconto = riduzione;         /* se il chiamante ha passato NULL si interrompe */
```

---

## Concetti collegati

- `03-funzioni/03-passaggio-per-riferimento` → primo incontro con i parametri puntatore
- `01-introduzione-ai-puntatori/03-errori-e-puntatori-sicuri` → `NULL` e `const`
- `02-puntatori-e-array/02-array-come-puntatori` → array come parametri
- `02-funzioni-che-restituiscono-puntatori` → il puntatore come valore di ritorno

---

## Esercizi proposti

1. In `010-scambio-e-ordine.c` scrivi `ordina_tre_decrescente` riusando
   `scambia`.

2. In `030-piu-risultati.c` scrivi `scomponi_euro(int centesimi, int *euro,
   int *cent)` e usala per stampare importi.

3. In `040-problema-resto-in-monete.c` aggiungi le monete inserite dal
   cliente alla scorta quando la vendita va a buon fine.

4. In `060-problema-lettura-data.c` scrivi `giorno_prima(&g, &m, &a)` e
   stampa anche il giorno precedente.

5. (Avanzato) In `070-problema-batteria-drone.c` aggiungi il comando `M`
   che fa volare il drone per il massimo dei minuti possibili, calcolati con
   `autonomia`.
