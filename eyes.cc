/* Eyes
 * Copyright (C) 2011  Krzysztof Mędrzycki, Damian Chiliński
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "eyes.hxx"

#include <debug.hxx>

#include <QPainter>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define MM_NO_MOTION 10000
#define DEF_THEME "draw"

static char   folder[]    = "./pics/";
static char * files[]     = {
    "bul_01_a", "bul_01_m", "bul_01_o", "bul_01_s",                 //4
    "bul_02_a", "bul_02_m", "bul_02_o", "bul_02_s",                 //8
    "bul_03_a", "bul_03_m", "bul_03_o", "bul_03_s",                 //12
    "bul_04_a", "bul_04_m", "bul_04_o", "bul_04_s",                 //16
    "bul_05_a", "bul_05_m", "bul_05_o", "bul_05_s",                 //20
    "bul_06_a", "bul_06_m", "bul_06_o", "bul_06_s",                 //24
    "bul_07_a", "bul_07_m", "bul_07_o", "bul_07_s",                 //28
    "bul_08_a", "bul_08_m", "bul_08_o", "bul_08_s",                 //32
    "bul_09_a", "bul_09_m", "bul_09_o", "bul_09_s",                 //36
    "bul_10_a", "bul_10_m", "bul_10_o", "bul_10_s",                 //40
    "bul_11_a", "bul_11_m", "bul_11_o", "bul_11_s",                 //44
    "bul_12_a", "bul_12_m", "bul_12_o", "bul_12_s",                 //48
    "bul_13_a", "bul_13_m", "bul_13_o", "bul_13_s",                 //52
    "bul_14_a", "bul_14_m", "bul_14_o", "bul_14_s",                 //56
    "bul_15_a", "bul_15_m", "bul_15_o", "bul_15_s",                 //60
    "bul_16_a", "bul_16_m", "bul_16_o", "bul_16_s",                 //64
    "clap_01_a", "clap_01_m", "clap_01_o", "clap_01_s",             //68
    "clap_02_a", "clap_02_m", "clap_02_o", "clap_02_s",             //72
    "clap_03_a", "clap_03_m", "clap_03_o", "clap_03_s",             //76
    "clap_04_a", "clap_04_m", "clap_04_o", "clap_04_s",             //80
    "clap_05_a", "clap_05_m", "clap_05_o", "clap_05_s",             //84
    "cusual_01_a", "cusual_01_m", "cusual_01_o", "cusual_01_s",     //88
    "sh_01_a", "sh_01_m", "sh_01_o", "sh_01_s",                     //92
    "sh_02_a", "sh_02_m", "sh_02_o", "sh_02_s",                     //96
    "slp_01_a", "slp_01_m", "slp_01_o", "slp_01_s",                 //100
    "slp_02_a", "slp_02_m", "slp_02_o", "slp_02_s",                 //104
    "slp_03_a", "slp_03_m", "slp_03_o", "slp_03_s",                 //108
    "slp_04_a", "slp_04_m", "slp_04_o", "slp_04_s",                 //112
    "slp_05_a", "slp_05_m", "slp_05_o", "slp_05_s",                 //116
    "slp_06_a", "slp_06_m", "slp_06_o", "slp_06_s",                 //120
    "slp_07_a", "slp_07_m", "slp_07_o", "slp_07_s",                 //124
    "slp_08_a", "slp_08_m", "slp_08_o", "slp_08_s",                 //128
    "slp_09_a", "slp_09_m", "slp_09_o", "slp_09_s",                 //132
    "slp_10_a", "slp_10_m", "slp_10_o", "slp_10_s",                 //136
    "hpp_01_a", "hpp_01_m", "hpp_01_o", "hpp_01_s",
    "hpp_02_a", "hpp_02_m", "hpp_02_o", "hpp_02_s",
    "hpp_03_a", "hpp_03_m", "hpp_03_o", "hpp_03_s",
    "hpp_04_a", "hpp_04_m", "hpp_04_o", "hpp_04_s",
    "hpp_05_a", "hpp_05_m", "hpp_05_o", "hpp_05_s",
    "hpp_06_a", "hpp_06_m", "hpp_06_o", "hpp_06_s",
    "hpp_07_a", "hpp_07_m", "hpp_07_o", "hpp_07_s",
    "bclap_01_a", "bclap_01_m", "bclap_01_o", "bclap_01_s",
    "bclap_02_a", "bclap_02_m", "bclap_02_o", "bclap_02_s",
    "bclap_03_a", "bclap_03_m", "bclap_03_o", "bclap_03_s",
    "bclap_04_a", "bclap_04_m", "bclap_04_o", "bclap_04_s",
    "bclap_05_a", "bclap_05_m", "bclap_05_o", "bclap_05_s",
    "bclap_06_a", "bclap_06_m", "bclap_06_o", "bclap_06_s",
    "bhclap_01_a", "bhclap_01_m", "bhclap_01_o", "bhclap_01_s",
    "bhclap_02_a", "bhclap_02_m", "bhclap_02_o", "bhclap_02_s",
    "bhclap_03_a", "bhclap_03_m", "bhclap_03_o", "bhclap_03_s",
    "bhclap_04_a", "bhclap_04_m", "bhclap_04_o", "bhclap_04_s",
    "bhclap_05_a", "bhclap_05_m", "bhclap_05_o", "bhclap_05_s",
    "bhclap_06_a", "bhclap_06_m", "bhclap_06_o", "bhclap_06_s",
    "tired_01", "tired_02", "tired_03",                             //139
    "spec"                                                          //140
};
static char * eyefiles[]  = {
    "eye_01", "eye_02", "eye_03", "eye_04", "eye_05",   // 5
    "eye_06", "eye_07", "eye_08", "eye_09", "eye_10",
    "blank"    // 10
};

const double versiond = 0.080001;
const char *verstr = "0.8 alpha";

void core_main ();
bool is_finished;
bool images_ready;

QString get_face_suffix ( QString face )
{
    Config cfg;
    try
    {
        cfg.readFile ( "colors.cfg" );
    }
    catch ( libconfig::ParseException e )
    {
        cerr << "Error while parsing configuration file.\n"
              << e.what () << '\n'
              << e.getFile () << '\n'
              << e.getLine () << '\n'
              << e.getError () << '\n';
        return QString ( "_g" );
    }
    std::string ret;
    if ( not cfg.lookupValue ( ( QString ( "colors." ) + face + ".suffix" ).toStdString (), ret ) )
    {
        cfg.lookupValue ( "colors.default", ret );
        if ( not cfg.lookupValue ( ( QString ( "colors." ) + ret.c_str () + ".suffix" ).toStdString (), ret ) )
            return QString ( "_g" );
    }
    return QString ( ret.c_str () );
}

eyes_view::eyes_view ( QWidget * parent, QString ncolor ) : QWidget ( parent )
{
    info << "(eyes) preparing...\n";
    layers = new _layer[NUM_LAYERS];
    px = MM_NO_MOTION;
    px = MM_NO_MOTION;
    epx1 = 46;
    epx2 = 213;
    mpx1 = 83;
    mpx2 = 252;
    epy = 10;
    mpy = 24;
    win = parent;
    spec = "spec";
    eye = "blank";
    face = "slp_10";
    face_next = "slp_10";
    // loading configuration
    info << "(eyes) loading config...\n";
    Configuration * cfg = Configuration::getInstance ();
    string scolor;
    scolor = cfg->lookupValue ( "ui.color", "green" );
    eye_s = cfg->lookupValue ( "ui.eye.size", 60 );
    eye_m = cfg->lookupValue ( "ui.eye.mirror", 9 );
    if ( ( color = get_face_suffix ( ncolor ) ) == "NIL" )
        color = get_face_suffix ( QString ( scolor.c_str () ) );
    theme = cfg->lookupValue ( "ui.theme", DEF_THEME );
    is_finished = false;
    images_ready = false;
    // initializing submodules
    info << "(eyes) initializing submodules...\n";
    time = QTime::currentTime ();
    qsrand ( (uint)time.msec () );
    setMinimumSize ( eyes_w, eyes_h );
    setMaximumSize ( eyes_w, eyes_h );
    clapper = new eyes_clapper ( this );
    looker = new eyes_looker ( this );
    core = new Core ( this );
    open_images ( color );
    set_layer ( SLEEPY, "tired_03" );
    toggle_layer ( SLEEPY, true );
    core->load_config ();
    area = new QPixmap ( eyes_w, eyes_h );
    clapper->run ();
    looker->run ();
    core->run ();
}

eyes_view::~eyes_view ()
{
    info << "(eyes) destroying eyes.\n";
}

void _som ( int i, int max )
{
    static int prew = 0;
    i ++;
    max;
    cerr << "\033[" << prew << "D";
    std::ostringstream ss;
    ss << '[' << i << '/' << max << ']';
    string s = ss.str ();
    if ( i > max )
        cerr << "done        \n";
    else
        cerr << s;
    prew = s.length ();
}

void eyes_view::open_images ( QString color )
{
    QPixmap * file ;
    info << "(eyes) loading images...  ";
    bool no_file ( false );
    for ( int i=0 ; i<216 ; i++ )
    {
        _som ( i, 216 );
        file = new QPixmap ();
        file->load ( QString ( folder ) + files[i] + ".png" );
        if ( file->isNull () )
        {
            cerr << '\n';
            error << "(eyes) file " << ( QString ( folder ) + files[i] + ".png" ).toStdString () << " is nil.\n";
            no_file = true;
            break;
        }
        else
        {
            pics.insert ( QString ( files[i] ), file->scaled ( eyes_w, eyes_h, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation ) );
            std::cout;
        }
        delete file;
    }
    _som ( 217, 216 );
    if ( no_file )
    {
        c_main.cancel ();
        exit ( 2 );
    }
    info << "(eyes) loading images...    ";
    for ( int i=0 ; i<10 ; i++ )
    {
        _som ( i, 10 );
        file = new QPixmap ();
        file->load ( QString ( folder ) + eyefiles[i] + color + ".png" );
        if ( file->isNull () )
        {
            cerr << '\n';
            error << "(eyes) file " << ( QString ( folder ) + eyefiles[i] + color + ".png" ).toStdString () << " is nil.\n";
            no_file = true;
            break;
        }
        else
        {
            eyes.insert ( QString ( eyefiles[i] ), file->copy () );
        }
        delete file;
    }
    _som ( 11, 10 );
    if ( no_file )
    {
        c_main.cancel ();
        exit ( 2 );
    }
    images_ready = true;
}

void eyes_view::paintEvent ( QPaintEvent * event )
{
    QPainter paint ( this );
    QPainter parea ( area );
    area->fill ( QColor ( 0, 0, 0 ) );
    parea.drawPixmap ( 0, 0, eyes_w, eyes_h, pics[face+"_a"] );
    parea.drawPixmap ( epx1, epy, eye_s, eye_s, eyes[eye] );
    parea.drawPixmap ( epx2, epy, eye_s, eye_s, eyes[eye] );
    parea.drawPixmap ( 0, 0, eyes_w, eyes_h, pics[face+"_s"] );
    parea.drawPixmap ( int(mpx1), int(mpy), eye_m, eye_m, pics[spec] );
    parea.drawPixmap ( int(mpx2), int(mpy), eye_m, eye_m, pics[spec] );
    parea.drawPixmap ( 0, 0, eyes_w, eyes_h, pics[face+"_m"] );
    parea.drawPixmap ( 0, 0, eyes_w, eyes_h, pics[face+"_o"] );
    for ( int i=0 ; i<NUM_LAYERS ; i++ )
    {
        if ( layers[i].drawable )
            parea.drawPixmap ( 0, 0, eyes_w, eyes_h, pics[layers[i].face] );
    }
    parea.end ();
    area->setMask ( pics[face+"_a"].mask () );
    paint.drawPixmap ( 0, 0, eyes_w, eyes_h, *area );
}

void eyes_view::mousePressEvent ( QMouseEvent * ev )
{
    ev->ignore ();
}

void eyes_view::mouseMoveEvent ( QMouseEvent * ev )
{
    ev->accept ();
    if ( px == MM_NO_MOTION or py == MM_NO_MOTION )
    {
        px = ev->x ();
        py = ev->y ();
        return;
    }
    int dx = ( ( px > ev->x () ? -1 : 1 ) * px ) + ev->x ();
    int dy = ( ( py > ev->y () ? -1 : 1 ) * py ) + ev->y ();
    win->move ( 10, 10 );
    repaint ();
}

void eyes_view::closeEvent ( QCloseEvent * ev )
{
    info << "(eyes) close event recived, exiting...\n";
    ev->accept ();
    is_finished = true;
    c_main.waitForFinished ();
    cout << "\033[0m";
}

void eyes_view::set_face ( QString nface )
{
    if ( not pics.contains ( nface+"_a" ) )
    {
        warning << "(eyes) setting face to " << nface.toStdString () << " but it not exists.\n";
        return;
    }
    face = nface;
}

void eyes_view::set_eyes ( QString neyes )
{
    eye = neyes;
}

void eyes_view::set_eyes_position ( int nx1, int nx2, int ny )
{
    epx1 = nx1;
    epx2 = nx2;
    epy = ny;
}

void eyes_view::set_mirror_position ( double nx1, double nx2, double ny )
{
    mpx1 = nx1;
    mpx2 = nx2;
    mpy = ny;
}

void eyes_view::set_animation ( QString start, QString end, int from, int to )
{
    clapper->set_animation ( start, end, from ,to );
}

void eyes_view::set_layer ( Layers layer, QString face )
{
    layers[layer].face = face;
}

void eyes_view::toggle_layer ( Layers layer, bool onoff )
{
    layers[layer].drawable = onoff;
}

int eyes_view::heightForWidth ( int w ) const
{
    return ( eyes_h );
}

QVariant eyes_view::inputMethodQuery ( Qt::InputMethodQuery query ) const
{
    return ( nil );
}

QSize eyes_view::sizeHint () const
{
    return ( QSize ( eyes_w, eyes_h ) );
}

QString eyes_view::get_face ()
{
    return ( face );
}

QString eyes_view::get_face_next ()
{
    return ( face_next );
}