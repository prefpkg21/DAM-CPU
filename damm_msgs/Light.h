#ifndef _ROS_damm_msgs_Light_h
#define _ROS_damm_msgs_Light_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace damm_msgs
{

  class Light : public ros::Msg
  {
    public:
      typedef bool _led1_type;
      _led1_type led1;
      typedef bool _led2_type;
      _led2_type led2;

    Light():
      led1(0),
      led2(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_led1;
      u_led1.real = this->led1;
      *(outbuffer + offset + 0) = (u_led1.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->led1);
      union {
        bool real;
        uint8_t base;
      } u_led2;
      u_led2.real = this->led2;
      *(outbuffer + offset + 0) = (u_led2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->led2);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_led1;
      u_led1.base = 0;
      u_led1.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->led1 = u_led1.real;
      offset += sizeof(this->led1);
      union {
        bool real;
        uint8_t base;
      } u_led2;
      u_led2.base = 0;
      u_led2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->led2 = u_led2.real;
      offset += sizeof(this->led2);
     return offset;
    }

    const char * getType(){ return "damm_msgs/Light"; };
    const char * getMD5(){ return "975d351cbf43b0dc116a176315305423"; };

  };

}
#endif
