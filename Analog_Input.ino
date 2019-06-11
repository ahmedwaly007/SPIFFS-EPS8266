#include "FS.h"

int ADCpin= A0;
int analogValue;
//float result;

int id=1;

void write_SPIFFS(char *file_name, int n_readings, int t_delay);
void read_SPIFFS(char *file_name, int n_readings);




void setup() {
  Serial.begin(9600);
  SPIFFS.begin();
  Serial.println("Formating...");
  SPIFFS.format();
  Serial.println("Spiffs formatted");
  write_SPIFFS("/temp.txt", 20, 300);
  read_SPIFFS("/temp.txt", 20);
}

void loop() 
{
}

void write_SPIFFS(char *file_name, int n_readings, int t_delay){
  File f = SPIFFS.open(file_name, "w");
  if (!f){
    Serial.println("file open failed");
  }
  Serial.println("Writing to SPIFFS file...");

  for (int i=1; i<=n_readings; i++){
    
    analogValue = analogRead(ADCpin); 
    
    f.print(analogValue);

    delay(t_delay);
  }
  Serial.println("Readings received");
  
  f.close();  
}

void read_SPIFFS(char *file_name, int n_readings){
  File f = SPIFFS.open(file_name, "r");
  if (!f) {
      Serial.println("file open failed");
  }  Serial.println("Reading from SPIFFS file ...");

  for (int i=1; i<=n_readings; i++){
    String s=f.readStringUntil('\n');
    Serial.println(s);
    s=f.readStringUntil('\n');
    Serial.println(s);
  }

  Serial.println("Reading done.");
  
}
