#pragma once
#include <string>

class Core;
namespace ctrl { class Keyboard; }

inline const std::string KeyUp = "Up";
inline const std::string KeyDown = "Down";
inline const std::string KeyLeft = "Left";
inline const std::string KeyRight = "Right";
inline const std::string KeyOK = "OK";
inline const std::string KeyKaboom = "Kaboom";
inline const std::string KeyPaused = "¨Pause";

void preinit(Core& _core);
void registerControls(Core& _core);