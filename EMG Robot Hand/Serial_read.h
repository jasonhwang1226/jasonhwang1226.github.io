/* 
 * File:   Serial_read.h
 * Author: Lab User
 *
 * Created on October 20, 2016, 6:11 PM
 */

#ifndef SERIAL_READ_H
#define	SERIAL_READ_H

static struct pt pt_input;
unsigned int sample;


static PT_THREAD(protothread_serial(struct pt *pt))
{
    PT_BEGIN(pt);
    
    while(1)    //Include while loop?
    {
        PT_SPAWN(pt,&pt_input,PT_GetSerialBuffer(&pt_input));   //Stores the value in PT_term_buffer[64]
        
        if(PT_term_buffer[0] == 'D')
        {
            ConfigIntADC10( ADC_INT_ON | ADC_INT_PRI_3 |  ADC_INT_SUB_PRI_0 );   //Enables the ADC interrupt
        }
        

        
    }
    
    PT_END(pt);
} // Serial read thread

#endif	/* SERIAL_READ_H */

