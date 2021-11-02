#pragma once

#include <memory>
#include <stack>

#include "Scene.hpp"

typedef std::unique_ptr<Scene> SceneRef;

class SceneHandler{
public:
    SceneHandler(){}
    ~SceneHandler(){}

    void AddScene( SceneRef newScene, bool isReplacing = true);
    void RemoveScene();

    void ProcessSceneChanges();

    SceneRef& GetActiveScene();
private:
    std::stack<SceneRef> _scenes;
    SceneRef _newScene;

    bool _isRemoving;
    bool _isAdding;
    bool _isReplacing;
};