#include "LOOP_freq.h"

#define loop_delay_ms 1
LOOP_freq loop_freq(loop_delay_ms);

void setup() {
  // serial to display data
  Serial.begin(115200);
  while(!Serial) {}
}

void loop() {
  loop_freq.loop_start();

  work_to_be_done();
  
  Serial.print(loop_freq.get_cpu_usage());   
  Serial.print("%\t");  
  Serial.print(loop_freq.get_loop_frequency());
  Serial.print("Hz\n");

  loop_freq.loop_end();
}

void work_to_be_done(){
  delay(10);
}

