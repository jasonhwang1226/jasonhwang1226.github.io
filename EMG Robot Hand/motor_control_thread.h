/* 
 * File:   motor_control_thread.h
 * Author: Lab User
 *
 * Created on October 20, 2016, 6:26 PM
 */

#ifndef MOTOR_CONTROL_THREAD_H
#define	MOTOR_CONTROL_THREAD_H



int print = 0;
static unsigned int sample_max = 10000;
int sample;
char sample_string[10];
unsigned int sample_counter = 0;
int j = 0;
int m = 0;

void print_values(void)
{
    if(print == 0)
    {
        sample = fix2int16(filter_output[1]);   // read the result of channel 4 conversion from the idle buffer
        
        
            //Output to serial at each ARC IRQ
        itoa(sample_string, sample, 10);  
        for(j = 0; sample_string[j] != '\0' ; j++)               //Send it over //Might not be right
        {
            while(UARTTransmitterIsReady(UART2) == 0);
            UARTSendDataByte(UART2, sample_string[j]);
        }        
        while(UARTTransmitterIsReady(UART2) == 0);       //New line
        UARTSendDataByte(UART2, '\n');
        
        for(m=0 ; m < j ; m++)
        {
            while(UARTTransmitterIsReady(UART2) == 0);
            UARTSendDataByte(UART2, backspace);
        }
        sample_counter++;

        //Check for max_samples            
        if(sample_counter == sample_max)
        {
            sample_counter = 0;
            while(UARTTransmitterIsReady(UART2) == 0);       //End
            UARTSendDataByte(UART2, 'Z');
            while(UARTTransmitterIsReady(UART2) == 0);       //New line
            UARTSendDataByte(UART2, '\n');
            while(UARTTransmitterIsReady(UART2) == 0);
            UARTSendDataByte(UART2, backspace);
            print = 0;
        }
    }
}








static PT_THREAD(protothread_motor_control(struct pt *pt))
{
    PT_BEGIN(pt);
      

    while(1)
    {
       //control_motor(5,pressed[4]); 
       PT_YIELD_TIME_msec(600); 
    }
    PT_END(pt);
} // motor control thread


#endif	/* MOTOR_CONTROL_THREAD_H */

