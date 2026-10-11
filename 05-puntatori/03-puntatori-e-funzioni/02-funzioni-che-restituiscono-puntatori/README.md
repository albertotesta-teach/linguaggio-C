# 02 – Funzioni che restituiscono puntatori

## Concetto

Una funzione può restituire un **indirizzo**. Una ricerca che restituisce il
puntatore all'elemento trovato permette al chiamante di leggerlo e di
**modificarlo direttamente**, senza conoscerne la posizione.

```c
int *massimo(int *v, int n);

int *caldo = massimo(temperature, N);
*caldo = *caldo - 3;                 /* modifica l'elemento nell'array */
printf("%d", (int) (caldo - temperature));   /* la sua posizione */
```

Se il chiamante deve solo leggere, parametro e risultato sono `const`:

```c
const int *minimo(const int *v, int n);
```

### `NULL` per "non trovato"

```c
int *cerca(int *v, int n, int valore)
{
    int *p = v;

    while (p < v + n && *p != valore) {
        p++;
    }
    return p < v + n ? p : NULL;
}

int *trovato = cerca(armadietti, N, matricola);
if (trovato != NULL) {
    *trovato = 0;
}
```

Il risultato si controlla **sempre** prima di usarlo.

### Quale indirizzo si può restituire

| Indirizzo restituito | Valido dopo il `return`? |
|----------------------|--------------------------|
| di un elemento di un array del chiamante | sì |
| di una parte di una stringa ricevuta (`testo + k`) | sì |
| `NULL` | sì, ma non si dereferenzia |
| di una variabile locale o di un parametro | **no**: la variabile non esiste più |

```c
double *media_sbagliata(const int *voti, int n)
{
    double m;
    ...
    return &m;            /* ERRORE: m sparisce al return */
}
```

Al posto dell'indirizzo di una variabile locale si restituisce il valore,
oppure si scrive il risultato in un parametro di uscita.

### Le funzioni della libreria

`strchr`, `strrchr` e `strstr` sono funzioni che restituiscono puntatori
dentro la stringa ricevuta. In questa sezione se ne scrivono le versioni a
mano: `trova` (come `strstr`) e `ultimo` (come `strrchr`).

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-puntatore-al-massimo.c` | `int *massimo(...)` per modificare l'elemento, `const int *minimo(...)` |
| `020-ricerca-con-null.c` | Ricerca che restituisce `NULL` se non trova, armadietti liberati |
| `030-mai-indirizzi-locali.c` | Perché non si restituisce `&locale`, tre alternative corrette |
| `040-problema-scaffale.c` | Puntatore alla quantità di un articolo cercato per codice |
| `040-problema-scaffale-analisi.md` | Analisi di `040-problema-scaffale.c` |
| `050-problema-prossimo-treno.c` | Puntatore al prossimo orario e treni successivi `p + 1`, `p + 2` |
| `050-problema-prossimo-treno-analisi.md` | Analisi di `050-problema-prossimo-treno.c` |
| `060-problema-cerca-parola.c` | `trova`, una `strstr` scritta a mano, conteggio e contesto |
| `060-problema-cerca-parola-analisi.md` | Analisi di `060-problema-cerca-parola.c` |
| `070-problema-nome-file.c` | `ultimo`, una `strrchr` scritta a mano: cartella, nome ed estensione |
| `070-problema-nome-file-analisi.md` | Analisi di `070-problema-nome-file.c` |
| `080-problema-aula-libera.c` | Puntatore all'aula libera più vicina |
| `080-problema-aula-libera-analisi.md` | Analisi di `080-problema-aula-libera.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-puntatore-al-massimo 010-puntatore-al-massimo.c
./010-puntatore-al-massimo

gcc -Wall -Wextra -o 020-ricerca-con-null 020-ricerca-con-null.c
./020-ricerca-con-null

gcc -Wall -Wextra -o 030-mai-indirizzi-locali 030-mai-indirizzi-locali.c
./030-mai-indirizzi-locali

gcc -Wall -Wextra -o 040-problema-scaffale 040-problema-scaffale.c
./040-problema-scaffale

gcc -Wall -Wextra -o 050-problema-prossimo-treno 050-problema-prossimo-treno.c
./050-problema-prossimo-treno

gcc -Wall -Wextra -o 060-problema-cerca-parola 060-problema-cerca-parola.c
./060-problema-cerca-parola

gcc -Wall -Wextra -o 070-problema-nome-file 070-problema-nome-file.c
./070-problema-nome-file

gcc -Wall -Wextra -o 080-problema-aula-libera 080-problema-aula-libera.c
./080-problema-aula-libera
```

---

## Output atteso

### 010-puntatore-al-massimo
```
Temperature:   3.8   4.2   6.1   3.5   4.7
Frigo piu' caldo: n. 3 con 6.1 gradi
Dopo l'intervento sul frigo n. 3:   3.8   4.2   4.9   3.5   4.7
Frigo piu' freddo: n. 4 con 3.5 gradi
Temperatura massima attuale: 4.9 gradi
```

### 020-ricerca-con-null
```
Armadietti: [4120] [libero] [3871] [4402] [libero] [3990] [4015] [libero]
Matricola 4402: armadietto n. 4 liberato
Matricola 5000: nessun armadietto assegnato
Matricola 3990: armadietto n. 6 liberato
Nuovo studente 4560: armadietto n. 2
Armadietti: [4120] [4560] [3871] [libero] [libero] [libero] [4015] [libero]
```

### 030-mai-indirizzi-locali
```
1. media(voti, n)          = 7.00
2. media_in(voti, n, &m)   -> m = 7.00
3. voto_migliore(voti, n)  -> 9, il 6-esimo voto
```

### 040-problema-scaffale
*(output dipendente dall'input – esempio di sessione)*
```
Inventario:  1001: 40  1002: 25  2010: 120  2011: 8  3050: 15
Movimento (C codice n, S codice n, Q): S 2011 5
  Codice 2011: scaricati 5, ora 3 pezzi
Movimento (C codice n, S codice n, Q): S 2011 5
  Codice 2011: solo 3 pezzi disponibili
Movimento (C codice n, S codice n, Q): C 2011 50
  Codice 2011: caricati 50, ora 53 pezzi
Movimento (C codice n, S codice n, Q): S 9999 1
  Codice 9999 inesistente.
Movimento (C codice n, S codice n, Q): C 1001 0
  Dati non validi.
Inventario:  1001: 40  1002: 25  2010: 120  2011: 53  3050: 15
```

### 050-problema-prossimo-treno
*(output dipendente dall'input – esempio di sessione)*
```
=== PROSSIME PARTENZE ===
Ora attuale (hh:mm, q per finire): 5:30
  Dalle 05:30:  06:12 (tra 42 min)  06:47 (tra 77 min)  07:15 (tra 105 min)
Ora attuale (hh:mm, q per finire): 7:20
  Dalle 07:20:  07:40 (tra 20 min)  08:25 (tra 65 min)  12:05 (tra 285 min)
Ora attuale (hh:mm, q per finire): 13:35
  Dalle 13:35:  13:35 (in partenza)  17:50 (tra 255 min)  21:10 (tra 455 min)
Ora attuale (hh:mm, q per finire): 18:00
  Dalle 18:00:  21:10 (tra 190 min)
Ora attuale (hh:mm, q per finire): 22:15
  Dalle 22:15: nessun treno fino a domani, primo alle 06:12
Ora attuale (hh:mm, q per finire): q
```

### 060-problema-cerca-parola
```
Art. 7 - Uso del telefono. Durante le lezioni il telefono deve restare spento. Il telefono si puo' usare solo con il permesso del docente. In laboratorio vale lo stesso divieto.

"telefono": 3 volte, la prima in posizione 17: "...7 - Uso del telefono. Durante le..."
"docente": 1 volta, la prima in posizione 130: "...ermesso del docente. In laborat..."
"divieto": 1 volta, la prima in posizione 169: "...e lo stesso divieto...."
"intervallo": non presente
```

### 070-problema-nome-file
```
4B/informatica/verifica-3.c
  cartella:   4B/informatica
  nome:       verifica-3
  estensione: c
4B/informatica/relazione.lab.pdf
  cartella:   4B/informatica
  nome:       relazione.lab
  estensione: pdf
5A/sistemi/v1.2/schema
  cartella:   5A/sistemi/v1.2
  nome:       schema
  estensione: (nessuna)
appunti.txt
  cartella:   (nessuna)
  nome:       appunti
  estensione: txt
4B/storia/.nascosto
  cartella:   4B/storia
  nome:       .nascosto
  estensione: (nessuna)
```

### 080-problema-aula-libera
*(output dipendente dall'input – esempio di sessione)*
```
  Corridoio: [ 1 X] [ 2  ] [ 3 X] [ 4 X] [ 5 X] [ 6  ] [ 7 X] [ 8 X] [ 9  ] [10 X]
Aula richiesta (1-10, 0 per finire): 2
  Assegnata l'aula 2.
  Corridoio: [ 1 X] [ 2 X] [ 3 X] [ 4 X] [ 5 X] [ 6  ] [ 7 X] [ 8 X] [ 9  ] [10 X]
Aula richiesta (1-10, 0 per finire): 5
  Aula 5 occupata: assegnata l'aula 6.
  Corridoio: [ 1 X] [ 2 X] [ 3 X] [ 4 X] [ 5 X] [ 6 X] [ 7 X] [ 8 X] [ 9  ] [10 X]
Aula richiesta (1-10, 0 per finire): 5
  Aula 5 occupata: assegnata l'aula 9.
  Corridoio: [ 1 X] [ 2 X] [ 3 X] [ 4 X] [ 5 X] [ 6 X] [ 7 X] [ 8 X] [ 9 X] [10 X]
Aula richiesta (1-10, 0 per finire): 10
  Nessuna aula libera.
Aula richiesta (1-10, 0 per finire): 12
  Aula inesistente.
Aula richiesta (1-10, 0 per finire): 0
```

---

## Errori comuni da evitare

**Restituire l'indirizzo di una variabile locale**
```c
int *crea(void)
{
    int x = 5;
    return &x;            /* avviso del compilatore, risultato non utilizzabile */
}
```

**Usare il risultato senza controllare `NULL`**
```c
*cerca(v, n, 7) = 0;      /* se 7 non c'è: dereferenziazione di NULL */
```

**Calcolare un indirizzo fuori dall'array**
```c
if (centro - d >= occupata) ...   /* centro - d può essere prima dell'array */
if (indice - d >= 0) ...          /* corretto: si controlla l'indice */
```

**Togliere `const` al risultato**
```c
int *p = minimo(v, n);    /* avviso: minimo restituisce const int * */
```

**Ricominciare la ricerca dallo stesso punto**
```c
trovato = trova(trovato, parola);       /* trova sempre la stessa occorrenza */
trovato = trova(trovato + 1, parola);   /* corretto */
```

---

## Concetti collegati

- `01-parametri-per-riferimento` → risultati nei parametri di uscita
- `02-puntatori-e-array/03-stringhe-e-puntatori` → puntatori dentro una stringa
- `04-array-e-stringhe/04-funzioni-su-stringhe` → `strchr`, `strrchr`, `strstr`
- `03-puntatori-a-funzione` → funzioni passate come argomento

---

## Esercizi proposti

1. In `010-puntatore-al-massimo.c` scrivi `int *primo_sopra(int *v, int n,
   int soglia)` e abbassa tutti i frigoriferi sopra i 5 gradi.

2. In `020-ricerca-con-null.c` scrivi `ultimo_uguale`, che restituisce il
   puntatore all'ultima occorrenza.

3. In `050-problema-prossimo-treno.c` mostra anche il treno appena
   partito, cioè `p - 1`, solo se esiste.

4. In `060-problema-cerca-parola.c` rendi la ricerca indipendente da
   maiuscole e minuscole.

5. (Avanzato) In `080-problema-aula-libera.c` scrivi `int *piu_vicina_da(int
   *occupata, int n, int richiesta, int verso)` che cerca solo a sinistra o
   solo a destra.
