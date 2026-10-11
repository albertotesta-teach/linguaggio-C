# Analisi – 050-problema-mcd-euclide.c

## 1. Problema

Calcolare il massimo comun divisore (MCD) di due interi positivi con
l'algoritmo di Euclide, mostrando i passaggi, e ricavare il minimo comune
multiplo (mcm). Esempio applicativo: con 84 cioccolatini e 60 caramelle si
possono preparare al massimo MCD(84, 60) = 12 sacchetti uguali.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `primo`, `secondo` | `int` | Numeri inseriti, conservati per la stampa finale |
| `a`, `b` | `int` | Coppia di lavoro aggiornata a ogni passo |
| `resto` | `int` | `a % b` |
| `passo` | `int` | Contatore dei passi |
| `mcd`, `mcm` | `int` | Risultati |

Proprietà usata: `MCD(a, b) = MCD(b, a % b)` e `MCD(a, 0) = a`.
Il numero di passi non è noto in anticipo: la struttura adatta è il `while`.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Due numeri con divisori comuni

**a) Input** – 84 e 60

**b) Output** – tabella dei passi (84, 60, 24), (60, 24, 12), (24, 12, 0);
MCD = 12 in 3 passi; mcm = 420

**c) Variabili di supporto** – `a`, `b`, `resto`, `passo`

**d) Vincoli** – il ciclo termina quando `b` vale 0; a ogni passo `b`
diminuisce, quindi la terminazione è garantita

**e) Assunzioni** – i numeri sono positivi

**f) Algoritmo in linguaggio naturale**
1. Leggere il primo numero ripetendo la richiesta finché non è positivo;
   lo stesso per il secondo.
2. Copiare i numeri in `a` e `b`, azzerare `passo`.
3. Finché `b` è diverso da 0: calcolare `resto = a % b`, incrementare
   `passo`, stampare la riga, porre `a = b` e `b = resto`.
4. `mcd = a`; `mcm = primo / mcd * secondo`.
5. Stampare i risultati; se il MCD vale 1 segnalare che i numeri sono primi
   tra loro.

### Caso d'uso 2 – Numeri primi tra loro

**a) Input** – 17 e 5

**b) Output** – MCD = 1, mcm = 85, "I due numeri sono primi tra loro."

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – nessuno in più

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Primo numero minore del secondo

**a) Input** – 60 e 84

**b) Output** – MCD = 12; il primo passo ha resto 60 e scambia i numeri

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – non serve ordinare i numeri prima del ciclo

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 4 – Valore non positivo

**a) Input** – 0 o un numero negativo

**b) Output** – la richiesta viene ripetuta

**c) Variabili di supporto** – nessuna

**d) Vincoli** – con `b = 0` iniziale il MCD sarebbe banale, con valori
negativi `%` darebbe resti negativi

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 1.
