#include "Arduino.h"
#include <Time.h>
#include <EDB.h>
#include <SD.h>
 
File dbFile;
#define TABLE_SIZE 1024
struct Entry {
  int timestamp;
  int value;
} 
entry;
 
void writer(unsigned long address, byte data)
{
  dbFile.seek(address); 
  dbFile.write(data); 
  dbFile.flush();
}
 
byte reader(unsigned long address)
{
  dbFile.seek(address); 
  return dbFile.read(); 
}
 
 
EDB db(&writer, &reader);
 
void setup()
{
  Serial.begin(9600);
    
  Serial.print("Initializing SD card...");
   
  pinMode(10, OUTPUT);
   
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    return;
  }
   
  Serial.println("initialization done.");
   
  Serial.println("Opening data.db ...");
  dbFile = SD.open("data.db", FILE_WRITE);
   
  db.create(0, TABLE_SIZE, sizeof(entry));
   
  Serial.print("Record Count: ");
  Serial.println(db.count());
  Serial.println("Creating Records...");
//CODE TO PRINT DATA  
//  Serial.print("Record Count: "); Serial.println(db.count());
//  for (recno = 1; recno < RECORDS_TO_CREATE; recno++)
//  {
//    db.readRec(recno, EDB_REC logEvent);
//    Serial.print("ID: "); Serial.println(logEvent.id);
//    Serial.print("Temp: "); Serial.println(logEvent.temperature);   
 // }
}
 
 
void loop()
{
  delay(1000);
  entry.timestamp = millis()/1000; 
  //entry.value = reading;//wherever the input comes from
  db.appendRec(EDB_REC entry);
  
}
