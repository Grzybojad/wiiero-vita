/*
 *  __      _ .__  .__
 * /  \    / \(__) (__)  ____ ______  ____
 * \   \/\/  /|  | |  |_/ __ \\_  _ \/  _ \
 *  \       //   |/   |\  ___/ |  |\(  <_> )
 *   \__/\_/ \__ \\__ \ \___  >|__|  \____/
 *              \/   \/     \/ By BScrk
 * Copyright (C) 2008-2009 Luca Benevolo <wiiero@free.fr>
 *
 * Original game concept (Liero) : Joosa Riekkinen in 1998
 * Wiiero is Liero game clone developed for Wii platform.
 * Wiiero is also avaiable on PSP and PC (linux/Windows) platform.
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
 *
 */
 
 
#ifndef INPUT_H
#define INPUT_H
 
#include "common.h"
#include <SDL/SDL.h>
#include "player.h"
#include "game.h"

#include <psp2/kernel/processmgr.h>
#include <psp2/touch.h>
#include <psp2/ctrl.h>
 
#include <vitasdk.h>
 
typedef enum { MODE_CMD
     , EXTRA_INFO
     , FIRE_CMD
     , JUMP_CMD
     , CROP_CMD
     , WSHOW_CMD
     , WLEFT_CMD
     , WRIGHT_CMD
     , NINJA_CMD
     , UP_CMD
     , DOWN_CMD
     , LEFT_CMD
     , RIGHT_CMD
     , MENU_CMD
     , PAUSE_CMD
     , OK_CMD
     , CANCEL_CMD
     , MAX_CMD
} lab_id_t;
 
char * cmd_labels[MAX_CMD] = {
  "PC controls"
 ,""
 ,"fire:"
 ,"jump:"
 ,"Dig:"
 ,"show weapon:"
 ,"prev weapon:"
 ,"next weapon:"
 ,"ninja hook:"
 ,"up:"
 ,"down:"
 ,"left:"
 ,"right:"
 ,"pause:"
 ,"menu:"
 ,"ok:"
 ,"cancel:"
};
 
 
char * cmd_key[2][MAX_CMD] = {
 { ""
  ,"Player 1"
  ,"[d]"
  ,"[a]"
  ,"[j+l]"
  ,"[z]"
  ,"[z+j]"
  ,"[z+l]"
  ,"[a+z]"
  ,"[i]"
  ,"[k]"
  ,"[j]"
  ,"[l]"
  ,"[space]"
  ,"[escape]"
  ,"[d]"
  ,"[a]"
 },{ ""
  ,"Player 2"
  ,"[page up]"
  ,"[insert]"
  ,"[4+6]"
  ,"[home]"
  ,"[home+4]"
  ,"[home+6]"
  ,"[insert+home]"
  ,"[8]"
  ,"[5]"
  ,"[4]"
  ,"[6]"
  ,"[space]"
  ,"[escape]"
  ,"[page up]"
  ,"[insert]"
 }
};
 
 
 
enum{/* - -- --- WIIERO EVENTS ---- --- -- - */
    P1_ACTION_KEY_UP     = SCE_CTRL_UP,
    P1_ACTION_KEY_DOWN   = SCE_CTRL_DOWN,
    P1_ACTION_KEY_LEFT   = SCE_CTRL_LEFT,
    P1_ACTION_KEY_RIGHT  = SCE_CTRL_RIGHT,
    P1_ACTION_KEY_JUMP   = SCE_CTRL_CIRCLE,
    P1_ACTION_KEY_CHANGE = SCE_CTRL_TRIANGLE,
    P1_ACTION_KEY_FIRE   = SCE_CTRL_SQUARE,
    P2_ACTION_KEY_UP     = SCE_CTRL_UP,
    P2_ACTION_KEY_DOWN   = SCE_CTRL_DOWN,
    P2_ACTION_KEY_LEFT   = SCE_CTRL_LEFT,
    P2_ACTION_KEY_RIGHT  = SCE_CTRL_RIGHT,
    P2_ACTION_KEY_JUMP   = SCE_CTRL_CIRCLE,
    P2_ACTION_KEY_CHANGE = SCE_CTRL_TRIANGLE,
    P2_ACTION_KEY_FIRE   = SCE_CTRL_SQUARE,
    GAME_ACTION_KEY_EXIT = SCE_CTRL_START,
    GAME_ACTION_KEY_FLIP = 0,
    GAME_ACTION_KEY_PAUSE= SCE_CTRL_SELECT,
};/* - -- --- WIIERO EVENTS ---- --- -- */
 
 
 
 
static __inline__ int are_controls_ready(){
  return 1;
}
 
/* PC event control */
static __inline__ void game_check_event(game_t* g){
  /* CHECK GAME EVENTS */
  uint32_t keystate;
  ASSERT(g);
 
  /* FLUSH EVENTS */
  SDL_Event event;
  while(SDL_PollEvent(&event)!=0){
    switch(event.type){
    case SDL_QUIT:
      g->wiiero_exit = 1;
      break;
    }
  }
 
  SceCtrlData pad, pad2;
  sceCtrlPeekBufferPositive(0, &pad, 1);
  sceCtrlPeekBufferPositive(2, &pad2, 1);
 
  /* GET KEYS */
  keystate = pad.buttons;
 
  // [PLAYER_1]
  if ( keystate & P1_ACTION_KEY_UP )
    g->worms[PLAYER_1]->worms_action |= ACTION_UP;
  if ( keystate & P1_ACTION_KEY_DOWN )
    g->worms[PLAYER_1]->worms_action |= ACTION_DOWN;
  if ( keystate & P1_ACTION_KEY_LEFT )
    g->worms[PLAYER_1]->worms_action |= ACTION_LEFT;
  if ( keystate & P1_ACTION_KEY_RIGHT )
    g->worms[PLAYER_1]->worms_action |= ACTION_RIGHT;
  if ( keystate & P1_ACTION_KEY_JUMP )
    g->worms[PLAYER_1]->worms_action |= (ACTION_JUMP | ACTION_CANCEL);
  if ( keystate & P1_ACTION_KEY_CHANGE )
    g->worms[PLAYER_1]->worms_action |= ACTION_CHANGE;
   if ( keystate & P1_ACTION_KEY_FIRE )
    g->worms[PLAYER_1]->worms_action |= (ACTION_FIRE | ACTION_OK);


  // On Vita TV, port 0 and 1 are the same controller
  // and that is the first one, so we check if port 2 is occupied
  // thanks caghandemir for the hackery that is here
  SceCtrlPortInfo myPortInfo;
  sceCtrlGetControllerPortInfo( &myPortInfo );
  if( myPortInfo.port[2] != SCE_CTRL_TYPE_UNPAIRED )
  {
    keystate = pad2.buttons;

    // [PLAYER_2]
    if ( keystate & P2_ACTION_KEY_UP )
      g->worms[PLAYER_2]->worms_action |= ACTION_UP;
    if ( keystate & P2_ACTION_KEY_DOWN )
      g->worms[PLAYER_2]->worms_action |= ACTION_DOWN;
    if ( keystate & P2_ACTION_KEY_LEFT )
      g->worms[PLAYER_2]->worms_action |= ACTION_LEFT;
    if ( keystate & P2_ACTION_KEY_RIGHT )
      g->worms[PLAYER_2]->worms_action |= ACTION_RIGHT;
    if ( keystate & P2_ACTION_KEY_JUMP )
      g->worms[PLAYER_2]->worms_action |= (ACTION_JUMP | ACTION_CANCEL);
    if ( keystate & P2_ACTION_KEY_CHANGE )
      g->worms[PLAYER_2]->worms_action |= ACTION_CHANGE;
    if ( keystate & P2_ACTION_KEY_FIRE )
      g->worms[PLAYER_2]->worms_action |= (ACTION_FIRE | ACTION_OK);
  }

  // [OTHER]
  if (keystate & GAME_ACTION_KEY_EXIT ){
     g->worms[PLAYER_1]->worms_action |= ACTION_MENU;
  }
 
  if (keystate & GAME_ACTION_KEY_FLIP)
       screen_flip_mode(g->wiiero_screen);
 
  if ( keystate & GAME_ACTION_KEY_PAUSE ){
    g->worms[PLAYER_1]->worms_action |= ACTION_PAUSE;
  }
}
 
 
/* Player event update PC */
static __inline__ void player_event_update(player_t* p,map_t* m,player_t* other_p){
  ASSERT(p);
  ASSERT(m);
 
  if(!(p->worms_status & STATUS_ALIVE)){
    if(p->ninja_hook->last_bullet)
      player_remove_hook(p,other_p);
    return;
  }
 
  p->worms_status &= ~STATUS_SHOW_W;
 
  /* Up & Down events */
  if(p->worms_action & ACTION_CHANGE){
      if(p->worms_action & ACTION_UP)
          player_change_rope_len(p,-ROPE_LEN_CHANGE_PITCH);
      if(p->worms_action & ACTION_DOWN)
          player_change_rope_len(p,ROPE_LEN_CHANGE_PITCH);
  }else{
    if((p->worms_action & ACTION_UP)){
      player_look_up(p);
    }else{
      if((p->worms_action & ACTION_DOWN))
        player_look_down(p);
      else p->reticle_pitch = ANGLE_PITCH;
    }
  }
  /* Ninja hook */
  if((p->worms_action & ACTION_JUMP) && (p->worms_action & ACTION_CHANGE)){
    if(!(p->worms_status & STATUS_NINJA_ACTION)){
      if(p->ninja_hook->last_bullet==0l){
        /* Launch */
        //printf("lauch\n");
        player_launch_hook(p);
      }else{
        /* Launch new */
        //printf("lauch new\n");
        player_remove_hook(p,other_p);
        player_launch_hook(p);
      }
      p->worms_status |= STATUS_NINJA_ACTION;
    }
  }else{
    /* jump */
    if((p->worms_action & ACTION_JUMP)){
      player_jump(p);
 
      /* Remove hook */
      if(!(p->worms_status & STATUS_NINJA_ACTION))
        if(p->ninja_hook->last_bullet!=0l){
           //printf("remove\n");
           player_remove_hook(p,other_p);
        }
    }
    p->worms_status &= ~STATUS_NINJA_ACTION;
  }
  /* crop , change or move */
  if((p->worms_action & ACTION_RIGHT) && (p->worms_action & ACTION_LEFT)){
    /* if crop, no weapon change */
    p->worms_status &= ~STATUS_CHANGING_W;
    if(!(p->worms_status & STATUS_CROPING))
      player_crop(p,m);
  }else{
    /* no crop */
    p->worms_status &= ~STATUS_CROPING;
    /* change or move */
    if(!(p->worms_action & ACTION_CHANGE)){
      /* if moving, no weapon change */
      p->worms_status &= ~STATUS_CHANGING_W;
      if((p->worms_action & ACTION_RIGHT))
        player_move_right(p);
      if((p->worms_action & ACTION_LEFT))
        player_move_left(p);
    }else{
      /* change */
      if(!(p->worms_action & ACTION_JUMP)){
        if((p->worms_action & ACTION_RIGHT)){
          if(!(p->worms_status & STATUS_CHANGING_W))
          player_change(p,1);
        }else{
          if((p->worms_action & ACTION_LEFT)){
            if(!(p->worms_status & STATUS_CHANGING_W))
              player_change(p,-1);
          }else{
            p->worms_status &= ~STATUS_CHANGING_W;
          }
        }
        p->worms_status |= STATUS_SHOW_W;
      }
    }
  }
  /* FIRE */
  if(p->worms_action & ACTION_FIRE)
     player_fire(p);  
 
}
 
#endif