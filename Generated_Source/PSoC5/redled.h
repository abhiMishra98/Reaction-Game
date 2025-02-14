/*******************************************************************************
* File Name: redled.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_redled_H) /* Pins redled_H */
#define CY_PINS_redled_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "redled_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 redled__PORT == 15 && ((redled__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    redled_Write(uint8 value);
void    redled_SetDriveMode(uint8 mode);
uint8   redled_ReadDataReg(void);
uint8   redled_Read(void);
void    redled_SetInterruptMode(uint16 position, uint16 mode);
uint8   redled_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the redled_SetDriveMode() function.
     *  @{
     */
        #define redled_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define redled_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define redled_DM_RES_UP          PIN_DM_RES_UP
        #define redled_DM_RES_DWN         PIN_DM_RES_DWN
        #define redled_DM_OD_LO           PIN_DM_OD_LO
        #define redled_DM_OD_HI           PIN_DM_OD_HI
        #define redled_DM_STRONG          PIN_DM_STRONG
        #define redled_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define redled_MASK               redled__MASK
#define redled_SHIFT              redled__SHIFT
#define redled_WIDTH              1u

/* Interrupt constants */
#if defined(redled__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in redled_SetInterruptMode() function.
     *  @{
     */
        #define redled_INTR_NONE      (uint16)(0x0000u)
        #define redled_INTR_RISING    (uint16)(0x0001u)
        #define redled_INTR_FALLING   (uint16)(0x0002u)
        #define redled_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define redled_INTR_MASK      (0x01u) 
#endif /* (redled__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define redled_PS                     (* (reg8 *) redled__PS)
/* Data Register */
#define redled_DR                     (* (reg8 *) redled__DR)
/* Port Number */
#define redled_PRT_NUM                (* (reg8 *) redled__PRT) 
/* Connect to Analog Globals */                                                  
#define redled_AG                     (* (reg8 *) redled__AG)                       
/* Analog MUX bux enable */
#define redled_AMUX                   (* (reg8 *) redled__AMUX) 
/* Bidirectional Enable */                                                        
#define redled_BIE                    (* (reg8 *) redled__BIE)
/* Bit-mask for Aliased Register Access */
#define redled_BIT_MASK               (* (reg8 *) redled__BIT_MASK)
/* Bypass Enable */
#define redled_BYP                    (* (reg8 *) redled__BYP)
/* Port wide control signals */                                                   
#define redled_CTL                    (* (reg8 *) redled__CTL)
/* Drive Modes */
#define redled_DM0                    (* (reg8 *) redled__DM0) 
#define redled_DM1                    (* (reg8 *) redled__DM1)
#define redled_DM2                    (* (reg8 *) redled__DM2) 
/* Input Buffer Disable Override */
#define redled_INP_DIS                (* (reg8 *) redled__INP_DIS)
/* LCD Common or Segment Drive */
#define redled_LCD_COM_SEG            (* (reg8 *) redled__LCD_COM_SEG)
/* Enable Segment LCD */
#define redled_LCD_EN                 (* (reg8 *) redled__LCD_EN)
/* Slew Rate Control */
#define redled_SLW                    (* (reg8 *) redled__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define redled_PRTDSI__CAPS_SEL       (* (reg8 *) redled__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define redled_PRTDSI__DBL_SYNC_IN    (* (reg8 *) redled__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define redled_PRTDSI__OE_SEL0        (* (reg8 *) redled__PRTDSI__OE_SEL0) 
#define redled_PRTDSI__OE_SEL1        (* (reg8 *) redled__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define redled_PRTDSI__OUT_SEL0       (* (reg8 *) redled__PRTDSI__OUT_SEL0) 
#define redled_PRTDSI__OUT_SEL1       (* (reg8 *) redled__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define redled_PRTDSI__SYNC_OUT       (* (reg8 *) redled__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(redled__SIO_CFG)
    #define redled_SIO_HYST_EN        (* (reg8 *) redled__SIO_HYST_EN)
    #define redled_SIO_REG_HIFREQ     (* (reg8 *) redled__SIO_REG_HIFREQ)
    #define redled_SIO_CFG            (* (reg8 *) redled__SIO_CFG)
    #define redled_SIO_DIFF           (* (reg8 *) redled__SIO_DIFF)
#endif /* (redled__SIO_CFG) */

/* Interrupt Registers */
#if defined(redled__INTSTAT)
    #define redled_INTSTAT            (* (reg8 *) redled__INTSTAT)
    #define redled_SNAP               (* (reg8 *) redled__SNAP)
    
	#define redled_0_INTTYPE_REG 		(* (reg8 *) redled__0__INTTYPE)
#endif /* (redled__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_redled_H */


/* [] END OF FILE */
