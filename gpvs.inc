/*

    GPVS - GetPlayerVehicleSeat
    ----------------------------

    v1.0 (2019-11-05) - Initial release.
    v1.1 (2025-05-19) - Code improvements and exploit prevention using IsSeatChangeTooFast.

    This system tracks which seat a player occupies in a vehicle by parsing RakNet packets.
    It also includes anti-abuse logic to prevent rapid seat switching exploits.

*/

#if defined _GPVS_included
    #endinput
#endif
#define _GPVS_included

#if !defined PAWNRAKNET_INC_
    #error Install Pawn.RakNet properly to make it work.
#endif

#define     INVALID_SEAT_ID     (-1)

static g_playerVehicleSeat[MAX_PLAYERS char];
static g_lastSeatChangeTick[MAX_PLAYERS];

stock GetPlayerVehicleSeat(playerid)
{
    if (!IsPlayerConnected(playerid) || !IsPlayerInAnyVehicle(playerid))
        return INVALID_SEAT_ID;

    return g_playerVehicleSeat{playerid};
}

stock bool:IsSeatChangeTooFast(playerid)
{
    new tick = GetTickCount();
    if (tick - g_lastSeatChangeTick[playerid] < 1000)
        return true;

    g_lastSeatChangeTick[playerid] = tick;
    return false;
}

public OnIncomingPacket(playerid, packetid, BitStream:bs)
{
    switch (packetid)
    {
        case 0xC8:
        {
            g_playerVehicleSeat{playerid} = 0;
            g_lastSeatChangeTick[playerid] = GetTickCount();
            break;
        }
        case 0xD3:
        {
            if (BS_GetNumberOfUnreadBits(bs) >= 32)
            {
                BS_SetReadOffset(bs, 26);
                new newSeat;
                BS_ReadValue(bs, PR_BITS, newSeat, 6);
                BS_ResetReadPointer(bs);

                if (IsSeatChangeTooFast(playerid))
                {
                    printf("[!] Player %d attempted to switch seats too quickly.", playerid);
                    return false;
                }

                g_playerVehicleSeat{playerid} = newSeat;
            }
            break;
        }
    }

    #if defined gpvsOnIncomingPacket
        return gpvsOnIncomingPacket(playerid, packetid, bs);
    #else
        return true;
    #endif
}

#if defined _ALS_OnIncomingPacket
    #undef OnIncomingPacket
#else
    #define _ALS_OnIncomingPacket
#endif
#define OnIncomingPacket gpvsOnIncomingPacket

#if defined gpvsOnIncomingPacket
    forward gpvsOnIncomingPacket(playerid, packetid, BitStream:bs);
#endif

#if defined _ALS_GetPlayerVehicleSeat
    #undef GetPlayerVehicleSeat
#else
    #define _ALS_GetPlayerVehicleSeat
#endif
#define GetPlayerVehicleSeat GetPlayerVehicleSeatFixed
