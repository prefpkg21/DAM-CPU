/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Taehun Lim (Darby) */

#include <DynamixelWorkbench.h>
#include <ros.h>

#include <Light.h>
#include <Servos.h>
#include <Servfour.h>
#include <Servo.h>
#include <math.h> 
#include <sensor_msgs/Joy.h>
#include <std_msgs/Empty.h>


#define BAUDRATE  1000000
#define SRV_COUNT 4
#define DXL_ID_1  1
#define DXL_ID_2  2
#define DXL_ID_3  3
#define DXL_ID_4  4
#define DXL1_MAX   4090
#define DXL1_MIN   0
#define DXL2_MAX   3090
#define DXL2_MIN   1030
#define DXL3_MAX   3360
#define DXL3_MIN   0
#define DXL4_MAX   4090
#define DXL4_MIN   10
#define LIN_MAX   135
#define LIN_MIN   45
#define CUT_LEFT  0
#define CUT_RIGHT  3000
#define DXL1_HOME  2040
#define DXL2_HOME  2040
#define CUT_HOME  1530
#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

DynamixelWorkbench dxl_wb;
Servo myservo;

const int led_1_pin = 13;
const int led_2_pin = 12;
int led1 = 0;
int led2 = 0;
  uint8_t dxl_id[4] = {DXL_ID_1, DXL_ID_2, DXL_ID_3, DXL_ID_4};
  int32_t hard_stat[4] = {0, 0, 0, 0};
  int32_t PID_position_p[4] = {300, 900, 950, 350};
  int32_t PID_position_i[4] = {0, 30, 0, 0};
  int32_t return_delay[4] = {0, 0, 0, 0};
  int32_t present_position[4] = {0, 0, 0, 0};
  int32_t goal_position[4] = {2048, 2048, 1530, 1530};
  int32_t home_position[4] = {DXL1_HOME, DXL2_HOME, CUT_HOME, DXL2_HOME};
  int     lin_srvo_goal = 70;
  int     lin_srvo_set  = 0;
const uint8_t handler_index = 0;
const uint8_t write_handler_index = 1;
const uint8_t integral_handler_index = 2;
const uint8_t return_handler_index = 3;
const uint8_t servo_count = SRV_COUNT; 

void reset_dxls( const std_msgs::Empty& rst) {
  reboot_all_dxl();
  init_dxl();
}

void goal_cb( const damm_msgs::Servfour& goal_msg);
void light_cb( const damm_msgs::Light&);
//ROS Setup
ros::NodeHandle nh;

damm_msgs::Servfour srvo_goal_msg;

damm_msgs::Light led_msg;

ros::Subscriber<damm_msgs::Servfour> goal_sub("damm_goal",  &goal_cb);
ros::Subscriber<damm_msgs::Light> light_sub("damm_light",  &light_cb);
ros::Subscriber<std_msgs::Empty> reset_sub ("reset_dxl",  &reset_dxls);
//ros::Publisher  position_pub("damm_position",  &srvo_pos_msg);



bool same_same (int32_t* goal, int32_t* pos, int len_g, int len_p) {
  if (len_g != len_p) return false;

  for (size_t n = 0; n < len_g; n++) if (abs(goal[n]-pos[n]) > 15) return false;

  return true;

}

void init_dxl() {
  const char *log;
  bool result = false;

  uint16_t model_number = 0;

  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  
  //Ping all servos to wakeup and assign
  for (int cnt = 0; cnt < SRV_COUNT; cnt++)
  {
    result = dxl_wb.ping(dxl_id[cnt], &model_number, &log);
    
    result = dxl_wb.jointMode(dxl_id[cnt], 0, 0, &log);
   
  } 
  nh.spinOnce();
  // Sync Handler allows writing to single register for multiple servos
  result = dxl_wb.addSyncWriteHandler(dxl_id[0], "Goal_Position", &log);
  dxl_wb.addSyncWriteHandler(dxl_id[0], "Position_P_Gain", &log);
  dxl_wb.addSyncWriteHandler(dxl_id[0], "Position_I_Gain", &log);
  dxl_wb.addSyncWriteHandler(dxl_id[0], "Return_Delay_Time", &log);
  //same for Read
  //result = dxl_wb.addSyncReadHandler(dxl_id[0], "Present_Position", &log);
  //result = dxl_wb.addSyncReadHandler(dxl_id[0], "Hardware_Error_Status", &log);
  
  result = dxl_wb.syncWrite(write_handler_index, dxl_id, SRV_COUNT, PID_position_p, 1, &log);
  result = dxl_wb.syncWrite(integral_handler_index, dxl_id, SRV_COUNT, PID_position_i, 1, &log);
  dxl_wb.syncWrite(return_handler_index, &return_delay[0], &log);
  //Set Home positions
  result = dxl_wb.syncWrite(handler_index, dxl_id, SRV_COUNT, home_position, 1, &log);

}

void setup() 
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(led_1_pin, OUTPUT);
  pinMode(led_2_pin, OUTPUT);

  digitalWrite(led_1_pin, HIGH); //RED
  digitalWrite(led_2_pin, LOW);  //GREEN both Yellow
  nh.getHardware()->setBaud(115200);
  
  nh.initNode();
  //nh.advertise(position_pub);
  nh.subscribe(goal_sub);
  nh.subscribe(light_sub);
  nh.subscribe(reset_sub);
  init_dxl();
  /*
  const char *log;
  bool result = false;

  uint16_t model_number = 0;

  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  
  //Ping all servos to wakeup and assign
  for (int cnt = 0; cnt < SRV_COUNT; cnt++)
  {
    result = dxl_wb.ping(dxl_id[cnt], &model_number, &log);
    
    result = dxl_wb.jointMode(dxl_id[cnt], 0, 0, &log);
   
  } 
  // Sync Handler allows writing to single register for multiple servos
  result = dxl_wb.addSyncWriteHandler(dxl_id[0], "Goal_Position", &log);
  dxl_wb.addSyncWriteHandler(dxl_id[0], "Position_P_Gain", &log);
  dxl_wb.addSyncWriteHandler(dxl_id[0], "Position_I_Gain", &log);
  dxl_wb.addSyncWriteHandler(dxl_id[0], "Return_Delay_Time", &log);
  //same for Read
  result = dxl_wb.addSyncReadHandler(dxl_id[0], "Present_Position", &log);
  result = dxl_wb.addSyncReadHandler(dxl_id[0], "Hardware_Error_Status", &log);
  
  result = dxl_wb.syncWrite(write_handler_index, dxl_id, SRV_COUNT, PID_position_p, 1, &log);
  result = dxl_wb.syncWrite(integral_handler_index, dxl_id, SRV_COUNT, PID_position_i, 1, &log);
  dxl_wb.syncWrite(return_handler_index, &return_delay[0], &log);
  //Set Home positions
  result = dxl_wb.syncWrite(handler_index, dxl_id, SRV_COUNT, home_position, 1, &log);
  */
  myservo.write(lin_srvo_goal);
  
}

void loop() 
{  
  
  const char *log;
  bool result = false;

  
  //if (!(same_same(goal_position, present_position, SRV_COUNT, SRV_COUNT))) result = dxl_wb.syncWrite(handler_index, dxl_id, SRV_COUNT, goal_position, 1, &log);
  result = dxl_wb.syncWrite(handler_index, dxl_id, SRV_COUNT, goal_position, 1, &log);
  //result = dxl_wb.syncRead(handler_index, &log);
  
  //result = dxl_wb.getSyncReadData(handler_index, &present_position[0], &log);
  //result = dxl_wb.syncRead(write_handler_index, &log);
  //result = dxl_wb.getSyncReadData(write_handler_index, &hard_stat[0], &log);

  //write linear Servo
  if (lin_srvo_goal != lin_srvo_set){
    myservo.write(lin_srvo_goal);
    lin_srvo_set = lin_srvo_goal;
  }
  
  //hardware_check(hard_stat);
  
  nh.spinOnce();
  
}

void goal_cb( const damm_msgs::Servfour& goal_msg){
   
    int linset = goal_msg.dxl3;
    //Max/min to maintain boundary
    goal_position[0] = fmax(fmin(goal_msg.dxl1, DXL1_MAX),DXL1_MIN);
    goal_position[1] = fmax(fmin(goal_msg.dxl2, DXL2_MAX),DXL2_MIN);
    lin_srvo_goal = fmax(fmin(goal_msg.linear, LIN_MAX), LIN_MIN);
    if (linset > 0){
      goal_position[2] = CUT_LEFT;
    }else if (linset < 0){
      goal_position[2] = CUT_RIGHT;
    }else{
      goal_position[2] = CUT_HOME;
    }

    goal_position[3] = fmax(fmin(goal_msg.dxl4, DXL4_MAX),DXL4_MIN);
    
   
}

void light_cb( const damm_msgs::Light& msg){
   led1 = msg.led1;
   led2 = msg.led2;
  (led1) ? digitalWrite(led_1_pin, HIGH) : digitalWrite(led_1_pin, LOW);
  (led2) ? digitalWrite(led_2_pin, HIGH) : digitalWrite(led_2_pin, LOW); 

}
void reboot_all_dxl(){
  const char *log;
  for( size_t n = 0; n < SRV_COUNT; n++){
    dxl_wb.reboot(uint8_t(n), &log);
  }
  nh.spinOnce();
 init_dxl();
}
bool hardware_check ( const int32_t* return_stat){
  
  for( size_t n = 0; n < SRV_COUNT; n++){
    if (return_stat[n]){
      reboot_all_dxl();
      break;
    }
    nh.spinOnce();
  }
}
