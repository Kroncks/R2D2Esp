#include <WiFi.h>
#include <WebServer.h>
#include <esp_wifi.h> // Pour esp_wifi_ap_get_sta_list
#include <lwip/inet.h> // Pour IP conversion

#define LED 2

const char* ssid = "R2D2";  
const char* password = "BONSOIRS";     


// =========   puissance (0-62)   =========   
const int puissance_avant = 40; 
const int puissance_recul = 30;

const int puissance_rotation = 20;

const int puissance_tourne_large = 30;
const int puissance_tourne_court = 20;

const int puissance_tourne_recul_large = 30;
const int puissance_tourne_recul_court = 20;
// ==========================================



WebServer server(80);

//Pages 

void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
    <!DOCTYPE html><html lang="fr"><head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>R2D2</title>
    </head><body>
    <h1>Bonsoir jeune Padawan !</h1>
    <button onclick="window.location.href = '/controls';">Controles</button>
    <p>R2D2 roulera-t-il pour le 3 juin ?</p>
    <p>Ayaaaaaaa...</p>
    </body></html>
  )rawliteral");
}


void handleBonsoir() {
  server.send(200, "text/html", R"rawliteral(
    <!DOCTYPE html><html lang="fr"><head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Bonsoir</title>
    </head><body>
    <h1>Bonsoir</h1>
    <button onclick="window.location.href = '/';">Home</button>
    <div style="font-family: SFMono-Regular,Menlo,Monaco,Consolas,Liberation Mono,Courier New,monospace;font-size:14px;white-space: pre;background-color: #ffffff; color: #000000;"><div>                           /~\    Bonsoir Paris</div><div>                          (O O) _/             </div><div>                          _\=/_                </div><div> Bjeep Bjeep Bjoup       /  _  \               </div><div>      \_  ___           //|/.\|\\              </div><div>         / ()\         ||  \_/  ||             </div><div>       _|_____|_       || |\ /| ||             </div><div>      | | === | |       # \_ _/ #              </div><div>      |_|  O  |_|         | | |                </div><div>       ||  O  ||          | | |                </div><div>       ||__*__||          []|[]                </div><div>      |~ \___/ ~|         | | |                </div><div>______/=\_/=\_/=\________/_]_[_\_____          </div></div>
    </body></html>
  )rawliteral");
}


void handleControls() {
    server.send(200, "text/html", R"rawliteral(
    <!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>Contrôle du Robot</title>
  <style>
    /* Réinitialisation des marges et du padding */
    html, body {
      margin: 0;
      padding: 0;
      height: 100%;
      overflow: hidden;
    }
    
    /* Fond fixe */
    .background {
      position: fixed;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      background: linear-gradient(to right,rgb(49, 193, 203), #02B8C5);
      z-index: -1; /* Placer l'arrière-plan derrière le contenu */
    }

    /* Container principal */
    .container {
      height: 100vh;
      width: 100%;
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      color: white;
      text-align: center;
      padding: 10px;
      box-sizing: border-box;
    }

    /* Titre */
    h1 {
      margin: 0;
      font-size: 24px;
      font-weight: bold;
    }

    /* Flèches directionnelles */
    .direction-buttons {
      display: flex;
      flex-direction: column;
      align-items: center;
      margin-top: 20px;
    }

    .button-row {
      display: flex;
      justify-content: center;
    }

    .button {
      background-color:rgb(86, 86, 86);
      color: #fff;
      font-size: 20px;
      padding: 10px;
      border: none;
      border-radius: 5px;
      cursor: pointer;
      margin: 5px;
      width: 50px;
      height: 50px;
      text-align: center;
    }

    .button:hover {
      background-color:rgb(18, 150, 150);
    }

    /* Adaptation pour les petits écrans */
    @media (max-width: 768px) {
      h1 {
        font-size: 20px;
      }

      .button {
        font-size: 16px;
        padding: 8px;
        width: 40px;
        height: 40px;
      }
    }
  </style>
</head>
<body>
  <div class="background"></div>
  <h1>Que la force soit avec toi !</h1>
  <button onclick="window.location.href = '/';">Home</button>
  <div class="container">
    <h1>Contrôle du Robot</h1>
    <div class="direction-buttons">
      <div class="button-row">
        <button class="button" id="diagleft">↖︎</button>
        <button class="button" id="up">↑</button>
        <button class="button" id="diagright">↗︎</button>
      </div>
      <div class="button-row">
        <button class="button" id="left">←</button>
        <button class="button" id="test">O</button>
        <button class="button" id="right">→</button>
      </div>
      <div class="button-row">
        <button class="button" id="recleft">↙︎</button>
        <button class="button" id="down">↓</button>
        <button class="button" id="recright">↘︎</button>
      </div>
    </div>
  </div>

  <script>
    // Références aux éléments
    const testButton = document.getElementById('test');
    const diagleftButton = document.getElementById('diagleft');
    const upButton = document.getElementById('up');
    const diagrightButton = document.getElementById('diagright');
    const downButton = document.getElementById('down');
    const leftButton = document.getElementById('left');
    const recleftButton = document.getElementById('recleft');
    const rightButton = document.getElementById('right');
    const recrightButton = document.getElementById('recright');

    // Fonction pour envoyer une commande
    function sendCommand(command) {
      fetch('/comand', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: 'command=' + command,
      }).catch(() => {
        alert('Erreur lors de l\'envoi de la commande.');
      });
    }

    // Gestion des flèches directionnelles
    testButton.addEventListener('mousedown', () => {
      sendCommand('test');
    });
    diagleftButton.addEventListener('mousedown', () => {
      sendCommand('diaggauche');
    });
    upButton.addEventListener('mousedown', () => {
      sendCommand('avancer');
    });
    // Gestion des flèches directionnelles
    diagrightButton.addEventListener('mousedown', () => {
      sendCommand('diagdroite');
    });
    downButton.addEventListener('mousedown', () => {
      sendCommand('reculer');
    });
    leftButton.addEventListener('mousedown', () => {
      sendCommand('gauche');
    });
    rightButton.addEventListener('mousedown', () => {
      sendCommand('droite');
    });
    recrightButton.addEventListener('mousedown', () => {
      sendCommand('recdroite');
    });
    recleftButton.addEventListener('mousedown', () => {
      sendCommand('recgauche');
    });
    
    // Arrêter le robot dès que la flèche est relâchée
    testButton.addEventListener('mouseup', () => {
      sendCommand('stop');
    });
    diagleftButton.addEventListener('mouseup', () => {
      sendCommand('stop');
    });
    upButton.addEventListener('mouseup', () => {
      sendCommand('stop');
    });
    diagrightButton.addEventListener('mouseup', () => {
      sendCommand('stop');
    });
    downButton.addEventListener('mouseup', () => {
      sendCommand('stop');
    });
    leftButton.addEventListener('mouseup', () => {
      sendCommand('stop');
    });
    rightButton.addEventListener('mouseup', () => {
      sendCommand('stop');
    });
    recrightButton.addEventListener('mouseup', () => {
      sendCommand('stop');
    });
    recleftButton.addEventListener('mouseup', () => {
      sendCommand('stop');
    });


    // Pour les écrans tactiles (gestion du touchend)
    testButton.addEventListener('touchstart', () => {
      sendCommand('test');
    });
    diagleftButton.addEventListener('touchstart', () => {
      sendCommand('diaggauche');
    });
    upButton.addEventListener('touchstart', () => {
      sendCommand('avancer');
    });
    diagrightButton.addEventListener('touchstart', () => {
      sendCommand('diagdroite');
    });
    downButton.addEventListener('touchstart', () => {
      sendCommand('reculer');
    });
    leftButton.addEventListener('touchstart', () => {
      sendCommand('gauche');
    });
    rightButton.addEventListener('touchstart', () => {
      sendCommand('droite');
    });
    recrightButton.addEventListener('touchstart', () => {
      sendCommand('recdroite');
    });
    recleftButton.addEventListener('touchstart', () => {
      sendCommand('recgauche');
    });

    testButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });
    diagleftButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });
    upButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });
    diagrightButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });
    downButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });
    leftButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });
    rightButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });
    recrightButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });
    recleftButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });


  </script>
</body>
</html>
  )rawliteral");
}

void handleComand() {
    if (server.hasArg("command")) {          // Vérifie si une commande a été envoyée
        String command = server.arg("command");  // Récupère la commande

        if (command == "test"){ // petit test avec 
            digitalWrite(LED,HIGH);
        } else if (command == "diaggauche") {           // Commande pour tourner diagonale gauche
            Serial2.write(65+puissance_tourne_large);  // Moteur 1 avance +
            Serial2.write(193+puissance_tourne_court); // Moteur 2 avance -

        } else if (command == "gauche") {           // Commande pour tourner à gauche
            Serial2.write(65+puissance_rotation);  // Moteur 1 avance
            Serial2.write(191-puissance_rotation); // Moteur 2 recule

        }else if (command == "diagdroite") {           // Commande pour tourner diagonale droite
            Serial2.write(65+puissance_tourne_court);  // Moteur 1 avance -
            Serial2.write(193+puissance_tourne_large); // Moteur 2 avance +

        } else if (command == "droite") {    // Commande pour tourner à droite
            Serial2.write(63-puissance_rotation);  // Moteur 1 recule 
            Serial2.write(193+puissance_rotation); // Moteur 2 avance 

        } else if (command == "reculer") {   // Commande pour reculer
            Serial2.write(63-puissance_recul);  // Moteur 1 recule
            Serial2.write(191-puissance_recul); // Moteur 2 recule

        } else if (command == "recdroite") {   // Commande pour reculer droite diag
            Serial2.write(63-puissance_tourne_recul_court);  // Moteur 1 recule -
            Serial2.write(191-puissance_tourne_recul_large); // Moteur 2 recule +

        }else if (command == "recgauche") {   // Commande pour diagonale gauche reculer
            Serial2.write(63-puissance_tourne_recul_large);  // Moteur 1 recule +
            Serial2.write(191-puissance_tourne_recul_court); // Moteur 2 recule -

        }else if (command == "avancer") {   // Commande pour avancer
            Serial2.write(65+puissance_avant);  // Moteur 1 avance 
            Serial2.write(193+puissance_avant); // Moteur 2 avance

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