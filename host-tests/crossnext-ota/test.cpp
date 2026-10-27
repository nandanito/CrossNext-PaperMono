#include <ReleaseJsonParser.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>

#include "../../src/network/FirmwareBoardTag.h"
#include "../../src/network/ReleaseSources.h"

namespace {
// Compiled once per board by run.sh: PaperMono checks this fork's releases,
// every other board keeps CrossNext's.
#if FREEINK_DEVICE_PAPERMONO
constexpr const char* kBoard = "papermono";
constexpr const char* kSource = "https://api.github.com/repos/nandanito/CrossNext-PaperMono/releases/latest";
constexpr const char* kAlias = "firmware-papermono.bin";
constexpr const char* kAliasUrl =
    "https://github.com/nandanito/CrossNext-PaperMono/releases/download/v1.0.1/firmware-papermono.bin";
constexpr const char* kOtherBoardAlias = "CrossNext-X4PRO-OTA.bin";
#else
constexpr const char* kBoard = "x4pro";
constexpr const char* kSource = "https://api.github.com/repos/manuelx900/CrossNext/releases/latest";
constexpr const char* kAlias = "CrossNext-X4PRO-OTA.bin";
constexpr const char* kAliasUrl =
    "https://github.com/manuelx900/CrossNext/releases/download/v1.0.1/CrossNext-X4PRO-OTA.bin";
constexpr const char* kOtherBoardAlias = "firmware-papermono.bin";
#endif

int checks = 0, failed = 0;
void check(bool ok, const char* message) {
  ++checks;
  if (!ok) {
    ++failed;
    std::fprintf(stderr, "FAIL: %s\n", message);
  }
}
std::string asset(const char* name, const char* url, int size) {
  return "{\"size\":" + std::to_string(size) + ",\"browser_download_url\":\"" + url + "\",\"name\":\"" + name + "\"}";
}
void parse(const std::string& assets, bool expected) {
  for (size_t chunk : {size_t(1), size_t(2), size_t(7), size_t(512)}) {
    // Assets before tag_name also has to work with a streaming response.
    const std::string json = "{\"assets\":[" + assets + "],\"tag_name\":\"v1.0.1\"}";
    ReleaseJsonParser parser;
    parser.setFirmwareAssetName(CROSSPOINT_RELEASE_ASSET);
    for (size_t at = 0; at < json.size(); at += chunk) parser.feed(json.data() + at, std::min(chunk, json.size() - at));
    check(parser.foundTag(), "release tag parsed");
    check(std::strcmp(parser.getTagName(), "v1.0.1") == 0, "release tag retained");
    check(parser.foundFirmware() == expected, "only exact CrossNext OTA alias matches");
    if (expected) {
      check(std::strcmp(parser.getFirmwareUrl(), kAliasUrl) == 0, "selected URL belongs to the application alias");
      check(parser.getFirmwareSize() == 7500000, "size belongs to selected asset");
    }
  }
}
}  // namespace

int main() {
  check(release_sources::kCount == 1, "one authoritative source");
  check(std::strcmp(release_sources::kUrls[0], kSource) == 0, "release source for this board");
  check(std::strcmp(CROSSPOINT_RELEASE_ASSET, kAlias) == 0, "stable application alias for this board");
  const std::string application = asset(CROSSPOINT_RELEASE_ASSET, kAliasUrl, 7500000);
  const std::string others =
      asset("firmware.bin", "https://example.invalid/upstream.bin", 1) + "," +
      asset("CrossNext-X4PRO-Firmware-v1.0.1-factory.bin", "https://example.invalid/factory.bin", 2) + "," +
      asset("CrossNext-X4PRO-Firmware-v1.0.1.zip", "https://example.invalid/firmware.zip", 3) + "," +
      asset("CrossNext-STICKY-OTA.bin", "https://example.invalid/other-board.bin", 4) + "," +
      asset(kOtherBoardAlias, "https://example.invalid/other-board-alias.bin", 5);
  parse(application + "," + others, true);
  parse(others + "," + application, true);
  parse(others, false);
  parse("", false);
  std::printf("crossnext-ota (%s): %d checks, %d failed\n", kBoard, checks, failed);
  return failed ? 1 : 0;
}
