/**
 * @author Ángel Fernández Pineda. Madrid. Spain.
 * @date 2022-10-23
 * @brief Conversion of Fanatec's Clubsport Universal Hub to wireless
 *
 * @copyright Creative Commons Attribution 4.0 International (CC BY 4.0)
 *
 */

#include <Arduino.h>
#include "SimWheel.h"
// #include "soc/soc.h"
// #include "soc/rtc_cntl_reg.h"
//  #include "debugUtils.h"

//------------------------------------------------------------------
// Global customization
//------------------------------------------------------------------

std::string DEVICE_NAME = "CSUH sim wheel";
std::string DEVICE_MANUFACTURER = "Mamandurrio";

#define MOD_LT JOY_LTHUMBSTICK_CLICK
#define MOD_RT JOY_RTHUMBSTICK_CLICK
#define MOD_LSB 10
#define MOD_RSB 11
#define MOD_LB 12
#define MOD_RB 13
#define ROT_CW 14
#define ROT_CCW 15
#define ROT_PUSH 16
#define FUNKY_CCW 17
#define FUNKY_CW 18
#define FUNKY_PUSH 19
#define DPAD_UP 32
#define DPAD_DOWN 33
#define DPAD_LEFT 34
#define DPAD_RIGHT 35

//#define VERTICAL_CIRCUIT_LAYOUT 0

//------------------------------------------------------------------
// Setup
//------------------------------------------------------------------

void add3BtnModule_X_Y_Back(gpio_num_t X, gpio_num_t Y, gpio_num_t Back)
{
    inputs::addDigital(X, JOY_X, true, true);
    inputs::addDigital(Y, JOY_Y, true, true);
    inputs::addDigital(Back, JOY_BACK, true, true);
}

void add3BtnModule_LT_LB_LSB(gpio_num_t LT, gpio_num_t LB, gpio_num_t LSB)
{
    inputs::addDigital(LT, MOD_LT, true, true);
    inputs::addDigital(LB, MOD_LB, true, true);
    inputs::addDigital(LSB, MOD_LSB, true, true);
}

void add3BtnModule_RT_RB_RSB(gpio_num_t RT, gpio_num_t RB, gpio_num_t RSB)
{
    inputs::addDigital(RT, MOD_RT, true, true);
    inputs::addDigital(RB, MOD_RB, true, true);
    inputs::addDigital(RSB, MOD_RSB, true, true);
}

void add3BtnModule_A_B_Start(gpio_num_t A, gpio_num_t B, gpio_num_t Start)
{
    inputs::addDigital(A, JOY_A, true, true);
    inputs::addDigital(B, JOY_B, true, true);
    inputs::addDigital(Start, JOY_START, true, true);
}

void simWheelSetup()
{
    //   Funky switch
    inputs::addRotaryEncoder(GPIO_NUM_16, GPIO_NUM_39, FUNKY_CW, FUNKY_CCW, true);
    inputs::addDigital(GPIO_NUM_36, DPAD_UP, true, false);
    inputs::addDigital(GPIO_NUM_34, DPAD_LEFT, true, false);
    inputs::addDigital(GPIO_NUM_35, DPAD_RIGHT, true, false);
    inputs::addDigital(GPIO_NUM_19, DPAD_DOWN, true, true);
    inputs::addDigital(GPIO_NUM_21, FUNKY_PUSH, true, true);

    //   Additional rotary encoder
    inputs::addRotaryEncoder(GPIO_NUM_17, GPIO_NUM_5, ROT_CW, ROT_CCW, false);
    inputs::addDigital(GPIO_NUM_18, ROT_PUSH, true, true);

#ifdef VERTICAL_CIRCUIT_LAYOUT
    //   3-button modules in vertical layout
    add3BtnModule_X_Y_Back(GPIO_NUM_26, GPIO_NUM_33, GPIO_NUM_27);
    add3BtnModule_A_B_Start(GPIO_NUM_3, GPIO_NUM_23, GPIO_NUM_22);
    add3BtnModule_RT_RB_RSB(GPIO_NUM_2, GPIO_NUM_15, GPIO_NUM_0);
    add3BtnModule_LT_LB_LSB(GPIO_NUM_12, GPIO_NUM_14, GPIO_NUM_13);
#else
    //   3-button modules in horizontal layout
    add3BtnModule_X_Y_Back(GPIO_NUM_26, GPIO_NUM_33, GPIO_NUM_27);
    add3BtnModule_LT_LB_LSB(GPIO_NUM_23, GPIO_NUM_3, GPIO_NUM_22);
    add3BtnModule_RT_RB_RSB(GPIO_NUM_2, GPIO_NUM_15, GPIO_NUM_0);
    add3BtnModule_A_B_Start(GPIO_NUM_14, GPIO_NUM_12, GPIO_NUM_13);
#endif

    //  shift paddles
    inputs::addDigital(GPIO_NUM_32, JOY_LSHIFT_PADDLE, true, true);
    inputs::addDigital(GPIO_NUM_25, JOY_RSHIFT_PADDLE, true, true);

    // Wheel functions
    inputs::setDigitalClutchPaddles(MOD_LT, MOD_RT);
    inputHub::setDPADControls(DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT);
    inputHub::setClutchCalibrationButtons(FUNKY_CW, FUNKY_CCW);
    inputHub::setSelectClutchFunctionBitmaps(
        BITMAP(ROT_PUSH) | BITMAP(JOY_Y),
        0ULL,
        BITMAP(ROT_PUSH) | BITMAP(JOY_X),
        BITMAP(ROT_PUSH) | BITMAP(JOY_BACK) );
}

//------------------------------------------------------------------
// Arduino entry point
//------------------------------------------------------------------

void setup()
{
    esp_log_level_set("*", ESP_LOG_ERROR);
    clutchState::begin();
    inputs::begin();
    simWheelSetup();

    hidImplementation::begin(
        DEVICE_NAME,
        DEVICE_MANUFACTURER,
        false);
    inputs::start();
}

void loop()
{
    vTaskDelay(portMAX_DELAY);
}