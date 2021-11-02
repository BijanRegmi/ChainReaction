#include "SceneHandler.hpp"

void SceneHandler::AddScene( SceneRef newScene, bool isReplacing ){
    _isAdding = true;
    this->_isReplacing = isReplacing;

    _newScene = std::move(newScene);
}

void SceneHandler::RemoveScene(){
    this->_isRemoving = true;
}

void SceneHandler::ProcessSceneChanges(){
    if (_isRemoving && !_scenes.empty()){
        _scenes.pop();
        if (!_scenes.empty())
            _scenes.top()->Resume();
        _isRemoving = false;
    }

    if (_isAdding){
        if (!_scenes.empty()){
            if (_isReplacing)
                _scenes.pop();
            else
                _scenes.top()->Pause();
        }
        _scenes.push(std::move(_newScene));
        _scenes.top()->Init();
        _isAdding = false;
    }
}

SceneRef& SceneHandler::GetActiveScene(){
    return _scenes.top();
}