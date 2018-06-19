#ifndef LOOP_freq_h
#define LOOP_freq_h
#include <Arduino.h>  

//Working properly up to 70min. Around 70min ther will be small glitch because of counter overflow.
class LOOP_freq {
public:
  //Constructor, setup loop delay
  LOOP_freq(uint8_t loop_delay_ms): loop_delay_ms(loop_delay_ms) {};
    
  //run as a first operation inside loop
  inline void loop_start() {  
    start_tp_us = micros();
    idle_per_us = start_tp_us - end_tp_us;
  };

  //run as a last operation inside loop
  inline void loop_end() {
    end_tp_us = micros();
    busy_per_us = end_tp_us - start_tp_us;
    delay(loop_delay_ms);
  };
  
  inline uint8_t get_cpu_usage(){
    return busy_per_us * 100uL / (busy_per_us + idle_per_us);
  };

  inline uint16_t get_loop_frequency(){
    return 1000000uL / (busy_per_us + idle_per_us);
  };
  
  inline void set_loop_delay(uint8_t delay_ms) {loop_delay_ms = delay_ms;};
  
private:
  uint8_t loop_delay_ms;
  
  uint32_t start_tp_us;
  uint32_t end_tp_us;

  uint16_t busy_per_us;
  uint16_t idle_per_us;
};

#endif