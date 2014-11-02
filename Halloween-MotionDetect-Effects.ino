// Simple Proximity Sensor using Infrared
// Description: Measure the distance to an obstacle using infrared light emitted by IR LED and
//   read the value with a IR photodiode. The accuracy is not perfect, but works great
//   with minor projects.
// Author: Ricardo Ouvina
// Date: 01/10/2012
// Version: 1.0

int IRpin      = A0;          // IR photodiode on analog pin A0
int IRemitter  = 2 ;          // IR emitter LED on digital pin 2
int Smoke      = 3 ;          // Circuit to turn Smoke machine on/off 
int ACSocket   = 4 ;          // Circuit to turn AC Circuit on/off
int LED1       = 5 ;          // Turn on LED Circuit 1
int LED2       = 6 ;          // Turn on LED Circuit 2
int ambientIR;                // variable to store the IR coming from the ambient
int obstacleIR;               // variable to store the IR coming from the object
int value[10];                // variable to store the IR values
int distance;                 // variable that will tell if there is an obstacle or not
int Tripped    = 0 ;

void setup(){
  Serial.begin(9600);          // initializing Serial monitor
  
  pinMode      (IRemitter, OUTPUT );  // IR emitter LED on digital pin 2
  digitalWrite (IRemitter, LOW    );  // set IR LED off
  
  pinMode      (Smoke    , OUTPUT );  // Smoke Machine on digital pin 3
  digitalWrite (Smoke    , LOW    );  // set Smoke Machine off  
  
  pinMode      (ACSocket , OUTPUT );  // AC Socket on digital pin 4
  digitalWrite (ACSocket , HIGH   );  // set AC Socket on
  
  pinMode      (LED1     , OUTPUT );  // LED 1 on digital pin 5
  digitalWrite (LED1     , LOW    );  // set LED 1 off

  pinMode      (LED2     , OUTPUT );  // LED 2 on digital pin 6
  digitalWrite (LED2     , LOW    );  // set LED2 off
  
}

void loop(){
  distance = readIR(10);  // calling the function that will read the distance and passing the "accuracy" to it
  //Serial.println(distance);   // writing the read value on Serial monitor
  //delay(1000);

  if (distance < 1){
       animation();
  }
  
}

void animation(){
  digitalWrite (ACSocket, LOW);
  Serial.println("System tripped!");
  delay (250);
  digitalWrite (Smoke, HIGH);
  delay (3000);
  digitalWrite (LED1, HIGH);
  digitalWrite (LED2, HIGH);
  delay (26750);
  
  digitalWrite (Smoke, LOW);
  digitalWrite (ACSocket, HIGH);
  digitalWrite (LED1, LOW);
  digitalWrite (LED2, LOW);

}

int readIR(int times){
  for(int x=0;x<times;x++){     
    digitalWrite(IRemitter,LOW);           // turning the IR LEDs off to read the IR coming from the ambient
    delay(1);                                             // minimum delay necessary to read values
    ambientIR = analogRead(IRpin);  // storing IR coming from the ambient
    digitalWrite(IRemitter,HIGH);          // turning the IR LEDs on to read the IR coming from the obstacle
    delay(1);                                             // minimum delay necessary to read values
    obstacleIR = analogRead(IRpin);  // storing IR coming from the obstacle
    value[x] = ambientIR-obstacleIR;   // calculating changes in IR values and storing it for future average
  }
 
  for(int x=0;x<times;x++){        // calculating the average based on the "accuracy"
    distance+=value[x];
  }
  return(distance/times);            // return the final value
}


//-- Function to sound a buzzer for audible measurements --//
void buzzer(){
  if (distance>1){
    if(distance>100){ // continuous sound if the obstacle is too close
      digitalWrite(11,HIGH);
    }
    else{  // beeps faster when an obstacle approaches
      digitalWrite(11,HIGH);
      delay(150-distance);  // adjust this value for your convenience
      digitalWrite(11,LOW);
      delay(150-distance);  // adjust this value for your convenience
    }
  }
  else{  // off if there is no obstacle
    digitalWrite(11,LOW);
  }
}
