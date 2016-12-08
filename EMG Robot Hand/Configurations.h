#ifndef CONFIGURATIONS_H
#define	CONFIGURATIONS_H










void setup_config()
{
    //Digital, thread and interrupt setup. 
    SYSTEMConfigPerformance(PBCLK);
    ANSELA = 0; ANSELB = 0; CM1CON = 0; CM2CON = 0;
    PT_setup();    // === config threads ==========  // turns OFF UART support and debugger pin
    INTEnableSystemMultiVectoredInt();    // === setup system wide interrupts  ========
  
     // init the display
    tft_init_hw();
    tft_begin();
    tft_fillScreen(ILI9340_BLACK);
    tft_setRotation(3); //240x320 vertical display // Use tft_setRotation(1) for 320x240
    
    

      //SETUP ADC
   /////////////////////////////////////////////////////////////////
        // configure and enable the ADC
	CloseADC10();	// ensure the ADC is off before setting the configuration

	// define setup parameters for OpenADC10
	// Turn module on | ouput in integer | trigger mode auto | enable autosample
        // ADC_CLK_AUTO -- Internal counter ends sampling and starts conversion (Auto convert)
        // ADC_AUTO_SAMPLING_ON -- Sampling begins immediately after last conversion completes; SAMP bit is automatically set
        // ADC_AUTO_SAMPLING_OFF -- Sampling begins with AcquireADC10();
        #define PARAM1  ADC_FORMAT_INTG32 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON //

	// define setup parameters for OpenADC10
	// ADC ref external  | disable offset test | enable scan mode | do 1 sample | use single buf | alternate mode off
	#define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_2 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF
        //
	// Define setup parameters for OpenADC10
        // use peripherial bus clock | set sample time | set ADC clock divider
        // ADC_CONV_CLK_Tcy2 means divide CLK_PB by 2 (max speed)
        // ADC_SAMPLE_TIME_5 seems to work with a source resistance < 1kohm
        #define PARAM3 ADC_CONV_CLK_PB | ADC_SAMPLE_TIME_5 | ADC_CONV_CLK_Tcy2 //ADC_SAMPLE_TIME_15| ADC_CONV_CLK_Tcy2

	// define setup parameters for OpenADC10
	// set AN11 and  as analog inputs
	#define PARAM4	 ENABLE_AN2_ANA|ENABLE_AN3_ANA  // pin 2 &pin 3

	// define setup parameters for OpenADC10
	// do not assign channels to scan
	#define PARAM5	~(SKIP_SCAN_AN2|SKIP_SCAN_AN3)

	// use ground as neg ref for A | use AN11 for input A     
	// configure to sample AN11 
	SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF ); // configure to sample AN1 
	OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 ); // configure ADC using the parameters defined above

	EnableADC10(); // Enable the ADC
    /////////////////////////////////////////////////////////////////
    
    
    
    //Output comparators setup
    OpenOC1(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE , pwm_control, pwm_control); 
    OpenOC2(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE , pwm_control, pwm_control); 
    OpenOC3(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE , pwm_control, pwm_control); 
    OpenOC4(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE , pwm_control, pwm_control); 
    OpenOC5(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE , pwm_control, pwm_control); 
    PPSOutput(1, RPB7, OC1);    // OC1 is PPS group 1, map to RPB7 (pin 16)
    PPSOutput(2, RPB11, OC2);    // OC2 is PPS group 2, map to RPB11 (pin 22)
    PPSOutput(4, RPB10, OC3);    // OC3 is PPS group 4, map to RPB10 (pin 21)
    PPSOutput(3, RPA2, OC4);    // OC4 is PPS group 3, map to RPA2 (pin 9)
    PPSOutput(3, RPB13, OC5);    // OC5 is PPS group 3, map to RPB13 (pin 24)
    

    
    //Timer setup   
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_16, PWM_50Hz);  //for the Output comparator 
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_4, filter_sample_rate);   //to implement filter
    ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_2);
    mT3ClearIntFlag(); // and clear the interrupt flag
    OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_4, 65535);   //to check timing constraints

	

 
}


#endif	/* CONFIGURATIONS_H */

