// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	srand(time(0));
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;
	bool start = false;
	bool noRepeat = false;
	int prevIndex = -1;

	// Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-C.ttf"))
        return EXIT_FAILURE;

	sf::Text text("Hello SFML", font, 50);
	string status = (noRepeat ? "On" : "Off");
	string prompt = "Place any number of vertices, hit enter, and place your last point\nNo repeat (N): " + status;
	// set the string to display
	text.setString(prompt);

	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

	// set the color
	text.setFillColor(sf::Color::White);

	// set the text style
	text.setStyle(sf::Text::Bold);

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			status = (noRepeat ? "On" : "Off");
			prompt = "Place any number of vertices, hit enter, and place your last point\nNo repeat (N): " + status;
			text.setString(prompt);
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				start = true;
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Key::N)
				{
					noRepeat = !noRepeat;
					cout << "No Repeat: (N)" << noRepeat << endl;
				}
			}
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					if (vertices.size() < 3 || !start)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					/*else if (points.size() == 0)
					{*/
					///fourth click
					///push back to points vector
					//points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					//}
					if (start)
					{
						///fourth click
						///push back to points vector
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0)
		{
			///generate more point(s)
			///select random vertex
			///calculate midpoint between random vertex and the last point in the vector
			///push back the newly generated coord.
			int index = -2;
			while ((index == prevIndex && noRepeat) || index < 0)
			{
				index = (rand() % vertices.size());
			}
			prevIndex = index;
			Vector2f vertex = vertices[index];
			Vector2f lastPoint = points[points.size() - 1];
			Vector2f midpoint((vertex.x + lastPoint.x) / 2, (vertex.y + lastPoint.y) / 2);
			points.push_back(midpoint);
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(10, 10));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Blue);
			window.draw(rect);
		}
		for (int i = 0; i < points.size(); i++)
		{
			RectangleShape rect(Vector2f(5, 5));
			rect.setPosition(Vector2f(points[i].x, points[i].y));
			rect.setFillColor(Color::Red);
			window.draw(rect);
		}
		

	// inside the main loop, between window.clear() and window.display()
	window.draw(text);

		window.display();
	}
}
