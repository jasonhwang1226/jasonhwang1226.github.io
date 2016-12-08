#ifndef PT_MAIN_H
#define	PT_MAIN_H




////Define variables used in pt_main
//static fix16 balls[rows][columns];      //2D array to keep track of balls
//static fix16 rij[2] = {0,0};         //rij = ri - rj = "vector from i to j"
//static fix16 vij[2] = {0,0};         //vij = vi - vj = "velocity of i relative to j"
//static fix16 delta_vi[2]  = {0,0};   //chnage in velocity for next frame
//static fix16 mag2_rij = 0;         //squared distance between ball i and j
//static fix16 drag = 0.001;         //drag from table



static PT_THREAD (protothread_main(struct pt *pt))
{
    PT_BEGIN(pt);
    
    
    //DRAW FIELD
    tft_drawLine(80, 0, 80, 60, ILI9340_YELLOW);   //x0, y0, x1, y1, color
    tft_drawLine(80, 180, 80, 240, ILI9340_YELLOW);
    
    //scale adc to size of the screen
    ADC_scale = float2fix16(220.0/990.0); //Vref/(full scale)
    
    
            
    while(1) {       
        begin_time = PT_GET_TIME();     
   
        miss_flag = 0; //updates once per frame
        
        update_paddle_pos();
        
        for(i=0; i<rows; i++) //ALL BALLS
        {
            if(balls[i][5] == int2fix16(1))    //Check if the ball exists
            {
                update_bb_velocity();
                update_b_sidewall_velocity();
                update_drag();
                update_paddle_hit();
            }
        }
        //      \COLLISIONS
        update_game_variables();
        update_position();
        inject_balls();
        
        //PRINT GAME VARIABLES
        output_TFT(275,0,game_time);
        output_TFT(275,20,framerate);
        output_TFT(275,40,num_balls);
        output_TFT(275,60,score);
    
        //inject_2balls();
        PT_YIELD_TIME_msec(67 - (PT_GET_TIME() - begin_time)) ;
    
        
      } // END WHILE(1)
  PT_END(pt);
} // main thread




#endif	/* PT_MAIN_H */
