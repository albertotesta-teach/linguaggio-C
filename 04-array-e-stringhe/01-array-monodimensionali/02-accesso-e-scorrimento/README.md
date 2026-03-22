# 02 – Accesso e scorrimento di array monodimensionali

## Concetto

Una volta dichiarato un array, si accede ai suoi elementi tramite l'**operatore di
indicizzazione `[]`**. L'indice può essere una costante, una variabile o qualsiasi
espressione intera. Gli indici validi vanno sempre da **0** a **dimensione − 1**.

```
  int v[5] = {10, 20, 30, 40, 50};

  Lettura:   x = v[2];        /* x = 30 */
  Scrittura: v[2] = 99;       /* v diventa {10, 20, 99, 40, 50} */
  Espressione come indice:
             i = 1;
             y = v[i + 1];   /* y = v[2] = 99 */
```

### Scorrimento con ciclo for

Il modo più comune per visitare tutti gli elementi:

```c
for (i = 0; i < N; i++) {
    printf("%d\n", v[i]);
}
```

### Varianti di scorrimento

```c
/* Ordine inverso */
for (i = N - 1; i >= 0; i--) { ... }

/* Passo 2 (elementi pari) */
for (i = 0; i < N; i += 2) { ... }

/* Scorrimento parziale (solo i primi k elementi) */
for (i = 0; i < k; i++) { ... }
```

### Accesso fuori dai limiti

In C il compilatore **non controlla** i limiti dell'array a runtime. Un accesso
fuori range produce comportamento indefinito: il programma può leggere dati
casuali, sovrascrivere altre variabili o andare in crash.

```c
int v[5];
v[5]  = 0;   /* ERRORE: indice valido fino a 4 */
v[-1] = 0;   /* ERRORE: indice negativo */
```

La difesa corretta è verificare sempre che l'indice sia nel range `[0, N-1]`
prima di usarlo.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-accesso-per-indice.c` | Lettura e scrittura tramite indice costante, variabile ed espressione; accesso sicuro con controllo dei limiti |
| `020-scorrimento-con-cicli.c` | Scorrimento con `for`, `while` e `do-while`; ordine inverso, passo 2, scorrimento parziale |
| `030-lettura-da-tastiera.c` | Acquisizione di valori da tastiera con validazione; barra grafica ASCII proporzionale al valore |
| `040-problema-rubrica-telefonica.c` | Rubrica 6 contatti: stampa, ricerca per prefisso del nome, filtro per prefisso telefonico |
| `040-problema-rubrica-telefonica-analisi.md` | Analisi di `040-problema-rubrica-telefonica.c` |
| `050-problema-sensori-industriali.c` | 8 sensori temperatura: dashboard con stato OK/ALLARME, elenco fuori soglia, media impianto |
| `050-problema-sensori-industriali-analisi.md` | Analisi di `050-problema-sensori-industriali.c` |
| `060-problema-questionario.c` | Questionario 10 domande A/B/C/D: input con validazione, correzione parallela, punteggio finale |
| `060-problema-questionario-analisi.md` | Analisi di `060-problema-questionario.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-accesso-per-indice 010-accesso-per-indice.c
./010-accesso-per-indice

gcc -Wall -Wextra -o 020-scorrimento-con-cicli 020-scorrimento-con-cicli.c
./020-scorrimento-con-cicli

gcc -Wall -Wextra -o 030-lettura-da-tastiera 030-lettura-da-tastiera.c
./030-lettura-da-tastiera

gcc -Wall -Wextra -o 040-problema-rubrica-telefonica 040-problema-rubrica-telefonica.c
./040-problema-rubrica-telefonica

gcc -Wall -Wextra -o 050-problema-sensori-industriali 050-problema-sensori-industriali.c
./050-problema-sensori-industriali

gcc -Wall -Wextra -o 060-problema-questionario 060-problema-questionario.c
./060-problema-questionario
```

---

## Output atteso

### 010-accesso-per-indice
```
Accesso con indice costante:
  misure[0] = 42  (primo elemento)
  misure[2] = 95  (terzo elemento)
  misure[5] = 31  (ultimo elemento, indice = DIMENSIONE-1)

Accesso con indice variabile (i = 3):
  misure[i] = misure[3] = 8

Prima della modifica: misure[1] = 17
Dopo la modifica:     misure[1] = 99

Accesso con espressione (i = 2):
  misure[i - 1] = misure[1] = 99
  misure[i + 1] = misure[3] = 8
  misure[i * 2] = misure[4] = 63

Tutti gli elementi con ciclo for:
  misure[0] = 42
  misure[1] = 99
  misure[2] = 95
  misure[3] = 8
  misure[4] = 63
  misure[5] = 31

Accesso sicuro: misure[4] = 63
```

### 020-scorrimento-con-cicli
```
Scorrimento con for (da sinistra a destra):
  valori[0] = 5
  valori[1] = 12
  valori[2] = 3
  valori[3] = 18
  valori[4] = 7
  valori[5] = 25
  valori[6] = 9
  valori[7] = 14

Scorrimento con while:
  [stessa sequenza]

Scorrimento con do-while:
  [stessa sequenza]

Scorrimento in ordine inverso:
  valori[7] = 14
  valori[6] = 9
  ...
  valori[0] = 5

Scorrimento parziale (solo i primi 4 elementi):
  valori[0] = 5
  valori[1] = 12
  valori[2] = 3
  valori[3] = 18

Scorrimento con passo 2 (elementi pari):
  valori[0] = 5
  valori[2] = 3
  valori[4] = 7
  valori[6] = 9
```

### 030-lettura-da-tastiera
*(output dipendente dai valori inseriti – esempio con input 7 8 6 9 5)*
```
=== Inserimento voti ===
Inserisci 5 voti (da 1 a 10):

  Voto studente 1: 7
  Voto studente 2: 8
  Voto studente 3: 6
  Voto studente 4: 9
  Voto studente 5: 5

=== Riepilogo voti inseriti ===
  Studente 1: 7
  Studente 2: 8
  Studente 3: 6
  Studente 4: 9
  Studente 5: 5

Media dei voti: 7.0

Distribuzione:
  Studente 1 [ 7]: *******
  Studente 2 [ 8]: ********
  Studente 3 [ 6]: ******
  Studente 4 [ 9]: *********
  Studente 5 [ 5]: *****
```

### 040-problema-rubrica-telefonica
```
======================================
           RUBRICA TELEFONICA
======================================
  Rossi Marco          3471234567
  Bianchi Sara         0212345678
  Verdi Luca           3389876543
  Ferrari Anna         0612223344
  Russo Pietro         3201112233
  Colombo Giulia       0116667788
======================================

Ricerca 'Rossi':
  Trovato: Rossi Marco - Tel: 3471234567

Contatti con numero di cellulare (prefisso '3'):
  Rossi Marco: 3471234567
  Verdi Luca: 3389876543
  Russo Pietro: 3201112233
Totale cellulari in rubrica: 3 su 6
```

### 050-problema-sensori-industriali
*(output dipendente dall'input – esempio)*
```
=== SISTEMA DI MONITORAGGIO SENSORI ===

Inserisci la temperatura rilevata per ciascun sensore (°C):
  Sensore S01: 65.0
  Sensore S02: 5.0
  ...

--- DASHBOARD IMPIANTO ---
  Sensore    | Temp (°C)  | Stato
  -----------|------------|-------
  S01        |     65.0 °C | OK
  S02        |      5.0 °C | ALLARME
  ...

Sensori fuori soglia [10°C - 80°C]:
  [!] S02: 5.0°C - TEMPERATURA TROPPO BASSA

Temperatura media impianto: 48.3°C
Sensori in allarme: 1 su 8
```

### 060-problema-questionario
*(output dipendente dall'input – esempio con risposte A C B D A C B A D C)*
```
=== QUESTIONARIO A RISPOSTA MULTIPLA ===
Inserisci la risposta (A/B/C/D) per ciascuna domanda:

  Domanda  1: A
  ...
  Domanda 10: C

=== CORREZIONE ===
  Dom. | Risposta | Corretta | Esito
  -----|----------|----------|------
     1 |    A     |    A     | OK
     2 |    C     |    C     | OK
  ...

=== RISULTATO ===
  Risposte corrette : 10 su 10
  Risposte errate   : 0 su 10
  Punteggio         : 100%
  Esito             : PROMOSSO
```

---

## Errori comuni da evitare

**Indice fuori dai limiti (off-by-one)**
```c
int v[5];
for (int i = 0; i <= 5; i++) {   /* ERRORE: i arriva a 5, fuori range */
    v[i] = 0;                     /* Corretto: i < 5 */
}
```

**Dimenticare di aggiornare l'indice nel while**
```c
int i = 0;
while (i < N) {
    printf("%d\n", v[i]);
    /* ERRORE: i non viene mai incrementato → ciclo infinito */
}
```

**Usare un intero senza segno come indice in decremento**
```c
unsigned int i;
for (i = N - 1; i >= 0; i--) {   /* ERRORE: unsigned non diventa mai negativo */
    /* ciclo infinito perché i >= 0 è sempre vero per unsigned */
}
/* Soluzione: usare int come tipo dell'indice */
```

**Leggere char con scanf senza lo spazio prima di %c**
```c
scanf("%c", &c);   /* potrebbe leggere il '\n' del prompt precedente */
scanf(" %c", &c);  /* corretto: lo spazio consuma tutti gli spazi e newline */
```

---

## Concetti collegati

- `01-dichiarazione-e-inizializzazione` → come creare e popolare un array
- `03-operazioni-su-array` → somma, ricerca, inversione
- `04-array-e-funzioni` → passare un array a una funzione per elaborarlo
- `05-array-a-tappo` → scorrimento con terminatore invece di dimensione fissa

---

## Esercizi proposti

1. Modifica `010-accesso-per-indice.c` per chiedere all'utente un indice,
   verificare che sia nel range valido `[0, DIMENSIONE-1]` e stampare
   l'elemento corrispondente (o un messaggio di errore).

2. Scrivi un programma che legga 6 valori interi da tastiera in un array
   e poi li stampi in ordine inverso, senza usare un secondo array.

3. Partendo da `030-lettura-da-tastiera.c`, aggiungi la stampa del numero
   di voti sufficienti (>= 6) e insufficienti (< 6) inseriti dall'utente.

4. Modifica `040-problema-rubrica-telefonica.c` per cercare un contatto
   leggendo il nome da tastiera invece di usare una stringa fissa.

5. (Avanzato) Estendi `060-problema-questionario.c` per gestire più
   studenti: inserisci le risposte di 3 studenti e stampa la classifica
   dal punteggio più alto al più basso.
