# 03 – Array di struct e funzioni

## Concetto

Un array di struct si passa a una funzione come ogni array: la funzione
riceve l'**indirizzo del primo elemento** e il numero di elementi va
passato a parte.

```c
double media_classe(const Studente classe[], int n);   /* sola lettura */
void arrotonda(Studente classe[], int n);              /* modifica gli elementi */

media_classe(classe, STUDENTI);
stampa(&classe[i]);                                    /* un solo elemento */
```

`const Studente classe[]` equivale a `const Studente *classe`: l'array non
viene copiato e la funzione non può modificarlo.

### Scorrere con un puntatore

L'aritmetica dei puntatori vale anche per le struct: `p + 1` punta
all'elemento successivo, `sizeof(Tipo)` byte più avanti.

```c
const Treno *p;
const Treno *fine = treni + n;

for (p = treni; p < fine; p++) {
    ... p->ritardo ...
}
```

La posizione dell'elemento puntato è `p - treni`.

### Funzioni di ricerca

| Restituisce | Prototipo | Il chiamante |
|-------------|-----------|--------------|
| l'indice | `int cerca(const Squadra s[], int n, ...)` | usa `s[i].campo`, controlla `-1` |
| il puntatore | `Squadra *cerca(Squadra s[], int n, ...)` | usa `p->campo`, controlla `NULL` |
| il puntatore in sola lettura | `const Treno *prossima(const Treno t[], ...)` | può solo leggere |

### Il criterio come parametro

Quando cambia solo la condizione, la condizione diventa una funzione:

```c
typedef int (*Criterio)(const Studente *s);

int conta(const Studente classe[], int n, Criterio c);

conta(classe, STUDENTI, insufficiente);
conta(classe, STUDENTI, eccellente);
```

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-array-come-parametro.c` | Media della classe e arrotondamento al mezzo voto |
| `020-puntatore-che-scorre.c` | Tabellone degli arrivi scorso con un puntatore; il treno più in ritardo |
| `030-criterio-come-parametro.c` | `conta` ed `elenca` con un `Criterio` passato come funzione |
| `040-problema-tabellone-stazione.c` | Ritardi, soppressioni e prossimo treno per una destinazione |
| `040-problema-tabellone-stazione-analisi.md` | Analisi di `040-problema-tabellone-stazione.c` |
| `050-problema-campionato-calcetto.c` | Risultati, tabella e capolista senza ordinare l'array |
| `050-problema-campionato-calcetto-analisi.md` | Analisi di `050-problema-campionato-calcetto.c` |
| `060-problema-noleggio-bici.c` | Noleggio e restituzione con le funzioni che lavorano su una bici |
| `060-problema-noleggio-bici-analisi.md` | Analisi di `060-problema-noleggio-bici.c` |
| `070-problema-elezione-rappresentanti.c` | Spoglio delle schede, i due più votati e il ballottaggio |
| `070-problema-elezione-rappresentanti-analisi.md` | Analisi di `070-problema-elezione-rappresentanti.c` |
| `080-problema-filtri-catalogo.c` | Ricerche nel catalogo con una tabella di `Filtro` |
| `080-problema-filtri-catalogo-analisi.md` | Analisi di `080-problema-filtri-catalogo.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-array-come-parametro 010-array-come-parametro.c
./010-array-come-parametro

gcc -Wall -Wextra -o 020-puntatore-che-scorre 020-puntatore-che-scorre.c
./020-puntatore-che-scorre

gcc -Wall -Wextra -o 030-criterio-come-parametro 030-criterio-come-parametro.c
./030-criterio-come-parametro

gcc -Wall -Wextra -o 040-problema-tabellone-stazione 040-problema-tabellone-stazione.c
./040-problema-tabellone-stazione

gcc -Wall -Wextra -o 050-problema-campionato-calcetto 050-problema-campionato-calcetto.c
./050-problema-campionato-calcetto

gcc -Wall -Wextra -o 060-problema-noleggio-bici 060-problema-noleggio-bici.c
./060-problema-noleggio-bici

gcc -Wall -Wextra -o 070-problema-elezione-rappresentanti 070-problema-elezione-rappresentanti.c
./070-problema-elezione-rappresentanti

gcc -Wall -Wextra -o 080-problema-filtri-catalogo 080-problema-filtri-catalogo.c
./080-problema-filtri-catalogo
```

---

## Output atteso

### 010-array-come-parametro
```
Medie calcolate:
  Bianchi Sara    7.82
  Colombo Luca    6.18
  Esposito Anna   8.36
  Ferrari Marco   5.71
  Galli Irene     6.94
  media della classe 7.00

Medie arrotondate al mezzo voto:
  Bianchi Sara    8.00
  Colombo Luca    6.00
  Esposito Anna   8.50
  Ferrari Marco   5.50
  Galli Irene     7.00
  media della classe 7.00
```

### 020-puntatore-che-scorre
```
  Pos  Treno    Provenienza      Ritardo   indirizzo
    0  R 10213  Acqui Terme        0 min   0x7fff6208df90
    1  R 10215  Ovada              7 min   0x7fff6208dfac
    2  RV 2131  Genova            15 min   0x7fff6208dfc8
    3  R 10217  Novi Ligure        3 min   0x7fff6208dfe4
    4  R 10219  Tortona            0 min   0x7fff6208e000
  (gli indirizzi crescono di sizeof(Treno) = 28 byte)

Ritardo maggiore: RV 2131 da Genova, 15 minuti (posizione 2)
Treni puntuali: 2 su 5
```

### 030-criterio-come-parametro
```
media sotto 6: 2 studenti
  Colombo Luca   media 5.4, assenze 48
  Ferrari Marco  media 5.8, assenze 31
media da 8.5 in su: 2 studenti
  Bianchi Sara   media 8.6, assenze 12
  Esposito Anna  media 9.1, assenze 6
piu' di 40 ore di assenza: 2 studenti
  Colombo Luca   media 5.4, assenze 48
  Galli Irene    media 7.2, assenze 54
```

### 040-problema-tabellone-stazione
*(output dipendente dall'input – esempio di sessione)*
```
Comando (R numero min, S numero, P hh:mm destinazione, T, Q): T
  Ora    Treno   Destinazione  Bin  Stato
  07:05  R10220  Genova          2  in orario
  07:12  RV2132  Torino          1  in orario
  07:20  R10404  Pavia           4  in orario
  07:35  R10222  Genova          2  in orario
  07:41  FR9512  Milano          3  in orario
  08:12  RV2134  Torino          1  in orario
Comando (R numero min, S numero, P hh:mm destinazione, T, Q): R R10220 12
  R10220 aggiornato.
Comando (R numero min, S numero, P hh:mm destinazione, T, Q): S R10222
  R10222 aggiornato.
Comando (R numero min, S numero, P hh:mm destinazione, T, Q): R XX1 3
  Treno XX1 non in tabellone.
Comando (R numero min, S numero, P hh:mm destinazione, T, Q): P 07:10 Genova
  Prossimo per Genova: R10220, binario 2, parte alle 07:17
Comando (R numero min, S numero, P hh:mm destinazione, T, Q): P 07:20 Genova
  Nessun treno per Genova.
Comando (R numero min, S numero, P hh:mm destinazione, T, Q): P 07:00 Milano
  Prossimo per Milano: FR9512, binario 3, parte alle 07:41
Comando (R numero min, S numero, P hh:mm destinazione, T, Q): P 07:50 Pavia
  Nessun treno per Pavia.
Comando (R numero min, S numero, P hh:mm destinazione, T, Q): T
  Ora    Treno   Destinazione  Bin  Stato
  07:05  R10220  Genova          2  ritardo 12'
  07:12  RV2132  Torino          1  in orario
  07:20  R10404  Pavia           4  in orario
  07:35  R10222  Genova          2  SOPPRESSO
  07:41  FR9512  Milano          3  in orario
  08:12  RV2134  Torino          1  in orario
Comando (R numero min, S numero, P hh:mm destinazione, T, Q): Q
```

### 050-problema-campionato-calcetto
*(output dipendente dall'input – esempio di sessione)*
```
Risultato (casa gol ospite gol, FINE): Fulmini 3 Tigri 1
Risultato (casa gol ospite gol, FINE): Squali 2 Aquile 2
Risultato (casa gol ospite gol, FINE): Lupi 0 Fulmini 4
Risultato (casa gol ospite gol, FINE): Tigri 2 Squali 1
Risultato (casa gol ospite gol, FINE): Aquile 3 Lupi 3
Risultato (casa gol ospite gol, FINE): Fulmini 1 Squali 1
Risultato (casa gol ospite gol, FINE): Tigri 2 Tigri 1
  Squadre non valide.
Risultato (casa gol ospite gol, FINE): FINE

  Squadra      G  Pt   GF  GS   DR
  Fulmini      3   7    8   2   +6
  Tigri        2   3    3   4   -1
  Squali       3   2    4   5   -1
  Aquile       2   2    5   5   +0
  Lupi         2   1    3   7   -4

Capolista: Fulmini (punti 7)
Ultima:    Lupi (punti 1)
```

### 060-problema-noleggio-bici
*(output dipendente dall'input – esempio di sessione)*
```
Comando (N tessera hh:mm, R tessera hh:mm, S, Q): N 3301 14:10
  Bici B-01 alla tessera 3301.
Comando (N tessera hh:mm, R tessera hh:mm, S, Q): N 3302 14:15
  Bici B-02 alla tessera 3302.
Comando (N tessera hh:mm, R tessera hh:mm, S, Q): N 3301 14:20
  La tessera 3301 ha gia' una bici.
Comando (N tessera hh:mm, R tessera hh:mm, S, Q): R 3302 14:40
  Bici B-02 restituita: 25 minuti, 0.00 euro.
Comando (N tessera hh:mm, R tessera hh:mm, S, Q): R 3301 15:25
  Bici B-01 restituita: 75 minuti, 1.00 euro.
Comando (N tessera hh:mm, R tessera hh:mm, S, Q): R 3303 15:30
  La tessera 3303 non ha bici.
Comando (N tessera hh:mm, R tessera hh:mm, S, Q): S
  B-01  libera     uso totale 75 min
  B-02  libera     uso totale 25 min
  B-03  libera     uso totale 0 min
  B-04  libera     uso totale 0 min
Comando (N tessera hh:mm, R tessera hh:mm, S, Q): Q
```

### 070-problema-elezione-rappresentanti
*(output dipendente dall'input – spoglio di 12 schede)*
```
Scheda (numero candidato, 0 bianca, -1 fine): 1
Scheda (numero candidato, 0 bianca, -1 fine): 2
Scheda (numero candidato, 0 bianca, -1 fine): 3
Scheda (numero candidato, 0 bianca, -1 fine): 1
Scheda (numero candidato, 0 bianca, -1 fine): 4
Scheda (numero candidato, 0 bianca, -1 fine): 0
Scheda (numero candidato, 0 bianca, -1 fine): 2
Scheda (numero candidato, 0 bianca, -1 fine): 7
Scheda (numero candidato, 0 bianca, -1 fine): 1
Scheda (numero candidato, 0 bianca, -1 fine): 3
Scheda (numero candidato, 0 bianca, -1 fine): 5
Scheda (numero candidato, 0 bianca, -1 fine): 4
Scheda (numero candidato, 0 bianca, -1 fine): -1

Schede valide 10, bianche 1, nulle 1
  1. Rossi Elena     4A  voti  3
  2. Marchetti Luca  5B  voti  2
  3. Sanna Giulia    3C  voti  2
  4. Ferri Omar      4B  voti  2
  5. Leone Chiara    5A  voti  1

Primo eletto:   Rossi Elena (voti 3)
Secondo posto: Marchetti Luca e altri 2 a pari voti (2): serve il ballottaggio
```

### 080-problema-filtri-catalogo
*(output dipendente dall'input – esempio di sessione)*
```
  1  autore contiene
  2  genere
  3  pubblicati dal
  4  disponibili
Filtro e valore (0 per finire): 1 Calvino
  Il barone rampante     Italo Calvino   romanzo      1957  libere 1
  Le citta' invisibili   Italo Calvino   romanzo      1972  libere 0
  Trovati: 2
Filtro e valore (0 per finire): 2 fantascienza
  Fahrenheit 451         Ray Bradbury    fantascienza 1953  libere 2
  Io, robot              Isaac Asimov    fantascienza 1950  libere 1
  Trovati: 2
Filtro e valore (0 per finire): 3 1960
  Le citta' invisibili   Italo Calvino   romanzo      1972  libere 0
  Il sistema periodico   Primo Levi      racconti     1975  libere 0
  Trovati: 2
Filtro e valore (0 per finire): 4 x
  Il barone rampante     Italo Calvino   romanzo      1957  libere 1
  Fahrenheit 451         Ray Bradbury    fantascienza 1953  libere 2
  Io, robot              Isaac Asimov    fantascienza 1950  libere 1
  Se questo e' un uomo   Primo Levi      memorie      1947  libere 3
  La luna e i falo'      Cesare Pavese   romanzo      1950  libere 2
  Trovati: 5
Filtro e valore (0 per finire): 9 a
  Filtro inesistente.
Filtro e valore (0 per finire): 0
```

---

## Errori comuni da evitare

**Calcolare il numero di elementi con sizeof dentro la funzione**
```c
double media_classe(const Studente classe[])
{
    int n = sizeof(classe) / sizeof(classe[0]);   /* sizeof di un puntatore */
}
```

**Passare l'elemento invece del suo indirizzo**
```c
stampa(classe[i]);        /* errore se stampa vuole const Studente * */
stampa(&classe[i]);       /* corretto */
```

**Andare oltre l'ultimo elemento con il puntatore**
```c
for (p = treni; p <= treni + n; p++)   /* l'ultimo giro legge fuori dall'array */
for (p = treni; p < treni + n; p++)    /* corretto */
```

**Restituire un puntatore non const a un array ricevuto come const**
```c
Treno *piu_in_ritardo(const Treno t[], int n);         /* warning: perde const */
const Treno *piu_in_ritardo(const Treno t[], int n);   /* corretto */
```

**Chiamare il criterio invece di passarlo**
```c
conta(classe, STUDENTI, insufficiente(&classe[0]));   /* passa un int */
conta(classe, STUDENTI, insufficiente);               /* corretto */
```

---

## Concetti collegati

- `05-puntatori/02-puntatori-e-array` → array come parametro e aritmetica dei puntatori
- `02-struct/03-array-di-struct` → array di struct, ricerca e massimo
- `02-puntatori-a-struct` → funzioni che lavorano su una sola struct
- `11-algoritmi` → ordinare un array di struct con un criterio

---

## Esercizi proposti

1. In `010-array-come-parametro.c` scrivi `int migliore(const Studente classe[], int n)`
   che restituisce l'indice dello studente con la media più alta.

2. In `030-criterio-come-parametro.c` aggiungi il criterio "media tra 6 e 7"
   e aggiungilo alla tabella dei criteri.

3. In `050-problema-campionato-calcetto.c` stampa anche la squadra con
   l'attacco migliore (più gol fatti) e quella con la difesa migliore.

4. In `060-problema-noleggio-bici.c` aggiungi il comando `T` che stampa
   l'incasso totale della giornata.

5. (Avanzato) In `080-problema-filtri-catalogo.c` permetti di combinare
   due filtri: un libro viene mostrato solo se li supera entrambi.
