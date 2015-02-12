#include "ksTextLog.h"
#include <iostream>

ksTextLog::ksTextLog( std::string font_file )
	: m_font_file( font_file ), m_current( 0 ), m_frame_count( 0 ), m_active( false ),
	  m_coord_x( 0.f ), m_coord_y( 0.f )
{
	m_array.setPrimitiveType( sf::Quads );
	m_array.resize( 4 );

	m_array[ 0 ].position = getPosition();
	m_array[ 1 ].position = sf::Vector2f( getPosition().x + 480, getPosition().y );
	m_array[ 2 ].position = sf::Vector2f( getPosition().x + 480, getPosition().y + 128 );
	m_array[ 3 ].position = sf::Vector2f( getPosition().x, getPosition().y + 128 );

	m_array[ 0 ].color = sf::Color( 0, 0, 0, 120 );
	m_array[ 1 ].color = sf::Color( 0, 0, 0, 120 );
	m_array[ 2 ].color = sf::Color( 0, 0, 0, 120 );
	m_array[ 3 ].color = sf::Color( 0, 0, 0, 120 );

	m_text_lines[ NUM_LINES ].setText( m_font_file, "Press {ENTER} to continue.", getPosition().x, 
										 ( NUM_LINES * 16 ) + getPosition().y, sf::Color::White );
}

void ksTextLog::insert( std::string line, sf::Color color )
{
	if ( m_current < NUM_LINES )
	{
		m_text_lines[ m_current ].setText( m_font_file, line, getPosition().x, 
										 ( m_current * 16 ) + getPosition().y, color );
		m_current++;
	}
	else
	{
		for ( int count = 0; count < NUM_LINES - 1; count++ )
		{
			m_text_lines[ count ].setText( m_font_file, m_text_lines[ count + 1 ].getText(),
										   getPosition().x, ( count * 16 ) + getPosition().y,
										   m_text_lines[ count + 1 ].getColor() );
			//m_text_lines[ count ].setText( m_text_lines[ count + 1 ] );
		}

		m_text_lines[ NUM_LINES - 1 ].setText( m_font_file, line, getPosition().x, 
											   ( ( NUM_LINES - 1 ) * 16 ) + getPosition().y, color );
	}

	for ( int count = 0; count < 4; count++ )
		m_array[ count ].color = sf::Color( 0, 0, 0, 120 );

	m_text_lines[ NUM_LINES ].setColor( m_text_lines[ NUM_LINES ].red, 
										m_text_lines[ NUM_LINES ].green,
										m_text_lines[ NUM_LINES ].blue, 255 );
}

void ksTextLog::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	target.draw( m_array, states );
}

void ksTextLog::drawLog( sf::RenderWindow & app )
{
	app.draw( *this );

	for ( int count = 0; count < NUM_LINES + 1; count++ )
		app.draw( m_text_lines[ count ] );

		// for ( int count = 0; count < NUM_LINES; count++ )
		//		app.draw( m_text_lines[ count ] );
}

void ksTextLog::update( bool & dialog_focus, int frame_time )
{
	if ( m_current > 0 && m_active )
	{
		float temp = ( (float) frame_time - (float) m_frame_count ) / (float) frame_time;
		
		if ( m_frame_count < frame_time )
		{
			for ( int count = 0; count < m_current; count++ )
			{
				m_text_lines[ count ].setColor( m_text_lines[ count ].red, 
												m_text_lines[ count ].green, 
												m_text_lines[ count ].blue, temp * 255 );

				for ( int count = 0; count < 4; count++ )
					m_array[ count ].color = sf::Color( 0, 0, 0, 120 * temp );
			}

			m_text_lines[ NUM_LINES ].setColor( m_text_lines[ NUM_LINES ].red, 
												m_text_lines[ NUM_LINES ].green, 
												m_text_lines[ NUM_LINES ].blue, temp * 255 );

			m_frame_count++;
		}
		else
		{
			m_current = 0;
			m_frame_count = 0;
			m_active = false;
			dialog_focus = false;

			setLogPosition( 0, 0 );
		}
	}
}

void ksTextLog::activate()
{
	if ( m_current > 0 )
		m_active = true;
}

void ksTextLog::clear()
{
	for ( int count = 0; count < m_current; count++ )
		m_text_lines[ count ].setColor( 0, 0, 0, 0 );

	m_current = 0;
	m_frame_count = 0;
	m_active = false;
}

void ksTextLog::moveLog( float x, float y )
{
	m_coord_x += x;
	m_coord_y += y;

	setLogPosition( m_coord_x, m_coord_y );
}

void ksTextLog::setLogPosition( float x, float y )
{
	m_coord_x = x;
	m_coord_y = y;

	m_text_lines[ NUM_LINES ].setPosition( x, y );

	//for ( int count = 0; count < NUM_LINES; count++ )
	//	m_text_lines[ count ].setPosition( x, y );

	setPosition( x, y );
}