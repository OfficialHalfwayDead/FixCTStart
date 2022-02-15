#include "pch.h"
#include "FixCTStart.h"


BAKKESMOD_PLUGIN(FixCTStart, "write a plugin description here", plugin_version, PLUGINTYPE_FREEPLAY)

float steer;

void FixCTStart::onLoad()
{
	// set steer on countdown tick to 0 and then set it back after
	gameWrapper->HookEvent("Function GameEvent_TrainingEditor_TA.Countdown.Tick", [this](std::string eventName) {
		auto pc = gameWrapper->GetPlayerController();
		if (!pc) return;
		auto input = pc.GetVehicleInput();
		steer = input.Steer;
		input.Steer = 0.f;
		pc.SetVehicleInput(input);
	});
	gameWrapper->HookEventPost("Function GameEvent_TrainingEditor_TA.Countdown.Tick", [this](std::string eventName) {
		auto pc = gameWrapper->GetPlayerController();
		if (!pc) return;
		auto input = pc.GetVehicleInput();
		input.Steer = steer;
		pc.SetVehicleInput(input);
		});
}

void FixCTStart::onUnload()
{
}