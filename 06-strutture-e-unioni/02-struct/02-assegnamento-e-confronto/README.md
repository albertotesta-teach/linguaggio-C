# 02 – Assegnamento e confronto

## Concetto

### Copiare: l'assegnamento =

Due struct dello stesso tipo si assegnano con `=`. Tutti i campi vengono
copiati, **compresi gli array** contenuti nella struct:

```c
Pagella simulazione;

simulazione = primo_quadrimestre;   /* copia nome, classe e tutti i voti */
simulazione.voti[1] = 6;            /* l'originale non cambia */
```

Con un array semplice l'assegnamento non è permesso:

| Operazione | Array `int v[4]` | Struct `Pagella p` |
|------------|------------------|--------------------|
| copia | ciclo o `strcpy`; `w = v` non compila | `q = p` |
| confronto | ciclo o `strcmp` | campo per campo |
| scambio | ciclo con appoggio | `temp = a; a = b; b = temp;` |

### Confrontare: campo per campo

```c
if (a == b)              /* errore di compilazione */

uguali = strcmp(a.codice, b.codice) == 0 &&
         strcmp(a.descrizione, b.descrizione) == 0 &&
         a.quantita == b.quantita;
```

I numeri si confrontano con `==`, le stringhe con `strcmp`. Spesso bastano
alcuni campi: due articoli sono lo stesso articolo se hanno lo stesso codice.

### Dimensione e allineamento

Il compilatore può lasciare byte vuoti (padding) tra i campi, così che
`int` e `double` stiano a indirizzi multipli della loro dimensione:

| Struct | Campi | sizeof tipico |
|--------|-------|---------------|
| `Lettura` | `char`, `int`, `char` | 12 |
| `LetturaCompatta` | `int`, `char`, `char` | 8 |

`offsetof(Tipo, campo)` di `<stddef.h>` dà la posizione di un campo.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-copia-con-assegnamento.c` | Copia di una `Pagella` con un array di voti; confronto con un array semplice |
| `020-confronto-campo-per-campo.c` | `==` tra struct non compila; confronto con `strcmp` e `==` |
| `030-dimensione-e-allineamento.c` | Padding, `offsetof` e ordine dei campi |
| `040-problema-scambio-posti.c` | Scambio di postazione: struct intere (sbagliato) e campi (corretto) |
| `040-problema-scambio-posti-analisi.md` | Analisi di `040-problema-scambio-posti.c` |
| `050-problema-backup-impostazioni.c` | Backup, ripristino e valori di fabbrica della LIM |
| `050-problema-backup-impostazioni-analisi.md` | Analisi di `050-problema-backup-impostazioni.c` |
| `060-problema-confronto-pagelle.c` | Secondo quadrimestre come copia del primo e confronto dei voti |
| `060-problema-confronto-pagelle-analisi.md` | Analisi di `060-problema-confronto-pagelle.c` |
| `070-problema-modifiche-anagrafica.c` | Copia di lavoro, elenco dei campi cambiati e conferma |
| `070-problema-modifiche-anagrafica-analisi.md` | Analisi di `070-problema-modifiche-anagrafica.c` |
| `080-problema-doppioni-iscrizioni.c` | Iscrizioni doppie e correzioni confrontate con la precedente |
| `080-problema-doppioni-iscrizioni-analisi.md` | Analisi di `080-problema-doppioni-iscrizioni.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-copia-con-assegnamento 010-copia-con-assegnamento.c
./010-copia-con-assegnamento

gcc -Wall -Wextra -o 020-confronto-campo-per-campo 020-confronto-campo-per-campo.c
./020-confronto-campo-per-campo

gcc -Wall -Wextra -o 030-dimensione-e-allineamento 030-dimensione-e-allineamento.c
./030-dimensione-e-allineamento

gcc -Wall -Wextra -o 040-problema-scambio-posti 040-problema-scambio-posti.c
./040-problema-scambio-posti

gcc -Wall -Wextra -o 050-problema-backup-impostazioni 050-problema-backup-impostazioni.c
./050-problema-backup-impostazioni

gcc -Wall -Wextra -o 060-problema-confronto-pagelle 060-problema-confronto-pagelle.c
./060-problema-confronto-pagelle

gcc -Wall -Wextra -o 070-problema-modifiche-anagrafica 070-problema-modifiche-anagrafica.c
./070-problema-modifiche-anagrafica

gcc -Wall -Wextra -o 080-problema-doppioni-iscrizioni 080-problema-doppioni-iscrizioni.c
./080-problema-doppioni-iscrizioni
```

---

## Output atteso

### 010-copia-con-assegnamento
```
  Materia       Pagella  Simulazione
  italiano            6            6
  matematica          5            6
  inglese             7            8
  informatica         8            8
La pagella di Elena Costa (4A) non e' cambiata.

Un array semplice si copia elemento per elemento: copia_voti[3] = 8
```

### 020-confronto-campo-per-campo
```
Inventario: EL-0042  Multimetro digitale   12
Conteggio:  EL-0042  Multimetro digitale   11

Stesso articolo (stesso codice): si'
Schede identiche (tutti i campi): no
Differenza di quantita': -1
```

### 030-dimensione-e-allineamento
```
=== Lettura: char, int, char ===
  stanza: offset  0, 1 byte
  valore: offset  4, 4 byte
  unita:  offset  8, 1 byte
  sizeof(Lettura) = 12 (dati: 6)

=== LetturaCompatta: int, char, char ===
  valore: offset  0
  stanza: offset  4
  unita:  offset  5
  sizeof(LetturaCompatta) = 8

Per 10000 letture: 120000 byte contro 80000 byte
```

### 040-problema-scambio-posti
*(output dipendente dall'input – esempio di sessione)*
```
Primo studente (nome fila pc): Sofia 2 5
Secondo studente (nome fila pc): Luca 3 1

Scambio delle schede intere (sbagliato):
  Luca     fila 3 pc 1
  Sofia    fila 2 pc 5
  ogni nome ha ancora la sua postazione: nessuno si e' spostato

Scambio di fila e pc (corretto):
  Sofia    fila 3 pc 1
  Luca     fila 2 pc 5
```

### 050-problema-backup-impostazioni
*(output dipendente dall'input – esempio di sessione)*
```
Comando (L n, V n, I nome, B, R, F, S, Q): S
  luminosita' 70, volume 40, ingresso HDMI1, spegnimento dopo 30 min
Comando (L n, V n, I nome, B, R, F, S, Q): L 90
  Luminosita' 90.
Comando (L n, V n, I nome, B, R, F, S, Q): V 120
  Valore tra 0 e 100.
Comando (L n, V n, I nome, B, R, F, S, Q): I PC
  Ingresso PC.
Comando (L n, V n, I nome, B, R, F, S, Q): B
  Impostazioni salvate.
Comando (L n, V n, I nome, B, R, F, S, Q): V 10
  Volume 10.
Comando (L n, V n, I nome, B, R, F, S, Q): S
  luminosita' 90, volume 10, ingresso PC, spegnimento dopo 30 min
Comando (L n, V n, I nome, B, R, F, S, Q): R
  Backup ripristinato.
Comando (L n, V n, I nome, B, R, F, S, Q): S
  luminosita' 90, volume 40, ingresso PC, spegnimento dopo 30 min
Comando (L n, V n, I nome, B, R, F, S, Q): I VGA
  Ingressi: HDMI1, HDMI2, PC.
Comando (L n, V n, I nome, B, R, F, S, Q): L 55
  Luminosita' 55.
Comando (L n, V n, I nome, B, R, F, S, Q): Q
Attenzione: ci sono modifiche non salvate.
```

### 060-problema-confronto-pagelle
*(output dipendente dall'input – esempio di sessione)*
```
Voti del secondo quadrimestre di Davide Greco
  italiano     (primo: 6): 6
  storia       (primo: 7): 8
  inglese      (primo: 5): 6
  matematica   (primo: 4): 5
  informatica  (primo: 8): 12
  voto non valido, resta 8

  Materia        1Q   2Q  Variazione
  italiano        6    6  =
  storia          7    8  +1
  inglese         5    6  +1
  matematica      4    5  +1
  informatica     8    8  =

Materie migliorate: 3, peggiorate: 0
Media: 6.00 -> 6.60
Insufficienze recuperate: 1
```

### 070-problema-modifiche-anagrafica
*(output dipendente dall'input – modifiche confermate)*
```
Scheda di Marino Chiara (Invio per lasciare invariato)
Telefono [0131 555 1234]: 
Email [famiglia.marino@posta.it]: fam.marino@scuola.it
Classe [3]: 4

Modifiche:
  email:    famiglia.marino@posta.it -> fam.marino@scuola.it
  classe:   3 -> 4
Confermi 2 modifiche? (S/N): S
Scheda aggiornata.
Scheda ufficiale: Marino Chiara, 0131 555 1234, fam.marino@scuola.it, classe 4
```

### 080-problema-doppioni-iscrizioni
*(output dipendente dall'input – esempio di sessione)*
```
Iscrizione (cognome corso giorno 1-5, FINE): Rossi robotica 2
  Nuova iscrizione: Rossi, robotica, mar.
Iscrizione (cognome corso giorno 1-5, FINE): Rossi robotica 2
  Doppione scartato.
Iscrizione (cognome corso giorno 1-5, FINE): Bianchi teatro 4
  Nuova iscrizione: Bianchi, teatro, gio.
Iscrizione (cognome corso giorno 1-5, FINE): Bianchi teatro 3
  Correzione: Bianchi passa da gio a mer.
Iscrizione (cognome corso giorno 1-5, FINE): Verdi coro 1
  Nuova iscrizione: Verdi, coro, lun.
Iscrizione (cognome corso giorno 1-5, FINE): Verdi coro 1
  Doppione scartato.
Iscrizione (cognome corso giorno 1-5, FINE): FINE
Iscrizioni valide: 3, doppioni scartati: 2, correzioni: 1
```

---

## Errori comuni da evitare

**Confrontare due struct con ==**
```c
if (corrente == salvate)            /* errore di compilazione */
```

**Confrontare due stringhe con ==**
```c
if (a.codice == b.codice)           /* confronta gli indirizzi: sempre falso */
if (strcmp(a.codice, b.codice) == 0)    /* corretto */
```

**Scambiare la struct intera quando va scambiato un solo dato**
```c
temp = a; a = b; b = temp;          /* scambia anche i nomi */
```

**Assegnare struct di tipi diversi**
```c
Volo v;
CartaImbarco c;
v = c;                              /* errore: tipi diversi, anche con campi simili */
```

**Calcolare la dimensione sommando i campi**
```c
LETTURE * (1 + 4 + 1)               /* sbagliato: dimentica il padding */
LETTURE * sizeof(Lettura)           /* corretto */
```

---

## Concetti collegati

- `01-dichiarazione-e-accesso` → struct, campi e inizializzazione
- `04-array-e-stringhe` → copia e confronto di array e stringhe
- `03-array-di-struct` → copiare un elemento di un array di struct
- `03-struct-e-funzioni` → passare una struct per valore è una copia

---

## Esercizi proposti

1. In `010-copia-con-assegnamento.c` crea una seconda simulazione e stampa
   le tre pagelle affiancate.

2. In `040-problema-scambio-posti.c` aggiungi un terzo studente e fai
   ruotare le postazioni dei tre.

3. In `050-problema-backup-impostazioni.c` aggiungi il comando `T n` per il
   tempo di spegnimento (5-120 minuti).

4. In `060-problema-confronto-pagelle.c` stampa la materia con il
   miglioramento più grande.

5. (Avanzato) In `030-dimensione-e-allineamento.c` aggiungi un campo
   `double` e trova l'ordine dei campi con la `sizeof` più piccola.
