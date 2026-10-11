# 02 – Array di puntatori

## Concetto

Un **array di puntatori** è un array i cui elementi sono indirizzi. Il caso
più frequente è un elenco di stringhe costanti:

```c
const char *giorni[7] = {"lunedi", "martedi", "mercoledi", ...};

printf("%s", giorni[2]);      /* mercoledi */
printf("%c", giorni[2][0]);   /* m */
```

### Matrice di `char` o array di puntatori

| | `char g[7][10]` | `const char *g[7]` |
|-|-----------------|--------------------|
| che cosa contiene | 7 righe di 10 caratteri | 7 indirizzi |
| memoria | 70 byte, anche per "sab" | 56 byte + la lunghezza reale dei testi |
| modificare un carattere | sì: `g[0][0] = 'L'` | no: i letterali sono di sola lettura |
| cambiare un elemento | copiando i caratteri | `g[6] = "---"`: si cambia il puntatore |
| scambiare due elementi | copia di tutti i caratteri | scambio di due indirizzi |

### Puntatori a variabili e ad array

Un array di puntatori raccoglie in un elenco variabili separate o array di
lunghezze diverse:

```c
int *sensori[3] = {&aula, &laboratorio, &palestra};
*sensori[1] = 205;                 /* modifica laboratorio */

int *gruppi[4] = {rossi, blu, verdi, gialli};   /* 3, 5, 4, 2 voti */
gruppi[1][2]                       /* terzo voto del gruppo blu */
```

### Riordinare senza spostare i dati

Per cambiare l'ordine basta scambiare i puntatori: i testi e i valori
restano dove sono.

```c
void scambia(const char **a, const char **b)
{
    const char *temp = *a;

    *a = *b;
    *b = temp;
}

scambia(&ordine[0], &ordine[2]);
```

Gli elementi dell'array sono `const char *`, quindi i loro indirizzi sono
`const char **`. Allo stesso modo, un parametro `const char *v[]` equivale
a `const char **v`.

### Tabella di puntatori a funzione

```c
void (*comandi[4])(int *x, int *y, int *dir) = {avanti, indietro, destra, sinistra};

comandi[k](&x, &y, &dir);
```

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-array-di-stringhe-costanti.c` | `const char *giorni[7]` e `char giorni[7][10]`: memoria, uso, letterali |
| `020-array-di-puntatori-a-variabili.c` | `int *sensori[3]` verso tre variabili separate |
| `030-scambiare-puntatori.c` | Scambio di due elementi con `const char **`: i testi non si spostano |
| `040-problema-menu-del-giorno.c` | Menu della mensa con piatti di lunghezza diversa |
| `040-problema-menu-del-giorno-analisi.md` | Analisi di `040-problema-menu-del-giorno.c` |
| `050-problema-classifica-per-puntatori.c` | Classifica fatta di puntatori a nomi e tempi, corretta con scambi |
| `050-problema-classifica-per-puntatori-analisi.md` | Analisi di `050-problema-classifica-per-puntatori.c` |
| `060-problema-messaggi-di-errore.c` | Tabella di descrizioni indicizzata dal codice di errore |
| `060-problema-messaggi-di-errore-analisi.md` | Analisi di `060-problema-messaggi-di-errore.c` |
| `070-problema-tabella-di-comandi.c` | Array di puntatori a funzione per i comandi di un robot |
| `070-problema-tabella-di-comandi-analisi.md` | Analisi di `070-problema-tabella-di-comandi.c` |
| `080-problema-gruppi-di-lavoro.c` | `int *gruppi[4]` verso array di lunghezze diverse |
| `080-problema-gruppi-di-lavoro-analisi.md` | Analisi di `080-problema-gruppi-di-lavoro.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-array-di-stringhe-costanti 010-array-di-stringhe-costanti.c
./010-array-di-stringhe-costanti

gcc -Wall -Wextra -o 020-array-di-puntatori-a-variabili 020-array-di-puntatori-a-variabili.c
./020-array-di-puntatori-a-variabili

gcc -Wall -Wextra -o 030-scambiare-puntatori 030-scambiare-puntatori.c
./030-scambiare-puntatori

gcc -Wall -Wextra -o 040-problema-menu-del-giorno 040-problema-menu-del-giorno.c
./040-problema-menu-del-giorno

gcc -Wall -Wextra -o 050-problema-classifica-per-puntatori 050-problema-classifica-per-puntatori.c
./050-problema-classifica-per-puntatori

gcc -Wall -Wextra -o 060-problema-messaggi-di-errore 060-problema-messaggi-di-errore.c
./060-problema-messaggi-di-errore

gcc -Wall -Wextra -o 070-problema-tabella-di-comandi 070-problema-tabella-di-comandi.c
./070-problema-tabella-di-comandi

gcc -Wall -Wextra -o 080-problema-gruppi-di-lavoro 080-problema-gruppi-di-lavoro.c
./080-problema-gruppi-di-lavoro
```

---

## Output atteso

> Gli indirizzi stampati cambiano a ogni esecuzione.

### 010-array-di-stringhe-costanti
```
=== MEMORIA ===
  char matrice[7][10]:     70 byte (7 righe da 10)
  const char *giorni[7]:   56 byte di puntatori + 57 byte di testo

=== OGNI ELEMENTO E' UNA STRINGA ===
  giorni[0] = lunedi     brevi[0] = lun   iniziale giorni[0][0] = l   (6 lettere)
  giorni[1] = martedi    brevi[1] = mar   iniziale giorni[1][0] = m   (7 lettere)
  giorni[2] = mercoledi  brevi[2] = mer   iniziale giorni[2][0] = m   (9 lettere)
  giorni[3] = giovedi    brevi[3] = gio   iniziale giorni[3][0] = g   (7 lettere)
  giorni[4] = venerdi    brevi[4] = ven   iniziale giorni[4][0] = v   (7 lettere)
  giorni[5] = sabato     brevi[5] = sab   iniziale giorni[5][0] = s   (6 lettere)
  giorni[6] = domenica   brevi[6] = dom   iniziale giorni[6][0] = d   (8 lettere)

Orario: lun mar mer gio ven sab --- 
```

### 020-array-di-puntatori-a-variabili
```
=== LETTURA TRAMITE L'ARRAY ===
  aula         sensori[0] = 0x7ffef3b44c20   *sensori[0] = 18.5 gradi
  laboratorio  sensori[1] = 0x7ffef3b44c24   *sensori[1] = 21.4 gradi
  palestra     sensori[2] = 0x7ffef3b44c28   *sensori[2] = 16.2 gradi

=== DOPO UN'ORA, LETTURA DIRETTA DELLE VARIABILI ===
  aula 19.5, laboratorio 20.4, palestra 17.2
```

### 030-scambiare-puntatori
```
Ordine iniziale:
  1. Martina  (testo all'indirizzo 0x55c21630a008)
  2. Luca     (testo all'indirizzo 0x55c21630a010)
  3. Giorgia  (testo all'indirizzo 0x55c21630a015)
  4. Samuele  (testo all'indirizzo 0x55c21630a01d)

Dopo scambia(&ordine[0], &ordine[2]):
  1. Giorgia  (testo all'indirizzo 0x55c21630a015)
  2. Luca     (testo all'indirizzo 0x55c21630a010)
  3. Martina  (testo all'indirizzo 0x55c21630a008)
  4. Samuele  (testo all'indirizzo 0x55c21630a01d)

Dopo scambia(&ordine[1], &ordine[3]):
  1. Giorgia  (testo all'indirizzo 0x55c21630a015)
  2. Samuele  (testo all'indirizzo 0x55c21630a01d)
  3. Martina  (testo all'indirizzo 0x55c21630a008)
  4. Luca     (testo all'indirizzo 0x55c21630a010)

Gli indirizzi dei testi non sono cambiati: e' cambiato solo
quale elemento dell'array punta a ciascun testo.
```

### 040-problema-menu-del-giorno
*(output dipendente dall'input – esempio di sessione)*
```
Giorno (1-5, 0 per finire): 1
  --- Lunedi ---
  Primo:    Pasta al pomodoro e basilico
  Secondo:  Pollo arrosto
  Contorno: Insalata
Giorno (1-5, 0 per finire): 3
  --- Mercoledi ---
  Primo:    Minestrone di verdure
  Secondo:  Merluzzo al forno
  Contorno: Patate al forno
Giorno (1-5, 0 per finire): 7
  Giorno non valido.
Giorno (1-5, 0 per finire): 0
Nome piu' lungo per il tabellone: "Pasta al pomodoro e basilico" (28 caratteri)
```

### 050-problema-classifica-per-puntatori
*(output dipendente dall'input – esempio di sessione)*
```
  1. Pietro   30:30
  2. Alice    29:55
  3. Irene    31:52
  4. Tommaso  30:01
  5. Nadia    31:20
  Attenzione: tempi non in ordine.
Comando (S a b, Q): S 1 2
  1. Alice    29:55
  2. Pietro   30:30
  3. Irene    31:52
  4. Tommaso  30:01
  5. Nadia    31:20
  Attenzione: tempi non in ordine.
Comando (S a b, Q): S 2 4
  1. Alice    29:55
  2. Tommaso  30:01
  3. Irene    31:52
  4. Pietro   30:30
  5. Nadia    31:20
  Attenzione: tempi non in ordine.
Comando (S a b, Q): S 3 4
  1. Alice    29:55
  2. Tommaso  30:01
  3. Pietro   30:30
  4. Irene    31:52
  5. Nadia    31:20
  Attenzione: tempi non in ordine.
Comando (S a b, Q): S 4 5
  1. Alice    29:55
  2. Tommaso  30:01
  3. Pietro   30:30
  4. Nadia    31:20
  5. Irene    31:52
  Classifica in ordine di tempo.
Comando (S a b, Q): Q
```

### 060-problema-messaggi-di-errore
```
=== REGISTRO DELLA SETTIMANA ===
  evento  1  codice 1  filamento esaurito
  evento  2  codice 3  piatto non livellato
  evento  3  codice 1  filamento esaurito
  evento  4  codice 0  nessun errore
  evento  5  codice 5  file di stampa danneggiato
  evento  6  codice 9  codice sconosciuto
  evento  7  codice 1  filamento esaurito
  evento  8  codice 3  piatto non livellato
  evento  9  codice 4  porta aperta durante la stampa
  evento 10  codice 1  filamento esaurito

=== RIEPILOGO ===
  4x filamento esaurito
  2x piatto non livellato
  1x porta aperta durante la stampa
  1x file di stampa danneggiato
  1x codice sconosciuto
```

### 070-problema-tabella-di-comandi
*(output dipendente dall'input – esempio di sessione)*
```
Robot in (0, 0) verso nord
Comandi (A I D S, riga vuota per finire): AADA
  Robot in (1, 2) verso est
Comandi (A I D S, riga vuota per finire): SSAAX
  'X' ignorato
  Robot in (-1, 2) verso ovest
Comandi (A I D S, riga vuota per finire): 
```

### 080-problema-gruppi-di-lavoro
```
  Rossi   (3)  voti:  7  8  6       media 7.00
  Blu     (5)  voti:  9  7  8  8  6 media 7.60
  Verdi   (4)  voti:  6  6  7  5    media 6.00
  Gialli  (2)  voti: 10  8          media 9.00

Gruppo con la media piu' alta: Gialli (9.00)
Voto piu' alto della classe: 10, nel gruppo Gialli
```

---

## Errori comuni da evitare

**Modificare un letterale attraverso l'array**
```c
const char *brevi[7] = {"lun", ...};
brevi[0][0] = 'L';        /* errore: testo di sola lettura */
brevi[0] = "LUN";         /* corretto: si cambia il puntatore */
```

**Dimenticare `const`**
```c
char *giorni[7] = {"lunedi", ...};   /* compila, ma i testi restano non modificabili */
```

**Confondere `int *a[4]` e `int (*a)[4]`**
```c
int *a[4];       /* array di 4 puntatori a int */
int (*b)[4];     /* puntatore a un array di 4 int (sezione 03) */
```

**Perdere la lunghezza degli array puntati**
```c
int *gruppi[4] = {rossi, blu, verdi, gialli};
sizeof(gruppi[1])            /* 8: la dimensione di un puntatore, non del gruppo */
```
Le dimensioni vanno conservate in un array a parte.

**Scambiare le copie invece degli elementi**
```c
void scambia(const char *a, const char *b);   /* scambia solo le copie */
void scambia(const char **a, const char **b); /* corretto */
```

---

## Concetti collegati

- `01-doppio-puntatore` → `const char **` per modificare un elemento dell'array
- `03-puntatori-e-funzioni/03-puntatori-a-funzione` → puntatori a funzione
- `03-matrici-e-puntatori` → righe di lunghezza diversa
- `12-programmazione-avanzata/03-argomenti-da-linea-di-comando` → `char *argv[]`

---

## Esercizi proposti

1. In `010-array-di-stringhe-costanti.c` aggiungi l'array dei mesi e stampa
   il mese con il nome più lungo.

2. In `040-problema-menu-del-giorno.c` aggiungi il dolce del giorno.

3. In `050-problema-classifica-per-puntatori.c` aggiungi il comando `P a`
   che sposta il concorrente in posizione `a` all'ultimo posto (penalità).

4. In `060-problema-messaggi-di-errore.c` stampa anche il codice più
   frequente.

5. (Avanzato) In `070-problema-tabella-di-comandi.c` aggiungi il comando
   `T` (turbo: due caselle avanti) aggiungendo una funzione alla tabella.
