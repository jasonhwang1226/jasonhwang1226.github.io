/* 
 * File:   ISR_routines.h
 * Author: Lab User
 *
 * Created on October 21, 2016, 3:45 PM
 */

#ifndef ISR_ROUTINES_H
#define	ISR_ROUTINES_H





void __ISR(_TIMER_3_VECTOR, ipl2) Timer2Handler(void)
{
    // clear the interrupt flag
    mT3ClearIntFlag();
    begin_time = ReadTimer4();
        for(i=0 ; i<2 ; i++)      //Calculates the averaged value of the signal input
        {
            current_input[i] = int2fix16((int)(ReadADC10(i)));
            
            //Moving average filter
            lowpass_filter(i);      //The output values are stored as global variables
            
            
            //print_values();
            
            //Updates the history
            update_history(i);
        }
        
        
        //Neural network
        //run_neural_network();       //Finds output from filter_output[] and stores it in global variable finger[]
        run_thresholding();

        //Move finger servo
       move_finger();
       
       execution_time = (int)(ReadTimer4()) - begin_time;
    
    
}







































//
//static unsigned int sample_max = 10;
//unsigned int sample;
//char sample_string[10];
//unsigned int sample_counter = 0;
//int j = 0;
//
//
//// === ISR ============================================
// volatile short current_capture = 0, previous_capture = 0;
// volatile short  capture_period = 0;
//// == Capture 1 ISR ====================================================
//void __ISR(_ADC_VECTOR   , ipl3) ADCHandler(void)
//{
//    // clear the interrupt flag
//    mAD1ClearIntFlag();
//    output_TFT_string(30,100,"ISR!");
//    // read the ADC
//    // read the first buffer position
//    sample = ReadADC10(0);   // read the result of channel 4 conversion from the idle buffer
//
//    //Output to serial at each ARC IRQ
//    itoa(sample_string, sample, 10);  
//    for(j = 0; sample_string[j] != '\0' ; j++)               //Send it over //Might not be right
//    {
//        while(UARTTransmitterIsReady(UART2) == 0);
//        UARTSendDataByte(UART2, sample_string[j]);
//    }        
//    while(UARTTransmitterIsReady(UART2) == 0);       //New line
//    UARTSendDataByte(UART2, '\n');
//    sample_counter++;
//                
//    //Check for max_samples            
//    if(sample_counter == sample_max)
//    {
//        sample_counter = 0;
//        while(UARTTransmitterIsReady(UART2) == 0);       //End
//        UARTSendDataByte(UART2, 'Z');
//        while(UARTTransmitterIsReady(UART2) == 0);       //New line
//        UARTSendDataByte(UART2, '\n');
//        ConfigIntADC10( ADC_INT_OFF ); 
//    }
//}

#endif	/* ISR_ROUTINES_H */

