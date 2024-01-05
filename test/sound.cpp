#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

void PlayLowFrequencySound(DWORD frequency, DWORD duration) {
    HWAVEOUT hWaveOut;
    WAVEFORMATEX wfx;

    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = 1;               // Mono audio
    wfx.nSamplesPerSec = frequency;  // Set the desired frequency
    wfx.wBitsPerSample = 16;         // 16-bit audio
    wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) / 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
    wfx.cbSize = 0;

    if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
        // Generate a simple sine wave for demonstration
        const int sampleRate = 44100;  // 44.1 kHz sample rate
        const double twoPi = 6.283185307179586;
        const double amplitude = 0.5;

        DWORD dataSize = duration * wfx.nAvgBytesPerSec / 1000;
        BYTE* buffer = new BYTE[dataSize];

        for (DWORD i = 0; i < dataSize; i += 2) {
            double time = static_cast<double>(i) / (2 * wfx.nChannels * wfx.wBitsPerSample / 8) / sampleRate;
            int16_t sample = static_cast<int16_t>(amplitude * 32767.0 * sin(twoPi * frequency * time));

            buffer[i] = static_cast<BYTE>(sample & 0xFF);
            buffer[i + 1] = static_cast<BYTE>((sample >> 8) & 0xFF);
        }

        WAVEHDR waveHeader;
        waveHeader.lpData = reinterpret_cast<LPSTR>(buffer);
        waveHeader.dwBufferLength = dataSize;
        waveHeader.dwFlags = 0;

        waveOutPrepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &waveHeader, sizeof(WAVEHDR));

        // Wait for the sound to finish playing
        while (waveOutUnprepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR)) == WAVERR_STILLPLAYING) {
            Sleep(10);
        }

        delete[] buffer;
        waveOutClose(hWaveOut);
    }
}

int main() {
    PlayLowFrequencySound(100, 500);  // Play a low-frequency sound for 500 milliseconds
    return 0;
}
