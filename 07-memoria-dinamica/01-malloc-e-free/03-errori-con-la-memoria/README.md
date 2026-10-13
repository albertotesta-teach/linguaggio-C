# 03 – Errori con la memoria

## Concetto

Il compilatore non controlla come si usa lo heap: gli errori con la
memoria compilano senza avvisi e spesso si manifestano lontano dal punto
in cui sono stati commessi.

| Errore | Che cosa succede | Difesa |
|--------|------------------|--------|
| **memory leak** | si perde l'indirizzo di un blocco, che resta occupato | `free` prima di riusare il puntatore |
| **uso dopo free** (puntatore pendente) | si legge o scrive memoria non più del programma | `p = NULL` subito dopo `free(p)` |
| **doppio free** | lo stesso blocco liberato due volte: il programma può bloccarsi | `p = NULL`, e `free(NULL)` non fa nulla |
| **fuori dai limiti** | si scrive oltre la fine del blocco e si rovina altra memoria | indici da 0 a n - 1, `strlen + 1` per le stringhe |
| **overflow di un buffer** | una riga troppo lunga in un array piccolo | `fgets` con la dimensione del buffer |

```c
free(p);
p = NULL;                          /* niente puntatori pendenti */

if (p != NULL) { ... }             /* il blocco c'è ancora? */
```

### Proprietario e copie

Ogni blocco deve avere un solo puntatore "proprietario". Se si copia una
struct che contiene un puntatore, la copia condivide il blocco (copia
**superficiale**); per avere un blocco proprio serve una copia
**profonda**, che alloca e copia i dati.

### Strumenti

```bash
gcc -g -fsanitize=address programma.c     # AddressSanitizer (gcc e clang)
```

Il programma si ferma al primo accesso fuori da un blocco, a un uso dopo
`free` o a un doppio `free`, e indica la riga; su Linux a fine programma
elenca anche i blocchi persi.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-memory-leak.c` | Un puntatore riusato senza `free`: contatori allocati e liberati |
| `020-doppio-free-e-puntatore-pendente.c` | `libera(&p)`: `free` e `p = NULL` insieme |
| `030-fuori-dai-limiti.c` | Un ciclo con `<=` che scrive nell'array vicino |
| `040-problema-contatore-allocazioni.c` | Registro dei blocchi: perdite e doppi free segnalati |
| `040-problema-contatore-allocazioni-analisi.md` | Analisi di `040-problema-contatore-allocazioni.c` |
| `050-problema-riga-sicura.c` | Righe lette senza overflow e copiate nella lunghezza esatta |
| `050-problema-riga-sicura-analisi.md` | Analisi di `050-problema-riga-sicura.c` |
| `060-problema-prestiti-attrezzatura.c` | Array di puntatori: `NULL` per lo scaffale libero |
| `060-problema-prestiti-attrezzatura-analisi.md` | Analisi di `060-problema-prestiti-attrezzatura.c` |
| `070-problema-copia-del-registro.c` | Copia superficiale e copia profonda di una struct con puntatore |
| `070-problema-copia-del-registro-analisi.md` | Analisi di `070-problema-copia-del-registro.c` |
| `080-problema-archivio-foto.c` | Foto e didascalie: memoria su due livelli |
| `080-problema-archivio-foto-analisi.md` | Analisi di `080-problema-archivio-foto.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-memory-leak 010-memory-leak.c
./010-memory-leak

gcc -Wall -Wextra -o 020-doppio-free-e-puntatore-pendente 020-doppio-free-e-puntatore-pendente.c
./020-doppio-free-e-puntatore-pendente

gcc -Wall -Wextra -o 030-fuori-dai-limiti 030-fuori-dai-limiti.c
./030-fuori-dai-limiti

gcc -Wall -Wextra -o 040-problema-contatore-allocazioni 040-problema-contatore-allocazioni.c
./040-problema-contatore-allocazioni

gcc -Wall -Wextra -o 050-problema-riga-sicura 050-problema-riga-sicura.c
./050-problema-riga-sicura

gcc -Wall -Wextra -o 060-problema-prestiti-attrezzatura 060-problema-prestiti-attrezzatura.c
./060-problema-prestiti-attrezzatura

gcc -Wall -Wextra -o 070-problema-copia-del-registro 070-problema-copia-del-registro.c
./070-problema-copia-del-registro

gcc -Wall -Wextra -o 080-problema-archivio-foto 080-problema-archivio-foto.c
./080-problema-archivio-foto
```

Gli indirizzi stampati cambiano da un'esecuzione all'altra.
`010-memory-leak.c` perde davvero due blocchi: compilato con
`-fsanitize=address` su Linux, a fine programma li segnala.

---

## Output atteso

### 010-memory-leak
```
Versione con perdita:
  monitor: Assemblea alle 10    blocco 0x55eae77012b0
  monitor: Palestra chiusa      blocco 0x55eae77012e0
  monitor: Uscita alle 12       blocco 0x55eae7701310
  allocati 3, liberati 1: blocchi persi 2 (80 byte)

Versione corretta:
  monitor: Assemblea alle 10    blocco 0x55eae7701310
  monitor: Palestra chiusa      blocco 0x55eae7701310
  monitor: Uscita alle 12       blocco 0x55eae7701310
  allocati 3, liberati 3: blocchi persi 0
```

### 020-doppio-free-e-puntatore-pendente
```
Prenotata LAB2 alla 3a ora (prof. Galli), blocco 0x561a9901d2a0
Annullata la prenotazione di LAB2.
Dopo l'annullamento il puntatore vale (nil)
Nessuna prenotazione da annullare.
```

### 030-fuori-dai-limiti
```
  mattina   :   0   0   0   0
  pomeriggio:  17   0   0   0

Ciclo sbagliato: i <= POSTI
  mattina   :   1   1   1   1
  pomeriggio:   1   0   0   0
La prenotazione 17 del pomeriggio e' stata cancellata.
```

### 040-problema-contatore-allocazioni
*(output dipendente dall'input – esempio di sessione)*
```
Comando (A, L, R, Q): A 400 elenco-studenti
  blocco 1: 400 byte per elenco-studenti
Comando (A, L, R, Q): A 2000 tabella-voti
  blocco 2: 2000 byte per tabella-voti
Comando (A, L, R, Q): A 64 nome-classe
  blocco 3: 64 byte per nome-classe
Comando (A, L, R, Q): L 2
  blocco 2 liberato
Comando (A, L, R, Q): L 2
  blocco 2 gia' liberato: doppio free evitato
Comando (A, L, R, Q): L 9
  blocco 9 inesistente
Comando (A, L, R, Q): R
  Blocchi allocati: 3, ancora attivi:
     1     400 byte  elenco-studenti
     3      64 byte  nome-classe
  Byte attivi: 464
Comando (A, L, R, Q): A 128 messaggio
  blocco 4: 128 byte per messaggio
Comando (A, L, R, Q): Q

Fine del programma
  Blocchi allocati: 4, ancora attivi:
     1     400 byte  elenco-studenti
     3      64 byte  nome-classe
     4     128 byte  messaggio
  Byte attivi: 592
  Il programma avrebbe perso questi blocchi: li libera il registro.
  Picco di memoria: 2464 byte
```

### 050-problema-riga-sicura
*(output dipendente dall'input – messaggi di varie lunghezze)*
```
Messaggi per la bacheca (al massimo 30 caratteri, FINE per terminare)
> Assemblea di istituto venerdi
  pubblicato (30 byte)
> Cercasi compagni per il torneo di scacchi del giovedi pomeriggio
  troppo lungo: 64 caratteri, massimo 30
> 
  messaggio vuoto
> Palestra chiusa per lavori
  pubblicato (27 byte)
> 123456789012345678901234567890
  pubblicato (31 byte)
> 1234567890123456789012345678901
  troppo lungo: 31 caratteri, massimo 30
> FINE

+--------------------------------+
| Assemblea di istituto venerdi  |
| Palestra chiusa per lavori     |
| 123456789012345678901234567890 |
+--------------------------------+
```

### 060-problema-prestiti-attrezzatura
*(output dipendente dall'input – esempio di sessione)*
```
Comando (U, R, E, Q): U pallone Marta
  pallone a Marta: scaffale 1
Comando (U, R, E, Q): U racchetta Luca
  racchetta a Luca: scaffale 2
Comando (U, R, E, Q): U cronometro Sara
  cronometro a Sara: scaffale 3
Comando (U, R, E, Q): R 2
  rientrato racchetta da Luca
Comando (U, R, E, Q): R 2
  Scaffale 2 vuoto: niente da far rientrare.
Comando (U, R, E, Q): U pallone Paolo
  pallone a Paolo: scaffale 2
Comando (U, R, E, Q): U corda Anna
  corda a Anna: scaffale 4
Comando (U, R, E, Q): U palla Rita
  Registro pieno: nessuno scaffale libero.
Comando (U, R, E, Q): R 7
  Scaffale non valido.
Comando (U, R, E, Q): E
  1  pallone        Marta
  2  pallone        Paolo
  3  cronometro     Sara
  4  corda          Anna
Comando (U, R, E, Q): Q

Chiusura del magazzino
  da recuperare: pallone (Marta)
  da recuperare: pallone (Paolo)
  da recuperare: cronometro (Sara)
  da recuperare: corda (Anna)
  blocchi allocati 5, liberati 5: nessun blocco rimasto in memoria
```

### 070-problema-copia-del-registro
*(output dipendente dall'input – due modifiche)*
```
Classe e numero di voti: 4B 5
Voti: 6 5.5 7 4 8
Modifica (posizione voto, FINE): 2 6
Modifica (posizione voto, FINE): 4 6
Modifica (posizione voto, FINE): 9 7
  modifica non valida
Modifica (posizione voto, FINE): FINE
   originale  4B:  6.0  5.5  7.0  4.0  8.0

1. Copia profonda: duplica(&originale, &copia)
   blocco dell'originale 0x5603ec470ac0, della copia 0x5603ec470af0
   copia      4B:  6.0  6.0  7.0  6.0  8.0
   originale  4B:  6.0  5.5  7.0  4.0  8.0
   L'originale non cambia.

2. Copia superficiale: copia = originale
   blocco dell'originale 0x5603ec470ac0, della copia 0x5603ec470ac0
   copia      4B:  6.0  6.0  7.0  6.0  8.0
   originale  4B:  6.0  6.0  7.0  6.0  8.0
   Anche l'originale e' cambiato: il blocco dei voti e' lo stesso.
```

### 080-problema-archivio-foto
*(output dipendente dall'input – esempio di sessione)*
```
Comando (A, C, D, M, Q): M
  archivio vuoto
Comando (A, C, D, M, Q): A 2024 Marta Festa di fine anno in cortile
  foto 1 aggiunta (didascalia di 30 byte)
Comando (A, C, D, M, Q): A 2025 Luca   Gara di robotica a Torino  
  foto 2 aggiunta (didascalia di 26 byte)
Comando (A, C, D, M, Q): A 2023 Sara
  Manca la didascalia.
Comando (A, C, D, M, Q): A 1800 Sara vecchia
  Dati non validi.
Comando (A, C, D, M, Q): A 2025 Sara Laboratorio di chimica
  foto 3 aggiunta (didascalia di 23 byte)
Comando (A, C, D, M, Q): C 2 Primo posto alla gara di robotica
  didascalia della foto 2 cambiata
Comando (A, C, D, M, Q): C 9 niente
  Foto inesistente.
Comando (A, C, D, M, Q): D 1
  foto 1 eliminata
Comando (A, C, D, M, Q): M
  1. [2025, Luca] Primo posto alla gara di robotica
  2. [2025, Sara] Laboratorio di chimica
Comando (A, C, D, M, Q): Q
Archivio chiuso: foto liberate 2, blocchi liberati 4
```

---

## Errori comuni da evitare

**Riassegnare un puntatore senza liberare il blocco**
```c
avviso = malloc(LUNG);
avviso = malloc(LUNG);             /* il primo blocco è perso */
```

**Usare un puntatore dopo free**
```c
free(p);
printf("%s", p->aula);             /* comportamento non definito */
```

**Liberare due volte lo stesso blocco**
```c
Registro copia = originale;        /* stesso puntatore voti */
free(copia.voti);
free(originale.voti);              /* doppio free */
```

**Ciclo con <= sulla dimensione**
```c
for (i = 0; i <= n; i++) { v[i] = 0; }    /* v[n] è fuori dal blocco */
```

**Liberare il blocco vecchio prima di avere il nuovo**
```c
free(f->didascalia);
f->didascalia = copia_testo(nuova);       /* se fallisce, la foto resta senza */
```

---

## Concetti collegati

- `01-allocare-e-liberare` → `malloc` e `free`
- `02-funzioni-e-memoria-dinamica` → coppie crea/distruggi
- `05-puntatori/04-puntatori-a-puntatori` → `libera(&p)`
- `04-array-e-stringhe/03-stringhe` → `fgets` e terminatore `'\0'`

---

## Esercizi proposti

1. In `010-memory-leak.c` scrivi una terza versione che conserva tutti gli
   avvisi in un array di puntatori e li libera alla fine.

2. In `040-problema-contatore-allocazioni.c` aggiungi il comando `T` con
   il numero totale di byte allocati dall'inizio.

3. In `060-problema-prestiti-attrezzatura.c` aggiungi il comando `S
   studente` che fa rientrare tutti gli oggetti di uno studente.

4. In `070-problema-copia-del-registro.c` scrivi `int uguali(const
   Registro *a, const Registro *b)` che confronta i voti, non i puntatori.

5. (Avanzato) In `080-problema-archivio-foto.c` aggiungi a ogni foto un
   secondo testo allocato, l'elenco delle persone ritratte, e aggiorna
   crea, distruggi e mostra.
