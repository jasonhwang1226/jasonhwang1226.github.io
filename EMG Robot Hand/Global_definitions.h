
#ifndef GLOBAL_VARIABLES_H
#define	GLOBAL_VARIABLES_H


#define	SYS_FREQ 4000000;                 // config.h sets 40 MHz
    // Open the desired DMA channels.
#define dmaChn0     0
#define dmaChn1     1
#define dmaChn2     2



//Fixed point arithmetic

// === the fixed point macros ========================================
typedef signed int fix16 ;
#define multfix16(a,b) ((fix16)(((( signed long long)(a))*(( signed long long)(b)))>>16)) //multiply two fixed 16:16
#define float2fix16(a) ((fix16)((a)*65536.0)) // 2^16
#define fix2float16(a) ((float)(a)/65536.0)
#define fix2int16(a)    ((int)((a)>>16))
#define int2fix16(a)    ((fix16)((a)<<16))
#define divfix16(a,b) ((fix16)((((signed long long)(a)<<16)/(b)))) 
#define sqrtfix16(a) (float2fix16(sqrt(fix2float16(a)))) 
#define absfix16(a) abs(a)
 fix16 fix16_zero =   0;        //0 equivalent
 fix16 fix16_one =   65536;     //1 equivalent











//Define threads
static struct pt pt_serial, pt_TFT_display, pt_motor_control ;     
int i;
int j;

// string buffer used to output to TFT
char tft_buffer[60];    














//Checking for time period
 int begin_time = 0;
int execution_time = 0;

//Timer config for ADC
//static int filter_sample_rate = 1500; // ISR called at 26.67 kHz. Bruce's choice.  Gives 13.335 kHz for Fs/2. 
 static int filter_sample_rate = 20000;
 
//PWM variables & Times
int angle_0 = 1350;  // 540 us for 0 degrees
int angle_180 = 6250;   // 2500 us for 180 degrees
int pwm_control = 0;    //pwm_control for the motors
int PWM_50Hz = 50000;       //prescalar 16 -> 800,000/16 = 50,000  Thus the timer runs out at 50 Hz. 

//Servo constants for movement
int not_pressed[5] = {180,180,180,0,0};
int pressed[5] = {0,0,0,180,180};
 
 //Servo Lag variables
 fix16 previous_finger_state[5] = {0,0,0,0,0};
 int wait[5] = {0,0,0,0,0};
 int lag[5] = {0,0,0,0,0};
 const int max_lag = 300;

 





int max_int(int x, int y)
{
    if(x >= y)
    {
        return x;
    }
    else
    {
        return y;
    }
}


float max_float(float x, float y)
{
    if(x >= y)
    {
        return x;
    }
    else
    {
        return y;
    }
}



#endif	/* GLOBAL_VARIABLES_H */

