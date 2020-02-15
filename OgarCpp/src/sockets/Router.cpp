#include "Router.h"
#include "../ServerHandle.h"

Router::Router(Listener* listener) : listener(listener), ejectTick(listener->handle->tick) {
	this->listener->addRouter(this);
};

void Router::createPlayer() {
	if (hasPlayer) return;
	hasPlayer = true;
	player = listener->handle->createPlayer(this);
};

void Router::destroyPlayer() {
	if (!hasPlayer) return;
	hasPlayer = false;
	listener->handle->removePlayer(player->id);
	player = nullptr;
};

void Router::onSpawnRequest() {
	int playerMaxNameLength = listener->handle->getSettingInt("playerMaxNameLength");
	std::string name = spawningName.substr(0, playerMaxNameLength);
	std::string skin = "";
	if (listener->handle->getSettingBool("playerAllowSkinInName")) {
		std::smatch sm;
		std::regex_match(name, sm, nameSkinRegex);
		if (sm.size() == 3) {
			skin = sm[1];
			name = sm[2];
		}
	}
	listener->handle->gamemode->onPlayerSpawnRequest(player, name, skin);
};

void Router::onSpectateRequest() {
	if (!hasPlayer) return;
	player->updateState(SPEC);
}

void Router::onQPress() {
	if (!hasPlayer) return;
	listener->handle->gamemode->onPlayerPressQ(player);
};

void Router::attemptSplit() {
	if (!hasPlayer) return;
	listener->handle->gamemode->onPlayerSplit(player);
}

void Router::attemptEject() {
	if (!hasPlayer) return;
	listener->handle->gamemode->onPlayerEject(player);
}

void Router::close() {
	listener->removeRouter(this);
}