#include "UnoJoy.h"

void setup(){
  setupPins(); // Subrotina que configura os pinos do Arduino
  setupUnoJoy();// Inicializa as funções do UnoJoy
}

void loop(){
  // Sempre fica atualizando o dado a ser enviado ao computador
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
}

void setupPins(void){
  // Configura os pinos digitais 2~12 
  // como entrada e com pull-up ativado 
  for (int i = 2; i <= 12; i++){
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
}

dataForController_t getControllerData(void){
  
  //  Configura local onde dados do controle são armazenados
  //  Serve para limpar o buffer onde os dados do controle são armazenados
  dataForController_t controllerData = getBlankDataForController();
  
  
  //  Associa os pinos digitais com o botão do UnoJoy
  //  A "!" inverte a leitura 
  controllerData.triangleOn = !digitalRead(4);
  controllerData.circleOn = !digitalRead(3);
  controllerData.squareOn = !digitalRead(6);
  controllerData.crossOn = !digitalRead(5);
  controllerData.selectOn = !digitalRead(2);
  controllerData.startOn = !digitalRead(7);
  
  //  Configura o joystick Analógico
  //  A leitura "analogRead(pin)" retorna um valor de 10 bits(0~1023),
  //  Nós usamos um o "map" para deixar na faixa de 8 bits (0~255) 
  //  Aproveitamos o map para inverte a leitura no eixo Y
  controllerData.leftStickX = map((analogRead(A0)),0,1023,0,255);
  controllerData.leftStickY = map((analogRead(A1)),0,1023,255,0);
 
  return controllerData;
}
