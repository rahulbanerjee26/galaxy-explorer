#include <galaxy-explorer/GameAI.hpp>
#include <galaxy-explorer/MyAIData.hpp>

#include <SFML/Graphics.hpp>
/* Variable to check the direction of rotation
 * true => clockwise and false => anticlockwise
 * At start, phasor is rotating clockwise
 */
bool rotateDirection = true; 

GameAI::GameAI(const GameInfo& game_info, sf::RenderTarget* debug_rt)
{
	this->debug_rt = debug_rt;
	this->game_info = game_info;
	this->asteroid_observer = AsteroidsObserver(this);
	this->my_game_ai = new MyAIData();

	// customState().debug_on = false;
}

GameAI::~GameAI() {
	delete my_game_ai;
}

SuggestedAction GameAI::suggestAction(const ShipState& ship_state) {
	debug_rt->clear(sf::Color::Transparent);

	if (customState().debug_on) {
		if (not asteroidsObserver().asteroids().isEmpty()) {
			const sf::IntRect first_ast_hb = asteroidsObserver().asteroids().front().getCurrentHitbox();
			sf::RectangleShape ast_rect(sf::Vector2f(first_ast_hb.width, first_ast_hb.height));
			ast_rect.setPosition(first_ast_hb.left, first_ast_hb.top);
			ast_rect.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
			ast_rect.setOutlineColor(sf::Color::Yellow);
			ast_rect.setFillColor(sf::Color::Transparent);
			debug_rt->draw(ast_rect);
		}
	}
        /* After testing out different bounds , 38 degrees had the best avg score
         */
        /* Left Bound is -38 degrees
         */
        if(ship_state.millidegree_rotation >= 38000 && rotateDirection ){
            rotateDirection = false;
            return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
        }
        /* Right Bound is 38 degrees
         */
        else if (ship_state.millidegree_rotation <= -38000 && !rotateDirection){
            rotateDirection = true;
            return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
        }
        else if(rotateDirection)
             return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
        else if (!rotateDirection)
            return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
        else
            return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
        
}
