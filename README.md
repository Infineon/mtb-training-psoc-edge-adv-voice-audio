# PSOC™ Edge Training - Advanced Voice and Audio Development

This training provides practical experience with voice and audio development on PSOC™ Edge,
focusing on PDM microphone configuration, dynamic-range optimization, DEEPCRAFT™ Audio Enhancement,
real-time tuning with the AFE Configurator, and audio analysis with Audacity.
The hands-on labs cover the workflow from low-level audio capture and clipping analysis to
real-time audio enhancement and multi-channel pipeline visualization.

## Device family
- [PSOC™ Edge](https://www.infineon.com/products/microcontroller/32-bit-psoc-arm-cortex/32-bit-psoc-edge-arm)

## How to use this training?
1. Download the training [content](#content).
2. Watch the video or review the presentation at your own pace.
3. Follow the step-by-step instructions in the training manual during the hands-on sections.
4. Use the provided source files and audio test data if needed to verify the lab results.

## Training level
- E3: Advanced

## Prerequisites
### Recommended trainings
- This training does not cover foundational concepts of ModusToolbox™ and PSOC™ Edge.
- For an introduction to PSOC™ MCUs, including getting-started guides for ModusToolbox™, see the [PSOC™ Developer Journey](https://www.infineon.com/PSOCdeveloper).
- For PSOC™ Edge trainings, from beginner tutorials to advanced sessions, visit the [PSOC™ Edge E84 Training Collection](https://infineon-academy.csod.com/ui/lms-learner-playlist/PlaylistDetails?playlistId=8f04565f-88f4-4ca7-83b3-22e501656fbd).

### Tools (see [training manual](#content) for versions and installation instructions)
- [ModusToolbox™ with Eclipse IDE](https://softwaretools.infineon.com/tools/com.ifx.tb.tool.modustoolboxsetup)
- [Edge Protect Security Suite](https://softwaretools.infineon.com/tools/com.ifx.tb.tool.modustoolboxsetup)
- [ModusToolbox™ Programming tools](https://softwaretools.infineon.com/tools/com.ifx.tb.tool.modustoolboxsetup)
- [LLVM for Arm®](https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm/releases/)
- [Audacity](https://www.audacityteam.org/download/)
- [DEEPCRAFT™ Audio Enhancement Tech Pack](https://softwaretools.infineon.com/tools/com.ifx.tb.tool.modustoolboxsetup)
- Terminal emulator

## Hardware
- [KIT_PSE84_EVAL](https://www.infineon.com/evaluation-board/KIT-PSE84-EVAL)
- 2 USB-C cables

## Duration
- 2 hours, including video and hands-on labs

## Agenda
1. Audio input and output methods using PSOC™ Edge MCUs
2. Lab 1: Understanding PDM microphone configuration - 16-bit vs 24-bit
3. DEEPCRAFT™ Audio Enhancement on PSOC™ Edge MCUs
4. Lab 2: Hands-on with DEEPCRAFT™ Audio Enhancement
5. DEEPCRAFT™ Voice Assistant on PSOC™ Edge MCUs

## Expected Outcomes
- Understand the signal chain for audio input and output.
- Understand the impact of microphone DC offset on 16-bit PDM-PCM audio capture.
- Gain hands-on experience configuring 24-bit audio capture and software gain.
- Learn to evaluate and tune the DEEPCRAFT™ Audio Enhancement pipeline in real time.
- Use Audacity and the AFE Configurator to analyze audio and visualize processing channels.

## Content
- Training video at Infineon Academy (coming soon)
- [Presentation](./Presentation/PSE_Advanced_Voice_Audio_Development.pdf)
- [Training manual document](./Manual/pse-advanced-voice-audio-devel-training-manual.md)
  - [Training manual web page](https://infineon.github.io/mtb-training-psoc-edge-adv-voice-audio)
- [Lab solutions](https://github.com/Infineon/mtb-training-psoc-edge-adv-voice-audio/tree/main/Lab_Source)

## References and resources
- [PSOC™ Edge MCUs](https://www.infineon.com/products/microcontroller/32-bit-psoc-arm-cortex/32-bit-psoc-edge-arm)
- [PSOC™ Developer Journey](https://www.infineon.com/PSOCdeveloper)
- [PSOC™ Edge E84 Training Collection](https://infineon-academy.csod.com/ui/lms-learner-playlist/PlaylistDetails?playlistId=8f04565f-88f4-4ca7-83b3-22e501656fbd)
- [DEEPCRAFT™ Audio Enhancement Tech Pack](https://softwaretools.infineon.com/tools/com.ifx.tb.tool.deepcraftaudioenhancementtechpack)
- [Audacity](https://www.audacityteam.org/download/)

## History

| Date | Version | Description |
| ---- | ------- | ----------- |
| 08/24/2026 | ** | First public release |