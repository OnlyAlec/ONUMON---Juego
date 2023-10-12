#include <allegro.h>
#include <allegro/sound.h>
#include <allegro/digi.h>
#include <allegro/midi.h>
//CREADORES ALEXA RIOS REINA, ALEJANDRO ZARATE RUBIO, PAULINA HERNÁNDEZ SOTO

int counter=0;

void increment_counter() {
    counter++;
}

struct elemento{
    BITMAP *imagen;
    int coordX;
    int coordY;
    int alto;
    int largo;
};typedef struct elemento E;

void pintarElemento(E,BITMAP*);
void jugar(E,BITMAP*,BITMAP*,BITMAP*,E[4],E[4],SAMPLE*);
void inicializarODS(E[4],E[4]);
void pintarODSyMarcador(E[4],BITMAP*,E[4],int);
int showODS (int,SAMPLE*);

int main ()
{
    int band=0;
    allegro_init();
    install_mouse();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 880, 650, 0, 0);
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "");
    set_window_title("ONUMON");
    BITMAP *buffer;
    BITMAP *background;
    BITMAP *play;
    BITMAP *quit;
    BITMAP *puntero;
    BITMAP *back2;
    BITMAP *capi;
    BITMAP *back2Org;
    SAMPLE *select = load_wav("multimedia//sonidos//select.wav");
    SAMPLE *ost = load_wav("multimedia//sonidos//ost.wav");
    buffer = create_bitmap(880,700);
    background = load_bitmap("multimedia//imagenes//main.bmp",NULL);
    play = load_bitmap("multimedia//imagenes//Main_Play.bmp",NULL);
    quit = load_bitmap("multimedia//imagenes//Main_Exit.bmp",NULL);
    puntero = load_bitmap("multimedia//imagenes//dedo.bmp",NULL);
    back2 = load_bitmap("multimedia//imagenes//fondo3.bmp",NULL);
    back2Org = load_bitmap("multimedia//imagenes//fondo3.bmp",NULL);
    capi = load_bitmap("multimedia//imagenes//capi.bmp",NULL);

    int menu=0, saliropcion;
    E capibara, ODS[4],ODSBLACK[4];
    capibara.imagen=capi;
    capibara.alto=32;
    capibara.largo=37;
    capibara.coordX=10;
    capibara.coordY=240;
    inicializarODS(ODS,ODSBLACK);
    play_sample(ost,100,127,1000,10);
    do{
    switch(menu){
        //---------------------MENU PRINCIPAL-------------------------------------------------
        case 0: saliropcion=0;
        do{
        if(mouse_x > 135 && mouse_x < 257 && mouse_y > 505 && mouse_y < 605)
        {
            draw_sprite(buffer,play,0,0);
            if(mouse_b&1)
            {
                play_sample(select,140,127,1000,0);
                menu=1;
                saliropcion=1;
                mouse_b = 0;
                rest(60);
            }
        }else if(mouse_x > 610 && mouse_x < 731 && mouse_y > 505 && mouse_y < 605){
            draw_sprite(buffer,quit,0,0);
            if(mouse_b & 1)
            {
                play_sample(select,150,127,2500,0);
                menu=3;
                saliropcion=1;
                mouse_b = 0;
            }
        }else{
            draw_sprite(buffer,background,0,0);
        }
        masked_blit(puntero,buffer,0,0,mouse_x,mouse_y,60,70);
        blit(buffer,screen,0,0,0,0,880,700);
        }while(saliropcion==0);
        break;
        //----------JUEGO------------------------------------------------------------

        case 1: jugar(capibara,back2,back2Org,buffer,ODS,ODSBLACK,select);
        menu=0;
        break;
        //----------------------------------------------------------------------
    }

    }while(menu!=3);

    return 0;
}

END_OF_MAIN ();


void pintarElemento(E elemento, BITMAP *buffer){
    masked_blit(elemento.imagen,buffer,0,0,elemento.coordX,elemento.coordY,elemento.largo,elemento.alto);
}

void inicializarODS(E ODS[4], E ODSBLACK[4]){
    ODS[0].imagen = load_bitmap("multimedia//imagenes//gota color.bmp",NULL);
    ODS[0].alto = 43;
    ODS[0].largo = 36;
    ODS[0].coordX=163;
    ODS[0].coordY=251;
    ODS[1].imagen = load_bitmap("multimedia//imagenes//arbol color.bmp",NULL);
    ODS[1].alto = 45;
    ODS[1].largo = 42;
    ODS[1].coordX=325;
    ODS[1].coordY=205;
    ODS[2].imagen = load_bitmap("multimedia//imagenes//sol color.bmp",NULL);
    ODS[2].alto = 40;
    ODS[2].largo = 40;
    ODS[2].coordX=483;
    ODS[2].coordY=279;
    ODS[3].imagen = load_bitmap("multimedia//imagenes//pez a color.bmp",NULL);
    ODS[3].alto = 40;
    ODS[3].largo = 54;
    ODS[3].coordX=664;
    ODS[3].coordY=157;

    ODSBLACK[0].imagen = load_bitmap("multimedia//imagenes//gota negra.bmp",NULL);
    ODSBLACK[0].alto = 47;
    ODSBLACK[0].largo = 36;
    ODSBLACK[0].coordX=669;
    ODSBLACK[0].coordY=594;
    ODSBLACK[1].imagen = load_bitmap("multimedia//imagenes//arbol negro.bmp",NULL);
    ODSBLACK[1].alto = 45;
    ODSBLACK[1].largo = 42;
    ODSBLACK[1].coordX=716;
    ODSBLACK[1].coordY=594;
    ODSBLACK[2].imagen = load_bitmap("multimedia//imagenes//sol negro.bmp",NULL);
    ODSBLACK[2].alto = 40;
    ODSBLACK[2].largo = 40;
    ODSBLACK[2].coordX=763;
    ODSBLACK[2].coordY=594;
    ODSBLACK[3].imagen = load_bitmap("multimedia//imagenes//pez negro.bmp",NULL);
    ODSBLACK[3].alto = 36;
    ODSBLACK[3].largo = 54;
    ODSBLACK[3].coordX=806;
    ODSBLACK[3].coordY=594;
}

void jugar(E capibara,BITMAP *back2, BITMAP *back2Org, BITMAP *buffer,E ODS[4],E ODSBLACK[4],SAMPLE *select){
    int bandcayendo=1,bandNotpressed=1,colision=0,i,j,cantods=0;
    SAMPLE *tubo = load_wav("multimedia//sonidos//tubo.wav");
    SAMPLE *salto = load_wav("multimedia//sonidos//salto.wav");
    SAMPLE *recolectar = load_wav("multimedia//sonidos//recolectar.wav");
    SAMPLE *end = load_wav("multimedia//sonidos//end.wav");
    do{
            if(bandcayendo==0){
                play_sample(salto,80,127,2000,0);
                for(i=1;i<4;i++)
                {
                    if(colisiontubos(capibara)==1){
                        colision = 1;
                        play_sample(tubo,100,127,1000,0);
                    }else{
                    if(capibara.coordX+capibara.largo<880 ){
                     capibara.coordX += i+2;
                    }
                    if(capibara.coordX+capibara.largo<880 ){
                    capibara.coordY -= ((i+2)*(i+1));
                    }
                    colisionODS(capibara,&cantods,select,recolectar);
                    pintarODSyMarcador(ODS,back2,ODSBLACK,cantods);
                    pintarElemento(capibara,back2);
                    draw_sprite(buffer,back2,0,0);
                    blit(buffer,screen,0,0,0,0,880,700);
                    blit(back2Org,back2,0,0,0,0,880,700);
                    }
                }
                bandcayendo = 1;
            }else{
                if(key[KEY_SPACE] && bandNotpressed==1){
                    clear_keybuf();
                    bandcayendo=0;
                    bandNotpressed=0;
                }
                if(!key[KEY_SPACE] && bandNotpressed==0){
                    bandNotpressed=1;
                }
                if(colisiontubos(capibara)==1){
                    colision=1;
                    play_sample(tubo,100,127,1000,0);
                }else{
                    if(capibara.coordX+capibara.largo>880 || capibara.coordY+capibara.alto>550){
                        colision = 1;
                    }
                    capibara.coordX +=3;
                    capibara.coordY +=3;
                    colisionODS(capibara,&cantods,select,recolectar);
                    pintarODSyMarcador(ODS,back2,ODSBLACK,cantods);
                    pintarElemento(capibara,back2);
                    draw_sprite(buffer,back2,0,0);
                    blit(buffer,screen,0,0,0,0,880,700);
                    blit(back2Org,back2,0,0,0,0,880,700);
                }
            }
            rest(27);
        }while(!key[KEY_ESC] && colision!=1);
        clear_keybuf();
        play_sample(end,100,127,1000,0);
        rest(100);
}

int colisiontubos(E capibara){
    //LINEA 1-------------------------------------
    if((capibara.coordX+capibara.largo>= 136 && capibara.coordX<= 225) && capibara.coordY<=179)
    {
        return 1;
    }
    if((capibara.coordX+capibara.largo>= 136 && capibara.coordX<= 225) && capibara.coordY+capibara.alto>=365)
    {
        return 1;
    }
    //LINEA 2-------------------------------------
    if((capibara.coordX+capibara.largo>= 302 && capibara.coordX<= 391) && capibara.coordY<=170)
    {
        return 1;
    }
    if((capibara.coordX+capibara.largo>= 302 && capibara.coordX<= 391) && capibara.coordY+capibara.alto>=280)
    {
        return 1;
    }
    //LINEA 3-------------------------------------
    if((capibara.coordX+capibara.largo>= 460 && capibara.coordX<= 548) && capibara.coordY<=250)
    {
        return 1;
    }
    if((capibara.coordX+capibara.largo>= 460 && capibara.coordX<= 548) && capibara.coordY+capibara.alto>=340)
    {
        return 1;
    }
    //LINEA 4-------------------------------------
      if((capibara.coordX+capibara.largo>= 648 && capibara.coordX<= 735) && capibara.coordY<=112)
    {
        return 1;
    }
    if((capibara.coordX+capibara.largo>= 648 && capibara.coordX<= 735) && capibara.coordY+capibara.alto>=235)
    {
        return 1;
    }
}

int colisionODS(E capibara, int *cantidad,SAMPLE *select,SAMPLE *recolectar){
    if(capibara.coordX>155)
    {
        if(*cantidad<1){
            play_sample(recolectar,100,127,1000,0);
            *cantidad=1;
            showODS(1,select);
            return 1;
        }
    }
    if(capibara.coordX>315)
    {
        if(*cantidad<2){
            play_sample(recolectar,100,127,1000,0);
            *cantidad=2;
            showODS(2,select);
            return 1;
        }
    }
    if(capibara.coordX>474)
    {
        if(*cantidad<3){
            play_sample(recolectar,100,127,1000,0);
            showODS(3,select);
            *cantidad=3;
            return 1;
        }
    }
    if(capibara.coordX>655)
    {
        if(*cantidad<4){
            play_sample(recolectar,100,127,1000,0);
            showODS(4,select);
            *cantidad=4;
            return 1;
        }
    }
    return 0;
}

void pintarODSyMarcador(E ods[4],BITMAP *fondo, E odsblack[4],int cantidad){
     int j;
     for(j=cantidad;j<4;j++){
        masked_blit(ods[j].imagen,fondo,0,0,ods[j].coordX,ods[j].coordY,ods[j].largo,ods[j].alto);
     }
     for(j=cantidad;j<4;j++){
        masked_blit(odsblack[j].imagen,fondo,0,0,odsblack[j].coordX,odsblack[j].coordY,odsblack[j].largo,odsblack[j].alto);
     }
     for(j=0;j<cantidad;j++){
        masked_blit(ods[j].imagen,fondo,0,0,odsblack[j].coordX,odsblack[j].coordY,ods[j].largo,ods[j].alto);
     }
}

int showODS (int input,SAMPLE *select) {
    int objY=10;
    BITMAP *buffer;
    BITMAP *obj;
    BITMAP *bg, *bg_down, *bg_org, *bg_orgDown;
// ----------------------------------------------------------------
    install_int_ex(increment_counter, BPS_TO_TIMER(30));

    char srcBG[40] = "./src/bg_ods/obj_"; //.bmp
    char srcBGDown[40]  = "./src/bg_ods/obj_"; //Down.bmp
    char srcObj[40] = "./src/icons/"; //.bmp
    int band=0;

    switch (input)
    {
    case 2:
        strcat(srcBG, "Arbol.bmp");
        strcat(srcBGDown, "ArbolDown.bmp");
        strcat(srcObj, "arbol.bmp");
        break;

    case 3:
        strcat(srcBG, "Sol.bmp");
        strcat(srcBGDown, "SolDown.bmp");
        strcat(srcObj, "sol.bmp");
        break;

    case 4:
        strcat(srcBG, "Pez.bmp");
        strcat(srcBGDown, "PezDown.bmp");
        strcat(srcObj, "pez.bmp");
        break;

    case 1:
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

    do{
        counter = 0;

        while (counter / 30.0 <= 3 && band==0) {
            if (counter / 30.0 <= 3 / 2.0) {
                objY = 100 - ((counter / 30.0) / (3 / 2.0) * 55);
            } else {
                objY = 100 - ((3 - (counter / 30.0)) / (3 / 2.0) * 55);
            }
            if(mouse_x > 705 && mouse_x < 831 && mouse_y > 548 && mouse_y < 599){
                draw_sprite(bg_down, obj, 300, objY);
                show_mouse(bg_down);
                draw_sprite(screen, bg_down, 0, 0);
                draw_sprite(bg_down, bg_orgDown, 0, 0);
                if(mouse_b&1){
                    play_sample(select,150,127,2500,0);
                    band=1;
                    mouse_b=0;
                }
           } else {
                draw_sprite(bg, obj, 300, objY);
                show_mouse(bg);
                draw_sprite(screen, bg, 0, 0);
                draw_sprite(bg, bg_org, 0, 0);
            }
            rest(5);
        }
    }while(!key[KEY_ESC] && band==0);
    clear_keybuf();
    return 0;
}
