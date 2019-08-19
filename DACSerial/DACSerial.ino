#include <SPI.h>
#include "AD5790.h"

#define HANDLER_ENTRY(NAME, np) { #NAME, handle_ ## NAME, np}

int handle_INIT(int argc, String argv[]);
int handle_SET(int argc, String argv[]);
int handle_READ(int argc, String argv[]);
int handle_RAMP(int argc, String argv[]);
int handle_HELP(int argc, String argv[]);
int handle_ERR(int argc, String argv[]);
void process_command(String cmd);

typedef int (*handler_function)(int argc, String argv[]);

typedef struct handler_entry
{
    String handler_name;
    handler_function func;
    int num_params;
} handler_entry;

handler_entry handlers[] = {
                                HANDLER_ENTRY(INIT, 0), //The number of parameters
                                HANDLER_ENTRY(SET, 2), 
                                HANDLER_ENTRY(READ, 1), 
                                HANDLER_ENTRY(RAMP, 4), 
                                HANDLER_ENTRY(HELP, 0),
                                HANDLER_ENTRY(ERR, 0),
                            };

int num_handlers = sizeof(handlers) / sizeof(handler_entry);

String cmd_str;

AD5790 dac1 = AD5790(2);
AD5790 dac2 = AD5790(3);
AD5790 dac3 = AD5790(4);
AD5790 dac4 = AD5790(5);


AD5790 dacs[4] = {dac1, dac2, dac3, dac4};

int num_dacs = sizeof(dacs) / sizeof(AD5790);

void setup() {
  /* Pin Configuration
   * DAC1 - 4
   * DAC2 - 10
   * DAC3 - 12
   * DAC4 - 3
   */
  SPI.begin();
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  
  Serial.begin(9600);
  Serial.println("Setting up server");
}

void loop() {
  while (Serial.available() > 0) {
    char received = Serial.read();
    cmd_str += received;
    if (received == '\n') {
      Serial.println(cmd_str);
      process_command(cmd_str);
      cmd_str = "";
    }
  }
}


void process_command(String cmd) {
  String argv[10];
  int argc = 0;
  int p1 = 0, p2 = 0;
  int dac = 0;
  long bitcode = 0;
  int increment = 0;
  while((argc < 10) && (cmd[p1] != '\n')) {
    while((cmd[p2] != ' ') && (cmd[p2] != '\n') && (cmd[p2] != '\r')) {
      p2++;
    }
    argv[argc] = cmd.substring(p1,p2);
    argc++;
    if (cmd[p2] == '\n') {
      break;
    }

    p2++;
    p1 = p2;
  }

  int i;
  for (i = 0; i < num_handlers - 1; i++) {
    if (argv[0] == handlers[i].handler_name) {
      if (argc > handlers[i].num_params) {
        handlers[i].func(argc, argv);
      } else {
        handle_ERR(argc, argv);
      }
      break;
    }
  }
  if (i == num_handlers - 1) {
    handlers[i].func(argc, argv);
  }
}

int handle_INIT(int argc, String argv[])
{
  int dac_num = argv[1].toInt();
  Serial.print("Initialization of DAC ");
  Serial.println(dac_num); 
  /* switch case doesn't work so don't change "if" statements
   * You would need to change pin & sync if you use different Arduino pins
   */
    if (dac_num == 1) {
    int pin = 4;
    int sync = 4;
    dacs[0].initialize_DAC(4,4);
    dacs[0].read_DAC_register(4);
    delay(20);
    Serial.println("Initialization complete");
    }
  else if (dac_num == 2){
    int pin = 10;
    int sync = 10;
    dacs[1].initialize_DAC(10,10);
    dacs[1].read_DAC_register(10);
    delay(20);
    Serial.println("Initialization complete");
    }
  else if (dac_num == 3) {
    int pin = 12;
    int sync = 12;
    dacs[2].initialize_DAC(12,12);
    dacs[2].read_DAC_register(12);
    delay(20);
    Serial.println("Initialization complete"); 
    }
  else if (dac_num == 4) {
    int pin = 3;
    int sync = 3;
    dacs[3].initialize_DAC(3,3);
    dacs[3].read_DAC_register(3);
    delay(20);
    Serial.println("Initialization complete");
  }
  else {
    Serial.println("Error: Specify DAC: INIT [DAC#]");
    return 0;
    }
}

int handle_SET(int argc, String argv[])
{
  Serial.println("SET");
  int dac_num = argv[1].toInt();
  long dac_val = argv[2].toInt();
  if (dac_num == 1) {
    int pin = 4;
    int _sync = 4;
    long rc = dacs[dac_num - 1].set_value(4,dac_val); 
    Serial.println(BITCODE_TO_DAC(rc)); 
    Serial.println("SET COMPLETE");
    }
  else if (dac_num == 2){
    int pin = 10;
    int _sync = 10;
    long rc = dacs[dac_num - 1].set_value(10,dac_val);
    Serial.println(BITCODE_TO_DAC(rc)); 
    Serial.println("SET COMPLETE"); 
    }
  else if (dac_num == 3) {
    int pin = 12;
    int _sync = 12; 
    long rc = dacs[dac_num - 1].set_value(12,dac_val);
    Serial.println(BITCODE_TO_DAC(rc)); 
    Serial.println("SET COMPLETE");
    }
  else if (dac_num == 4) {
    int pin = 3;
    int _sync = 3;
    long rc = dacs[dac_num - 1].set_value(3,dac_val);
    Serial.println(BITCODE_TO_DAC(rc)); 
    Serial.println("SET COMPLETE");
    }
  else {
    Serial.println("Error: Specify DAC: SET [DAC#] [BITCODE]");
    return 0;
    }
  
}


int handle_READ(int argc, String argv[])
{
  Serial.print("READ ");
  int dac_num = argv[1].toInt();
  Serial.println(dac_num); 
  
  if (dac_num == 1) {
    int pin = 4;
    int _sync = 4;
    long rc = dacs[dac_num - 1].read_DAC_register(4);
  Serial.println(BITCODE_TO_DAC(rc)); //bitcode returned
  float returnVolt = ((BITCODE_TO_DAC(rc) - 132536)/13225);
  Serial.println(returnVolt);
    }
  else if (dac_num == 2){
    int pin = 10;
    int _sync = 10;
    long rc = dacs[dac_num - 1].read_DAC_register(10);
  Serial.println(BITCODE_TO_DAC(rc)); //bitcode returned
  float returnVolt = ((BITCODE_TO_DAC(rc) - 132536)/13225);
  Serial.println(returnVolt);
    }
  else if (dac_num == 3) {
    int pin = 12;
    int _sync = 12; 
    long rc = dacs[dac_num - 1].read_DAC_register(12);
  Serial.println(BITCODE_TO_DAC(rc)); //bitcode returned
  float returnVolt = ((BITCODE_TO_DAC(rc) - 132536)/13225);
  Serial.println(returnVolt);
    }
  else if (dac_num == 4) {
    int pin = 3;
    int _sync = 3;
    long rc = dacs[dac_num - 1].read_DAC_register(3);
  Serial.println(BITCODE_TO_DAC(rc)); //bitcode returned
  float returnVolt = ((BITCODE_TO_DAC(rc) - 132536)/13225);
  Serial.println(returnVolt);
    }
}


int handle_RAMP(int argc, String argv[])
{
  int dac_num = argv[1].toInt();
  long dac_val = argv[2].toInt();
  long step_size = argv[3].toInt();
  int step_time = argv[4].toInt();
  if (dac_num == 1) {
    int pin = 4;
    int _sync = 4;
    dacs[dac_num - 1].ramp(dac_val, step_size, step_time);
    Serial.println("Ramp in progress ");
    }
  else if (dac_num == 2){
    int pin = 10;
    int _sync = 10;
    dacs[dac_num - 1].ramp(dac_val, step_size, step_time);
    Serial.println("Ramp in progress ");
    }
  else if (dac_num == 3) {
    int pin = 12;
    int _sync = 12; 
    dacs[dac_num - 1].ramp(dac_val, step_size, step_time);
    Serial.println("Ramp in progress ");
    }
  else if (dac_num == 4) {
    int pin = 3;
    int _sync = 3;
    dacs[dac_num - 1].ramp(dac_val, step_size, step_time);
    Serial.println("DAC RAMP DONE");
    }
  else {
    Serial.println("Invalid Dac Number");
    }
}


int handle_HELP(int argc, String argv[])
{
  print_help_message();
  return 0;
}


int handle_ERR(int argc, String argv[])
{
  Serial.println("Invalid command");
  print_help_message();
  return 0;
}


void print_help_message() {
  Serial.println("Usage: [COMMAND] [PARAM1] [PARAM2] ...");
  Serial.println("Set voltage: SET [DAC#] [BITCODE]");
  Serial.println("Ramp voltage: RAMP [DAC#] [BITCODE] [STEP_SIZE] [STEP_TIME]");
  Serial.println("Read voltage: READ [DAC#]");
  Serial.println("Initialize dacs: INIT [DAC#]");
  Serial.println("Help: HELP");
  Serial.println("1 bit = 38 microVolts");
  Serial.println("1 milliVolt = 26.2 bits");
}
