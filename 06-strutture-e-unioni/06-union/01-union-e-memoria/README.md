# 01 – Union e memoria

## Concetto

Una **union** si dichiara come una struct, ma i suoi campi cominciano
tutti allo stesso indirizzo e si sovrappongono:

```c
typedef union {
    int intero;
    double reale;
    char testo[8];
} Valore;
```

| `struct` | `union` |
|----------|---------|
| i campi stanno uno dopo l'altro | i campi condividono gli stessi byte |
| `sizeof` = somma dei campi (più il padding) | `sizeof` = il campo più grande (più l'allineamento) |
| contiene tutti i valori insieme | contiene **un** valore alla volta |

Scrivere un campo sovrascrive gli altri: ha senso leggere solo il campo
scritto per ultimo. Leggere un campo diverso compila, ma reinterpreta i
byte presenti e dà un valore senza legame con quello scritto.

### Stesso valore, due punti di vista

```c
#include <stdint.h>

typedef union {
    uint32_t valore;          /* il numero intero */
    uint8_t byte[4];          /* i suoi quattro byte */
} Parola;
```

`uint32_t` e `uint8_t` sono interi senza segno di esattamente 32 e 8 bit.
L'ordine dei byte dipende dalla macchina: **little-endian** (PC, Mac con
Apple Silicon) mette per primo il byte meno significativo, **big-endian**
il più significativo.

### Quando serve

- risparmiare memoria quando le alternative si escludono (un articolo è
  un componente *oppure* uno strumento);
- guardare gli stessi byte come numero e come sequenza di byte (indirizzi
  IP, colori, pacchetti di dati, bit di un `float`).

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-campi-sovrapposti.c` | La stessa terna di campi in una struct e in una union: dimensioni e indirizzi |
| `020-un-campo-alla-volta.c` | Tre scritture successive: dopo ognuna solo un campo ha senso |
| `030-vedere-i-byte.c` | `uint32_t` e `uint8_t[4]`: ordine dei byte e tipo di macchina |
| `040-problema-indirizzo-ip.c` | Indirizzo IP come numero e come quattro byte: rete, broadcast, stessa rete |
| `040-problema-indirizzo-ip-analisi.md` | Analisi di `040-problema-indirizzo-ip.c` |
| `050-problema-colore-rgba.c` | Canali di un colore indicizzati da un enum: schiarire, scurire, grigio |
| `050-problema-colore-rgba-analisi.md` | Analisi di `050-problema-colore-rgba.c` |
| `060-problema-anatomia-float.c` | Segno, esponente e mantissa di un `float` |
| `060-problema-anatomia-float-analisi.md` | Analisi di `060-problema-anatomia-float.c` |
| `070-problema-pacchetto-sensore.c` | Pacchetto di 8 byte letto come campi, con byte di controllo |
| `070-problema-pacchetto-sensore-analisi.md` | Analisi di `070-problema-pacchetto-sensore.c` |
| `080-problema-risparmio-memoria.c` | Inventario: struct con tutti i campi contro struct con union |
| `080-problema-risparmio-memoria-analisi.md` | Analisi di `080-problema-risparmio-memoria.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-campi-sovrapposti 010-campi-sovrapposti.c
./010-campi-sovrapposti

gcc -Wall -Wextra -o 020-un-campo-alla-volta 020-un-campo-alla-volta.c
./020-un-campo-alla-volta

gcc -Wall -Wextra -o 030-vedere-i-byte 030-vedere-i-byte.c
./030-vedere-i-byte

gcc -Wall -Wextra -o 040-problema-indirizzo-ip 040-problema-indirizzo-ip.c
./040-problema-indirizzo-ip

gcc -Wall -Wextra -o 050-problema-colore-rgba 050-problema-colore-rgba.c
./050-problema-colore-rgba

gcc -Wall -Wextra -o 060-problema-anatomia-float 060-problema-anatomia-float.c
./060-problema-anatomia-float

gcc -Wall -Wextra -o 070-problema-pacchetto-sensore 070-problema-pacchetto-sensore.c
./070-problema-pacchetto-sensore

gcc -Wall -Wextra -o 080-problema-risparmio-memoria 080-problema-risparmio-memoria.c
./080-problema-risparmio-memoria
```

---

## Output atteso

### 010-campi-sovrapposti
```
sizeof(int) = 4, sizeof(double) = 8, sizeof(char[8]) = 8
sizeof(TreValori) = 24 byte (i campi uno dopo l'altro)
sizeof(Valore)    = 8 byte (i campi sovrapposti)

Indirizzi nella struct:
  &s.intero = 0x7ffdb94bada0
  &s.reale  = 0x7ffdb94bada8
  &s.testo  = 0x7ffdb94badb0
Indirizzi nella union:
  &v.intero = 0x7ffdb94bad98
  &v.reale  = 0x7ffdb94bad98
  &v.testo  = 0x7ffdb94bad98
Nella union i tre indirizzi sono uguali.
```

### 020-un-campo-alla-volta
```
Dopo v.intero = 65:
  v.intero = 65
  v.reale  = 3.211426698e-322
  v.testo  = "A"

Dopo v.reale = 3.5:
  v.intero = 0
  v.reale  = 3.5
  v.testo  = ""

Dopo strcpy(v.testo, "ciao"):
  v.intero = 1868654947
  v.reale  = 3.50000083
  v.testo  = "ciao"
```

### 030-vedere-i-byte
```
valore = 0x0A0B0C0D
  byte[0] = 0x0D
  byte[1] = 0x0C
  byte[2] = 0x0B
  byte[3] = 0x0A

Con valore = 1, byte[0] vale 1: macchina little-endian.
Dopo byte[3] = 0xFF il valore e' 0xFF0B0C0D
```

### 040-problema-indirizzo-ip
*(output dipendente dall'input – tre reti)*
```
Indirizzo/prefisso e altro indirizzo (FINE): 192.168.10.11/24 192.168.10.200
  maschera  255.255.255.0
  rete      192.168.10.0
  broadcast 192.168.10.255
  in memoria: 0B 0A A8 C0 (byte[0] ... byte[3])
  192.168.10.200 e' nella stessa rete
Indirizzo/prefisso e altro indirizzo (FINE): 10.1.5.20/16 10.2.0.1
  maschera  255.255.0.0
  rete      10.1.0.0
  broadcast 10.1.255.255
  in memoria: 14 05 01 0A (byte[0] ... byte[3])
  10.2.0.1 NON e' nella stessa rete
Indirizzo/prefisso e altro indirizzo (FINE): 172.16.300.1/24 1.1.1.1
  Dati non validi.
Indirizzo/prefisso e altro indirizzo (FINE): FINE
```

### 050-problema-colore-rgba
*(output dipendente dall'input – esempio di sessione)*
```
Comando (S RRGGBB p, D RRGGBB p, G RRGGBB, Q): S 3366CC 40
  originale  #3366CCFF   R  51  G 102  B 204  A 255
  schiarito  #84A3E0FF   R 132  G 163  B 224  A 255
Comando (S RRGGBB p, D RRGGBB p, G RRGGBB, Q): D 3366CC 50
  originale  #3366CCFF   R  51  G 102  B 204  A 255
  scurito    #1A3366FF   R  26  G  51  B 102  A 255
Comando (S RRGGBB p, D RRGGBB p, G RRGGBB, Q): G 3366CC
  originale  #3366CCFF   R  51  G 102  B 204  A 255
  grigio     #626262FF   R  98  G  98  B  98  A 255
Comando (S RRGGBB p, D RRGGBB p, G RRGGBB, Q): G FF0000
  originale  #FF0000FF   R 255  G   0  B   0  A 255
  grigio     #4C4C4CFF   R  76  G  76  B  76  A 255
Comando (S RRGGBB p, D RRGGBB p, G RRGGBB, Q): X
  Comando sconosciuto.
Comando (S RRGGBB p, D RRGGBB p, G RRGGBB, Q): Q
```

### 060-problema-anatomia-float
*(output dipendente dall'input – sei numeri)*
```
Numero (FINE): 1
  1
  0 01111111 00000000000000000000000
  segno 0 (positivo), esponente 127 - 127 = 0, mantissa 0x000000
Numero (FINE): -2.5
  -2.5
  1 10000000 01000000000000000000000
  segno 1 (negativo), esponente 128 - 127 = 1, mantissa 0x200000
Numero (FINE): 0.1
  0.100000001
  0 01111011 10011001100110011001101
  segno 0 (positivo), esponente 123 - 127 = -4, mantissa 0x4CCCCD
Numero (FINE): 3.14159
  3.14159012
  0 10000000 10010010000111111010000
  segno 0 (positivo), esponente 128 - 127 = 1, mantissa 0x490FD0
Numero (FINE): 0
  0
  0 00000000 00000000000000000000000
  segno 0 (positivo), esponente 0 (zero), mantissa 0x000000
Numero (FINE): abc
  Non e' un numero.
Numero (FINE): FINE
```

### 070-problema-pacchetto-sensore
*(output dipendente dall'input – quattro pacchetti)*
```
Pacchetto (8 byte esadecimali, FINE): E1 00 5E 01 E8 0B 03 36
  sensore 3: 22.5 gradi, umidita' 35.0%, batteria 3048 mV
Pacchetto (8 byte esadecimali, FINE): DD FF 22 03 86 0B 07 99
  sensore 7: -3.5 gradi, umidita' 80.2%, batteria 2950 mV  CAMBIARE LE PILE
Pacchetto (8 byte esadecimali, FINE): E1 00 5E 01 E8 0B 03 37
  Pacchetto corrotto: controllo errato.
Pacchetto (8 byte esadecimali, FINE): E1 00
  Servono 8 byte.
Pacchetto (8 byte esadecimali, FINE): FINE
```

### 080-problema-risparmio-memoria
*(output dipendente dall'input – 500 articoli)*
```
sizeof(Componente) = 16, sizeof(Strumento) = 32, sizeof(Manuale) = 28
sizeof(ArticoloCompleto) = 96 byte
sizeof(ArticoloCompatto) = 48 byte
Esempio: R-0047, 4700 ohm +/- 5%

Articoli in inventario: 500
  struct con tutti i campi:    48000 byte
  struct con union:            24000 byte
  risparmio:                   24000 byte (50%)
```

*(output dipendente dall'input – numero non valido)*
```
sizeof(Componente) = 16, sizeof(Strumento) = 32, sizeof(Manuale) = 28
sizeof(ArticoloCompleto) = 96 byte
sizeof(ArticoloCompatto) = 48 byte
Esempio: R-0047, 4700 ohm +/- 5%

Articoli in inventario: 0
Numero non valido (da 1 a 100000).
```

---

## Errori comuni da evitare

**Leggere un campo diverso da quello scritto**
```c
v.reale = 3.5;
printf("%d", v.intero);            /* byte del double letti come int */
```

**Pensare che la union contenga tutti i campi**
```c
v.intero = 7;
v.reale = 2.5;                     /* v.intero non vale più 7 */
```

**Dare per scontato l'ordine dei byte**
```c
p.valore = 0x0A0B0C0D;
p.byte[0]                          /* 0x0D su little-endian, 0x0A su big-endian */
```

**Usare int al posto dei tipi a dimensione fissa**
```c
union { unsigned int n; unsigned char b[4]; }    /* int non è sempre 4 byte */
union { uint32_t n; uint8_t b[4]; }              /* corretto */
```

**Contare i byte di una struct senza controllare il padding**
```c
/* una struct di 2 + 2 + 2 + 1 + 1 byte può occupare di più */
if (sizeof(p.campi) != sizeof(p.grezzi)) { ... }   /* si controlla */
```

---

## Concetti collegati

- `02-struct` → dimensioni, padding e `sizeof`
- `01-introduzione/04-operatori` → spostamenti e maschere di bit
- `05-enum` → costanti usate come indici
- `02-union-con-etichetta` → ricordare quale campo è valido

---

## Esercizi proposti

1. In `010-campi-sovrapposti.c` aggiungi alla union un campo `char
   testo[20]` e verifica come cambia `sizeof`.

2. In `040-problema-indirizzo-ip.c` stampa anche quanti indirizzi utili
   (esclusi rete e broadcast) ha la rete.

3. In `050-problema-colore-rgba.c` aggiungi il comando `I RRGGBB` che
   stampa il colore inverso (255 meno ogni canale).

4. In `060-problema-anatomia-float.c` riconosci e segnala i valori
   speciali: esponente 255 con mantissa nulla (infinito) o non nulla
   (NaN).

5. (Avanzato) In `070-problema-pacchetto-sensore.c` aggiungi il comando
   per costruire un pacchetto da temperatura, umidità, batteria e
   sensore, calcolando il byte di controllo, e stampa gli 8 byte.
