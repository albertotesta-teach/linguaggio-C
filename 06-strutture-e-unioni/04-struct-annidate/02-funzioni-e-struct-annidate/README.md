# 02 – Funzioni e struct annidate

## Concetto

Con le struct annidate una funzione può ricevere la struct intera oppure
**solo la parte che le serve**:

```c
int eta(Data nascita, Data oggi);          /* lavora su qualunque Data */

eta(s.nascita, gita);                      /* la data di nascita di uno studente */
eta(p.scadenza, oggi);                     /* oppure la scadenza di un prestito */
```

Una funzione che riceve la parte è più generale: non dipende dalla struct
che la contiene.

### Puntatori e parti interne

| Ho in mano | Campo interno | Indirizzo della parte |
|------------|---------------|-----------------------|
| `Studente s` | `s.residenza.cap` | `&s.residenza` |
| `Studente *p` | `p->residenza.cap` | `&p->residenza` |

La freccia serve solo dove c'è un puntatore: `p->residenza` è già una
struct, quindi dopo si usa il punto. `&p->residenza` si legge
`&(p->residenza)`.

```c
void cambia_indirizzo(Indirizzo *i, const char *via, ...);

cambia_indirizzo(&s.residenza, ...);       /* modifica solo l'indirizzo */
```

### Funzioni a livelli

Ogni tipo ha le sue funzioni; quella del tipo esterno chiama quelle dei
tipi interni:

```c
void stampa_studente(const Studente *s)
{
    stampa_data(&s->nascita);
    stampa_indirizzo(&s->residenza);
}
```

Se cambia il formato delle date si modifica solo `stampa_data`.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-passare-una-parte.c` | `eta(s.nascita, gita)`: autorizzazioni per i minorenni |
| `020-puntatore-e-campo-interno.c` | `p->residenza.cap` e `&s.residenza`: trasloco e cambio di classe |
| `030-funzioni-a-livelli.c` | Stampa e controllo dello studente con le funzioni delle parti |
| `040-problema-rinnovo-abbonamenti.c` | `aggiungi_mesi(&ab->scadenza, mesi)` e avvisi di scadenza |
| `040-problema-rinnovo-abbonamenti-analisi.md` | Analisi di `040-problema-rinnovo-abbonamenti.c` |
| `050-problema-scheda-dispositivo.c` | Controllo separato di `Hardware` e `Rete`, indirizzi IP duplicati |
| `050-problema-scheda-dispositivo-analisi.md` | Analisi di `050-problema-scheda-dispositivo.c` |
| `060-problema-agenda-verifiche.c` | Spostare una verifica cambiando solo data e ora |
| `060-problema-agenda-verifiche-analisi.md` | Analisi di `060-problema-agenda-verifiche.c` |
| `070-problema-conto-della-gita.c` | `Importo` dentro `Voce`: conto e quota a studente |
| `070-problema-conto-della-gita-analisi.md` | Analisi di `070-problema-conto-della-gita.c` |
| `080-problema-validazione-iscrizione.c` | Una funzione di lettura per ogni parte, con il codice della parte sbagliata |
| `080-problema-validazione-iscrizione-analisi.md` | Analisi di `080-problema-validazione-iscrizione.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-passare-una-parte 010-passare-una-parte.c
./010-passare-una-parte

gcc -Wall -Wextra -o 020-puntatore-e-campo-interno 020-puntatore-e-campo-interno.c
./020-puntatore-e-campo-interno

gcc -Wall -Wextra -o 030-funzioni-a-livelli 030-funzioni-a-livelli.c
./030-funzioni-a-livelli

gcc -Wall -Wextra -o 040-problema-rinnovo-abbonamenti 040-problema-rinnovo-abbonamenti.c
./040-problema-rinnovo-abbonamenti

gcc -Wall -Wextra -o 050-problema-scheda-dispositivo 050-problema-scheda-dispositivo.c
./050-problema-scheda-dispositivo

gcc -Wall -Wextra -o 060-problema-agenda-verifiche 060-problema-agenda-verifiche.c
./060-problema-agenda-verifiche

gcc -Wall -Wextra -o 070-problema-conto-della-gita 070-problema-conto-della-gita.c
./070-problema-conto-della-gita

gcc -Wall -Wextra -o 080-problema-validazione-iscrizione 080-problema-validazione-iscrizione.c
./080-problema-validazione-iscrizione
```

---

## Output atteso

### 010-passare-una-parte
```
Gita del 18/04/2026
  Bruni Chiara  nato/a il 14/04/2008  18 anni
  Conte Mattia  nato/a il 20/04/2008  17 anni  serve l'autorizzazione
  Fabbri Ivo    nato/a il 02/01/2008  18 anni
  Galli Nora    nato/a il 30/09/2008  17 anni  serve l'autorizzazione
Autorizzazioni da raccogliere: 2
```

### 020-puntatore-e-campo-interno
```
Prima:            Neri Luca, 4C, via Roma 77 - 15076 Ovada
Nuova casa:       Neri Luca, 4C, via Cavour 3 - 15121 Alessandria
Nuova classe:     Neri Luca, 4A, corso Roma 10 - 15121 Alessandria
```

### 030-funzioni-a-livelli
```
Rossi Elena, nato/a il 12 mar 2010
  residente in via Marengo 12, 15121 Alessandria
  scheda corretta
Greco Paolo, nato/a il 31 apr 2010
  residente in corso Italia 4, 150A7 Novi Ligure
  data di nascita non valida
  indirizzo non valido
  scheda da correggere
```

### 040-problema-rinnovo-abbonamenti
*(output dipendente dall'input – esempio di sessione)*
```
Data di oggi (gg/mm/aaaa): 20/01/2026
Comando (R numero mesi, A, S, Q): A
  A-1001 Rossi Elena  L3  scadenza 31/01/2026  in scadenza tra 11 giorni
  A-1002 Greco Paolo  L7  scadenza 15/01/2026  SCADUTO da 5 giorni
  A-1004 Villa Sara   L1  scadenza 02/02/2026  in scadenza tra 13 giorni
Comando (R numero mesi, A, S, Q): R A-1001 1
  A-1001 Rossi Elena  L3  scadenza 28/02/2026  valido
Comando (R numero mesi, A, S, Q): R A-1002 3
  A-1002 Greco Paolo  L7  scadenza 20/04/2026  valido
Comando (R numero mesi, A, S, Q): R A-1009 1
  Abbonamento A-1009 inesistente.
Comando (R numero mesi, A, S, Q): R A-1003 13
  Durata non valida: da 1 a 12 mesi.
Comando (R numero mesi, A, S, Q): S
  A-1001 Rossi Elena  L3  scadenza 28/02/2026  valido
  A-1002 Greco Paolo  L7  scadenza 20/04/2026  valido
  A-1003 Costa Marta  L3  scadenza 30/06/2026  valido
  A-1004 Villa Sara   L1  scadenza 02/02/2026  in scadenza tra 13 giorni
Comando (R numero mesi, A, S, Q): Q
```

### 050-problema-scheda-dispositivo
```
PC-01  i5   16 GB RAM   512 GB  192.168.10.11/24 gw 192.168.10.1
    ok
PC-02  i3    8 GB RAM   256 GB  192.168.10.12/24 gw 192.168.1.1
    gateway fuori dalla sottorete
PC-03  i5    4 GB RAM   512 GB  192.168.10.13/24 gw 192.168.10.1
    RAM insufficiente: 4 GB
PC-04  i7   16 GB RAM  1024 GB  192.168.10.11/24 gw 192.168.10.1
    indirizzo gia' usato da PC-01
PC-05  i5   16 GB RAM   512 GB  192.168.10.300/24 gw 192.168.10.1
    indirizzo o gateway con numeri oltre 255

Schede da correggere: 4 su 5
```

### 060-problema-agenda-verifiche
*(output dipendente dall'input – esempio di sessione)*
```
Comando (E, S n gg/mm/aaaa hh:mm, C classe, Q): E
  0  3B  Matematica  10/02/2026  08:00
  1  3B  Inglese     12/02/2026  10:00
  2  3B  Storia      13/02/2026  11:00
  3  4A  Matematica  12/02/2026  09:00
  4  4A  Fisica      16/02/2026  08:00
Comando (E, S n gg/mm/aaaa hh:mm, C classe, Q): S 0 12/02/2026 09:00
  La 3B ha gia' Inglese quel giorno.
Comando (E, S n gg/mm/aaaa hh:mm, C classe, Q): S 0 11/02/2026 09:00
  Spostata: 3B  Matematica  11/02/2026  09:00
Comando (E, S n gg/mm/aaaa hh:mm, C classe, Q): S 4 30/02/2026 08:00
  Data non valida.
Comando (E, S n gg/mm/aaaa hh:mm, C classe, Q): S 4 17/02/2026 14:00
  Le verifiche si fanno tra le 8:00 e le 13:00.
Comando (E, S n gg/mm/aaaa hh:mm, C classe, Q): S 9 17/02/2026 08:00
  Verifica 9 inesistente.
Comando (E, S n gg/mm/aaaa hh:mm, C classe, Q): C 3B
  3B  Matematica  11/02/2026  09:00
  3B  Inglese     12/02/2026  10:00
  3B  Storia      13/02/2026  11:00
Comando (E, S n gg/mm/aaaa hh:mm, C classe, Q): Q
```

### 070-problema-conto-della-gita
*(output dipendente dall'input – 24 studenti e 2 accompagnatori)*
```
Studenti e accompagnatori: 24 2
  Pullman (2 giorni)                         1450.00 euro
  Albergo, 1 notte        58.50 euro x 26 =  1521.00 euro
  Museo Egizio             6.00 euro x 26 =   156.00 euro
  Guida                                       180.00 euro
  Assicurazione            3.50 euro x 26 =    91.00 euro
  Totale                                     3398.00 euro
Quota per studente:   141.59 euro (24 studenti, 2 accompagnatori gratuiti)
Raccolto  3398.16 euro, avanzo     0.16 euro
```

*(output dipendente dall'input – accompagnatori insufficienti)*
```
Studenti e accompagnatori: 40 2
Servono almeno 3 accompagnatori per 40 studenti.
```

### 080-problema-validazione-iscrizione
*(output dipendente dall'input – data sbagliata, poi scheda corretta)*
```
--- Tentativo 1 ---
Nome e cognome: Rossi Elena
Data di nascita (gg/mm/aaaa): 31/04/2012
  Errore nella parte: data di nascita.
--- Tentativo 2 ---
Nome e cognome: Rossi Elena
Data di nascita (gg/mm/aaaa): 12/04/2012
Via: via Marengo 12
CAP: 15121
Comune: Alessandria

Iscrizione registrata:
  Rossi Elena, nato/a il 12/04/2012
  via Marengo 12, 15121 Alessandria
```

*(output dipendente dall'input – tre tentativi sbagliati)*
```
--- Tentativo 1 ---
Nome e cognome: 
  Errore nella parte: nome.
--- Tentativo 2 ---
Nome e cognome: Greco Paolo
Data di nascita (gg/mm/aaaa): 05/09/2009
  Errore nella parte: data di nascita.
--- Tentativo 3 ---
Nome e cognome: Greco Paolo
Data di nascita (gg/mm/aaaa): 05/09/2012
Via: corso Italia 4
CAP: 1506
Comune: Novi Ligure
  Errore nella parte: indirizzo.

Iscrizione non registrata.
```

---

## Errori comuni da evitare

**Passare la struct intera quando serve solo una parte**
```c
int eta(Studente s, Data oggi);       /* funziona solo con gli studenti */
int eta(Data nascita, Data oggi);     /* funziona con qualunque Data */
```

**Usare la freccia dopo il primo livello**
```c
p->residenza->cap        /* errore: residenza non è un puntatore */
p->residenza.cap         /* corretto */
```

**Passare la parte per valore a una funzione che deve modificarla**
```c
void aggiungi_mesi(Data d, int mesi);        /* modifica una copia */
void aggiungi_mesi(Data *d, int mesi);       /* corretto */
aggiungi_mesi(&ab->scadenza, 3);
```

**Dimenticare & davanti alla parte**
```c
stampa_data(s->nascita);        /* errore se stampa_data vuole const Data * */
stampa_data(&s->nascita);       /* corretto */
```

**Ricopiare in ogni funzione il codice delle parti**
```c
printf("%02d/%02d/%d", s->nascita.giorno, ...);   /* ripetuto ovunque */
stampa_data(&s->nascita);                           /* una funzione sola */
```

---

## Concetti collegati

- `03-struct-e-funzioni` → per valore, per indirizzo, `const`
- `01-struct-dentro-struct` → accesso ai campi interni
- `03-array-e-struct-annidate` → funzioni sui livelli di array e struct
- `05-puntatori/03-puntatori-e-funzioni` → passaggio per indirizzo

---

## Esercizi proposti

1. In `010-passare-una-parte.c` aggiungi la funzione `int compie_nel_mese(Data nascita, Data gita)`
   che indica chi compie gli anni nel mese della gita.

2. In `030-funzioni-a-livelli.c` cambia il formato delle date in
   `12/03/2010`, modificando solo `stampa_data`.

3. In `040-problema-rinnovo-abbonamenti.c` aggiungi il comando `T numero`
   che trasferisce l'abbonamento su un'altra linea.

4. In `060-problema-agenda-verifiche.c` rifiuta le verifiche di sabato e di
   domenica (il 1/1/2000 era un sabato).

5. (Avanzato) In `050-problema-scheda-dispositivo.c` aggiungi a `Rete` il
   server DNS e controlla che sia nella stessa sottorete.
