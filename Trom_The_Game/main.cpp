//

// Disclaimer:

// ----------

//

// This code will work only if you selected window, graphics and audio.

//

// Note that the "Run Script" build phase will copy the required frameworks

// or dylibs to your application bundle so you can execute it on any OS X

// computer.

//

// Your resource files (images, sounds, fonts, ...) are also copied to your

// application bundle. To get the path to these resources, use the helper

// function `resourcePath()` from ResourcePath.hpp

//


#include <SFML/Audio.hpp>

#include <SFML/Graphics.hpp>

#include <fstream>
#include <sstream>

using namespace std;
using namespace sf;

// Resources

#include "ResourcePath.hpp"




const int W=800;

const int H=600;

int speed = 4;

bool field [W][H]={0};




struct player{
    
    int x,y,dir;
    
    Color color;
    
    player (Color c){
        
        
        
        x=rand() % W;
        
        y=rand() % H;
        
        color=c;
        
        dir=rand() % 4;
        
    }
    
    
    
    void tick(){
        
        
        
        if (dir==0) y += 1;
        
        if (dir==1) x -= 1;
        
        if (dir==2) x += 1;
        
        if (dir==3) y -= 1;
        
        
        
        if (x>=W) x=0; if (x<0) x=W-1;
        
        if (y>=H) y=0; if (y<0) y=H-1;
        
    }
    
    
    
    Vector3f getColor(){
        
        return Vector3f(color.r,color.g,color.b);
        
    }
    
};
/**
 -------------CODIGO NUEVO------------
 */

string toString(int n){
    stringstream s;
    s<<n;
    return s.str();
}

void registro(){
    RenderWindow app(VideoMode(800, 600), "Tron");
    // app.setFramerateLimit(60);
    Texture t;
    if (!t.loadFromFile(resourcePath() + "Background.jpg")) {
        return EXIT_FAILURE;
    }
    Sprite ft(t);
    Font fuente;
    if (!fuente.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    Text texto;
    String cadena;
    cadena="=======================\n   MIS REGISTROS       \n=======================\n";
    texto.setFont(fuente);
    texto.setCharacterSize(15);
    texto.setPosition(10,10);
    ifstream archivo("Registro.txt");
    string line;
    if(archivo.is_open()){
        while(getline(archivo,line)){
            cadena=cadena+line+"\n";
        }
    }
    
    archivo.close();
    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }
        texto.setString(cadena);
        app.clear();
        app.draw(ft);
        app.draw(texto);
        app.display();
    }
    
}

void escribir(string pal){
    ofstream fichero;
    fichero.open("Registro.txt",std::ios_base::app);
    fichero<<pal;
    fichero.close();
}


void game(){
    
    srand(time(0));
    
    
    
    RenderWindow window (VideoMode(W,H), "The Tron Game");
    
    window.setFramerateLimit(60);
    
    
    
    
    
    Texture texture;
    
    if (!texture.loadFromFile(resourcePath() + "Background.jpg")) {
        
        return EXIT_FAILURE;
        
    }
    
    
    Sprite sBackground(texture);
    
    
    
    player p1(Color::Red), p2(Color::Green);
    
    
    
    Sprite sprite;
    
    
    
    RenderTexture text;
    
    text.create(W, H);
    
    text.setSmooth(true);
    
    sprite.setTexture(text.getTexture());
    
    text.clear();
    
    text.draw(sBackground);
    
    
    
    Font font;
    
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        
        return EXIT_FAILURE;
        
    }
    
    Text tex ("You  Win!", font, 35);
    
    tex.setPosition(W/2-80,20);
    
    
    
    Shader* shader = new Shader;
    
    
    
    shader -> loadFromFile(resourcePath()+"shader.frag", Shader :: Fragment);
    
    shader -> setUniform("frag_ScreenResolution", Vector2f(W, H));
    
    shader -> setUniform("frag_LightAttenuation", 100);
    
    RenderStates states; states.shader = shader;
    
    
    
    bool Game=-1;
    
    
    
    while (window.isOpen()){
        
        
        
        Event eve;
        
        while (window.pollEvent(eve)){
            
            if(eve.type == Event::Closed)
                
                window.close();
            
        }
        
        
        
        if (Keyboard :: isKeyPressed(Keyboard :: Left)) if (p1.dir != 2) p1.dir = 1;
        
        if (Keyboard :: isKeyPressed(Keyboard :: Right)) if (p1.dir != 1) p1.dir = 2;
        
        if (Keyboard :: isKeyPressed(Keyboard :: Up)) if (p1.dir != 0) p1.dir = 3;
        
        if (Keyboard :: isKeyPressed(Keyboard :: Down)) if (p1.dir != 3) p1.dir = 0;
        
        
        
        if (Keyboard :: isKeyPressed(Keyboard :: A)) if (p2.dir != 2) p2.dir = 1;
        
        if (Keyboard :: isKeyPressed(Keyboard :: D)) if (p2.dir != 1) p2.dir = 2;
        
        if (Keyboard :: isKeyPressed(Keyboard :: W)) if (p2.dir != 0) p2.dir = 3;
        
        if (Keyboard :: isKeyPressed(Keyboard :: S)) if (p2.dir != 3) p2.dir = 0;
        
        
        
        if (!Game){
            
            
            
            window.draw(tex);
            
            window.display();
            
            continue;
            
        }
        
        //Ve
        
        for (int i=0; i<speed; i++) {
            
            
            
            p1.tick(); p2.tick();
            
            
            
            if (field [p1.x] [p1.y] == 1){
                
                
                
                Game = 0;
                
                
                
                tex.setFillColor(p2.color);
                escribir("\n\n GANADOR: Jugador1\t Score: 10 puntos");
                
            }
            
            if (field [p2.x] [p2.y] == 1){
                
                
                
                Game = 0;
                
                
                
                tex.setFillColor(p1.color);
                escribir("\n\n GANADOR: Jugador2\t Score: 10 puntos");
            }
            
            field [p1.x] [p1.y] = 1;
            
            field [p2.x] [p2.y] = 1;
            
            
            
            CircleShape cir(3);
            
            
            
            cir.setPosition(p1.x, p1.y); cir.setFillColor(p1.color); text.draw(cir);
            
            cir.setPosition(p2.x, p2.y); cir.setFillColor(p2.color); text.draw(cir);
            
            text.display();
            
            
            
            shader -> setUniform("frag_LightOrigin", Vector2f(p1.x, p1.y));
            
            shader -> setUniform ("frag_LightColor", p1.getColor());
            
            text.draw(sprite, states);
            
            shader -> setUniform("frag_LightOrigin", Vector2f(p2.x, p2.y));;
            
            text.draw(sprite, states);
            
            
            
        }
        
        
        
        /////// Draw the game ///////
        
        
        
        window.clear();
        
        window.draw(sprite);
        
        window.display();
        
    }
    
    
}


void instrucciones(){
    
    RenderWindow app(VideoMode(800,600),"How to play");
    
    app.setFramerateLimit(60);
    
    
    
    Texture t1;
    
    if (!t1.loadFromFile(resourcePath() + "Instructions.jpg")) {
        
        return EXIT_FAILURE;
        
    }
    
    Sprite sback(t1);
    
    while(app.isOpen()){
        
        Event e;
        
        while(app.pollEvent(e)){
            
            if(e.type==Event::Closed){
                
                app.close();
                
            }
            
        }
        
        app.clear();
        
        app.draw(sback);
        
        app.display();
        
        
        
    }
    
    
    
}

int main()

{
    
    // Create the main window
    
    
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tron The Game");
    
    
    
    
    
    
    
    
    
    
    
    // Set the Icon
    
    sf::Image icon;
    
    if (!icon.loadFromFile(resourcePath() + "icono.png")) {
        
        return EXIT_FAILURE;
        
    }
    
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    
    // Load a sprite to display
    
    sf::Texture texture;
    
    if (!texture.loadFromFile(resourcePath() + "Legacy.jpg")) {
        
        return EXIT_FAILURE;
        
    }
    
    sf::Sprite sprite(texture);
    
    
    // Create a graphical text to display
    
    sf::Font font;
    
    if (!font.loadFromFile(resourcePath() + "CHICORY_.TTF")) {
        
        return EXIT_FAILURE;
        
    }
    
    sf::Text text(" \n " " \n " " \n  " " \n Hello User : \n "" \n Welcome to The Tron Game \n "" \n Choose an option : \n \n \n  "" \n " " A- To play \n \n \n " " B- Guide \n \n \n " " S- Score \n \n " " C- Exit" , font, 18);
    
    text.setFillColor(sf::Color::White);
    
    
    
    
    
    
    
    
    
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
    
    //   sf::RenderWindow screen(sf::VideoMode(800, 600), "Tron The Game");
    
    
    
    
    
    //}
    
    
    
    //Play the game
    
    
    
    
    
    
    
    // Load a music to play
    
    sf::Music music;
    
    if (!music.openFromFile(resourcePath() + "Tron_main.ogg")) {
        
        return EXIT_FAILURE;
        
    }
    
    
    // Play the music
    
    music.play();
    
    
    // Start the game loop
    
    while (window.isOpen())
        
    {
        
        // Process events ======== DESDE AQUI ===========
        
        sf::Event event;
        
        while (window.pollEvent(event))
            
        {
            
            // Close window: exit
            
            if (event.type == sf::Event::Closed)
                
                window.close();
            
            
            
        }
        
        
        
        // Escape pressed: exit
        
        if (Keyboard::isKeyPressed(Keyboard::C)) {
            
            window.close();
            
        }
        
        else if (Keyboard::isKeyPressed(Keyboard::B)) {
            
            instrucciones();       
            
        }else if (Keyboard::isKeyPressed(Keyboard::A)) {
            
            game();
        }else if(Keyboard::isKeyPressed(Keyboard::S)){
            registro();
        }
        
        
        
    
    
    
    
    
    // Clear screen
    
    window.clear();
    
    
    
    
    
    
    // Draw the sprite
    
    window.draw(sprite);
    
    
    
    
    // Draw the string
    
    window.draw(text);
    
    
    // Update the window
    
    window.display();
    
    
    
}


return EXIT_SUCCESS;

}
