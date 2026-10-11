# Analisi – 080-problema-cifrario-vigenere.c

## 1. Problema

Due studenti vogliono scambiarsi messaggi cifrati con il cifrario di
Vigenère. Ogni lettera del messaggio viene spostata in avanti nell'alfabeto
del valore della lettera corrispondente della chiave (A = 0, … Z = 25), che
si ripete ciclicamente. Le lettere mantengono maiuscola o minuscola, gli
altri caratteri restano invariati. Il programma cifra ogni frase e, come
verifica, la decifra di nuovo.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `chiave` | `char[]` | 20 | Parola chiave, portata in maiuscolo |
| `messaggio` | `char[]` | 80 | Frase da cifrare |
| `cifrato`, `decifrato` | `char[]` | 80 | Risultati |

| Funzione | Compito |
|----------|---------|
| `chiave_valida` | Chiave non vuota con sole lettere (`isalpha`) |
| `vigenere` | Cifra (`verso` = 1) o decifra (`verso` = -1) |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Chiave non valida

**a) Input** – `luna 2`, poi `luna`

**b) Output** – "Chiave non valida."; "Chiave in uso: LUNA"

**c) Variabili di supporto** – esito di `chiave_valida`

**d) Vincoli** – la chiave deve contenere almeno una lettera e solo lettere

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ripetere la richiesta con un
`do-while` finché la chiave è valida, poi convertirla in maiuscolo con `toupper`.

### Caso d'uso 2 – Cifratura

**a) Input** – `CIAO MONDO` con chiave `LUNA`

**b) Output** – `NCNO XIADZ`

**c) Variabili di supporto** – `k` (indice nella chiave), `spostamento`, `base`

**d) Vincoli** – `k` avanza solo sulle lettere: gli spazi non consumano la chiave

**e) Assunzioni** – lettere senza accenti

**f) Algoritmo in linguaggio naturale**
1. Per ogni carattere: se è una lettera, `base` = 'A' o 'a' a seconda di `isupper`.
2. `spostamento = chiave[k % lunghezza] - 'A'`.
3. Nuova lettera = `base + (c - base + spostamento) % 26`; incrementare `k`.
4. Gli altri caratteri si copiano invariati.

### Caso d'uso 3 – Decifratura e verifica

**a) Input** – il testo cifrato di `Ci vediamo alle 16, in biblioteca!`

**b) Output** – il testo originale e "(uguale all'originale)"

**c) Variabili di supporto** – `verso` = -1

**d) Vincoli** – sottraendo si può scendere sotto 0: si aggiunge 26 prima del `% 26`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come la cifratura con lo
spostamento negativo; poi `strcmp` tra decifrato e messaggio originale.
