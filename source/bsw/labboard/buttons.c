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

#include "buttons.h"
#include "sevenSegment.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

//unsigned short randomNum = 0;
//unsigned short buttonFlag = 0;


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

RC_t buttonInit() {
    // Implementation of the function
    srand (time(NULL));
    
    if((Button_1_Read() == 1) || (Button_2_Read() == 1)){
        return RC_ERROR;
    }else{
    return RC_SUCCESS;
    }
}

unsigned short BTN_read(BTN_t *const me)
{
    if (0 == me->m_read) return BTN_UNDEF;
    
    //Read the port
    uint8_t curState = me->m_read();
    
    return curState;
    
 //   BTN_state_t result = BTN_UNDEF;
    
//    if (1 == curState)
//    {
//        switch (me->m_prevState)
//        {
//            case BTN_LOW : 
//           // UART_LOG_PutString("AA\r\n");
//                result = BTN_RISING; 
//                break;
//            case BTN_HIGH : 
//            //   UART_LOG_PutString("BB\r\n");
//                result = BTN_HIGH;
//                break;
//            default: 
//            //   UART_LOG_PutString("CC\r\n");
//                result = BTN_UNDEF;
//                break;
//        }
//        
//        //Memorize current state
//        me->m_prevState = BTN_HIGH;
//            
//    }
//    else
//    {
//        switch (me->m_prevState)
//        {
//            case BTN_LOW : 
//            //   UART_LOG_PutString("AA\r\n");
//                result = BTN_LOW; 
//                break;
//            case BTN_HIGH : 
//           // UART_LOG_PutString("BB\r\n");    
//            result = BTN_FALLING;
//                break;
//            default: 
//           // UART_LOG_PutString("CC\r\n");    
//                result = BTN_UNDEF;
//                break;
//        }
//        
//        //Memorize current state
//        me->m_prevState = BTN_LOW;        
//    }

    //return result;
}



//unsigned short randomTimeGenerate(){
//    unsigned short randomTimeMs = (rand()%3 +1)*1000;
//    CyDelay(randomTimeMs);
//    randomNumGenerate(randomNum);
//    return randomTimeMs;
//}
