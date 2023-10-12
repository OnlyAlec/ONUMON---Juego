#include <stdio.h>
#include <string.h>
#include <allegro.h>

int counter=0, objY=10;

int showODS (int);
void increment_counter() {
    counter++;
}
END_OF_FUNCTION(increment_counter)

int main(int argc, char const *argv[])
{
    // 1 - Arbol
    // 2 - Sol
    // 3 - Pez
    // 4 - Gota
    int pantalla = 2;
    showODS(pantalla);
    return 0;
}



int showODS (int input) {
    BITMAP *buffer;
    BITMAP *obj;
    BITMAP *bg, *bg_down, *bg_org, *bg_orgDown;

// TEMP
    allegro_init();
    install_mouse();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 880, 650, 0, 0);
    buffer = create_bitmap(880,700);
// ----------------------------------------------------------------
    install_int_ex(increment_counter, BPS_TO_TIMER(30));

    char srcBG[40] = "./src/bg_ods/obj_"; //.bmp
    char srcBGDown[40]  = "./src/bg_ods/obj_"; //Down.bmp
    char srcObj[40] = "./src/icons/"; //.bmp

    switch (input)
    {
    case 1:
        strcat(srcBG, "Arbol.bmp");
        strcat(srcBGDown, "ArbolDown.bmp");
        strcat(srcObj, "arbol.bmp");
        break;
    
    case 2:
        strcat(srcBG, "Sol.bmp");
        strcat(srcBGDown, "SolDown.bmp");
        strcat(srcObj, "sol.bmp");
        break;
    
    case 3:
        strcat(srcBG, "Pez.bmp");
        strcat(srcBGDown, "PezDown.bmp");
        strcat(srcObj, "pez.bmp");
        break;
    
    case 4:
        strcat(srcBG, "Gota.bmp");
        strcat(srcBGDown, "GotaDown.bmp");
        strcat(srcObj, "gota.bmp");
        break;
    }

    bg = load_bitmap(srcBG, NULL);
    bg_org = load_bitmap(srcBG, NULL);
    bg_down = load_bitmap(srcBGDown, NULL);
    bg_orgDown = load_bitmap(srcBGDown, NULL);
    obj = load_bitmap(srcObj, NULL);

    while (!key[KEY_ESC]) {
        counter = 0;

        while (counter / 30.0 <= 3) {
            if (counter / 30.0 <= 3 / 2.0) {
                objY = 100 - ((counter / 30.0) / (3 / 2.0) * 55);
            } else {
                objY = 100 - ((3 - (counter / 30.0)) / (3 / 2.0) * 55);
            }
            if(mouse_x > 705 && mouse_x < 831 && mouse_y > 548 && mouse_y < 599){
                draw_sprite(bg_down, obj, 300, objY);
                draw_sprite(screen, bg_down, 0, 0);
                draw_sprite(bg_down, bg_orgDown, 0, 0);
                
            } else {
                draw_sprite(bg, obj, 300, objY);
                draw_sprite(screen, bg, 0, 0);
                draw_sprite(bg, bg_org, 0, 0);
            }
            show_mouse(bg_org);
            rest(5);
        }
    }
    destroy_bitmap(obj);
    destroy_bitmap(bg);
    destroy_bitmap(bg_down);
    allegro_exit();
    return 0;
}
END_OF_MAIN ();
