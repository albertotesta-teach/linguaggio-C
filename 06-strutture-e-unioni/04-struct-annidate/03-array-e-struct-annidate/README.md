# 03 – Array e struct annidate

## Concetto

Array e struct si combinano a più livelli: una struct può contenere un
array di struct, e ogni elemento può contenere altre struct o altri array.

```c
typedef struct {
    char nome[4];
    Studente alunni[MAX_ALUNNI];
    int n_alunni;                      /* elementi usati */
} Classe;

typedef struct {
    Classe classi[MAX_CLASSI];
    int n_classi;
} Scuola;
```

### Leggere una catena di accessi

| Espressione | Tipo |
|-------------|------|
| `scuola.classi` | array di `Classe` |
| `scuola.classi[c]` | una `Classe` |
| `scuola.classi[c].alunni` | array di `Studente` |
| `scuola.classi[c].alunni[s]` | uno `Studente` |
| `scuola.classi[c].alunni[s].nascita` | una `Data` |
| `scuola.classi[c].alunni[s].nascita.anno` | un `int` |

Dopo un array viene `[ ]`, dopo una struct viene il punto. I cicli si
annidano allo stesso modo: classi fuori, studenti della classe `c` dentro,
fino a `scuola.classi[c].n_alunni`.

### Una funzione per ogni livello

```c
double media_studente(const Studente *s);       /* voti */
double media_classe(const Classe *c);           /* chiama media_studente(&c->alunni[s]) */
const Classe *migliore(const Scuola *sc);       /* chiama media_classe(&sc->classi[k]) */
```

Le struct che contengono array sono grandi: si passano per indirizzo.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-array-di-struct-in-un-campo.c` | `Classe` con un array di `Studente` e il suo contatore |
| `020-catena-di-accessi.c` | `scuola.classi[c].alunni[s].nascita.anno` con due cicli annidati |
| `030-funzioni-sul-livello-giusto.c` | Medie di studenti, classi e scuola con funzioni a cascata |
| `040-problema-orario-settimanale.c` | Matrice di `Lezione` in ogni classe: ore dei docenti e conflitti |
| `040-problema-orario-settimanale-analisi.md` | Analisi di `040-problema-orario-settimanale.c` |
| `050-problema-torneo-a-squadre.c` | Squadre con la rosa: gol, rose e capocannoniere |
| `050-problema-torneo-a-squadre-analisi.md` | Analisi di `050-problema-torneo-a-squadre.c` |
| `060-problema-itinerario-gita.c` | Tappe con due `Orario`: controllo della sequenza e tempi |
| `060-problema-itinerario-gita-analisi.md` | Analisi di `060-problema-itinerario-gita.c` |
| `070-problema-menu-mensa.c` | Settimana di menu da tre piatti: calorie e piatti ripetuti |
| `070-problema-menu-mensa-analisi.md` | Analisi di `070-problema-menu-mensa.c` |
| `080-problema-registro-di-classe.c` | Voti con data e materia: medie con filtri facoltativi |
| `080-problema-registro-di-classe-analisi.md` | Analisi di `080-problema-registro-di-classe.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-array-di-struct-in-un-campo 010-array-di-struct-in-un-campo.c
./010-array-di-struct-in-un-campo

gcc -Wall -Wextra -o 020-catena-di-accessi 020-catena-di-accessi.c
./020-catena-di-accessi

gcc -Wall -Wextra -o 030-funzioni-sul-livello-giusto 030-funzioni-sul-livello-giusto.c
./030-funzioni-sul-livello-giusto

gcc -Wall -Wextra -o 040-problema-orario-settimanale 040-problema-orario-settimanale.c
./040-problema-orario-settimanale

gcc -Wall -Wextra -o 050-problema-torneo-a-squadre 050-problema-torneo-a-squadre.c
./050-problema-torneo-a-squadre

gcc -Wall -Wextra -o 060-problema-itinerario-gita 060-problema-itinerario-gita.c
./060-problema-itinerario-gita

gcc -Wall -Wextra -o 070-problema-menu-mensa 070-problema-menu-mensa.c
./070-problema-menu-mensa

gcc -Wall -Wextra -o 080-problema-registro-di-classe 080-problema-registro-di-classe.c
./080-problema-registro-di-classe
```

---

## Output atteso

### 010-array-di-struct-in-un-campo
```
Classe piena: Fumo Pia non inserito/a.
Classe 1A (4/4 posti)
  Bassi Rita    7.50
  Corti Ugo     6.00
  Dini Ada      8.25
  Elia Gino     5.50
  media della classe 6.81
sizeof(Studente) = 32 byte, sizeof(Classe) = 144 byte
```

### 020-catena-di-accessi
```
Classe 1S
  Bassi Rita   03/05/2004
  Corti Ugo    21/01/1998
Classe 2S
  Dini Ada     09/09/2006
  Elia Gino    14/02/1995
  Fumo Pia     30/06/2006
Classe 3S
  Gallo Ivo    11/12/1990

Il piu' giovane: Dini Ada della 2S
Nati per anno:  1990: 1  1995: 1  1998: 1  2004: 1  2006: 2
```

### 030-funzioni-sul-livello-giusto
```
1A  media 6.75
    Bassi Rita   7.50
    Corti Ugo    6.00
1B  media 7.19
    Dini Ada     8.33
    Elia Gino    6.00
    Fumo Pia     7.25
2A  media 6.79
    Gallo Ivo    8.25
    Leva Teo     5.33

Premio alla 1B con media 7.19
```

### 040-problema-orario-settimanale
*(output dipendente dall'input – esempio di sessione)*
```
Comando (O classe, D docente, C, Q): O 1A
  1A   Lun         Mar         Mer         Gio         Ven        
  1a   Matematica  Fisica      Informatica Italiano    Inglese    
  2a   Italiano    Matematica  Informatica Ed. fisica  Fisica     
  3a   Inglese     Storia      Matematica  Ed. fisica  Italiano   
  4a   Informatica Italiano    Inglese     Matematica  Storia     
Comando (O classe, D docente, C, Q): D Rossi
  Lun 1a ora  1A  A12      Matematica
  Lun 2a ora  1B  A14      Matematica
  Mar 2a ora  1A  A12      Matematica
  Mar 2a ora  1B  A14      Matematica
  Mer 1a ora  1B  A14      Matematica
  Mer 3a ora  1A  A12      Matematica
  Gio 4a ora  1A  A12      Matematica
  Ven 2a ora  1B  LabFis   Matematica
  Rossi: 8 ore settimanali
Comando (O classe, D docente, C, Q): C
  Mar 2a ora: Rossi in 1A e in 1B
  Ven 2a ora: aula LabFis occupata da 1A e 1B
  Conflitti: 2
Comando (O classe, D docente, C, Q): O 3C
  Classe 3C inesistente.
Comando (O classe, D docente, C, Q): Q
```

### 050-problema-torneo-a-squadre
*(output dipendente dall'input – esempio di sessione)*
```
Comando (G squadra giocatore, R squadra, C, Q): C
  Capocannoniere con 3 gol: Fumo (Tigri)
Comando (G squadra giocatore, R squadra, C, Q): G Tigri Fumo
  Gol di Fumo (Tigri): 4 in tutto.
Comando (G squadra giocatore, R squadra, C, Q): G Squali Orsi
  Gol di Orsi (Squali): 3 in tutto.
Comando (G squadra giocatore, R squadra, C, Q): G Squali Gallo
  Gallo non e' nella rosa della squadra Squali.
Comando (G squadra giocatore, R squadra, C, Q): G Delfini Neri
  Squadra Delfini inesistente.
Comando (G squadra giocatore, R squadra, C, Q): R Squali
  Squali
    Neri     1 gol
    Orsi     3 gol
    Pini     0 gol
    Rota     0 gol
  Totale squadra: 4 gol
Comando (G squadra giocatore, R squadra, C, Q): G Squali Orsi
  Gol di Orsi (Squali): 4 in tutto.
Comando (G squadra giocatore, R squadra, C, Q): C
  Capocannoniere con 4 gol: Fumo (Tigri) Orsi (Squali)
Comando (G squadra giocatore, R squadra, C, Q): Q
```

### 060-problema-itinerario-gita
*(output dipendente dall'input – esempio di sessione)*
```
Tappa (luogo hh:mm hh:mm, FINE): Alessandria 07:00 07:00
  Alessandria: aggiunta
Tappa (luogo hh:mm hh:mm, FINE): Riomaggiore 09:30 11:00
  Riomaggiore: aggiunta
Tappa (luogo hh:mm hh:mm, FINE): Manarola 11:15 12:45
  Manarola: aggiunta
Tappa (luogo hh:mm hh:mm, FINE): Vernazza 12:30 14:00
  Vernazza: arrivo prima della partenza dalla tappa precedente
Tappa (luogo hh:mm hh:mm, FINE): Vernazza 13:05 14:30
  Vernazza: aggiunta
Tappa (luogo hh:mm hh:mm, FINE): Monterosso 15:00 14:00
  Monterosso: orari non validi
Tappa (luogo hh:mm hh:mm, FINE): Monterosso 14:50 16:30
  Monterosso: aggiunta
Tappa (luogo hh:mm hh:mm, FINE): Alessandria 19:00 19:00
  Alessandria: aggiunta
Tappa (luogo hh:mm hh:mm, FINE): FINE

Gita: Cinque Terre
  07:00-07:00  Alessandria    sosta 0 min
        viaggio 150 min
  09:30-11:00  Riomaggiore    sosta 90 min
        viaggio 15 min
  11:15-12:45  Manarola       sosta 90 min
        viaggio 20 min
  13:05-14:30  Vernazza       sosta 85 min
        viaggio 20 min
  14:50-16:30  Monterosso     sosta 100 min
        viaggio 150 min
  19:00-19:00  Alessandria    sosta 0 min
Tappe 6, in viaggio 5 h 55 min, in sosta 6 h 05 min
```

### 070-problema-menu-mensa
*(output dipendente dall'input – limite di 800 kcal)*
```
Limite di calorie per il pranzo: 800

Settimana 12
  Lun  Pasta al pomodoro  Petto di pollo    Insalata          640 kcal
  Mar  Risotto            Frittata          Carote            720 kcal
  Mer  Lasagne            Arrosto           Patate al forno  1000 kcal  OLTRE
  Gio  Pasta al pomodoro  Merluzzo          Insalata          600 kcal
  Ven  Minestrone         Pizza margherita  Insalata          700 kcal
Piu' calorico: Mer (1000 kcal); media 732 kcal
Piatti ripetuti:
  Pasta al pomodoro: 2 volte
  Insalata: 3 volte
```

### 080-problema-registro-di-classe
*(output dipendente dall'input – esempio di sessione)*
```
Comando (V studente materia voto data, M materia, P da a, Q): M Matematica
  Bassi    6.50 (2 voti)
  Conte    6.00 (2 voti)
  Dini     9.00 (1 voto)
Comando (V studente materia voto data, M materia, P da a, Q): M Inglese
  Bassi    8.00 (1 voto)
  Conte    6.50 (2 voti)
  Dini     8.00 (1 voto)
Comando (V studente materia voto data, M materia, P da a, Q): V Dini Matematica 6 10/01/2026
  Registrato: Dini, Matematica 6
Comando (V studente materia voto data, M materia, P da a, Q): V Rossi Inglese 7 10/01/2026
  Rossi non e' nella 3B.
Comando (V studente materia voto data, M materia, P da a, Q): V Bassi Inglese 11 10/01/2026
  Voto non valido.
Comando (V studente materia voto data, M materia, P da a, Q): P 01/10/2025 31/10/2025
  Bassi    7.50 (2 voti)
  Conte    5.50 (2 voti)
  Dini     9.00 (1 voto)
Comando (V studente materia voto data, M materia, P da a, Q): P 01/12/2025 31/01/2026
  Bassi    nessun voto
  Conte    7.00 (1 voto)
  Dini     7.00 (2 voti)
Comando (V studente materia voto data, M materia, P da a, Q): P 01/02/2026 01/01/2026
  Periodo non valido.
Comando (V studente materia voto data, M materia, P da a, Q): Q
```

---

## Errori comuni da evitare

**Mettere l'indice sul livello sbagliato**
```c
scuola.classi.alunni[s][c]       /* errore: classi è l'array, va indicizzato subito */
scuola.classi[c].alunni[s]       /* corretto */
```

**Usare la dimensione massima invece del contatore**
```c
for (s = 0; s < MAX_ALUNNI; s++)               /* legge anche i posti vuoti */
for (s = 0; s < c->n_alunni; s++)              /* corretto */
```

**Aggiungere senza controllare lo spazio**
```c
c->alunni[c->n_alunni] = nuovo;     /* solo se n_alunni < MAX_ALUNNI */
```

**Passare per valore una struct con un array grande**
```c
double media_classe(Classe c);              /* copia tutto l'array */
double media_classe(const Classe *c);       /* corretto */
```

**Scrivere tutta la catena in ogni funzione**
```c
sc->classi[k].alunni[s].voti[v]          /* tre livelli in una funzione sola */
media_classe(&sc->classi[k])             /* meglio: ogni funzione un livello */
```

---

## Concetti collegati

- `02-struct/03-array-di-struct` → array di struct e ricerche su un campo
- `03-struct-e-funzioni/03-array-di-struct-e-funzioni` → array di struct come parametro
- `04-array-e-stringhe/02-array-multidimensionali` → matrici dentro le struct
- `07-memoria-dinamica` → elenchi senza un numero massimo fissato

---

## Esercizi proposti

1. In `010-array-di-struct-in-un-campo.c` aggiungi `int rimuovi(Classe *c, const char *nome)`
   che toglie uno studente spostando indietro quelli successivi.

2. In `020-catena-di-accessi.c` stampa la classe con l'età media più alta.

3. In `050-problema-torneo-a-squadre.c` aggiungi il comando `T` con la
   classifica delle squadre per gol segnati.

4. In `070-problema-menu-mensa.c` segnala i giorni in cui primo e secondo
   insieme superano metà del limite.

5. (Avanzato) In `080-problema-registro-di-classe.c` aggiungi il comando
   `I materia` che elenca gli studenti con la media insufficiente in quella
   materia nel primo periodo (fino al 31 gennaio).
