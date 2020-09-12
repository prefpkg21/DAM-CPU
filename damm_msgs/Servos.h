#ifndef _ROS_damm_msgs_Servos_h
#define _ROS_damm_msgs_Servos_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace damm_msgs
{

  class Servos : public ros::Msg
  {
    public:
      typedef float _dxl1_type;
      _dxl1_type dxl1;
      typedef float _dxl2_type;
      _dxl2_type dxl2;
      typedef float _dxl3_type;
      _dxl3_type dxl3;
      typedef float _linear_type;
      _linear_type linear;

    Servos():
      dxl1(0),
      dxl2(0),
      dxl3(0),
      linear(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_dxl1;
      u_dxl1.real = this->dxl1;
      *(outbuffer + offset + 0) = (u_dxl1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dxl1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dxl1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dxl1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dxl1);
      union {
        float real;
        uint32_t base;
      } u_dxl2;
      u_dxl2.real = this->dxl2;
      *(outbuffer + offset + 0) = (u_dxl2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dxl2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dxl2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dxl2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dxl2);
      union {
        float real;
        uint32_t base;
      } u_dxl3;
      u_dxl3.real = this->dxl3;
      *(outbuffer + offset + 0) = (u_dxl3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dxl3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dxl3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dxl3.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dxl3);
      union {
        float real;
        uint32_t base;
      } u_linear;
      u_linear.real = this->linear;
      *(outbuffer + offset + 0) = (u_linear.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_linear.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_linear.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_linear.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->linear);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_dxl1;
      u_dxl1.base = 0;
      u_dxl1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dxl1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dxl1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dxl1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dxl1 = u_dxl1.real;
      offset += sizeof(this->dxl1);
      union {
        float real;
        uint32_t base;
      } u_dxl2;
      u_dxl2.base = 0;
      u_dxl2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dxl2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dxl2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dxl2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dxl2 = u_dxl2.real;
      offset += sizeof(this->dxl2);
      union {
        float real;
        uint32_t base;
      } u_dxl3;
      u_dxl3.base = 0;
      u_dxl3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dxl3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dxl3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dxl3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dxl3 = u_dxl3.real;
      offset += sizeof(this->dxl3);
      union {
        float real;
        uint32_t base;
      } u_linear;
      u_linear.base = 0;
      u_linear.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_linear.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_linear.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_linear.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->linear = u_linear.real;
      offset += sizeof(this->linear);
     return offset;
    }

    const char * getType(){ return "damm_msgs/Servos"; };
    const char * getMD5(){ return "407cdb1ad6178d9cbff717a19cc80744"; };

  };

}
#endif
