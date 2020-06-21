//
// Created by Adam on 16.06.2020.
//

#ifndef GENERIC_GIERKA_TILEMAP_H
#define GENERIC_GIERKA_TILEMAP_H


class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::vector<std::vector<std::vector<sf::Vertex>>> vertices;
    sf::Texture m_tileset;
    std::vector<std::vector<std::vector<int>>> hello;
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<std::vector<int>>>* tiles, unsigned int width, unsigned int height, unsigned int layer);

};

#endif //GENERIC_GIERKA_TILEMAP_H
