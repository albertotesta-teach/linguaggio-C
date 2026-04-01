# Analisi – 060-problema-analisi-voti.c

## 1. Problema
Un registro scolastico raccoglie i voti di uno studente in cinque materie
(Matematica, Italiano, Inglese, Informatica, Fisica). Il programma calcola la
media aritmetica, individua il voto minimo e massimo, determina se lo studente
è promosso (tutti i voti ≥ 6) e assegna un giudizio testuale. Tutti i dati
vengono stampati in una scheda riepilogativa.

## 2. Analisi generale e struttura dati

| Costante | Valore | Descrizione |
|---|---|---|
| `VOTO_MINIMO_SUFFICIENZA` | 6 | Soglia di promozione |

| Variabile | Tipo | Descrizione |
|---|---|---|
| `mat`, `ita`, `ing`, `inf`, `fis` | int | Voti delle cinque materie (1–10) |
| `media` | double | Media aritmetica calcolata |
| `promosso` | int | Flag: 1 se promosso, 0 altrimenti |

| Funzione | Firma | Descrizione |
|---|---|---|
| `calcola_media` | `double(int,int,int,int,int)` | Media dei cinque voti |
| `determina_promosso` | `int(int,int,int,int,int)` | 1 se tutti ≥ 6, altrimenti 0 |
| `voto_minimo` | `int(int,int,int,int,int)` | Voto più basso |
| `voto_massimo` | `int(int,int,int,int,int)` | Voto più alto |
| `stampa_giudizio` | `void(double)` | Giudizio testuale basato sulla media |
| `stampa_scheda` | `void(int,int,int,int,int)` | Scheda riepilogativa completa |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Studente promosso con ottima media

**a) Input** – voti: 8, 9, 7, 9, 8

**b) Output**
```
SCHEDA DELLO STUDENTE
Matematica:      8
Italiano:        9
...
Media:           8.20
Voto minimo:     7
Voto massimo:    9
Giudizio:        Ottimo
Esito:           PROMOSSO
```

**c) Variabili di supporto** – `media` (double), `promosso` (int) calcolati dentro `stampa_scheda`

**d) Vincoli** – tutti i voti devono essere compresi tra 1 e 10 (assunzione, non validato)

**e) Assunzioni** – l'utente inserisce valori interi nell'intervallo corretto

**f) Algoritmo in linguaggio naturale**
1. Leggere i cinque voti
2. Chiamare `stampa_scheda` con i cinque voti
3. Dentro `stampa_scheda`: calcolare media, min, max, promosso
4. Chiamare `stampa_giudizio(media)` per il giudizio testuale
5. Stampare l'esito in base al flag `promosso`

### Caso d'uso 2 – Studente non promosso (un voto insufficiente)

**a) Input** – voti: 7, 5, 8, 6, 7

**b) Output** – media 6.60, giudizio Sufficiente, esito NON PROMOSSO

**c) Variabili di supporto** – `promosso = 0` perché Italiano (5) < 6

**d) Vincoli** – anche un solo voto sotto la soglia determina la non promozione

**e) Assunzioni** – la soglia di sufficienza è definita con `#define` e non varia a runtime

**f) Algoritmo in linguaggio naturale**
1. `determina_promosso` valuta la congiunzione logica di tutti i confronti
2. Se anche uno solo è falso, il risultato è 0 (non promosso)
3. `stampa_scheda` stampa `NON PROMOSSO`

### Caso d'uso 3 – Giudizio testuale dalla media

**a) Input** – media 9.4

**b) Output** – `Giudizio: Eccellente`

**c) Variabili di supporto** – la media viene passata come parametro a `stampa_giudizio`

**d) Vincoli** – le soglie devono coprire tutti i valori possibili (1.0–10.0) senza sovrapposizioni

**e) Assunzioni** – la media è sempre compresa tra 1.0 e 10.0

**f) Algoritmo in linguaggio naturale**
1. Se media ≥ 9.0 → Eccellente
2. Altrimenti se media ≥ 8.0 → Ottimo
3. Altrimenti se media ≥ 7.0 → Buono
4. Altrimenti se media ≥ 6.0 → Sufficiente
5. Altrimenti → Insufficiente
