# Analisi – 070-problema-cifratura-messaggi.c

## 1. Problema

Il club di crittografia confronta tre cifrari che agiscono su una lettera
alla volta: Cesare (+3), ROT13 (+13) e Atbash (alfabeto rovesciato). Per
ogni messaggio il programma mostra il testo cifrato con i tre metodi e
controlla che decifrandolo si torni all'originale. Una riga vuota termina.
Le trasformazioni hanno il tipo `Trasforma`, un puntatore a funzione.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `messaggio` | `char[100]` | Una riga di testo; la riga vuota termina |

### Output

- Per ogni metodo: nome, testo cifrato e `-> decifrato ok` (oppure
  `ERRATO` se la decifratura non restituisce l'originale).

### Vincoli

- `typedef char (*Trasforma)(char c);`
- Le lettere maiuscole e minuscole restano tali; gli altri caratteri non
  cambiano.
- Dopo la Z si ricomincia dalla A (aritmetica modulo 26); tornare indietro
  di 3 equivale ad andare avanti di 23.
- ROT13 e Atbash sono il proprio inverso.
- Una riga più lunga di 99 caratteri: si usano i primi 99 e il resto viene
  scartato.

### Assunzioni

- Il testo usa l'alfabeto inglese senza lettere accentate.
- A fine input il programma termina come con la riga vuota.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Trasforma` | `typedef char (*Trasforma)(char c);` | Funzione che trasforma un carattere |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `cifra`, `decifra` | `Trasforma[3]` | Funzioni per cifrare e decifrare, nello stesso ordine |
| `nomi` | `const char *[3]` | Nomi dei metodi |
| `copia` | `char[100]` | Testo su cui si lavora, per non perdere l'originale |
| `a_capo`, `resto` | `char *`, `int` | Gestione del `'\n'` e delle righe lunghe |
| `continua` | `int` | Flag di uscita |

| Funzione | Compito |
|----------|---------|
| `sposta(c, passo)` | Sposta una lettera nel suo alfabeto |
| `cesare`, `cesare_inverso`, `rot13` | Spostamenti di 3, 23 e 13 |
| `atbash(c)` | A ↔ Z, B ↔ Y, ... |
| `applica(testo, t)` | Applica `t` a ogni carattere del testo |

### Algoritmo in linguaggio naturale

1. Finché si continua:
   1. leggere una riga, togliere il `'\n'` o scartare il resto della riga;
   2. se la riga è vuota (o l'input è finito) terminare;
   3. per ogni metodo: copiare il messaggio, applicare `cifra[m]`,
      stampare, applicare `decifra[m]` e confrontare con l'originale.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Lettere al confine dell'alfabeto

- **Cosa si verifica:** il ritorno all'inizio dopo la Z e le maiuscole.
- **Input:** `Zebra xyz`, riga vuota
- **Output atteso:**
  ```
    Cesare  Cheud abc   -> decifrato ok
    ROT13   Mroen klm   -> decifrato ok
    Atbash  Avyiz cba   -> decifrato ok
  ```

### Test 2 – Punteggiatura

- **Cosa si verifica:** i caratteri non alfabetici restano invariati.
- **Input:** `Ciao, Mondo!`, riga vuota
- **Output atteso:**
  ```
    Cesare  Fldr, Prqgr!   -> decifrato ok
    ROT13   Pvnb, Zbaqb!   -> decifrato ok
    Atbash  Xrzl, Nlmwl!   -> decifrato ok
  ```

### Test 3 – Riga troppo lunga

- **Cosa si verifica:** il resto della riga non diventa un nuovo messaggio.
- **Input:** una riga di 120 cifre `0`, riga vuota
- **Output atteso:** tre righe con 99 zeri e `-> decifrato ok`, poi il
  programma termina.
