# 01 – Hello World

## Concetto

Il primo programma in C è il punto di partenza per capire la struttura
minima di un sorgente: direttive al preprocessore, funzione `main`,
istruzioni e valore di ritorno.

```
┌─────────────────────────────────────────────┐
│  #include <stdio.h>   ← direttiva           │
│                                             │
│  int main(void)       ← punto di inizio     │
│  {                                          │
│      printf("...\n"); ← istruzione          │
│      return 0;        ← fine senza errori   │
│  }                                          │
└─────────────────────────────────────────────┘
```

Ogni programma C deve avere **esattamente una funzione `main`**.
L'esecuzione inizia sempre da lì e termina quando `main` restituisce
un valore intero al sistema operativo (0 = nessun errore).

---

## File dell'esempio

| File | Tipo | Descrizione |
|------|------|-------------|
| `010-hello-world.c` | concetto base | Struttura minima: include, main, printf, return |
| `020-struttura-programma.c` | concetto base | Anatomia completa: direttive, costanti, variabili, output |
| `030-commenti.c` | concetto base | Sintassi `/* */` e `//`, buone pratiche di documentazione |
| `040-problema-saluto-personalizzato.c` | problema specifico | Calcolo età da data di nascita, output formattato |
| `040-problema-saluto-personalizzato-analisi.md` | analisi | Analisi del problema saluto personalizzato |
| `050-problema-biglietto-da-visita.c` | problema specifico | Biglietto da visita testuale con bordo ASCII |
| `050-problema-biglietto-da-visita-analisi.md` | analisi | Analisi del problema biglietto da visita |
| `060-problema-intestazione-documento.c` | problema specifico | Intestazione documento scolastico formattata |
| `060-problema-intestazione-documento-analisi.md` | analisi | Analisi del problema intestazione documento |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-hello-world          010-hello-world.c
gcc -Wall -Wextra -o 020-struttura-programma  020-struttura-programma.c
gcc -Wall -Wextra -o 030-commenti             030-commenti.c
gcc -Wall -Wextra -o 040-problema-saluto      040-problema-saluto-personalizzato.c
gcc -Wall -Wextra -o 050-problema-biglietto   050-problema-biglietto-da-visita.c
gcc -Wall -Wextra -o 060-problema-intestazione 060-problema-intestazione-documento.c
```

---

## Output atteso

### 010-hello-world
```
Ciao, mondo!
```

### 020-struttura-programma
```
Programma di esempio - versione 1 (2024)
Eta':     18 anni
Altezza:  1.75 m
```

### 030-commenti
```
Il valore e': 42
```

### 040-problema-saluto-personalizzato
Input di esempio: 15 6 1990 2024
```
=== Saluto personalizzato ===

Giorno di nascita (1-31): 15
Mese di nascita  (1-12): 6
Anno di nascita:         1990
Anno corrente:           2024

--- Riepilogo ---
Data di nascita: 15/06/1990
Anno corrente:   2024
Eta' stimata:    34 anni

Benvenuto! Hai circa 34 anni.
```

### 050-problema-biglietto-da-visita
Input di esempio: 2 1234567 1985 10 20121
```
=== Creazione biglietto da visita ===

+--------------------------------------+
|                                      |
|   MARIO ROSSI                        |
|   Sviluppatore Software              |
|                                      |
|   ACME S.r.l.  (dal 1985)          |
|   Via Roma, 10                      |
|   20121  Milano                     |
|                                      |
|   Tel: 002 / 1234567          |
|                                      |
+--------------------------------------+
```

### 060-problema-intestazione-documento
Input di esempio: 2024 3 1 1 15 10 2024
```
=== Generazione intestazione documento ===

====================================================
  ISTITUTO TECNICO INDUSTRIALE "G. MARCONI"
====================================================
  Anno scolastico: 2024 / 2025
  Classe:          3^  Sezione: 1
  Materia:         Informatica e Sistemi
  Documento n.:    001
  Data:            15 / 10 / 2024
====================================================
  Verifica scritta - Primo quadrimestre
====================================================
```

---

## Errori comuni da evitare

```c
/* ERRORE 1: dimenticare \n alla fine di printf */
printf("Ciao");          /* il cursore resta sulla stessa riga */
printf("Ciao\n");        /* corretto: va a capo dopo la stampa */

/* ERRORE 2: dimenticare il punto e virgola */
printf("Ciao\n")         /* errore di compilazione */
printf("Ciao\n");        /* corretto */

/* ERRORE 3: omettere #include <stdio.h> */
/* senza l'include, printf non è dichiarata e il compilatore segnala errore */

/* ERRORE 4: scrivere Main invece di main (C è case-sensitive) */
int Main(void) { ... }   /* il linker non trova il punto di ingresso */
int main(void) { ... }   /* corretto */

/* ERRORE 5: dimenticare return 0 */
/* alcuni compilatori lo aggiungono implicitamente, ma è buona norma
 * scriverlo esplicitamente per chiarezza */
```

---

## Concetti collegati

- [`02-variabili-e-tipi`](../02-variabili-e-tipi/) — tipi di dato, dichiarazione e inizializzazione
- [`03-input-output`](../03-input-output/) — printf e scanf in dettaglio

---

## Esercizi proposti

1. **Modifica il saluto**: cambia `010-hello-world.c` per stampare tre righe
   distinte con il tuo nome, la città e l'anno corrente.

2. **Costanti personalizzate**: in `020-struttura-programma.c` aggiungi due
   costanti (`PESO_MIN` e `PESO_MAX`) e stampale insieme al valore della
   variabile `altezza`.

3. **Commenta il tuo codice**: scrivi un programma che calcoli la somma di
   due interi inseriti a compile-time (non da tastiera) e aggiungi un
   commento esplicativo a ogni riga, seguendo le buone pratiche di `030-commenti.c`.

4. **Biglietto esteso**: modifica `050-problema-biglietto-da-visita.c` per
   aggiungere un secondo numero di telefono (cellulare) al biglietto.

5. **Data estesa**: modifica `040-problema-saluto-personalizzato.c` per
   stampare anche il giorno della settimana come numero (1=lunedì … 7=domenica),
   inserito dall'utente.
