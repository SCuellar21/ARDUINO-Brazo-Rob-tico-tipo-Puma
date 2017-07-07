#include <Servo.h>

Servo servobase, servo1, servo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int cont = 1;
float x, y, z, l1 = 7.0, l2 = 5.3, l3 = 6.1, teta1_0 = 0, teta2_0 = 0, teta3_0 = 0, teta1_F, teta2_F, teta3_F;
String inString = "";         // a string to hold incoming data
boolean strComplete = false;  // whether the string is complete


void setup() {
  Serial.begin(9600);
  // reserve 200 bytes for the inString:
  inString.reserve(200);
  servobase.attach(9);  // attaches the servo on pin 9 to the servo object
  servo1.attach(10);
  servo2.attach(11);
  Serial.println("Escribe el valor para X deseada ");
}

void loop() {
  if(strComplete){  //revisa si se envio algun valor en la consola
    //Establece los valores para las coordenadas
    if(cont==1){     //revisa cual fue el valor que se envio
      x=inString.toFloat();      //asigna el valor recivido a la variable en forma numerica
      Serial.println(x,5);
      Serial.println("Escribe el valor para Y deseada ");
    }
    else if(cont==2){
      y=inString.toFloat();
      Serial.println(y,5);
      Serial.println("Escribe el valor para Z deseada ");
    }
    else if(cont==3){
      z=inString.toFloat();
      Serial.println(z,5);
    }
    inString = "";
    strComplete = false;
    cont++;
    
    //Si ya tomo los tres valores, realiza el movimiento de los servos
    if(cont>3){
      teta1_0=atan2(y,x)*180/3.1416;            //calcula teta 1
      Serial.println(teta1_0,5);
      teta2_0=(atan2(z-l1,sqrt(pow(x,2)+pow(y,2)))+acos((pow(l3,2)-pow(l2,2)-pow(z-l1,2)-pow(x,2)-pow(y,2))/(-2*l2*sqrt(pow(z-l1,2)+pow(x,2)+pow(y,2)))))*180/3.1416;  //calcula teta 2
      Serial.println(teta2_0,5);
      teta3_0=fabs(acos((pow(z-l1,2)+pow(x,2)+pow(y,2)-pow(l2,2)-pow(l3,2))/(-2*l2*l3))*180/3.1416-180);    //calcula teta 3
      Serial.println(teta3_0,5);
      Serial.println("Moviendo el brazo...");
      if(teta1_0>=0){                                 //si teta1_0 es positivo
        for (int i = 0; i <= teta1_0; ++i) { //mueve le servo un grado a la vez hasta llegar al valor de teta1_0
          servobase.write(i);
          delay(15);
        }
        
      //Serial.println(servobase.read());
      }
      else{                                        //si teta1_0 es negativo
        for (int i = 0; i >= teta1_0; --i) {
          servobase.write(i);
          delay(15);
        }
        
      //Serial.println(servobase.read());
      }
      if(teta2_0>=0){
        for (int i = 0; i <= teta2_0; i++) {
          servo1.write(i);
          delay(15);
        }
      }
      else{
        for (int i = 0; i >= teta2_0; i--) {
          servo1.write(i);
          delay(15);
        }
      }
      if(teta3_0>=0){
        for (int i = 0; i <= teta3_0; i++) {
          servo2.write(i);
          delay(15);
        }
      }
      else{
        for (int i = 0; i >= teta3_0; i--) {
          servo2.write(i);
          delay(15);
        }
      }
      Serial.println("Brazo movido!");
      Serial.println(servobase.read());
      Serial.println(servo1.read());
      Serial.println(servo2.read());
      delay(4000);
      regresar();
      cont=1;
      Serial.println("Escribe el valor para X deseada ");
    }
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      strComplete = true;
    }
    else{             // add it to the inString:
      inString += inChar;
    }
  }
}

void regresar(){
  Serial.println("Regrezando a posicion original...");
  if(teta1_0<=0){
    for (int i = teta1_0; i <= 0; i++) {
      servobase.write(i);
      delay(15);
    }
  }
  else{
    for (int i = teta1_0; i >= 0; i--) {
      servobase.write(i);
      delay(15);
    }
  }
  if(teta2_0<=0){
    for (int i = teta2_0; i <= 0; i++) {
      servo1.write(i);
      delay(15);
    }
  }
  else{
    for (int i = teta2_0; i >= 0; i--) {
      servo1.write(i);
      delay(15);
    }
  }
  if(teta3_0<=0){
    for (int i = teta3_0; i <= 0; i++) {
      servo2.write(i);
      delay(15);
    }
  }
  else{
    for (int i = teta3_0; i >= 0; i--) {
      servo2.write(i);
      delay(15);
    }
  }
  Serial.println(servobase.read());
  Serial.println(servo1.read());
  Serial.println(servo2.read());
  Serial.println("Brazo regresado!");
}

/*void moverbrazo(){
  teta1_F=atan2(y,x);            //calcula teta 1
  Serial.println(teta1_0);
  teta2_F=atan2(z-l1,sqrt(pow(x,2)+pow(y,2)))+acos((pow(l3,2)-pow(l2,2)-pow(z-l1,2)-pow(x,2)-pow(y,2))/(-2*l2*sqrt(pow(z-l1,2)+pow(x,2)+pow(y,2))));  //calcula teta 2
  Serial.println(teta2_0);
  teta3_F=acos((pow(z-l1,2)+pow(x,2)+pow(y,2)-pow(l2,2)-pow(l3,2))/(-2*l2*l3))-180;    //calcula teta 3
  Serial.println(teta3_0);
  Serial.println("Moviendo el brazo...");
  if(teta1_F>=teta1_0){                                 //si teta1_0 es positivo
    for (int i = 0; i <= teta1_0; i++) { //mueve le servo un grado a la vez hasta llegar al valor de teta1_0
      servobase.write(i);
      delay(15);
    }
  }
  else{                                        //si teta1_0 es negativo
    for (int i = 0; i >= teta1_0; i--) {
      servobase.write(i);
      delay(15);
    }
  }
  if(teta2_0>=0){
    for (int i = 0; i <= teta2_0; i++) {
      servo1.write(i);
      delay(15);
    }
  }
  else{
    for (int i = 0; i >= teta2_0; i--) {
      servo1.write(i);
      delay(15);
    }
  }
  if(teta3_0>=0){
    for (int i = 0; i <= teta3_0; i++) {
      servo2.write(i);
      delay(15);
    }
  }
  else{
    for (int i = 0; i >= teta3_0; i--) {
      servo2.write(i);
      delay(15);
    }
  }
  Serial.println("Brazo movido!");
}
*/



