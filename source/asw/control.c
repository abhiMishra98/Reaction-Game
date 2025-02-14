/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "control.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

typedef enum
{
    CTRL_STATE_WAIT_BTNPRESS,
    CTRL_STATE_WAIT_TIMEOUT,
    CTRL_STATE_USERACTION,
    CTRL_STATE_GAMEENDS
} CTRL_state_t;

static CTRL_state_t CTRL_state = CTRL_STATE_WAIT_BTNPRESS;

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

static unsigned short randomNum = 0;
unsigned short buttonFlag = 0;
unsigned short time_count = 0;
static unsigned short noOfTurns = 0;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * <Description>
 * \param <first para>
 * \return <return value>
 */
unsigned short randomTimeGenerate(){
    unsigned short randomTimeMs = (rand()%3 +1)*1000;
    return randomTimeMs;
}

RC_t randomNumGenerate(){
    Pin_SelA_Write(1);
    char buffer[128];
    uint8_t bitPattern = 0b00111111;
    sevenSegmentDisplay(bitPattern);
    
    randomNum = (rand()%2 +1);
    
    Pin_SelA_Write(0);
    
    if(randomNum == 1){
        bitPattern = 0b00000110;
        sevenSegmentDisplay(bitPattern);
        time_count= 0;
        SetRelAlarm(alrm_Timer,1,1);      
        return RC_SUCCESS;
    }else if(randomNum == 2){
        bitPattern = 0b01011011;
        sevenSegmentDisplay(bitPattern);
        time_count= 0;
        SetRelAlarm(alrm_Timer,1,1);
        return RC_SUCCESS;
    }else{
        return RC_ERROR;
    }
}

void CTRL_processEvent1(CTRL_event_t ev)
{ 
    char buffer[64];
    unsigned short randomTime;
    switch (CTRL_state)
    {
        case CTRL_STATE_WAIT_BTNPRESS:
            if (ev == EV_button1Press)
            {     
               if(noOfTurns<10){
                    randomTime = randomTimeGenerate();
                    SetRelAlarm(alrm_randomTime, randomTime,0);
                    CTRL_state = CTRL_STATE_USERACTION;
                }
            }
            else if (ev == EV_button2Press)
            {  
                if(noOfTurns<10){
                    randomTime = randomTimeGenerate();
                    SetRelAlarm(alrm_randomTime, randomTime,0);
                    CTRL_state = CTRL_STATE_USERACTION;
                }
            }
            else
            {
                    //nothing
            }
            break;         
        case  CTRL_STATE_USERACTION:
              if (ev == EV_button2Press)
            {
                validateBtnPress1(ev);
            }
            else if (ev == EV_button1Press)
            {
                 validateBtnPress1(ev);
            }
            else
            {
                //nothing
            }
            break;
        case CTRL_STATE_GAMEENDS:
            CancelAlarm(alrm_50ms);
            sprintf(buffer+strlen(buffer),"%s\r\n","Game Ends");
            sprintf(buffer+strlen(buffer),"Correct buttons pressed = %d\r\n",game.crctBtnPress);
            sprintf(buffer+strlen(buffer),"Total time = %dms \r\n",game.totalTime);
            float totalTime = (float)game.totalTime/10;
            sprintf(buffer + strlen(buffer), "Average time = %d.%06d ms \r\n",(int)totalTime, (int)((totalTime - (int)totalTime) * 1000000));
            UART_LOG_PutString(buffer);
            
            
            LED_init();
            
            stopFaderGlower();
            
            sevenSegmentInit(); 
            SetEvent(tsk_control,ev_resetGame);
            CTRL_state = CTRL_STATE_WAIT_BTNPRESS;                  
        default:
            break;  
    }
    
}

void validateBtnPress1(CTRL_event_t ev){
    char buffer[128] = {0};
    if(noOfTurns < 10){
        if(time_count<1000){
            switch(ev){
             case EV_button1Press:
                if(randomNum == 2){
                    CancelAlarm(alrm_Timer);
                    noOfTurns++;
                    sprintf(buffer+strlen(buffer),"Round number %d \r\n", noOfTurns);
                    sprintf(buffer + strlen(buffer), "%s \r\n", "Great - correct button pressed");
                    game.totalTime+=time_count;
                    sprintf(buffer + strlen(buffer), "Reaction time :%d ms \r\n", time_count);
                   
                    game.crctBtnPress++;
 
                    sprintf(buffer + strlen(buffer),"Correct buttons press = %d \r\n", game.crctBtnPress);
                    UART_LOG_PutString(buffer);
                    sevenSegmentInit(); 
                    
                    if(noOfTurns == 10){
                       CTRL_state = CTRL_STATE_GAMEENDS;
                       CTRL_processEvent1(EV_button1Press);
                    }else{
                       SetEvent(tsk_control,ev_resetGame);
                       CTRL_state = CTRL_STATE_WAIT_BTNPRESS; 
                    }
                }else{
                    CancelAlarm(alrm_Timer);
                    noOfTurns++;
                    
                    sprintf(buffer+strlen(buffer),"Round number %d \r\n", noOfTurns);
                    sprintf(buffer+strlen(buffer),"%s \r\n","Incorrect button pressed");
                    UART_LOG_PutString(buffer);
                    sevenSegmentInit();  
                    
                    if(noOfTurns == 10){
                       CTRL_state = CTRL_STATE_GAMEENDS;
                       CTRL_processEvent1(EV_button1Press);
                    }else{
                       SetEvent(tsk_control,ev_resetGame);
                       CTRL_state = CTRL_STATE_WAIT_BTNPRESS; 
                    }
                }   
                break;
             case EV_button2Press:
                if(randomNum == 1){
                    CancelAlarm(alrm_Timer);
                    noOfTurns++;
                    
                    sprintf(buffer+strlen(buffer),"Round number %d \r\n", noOfTurns);
                    sprintf(buffer + strlen(buffer), "%s \r\n", "Great - correct button pressed");
                    game.totalTime+=time_count;
                    sprintf(buffer + strlen(buffer), "Reaction time :%d ms \r\n", time_count);
                    
                    game.crctBtnPress++;
                    
                    sprintf(buffer + strlen(buffer),"Correct buttons press = %d \r\n", game.crctBtnPress);
                    UART_LOG_PutString(buffer);
                    sevenSegmentInit();   
                    
                    if(noOfTurns == 10){
                       CTRL_state = CTRL_STATE_GAMEENDS;
                       CTRL_processEvent1(EV_button1Press);
                    }else{
                       SetEvent(tsk_control,ev_resetGame);
                       CTRL_state = CTRL_STATE_WAIT_BTNPRESS; 
                    }
                }else{
                    CancelAlarm(alrm_Timer);
                    noOfTurns++;
                    
                    sprintf(buffer+strlen(buffer),"Round number %d \r\n", noOfTurns);
                    sprintf(buffer+strlen(buffer),"%s \r\n","Incorrect button pressed");
                    UART_LOG_PutString(buffer);
                    
                    sevenSegmentInit();  
                    
                    if(noOfTurns == 10){
                       CTRL_state = CTRL_STATE_GAMEENDS;
                       CTRL_processEvent1(EV_button1Press);
                    }else{
                       SetEvent(tsk_control,ev_resetGame);
                       CTRL_state = CTRL_STATE_WAIT_BTNPRESS; 
                    }
                }   
                break;
             default:
                break;
            }          
        }else{
            CancelAlarm(alrm_Timer);
            noOfTurns++;
            
            sprintf(buffer+strlen(buffer),"Round number %d \r\n", noOfTurns);
            sprintf(buffer+strlen(buffer),"%s \r\n", "Too slow");
            UART_LOG_PutString(buffer); 
            
            sevenSegmentInit();  
            
             if(noOfTurns == 10){
                   CTRL_state = CTRL_STATE_GAMEENDS;
                   CTRL_processEvent1(EV_button1Press);
              }else{
                   SetEvent(tsk_control,ev_resetGame);
                   CTRL_state = CTRL_STATE_WAIT_BTNPRESS; 
              } 
        }
      
    }
    

}


