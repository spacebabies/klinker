# Roadmap & Todo

## Phase 1: The Engine (Current Focus)
- [x] **Implement Circular Buffer:**
    - Add `AudioBuffer<float> delayBuffer` and `int writePosition` to header.
    - Implement the write/read logic in `processBlock`.
    - Hardcode parameters for now (350ms delay, 40% feedback) to test DSP.
    - *Reference:* See cached memory/chat logs for the approved C++ implementation.
- [x] **Fix tail length reporting** (so DAWs don't cut off the delay tail)
- [ ] **Add denormal handling for delay buffer** (prevent CPU spikes in feedback loops)

## Phase 1.5: Polish & Testing (Before Parameters)
- [ ] **Unit Tests:**
    - DSP tests: buffer wrapping, feedback accumulation, clipping check
    - Integration tests: sample rate changes (48k→96k), buffer size changes
    - Regression tests: waveform comparison, frequency response analysis
- [ ] Test plugin at various sample rates (44.1k, 48k, 96k, 192k)
- [ ] Validate denormal handling under sustained feedback

## Phase 2: Parameters
- [ ] Add `AudioProcessorValueTreeState` (APVTS) for parameter management.
- [ ] Connect Delay Time, Feedback, and Mix knobs.

## Phase 3: The GUI
- [ ] Create a basic Editor interface.
- [ ] Visualize the "Klinker" concept.