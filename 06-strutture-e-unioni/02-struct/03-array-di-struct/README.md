# 03 – Array di struct

## Concetto

Una struct descrive un oggetto; un **array di struct** descrive un elenco
di oggetti dello stesso tipo, come le righe di una tabella:

```c
Studente classe[STUDENTI] = {
    {"Bianchi Sara", 16, 7.8},
    {"Colombo Luca", 17, 6.2},
    ...
};

classe[i]            /* lo studente i: una struct */
classe[i].media      /* un campo dello studente i */
classe[i].nome[0]    /* l'iniziale del suo nome */
```

| Array paralleli | Array di struct |
|-----------------|-----------------|
| `nomi[i]`, `eta[i]`, `medie[i]` | `classe[i].nome`, `classe[i].eta`, `classe[i].media` |
| tre array da tenere allineati | un solo array, i dati restano insieme |
| uno scambio richiede tre scambi | `temp = classe[i]` copia tutto il record |

### Algoritmi sui campi

| Operazione | Condizione |
|------------|------------|
| ricerca per nome | `strcmp(libri[i].titolo, cercato) == 0` |
| massimo | `libri[i].prestiti > libri[migliore].prestiti` |
| conteggio | `libri[i].copie > libri[i].in_prestito` |

Il risultato di una ricerca è l'**indice**: con l'indice si leggono tutti
gli altri campi dello stesso elemento.

### Struct che contengono array

```c
typedef struct {
    char nome[20];
    int voti[MAX_VOTI];
    int n_voti;
} Registro;

classe[s].voti[v]    /* voto v dello studente s */
```

Si legge da sinistra a destra: elemento dell'array esterno, campo, elemento
del campo.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-array-di-struct.c` | Elenco della classe come array di `Studente`, media e copia di un elemento |
| `020-ricerca-e-massimo.c` | Ricerca per titolo, libro più prestato e conteggio dei disponibili |
| `030-struct-con-array.c` | `Registro` con un array di voti; `classe[s].voti[v]` |
| `040-problema-rubrica-classe.c` | Ricerca per inizio del cognome e per ruolo |
| `040-problema-rubrica-classe-analisi.md` | Analisi di `040-problema-rubrica-classe.c` |
| `050-problema-magazzino-laboratorio.c` | Carico, prelievo e articoli sottoscorta |
| `050-problema-magazzino-laboratorio-analisi.md` | Analisi di `050-problema-magazzino-laboratorio.c` |
| `060-problema-corsa-campestre.c` | Podio per categoria con ricerche ripetute del minimo |
| `060-problema-corsa-campestre-analisi.md` | Analisi di `060-problema-corsa-campestre.c` |
| `070-problema-prenotazione-aule.c` | Prenotazioni ora per ora con una matrice dentro ogni `Aula` |
| `070-problema-prenotazione-aule-analisi.md` | Analisi di `070-problema-prenotazione-aule.c` |
| `080-problema-registro-assenze.c` | Ore di assenza mensili e stima rispetto al limite annuale |
| `080-problema-registro-assenze-analisi.md` | Analisi di `080-problema-registro-assenze.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-array-di-struct 010-array-di-struct.c
./010-array-di-struct

gcc -Wall -Wextra -o 020-ricerca-e-massimo 020-ricerca-e-massimo.c
./020-ricerca-e-massimo

gcc -Wall -Wextra -o 030-struct-con-array 030-struct-con-array.c
./030-struct-con-array

gcc -Wall -Wextra -o 040-problema-rubrica-classe 040-problema-rubrica-classe.c
./040-problema-rubrica-classe

gcc -Wall -Wextra -o 050-problema-magazzino-laboratorio 050-problema-magazzino-laboratorio.c
./050-problema-magazzino-laboratorio

gcc -Wall -Wextra -o 060-problema-corsa-campestre 060-problema-corsa-campestre.c
./060-problema-corsa-campestre

gcc -Wall -Wextra -o 070-problema-prenotazione-aule 070-problema-prenotazione-aule.c
./070-problema-prenotazione-aule

gcc -Wall -Wextra -o 080-problema-registro-assenze 080-problema-registro-assenze.c
./080-problema-registro-assenze
```

---

## Output atteso

### 010-array-di-struct
```
  N.  Nome            Eta'  Media
   1  Bianchi Sara      16    7.8
   2  Colombo Luca      17    6.2
   3  Esposito Anna     16    8.4
   4  Ferrari Marco     16    5.9
   5  Galli Irene       17    7.1

Media della classe: 7.08
Rappresentante: Esposito Anna (iniziale E)

sizeof(Studente) = 32, sizeof(classe) = 160 = 5 x 32
```

### 020-ricerca-e-massimo
```
"Fahrenheit 451" di Ray Bradbury: 3 copie, 3 in prestito
Libro piu' prestato: "Fahrenheit 451" (21 prestiti)
Titoli con almeno una copia disponibile: 4 su 6
```

### 030-struct-con-array
```
  Studente         Voti              Media
  Bruno Elisa       7  8  6  9        7.50
  Conti Paolo       5  6  5           5.33
  De Luca Ilaria    8  8  9  7 10     8.40
  Moretti Samuele   4  6              5.00  (pochi voti)

Aggiunto un 7 a Moretti Samuele: ora ha 3 voti
```

### 040-problema-rubrica-classe
*(output dipendente dall'input – esempio di sessione)*
```
Comando (C cognome, R ruolo, E, Q): C Ba
  Barbieri   Giorgia  347 1122334  studente
  Bassi      Andrea   333 5566778  studente
  Bassi      Paola    335 1212121  genitore
  Trovati: 3
Comando (C cognome, R ruolo, E, Q): R docente
  Benedetti  Laura    0131 222333  docente
  Fontana    Diego    0131 444555  docente
  Trovati: 2
Comando (C cognome, R ruolo, E, Q): C Z
  Trovati: 0
Comando (C cognome, R ruolo, E, Q): Q
```

### 050-problema-magazzino-laboratorio
*(output dipendente dall'input – esempio di sessione)*
```
Comando (P codice n, C codice n, S, Q): P LED-R 30
  LED rosso 5 mm: ora 34 pezzi.
  Attenzione: sotto la scorta minima (40).
Comando (P codice n, C codice n, S, Q): P BB400 12
  Breadboard 400 punti: disponibili solo 9 pezzi.
Comando (P codice n, C codice n, S, Q): C BB400 15
  Breadboard 400 punti: ora 24 pezzi.
Comando (P codice n, C codice n, S, Q): P ABC 3
  Codice ABC sconosciuto.
Comando (P codice n, C codice n, S, Q): S
  LED-R  LED rosso 5 mm          34 (minimo 40): ordinare 46
  LED-V  LED verde 5 mm          35 (minimo 40): ordinare 45
  Articoli sottoscorta: 2
Comando (P codice n, C codice n, S, Q): Q
```

### 060-problema-corsa-campestre
```
=== ALLIEVI (4 arrivati) ===
  1. Pellegrini  2C  12'08"
  2. Testa       2A  12'15"  +7 s
  3. Rinaldi     1A  12'22"  +14 s
=== JUNIORES (4 arrivati) ===
  1. Mancini     5A  11'29"
  2. Fabbri      4C  11'38"  +9 s
  3. Gentile     4B  11'41"  +12 s
```

### 070-problema-prenotazione-aule
*(output dipendente dall'input – esempio di sessione)*
```
Comando (P aula ora classe studenti, L ora, T, Q): P 1 1 2C 20
  Lab Alfa alla 1a ora e' gia' della 3A.
Comando (P aula ora classe studenti, L ora, T, Q): P 3 2 1D 22
  Lab Gamma ha solo 16 postazioni.
Comando (P aula ora classe studenti, L ora, T, Q): P 3 2 1D 15
  Prenotato: Lab Gamma, 2a ora, 1D.
Comando (P aula ora classe studenti, L ora, T, Q): L 4
  Lab Beta (24 postazioni)
  Lab Gamma (16 postazioni)
  Aule libere alla 4a ora: 2
Comando (P aula ora classe studenti, L ora, T, Q): T
  Aula        1a  2a  3a  4a  5a  6a
  Lab Alfa    3A   --   --   4B   --   -- 
  Lab Beta    --   5C   5C   --   --   -- 
  Lab Gamma   --   1D   --   --   --   -- 
Comando (P aula ora classe studenti, L ora, T, Q): Q
```

### 080-problema-registro-assenze
```
  Studente          set  ott  nov  dic  gen  Totale     %   Stima
  Amato Giada         2    6    4    3    5      20   3.9      41
  Bellini Tommaso    15   34   32   24   30     135  26.2     276  a rischio
  Cattaneo Sofia      0    3    2    0    1       6   1.2      12
  Donati Kevin       12   27   25   19   24     107  20.7     219  attenzione
  Longo Martina       5   11    9    7    8      40   7.8      82

Ore di lezione svolte: 516 su 1056
Mese con piu' assenze nella classe: ott (81 ore)
```

---

## Errori comuni da evitare

**Mettere l'indice nel posto sbagliato**
```c
classe.media[i]          /* errore: classe è l'array, media non è un array */
classe[i].media          /* corretto */
```

**Cercare con == su un campo stringa**
```c
if (libri[i].titolo == cercato)              /* sbagliato */
if (strcmp(libri[i].titolo, cercato) == 0)   /* corretto */
```

**Usare l'indice -1 di una ricerca senza esito**
```c
printf("%s", libri[trovato].autore);   /* solo dopo aver controllato trovato != -1 */
```

**Scrivere oltre il numero di elementi validi del campo array**
```c
classe[s].voti[classe[s].n_voti] = 7;  /* solo se n_voti < MAX_VOTI */
```

**Inizializzare con meno parentesi del necessario**
```c
Registro r = {"Bruno", 7, 8, 6, 4};       /* confuso: i voti vanno tra graffe */
Registro r = {"Bruno", {7, 8, 6}, 3};     /* corretto */
```

---

## Concetti collegati

- `04-array-e-stringhe/01-array-monodimensionali` → ricerca, massimo e conteggi
- `02-assegnamento-e-confronto` → copiare e confrontare gli elementi
- `03-struct-e-funzioni` → passare un array di struct a una funzione
- `11-algoritmi` → ordinare un array di struct per un campo

---

## Esercizi proposti

1. In `010-array-di-struct.c` stampa gli studenti con la media sopra la
   media della classe.

2. In `040-problema-rubrica-classe.c` rendi la ricerca indipendente da
   maiuscole e minuscole.

3. In `050-problema-magazzino-laboratorio.c` aggiungi il comando `V` con il
   valore del magazzino, dato il prezzo unitario di ogni articolo.

4. In `070-problema-prenotazione-aule.c` aggiungi il comando `A aula ora`
   per annullare una prenotazione.

5. (Avanzato) In `060-problema-corsa-campestre.c` stampa la classifica a
   squadre: la somma dei piazzamenti degli atleti di ogni classe.
