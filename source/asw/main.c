/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "../bsw/labboard/buttons.h"
#include "../bsw/labboard/game.h"
#include "../bsw/labboard/led.h"
#include "control.h"


extern unsigned short time_count;
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    gameInit();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    	
    
    for(;;)
    {
       	StartOS(OSDEFAULTAPPMODE);
        /* Place your application code here. */
    }
}

TASK(tsk_init){
    EE_system_init();
    EE_systick_start(); 
    
    LED_init();
    RGB_PWM_Yellow_Start();
    RGB_PWM_Green_Start();
    RGB_PWM_Red_Start();
    RGB_PWM_Yellow_1_Start();
    RGB_PWM_Green_1_Start();
    RGB_PWM_Red_1_Start();
    
    
    
    SetRelAlarm(alrm_50ms,50,50);
    SetRelAlarm(alrm_fader,1,50);
    SetRelAlarm(alrm_glower,1,50);
    ActivateTask(tsk_fader);
    ActivateTask(tsk_glower);
    ActivateTask(tsk_control);
    ActivateTask(tsk_background);
    
    TerminateTask();
}
TASK(tsk_background){
 while(1)
    {
        //do something with low prioroty
        __asm("nop");
    }
}
void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}
// extern unsigned short randomTime;



TASK(tsk_control){
    EventMaskType ev = 0;
    EventMaskType activeEvents;
    
    while(1){
         WaitEvent(ev_btn1Press | ev_btn2Press | ev_resetGame);
         GetEvent(tsk_control, &activeEvents);
        
        if(activeEvents & ev_btn1Press){
         CTRL_processEvent1(EV_button1Press);
         ClearEvent(ev_btn1Press);
        }
        else if(activeEvents & ev_btn2Press){
         CTRL_processEvent1(EV_button2Press);
         ClearEvent(ev_btn2Press);
        }  
        else if(activeEvents & ev_resetGame){
         ClearEvent(ev_resetGame);
        }
        ClearEvent(activeEvents);
    }
    TerminateTask();
}

TASK(tsk_timer){
    time_count++;
    TerminateTask();  
}

TASK(tsk_timeDelay){
    randomNumGenerate();
    TerminateTask();
}
CY_ISR(isr_button){

    if(Button_1_Read() == 1){
     SetEvent(tsk_control,ev_btn1Press);
    }else if(Button_2_Read() == 1){
     SetEvent(tsk_control,ev_btn2Press);
    }else{
     //nothing
    }
        
}

TASK(tsk_fader){
 LED_fadeEffect();
 TerminateTask();
}

TASK(tsk_glower){
 playGlowSequence(RG_glowtable_1, RG_glowtable_1_len);
 TerminateTask();
}

/* [] END OF FILE */
