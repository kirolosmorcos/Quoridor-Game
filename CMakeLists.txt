cmake_minimum_required(VERSION 3.16)
project(Quoridor_Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QRC_FILES
        "src/UserInterface//resources.qrc"
)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

#qt_add_resources(RESOURCE_FILES resources.qrc)

add_executable(Quoridor_Game
        "src/AI/Alpha Beta Minimax.h"
        "src/AI/Alpha Beta Minimax.cpp"
        "src/AI/Best Move.cpp"
        "src/AI/Best Move.h"
        "src/AI/Evaluaion Function.h"
        "src/AI/Evaluation Function.cpp"
        "src/Game Logic/BFS.cpp"
        "src/Game Logic/BFS.h"
        "src/Game Logic/Legal Moves.cpp"
        "src/Game Logic/Legal Moves.h"
        src/Models/GameState.h
        src/UserInterface/Controller.h
        src/UserInterface/Controller.cpp
        src/UserInterface/assets
        src/UserInterface/util/Constants.h
        src/UserInterface/Main.cpp
        src/UserInterface/ui/MainMenuWindow.h
        src/UserInterface/ui/MainMenuWindow.cpp
        src/UserInterface/ui/GameWindow.cpp
        src/UserInterface/ui/GameWindow.h
        src/UserInterface/scene/BoardScene.cpp
        src/UserInterface/scene/BoardScene.h
        src/UserInterface/model/PawnItem.cpp
        src/UserInterface/model/PawnItem.h
        src/UserInterface/model/WallItem.cpp
        src/UserInterface/model/WallItem.h
        src/UserInterface/ui/ModeSelectWindow.cpp
        src/UserInterface/ui/ModeSelectWindow.h
        src/UserInterface/ui/PawnSelectWindow.cpp
        src/UserInterface/ui/PawnSelectWindow.h

)

target_link_libraries(Quoridor_Game
        Qt6::Widgets
)