/* 
 * File:   Lowpass_filter.h
 * Author: Krishnaa
 *
 * Created on 3 December, 2016, 11:13 PM
 */

#ifndef LOWPASS_FILTER_H
#define	LOWPASS_FILTER_H


//Filter variables
const int averager_length = 127;
fix16 input_history[127][2] = 
{{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0},
{0,0}
};   //An array of the previous 15 entries. 
fix16 current_input[2] = {0,0}; //Current ADC read from buffer
fix16 filter_output[2] = {0,0}; //Filter_output (Averager)

void lowpass_filter(int electrode)         //Does the moving averager which is a low pass filter. Electrode is 0 or 1
{
    filter_output[electrode] = current_input[electrode];
    
    for(j = 0; j < averager_length ; j++)
    {
        filter_output[electrode] = filter_output[electrode] + input_history[j][electrode];
    }
    
    filter_output[electrode] = divfix16(filter_output[electrode],int2fix16(averager_length + 1));    //To divide by 32. 
}



void update_history(int electrode)
{
    
    for(j=(averager_length-1); j>0 ; j--)
    {
        input_history[j][electrode] = input_history[j-1][electrode];
    }
    
    input_history[0][electrode] = current_input[electrode];
}






//Filter variables
const int probability_averager_length = 31;
fix16 probability_history[31][5] = 
{{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0}
};   //An array of the previous 15 entries. 


fix16 averaged_probability[5] = {0,0,0,0,0};
fix16    finger_probability[5] = {0,0,0,0,0}; // Probability that a finger was pressed


void probability_averager(int finger)         //Does the moving averager which is a low pass filter. Electrode is 0 or 1
{
    averaged_probability[finger] = finger_probability[finger];
    
    for(j = 0; j < probability_averager_length ; j++)
    {
        averaged_probability[finger] = averaged_probability[finger] + probability_history[j][finger];
    }
    
    averaged_probability[finger] = divfix16(averaged_probability[finger],int2fix16(probability_averager_length + 1));    //To divide by 32. 
}



void update_probability_history(int finger)
{
    
    for(j=(probability_averager_length-1); j>0 ; j--)
    {
        probability_history[j][finger] = probability_history[j-1][finger];
    }
    
    probability_history[0][finger] = finger_probability[finger];
}





#endif	/* LOWPASS_FILTER_H */

