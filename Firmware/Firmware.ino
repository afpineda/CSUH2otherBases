/**
 * @author Ángel Fernández Pineda. Madrid. Spain.
 * @date 2022-10-23
 * @brief Conversion of Fanatec's Clubsport Universal Hub to wireless
 *
 * @copyright Creative Commons Attribution 4.0 International (CC BY 4.0)
 *
 */

#include "SimWheel.hpp"

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

// #define VERTICAL_CIRCUIT_LAYOUT 0

#define BLE_CUSTOM_PID 0xFFF0

//------------------------------------------------------------------
// Setup
//------------------------------------------------------------------

void add3BtnModule_X_Y_Back(gpio_num_t X, gpio_num_t Y, gpio_num_t Back)
{
    inputs::addButton(X, JOY_X);
    inputs::addButton(Y, JOY_Y);
    inputs::addButton(Back, JOY_BACK);
}

void add3BtnModule_LT_LB_LSB(gpio_num_t LT, gpio_num_t LB, gpio_num_t LSB)
{
    inputs::addButton(LT, MOD_LT);
    inputs::addButton(LB, MOD_LB);
    inputs::addButton(LSB, MOD_LSB);
}

void add3BtnModule_RT_RB_RSB(gpio_num_t RT, gpio_num_t RB, gpio_num_t RSB)
{
    inputs::addButton(RT, MOD_RT);
    inputs::addButton(RB, MOD_RB);
    inputs::addButton(RSB, MOD_RSB);
}

void add3BtnModule_A_B_Start(gpio_num_t A, gpio_num_t B, gpio_num_t Start)
{
    inputs::addButton(A, JOY_A);
    inputs::addButton(B, JOY_B);
    inputs::addButton(Start, JOY_START);
}

void simWheelSetup()
{
    //   Funky switch
    inputs::addRotaryEncoder(
        GPIO_NUM_16,
        GPIO_NUM_39,
        FUNKY_CW,
        FUNKY_CCW,
        true);
    inputs::addButton(GPIO_NUM_36, DPAD_UP);
    inputs::addButton(GPIO_NUM_34, DPAD_LEFT);
    inputs::addButton(GPIO_NUM_35, DPAD_RIGHT);
    inputs::addButton(GPIO_NUM_19, DPAD_DOWN);
    inputs::addButton(GPIO_NUM_21, FUNKY_PUSH);

    //   Additional rotary encoder
    inputs::addRotaryEncoder(
        GPIO_NUM_17,
        GPIO_NUM_5,
        ROT_CW,
        ROT_CCW,
        false);
    inputs::addButton(GPIO_NUM_18, ROT_PUSH);

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
    inputs::addButton(GPIO_NUM_32, JOY_LSHIFT_PADDLE);
    inputs::addButton(GPIO_NUM_25, JOY_RSHIFT_PADDLE);

    // Wheel functions
    inputHub::clutch::inputs(MOD_LT, MOD_RT);
    inputHub::clutch::bitePointInputs(FUNKY_CW, FUNKY_CCW);
    inputHub::clutch::cycleWorkingModeInputs({ROT_PUSH, JOY_Y});
    inputHub::dpad::inputs(DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT);
    inputMap::setOptimal();
}

//------------------------------------------------------------------

void customFirmware()
{
    simWheelSetup();
    hid::configure(
        DEVICE_NAME,
        DEVICE_MANUFACTURER,
        false
#if defined(BLE_CUSTOM_VID)
        ,
        BLE_CUSTOM_VID
#if defined(BLE_CUSTOM_PID)
        ,
        BLE_CUSTOM_PID
#endif
#endif
    );
    hid::connectivity(Connectivity::BLE);
}

//------------------------------------------------------------------
// Arduino entry point
//------------------------------------------------------------------

void setup()
{
    firmware::run(customFirmware);
}

void loop()
{
    vTaskDelay(portMAX_DELAY);
}