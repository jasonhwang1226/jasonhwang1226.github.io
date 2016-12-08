/* 
 * File:   TFT_display_thread.h
 * Author: Lab User
 *
 * Created on October 20, 2016, 6:24 PM
 */

#ifndef TFT_DISPLAY_THREAD_H
#define	TFT_DISPLAY_THREAD_H




static PT_THREAD(protothread_TFT_display(struct pt *pt))
{
    PT_BEGIN(pt);
    
    while(1)
    {
//        output_TFT_float(30,10,fix2float16(finger_probability[0]));
//        output_TFT_float(30,40,fix2float16(finger_probability[1]));
//        output_TFT_float(30,100,fix2float16(finger_probability[2]));
//        output_TFT_float(30,140,fix2float16(finger_probability[3]));
//        output_TFT_float(30,180,fix2float16(finger_probability[4]));
//        output_TFT_int(100,10,finger_state[0]);
//        output_TFT_int(100,40,finger_state[1]);
//        output_TFT_int(100,100,finger_state[2]);
//        output_TFT_int(100,140,finger_state[3]);
//        output_TFT_int(100,180,finger_state[4]);
        output_TFT_int(100,140,indicator);
        output_TFT_int(200,10,changes_finger[0]);
        output_TFT_int(200,40,changes_finger[1]);
        output_TFT_int(200,80,changes_finger[2]);
        output_TFT_int(200,100,changes_finger[3]);
        output_TFT_int(200,140,changes_finger[4]);
////        output_TFT_int(30,100,fix2int16(filter_output[0]));
////        output_TFT_int(30,200,fix2int16(filter_output[1]));
          output_TFT_int(30,100,fix2int16(filter_output[0]));
          output_TFT_int(30,200,fix2int16(filter_output[1]));

//        output_TFT_int(30,100,fix2int16(current_input[0]));
//        output_TFT_int(30,200,fix2int16(current_input[1]));
        
//        
        PT_YIELD_TIME_msec(30); 
    }    
    
    PT_END(pt);
} // TFT display thread

#endif	/* TFT_DISPLAY_THREAD_H */

