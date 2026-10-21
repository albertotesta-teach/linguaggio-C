# Analisi – 050-problema-mcd-euclide.c

## 1. Problema

Calcolare il massimo comun divisore (MCD) di due interi positivi con
l'algoritmo di Euclide, mostrando i passaggi, e ricavare il minimo comune
multiplo (mcm). Esempio applicativo: con 84 cioccolatini e 60 caramelle si
possono preparare al massimo MCD(84, 60) = 12 sacchetti uguali.

## 2. Analisi

### Input

| Variabile          | Tipo  | Significato                                        |
|--------------------|-------|----------------------------------------------------|
| `primo`, `secondo` | `int` | Numeri inseriti, conservati per la stampa finale   |

### Output
La tabella dei passi (valori di `a`, `b` e del resto a ogni passo), il MCD
con il numero di passi, il mcm e, se il MCD vale 1, l'avviso che i due
numeri sono primi tra loro.

### Vincoli
- Entrambi i numeri sono positivi: la richiesta si ripete finché non lo
  sono (con `b = 0` iniziale il MCD sarebbe banale, con valori negativi
  `%` darebbe resti negativi)
- Il ciclo termina quando `b` vale 0; a ogni passo `b` diminuisce, quindi
  la terminazione è garantita
- Non serve ordinare i numeri prima del ciclo: se il primo è minore del
  secondo, il primo passo li scambia

### Assunzioni
- L'utente inserisce numeri interi
- Il mcm sta in un `int`

### Variabili di supporto

| Variabile    | Tipo  | Significato                        |
|--------------|-------|------------------------------------|
| `a`, `b`     | `int` | Coppia di lavoro aggiornata a ogni passo |
| `resto`      | `int` | `a % b`                            |
| `passo`      | `int` | Contatore dei passi                |
| `mcd`, `mcm` | `int` | Risultati                          |

Proprietà usata: `MCD(a, b) = MCD(b, a % b)` e `MCD(a, 0) = a`.
Il numero di passi non è noto in anticipo: la struttura adatta è il `while`.

### Algoritmo in linguaggio naturale
1. Leggere il primo numero ripetendo la richiesta finché non è positivo;
   lo stesso per il secondo.
2. Copiare i numeri in `a` e `b`, azzerare `passo`.
3. Finché `b` è diverso da 0: calcolare `resto = a % b`, incrementare
   `passo`, stampare la riga, porre `a = b` e `b = resto`.
4. `mcd = a`; `mcm = primo / mcd * secondo`.
5. Stampare i risultati; se il MCD vale 1 segnalare che i numeri sono primi
   tra loro.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Due numeri con divisori comuni
- **Input:** 84 e 60
- **Output atteso:** tabella dei passi (84, 60, 24), (60, 24, 12), (24, 12, 0);
  MCD = 12 in 3 passi; mcm = 420

### Test 2 – Numeri primi tra loro
- **Input:** 17 e 5
- **Output atteso:** MCD = 1, mcm = 85, "I due numeri sono primi tra loro."

### Test 3 – Primo numero minore del secondo
- **Cosa si verifica:** il primo passo scambia i numeri senza bisogno di
  ordinarli
- **Input:** 60 e 84
- **Output atteso:** il primo passo ha resto 60; MCD = 12

### Test 4 – Valore non positivo
- **Input:** 0 oppure un numero negativo
- **Output atteso:** la richiesta viene ripetuta
