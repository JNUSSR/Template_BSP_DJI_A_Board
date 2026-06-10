#ifndef DVC_SERVO_H_
#define DVC_SERVO_H_

#include "drv_uart.h"

#define GET_LOW_BYTE(A) ((uint8_t)(A))
//宏函数 获得A的低八位
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))
//宏函数 获得A的高八位


#define FRAME_HEADER 0x55  
#define CMD_SERVO_MOVE 0x03           
#define CMD_ACTION_GROUP_RUN 0x06     
#define CMD_ACTION_GROUP_STOP 0x07    
#define CMD_ACTION_GROUP_SPEED 0x0B   
#define CMD_GET_BATTERY_VOLTAGE 0x0F  
#define CMD_MULT_SERVO_POS_READ 0x15
#define CMD_MULT_SERVO_UNLOAD 0x14


typedef struct
{
    uint8_t ID;
    uint16_t Position;
} Struct_Servo;


class Class_Servo_Bus
{
public:
    void Init(Struct_UART_Manage_Object * __UART_Manage_Object);

    inline uint8_t Get_RX_Command(void);

    inline uint16_t Get_Voltage(void);

    inline uint8_t Get_NumServo(void);

    inline Struct_Servo * Get_Servos(uint8_t __Index);
    
    void Add_Servo2Bus(const uint8_t * __IDs, uint8_t __num);

    void CMD_MoveServos(uint8_t Num, uint16_t Time, ...);

    void CMD_RunActionGroup(uint8_t numOfAction, uint16_t Times);

    void CMD_StopActionGroup(void);

    void CMD_SetActionGroupSpeed(uint8_t numOfAction, uint16_t Speed);

    void CMD_SetAllActionGroupSpeed(uint16_t Speed);

    void CMD_GetBatteryVoltage(void);

    void CMD_MultServoPosRead(uint8_t Num, ...);

    void CMD_UnloadServo(uint8_t Num, ...);

    //在类定义的回调函数中处理数据DataProcess,再在外层封装一层函数，该函数调用类中的回调函数，再对类回调中处理号的函数进行判断，做出相应措施
    void UART_RxCpltCallback(uint8_t *Rx_Data, uint16_t Length);
    

protected:
    Struct_Servo servo[32];

    uint8_t id_map[33] = {0};

    uint8_t Num_Servo = 0;

    Struct_UART_Manage_Object * UART_Manage_Object;

    uint16_t Position_Now;

    uint8_t Servo_TXCommand_Buffer[128];

    uint8_t Servo_RX_Buffer[128];

    uint16_t Voltage;

    bool isUartRxCplt;

    uint8_t RX_Command;

    void RXCommand_Judge();

    uint16_t BatteryVolt;

    //若有可能在一次接收中包含多个指令，使用以下变量

    // uint8_t RX_Command_Num;


    

};

inline uint8_t Class_Servo_Bus::Get_RX_Command(void)
{
    return RX_Command;
}

inline uint16_t Class_Servo_Bus::Get_Voltage(void)
{
    return BatteryVolt;
}

inline uint8_t Class_Servo_Bus::Get_NumServo(void)
{
    return Num_Servo;
}

inline Struct_Servo * Class_Servo_Bus::Get_Servos(uint8_t __Index)
{
    return &servo[__Index];
}
#endif /* DVC_SERVO_H_ */