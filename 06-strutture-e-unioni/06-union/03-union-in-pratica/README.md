# 03 – Union in pratica

## Concetto

### Union anonima (C11)

Dentro una struct la union può non avere nome: i suoi campi si usano come
campi della struct, ma continuano a condividere la memoria.

```c
typedef struct {
    TipoDato tipo;
    union {
        int intero;
        double reale;
        char testo[16];
    };                          /* nessun nome */
} Dato;

Dato d = {.tipo = REALE, .reale = 9.81};
d.reale                         /* invece di d.v.reale */
```

### Array di valori misti

Gli elementi di un array sono tutti `Dato`, ma ognuno può contenere un
tipo diverso: un ciclo guarda l'etichetta di ogni elemento.

```c
Dato riga[] = {
    {.tipo = TESTO, .testo = "Bassi"},
    {.tipo = INTERO, .intero = 17},
    {.tipo = REALE, .reale = 7.5}
};
```

### Accesso controllato

```c
int come_reale(const Dato *d, double *risultato);   /* 1 se riesce */

if (come_reale(&d, &x)) {
    /* x è valido */
}
```

La funzione controlla l'etichetta e restituisce un esito: chi la chiama
non tocca mai la union e non può leggere il campo sbagliato.

### Dove si usano

| Situazione | Etichetta | Alternative |
|------------|-----------|-------------|
| file di configurazione | tipo previsto per la chiave | intero, reale, sì/no, testo |
| comandi di un robot | comando | spostamento, angolo, frase |
| espressioni | tipo di token | numero oppure simbolo |
| registro di eventi | tipo di evento | dati della porta, del sensore, del badge |

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-union-anonima.c` | La stessa struct con union con nome e anonima |
| `020-array-di-valori-misti.c` | Una riga di iscrizioni: conteggi per tipo, somma, testi |
| `030-accesso-controllato.c` | `come_intero` e `come_reale` con esito e parametro di uscita |
| `040-problema-impostazioni.c` | File `chiave=valore` convertito secondo il tipo di ogni chiave |
| `040-problema-impostazioni-analisi.md` | Analisi di `040-problema-impostazioni.c` |
| `050-problema-comandi-robot.c` | Programma del robot: analisi delle righe ed esecuzione |
| `050-problema-comandi-robot-analisi.md` | Analisi di `050-problema-comandi-robot.c` |
| `060-problema-token-espressione.c` | Token di un'espressione e calcolo ricorsivo con precedenza |
| `060-problema-token-espressione-analisi.md` | Analisi di `060-problema-token-espressione.c` |
| `070-problema-registro-eventi.c` | Eventi di porte, sensori e badge: filtro per tipo e anomalie |
| `070-problema-registro-eventi-analisi.md` | Analisi di `070-problema-registro-eventi.c` |
| `080-problema-calcolatrice-unita.c` | Conversioni tra unità: un enum di unità per ogni dimensione |
| `080-problema-calcolatrice-unita-analisi.md` | Analisi di `080-problema-calcolatrice-unita.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-union-anonima 010-union-anonima.c
./010-union-anonima

gcc -Wall -Wextra -o 020-array-di-valori-misti 020-array-di-valori-misti.c
./020-array-di-valori-misti

gcc -Wall -Wextra -o 030-accesso-controllato 030-accesso-controllato.c
./030-accesso-controllato

gcc -Wall -Wextra -o 040-problema-impostazioni 040-problema-impostazioni.c
./040-problema-impostazioni

gcc -Wall -Wextra -o 050-problema-comandi-robot 050-problema-comandi-robot.c
./050-problema-comandi-robot

gcc -Wall -Wextra -o 060-problema-token-espressione 060-problema-token-espressione.c
./060-problema-token-espressione

gcc -Wall -Wextra -o 070-problema-registro-eventi 070-problema-registro-eventi.c
./070-problema-registro-eventi

gcc -Wall -Wextra -o 080-problema-calcolatrice-unita 080-problema-calcolatrice-unita.c
./080-problema-calcolatrice-unita
```

---

## Output atteso

### 010-union-anonima
```
a.v.reale = 9.81   (union con nome v)
b.reale   = 9.81   (union anonima)
c.intero  = 42
sizeof(DatoConNome) = 16, sizeof(Dato) = 16: la memoria e' la stessa
&c.intero == &c.reale? si'
```

### 020-array-di-valori-misti
```
interi  2
reali   2
testi   3
Somma dei numeri: 1345.0
Testi: Bassi Rita 4B
```

### 030-accesso-controllato
```
valore  come intero  come reale
  1     12           12.00
  2     7            7.00
  3     no           7.50
  4     no           no
  5     -3           -3.00
```

### 040-problema-impostazioni
*(output dipendente dall'input – file con errori)*
```
File delle impostazioni (FINE per terminare):
# configurazione del registro
porta=8080
timeout=2.5
registro=forse
  riga 4: valore non valido per registro
server=registro.lan
colore=blu
  riga 6: chiave sconosciuta "colore"
porta 99
  riga 7: manca '='

timeout=-1
  riga 9: valore non valido per timeout
FINE

Configurazione:
  porta     = 8080
  timeout   = 2.5 s
  registro  = no
  server    = "registro.lan"
```

### 050-problema-comandi-robot
*(output dipendente dall'input – programma con due righe sbagliate)*
```
Programma del robot (FINE per eseguire):
MUOVI 3 4
RUOTA 90
DI Buongiorno 3B!
RUOTA 45
  riga 4 scartata: "RUOTA 45"
SALTA 2
  riga 5 scartata: "SALTA 2"
MUOVI -1 2
RUOTA -180
FINE

Esecuzione di 5 comandi
  muove di (3, 4): ora in (3, 4)
  ruota di 90 gradi: ora orientato a 90 gradi
  dice: "Buongiorno 3B!"
  muove di (-1, 2): ora in (2, 6)
  ruota di -180 gradi: ora orientato a 270 gradi
Posizione finale (2, 6), orientamento 270 gradi
```

### 060-problema-token-espressione
*(output dipendente dall'input – sei espressioni)*
```
Espressione (FINE): 2 * (3 + 4.5) - 1
  = 14  (9 token)
Espressione (FINE): 1 + 2 * 3
  = 7  (5 token)
Espressione (FINE): (1 + 2) * 3
  = 9  (7 token)
Espressione (FINE): 10 / (5 - 5)
  Espressione non valida.
Espressione (FINE): (2 + 3
  Espressione non valida.
Espressione (FINE): 7 % 2
  Espressione non valida.
Espressione (FINE): FINE
```

### 070-problema-registro-eventi
*(output dipendente dall'input – esempio di sessione)*
```
Comando (T tipo, A, Q): T PORTA
  06:40  porta ingresso     aperta
  18:30  porta palestra     chiusa
  21:10  porta magazzino    aperta
Comando (T tipo, A, Q): T BADGE
  06:42  badge 1047         Ferri (bidello)
  07:55  badge 2210         prof. Galli
  14:05  badge 9999         NON REGISTRATO
Comando (T tipo, A, Q): A
  06:40  porta ingresso     aperta
  13:30  sensore server     31.2 gradi
  14:05  badge 9999         NON REGISTRATO
  21:10  porta magazzino    aperta
  Anomalie: 4
Comando (T tipo, A, Q): T AUTO
  Tipo sconosciuto: PORTA, SENSORE o BADGE.
Comando (T tipo, A, Q): Q
```

### 080-problema-calcolatrice-unita
*(output dipendente dall'input – sette conversioni)*
```
Conversione (valore sigla in sigla, FINE): 12 km in m
  12 km = 12000 m
Conversione (valore sigla in sigla, FINE): 5 lb in kg
  5 lb = 2.26796 kg
Conversione (valore sigla in sigla, FINE): 100 F in C
  100 F = 37.7778 C
Conversione (valore sigla in sigla, FINE): 300 K in C
  300 K = 26.85 C
Conversione (valore sigla in sigla, FINE): 3 m in kg
  Non si converte una lunghezza in una massa.
Conversione (valore sigla in sigla, FINE): 2 mi in km
  2 mi = 3.21869 km
Conversione (valore sigla in sigla, FINE): 4 yd in m
  Unita' sconosciuta: yd
Conversione (valore sigla in sigla, FINE): FINE
```

---

## Errori comuni da evitare

**Compilare una union anonima con uno standard vecchio**
```bash
gcc -std=c89 ...                   # le union anonime sono del C11
gcc -std=c11 ...                   # corretto
```

**Due campi con lo stesso nome nella struct e nella union anonima**
```c
struct { char nome[12]; union { char nome[12]; int n; }; }   /* errore */
```

**Inizializzare due campi della stessa union**
```c
Dato d = {.tipo = REALE, .intero = 3, .reale = 2.5};   /* vale solo l'ultimo */
```

**Leggere il valore di uscita quando la funzione fallisce**
```c
come_intero(&d, &n);
printf("%d", n);                   /* n non è stato scritto */
if (come_intero(&d, &n)) { printf("%d", n); }   /* corretto */
```

**Usare un indice di token senza controllare la fine**
```c
t[*pos].tipo == NUMERO             /* e se *pos == n? */
*pos < n && t[*pos].tipo == NUMERO /* corretto */
```

---

## Concetti collegati

- `02-union-con-etichetta` → etichetta, switch e costruttrici
- `05-enum` → array indicizzati dall'enum
- `03-funzioni` → funzioni che si chiamano a vicenda
- `08-file/02-lettura-e-scrittura-testo` → leggere la configurazione da un file vero

---

## Esercizi proposti

1. In `020-array-di-valori-misti.c` stampa la media dei soli numeri.

2. In `040-problema-impostazioni.c` aggiungi la chiave `lingua` con un
   valore che deve essere `it` o `en`.

3. In `050-problema-comandi-robot.c` aggiungi `MUOVI n`, che avanza di n
   passi nella direzione in cui il robot è orientato.

4. In `070-problema-registro-eventi.c` aggiungi il comando `O hh` con gli
   eventi di quell'ora.

5. (Avanzato) In `060-problema-token-espressione.c` aggiungi il meno
   unario (`-3 + 5`, `-(2 * 4)`) nella funzione `fattore`.
