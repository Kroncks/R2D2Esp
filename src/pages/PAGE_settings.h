const char PAGE_settings[] = R"rawliteral(
    <!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>Settings</title>
  <style>
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
  </style>
</head>
<body>
<h1>Bonsoir</h1>
<div>
<button onclick="window.location.href = '/';">Home</button>
</div>
<p>Controles<p>
<div>
<button class="button" id="test">test</button>
<button class="button" id="toggle">toggle</button>
</div>
<script>
    // Références aux éléments
    const testButton = document.getElementById('test');
    const toggleButton = document.getElementById('toggle');

    // Fonction pour envoyer une commande
    function sendCommand(command) {
      fetch('/comand', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: 'settings=' + command,
      }).catch(() => {
        alert('Erreur lors de l\'envoi de la commande.');
      });
    }

    testButton.addEventListener('mousedown', () => {
      sendCommand('test');
    });

    testButton.addEventListener('mouseup', () => {
      sendCommand('stop');
    });
    toggleButton.addEventListener('mouseup', () => {
      sendCommand('toggle');
    });

    //  écrans tactiles 
    testButton.addEventListener('touchstart', () => {
      sendCommand('test');
    });

    testButton.addEventListener('touchend', () => {
      sendCommand('stop');
    });
    toggleButton.addEventListener('touchend', () => {
      sendCommand('toggle');
    });

  </script>
</body>
</html>
  )rawliteral";