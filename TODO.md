# Roadmap & Todo

## Phase 1: The Engine (Current Focus)
- [ ] **Implement Circular Buffer:**
    - Add `AudioBuffer<float> delayBuffer` and `int writePosition` to header.
    - Implement the write/read logic in `processBlock`.
    - Hardcode parameters for now (350ms delay, 40% feedback) to test DSP.
    - *Reference:* See cached memory/chat logs for the approved C++ implementation.

## Phase 2: Parameters
- [ ] Add `AudioProcessorValueTreeState` (APVTS) for parameter management.
- [ ] Connect Delay Time, Feedback, and Mix knobs.

## Phase 3: The GUI
- [ ] Create a basic Editor interface.
- [ ] Visualize the "Klinker" concept.