const char PAGE_readme[] = R"rawliteral(
    <!DOCTYPE html><html lang="fr"><head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>Readme</title>
  <style>
      
      .hljs-comment { color: #6a9955; font-style: italic; }
      .hljs-keyword { color: #569cd6; font-weight: bold; }
      .hljs-number { color: #b5cea8; }
      .hljs-string { color: #d69d85; }
      .hljs-function { color: #dcdcaa; }
      .hljs-title { color: #4ec9b0; }
      .hljs-variable { color: #9cdcfe; }
      .hljs-attr { color: #9cdcfe; }
    

    pre {
    background-color: #f5f5f5; /* gris clair */
    border: 1px solid #ccc;
    padding: 1em;
    border-radius: 8px;
    overflow-x: auto;
    width: fit-content; 
    font-family: Consolas, monospace;
    font-size: 0.9em;
    padding-right: 45px;
  }

  code.language-cpp {
    color: #000;
  }
    
    </style> 
    </head><body>

    <button onclick="window.location.href = '/';">Home</button>

    <!-- README CONVERTI AVEC https://dillinger.io/ -->

    <h1 class="code-line" data-line-start=0 data-line-end=1 ><a id="Controle_du_R2D2_par_ESP32_0"></a>Controle du R2D2 par ESP32</h1>
    <h2 class="code-line" data-line-start=2 data-line-end=3 ><a id="Acceder_a_linterface_de_commande_2"></a>Acceder a l’interface de commande</h2>
    <ul>
    <li class="has-line-data" data-line-start="3" data-line-end="4">Allumer l’ESP32</li>
    <li class="has-line-data" data-line-start="4" data-line-end="5">Se connecter au reseau R2D2 avec le code : <code>BONSOIRS</code></li>
    <li class="has-line-data" data-line-start="5" data-line-end="6">Ouvrir <a href="http://192.168.4.1/">http://192.168.4.1/</a> sur un navigateur</li>
    <li class="has-line-data" data-line-start="6" data-line-end="8">Cliquer sur le bouton <code>Controles</code></li>
    </ul>
    <h2 class="code-line" data-line-start=8 data-line-end=9 ><a id="Verifier_que_la_connexion_fonctionne_8"></a>Verifier que la connexion fonctionne</h2>
    <ul>
    <li class="has-line-data" data-line-start="9" data-line-end="10">Appuyer sur le bouton au centre de la croix directionelle</li>
    <li class="has-line-data" data-line-start="10" data-line-end="12">Verifier qu’une LED bleu s’allume bien sur l’ESP32</li>
    </ul>
    <h2 class="code-line" data-line-start=12 data-line-end=13 ><a id="Connexion_de_lESP32_au_driver_moteur_Sabertooth_12"></a>Connexion de l’ESP32 au driver moteur Sabertooth</h2>
    <ul>
    <li class="has-line-data" data-line-start="13" data-line-end="14">Relier la pin TX2 de l’ESP32 a l’entree S1 du Sabertooth</li>
    <li class="has-line-data" data-line-start="14" data-line-end="16">Ne pas modifier les reglages du Sabertooth ( 010100 -&gt; Serial 9600 )</li>
    </ul>
    <h2 class="code-line" data-line-start=16 data-line-end=17 ><a id="Connexion_des_moteurs_au_Sabertooth_16"></a>Connexion des moteurs au Sabertooth</h2>
    <ul>
    <li class="has-line-data" data-line-start="17" data-line-end="18">Connecter le moteur droit sur M1</li>
    <li class="has-line-data" data-line-start="18" data-line-end="20">Connecter le moteur gauche sur M2</li>
    </ul>
    <h2 class="code-line" data-line-start=20 data-line-end=21 ><a id="Modifier_la_valeur_de_la_vitesse_20"></a>Modifier la valeur de la vitesse</h2>
    <ul>
    <li class="has-line-data" data-line-start="21" data-line-end="22">Ouvrir le code dans une IDE et ouvrir <code>src/main.cpp</code></li>
    <li class="has-line-data" data-line-start="22" data-line-end="23">Modifier les valeures des puissances de la ligne 13 à 28</li>
    </ul>
    <pre><code class="language-cpp has-line-data" data-line-start="24" data-line-end="43">
    
    <span class="hljs-comment">// =========   puissance (0-62)   =========</span>

    <span class="hljs-comment">// Avancer / Reculer</span>
    <span class="hljs-keyword">const</span> <span class="hljs-keyword">int</span> puissance_avant = <span class="hljs-number">40</span>; <span class="hljs-comment">// puissance pour avancer droit</span>
    <span class="hljs-keyword">const</span> <span class="hljs-keyword">int</span> puissance_recul = <span class="hljs-number">30</span>; <span class="hljs-comment">// puissance pour reculler droit</span>

    <span class="hljs-comment">// Rotation</span>
    <span class="hljs-keyword">const</span> <span class="hljs-keyword">int</span> puissance_rotation = <span class="hljs-number">20</span>; <span class="hljs-comment">// puissance des roues pour tourner sur soi meme </span>

    <span class="hljs-comment">// tourner en diagonale </span>
    <span class="hljs-keyword">const</span> <span class="hljs-keyword">int</span> puissance_tourne_large = <span class="hljs-number">30</span>; <span class="hljs-comment">// puissance de la roue externe au virage </span>
    <span class="hljs-keyword">const</span> <span class="hljs-keyword">int</span> puissance_tourne_court = <span class="hljs-number">20</span>; <span class="hljs-comment">// puissance de la roue intenre au virage </span>

    <span class="hljs-comment">// reculer en diagonale </span>
    <span class="hljs-keyword">const</span> <span class="hljs-keyword">int</span> puissance_tourne_recul_large = <span class="hljs-number">30</span>; <span class="hljs-comment">// puissance de la roue externe au virage</span>
    <span class="hljs-keyword">const</span> <span class="hljs-keyword">int</span> puissance_tourne_recul_court = <span class="hljs-number">20</span>; <span class="hljs-comment">// puissance de la roue intenre au virage</span>

    <span class="hljs-comment">// ==========================================</span>
    </code></pre>
    <ul>
    <li class="has-line-data" data-line-start="43" data-line-end="45">Televerser le code sur l’ESP32</li>
    </ul>
    <h2 class="code-line" data-line-start=45 data-line-end=46 ><a id="Github_45"></a>Github</h2>
    <p class="has-line-data" data-line-start="46" data-line-end="47"><a href="https://github.com/Kroncks/R2D2Esp">GitHub</a></p>

    <!-- FIN README -->
    </body></html>
  )rawliteral";