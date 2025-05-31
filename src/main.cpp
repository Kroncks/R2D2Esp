#include <WiFi.h>
#include <WebServer.h>
#include <esp_wifi.h> // Pour esp_wifi_ap_get_sta_list
#include <lwip/inet.h> // Pour IP conversion

#include "pages.h"

#define LED 2

const char* ssid = "R2D2";  
const char* password = "BONSOIRS";     


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



WebServer server(80);

//Pages 

void handleReadme() {
  server.send(200, "text/html", PAGE_readme);
}

void handleRoot() {
  server.send(200, "text/html", PAGE_root);
}

void handleBonsoir() {
  server.send(200, "text/html", PAGE_bonsoir);
}

void handleControls() {
    server.send(200, "text/html", PAGE_controls);
}


// gestion des commandes entrantes 

void handleComand() {
    if (server.hasArg("command")) {          // Vérifie si une commande a été envoyée
        String command = server.arg("command");  // Récupère la commande

        // les moteurs sont inversés, merci la meca 


        if (command == "test"){ // petit test avec 
            digitalWrite(LED,HIGH);
        } else if (command == "diaggauche") {           // Commande pour tourner diagonale gauche
            Serial2.write(63-puissance_tourne_large);  // Moteur 1 avance +
            Serial2.write(191-puissance_tourne_court); // Moteur 2 avance -

        } else if (command == "gauche") {           // Commande pour tourner à gauche
            Serial2.write(63-puissance_rotation);  // Moteur 1 avance
            Serial2.write(193+puissance_rotation); // Moteur 2 recule

        }else if (command == "diagdroite") {           // Commande pour tourner diagonale droite
            Serial2.write(63-puissance_tourne_court);  // Moteur 1 avance -
            Serial2.write(191-puissance_tourne_large); // Moteur 2 avance +

        } else if (command == "droite") {    // Commande pour tourner à droite
            Serial2.write(65+puissance_rotation);  // Moteur 1 recule 
            Serial2.write(191-puissance_rotation); // Moteur 2 avance 

        } else if (command == "reculer") {   // Commande pour reculer
            Serial2.write(65+puissance_recul);  // Moteur 1 recule
            Serial2.write(193+puissance_recul); // Moteur 2 recule

        } else if (command == "recdroite") {   // Commande pour reculer droite diag
            Serial2.write(65+puissance_tourne_recul_court);  // Moteur 1 recule -
            Serial2.write(193+puissance_tourne_recul_large); // Moteur 2 recule +

        }else if (command == "recgauche") {   // Commande pour diagonale gauche reculer
            Serial2.write(65+puissance_tourne_recul_large);  // Moteur 1 recule +
            Serial2.write(193+puissance_tourne_recul_court); // Moteur 2 recule -

        }else if (command == "avancer") {   // Commande pour avancer
            Serial2.write(63-puissance_avant);  // Moteur 1 avance 
            Serial2.write(191-puissance_avant); // Moteur 2 avance

        } else if (command == "stop") {      // Commande pour arrêter les moteurs
            Serial2.write(64);  // Stop moteur 1
            Serial2.write(192); // Stop moteur 2

            digitalWrite(LED,LOW); //eteins la led de controle

        }else {                             // Si la commande est inconnue
            server.send(400, "text/plain", "Commande invalide");
            return;
        }

        // Confirmation d'exécution de la commande
        server.send(200, "text/plain", "Commande exécutée");
    } else {                                 // Si aucune commande n'a été envoyée
        server.send(400, "text/plain", "Commande manquante");
    }
}





//=====



// Configuration initiale 
void setup() {
    pinMode(LED,OUTPUT); // led de controle

    Serial2.begin(9600); // RX = 16 / TX = 17

    WiFi.mode(WIFI_AP);                 // Configure l'ESP32 en wifi 
    WiFi.softAP(ssid, password, 1);     
    
    server.on("/", HTTP_GET, handleRoot);
    server.on("/bonsoir", HTTP_GET, handleBonsoir);
    server.on("/readme", HTTP_GET, handleReadme);

    server.on("/controls", HTTP_GET, handleControls); // affichage 
    server.on("/comand", HTTP_POST, handleComand); // envoi des comandes 
    
    server.begin();

    delay(500);
    Serial2.write(64);  // Stop moteur 1
    Serial2.write(192); // Stop moteur 2
}

void loop() {
  server.handleClient();
}