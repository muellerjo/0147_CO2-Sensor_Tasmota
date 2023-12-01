/*
  user_config_override.h - user configuration overrides my_user_config.h for Tasmota

  Copyright (C) 2021  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/

/*
Examples :

// -- Master parameter control --------------------
#undef  CFG_HOLDER
#define CFG_HOLDER        4617                   // [Reset 1] Change this value to load SECTION1 configuration parameters to flash

// -- Setup your own Wifi settings  ---------------
#undef  STA_SSID1
#define STA_SSID1         "YourSSID"             // [Ssid1] Wifi SSID

#undef  STA_PASS1
#define STA_PASS1         "YourWifiPassword"     // [Password1] Wifi password

// -- Setup your own MQTT settings  ---------------
#undef  MQTT_HOST
#define MQTT_HOST         "your-mqtt-server.com" // [MqttHost]

#undef  MQTT_PORT
#define MQTT_PORT         1883                   // [MqttPort] MQTT port (10123 on CloudMQTT)

#undef  MQTT_USER
#define MQTT_USER         "YourMqttUser"         // [MqttUser] Optional user

#undef  MQTT_PASS
#define MQTT_PASS         "YourMqttPass"         // [MqttPassword] Optional password

// You might even pass some parameters from the command line ----------------------------
// Ie:  export PLATFORMIO_BUILD_FLAGS='-DUSE_CONFIG_OVERRIDE -DMY_IP="192.168.1.99" -DMY_GW="192.168.1.1" -DMY_DNS="192.168.1.1"'

#ifdef MY_IP
#undef  WIFI_IP_ADDRESS
#define WIFI_IP_ADDRESS     MY_IP                // Set to 0.0.0.0 for using DHCP or enter a static IP address
#endif

#ifdef MY_GW
#undef  WIFI_GATEWAY
#define WIFI_GATEWAY        MY_GW                // if not using DHCP set Gateway IP address
#endif

#ifdef MY_DNS
#undef  WIFI_DNS
#define WIFI_DNS            MY_DNS               // If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)
#endif

#ifdef MY_DNS2
#undef  WIFI_DNS2
#define WIFI_DNS2           MY_DNS2              // If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)
#endif

// !!! Remember that your changes GOES AT THE BOTTOM OF THIS FILE right before the last #endif !!!
*/


// Define the SDA and SCL pins for I2C
//#define USER_TEMPLATE "{\"NAME\":\"Generic\",\"GPIO\":[1,1,1,1,1,1,1,1,1,1,1,1,1,1],\"FLAG\":0,\"BASE\":18}"  // [Template] Set JSON template
//#define MODULE GENERIC
//#define SUPPORT_IF_STATEMENT   // Add support for IF statement in rules (+4k2 code, -332 bytes mem)  

// To ignore default button behaviour of controlling power outputs you can:
// SetOption73 1
#define USER_BACKLOG "Rule1 1;Rule2 0;Rule3 1;SetOption73 1"

#define USER_RULE1 "ON System#Boot do Power2 on endon ON System#Boot do Rule2 0 endon ON System#Boot do displaytext [l1c1]MTWT CO2-Sensor endon ON System#Boot do ruletimer1 10 ENDON ON System#Boot do ruletimer2 2 ENDON ON rules#timer=1 do Power2 off ENDON ON rules#timer=2 do displaytext [l1c1][z] ENDON ON rules#timer=2 do Rule2 1 ENDON "

// display temperature in display
#define USER_RULE2 "on AHT1X#temperature do displaytext [l1c1]%value% ~dfC endon on AHT1X#humidity do displaytext [l1c10]%value% % endon on MHZ19B#CarbonDioxide do displaytext [l2c1]CO2 %value% ppm endon"

// button steuerung
#define USER_RULE3 "ON Button1#State do Power2 on ENDON ON Button1#State do ruletimer1 10 ENDON ON AHT1X#humidity<51 DO Color 0,255,0 ENDON ON AHT1X#humidity>=51 DO Color 255,255,0 ENDON ON AHT1X#humidity>=65 DO Color 255,0,0 ENDON"

// example from https://tasmota.github.io/docs/Rules/#time-delayed-auto-off-switch


#endif  // _USER_CONFIG_OVERRIDE_H_



#ifndef USE_DISPLAY
#define USE_DISPLAY
#endif

#ifndef USE_AHT1x
#define USE_AHT1x       // [I2cDriver43] Enable AHT10/15 humidity and temperature sensor (I2C address 0x38, 0x39) (+0k8 code)
#endif

#ifndef USE_MHZ19 
#define USE_MHZ19       // Add support for MH-Z19 CO2 sensor (+2k code)
#endif

#ifdef MODULE
#undef MODULE
#endif
#define MODULE                 USER_MODULE   // [Module] Select default model (the list is kModuleNiceList() in file tasmota_template.h) USER_MODULE is the TEMPLATE

#ifdef FALLBACK_MODULE
#undef FALLBACK_MODULE
#endif
#define FALLBACK_MODULE        USER_MODULE   // to Select the default model as FALLBACK when the user does a RESET 1 

#ifdef USER_TEMPLATE
#undef USER_TEMPLATE
#endif
#define USER_TEMPLATE          "{\"NAME\":\"MTWT-CO2_v2\",\"GPIO\":[32,1,416,1,608,640,1,1,1,1,417,418,1,1],\"FLAG\":0,\"BASE\":18}" // [Template] Set JSON template
//#define USER_TEMPLATE          "{\"NAME\":\"ESP01-Dimmer\",\"GPIO\":[1,1,416,1,1,1,1,1,1,1,1,1,1,1],\"FLAG\":0,\"BASE\":18}" // [Template] Set JSON template

// https://tasmota.github.io/docs/Components/#gpio-overview
// 32 Button
// 608 SDA
// 640 SCL
// 288 LED
// 416 PWM1 - GPIO2   D4 R
// 417 PWM2 - GPIO14  D5 G
// 418 PWM3 - GPIO15  D8 B
// 1408 MHZ Tx
// 1440 MHZ Rx

#define displaymode 0


