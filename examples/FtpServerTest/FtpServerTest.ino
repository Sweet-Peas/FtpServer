/*
 * This sketch demonstrate the use of FTP server library
 * Copyright (c) 2014-2015 by Jean-Michel Gallego
 */

#include <SPI.h>
#include <Ethernet.h>
#include <FatLib.h>
#if FAT_SYST == 0
  #include <SdFat.h>
#else
  #include <FatFs.h>
#endif
#include <FtpServer.h>

// Define Chip Select for your SD card according to hardware 
#define CS_SDCARD 4  // SD card reader of Ehernet shield
// #define CS_SDCARD 52

// Define Reset pin for W5200 (set to -1 for an other ethernet chip)
// #define P_RESET -1
#define P_RESET 8

FtpServer ftpSrv;

// Mac address of ethernet adapter
// byte mac[] = { 0x90, 0xa2, 0xda, 0x00, 0x00, 0x00 };
byte mac[] = { 0x00, 0xaa, 0xbb, 0xcc, 0xde, 0x04 };

// IP address of FTP server
// IPAddress serverIp( 192, 168, 128, 211 );
IPAddress serverIp( 192, 168, 1, 82 );

/*******************************************************************************
**                                                                            **
**                               INITIALISATION                               **
**                                                                            **
*******************************************************************************/

void setup()
{
  Serial.begin(9600);
  Serial.println(F("=== Test of FTP Server ===="));

  // If other chips are connected to SPI bus, set to high the pin connected to their CS
  pinMode( 4, OUTPUT ); 
  digitalWrite( 4, HIGH );

  // Initialize the SD card.
  Serial.print(F("Mount the SD card with library "));
  #if FAT_SYST == 0
    Serial.print(F("SdFat ... "));
  #else
    Serial.print/F("FatFs ... "));
  #endif

  if( ! FAT.begin( CS_SDCARD, SPI_FULL_SPEED ))
  {
    Serial.println(F("Unable to mount SD card"));
    while( true ) ;
  }
  Serial.println(F("ok"));

  // Send reset to W5200
  if( P_RESET > -1 )
  {
    pinMode( P_RESET, OUTPUT );
    digitalWrite( P_RESET, LOW );
    delay( 200 );
    digitalWrite( P_RESET, HIGH );
    delay( 200 );
  }

  // Initialize the network
  // Ethernet.begin( mac, serverIp );
  // /*
  if( Ethernet.begin( mac ) == 0 )
  {
    Serial.println(F("Can't connect to network!"));
    while( 1 ) ;
  }
  serverIp = Ethernet.localIP();
  Serial.print(F("IP address of server: "));
  Serial.print(serverIp[0]); Serial.write('.');
  Serial.print(serverIp[1]); Serial.write('.');
  Serial.print(serverIp[2]); Serial.write('.');
  Serial.print(serverIp[3]); Serial.println();
  // */
  
  // Initialize the FTP server
  ftpSrv.init();
}

/*******************************************************************************
**                                                                            **
**                                 MAIN LOOP                                  **
**                                                                            **
*******************************************************************************/

void loop()
{
  ftpSrv.service();
 
  // more process... 
}

