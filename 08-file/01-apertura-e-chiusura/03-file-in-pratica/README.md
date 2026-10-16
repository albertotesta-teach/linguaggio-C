# 03 – File in pratica

## Concetto

### Più file aperti insieme

Un programma può tenere aperti più file, ognuno con il suo `FILE *`. Il
minimo garantito è `FOPEN_MAX` (almeno 8, compresi `stdin`, `stdout` e
`stderr`). Quando servono tutti, se un'apertura fallisce si chiudono
quelli già aperti:

```c
aperti = 0;
ok = 1;
while (aperti < n && ok) {
    f[aperti] = fopen(nomi[aperti], "w");
    ok = f[aperti] != NULL;
    if (ok) {
        aperti++;
    }
}
if (!ok) {
    chiudi_tutti(f, aperti);       /* dall'ultimo al primo */
}
```

### Il buffer

`fputc`, `fputs` e `fprintf` scrivono in un **buffer** in memoria; i dati
arrivano nel file quando il buffer è pieno, con `fflush(f)` o con
`fclose(f)`. Se il programma termina in modo anomalo senza chiudere il
file, i dati nel buffer vanno persi.

### remove e rename

| Funzione | Compito | Risultato |
|----------|---------|-----------|
| `remove(nome)` | cancella il file | 0 se riesce |
| `rename(vecchio, nuovo)` | cambia il nome | 0 se riesce |

Il file non deve essere aperto. Se il nuovo nome esiste già, Linux e
macOS lo sostituiscono, Windows rifiuta: per un programma portabile si
rimuove prima la destinazione.

### Salvataggio sicuro

```c
f = fopen("dati.tmp", "w");
... scrittura di tutti i dati ...
fclose(f);
remove("dati.txt");
rename("dati.tmp", "dati.txt");
```

Fino alla `rename` il file originale resta intatto: un'interruzione a metà
non lo rovina.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-piu-file-aperti.c` | Tre file aperti insieme: tutti o nessuno |
| `020-buffer-e-fflush.c` | Quanti caratteri ci sono nel file prima e dopo `fflush` e `fclose` |
| `030-rimuovere-e-rinominare.c` | `remove` e `rename` riusciti e falliti |
| `040-problema-salvataggio-sicuro.c` | Biblioteca di classe caricata e salvata con un file temporaneo |
| `040-problema-salvataggio-sicuro-analisi.md` | Analisi di `040-problema-salvataggio-sicuro.c` |
| `050-problema-divisione-per-classe.c` | Un file aperto per ogni classe incontrata |
| `050-problema-divisione-per-classe-analisi.md` | Analisi di `050-problema-divisione-per-classe.c` |
| `060-problema-unione-di-file.c` | Più file uniti in uno, saltando quelli mancanti |
| `060-problema-unione-di-file-analisi.md` | Analisi di `060-problema-unione-di-file.c` |
| `070-problema-copie-di-sicurezza.c` | Copie `.bak1`, `.bak2`, `.bak3` a rotazione |
| `070-problema-copie-di-sicurezza-analisi.md` | Analisi di `070-problema-copie-di-sicurezza.c` |
| `080-problema-file-di-blocco.c` | Prenotazione dell'aula con un file di blocco |
| `080-problema-file-di-blocco-analisi.md` | Analisi di `080-problema-file-di-blocco.c` |

---

## Compilazione ed esecuzione

I programmi lavorano nella cartella da cui vengono eseguiti; `060` unisce
i file creati da `050`. Il valore di `FOPEN_MAX` dipende dal sistema.

```bash
gcc -Wall -Wextra -o 010-piu-file-aperti 010-piu-file-aperti.c
./010-piu-file-aperti

gcc -Wall -Wextra -o 020-buffer-e-fflush 020-buffer-e-fflush.c
./020-buffer-e-fflush

gcc -Wall -Wextra -o 030-rimuovere-e-rinominare 030-rimuovere-e-rinominare.c
./030-rimuovere-e-rinominare

gcc -Wall -Wextra -o 040-problema-salvataggio-sicuro 040-problema-salvataggio-sicuro.c
./040-problema-salvataggio-sicuro

gcc -Wall -Wextra -o 050-problema-divisione-per-classe 050-problema-divisione-per-classe.c
./050-problema-divisione-per-classe

gcc -Wall -Wextra -o 060-problema-unione-di-file 060-problema-unione-di-file.c
./060-problema-unione-di-file

gcc -Wall -Wextra -o 070-problema-copie-di-sicurezza 070-problema-copie-di-sicurezza.c
./070-problema-copie-di-sicurezza

gcc -Wall -Wextra -o 080-problema-file-di-blocco 080-problema-file-di-blocco.c
./080-problema-file-di-blocco
```

---

## Output atteso

### 010-piu-file-aperti
```
FOPEN_MAX su questo sistema: 16

Primo tentativo:
  aperto turno-1.txt
  aperto turno-2.txt
  aperto turno-3.txt
  chiuso il file 3
  chiuso il file 2
  chiuso il file 1
  scritti e chiusi 3 file
Secondo tentativo:
  aperto turno-4.txt
  aperto turno-5.txt
  impossibile aprire inesistente/turno-6.txt
  chiuso il file 2
  chiuso il file 1
  nessun file aperto: il lavoro non viene fatto
```

### 020-buffer-e-fflush
```
Dopo due fprintf:       0 caratteri nel file
Dopo fflush:           46 caratteri nel file
Dopo un altro fprintf: 46 caratteri nel file
Dopo fclose:           69 caratteri nel file
```

### 030-rimuovere-e-rinominare
```
creato bozza.txt
rename("bozza.txt", "circolare.txt")     riuscita
  bozza.txt esiste: no, circolare.txt esiste: si'
rename("bozza.txt", "altro.txt")         fallita (il file non c'e')
remove("circolare.txt")                  riuscita
  circolare.txt esiste: no
remove("circolare.txt")                  fallita (il file non c'e')
```

### 040-problema-salvataggio-sicuro
*(output dipendente dall'input – prima esecuzione: libri.txt non esiste)*
```
Libri caricati da libri.txt: 0
Comando (A, R, E, S, Q): A Il barone rampante
  aggiunto al numero 1
Comando (A, R, E, S, Q): A Se questo e' un uomo
  aggiunto al numero 2
Comando (A, R, E, S, Q): A La coscienza di Zeno
  aggiunto al numero 3
Comando (A, R, E, S, Q): E
   1. Il barone rampante
   2. Se questo e' un uomo
   3. La coscienza di Zeno
Comando (A, R, E, S, Q): S
  salvati 3 titoli in libri.txt
Comando (A, R, E, S, Q): Q
```

*(output dipendente dall'input – seconda esecuzione: l'elenco viene ricaricato)*
```
Libri caricati da libri.txt: 3
Comando (A, R, E, S, Q): E
   1. Il barone rampante
   2. Se questo e' un uomo
   3. La coscienza di Zeno
Comando (A, R, E, S, Q): R 2
  rimosso: Se questo e' un uomo
Comando (A, R, E, S, Q): A Il sentiero dei nidi di ragno
  aggiunto al numero 3
Comando (A, R, E, S, Q): R 9
  numero non valido
Comando (A, R, E, S, Q): E
   1. Il barone rampante
   2. La coscienza di Zeno
   3. Il sentiero dei nidi di ragno
Comando (A, R, E, S, Q): Q
  attenzione: le ultime modifiche non sono state salvate
```

### 050-problema-divisione-per-classe
*(output dipendente dall'input – iscritti al corso di primo soccorso)*
```
Iscritti (classe cognome, FINE per terminare):
3A Rossi 4B Bianchi 3A Verdi 5C Neri
4B Russo 3A Gallo 5C Costa FINE

File creati: 3, iscritti scartati: 0
--- classe-3A.txt (iscritti: 3) ---
Rossi
Verdi
Gallo
--- classe-4B.txt (iscritti: 2) ---
Bianchi
Russo
--- classe-5C.txt (iscritti: 2) ---
Neri
Costa
```

### 060-problema-unione-di-file
*(output dipendente dall'input – unione dei file delle classi)*
```
File da creare: iscritti.txt
File da unire (FINE per terminare):
classe-3A.txt classe-4B.txt classe-2D.txt iscritti.txt classe-5C.txt FINE
  aggiunto classe-3A.txt
  aggiunto classe-4B.txt
  classe-2D.txt non trovato: saltato
  iscritti.txt e' il file di destinazione: saltato
  aggiunto classe-5C.txt
iscritti.txt: file uniti 3, mancanti 1, caratteri copiati 43
=== classe-3A.txt ===
Rossi
Verdi
Gallo
=== classe-4B.txt ===
Bianchi
Russo
=== classe-5C.txt ===
Neri
Costa
```

### 070-problema-copie-di-sicurezza
*(output dipendente dall'input – prima modifica: nessuna copia)*
```
File da modificare: verbale.txt
Riga da aggiungere: Seduta del 3 ottobre: presenti tutti i docenti
Aggiunta a verbale.txt.
Versioni presenti:
  verbale.txt        righe: 1
```

*(output dipendente dall'input – seconda modifica)*
```
File da modificare: verbale.txt
Riga da aggiungere: Punto 1: andamento didattico
Aggiunta a verbale.txt.
Versioni presenti:
  verbale.txt        righe: 2
  verbale.txt.bak1   righe: 1
```

*(output dipendente dall'input – terza modifica)*
```
File da modificare: verbale.txt
Riga da aggiungere: Punto 2: uscite didattiche
Aggiunta a verbale.txt.
Versioni presenti:
  verbale.txt        righe: 3
  verbale.txt.bak1   righe: 2
  verbale.txt.bak2   righe: 1
```

*(output dipendente dall'input – quarta modifica)*
```
File da modificare: verbale.txt
Riga da aggiungere: Punto 3: varie
Aggiunta a verbale.txt.
Versioni presenti:
  verbale.txt        righe: 4
  verbale.txt.bak1   righe: 3
  verbale.txt.bak2   righe: 2
  verbale.txt.bak3   righe: 1
```

*(output dipendente dall'input – quinta modifica: la copia piu' vecchia si perde)*
```
File da modificare: verbale.txt
Riga da aggiungere: La seduta e' tolta alle 16:30
Aggiunta a verbale.txt.
Versioni presenti:
  verbale.txt        righe: 5
  verbale.txt.bak1   righe: 4
  verbale.txt.bak2   righe: 3
  verbale.txt.bak3   righe: 2
```

### 080-problema-file-di-blocco
*(output dipendente dall'input – due docenti e l'aula)*
```
Comando (P, L, S, R, Q): S
  libera
Comando (P, L, S, R, Q): P Rossi
  aula prenotata da Rossi
Comando (P, L, S, R, Q): P Bianchi
  aula occupata da Rossi
Comando (P, L, S, R, Q): L Bianchi
  solo Rossi puo' liberare l'aula
Comando (P, L, S, R, Q): S
  occupata da Rossi
Comando (P, L, S, R, Q): L Rossi
  aula liberata da Rossi
Comando (P, L, S, R, Q): P Bianchi
  aula prenotata da Bianchi
Comando (P, L, S, R, Q): R
prenotazione di Rossi
prenotazione di Bianchi
Comando (P, L, S, R, Q): L Bianchi
  aula liberata da Bianchi
Comando (P, L, S, R, Q): Q
```

---

## Errori comuni da evitare

**Lasciare aperti i file già aperti quando un'apertura fallisce**
```c
a = fopen("a.txt", "w");
b = fopen("b.txt", "w");
if (b == NULL) {
    return 1;                       /* a resta aperto */
}
```

**Leggere un file mentre un altro FILE * ci sta scrivendo**
```c
fprintf(f, "dati\n");               /* ancora nel buffer */
conta = conta_caratteri("dati.txt");/* 0: serve fflush(f) o fclose(f) */
```

**Rinominare o rimuovere un file ancora aperto**
```c
f = fopen("bozza.txt", "w");
rename("bozza.txt", "finale.txt");  /* prima fclose(f) */
```

**Riscrivere in "w" il file da salvare**
```c
f = fopen("libri.txt", "w");        /* se il programma si ferma qui, l'elenco è perso */
```

**Ruotare le copie partendo dalla più recente**
```c
rename("x.bak1", "x.bak2");         /* sovrascrive bak2 prima di spostarla */
rename("x.bak2", "x.bak3");
```

---

## Concetti collegati

- `01-aprire-e-chiudere` → `fopen`, `fclose`, modalità di apertura
- `02-flussi-standard` → `stderr` per i messaggi d'errore
- `05-gestione-errori` → `errno` e `perror` per sapere perché `remove` o `rename` falliscono
- `07-memoria-dinamica/01-malloc-e-free` → liberare ciò che si è ottenuto, anche quando qualcosa fallisce

---

## Esercizi proposti

1. In `010-piu-file-aperti.c` rimuovi con `remove` i file vuoti creati
   prima del fallimento.

2. In `040-problema-salvataggio-sicuro.c` aggiungi il comando `O` che
   ordina i titoli prima del salvataggio.

3. In `050-problema-divisione-per-classe.c` scrivi in testa a ogni file il
   nome della classe e, alla fine, il numero di iscritti.

4. In `070-problema-copie-di-sicurezza.c` rendi il numero di copie un
   valore scelto dall'utente.

5. (Avanzato) In `080-problema-file-di-blocco.c` scrivi nel file di blocco
   anche l'ora di inizio e rifiuta di liberare l'aula dopo un tempo massimo.
