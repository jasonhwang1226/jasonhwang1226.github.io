/* 
 * File:   our_debugger.h
 * Author: Krishnaa
 *
 * Created on 24 September, 2016, 9:04 PM
 */

#ifndef OUR_DEBUGGER_H
#define	OUR_DEBUGGER_H

char tft_buffer[60];                      // string buffer used to output to TFT


static int cont_samples[12] = {0,0,0,0,0,0,0,0,0,0,0,0};        //Debug continuous samples of a particular data
static int samples_length = 0;


//Our degugger to test any outputs we want
static struct pt pt_test ; 

void output_TFT_string(int x, int y,  char* data)
{
        //write data to TFT
        tft_fillRoundRect(x,y, 200, 28, 1, ILI9340_BLACK);// x,y,w,h,radius,color
        tft_setCursor(x,y);    //x,y
        tft_setTextColor(ILI9340_YELLOW); tft_setTextSize(2);    //color & size
        sprintf(tft_buffer,"%s", data);
        tft_writeString(tft_buffer);   
}

void output_TFT_int(int x, int y, int data)
{
        //write data to TFT
        tft_fillRoundRect(x,y, 200, 28, 1, ILI9340_BLACK);// x,y,w,h,radius,color
        tft_setCursor(x,y);    //x,y
        tft_setTextColor(ILI9340_YELLOW); tft_setTextSize(2);    //color & size
        sprintf(tft_buffer,"%d", data);
        tft_writeString(tft_buffer);   
}

void output_TFT_float(int x, int y, float data)
{
        //write data to TFT
        tft_fillRoundRect(x,y, 200, 28, 1, ILI9340_BLACK);// x,y,w,h,radius,color
        tft_setCursor(x,y);    //x,y
        tft_setTextColor(ILI9340_YELLOW); tft_setTextSize(2);    //color & size
        sprintf(tft_buffer,"%f", data);
        tft_writeString(tft_buffer);   
}




void outputarray_TFT(int x, int y, int* data)
{
     //write data to TFT
        tft_fillRoundRect(x,y, 240, 28, 1, ILI9340_BLACK);// x,y,w,h,radius,color
        tft_setCursor(x,y);    //x,y
        tft_setTextColor(ILI9340_YELLOW); tft_setTextSize(2);    //color & size
        sprintf(tft_buffer,"%d%d%d%d%d%d%d%d%d%d%d%d", 
        data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11]);
        tft_writeString(tft_buffer);   
}


void displaysamples_TFT(int x, int y, int data)             //Displays continuous samples of a data on the screen. 
{
            samples_length = samples_length % 12;
            cont_samples[samples_length] = data;
            samples_length++;
            
            outputarray_TFT(x,y,cont_samples);
            
}

int sign(int data){
    if (data<0){
        return 0;
    }
    else
        return 1;
    
}

static int read;

static PT_THREAD (protothread_test(struct pt *pt))
{
    PT_BEGIN(pt);
    
    while(1)
    {                
        
        PT_YIELD_TIME_msec(30); 
    }
  PT_END(pt);
} // test out ideas


#endif	/* OUR_DEBUGGER_H */

