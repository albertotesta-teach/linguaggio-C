# 03 – Switch

## Concetto

Lo `switch` sceglie un ramo confrontando il valore di **un'espressione
intera** con una serie di **costanti**. È l'alternativa leggibile a una
catena `else if` del tipo `x == 1`, `x == 2`, `x == 3`...

```c
switch (espressione) {
    case COSTANTE_1:
        istruzioni;
        break;
    case COSTANTE_2:
        istruzioni;
        break;
    default:
        istruzioni per tutti gli altri valori;
        break;
}
```

```
  espressione ──┬── == COSTANTE_1 ? ──► ramo 1 ──► break ──┐
                ├── == COSTANTE_2 ? ──► ramo 2 ──► break ──┤
                └── nessuna        ──► default ──► break ──┴──► dopo lo switch
```

### Regole

| Regola | Esempio corretto | Errore |
|--------|------------------|--------|
| espressione di tipo intero (`int`, `char`) | `switch (giorno)` | `switch (temperatura)` con `double` |
| `case` seguito da una costante | `case 3:`, `case 'S':`, `case MAX:` | `case x:`, `case eta >= 18:` |
| costanti tutte diverse | | due `case 3:` |
| `default` sempre presente | | |

### Break e casi raggruppati

`break` fa uscire dallo `switch`. Senza `break` l'esecuzione **prosegue nel
case successivo** (*fall-through*). Si sfrutta per raggruppare più valori
che condividono lo stesso codice:

```c
case 6:
case 7:
    printf("fine settimana\n");
    break;
```

Il `break` dentro lo `switch` è l'**unico uso di `break` ammesso** dalle
convenzioni del corso (vedi `06-break-continue`).

### Switch o else-if?

| Situazione | Struttura |
|------------|-----------|
| una variabile confrontata con valori singoli (menu, codici, mesi) | `switch` |
| intervalli (`voto >= 6`), condizioni composte, valori reali | `if / else if` |

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-switch-base.c` | Struttura dello switch: un ramo per valore, più istruzioni per ramo, valori non consecutivi, default |
| `020-casi-raggruppati.c` | Case raggruppati (feriale/festivo, stagioni, fasce di voto) ed effetto del break dimenticato |
| `030-switch-su-caratteri.c` | Menu a lettere letto da tastiera con maiuscole e minuscole |
| `040-problema-giorni-del-mese.c` | Nome e numero di giorni di un mese, febbraio bisestile |
| `040-problema-giorni-del-mese-analisi.md` | Analisi di `040-problema-giorni-del-mese.c` |
| `050-problema-distributore-bevande.c` | Codice prodotto → nome e prezzo, pagamento e resto |
| `050-problema-distributore-bevande-analisi.md` | Analisi di `050-problema-distributore-bevande.c` |
| `060-problema-giudizio-voto.c` | Voto in decimi → giudizio, livello di apprendimento ed esito |
| `060-problema-giudizio-voto-analisi.md` | Analisi di `060-problema-giudizio-voto.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-switch-base 010-switch-base.c
./010-switch-base

gcc -Wall -Wextra -o 020-casi-raggruppati 020-casi-raggruppati.c
./020-casi-raggruppati

gcc -Wall -Wextra -o 030-switch-su-caratteri 030-switch-su-caratteri.c
./030-switch-su-caratteri

gcc -Wall -Wextra -o 040-problema-giorni-del-mese 040-problema-giorni-del-mese.c
./040-problema-giorni-del-mese

gcc -Wall -Wextra -o 050-problema-distributore-bevande 050-problema-distributore-bevande.c
./050-problema-distributore-bevande

gcc -Wall -Wextra -o 060-problema-giudizio-voto 060-problema-giudizio-voto.c
./060-problema-giudizio-voto
```

---

## Output atteso

### 010-switch-base
```
=== Giorno della settimana ===
giorno = 3 -> mercoledi'

=== Livello di difficolta' ===
livello = 2
Medio: 3 vite, nemici normali.
Suggerimenti solo su richiesta.

=== Codici di stato HTTP ===
codice 404: pagina non trovata
```

### 020-casi-raggruppati
```
=== Feriale o festivo ===
giorno = 6 -> fine settimana

=== Stagione ===
mese = 11 -> autunno

=== Esito della verifica ===
voto = 4 -> gravemente insufficiente
```

### 030-switch-su-caratteri
*(output dipendente dall'input – esempio con la scelta m)*
```
=== CONTO CORRENTE - MENU ===
  S - Saldo
  M - Movimenti
  B - Bonifico
  E - Esci
Scelta: m

Ultimi movimenti:
  03/10  stipendio        +1450.00
  05/10  bolletta luce      -78.40
```

### 040-problema-giorni-del-mese
*(output dipendente dall'input – esempio con febbraio 2024)*
```
=== GIORNI DEL MESE ===

Mese (1-12): 2
Anno: 2024

Febbraio 2024 ha 29 giorni.
```

*(output dipendente dall'input – esempio con il mese 13)*
```
=== GIORNI DEL MESE ===

Mese (1-12): 13
Anno: 2025

Mese 13: non e' un mese valido (inserire un numero da 1 a 12).
```

### 050-problema-distributore-bevande
*(output dipendente dall'input – esempio con codice 21 e 200 centesimi)*
```
=== DISTRIBUTORE AUTOMATICO ===
  11  Acqua naturale     0,60
  12  Acqua frizzante    0,60
  21  Te' al limone      1,20
  22  Succo di frutta    1,20
  31  Caffe' freddo      1,50
Codice prodotto: 21
Selezionato: Te' al limone
Prezzo: 1,20 euro
Importo inserito (centesimi): 200
Erogazione in corso... Resto: 0,80 euro
```

*(output dipendente dall'input – esempio con codice 31 e 100 centesimi)*
```
=== DISTRIBUTORE AUTOMATICO ===
  11  Acqua naturale     0,60
  12  Acqua frizzante    0,60
  21  Te' al limone      1,20
  22  Succo di frutta    1,20
  31  Caffe' freddo      1,50
Codice prodotto: 31
Selezionato: Caffe' freddo
Prezzo: 1,50 euro
Importo inserito (centesimi): 100
Importo insufficiente: mancano 50 centesimi. Monete restituite.
```

### 060-problema-giudizio-voto
*(output dipendente dall'input – esempio con il voto 8)*
```
=== REGISTRO - GIUDIZIO DEL VOTO ===

Voto in decimi (1-10): 8

Giudizio: buono
Livello di apprendimento: intermedio
Esito: SUFFICIENTE
```

*(output dipendente dall'input – esempio con il voto 5)*
```
=== REGISTRO - GIUDIZIO DEL VOTO ===

Voto in decimi (1-10): 5

Giudizio: mediocre
Livello di apprendimento: in via di acquisizione
Esito: INSUFFICIENTE - manca 1 punto alla sufficienza
```

---

## Errori comuni da evitare

**Break dimenticato**
```c
case 6:
    printf("sabato\n");      /* manca break: prosegue nel case 7 */
case 7:
    printf("domenica\n");
    break;
/* con giorno = 6 stampa "sabato" e "domenica" */
```

**Condizione al posto di una costante**
```c
switch (voto) {
    case voto >= 6:     /* ERRORE: serve una costante */
```

**Switch su un valore reale**
```c
double prezzo = 1.20;
switch (prezzo) { ... }  /* ERRORE di compilazione: serve un tipo intero */
```

**Stringa al posto di un carattere**
```c
case "S":   /* ERRORE: "S" è una stringa */
case 'S':   /* corretto */
```

**Default mancante**
```c
switch (scelta) {
    case 1: ...
    case 2: ...
}   /* un valore imprevisto viene ignorato in silenzio */
```

---

## Concetti collegati

- `02-if-else` → catena else-if, necessaria per intervalli e condizioni composte
- `01-logica-booleana/050-problema-anno-bisestile.c` → regola usata per febbraio
- `04-while-do-while` → lo switch dentro un ciclo per realizzare un menu ripetuto
- `06-break-continue` → perché il break è ammesso solo nello switch

---

## Esercizi proposti

1. Scrivi un programma che legga un numero da 1 a 12 e stampi il trimestre
   (primo, secondo, terzo, quarto) usando case raggruppati.

2. Modifica `030-switch-su-caratteri.c` aggiungendo l'opzione `P - Prelievo`
   che chiede un importo e lo sottrae dal saldo se è disponibile.

3. Scrivi una calcolatrice che legga due numeri e un operatore (`+`, `-`,
   `*`, `/`) e usi uno switch sul carattere; gestisci la divisione per zero.

4. Estendi `050-problema-distributore-bevande.c` con un nuovo prodotto
   (codice 32, cioccolata calda, 1,50 euro). Quanti punti del codice devi
   modificare?

5. (Avanzato) Scrivi un programma che, dati giorno e mese di nascita, stampi
   il segno zodiacale: uno switch sul mese e, dentro ogni ramo, un if sul giorno
   (per esempio a marzo: fino al 20 Pesci, dal 21 Ariete). Controlla anche che
   il giorno sia valido per il mese inserito.
