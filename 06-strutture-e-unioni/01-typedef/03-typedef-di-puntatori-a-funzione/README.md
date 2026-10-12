# 03 – Typedef di puntatori a funzione

## Concetto

Il tipo "puntatore a funzione" è il caso in cui `typedef` aiuta di più. La
regola resta la stessa: la dichiarazione di una variabile con `typedef`
davanti.

```c
double (*calcolo)(double, double);              /* variabile */
typedef double (*Operazione)(double, double);   /* tipo */

Operazione calcolo = somma;
calcolo(3, 4);
```

`Operazione` significa "puntatore a una funzione che riceve due `double` e
restituisce un `double`".

### Dove si vede la differenza

| Uso | Senza typedef | Con typedef |
|-----|---------------|-------------|
| variabile | `double (*op)(double, double);` | `Operazione op;` |
| parametro | `double applica(double (*op)(double, double), double a, double b);` | `double applica(Operazione op, double a, double b);` |
| array | `double (*tabella[4])(double, double);` | `Operazione tabella[4];` |
| valore restituito | `double (*scegli(char s))(double, double);` | `Operazione scegli(char s);` |

L'ultima riga è la più importante: senza typedef il nome della funzione e i
suoi parametri finiscono "dentro" il tipo restituito.

### Confrontare puntatori a funzione

Due puntatori a funzione si confrontano con `==` e `!=`: sono uguali se
indicano la stessa funzione. Così una funzione può restituire una
`Tariffa` e il chiamante può ritrovarne il nome nella tabella.

```c
migliore = piu_conveniente(minuti, tariffe, TARIFFE);
t = 0;
while (t < TARIFFE && tariffe[t] != migliore) {
    t++;
}
```

### Lo stesso prototipo per tutte

Le funzioni di una tabella devono avere tutte il prototipo del tipo, anche
quando non usano qualche parametro (`(void) minuti;` evita l'avviso).

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-nome-a-un-puntatore-a-funzione.c` | La stessa variabile con e senza typedef; `Operazione` come parametro |
| `020-funzione-che-restituisce-un-operazione.c` | `Operazione scegli(char)` a confronto con `double (*scegli(char))(double, double)` |
| `030-tabella-di-operazioni.c` | `Operazione tabella[4]` e il simbolo come indice |
| `040-problema-ricette-americane.c` | Tabella di `Conversione` dalle unità americane al sistema metrico |
| `040-problema-ricette-americane-analisi.md` | Analisi di `040-problema-ricette-americane.c` |
| `050-problema-allarmi-sensori.c` | Una `Regola` di allarme per ogni sensore del laboratorio |
| `050-problema-allarmi-sensori-analisi.md` | Analisi di `050-problema-allarmi-sensori.c` |
| `060-problema-menu-a-funzioni.c` | Menu del borsellino della mensa come tabella di `Azione` |
| `060-problema-menu-a-funzioni-analisi.md` | Analisi di `060-problema-menu-a-funzioni.c` |
| `070-problema-cifratura-messaggi.c` | Cesare, ROT13 e Atbash come `Trasforma`, con controllo della decifratura |
| `070-problema-cifratura-messaggi-analisi.md` | Analisi di `070-problema-cifratura-messaggi.c` |
| `080-problema-tariffe-parcheggio.c` | Una funzione che restituisce la `Tariffa` più conveniente |
| `080-problema-tariffe-parcheggio-analisi.md` | Analisi di `080-problema-tariffe-parcheggio.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-nome-a-un-puntatore-a-funzione 010-nome-a-un-puntatore-a-funzione.c
./010-nome-a-un-puntatore-a-funzione

gcc -Wall -Wextra -o 020-funzione-che-restituisce-un-operazione 020-funzione-che-restituisce-un-operazione.c
./020-funzione-che-restituisce-un-operazione

gcc -Wall -Wextra -o 030-tabella-di-operazioni 030-tabella-di-operazioni.c
./030-tabella-di-operazioni

gcc -Wall -Wextra -o 040-problema-ricette-americane 040-problema-ricette-americane.c
./040-problema-ricette-americane

gcc -Wall -Wextra -o 050-problema-allarmi-sensori 050-problema-allarmi-sensori.c
./050-problema-allarmi-sensori

gcc -Wall -Wextra -o 060-problema-menu-a-funzioni 060-problema-menu-a-funzioni.c
./060-problema-menu-a-funzioni

gcc -Wall -Wextra -o 070-problema-cifratura-messaggi 070-problema-cifratura-messaggi.c
./070-problema-cifratura-messaggi

gcc -Wall -Wextra -o 080-problema-tariffe-parcheggio 080-problema-tariffe-parcheggio.c
./080-problema-tariffe-parcheggio
```

---

## Output atteso

### 010-nome-a-un-puntatore-a-funzione
```
Senza typedef:  senza_nome(1.20, 0.90) = 2.10
Con typedef:    calcolo(1.20, 0.90)    = 2.10
Dopo calcolo = prodotto: calcolo(3, 1.10) = 3.30

applica(somma, 2.50, 1.20)    = 3.70
applica(prodotto, 4, 0.90)    = 3.60

sizeof(Operazione) = 8 byte: e' un indirizzo
```

### 020-funzione-che-restituisce-un-operazione
```
  12 + 4 = 16   (senza typedef: 16)
  12 - 4 = 8   (senza typedef: 8)
  12 * 4 = 48   (senza typedef: 48)
  12 / 4 = 3   (senza typedef: 3)
  12 % 4   operazione non disponibile
```

### 030-tabella-di-operazioni
```
La tabella contiene 4 operazioni, 32 byte (4 indirizzi)

   120.00 +  35.00 =   155.00   (tabella[0])
    85.50 -  12.50 =    73.00   (tabella[1])
    24.00 *   3.50 =    84.00   (tabella[2])
   300.00 /  25.00 =    12.00   (tabella[3])
    18.00 ^   2.00   simbolo sconosciuto
```

### 040-problema-ricette-americane
*(output dipendente dall'input – esempio di sessione)*
```
Unita' riconosciute: cup tbsp oz lb F
Quantita' e unita' (0 per finire): 2 cup
  2 cup = 473.2 ml
Quantita' e unita' (0 per finire): 3 tbsp
  3 tbsp = 44.4 ml
Quantita' e unita' (0 per finire): 8 oz
  8 oz = 226.8 g
Quantita' e unita' (0 per finire): 1.5 lb
  1.5 lb = 680.4 g
Quantita' e unita' (0 per finire): 350 F
  350 F = 176.7 gradi C
Quantita' e unita' (0 per finire): 4 pinch
  Unita' "pinch" sconosciuta.
Quantita' e unita' (0 per finire): 0
```

### 050-problema-allarmi-sensori
```
=== ORA PER ORA ===
  ore  8:  temperatura (15.2)
  ore  9:  rumore (82)
  ore 10:  CO2 (1080)
  ore 11:  umidita' (72)  CO2 (1240)
  ore 12:  umidita' (75)  rumore (88)
  ore 13:  temperatura (28.6)  CO2 (1050)

=== ALLARMI PER SENSORE ===
  temperatura  2 su 6 letture
  umidita'     2 su 6 letture
  CO2          3 su 6 letture
  rumore       2 su 6 letture
```

### 060-problema-menu-a-funzioni
*(output dipendente dall'input – esempio di sessione)*
```

  1  ricarica
  2  paga il pasto
  3  paga la merenda
  4  mostra il saldo
  0  esci
Scelta: 4
  Saldo: 8.30 euro

  1  ricarica
  2  paga il pasto
  3  paga la merenda
  4  mostra il saldo
  0  esci
Scelta: 2
  Pagato: pasto 5.20 euro.

  1  ricarica
  2  paga il pasto
  3  paga la merenda
  4  mostra il saldo
  0  esci
Scelta: 2
  Credito insufficiente per pasto: servono 5.20 euro.

  1  ricarica
  2  paga il pasto
  3  paga la merenda
  4  mostra il saldo
  0  esci
Scelta: 1
  Importo in euro (5-50): 20
  Ricarica di 20 euro eseguita.

  1  ricarica
  2  paga il pasto
  3  paga la merenda
  4  mostra il saldo
  0  esci
Scelta: 3
  Pagato: merenda 1.50 euro.

  1  ricarica
  2  paga il pasto
  3  paga la merenda
  4  mostra il saldo
  0  esci
Scelta: 1
  Importo in euro (5-50): 100
  Importo non valido.

  1  ricarica
  2  paga il pasto
  3  paga la merenda
  4  mostra il saldo
  0  esci
Scelta: 7
  Voce inesistente.

  1  ricarica
  2  paga il pasto
  3  paga la merenda
  4  mostra il saldo
  0  esci
Scelta: 0
Arrivederci. Credito residuo: 21.60 euro
```

### 070-problema-cifratura-messaggi
*(output dipendente dall'input – esempio di sessione)*
```
Messaggio (riga vuota per finire): Ci vediamo alle 15, in Aula Magna!
  Cesare  Fl yhgldpr dooh 15, lq Dxod Pdjqd!   -> decifrato ok
  ROT13   Pv irqvnzb nyyr 15, va Nhyn Zntan!   -> decifrato ok
  Atbash  Xr evwrznl zoov 15, rm Zfoz Nztmz!   -> decifrato ok
Messaggio (riga vuota per finire): Zebra xyz
  Cesare  Cheud abc   -> decifrato ok
  ROT13   Mroen klm   -> decifrato ok
  Atbash  Avyiz cba   -> decifrato ok
Messaggio (riga vuota per finire): 
```

### 080-problema-tariffe-parcheggio
*(output dipendente dall'input – esempio di sessione)*
```
Durata della sosta in minuti (0 per finire): 45
  oraria             1.50 euro
  prima ora gratis   0.00 euro
  giornaliera        9.00 euro
  Conviene: prima ora gratis (0.00 euro)
Durata della sosta in minuti (0 per finire): 100
  oraria             3.00 euro
  prima ora gratis   2.00 euro
  giornaliera        9.00 euro
  Conviene: prima ora gratis (2.00 euro)
Durata della sosta in minuti (0 per finire): 200
  oraria             6.00 euro
  prima ora gratis   6.00 euro
  giornaliera        9.00 euro
  Conviene: oraria (6.00 euro)
Durata della sosta in minuti (0 per finire): 500
  oraria            13.50 euro
  prima ora gratis  16.00 euro
  giornaliera        9.00 euro
  Conviene: giornaliera (9.00 euro)
Durata della sosta in minuti (0 per finire): -3
  Durata non valida.
Durata della sosta in minuti (0 per finire): 0
```

---

## Errori comuni da evitare

**Dimenticare le parentesi intorno al nome**
```c
typedef double *Operazione(double, double);     /* tipo funzione che restituisce double * */
typedef double (*Operazione)(double, double);   /* corretto: puntatore a funzione */
```

**Mettere nella tabella una funzione con un prototipo diverso**
```c
double radice(double x);
Operazione tabella[2] = {somma, radice};   /* errore: radice riceve un solo double */
```

**Chiamare un puntatore NULL**
```c
op = scegli('%');
op(12, 4);                 /* errore in esecuzione: op è NULL */
if (op != NULL) { ... }    /* corretto */
```

**Scrivere le parentesi della chiamata nell'assegnamento**
```c
Operazione op = somma(2, 3);    /* errore: assegna il risultato, non la funzione */
Operazione op = somma;          /* corretto */
```

**Indice della tabella fuori dai limiti**
```c
azioni[scelta - 1](&credito);   /* solo dopo aver controllato 1 <= scelta <= VOCI */
```

---

## Concetti collegati

- `05-puntatori/03-puntatori-e-funzioni/03-puntatori-a-funzione` → puntatori a funzione senza typedef
- `05-puntatori/04-puntatori-a-puntatori/02-array-di-puntatori` → la tabella di comandi del robot
- `01-alias-di-tipi-base` → la regola della sintassi di typedef
- `11-algoritmi` → funzioni di confronto passate agli algoritmi di ordinamento

---

## Esercizi proposti

1. In `010-nome-a-un-puntatore-a-funzione.c` aggiungi `differenza` e
   chiamala con `applica`.

2. In `040-problema-ricette-americane.c` aggiungi i millilitri da `fl oz`
   (1 fl oz = 29.57 ml) inserendo una sola funzione e un elemento nelle
   tabelle.

3. In `060-problema-menu-a-funzioni.c` aggiungi la voce "paga la colazione"
   da 2.30 euro.

4. In `070-problema-cifratura-messaggi.c` aggiungi un cifrario che sposta
   le cifre da 0 a 9 di 5 posizioni; qual è la sua funzione inversa?

5. (Avanzato) In `080-problema-tariffe-parcheggio.c` aggiungi una tariffa
   notturna e scrivi `Tariffa piu_cara(...)`: per quali durate la tariffa
   giornaliera è la peggiore?
