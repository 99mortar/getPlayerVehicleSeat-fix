# GPVS - GetPlayerVehicleSeat

**GPVS** is a lightweight and efficient Pawn system for tracking the vehicle seat each player occupies, based on RakNet packet interception.

It also includes a security check to prevent abuse through rapid seat switching.

---

## 🚀 Features

- 📦 Accurately detects the seat a player occupies in any vehicle.
- 🔒 Anti-exploit system using a cooldown (`IsSeatChangeTooFast`).
- ⚙️ Easily integrates into admin tools or gameplay logic (e.g., seat restrictions).

---

## 📥 Requirements

- [Pawn.RakNet](https://github.com/urShadow/Pawn.RakNet)

---

## 📦 Installation

1. **Download or clone** this repository.
2. Place the `.inc` file in your script's `include` folder.
3. Include it at the top of your script:

```pawn
#include <gpvs>
