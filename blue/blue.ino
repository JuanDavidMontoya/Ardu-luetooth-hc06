

#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); //10 RX, 11 TX.

char cadena[255]; //Creamos un array de caracteres de 256 cposiciones
int i = 0; //Tamaño actual del array
int val;
int temppin = 1;

void setup()
{
  BT.begin(9600);
  Serial.begin(9600);
  
}

void loop()
{
  
  if (BT.available())
  {
    char dato = BT.read(); //Guarda los datos carácter a carácter en la variable "dato"
    cadena[i++] = dato; //Vamos colocando cada carácter recibido en el array "cadena"

    //Cuando reciba una nueva línea (al pulsar enter en la app) entra en la función
    if (dato == '\n')
    {
      Serial.print(cadena); //Visualizamos el comando recibido en el Monitor Serial
      if (strstr(cadena, "temp") != 0)
      {
       float Temperatura = Temp();
        BT.write("Temperatura es: ");
        String mystring;
        mystring = String(Temperatura);
        BT.write((char)mystring);
      }
      

      BT.write("\r"); //Enviamos un retorno de carro de la app. La app ya crea una línea nueva
      clean(); //Ejecutamos la función clean() para limpiar el array
    }
  }
}

//Limpia el array
void clean()
{
  for (int cl = 0; cl <= i; cl++)
  {
    cadena[cl] = 0;
  }
  i = 0;
}

float Temp (){
  val = analogRead (temppin);
  float mv = (val/1024.0)*5000.0;
  float centi = mv/10; 
  return centi;
  
}
