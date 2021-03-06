#include <SDL2/SDL.h>
#include <stdio.h>
#include "renderer.h"
#include "microui.h"
#include "smartcalc.h"

#define NM_BTN_CALC_MODE "Calc mode"
#define ONE_FIELD {90, 40}
#define TWO_FIELDS {90, 40, 90, 40}

#define MAIN_SIZE 

static  char logbuf[64000];
static   int logbuf_updated = 0;
static float bg[3] = { 90, 95, 100 };


static void write_log(const char *text) {
  if (logbuf[0]) { strcat(logbuf, "\n"); }
  strcat(logbuf, text);
  logbuf_updated = 1;
}


static void test_window(mu_Context *ctx) {
  /* do window */
  if (mu_begin_window(ctx, "Smartcalc v1.0", mu_rect(40, 0, 300, 550))) {
    mu_Container *win = mu_get_current_container(ctx);
    win->rect.w = mu_max(win->rect.w, 240);
    win->rect.h = mu_max(win->rect.h, 300);
    
    
    /* window info */
     
    if (mu_header_ex(ctx, "Standart", MU_OPT_EXPANDED)) {
      //Set x
      
      //int submitted1 = 0;
      static char xval_buf[128];
      mu_layout_row(ctx, 2, (int[]) { 105, 40 }, 0);
      mu_label(ctx, "x value (default = 0):");
      if (mu_textbox(ctx, xval_buf, sizeof(xval_buf)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
        //submitted1 = 1;
      }


      static char buf[256];
      int submitted = 0;
      mu_layout_row(ctx, 2, (int[]) { -1, -1 }, 0);
      if (mu_textbox(ctx, buf, sizeof(buf)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
        submitted = 1;
      }
      
      mu_layout_row(ctx, 4, (int[]) {90, 90, 90, 90}, 0);
      if (mu_button(ctx, "Calculate")) { submitted = 1; }
      if (submitted) {
        write_log(buf);
        //buf[0] = '\0';
      }
      mu_button(ctx, "Draw plot");
      mu_layout_row(ctx, 2, (int[]) {90, 90}, 0);
      mu_text(ctx, "");
    }

    /* CREDIT */
    mu_text(ctx, "");
    if (mu_header_ex(ctx, "Credit", MU_OPT_EXPANDED)) {

      static char cred_amount[128];
      mu_layout_row(ctx, 4, (int[]) TWO_FIELDS, 0);
      mu_label(ctx, "amount:");
      if (mu_textbox(ctx, cred_amount, sizeof(cred_amount)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
      }

      static char cred_term[128];
      mu_label(ctx, "term in months:");
      if (mu_textbox(ctx, cred_term, sizeof(cred_term)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
      }

      static char cred_interest[128];
      mu_layout_row(ctx, 2, (int[]) ONE_FIELD, 0);
      mu_label(ctx, "interest rate:");
      if (mu_textbox(ctx, cred_interest, sizeof(cred_interest)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
      }
      mu_layout_begin_column(ctx);
      static int checks[3] = { 1, 0 };
      
      mu_layout_row(ctx, 3, (int[]) {90, 80, 100}, 0);
      mu_label(ctx, "credit type:");
      mu_checkbox(ctx, "annuity", &checks[0]);
      mu_checkbox(ctx, "differentiated", &checks[1]);
      mu_layout_end_column(ctx);

      mu_layout_row(ctx, 2, (int[]) { 90, 40 }, 0);
      mu_button(ctx, "Calculate");
      mu_layout_row(ctx, 2, (int[]) { 90, 40 }, 0);
      mu_text(ctx, "");
    }
    
    /* DEPOSIT */
    mu_text(ctx, "");
    if (mu_header_ex(ctx, "Deposit", MU_OPT_EXPANDED)) {
      mu_layout_row(ctx, 3, (int[]) { 86, -110, -1 }, 0);

      
      static char dep_amount[128];
      mu_layout_row(ctx, 4, (int[]) TWO_FIELDS, 0);
      mu_label(ctx, "amount:");
      if (mu_textbox(ctx, dep_amount, sizeof(dep_amount)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
      }
      static char dep_term[128];
      mu_label(ctx, "term:");
      
      if (mu_textbox(ctx, dep_term, sizeof(dep_term)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
      }

      static char dep_interest[128];
      mu_layout_row(ctx, 4, (int[]) TWO_FIELDS, 0);
      mu_label(ctx, "interest rate:");
      if (mu_textbox(ctx, dep_interest, sizeof(dep_interest)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
      }

      static char dep_tax[128];
      mu_label(ctx, "tax rate:");
      if (mu_textbox(ctx, dep_tax, sizeof(dep_tax)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
      }

      mu_layout_begin_column(ctx);
      static int checks[3] = { 1, 0 };
      
      mu_layout_row(ctx, 3, (int[]) {90, 80, 100}, 0);
      mu_label(ctx, "capit. of interest:");
      mu_checkbox(ctx, "yes", &checks[0]);
      mu_checkbox(ctx, "no", &checks[1]);
      mu_layout_end_column(ctx);

      /* replenishments */
      mu_layout_row(ctx, 2, (int[]) {200, -1}, 0);
      mu_label(ctx, "replenishments    (delimeter = ' ; ' )");

      mu_layout_row(ctx, 3, (int[]) {10, 80, -1}, 0);
      static char repl_times[1024];
      mu_text(ctx, "");
      mu_label(ctx, "months:");
      if (mu_textbox(ctx, repl_times, sizeof(repl_times)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
      }
      mu_layout_row(ctx, 3, (int[]) {10, 80, -1}, 0);
      static char repl_amounts[1024];
      mu_text(ctx, "");
      mu_label(ctx, "amounts:");
      if (mu_textbox(ctx, repl_amounts, sizeof(repl_amounts)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
      }


      /* withdrawals */
      mu_layout_row(ctx, 2, (int[]) {200, -1}, 0);
      mu_label(ctx, "withdrawals    (delimeter = ' ; ' )");

      mu_layout_row(ctx, 3, (int[]) {10, 80, -1}, 0);
      static char widr_times[1024];
      mu_text(ctx, "");
      mu_label(ctx, "months:");
      if (mu_textbox(ctx, widr_times, sizeof(widr_times)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
      }

      mu_layout_row(ctx, 3, (int[]) {10, 80, -1}, 0);
      static char widr_amounts[1024];
      mu_text(ctx, "");
      mu_label(ctx, "amounts:");
      if (mu_textbox(ctx, widr_amounts, sizeof(widr_amounts)) & MU_RES_SUBMIT) {
        mu_set_focus(ctx, ctx->last_id);
      }
      
      mu_layout_row(ctx, 2, (int[]) { 90, 40 }, 0);
      mu_button(ctx, "Calculate");
    }
    mu_end_window(ctx);
  }
}


static void log_window(mu_Context *ctx) {
  if (mu_begin_window(ctx, "Log Window", mu_rect(350, 0, 300, 550))) {
    /* output text panel */
    mu_layout_row(ctx, 1, (int[]) { -1 }, -25);
    mu_begin_panel(ctx, "Log Output");
    mu_Container *panel = mu_get_current_container(ctx);
    mu_layout_row(ctx, 1, (int[]) { -1 }, -1);
    mu_text(ctx, logbuf);
    mu_end_panel(ctx);
    if (logbuf_updated) {
      panel->scroll.y = panel->content_size.y;
      logbuf_updated = 0;
    }
    
    // input textbox + submit button
    static char buf[128];
    int submitted = 0;
    mu_layout_row(ctx, 2, (int[]) { -70, -1 }, 0);
    if (mu_textbox(ctx, buf, sizeof(buf)) & MU_RES_SUBMIT) {
      mu_set_focus(ctx, ctx->last_id);
      submitted = 1;
    }
    if (mu_button(ctx, "Calculate")) { submitted = 1; }
    if (submitted) {
      write_log(buf);
      buf[0] = '\0';
    }
    
    mu_end_window(ctx);
  }
}


static int uint8_slider(mu_Context *ctx, unsigned char *value, int low, int high) {
  static float tmp;
  mu_push_id(ctx, &value, sizeof(value));
  tmp = *value;
  int res = mu_slider_ex(ctx, &tmp, low, high, 0, "%.0f", MU_OPT_ALIGNCENTER);
  *value = tmp;
  mu_pop_id(ctx);
  return res;
}


static void style_window(mu_Context *ctx) {
  static struct { const char *label; int idx; } colors[] = {
    { "text:",         MU_COLOR_TEXT        },
    { "border:",       MU_COLOR_BORDER      },
    { "windowbg:",     MU_COLOR_WINDOWBG    },
    { "titlebg:",      MU_COLOR_TITLEBG     },
    { "titletext:",    MU_COLOR_TITLETEXT   },
    { "panelbg:",      MU_COLOR_PANELBG     },
    { "button:",       MU_COLOR_BUTTON      },
    { "buttonhover:",  MU_COLOR_BUTTONHOVER },
    { "buttonfocus:",  MU_COLOR_BUTTONFOCUS },
    { "base:",         MU_COLOR_BASE        },
    { "basehover:",    MU_COLOR_BASEHOVER   },
    { "basefocus:",    MU_COLOR_BASEFOCUS   },
    { "scrollbase:",   MU_COLOR_SCROLLBASE  },
    { "scrollthumb:",  MU_COLOR_SCROLLTHUMB },
    { NULL }
  };

  if (mu_begin_window(ctx, "Style Editor", mu_rect(350, 250, 300, 240))) {
    int sw = mu_get_current_container(ctx)->body.w * 0.14;
    mu_layout_row(ctx, 6, (int[]) { 80, sw, sw, sw, sw, -1 }, 0);
    for (int i = 0; colors[i].label; i++) {
      mu_label(ctx, colors[i].label);
      uint8_slider(ctx, &ctx->style->colors[i].r, 0, 255);
      uint8_slider(ctx, &ctx->style->colors[i].g, 0, 255);
      uint8_slider(ctx, &ctx->style->colors[i].b, 0, 255);
      uint8_slider(ctx, &ctx->style->colors[i].a, 0, 255);
      mu_draw_rect(ctx, mu_layout_next(ctx), ctx->style->colors[i]);
    }
    mu_end_window(ctx);
  }
}


static void process_frame(mu_Context *ctx) {
  mu_begin(ctx);
  style_window(ctx);
  log_window(ctx);
  test_window(ctx);
  mu_end(ctx);
}



static const char button_map[256] = {
  [ SDL_BUTTON_LEFT   & 0xff ] =  MU_MOUSE_LEFT,
  [ SDL_BUTTON_RIGHT  & 0xff ] =  MU_MOUSE_RIGHT,
  [ SDL_BUTTON_MIDDLE & 0xff ] =  MU_MOUSE_MIDDLE,
};

static const char key_map[256] = {
  [ SDLK_LSHIFT       & 0xff ] = MU_KEY_SHIFT,
  [ SDLK_RSHIFT       & 0xff ] = MU_KEY_SHIFT,
  [ SDLK_LCTRL        & 0xff ] = MU_KEY_CTRL,
  [ SDLK_RCTRL        & 0xff ] = MU_KEY_CTRL,
  [ SDLK_LALT         & 0xff ] = MU_KEY_ALT,
  [ SDLK_RALT         & 0xff ] = MU_KEY_ALT,
  [ SDLK_RETURN       & 0xff ] = MU_KEY_RETURN,
  [ SDLK_BACKSPACE    & 0xff ] = MU_KEY_BACKSPACE,
};


static int text_width(mu_Font font, const char *text, int len) {
  if (len == -1) { len = strlen(text); }
  (void)font;
  return r_get_text_width(text, len);
}

static int text_height(mu_Font font) {
  (void)font;
  return r_get_text_height();
}


int run_gui(void) {
  /* init SDL and renderer */
  SDL_Init(SDL_INIT_EVERYTHING);
  r_init();

  /* init microui */
  mu_Context *ctx = malloc(sizeof(mu_Context));
  mu_init(ctx);
  ctx->text_width = text_width;
  ctx->text_height = text_height;

  /* main loop */
  for (;;) {
    /* handle SDL events */
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT: exit(EXIT_SUCCESS); break;
        case SDL_MOUSEMOTION: mu_input_mousemove(ctx, e.motion.x, e.motion.y); break;
        case SDL_MOUSEWHEEL: mu_input_scroll(ctx, 0, e.wheel.y * -30); break;
        case SDL_TEXTINPUT: mu_input_text(ctx, e.text.text); break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
          int b = button_map[e.button.button & 0xff];
          if (b && e.type == SDL_MOUSEBUTTONDOWN) { mu_input_mousedown(ctx, e.button.x, e.button.y, b); }
          if (b && e.type ==   SDL_MOUSEBUTTONUP) { mu_input_mouseup(ctx, e.button.x, e.button.y, b);   }
          break;
        }

        case SDL_KEYDOWN:
        case SDL_KEYUP: {
          int c = key_map[e.key.keysym.sym & 0xff];
          if (c && e.type == SDL_KEYDOWN) { mu_input_keydown(ctx, c); }
          if (c && e.type ==   SDL_KEYUP) { mu_input_keyup(ctx, c);   }
          break;
        }
      }
    }

    /* process frame */
    process_frame(ctx);

    /* render */
    r_clear(mu_color(bg[0], bg[1], bg[2], 255));
    mu_Command *cmd = NULL;
    while (mu_next_command(ctx, &cmd)) {
      switch (cmd->type) {
        case MU_COMMAND_TEXT: r_draw_text(cmd->text.str, cmd->text.pos, cmd->text.color); break;
        case MU_COMMAND_RECT: r_draw_rect(cmd->rect.rect, cmd->rect.color); break;
        case MU_COMMAND_ICON: r_draw_icon(cmd->icon.id, cmd->icon.rect, cmd->icon.color); break;
        case MU_COMMAND_CLIP: r_set_clip_rect(cmd->clip.rect); break;
      }
    }
    r_present();
  }

  return 0;
}


