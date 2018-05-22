/*Cliente mqtt para enviar y recivir mensajes a travez del broker instalado en el servidor*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Asignacion de id y password de la red a la que nis conectaremos, ademas se agrega la ip del broker dentro de la red
const char* ssid = "TalaDeArboles";
const char* password = "tala1234";
const char* mqtt_server = "192.168.1.102";

WiFiClient espClient; //se crea una instancia de tipo WiFiClient para trabajar con el wifi del uC
PubSubClient client(espClient);// El cliente MQTT recibe como parametro el objeto creado anteriormente 

// declaracion de variables para guardar datos de comunicacion
long lastMsg = 0;
char msg[50];
int value = 0;


//Procedimiento para configurar el wifi
void setup_wifi() {

  delay(10);
  //Impresion en el puerto serial del ssid al que nos conectaremos
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(ssid);

  //inicializacion de la coneccion wifi, recive 2 parametros el ssid de la red y la contraseña 
  WiFi.begin(ssid, password);

  //Mientras no se conecte visualizaremos unicamente puntos
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());


  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Direccion IP : ");
  Serial.println(WiFi.localIP()); //imprime la direccion ip que se le asigno por el servidor DHCP
}

//Callback es un procedimiento que se utiliza al recivir un mensaje, el contenido del mensaje se almacena en la variable payload
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recivido [");
  Serial.print(topic);
  Serial.print("] ");
  //El siguiente ciclo se utiliza para imprimir un por uno por uno los bytes recividos que se ven representados en letras
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

 
}

//Procedimiento para reconectar al broker mqtt
void reconnect() {

  while (!client.connected()) {
    // en las siguientes dos lineas se crea un ID random para el uC
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    //Reconeccion
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado");
      // una vez que se conecta publica un mensaje para anunciarlo.
      client.publish("outTopic", "Estoy conectado :D");
      //Topico de suscripcion 
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
 
  Serial.begin(115200); //Inicializamos el puerto serial con una velocidad de 115200 baudios/s
  pinMode(5, INPUT); //Indicamos que el pin 5 sera una entrada digital
  setup_wifi();//llamamos al procedimiento setup wifi para conectarnos a la red wifi
  client.setServer(mqtt_server, 1883); //inicializamos el cliente mqtt y le enviamos la ip del broker dentro de la red y el puerto por el que se conectara
  client.setCallback(callback);//Seteamos nuesta funcion callback.
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

//Si recibimos un HIGH en el pin 5 significa que estamos reciviento a travez del filtro digital una 
//señal que oscila en la frecuecia del sonido la motocierra 
  if(digitalRead(5)==HIGH)
  {
    //Publicamos un mensaje para activar la alarma en el servidor que contiene la interfaz grafica
    snprintf (msg, 75, "on");
    Serial.println(msg);
    client.publish("office/rgb1/light/status2", msg);
  }
//De lo contrario no enciende nunguna alrma
  else(digitalRead(5)==LOW)
  {
    snprintf (msg, 75, "off");
    Serial.println(msg);
    client.publish("office/rgb1/light/status2", msg);
  }
  
}
