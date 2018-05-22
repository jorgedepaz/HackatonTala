
unsigned long microLectura=30UL;//tiempos de microlecturas
unsigned long tiempoLectura=8000UL;//tiempo total de lecturas
unsigned long calibracion=1000UL;
int tolerancia =35;
int toleranciaSenso =350; 
int valorEstable = 0;
volatile int valor;
// micro senso de datos para buscar picos en la señal durate el tiempo de microLectura 
boolean senso(){  
   unsigned long tiempoLectura= millis()+microLectura;
   while(tiempoLectura > millis()){
    valor = analogRead(A0);
    delay(1);
    //si encuentra un pico durante el tiempo de lectura devolvera true de no ser asi devolvera false
     if ((valor < valorEstable - toleranciaSenso )||(valor > valorEstable + toleranciaSenso)){
       return true;
      }
   }
   return false;
  }
 // senso de datos largo que busca una señal estable durante el tiempoLectura 
boolean sensar(){
  unsigned long lectura= millis()+tiempoLectura;
  while(millis()<lectura){
    //si senso devuelve true se sigue con las lecturas hasta acabar con el tiempo
      if (senso()){
         Serial.println("Frecuencia Encontrada");
        }
     else{
      //en caso contrario devolveremos false
         Serial.println("Sin precencia de frecuencia");
         return false; 
        }
    }
    //si todo el tiempo se encontro frecuencia se devuelve true para activar la alarma
    return true;
 }
boolean calibrar(){
  boolean estable = true;
  valorEstable=analogRead(A0);
  delay(1);
  Serial.println(valorEstable); 
  Serial.print("Calibrando: ");
  unsigned long tiempoCalibracion = millis()+calibracion;
  while (millis()< tiempoCalibracion ){
    
    valor =  analogRead(A0);
    delay(1);
    Serial.print(".");
    //Serial.println(valor);    
    if ((valor < valorEstable - tolerancia )||(valor > valorEstable + tolerancia)){
      Serial.println("");
      Serial.println("Calibracion errada");
      return false;
      }
    }
  Serial.println("");
  Serial.println(" Calibracion Exitosa");
  return true;
 }

void alarma(){
      while(1){
      Serial.println("Alarma!!!");    
      delay(400);
      Serial.println("!!!");  
      delay(200);
     }
  
  }

void actividadNormal(){
    Serial.println("Actividad en parametros normales");  
  }
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!calibrar()){
    }
}

void loop() {
  //senso de datos de lambda tiempoLectura
  if (sensar()){
    alarma();
    }
  else{
  actividadNormal();
     }
  delay(500);
}

