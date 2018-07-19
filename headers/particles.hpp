#ifndef particles_hpp
#define particles_hpp

#include <SFML/Graphics.hpp>
#include <cmath>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    ParticleSystem(unsigned int count);
    void resize(unsigned int count);
    void setEmitter(sf::Vector2f position);
    void update(sf::Time elapsed);
    void reset();
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void resetParticle(std::size_t index);
    struct Particle{
        sf::Vector2f velocity;
        sf::Time lifetime;
    };
    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
    sf::Color couleur;
};

#endif /* particles_hpp */
