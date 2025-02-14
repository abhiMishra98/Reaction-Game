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

#include "game.h"

ISR(systick_handler)
{
   CounterTick(cnt_systick);
}

CY_ISR_PROTO(isr_button);


/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



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
//RC_t FILE_function(type para)

void SysTick_Handler(void) {
    systickCounter++;
}

RC_t gameInit(){
   UART_LOG_Start();
   isr_button_StartEx(isr_button);
    srand (time(NULL));
    
    CySysTickInit();
    CySysTickSetCallback(0,SysTick_Handler);
    CySysTickSetReload(BCLK__BUS_CLK__HZ/1000 -1);
    CySysTickEnable();
    
    EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
    EE_systick_enable_int();
 

    char buffer[128] = {0};
    sprintf(buffer + strlen(buffer),"\r\n%s :","Reaction test program round 1"); 
  
    sprintf(buffer + strlen(buffer),"\r\n%s :","press one of the two buttons to start..."); 
   
    
    sevenSegmentInit();
    
    UART_LOG_PutString(buffer);
    
    return RC_SUCCESS;
}

