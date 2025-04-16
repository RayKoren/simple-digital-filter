#include "DigitalFilter.hpp"
#include <portaudio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <thread>
#include <atomic>
#include <mutex>

// Global variables for audio processing
std::atomic<double> currentCutoffFrequency{200.0};
std::mutex filterMutex;
DigitalFilter* filter = nullptr;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(-1.0, 1.0);

// Audio callback function
static int audioCallback(const void* inputBuffer, void* outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void* userData) {
    float* out = (float*)outputBuffer;
    (void)inputBuffer; // Unused parameter
    
    std::lock_guard<std::mutex> lock(filterMutex);
    
    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        // Generate white noise
        double noise = dis(gen);
        
        // Process through filter
        double filtered = filter->processSample(noise);
        
        // Write to output buffer (stereo)
        *out++ = filtered;
        *out++ = filtered;
    }
    
    return paContinue;
}

void updateFilterThread() {
    while (true) {
        double newCutoff;
        std::cout << "Enter new cutoff frequency (Hz) or 0 to quit: ";
        std::cin >> newCutoff;
        
        if (newCutoff <= 0) {
            break;
        }
        
        std::lock_guard<std::mutex> lock(filterMutex);
        filter->setCutoffFrequency(newCutoff);
        std::cout << "Cutoff frequency set to " << newCutoff << " Hz\n";
    }
}

int main() {
    // Initialize PortAudio
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }
    
    // Create filter
    filter = new DigitalFilter(currentCutoffFrequency, 44100.0);
    
    // Open audio stream
    PaStream* stream;
    err = Pa_OpenDefaultStream(&stream,
                              0,          // No input channels
                              2,          // Stereo output
                              paFloat32,  // 32-bit floating point output
                              44100,      // Sample rate
                              256,        // Frames per buffer
                              audioCallback,
                              nullptr);   // No user data
    
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        Pa_Terminate();
        return 1;
    }
    
    // Start audio stream
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }
    
    // Start filter update thread
    std::thread updateThread(updateFilterThread);
    
    // Wait for update thread to finish
    updateThread.join();
    
    // Cleanup
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    delete filter;
    
    return 0;
}
