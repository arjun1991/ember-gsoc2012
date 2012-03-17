//
// C++ Interface: ServerWidget
//
// Description: 
//
//
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2004
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.//
//
#ifndef EMBEROGRE_SERVERWIDGET_H
#define EMBEROGRE_SERVERWIDGET_H

#include <Eris/ServerInfo.h>
#include <Eris/Connection.h>
#include <Eris/Avatar.h>
#include <Eris/Account.h>

#include <Atlas/Objects/Entity.h>
#include <Atlas/Message/Element.h>

#include "Widget.h"
#include <map>
#include <vector>

namespace Ember
{
class AvatarTransferInfo;
namespace OgreView
{

class GUIManager;
namespace Gui
{

class NewCharacter
{
public:
  std::string name;
  std::string description;
  std::string gender;
  std::string type;
  std::string spawnPoint;

  bool isValid() const;

};

class Widget;
class ModelRenderer;
/**
 @author Erik Hjortsberg
 */
class ServerWidget: public Widget
{
public:

  ServerWidget();
  virtual ~ServerWidget();
  virtual void buildWidget();

protected:

  typedef std::multimap<std::string, std::string> CharacterAndSpawnsStore;

  Eris::Account* mAccount;

  /**
   A preview renderer for creating new characters
   */
  ModelRenderer* mModelPreviewRenderer;

  NewCharacter mNewChar;

  CEGUI::Listbox* mCharacterList;
  CEGUI::PushButton* mCreateChar;
  CEGUI::PushButton* mUseCreator;
  CEGUI::Editbox* mNewCharName;
  CEGUI::MultiLineEditbox* mNewCharDescription;
  CEGUI::Combobox* mTypesList;
  CEGUI::RadioButton* mGenderRadioButton;

  CharacterAndSpawnsStore mCharacterAndSpawns;

  AvatarTransferInfo* mAvatarTransferInfo;

  /**
   * @brief Keeps track of the character ids of the characters in the mCharacterList listbox.
   */
  std::vector<std::string> mCharacterModel;

  void createdAccount(Eris::Account* account);
  void gotAvatar(Eris::Avatar* avatar);
  void avatar_Deactivated(bool clean);

  bool Login_Click(const CEGUI::EventArgs& args);
  bool LogoutButton_Click(const CEGUI::EventArgs& args);
  bool Choose_Click(const CEGUI::EventArgs& args);
  bool UseCreator_Click(const CEGUI::EventArgs& args);
  bool CreateChar_Click(const CEGUI::EventArgs& args);
  bool CreateAcc_Click(const CEGUI::EventArgs& args);
  bool OkButton_Click(const CEGUI::EventArgs& args);
  bool Disconnect_Click(const CEGUI::EventArgs& args);

  bool TeleportYes_Click(const CEGUI::EventArgs& args);
  bool TeleportNo_Click(const CEGUI::EventArgs& args);

  bool fetchCredentials(Eris::Connection* connection, std::string& user, std::string& pass);
  bool saveCredentials(void);
  void loginSuccess(Eris::Account* account);
  void logoutComplete(bool clean);

  /**
   * Shows the error message sent from Eris if the login does not succeed.
   */
  void showLoginFailure(Eris::Account* account, std::string msg);

  /**
   * Hides the login error message and moves the HelpText to it's original position.
   */
  bool hideLoginFailure();

  /**
   * This function is a slot reacting on a ChangeEvent in the user name box.
   */
  bool nameBox_TextChanged(const CEGUI::EventArgs& args);

  /**
   * This function is a slot reacting on a ChangeEvent in the password box.
   */
  bool passwordBox_TextChanged(const CEGUI::EventArgs& args);
  void gotAllCharacters(Eris::Account* account);

  bool TypesList_SelectionChanged(const CEGUI::EventArgs& args);
  bool Gender_SelectionChanged(const CEGUI::EventArgs& args);
  bool Name_TextChanged(const CEGUI::EventArgs& args);
  bool Description_TextChanged(const CEGUI::EventArgs& args);

  void updateNewCharacter();

  /**
   *    Fills the drop down list with available character types from the server.
   * @param account 
   */
  void fillAllowedCharacterTypes(Eris::Account* account);

  /**
   *    Set up the preview renderer.
   */
  void createPreviewTexture();

  /**
   *    Consume Eris::Connection::GotServerInfo signals.
   */
  void connection_GotServerInfo(Eris::Connection* connection);

  void setConnection(Eris::Connection* connection);

  void connection_Disconnected();

  /**
   *    Shows server info.
   */
  void showServerInfo(Eris::Connection* connection);

  /**
   * @brief Shows an alert explaining to the user that the server doesn't have any available characters and thus isn't correctly setup.
   */
  void showNoCharactersAlert();

  void server_TransferInfoAvailable(const std::vector<AvatarTransferInfo>& transferInfos);
};
}
}
}

#endif
