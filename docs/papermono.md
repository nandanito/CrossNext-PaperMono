# M5Stack PaperMono and PaperMono-Lite

Both models use the `papermono` firmware. Lite removes NFC and LoRa; this
firmware uses neither. The port relies on the PaperMono support in the vendored
FreeInk SDK, without adding another display or input driver.

## Hardware

The [M5Stack PaperMono-Lite documentation](https://docs.m5stack.com/en/core/PaperMono-Lite)
and the SDK's `BoardConfig::PAPER_MONO` describe:

- ESP32-S3R8, 16 MB flash and 8 MB octal PSRAM.
- SSD1677 e-paper panel, 480 × 800 in portrait, and FT6336G touch.
- Two user buttons on GPIO2 and GPIO3, mapped to Up and Down.
- M5PM1 power management and single-channel frontlight; M5IOE1 controls
  display, touch and SD power/reset. Brightness is adjustable; warmth is not.
- SDMMC storage and RX8130 RTC.
- BMI270 IMU, backported from FreeInk SDK PR #152. It enables
  **Tilt Page Turn** (off by default). The sensor's 8 KB configuration loads on
  first use, not at boot. Its axis flips come from the SDK profile and have not
  been verified on a device.

The SDK transforms touch coordinates into its landscape framebuffer and handles
panel rotation. The hardware's touch range excludes approximately five pixels
at each portrait edge. The firmware uses the board's existing viewable insets.

## Controls

The PaperMono has no Home, Back or Confirm key, so navigation is by gesture:
Back is a right swipe from the left edge, Home an up swipe from the bottom edge,
and a down swipe from the top edge opens the frontlight panel.

The reading surface claims two of those edges. A left-edge swipe pages back
(`ReaderUtils::handleBackNavigation` ignores the Back gesture there), and the
bottom-edge swipe opens the Contents, Font, Layout and More sheet before the
global Home gesture is checked. The full reader menu, which has Go Home, only
opens with a Confirm key. So on boards without a Home key, **Go Home** is added
to the EPUB sheet's More panel and to the XTC sheet's More tab.

## microSD card

The card must be FAT32 or exFAT on an **MBR** partition table. SdFat reads only
MBR partitions, so a card erased with a GUID (GPT) scheme, which macOS Disk
Utility can pick, fails to mount and boot stops at "SD card error". Copy the
folders from `CrossNext-Resources.zip` to the card root.

## Build and install

`papermono` is the development image and `gh_release_papermono` the release
image. Both have PSRAM, USB mass storage, the SDMMC block-device interface and a
16 KB render-task stack. Only the development image contains the USB input/debug
bridge. Boot does not wait for a serial monitor. The inherited CI workflows only
run in CrossPlay's repository, so build and check locally:

```bash
pio run -e gh_release_papermono
python3 scripts_local/stack_budget.py --build-dir .pio/build/gh_release_papermono
```

The stack check needs the build to have been made with
`PLATFORMIO_BUILD_FLAGS="-fstack-usage -fcallgraph-info=su"`.

A build leaves two images in `.pio/build/<env>/`:

| File | Use |
| --- | --- |
| `firmware.factory.bin` | Full image for a first install over USB at offset `0x0` |
| `firmware.bin` | Application only, at `0x10000`; published as `firmware-papermono.bin` for online updates |

The first install must be a full USB flash: it writes the partition table, whose
two 7.94 MB app slots this image needs. CrossPoint's 6.25 MB slots are too small,
so an update from CrossPoint over SD or Wi-Fi will not fit.

Hold the power button for about two seconds until the red LED flashes to enter
download mode, then release it. Back up the device first:

```bash
~/.platformio/penv/bin/esptool --chip esp32s3 read-flash 0 0x1000000 papermono-backup.bin
pio run -e papermono -t upload
```

Restore with `esptool --chip esp32s3 write-flash 0 papermono-backup.bin` in
download mode. If the device does not restart after flashing, double-click the
power button to turn it off, then press it once to start.

The firmware carries the `papermono` board tag. Both on-device updaters reject
images tagged for X4 Pro or Sticky. PaperMono builds check this repository's
latest GitHub release for `firmware-papermono.bin`. The version comes from
`crossplay.version` in `platformio.ini`, so a release tag must be higher than the
installed version for the updater to offer it.

To bring the frontlight back on after a restart or sleep, enable **Settings →
Display → Restore Light on Wake**. Brightness is retained even when this option
is off; the option controls whether the light turns on. Existing SD settings
are preserved when installing this firmware.

## Hardware verification

Use a FAT32 or exFAT card (MBR) with a book and saved game data. Before flashing,
back up the existing firmware and retain the card's contents.

Checked on a PaperMono so far (2026-10-28): the USB install, the card mount,
opening a book, turning pages and leaving a book through **More → Go Home**.

1. Boot without a serial monitor; check the Home screen, card mount and available PSRAM.
2. Open Games and Apps, launch a game, return with the back gesture, then open a book.
3. Check touch targets and swipes in all four orientations, including near the edges.
4. Check both physical keys and page navigation.
5. Turn the frontlight on, change brightness, turn it off, and check persistence after restart.
6. Sleep from a book and a game, then wake with the power button and check saved progress.
7. Copy a file through USB Drive, eject cleanly, and verify that the reader can open it.
8. Exercise repeated navigation and inspect heap and render-task high-water logs for exhaustion.

A framebuffer screenshot verifies what was rendered, but cannot establish physical
touch alignment, frontlight output, panel ghosting or standby power consumption.
Those checks require observing the device. M5Stack recommends a full refresh after
approximately ten partial refreshes; the port retains the SDK's existing PaperMono
waveforms rather than introducing unverified panel drive settings.
