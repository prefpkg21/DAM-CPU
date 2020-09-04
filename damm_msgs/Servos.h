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
      typedef float _dxl4_type;
      _dxl4_type dxl4;
      typedef float _linear_type;
      _linear_type linear;

    Servos():
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
      offset += serializeAvrFloat64(outbuffer + offset, this->dxl1);
      offset += serializeAvrFloat64(outbuffer + offset, this->dxl2);
      offset += serializeAvrFloat64(outbuffer + offset, this->dxl3);
      offset += serializeAvrFloat64(outbuffer + offset, this->dxl4);
      offset += serializeAvrFloat64(outbuffer + offset, this->linear);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->dxl1));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->dxl2));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->dxl3));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->dxl4));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->linear));
     return offset;
    }

    const char * getType(){ return "damm_msgs/Servos"; };
    const char * getMD5(){ return "6b6fea426358a73b5675cff7baddf457"; };

  };

}
#endif
