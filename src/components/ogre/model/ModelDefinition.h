//
// C++ Interface: ModelDefinition
//
// Description:
//
//
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2004
// Copyright (c) 2005 The Cataclysmos Team
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
#ifndef EMBEROGREMODELDEFINITION_H
#define EMBEROGREMODELDEFINITION_H

#include "components/ogre/EmberOgrePrerequisites.h"
#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include <OgreLight.h>
#include <OgreColourValue.h>
#include <OgreResource.h>
#include <OgreSharedPtr.h>
#include <map>
#include <vector>

namespace Ember
{
namespace OgreView
{
namespace Model
{

class Model;
class PartDefinition;
class SubModelDefinition;
class ModelDefinition;
class SubEntityDefinition;

class ActionDefinition;
class SoundDefinition;
class AnimationDefinition;
struct AnimationPartDefinition;
struct ActivationDefinition;
struct AttachPointDefinition;
struct ViewDefinition;

typedef std::map<std::string, Model*> ModelInstanceStore;

typedef std::vector<SubModelDefinition*> SubModelDefinitionsStore;
typedef std::vector<PartDefinition*> PartDefinitionsStore;
typedef std::vector<SubEntityDefinition*> SubEntityDefinitionsStore;
typedef std::vector<AnimationDefinition*> AnimationDefinitionsStore;
typedef std::vector<AnimationPartDefinition*> AnimationPartDefinitionsStore;
typedef std::vector<SoundDefinition*> SoundDefinitionsStore;
typedef std::vector<ActionDefinition*> ActionDefinitionsStore;
typedef std::vector<AttachPointDefinition> AttachPointDefinitionStore;
typedef std::vector<ActivationDefinition*> ActivationDefinitionStore;
typedef std::map<std::string, ViewDefinition*> ViewDefinitionStore;
typedef std::map<std::string, std::string> StringParamStore;

/**
 A rendering definition. This allows you to specify a different render method than the default one (regular Model).
 All of this requires that you create functionality for implementing the different schemes that might be specified.
 */
class RenderingDefinition
{
  friend class XMLModelDefinitionSerializer;
public:

  /**
   * Gets the scheme which will be used.
   * @return
   */
  const std::string& getScheme() const;
  /**
   * Sets the scheme.
   * @param scheme
   */
  void setScheme(const std::string& scheme);
  /**
   * Gets a collection of parameters for the rendering scheme.
   * @return
   */
  const StringParamStore& getParameters() const;

private:
  StringParamStore mParams;
  std::string mScheme;
};

class SubEntityDefinition
{
  friend class PartDefinition;
public:
  const std::string& getSubEntityName() const;
  unsigned int getSubEntityIndex() const;
  //void setSubEntityName(const std::string&);

  const std::string& getMaterialName() const;
  void setMaterialName(const std::string& materialName);

  const PartDefinition& getPartDefinition() const;

private:
  SubEntityDefinition(const std::string& subEntityName, PartDefinition& partdef);
  SubEntityDefinition(unsigned int subEntityIndex, PartDefinition& partdef);
  std::string mSubEntityName;
  std::string mMaterialName;
  unsigned int mSubEntityIndex;
  PartDefinition& mPartDef;
};

class PartDefinition
{
  friend class SubModelDefinition;
public:
  ~PartDefinition();

  void setName(const std::string& name);
  const std::string& getName() const;

  void setGroup(const std::string& group);
  const std::string& getGroup() const;

  void setShow(bool show);
  bool getShow() const;

  SubEntityDefinition* createSubEntityDefinition(const std::string& subEntityName);
  SubEntityDefinition* createSubEntityDefinition(unsigned int subEntityIndex);
  const SubEntityDefinitionsStore& getSubEntityDefinitions() const;
  void removeSubEntityDefinition(SubEntityDefinition* def);

  const SubModelDefinition& getSubModelDefinition() const;

private:
  PartDefinition(const std::string& name, SubModelDefinition& subModelDef);
  std::string mName;
  bool mShow;
  std::string mGroup;
  SubEntityDefinitionsStore mSubEntities;
  SubModelDefinition& mSubModelDef;
};

class SubModelDefinition
{
  friend class ModelDefinition;
public:
  ~SubModelDefinition();

  const std::string& getMeshName() const;

  PartDefinition* createPartDefinition(const std::string& partname);
  const PartDefinitionsStore& getPartDefinitions() const;
  void removePartDefinition(PartDefinition* def);

  const ModelDefinition& getModelDefinition() const;

private:
  SubModelDefinition(const std::string& meshname, ModelDefinition& modelDef);
  std::string mMeshName;
  PartDefinitionsStore mParts;
  ModelDefinition& mModelDef;
};

/**
 A simple struct for defining a certain view of the Model. These settings needs to be applied to the camera rendering the Model.
 */
struct ViewDefinition
{
  /**
   The name of the view.
   */
  std::string Name;

  /**
   The rotation of the camera related to the Model.
   */
  Ogre::Quaternion Rotation;

  /**
   The distance of the camera from the Model.
   */
  float Distance;
};

struct AttachPointDefinition
{
  std::string Name;
  std::string BoneName;
  Ogre::Quaternion Rotation;
};

struct AnimationPartDefinition
{
  std::string Name;
  Ogre::Real Weight;
};

class AnimationDefinition
{
  friend class ActionDefinition;
public:
  ~AnimationDefinition();
  AnimationPartDefinition* createAnimationPartDefinition(const std::string& ogreAnimationName, Ogre::Real weight = 1);
  const AnimationPartDefinitionsStore& getAnimationPartDefinitions() const;
  void removeAnimationPartDefinition(AnimationPartDefinition* def);

  const std::string& getName() const;
  int getIterations() const;

private:
  AnimationDefinition(int iterations);

  AnimationPartDefinitionsStore mAnimationParts;
  std::string mName;
  int mIterations;
};

struct SoundDefinition
{
  std::string groupName;
  unsigned int playOrder;
};

/**
 * @brief A definition for an action activation.
 *
 * This structure is used to determine when an action should be played.
 */
struct ActivationDefinition
{
  /**
   * @brief The type of activation.
   */
  enum Type
  {
    /**
     * @brief Activation through change of movement type.
     */
    MOVEMENT, //!< MOVEMENT

    /**
     * @brief Activation through an entity action.
     */
    ACTION, //!< ACTION

    /**
     * @brief Activation through a task being carried out.
     */
    TASK //!< TASK
  };

  /**
   * @brief The type of the activation.
   */
  Type type;

  /**
   * @brief The trigger for the activation.
   *
   * The interpretion of this value is dependent on the type.
   */
  std::string trigger;
};

class ActionDefinition
{
  friend class ModelDefinition;
public:
  ~ActionDefinition();

  AnimationDefinition* createAnimationDefinition(int iterations = 1);
  const AnimationDefinitionsStore& getAnimationDefinitions() const;
  void removeAnimationDefinition(AnimationDefinition* def);

  SoundDefinition* createSoundDefinition(const std::string& groupName, unsigned int play);
  const SoundDefinitionsStore& getSoundDefinitions() const;
  void removeSoundDefinition(SoundDefinition* def);

  ActivationDefinition* createActivationDefinition(const ActivationDefinition::Type& type, const std::string& trigger);
  const ActivationDefinitionStore& getActivationDefinitions() const;
  void removeActivationDefinition(ActivationDefinition* def);

  const std::string& getName() const;
  Ogre::Real getAnimationSpeed() const
  {
    return mAnimationSpeed;
  }
  void setAnimationSpeed(Ogre::Real speed)
  {
    mAnimationSpeed = speed;
  }

private:
  ActionDefinition(const std::string& name);

  std::string mName;
  AnimationDefinitionsStore mAnimations;
  SoundDefinitionsStore mSounds;
  ActivationDefinitionStore mActivations;
  Ogre::Real mAnimationSpeed;
};

/**
 @author Erik Hjortsberg
 */
class ModelDefinition: public Ogre::Resource
{

  friend class XMLModelDefinitionSerializer;
  friend class Model;

public:

  /**
   whether to use a certain axis for scaling
   for example, if you use a model of a human you probably want to scale according to the height
   this might mean that width and depths aren't correct though
   */
  enum UseScaleOf
  {
    MODEL_ALL = 0, MODEL_NONE = 1, MODEL_WIDTH = 2, MODEL_DEPTH = 3, MODEL_HEIGHT = 4
  };

  //th ModelDefinition(const Ogre::String& name, const Ogre::String& path);

  ModelDefinition(Ogre::ResourceManager* creator, const Ogre::String& name, Ogre::ResourceHandle handle, const Ogre::String& group, bool isManual = false, Ogre::ManualResourceLoader* loader = 0);

  virtual ~ModelDefinition();

  bool isValid(void) const;
  void setValid(bool valid);

  //Ogre resource virtual functions
  void loadImpl(void);

  void unloadImpl(void);

  size_t calculateSize(void) const;

  /**
   *    Gets the amount of scale that needs to be applied to derived Models.
   * @return
   */
  Ogre::Real getScale() const;
  void setScale(Ogre::Real scale);

  /**
   *    Gets how derived Models needs to be scaled.
   Defaults to "ALL"
   * @return
   */
  const UseScaleOf getUseScaleOf() const;
  void setUseScaleOf(const UseScaleOf useScale);

  /**
   *    Gets an optional translation vector which should be applied to derived Models.
   * @return
   */
  const Ogre::Vector3& getTranslate() const;
  void setTranslate(const Ogre::Vector3 translate);

  /**
   *	Whether contained entities should be shown or not.
   Defaults to true.
   * @return true if contained entities should be shown, else false
   */
  bool getShowContained() const;
  void setShowContained(bool show);

  /**
   *    If set to something else than 0, all models beyond this distance won't be shown.
   * @return
   */
  float getRenderingDistance() const;
  void setRenderingDistance(float distance);

  /**
   *    Returns a vector defining how much, if ever, contained entities should be offset.
   *    If they shouldn't, Ogre::Vector3::ZERO will be returned.
   * @return A offset vector.
   */
  const Ogre::Vector3& getContentOffset() const;
  void setContentOffset(const Ogre::Vector3&);

  /**
   *    Gets the rotation of the model.
   * @return
   */
  const Ogre::Quaternion& getRotation() const;

  /**
   *    Sets the rotation of the model.
   * @param rotation
   */
  void setRotation(const Ogre::Quaternion rotation);

  /**
   *    Gets a path to an icon resource, if defined.
   * @return a path to an image which can be used as an icon for the model
   */
  const std::string& getIconPath() const;

  /**
   *    Creates and returns a new sub model definition for the supplied mesh name.
   * @param meshname The name of the mesh to base the new sub model on. Must be a valid mesh.
   * @return
   */
  SubModelDefinition* createSubModelDefinition(const std::string& meshname);

  /**
   *    Returns all SubModelDefinitions defined.
   * @return The SubModelDefinitions store.
   */
  const SubModelDefinitionsStore& getSubModelDefinitions() const;

  /**
   *    Removes a certain SubModelDefinition.
   * @param def The definition to remove.
   */
  void removeSubModelDefinition(SubModelDefinition* def);

  /**
   * Creates and returns a new ActionDefintion with the given name.
   * @param actionname The name of the new ActionDefinition.
   * @return A pointer to the new ActionDefinition.
   */
  ActionDefinition* createActionDefinition(const std::string& actionname);

  /**
   *    Returns all ActionDefinitions defined.
   * @return
   */
  const ActionDefinitionsStore& getActionDefinitions() const;

  /**
   * @brief Removes a certain ActionDefinition.
   * @param def The definition to remove.
   */
  void removeActionDefinition(ActionDefinition* def);

  /**
   * @brief Gets all attach point definitions.
   * @return All attach point definitions.
   */
  const AttachPointDefinitionStore& getAttachPointsDefinitions() const;

  /**
   * @brief Adds a new attach point definition.
   *
   * If an definition with the same name already exists it will be updated. Else a new entry will be added.
   *
   * @param definition The new definition.
   */
  void addAttachPointDefinition(const AttachPointDefinition& definition);

  /**
   Creates and returns a new ViewDefinition with the supplied name.
   @param viewname The name of the view
   @return A pointer to the new view.
   */
  ViewDefinition* createViewDefinition(const std::string& viewname);

  /**
   * Returns all views defined.
   * @return
   */
  const ViewDefinitionStore& getViewDefinitions() const;

  /**
   * Removed a named view. If no view can be found, no exception will be thrown.
   * @param name The name of the view to to remove.
   */
  void removeViewDefinition(const std::string name);

  /**
   * Utility method for removing a defintion from a non-associative stores (vector, list etc.)
   * @param def The defintion to remove.
   * @param store The store to remove from.
   */
  template<typename T, typename T1>
  static void removeDefinition(T* def, T1& store);

  /**
   *    Reloads all the Model instances that uses this definition.
   */
  void reloadAllInstances();

  /**
   *    Gets a pointer to the rendering scheme definition, or null if none specified.
   * @return
   */
  const RenderingDefinition* getRenderingDefinition() const;

private:

  struct BindingDefinition
  {
    std::string EmitterVar;
    std::string AtlasAttribute;
  };

  typedef std::vector<BindingDefinition> BindingSet;

  /**
   * @brief A definition of a particle system.
   */
  struct ParticleSystemDefinition
  {
    /**
     * @brief The script to use for the particle system.
     *
     * This must be defined in a separate Ogre .particle script.
     */
    std::string Script;

    /**
     * @brief An optional world direction to which the particle system should be locked.
     *
     * In most cases this would be up, since most particle systems would want to be emitted upwards (smoke, fire etc.).
     * If no direction is defined, this will be invalid. In these cases, the particle system will use the local coords of the parent scene node. If the particle system is directional, this will look strange when the model is attached to another model (such as when wielded).
     */
    Ogre::Vector3 Direction;

    /**
     * @brief A set of bindings.
     *
     * A binding is a connection between an entity attribute and a parameter of the particle system.
     * This allows for such effects as a fire growing larger as the status of the fire entity increases.
     */
    BindingSet Bindings;
  };

  typedef std::vector<ParticleSystemDefinition> ParticleSystemSet;

  struct LightDefinition
  {
    Ogre::Light::LightTypes type;
    Ogre::ColourValue diffuseColour, specularColour;
    Ogre::Real range, constant, linear, quadratic;
    Ogre::Vector3 position;
  };

  typedef std::vector<LightDefinition> LightSet;

  /**
   *    Adds a model instance to the internal store of instances. This method should be called from the class Model when a new Model is created.
   * @param
   */
  void addModelInstance(Model*);
  /**
   *    Removed a model instance from the internal store of instances. This method should be called from the class Model when a new Model is removed.
   * @param
   */
  void removeModelInstance(Model*);

  /**
   A store of all model instances of this definition.
   This can be used to update all instances at once.
   */
  ModelInstanceStore mModelInstances;

  /**
   The minimum distance at which the model will be shown.
   */
  float mRenderingDistance;

  SubModelDefinitionsStore mSubModels;
  ActionDefinitionsStore mActions;
  ParticleSystemSet mParticleSystems;
  LightSet mLights;

  AttachPointDefinitionStore mAttachPoints;

  UseScaleOf mUseScaleOf;
  Ogre::Real mScale;
  Ogre::Quaternion mRotation;
// 	const Ogre::String mPath;

  /**
   Defines how much contained entities should be offset. ZERO if not.
   */
  Ogre::Vector3 mContentOffset;

  /**
   Whether contained entities should be shown or not.
   Defaults to true.
   */
  bool mShowContained;

  /**
   How, if any, to transform the model from the base position.
   Defaults to a zeroed vector.
   */
  Ogre::Vector3 mTranslate;

  bool mIsValid;

  ViewDefinitionStore mViews;

  /**
   A path to an image resource which can be shown as an icon for the model.
   */
  std::string mIconPath;

  RenderingDefinition* mRenderingDef;

};

/** Specialisation of SharedPtr to allow SharedPtr to be assigned to ModelDefnPtr
 @note Has to be a subclass since we need operator=.
 We could templatise this instead of repeating per Resource subclass,
 except to do so requires a form VC6 does not support i.e.
 ResourceSubclassPtr<T> : public SharedPtr<T>
 */
class ModelDefnPtr: public Ogre::SharedPtr<ModelDefinition>
{
public:
  ModelDefnPtr() :
      Ogre::SharedPtr<ModelDefinition>()
  {
  }
  explicit ModelDefnPtr(ModelDefinition* rep) :
      Ogre::SharedPtr<ModelDefinition>(rep)
  {
  }
  ModelDefnPtr(const ModelDefnPtr& r) :
      Ogre::SharedPtr<ModelDefinition>(r)
  {
  }
  ModelDefnPtr(const Ogre::ResourcePtr& r);
  /// Operator used to convert a ResourcePtr to a ModelDefnPtr
  ModelDefnPtr& operator=(const Ogre::ResourcePtr& r);
protected:
  /// Override destroy since we need to delete Mesh after fully defined
//         void destroy(void);
};

typedef ModelDefnPtr ModelDefinitionPtr;

///implementations

inline const Ogre::Vector3& ModelDefinition::getContentOffset() const
{
  return mContentOffset;
}
inline void ModelDefinition::setContentOffset(const Ogre::Vector3& offset)
{
  mContentOffset = offset;
}

inline void ModelDefinition::setValid(bool valid)
{
  mIsValid = valid;
}

inline size_t ModelDefinition::calculateSize(void) const
{
  //TODO:implement this
  return 0;
}

inline Ogre::Real ModelDefinition::getScale() const
{
  return mScale;
}
inline void ModelDefinition::setScale(Ogre::Real scale)
{
  mScale = scale;
}

inline const ModelDefinition::UseScaleOf ModelDefinition::getUseScaleOf() const
{
  return mUseScaleOf;
}
inline void ModelDefinition::setUseScaleOf(const UseScaleOf useScale)
{
  mUseScaleOf = useScale;
}

inline float ModelDefinition::getRenderingDistance() const
{
  return mRenderingDistance;
}

inline void ModelDefinition::setRenderingDistance(float distance)
{
  mRenderingDistance = distance;
}

inline const std::string& ModelDefinition::getIconPath() const
{
  return mIconPath;
}

inline int AnimationDefinition::getIterations() const
{
  return mIterations;
}

}
}
}
#endif
