//Configuration libs (Include only once!!)                    
#include "config.h"                  

//TFT libs (Include only once!))
#include "tft_master.h"
#include "tft_gfx.h"

//Protothread libs (Include only once!))
#include "pt_cornell_1_2_1.h"  


//Inbuilt libs 
#include <stdlib.h>
#include <plib.h>
#include <math.h>



//Global declarations (can be included multiple times)
#include "Global_declarations.h"

//Global variables (Include only once!!)
#include "Global_definitions.h"

//Peripheral configurations (Include only once!)
#include "Configurations.h"


//Debugging functions  and helper functions(Include only once! )
#include "our_debugger.h"
#include "Lowpass_filter.h"
#include "Neural_network.h"
#include "Servo_functions.h"




//Thread files
//#include "Serial_read.h"
#include "TFT_display_thread.h"
#include "motor_control_thread.h"

//ISRs
#include "ISR_routines.h"





// === Main  ======================================================
void main(void) {
  
  setup_config();
  
  
  
  
// init the threads
  //PT_INIT(&pt_serial);
  PT_INIT(&pt_TFT_display);
  //PT_INIT(&pt_motor_control);


  // round-robin scheduler for threads
  while(1)
  {
      //PT_SCHEDULE(protothread_serial(&pt_serial));
      PT_SCHEDULE(protothread_TFT_display(&pt_TFT_display));
      //PT_SCHEDULE(protothread_motor_control(& pt_motor_control));
  }
  
  } // main

// === end  ======================================================
