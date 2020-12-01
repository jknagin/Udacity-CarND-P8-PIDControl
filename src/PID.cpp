#include "PID.h"
#include <cmath>

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  p_error = 0;
  i_error = 0;
  d_error = 0;
}

void PID::UpdateError(double cte) {
  /**
   * Update PID errors based on cte.
   */
  d_error = Kd*(cte - p_error/Kp);  // p_error/Kp is the previous cte
  p_error = Kp*cte;
  i_error += Ki*cte;
}

double PID::TotalError() {
  /**
   * Calculate and return the total error
   */
   return p_error + i_error + d_error;
}

double PID::CalculateSteering()
{
  /**
   * Return steering value
   */
  return -TotalError();
}