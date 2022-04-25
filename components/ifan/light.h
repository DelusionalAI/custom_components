#pragma once

#include "esphome/core/component.h"
#include "esphome/components/output/binary_output.h"
#include "esphome/components/light/light_output.h"
#include "esphome.h"

namespace esphome {
namespace ifan {

class IFanLight : public light::LightOutput {
 public:
  light::LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes({light::ColorMode::ON_OFF});
    return traits;
  }
  void write_state(light::LightState *state) override {
    bool binary;
    pinMode(9, 0x01);
    state->current_values_as_binary(&binary);
    if (binary)
      digitalWrite(9, LOW);
    else
      digitalWrite(9, HIGH);
    current_state = binary;
  }
  static void toggle_light(){
    this->state = !current_state;
    write_state();
  }
 protected:
  bool current_state;
};  // class
}  // namespace ifan
}  // namespace esphome
