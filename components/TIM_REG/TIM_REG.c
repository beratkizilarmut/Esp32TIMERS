#include "TIM_REG.h"

int *GPIO_OUT_REG = (int *) 0x3FF44004; /* GPIO Address */
int toggle = 1; /* Button toggle variable */
int *TIMG0_T0_INT_CLR_REG = (int *) 0x3FF5F0A4; /* Interrupt flag clear address */

void Init_TIM_REG(void)
{   
    /* Enabling TIMG0 Clock */
    int *DPORT_PERIP_CLK_EN_REG = (int *) 0x3FF000C0;
    *DPORT_PERIP_CLK_EN_REG |= (1U << 13);
    /* TIMG0 TIM0 Addresses */
    int *TIMG0_T0CONFIG_REG = (int *) 0x3FF5F000; /* Timer 0 Config Register Address */
    int *TIMG0_UPDATE_REG = (int *) 0x3FF5F00C; /* Timer value Address */
    int *TIMG0_T0_INT_ENA_REG = (int *) 0x3FF5F098; /* Interrupt enable address */
    int *TIMG0_T0LOADLO_REG = (int *) 0x3FF5F018; /* Low 32 bits reload value address */
    int *TIMG0_T0LOAD_REG = (int *) 0x3FF5F020; /* Reload trigger address */
    int *TIMG0_T0ALARMLO_REG = (int *) 0x3FF5F010; /* Alarm trigger lo value address */
    int *TIMG0_T0ALARMHI_REG = (int *) 0x3FF5F014; /* Alarm trigger hi value address */
    /* Setting up TIMG0 TIM0 */
    *TIMG0_T0LOADLO_REG = (415U); /* Load value set as 415 */
    *TIMG0_T0LOAD_REG = (1U); /* Triggering reload */
    *TIMG0_T0ALARMLO_REG = (1000U); /* Trigger value set as 415 */
    *TIMG0_T0ALARMHI_REG = 0; /* Clearing high value */
    *TIMG0_T0CONFIG_REG = 0; /* Clearing config register */
    *TIMG0_T0CONFIG_REG |= (1U << 30); /* Set counting increment */
    *TIMG0_T0CONFIG_REG |= (1U << 29); /* Enable AutoReload */
    *TIMG0_T0CONFIG_REG |= (1U << 12); /* Enable edge type interrupt */
    *TIMG0_T0CONFIG_REG |= (1U << 10); /* Enable Alarm */
    /* Setting prescaler for microsecond increment */
    //**TIMG0_T0CONFIG_REG |= (80U << 13); /* Set 80 for 80 MHz */
    *TIMG0_UPDATE_REG |= (414U); /* Set 415 micro seconds */
    /* Enabling TIMG0 TIM0 */
    *TIMG0_T0CONFIG_REG |= (1U << 31); /* Enable TIMG0_T0 Clock */
    *TIMG0_T0_INT_ENA_REG = (1U); /* Enabling Interrupt */

    /* Setting up Output LED */
    int *GPIO_ENABLE_REG = (int *) 0x3FF44020; /* GPIO Enable address */
    *GPIO_ENABLE_REG = (1U << 25); /* Enabling GPIO25 */
    TIM_REG_RunTime();
}

void TIM_REG_RunTime(void)
{
    int *TIMG0_T0_INT_RAW_REG = (int *) 0x3FF5F09C; /* Interrupt status address */
    int *TIMG0_T0_INT_CLR_REG = (int *) 0x3FF5F0A4; /* Interrupt flag clear address */
    int *GPIO_OUT_REG = (int * ) 0x3FF44004; /* GPIO Enable address */
    int toggle = 1; /* Button toggle variable */
    int *TIMG0_T0CONFIG_REG = (int *) 0x3FF5F000; /* Timer 0 Config Register Address */

    while(1)
    {
        if(*TIMG0_T0_INT_RAW_REG){
            if(toggle)
            {
                *GPIO_OUT_REG &= ~(1U << 25);
                toggle = 0;
            }
            else
            {
                *GPIO_OUT_REG |= (1U << 25);
                toggle = 1;
            }
            *TIMG0_T0_INT_CLR_REG = (1U); /* Clearing interrupt flag */
            *TIMG0_T0CONFIG_REG |= (1U << 10); /* Enable Alarm */
        }
    } 
}