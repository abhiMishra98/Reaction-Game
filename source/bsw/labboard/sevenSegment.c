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

#include "sevenSegment.h"

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


RC_t sevenSegmentInit(){
    Pin_SelA_Write(1);
    uint8_t bitPattern = 0b00111111;
    sevenSegmentDisplay(bitPattern);
    Pin_SelA_Write(0);
    sevenSegmentDisplay(bitPattern);
    return RC_SUCCESS;
}

//RC_t randomNumGenerate(){
//    Pin_SelA_Write(1);
//     char buffer[128];
//    uint8_t bitPattern = 0b00111111;
//    sevenSegmentDisplay(bitPattern);
//    extern unsigned short randomNum;
//    unsigned short randomNumber = (rand()%2 +1);
//    randomNum = randomNumber;
//    Pin_SelA_Write(0);
//    
//    if(randomNumber == 1){
//        bitPattern = 0b00000110;
//        sevenSegmentDisplay(bitPattern);
//        game.startTime = systickCounter;
//        sprintf(buffer + strlen(buffer), "SysTick timer = %d \r\n", systickCounter);
//        UART_LOG_PutString(buffer);
//        return RC_SUCCESS;
//    }else if(randomNumber == 2){
//        bitPattern = 0b01011011;
//        sevenSegmentDisplay(bitPattern);
//        game.startTime = systickCounter;
//        sprintf(buffer + strlen(buffer), "SysTick timer = %d \r\n", systickCounter);
//        UART_LOG_PutString(buffer);
//        return RC_SUCCESS;
//    }else{
//        return RC_ERROR;
//    }
//}

RC_t sevenSegmentDisplay(uint8_t bitPattern){
    Pin_A_Write(bitPattern & 0x01);
    Pin_B_Write((bitPattern >> 1) & 0x01);
    Pin_C_Write((bitPattern >> 2) & 0x01);
    Pin_D_Write((bitPattern >> 3) & 0x01);
    Pin_DP_Write((bitPattern >> 4) & 0x01);
    Pin_E_Write((bitPattern >> 5) & 0x01);
    Pin_F_Write((bitPattern >> 6) & 0x01);
    Pin_G_Write((bitPattern >> 7) & 0x01);
    return RC_SUCCESS;
}
