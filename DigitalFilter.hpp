#pragma once

#include <vector>
#include <cmath>

class DigitalFilter {
public:
    DigitalFilter(double cutoffFrequency, double sampleRate);
    
    // Update filter parameters
    void setCutoffFrequency(double cutoffFrequency);
    void setSampleRate(double sampleRate);
    
    // Process a single sample
    double processSample(double input);
    
    // Process a buffer of samples
    void processBuffer(const std::vector<double>& input, std::vector<double>& output);
    
private:
    double cutoffFrequency_;
    double sampleRate_;
    double alpha_;  // Filter coefficient
    double prevOutput_;  // Previous output for the filter
    
    void updateCoefficients();
}; 