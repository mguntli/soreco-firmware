#ifndef DEVICESTATEMACHINE_H
#define DEVICESTATEMACHINE_H

#include <stdint.h>
#include "DeviceHandler.h"

/**
 * Command line interface for development to interact with the device.
 */
class DeviceStateMachine {
public:

    /**
    * Default constructor.
    */
    DeviceStateMachine(WifiManager& wifiManager, SonosDevice& sonosDevice);

    /**
    * Destructor.
    */
    ~DeviceStateMachine(void);

    /**
     * Runs the state machine. Call this method for running the state machine.
     */
    void runStateMachine(void);

    /**
     * Rests the state machine.
     */
    void resetStateMachine(void);

    /**
     * Returns the device handler
     */
    RemoteEventHandlerIfc& getRemoteHandler(void);
private:

    /**
     * States provided by this state machine
     */
    struct State {
        enum Id {
            Init,
            Hotspot_Starting,
            Hotspot_Idle,
            Wifi_Connecting,
            Sonos_Connecting,
            Sonos_Retry,
            Idle
        };
    };

    /**
    * Private copy constructor.
    */
    DeviceStateMachine(const DeviceStateMachine&);

    /**
    * Private assignment constructor.
    */
    DeviceStateMachine& operator=(const DeviceStateMachine&);

    void onEnterState(const State::Id state);
    void onRunState(const State::Id state);
    void onLeaveState(const State::Id state);

    /**
     * Switch to the given state if conditional valid
     */
    void conditionalStep(const bool isValid, const State::Id state);

    const uint16_t SONOS_RETRY_DELAY_MS = 5000;

    State::Id m_currentState;
    State::Id m_nextState;
    DeviceHandler m_deviceHandler;
    unsigned long m_sonosRetryTimestampMs;
};

#endif //DEVICESTATEMACHINE_H