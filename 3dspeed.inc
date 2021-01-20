/*
	3dspeed 1.0.1
	mrks.cf | github.com/markski1
	Thanks to:
		open.mp/docs contributors
		SACNR
*/

#if defined tdspeed_included
	#endinput
#endif

#define tdspeed_included

#if !defined _streamer_included
	#tryinclude <streamer>
	#tryinclude "streamer"
#endif

#if !defined _streamer_included
	#error "Could not include the streamer. Get it here: https://github.com/samp-incognito/samp-streamer-plugin"
#endif

/*
	Configuration constants, include before this file.

	TDSPEED_MPH to say MPH instead of KMH
	TDSPEED_SPANISH to have spanish text.
	TDSPEED_HIDENAME to not show vehicle name.
*/

// TODO: change some of these names to avoid global scope conflict; prefix these and static globals accordingly
// TODO: add ability to specify custom offsets for each player
// TODO: change prefixing of macros to 'TDS' to shorten length? Probably not
// TODO: hidename macro was there to avoid drawing an object if they are not meant to be drawn - however, this was very forcing to all players and not versatile; explain in PR
// TODO: fix hooks not returning 1 if custom name not defined. Also, why not ALS? Point is to communicate that to other libraries, or am I confusing something?

#define TDSPEED_INVALID_ITEM -1

enum {
	TDSPEED_LANG_ENGLISH = 0,
	TDSPEED_LANG_SPANISH,

	TDSPEED_LANG_MAX
};

#if defined TDSPEED_SPANISH
	static _g_s_activeLanguage = TDSPEED_LANG_SPANISH;
#else
	static _g_s_activeLanguage = TDSPEED_LANG_ENGLISH;
#endif

enum {
    TDSPEED_ITEM_FUEL= 0,
    TDSPEED_ITEM_HEALTH,
    TDSPEED_ITEM_SPEED,
    TDSPEED_ITEM_NAME,

    TDSPEED_ITEM_MAX
};

static _g_s_languageStrings[TDSPEED_LANG_MAX][2][16] = {
	{"Fuel", "Health"},
	{"Combustible", "Vida"}
};

enum SpeedometerComponents {
	Name,
	Status,
	Speed,
	Enabled
}

static tds_Player[MAX_PLAYERS][SpeedometerComponents];

/* Vehicle names array */

static gVehicleNames[][] = {
	"Landstalker",
	"Bravura",
	"Buffalo",
	"Linerunner",
	"Perenniel",
	"Sentinel",
	"Dumper",
	"Firetruck",
	"Trashmaster",
	"Stretch",
	"Manana",
	"Infernus",
	"Voodoo",
	"Pony",
	"Mule",
	"Cheetah",
	"Ambulance",
	"Leviathan",
	"Moonbeam",
	"Esperanto",
	"Taxi",
	"Washington",
	"Bobcat",
	"Mr Whoopee",
	"BF Injection",
	"Hunter",
	"Premier",
	"Enforcer",
	"Securicar",
	"Banshee",
	"Predator",
	"Bus",
	"Rhino",
	"Barracks",
	"Hotknife",
	"Trailer",
	"Previon",
	"Coach",
	"Cabbie",
	"Stallion",
	"Rumpo",
	"RC Bandit",
	"Romero",
	"Packer",
	"Monster Truck",
	"Admiral",
	"Squalo",
	"Seasparrow",
	"Pizzaboy",
	"Tram",
	"Trailer",
	"Turismo",
	"Speeder",
	"Reefer",
	"Tropic",
	"Flatbed",
	"Yankee",
	"Caddy",
	"Solair",
	"Berkley's RC Van",
	"Skimmer",
	"PCJ-600",
	"Faggio",
	"Freeway",
	"RC Baron",
	"RC Raider",
	"Glendale",
	"Oceanic",
	"Sanchez",
	"Sparrow",
	"Patriot",
	"Quad",
	"Coastguard",
	"Dinghy",
	"Hermes",
	"Sabre",
	"Rustler",
	"ZR-350",
	"Walton",
	"Regina",
	"Comet",
	"BMX",
	"Burrito",
	"Camper",
	"Marquis",
	"Baggage",
	"Dozer",
	"Maverick",
	"News Chopper",
	"Rancher",
	"FBI Rancher",
	"Virgo",
	"Greenwood",
	"Jetmax",
	"Hotring",
	"Sandking",
	"Blista Compact",
	"Police Maverick",
	"Boxville",
	"Benson",
	"Mesa",
	"RC Goblin",
	"Hotring Racer",
	"Hotring Racer",
	"Bloodring Banger",
	"Rancher",
	"Super GT",
	"Elegant",
	"Journey",
	"Bike",
	"Mountain Bike",
	"Beagle",
	"Cropdust",
	"Stunt Plane",
	"Tanker",
	"RoadTrain",
	"Nebula",
	"Majestic",
	"Buccaneer",
	"Shamal",
	"Hydra",
	"FCR-900",
	"NRG-500",
	"HPV1000",
	"Cement Truck",
	"Tow Truck",
	"Fortune",
	"Cadrona",
	"FBI Truck",
	"Willard",
	"Forklift",
	"Tractor",
	"Combine",
	"Feltzer",
	"Remington",
	"Slamvan",
	"Blade",
	"Freight",
	"Streak",
	"Vortex",
	"Vincent",
	"Bullet",
	"Clover",
	"Sadler",
	"Firetruck",
	"Hustler",
	"Intruder",
	"Primo",
	"Cargobob",
	"Tampa",
	"Sunrise",
	"Merit",
	"Utility",
	"Nevada",
	"Yosemite",
	"Windsor",
	"Monster Truck",
	"Monster Truck",
	"Uranus",
	"Jester",
	"Sultan",
	"Stratum",
	"Elegy",
	"Raindance",
	"RC Tiger",
	"Flash",
	"Tahoma",
	"Savanna",
	"Bandito",
	"Freight",
	"Trailer",
	"Kart",
	"Mower",
	"Duneride",
	"Sweeper",
	"Broadway",
	"Tornado",
	"AT-400",
	"DFT-30",
	"Huntley",
	"Stafford",
	"BF-400",
	"Newsvan",
	"Tug",
	"Trailer",
	"Emperor",
	"Wayfarer",
	"Euros",
	"Hotdog",
	"Club",
	"Trailer",
	"Trailer",
	"Andromada",
	"Dodo",
	"RC Cam",
	"Launch",
	"Police Car (LSPD)",
	"Police Car (SFPD)",
	"Police Car (LVPD)",
	"Police Ranger",
	"Picador",
	"S.W.A.T. Van",
	"Alpha",
	"Phoenix",
	"Glendale",
	"Sadler",
	"Luggage Trailer",
	"Luggage Trailer",
	"Stair Trailer",
	"Boxville",
	"Farm Plow",
	"Utility Trailer"
};

/* Functions */

stock Update3DSpeedometer(playerid, bool:showName=true, bool:showHealth = false, speed=TDSPEED_INVALID_ITEM, fuel=TDSPEED_INVALID_ITEM) {
	if (!tds_Player[playerid][Enabled]) return 1;
	if (!IsPlayerInAnyVehicle(playerid)) {
		tdSpeedo_Toggle(playerid, 0);
		return 1;
	} else if (!IsPlayerNPC(playerid)) {
		new vehid = GetPlayerVehicleID(playerid);
		new Float:vhp;
		GetVehicleHealth(vehid, vhp);
		vhp = (((vhp - 250.0) / 750.0) * 100.0);

		// Format the status text in order: fuel first, then health
		new statusText[48] = " ";
		if(fuel != TDSPEED_INVALID_ITEM) {
			format(statusText, _, "%s: %i%%", _g_s_languageStrings[_g_s_activeLanguage][TDSPEED_ITEM_FUEL], fuel);
		}
		if(showHealth) {
			if(fuel == TDSPEED_INVALID_ITEM) {
				format(statusText, _, "%s: %3.0f%%", _g_s_languageStrings[_g_s_activeLanguage][TDSPEED_ITEM_HEALTH], vhp);
			}
			else {
				format(statusText, _, "%s, %s: %3.0f%%", statusText, _g_s_languageStrings[_g_s_activeLanguage][TDSPEED_ITEM_HEALTH], vhp);
			}
		}

		// Format the speed text (in separate line)
		new speedText[48] = " ";
		if(speed != TDSPEED_INVALID_ITEM)
		{
			#if !defined TDSPEED_MPH
				format(speedText, _, "%i KMH", speed);
			#else
				format(speedText, _, "%i MPH", speed);
			#endif
		}
		// Decide whether or not to display the vehicle name; then render name, status, speed in that order
		new modelid = GetVehicleModel(vehid);
		// TODO: explain how below the alternate text cannot be empty as it will not be re-rendered -> use spaces where appropriate
		SetDynamicObjectMaterialText(tds_Player[playerid][Name], 0, showName ? gVehicleNames[modelid-400] : " ", OBJECT_MATERIAL_SIZE_512x256, "Arial", 30, true, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_RIGHT);
		SetDynamicObjectMaterialText(tds_Player[playerid][Status], 0, statusText, OBJECT_MATERIAL_SIZE_512x256, "Arial", 30, false, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_RIGHT);
		SetDynamicObjectMaterialText(tds_Player[playerid][Speed], 0, speedText, OBJECT_MATERIAL_SIZE_512x256, "Arial", 30, false, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_RIGHT);
	}
	return 1;
}

static tdSpeedo_Toggle(playerid, activate) {
	if (activate) {
		if (tds_Player[playerid][Enabled]) {
			return 1;
		}
		new vid = GetPlayerVehicleID(playerid);
		new vmod = GetVehicleModel(vid);
		tds_Player[playerid][Name] = CreateDynamicObject(19482, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, playerid, 200.0);
		tds_Player[playerid][Status] = CreateDynamicObject(19482, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, playerid, 200.0);
		tds_Player[playerid][Speed] = CreateDynamicObject(19482, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, playerid, 200.0);
		new Float:vX,Float:vY,Float:vZ;
		GetVehicleModelInfo(vmod, VEHICLE_MODEL_INFO_SIZE, vX, vY, vZ);
		if (vX < 1.5) {
			vX = 1.5;
		}
		AttachDynamicObjectToVehicle(tds_Player[playerid][Name], vid, -vX-1.75, -1.0, 0.0, 0.0, 0.0, 290.0);
		AttachDynamicObjectToVehicle(tds_Player[playerid][Status], vid, -vX-1.75, -1.0, -0.3, 0.0, 0.0, 290.0);
		AttachDynamicObjectToVehicle(tds_Player[playerid][Speed], vid, -vX-1.75, -1.0, -0.6, 0.0, 0.0, 290.0);
		Streamer_Update(playerid);
		tds_Player[playerid][Enabled] = 1;
	} else {
		if (tds_Player[playerid][Status] != INVALID_OBJECT_ID) {
			DestroyDynamicObject(tds_Player[playerid][Name]);
			tds_Player[playerid][Name] = INVALID_OBJECT_ID;
			DestroyDynamicObject(tds_Player[playerid][Status]);
			tds_Player[playerid][Status] = INVALID_OBJECT_ID;
			DestroyDynamicObject(tds_Player[playerid][Speed]);
			tds_Player[playerid][Speed] = INVALID_OBJECT_ID;
		}
		tds_Player[playerid][Enabled] = 0;
	}
	return 1;
}


/*
   Hooks
*/

public OnPlayerConnect(playerid) {
	for (new i = 0; i < _:SpeedometerComponents-1; i++) {
		tds_Player[playerid][SpeedometerComponents:i] = INVALID_OBJECT_ID;
	}
	tds_Player[playerid][Enabled] = 0;

	#if defined tf_OnPlayerConnect
		return tds_OnPlayerConnect(playerid);
	#endif
}


public OnPlayerDisconnect(playerid, reason) {
	if(tds_Player[playerid][Status] != INVALID_OBJECT_ID) {
		DestroyDynamicObject(tds_Player[playerid][Name]);
		DestroyDynamicObject(tds_Player[playerid][Status]);
		DestroyDynamicObject(tds_Player[playerid][Speed]);
	}

	#if defined tf_OnPlayerDisconnect
		return tds_OnPlayerDisconnect(playerid);
	#endif
}

public OnPlayerStateChange(playerid, newstate, oldstate) {
	if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) {
		tdSpeedo_Toggle(playerid, 1);
	} else {
		tdSpeedo_Toggle(playerid, 0);
	}

	#if defined tf_OnPlayerStateChange
		return tds_OnPlayerStateChange(playerid);
	#endif
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect tds_OnPlayerConnect

#if defined tds_OnPlayerConnect
	forward tds_OnPlayerConnect();
#endif

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect tds_OnPlayerDisconnect

#if defined tds_OnPlayerDisconnect
	forward tds_OnPlayerDisconnect();
#endif

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange tds_OnPlayerStateChange

#if defined tds_OnPlayerStateChange
	forward tds_OnPlayerStateChange();
#endif
