#pragma once
#include <string>

class Core;
namespace ctrl { class Keyboard; }

extern const std::string KeyOpenMenu;
extern const std::string KeyOpenGame;

void preinit(Core& _core);
void registerControls(Core& _core);