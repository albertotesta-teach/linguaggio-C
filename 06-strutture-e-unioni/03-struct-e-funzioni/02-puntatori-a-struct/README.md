# 02 – Puntatori a struct

## Concetto

Un puntatore può contenere l'indirizzo di una struct. Per raggiungere un
campo attraverso il puntatore si usa l'operatore **freccia**:

```c
Studente s = {"Bianchi Sara", 16, 7.8};
Studente *p = &s;

(*p).media      /* prima *p (la struct), poi .media */
p->media        /* la stessa cosa, più leggibile */
```

| Ho in mano | Scrivo |
|------------|--------|
| una variabile struct `s` | `s.media` |
| un puntatore `p` a struct | `p->media` |

### Modificare la struct del chiamante

Per modificare un `int` del chiamante una funzione riceve un `int *`; per
modificare una struct riceve l'indirizzo della struct:

```c
void ricarica(Tessera *t, double euro)
{
    t->credito = t->credito + euro;
}

ricarica(&tessera, 20.00);
```

Il valore restituito resta libero per l'esito dell'operazione:
`int paga(Tessera *t, double euro)` restituisce 1 o 0.

### Leggere senza copiare: const

```c
double media(const Registro *r);   /* 8 byte invece di sizeof(Registro) */
```

Con `const` il compilatore rifiuta ogni assegnamento ai campi di `*r`.

| Prototipo | Copia | Può modificare | Quando |
|-----------|-------|----------------|--------|
| `void f(Tipo t)` | sì | solo la copia | struct piccole, solo lettura |
| `void f(const Tipo *t)` | no | no | struct grandi, solo lettura |
| `void f(Tipo *t)` | no | sì | la funzione deve aggiornare la struct |

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-operatore-freccia.c` | `(*p).campo` e `p->campo`: il rappresentante di classe scelto con un puntatore |
| `020-modificare-tramite-puntatore.c` | `ricarica` e `paga` sulla tessera della mensa |
| `030-const-per-leggere.c` | Il registro passato come `const Registro *` invece che per valore |
| `040-problema-borsellino-elettronico.c` | Acquisti e ricariche con codici di esito |
| `040-problema-borsellino-elettronico-analisi.md` | Analisi di `040-problema-borsellino-elettronico.c` |
| `050-problema-termostato-aule.c` | La stessa funzione aggiorna i termostati di due aule |
| `050-problema-termostato-aule-analisi.md` | Analisi di `050-problema-termostato-aule.c` |
| `060-problema-scambio-studenti.c` | Scambio tra due struct tramite puntatori e confronto con le copie |
| `060-problema-scambio-studenti-analisi.md` | Analisi di `060-problema-scambio-studenti.c` |
| `070-problema-lettura-scheda.c` | Una funzione riempie la struct del chiamante e controlla l'ISBN |
| `070-problema-lettura-scheda-analisi.md` | Analisi di `070-problema-lettura-scheda.c` |
| `080-problema-ricerca-puntatore.c` | La ricerca restituisce il puntatore al PC da modificare |
| `080-problema-ricerca-puntatore-analisi.md` | Analisi di `080-problema-ricerca-puntatore.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-operatore-freccia 010-operatore-freccia.c
./010-operatore-freccia

gcc -Wall -Wextra -o 020-modificare-tramite-puntatore 020-modificare-tramite-puntatore.c
./020-modificare-tramite-puntatore

gcc -Wall -Wextra -o 030-const-per-leggere 030-const-per-leggere.c
./030-const-per-leggere

gcc -Wall -Wextra -o 040-problema-borsellino-elettronico 040-problema-borsellino-elettronico.c
./040-problema-borsellino-elettronico

gcc -Wall -Wextra -o 050-problema-termostato-aule 050-problema-termostato-aule.c
./050-problema-termostato-aule

gcc -Wall -Wextra -o 060-problema-scambio-studenti 060-problema-scambio-studenti.c
./060-problema-scambio-studenti

gcc -Wall -Wextra -o 070-problema-lettura-scheda 070-problema-lettura-scheda.c
./070-problema-lettura-scheda

gcc -Wall -Wextra -o 080-problema-ricerca-puntatore 080-problema-ricerca-puntatore.c
./080-problema-ricerca-puntatore
```

---

## Output atteso

### 010-operatore-freccia
```
=== TRE SCRITTURE DELLO STESSO CAMPO ===
  giulia.media     = 7.8
  (*eletto).media  = 7.8
  eletto->media    = 7.8

Indirizzo di giulia: 0x7fff20efe850, valore di eletto: 0x7fff20efe850
Dopo eletto->media += 0.2: giulia.media = 8.0

Ora il rappresentante e' Marco Riva (3B), media 6.9
Iniziale: M
```

### 020-modificare-tramite-puntatore
```
tessera 1024: credito 3.50 euro, pasti consumati 0
Dopo ricarica(&tessera, 10.00): tessera 1024: credito 13.50 euro, pasti consumati 0
Primo pasto pagato:  tessera 1024: credito 8.30 euro, pasti consumati 1
Secondo pasto pagato: tessera 1024: credito 3.10 euro, pasti consumati 2
Terzo pasto rifiutato: credito insufficiente. tessera 1024: credito 3.10 euro, pasti consumati 2
```

### 030-const-per-leggere
```
Registro della 3B: 12 voti
  media 6.50, massimo 9, insufficienze 3
Dopo aggiungi_voto(&registro, 10): media 6.77, massimo 10

Byte passati a ogni chiamata: 8 invece di 808
```

### 040-problema-borsellino-elettronico
*(output dipendente dall'input – esempio di sessione)*
```
  Galli Irene: credito 4.00, speso oggi 0.00 su 3.00
Comando (R euro, A prezzo, G, B, S, Q): S
  Galli Irene: credito 4.00, speso oggi 0.00 su 3.00
Comando (R euro, A prezzo, G, B, S, Q): A 1.20
  acquisto riuscito
Comando (R euro, A prezzo, G, B, S, Q): A 1.50
  acquisto riuscito
Comando (R euro, A prezzo, G, B, S, Q): A 0.80
  limite giornaliero superato
Comando (R euro, A prezzo, G, B, S, Q): G
  Nuovo giorno: spesa azzerata.
Comando (R euro, A prezzo, G, B, S, Q): A 2.50
  credito insufficiente
Comando (R euro, A prezzo, G, B, S, Q): A 1.00
  acquisto riuscito
Comando (R euro, A prezzo, G, B, S, Q): R 60
  Importo non valido (da 1 a 50 euro).
Comando (R euro, A prezzo, G, B, S, Q): R 10
  Ricarica di 10.00 euro.
Comando (R euro, A prezzo, G, B, S, Q): B
  Tessera bloccata.
Comando (R euro, A prezzo, G, B, S, Q): A 0.50
  tessera bloccata
Comando (R euro, A prezzo, G, B, S, Q): B
  Tessera sbloccata.
Comando (R euro, A prezzo, G, B, S, Q): S
  Galli Irene: credito 10.30, speso oggi 1.00 su 3.00
Comando (R euro, A prezzo, G, B, S, Q): Q
```

### 050-problema-termostato-aule
```
  Ora    A1-12          Lab-B         
  08:00  17.8 acceso    18.9 spento   
  08:15  18.6 acceso    18.7 spento   
  08:30  19.4 acceso    18.4 acceso   
  08:45  20.1 acceso    18.8 acceso   
  09:00  20.6 spento    19.3 acceso   
  09:15  20.2 spento    19.6 spento   
  09:30  19.6 spento    19.1 spento   
  09:45  19.3 acceso    18.6 spento   

  A1-12: obiettivo 20.0, minima 17.8, massima 20.6, accensioni 2
  Lab-B: obiettivo 19.0, minima 18.4, massima 19.6, accensioni 1
```

### 060-problema-scambio-studenti
```
Prima dello scambio:
  1A: Lorenzo Fabbri   tedesco
  1B: Aurora Neri      tedesco
  (dentro scambia_copie la copia a contiene Aurora Neri)

Dopo scambia_copie (per valore): nessun cambiamento
  1A: Lorenzo Fabbri   tedesco
  1B: Aurora Neri      tedesco

Dopo scambia_studenti(&prima, &seconda):
  1A: Aurora Neri      tedesco
  1B: Lorenzo Fabbri   tedesco

Scambio con Mattia Conte rifiutato: seconda lingua diversa.
```

### 070-problema-lettura-scheda
*(output dipendente dall'input – titolo vuoto, poi scheda corretta)*
```
--- Tentativo 1 ---
Titolo: 
  Titolo e autore non possono essere vuoti o troppo lunghi.
--- Tentativo 2 ---
Titolo: Il nome della rosa
Autore: Umberto Eco
Anno e pagine: 1980 503
ISBN (13 cifre): 9788845292613

Scheda inserita:
  Il nome della rosa, Umberto Eco (1980), 503 pagine, ISBN 9788845292613
```

*(output dipendente dall'input – cifra di controllo dell'ISBN sbagliata)*
```
--- Tentativo 1 ---
Titolo: Il nome della rosa
Autore: Umberto Eco
Anno e pagine: 1980 503
ISBN (13 cifre): 9788845292614
  ISBN non valido.
--- Tentativo 2 ---
Titolo: Il nome della rosa
Autore: Umberto Eco
Anno e pagine: 1980 503
ISBN (13 cifre): 9788845292613

Scheda inserita:
  Il nome della rosa, Umberto Eco (1980), 503 pagine, ISBN 9788845292613
```

### 080-problema-ricerca-puntatore
*(output dipendente dall'input – esempio di sessione)*
```
Comando (G codice, R codice, U codice n, S, Q): G PC-014
  Guasto registrato sulla postazione 3.
Comando (G codice, R codice, U codice n, S, Q): U PC-012 16
  PC-012 ora ha 16 GB.
Comando (G codice, R codice, U codice n, S, Q): U PC-015 8
  La RAM si puo' solo aumentare (ora 16 GB).
Comando (G codice, R codice, U codice n, S, Q): R PC-014
  PC-014 di nuovo funzionante.
Comando (G codice, R codice, U codice n, S, Q): G PC-099
  PC-099 non e' nell'inventario.
Comando (G codice, R codice, U codice n, S, Q): S
  postazione 1  PC-011   8 GB  guasti 0  ok
  postazione 2  PC-012  16 GB  guasti 1  ok
  postazione 3  PC-014   4 GB  guasti 3  ok
  postazione 4  PC-015  16 GB  guasti 0  ok
  postazione 5  PC-019   8 GB  guasti 0  ok
Comando (G codice, R codice, U codice n, S, Q): Q
```

---

## Errori comuni da evitare

**Usare il punto con un puntatore (o la freccia con una variabile)**
```c
p.media         /* errore: p è un indirizzo */
s->media        /* errore: s non è un puntatore */
```

**Dimenticare le parentesi in (*p).campo**
```c
*p.media        /* significa *(p.media): errore */
(*p).media      /* corretto, ma si preferisce p->media */
```

**Passare la struct invece del suo indirizzo**
```c
ricarica(tessera, 20.00);      /* errore: serve un Tessera * */
ricarica(&tessera, 20.00);     /* corretto */
```

**Dimenticare const in una funzione che legge soltanto**
```c
double media(Registro *r);         /* il prototipo promette una modifica */
double media(const Registro *r);   /* corretto: solo lettura */
```

**Usare il puntatore restituito da una ricerca senza controllarlo**
```c
Computer *pc = cerca(laboratorio, PC, codice);
pc->ram = 16;                      /* se pc == NULL il programma va in crash */
if (pc != NULL) { pc->ram = 16; }  /* corretto */
```

---

## Concetti collegati

- `05-puntatori/03-puntatori-e-funzioni` → passaggio per indirizzo
- `01-struct-per-valore` → passaggio per copia e struct restituita
- `03-array-di-struct-e-funzioni` → puntatori agli elementi di un array
- `07-memoria-dinamica` → struct allocate con `malloc` e raggiunte con `->`

---

## Esercizi proposti

1. In `010-operatore-freccia.c` aggiungi un terzo studente e fai indicare a
   `p` quello con la media più alta.

2. In `020-modificare-tramite-puntatore.c` aggiungi `int trasferisci(Tessera *da, Tessera *a, double euro)`.

3. In `050-problema-termostato-aule.c` aggiungi una terza aula con un
   obiettivo diverso.

4. In `070-problema-lettura-scheda.c` aggiungi il campo `editore` con il
   suo controllo dentro `leggi_libro`.

5. (Avanzato) In `080-problema-ricerca-puntatore.c` aggiungi il comando
   `M codice1 codice2` che scambia i dati di due postazioni con una
   funzione `scambia(Computer *a, Computer *b)`.
