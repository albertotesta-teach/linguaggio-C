# 03 – Input e output

## Concetto

In C l'input e l'output da console si gestiscono con due funzioni
della libreria standard `<stdio.h>`:

- `printf` — stampa dati formattati sullo schermo (standard output)
- `scanf`  — legge dati formattati dalla tastiera (standard input)

Entrambe usano una **stringa di formato** con specificatori che iniziano
con `%`, seguiti da un carattere che indica il tipo di dato:

```
┌──────────┬──────────────────────────────────────────────┐
│ Specif.  │ Significato                                  │
├──────────┼──────────────────────────────────────────────┤
│ %d       │ intero con segno (int)                       │
│ %u       │ intero senza segno (unsigned int)            │
│ %ld      │ long int                                     │
│ %lld     │ long long int                                │
│ %f       │ double in printf / float in scanf            │
│ %lf      │ double in scanf (e in printf, equivalente)   │
│ %e       │ notazione scientifica                        │
│ %g       │ automatico: decimale o scientifico           │
│ %c       │ singolo carattere (char)                     │
│ %%       │ simbolo % letterale                          │
└──────────┴──────────────────────────────────────────────┘
```

Le opzioni di formato di `printf` seguono la sintassi:
```
%[flag][larghezza][.precisione]tipo
```
Esempi: `%8d`, `%-8d`, `%08d`, `%.2f`, `%10.3f`.

In `scanf` ogni variabile deve essere preceduta da `&` (operatore indirizzo):
```c
scanf("%d", &eta);     /* corretto: passa l'indirizzo di eta */
scanf("%d", eta);      /* errato: comportamento indefinito   */
```

---

## File dell'esempio

| File | Tipo | Descrizione |
|------|------|-------------|
| `010-printf-basi.c` | concetto base | Specificatori principali, sequenze di escape, più valori |
| `020-scanf-basi.c` | concetto base | Lettura tipi diversi, operatore &, problema del char residuo |
| `030-formattazione-avanzata.c` | concetto base | Larghezza, allineamento, zeri, precisione, tabelle |
| `040-problema-scheda-studente.c` | problema specifico | Dati studente, media voti, scheda formattata |
| `040-problema-scheda-studente-analisi.md` | analisi | Analisi del problema scheda studente |
| `050-problema-scontrino.c` | problema specifico | Tre articoli, subtotali, IVA, scontrino ASCII |
| `050-problema-scontrino-analisi.md` | analisi | Analisi del problema scontrino |
| `060-problema-dati-veicolo.c` | problema specifico | Dati veicolo, anzianità, conversione kW→CV, scheda tecnica |
| `060-problema-dati-veicolo-analisi.md` | analisi | Analisi del problema dati veicolo |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-printf-basi           010-printf-basi.c
gcc -Wall -Wextra -o 020-scanf-basi            020-scanf-basi.c
gcc -Wall -Wextra -o 030-formattazione-avanzata 030-formattazione-avanzata.c
gcc -Wall -Wextra -o 040-problema-scheda-studente 040-problema-scheda-studente.c
gcc -Wall -Wextra -o 050-problema-scontrino    050-problema-scontrino.c
gcc -Wall -Wextra -o 060-problema-dati-veicolo 060-problema-dati-veicolo.c
```

---

## Output atteso

### 010-printf-basi
```
=== Specificatori di formato ===
Intero con segno:     42
Intero negativo:      -7
Intero senza segno:   300
Long:                 1234567890
Double (default):     36.600000
Double (scientific):  3.660000e+01
Carattere:            M
Percentuale:          100%

=== Sequenze di escape ===
A capo:        riga 1
              riga 2
Tabulazione:   col1	col2	col3
Virgolette:    "testo tra virgolette"
Barra rovescia: C:\Users\nome

=== Più valori in una printf ===
Contatore=42, temperatura=36.6, iniziale=M
Il valore di contatore e': 42 (decimale)
```

### 020-scanf-basi
Input di esempio: 25  1.80  72.5  M  1999
```
Eta' (anni): 25
Altezza (es. 1.75): 1.80
Peso in kg (es. 70.5): 72.5
Sesso (M/F): M
Anno di nascita: 1999

--- Dati inseriti ---
Eta':            25 anni
Altezza:         1.80 m
Peso:            72.5 kg
Sesso:           M
Anno di nascita: 1999
```

### 030-formattazione-avanzata
```
=== Larghezza minima ===
[   42]
[   -7]
[12345]
[123456]

=== Allineamento a sinistra (flag -) ===
[42   ]
[12345]

=== Zeri iniziali (flag 0) ===
[00042]
[001234]

=== Precisione decimale ===
[      3.14]
[    3.1416]
[3.14      ]
[3]

=== Esempio: tabella prodotti ===
Cod   Prodotto          Prezzo   Qta'
----  ---------------  --------  ------
1     Penna                0.50     200
2     Quaderno             2.90      85
12    Zaino               34.99      12

=== Notazione scientifica ===
%e (scientifica): 1.234568e+05
%g (automatica):  123457
%g (piccolo):     0.000123
%g (grande):      1.23e+10
```

### 040-problema-scheda-studente
Input: 12345  2  28  30  27  105.5
```
============================================
  SCHEDA STUDENTE
============================================
  Matricola:      0012345
  Anno di corso:  2° anno
--------------------------------------------
  Voto esame 1:    28 / 30
  Voto esame 2:    30 / 30
  Voto esame 3:    27 / 30
  Media:           28.33 / 30
--------------------------------------------
  Voto di laurea:  105.5 / 110
============================================
```

### 050-problema-scontrino
Input: 1.50 3  4.90 2  0.80 5
```
+-------------------------------------+
|        SCONTRINO FISCALE            |
+-------------------------------------+
| Articolo           Qta'   Importo   |
+-------------------------------------+
| Articolo 1            3      4.50   |
| Articolo 2            2      9.80   |
| Articolo 3            5      4.00   |
+-------------------------------------+
| Totale imponibile           18.30   |
| IVA 22%                      4.03   |
+-------------------------------------+
| TOTALE                      22.33   |
+-------------------------------------+
```

### 060-problema-dati-veicolo
Input: 2022  1200  66.0  5  18500.00
```
==========================================
  SCHEDA TECNICA VEICOLO
==========================================
  Anno immatricolazione: 2022
  Anzianita':            2 anni
------------------------------------------
  Cilindrata:        1200 cc
  Potenza:             66.0 kW
  Potenza:             89.7 CV
  Porte:                  5
------------------------------------------
  Prezzo listino:  18500.00 EUR
==========================================
```

---

## Errori comuni da evitare

```c
/* ERRORE 1: dimenticare & in scanf */
int eta;
scanf("%d", eta);    /* comportamento indefinito */
scanf("%d", &eta);   /* corretto */

/* ERRORE 2: usare %f per double in scanf */
double altezza;
scanf("%f", &altezza);    /* legge un float, non un double: dati corrotti */
scanf("%lf", &altezza);   /* corretto */

/* ERRORE 3: non gestire il '\n' residuo prima di %c */
int n;
char c;
scanf("%d", &n);
scanf("%c", &c);     /* legge '\n', non il carattere voluto */
scanf(" %c", &c);    /* corretto: lo spazio salta i caratteri bianchi */

/* ERRORE 4: confondere larghezza e precisione */
printf("%2.5d\n", 42);    /* larghezza 2, precisione 5 per un intero: confuso */
printf("%8.2f\n", 3.14);  /* corretto: larghezza 8, 2 decimali */

/* ERRORE 5: dimenticare %% per stampare il simbolo % */
printf("Sconto: 10%\n");    /* produce un warning o output imprevisto */
printf("Sconto: 10%%\n");   /* corretto */
```

---

## Concetti collegati

- [`01-hello-world`](../01-hello-world/) — primo uso di printf
- [`02-variabili-e-tipi`](../02-variabili-e-tipi/) — tipi di dato usati con printf e scanf

---

## Esercizi proposti

1. **Tabella di moltiplicazione**: scrivi un programma che chieda un intero
   `n` (1–9) e stampi i primi 5 multipli di `n` in una tabella allineata
   con colonne di larghezza fissa usando `%5d`.

2. **Convertitore di valuta**: chiedi un importo in EUR e un tasso di cambio,
   poi stampa l'equivalente in USD, GBP e JPY su righe allineate con
   etichette a larghezza fissa e due cifre decimali.

3. **Dati personali**: chiedi nome (come intero: 1=Mario, 2=Laura, 3=altro),
   età, altezza e peso. Calcola l'IMC e stampa una scheda allineata simile
   a `040-problema-scheda-studente.c`.

4. **Scontrino esteso**: modifica `050-problema-scontrino.c` aggiungendo
   un quarto articolo e una riga "CONTANTI" in cui l'utente inserisce
   il denaro consegnato; stampa il resto.

5. **Scheda carburante**: chiedi litri erogati, prezzo al litro e km percorsi.
   Calcola il costo totale e il consumo in l/100km. Stampa una ricevuta
   formattata con tutti i valori allineati.
