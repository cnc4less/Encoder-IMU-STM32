#define encoderOutputPerRotation 1024 
#define channelA PB13 
#define channelB PB12 
volatile long encoderOutputValue = 0;
int RPM = 0;
// counters for the time to calculate the motor speed
long pre_millis = 0 ;
long cur_millis = 0 ;
void setup() {
  Serial3.begin(115200);
  pinMode(channelA , INPUT_PULLUP);
  pinMode(channelB , INPUT);
  attachInterrupt(channelA, update_encoder, RISING);
  pre_millis = millis() ;
}

void loop() {
    cur_millis = millis ();
    if (cur_millis - pre_millis > 1000) {
      RPM = (float)(encoderOutputValue / encoderOutputPerRotation);
      Serial3.print("Motor speed= ");
      Serial3.println(RPM);
      encoderOutputValue = 0 ;
      pre_millis = cur_millis ;
    }
  Serial3.println(encoderOutputValue);
}
void update_encoder () {
  if (digitalRead(channelA) == HIGH){
	  if(digitalRead(channelB)==HIGH)
	    encoderOutputValue++ ;
  	  else 
	    encoderOutputValue -- ;
   }
}

/*
clockwise
when A on Rising state B is High
     ____      ____      ____      ____ 
____|    |____|    |____|    |____|    |  (((A)))
   ____      ____      ____      ____ 
__|    |____|    |____|    |____|    |    (((B)))
counterclockwise
when A on Rising state B is LOw
   ____      ____      ____      ____ 
__|    |____|    |____|    |____|    |    (((A)))
     ____      ____      ____      ____ 
____|    |____|    |____|    |____|    |  (((B)))
*/
