#include "esphome/core/helpers.h"  // for clamp() and lerp()
#include "output.h"

namespace esphome {
namespace opentherm {

void opentherm::OpenthermOutput::write_state(float state) {
  ESP_LOGD("opentherm.output", "Received state: %.2f. Min value: %.2f, max value: %.2f", state, min_value_, max_value_);
  if (state < 0.003 && this->zero_means_zero_) {
    state = 0.0;
    ESP_LOGD("opentherm.output", "Zeroing state");
  }
  else {
    state = lerp(state, min_value_, max_value_);
    ESP_LOGD("opentherm.output", "Linear extrapolation result: %.2f", this->state);
    state = clamp(state, min_value_, max_value_);
    ESP_LOGD("opentherm.output", "Clamping result: %.2f", this->state);
  }
  this->has_state_ = true;
  ESP_LOGD("opentherm.output", "Output %s set to %.2f", this->id_, this->state);
}
}  // namespace opentherm
}  // namespace esphome
