# 03 – Passaggio per riferimento

## Concetto

In C i parametri scalari sono passati **per valore**: la funzione riceve una
copia del dato e non può modificare la variabile originale del chiamante.
Quando una funzione deve modificare una variabile esterna, oppure deve
"restituire" più di un risultato, si usa il **passaggio per riferimento**:
si passa l'**indirizzo** della variabile invece del suo valore.

### I due operatori fondamentali

| Operatore | Nome | Significato |
|-----------|------|-------------|
| `&x` | indirizzo-di | restituisce l'indirizzo in memoria di `x` |
| `*p` | dereferenziazione | accede al valore all'indirizzo contenuto in `p` |

```c
int eta = 25;
int *p = &eta;   /* p contiene l'indirizzo di eta */

*p = 30;         /* modifica eta tramite il puntatore */
printf("%d\n", eta);   /* stampa 30 */
```

### Passaggio per riferimento nelle funzioni

Per modificare una variabile del chiamante, la funzione deve ricevere il suo
**indirizzo** come parametro (un puntatore) e usare `*` per accedervi:

```c
void raddoppia(int *n)   /* n è un puntatore a int */
{
    *n = *n * 2;         /* modifica la variabile puntata */
}

int main(void) {
    int x = 5;
    raddoppia(&x);       /* si passa &x, non x */
    printf("%d\n", x);   /* stampa 10 */
    return 0;
}
```

### Confronto per valore vs per riferimento

```
Per valore:                    Per riferimento:
──────────────────────         ──────────────────────────
int x = 5;                     int x = 5;
f(x);        ←copia→           f(&x);    ←indirizzo→
             int n = 5;                   int *n = &x;
             n = n*2;                     *n = *n*2;
x rimane 5                     x diventa 10
```

### Parametri IN e OUT

Nella stessa funzione si possono avere parametri di entrambi i tipi:

```c
void dividi(int a, int b, int *q, int *r)
{      /* IN  IN    OUT      OUT  */
    *q = a / b;
    *r = a % b;
}
```

Convenzione: i parametri **IN** (sola lettura) si passano per valore;
i parametri **OUT** (scrittura) si passano per riferimento.

### Nota sul capitolo 05

Questo file introduce i puntatori solo nella misura necessaria per il
passaggio per riferimento. Il capitolo 05 tratta i puntatori in modo
completo: aritmetica dei puntatori, puntatori a puntatori, puntatori e
array, allocazione dinamica.

---

## File dell'esempio

| File | Tipo | Descrizione |
|------|------|-------------|
| `010-introduzione-ai-puntatori.c` | Concetto base | Operatori `&` e `*`, relazione tra variabile e puntatore |
| `020-modifica-tramite-puntatore.c` | Concetto base | Confronto per valore vs per riferimento; `incrementa`, `azzera` |
| `030-parametri-misti.c` | Concetto base | Parametri IN per valore e OUT per riferimento nella stessa funzione |
| `040-problema-scambio-valori.c` | Problema specifico | `scambia()` e ordinamento di tre interi |
| `040-problema-scambio-valori-analisi.md` | Analisi | Analisi del problema scambio valori |
| `050-problema-minmax.c` | Problema specifico | Min, max, media ed escursione di cinque misurazioni |
| `050-problema-minmax-analisi.md` | Analisi | Analisi del problema minmax |
| `060-problema-divisione-intera.c` | Problema specifico | Conversione secondi→HH:MM:SS e centesimi→EUR+cent |
| `060-problema-divisione-intera-analisi.md` | Analisi | Analisi del problema divisione intera |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-introduzione-ai-puntatori 010-introduzione-ai-puntatori.c
./010-introduzione-ai-puntatori

gcc -Wall -Wextra -o 020-modifica-tramite-puntatore 020-modifica-tramite-puntatore.c
./020-modifica-tramite-puntatore

gcc -Wall -Wextra -o 030-parametri-misti 030-parametri-misti.c
./030-parametri-misti

gcc -Wall -Wextra -o 040-problema-scambio-valori 040-problema-scambio-valori.c
./040-problema-scambio-valori

gcc -Wall -Wextra -o 050-problema-minmax 050-problema-minmax.c
./050-problema-minmax

gcc -Wall -Wextra -o 060-problema-divisione-intera 060-problema-divisione-intera.c
./060-problema-divisione-intera
```

---

## Output atteso

### 010-introduzione-ai-puntatori
```
=== Variabile e puntatore ===

Valore di eta:            25
Indirizzo di eta (&eta):  0x... (varia)

Valore di p (indirizzo):  0x... (uguale a &eta)
Valore puntato da p (*p): 25

=== Modifica tramite puntatore ===

Prima della modifica:  eta = 25
Dopo  *p = 30:         eta = 30

=== Riepilogo ===

  &eta = 0x...  (indirizzo della variabile)
  p    = 0x...  (stesso indirizzo nel puntatore)
  eta  = 30            (valore nella cella)
  *p   = 30            (stesso valore letto via puntatore)
```

### 020-modifica-tramite-puntatore
```
=== Confronto: per valore vs per riferimento ===

valore_a prima: 10
  [per valore]      dentro la funzione: n = 20
valore_a dopo:  10  ← invariato

valore_b prima: 10
  [per riferimento] dentro la funzione: *n = 20
valore_b dopo:  20  ← modificato dalla funzione

=== Incremento ===

contatore prima: 0
contatore dopo +5: 5
contatore dopo +3: 8

=== Azzeramento ===

saldo prima: 150.75
saldo dopo:  0.00
```

### 030-parametri-misti
```
=== Divisione intera ===

17 / 5 = 3  (resto 2)
100 / 7 = 14  (resto 2)
36 / 6 = 6  (resto 0)

=== Minimo e massimo ===

Valori: 8, 3, 11  →  min=3  max=11
Valori: -5, 0, -2  →  min=-5  max=0

=== Conversione temperatura ===

0 C  →  32.00 F  /  273.15 K
100 C  →  212.00 F  /  373.15 K
-273.15 C  →  -459.67 F  /  0.00 K
```

### 040-problema-scambio-valori
```
=== Scambio di due variabili ===

Prima dello scambio:  primo=42  secondo=7
Dopo  lo scambio:     primo=7  secondo=42

=== Ordinamento di tre numeri ===

Prima:   9  3  6
Dopo:    3  6  9

Prima:   1  1  1
Dopo:    1  1  1

Prima:   100  -5  42
Dopo:    -5  42  100
```

### 050-problema-minmax
```
=== Report temperatura giornaliera ===

Stazione A (citta'):
Misurazioni: 18.5  22.0  24.3  21.5  19.0
-------------------------------------------
Minimo:      18.5 C
Massimo:     24.3 C
Media:       21.1 C
Escursione:   5.8 C

Stazione B (montagna):
Misurazioni: 4.0  8.5  11.0  9.0  5.5
-------------------------------------------
Minimo:       4.0 C
Massimo:     11.0 C
Media:        7.6 C
Escursione:   7.0 C

Stazione C (costa):
Misurazioni: 21.0  23.5  25.0  24.0  22.0
-------------------------------------------
Minimo:      21.0 C
Massimo:     25.0 C
Media:       23.1 C
Escursione:   4.0 C
```

### 060-problema-divisione-intera
```
=== Conversione durate ===

      0 secondi  →  0h 00m 00s
     59 secondi  →  0h 00m 59s
     60 secondi  →  0h 01m 00s
   3600 secondi  →  1h 00m 00s
   3725 secondi  →  1h 02m 05s
   7384 secondi  →  2h 03m 04s
  86399 secondi  →  23h 59m 59s

=== Conversione importi ===

      0 centesimi →  0 EUR e 00 cent
     99 centesimi →  0 EUR e 99 cent
    100 centesimi →  1 EUR e 00 cent
   1275 centesimi →  12 EUR e 75 cent
   9999 centesimi →  99 EUR e 99 cent
  25000 centesimi →  250 EUR e 00 cent
```

---

## Errori comuni da evitare

```c
/* ERRORE 1: passare il valore invece dell'indirizzo */
void azzera(int *n) { *n = 0; }

int main(void) {
    int x = 5;
    azzera(x);    /* ERRORE: x non è un puntatore, serve &x */
    azzera(&x);   /* CORRETTO */
    return 0;
}
```

```c
/* ERRORE 2: dimenticare il * nella dereferenziazione */
void raddoppia(int *n)
{
    n = n * 2;    /* ERRORE: modifica il puntatore (l'indirizzo), non il valore */
    *n = *n * 2;  /* CORRETTO: modifica il valore puntato */
}
```

```c
/* ERRORE 3: puntatore non inizializzato (puntatore pendente) */
int *p;    /* p contiene un indirizzo casuale! */
*p = 42;   /* ERRORE GRAVE: scrittura in memoria arbitraria → crash */

int x;
int *p = &x;   /* CORRETTO: p punta a una variabile valida */
*p = 42;
```

```c
/* ERRORE 4: non passare & quando la funzione si aspetta un puntatore */
void leggi(int *n) { scanf("%d", n); }

int main(void) {
    int valore;
    leggi(valore);   /* ERRORE: valore non è un puntatore */
    leggi(&valore);  /* CORRETTO */
    return 0;
}
```

---

## Concetti collegati

- `02-parametri-e-return` – passaggio per valore e valore di ritorno
- `05-puntatori` – trattazione completa: aritmetica, puntatori e array, allocazione dinamica
- `05-puntatori/03-puntatori-e-funzioni` – approfondimento del passaggio per riferimento

---

## Esercizi proposti

1. **(Facile)** Scrivi una funzione `void incrementa_e_decrementa(int *a, int *b)`
   che incrementa `*a` di 1 e decrementa `*b` di 1. Verificane il comportamento
   nel main con `a=10` e `b=10`.

2. **(Medio)** Scrivi una funzione `void normalizza(double *min, double *max)`
   che, dati due valori, si assicura che `*min <= *max`: se necessario li
   scambia. Chiamala con coppie in ordine corretto e invertito.

3. **(Avanzato)** Scrivi una funzione `void scomponi_data(int giorni_totali,
   int *settimane, int *giorni_rimanenti)` che converte un numero di giorni
   in settimane e giorni residui. Estendila poi in `void scomponi_data_completa`
   che produce anche anni (365 giorni) e mesi (30 giorni approssimati).
