#include "grid.hpp"

grid::grid(GameDataRef data, int x, int y, int p):_data(data), size_x(x), size_y(y), player_count(p){
    sf::Vector2u size = _data->window.getSize();
    len_x = size.x/size_x; len_y = size.y/size_y;
    for (int i=1; i<=p; i++){
        playerlist[i] = true;
    }
}

void grid::Init(){
    // Load Resources
    for (int i=1; i<=player_count; i++){
        std::string str = "Player"+std::to_string(i);
        std::string fName = "res/"+std::to_string(i)+".png";
        _data->res.LoadTexture(str, fName);
    }
    _data->res.LoadTexture("GridBg", GRID_BG_PATH);
    _background.setTexture(_data->res.GetTexture("GridBg"));

    // Create tiles
    for (int i=0; i<size_y; ++i){
        std::vector<tile> horiz;
        for (int j=0; j<size_x; ++j){
            int m_size = 4;
            
            if (i == 0 || i == size_y-1) m_size -= 1;
            if (j == 0 || j == size_x-1) m_size -= 1;
            
            horiz.push_back(tile(j, i, m_size, len_x, len_y, _data));
        }
        m_grid.push_back(horiz);
    }
}

void grid::draw_grid(){
    // Stack overflow jindabad
    int numLines = size_x+size_y-2;
    sf::VertexArray grid(sf::Lines, 2*(numLines));
    
    for(int i=0; i < size_y-1; i++){
        int r = i+1;
        float rowY = len_y*r;
        grid[i*2].position = {0, rowY};
        grid[i*2+1].position = {len_x*size_x, rowY};
    }
    
    for(int i=size_y-1; i < numLines; i++){
        int c = i-size_y+2;
        float colX = len_x*c;
        grid[i*2].position = {colX, 0};
        grid[i*2+1].position = {colX, len_y*size_y};
    }
    
    _data->window.draw(grid);
}

int grid::CheckGameOver(){
    std::set<int> foundPlayers;
    for (auto x: m_grid){
        for (auto y: x){
            if (y.occupied){
                foundPlayers.insert(y.player);
            }
        }
    }
    if (foundPlayers.size() == 1) return *foundPlayers.begin();                          // If only one player is alive game is over
    for (int i=1; i<=player_count; i++) playerlist[i] = false;                           // Make everyone dead before updating their status
    for (auto i=foundPlayers.begin(), j=foundPlayers.end(); i!=j; ++i){
        playerlist[*i] = true;                                                           // Found players are set as alive
    }
    return -1;
    
}

void grid::explosion(int x, int y){
    tile& t = m_grid[y][x];
    int p = t.player;
    if (t.overflow()){
        t.makeVaccant();
        if (x>0){
            click(x-1, y, p, 1);
            t.remove();
        }
        if (x<size_x-1){
            click(x+1, y, p, 1);
            t.remove();
        }
        if (y>0){
            click(x, y-1, p, 1);
            t.remove();
        }
        if (y<size_y-1){
            click(x, y+1, p, 1);
            t.remove();
        }
    }
}

bool grid::click(int x, int y, int p, bool force){
    if (!isRunning) return false;
    tile& t = m_grid[y][x];    
    if (!t.occupied){fill(t, p); return true;}
    if (t.player != p && !force) return false;
    fill(t, p);
    explosion(x, y);
    return true;
}

void grid::fill(tile& t, int p){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    t.fill(p);
    Draw();
    Update();
}

void grid::HandleInput(){
    while(_data->window.pollEvent(_data->event)){
        if ((_data->event.type == sf::Event::Closed) || (_data->event.type == sf::Event::KeyPressed && _data->event.key.code == sf::Keyboard::Escape))
            _data->window.close();
        else if (_data->event.type == sf::Event::MouseButtonPressed && _data->event.mouseButton.button == sf::Mouse::Left){

            sf::Vector2i mPos = sf::Mouse::getPosition(_data->window);
            
            if (click(mPos.x/len_x, mPos.y/len_y, curr_player)){                        // If click was success
                if (!beginCheck) if (curr_player == player_count) beginCheck = true;    // Begin game over checks once all player placed their ball
                do {
                    curr_player = (curr_player%player_count)+1;
                } while (!playerlist[curr_player]);                                     // Increase curr_player count if the player is already dead
            }

        } else if (_data->event.type == sf::Event::KeyPressed && _data->event.key.code == sf::Keyboard::Return)
            _data->handler.RemoveScene();
    }
}


void grid::Draw(){
    _data->window.clear();
    _data->window.draw(_background);
    draw_grid();
    for (int i=0; i<size_y; i++){
        for (int j=0; j<size_x; j++){
            m_grid[i][j].Draw();
        }
    }
    _data->window.display();
}

void grid::Update(){
    if (beginCheck){
        int winner = CheckGameOver();
        if (winner!=-1){
            std::cout << "Player " << winner << " won the game!" << std::endl;
            _data->handler.RemoveScene();
            isRunning = false;
        }
    }
}
