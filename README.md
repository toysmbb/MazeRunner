
# MazeRunner

**MazeRunner** is a learning-oriented project designed to explore Unreal Engine 5’s C++ API, AI systems, and interactive gameplay mechanics, It is a C++ project built in **Unreal Engine 5** — a survival maze game where the player must escape a dark labyrinth filled with traps, buffs, and a pursuing AI enemy known as the **Catcher**.  
The project demonstrates core gameplay mechanics such as **AI Behavior Trees**, **interactive objects**, **buff/debuff systems**, **teleportation**, and **dynamic lighting** integrated with **UMG UI**.

---

##  Key Features

-  **AI Catcher**
  - A simple **Behavior Tree** controls the enemy that chases the player and deals damage on contact.

-  **Light System**
  - The player can toggle the light system, affecting the visibility and activity of traps and other objects.

-  **Traps and Activators**
  - Traps can be triggered only under certain conditions, such as when lights are active or the player steps into an activator area.

-  **HP Buff**
  - Restores or increases the player’s health when collected.

-  **Death Debuff**
  - Instantly kills the player upon interaction.

-  **Speed Buff**
  - Temporarily boosts the player’s movement speed.

-  **Teleporter**
  - Randomly teleports the player to different points around the level.

-  **UMG User Interface**
  - The in-game HUD and interaction prompts are implemented using **Unreal Motion Graphics (UMG)**.

Technologies Used
Unreal Engine 5	Game engine
C++	Core gameplay logic
Blueprints	Visual scripting for AI and UI
UMG (Unreal Motion Graphics)	User interface system
Behavior Tree	AI decision-making system for Catcher
Visual Studio 2022	Development environment

## Behavior Tree Overview

The **Catcher AI** continuously chases the player throughout the level, regardless of visibility or distance.  
Its behavior logic is implemented using a simple **Behavior Tree** and **AI Controller** combination.

### Behavior Flow:
1. **Constant Pursuit** — The Catcher always moves toward the player’s position.  
2. **Damage on Collision** — When the Catcher touches the player, it immediately deals damage.  
3. **Stun / Cooldown State** — After dealing damage, the Catcher enters a short cooldown state (≈5 seconds) before resuming pursuit.  
4. **Resume Chase** — Once the cooldown period ends, the Catcher continues chasing the player.

This setup demonstrates a **basic but effective AI system** using Unreal Engine’s **Behavior Tree** and **C++ event-driven logic**, without relying on vision checks or perception components.


## 🧱 Project Structure

