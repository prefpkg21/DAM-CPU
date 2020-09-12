#ifndef _ROS_damm_msgs_Servfour_h
#define _ROS_damm_msgs_Servfour_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace damm_msgs
{

  class Servfour : public ros::Msg
  {
    public:
      typedef int16_t _dxl1_type;
      _dxl1_type dxl1;
      typedef int16_t _dxl2_type;
      _dxl2_type dxl2;
      typedef int16_t _dxl3_type;
      _dxl3_type dxl3;
      typedef int16_t _dxl4_type;
      _dxl4_type dxl4;
      typedef int16_t _linear_type;
      _linear_type linear;

    Servfour():
      dxl1(0),
      dxl2(0),
      dxl3(0),
      dxl4(0),
      linear(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_dxl1;
      u_dxl1.real = this->dxl1;
      *(outbuffer + offset + 0) = (u_dxl1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dxl1.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->dxl1);
      union {
        int16_t real;
        uint16_t base;
      } u_dxl2;
      u_dxl2.real = this->dxl2;
      *(outbuffer + offset + 0) = (u_dxl2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dxl2.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->dxl2);
      union {
        int16_t real;
        uint16_t base;
      } u_dxl3;
      u_dxl3.real = this->dxl3;
      *(outbuffer + offset + 0) = (u_dxl3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dxl3.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->dxl3);
      union {
        int16_t real;
        uint16_t base;
      } u_dxl4;
      u_dxl4.real = this->dxl4;
      *(outbuffer + offset + 0) = (u_dxl4.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dxl4.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->dxl4);
      union {
        int16_t real;
        uint16_t base;
      } u_linear;
      u_linear.real = this->linear;
      *(outbuffer + offset + 0) = (u_linear.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_linear.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->linear);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_dxl1;
      u_dxl1.base = 0;
      u_dxl1.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dxl1.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->dxl1 = u_dxl1.real;
      offset += sizeof(this->dxl1);
      union {
        int16_t real;
        uint16_t base;
      } u_dxl2;
      u_dxl2.base = 0;
      u_dxl2.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dxl2.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->dxl2 = u_dxl2.real;
      offset += sizeof(this->dxl2);
      union {
        int16_t real;
        uint16_t base;
      } u_dxl3;
      u_dxl3.base = 0;
      u_dxl3.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dxl3.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->dxl3 = u_dxl3.real;
      offset += sizeof(this->dxl3);
      union {
        int16_t real;
        uint16_t base;
      } u_dxl4;
      u_dxl4.base = 0;
      u_dxl4.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dxl4.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->dxl4 = u_dxl4.real;
      offset += sizeof(this->dxl4);
      union {
        int16_t real;
        uint16_t base;
      } u_linear;
      u_linear.base = 0;
      u_linear.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_linear.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->linear = u_linear.real;
      offset += sizeof(this->linear);
     return offset;
    }

    const char * getType(){ return "damm_msgs/Servfour"; };
    const char * getMD5(){ return "56a268fbdaab198839dd86d7c82ad85d"; };

  };

}
#endif
