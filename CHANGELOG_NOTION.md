# ERI Robotics QGroundControl 5.0

## Custom Android Release History

> This document describes the archived ERI Robotics Android builds based on QGroundControl 5.0.0.

The `customN` suffix identifies an APK build iteration. The application version remains **QGroundControl 5.0.0**. The embedded Git revision identifies the committed source used to build each APK.

APKs that embed the same revision use the same committed source, but they can still differ because of build configuration, signing, packaging, or local build state. They are not necessarily byte-for-byte identical.

---

## Version Overview

### v5.0.0-1.0.0

- **Release type:** Historical published release
- **Release date:** 2026-08-31
- **Git tag revision:** `ed7500e09`
- **Published APK revision:** `be0e48e27`
- **Source-equivalent custom version:** `v5.0.0-custom7`
- **Important:** The published APK was not built from the revision referenced by its Git tag.
- **Impact:** Functions added after `custom7` are not present in the current `v5.0.0-1.0.0` APK.
- **GitHub release:** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-1.0.0

### v5.0.0-custom11

- **Release date:** 2026-06-02
- **Embedded revision:** `f50f27c87`
- **Relationship:** Latest archived custom APK source
- **GitHub release:** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom11

### v5.0.0-custom10

- **Embedded revision:** `c322549be`
- **Relationship:** Same committed source as `custom8` and `custom9`
- **GitHub release:** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom10

### v5.0.0-custom9

- **Embedded revision:** `c322549be`
- **Relationship:** Same committed source as `custom8` and `custom10`
- **GitHub release:** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom9

### v5.0.0-custom8

- **Release date:** 2026-05-11
- **Embedded revision:** `c322549be`
- **Relationship:** Newer committed source than `custom7`
- **GitHub release:** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom8

### v5.0.0-custom7

- **Release date:** 2026-04-01
- **Embedded revision:** `be0e48e27`
- **Relationship:** Same committed source revision as the published `v5.0.0-1.0.0` APK
- **GitHub release:** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom7

### v5.0.0-custom6

- **Embedded revision:** `e12b1afe3`
- **Relationship:** Same committed source as `custom4` and `custom5`
- **GitHub release:** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom6

### v5.0.0-custom5

- **Embedded revision:** `e12b1afe3`
- **Relationship:** Same committed source as `custom4` and `custom6`
- **GitHub release:** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom5

### v5.0.0-custom4

- **Release date:** 2026-03-19
- **Embedded revision:** `e12b1afe3`
- **Relationship:** Newer committed source than `custom2`
- **GitHub release:** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom4

### v5.0.0-custom3

- **Status:** Not available
- **APK:** Not supplied
- **Source revision:** Unknown
- **GitHub release:** Not created

### v5.0.0-custom2

- **Embedded revision:** `ef4ff6dca`
- **Relationship:** Same committed source as `custom1`
- **GitHub release:** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom2

### v5.0.0-custom1

- **Release date:** 2026-03-11
- **Embedded revision:** `ef4ff6dca`
- **Relationship:** First archived revision in this series
- **GitHub release:** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom1

---

## Functional Changelog

### v5.0.0-custom11

Changes since the source used by `custom10`:

#### Settings and PiP

- Replaced separate PiP controls with a unified **Settings** panel.
- Added RTSP/PiP URL configuration.
- Added a **Clear PiP** action.
- Added display of the active communication endpoint.
- Removed the separate URL editor from the PiP window.

#### VOXL Safe Shutdown

- Added a confirmation dialog before shutdown.
- Added custom MAVLink message `CUSMVL_SAFE_SHUTDOWN` (`42010`).
- Added request identification and duplicate-request protection fields.
- Added pending, success, error, and timeout status feedback.
- Added a 15-second confirmation timeout.
- Detects primary-link loss after the request as shutdown confirmation.

#### Video Recovery

- Added retry backoff between 10 and 30 seconds.
- Improved main and PiP stream restart handling.
- Reduced repeated immediate restart attempts after stream failure.

#### Flight HUD

- Added ToF ON/OFF state display.
- Added BRK ON/OFF indication based on the `CP_DIST` parameter.

#### Networking

- Added active UDP peer IP address and port tracking.
- Added TCP and configured UDP endpoint fallback.
- Displays the active endpoint in the Settings panel.

---

### v5.0.0-custom8 to v5.0.0-custom10

All three APKs embed revision `c322549be`. There are no committed source changes between `custom8`, `custom9`, and `custom10`.

#### Controller

- Added G4 controller dial calibration handling.

#### Flight HUD

- Adjusted the HUD compass layout.
- Changed the relative-position display to S/D/H format.
- Changed Wi-Fi strength to percentage display.

#### Status Messages

- Added a dedicated `STATUSTEXT` error overlay.

#### UI

- Applied additional layout and presentation adjustments.

#### Build Tooling

- Added Windows custom-build workflows.
- Added NSIS installer generation.
- Added Linux diagnostic workflows.
- Fixed custom workflow overwrite and Qt StateMachine issues.
- Changed GitHub Actions to manual execution.

---

### v5.0.0-custom7

#### Controller

- Added normalized G4 auxiliary-axis handling.
- Added auxiliary-axis debugging information.

#### Flight HUD

- Added CPU temperature display.
- Reorganized debug information.

#### Recording UI

- Adjusted level and recording UI layout.
- Added support for additional `REC_STAT` states.

---

### v5.0.0-custom4 to v5.0.0-custom6

All three APKs embed revision `e12b1afe3`. There are no committed source changes between `custom4`, `custom5`, and `custom6`.

#### Video UI

- Moved the level indicator to the lower-left area.
- Resized and repositioned the PiP window.
- Adjusted the recording and camera-control layout.
- Added a crosshair to the main video.

#### Controller and MAVLink

- Added RC auxiliary-axis transmission.
- Added recording-state transmission and display.
- Tested raw and ±1000 auxiliary values before settling on normalized `MANUAL_CONTROL` values.

#### Recording Status

- Added recording-state display.
- Refined `REC_STAT` wording and state colors.

#### Communications

- Fixed communication-link deletion behavior.

---

### v5.0.0-custom1 to v5.0.0-custom2

Both APKs embed revision `ef4ff6dca`. There are no committed source changes between `custom1` and `custom2`.

#### Android UI and Telemetry

- Added the initial custom Android UI.
- Fixed TIMESYNC transmission.

#### Battery Telemetry

- Ignored invalid extended `BATTERY_STATUS` voltage values.

#### Android Signing

- Added support for loading local Android signing configuration.

---

## QGroundControl 5.0 Base Changes

- Added a combined compass and attitude instrument.
- Added desktop click and mobile long-press instrument selection.
- Renamed Fly View and Joystick **Custom Actions** to **MAVLink Actions**.
- Added support for setting individual MAVLink message rates in the Inspector.
- Enabled MAVLink 2 signing.
- Added dynamic battery bars with configurable thresholds.

---

## Recommended Release Correction

If `v5.0.0-1.0.0` is intended to be the final release after `custom11`:

1. Select the intended final source revision.
2. Ensure the Git tag points to that revision.
3. Rebuild the Android APK from a clean checkout of that tag.
4. Verify the APK's embedded revision before publishing.
5. Replace the current release asset with the verified APK.

