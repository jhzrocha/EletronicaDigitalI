#include "htmlCreator.h"

const char HTMLCreator::index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <title>Aquário</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      padding: 20px;
    }

    .container {
      display: flex;
      justify-content: center;
      align-items: flex-end;
      margin-top: 20px;
      flex-wrap: wrap;
    }

    .tank-area {
      position: relative;
      width: 200px;
      height: 300px;
      margin: 20px 0;
      background: linear-gradient(to top, #0f0 50%, #fff 50%);
      border: 3px solid #000;
      border-radius: 10px;
      overflow: hidden;
    }

    #tank {
      width: 200px;
      height: 300px;
      border: 2px solid #000;
      position: relative;
      background: linear-gradient(to top, #00f 50%, #fff 50%);
      border-radius: 10px;
      overflow: hidden;
    }

    .pump {
      width: 120px;
      height: 120px;
      display: flex;
      justify-content: center;
      align-items: center;
      margin: 20px;
    }

    .pump svg {
      width: 100px;
      height: 100px;
    }

    #fan {
      margin-bottom: 10px;
    }

    .pump.right svg {
      transform: scaleX(-1);
    }

    #ph-value, #temp-value {
      font-size: 24px;
      margin-top: 20px;
    }

    button {
      padding: 10px 20px;
      margin: 10px 5px;
      font-size: 16px;
      cursor: pointer;
      border-radius: 5px;
      border: none;
      background-color: #3498db;
      color: white;
    }

    button:hover {
      background-color: #2980b9;
    }

    .config {
      margin: 20px auto;
      max-width: 400px;
      text-align: left;
    }

    .config label {
      display: block;
      margin-top: 10px;
      font-weight: bold;
    }

    .config input {
      width: 100%;
      padding: 8px;
      font-size: 16px;
      box-sizing: border-box;
      margin-top: 5px;
      border-radius: 4px;
      border: 1px solid #ccc;
    }

    .bombaEmFuncionamento {
      transform-origin: 50% 50%;
      animation: spin 2s linear infinite;
    }

    @keyframes spin {
      0% { transform: rotate(0deg); }
      100% { transform: rotate(360deg); }
    }

    .rotating {
      animation: spin 2s linear infinite;
      transform-origin: center center;
    }

    @media (max-width: 600px) {
      .container {
        flex-direction: column;
        align-items: center;
        gap: 20px;
      }

      #tank, .tank-area {
        width: 150px;
        height: 220px;
      }

      .pump {
        width: 80px;
        height: 80px;
      }

      .pump svg {
        width: 70px;
        height: 70px;
      }

      #ph-value, #temp-value {
        font-size: 20px;
      }

      button {
        width: 90%;
        font-size: 18px;
        padding: 12px;
        margin: 5px auto;
      }

      .config {
        max-width: 90%;
      }

      .config input {
        font-size: 18px;
      }
    }
  </style>
</head>
<body>

  <h1>Aquário</h1>

  <div class="container">

    <div id="fan" class="pump">
      <div style="text-align: center;">
        <div style="margin-bottom: 5px; font-weight: bold;">Ventilador</div>
        <svg viewBox="0 0 100 100" width="60" height="60" id = fanBlades class = bombaEmFuncionamento>
          <circle cx="50" cy="50" r="30" fill="lightblue" stroke="black" stroke-width="2"/>
          <g  transform="translate(50,50)">
            <path d="M0,-20 Q10,-10 0,0 Q-10,-10 0,-20" fill="blue"/>
            <path d="M0,-20 Q10,-10 0,0 Q-10,-10 0,-20" fill="blue" transform="rotate(120)"/>
            <path d="M0,-20 Q10,-10 0,0 Q-10,-10 0,-20" fill="blue" transform="rotate(240)"/>
          </g>
        </svg>
      </div>
    </div>

    <div style="display: flex; justify-content: center; align-items: center; margin-top: 20px;">
      
      <div id="acidPump" class="pump" style="margin-right: 40px;">
        <div style="text-align: center;">
          <div style="margin-bottom: 5px; font-weight: bold;">Bomba Ácida</div>
          <svg viewBox="0 0 100 100" width="60" height="60">
            <rect x="20" y="20" width="60" height="60" rx="10" ry="10" fill="gray" stroke="black" stroke-width="2"/>
            <rect x="80" y="40" width="15" height="20" rx="4" ry="4" fill="darkgray" stroke="black" stroke-width="2"/>
            <g id ="bombaAcida" class="bombaEmFuncionamento">
              <g transform="translate(50,50)">
                <path d="M0,-15 Q7,0 0,15 Q-7,0 0,-15" fill="black" stroke="black" stroke-width="1"/>
              </g>
            </g>
          </svg>
        </div>
      </div>

      <div class="tank-area" id="tank">
        <div id="heater">
          <svg id="heaterSvg" viewBox="0 0 100 100" width="100" height="100">
            <rect id="heaterBody" x="30" y="20" width="40" height="60" fill="orange" stroke="black" stroke-width="2"/>
            <path d="M50 30 Q45 40 50 50 Q55 60 50 70" stroke="red" stroke-width="3" fill="none"/>
          </svg>
        </div>
      </div>

      <div id="basePump" class="pump right" style="margin-left: 40px;">
        <div style="text-align: center;">
          <div style="margin-bottom: 5px; font-weight: bold;">Bomba Básica</div>
          <svg viewBox="0 0 100 100" width="60" height="60">
            <rect x="20" y="20" width="60" height="60" rx="10" ry="10" fill="gray" stroke="black" stroke-width="2"/>
            <rect x="80" y="40" width="15" height="20" rx="4" ry="4" fill="darkgray" stroke="black" stroke-width="2"/>
            <g id ="bombaBasica" class="bombaEmFuncionamento">
              <g transform="translate(50,50)">
                <path d="M0,-15 Q7,0 0,15 Q-7,0 0,-15" fill="black" stroke="black" stroke-width="1"/>
              </g>
            </g>
          </svg>
        </div>
      </div>

    </div>
  </div>

  <div>
    <button onclick="addAcid()">Adicionar Ácido</button>
    <button onclick="addBase()">Adicionar Base</button>
    <button onclick="heat()">Aquecer</button>
    <button onclick="cool()">Resfriar</button>
  </div>

  <div id="ph-value">pH atual: 7.00</div>
  <div id="temp-value">Temperatura atual: 20°C</div>

  <div class="config">
    <h2>Configurações</h2>

    <label for="idealPh">pH Ideal:</label>
    <input type="number" id="idealPh" value="7.0" step="0.01">

    <label for="idealTemp">Temperatura Ideal (°C):</label>
    <input type="number" id="idealTemp" value="25" step="0.1">

    <label for="acidSolutionPh">pH da Solução Ácida:</label>
    <input type="number" id="acidSolutionPh" value="3.0" step="0.01">

    <label for="baseSolutionPh">pH da Solução Básica:</label>
    <input type="number" id="baseSolutionPh" value="11.0" step="0.01">

    <label for="acidFlowRate">Vazão da Bomba Ácida (mL/s):</label>
    <input type="number" id="acidFlowRate" value="5" step="0.1">

    <label for="baseFlowRate">Vazão da Bomba Básica (mL/s):</label>
    <input type="number" id="baseFlowRate" value="5" step="0.1">
  </div>

  <script>
    let ph = 7.0;
    let temperature = 20.0;

    let temperatureAction = 'none';
    let phAction = 'none';
    

function updateDisplay() {
  document.getElementById('ph-value').textContent = `pH atual: ${ph.toFixed(2)}`;
  document.getElementById('temp-value').textContent = `Temperatura atual: ${temperature.toFixed(1)}°C`;

  const tank = document.getElementById('tank');
  const idealPh = parseFloat(document.getElementById('idealPh').value) || 7.0;
  const idealTemp = parseFloat(document.getElementById('idealTemp').value) || 25.0;
  const bombaBasica = document.getElementById('bombaBasica');
  const bombaAcida = document.getElementById('bombaAcida');

  let phAction = 'none';
  let temperatureAction = 'none';

  if (Math.abs(ph - idealPh) < 0.01) {
    tank.style.background = "linear-gradient(to top, #0f0 50%, #fff 50%)";
    bombaAcida.classList.remove('bombaEmFuncionamento');
    bombaBasica.classList.remove('bombaEmFuncionamento');
  } else if (ph < idealPh) {
    const red = 255;
    const green = Math.max(0, Math.floor(255 * (ph / 7)));
    const blue = green;
    tank.style.background = `linear-gradient(to top, rgb(${red}, ${green}, ${blue}) 50%, #fff 50%)`;
    phAction = 'addBase';

    bombaBasica.classList.add('bombaEmFuncionamento');
    bombaAcida.classList.remove('bombaEmFuncionamento');

  } else {
    const blue = 255;
    const red = Math.min(255, Math.floor(255 * ((ph - 7) / 7)));
    const green = 0;
    tank.style.background = `linear-gradient(to top, rgb(${red}, ${green}, ${blue}) 50%, #fff 50%)`;
    phAction = 'addAcid';
    bombaAcida.classList.add('bombaEmFuncionamento');
    bombaBasica.classList.remove('bombaEmFuncionamento');
    
  }

  const heaterBody = document.getElementById('heaterBody');
  if (temperature < idealTemp) {
    heaterBody.setAttribute('fill', 'red');
    temperatureAction = 'heat';
  } else if (temperature > idealTemp) {
    heaterBody.setAttribute('fill', 'orange');
    temperatureAction = 'cool';
  } else {
    heaterBody.setAttribute('fill', 'orange');
  }

  const fanBlades = document.getElementById('fanBlades');
  if (temperature > idealTemp) {
    fanBlades.classList.add('bombaEmFuncionamento');
  } else {
    fanBlades.classList.remove('bombaEmFuncionamento');
  }

  // Envia a ação para o ESP32 sem recarregar a página
  fetch(`/update?phAction=${phAction}&tempAction=${temperatureAction}`)
    .then(response => response.text())
    .then(data => console.log('Resposta do ESP32:', data))
    .catch(error => console.error('Erro na requisição:', error));
}

    function addAcid() {
      const acidPh = parseFloat(document.getElementById('acidSolutionPh').value) || 3.0;
      const acidFlow = parseFloat(document.getElementById('acidFlowRate').value) || 5;
      const influence = (7 - acidPh) * (acidFlow / 100);
      ph = Math.max(0, ph - influence);
      updateDisplay();
    }

    function addBase() {
      const basePh = parseFloat(document.getElementById('baseSolutionPh').value) || 11.0;
      const baseFlow = parseFloat(document.getElementById('baseFlowRate').value) || 5;
      const influence = (basePh - 7) * (baseFlow / 100);
      ph = Math.min(14, ph + influence);
      updateDisplay();
    }

    function heat() {
      temperature += 0.5;
      updateDisplay();
    }

    function cool() {
      temperature -= 0.5;
      updateDisplay();
    }

    updateDisplay();
  </script>

</body>
</html>)rawliteral";

const char* HTMLCreator::getHTMLPage() {
  return index_html;
}
