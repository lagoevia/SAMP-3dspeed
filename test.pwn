#include <a_samp>
#include <YSI_Visual\y_commands>
#include <sscanf2>

// Can place definitions for speed include here (i.e language, mph, etc.)
#include "3dspeed.inc"

static
    bool:_g_s_fuel = false,
    bool:_g_s_speed = false,
    bool:_g_s_showHealth = false,
    bool:_g_s_showName = false;

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
            speed = _g_s_speed ? random(140) : TDSPEED_INVALID_ITEM,
            fuel = _g_s_fuel ? random(101) : TDSPEED_INVALID_ITEM,
            bool:showHealth = _g_s_showHealth,
            bool:showName = _g_s_showName
        ;

        Update3DSpeedometer(playerid, showName, showHealth, speed, fuel);
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

YCMD:toggle(playerid, params[], help)
{
    new itemid;
    if(sscanf(params, "d", itemid)) return SendClientMessage(playerid, -1, "Usage: /toggle <item>, where item = (0) fuel, (1) health, (2) speed, or (3) name");
    new msg[64];
    switch(itemid)
    {
        case TDSPEED_ITEM_FUEL:
        {
            _g_s_fuel = !_g_s_fuel;
            format(msg, _, "Fuel toggled to state: %s", _g_s_fuel ? "ON" : "OFF");
        }
        case TDSPEED_ITEM_HEALTH:
        {
            _g_s_showHealth = !_g_s_showHealth;
            format(msg, _, "Health toggled to state: %s", _g_s_showHealth ? "ON" : "OFF");
        }
        case TDSPEED_ITEM_SPEED:
        {
            _g_s_speed = !_g_s_speed;
            format(msg, _, "Speed toggled to state: %s", _g_s_speed ? "ON" : "OFF");
        }
        case TDSPEED_ITEM_NAME:
        {
            _g_s_showName = !_g_s_showName;
            format(msg, _, "HideName toggled to state: %s", _g_s_showName ? "ON" : "OFF");
        }
        default:
        {
            format(msg, _, "Unknown item id: %d", itemid);
        }
    }

    SendClientMessage(playerid, -1, msg);
    return 1;
}