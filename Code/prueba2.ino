#include <Servo.h>

//MAPEO
int vel;

//MOTOR DC
int IN1 = 3;
int IN2 = 4;

//SERVO
int angulo = 0;
Servo motor1;
int step=2;

//SENSOR
const int Trigger = 6;
const int Echo = 7;   
int tiempo;
int distancia;

//PID
int punto=20;
int duracion;
int pid;
int salida;
int h;
int tk;
int tk_1=0;
int error=0;
int error_ant=0;
int der=0;
int inte=0;
int kp=8;
int kd=11;
int ki=0.00000001;


void setup() {

  Serial.begin(9600);

  //MOTOR DC
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  //SERVO
  motor1.attach(A1);
  motor1.write(0);
  
  //SENSOR
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);

  //PID
    



}

void loop() {

  //SENSOR
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  tiempo = pulseIn(Echo, HIGH);
  distancia = tiempo/59;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(10);
  
  //MAPEO
  


  //PID
  tk=millis();
  h=tk-tk_1;//guardamos en h el perdiodo de ciclo
  error = punto - distancia;//calculamos el error
  inte = inte + (error*h);//se calcula el integral del error
  der = (error - error_ant)/h;//se calcula la derivada del error
  pid = (error*kp) + (inte*ki) + (der*kd);// ecuaciones del pid
  error_ant = error;//se manda el error actual al error anterior
  tk_1=tk;//se manda el tiempo actual al tiempo anterior

  if (pid > 85)     {pid  = 85;}// Se pone un límite en el valor máximo que puede alcanzar el valor de pid
     else if (pid < -100) { pid = -100;}//Se pone un límite en el valor mínimo que puede alcanzar el valor de pid
  
    
    if (pid < 0)
    {
      vel=map(pid,0,-100,0,255);
      digitalWrite(4,LOW);
      digitalWrite(3,vel);
      
      

      
    }
    if (pid>0)
    {
      vel=map(pid,0,100,0,255);
       digitalWrite(4,vel);
       digitalWrite(3,LOW);
    }

    if (pid==0)
    {
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);
    
      
      
    }
    // Estos comandos son para vizualizar los datos obtenidos 
 Serial.print("Distancia:");
 Serial.print(distancia);
 Serial.print("Salida:");
 Serial.print(salida);
 Serial.print("PID:");
 Serial.println(pid);
   
 motor1.write(angulo);  // mueve el servo a la posición 'pos'
  delay(15);           // espera 15ms para que el servo alcance la posición

  angulo += step;         // incrementa la posición

  // si la posición es 180 o 0, cambia la dirección del movimiento
  if (angulo >= 180 || angulo <= 0) {
    step = -step;
  }
}







