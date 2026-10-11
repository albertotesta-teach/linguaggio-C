# 01 – Doppio puntatore

## Concetto

Un puntatore è una variabile e ha un indirizzo. Un **puntatore a
puntatore** contiene l'indirizzo di un puntatore.

```c
int x = 42;
int *p = &x;          /* p punta a x */
int **pp = &p;        /* pp punta a p */
```

| Espressione | Valore |
|-------------|--------|
| `pp` | indirizzo di `p` |
| `*pp` | valore di `p`, cioè l'indirizzo di `x` |
| `**pp` | valore di `x` |
| `**pp = 5` | scrive in `x` |
| `*pp = &y` | `p` ora punta a `y` |

### Perché serve: modificare un puntatore del chiamante

È la stessa regola del passaggio per riferimento, un livello più su:

| Per modificare nel chiamante | la funzione riceve | e scrive |
|------------------------------|--------------------|----------|
| un `int` | `int *` | `*x = ...` |
| un `int *` (dove punta) | `int **` | `*p = ...` |

```c
void scegli_coda(int **coda, int *c1, int *c2, int *c3)
{
    *coda = c1;
    if (*c2 < **coda) {
        *coda = c2;
    }
    ...
}

scegli_coda(&mia_coda, &cassa1, &cassa2, &cassa3);
```

### Il puntatore di lettura che avanza

Una funzione che legge da una stringa può far avanzare il puntatore di
lettura del chiamante: alla chiamata successiva la lettura riprende da lì.

```c
int leggi_numero(const char **p, int *numero)
{
    ...
    while (**p >= '0' && **p <= '9') {
        *numero = *numero * 10 + (**p - '0');
        (*p)++;                 /* sposta il puntatore del chiamante */
    }
    ...
}

const char *lettura = testo;
while (leggi_numero(&lettura, &n)) { ... }
```

`(*p)++` sposta il puntatore del chiamante; `*p++` sposterebbe la copia
locale `p`.

### Esito con `return`, puntatore in uscita

```c
int cerca(int *v, int n, int valore, int **trovato);

if (cerca(posti, N, 0, &posto)) {
    *posto = tessera;
}
```

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-puntatore-a-puntatore.c` | `int **`, `*pp` e `**pp`, tre livelli di indirizzi |
| `020-modificare-un-puntatore-del-chiamante.c` | `int **` per cambiare dove punta un puntatore del main; versione sbagliata con la copia |
| `030-puntatore-che-avanza.c` | `leggi_numero(&p, &n)` con `(*p)++` |
| `040-problema-turno-di-guardia.c` | Puntatore al docente di turno spostato da una funzione |
| `040-problema-turno-di-guardia-analisi.md` | Analisi di `040-problema-turno-di-guardia.c` |
| `050-problema-calcolatrice-espressioni.c` | Espressioni di somme e sottrazioni lette con un unico puntatore |
| `050-problema-calcolatrice-espressioni-analisi.md` | Analisi di `050-problema-calcolatrice-espressioni.c` |
| `060-problema-coppia-piu-vicina.c` | Due puntatori di uscita `const int **` ai tempi più vicini |
| `060-problema-coppia-piu-vicina-analisi.md` | Analisi di `060-problema-coppia-piu-vicina.c` |
| `070-problema-lettore-comandi.c` | Comandi `SET`/`GET` letti parola per parola |
| `070-problema-lettore-comandi-analisi.md` | Analisi di `070-problema-lettore-comandi.c` |
| `080-problema-ricerca-con-esito.c` | Esito con `return` e puntatore all'elemento in `int **` |
| `080-problema-ricerca-con-esito-analisi.md` | Analisi di `080-problema-ricerca-con-esito.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-puntatore-a-puntatore 010-puntatore-a-puntatore.c
./010-puntatore-a-puntatore

gcc -Wall -Wextra -o 020-modificare-un-puntatore-del-chiamante 020-modificare-un-puntatore-del-chiamante.c
./020-modificare-un-puntatore-del-chiamante

gcc -Wall -Wextra -o 030-puntatore-che-avanza 030-puntatore-che-avanza.c
./030-puntatore-che-avanza

gcc -Wall -Wextra -o 040-problema-turno-di-guardia 040-problema-turno-di-guardia.c
./040-problema-turno-di-guardia

gcc -Wall -Wextra -o 050-problema-calcolatrice-espressioni 050-problema-calcolatrice-espressioni.c
./050-problema-calcolatrice-espressioni

gcc -Wall -Wextra -o 060-problema-coppia-piu-vicina 060-problema-coppia-piu-vicina.c
./060-problema-coppia-piu-vicina

gcc -Wall -Wextra -o 070-problema-lettore-comandi 070-problema-lettore-comandi.c
./070-problema-lettore-comandi

gcc -Wall -Wextra -o 080-problema-ricerca-con-esito 080-problema-ricerca-con-esito.c
./080-problema-ricerca-con-esito
```

---

## Output atteso

> Gli indirizzi stampati cambiano a ogni esecuzione.

### 010-puntatore-a-puntatore
```
=== TRE LIVELLI ===
  ascensore    = 2          &ascensore    = 0x7ffe01012530
  selezionato  = 0x7ffe01012530   &selezionato  = 0x7ffe01012538
  pannello     = 0x7ffe01012538

  *pannello    = 0x7ffe01012530   (il valore di selezionato)
  **pannello   = 2                (il valore di ascensore)

Dopo **pannello = 4:  ascensore = 4
Dopo *pannello = &montacarichi: selezionato punta al montacarichi
Dopo **pannello = 1:  ascensore = 4, montacarichi = 1

Ogni livello occupa 8 byte: sizeof(int *) = sizeof(int **)
```

### 020-modificare-un-puntatore-del-chiamante
```
Code iniziali: 4 2 5
  dentro scegli_coda_copia: coda punta a una fila di 2 persone
Dopo scegli_coda_copia: mia_coda punta ancora alla cassa 1? si'
Cliente 1 -> cassa 2.  Code: 4 3 5
Cliente 2 -> cassa 2.  Code: 4 4 5
Cliente 3 -> cassa 1.  Code: 5 4 5
Cliente 4 -> cassa 2.  Code: 5 5 5
```

### 030-puntatore-che-avanza
```
Riga: "  12 7  130 45 9"

  squadra 1:  12 punti   (lettura ora in posizione  4: " 7  130 45 9")
  squadra 2:   7 punti   (lettura ora in posizione  6: "  130 45 9")
  squadra 3: 130 punti   (lettura ora in posizione 11: " 45 9")
  squadra 4:  45 punti   (lettura ora in posizione 14: " 9")
  squadra 5:   9 punti   (lettura ora in posizione 16: "")

Totale: 203 punti
```

### 040-problema-turno-di-guardia
*(output dipendente dall'input – esempio di sessione)*
```
=== SPORTELLO DI TUTORAGGIO ===
Di turno: Rossi. Comando (T svolto, S assente, Q fine): T
  Rossi ha svolto la sua 1a ora
Di turno: Bianco. Comando (T svolto, S assente, Q fine): T
  Bianco ha svolto la sua 1a ora
Di turno: Greco. Comando (T svolto, S assente, Q fine): S
  Greco assente, turno al successivo
Di turno: Fontana. Comando (T svolto, S assente, Q fine): T
  Fontana ha svolto la sua 1a ora
Di turno: Conti. Comando (T svolto, S assente, Q fine): T
  Conti ha svolto la sua 1a ora
Di turno: Rossi. Comando (T svolto, S assente, Q fine): T
  Rossi ha svolto la sua 2a ora
Di turno: Bianco. Comando (T svolto, S assente, Q fine): X
  Comando sconosciuto.
Di turno: Bianco. Comando (T svolto, S assente, Q fine): Q

Ore svolte:  Rossi 2  Bianco 1  Greco 0  Fontana 1  Conti 1
```

### 050-problema-calcolatrice-espressioni
*(output dipendente dall'input – esempio di sessione)*
```
=== CASSA DI CLASSE ===
Espressione (riga vuota per finire): 150 + 35 - 48 + 20 - 12
  = 145 euro
Espressione (riga vuota per finire): 7+8+9
  = 24 euro
Espressione (riga vuota per finire): 150 + - 20
  150 + - 20
        ^ errore qui
Espressione (riga vuota per finire): 100 * 2
  100 * 2
      ^ errore qui
Espressione (riga vuota per finire): 
```

### 060-problema-coppia-piu-vicina
```
Pettorale:      1      2      3      4      5      6      7      8
Tempo (s):  734.2  712.0  786.5  734.3  724.0  746.1  722.8  798.0

Arrivo piu' combattuto: pettorali 1 e 4 (734.2 s e 734.3 s), distacco 0.1 s
Distacco sotto i 2 decimi: serve il fotofinish.
```

### 070-problema-lettore-comandi
*(output dipendente dall'input – esempio di sessione)*
```
Comandi (riga vuota per finire): SET luce 80; SET aria 22; GET luce
  luce -> 80
  aria -> 22
  luce = 80
Comandi (riga vuota per finire): GET tapparelle; SET tapparelle 40; GET tapparelle
  tapparelle = 100
  tapparelle -> 40
  tapparelle = 40
Comandi (riga vuota per finire): SET forno 200; SET luce; GET aria
  SET forno: dispositivo sconosciuto
  SET luce: comando non valido
  aria = 22
Comandi (riga vuota per finire): 
```

### 080-problema-ricerca-con-esito
*(output dipendente dall'input – esempio di sessione)*
```
  Rastrelliera: [ libero ] [    2041] [ libero ] [    1877] [ libero ] [ libero ]
Comando (E tessera, U tessera, Q): E 3310
  Posto 1 assegnato.
  Rastrelliera: [    3310] [    2041] [ libero ] [    1877] [ libero ] [ libero ]
Comando (E tessera, U tessera, Q): E 2041
  La tessera 2041 ha gia' una bici al posto 2.
  Rastrelliera: [    3310] [    2041] [ libero ] [    1877] [ libero ] [ libero ]
Comando (E tessera, U tessera, Q): U 1877
  Posto 4 liberato.
  Rastrelliera: [    3310] [    2041] [ libero ] [ libero ] [ libero ] [ libero ]
Comando (E tessera, U tessera, Q): U 9999
  Nessuna bici con la tessera 9999.
  Rastrelliera: [    3310] [    2041] [ libero ] [ libero ] [ libero ] [ libero ]
Comando (E tessera, U tessera, Q): E 4100
  Posto 3 assegnato.
  Rastrelliera: [    3310] [    2041] [    4100] [ libero ] [ libero ] [ libero ]
Comando (E tessera, U tessera, Q): E 4200
  Posto 4 assegnato.
  Rastrelliera: [    3310] [    2041] [    4100] [    4200] [ libero ] [ libero ]
Comando (E tessera, U tessera, Q): E 4300
  Posto 5 assegnato.
  Rastrelliera: [    3310] [    2041] [    4100] [    4200] [    4300] [ libero ]
Comando (E tessera, U tessera, Q): E 4400
  Posto 6 assegnato.
  Rastrelliera: [    3310] [    2041] [    4100] [    4200] [    4300] [    4400]
Comando (E tessera, U tessera, Q): E 4500
  Rastrelliera piena.
  Rastrelliera: [    3310] [    2041] [    4100] [    4200] [    4300] [    4400]
Comando (E tessera, U tessera, Q): Q
```

---

## Errori comuni da evitare

**Passare il puntatore invece del suo indirizzo**
```c
scegli_coda(mia_coda, ...);     /* avviso: int * al posto di int ** */
scegli_coda(&mia_coda, ...);    /* corretto */
```

**Confondere `*pp` e `**pp`**
```c
*coda = 0;        /* mette a NULL il puntatore del chiamante */
**coda = 0;       /* azzera la variabile puntata */
```

**`*p++` invece di `(*p)++`**
```c
*p++;             /* sposta la copia locale p e legge il carattere */
(*p)++;           /* sposta il puntatore del chiamante */
```

**Modificare la copia del puntatore**
```c
void scegli_coda_copia(int *coda, ...)
{
    coda = c2;    /* il chiamante non vede nulla */
}
```

**Usare il puntatore di uscita quando la ricerca fallisce**
```c
cerca(posti, N, tessera, &posto);
*posto = 0;       /* se l'esito è 0, posto vale NULL */
```

---

## Concetti collegati

- `03-puntatori-e-funzioni/01-parametri-per-riferimento` → la stessa regola un livello più in basso
- `03-puntatori-e-funzioni/02-funzioni-che-restituiscono-puntatori` → puntatore come valore di ritorno
- `02-array-di-puntatori` → un array di puntatori passato a una funzione è un `**`
- `06-memoria-dinamica/01-malloc-e-free` → funzioni che allocano e restituiscono memoria tramite `**`

---

## Esercizi proposti

1. In `010-puntatore-a-puntatore.c` aggiungi un terzo livello `int ***` e
   modifica l'ascensore attraverso tutti e tre i livelli.

2. In `020-modificare-un-puntatore-del-chiamante.c` aggiungi una quarta
   cassa.

3. In `030-puntatore-che-avanza.c` accetta anche numeri separati da virgola.

4. In `050-problema-calcolatrice-espressioni.c` aggiungi la moltiplicazione
   (senza precedenza tra operatori).

5. (Avanzato) In `070-problema-lettore-comandi.c` aggiungi il comando `ADD
   dispositivo n` che somma `n` al valore attuale.
