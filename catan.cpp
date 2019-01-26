

#include <nana/gui.hpp>

class cHexTile
{
public:
    cHexTile( float x, float y )
        : myX( x )
        , myY( y )
    {

    }

    void Draw( nana::paint::graphics& graph );

private:
    nana::color myColor;
    float myX;
    float myY;
};

class cHexBoard
{
public:
    cHexBoard( nana::form& fm, int size );
private:
    std::vector< cHexTile > myTile;
};

void cHexTile::Draw( nana::paint::graphics& graph )
{
    const int scale = 60;

    int x = myX*scale + scale;
    int y = myY*scale + scale;
    graph.line_begin( x,y );
    x += scale/3;
    y -= scale/2;
    graph.line_to( {x,y},nana::colors::black);
    x += scale/3;
    graph.line_to( {x,y});
    x += scale/3;
    y += scale/2;
    graph.line_to( {x,y});
    x -= scale/3;
    y += scale/2;
    graph.line_to( {x,y});
    x -= scale/3;
    graph.line_to( {x,y});
    x -= scale/3;
    y -= scale/2;
    graph.line_to( {x,y});
}

cHexBoard::cHexBoard( nana::form& fm, int size )
{
    int tileCount = size;
    for( int rowCount=size-1; rowCount != 2; rowCount-- )
    {
        tileCount += 2 * rowCount;
    }
    float x = 0;
    float y = 2;
    for( int t = 0; t < tileCount; t++ )
    {
        if( t < 3 )
            x = 0;
        else if( t < 7 )
            x = .67;
        else if( t < 12 )
            x = 2 * .67;
        else if( t < 16 )
            x = 3 * .67;
        else
            x = 4 * .67;
        if( t == 0 || t == 16 )
            y = 1;
        else if( t == 3 || t == 12 )
            y = 0.5;
        else if( t == 7 )
            y = 0;
        else
            y += 1;

        myTile.push_back( cHexTile( x, y ) );
    }

    nana::drawing dw{fm};
    dw.draw([this](nana::paint::graphics& graph)
    {
        for( auto& t : myTile )
        {
            t.Draw( graph );
        }
    });
}

int main()
{
    // construct application form
    nana::form fm( nana::rectangle( 100,100, 300, 400 ));

    cHexBoard Board( fm, 5 );

    // show & run
    fm.show();
    nana::exec();

}
