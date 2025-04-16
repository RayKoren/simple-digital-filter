#include "DigitalFilter.hpp"

DigitalFilter::DigitalFilter(double cutoffFrequency, double sampleRate)
    : cutoffFrequency_(cutoffFrequency)
    , sampleRate_(sampleRate)
    , prevOutput_(0.0)
{
    updateCoefficients();
}

void DigitalFilter::setCutoffFrequency(double cutoffFrequency) {
    cutoffFrequency_ = cutoffFrequency;
    updateCoefficients();
}

void DigitalFilter::setSampleRate(double sampleRate) {
    sampleRate_ = sampleRate;
    updateCoefficients();
}

void DigitalFilter::updateCoefficients() {
    // Calculate the filter coefficient using the formula for a first-order low-pass filter
    // alpha = 1 / (1 + RC), where RC = 1/(2*pi*fc)
    double RC = 1.0 / (2.0 * M_PI * cutoffFrequency_);
    alpha_ = 1.0 / (1.0 + RC * sampleRate_);
}

double DigitalFilter::processSample(double input) {
    // Apply the first-order low-pass filter equation:
    // y[n] = alpha * x[n] + (1 - alpha) * y[n-1]
    double output = alpha_ * input + (1.0 - alpha_) * prevOutput_;
    prevOutput_ = output;
    return output;
}

void DigitalFilter::processBuffer(const std::vector<double>& input, std::vector<double>& output) {
    output.resize(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = processSample(input[i]);
    }
} 