# Controle du R2D2 par ESP32 

## Acceder a l'interface de commande
- Allumer l'ESP32
- Se connecter au reseau R2D2 avec le code : `BONSOIRS`
- Ouvrir http://192.168.4.1/ sur un navigateur
- Cliquer sur le bouton `Controles`

## Verifier que la connexion fonctionne 
- Appuyer sur le bouton au centre de la croix directionelle
- Verifier qu'une LED bleu s'allume bien sur l'ESP32

## Connexion de l'ESP32 au driver moteur Sabertooth
- Relier la pin TX2 de l'ESP32 a l'entree S1 du Sabertooth
- Ne pas modifier les reglages du Sabertooth ( 010100 -> Serial 9600 )

## Connexion des moteurs au Sabertooth 
- Connecter le moteur droit sur M1
- Connecter le moteur gauche sur M2

## Modifier la valeur de la vitesse
- Ouvrir le code dans une IDE et ouvrir `src/main.cpp`
- Modifier les valeures des puissances de la ligne 13 à 28
```cpp
// =========   puissance (0-62)   =========

// Avancer / Reculer
const int puissance_avant = 40; // puissance pour avancer droit
const int puissance_recul = 30; // puissance pour reculler droit

// Rotation
const int puissance_rotation = 20; // puissance des roues pour tourner sur soi meme 

// tourner en diagonale 
const int puissance_tourne_large = 30; // puissance de la roue externe au virage 
const int puissance_tourne_court = 20; // puissance de la roue intenre au virage 

// reculer en diagonale 
const int puissance_tourne_recul_large = 30; // puissance de la roue externe au virage
const int puissance_tourne_recul_court = 20; // puissance de la roue intenre au virage

// ==========================================
```
- Televerser le code sur l'ESP32

## Github
[GitHub](https://github.com/Kroncks/R2D2Esp)
