#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"

namespace esphome {
namespace qwiic_twist {

class QwiicTwist : public light::LightOutput {

  public:
    light::LightTraits get_traits() override {
      auto traits = light::LightTraits();
      traits.set_supported_color_modes({light::ColorMode::RGB});
      return traits;
    }

    void write_state(light::LightState *state) override {
      float red, green, blue;
      state->current_values_as_rgb(&red, &green, &blue, false);

      Wire.beginTransmission(i2c_address_);
      Wire.write(0x0D); // Red
      Wire.write(char(red*255));
      Wire.endTransmission();
      
      Wire.beginTransmission(i2c_address_);
      Wire.write(0x0E); // Green
      Wire.write(char(green*255));
      Wire.endTransmission();
      
      Wire.beginTransmission(i2c_address_);
      Wire.write(0x0F); // Blue
      Wire.write(char(blue*255));
      Wire.endTransmission();
    }
  
  protected:
    char i2c_address_ = 0x3F;

};

} // namespace qwiic_twist
} // namespace esphome