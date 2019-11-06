#if defined	_GPVS_included
	#endinput
#endif
#define _GPVS_included


#if !defined PAWNRAKNET_INC_
	#error You need to have Pawn.RakNet.
#endif


#define 	INVALID_SEAT_ID		(-1)


static gpvsPlayerSeat[MAX_PLAYERS char];

/*
	Function ~>
*/
stock GetPlayerVehicleSeat(playerid)
{
	if(!IsPlayerConnected(playerid) || !IsPlayerInAnyVehicle(playerid))
		return INVALID_SEAT_ID;
	else
		return gpvsPlayerSeat{playerid};
}


public OnIncomingPacket(playerid, packetid, BitStream:bs)
{
	if(packetid == 0xC8)
		gpvsPlayerSeat{playerid} = 0;
	else if(packetid == 0xD3)
	{
		BS_SetReadOffset(bs, 26);
		BS_ReadValue(\
			bs,
			PR_BITS, gpvsPlayerSeat{playerid}, 6
		);
		BS_ResetReadPointer(bs);
	}
	#if defined gpvsOnIncomingPacket
		return gpvsOnIncomingPacket(playerid, packetid, bs);
	#else
		return true;
	#endif
}

/*

	Hooking fucktion and callback.
*/
#if defined _ALS_OnIncomingPacket
	#undef OnIncomingPacket
#else
	#define _ALS_OnIncomingPacket
#endif
#define 	OnIncomingPacket 	gpvsOnIncomingPacket

#if defined gpvsOnIncomingPacket
	forward gpvsOnIncomingPacket(playerid, packetid, BitStream:bs);
#endif

/* <~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~> */
#if defined _ALS_GetPlayerVehicleSeat
	#undef GetPlayerVehicleSeat
#else
	#define _ALS_GetPlayerVehicleSeat
#endif
#define 	GetPlayerVehicleSeat 	GetPlayerVehicleSeatFixed
