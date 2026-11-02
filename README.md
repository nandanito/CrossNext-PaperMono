<h1 align="center">
  <img src="site/assets/logo.svg#gh-light-mode-only" width="72" alt="CrossNext"><img src="site/assets/logo-dark.svg#gh-dark-mode-only" width="72" alt="CrossNext"><br>
  CrossNext for PaperMono
</h1>

[Español](README.es.md) · [PaperMono notes](docs/papermono.md) · [Installation](docs/install.md) · [Changes and upstream credits](docs/crossnext-changes.md)

Reading, study tools and games for the **M5Stack PaperMono** and PaperMono-Lite.
Read a book, save new vocabulary, review flashcards, track your reading and take
a break with a game, all on the same e-ink device.

This is a port of [CrossNext](https://github.com/manuelx900/CrossNext), which is
based on [CrossPlay 1.14.2](https://github.com/ma-r-s/crossplay) and
[CrossPoint 1.6.5](https://github.com/crosspoint-reader/crosspoint-reader), with
the FreeInk SDK. The reader, apps and games come from those projects; this fork
adds what the PaperMono needs. Additional references include
[CrossInk](https://github.com/uxjulia/CrossInk),
[CrossDiTo](https://github.com/dito94/CrossDiTo) and
[VCodex](https://github.com/franssjz/cpr-vcodex); see the [credits](docs/crossnext-changes.md).
For the Xteink X4 Pro, install [upstream CrossNext](https://github.com/manuelx900/CrossNext).

> [!NOTE]
> **Early port.** Installing over USB, the microSD card, reading, turning pages
> and leaving a book have been tested on a PaperMono. The rest of the hardware is
> still being checked; see the [hardware checklist](docs/papermono.md#hardware-verification).

![CrossNext screens](docs/images/overview.png)

## On the PaperMono

Both models use the same firmware. The Lite has no NFC or LoRa.

| Hardware | In this firmware |
| --- | --- |
| Screen (480 × 800) and touch | Supported |
| Two side buttons | Turn pages; hold to change chapter |
| Power button | Click to sleep and wake |
| Frontlight | Brightness from the top-edge swipe; warmth is not adjustable |
| microSD | FAT32 or exFAT, with an MBR partition table |
| USB drive | Supported, not yet tested on a PaperMono |
| Clock (RX8130) | Supported |
| Gyroscope (BMI270) | **Tilt Page Turn**, off by default; not yet tested |
| Microphone, buzzer, RGB LED | SDK drivers only; no app uses them yet |
| LoRa, NFC | Not supported |

### Touch controls

The PaperMono has no Home or Back key, so these are gestures:

| Action | Gesture |
| --- | --- |
| Back | Swipe right from the left edge |
| Home | Swipe up from the bottom edge |
| Leave a book | Swipe up from the bottom edge, then **More → Go Home** |
| Frontlight | Swipe down from the top edge |
| Turn pages | Tap or swipe the page, or use the side buttons |

Inside a book, the left-edge swipe turns back a page and the bottom-edge swipe
opens the reader's Contents, Font, Layout and More sheet. That is why leaving a
book goes through **More**.

## Install it

No release has been published yet, so build and flash from source. The first
install has to be over USB: it also writes the partition table, which this
firmware needs. An SD-card or online update from CrossPoint will not fit.

1. Install [PlatformIO](https://platformio.org/install/cli), clone this repository
   and build it once with `pio run -e papermono`. The first build also installs
   the flashing tools.
2. Connect the PaperMono over USB-C, then hold the power button for about two
   seconds until the red LED flashes. This is download mode.
3. Back up the current firmware. Keep the file somewhere safe:
   ```bash
   ~/.platformio/penv/bin/esptool --chip esp32s3 read-flash 0 0x1000000 papermono-backup.bin
   ```
4. Flash from the repository folder:
   ```bash
   pio run -e papermono -t upload
   ```
   This writes the bootloader and partition table as well as the app. If it does
   not restart, double-click the power button to turn it off, then press it once.

To go back to the previous firmware, write the backup in download mode:
`~/.platformio/penv/bin/esptool --chip esp32s3 write-flash 0 papermono-backup.bin`.

Once releases are published, **Settings → Device → Check for Updates** installs
new versions from this fork's [GitHub Releases](https://github.com/nandanito/CrossNext-PaperMono/releases),
using each release's `firmware-papermono.bin`. See [online updates](docs/install.md#online-update-source).

## Set up the microSD card

1. Format the card as **FAT32** (or exFAT) with a **Master Boot Record**
   partition table. On a Mac, use Disk Utility with **View → Show All Devices**,
   select the card itself and choose MS-DOS (FAT) and Master Boot Record. A card
   with a GUID partition table shows "SD card error" at boot.
2. Download `CrossNext-Resources.zip` from the
   [CrossNext releases](https://github.com/manuelx900/CrossNext/releases), unzip
   it and copy its **folders** to the root of the card. It holds the reader fonts,
   dictionaries and the content that Reading Quest, PET and The Intercept need.
3. Put your books in a folder such as `/Books`. The Library finds EPUB, TXT,
   Markdown and XTC/XTCH files up to five folders deep, but skips the resource
   folders (`apps`, `fonts`, `dictionaries`, `licenses`, `flashcards`, `sleep`,
   `wallpaper`, `wallpapers`) and anything whose name starts with a dot.

You can also add books over Wi-Fi: open **File Transfer**, join a network and
open the address it shows in a browser. Calibre can send books the same way;
see the [user guide](USER_GUIDE.md#351-calibre-wireless-transfers).

## PET: your reading companion

PET turns your reading routine into a story with a virtual companion. Choose an
egg, name your pet and watch it grow as you read.

- **Reading statistics:** follow your reading time, reading days and streaks.
- **Difficulty and goals:** adjust the care difficulty and daily reading goal
  to suit your routine.
- **Daily care:** feed, clean and care for your pet, keeping an eye on its
  needs and health.
- **Games and affection:** pet your companion and play minigames to lift its mood.
- **A home of its own:** unlock furnishings through reading and arrange its
  room to your liking.
- **Memories and generations:** discover memories as you progress, follow your
  pet's life stages and revisit previous generations.

![PET: status, care, home and memories](docs/images/pet.png)

PET needs `CrossNext-Resources.zip` on the microSD.
See [PET's guide](docs/apps/pet.md) and
[what's new in v1.2.0](docs/releases/CrossNext-v1.2.0.md).

## Read, study and play

- EPUB, text, Markdown and XTC/XTCH reading, a file browser and a cover library.
- Reading history, statistics, calendars and Reading Quest.
- Flashcards imported from files/Anki, local FSRS review and a saved vocabulary app.
- Independent title/question and content sizes: 10, 12, 14, 16 and 18 pt.
  Smart sizing is enabled by default; long text keeps complete pagination.
- Horizontal paging in supported app/puzzle selectors and study cards.
- Anki image zoom uses a separate high-resolution copy only while enlarged;
  normal cards keep the small preview. Rotation toggles between two positions.
- Pomodoro's physical button starts and pauses; XTC/XTCH can reverse swipes
  and page-tap zones for manga reading.

The active shelf contains these **16 games**:
Chess (including puzzles), Checkers, Go, Minesweeper, Picross, Wordle, 2048,
The Intercept, Battleship, Solitaire, Hearts, Murdle, Carnivore, Connect Four,
Sudoku and Othello.

Its **13 app entries** are Reading Quest, PET, Habits, To Do List, Notes, Pomodoro,
Wallpapers, Quotes, Flashcards, Words, Calendar, Clock and Counter.

Fresh settings start in **English**. Spanish is available in the language
settings; an existing installation keeps its saved language.

## In pictures

These screenshots come from CrossNext on the Xteink X4 Pro, which has the same
480 × 800 screen; the PaperMono shows the same screens.

### Two Home layouts

![Two Home layouts](docs/images/appearances.png)

### Reading statistics

![Reading statistics](docs/images/statistics.png)

Optional **CrossPoint Sync** keeps your account history and new local reading in one statistics view. Read offline, then use the sync shortcut beside the battery to synchronize statistics and book positions together. Each book on the microSD keeps the furthest position from the reader or your account. The shortcut appears only after configuring a compatible sync account. See [reading statistics](docs/reading-stats.md#crosspoint-sync).

### Games

![Games](docs/images/games.png)

### Apps and productivity

![Apps and productivity](docs/images/apps.png)

### Flashcards and saved words

![Flashcards and saved words](docs/images/study.png)

### Reading controls

![Reading controls](docs/images/reading.png)

### Everyday tools

![Everyday tools](docs/images/tools.png)

## Try the local simulator

Follow [Windows setup](docs/simulator-windows.md#setup-from-a-source-export), then
run `Start-Simulator.cmd`. The local browser opens `http://127.0.0.1:8765/` and
runs the firmware from these sources. There is no PaperMono simulator; it
simulates the X4 Pro, which runs the same screens. The showcase supplies books
with original notices, synthetic statistics, files and saved app/game examples
for screenshots. It uses separate demonstration data rather than the reader's
personal records.

See [the showcase guide](docs/simulator-showcase.md). Browser-specific network
and sleep adaptations are described in [the site documentation](site/README.md).
The original [CrossPlay demo](https://crossplay.ma-r-s.com) is maintained upstream.

## Develop and verify

Use `papermono` for the device, `gh_release_papermono` for a release image and
`simulator_x4_pro` for the simulator. The upstream `default` environment targets
a different chip. In a configured development checkout, run
`./scripts_local/check.sh` from your own worktree.
Use the repository's `./bin/clang-format-fix -g` wrapper for changed C/C++ files.
Read the [contributor guide](docs/contributing/getting-started.md) and
[local script documentation](scripts_local/README.md) before changing firmware.
Inherited CrossPlay automation is restricted to its original repository; releases
are published manually.

Useful feature details: [Flashcards](docs/apps/flashcards-ui.md),
[Words](docs/apps/words.md), [Pomodoro](docs/pomodoro.md),
[Library performance](docs/library-performance.md) and
[the render audit](docs/render-performance.md).
Builds, native tests and simulator checks do not replace physical-device testing
of display refresh, SD behavior, memory and all orientations before publication.

## Licence and attribution

Keep [LICENSE](LICENSE), original copyright notices and bundled asset licences.
CrossPlay supplies the app/game shelf and implementations; CrossPoint supplies
the e-reader foundation. [CrossNext changes](docs/crossnext-changes.md) describes
CrossNext's adaptations without claiming those inherited projects as new work.

[What’s new in v1.2.0](docs/releases/CrossNext-v1.2.0.md)

## Support CrossNext

CrossNext is developed by [manuelx900](https://github.com/manuelx900). If you would
like to support its ongoing development, please consider supporting its author on Ko-fi.

[![Support me on Ko-fi](site/assets/support-ko-fi.svg)](https://ko-fi.com/manuelx900)
