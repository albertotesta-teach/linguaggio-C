# 01 – Alias di tipi base

## Concetto

`typedef` dà un **nuovo nome** a un tipo che esiste già:

```c
typedef int Voto;
typedef double Euro;

Voto verifica = 7;          /* come int verifica = 7; */
Euro pranzo = 4.80;         /* come double pranzo = 4.80; */
```

La regola della sintassi: si scrive la dichiarazione di una variabile
(`double Euro;`) e si mette `typedef` davanti. Il nome che sarebbe stato la
variabile diventa il nome del tipo. Nel corso i nomi dei tipi hanno
l'**iniziale maiuscola**; le variabili restano in minuscolo.

### Perché usarlo

| Senza typedef | Con typedef |
|---------------|-------------|
| `double media(const double *v, int n);` | `Gradi media(const Gradi *v, int n);` |
| il prototipo dice come è fatto il dato | il prototipo dice che cosa rappresenta |
| per passare da `float` a `double` si cerca ogni `float` | si cambia la sola riga della `typedef` |

### Un nome nuovo, non un tipo nuovo

`Voto`, `Euro` e i tipi originali sono **lo stesso tipo**: il compilatore
accetta di mescolarli senza errori né avvisi.

```c
typedef double Euro;
typedef double Chilometri;

Euro costo_carburante(Chilometri distanza, KmPerLitro consumo, Euro prezzo);

costo_carburante(consumo, distanza, prezzo);   /* argomenti scambiati: nessun errore */
```

Un tipo che il compilatore distingue davvero dagli altri si costruisce con
`struct` (sottocapitolo `02-struct`): lì `typedef` servirà a dargli un nome.

### Che cosa typedef non cambia

- la dimensione: `sizeof(Voto) == sizeof(int)`;
- gli operatori e le conversioni del tipo originale;
- i formati di `printf` e `scanf`: un `Voto` definito come `double` si
  legge con `%lf`.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-nome-a-un-tipo.c` | `Voto`, `Euro`, `Minuti`: dichiarazione, uso e `sizeof` |
| `020-cambiare-tipo-in-un-punto.c` | `typedef float Misura;` e l'errore di arrotondamento che sparisce con `double` |
| `030-alias-non-tipo-nuovo.c` | Parametri scambiati e assegnamenti tra "tipi" diversi accettati dal compilatore |
| `040-problema-registro-temperature.c` | Temperature minime e massime della serra con il tipo `Gradi` |
| `040-problema-registro-temperature-analisi.md` | Analisi di `040-problema-registro-temperature.c` |
| `050-problema-scontrino-mensa.c` | Scontrino della mensa con `Euro` e `Quantita` |
| `050-problema-scontrino-mensa-analisi.md` | Analisi di `050-problema-scontrino-mensa.c` |
| `060-problema-consumo-acqua.c` | Letture del contatore in `MetriCubi`, consumi in `Litri` |
| `060-problema-consumo-acqua-analisi.md` | Analisi di `060-problema-consumo-acqua.c` |
| `070-problema-cronometro.c` | Tempi di una gara di nuoto in `Decimi` di secondo |
| `070-problema-cronometro-analisi.md` | Analisi di `070-problema-cronometro.c` |
| `080-problema-media-pesata.c` | Media pesata con `Voto` e `Peso` |
| `080-problema-media-pesata-analisi.md` | Analisi di `080-problema-media-pesata.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-nome-a-un-tipo 010-nome-a-un-tipo.c
./010-nome-a-un-tipo

gcc -Wall -Wextra -o 020-cambiare-tipo-in-un-punto 020-cambiare-tipo-in-un-punto.c
./020-cambiare-tipo-in-un-punto

gcc -Wall -Wextra -o 030-alias-non-tipo-nuovo 030-alias-non-tipo-nuovo.c
./030-alias-non-tipo-nuovo

gcc -Wall -Wextra -o 040-problema-registro-temperature 040-problema-registro-temperature.c
./040-problema-registro-temperature

gcc -Wall -Wextra -o 050-problema-scontrino-mensa 050-problema-scontrino-mensa.c
./050-problema-scontrino-mensa

gcc -Wall -Wextra -o 060-problema-consumo-acqua 060-problema-consumo-acqua.c
./060-problema-consumo-acqua

gcc -Wall -Wextra -o 070-problema-cronometro 070-problema-cronometro.c
./070-problema-cronometro

gcc -Wall -Wextra -o 080-problema-media-pesata 080-problema-media-pesata.c
./080-problema-media-pesata
```

---

## Output atteso

### 010-nome-a-un-tipo
```
=== LA GIORNATA ===
  Voto della verifica:  7
  Spesa del giorno:     6.00 euro
  Studio a casa:        115 minuti (1 h 55 min)

=== DIMENSIONI ===
  sizeof(Voto)   = 4   sizeof(int)    = 4
  sizeof(Euro)   = 8   sizeof(double) = 8
  sizeof(Minuti) = 4   sizeof(int)    = 4
```

### 020-cambiare-tipo-in-un-punto
```
Tipo Misura: 4 byte (float)
Letture: 1000, massima 3.1 mm in 10 minuti
Totale calcolato:  106.999054 mm
Totale esatto:     107.000000 mm
```

### 030-alias-non-tipo-nuovo
```
Gita a Genova: 290 km, 3.5 km/l, gasolio a 1.79 euro/l

Costo corretto:              148.31 euro
Parametri scambiati:           0.02 euro   <- nessun errore di compilazione
Euro stranezza = km:         290.00 euro   <- accettato

Euro e Chilometri sono due nomi dello stesso tipo double.
```

### 040-problema-registro-temperature
```
  Giorno      Minima  Massima  Escursione
  lunedi        3.5     12.0         8.5
  martedi       1.2     14.5        13.3   rischio gelo
  mercoledi    -0.8     11.2        12.0   rischio gelo
  giovedi       2.4      9.8         7.4
  venerdi       4.1     13.3         9.2
  sabato        5.0     15.7        10.7
  domenica      1.6     16.4        14.8   rischio gelo

Media delle minime:  2.43 gradi
Media delle massime: 13.27 gradi
Escursione piu' ampia: domenica (14.8 gradi)
Giorni con rischio di gelo: 3
```

### 050-problema-scontrino-mensa
*(output dipendente dall'input – esempio di sessione)*
```
Listino:
  1  Primo piatto     3.20
  2  Secondo piatto   3.90
  3  Contorno         1.50
  4  Frutta           0.80
  5  Acqua 0.5 l      0.50
  6  Yogurt           1.10
Codice prodotto (0 per chiudere): 1
Quantita': 1
   1 x Primo piatto      3.20
Codice prodotto (0 per chiudere): 2
Quantita': 1
   1 x Secondo piatto    3.90
Codice prodotto (0 per chiudere): 5
Quantita': 2
   2 x Acqua 0.5 l       1.00
Codice prodotto (0 per chiudere): 9
  Codice inesistente.
Codice prodotto (0 per chiudere): 4
Quantita': 0
  Quantita' non valida, prodotto non aggiunto.
Codice prodotto (0 per chiudere): 6
Quantita': 3
   3 x Yogurt            3.30
Codice prodotto (0 per chiudere): 0
Tessera studenti? (S/N): S

  Totale             11.40
  Sconto 10%         -1.14
  Da pagare          10.26 euro
```

### 060-problema-consumo-acqua
```
  Mese       Consumo m3   Litri   Litri/persona/giorno
  gennaio         10.7    10700           115
  febbraio         9.6     9600           114
  marzo           10.9    10900           117
  aprile          10.3    10300           114
  maggio          12.3    12300           132
  giugno          14.6    14600           162   oltre soglia

Consumo totale del semestre: 68.4 m3 (68400 litri)
Mese con il consumo piu' alto: giugno (14.6 m3)
Mesi oltre 150 litri per persona al giorno: 1
```

### 070-problema-cronometro
*(output dipendente dall'input – esempio di sessione)*
```
Tempo di Bianchi  (minuti secondi decimi): 1 5 3
Tempo di Esposito (minuti secondi decimi): 1 2 8
Tempo di Ferrari  (minuti secondi decimi): 0 59 9
Tempo di Russo    (minuti secondi decimi): 1 70 2
  Tempo non valido, ripetere.
Tempo di Russo    (minuti secondi decimi): 1 1 4
Tempo di Colombo  (minuti secondi decimi): 1 3 0

Vincitore: Ferrari con 0'59"9

  Atleta     Tempo     Distacco
  Bianchi   1'05"3    +0'05"4
  Esposito  1'02"8    +0'02"9
  Ferrari   0'59"9    +0'00"0
  Russo     1'01"4    +0'01"5
  Colombo   1'03"0    +0'03"1
```

### 080-problema-media-pesata
*(output dipendente dall'input – esempio di sessione)*
```
Voto e peso (0 0 per finire): 7 100
Voto e peso (0 0 per finire): 5.5 50
Voto e peso (0 0 per finire): 8 25
Voto e peso (0 0 per finire): 11 50
  Coppia non valida, scartata.
Voto e peso (0 0 per finire): 9 25
Voto e peso (0 0 per finire): 0 0

Voti inseriti: 4
Media semplice: 7.38
Media pesata:   7.00  -> sufficiente
```

---

## Errori comuni da evitare

**Invertire l'ordine nella typedef**
```c
typedef Voto int;      /* errore: prima il tipo esistente, poi il nuovo nome */
typedef int Voto;      /* corretto */
```

**Credere che il compilatore controlli le "unità"**
```c
Euro prezzo = distanza;    /* accettato: Euro e Chilometri sono entrambi double */
```

**Dimenticare il formato del tipo originale in scanf**
```c
typedef double Voto;
scanf("%f", &voto);        /* sbagliato: Voto è un double */
scanf("%lf", &voto);       /* corretto */
```

**Cambiare il tipo nella typedef senza controllare gli scanf**
```c
typedef float Misura;      /* scanf("%f", ...) */
typedef double Misura;     /* ora serve scanf("%lf", ...) */
```

**Usare il nome del tipo come nome di variabile**
```c
Voto Voto = 7;             /* confonde chi legge: il tipo è Voto, la variabile voto */
Voto voto = 7;             /* corretto */
```

---

## Concetti collegati

- `01-introduzione/02-variabili-e-tipi` → i tipi base a cui typedef dà un nome
- `02-typedef-di-array` → un nome per un tipo array
- `03-typedef-di-puntatori-a-funzione` → un nome per un puntatore a funzione
- `02-struct` → un tipo davvero nuovo, con il nome dato da typedef

---

## Esercizi proposti

1. In `020-cambiare-tipo-in-un-punto.c` cambia la typedef in `double` e
   confronta il totale calcolato con quello esatto.

2. In `040-problema-registro-temperature.c` aggiungi il tipo `Fahrenheit`
   e una funzione `Fahrenheit in_fahrenheit(Gradi g)` per stampare anche la
   media in gradi Fahrenheit.

3. In `050-problema-scontrino-mensa.c` aggiungi un limite di 5 pezzi per
   prodotto, scritto come costante di tipo `Quantita`.

4. In `070-problema-cronometro.c` stampa anche la media dei tempi in
   `Decimi`, arrotondata al decimo.

5. (Avanzato) In `030-alias-non-tipo-nuovo.c` trova un modo, senza struct,
   per rendere più difficile scambiare gli argomenti (suggerimento: l'ordine
   e i nomi dei parametri, i commenti nel prototipo). Perché nessuna
   soluzione è davvero sicura?
