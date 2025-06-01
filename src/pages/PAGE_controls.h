const char PAGE_controls[] = R"rawliteral(
    <!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>Contrôle du Robot</title>
  <style>
    /* Réinitialisation des marges et du padding */
    html{
      margin: 0;
      padding: 0;
      height: 100%;
      overflow: hidden;
    }

    body {
            margin: 0;
            padding: 0;
            height: 100vh;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            background: linear-gradient(to right, #007179, #02B8C5);
            color: white;
            text-align: center;
            touch-action: none; /* Empêche le zoom et le scroll */
                  -webkit-user-select: none; /*empêche la sélection de texte */
      -moz-user-select: none;
      -ms-user-select: none;
      user_select: none; 
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
  <h1>Tete</h1>
  <div class="direction-buttons">
      <div class="button-row">
        <button class="button" id="teteleft">←</button>
        <button class="button" id="teteright">→</button>
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

    const teteleftButton = document.getElementById('teteleft');
    const teterightButton = document.getElementById('teteright');

    // Fonction pour envoyer une commande
    function sendCommand(command) {
      fetch('/comand', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: 'deplacement=' + command,
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
    teterightButton.addEventListener('mousedown', () => {
      sendCommand('tetedroite');
    });
    teteleftButton.addEventListener('mousedown', () => {
      sendCommand('tetegauche');
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
    teterightButton.addEventListener('mouseup', () => {
      sendCommand('stop');
    });
    teteleftButton.addEventListener('mouseup', () => {
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
    teterightButton.addEventListener('touchstart', () => {
      sendCommand('tetedroite');
    });
    teteleftButton.addEventListener('touchstart', () => {
      sendCommand('tetegauche');
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
    teterightButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });
    teteleftButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });

  </script>
</body>
</html>
  )rawliteral";