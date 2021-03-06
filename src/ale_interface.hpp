/* *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2013 by Yavar Naddaf, Joel Veness, Marc G. Bellemare,
 *  Matthew Hausknecht, and the Reinforcement Learning and Artificial Intelligence 
 *  Laboratory
 * Released under the GNU General Public License; see License.txt for details. 
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 *  ale_interface.hpp
 *
 *  The shared library interface.
 **************************************************************************** */
#ifndef __ALE_INTERFACE_HPP__
#define __ALE_INTERFACE_HPP__

#include "emucore/FSNode.hxx"
#include "emucore/OSystem.hxx"
#include "os_dependent/SettingsWin32.hxx"
#include "os_dependent/OSystemWin32.hxx"
#include "os_dependent/SettingsUNIX.hxx"
#include "os_dependent/OSystemUNIX.hxx"
#include "games/Roms.hpp"
#include "common/Defaults.hpp"
#include "common/display_screen.h"
#include "environment/stella_environment.hpp"

static const std::string Version = "0.4.4";

/**
   This class interfaces ALE with external code for controlling agents.
 */
class ALEInterface {
public:
  ALEInterface();
  ~ALEInterface();

  // Get the value of a setting.
  std::string getString(const std::string& key);
  int getInt(const std::string& key);
  bool getBool(const std::string& key);
  float getFloat(const std::string& key);

  // Set the value of a setting. loadRom() must be called before the
  // setting will take effect.
  void set(const std::string& key, const std::string& value);
  void set(const std::string& key, const int& value);
  void set(const std::string& key, const bool& value);
  void set(const std::string& key, const float& value);

  // Resets the Atari and loads a game. After this call the game
  // should be ready to play. This is necessary after changing a
  // setting for the setting to take effect.
  void loadROM(string rom_file);

  // Applies an action to the game and returns the reward. It is the
  // user's responsibility to check if the game has ended and reset
  // when necessary - this method will keep pressing buttons on the
  // game over screen.
  reward_t act(Action action);

  // Indicates if the game has ended.
  bool game_over();

  // Resets the game, but not the full system.
  void reset_game();

  // Returns the vector of legal actions. This should be called only
  // after the rom is loaded.
  ActionVect getLegalActionSet();

  // Returns the vector of the minimal set of actions needed to play
  // the game.
  ActionVect getMinimalActionSet();

  // Returns the frame number since the loading of the ROM
  int getFrameNumber();

  // Returns the frame number since the start of the current episode
  int getEpisodeFrameNumber();

  // Returns the current game screen
  const ALEScreen &getScreen();

  // Returns the current RAM content
  const ALERAM &getRAM();

  // Saves the state of the system
  void saveState();

  // Loads the state of the system
  void loadState();

  ALEState cloneState();

  void restoreState(const ALEState& state);

 public:
  std::auto_ptr<OSystem> theOSystem;
  std::auto_ptr<Settings> theSettings;
  std::auto_ptr<RomSettings> romSettings;
  std::auto_ptr<StellaEnvironment> environment;
  int max_num_frames; // Maximum number of frames for each episode

 public:
  // Display ALE welcome message
  static std::string welcomeMessage();
  static void disableBufferedIO();
  static void createOSystem(std::auto_ptr<OSystem> &theOSystem,
                            std::auto_ptr<Settings> &theSettings);
  static void loadSettings(const string& romfile,
                           std::auto_ptr<OSystem> &theOSystem);
};

#endif
