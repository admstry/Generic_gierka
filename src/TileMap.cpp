//
// Created by Adam on 16.06.2020.
//
#include "pch.h"
#include "TileMap.h"
//TODO REMOVE COMMENTED CODE
bool TileMap::load(const std::string &tileset, sf::Vector2u tileSize, const std::vector<std::vector<std::vector<int>>> *tiles, unsigned int width, unsigned int height, unsigned int layer) {
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;
    // resize the vertex array to fit the level size
    // vertices.resize(width*height*4, sf::Vertex());
    // vertices.resize(width, std::vector<sf::Vertex>());
    // for (unsigned int x = 0; x < width; x++) {
    //    vertices.at(x).resize(height*4, sf::Vertex());
    // }
    vertices.resize(width, std::vector<std::vector<sf::Vertex>>());
    for (unsigned int x = 0; x < width; x++) {
        vertices.at(x).resize(height, std::vector<sf::Vertex>());
        for (unsigned int y = 0; y < height; y++) {
            vertices.at(x).at(y).resize(4, sf::Vertex());
        }
    }

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles->at(j).at(i).at(layer);
            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            // sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
            // sf::Vertex* quad = &vertices2[i][j*4];
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

            // TODO DEBUG ONLY REMOVE LATER
            std::cout << i << " " << j << " " << tileNumber <<  " " << tv << tu << "\n";
        }

    return true;
}


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    // try 1
    //    target.draw(&vertices[0], vertices.size(), sf::Quads, states);
    // try 2
    //    for (unsigned int it = 0; it < vertices.size(); it++) {
    //        target.draw(&vertices[it][0], vertices.size(), sf::Quads, states);
    //    }
    // try 3
    for (unsigned int it = 0; it < vertices.size(); it++) {
        for (unsigned int it2 = 0; it2 < vertices.at(it).size(); it2++) {
            target.draw(&vertices[it][it2][0], 4, sf::Quads, states);
        }
    }
}
