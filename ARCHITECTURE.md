# Arduino Alarm System - Architecture Documentation

## Project Overview

This is an Arduino-based security alarm system featuring PIN code authentication, motion detection, and visual/audio feedback. The system is built using a modular, event-driven architecture with a state machine pattern at its core.

**Target Platform:** Arduino UNO R4 WiFi (or compatible boards with LED Matrix support)

## System Architecture

### Design Philosophy

The project follows these key principles:
- **Non-blocking execution**: All components use callback-based, event-driven design
- **Separation of concerns**: Each hardware component has its own dedicated class
- **State machine pattern**: Central alarm logic managed through well-defined states
- **Callback/Observer pattern**: Components communicate via callbacks to maintain loose coupling

### Hardware Components

| Component | Pin(s) | Purpose |
|-----------|--------|---------|
| PIR Motion Sensor | Digital Pin 9 | Detects motion when system is armed |
| Buzzer | Digital Pin 10 | Audio feedback and alarm sound |
| 4x3 Matrix Keypad | Rows: 5,4,3,2 / Cols: 8,7,6 | PIN entry (0-9, *, #) |
| LED Matrix | Built-in (Arduino UNO R4) | Visual display for feedback |

## Core Components

### 1. AlarmStateMachine (`AlarmStateMachine.h/cpp`)

**Purpose:** Central coordinator managing alarm system states and transitions. Owns and manages an internal Timer instance.

**States:**
```
DISARMED    → System off, ready to arm
ARMING      → 10-second countdown to arm (exit delay)
ARMED       → Monitoring for motion
ENTRY_DELAY → Motion detected, 10 seconds to enter PIN
TRIGGERED   → Alarm activated
```

**State Transitions:**
```
DISARMED ---[* key pressed]---> ARMING
ARMING ---[timer expires]---> ARMED
ARMED ---[motion detected]---> ENTRY_DELAY
ENTRY_DELAY ---[timer expires]---> TRIGGERED
ENTRY_DELAY ---[correct PIN + #]---> DISARMED
TRIGGERED ---[correct PIN + #]---> DISARMED
```

**Key Methods:**
- `handleKeyPress(char key)` - Process keypad input
- `handleMotionDetected()` - Process motion sensor events
- `update()` - Called every loop iteration (updates internal timer)

**Callbacks (registered in setup):**
- `onTriggered` - Called when alarm triggers
- `onDisarmed` - Called when system disarms
- `onArming` - Called when entering arming state
- `onEntryDelay` - Called when entering entry delay

**Internal Components:**
- `Timer timer` - Internal timer instance for managing ARMING and ENTRY_DELAY durations

**Configuration:**
- Constructor: `AlarmStateMachine(pin, delayMs)`
  - `pin`: String containing the correct PIN (default: "1234")
  - `delayMs`: Duration for ARMING and ENTRY_DELAY states (default: 10000ms)

---

### 2. KeypadScanner (`KeypadScanner.h/cpp`)

**Purpose:** Non-blocking scanning of 4x3 matrix keypad.

**Keypad Layout:**
```
1 2 3
4 5 6
7 8 9
* 0 #
```

**How It Works:**
- Uses `areConnected()` method to test each row-column pair
- Detects key press only on state change (not continuous)
- Calls callback function once per key press

**Key Methods:**
- `begin()` - Initialize pin modes
- `update()` - Scan keypad (call in loop)
- `onKeyPress(callback)` - Register callback for key events
- `scan()` - Internal: scan matrix and return pressed key

**Callback Signature:**
```cpp
typedef void (*KeyPressCallback)(char key);
```

---

### 3. MotionSensor (`MotionSensor.h/cpp`)

**Purpose:** Wrapper for PIR motion sensor with edge detection.

**How It Works:**
- Monitors PIR sensor pin state
- Detects LOW→HIGH transition (motion start)
- Calls callback only when motion begins (not continuously)

**Key Methods:**
- `begin()` - Initialize sensor pin
- `update()` - Check sensor state (call in loop)
- `onMotionStart(callback)` - Register motion detection callback

**Callback Signature:**
```cpp
typedef void (*MotionStartCallback)();
```

---

### 4. Timer (`Timer.h/cpp`)

**Purpose:** Non-blocking timer utility for delays.

**How It Works:**
- Uses `millis()` for time tracking
- Single timer instance shared across all states
- Calls callback when duration expires

**Key Methods:**
- `start(durationMs)` - Start timer with duration
- `stop()` - Stop/reset timer
- `update()` - Check expiration (call in loop)
- `onExpired(callback)` - Register expiration callback

**Callback Signature:**
```cpp
typedef void (*TimerCallback)();
```

---

### 5. Buzzer (`Buzzer.h/cpp`)

**Purpose:** Buzzer control with pattern playback support.

**Features:**
- Simple on/off control
- Non-blocking pattern playback
- Pattern cycling with configurable on/off durations

**Key Methods:**
- `begin()` - Initialize buzzer pin
- `on()` / `off()` - Direct control
- `blip(duration)` - Short beep (blocking)
- `playPattern(pattern)` - Play pattern (non-blocking)
- `stopPattern()` - Stop pattern
- `update()` - Update pattern state (call in loop)

**Pattern Structure:**
```cpp
struct BuzzerPattern {
  unsigned int onDuration;   // Ms buzzer is on
  unsigned int offDuration;  // Ms buzzer is off
  int cycles;                // Number of cycles (-1 = infinite)
};
```

**Factory Method:**
```cpp
BuzzerPattern pattern = Buzzer::createBeepPattern(onMs, offMs, cycles);
```

---

### 6. DigitMatrix (`DigitMatrix.h/cpp`)

**Purpose:** LED matrix display with digit rendering and pattern animation.

**Features:**
- Pre-defined digit patterns (0-9, *, #)
- Two built-in patterns: blink and countdown
- Non-blocking pattern animation

**Key Methods:**
- `begin()` - Initialize LED matrix
- `setDigit(digit)` - Display digit 0-9
- `setChar(char)` - Display char ('0'-'9', '*', '#')
- `clear()` - Clear display
- `playPattern(pattern)` - Play animation pattern
- `stopPattern()` - Stop animation
- `update()` - Update animation (call in loop)

**Pattern Structure:**
```cpp
struct Pattern {
  byte** frames;        // Array of frame data pointers
  int frameCount;       // Number of frames
  bool loops;           // Whether to loop
  int intervalMs;       // Ms between frames
};
```

**Factory Methods:**
```cpp
Pattern blink = DigitMatrix::createBlinkPattern(intervalMs);
Pattern countdown = DigitMatrix::createCountdownPattern(intervalMs);
```

## Program Flow

### Initialization (`setup()`)

1. Initialize Serial communication (9600 baud)
2. Create display patterns (blink, countdown)
3. Create buzzer pattern (beep)
4. Initialize all hardware components:
   - Buzzer → `buzzer.begin()`
   - LED Matrix → `digitMatrix.begin()`
   - Keypad → `keypad.begin()`
   - Motion Sensor → `motionSensor.begin()`
5. Register callbacks for components:
   - Keypad → `handleKeyPress()`
   - Motion Sensor → `onMotionDetected()`
   - AlarmStateMachine → state callbacks (onTriggered, onDisarmed, onArming, onEntryDelay)
6. Initialize alarm state machine → `alarmSystem.begin()` (sets up internal timer)

### Main Loop (`loop()`)

All components updated every iteration (100ms cycle):
```cpp
motionSensor.update();    // Check motion sensor
keypad.update();          // Scan keypad
alarmSystem.update();     // Update state machine (includes internal timer)
digitMatrix.update();     // Update LED animation
buzzer.update();          // Update buzzer pattern
delay(100);               // Stability delay
```

### Event Flow Examples

**Arming the System:**
1. User presses `*` key
2. `handleKeyPress('*')` called
3. AlarmStateMachine → `handleKeyPress('*')`
4. State changes: DISARMED → ARMING
5. `onArming()` callback triggered
6. Timer started (10 seconds)
7. Buzzer plays beep pattern
8. Display shows countdown
9. After 10 seconds: state → ARMED

**Motion Detection While Armed:**
1. PIR sensor detects motion
2. `onMotionDetected()` callback
3. AlarmStateMachine → `handleMotionDetected()`
4. State changes: ARMED → ENTRY_DELAY
5. `onEntryDelay()` callback triggered
6. Timer started (10 seconds)
7. Buzzer blips once
8. Display shows countdown
9. If no PIN entered: state → TRIGGERED

**Disarming:**
1. User enters PIN (e.g., "1234#")
2. Each digit: `handleKeyPress(digit)`
3. AlarmStateMachine stores digits
4. On `#` key: PIN verification
5. If correct: state → DISARMED
6. `onDisarmed()` callback triggered
7. Buzzer stops
8. Display clears

## Extending the System

### Adding a New Hardware Component

1. Create class with `.h` and `.cpp` files
2. Implement these methods:
   - `Constructor(pin)` - Store pin number
   - `begin()` - Initialize hardware
   - `update()` - Non-blocking update (called in loop)
3. Use callbacks for events (not polling in main sketch)
4. Add instance to `arduino_alarm.ino`
5. Call `begin()` in `setup()`
6. Call `update()` in `loop()`

### Adding a New Alarm State

1. Add state to `AlarmState` enum in `AlarmStateMachine.h`
2. Update `changeState()` in `AlarmStateMachine.cpp`
3. Add state-specific callback type and member
4. Implement transition logic in event handlers
5. Update `printStatus()` for new state
6. Register callback in `setup()`

### Modifying PIN or Delay Duration

In `arduino_alarm.ino`, line 36:
```cpp
AlarmStateMachine alarmSystem("1234", 10000);
//                             ^PIN    ^delay in ms
```

## Design Patterns Used

### 1. State Machine Pattern
- **Where:** AlarmStateMachine
- **Why:** Manages complex state transitions and behaviors
- **Benefit:** Clear, maintainable state logic

### 2. Observer/Callback Pattern
- **Where:** All components
- **Why:** Decouple components, enable event-driven design
- **Benefit:** Loose coupling, extensible architecture

### 3. Non-blocking Pattern
- **Where:** Timer, Buzzer, DigitMatrix updates
- **Why:** Allow concurrent operations without delays
- **Benefit:** Responsive system, no missed events

### 4. Factory Method Pattern
- **Where:** Pattern creation in Buzzer and DigitMatrix
- **Why:** Simplify pattern object creation
- **Benefit:** Clean API, encapsulated complexity

## Common Pitfalls & Solutions

### Pitfall: Blocking Delays
**Problem:** Using `delay()` blocks all other operations.
**Solution:** All timing uses `millis()` and state tracking. Only one 100ms delay in main loop for stability.

### Pitfall: Missing Callbacks
**Problem:** Null pointer dereference if callback not registered.
**Solution:** All components check for `nullptr` and print warning to Serial.

### Pitfall: Keypad Bounce
**Problem:** Single key press registered multiple times.
**Solution:** `KeypadScanner` tracks last key state, only triggers on change.

### Pitfall: Timer Conflicts
**Problem:** Multiple states need timers simultaneously.
**Solution:** AlarmStateMachine owns a single Timer instance, managing it internally for state transitions.

## File Structure

```
arduino_alarm/
├── arduino_alarm.ino          # Main program, hardware setup, callback glue
├── AlarmStateMachine.h/cpp    # State machine logic
├── KeypadScanner.h/cpp        # Keypad matrix scanning
├── MotionSensor.h/cpp         # PIR sensor wrapper
├── Timer.h/cpp                # Non-blocking timer utility
├── Buzzer.h/cpp               # Buzzer with pattern support
├── DigitMatrix.h/cpp          # LED matrix display control
├── README.md                  # Basic project description
├── ARCHITECTURE.md            # This file
└── LICENSE                    # Project license
```

## Dependencies

- **Arduino Core Library** - Standard Arduino functions
- **Arduino_LED_Matrix** - LED matrix control (built-in for UNO R4 WiFi)

## Serial Output

The system provides detailed logging via Serial (9600 baud):
- State transitions
- Key presses
- PIN entry status
- Timer events
- Motion detection
- Pattern playback status
- Warnings for missing callbacks

**Enable monitoring:** Open Serial Monitor in Arduino IDE at 9600 baud.

## Testing Recommendations

### Unit Testing Strategy
1. **Component Isolation:** Test each class independently
2. **Mock Callbacks:** Use test callbacks to verify event firing
3. **State Transitions:** Verify all state machine transitions
4. **Edge Cases:** Test PIN with wrong entries, timer edge cases

### Integration Testing
1. **Full Arm/Disarm Cycle:** Verify complete workflow
2. **Timer Accuracy:** Verify 10-second delays
3. **Pattern Playback:** Verify visual and audio feedback
4. **Concurrent Events:** Test multiple simultaneous inputs

## Performance Characteristics

- **Loop Cycle Time:** ~100ms (includes 100ms stability delay)
- **Keypad Scan Time:** ~5-10ms (depends on matrix size)
- **Pattern Update:** Negligible (<1ms)
- **State Transition:** Instantaneous
- **Memory Usage:** Low (no dynamic allocation during operation)

## Future Enhancement Ideas

1. **Multiple PINs:** Support different users
2. **EEPROM Storage:** Persist PIN across power cycles
3. **Remote Access:** Wi-Fi connectivity for remote control
4. **Sensor Zones:** Multiple motion sensors for different areas
5. **Logging:** Store alarm events with timestamps
6. **Adjustable Delays:** Runtime configuration of timer durations
7. **Silent Arm:** Arm without countdown when leaving
8. **Panic Button:** Instant alarm trigger

---

## Quick Reference for AI Code Agents

### When modifying this codebase:

1. **Never use blocking delays** - Use callbacks and `millis()` based timing
2. **Always register callbacks** - Check existing callback patterns before adding new ones
3. **Follow the non-blocking pattern** - Components update via `update()` method in loop
4. **State changes through AlarmStateMachine** - Don't directly modify state variables
5. **Test with Serial output** - Extensive logging already in place
6. **Maintain separation of concerns** - Each component should be self-contained
7. **Use factory methods for patterns** - Don't manually construct BuzzerPattern/Pattern structs
8. **Check for nullptr** - Always verify callbacks are set before calling

### Component Communication Flow:
```
User Input → Component (KeypadScanner/MotionSensor) 
         → Callback → arduino_alarm.ino callback handler
         → AlarmStateMachine event handler
         → State change
         → State callback → arduino_alarm.ino state handler
         → Output Components (Buzzer/DigitMatrix)
```

### Critical Global Instances (defined in arduino_alarm.ino):
- `digitMatrix` - LED matrix display
- `keypad` - Keypad scanner
- `motionSensor` - PIR sensor
- `buzzer` - Buzzer control
- `alarmSystem` - State machine (contains internal timer)

All instances must be initialized in `setup()` and updated in `loop()`.

