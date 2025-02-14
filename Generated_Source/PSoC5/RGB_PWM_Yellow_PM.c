/*******************************************************************************
* File Name: RGB_PWM_Yellow_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RGB_PWM_Yellow.h"

static RGB_PWM_Yellow_backupStruct RGB_PWM_Yellow_backup;


/*******************************************************************************
* Function Name: RGB_PWM_Yellow_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RGB_PWM_Yellow_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void RGB_PWM_Yellow_SaveConfig(void) 
{

    #if(!RGB_PWM_Yellow_UsingFixedFunction)
        #if(!RGB_PWM_Yellow_PWMModeIsCenterAligned)
            RGB_PWM_Yellow_backup.PWMPeriod = RGB_PWM_Yellow_ReadPeriod();
        #endif /* (!RGB_PWM_Yellow_PWMModeIsCenterAligned) */
        RGB_PWM_Yellow_backup.PWMUdb = RGB_PWM_Yellow_ReadCounter();
        #if (RGB_PWM_Yellow_UseStatus)
            RGB_PWM_Yellow_backup.InterruptMaskValue = RGB_PWM_Yellow_STATUS_MASK;
        #endif /* (RGB_PWM_Yellow_UseStatus) */

        #if(RGB_PWM_Yellow_DeadBandMode == RGB_PWM_Yellow__B_PWM__DBM_256_CLOCKS || \
            RGB_PWM_Yellow_DeadBandMode == RGB_PWM_Yellow__B_PWM__DBM_2_4_CLOCKS)
            RGB_PWM_Yellow_backup.PWMdeadBandValue = RGB_PWM_Yellow_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(RGB_PWM_Yellow_KillModeMinTime)
             RGB_PWM_Yellow_backup.PWMKillCounterPeriod = RGB_PWM_Yellow_ReadKillTime();
        #endif /* (RGB_PWM_Yellow_KillModeMinTime) */

        #if(RGB_PWM_Yellow_UseControl)
            RGB_PWM_Yellow_backup.PWMControlRegister = RGB_PWM_Yellow_ReadControlRegister();
        #endif /* (RGB_PWM_Yellow_UseControl) */
    #endif  /* (!RGB_PWM_Yellow_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RGB_PWM_Yellow_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RGB_PWM_Yellow_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void RGB_PWM_Yellow_RestoreConfig(void) 
{
        #if(!RGB_PWM_Yellow_UsingFixedFunction)
            #if(!RGB_PWM_Yellow_PWMModeIsCenterAligned)
                RGB_PWM_Yellow_WritePeriod(RGB_PWM_Yellow_backup.PWMPeriod);
            #endif /* (!RGB_PWM_Yellow_PWMModeIsCenterAligned) */

            RGB_PWM_Yellow_WriteCounter(RGB_PWM_Yellow_backup.PWMUdb);

            #if (RGB_PWM_Yellow_UseStatus)
                RGB_PWM_Yellow_STATUS_MASK = RGB_PWM_Yellow_backup.InterruptMaskValue;
            #endif /* (RGB_PWM_Yellow_UseStatus) */

            #if(RGB_PWM_Yellow_DeadBandMode == RGB_PWM_Yellow__B_PWM__DBM_256_CLOCKS || \
                RGB_PWM_Yellow_DeadBandMode == RGB_PWM_Yellow__B_PWM__DBM_2_4_CLOCKS)
                RGB_PWM_Yellow_WriteDeadTime(RGB_PWM_Yellow_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(RGB_PWM_Yellow_KillModeMinTime)
                RGB_PWM_Yellow_WriteKillTime(RGB_PWM_Yellow_backup.PWMKillCounterPeriod);
            #endif /* (RGB_PWM_Yellow_KillModeMinTime) */

            #if(RGB_PWM_Yellow_UseControl)
                RGB_PWM_Yellow_WriteControlRegister(RGB_PWM_Yellow_backup.PWMControlRegister);
            #endif /* (RGB_PWM_Yellow_UseControl) */
        #endif  /* (!RGB_PWM_Yellow_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: RGB_PWM_Yellow_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RGB_PWM_Yellow_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void RGB_PWM_Yellow_Sleep(void) 
{
    #if(RGB_PWM_Yellow_UseControl)
        if(RGB_PWM_Yellow_CTRL_ENABLE == (RGB_PWM_Yellow_CONTROL & RGB_PWM_Yellow_CTRL_ENABLE))
        {
            /*Component is enabled */
            RGB_PWM_Yellow_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            RGB_PWM_Yellow_backup.PWMEnableState = 0u;
        }
    #endif /* (RGB_PWM_Yellow_UseControl) */

    /* Stop component */
    RGB_PWM_Yellow_Stop();

    /* Save registers configuration */
    RGB_PWM_Yellow_SaveConfig();
}


/*******************************************************************************
* Function Name: RGB_PWM_Yellow_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RGB_PWM_Yellow_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void RGB_PWM_Yellow_Wakeup(void) 
{
     /* Restore registers values */
    RGB_PWM_Yellow_RestoreConfig();

    if(RGB_PWM_Yellow_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        RGB_PWM_Yellow_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
