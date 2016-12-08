/* 
 * File:   Servo_functions.h
 * Author: Krishnaa
 *
 * Created on 3 December, 2016, 11:12 PM
 */

#ifndef SERVO_FUNCTIONS_H
#define	SERVO_FUNCTIONS_H


int difference  = 0;
int angle = 0;



int flag = 0;

void oscillate_motor(int oc)
{  
    if(flag == 1){
        pwm_control = angle_0;        //convert High time to ticks
        flag = 0;
    }
    else{
        pwm_control = angle_180;      
        flag = 1;
    }
    
    
    //Sending the PWM signal
    switch(oc)
    {
        case 1:
            SetDCOC1PWM(pwm_control);
            break;
        case 2:
            SetDCOC2PWM(pwm_control);
            break;
        case 3:
            SetDCOC3PWM(pwm_control);
            break;
        case 4:
            SetDCOC4PWM(pwm_control);
            break;
        case 5:
            SetDCOC5PWM(pwm_control);
            break;
    }
}









void control_motor(int oc, int angle)
{  
    //Calculating the control
    //pwm_control = ((int)(  ((float)angle)  /180.0   )*   ((float)(max_angle - min_angle) ) )      + min_angle    ;
    if(angle == 180)
    {
        pwm_control = angle_180;
    }
    else if(angle == 0)
    {
        pwm_control = angle_0;
    }
    
    //Clamping the control
//    if(pwm_control < min_angle)
//    {
//        pwm_control = min_angle;
//    }
//    else if(pwm_control > max_angle)
//    {
//        pwm_control = max_angle;
//    }
    
    //Sending the PWM signal
    switch(oc)
    {
        case 1:
            SetDCOC1PWM(pwm_control);
            break;
        case 2:
            SetDCOC2PWM(pwm_control);
            break;
        case 3:
            SetDCOC3PWM(pwm_control);
            break;
        case 4:
            SetDCOC4PWM(pwm_control);
            break;
        case 5:
            SetDCOC5PWM(pwm_control);
            break;
    }
}


int lock_motor = 0;


void move_finger(void)
{
    for(i=0 ; i<5 ; i++)
    {
        if(    (finger_state[i] != previous_finger_state[i])     ||   (lag[i]>0)       )
        {
            if( lock_press == 0)    //Just changed state. Start waiting if there is no other motor in use 
            {
                lock_motor = i+1;
                //Make the servo wait for 600ms
                lag[i] = max_lag;       //1200. Twice 600ms. 
                
                    if(finger_state[i] == 1)      //Move the servo
                    {
                        control_motor(i+1,pressed[i]);
                    }
                    else
                    {
                        control_motor(i+1,not_pressed[i]);
                    }
            }
            else        //Already waiting
            {
                lag[i] = lag[i] - 1;
                if(lag[i] <= 0)
                {
                    lag[i] = 0;
                    if(lock_motor == i+1)
                    {
                        lock_motor = 0;
                    }
                }
                
            }
        }
        else    //No lag nor change in the last 600ms
        {
                    if(finger_state[i] == 1)
                    {
                        control_motor(i+1,pressed[i]);
                    }
                    else
                    {
                        control_motor(i+1,not_pressed[i]);
                    }
        }
        
        //Update the previous probability
        previous_finger_state[i] = finger_state[i];
    }
    
    
    
    
    
    
//    for(i=0 ; i<5 ; i++)
//    {
//        if(fix2int16(finger_probability[i]) == 1)
//        {
//            control_motor(i+1,not_pressed[i]);
//        }
//        else
//        {
//            control_motor(i+1,pressed[i]);
//        }
//    }
}

#endif	/* SERVO_FUNCTIONS_H */

