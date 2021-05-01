//WeMos D1 R1 (ESP8266 Boards 2.5.2), upload 921600, 80MHz, COM:7,WeMos D1R1 Boards 2
//Program: Creates SD card file, opens, writes, prints out
//WeMos Micro SD Shield uses: 3V3, G & pins:
//D5 = CLK       Clock
//D6 = MISO      master in, slave out (primary in, secondary out)
//D7 = MOSI      master out, slave in (primary out, secondary in)
//D8 = CS        Chip select
//SD library --> 8.3 filenames (not case-sensitive, A.txt = a.txt)
//20210323 By TSBrownie.  For non-commercial use only.
#include <SD.h>               //SD card library
#include <SPI.h>              //Serial Peripheral Interface bus lib for COMM, SD com
File diskFile;                //Link to file name (file handle)
String FName = "SDfile1.txt"; //SD card file name to create / write / read
String testData = "YYYYMMDD,This, is, a, test";        //Data to write to SD "disk"

void openSD(){
  Serial.println(); Serial.println("Open SD card");    //User message
  if (!SD.begin(4)) {                                  //If not open, print error msg
    Serial.println("Open SD card failed");
    return;
  }
  Serial.println("SD Card open");
}

void openWriteFile(){ //Open file. Only one at a time.  Must close this one before opening another.
  diskFile = SD.open(FName, FILE_WRITE);     //Open at end for write
}

void openReadFile(){ //Open file. Only one at a time.  Must close this one before opening another.
  diskFile = SD.open(FName, FILE_READ);      //Open at beginning for read
}

void print2File(){
  if (diskFile) {                            //If file there & opened --> write
    diskFile.println(testData);              //Print test text to file
    diskFile.close();                        //Close file, flush buffer (reliable but slow)
  } else {                                   //File didn't open
    Serial.println("Error opening file for write");
  }
}

void getRecordFile(){                        //Get 1 record from SD file
  if (diskFile) {                            //If file available
    Serial.write(diskFile.read());           //Read, then write to COM
  } else {                                   //File didn't open
      Serial.println("Error opening file for read");
  }
}

void setup() {
  Serial.begin(74880);                       //Open serial com (74880, 38400, 115200)                      
  openSD();                                  //Open SD card
  openWriteFile();                           //Open user SD file for write
  print2File();                              //Append print data to SD file
  openReadFile();                            //Open SD file at beginning to read
  while (diskFile.available()) {             //Read SD file until EOF
    getRecordFile();                         //Get 1 record / line from SD file
  }
  diskFile.close();                          //Close SD file
}

void loop() {
  //Enter your code to do whatever
}
