# 05 – Array di stringhe

## Concetto

Un elenco di parole (nomi, titoli, codici) si memorizza in una **matrice di
`char`**: ogni riga contiene una stringa.

```c
#define N    5
#define LUNG 16

char materie[N][LUNG] = {"Italiano", "Matematica", "Informatica", "Inglese", "Storia"};
```

| Espressione | Che cos'è |
|-------------|-----------|
| `materie[k]` | la riga `k`: una stringa da usare con `printf`, `strlen`, `strcpy`, `strcmp`, `fgets` |
| `materie[k][i]` | il carattere `i` della parola `k` |

Ogni riga occupa sempre `LUNG` celle, anche quando la parola è corta: `LUNG`
deve contenere la parola più lunga **più il `'\0'`**.

### Leggere e assegnare una riga

```c
leggi_riga(citta[k], LUNG);           /* fgets nella riga k */
strcpy(elenco[n], nuovo);             /* assegnazione: mai elenco[n] = nuovo */
```

### Elenchi come parametri

Come per le matrici di numeri, nel parametro va indicato il numero di colonne:

```c
int cerca(const char elenco[][LUNG], int n, const char parola[]);
```

### Operazioni tipiche

| Operazione | Schema |
|------------|--------|
| Ricerca | ricerca lineare con `strcmp(elenco[k], parola) == 0` e flag |
| Primo in ordine alfabetico | come il minimo, con `strcmp(elenco[k], elenco[primo]) < 0` |
| Scambio di due righe | tre `strcpy` con una stringa di appoggio |
| Aggiunta (array a tappo) | `strcpy(elenco[n], nuovo); n++;` |
| Cancellazione | le righe successive si copiano indietro di una posizione, poi `n--` |
| Elenchi paralleli | `nomi[k]`, `numeri[k]`, `prezzi[k]` descrivono lo stesso elemento |

L'ordinamento completo di un elenco (ordinamento per selezione) è trattato
nel capitolo 11.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-elenco-di-parole.c` | Elenco inizializzato e letto da tastiera, lunghezze e memoria occupata |
| `020-ricerca-nell-elenco.c` | Ricerca esatta e senza maiuscole, conteggio per iniziale, array parallelo |
| `030-primo-ultimo-e-scambio.c` | Primo e ultimo in ordine alfabetico, scambio di due righe |
| `040-problema-dizionario.c` | Dizionario italiano-inglese con suggerimenti |
| `040-problema-dizionario-analisi.md` | Analisi di `040-problema-dizionario.c` |
| `050-problema-iscrizioni-duplicate.c` | Duplicati riconosciuti dopo la normalizzazione, elenco pulito |
| `050-problema-iscrizioni-duplicate-analisi.md` | Analisi di `050-problema-iscrizioni-duplicate.c` |
| `060-problema-menu-ristorante.c` | Menu per categoria, ordinazione e conto |
| `060-problema-menu-ristorante-analisi.md` | Analisi di `060-problema-menu-ristorante.c` |
| `070-problema-rubrica-modificabile.c` | Rubrica a tappo: aggiunta, ricerca, cancellazione |
| `070-problema-rubrica-modificabile-analisi.md` | Analisi di `070-problema-rubrica-modificabile.c` |
| `080-problema-anagrammi.c` | Anagrammi trovati confrontando il conteggio delle lettere |
| `080-problema-anagrammi-analisi.md` | Analisi di `080-problema-anagrammi.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-elenco-di-parole 010-elenco-di-parole.c
./010-elenco-di-parole

gcc -Wall -Wextra -o 020-ricerca-nell-elenco 020-ricerca-nell-elenco.c
./020-ricerca-nell-elenco

gcc -Wall -Wextra -o 030-primo-ultimo-e-scambio 030-primo-ultimo-e-scambio.c
./030-primo-ultimo-e-scambio

gcc -Wall -Wextra -o 040-problema-dizionario 040-problema-dizionario.c
./040-problema-dizionario

gcc -Wall -Wextra -o 050-problema-iscrizioni-duplicate 050-problema-iscrizioni-duplicate.c
./050-problema-iscrizioni-duplicate

gcc -Wall -Wextra -o 060-problema-menu-ristorante 060-problema-menu-ristorante.c
./060-problema-menu-ristorante

gcc -Wall -Wextra -o 070-problema-rubrica-modificabile 070-problema-rubrica-modificabile.c
./070-problema-rubrica-modificabile

gcc -Wall -Wextra -o 080-problema-anagrammi 080-problema-anagrammi.c
./080-problema-anagrammi
```

---

## Output atteso

### 010-elenco-di-parole
*(output dipendente dall'input – esempio con una riga troppo lunga)*
```
=== MATERIE ===
  1. Italiano      8 caratteri, iniziale 'I'
  2. Matematica   10 caratteri, iniziale 'M'
  3. Informatica  11 caratteri, iniziale 'I'
  4. Inglese       7 caratteri, iniziale 'I'
  5. Storia        6 caratteri, iniziale 'S'
Memoria: 80 celle riservate (5 x 16), 47 usate dalle parole

=== CITTA' DI PROVENIENZA ===
Citta' dello studente 1: Alessandria
Citta' dello studente 2: Novi Ligure
Citta' dello studente 3:   Acqui Terme
Citta' dello studente 4: Casale Monferrato e dintorni

Elenco inserito:
  [Alessandria]
  [Novi Ligure]
  [  Acqui Terme]
  [Casale Monferra]
Le parentesi mostrano che fgets ha letto anche gli spazi,
e che il testo oltre i 15 caratteri e' stato scartato.
```

### 020-ricerca-nell-elenco
```
=== RICERCA ESATTA (strcmp) ===
  Ferrari Anna   posizione 3, classe 5C
  ferrari anna   non iscritto
  Rossi Mario    non iscritto
  Conti Giulia   posizione 6, classe 5C

=== RICERCA SENZA MAIUSCOLE ===
  ferrari anna   posizione 3, classe 5C

=== ISCRITTI PER INIZIALE DEL COGNOME ===
  B: 2   C: 2   R: 1   Z: 0
```

### 030-primo-ultimo-e-scambio
```
Elenco iniziale:
  0. Il barone rampante
  1. Marcovaldo
  2. Il deserto dei Tartari
  3. Cuore
  4. La luna e i falo'
  5. Il nome della rosa

Primo in ordine alfabetico : "Cuore" (riga 3)
Ultimo in ordine alfabetico: "Marcovaldo" (riga 1)

Dopo lo scambio della riga 0 con la riga 3:
  0. Cuore
  1. Marcovaldo
  2. Il deserto dei Tartari
  3. Il barone rampante
  4. La luna e i falo'
  5. Il nome della rosa
```

### 040-problema-dizionario
*(output dipendente dall'input – esempio con cinque parole)*
```
=== DIZIONARIO ITALIANO-INGLESE (10 voci) ===
Parola (riga vuota per uscire): Scuola
  IT -> EN: scuola = school
Parola (riga vuota per uscire): BOOK
  EN -> IT: book = libro
Parola (riga vuota per uscire): quadro
  "quadro" non e' nel dizionario.
  Forse cercavi: quaderno (notebook)
Parola (riga vuota per uscire): teach
  "teach" non e' nel dizionario.
  Forse cercavi: teacher (insegnante)
Parola (riga vuota per uscire): gatto
  "gatto" non e' nel dizionario.
  Nessun suggerimento.
Parola (riga vuota per uscire): 
```

### 050-problema-iscrizioni-duplicate
```
=== CONTROLLO DEI DUPLICATI ===
  modulo  3 [ROSSI MARIO] e' un duplicato del modulo 1 [Rossi Mario]
  modulo  5 [  bianchi  sara] e' un duplicato del modulo 2 [Bianchi Sara]
  modulo  9 [Verdi  Luca ] e' un duplicato del modulo 4 [Verdi Luca]
  modulo 10 [Neri Anna] e' un duplicato del modulo 6 [Neri Anna]

Moduli ricevuti: 10, duplicati: 4, iscritti: 6
Elenco degli iscritti:
  1. Rossi Mario
  2. Bianchi Sara
  3. Verdi Luca
  4. Neri Anna
  5. Gallo Paolo
  6. Rossi Maria
```

### 060-problema-menu-ristorante
*(output dipendente dall'input – esempio di ordinazione)*
```
=== TRATTORIA DEL BORGO ===
Primi
  Agnolotti al sugo     11.00
  Risotto ai funghi     12.00
Secondi
  Brasato al Barolo     16.00
  Tagliata di manzo     18.00
Contorni
  Insalata mista         4.50
  Patate al forno        4.50
Dolci
  Bonet                  5.50
  Panna cotta            5.00

Tavolo da 2. Piatti ordinati ("conto" per chiudere):
> agnolotti al sugo
  + Agnolotti al sugo
> Brasato al Barolo
  + Brasato al Barolo
> Tiramisu
  "Tiramisu" non e' nel menu.
> BONET
  + Bonet
> Agnolotti al sugo
  + Agnolotti al sugo
> patate al forno
  + Patate al forno
> conto

=== CONTO ===
  2 x Agnolotti al sugo     22.00
  1 x Brasato al Barolo     16.00
  1 x Bonet                  5.50
  1 x Patate al forno        4.50
  2 x Coperto                5.00
  TOTALE                    53.00
```

### 070-problema-rubrica-modificabile
*(output dipendente dall'input – esempio con aggiunte, ricerca e cancellazione)*
```

[3/5] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci
> 1
  Nome: Medico sociale
  Numero: 340 1112223
  Aggiunto.

[4/5] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci
> 1
  Nome: Magazzino
  Numero: 011 223344
  "Magazzino" e' gia' in rubrica.

[4/5] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci
> 1
  Nome: Pulmino
  Numero: 338 9998877
  Aggiunto.

[5/5] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci
> 1
  Rubrica piena: cancella un contatto.

[5/5] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci
> 4
  1. Allenatore Marco   333 1234567
  2. Magazzino          0131 445566
  3. Presidente         347 7654321
  4. Medico sociale     340 1112223
  5. Pulmino            338 9998877

[5/5] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci
> 2
  Testo da cercare: M
  Allenatore Marco   333 1234567
  Magazzino          0131 445566
  Medico sociale     340 1112223

[5/5] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci
> 3
  Nome da cancellare: Magazzino
  Cancellato.

[4/5] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci
> 4
  1. Allenatore Marco   333 1234567
  2. Presidente         347 7654321
  3. Medico sociale     340 1112223
  4. Pulmino            338 9998877

[4/5] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci
> 7
  Scelta non valida.

[4/5] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci
> 0
Rubrica chiusa con 4 contatti.
```

### 080-problema-anagrammi
*(output dipendente dall'input – esempio con quattro parole)*
```
=== RICERCA DI ANAGRAMMI (12 parole in elenco) ===
Parola (riga vuota per uscire): Roma
  amor
  ramo
  Mora
  orma
  armo
  -> 5 anagrammi di "Roma"
Parola (riga vuota per uscire): attore
  teatro
  rotate
  -> 2 anagrammi di "attore"
Parola (riga vuota per uscire): Tale
  tela
  -> 1 anagramma di "Tale"
Parola (riga vuota per uscire): lieto
  -> 0 anagrammi di "lieto"
Parola (riga vuota per uscire): 
```

---

## Errori comuni da evitare

**Riga troppo corta per la parola più lunga**
```c
char materie[5][10] = {"Informatica", ...};   /* 11 lettere + '\0': non entra */
```

**Assegnare una riga con `=`**
```c
elenco[n] = nuovo;            /* errore di compilazione */
strcpy(elenco[n], nuovo);     /* corretto */
```

**Cercare oltre le righe usate**
```c
for (k = 0; k < MAX; k++)     /* in un array a tappo le righe da n in poi */
for (k = 0; k < n; k++)       /* non contengono dati validi */
```

**Cancellare spostando le righe nel verso sbagliato**
```c
/* si copia la riga k + 1 nella riga k partendo da pos verso la fine:
   partendo dalla fine si copierebbe sempre la stessa riga */
```

**Omettere le colonne nel parametro**
```c
int cerca(const char elenco[][], int n, const char parola[]);   /* non compila */
```

---

## Concetti collegati

- `02-array-multidimensionali/01-dichiarazione-e-inizializzazione` → `char nomi[N][LEN]`
- `01-array-monodimensionali/05-array-a-tappo` → aggiunta e cancellazione
- `02-libreria-string-h` → `strcpy`, `strcmp`, `strncmp`
- `11-algoritmi/ordinamento-selection-sort` → ordinare un elenco di parole

---

## Esercizi proposti

1. In `030-primo-ultimo-e-scambio.c` ripeti il passo "trova il primo e
   portalo in cima" sulle righe da 1 in poi, poi da 2 in poi…: ottieni
   l'elenco ordinato.

2. In `040-problema-dizionario.c` aggiungi la possibilità di inserire nuove
   voci (array a tappo con `MAX` voci).

3. In `050-problema-iscrizioni-duplicate.c` stampa per ogni iscritto quante
   volte ha inviato il modulo.

4. In `070-problema-rubrica-modificabile.c` aggiungi il comando "modifica"
   che cambia il numero di un contatto esistente.

5. (Avanzato) In `080-problema-anagrammi.c` raggruppa tutte le parole
   dell'elenco in famiglie di anagrammi e stampa ogni famiglia su una riga.
