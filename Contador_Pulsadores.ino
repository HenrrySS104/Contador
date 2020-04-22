/* Cronometro de tres Digigitos en 7 Segmentos usando multiplexacion
 con boton de inicio, parada y retroceso.


 Conexiones:  Las conexiones entre el Arduino y el Display deben realizarse
              con una resistencia de 1K ohmio.
 ARDUINO  -    Display 7 Segmentos (catodo comun)
   3            a
   4            b
   5            c
   6            d
   7            e
   8            f
   9            g


   10           COM digito unidades usando Transistor NPN
   11           COM digito decenas  usando Transistor NPN
   12           COM digito centenas usando Transistor NPN

   2   -  Boton de inicio (se activa con GND)
   13   -  Boton de parada (se activa con GND)
   1   -  Boton de retroceso (se activa con GND)
*/

int inicio = 1;               // variable para el boton de inicio
int parada = 1;               // variable para el boton de parada
int retroceso = 1;               // variable para el boton de retroceso
int activar_boton_inicio = 1; // activa boton de inicio con "1" desactiva con "0"
int activar_boton_parada = 0; // activa boton de parada con "1" desactiva con "0"
int activar_boton_retroceso = 0; // activa boton de retroceso con "1" desactiva con "0"
int activar_incremento=0;     // activa incremento del contador con "1" desactiva con "0"
int activar_decremento=0;     // activa incremento del contador con "1" desactiva con "0"


int retardo = 10;     // tiempo que dura encendido cada 7 seg (10 mili segundos)
int var = 0;          // Valor del digito que se va a desplegar por el 7 seg.
int unidad = 0;       // cuenta las unidades
int decena = 0;       // cuenta las decenas
int centena = 0;       // cuenta las centenas
int conmutador = 0;   // multiplexacion de uno a otro 7 segmentos
int cont = 0;         // contador de ciclos de espera para cambiar de numero
int conta = 0;         // contador de ciclos de espera para cambiar de numero para diferenciar entre incremento y decremento


void setup() {
  pinMode(3, OUTPUT);  //seg a
  pinMode(4, OUTPUT);  //seg b
  pinMode(5, OUTPUT);  //seg c
  pinMode(6, OUTPUT);  //seg d
  pinMode(7, OUTPUT);  //seg e
  pinMode(8, OUTPUT);  //seg f
  pinMode(9, OUTPUT);  //seg g

  pinMode(10, OUTPUT);  // activa digito 1 (unidad)
  pinMode(11, OUTPUT);  // activa digito 2 (decena)
  pinMode(12, OUTPUT);  // activa digito 3 (centena)

  pinMode(2, INPUT);   // boton de inicio
  pinMode(13, INPUT);   // boton de parada
  pinMode(1, INPUT);   // boton de retroceso
}

void loop() {

  inicio = digitalRead(2);     // lee el estado del boron de inicio
  parada = digitalRead(13);     // lee el estado del boton de parada
  retroceso = digitalRead(1);     // lee el estado del boton de retroceso

  delay(10);               // tiempo que dura encendido cada 7seg antes de cambiar al otro

  if (inicio == 0) {                // si oprime boton de inicio el cronometro inicializa en 00
    if (activar_boton_inicio == 1) { // si esta activado el boton de inicio
     
      activar_boton_inicio = 0;     // desactiva boton de inicio
      activar_boton_parada = 1;     // activa boton de parada
      activar_boton_retroceso = 0;
      activar_incremento = 1;       //desactiva el incremento del contador
    }
  }
  
  if (parada == 0) {                     // si oprime boton parada
    if (activar_boton_parada == 1) {// si esta activado el boton de parada
      
      activar_boton_parada = 0;          // desactiva boton de parada
      activar_boton_inicio = 1;          // activa boton de inicio
      activar_boton_retroceso = 1;
      activar_incremento = 0;            //desactiva el incremento del contador
      activar_decremento = 0;            //desactiva el incremento del contador
    }
  }

if (retroceso == 0) {                // si oprime boton de inicio el cronometro inicializa en 00
    if (activar_boton_retroceso == 1) { // si esta activado el boton de inicio
      
      activar_boton_inicio = 0;     // desactiva boton de inicio
      activar_boton_parada = 1;     // activa boton de parada
      activar_boton_retroceso = 0;
      activar_decremento = 1;       //desactiva el incremento del contador
      
    }
  }
  
  if (activar_incremento == 1) {       // si esta activo el incremento del contador
    cont++;                        // incrementa el contador de ciclos en Uno
  }

if (activar_decremento == 1) {       // si esta activo el incremento del contador
    conta++;                        // incrementa el contador de ciclos en Uno
  }

  if (cont == 10) {                 // cada cuanto tiempo (ciclos)cambia un numero
    cont = 0;                    // inicializa el contador de ciclos
    unidad = unidad + 1;           // incrementa la unidad, primer 7seg
    if (unidad >= 10) {           // cuando la unidad llegue a 10 incrementa la decena
      decena = decena + 1;      // incrementa la decena,  segundo 7seg
      unidad = 0;                 // regresa la unidad a cero
      if (decena >= 10) {         // cuando la decena llegue a 10 incrementa la centena
        centena = centena + 1;
        decena = 0;
        if (centena >= 10) {         // cuando la decena llegue a 10 se inicializa a cero
          centena = 0;
        }
      }
    }
  }

 if (conta == 10) {                 // cada cuanto tiempo (ciclos)cambia un numero
    conta = 0;                    // inicializa el contador de ciclos
    unidad = unidad - 1;           // incrementa la unidad, primer 7seg
    if (unidad == -1) {           // cuando la unidad llegue a 10 incrementa la decena
      decena = decena - 1;      // incrementa la decena,  segundo 7seg
      unidad = 9;                 // regresa la unidad a cero
      if (decena == -1) {         // cuando la decena llegue a 10 incrementa la centena
        centena = centena - 1;
        decena = 9;
        if (centena == -1) {         // cuando la decena llegue a 10 se inicializa a cero
          centena = 9;
        }
      }
    }
  }

  if (conmutador == 0) {    // hace la multiplexacion conmutando entre los dos 7seg  izq y der
    digitalWrite(10, 1);    // enciende el derecho
    digitalWrite(11, 0);    // apaga el izquierdo
    digitalWrite(12, 0);    // apaga el izquierdo
    var = unidad;           // iguala la variable que escribe el numero en el 7seg al valor de la unidad
    conmutador = 1;         // cambia el conmutador para que en el siguiente ciclo cumpla la otra condicion

  }
  else {
    if (conmutador == 1) {
      digitalWrite(10, 0);       // apaga el derecho
      digitalWrite(11, 1);      // enciende el izquierdo
      digitalWrite(12, 0);    // apaga el izquierdo
      var = decena;             // iguala la variable que escribe el numero en el 7seg al valor de la decena
      conmutador = 2;           // cambia el conmutador para que en el siguiente ciclo cumpla la otra condicion
    } else {
      digitalWrite(10, 0);       // apaga el derecho
      digitalWrite(11, 0);      // apaga el izquierdo
      digitalWrite(12, 1);    // enciende el izquierdo
      var = centena;             // iguala la variable que escribe el numero en el 7seg al valor de la decena
      conmutador = 0;           // cambia el conmutador para que en el siguiente ciclo cumpla la otra condicion
    }

  }

  switch (var) {
    case 1:                 //escribe en el 7seg el numero 1
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      break;
    case 2:                //escribe en el 7seg el numero 2
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 0);
      digitalWrite(6, 1);
      digitalWrite(7, 1);
      digitalWrite(8, 0);
      digitalWrite(9, 1);
      break;
    case 3:               //escribe en el 7seg el numero 3
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
      digitalWrite(9, 1);
      break;
    case 4:               //escribe en el 7seg el numero 4
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      break;
    case 5:               //escribe en el 7seg el numero 5
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 0);
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      break;
    case 6:               //escribe en el 7seg el numero 6
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 1);
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      break;
    case 7:              //escribe en el 7seg el numero 7
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      break;
    case 8:              //escribe en el 7seg el numero 8
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 1);
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      break;
    case 9:               //escribe en el 7seg el numero 9
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      break;
    case 0:                //escribe en el 7seg el numero 0
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      digitalWrite(5, 1);
      digitalWrite(6, 1);
      digitalWrite(7, 1);
      digitalWrite(8, 1);
      digitalWrite(9, 0);
      break;
    default:
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
  }
}
