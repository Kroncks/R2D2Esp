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

## Github
[GitHub](https://github.com/Kroncks/R2D2Esp)
