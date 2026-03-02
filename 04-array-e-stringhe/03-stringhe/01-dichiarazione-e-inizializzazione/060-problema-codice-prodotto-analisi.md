# Analisi – 060-problema-codice-prodotto.c

## 1. Problema

Un sistema di magazzino utilizza codici prodotto nel formato `CAT-NNN-XX`.
Il programma deve estrarre le componenti di un codice (categoria, progressivo,
variante) accedendo ai caratteri per indice, e verificare se due prodotti
appartengono alla stessa categoria confrontando i caratteri uno a uno.

---

## 2. Analisi generale e struttura dati

Il codice prodotto ha lunghezza fissa di 10 caratteri più il terminatore.
Le posizioni dei campi e dei separatori sono note e costanti.

| Variabile        | Tipo     | Dimensione | Motivazione                                      |
|------------------|----------|------------|--------------------------------------------------|
| `prodotto1`      | `char[]` | 11         | Codice prodotto (10 caratteri + `'\0'`)          |
| `prodotto2`      | `char[]` | 11         | Codice prodotto (10 caratteri + `'\0'`)          |
| `prodotto3`      | `char[]` | 11         | Codice prodotto (10 caratteri + `'\0'`)          |
| `categoria`      | `char[]` | 4          | 3 lettere della categoria + `'\0'`               |
| `progressivo`    | `char[]` | 4          | 3 cifre del progressivo + `'\0'`                 |
| `variante`       | `char[]` | 3          | 2 lettere della variante + `'\0'`                |
| `i`              | `int`    | —          | Indice per il ciclo di confronto                 |
| `stessa_categoria` | `int`  | —          | Flag: 1 = stessa categoria, 0 = categorie diverse|

Struttura del codice prodotto (indici):
```
Indice:  0    1    2    3    4    5    6    7    8    9    10
         'E'  'L'  'E'  '-'  '0'  '4'  '2'  '-'  'B'  'L'  '\0'
          ^    ^    ^    ^    ^    ^    ^    ^    ^    ^
         categoria  sep  progressivo   sep  variante
```

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Estrazione delle componenti

**a) Input**
La stringa `prodotto1` dichiarata e inizializzata nel programma.

**b) Output**
Le tre componenti stampate a video:
```
Analisi Prodotto 1 (ELE-042-BL):
  Categoria   : ELE
  Progressivo : 042
  Variante    : BL
```

**c) Variabili di supporto**
- `categoria`, `progressivo`, `variante`: array di char che ricevono i
  caratteri estratti e sono terminati manualmente con `'\0'`.

**d) Vincoli**
- I separatori agli indici 3 e 7 vengono ignorati durante l'estrazione.
- Ogni array estratto deve essere terminato esplicitamente con `'\0'`.

**e) Assunzioni**
- Le posizioni dei campi nel codice prodotto sono fisse e note a priori.
- Non si usano funzioni di libreria per mostrare l'accesso diretto per indice.

**f) Algoritmo in linguaggio naturale**
```
1. Copiare prodotto1[0], [1], [2] in categoria; aggiungere '\0'.
2. Copiare prodotto1[4], [5], [6] in progressivo; aggiungere '\0'.
3. Copiare prodotto1[8], [9] in variante; aggiungere '\0'.
4. Stampare le tre componenti.
```

---

### Caso d'uso 2 – Confronto delle categorie tra due prodotti

**a) Input**
Due stringhe codice prodotto da confrontare (es. `prodotto1` e `prodotto2`,
poi `prodotto1` e `prodotto3`).

**b) Output**
Esito del confronto per ciascuna coppia:
```
Confronto categorie:
  ELE-042-BL e ELE-107-RO: STESSA categoria (ELE)
  ELE-042-BL e ALI-003-VE: categorie DIVERSE
```

**c) Variabili di supporto**
- `i` (`int`): indice che scorre le posizioni 0, 1, 2 dei due codici.
- `stessa_categoria` (`int`): flag inizializzato a 1, impostato a 0 alla
  prima differenza trovata.

**d) Vincoli**
- Il confronto riguarda solo i primi 3 caratteri (la categoria).
- Il ciclo si interrompe naturalmente quando `i` raggiunge 3 oppure
  quando `stessa_categoria` diventa 0 (condizione composta nel `while`).
- Non si usa `strcmp` per mantenere il confronto manuale carattere per carattere.

**e) Assunzioni**
- Entrambi i codici prodotto hanno formato valido.
- Le categorie sono sempre in maiuscolo.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare i a 0 e stessa_categoria a 1.
2. Finché i < 3 E stessa_categoria è 1:
   a. Se prodottoA[i] è diverso da prodottoB[i]:
      - Impostare stessa_categoria a 0.
   b. Incrementare i.
3. Se stessa_categoria è 1: stampare "STESSA categoria".
4. Altrimenti: stampare "categorie DIVERSE".
```

---

### Caso d'uso 3 – Verifica dell'integrità del formato

**a) Input**
La stringa `prodotto1`.

**b) Output**
Messaggio di conferma o errore sul formato:
```
Verifica integrità formato ELE-042-BL:
  Separatori '-' in posizione corretta: formato VALIDO
```

**c) Variabili di supporto**
Nessuna variabile aggiuntiva: il controllo è un confronto diretto sugli indici 3 e 7.

**d) Vincoli**
- I separatori devono trovarsi esattamente agli indici 3 e 7.
- Il carattere atteso è `'-'` (ASCII 45).

**e) Assunzioni**
- La stringa ha lunghezza sufficiente (almeno 8 caratteri) per accedere
  agli indici 3 e 7 senza uscire dai limiti dell'array.

**f) Algoritmo in linguaggio naturale**
```
1. Verificare che prodotto1[3] sia uguale a '-'.
2. Verificare che prodotto1[7] sia uguale a '-'.
3. Se entrambe le condizioni sono vere: stampare "formato VALIDO".
4. Altrimenti: stampare messaggio di errore.
```
