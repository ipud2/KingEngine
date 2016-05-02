/********************************************************
* Class:            ksLightSystem
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksLightSystem.h
*
*   Overview:
*       Class that contains the system for lighting and
*       shadows in the KingEngine. The lighting is 
*       calculated based on a reference to the game world 
*       that contains the required 3D transformation
*       methods.
*
********************************************************/

#ifndef KS_LIGHT_SYSTEM_H

#include <SFML/Graphics.hpp>
#include "ksWorld.h"

class ksLightSystem : public sf::Drawable, public sf::Transformable
{
    public:
        //                       Constructors
        ksLightSystem(ksWorld * world, sf::Color light_base_color, sf::Color dark_base_color);
            
        //                       Methods
        void                     draw(sf::RenderTarget & target, sf::RenderStates states) const;
        
    private:
        //                       Members
        ksWorld *                m_world;
        sf::Color                m_light_base_color;
        sf::Color                m_dark_base_color;
        sf::VertexArray          m_array;
};

#endif