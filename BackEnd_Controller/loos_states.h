#include <mbed.h>


typedef enum 
{ 
    S_RUN, 
    S_SER,
    S_SET 
} sysMode_t;

typedef struct
{
    sysMode_t sysMode;
}sysState_struct_t;


typedef enum 
{
    ME_INITIALISING,
    ME_RUN,     
    ME_SERVICE, 
    ME_REFILM,  
    ME_JAM, 
    ME_SUDATA,  
    ME_REFILL_CONFIRMATION,
    ME_JAM_CONFIRMATION, 
    ME_SETUP,
} T_MenuState;
