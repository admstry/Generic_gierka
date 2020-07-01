//
// Created by Adam on 16.06.2020.
//

#ifndef GENERIC_GIERKA_TILEMAP_H
#define GENERIC_GIERKA_TILEMAP_H

#include "Entity.h"

class TileMap {
private:
    // variables
    std::vector<std::vector<std::vector<sf::Vertex>>> vertices;
    std::vector<std::vector<std::vector<int>>> tiles;
    std::vector<std::vector<int>> colliders;
    std::vector<std::vector<sf::FloatRect>> walls;
    sf::Texture m_tileset;
    sf::RenderStates states;
    int mapWidth;
    int mapHeight;
    unsigned gridSize;
    int gridSizeI;
    int leftX;
    int rightX;
    int upY;
    int downY;
public:
    TileMap();
    virtual ~TileMap();

    // functions
    bool load(const std::string& tileset_path, sf::Vector2u tileSize, const std::string &tiles_path, const std::string &collmap_path, unsigned int width, unsigned int height, unsigned int layer);
    bool loadFile(const std::string& path,const std::string& path2);
    void updateGlobalBounds(Entity &entity) const;
    void updateTileCollision(Entity *entity, const float &tm);
    void render(sf::RenderTarget& target, sf::Vector2i &gridPos);
};

#endif //GENERIC_GIERKA_TILEMAP_H
