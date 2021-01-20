#include <a_samp>
#include <YSI_Visual\y_commands>
#include <sscanf2>

// Can place definitions for speed include here (i.e language, mph, etc.)
#include "3dspeed.inc"

static bool:_g_s_toggleFuel = false;

main()
{
    print("Simple local test environment for SAMP-3dspeed");
    print("Repo home is at: https://github.com/markski1/SAMP-3dspeed/");
}

public OnGameModeInit()
{
    AddPlayerClass(1, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0); // Give some class to spawn as
    return 1;
}

public OnPlayerUpdate(playerid)
{
    // NOTE: only used here for testing - you may want to use it somewhere else
    new vid = GetPlayerVehicleID(playerid);
    if(vid != INVALID_VEHICLE_ID)
    {
        // Include itself is not responsible for calculating speed/fuel, so just generate random int values in a range and pass those
        new
            speed = random(140),
            fuel = _g_s_toggleFuel ? random(101) : -1; // [0, 100] or -1 if toggled off

        Update3DSpeedometer(playerid, speed, fuel);
    }
}

YCMD:v(playerid, params[], help)
{
    new Float:pos[3], Float:angle;
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    GetPlayerFacingAngle(playerid, angle);
    new modelid;
    if(sscanf(params, "d", modelid)) return SendClientMessage(playerid, -1, "Usage: /v <modelid>");
    new vid = CreateVehicle(modelid, pos[0], pos[1], pos[2], angle, random(10), random(10), 0, 0);
    PutPlayerInVehicle(playerid, vid, 0);
    return 1;
}

YCMD:tf(playerid, params[], help)
{
    _g_s_toggleFuel = !_g_s_toggleFuel;
    new msg[64];
    format(msg, _, "Fuel toggled to state: %s", _g_s_toggleFuel ? "ON" : "OFF");
    SendClientMessage(playerid, -1, msg);
    return 1;
}