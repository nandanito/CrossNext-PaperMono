#pragma once

namespace release_sources {
// PaperMono releases are published by this fork; every other board keeps
// CrossNext's. OtaUpdater stops at the first source that answers with a tag,
// so a second entry here would never act as a fallback for a missing asset.
constexpr const char* const kUrls[] = {
#if FREEINK_DEVICE_PAPERMONO
    "https://api.github.com/repos/nandanito/CrossNext-PaperMono/releases/latest",
#else
    "https://api.github.com/repos/manuelx900/CrossNext/releases/latest",
#endif
};
constexpr int kCount = static_cast<int>(sizeof(kUrls) / sizeof(kUrls[0]));
}  // namespace release_sources
