// Defines
#define TFMINI_BAUDRATE   115200
#define TFMINI_DEBUGMODE  0

// The frame size is nominally 9 characters, but we don't include the first two 0x59's marking the start of the frame
#define TFMINI_FRAME_SIZE                 7

// Timeouts
#define TFMINI_MAXBYTESBEFOREHEADER       30
#define TFMINI_MAX_MEASUREMENT_ATTEMPTS   10

// States
#define READY                             0
#define ERROR_SERIAL_NOHEADER             1
#define ERROR_SERIAL_BADCHECKSUM          2
#define ERROR_SERIAL_TOOMANYTRIES         3
#define MEASUREMENT_OK                    10


//
// Driver Class Definition
//
class TFMini {
  public: 
    TFMini(void);

    // Configuration
    boolean begin(Stream* _streamPtr);
    void setSingleScanMode();
    
    // Data collection
    uint16_t getDistance();
    uint16_t getRecentSignalStrength();
    void externalTrigger();

  private:
    Stream* streamPtr;
    int state;
    uint16_t distance;
    uint16_t strength;
    
    // Low-level communication
    void setStandardOutputMode();
    void setConfigMode();
    int takeMeasurement();
    
};