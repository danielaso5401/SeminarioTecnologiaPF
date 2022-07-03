//Librerias
#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales
#include<Servo.h> //libreria para controlar el servo



//Variables de conexión
SoftwareSerial miBT(10, 11);  // pin 10 como RX, pin 11 como TX
char DATO = 0;//Variable para almacenar caracter recibido
int TRIG = 9;//Pureto digital para S. Proximidad Ouput
int ECO = 8;//Pureto digital para S. Proximidad Input
int SERVO=7;//Pureto digital para Servo
Servo servoMotor;//Declaramos la variable para controlar el servo

//Variables Externas
int DURACION;
int DISTANCIA;


//Se declara los componentes con sus pines y comunicación serial
void setup(){
    miBT.begin(38400);
    Serial.begin(9600);// inicializacion de comunicacion serial a 9600 bps
    pinMode(TRIG, OUTPUT);// trigger como salida
    pinMode(ECO, INPUT);// echo como entrada
    pinMode(LEDROJO, OUTPUT); // pin 2 como salida
    servoMotor.attach(SERVO);//Iniciamos el servo para que empiece a trabajar con el pin 7
}


//Bucle de consultas y recepción de información
void loop(){
    DATO = miBT.read();   // almacena en DATO el caracter recibido desde modulo
    digitalWrite(TRIG, HIGH);     // generacion del pulso a enviar
    delay(1);       // al pin conectado al trigger
    digitalWrite(TRIG, LOW);    // del sensor
    DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
    DISTANCIA = DURACION / 58.2;
    if(DISTANCIA<20){
        Serial.println(DISTANCIA);// envio de valor de distancia por monitor serial
        miBT.println(DISTANCIA);// distancia medida en centimetros
        miBT.println(1);//se envia comando par abrir la puerta y cerrar
        delay(200);// demora entre datos 
        servoMotor.write(180);// Desplazamos a la posición 180º para la apertura
    }
    else{
        Serial.println(DISTANCIA);// envio de valor de distancia por monitor serial
        miBT.println(DISTANCIA);// distancia medida en centimetros
        delay(200);// demora entre datos
        if (Dato==0){

            Serial.println(DISTANCIA);// envio de valor de distancia por monitor serial
            miBT.println(DISTANCIA);// distancia medida en centimetros
            delay(200);// demora entre datos
            servoMotor.write(0);// Desplazamos a la posición 0º para el cierre
        }
    }

}