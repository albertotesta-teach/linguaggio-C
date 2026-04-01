Crea una presentazione didattica in italiano sull'**introduzione al linguaggio C**, destinata a studenti di istituto tecnico e primo anno di università.

La presentazione deve coprire i seguenti argomenti, in questo ordine:

---

**Slide 1 – Titolo**
"Introduzione al linguaggio C" – sottotitolo: "Hello world, variabili e tipi, input/output, operatori"

---

**Slide 2 – Cos'è il linguaggio C**
- Linguaggio compilato, tipizzato staticamente, procedurale
- Creato nei Bell Labs negli anni '70; ancora oggi alla base di sistemi operativi, firmware e linguaggi moderni
- Il ciclo di sviluppo: sorgente `.c` → compilatore (`gcc`) → eseguibile
- Schema visivo del processo:

```
  sorgente         compilatore        eseguibile
 +---------+      +----------+      +----------+
 | hello.c |  →   |   gcc    |  →   |  hello   |
 +---------+      +----------+      +----------+
                       |
               -Wall -Wextra -o
```

- Lo standard C11 è quello usato in questo corso

---

**Slide 3 – Struttura minima di un programma**
Schema con tutte le parti etichettate:

```
 #include <stdio.h>    ← direttiva al preprocessore

 int main(void)        ← punto di inizio obbligatorio
 {                     ← apertura del blocco
     printf("Ciao!\n");← istruzione (termina con ;)
     return 0;         ← valore di ritorno al sistema
 }                     ← chiusura del blocco
```

- Ogni programma ha esattamente una funzione `main`
- `return 0` comunica al sistema operativo che il programma è terminato senza errori
- `#include <stdio.h>` rende disponibili `printf` e `scanf`

---

**Slide 4 – Commenti**
- Due sintassi disponibili dal C99:

```
 /* Commento su più righe:
    inizia con  /*  e termina con  */

 // Commento a riga singola: dalla doppia barra alla fine della riga
```

- Il commento spiega il **perché**, non il **cosa** (il codice lo dice già)
- Esempio di commento utile vs inutile:

```
 // Male:  x = x + 1;   // incrementa x di 1
 // Bene:  x = x + 1;   // prossima posizione libera nell'array
```

- Mantenere i commenti aggiornati: un commento sbagliato è peggio di nessun commento

---

**Slide 5 – Tipi interi**
Schema dimensioni e intervalli (sistema a 64 bit):

```
 Tipo            Byte   Minimo              Massimo
 ─────────────────────────────────────────────────────
 short             2    -32 768             32 767
 int               4    -2 147 483 648      2 147 483 647
 long              8    -9.2 × 10^18        9.2 × 10^18
 long long         8    -9.2 × 10^18        9.2 × 10^18
 unsigned int      4    0                   4 294 967 295
```

- `sizeof(tipo)` restituisce i byte; i limiti sono in `<limits.h>`
- Il suffisso `L` indica un letterale `long`, `U` indica `unsigned`, `LL` indica `long long`
- **Overflow**: superare il massimo "ricomincia" dall'estremo opposto → scegliere sempre il tipo adatto

---

**Slide 6 – Tipi reali**
Schema precisione a confronto su π:

```
 Tipo          Byte   Cifre   π stampato con 20 decimali
 ──────────────────────────────────────────────────────────────
 float           4      6     3.14159274101257324219
 double          8     15     3.14159265358979323846
 long double    16     18     3.14159265358979323851
                              ^^^^^^^^^^^^^^^^
                              cifre affidabili
```

- Notazione scientifica: `1.496e8` = 150 000 000; `9.1e-31` = 0,000…091
- **Non confrontare reali con `==`**: gli errori di arrotondamento possono far risultare diversi due valori matematicamente uguali
- Usare una tolleranza: `differenza < 1e-9` al posto di `==`

---

**Slide 7 – Tipo char e simulazione del booleano**
Schema char come intero:

```
 char lettera = 'A';

 Stampa con %c  →  A         (il carattere)
 Stampa con %d  →  65        (il codice ASCII)

 Aritmetica:  'A' + 1  →  'B'  (codice 66)
              'A' + 2  →  'C'  (codice 67)
```

Sequenze di escape principali:

```
 \n   a capo (10)       \t   tabulazione (9)
 \\   barra rovescia    \'   apice singolo
 \0   carattere null (0)
```

Simulazione del booleano con `int`:

```c
 int maggiorenne = (eta >= 18);   // vale 0 o 1
 int valido = (eta >= 0) && (eta <= 120);
```

---

**Slide 8 – Costanti: #define vs const**

```
 #define PI_GRECO  3.14159   // preprocessore: sostituzione testuale, senza tipo
 const double PI = 3.14159;  // variabile tipizzata, protetta da modifiche
```

Schema a confronto:

```
 Caratteristica      #define              const
 ─────────────────────────────────────────────────
 Tipo                nessuno              sì (double, int, …)
 Visibile debugger   no                   sì
 Uso in #if          sì                   no
 Sintassi errore     a runtime            a compile-time
```

- Convenzione: nomi `#define` in MAIUSCOLO_CON_UNDERSCORE
- `const` è preferito quando il tipo è importante per la correttezza dei calcoli

---

**Slide 9 – printf: specificatori di formato**
Tabella degli specificatori principali:

```
 Spec.   Tipo                  Esempio
 ──────────────────────────────────────────────────
 %d      int                   printf("%d", 42)      → 42
 %u      unsigned int          printf("%u", 300u)    → 300
 %ld     long                  printf("%ld", 1L)     → 1
 %f      double (6 dec.)       printf("%f", 3.14)    → 3.140000
 %lf     double (equivalente)
 %e      notazione scient.     printf("%e", 3.14)    → 3.140000e+00
 %g      automatico            printf("%g", 3.14)    → 3.14
 %c      char                  printf("%c", 'A')     → A
 %%      simbolo %             printf("100%%")       → 100%
```

- Sequenze di escape: `\n` (a capo), `\t` (tab), `\\` (barra), `\"` (virgolette)

---

**Slide 10 – printf: formattazione avanzata**
Sintassi: `%[flag][larghezza][.precisione]tipo`

```
 Formato       Valore    Output        Spiegazione
 ─────────────────────────────────────────────────────────
 %5d           42        [   42]       padding a sinistra
 %-5d          42        [42   ]       allineato a sinistra
 %05d          42        [00042]       zeri iniziali
 %.2f          3.14159   [3.14]        2 cifre decimali
 %10.3f        3.14159   [     3.142]  larghezza 10, 3 decimali
```

Esempio tabella prodotti allineata:

```
 printf("%-4d  %-15s  %8.2f  %6d\n", 1, "Penna", 0.50, 200);
 printf("%-4d  %-15s  %8.2f  %6d\n", 2, "Quaderno", 2.90, 85);

 1     Penna              0.50     200
 2     Quaderno           2.90      85
```

---

**Slide 11 – scanf: lettura da tastiera**
Schema del flusso:

```
 Tastiera  →  buffer stdin  →  scanf  →  variabile in memoria
                                  |
                               &eta  ← operatore indirizzo
                               "dove salvare il valore"
```

Regole fondamentali:

```c
 int    eta;    scanf("%d",  &eta);     // intero
 double peso;   scanf("%lf", &peso);    // double: %lf (non %f!)
 char   sesso;  scanf(" %c", &sesso);   // lo spazio salta il '\n' residuo
```

Errori comuni:

```
 scanf("%d", eta);      // ERRORE: manca &  → comportamento indefinito
 scanf("%f", &peso);    // ERRORE: %f per double in scanf → dati corrotti
 scanf("%c", &sesso);   // RISCHIO: legge il '\n' dell'invio precedente
```

---

**Slide 12 – Operatori aritmetici**
Schema divisione intera vs reale:

```
 Operandi         Operazione    Risultato    Spiegazione
 ──────────────────────────────────────────────────────────
 17   /  5        int / int       3          parte decimale persa!
 17.0 /  5        double / int    3.4        un double basta
 17   /  5.0      int / double    3.4        un double basta
 (double)17 / 5   cast + div      3.4        cast esplicito
```

Operatore modulo `%` (solo interi):

```
 17 % 5  = 2   (17 = 5×3 + 2)
 10 % 2  = 0   → numero pari
 11 % 2  = 1   → numero dispari
 17 % 10 = 7   → ultima cifra
```

Precedenza: `*`, `/`, `%` prima di `+`, `-`; le parentesi forzano l'ordine.

---

**Slide 13 – Operatori relazionali e logici**
Gli operatori relazionali producono **0 (falso) o 1 (vero)**:

```c
 int maggiorenne = (eta >= 18);           // 0 o 1
 int in_range    = (eta >= 18) && (eta <= 65);  // 0 o 1
 int fuori_range = (eta < 0)  || (eta > 120);   // 0 o 1
 int non_valido  = !in_range;                    // 0 o 1
```

Schema valutazione a corto circuito:

```
 &&  →  se il primo è 0 (falso), il secondo NON viene valutato
 ||  →  se il primo è 1 (vero),  il secondo NON viene valutato
```

- Il risultato può essere salvato in una variabile `int` e usato come qualsiasi numero
- Non servono `if/else` per calcolare un valore booleano

---

**Slide 14 – Operatori di assegnazione e incremento**
Operatori composti:

```
 x += 3    equivale a    x = x + 3
 x -= 3    equivale a    x = x - 3
 x *= 2    equivale a    x = x * 2
 x /= 4    equivale a    x = x / 4
 x %= 4    equivale a    x = x % 4
```

Incremento e decremento: differenza prefisso vs postfisso:

```
 a = 5;  b = ++a;   →   a=6, b=6   (prima incrementa, poi assegna)
 a = 5;  b = a++;   →   a=6, b=5   (prima assegna, poi incrementa)
```

Uso tipico come accumulatore:

```c
 somma += valore;    // invece di somma = somma + valore
 totale *= 1.22;     // applica IVA al 22%
```

---

**Slide 15 – Operatore ternario e operatori bit a bit**
Operatore ternario `?:` — espressione che restituisce un valore:

```
 condizione ? valore_se_vero : valore_se_falso

 double prezzo = (fascia == 1) ? 0.28
               : (fascia == 2) ? 0.22
               :                 0.18;
```

Schema operatori bit a bit su `a=60` (0011 1100) e `b=15` (0000 1111):

```
 a & b  →  0000 1100  =  12   (AND: 1 solo se entrambi 1)
 a | b  →  0011 1111  =  63   (OR:  1 se almeno uno 1)
 a ^ b  →  0011 0011  =  51   (XOR: 1 solo se diversi)
 a << 1 →  0111 1000  = 120   (shift sx: ×2)
 a >> 1 →  0001 1110  =  30   (shift dx: ÷2)
```

---

**Slide 16 – Errori comuni da evitare**

```c
 // 1. Divisione intera involontaria
 double r = 7 / 2;          // r = 3.0, non 3.5!
 double r = (double)7 / 2;  // corretto

 // 2. Confondere = con ==
 int x = (eta = 18);    // assegna 18, non confronta!
 int x = (eta == 18);   // corretto: 0 o 1

 // 3. Manca & in scanf
 scanf("%d", eta);       // comportamento indefinito
 scanf("%d", &eta);      // corretto

 // 4. %f per double in scanf
 scanf("%f", &peso);     // sbagliato: peso è double
 scanf("%lf", &peso);    // corretto

 // 5. Confronto tra reali con ==
 if (x == 0.3) { … }    // può non entrare mai
 if (x - 0.3 < 1e-9) { … }  // corretto: tolleranza
```

---

**Slide 17 – Riepilogo concetti**
Tabella riassuntiva:

| Argomento | Concetto chiave | Da ricordare |
|---|---|---|
| Hello world | Struttura minima: include, main, return | Un solo main per programma |
| Tipi interi | short, int, long, unsigned | Scegliere il tipo giusto per l'intervallo |
| Tipi reali | float, double, long double | Non usare == per confrontare reali |
| char | Intero a 8 bit, codice ASCII | %c carattere, %d codice numerico |
| Costanti | #define (testo) vs const (tipizzato) | MAIUSCOLO per i nomi #define |
| printf | Specificatori + opzioni larghezza/precisione | %lf in scanf, %f o %lf in printf |
| scanf | & obbligatorio, spazio prima di %c | %lf per double, non %f |
| Aritmetici | / tra int tronca; % solo per interi | Cast (double) per divisione reale |
| Relaz./logici | Risultato sempre 0 o 1 (int) | && e \|\| con corto circuito |
| Assegnazione | += -= *= /= %=; ++/-- pre e post | Prefisso incrementa prima |
| Ternario | condizione ? vero : falso | Espressione, non istruzione |
| Bit a bit | & \| ^ ~ << >> | << ×2; >> ÷2 |

---

**Slide 18 – Esempi: 01 – Hello world (concetti base)**

`010-hello-world.c`
- Problema: scrivere il programma più semplice possibile in C e verificare che l'ambiente funzioni
- Aspetti tecnici: struttura minima con `#include <stdio.h>`, `int main(void)`, una `printf` con `\n`, `return 0`; nessuna variabile dichiarata

`020-struttura-programma.c`
- Problema: mostrare tutte le parti di un programma C con etichette e commenti esplicativi
- Aspetti tecnici: direttive `#include` e `#define`; dichiarazione di variabili `int` e `double`; assegnazione; `printf` con `%d` e `%.2f`; commenti `/* */` su ogni sezione

`030-commenti.c`
- Problema: illustrare le due sintassi di commento e le buone pratiche di documentazione
- Aspetti tecnici: commento `/* */` multi-riga; commento `//` a singola riga; esempio di commento utile (spiega il perché) vs inutile (ripete il cosa); dimostrazione che un commento sbagliato è peggio di nessun commento

---

**Slide 19 – Esempi: 01 – Hello world (problemi)**

`040-problema-saluto-personalizzato.c`
- Problema: chiedere all'utente giorno, mese, anno di nascita e anno corrente; calcolare l'età e stampare un saluto con riepilogo formattato
- Aspetti tecnici: quattro variabili `int`; `scanf("%d", &var)` per ogni dato; calcolo `eta = anno_corrente - anno_nascita`; formattazione data con `%02d`; nessun array, nessuna stringa

`050-problema-biglietto-da-visita.c`
- Problema: chiedere dati numerici (prefisso e numero di telefono, anno di fondazione, numero civico, CAP) e stamparli dentro un biglietto da visita con bordo ASCII
- Aspetti tecnici: testo fisso nelle `printf` per nome, ruolo e città (nessuna stringa in input); `%03d` per il prefisso; `%06d` per il codice; costante `#define LARGHEZZA` per documentare la dimensione del bordo

`060-problema-intestazione-documento.c`
- Problema: chiedere anno scolastico, classe, sezione, numero documento e data; calcolare l'anno finale del biennio e produrre un'intestazione scolastica formattata
- Aspetti tecnici: `anno_fine = anno_inizio + 1` (calcolato, non inserito); `%03d` per il numero documento con zeri iniziali; `%02d` per giorno e mese; sezione rappresentata come intero (le stringhe non sono ancora disponibili)

---

**Slide 20 – Esempi: 02 – Variabili e tipi (concetti base)**

`010-tipi-interi.c`
- Problema: mostrare le dimensioni, i limiti e i valori delle principali variabili intere
- Aspetti tecnici: `sizeof(tipo)` con `%zu`; costanti di `<limits.h>` (`INT_MAX`, `SHRT_MIN`, ecc.); suffissi `L`, `U`, `LL`; comportamento dell'overflow mostrato nei commenti

`020-tipi-reali.c`
- Problema: confrontare la precisione di float, double e long double su un caso concreto
- Aspetti tecnici: `FLT_DIG`, `DBL_DIG` da `<float.h>`; stampa con `%.20f` per vedere le cifre non affidabili; notazione scientifica con `1.496e8`; dimostrazione del pericolo di `==` tra reali

`030-caratteri-e-booleani.c`
- Problema: mostrare che `char` è un intero e come si simula il booleano senza `<stdbool.h>`
- Aspetti tecnici: stampa con `%c` e `%d` sullo stesso `char`; aritmetica `'A' + 1` → `'B'`; sequenze di escape; espressione `(eta >= 18)` assegnata a `int maggiorenne`

`040-costanti.c`
- Problema: confrontare `#define` e `const` in esempi pratici e spiegare quando usare l'uno o l'altro
- Aspetti tecnici: costanti matematiche (`PI_GRECO`, `GRAVITA`) e applicative (`ETA_MINIMA`, `IVA`); `const double` per la velocità della luce; tentativo di modifica mostrato nei commenti come errore di compilazione

---

**Slide 21 – Esempi: 02 – Variabili e tipi (problemi)**

`050-problema-conversione-temperature.c`
- Problema: leggere una temperatura in Celsius e stamparla convertita in Fahrenheit e Kelvin
- Aspetti tecnici: costanti `#define FATTORE_F (9.0/5.0)` e `OFFSET_K 273.15`; divisione `9.0/5.0` (reale) non `9/5` (intera); `%lf` in `scanf` e `%.2f` in `printf`; riga bonus con i due valori di riferimento (0°C e 100°C)

`060-problema-calcolo-area.c`
- Problema: scegliere una figura (1=quadrato, 2=rettangolo, 3=cerchio) e calcolarne area e perimetro
- Aspetti tecnici: `if/else if` per la selezione (switch non ancora disponibile); costante `PI_GRECO` con `#define`; `scanf("%lf", &raggio)` per i reali; `return 1` in caso di scelta non valida

`070-problema-scheda-prodotto.c`
- Problema: inserire codice prodotto, prezzo, quantità e percentuale di sconto; calcolare prezzo scontato e valore totale di magazzino
- Aspetti tecnici: tipi misti `int` e `double` nella stessa scheda; `fattore_sconto = sconto_percento / 100.0`; cast `(double)quantita` prima della moltiplicazione con il prezzo; `%06d` per il codice con zeri iniziali

---

**Slide 22 – Esempi: 03 – Input e output (concetti base)**

`010-printf-basi.c`
- Problema: mostrare sistematicamente tutti i principali specificatori di formato con esempi concreti
- Aspetti tecnici: `%d`, `%u`, `%ld`, `%f`, `%e`, `%c`, `%%`; sequenze `\n`, `\t`, `\\`, `\"`; più valori nella stessa `printf` con ordine degli argomenti corrispondente agli specificatori

`020-scanf-basi.c`
- Problema: leggere variabili di tipo diverso dalla tastiera e riepilogarle
- Aspetti tecnici: `&` come "indirizzo dove salvare il valore" (teoria dei puntatori rimandata al cap. 05); `%lf` obbligatorio per `double` in `scanf`; spazio prima di `" %c"` per saltare il `'\n'` residuo; errori comuni mostrati in commento

`030-formattazione-avanzata.c`
- Problema: costruire output tabellare allineato usando le opzioni di formato di `printf`
- Aspetti tecnici: `%5d` padding, `%-5d` allineamento sinistro, `%05d` zeri, `%.2f` precisione, `%10.3f` combinazione; tabella prodotti con quattro colonne allineate; `%e` e `%g` per la notazione scientifica

---

**Slide 23 – Esempi: 03 – Input e output (problemi)**

`040-problema-scheda-studente.c`
- Problema: inserire matricola, anno di corso, tre voti e voto di laurea; calcolare la media e stampare una scheda formattata
- Aspetti tecnici: `%07d` per la matricola con zeri iniziali; media con `(voto1 + voto2 + voto3) / 3.0` (divisione reale); `scanf` con tipi misti (`int` e `double`); `printf` con larghezze di campo per allineare le colonne

`050-problema-scontrino.c`
- Problema: inserire prezzo e quantità di tre articoli; calcolare subtotali, totale imponibile, IVA al 22% e totale ivato; stampare uno scontrino con bordo ASCII
- Aspetti tecnici: `cast (double)quantita` nella moltiplicazione; `#define IVA 0.22`; scontrino con bordo `+---+` e colonne allineate con `%-18s`, `%4d`, `%8.2f`

`060-problema-dati-veicolo.c`
- Problema: inserire dati di un veicolo e stampare una scheda tecnica con anzianità e conversione potenza kW→CV
- Aspetti tecnici: `#define ANNO_CORRENTE 2024` e `#define KW_IN_CV 1.35962`; `anzianita = ANNO_CORRENTE - anno_immatricolazione` (differenza tra interi); `potenza_cv = potenza_kw * KW_IN_CV`; scheda con separatori `--` e colonne `%8.1f`

---

**Slide 24 – Esempi: 04 – Operatori (concetti base)**

`010-operatori-aritmetici.c`
- Problema: mostrare il comportamento di tutti gli operatori aritmetici, con enfasi sulla divisione intera
- Aspetti tecnici: confronto diretto `17/5=3` vs `17.0/5=3.4`; cast esplicito `(double)a/b`; modulo `%` con applicazioni pratiche (parità, ultima cifra); precedenza `*` prima di `+` con e senza parentesi

`020-operatori-relazionali-e-logici.c`
- Problema: dimostrare che gli operatori relazionali e logici producono valori interi 0/1 salvabili in variabili
- Aspetti tecnici: `int maggiorenne = (eta >= 18)`; condizioni composte con `&&` e `||`; operatore `!`; valutazione a corto circuito spiegata nei commenti; nessun `if/else`

`030-operatori-di-assegnazione.c`
- Problema: confrontare le forme compatte di assegnazione con quelle estese e mostrare la differenza tra prefisso e postfisso
- Aspetti tecnici: `+=`, `-=`, `*=`, `/=`, `%=` applicati in sequenza a partire da 10; `b = ++a` vs `b = a++` con due variabili per evidenziare la differenza; pericolo del doppio incremento nella stessa espressione mostrato nei commenti

`040-operatori-bit-a-bit.c`
- Problema: visualizzare l'effetto di ogni operatore bit a bit con rappresentazione binaria nei commenti
- Aspetti tecnici: valori `a=60` (0011 1100) e `b=15` (0000 1111); schema binario affiancato per `&`, `|`, `^`; shift come moltiplicazione e divisione per 2; test/set/clear di un bit con maschera `1u << 2`

---

**Slide 25 – Esempi: 04 – Operatori (problemi)**

`050-problema-calcolo-bolletta.c`
- Problema: calcolare la bolletta elettrica da letture del contatore, potenza impegnata e fascia oraria
- Aspetti tecnici: selezione del prezzo per fascia con operatore ternario annidato `(fascia==1) ? PREZZO_F1 : (fascia==2) ? PREZZO_F2 : PREZZO_F3`; calcolo `kwh_consumati = lettura_attuale - lettura_precedente`; IVA domestica al 10% con `#define`; zero `if/else`

`060-problema-indice-massa-corporea.c`
- Problema: calcolare l'IMC e determinare la categoria (sottopeso/normopeso/sovrappeso/obesità)
- Aspetti tecnici: `imc = peso / (altezza * altezza)`; quattro flag `int sottopeso = (imc < 18.5)` ecc. con operatori relazionali e logici; stampa dei flag come 0/1 per mostrare il concetto; categoria stampata con operatore ternario annidato su `%s`; zero `if/else`

`070-problema-cambio-valuta.c`
- Problema: convertire un importo in EUR nella valuta scelta (USD, GBP, JPY, CHF) sottraendo la commissione
- Aspetti tecnici: tasso selezionato con ternario annidato su `scelta`; `importo_commissione *= COMMISSIONE` per calcolare la commissione con assegnazione composta; simbolo valuta selezionato con secondo ternario in `printf`; zero `if/else`

---

**Istruzioni di stile – applicare in modo rigoroso su ogni slide:**
Usa il tema "Modello T". Titoli in Verdana grassetto 30pt, corpo in Verdana normale 18pt. Tutto il testo allineato a sinistra. Nessun altro font, variante o allineamento diverso. Impostazioni costanti su tutte le slide. Non inserire immagini decorative o di sfondo. Usa immagini, grafici o schemi solo se direttamente pertinenti al contenuto della slide e funzionali alla comprensione.
