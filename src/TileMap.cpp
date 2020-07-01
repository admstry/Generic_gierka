//
// Created by Adam on 18.06.2020.
//
#include "pch.h"
#include "TileMap.h"

TileMap::TileMap() {
    mapWidth = 0;
    mapHeight = 0;
    gridSize = 0;
    gridSizeI = 0;
    leftX = 0;
    rightX = 0;
    upY = 0;
    downY = 0;
}

TileMap::~TileMap() = default;

bool TileMap::load(const std::string &tileset_path, sf::Vector2u tileSize, const std::string &tiles_path,
                   const std::string &collmap_path, unsigned int width, unsigned int height, unsigned int layer) {

    mapWidth = static_cast<int>(width);
    mapHeight = static_cast<int>(height);

    gridSize = tileSize.x;
    gridSizeI = static_cast<int>(gridSize);

    if (!m_tileset.loadFromFile(tileset_path)) {
        return false;
    }

    vertices.resize(width, std::vector<std::vector<sf::Vertex>>());
    for (unsigned int x = 0; x < width; x++) {
        vertices.at(x).resize(height, std::vector<sf::Vertex>());
        for (unsigned int y = 0; y < height; y++) {
            vertices.at(x).at(y).resize(4, sf::Vertex());
        }
    }
    tiles.resize(width, std::vector<std::vector<int>>());
    for (unsigned int x = 0; x < width; x++) {
        tiles.at(x).resize(height, std::vector<int>());
    }

    colliders.resize(width, std::vector<int>());

    walls.resize(width, std::vector<sf::FloatRect>());


    if (!loadFile(tiles_path,collmap_path)) {
        return false;
    }

    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j) {
            // get the current tile number
            int tileNumber = tiles.at(j).at(i).at(layer);
            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &vertices.at(i).at(j).at(0);


            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

        }

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            if (colliders.at(j).at(i) == 32) {
                walls.at(i).push_back(sf::FloatRect(i*gridSizeI,j*gridSizeI,gridSizeI,gridSizeI));
            }
        }
    }

    return true;
}

bool TileMap::loadFile(const std::string &path, const std::string &path2) {

    std::ifstream File(path);
    std::ifstream File2(path2);
    std::string line;
    int values,y,x = 0;

    if (!File.is_open()) return false;
    if (!File2.is_open()) return false;
    if (File.good()) {
        while(std::getline(File, line)) {
            // Create a stringstream of the current line
            std::stringstream ss(line);

            // Keep track of the current column index
            y = 0;
            // Extract each integer
            while(ss >> values){

                // Add the current integer to the 'colIdx' column's values vector
                tiles.at(x).at(y).push_back(values);

                // If the next token is a comma, ignore it and move on
                if(ss.peek() == ',') ss.ignore();

                // Increment the column index
                y++;
            }
            x++;
        }
    }

    File.close();

    x = 0;
    if (File2.good()) {
        while(std::getline(File2, line)) {
            std::stringstream ss(line);
            while(ss >> values){
                colliders.at(x).push_back(values);
                if(ss.peek() == ',') ss.ignore();
            }
            x++;
        }
    }

    File2.close();

    return true;
}

void TileMap::updateGlobalBounds(Entity &entity) const {

}

void TileMap::updateTileCollision(Entity * entity, const float &tm) {

    for (auto &it : walls) {
        for (auto &wall : it) {
            if (wall.intersects(entity->getNextBounds(tm))) {
                sf::FloatRect entityBounds = entity->getGlobalBounds();
                // bottom collision
                if (entityBounds.top < wall.top
                    && entityBounds.top + entityBounds.height < wall.top + wall.height
                    && entityBounds.left < wall.left + wall.width
                    && entityBounds.left + entityBounds.width > wall.left
                        ) {
                    entity->stopVelocityY();
                    entity->setPosition(sf::Vector2f(entityBounds.left, wall.top - entityBounds.height));
                }

                    // top collision
                else if (entityBounds.top > wall.top
                         && entityBounds.top + entityBounds.height > wall.top + wall.height
                         && entityBounds.left < wall.left + wall.width
                         && entityBounds.left + entityBounds.width > wall.left
                        ) {
                    entity->stopVelocityY();
                    entity->setPosition(sf::Vector2f(entityBounds.left, wall.top + wall.height));
                }

                // right collision
                if (entityBounds.left < wall.left
                    && entityBounds.left + entityBounds.width < wall.left + wall.width
                    && entityBounds.top < wall.top + wall.height - 5.f
                    && entityBounds.top + entityBounds.height > wall.top + 5.f
                        ) {
                    entity->stopVelocityX();
                    entity->setPosition(sf::Vector2f(wall.left - entityBounds.width, entityBounds.top));
                }

                    // left collision
                else if (entityBounds.left > wall.left
                         && entityBounds.left + entityBounds.width > wall.left + wall.width
                         && entityBounds.top < wall.top + wall.height - 5.f
                         && entityBounds.top + entityBounds.height > wall.top + 5.f
                        ) {
                    entity->stopVelocityX();
                    entity->setPosition(sf::Vector2f(wall.left + wall.width, entityBounds.top));
                }
            }
        }
    }

}

void TileMap::render(sf::RenderTarget &target, sf::Vector2i &gridPos) {

    states.texture = &m_tileset;

    leftX = gridPos.x - 15;
    if (leftX < 0) leftX = 0;
    else if (leftX > mapWidth) leftX = mapWidth;

    rightX = gridPos.x + 16;
    if (rightX < 0) rightX = 0;
    else if (rightX > mapWidth) rightX = mapWidth;

    upY = gridPos.y - 8;
    if (upY < 0) upY = 0;
    else if (upY > mapWidth) upY = mapWidth;

    downY = gridPos.y + 9;
    if (downY < 0) downY = 0;
    else if (downY > mapWidth) downY = mapWidth;


    for (unsigned int it = leftX; it < rightX; it++) {
        for (unsigned int it2 = upY; it2 < downY; it2++) {
            target.draw(&vertices[it][it2][0], 4, sf::Quads, states);
        }
    }
}


