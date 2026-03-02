# Analisi – 050-problema-targa.c

## 1. Problema

Un sistema di gestione di un parcheggio deve analizzare le targhe dei veicoli
in ingresso per estrarne le componenti (lettere iniziali, cifre centrali,
lettere finali) e verificare che il formato corrisponda allo standard italiano
attuale introdotto nel 1994 (es. `FL519RX`).

---

## 2. Analisi generale e struttura dati

La targa è rappresentata come array di char di dimensione fissa (7 caratteri
+ terminatore). Le componenti estratte vengono memorizzate in array separati
per poter essere stampate e analizzate indipendentemente.

| Variabile          | Tipo     | Dimensione | Motivazione                                     |
|--------------------|----------|------------|-------------------------------------------------|
| `targa`            | `char[]` | 8          | 7 caratteri della targa + `'\0'`                |
| `lettere_iniziali` | `char[]` | 3          | 2 lettere iniziali + `'\0'`                     |
| `cifre`            | `char[]` | 4          | 3 cifre centrali + `'\0'`                       |
| `lettere_finali`   | `char[]` | 3          | 2 lettere finali + `'\0'`                       |
| `lunghezza`        | `int`    | —          | Contatore per verifica lunghezza                |
| `formato_valido`   | `int`    | —          | Flag generale: 1 = valido, 0 = non valido       |
| `cifre_valide`     | `int`    | —          | Flag verifica cifre: 1 = valide, 0 = non valide |
| `lettere_valide`   | `int`    | —          | Flag verifica lettere: 1 = valide, 0 non valide |

Struttura della targa italiana standard (dal 1994):
```
Indice:  0    1    2    3    4    5    6    7
         'F'  'L'  '5'  '1'  '9'  'R'  'X'  '\0'
          ^    ^    ^    ^    ^    ^    ^
        lett lett  cif  cif  cif lett lett
```

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Verifica della lunghezza

**a) Input**
La stringa `targa` dichiarata e inizializzata nel programma.

**b) Output**
Messaggio a video con la lunghezza rilevata e conferma o errore:
```
Lunghezza targa: 7 caratteri
```

**c) Variabili di supporto**
- `lunghezza` (`int`): contatore incrementato a ogni iterazione fino a `'\0'`.

**d) Vincoli**
- Il ciclo `while` si ferma al terminatore senza includerlo nel conteggio.
- La lunghezza corretta attesa è esattamente 7.

**e) Assunzioni**
- La stringa è sempre terminata da `'\0'` (garanzia dell'inizializzazione statica).
- Non si usa `strlen` per mostrare allo studente il conteggio manuale.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare lunghezza a 0.
2. Finché il carattere in posizione lunghezza non è '\0':
   a. Incrementare lunghezza.
3. Se lunghezza è diverso da 7:
   a. Impostare formato_valido a 0.
   b. Stampare messaggio di errore.
4. Altrimenti stampare la lunghezza rilevata.
```

---

### Caso d'uso 2 – Estrazione delle componenti

**a) Input**
La stringa `targa` (solo se `formato_valido` è 1).

**b) Output**
Le tre componenti stampate a video:
```
Componenti estratte:
  Lettere iniziali : FL
  Cifre centrali   : 519
  Lettere finali   : RX
```

**c) Variabili di supporto**
- `lettere_iniziali`, `cifre`, `lettere_finali`: array di char che ricevono
  i caratteri estratti e vengono terminati manualmente con `'\0'`.

**d) Vincoli**
- L'estrazione avviene solo se `formato_valido` è 1.
- Ogni array estratto deve essere terminato esplicitamente con `'\0'`.

**e) Assunzioni**
- Le posizioni dei campi nella targa sono fisse e note a priori.
- Non si usano funzioni di libreria (`strcpy`, `strncpy`) per mostrare
  l'accesso diretto tramite indice.

**f) Algoritmo in linguaggio naturale**
```
1. Se formato_valido è 0, saltare questo caso d'uso.
2. Copiare targa[0] e targa[1] in lettere_iniziali, aggiungere '\0'.
3. Copiare targa[2], targa[3], targa[4] in cifre, aggiungere '\0'.
4. Copiare targa[5] e targa[6] in lettere_finali, aggiungere '\0'.
5. Stampare le tre componenti.
```

---

### Caso d'uso 3 – Verifica del formato

**a) Input**
La stringa `targa` (solo se `formato_valido` è 1).

**b) Output**
Messaggio di validità o errore specifico:
```
Verifica formato:
  Formato: VALIDO (targa italiana standard dal 1994)
```

**c) Variabili di supporto**
- `lettere_valide` (`int`): flag che diventa 0 se una lettera non è maiuscola.
- `cifre_valide` (`int`): flag che diventa 0 se una cifra non è numerica.

**d) Vincoli**
- Le lettere devono essere comprese tra `'A'` e `'Z'` (ASCII 65-90).
- Le cifre devono essere comprese tra `'0'` e `'9'` (ASCII 48-57).
- La verifica avviene solo se `formato_valido` è 1.

**e) Assunzioni**
- Si considera solo il formato maiuscolo standard; le targhe speciali
  (es. forze armate, diplomatiche) non vengono gestite come casi separati.

**f) Algoritmo in linguaggio naturale**
```
1. Se formato_valido è 0, saltare questo caso d'uso.
2. Verificare che targa[0], targa[1], targa[5], targa[6] siano tra 'A' e 'Z'.
   Se almeno uno non lo è, impostare lettere_valide a 0.
3. Verificare che targa[2], targa[3], targa[4] siano tra '0' e '9'.
   Se almeno uno non lo è, impostare cifre_valide a 0.
4. Se entrambi i flag sono 1: stampare "VALIDO".
5. Se lettere_valide è 0: stampare errore sulle lettere.
6. Se cifre_valide è 0: stampare errore sulle cifre.
```
