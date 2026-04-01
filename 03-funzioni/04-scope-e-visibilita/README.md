# 04 – Scope e visibilità

## Concetto

Lo **scope** (o ambito di visibilità) di una variabile definisce la porzione
di codice in cui quella variabile è accessibile. In C esistono due scope
principali: **locale** e **globale**.

### Variabili locali

Una variabile dichiarata all'interno di una funzione o di un blocco `{}` è
**locale** a quel blocco. Essa:

- è visibile solo all'interno del blocco in cui è dichiarata
- viene creata quando l'esecuzione entra nel blocco e distrutta quando ne esce
- non esiste al di fuori del blocco, nemmeno tra una chiamata e la successiva

```c
void funzione_a(void) {
    int x = 10;   /* x locale a funzione_a */
}

void funzione_b(void) {
    int x = 99;   /* x diversa e indipendente da quella di funzione_a */
}
```

### Variabili globali

Una variabile dichiarata fuori da qualsiasi funzione è **globale**. Essa:

- è visibile in tutte le funzioni del file
- esiste per tutta la durata del programma
- viene inizializzata a zero automaticamente se non viene fornito un valore

```c
int contatore = 0;   /* variabile globale */

void incrementa(void) { contatore++; }  /* la modifica è visibile ovunque */
void azzera(void)     { contatore = 0; }
```

Le variabili globali vanno usate con cautela: qualsiasi funzione può
modificarle, rendendo il comportamento del programma difficile da prevedere
e da testare. Sono appropriate quando più funzioni devono condividere uno
stato che deve persistere tra le chiamate.

### Shadowing

Se una variabile locale ha lo stesso nome di una globale, la locale **oscura**
(shadowing) la globale all'interno del proprio scope. Durante l'esecuzione del
blocco, il nome si riferisce alla variabile locale; la globale esiste ancora
ma non è raggiungibile con quel nome.

```c
int valore = 100;   /* globale */

void funzione(void) {
    int valore = 5;  /* locale: oscura la globale */
    valore++;        /* modifica solo la locale: la globale rimane 100 */
}
```

Lo shadowing è legale ma va evitato: causa bug sottili in cui il programmatore
crede di modificare la globale ma in realtà modifica solo la copia locale.

### Schema riassuntivo

```
int globale = 0;          ← visibile in tutto il file

void funzione(void) {
    int locale = 1;       ← visibile solo qui dentro
    {
        int locale2 = 2;  ← visibile solo in questo blocco
    }
    /* locale2 non esiste più */
}
/* locale non esiste più */
```

---

## File dell'esempio

| File | Tipo | Descrizione |
|------|------|-------------|
| `010-variabili-locali.c` | Concetto base | Durata e visibilità delle locali; stesso nome in funzioni diverse; blocchi annidati |
| `020-variabili-globali.c` | Concetto base | Dichiarazione globale, condivisione tra funzioni, inizializzazione automatica |
| `030-shadowing.c` | Concetto base | Oscuramento di una globale da parte di una locale con lo stesso nome |
| `040-problema-contatore-chiamate.c` | Problema specifico | Contatori globali di invocazioni per un sistema di diagnostica |
| `040-problema-contatore-chiamate-analisi.md` | Analisi | Analisi del problema contatore chiamate |
| `050-problema-temperatura-giornaliera.c` | Problema specifico | Stazione meteorologica: min, max, media con stato globale accumulato |
| `050-problema-temperatura-giornaliera-analisi.md` | Analisi | Analisi del problema temperatura giornaliera |
| `060-problema-validazione-input.c` | Problema specifico | Validazione modulo con contatore globale di errori |
| `060-problema-validazione-input-analisi.md` | Analisi | Analisi del problema validazione input |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-variabili-locali 010-variabili-locali.c
./010-variabili-locali

gcc -Wall -Wextra -o 020-variabili-globali 020-variabili-globali.c
./020-variabili-globali

gcc -Wall -Wextra -o 030-shadowing 030-shadowing.c
./030-shadowing

gcc -Wall -Wextra -o 040-problema-contatore-chiamate 040-problema-contatore-chiamate.c
./040-problema-contatore-chiamate

gcc -Wall -Wextra -o 050-problema-temperatura-giornaliera 050-problema-temperatura-giornaliera.c
./050-problema-temperatura-giornaliera

gcc -Wall -Wextra -o 060-problema-validazione-input 060-problema-validazione-input.c
./060-problema-validazione-input
```

---

## Output atteso

### 010-variabili-locali
```
=== Variabili locali in funzioni diverse ===

funzione_a: valore = 10  (indirizzo: 0x... varia)
funzione_b: valore = 99  (indirizzo: 0x... diverso)
funzione_a: valore = 10  (indirizzo: 0x... può variare)

=== Variabili locali in blocchi annidati ===

blocco esterno: x = 1
blocco interno: x = 1, y = 2
blocco esterno (dopo il blocco interno): x = 1

=== Variabile locale al main ===

locale_main = 42
```

### 020-variabili-globali
```
=== Registro operazioni ===

Operazioni eseguite: 0
Totale corrente:     0.00

Operazioni eseguite: 3
Totale corrente:     175.00

Operazioni eseguite: 4
Totale corrente:     145.00

(stato azzerato)
Operazioni eseguite: 0
Totale corrente:     0.00
```

### 030-shadowing
```
=== Modifica corretta della globale ===

contatore globale iniziale = 0

incrementa_globale: contatore (globale) = 1
incrementa_globale: contatore (globale) = 2
contatore globale dopo 2 incrementi = 2

=== Shadowing: la globale NON viene modificata ===

funzione_con_shadowing: contatore (locale)  = 100
funzione_con_shadowing: contatore (locale)  = 101  (dopo +1)
contatore globale dopo funzione_con_shadowing = 2

=== Shadowing in un blocco annidato ===

prima del blocco: contatore (globale) = 2
dentro il blocco: contatore (locale)  = 999
dopo il blocco:   contatore (globale) = 2
```

### 040-problema-contatore-chiamate
```
=== Listino prezzi scontati ===

Prodotto A (sconto 10%, IVA 22%):
  Prezzo originale:   150.00 EUR
  Prezzo finale:      164.34 EUR
  Risparmio:          -14.34 EUR

Prodotto B (sconto 20%, IVA 22%):
  Prezzo originale:   200.00 EUR
  Prezzo finale:      195.12 EUR
  Risparmio:            4.88 EUR

Prodotto C (nessuno sconto, IVA 22%):
  Prezzo originale:    80.00 EUR
  Prezzo finale:       97.60 EUR
  Risparmio:          -17.60 EUR

Prodotto D (sconto 15% + 5%, IVA 22%):
  Prezzo originale:   300.00 EUR
  Prezzo finale:      295.55 EUR
  Risparmio:            4.45 EUR

=== Riepilogo chiamate ===
  calcola_sconto:  4
  calcola_iva:     4
  stampa_prezzo:   4
  Totale:          12
```

### 050-problema-temperatura-giornaliera
```
=== Stazione meteorologica - 20/03/2024 ===

Ora     Temperatura
-------------------
  00:00   +4.2 C
  02:00   +3.8 C
  04:00   +3.1 C
  06:00   +4.5 C
  08:00   +7.3 C
  10:00  +11.8 C
  12:00  +14.2 C
  14:00  +15.6 C
  16:00  +13.9 C
  18:00  +10.4 C
  20:00   +7.8 C
  22:00   +5.9 C

--- Report giornaliero ---
Rilevazioni:   12
Temperatura minima:   +3.1 C
Temperatura massima: +15.6 C
Temperatura media:    +7.7 C
Escursione termica:   12.5 C
```

### 060-problema-validazione-input
```
=== Validazione modulo di registrazione ===

--- Caso 1: dati corretti ---
  Eta':    35
  Codice:  47231

Modulo ACCETTATO. Nessun errore rilevato.

--- Caso 2: eta' non valida ---
  Eta':    15
  Codice:  83400
  ERRORE: eta' non valida (deve essere compresa tra 18 e 120)

Modulo RIFIUTATO. Errori rilevati: 1

--- Caso 3: tutti i campi errati ---
  Eta':    200
  Codice:  999
  ERRORE: eta' non valida (deve essere compresa tra 18 e 120)
  ERRORE: codice cliente non valido (deve essere a 5 cifre)

Modulo RIFIUTATO. Errori rilevati: 2
```

---

## Errori comuni da evitare

```c
/* ERRORE 1: credere che una variabile locale conservi il valore
 * tra una chiamata e la successiva */
void conta(void) {
    int n = 0;   /* ricreata a zero a ogni chiamata */
    n++;
    printf("%d\n", n);   /* stampa sempre 1 */
}
/* Per conservare il valore tra le chiamate serve una variabile globale
 * (o, in futuro, una variabile static - capitolo 12). */
```

```c
/* ERRORE 2: shadowing involontario */
int risultato = 0;   /* globale */

void aggiorna(int valore) {
    int risultato = valore;   /* ATTENZIONE: oscura la globale */
    /* la globale non viene modificata */
}
/* Soluzione: usare nomi distinti per evitare ambiguità */
```

```c
/* ERRORE 3: usare una variabile locale fuori dal suo scope */
void funzione(void) {
    int x = 5;
}

int main(void) {
    funzione();
    printf("%d\n", x);   /* ERRORE: x non esiste qui */
    return 0;
}
```

```c
/* ERRORE 4: dimenticare di azzerare il contatore globale tra un caso e l'altro */
int errori = 0;

void valida_primo_modulo(void)  { /* ... incrementa errori ... */ }
void valida_secondo_modulo(void){ /* ... incrementa errori ... */ }

int main(void) {
    valida_primo_modulo();
    /* errori va azzerato qui prima di procedere con il secondo modulo */
    errori = 0;
    valida_secondo_modulo();
    return 0;
}
```

---

## Concetti collegati

- `01-definizione-e-chiamata` – struttura delle funzioni e chiamata
- `02-parametri-e-return` – alternative alle globali per condividere dati tra funzioni
- `12-programmazione-avanzata/01-variabili-statiche-ed-extern` – variabili `static` (locali con durata permanente) e `extern` (globali tra file diversi)

---

## Esercizi proposti

1. **(Facile)** Scrivi un programma con una variabile globale `int passi = 0`
   e due funzioni: `avanza()` che incrementa `passi` di 1 e `indietreggia()`
   che lo decrementa di 1. Chiamale in sequenza e stampa il valore di `passi`
   dopo ogni operazione.

2. **(Medio)** Riscrivi l'esempio `020-variabili-globali.c` eliminando le
   variabili globali: passa `numero_operazioni` e `totale` come parametri
   per riferimento alle funzioni che le modificano. Confronta le due versioni
   e valuta quale è più leggibile.

3. **(Avanzato)** Aggiungi al programma `060-problema-validazione-input.c`
   una terza funzione `valida_anno_nascita(int anno)` che controlla che
   l'anno di nascita sia compreso tra 1900 e 2006 (età minima 18 anni
   rispetto al 2024). Assicurati che `errori_trovati` venga aggiornato
   correttamente anche dalla nuova funzione.
