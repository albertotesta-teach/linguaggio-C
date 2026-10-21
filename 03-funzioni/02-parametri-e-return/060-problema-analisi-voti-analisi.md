# Analisi – 060-problema-analisi-voti.c

## 1. Problema
Un registro scolastico raccoglie i voti di uno studente in cinque materie
(Matematica, Italiano, Inglese, Informatica, Fisica). Il programma calcola la
media aritmetica, individua il voto minimo e massimo, determina se lo studente
è promosso (tutti i voti ≥ 6) e assegna un giudizio testuale. Tutti i dati
vengono stampati in una scheda riepilogativa.

## 2. Analisi

### Input

| Variabile | Tipo | Descrizione |
|---|---|---|
| `mat`, `ita`, `ing`, `inf`, `fis` | int | Voti delle cinque materie (1–10) |

### Output
Una scheda con i cinque voti, la media (due decimali), il voto minimo e
massimo, il giudizio e l'esito (PROMOSSO / NON PROMOSSO).

Il giudizio dipende dalla media:

| Media | Giudizio |
|---|---|
| ≥ 9.0 | Eccellente |
| ≥ 8.0 | Ottimo |
| ≥ 7.0 | Buono |
| ≥ 6.0 | Sufficiente |
| < 6.0 | Insufficiente |

### Vincoli
- I voti sono compresi tra 1 e 10 (non verificato dal programma)
- Lo studente è promosso solo se **tutti** i voti sono almeno 6: basta un
  voto insufficiente per la non promozione, qualunque sia la media
- Le soglie del giudizio coprono tutte le medie possibili senza
  sovrapposizioni
- La media si calcola dividendo per `5.0`, per non perdere i decimali

### Assunzioni
- L'utente inserisce valori interi nell'intervallo corretto
- La soglia di sufficienza è la costante `VOTO_MINIMO_SUFFICIENZA` (6)
- I voti si passano come cinque parametri separati, perché gli array non
  sono ancora disponibili

### Variabili di supporto

| Variabile | Tipo | Descrizione |
|---|---|---|
| `media` | double | Media aritmetica, locale a `stampa_scheda` |
| `promosso` | int | 1 se promosso, 0 altrimenti, locale a `stampa_scheda` |

| Funzione | Firma | Descrizione |
|---|---|---|
| `calcola_media` | `double(int,int,int,int,int)` | Media dei cinque voti |
| `determina_promosso` | `int(int,int,int,int,int)` | 1 se tutti ≥ 6, altrimenti 0 |
| `voto_minimo` | `int(int,int,int,int,int)` | Voto più basso |
| `voto_massimo` | `int(int,int,int,int,int)` | Voto più alto |
| `stampa_giudizio` | `void(double)` | Giudizio testuale basato sulla media |
| `stampa_scheda` | `void(int,int,int,int,int)` | Scheda riepilogativa completa |

### Algoritmo in linguaggio naturale
1. Leggere i cinque voti.
2. Chiamare `stampa_scheda` con i cinque voti, che:
   a. stampa i voti;
   b. calcola e stampa media, voto minimo e voto massimo;
   c. chiama `stampa_giudizio(media)`, che sceglie il giudizio con una
      catena `if/else if` dalla soglia più alta alla più bassa;
   d. calcola `promosso` come AND dei cinque confronti con la soglia e
      stampa l'esito.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso. I voti sono nell'ordine Matematica,
Italiano, Inglese, Informatica, Fisica.

### Test 1 – Promosso con media alta
- **Input:** 8, 9, 7, 9, 8
- **Valori intermedi attesi:** media = 41 / 5.0 = 8.20
- **Output atteso (parte finale):**
```
Media:           8.20
Voto minimo:     7
Voto massimo:    9
Giudizio: Ottimo
Esito:           PROMOSSO
```

### Test 2 – Media sufficiente ma un voto insufficiente
- **Cosa si verifica:** basta un voto sotto 6 per la non promozione
- **Input:** 7, 5, 8, 6, 7
- **Output atteso:** media 6.60, minimo 5, massimo 8, giudizio Sufficiente,
  esito NON PROMOSSO

### Test 3 – Giudizio Eccellente
- **Cosa si verifica:** la soglia più alta della catena
- **Input:** 10, 9, 9, 10, 9
- **Output atteso:** media 9.40, giudizio Eccellente, esito PROMOSSO

### Test 4 – Media insufficiente
- **Cosa si verifica:** il ramo `else` finale del giudizio
- **Input:** 5, 4, 6, 5, 4
- **Output atteso:** media 4.80, minimo 4, massimo 6, giudizio Insufficiente,
  esito NON PROMOSSO
