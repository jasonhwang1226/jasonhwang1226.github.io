/* 
 * File:   Neural_network.h
 * Author: Krishnaa
 *
 * Created on 3 December, 2016, 10:51 PM
 */

#ifndef NEURAL_NETWORK_H
#define	NEURAL_NETWORK_H

//Neural network variables
int no_neurons = 20;
fix16 neuron[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //Neural Layer output.    

fix16 threshold_probability = float2fix16(0.9);
int consistency_up[5] = {100,100,100,100,50};
int cap_value[5] = {1000,1000,1000,10000,1000};
int consistency_down[5] = {0,0,0,0,0};
int changes_finger[5] = {0,0,0,0,0};        //Checkes for consistency in the finger signal
int finger_state[5] = {0,0,0,0,0};          //Tue finger state. 1 for pressed and 0 for not pressed.
//fix16 synapse0[2][20] = 
//{{         -231947,         -463795,         -261507,         -246608,         -239312,          232962,         -342850,         -222128,          191622,          141771,          182249,          218048,         -228825,         -244540,         -339951,          262883,          449660,          268807,         -201708,         -280299}, 
//{           66791,         -414071,          554269,          529464,           73239,         -530542,         -183615,         1419485,         -505406,        -1011351,         -622048,         -543519,          113419,          217961,         -262018,         -582510,          276325,         -718750,         1290106,          510309}}; 
//fix16 synapse1[20][5] = 
//{{         -514216,         -191350,          285390,              47,          -29687}, 
//{         -600872,         -188571,         -675160,          -21384,          -95720}, 
//{         -125501,         -287537,          739172,           -8312,          -24064}, 
//{          -98720,         -382502,          682327,          -83829,          -57960}, 
//{         -581109,         -285937,          237665,          -62556,          -36865}, 
//{          -51350,          148421,         -625307,          -72592,          -87325}, 
//{         -676171,         -243579,         -285844,          -48652,          -49872}, 
//{          711950,         -550181,         1243030,         -107553,          -45904}, 
//{         -175400,           70988,         -545701,          -10445,          -11016}, 
//{         -743795,          199870,         -701381,          -74104,         -116042}, 
//{         -281625,           93468,         -610688,          -66612,          -91824}, 
//{         -163000,          -47306,         -606684,          -87883,         -124374}, 
//{         -414800,         -203548,          323438,          -70113,           -9784}, 
//{         -452120,         -253512,          437346,          -51285,          -17727}, 
//{         -608126,         -165498,         -301262,           10478,          -71116}, 
//{           14974,           67802,         -716549,          -41452,          -84202}, 
//{          622642,           52826,          572108,         -104659,          -73554}, 
//{          -71197,          166573,         -827348,         -138859,          -54573}, 
//{          709083,         -392395,         1101734,          -19948,         -104808}, 
//{         -343478,         -271112,          733407,          -67923,            9958}}; 
//
//
//
//fix16 normalization_value = int2fix16(200);
//
//
//
//
//
//fix16 sigmoid(fix16 x)
//{
//    return divfix16(fix16_one, fix16_one + float2fix16(exp(fix2float16(multfix16(int2fix16(-1),x)))));
//}
//
//
//
//void run_neural_network(void)
//{
//    //Synapse0 propogation
//    for(i=0 ; i<no_neurons ; i++)           //For all neurons
//    {
//        neuron[i] = multfix16(divfix16(filter_output[0],normalization_value),synapse0[0][i])      +      multfix16(divfix16(filter_output[1],normalization_value),synapse0[1][i]);     //As only two inputs exist
//    }
//    
//    
//    
//    
//    //Synapse1 propogation
//    finger_probability[0] = fix16_zero;
//    finger_probability[1] = fix16_zero;
//    finger_probability[2] = fix16_zero;
//    finger_probability[3] = fix16_zero;
//    finger_probability[4] = fix16_zero;
//    for(i=0 ; i<no_neurons ; i++)       //For all neurons
//    {
//        
//        neuron[i] = sigmoid(neuron[i]);
//        
//        
//        finger_probability[0] = finger_probability[0] + multfix16(neuron[i],synapse1[i][0]);
//        finger_probability[1] = finger_probability[1] + multfix16(neuron[i],synapse1[i][1]);
//        finger_probability[2] = finger_probability[2] + multfix16(neuron[i],synapse1[i][2]);
//        finger_probability[3] = finger_probability[3] + multfix16(neuron[i],synapse1[i][3]);
//        finger_probability[4] = finger_probability[4] + multfix16(neuron[i],synapse1[i][4]);
//    }
//    
//    //Output thresholding
//    for(i=0 ; i<5 ; i++)
//    {
//        finger_probability[i] = sigmoid(finger_probability[i]);
//    }
//    
//    
//    //Averager of probability
////    for(i=0 ; i<5 ; i++)
////    {
////        probability_averager(i);
////        update_probability_history(i);
////    }
//    
//    
//    
//    //Hysteresis code for the finger probability
//    for(i=0 ; i<5; i++)
//    {
//        if(finger_probability[i] > threshold_probability)
//        {
//            changes_finger[i] = changes_finger[i] + 1;
//            if(changes_finger[i] >= consistency_up[i])
//            {
//                finger_state[i] = 1;
//                if(changes_finger[i] >= cap_value[i])
//                {
//                    changes_finger[i] = cap_value[i];
//                }
//            }
//        }
//        else
//        {
//            changes_finger[i] = changes_finger[i] - 1;
//            if(changes_finger[i] <= consistency_down[i])
//            {
//                finger_state[i] = 0;
//                changes_finger[i] = 0;
//            }
//        }
//        
//        //So that the earliest finger is given preference
//        if(finger_state[i] == 1)
//        {
//            break;
//        }
//    }
//    
//}







int e1 = 0;
int e2 = 0;

int indicator = 0;
int lock_press = 0;

void run_thresholding(void)
{
    e1 = fix2int16(filter_output[0]);
    e2 = fix2int16(filter_output[1]);
    
    if( (e1>70 && e1<85) )  //pinky - hard
    {
        indicator = 1;
            changes_finger[0] = changes_finger[0] + 2;
            if(changes_finger[0] >= consistency_up[0])
            {
                finger_state[0] = 1;
                finger_state[1] = 0;
                finger_state[2] = 0;
                finger_state[3] = 0;
                finger_state[4] = 0;
                if(changes_finger[0] >= cap_value[0])
                {
                    lock_press = 1;
                    changes_finger[0] = cap_value[0];
                }
            }
    }
    else if( (e1>90 ) )    //ring - squeeze hard
    {
        indicator = 2;
            changes_finger[1] = changes_finger[1] + 2;
            if(changes_finger[1] >= consistency_up[1])
            {
                finger_state[0] = 0;
                finger_state[1] = 1;
                finger_state[2] = 0;
                finger_state[3] = 0;
                finger_state[4] = 0;
                if(changes_finger[1] >= cap_value[1])
                {
                    lock_press = 2;
                    changes_finger[1] = cap_value[1];
                }
            }
    }
    else if( (e1>48 && e1<60) && (e2>30 && e2<50)) //middle
    {
        indicator = 3;
            changes_finger[2] = changes_finger[2] + 2;
            if(changes_finger[2] >= consistency_up[2])
            {
                finger_state[0] = 0;
                finger_state[1] = 0;
                finger_state[2] = 1;
                finger_state[3] = 0;
                finger_state[4] = 0;
                if(changes_finger[2] >= cap_value[2])
                {
                    lock_press = 3;
                    changes_finger[2] = cap_value[2];
                }
            }
    }
    else if( (e1>43 && e1<59) && (e2>1 && e2<5)) //index - light 
    {
        indicator = 4;
            changes_finger[3] = changes_finger[3] + 2;
            if(changes_finger[3] >= consistency_up[3])
            {
                finger_state[0] = 0;
                finger_state[1] = 0;
                finger_state[2] = 0;
                finger_state[3] = 1;
                finger_state[4] = 0;
                if(changes_finger[3] >= cap_value[3])
                {
                    lock_press = 4;
                    changes_finger[3] = cap_value[3];
                }
            }
    }
    else if( (e1>50 && e1<59) && (e2>10 && e2<30)) //thumb
    {
        indicator = 5;
            changes_finger[4] = changes_finger[4] + 1;
            if(changes_finger[4] >= consistency_up[4])
            {
                finger_state[0] = 0;
                finger_state[1] = 0;
                finger_state[2] = 0;
                finger_state[3] = 0;
                finger_state[4] = 1;
                if(changes_finger[4] >= cap_value[4])
                {
                    lock_press = 5;
                    changes_finger[4] = cap_value[4];
                }
            }
    }
    
    
    else //decrementing
    {
            indicator = 0;
            changes_finger[0] = changes_finger[0] - max_int(1, changes_finger[0]>>6);
            if(changes_finger[0] <= consistency_down[0])  //pinky
            {
                finger_state[0] = 0;
                changes_finger[0] = 0;
            }
        
        
           
           changes_finger[1] = changes_finger[1] - max_int(1, changes_finger[1]>>6);
            if(changes_finger[1] <= consistency_down[1]) //ring
            {
                finger_state[1] = 0;
                changes_finger[1] = 0;
            }  
           
           
           changes_finger[2] = changes_finger[2] - max_int(1, changes_finger[1]>>6);
            if(changes_finger[2] <= consistency_down[2])    //middle
            {
                finger_state[2] = 0;
                changes_finger[2] = 0;
            } 
           
           changes_finger[3] = changes_finger[3] - max_int(1, changes_finger[1]>>6);
            if(changes_finger[3] <= consistency_down[3])    //index
            {
                finger_state[3] = 0;
                changes_finger[3] = 0;
            }
           
            changes_finger[4] = changes_finger[4] - 1;
            if(changes_finger[4] <= consistency_down[4])    //thumb
            {
                finger_state[4] = 0;
                changes_finger[4] = 0;
            }
       
    }
    
    
}






#endif	/* NEURAL_NETWORK_H */

