/*
 Nuklear - v1.00 - public domain
 no warrenty implied; use at your own risk.
 authored from 2015-2016 by Micha Mettke

ABOUT:
    This is a minimal state immediate mode graphical user interface single header
    toolkit written in ANSI C and licensed under public domain.
    It was designed as a simple embeddable user interface for application and does
    not have any dependencies, a default renderbackend or OS window and input handling
    but instead provides a very modular library approach by using simple input state
    for input and draw commands describing primitive shapes as output.
    So instead of providing a layered library that tries to abstract over a number
    of platform and render backends it only focuses on the actual UI.

VALUES:
    - Immediate mode graphical user interface toolkit
    - Single header library
    - Written in C89 (ANSI C)
    - Small codebase (~15kLOC)
    - Focus on portability, efficiency and simplicity
    - No dependencies (not even the standard library if not wanted)
    - Fully skinnable and customizable
    - Low memory footprint with total memory control if needed or wanted
    - UTF-8 support
    - No global or hidden state
    - Customizable library modules (you can compile and use only what you need)
    - Optional font baker and vertex buffer output

USAGE:
    This library is self contained in one single header file and can be used either
    in header only mode or in implementation mode. The header only mode is used
    by default when included and allows including this header in other headers
    and does not contain the actual implementation.

    The implementation mode requires to define  the preprocessor macro
    NK_IMPLEMENTATION in *one* .c/.cpp file before #includeing this file, e.g.:

        #define NK_IMPLEMENTATION
        #include "nuklear.h"

    Also optionally define the symbols listed in the section "OPTIONAL DEFINES"
    below in implementation mode if you want to use additional functionality
    or need more control over the library.

FEATURES:
    - Absolutely no platform dependent code
    - Memory management control ranging from/to
        - Ease of use by allocating everything from the standard library
        - Control every byte of memory inside the library
    - Font handling control ranging from/to
        - Use your own font implementation to draw shapes/vertexes
        - Use this libraries internal font baking and handling API
    - Drawing output control ranging from/to
        - Simple shapes for more high level APIs which already having drawing capabilities
        - Hardware accessible anti-aliased vertex buffer output
    - Customizable colors and properties ranging from/to
        - Simple changes to color by filling a simple color table
        - Complete control with ability to use skinning to decorate widgets
    - Bendable UI library with widget ranging from/to
        - Basic widgets like buttons, checkboxes, slider, ...
        - Advanced widget like abstract comboboxes, contextual menus,...
    - Compile time configuration to only compile what you need
        - Subset which can be used if you do not want to link or use the standard library
    - Can be easily modified only update on user input instead of frame updates

OPTIONAL DEFINES:
    NK_PRIVATE
        If defined declares all functions as static, so they can only be accessed
        for the file that creates the implementation

    NK_INCLUDE_FIXED_TYPES
        If defined it will include header <stdint.h> for fixed sized types
        otherwise you have to select the correct types.

    NK_INCLUDE_DEFAULT_ALLOCATOR
        if defined it will include header <stdlib.h> and provide additional functions
        to use this library without caring for memory allocation control and therefore
        ease memory management.
        IMPORTANT:  this adds the standard library with malloc and free so don't define
                    if you don't want to link to the standard library!

    NK_INCLUDE_STANDARD_IO
        if defined it will include header <stdio.h> and <stdarg.h> and provide
        additional functions depending on file loading and variable arguments
        IMPORTANT:  this adds the standard library with fopen, fclose,...
                    as well as va_list,... so don't define this
                    if you don't want to link to the standard library!

    NK_INCLUDE_VERTEX_BUFFER_OUTPUT
        Defining this adds a vertex draw command list backend to this
        library, which allows you to convert queue commands into vertex draw commands.
        This is mainly if you need a hardware accessible format for OpenGL, DirectX,
        Vulkan, Metal,...

    NK_INCLUDE_FONT_BAKING
        Defining this adds the `stb_truetype` and `stb_rect_pack` implementation
        to this library and provides a default font for font loading and rendering.
        If you already have font handling or do not want to use this font handler
        you don't have to define it.

    NK_INCLUDE_DEFAULT_FONT
        Defining this adds the default font: ProggyClean.ttf font into this library
        which can be loaded into a font atlas and allows using this library without
        having a truetype font
        IMPORTANT: enabling this adds ~12kb to global stack memory

    NK_INCLUDE_COMMAND_USERDATA
        Defining this adds a userdata pointer into each command. Can be useful for
        example if you want to provide custom shader depending on the used widget.
        Can be combined with the style structures.

    NK_BUTTON_TRIGGER_ON_RELEASE
        Different platforms require button clicks occuring either on buttons being
        pressed (up to down) or released (down to up).
        By default this library will react on buttons being pressed, but if you
        define this it will only trigger if a button is released.

    NK_ASSERT
        If you don't define this, nuklear will use <assert.h> with assert().
        IMPORTANT:  it also adds the standard library so define to nothing of not wanted!

    NK_BUFFER_DEFAULT_INITIAL_SIZE
        Initial buffer size allocated by all buffers while using the default allocator
        functions included by defining NK_INCLUDE_DEFAULT_ALLOCATOR. If you don't
        want to allocate the default 4k memory then redefine it.

    NK_MAX_NUMBER_BUFFER
        Maximum buffer size for the conversion buffer between float and string
        Under normal circumstances this should be more than sufficient.

    NK_INPUT_MAX
        Defines the max number of bytes which can be added as text input in one frame.
        Under normal circumstances this should be more than sufficient.

    NK_MEMSET
        You can define this to 'memset' or your own memset implementation
        replacement. If not nuklear will use its own version.

    NK_MEMCOPY
        You can define this to 'memcpy' or your own memcpy implementation
        replacement. If not nuklear will use its own version.

    NK_SQRT
        You can define this to 'sqrt' or your own sqrt implementation
        replacement. If not nuklear will use its own slow and not highly
        accurate version.

    NK_SIN
        You can define this to 'sinf' or your own sine implementation
        replacement. If not nuklear will use its own approximation implementation.

    NK_COS
        You can define this to 'cosf' or your own cosine implementation
        replacement. If not nuklear will use its own approximation implementation.

    NK_BYTE
    NK_INT16
    NK_UINT16
    NK_INT32
    NK_UINT32
    NK_SIZE_TYPE
    NK_POINTER_TYPE
        If you compile without NK_USE_FIXED_TYPE then a number of standard types
        will be selected and compile time validated. If they are incorrect you can
        define the correct types.

CREDITS:
    Developed by Micha Mettke and every direct or indirect contributor to the GitHub.

    Embeds stb_texedit, stb_truetype and stb_rectpack by Sean Barret (public domain)
    Embeds ProggyClean.ttf font by Tristan Grimmer (MIT license).

    Big thank you to Omar Cornut (ocornut@github) for his imgui library and
    giving me the inspiration for this library, Casey Muratori for handmade hero
    and his original immediate mode graphical user interface idea and Sean
    Barret for his amazing single header libraries which restored by faith
    in libraries and brought me to create some of my own.

LICENSE:
    This software is dual-licensed to the public domain and under the following
    license: you are granted a perpetual, irrevocable license to copy, modify,
    publish and distribute this file as you see fit.
*/
#ifndef NK_H_
#define NK_H_

#ifdef __cplusplus
extern "C" {
#endif
/*
 * ==============================================================
 *
 *                          CONSTANTS
 *
 * ===============================================================
 */
#define NK_UTF_INVALID 0xFFFD /* internal invalid utf8 rune */
#define NK_UTF_SIZE 4 /* describes the number of bytes a glyph consists of*/
#ifndef NK_INPUT_MAX
#define NK_INPUT_MAX 16
#endif
#ifndef NK_MAX_NUMBER_BUFFER
#define NK_MAX_NUMBER_BUFFER 64
#endif
/*
 * ===============================================================
 *
 *                          BASIC
 *
 * ===============================================================
 */
#ifdef NK_INCLUDE_FIXED_TYPES
#include <stdint.h>
typedef int16_t nk_short;
typedef uint16_t nk_ushort;
typedef int32_t nk_int;
typedef uint32_t nk_uint;
typedef uint32_t nk_hash;
typedef uintptr_t nk_size;
typedef uintptr_t nk_ptr;
typedef uint32_t nk_flags;
typedef uint32_t nk_rune;
typedef uint8_t nk_byte;
#else
#ifndef NK_BYTE
typedef unsigned char nk_byte;
#else
typedef NK_BYTE nk_byte;
#endif
#ifndef NK_INT16
typedef short nk_short;
#else
typedef NK_INT16 nk_short;
#endif
#ifndef NK_UINT16
typedef unsigned short nk_ushort;
#else
typedef NK_UINT16 nk_ushort;
#endif
#ifndef NK_INT32
typedef int nk_int;
#else
typedef NK_INT32 nk_int;
#endif
#ifndef NK_UINT32
typedef unsigned int nk_uint;
#else
typedef NK_UINT32 nk_uint;
#endif
#ifndef NK_SIZE_TYPE
typedef unsigned long nk_size;
#else
typedef NK_SIZE_TYPE nk_size;
#endif
#ifndef NK_POINTER_TYPE
typedef unsigned long nk_ptr;
#else
typedef NK_POINTER_TYPE nk_ptr;
#endif
typedef NK_UINT32 nk_hash;
typedef unsigned int nk_flags;
typedef nk_uint nk_rune;
typedef unsigned char nk_byte;
#endif

#ifdef NK_PRIVATE
#define NK_API static
#else
#define NK_API extern
#endif

#define NK_INTERN static
#define NK_STORAGE static
#define NK_GLOBAL static

/* ============================================================================
 *
 *                                  API
 *
 * =========================================================================== */
#define NK_UNDEFINED (-1.0f)
#define NK_FLAG(x) (1 << (x))
#define NK_STRINGIFY(x) #x
#define NK_LINE_STR(x) NK_STRINGIFY(x)
#define NK_FILE_LINE __FILE__":"NK_LINE_STR(__LINE__)

struct nk_buffer;
struct nk_allocator;
struct nk_command_buffer;
struct nk_draw_command;
struct nk_convert_config;
struct nk_text_edit;
struct nk_draw_list;
struct nk_user_font;
struct nk_panel;
struct nk_context;

enum {nk_false, nk_true};
struct nk_color {nk_byte r,g,b,a;};
struct nk_vec2 {float x,y;};
struct nk_vec2i {short x, y;};
struct nk_rect {float x,y,w,h;};
struct nk_recti {short x,y,w,h;};
typedef char nk_glyph[NK_UTF_SIZE];
typedef union {void *ptr; int id;} nk_handle;
struct nk_image {nk_handle handle;unsigned short w,h;unsigned short region[4];};
struct nk_scroll {unsigned short x, y;};
enum nk_heading {NK_UP, NK_RIGHT, NK_DOWN, NK_LEFT};

typedef int(*nk_filter)(const struct nk_text_edit*, nk_rune unicode);
typedef void(*nk_paste_f)(nk_handle, struct nk_text_edit*);
typedef void(*nk_copy_f)(nk_handle, const char*, int len);

enum nk_button_behavior {NK_BUTTON_DEFAULT,NK_BUTTON_REPEATER};
enum nk_modify          {NK_FIXED=nk_false,NK_MODIFIABLE=nk_true};
enum nk_orientation     {NK_VERTICAL,NK_HORIZONTAL};
enum nk_collapse_states {NK_MINIMIZED=nk_false,NK_MAXIMIZED = nk_true};
enum nk_show_states     {NK_HIDDEN=nk_false,NK_SHOWN=nk_true};
enum nk_chart_type      {NK_CHART_LINES,NK_CHART_COLUMN,NK_CHART_MAX};
enum nk_chart_event     {NK_CHART_HOVERING=0x01, NK_CHART_CLICKED=0x02};
enum nk_color_format    {NK_RGB, NK_RGBA};
enum nk_popup_type      {NK_POPUP_STATIC,NK_POPUP_DYNAMIC};
enum nk_layout_format   {NK_DYNAMIC,NK_STATIC};
enum nk_tree_type       {NK_TREE_NODE,NK_TREE_TAB};
enum nk_anti_aliasing   {NK_ANTI_ALIASING_OFF,NK_ANTI_ALIASING_ON};

struct nk_allocator {
    nk_handle userdata;
    void*(*alloc)(nk_handle, void *old, nk_size);
    void(*free)(nk_handle, void*);
};

struct nk_draw_null_texture {
    nk_handle texture;/* texture handle to a texture with a white pixel */
    struct nk_vec2 uv; /* coordinates to a white pixel in the texture  */
};
struct nk_convert_config {
    float global_alpha; /* global alpha value */
    enum nk_anti_aliasing line_AA; /* line anti-aliasing flag can be turned off if you are tight on memory */
    enum nk_anti_aliasing shape_AA; /* shape anti-aliasing flag can be turned off if you are tight on memory */
    unsigned int circle_segment_count; /* number of segments used for circles: default to 22 */
    unsigned int arc_segment_count; /* number of segments used for arcs: default to 22 */
    unsigned int curve_segment_count; /* number of segments used for curves: default to 22 */
    struct nk_draw_null_texture null; /* handle to texture with a white pixel for shape drawing */
};

enum nk_symbol_type {
    NK_SYMBOL_NONE,
    NK_SYMBOL_X,
    NK_SYMBOL_UNDERSCORE,
    NK_SYMBOL_CIRCLE,
    NK_SYMBOL_CIRCLE_FILLED,
    NK_SYMBOL_RECT,
    NK_SYMBOL_RECT_FILLED,
    NK_SYMBOL_TRIANGLE_UP,
    NK_SYMBOL_TRIANGLE_DOWN,
    NK_SYMBOL_TRIANGLE_LEFT,
    NK_SYMBOL_TRIANGLE_RIGHT,
    NK_SYMBOL_PLUS,
    NK_SYMBOL_MINUS,
    NK_SYMBOL_MAX
};

enum nk_keys {
    NK_KEY_NONE,
    NK_KEY_SHIFT,
    NK_KEY_CTRL,
    NK_KEY_DEL,
    NK_KEY_ENTER,
    NK_KEY_TAB,
    NK_KEY_BACKSPACE,
    NK_KEY_COPY,
    NK_KEY_CUT,
    NK_KEY_PASTE,
    NK_KEY_UP,
    NK_KEY_DOWN,
    NK_KEY_LEFT,
    NK_KEY_RIGHT,
    NK_KEY_TEXT_INSERT_MODE,
    NK_KEY_TEXT_REPLACE_MODE,
    NK_KEY_TEXT_RESET_MODE,
    NK_KEY_TEXT_LINE_START,
    NK_KEY_TEXT_LINE_END,
    NK_KEY_TEXT_START,
    NK_KEY_TEXT_END,
    NK_KEY_TEXT_UNDO,
    NK_KEY_TEXT_REDO,
    NK_KEY_TEXT_WORD_LEFT,
    NK_KEY_TEXT_WORD_RIGHT,
    NK_KEY_MAX
};

enum nk_buttons {
    NK_BUTTON_LEFT,
    NK_BUTTON_MIDDLE,
    NK_BUTTON_RIGHT,
    NK_BUTTON_MAX
};

enum nk_style_colors {
    NK_COLOR_TEXT,
    NK_COLOR_WINDOW,
    NK_COLOR_HEADER,
    NK_COLOR_BORDER,
    NK_COLOR_BUTTON,
    NK_COLOR_BUTTON_HOVER,
    NK_COLOR_BUTTON_ACTIVE,
    NK_COLOR_TOGGLE,
    NK_COLOR_TOGGLE_HOVER,
    NK_COLOR_TOGGLE_CURSOR,
    NK_COLOR_SELECT,
    NK_COLOR_SELECT_ACTIVE,
    NK_COLOR_SLIDER,
    NK_COLOR_SLIDER_CURSOR,
    NK_COLOR_SLIDER_CURSOR_HOVER,
    NK_COLOR_SLIDER_CURSOR_ACTIVE,
    NK_COLOR_PROPERTY,
    NK_COLOR_EDIT,
    NK_COLOR_EDIT_CURSOR,
    NK_COLOR_COMBO,
    NK_COLOR_CHART,
    NK_COLOR_CHART_COLOR,
    NK_COLOR_CHART_COLOR_HIGHLIGHT,
    NK_COLOR_SCROLLBAR,
    NK_COLOR_SCROLLBAR_CURSOR,
    NK_COLOR_SCROLLBAR_CURSOR_HOVER,
    NK_COLOR_SCROLLBAR_CURSOR_ACTIVE,
    NK_COLOR_TAB_HEADER,
    NK_COLOR_COUNT
};

enum nk_widget_layout_states {
    NK_WIDGET_INVALID, /* The widget cannot be seen and is completely out of view */
    NK_WIDGET_VALID, /* The widget is completely inside the window and can be updated and drawn */
    NK_WIDGET_ROM /* The widget is partially visible and cannot be updated */
};

/* widget states */
enum nk_widget_states {
    NK_WIDGET_STATE_MODIFIED    = NK_FLAG(1),
    NK_WIDGET_STATE_INACTIVE    = NK_FLAG(2), /* widget is neither active nor hovered */
    NK_WIDGET_STATE_ENTERED     = NK_FLAG(3), /* widget has been hovered on the current frame */
    NK_WIDGET_STATE_HOVER       = NK_FLAG(4), /* widget is being hovered */
    NK_WIDGET_STATE_ACTIVED     = NK_FLAG(5),/* widget is currently activated */
    NK_WIDGET_STATE_LEFT        = NK_FLAG(6), /* widget is from this frame on not hovered anymore */
    NK_WIDGET_STATE_HOVERED     = NK_WIDGET_STATE_HOVER|NK_WIDGET_STATE_MODIFIED, /* widget is being hovered */
    NK_WIDGET_STATE_ACTIVE      = NK_WIDGET_STATE_ACTIVED|NK_WIDGET_STATE_MODIFIED /* widget is currently activated */
};

/* text alignment */
enum nk_text_align {
    NK_TEXT_ALIGN_LEFT        = 0x01,
    NK_TEXT_ALIGN_CENTERED    = 0x02,
    NK_TEXT_ALIGN_RIGHT       = 0x04,
    NK_TEXT_ALIGN_TOP         = 0x08,
    NK_TEXT_ALIGN_MIDDLE      = 0x10,
    NK_TEXT_ALIGN_BOTTOM      = 0x20
};
enum nk_text_alignment {
    NK_TEXT_LEFT        = NK_TEXT_ALIGN_MIDDLE|NK_TEXT_ALIGN_LEFT,
    NK_TEXT_CENTERED    = NK_TEXT_ALIGN_MIDDLE|NK_TEXT_ALIGN_CENTERED,
    NK_TEXT_RIGHT       = NK_TEXT_ALIGN_MIDDLE|NK_TEXT_ALIGN_RIGHT
};

enum nk_edit_flags {
    NK_EDIT_DEFAULT                 = 0,
    NK_EDIT_READ_ONLY               = NK_FLAG(0),
    NK_EDIT_AUTO_SELECT             = NK_FLAG(1),
    NK_EDIT_SIG_ENTER               = NK_FLAG(2),
    NK_EDIT_ALLOW_TAB               = NK_FLAG(3),
    NK_EDIT_NO_CURSOR               = NK_FLAG(4),
    NK_EDIT_SELECTABLE              = NK_FLAG(5),
    NK_EDIT_CLIPBOARD               = NK_FLAG(6),
    NK_EDIT_CTRL_ENTER_NEWLINE      = NK_FLAG(7),
    NK_EDIT_NO_HORIZONTAL_SCROLL    = NK_FLAG(8),
    NK_EDIT_ALWAYS_INSERT_MODE      = NK_FLAG(9),
    NK_EDIT_MULTILINE               = NK_FLAG(11)
};
enum nk_edit_types {
    NK_EDIT_SIMPLE  = NK_EDIT_ALWAYS_INSERT_MODE,
    NK_EDIT_FIELD   = NK_EDIT_SIMPLE|NK_EDIT_SELECTABLE,
    NK_EDIT_BOX     = NK_EDIT_ALWAYS_INSERT_MODE| NK_EDIT_SELECTABLE|
                        NK_EDIT_MULTILINE|NK_EDIT_ALLOW_TAB,
    NK_EDIT_EDITOR  = NK_EDIT_SELECTABLE|NK_EDIT_MULTILINE|NK_EDIT_ALLOW_TAB|
                        NK_EDIT_CLIPBOARD

};
enum nk_edit_events {
    NK_EDIT_ACTIVE      = NK_FLAG(0), /* edit widget is currently being modified */
    NK_EDIT_INACTIVE    = NK_FLAG(1), /* edit widget is not active and is not being modified */
    NK_EDIT_ACTIVATED   = NK_FLAG(2), /* edit widget went from state inactive to state active */
    NK_EDIT_DEACTIVATED = NK_FLAG(3), /* edit widget went from state active to state inactive */
    NK_EDIT_COMMITED    = NK_FLAG(4) /* edit widget has received an enter and lost focus */
};

enum nk_panel_flags {
    NK_WINDOW_BORDER        = NK_FLAG(0), /* Draws a border around the window to visually separate the window * from the background */
    NK_WINDOW_BORDER_HEADER = NK_FLAG(1), /* Draws a border between window header and body */
    NK_WINDOW_MOVABLE       = NK_FLAG(2), /* The movable flag indicates that a window can be moved by user input or * by dragging the window header */
    NK_WINDOW_SCALABLE      = NK_FLAG(3), /* The scalable flag indicates that a window can be scaled by user input * by dragging a scaler icon at the button of the window */
    NK_WINDOW_CLOSABLE      = NK_FLAG(4), /* adds a closable icon into the header */
    NK_WINDOW_MINIMIZABLE   = NK_FLAG(5), /* adds a minimize icon into the header */
    NK_WINDOW_DYNAMIC       = NK_FLAG(6), /* special window type growing up in height while being filled to a * certain maximum height */
    NK_WINDOW_NO_SCROLLBAR  = NK_FLAG(7), /* Removes the scrollbar from the window */
    NK_WINDOW_TITLE         = NK_FLAG(8) /* Forces a header at the top at the window showing the title */
};

/* context */
#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API int                      nk_init_default(struct nk_context*, const struct nk_user_font*);
#endif
NK_API int                      nk_init_fixed(struct nk_context*, void *memory, nk_size size, const struct nk_user_font*);
NK_API int                      nk_init_custom(struct nk_context*, struct nk_buffer *cmds, struct nk_buffer *pool, const struct nk_user_font*);
NK_API int                      nk_init(struct nk_context*, struct nk_allocator*, const struct nk_user_font*);
NK_API void                     nk_clear(struct nk_context*);
NK_API void                     nk_free(struct nk_context*);
#ifdef NK_INCLUDE_COMMAND_USERDATA
NK_API void                     nk_set_user_data(struct nk_context*, nk_handle handle);
#endif

/* window */
NK_API int                      nk_begin(struct nk_context*, struct nk_panel*, const char *title, struct nk_rect bounds, nk_flags flags);
NK_API void                     nk_end(struct nk_context*);

NK_API struct nk_window*        nk_window_find(struct nk_context *ctx, const char *name);
NK_API struct nk_rect           nk_window_get_bounds(const struct nk_context*);
NK_API struct nk_vec2           nk_window_get_position(const struct nk_context*);
NK_API struct nk_vec2           nk_window_get_size(const struct nk_context*);
NK_API float                    nk_window_get_width(const struct nk_context*);
NK_API float                    nk_window_get_height(const struct nk_context*);
NK_API struct nk_panel*         nk_window_get_panel(struct nk_context*);
NK_API struct nk_rect           nk_window_get_content_region(struct nk_context*);
NK_API struct nk_vec2           nk_window_get_content_region_min(struct nk_context*);
NK_API struct nk_vec2           nk_window_get_content_region_max(struct nk_context*);
NK_API struct nk_vec2           nk_window_get_content_region_size(struct nk_context*);
NK_API struct nk_command_buffer* nk_window_get_canvas(struct nk_context*);

NK_API int                      nk_window_has_focus(const struct nk_context*);
NK_API int                      nk_window_is_collapsed(struct nk_context*, const char*);
NK_API int                      nk_window_is_closed(struct nk_context*, const char*);
NK_API int                      nk_window_is_active(struct nk_context*, const char*);
NK_API int                      nk_window_is_hovered(struct nk_context*);
NK_API int                      nk_window_is_any_hovered(struct nk_context*);
NK_API int                      nk_item_is_any_active(struct nk_context*);

NK_API void                     nk_window_set_bounds(struct nk_context*, struct nk_rect);
NK_API void                     nk_window_set_position(struct nk_context*, struct nk_vec2);
NK_API void                     nk_window_set_size(struct nk_context*, struct nk_vec2);
NK_API void                     nk_window_set_focus(struct nk_context*, const char *name);

NK_API void                     nk_window_close(struct nk_context *ctx, const char *name);
NK_API void                     nk_window_collapse(struct nk_context*, const char *name, enum nk_collapse_states);
NK_API void                     nk_window_collapse_if(struct nk_context*, const char *name, enum nk_collapse_states, int cond);
NK_API void                     nk_window_show(struct nk_context*, const char *name, enum nk_show_states);
NK_API void                     nk_window_show_if(struct nk_context*, const char *name, enum nk_show_states, int cond);

/* Layout */
NK_API void                     nk_layout_row_dynamic(struct nk_context*, float height, int cols);
NK_API void                     nk_layout_row_static(struct nk_context*, float height, int item_width, int cols);

NK_API void                     nk_layout_row_begin(struct nk_context*, enum nk_layout_format, float row_height, int cols);
NK_API void                     nk_layout_row_push(struct nk_context*, float value);
NK_API void                     nk_layout_row_end(struct nk_context*);
NK_API void                     nk_layout_row(struct nk_context*, enum nk_layout_format, float height, int cols, const float *ratio);

NK_API void                     nk_layout_space_begin(struct nk_context*, enum nk_layout_format, float height, int widget_count);
NK_API void                     nk_layout_space_push(struct nk_context*, struct nk_rect);
NK_API void                     nk_layout_space_end(struct nk_context*);

NK_API struct nk_rect           nk_layout_space_bounds(struct nk_context*);
NK_API struct nk_vec2           nk_layout_space_to_screen(struct nk_context*, struct nk_vec2);
NK_API struct nk_vec2           nk_layout_space_to_local(struct nk_context*, struct nk_vec2);
NK_API struct nk_rect           nk_layout_space_rect_to_screen(struct nk_context*, struct nk_rect);
NK_API struct nk_rect           nk_layout_space_rect_to_local(struct nk_context*, struct nk_rect);

/* Layout: Group */
NK_API int                      nk_group_begin(struct nk_context*, struct nk_panel*, const char *title, nk_flags);
NK_API void                     nk_group_end(struct nk_context*);

/* Layout: Tree */
#define                         nk_tree_push(ctx, type, title, state) nk_tree_push_hashed(ctx, type, title, state, __FILE__,nk_strlen(__FILE__),__LINE__)
#define                         nk_tree_push_id(ctx, type, title, state, id) nk_tree_push_hashed(ctx, type, title, state, NK_FILE_LINE,nk_strlen(NK_FILE_LINE),id)
NK_API int                      nk_tree_push_hashed(struct nk_context*, enum nk_tree_type, const char *title, enum nk_collapse_states initial_state, const char *hash, int len,int seed);
NK_API void                     nk_tree_pop(struct nk_context*);

/* Widgets */
NK_API void                     nk_text(struct nk_context*, const char*, int, nk_flags);
NK_API void                     nk_text_colored(struct nk_context*, const char*, int, nk_flags, struct nk_color);
NK_API void                     nk_text_wrap(struct nk_context*, const char*, int);
NK_API void                     nk_text_wrap_colored(struct nk_context*, const char*, int, struct nk_color);

NK_API void                     nk_label(struct nk_context*, const char*, nk_flags);
NK_API void                     nk_label_colored(struct nk_context*, const char*, nk_flags align, struct nk_color);
NK_API void                     nk_label_wrap(struct nk_context*, const char*);
NK_API void                     nk_label_colored_wrap(struct nk_context*, const char*, struct nk_color);
NK_API void                     nk_image(struct nk_context*, struct nk_image);
#ifdef NK_INCLUDE_STANDARD_IO
NK_API void                     nk_labelf(struct nk_context*, nk_flags, const char*, ...);
NK_API void                     nk_labelf_colored(struct nk_context*, nk_flags align, struct nk_color, const char*,...);
NK_API void                     nk_labelf_wrap(struct nk_context*, const char*,...);
NK_API void                     nk_labelf_colored_wrap(struct nk_context*, struct nk_color, const char*,...);

NK_API void                     nk_value_bool(struct nk_context*, const char *prefix, int);
NK_API void                     nk_value_int(struct nk_context*, const char *prefix, int);
NK_API void                     nk_value_uint(struct nk_context*, const char *prefix, unsigned int);
NK_API void                     nk_value_float(struct nk_context*, const char *prefix, float);
NK_API void                     nk_value_color_byte(struct nk_context*, const char *prefix, struct nk_color);
NK_API void                     nk_value_color_float(struct nk_context*, const char *prefix, struct nk_color);
NK_API void                     nk_value_color_hex(struct nk_context*, const char *prefix, struct nk_color);
#endif

/* Widgets: Buttons */
NK_API int                      nk_button_text(struct nk_context *ctx, const char *title, int len, enum nk_button_behavior);
NK_API int                      nk_button_label(struct nk_context *ctx, const char *title, enum nk_button_behavior);
NK_API int                      nk_button_color(struct nk_context*, struct nk_color, enum nk_button_behavior);
NK_API int                      nk_button_symbol(struct nk_context*, enum nk_symbol_type, enum nk_button_behavior);
NK_API int                      nk_button_image(struct nk_context*, struct nk_image img, enum nk_button_behavior);
NK_API int                      nk_button_symbol_label(struct nk_context*, enum nk_symbol_type, const char*, nk_flags text_alignment, enum nk_button_behavior);
NK_API int                      nk_button_symbol_text(struct nk_context*, enum nk_symbol_type, const char*, int, nk_flags alignment, enum nk_button_behavior);
NK_API int                      nk_button_image_label(struct nk_context*, struct nk_image img, const char*, nk_flags text_alignment, enum nk_button_behavior);
NK_API int                      nk_button_image_text(struct nk_context*, struct nk_image img, const char*, int, nk_flags alignment, enum nk_button_behavior);

/* Widgets: Checkbox */
NK_API int                      nk_check_label(struct nk_context*, const char*, int active);
NK_API int                      nk_check_text(struct nk_context*, const char*, int,int active);
NK_API unsigned                 nk_check_flags_label(struct nk_context*, const char*, unsigned int flags, unsigned int value);
NK_API unsigned                 nk_check_flags_text(struct nk_context*, const char*, int, unsigned int flags, unsigned int value);
NK_API int                      nk_checkbox_label(struct nk_context*, const char*, int *active);
NK_API int                      nk_checkbox_text(struct nk_context*, const char*, int, int *active);
NK_API int                      nk_checkbox_flags_label(struct nk_context*, const char*, unsigned int *flags, unsigned int value);
NK_API int                      nk_checkbox_flags_text(struct nk_context*, const char*, int, unsigned int *flags, unsigned int value);

/* Widgets: Radio */
NK_API int                      nk_radio_label(struct nk_context*, const char*, int *active);
NK_API int                      nk_radio_text(struct nk_context*, const char*, int, int *active);
NK_API int                      nk_option_label(struct nk_context*, const char*, int active);
NK_API int                      nk_option_text(struct nk_context*, const char*, int, int active);

/* Widgets: Selectable */
NK_API int                      nk_selectable_label(struct nk_context*, const char*, nk_flags align, int *value);
NK_API int                      nk_selectable_text(struct nk_context*, const char*, int, nk_flags align, int *value);
NK_API int                      nk_select_label(struct nk_context*, const char*, nk_flags align, int value);
NK_API int                      nk_select_text(struct nk_context*, const char*, int, nk_flags align, int value);

/* Widgets: Slider */
NK_API float                    nk_slide_float(struct nk_context*, float min, float val, float max, float step);
NK_API int                      nk_slide_int(struct nk_context*, int min, int val, int max, int step);
NK_API int                      nk_slider_float(struct nk_context*, float min, float *val, float max, float step);
NK_API int                      nk_slider_int(struct nk_context*, int min, int *val, int max, int step);

/* Widgets: Progressbar */
NK_API int                      nk_progress(struct nk_context*, nk_size *cur, nk_size max, int modifyable);
NK_API nk_size                  nk_prog(struct nk_context*, nk_size cur, nk_size max, int modifyable);

/* Widgets: Color picker */
NK_API struct nk_color          nk_color_picker(struct nk_context*, struct nk_color, enum nk_color_format);
NK_API int                      nk_color_pick(struct nk_context*, struct nk_color*, enum nk_color_format);

/* Widgets: Property */
NK_API void                     nk_property_float(struct nk_context *layout, const char *name, float min, float *val, float max, float step, float inc_per_pixel);
NK_API void                     nk_property_int(struct nk_context *layout, const char *name, int min, int *val, int max, int step, int inc_per_pixel);
NK_API float                    nk_propertyf(struct nk_context *layout, const char *name, float min, float val, float max, float step, float inc_per_pixel);
NK_API int                      nk_propertyi(struct nk_context *layout, const char *name, int min, int val, int max, int step, int inc_per_pixel);

/* Widgets: TextEdit */
NK_API nk_flags                 nk_edit_string(struct nk_context*, nk_flags, char *buffer, int *len, int max, nk_filter);
NK_API nk_flags                 nk_edit_buffer(struct nk_context*, nk_flags, struct nk_text_edit*, nk_filter);

/* Chart */
NK_API int                      nk_chart_begin(struct nk_context*, enum nk_chart_type, int num, float min, float max);
NK_API void                     nk_chart_add_slot(struct nk_context *ctx, const enum nk_chart_type type, int count, float min_value, float max_value);
NK_API nk_flags                 nk_chart_push(struct nk_context*, float);
NK_API nk_flags                 nk_chart_push_slot(struct nk_context*, float, int);
NK_API void                     nk_chart_end(struct nk_context*);
NK_API void                     nk_plot(struct nk_context*, enum nk_chart_type, const float *values, int count, int offset);
NK_API void                     nk_plot_function(struct nk_context*, enum nk_chart_type, void *userdata, float(*value_getter)(void* user, int index), int count, int offset);

/* Popups */
NK_API int                      nk_popup_begin(struct nk_context*, struct nk_panel*, enum nk_popup_type, const char*, nk_flags, struct nk_rect bounds);
NK_API void                     nk_popup_close(struct nk_context*);
NK_API void                     nk_popup_end(struct nk_context*);

/* Combobox */
NK_API int                      nk_combo(struct nk_context*, const char **items, int count, int selected, int item_height);
NK_API int                      nk_combo_separator(struct nk_context*, const char *items_separated_by_separator, int separator, int selected, int count, int item_height);
NK_API int                      nk_combo_string(struct nk_context*, const char *items_separated_by_zeros, int selected, int count, int item_height);
NK_API int                      nk_combo_callback(struct nk_context*, void(*item_getter)(void*, int, const char**), void *userdata, int selected, int count, int item_height);
NK_API void                     nk_combobox(struct nk_context*, const char **items, int count, int *selected, int item_height);
NK_API void                     nk_combobox_string(struct nk_context*, const char *items_separated_by_zeros, int *selected, int count, int item_height);
NK_API void                     nk_combobox_separator(struct nk_context*, const char *items_separated_by_separator, int separator,int *selected, int count, int item_height);
NK_API void                     nk_combobox_callback(struct nk_context*, void(*item_getter)(void*, int, const char**), void*, int *selected, int count, int item_height);

/* Combobox: abstract */
NK_API int                      nk_combo_begin_text(struct nk_context*, struct nk_panel*, const char *selected, int, int max_height);
NK_API int                      nk_combo_begin_label(struct nk_context*, struct nk_panel*, const char *selected, int max_height);
NK_API int                      nk_combo_begin_color(struct nk_context*, struct nk_panel*, struct nk_color color, int max_height);
NK_API int                      nk_combo_begin_symbol(struct nk_context*, struct nk_panel*, enum nk_symbol_type,  int max_height);
NK_API int                      nk_combo_begin_symbol_label(struct nk_context*, struct nk_panel*, const char *selected, enum nk_symbol_type, int height);
NK_API int                      nk_combo_begin_symbol_text(struct nk_context*, struct nk_panel*, const char *selected, int, enum nk_symbol_type, int height);
NK_API int                      nk_combo_begin_image(struct nk_context*, struct nk_panel*, struct nk_image img,  int max_height);
NK_API int                      nk_combo_begin_image_label(struct nk_context*, struct nk_panel*, const char *selected, struct nk_image, int height);
NK_API int                      nk_combo_begin_image_text(struct nk_context*, struct nk_panel*, const char *selected, int, struct nk_image, int height);
NK_API int                      nk_combo_item_label(struct nk_context*, const char*, nk_flags alignment);
NK_API int                      nk_combo_item_text(struct nk_context*, const char*,int, nk_flags alignment);
NK_API int                      nk_combo_item_image_label(struct nk_context*, struct nk_image, const char*, nk_flags alignment);
NK_API int                      nk_combo_item_image_text(struct nk_context*, struct nk_image, const char*, int,nk_flags alignment);
NK_API int                      nk_combo_item_symbol_label(struct nk_context*, enum nk_symbol_type, const char*, nk_flags alignment);
NK_API int                      nk_combo_item_symbol_text(struct nk_context*, enum nk_symbol_type, const char*, int, nk_flags alignment);
NK_API void                     nk_combo_close(struct nk_context*);
NK_API void                     nk_combo_end(struct nk_context*);

/* Contextual */
NK_API int                      nk_contextual_begin(struct nk_context*, struct nk_panel*, nk_flags, struct nk_vec2, struct nk_rect trigger_bounds);
NK_API int                      nk_contextual_item_text(struct nk_context*, const char*, int,nk_flags align);
NK_API int                      nk_contextual_item_label(struct nk_context*, const char*, nk_flags align);
NK_API int                      nk_contextual_item_image_label(struct nk_context*, struct nk_image, const char*, nk_flags alignment);
NK_API int                      nk_contextual_item_image_text(struct nk_context*, struct nk_image, const char*, int len, nk_flags alignment);
NK_API int                      nk_contextual_item_symbol_label(struct nk_context*, enum nk_symbol_type, const char*, nk_flags alignment);
NK_API int                      nk_contextual_item_symbol_text(struct nk_context*, enum nk_symbol_type, const char*, int, nk_flags alignment);
NK_API void                     nk_contextual_close(struct nk_context*);
NK_API void                     nk_contextual_end(struct nk_context*);

/* Tooltip */
NK_API void                     nk_tooltip(struct nk_context*, const char*);
NK_API int                      nk_tooltip_begin(struct nk_context*, struct nk_panel*, float width);
NK_API void                     nk_tooltip_end(struct nk_context*);

/* Menu */
NK_API void                     nk_menubar_begin(struct nk_context*);
NK_API void                     nk_menubar_end(struct nk_context*);
NK_API int                      nk_menu_begin_text(struct nk_context*, struct nk_panel*, const char*, int, nk_flags align, float width);
NK_API int                      nk_menu_begin_label(struct nk_context*, struct nk_panel*, const char*, nk_flags align, float width);
NK_API int                      nk_menu_begin_image(struct nk_context*, struct nk_panel*, const char*, struct nk_image, float width);
NK_API int                      nk_menu_begin_image_text(struct nk_context*, struct nk_panel*, const char*, int,nk_flags align,struct nk_image, float width);
NK_API int                      nk_menu_begin_image_label(struct nk_context*, struct nk_panel*, const char*, nk_flags align,struct nk_image, float width);
NK_API int                      nk_menu_begin_symbol(struct nk_context*, struct nk_panel*, const char*, enum nk_symbol_type, float width);
NK_API int                      nk_menu_begin_symbol_text(struct nk_context*, struct nk_panel*, const char*, int,nk_flags align,enum nk_symbol_type, float width);
NK_API int                      nk_menu_begin_symbol_label(struct nk_context*, struct nk_panel*, const char*, nk_flags align,enum nk_symbol_type, float width);
NK_API int                      nk_menu_item_text(struct nk_context*, const char*, int,nk_flags align);
NK_API int                      nk_menu_item_label(struct nk_context*, const char*, nk_flags alignment);
NK_API int                      nk_menu_item_image_label(struct nk_context*, struct nk_image, const char*, nk_flags alignment);
NK_API int                      nk_menu_item_image_text(struct nk_context*, struct nk_image, const char*, int len, nk_flags alignment);
NK_API int                      nk_menu_item_symbol_text(struct nk_context*, enum nk_symbol_type, const char*, int, nk_flags alignment);
NK_API int                      nk_menu_item_symbol_label(struct nk_context*, enum nk_symbol_type, const char*, nk_flags alignment);
NK_API void                     nk_menu_close(struct nk_context*);
NK_API void                     nk_menu_end(struct nk_context*);

/* Drawing*/
#define                         nk_foreach(c, ctx)for((c)=nk__begin(ctx); (c)!=0; (c)=nk__next(ctx, c))
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
NK_API void                     nk_convert(struct nk_context*, struct nk_buffer *cmds, struct nk_buffer *vertices, struct nk_buffer *elements, const struct nk_convert_config*);
#define                         nk_draw_foreach(cmd,ctx, b) for((cmd)=nk__draw_begin(ctx, b); (cmd)!=0; (cmd)=nk__draw_next(cmd, b, ctx))
#endif

/* User Input */
NK_API void                     nk_input_begin(struct nk_context*);
NK_API void                     nk_input_motion(struct nk_context*, int x, int y);
NK_API void                     nk_input_key(struct nk_context*, enum nk_keys, int down);
NK_API void                     nk_input_button(struct nk_context*, enum nk_buttons, int x, int y, int down);
NK_API void                     nk_input_scroll(struct nk_context*, float y);
NK_API void                     nk_input_char(struct nk_context*, char);
NK_API void                     nk_input_glyph(struct nk_context*, const nk_glyph);
NK_API void                     nk_input_unicode(struct nk_context*, nk_rune);
NK_API void                     nk_input_end(struct nk_context*);

/* Style */
NK_API void                     nk_style_default(struct nk_context*);
NK_API void                     nk_style_from_table(struct nk_context*, const struct nk_color*);
NK_API const char*              nk_style_color_name(enum nk_style_colors);
NK_API void                     nk_style_set_font(struct nk_context*, const struct nk_user_font*);

/* Utilities */
NK_API struct nk_rect           nk_widget_bounds(struct nk_context*);
NK_API struct nk_vec2           nk_widget_position(struct nk_context*);
NK_API struct nk_vec2           nk_widget_size(struct nk_context*);
NK_API int                      nk_widget_is_hovered(struct nk_context*);
NK_API int                      nk_widget_is_mouse_clicked(struct nk_context*, enum nk_buttons);
NK_API int                      nk_widget_has_mouse_click_down(struct nk_context*, enum nk_buttons, int down);
NK_API void                     nk_spacing(struct nk_context*, int cols);

/* base widget function  */
NK_API enum nk_widget_layout_states nk_widget(struct nk_rect*, const struct nk_context*);
NK_API enum nk_widget_layout_states nk_widget_fitting(struct nk_rect*, struct nk_context*, struct nk_vec2);

/* color (conversion user --> nuklear) */
NK_API struct nk_color          nk_rgb(int r, int g, int b);
NK_API struct nk_color          nk_rgb_iv(const int *rgb);
NK_API struct nk_color          nk_rgb_bv(const nk_byte* rgb);
NK_API struct nk_color          nk_rgb_f(float r, float g, float b);
NK_API struct nk_color          nk_rgb_fv(const float *rgb);
NK_API struct nk_color          nk_rgb_hex(const char *rgb);

NK_API struct nk_color          nk_rgba(int r, int g, int b, int a);
NK_API struct nk_color          nk_rgba_u32(nk_uint);
NK_API struct nk_color          nk_rgba_iv(const int *rgba);
NK_API struct nk_color          nk_rgba_bv(const nk_byte *rgba);
NK_API struct nk_color          nk_rgba_f(float r, float g, float b, float a);
NK_API struct nk_color          nk_rgba_fv(const float *rgba);
NK_API struct nk_color          nk_rgba_hex(const char *rgb);

NK_API struct nk_color          nk_hsv(int h, int s, int v);
NK_API struct nk_color          nk_hsv_iv(const int *hsv);
NK_API struct nk_color          nk_hsv_bv(const nk_byte *hsv);
NK_API struct nk_color          nk_hsv_f(float h, float s, float v);
NK_API struct nk_color          nk_hsv_fv(const float *hsv);

NK_API struct nk_color          nk_hsva(int h, int s, int v, int a);
NK_API struct nk_color          nk_hsva_iv(const int *hsva);
NK_API struct nk_color          nk_hsva_bv(const nk_byte *hsva);
NK_API struct nk_color          nk_hsva_f(float h, float s, float v, float a);
NK_API struct nk_color          nk_hsva_fv(const float *hsva);

/* color (conversion nuklear --> user) */
NK_API void                     nk_color_f(float *r, float *g, float *b, float *a, struct nk_color);
NK_API void                     nk_color_fv(float *rgba_out, struct nk_color);
NK_API nk_uint                  nk_color_u32(struct nk_color);
NK_API void                     nk_color_hex_rgba(char *output, struct nk_color);
NK_API void                     nk_color_hex_rgb(char *output, struct nk_color);

NK_API void                     nk_color_hsv_i(int *out_h, int *out_s, int *out_v, struct nk_color);
NK_API void                     nk_color_hsv_b(nk_byte *out_h, nk_byte *out_s, nk_byte *out_v, struct nk_color);
NK_API void                     nk_color_hsv_iv(int *hsv_out, struct nk_color);
NK_API void                     nk_color_hsv_bv(nk_byte *hsv_out, struct nk_color);
NK_API void                     nk_color_hsv_f(float *out_h, float *out_s, float *out_v, struct nk_color);
NK_API void                     nk_color_hsv_fv(float *hsv_out, struct nk_color);

NK_API void                     nk_color_hsva_i(int *h, int *s, int *v, int *a, struct nk_color);
NK_API void                     nk_color_hsva_b(nk_byte *h, nk_byte *s, nk_byte *v, nk_byte *a, struct nk_color);
NK_API void                     nk_color_hsva_iv(int *hsva_out, struct nk_color);
NK_API void                     nk_color_hsva_bv(nk_byte *hsva_out, struct nk_color);
NK_API void                     nk_color_hsva_f(float *out_h, float *out_s, float *out_v, float *out_a, struct nk_color);
NK_API void                     nk_color_hsva_fv(float *hsva_out, struct nk_color);

/* image */
NK_API nk_handle                nk_handle_ptr(void*);
NK_API nk_handle                nk_handle_id(int);
NK_API struct nk_image          nk_image_ptr(void*);
NK_API struct nk_image          nk_image_id(int);
NK_API int                      nk_image_is_subimage(const struct nk_image* img);
NK_API struct nk_image          nk_subimage_ptr(void*, unsigned short w, unsigned short h, struct nk_rect sub_region);
NK_API struct nk_image          nk_subimage_id(int, unsigned short w, unsigned short h, struct nk_rect sub_region);

/* math */
NK_API nk_hash                  nk_murmur_hash(const void *key, int len, nk_hash seed);
NK_API void                     nk_triangle_from_direction(struct nk_vec2 *result, struct nk_rect r, float pad_x, float pad_y, enum nk_heading);

NK_API struct nk_vec2           nk_vec2(float x, float y);
NK_API struct nk_vec2           nk_vec2i(int x, int y);
NK_API struct nk_vec2           nk_vec2v(const float *xy);
NK_API struct nk_vec2           nk_vec2iv(const int *xy);

NK_API struct nk_rect           nk_get_null_rect(void);
NK_API struct nk_rect           nk_rect(float x, float y, float w, float h);
NK_API struct nk_rect           nk_recti(int x, int y, int w, int h);
NK_API struct nk_rect           nk_recta(struct nk_vec2 pos, struct nk_vec2 size);
NK_API struct nk_rect           nk_rectv(const float *xywh);
NK_API struct nk_rect           nk_rectiv(const int *xywh);
NK_API struct nk_vec2           nk_rect_pos(struct nk_rect);
NK_API struct nk_vec2           nk_rect_size(struct nk_rect);

/* string*/
NK_API int                      nk_strlen(const char *str);
NK_API int                      nk_stricmp(const char *s1, const char *s2);
NK_API int                      nk_stricmpn(const char *s1, const char *s2, int n);
NK_API int                      nk_strtof(float *number, const char *buffer);
NK_API int                      nk_strfilter(const char *text, const char *regexp);
NK_API int                      nk_strmatch_fuzzy_string(char const *str, char const *pattern, int *out_score);
NK_API int                      nk_strmatch_fuzzy_text(const char *txt, int txt_len, const char *pattern, int *out_score);
#ifdef NK_INCLUDE_STANDARD_IO
NK_API int                      nk_strfmt(char *buf, int len, const char *fmt,...);
#endif

/* UTF-8 */
NK_API int                      nk_utf_decode(const char*, nk_rune*, int);
NK_API int                      nk_utf_encode(nk_rune, char*, int);
NK_API int                      nk_utf_len(const char*, int byte_len);
NK_API const char*              nk_utf_at(const char *buffer, int length, int index, nk_rune *unicode, int *len);

/* ==============================================================
 *
 *                          MEMORY BUFFER
 *
 * ===============================================================*/
/*  A basic (double)-buffer with linear allocation and resetting as only
    freeing policy. The buffers main purpose is to control all memory management
    inside the GUI toolkit and still leave memory control as much as possible in
    the hand of the user while also making sure the library is easy to use if
    not as much control is needed.
    In general all memory inside this library can be provided from the user in
    three different ways.

    The first way and the one providing most control is by just passing a fixed
    size memory block. In this case all control lies in the hand of the user
    since he can exactly control where the memory comes from and how much memory
    the library should consume. Of course using the fixed size API removes the
    ability to automatically resize a buffer if not enough memory is provided so
    you have to take over the resizing. While being a fixed sized buffer sounds
    quite limiting, it is very effective in this library since the actual memory
    consumption is quite stable and has a fixed upper bound for a lot of cases.

    If you don't want to think about how much memory the library should allocate
    at all time or have a very dynamic UI with unpredictable memory consumption
    habits but still want control over memory allocation you can use the dynamic
    allocator based API. The allocator consists of two callbacks for allocating
    and freeing memory and optional userdata so you can plugin your own allocator.

    The final and easiest way can be used by defining
    NK_INCLUDE_DEFAULT_ALLOCATOR which uses the standard library memory
    allocation functions malloc and free and takes over complete control over
    memory in this library.
*/
struct nk_memory_status {
    void *memory;
    unsigned int type;
    nk_size size;
    nk_size allocated;
    nk_size needed;
    nk_size calls;
};

enum nk_allocation_type {
    NK_BUFFER_FIXED,
    NK_BUFFER_DYNAMIC
};

enum nk_buffer_allocation_type {
    NK_BUFFER_FRONT,
    NK_BUFFER_BACK,
    NK_BUFFER_MAX
};

struct nk_buffer_marker {
    int active;
    nk_size offset;
};

struct nk_memory {void *ptr;nk_size size;};
struct nk_buffer {
    struct nk_buffer_marker marker[NK_BUFFER_MAX];
    /* buffer marker to free a buffer to a certain offset */
    struct nk_allocator pool;
    /* allocator callback for dynamic buffers */
    enum nk_allocation_type type;
    /* memory management type */
    struct nk_memory memory;
    /* memory and size of the current memory block */
    float grow_factor;
    /* growing factor for dynamic memory management */
    nk_size allocated;
    /* total amount of memory allocated */
    nk_size needed;
    /* totally consumed memory given that enough memory is present */
    nk_size calls;
    /* number of allocation calls */
    nk_size size;
    /* current size of the buffer */
};

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void nk_buffer_init_default(struct nk_buffer*);
#endif
NK_API void nk_buffer_init(struct nk_buffer*, const struct nk_allocator*, nk_size size);
NK_API void nk_buffer_init_fixed(struct nk_buffer*, void *memory, nk_size size);
NK_API void nk_buffer_info(struct nk_memory_status*, struct nk_buffer*);
NK_API void nk_buffer_push(struct nk_buffer*, enum nk_buffer_allocation_type type, void *memory, nk_size size, nk_size align);
NK_API void nk_buffer_mark(struct nk_buffer*, enum nk_buffer_allocation_type type);
NK_API void nk_buffer_reset(struct nk_buffer*, enum nk_buffer_allocation_type type);
NK_API void nk_buffer_clear(struct nk_buffer*);
NK_API void nk_buffer_free(struct nk_buffer*);
NK_API void *nk_buffer_memory(struct nk_buffer*);
NK_API const void *nk_buffer_memory_const(const struct nk_buffer*);
NK_API nk_size nk_buffer_total(struct nk_buffer*);

/* ==============================================================
 *
 *                          STRING
 *
 * ===============================================================*/
/*  Basic string buffer which is only used in context with the text editor
 *  to manage and manipulate dynamic or fixed size string content. This is _NOT_
 *  the default string handling method.*/
struct nk_str {
    struct nk_buffer buffer;
    int len; /* in codepoints/runes/glyphs */
};

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void nk_str_init_default(struct nk_str*);
#endif
NK_API void nk_str_init(struct nk_str*, const struct nk_allocator*, nk_size size);
NK_API void nk_str_init_fixed(struct nk_str*, void *memory, nk_size size);
NK_API void nk_str_clear(struct nk_str*);
NK_API void nk_str_free(struct nk_str*);

NK_API int nk_str_append_text_char(struct nk_str*, const char*, int);
NK_API int nk_str_append_str_char(struct nk_str*, const char*);
NK_API int nk_str_append_text_utf8(struct nk_str*, const char*, int);
NK_API int nk_str_append_str_utf8(struct nk_str*, const char*);
NK_API int nk_str_append_text_runes(struct nk_str*, const nk_rune*, int);
NK_API int nk_str_append_str_runes(struct nk_str*, const nk_rune*);

NK_API int nk_str_insert_at_char(struct nk_str*, int pos, const char*, int);
NK_API int nk_str_insert_at_rune(struct nk_str*, int pos, const char*, int);

NK_API int nk_str_insert_text_char(struct nk_str*, int pos, const char*, int);
NK_API int nk_str_insert_str_char(struct nk_str*, int pos, const char*);
NK_API int nk_str_insert_text_utf8(struct nk_str*, int pos, const char*, int);
NK_API int nk_str_insert_str_utf8(struct nk_str*, int pos, const char*);
NK_API int nk_str_insert_text_runes(struct nk_str*, int pos, const nk_rune*, int);
NK_API int nk_str_insert_str_runes(struct nk_str*, int pos, const nk_rune*);

NK_API void nk_str_remove_chars(struct nk_str*, int len);
NK_API void nk_str_remove_runes(struct nk_str *str, int len);
NK_API void nk_str_delete_chars(struct nk_str*, int pos, int len);
NK_API void nk_str_delete_runes(struct nk_str*, int pos, int len);

NK_API char *nk_str_at_char(struct nk_str*, int pos);
NK_API char *nk_str_at_rune(struct nk_str*, int pos, nk_rune *unicode, int *len);
NK_API nk_rune nk_str_rune_at(const struct nk_str*, int pos);
NK_API const char *nk_str_at_char_const(const struct nk_str*, int pos);
NK_API const char *nk_str_at_const(const struct nk_str*, int pos, nk_rune *unicode, int *len);

NK_API char *nk_str_get(struct nk_str*);
NK_API const char *nk_str_get_const(const struct nk_str*);
NK_API int nk_str_len(struct nk_str*);
NK_API int nk_str_len_char(struct nk_str*);

/*===============================================================
 *
 *                      TEXT EDITOR
 *
 * ===============================================================*/
/* Editing text in this library is handled by either `nk_edit_string` or
 * `nk_edit_buffer`. But like almost everything in this library there are multiple
 * ways of doing it and a balance between control and ease of use with memory
 * as well as functionality controlled by flags.
 *
 * This library generally allows three different levels of memory control:
 * First of is the most basic way of just providing a simple char array with
 * string length. This method is probably the easiest way of handling simple
 * user text input. Main upside is complete control over memory while the biggest
 * downside in comparsion with the other two approaches is missing undo/redo.
 *
 * For UIs that require undo/redo the second way was created. It is based on
 * a fixed size nk_text_edit struct, which has an internal undo/redo stack.
 * This is mainly useful if you want something more like a text editor but don't want
 * to have a dynamically growing buffer.
 *
 * The final ways is using a dynamically growing nk_text_edit struct, which
 * has both a default version if you don't care were memory comes from and a
 * allocator version if you do. While the text editor is quite powerful for its
 * complexity I would not recommend editing gigabytes of data with it.
 * It is rather designed for uses cases which make sense for a GUI library not for
 * an full blown text editor.
 */
#ifndef NK_TEXTEDIT_UNDOSTATECOUNT
#define NK_TEXTEDIT_UNDOSTATECOUNT     99
#endif

#ifndef NK_TEXTEDIT_UNDOCHARCOUNT
#define NK_TEXTEDIT_UNDOCHARCOUNT      999
#endif

struct nk_text_edit;
struct nk_clipboard {
    nk_handle userdata;
    nk_paste_f paste;
    nk_copy_f copy;
};

struct nk_text_undo_record {
   int where;
   short insert_length;
   short delete_length;
   short char_storage;
};

struct nk_text_undo_state {
   struct nk_text_undo_record undo_rec[NK_TEXTEDIT_UNDOSTATECOUNT];
   nk_rune undo_char[NK_TEXTEDIT_UNDOCHARCOUNT];
   short undo_point;
   short redo_point;
   short undo_char_point;
   short redo_char_point;
};

enum nk_text_edit_type {
    NK_TEXT_EDIT_SINGLE_LINE,
    NK_TEXT_EDIT_MULTI_LINE
};

enum nk_text_edit_mode {
    NK_TEXT_EDIT_MODE_VIEW,
    NK_TEXT_EDIT_MODE_INSERT,
    NK_TEXT_EDIT_MODE_REPLACE
};

struct nk_text_edit {
    struct nk_clipboard clip;
    struct nk_str string;
    nk_filter filter;
    struct nk_vec2 scrollbar;

    int cursor;
    int select_start;
    int select_end;
    unsigned char mode;
    unsigned char cursor_at_end_of_line;
    unsigned char initialized;
    unsigned char has_preferred_x;
    unsigned char single_line;
    unsigned char active;
    unsigned char padding1;
    float preferred_x;
    struct nk_text_undo_state undo;
};

/* filter function */
NK_API int nk_filter_default(const struct nk_text_edit*, nk_rune unicode);
NK_API int nk_filter_ascii(const struct nk_text_edit*, nk_rune unicode);
NK_API int nk_filter_float(const struct nk_text_edit*, nk_rune unicode);
NK_API int nk_filter_decimal(const struct nk_text_edit*, nk_rune unicode);
NK_API int nk_filter_hex(const struct nk_text_edit*, nk_rune unicode);
NK_API int nk_filter_oct(const struct nk_text_edit*, nk_rune unicode);
NK_API int nk_filter_binary(const struct nk_text_edit*, nk_rune unicode);

/* text editor */
#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void nk_textedit_init_default(struct nk_text_edit*);
#endif
NK_API void nk_textedit_init(struct nk_text_edit*, struct nk_allocator*, nk_size size);
NK_API void nk_textedit_init_fixed(struct nk_text_edit*, void *memory, nk_size size);
NK_API void nk_textedit_free(struct nk_text_edit*);
NK_API void nk_textedit_text(struct nk_text_edit*, const char*, int total_len);
NK_API void nk_textedit_delete(struct nk_text_edit*, int where, int len);
NK_API void nk_textedit_delete_selection(struct nk_text_edit*);
NK_API void nk_textedit_select_all(struct nk_text_edit*);
NK_API int nk_textedit_cut(struct nk_text_edit*);
NK_API int nk_textedit_paste(struct nk_text_edit*, char const*, int len);
NK_API void nk_textedit_undo(struct nk_text_edit*);
NK_API void nk_textedit_redo(struct nk_text_edit*);

/* ===============================================================
 *
 *                          FONT
 *
 * ===============================================================*/
/*  Font handling in this library was designed to be quite customizable and lets
    you decide what you want to use and what you want to provide. In this sense
    there are four different degrees between control and ease of use and two
    different drawing APIs to provide for.

    So first of the easiest way to do font handling is by just providing a
    `nk_user_font` struct which only requires the height in pixel of the used
    font and a callback to calculate the width of a string. This way of handling
    fonts is best fitted for using the normal draw shape command API were you
    do all the text drawing yourself and the library does not require any kind
    of deeper knowledge about which font handling mechanism you use.

    While the first approach works fine if you don't want to use the optional
    vertex buffer output it is not enough if you do. To get font handling working
    for these cases you have to provide two additional parameter inside the
    `nk_user_font`. First a texture atlas handle used to draw text as subimages
    of a bigger font atlas texture and a callback to query a characters glyph
    information (offset, size, ...). So it is still possible to provide your own
    font and use the vertex buffer output.

    The final approach if you do not have a font handling functionality or don't
    want to use it in this library is by using the optional font baker. This API
    is divided into a high- and low-level API with different priorities between
    ease of use and control. Both API's can be used to create a font and 
    font atlas texture and can even be used with or without the vertex buffer
    output. So it still uses the `nk_user_font` struct and the two different
    approaches previously stated still work.
    Now to the difference between the low level API and the high level API. The low
    level API provides a lot of control over the baking process of the font and
    provides total control over memory. It consists of a number of functions that
    need to be called from begin to end and each step requires some additional
    configuration, so it is a lot more complex than the high-level API.
    If you don't want to do all the work required for using the low-level API
    you can use the font atlas API. It provides the same functionality as the
    low-level API but takes away some configuration and all of memory control and
    in term provides a easier to use API.
*/
struct nk_user_font_glyph;
typedef float(*nk_text_width_f)(nk_handle, float h, const char*, int len);
typedef void(*nk_query_font_glyph_f)(nk_handle handle, float font_height,
                                    struct nk_user_font_glyph *glyph,
                                    nk_rune codepoint, nk_rune next_codepoint);

#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
struct nk_user_font_glyph {
    struct nk_vec2 uv[2];
    /* texture coordinates */
    struct nk_vec2 offset;
    /* offset between top left and glyph */
    float width, height;
    /* size of the glyph  */
    float xadvance;
    /* offset to the next glyph */
};
#endif

struct nk_user_font {
    nk_handle userdata;
    /* user provided font handle */
    float height;
    /* max height of the font */
    nk_text_width_f width;
    /* font string width in pixel callback */
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    nk_query_font_glyph_f query;
    /* font glyph callback to query drawing info */
    nk_handle texture;
    /* texture handle to the used font atlas or texture */
#endif
};

#ifdef NK_INCLUDE_FONT_BAKING
enum nk_font_coord_type {
    NK_COORD_UV,
    /* texture coordinates inside font glyphs are clamped between 0-1 */
    NK_COORD_PIXEL
    /* texture coordinates inside font glyphs are in absolute pixel */
};

struct nk_baked_font {
    float height;
    /* height of the font  */
    float ascent, descent;
    /* font glyphs ascent and descent  */
    nk_rune glyph_offset;
    /* glyph array offset inside the font glyph baking output array  */
    nk_rune glyph_count;
    /* number of glyphs of this font inside the glyph baking array output */
    const nk_rune *ranges;
    /* font codepoint ranges as pairs of (from/to) and 0 as last element */
};

struct nk_font_config {
    void *ttf_blob;
    /* pointer to loaded TTF file memory block.
     * NOTE: not needed for nk_font_atlas_add_from_memory and nk_font_atlas_add_from_file. */
    nk_size ttf_size;
    /* size of the loaded TTF file memory block
     * NOTE: not needed for nk_font_atlas_add_from_memory and nk_font_atlas_add_from_file. */

    unsigned char ttf_data_owned_by_atlas;
    /* used inside font atlas: default to: 0*/
    unsigned char merge_mode;
    /* merges this font into the last font */
    unsigned char pixel_snap;
    /* align very character to pixel boundary (if true set oversample (1,1)) */
    unsigned char oversample_v, oversample_h;
    /* rasterize at hight quality for sub-pixel position */
    unsigned char padding[3];

    float size;
    /* baked pixel height of the font */
    enum nk_font_coord_type coord_type;
    /* texture coordinate format with either pixel or UV coordinates */
    struct nk_vec2 spacing;
    /* extra pixel spacing between glyphs  */
    const nk_rune *range;
    /* list of unicode ranges (2 values per range, zero terminated) */
    struct nk_baked_font *font;
    /* font to setup in the baking process: NOTE: not needed for font atlas */
    nk_rune fallback_glyph;
    /* fallback glyph to use if a given rune is not found */
};

struct nk_font_glyph {
    nk_rune codepoint;
    float xadvance;
    float x0, y0, x1, y1, w, h;
    float u0, v0, u1, v1;
};

struct nk_font {
    struct nk_user_font handle;
    struct nk_baked_font info;
    float scale;
    struct nk_font_glyph *glyphs;
    const struct nk_font_glyph *fallback;
    nk_rune fallback_codepoint;
    nk_handle texture;
    int config;
};

enum nk_font_atlas_format {
    NK_FONT_ATLAS_ALPHA8,
    NK_FONT_ATLAS_RGBA32
};

struct nk_font_atlas {
    void *pixel;
    int tex_width;
    int tex_height;
    struct nk_allocator alloc;
    struct nk_recti custom;

    int glyph_count;
    struct nk_font *default_font;
    struct nk_font_glyph *glyphs;
    struct nk_font **fonts;
    struct nk_font_config *config;
    int font_num, font_cap;
};

/* some language glyph codepoint ranges */
NK_API const nk_rune *nk_font_default_glyph_ranges(void);
NK_API const nk_rune *nk_font_chinese_glyph_ranges(void);
NK_API const nk_rune *nk_font_cyrillic_glyph_ranges(void);
NK_API const nk_rune *nk_font_korean_glyph_ranges(void);

/* Font Atlas
 * ---------------------------------------------------------------
 * This is the high level font baking and handling API to generate an image
 * out of font glyphs used to draw text onto the screen. This API takes away
 * some control over the baking process like fine grained memory control and
 * custom baking data but provides additional functionality and easier to
 * use and manage data structures and functions. */
#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void nk_font_atlas_init_default(struct nk_font_atlas*);
#endif
NK_API void nk_font_atlas_init(struct nk_font_atlas*, struct nk_allocator*);
NK_API void nk_font_atlas_begin(struct nk_font_atlas*);
NK_API struct nk_font_config nk_font_config(float pixel_height);
NK_API struct nk_font *nk_font_atlas_add(struct nk_font_atlas*, const struct nk_font_config*);
#ifdef NK_INCLUDE_DEFAULT_FONT
NK_API struct nk_font* nk_font_atlas_add_default(struct nk_font_atlas*, float height, const struct nk_font_config*);
#endif
NK_API struct nk_font* nk_font_atlas_add_from_memory(struct nk_font_atlas *atlas, void *memory, nk_size size, float height, const struct nk_font_config *config);
#ifdef NK_INCLUDE_STANDARD_IO
NK_API struct nk_font* nk_font_atlas_add_from_file(struct nk_font_atlas *atlas, const char *file_path, float height, const struct nk_font_config*);
#endif
NK_API struct nk_font *nk_font_atlas_add_compressed(struct nk_font_atlas*, void *memory, nk_size size, float height, const struct nk_font_config*);
NK_API struct nk_font* nk_font_atlas_add_compressed_base85(struct nk_font_atlas*, const char *data, float height, const struct nk_font_config *config);
NK_API const void* nk_font_atlas_bake(struct nk_font_atlas*, int *width, int *height, enum nk_font_atlas_format);
NK_API void nk_font_atlas_end(struct nk_font_atlas*, nk_handle tex, struct nk_draw_null_texture*);
NK_API void nk_font_atlas_clear(struct nk_font_atlas*);

/* Font
 * -----------------------------------------------------------------
 * The font structure is just a simple container to hold the output of a baking
 * process in the low level API. */
NK_API void nk_font_init(struct nk_font*, float pixel_height, nk_rune fallback_codepoint, struct nk_font_glyph*, const struct nk_baked_font*, nk_handle atlas);
NK_API const struct nk_font_glyph* nk_font_find_glyph(struct nk_font*, nk_rune unicode);

/* Font baking (needs to be called sequentially top to bottom)
 * --------------------------------------------------------------------
 * This is a low level API to bake font glyphs into an image and is more
 * complex than the atlas API but provides more control over the baking
 * process with custom bake data and memory management. */
NK_API void nk_font_bake_memory(nk_size *temporary_memory, int *glyph_count, struct nk_font_config*, int count);
NK_API int nk_font_bake_pack(nk_size *img_memory, int *img_width, int *img_height, struct nk_recti *custom_space, void *temporary_memory, nk_size temporary_size, const struct nk_font_config*, int font_count, struct nk_allocator *alloc);
NK_API void nk_font_bake(void *image_memory, int image_width, int image_height, void *temporary_memory, nk_size temporary_memory_size, struct nk_font_glyph*, int glyphs_count, const struct nk_font_config*, int font_count);
NK_API void nk_font_bake_custom_data(void *img_memory, int img_width, int img_height, struct nk_recti img_dst, const char *image_data_mask, int tex_width, int tex_height,char white,char black);
NK_API void nk_font_bake_convert(void *out_memory, int image_width, int image_height, const void *in_memory);

#endif

/* ===============================================================
 *
 *                          DRAWING
 *
 * ===============================================================*/
/*  This library was designed to be render backend agnostic so it does
    not draw anything to screen. Instead all drawn shapes, widgets
    are made of, are buffered into memory and make up a command queue.
    Each frame therefore fills the command buffer with draw commands
    that then need to be executed by the user and his own render backend.
    After that the command buffer needs to be cleared and a new frame can be
    started. It is probably important to note that the command buffer is the main
    drawing API and the optional vertex buffer API only takes this format and
    converts it into a hardware accessible format.

    Draw commands are divided into filled shapes and shape outlines but only
    filled shapes as well as line, curves and scissor are required to be provided.
    All other shape drawing commands can be used but are not required. This was
    done to allow the maximum number of render backends to be able to use this
    library without you having to do additional work.
*/
enum nk_command_type {
    NK_COMMAND_NOP,
    NK_COMMAND_SCISSOR,
    NK_COMMAND_LINE,
    NK_COMMAND_CURVE,
    NK_COMMAND_RECT,
    NK_COMMAND_RECT_FILLED,
    NK_COMMAND_RECT_MULTI_COLOR,
    NK_COMMAND_CIRCLE,
    NK_COMMAND_CIRCLE_FILLED,
    NK_COMMAND_ARC,
    NK_COMMAND_ARC_FILLED,
    NK_COMMAND_TRIANGLE,
    NK_COMMAND_TRIANGLE_FILLED,
    NK_COMMAND_POLYGON,
    NK_COMMAND_POLYGON_FILLED,
    NK_COMMAND_POLYLINE,
    NK_COMMAND_TEXT,
    NK_COMMAND_IMAGE
};

/* command base and header of every command inside the buffer */
struct nk_command {
    enum nk_command_type type;
    nk_size next;
#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_handle userdata;
#endif
};

struct nk_command_scissor {
    struct nk_command header;
    short x, y;
    unsigned short w, h;
};

struct nk_command_line {
    struct nk_command header;
    unsigned short line_thickness;
    struct nk_vec2i begin;
    struct nk_vec2i end;
    struct nk_color color;
};

struct nk_command_curve {
    struct nk_command header;
    unsigned short line_thickness;
    struct nk_vec2i begin;
    struct nk_vec2i end;
    struct nk_vec2i ctrl[2];
    struct nk_color color;
};

struct nk_command_rect {
    struct nk_command header;
    unsigned short rounding;
    unsigned short line_thickness;
    short x, y;
    unsigned short w, h;
    struct nk_color color;
};

struct nk_command_rect_filled {
    struct nk_command header;
    unsigned short rounding;
    short x, y;
    unsigned short w, h;
    struct nk_color color;
};

struct nk_command_rect_multi_color {
    struct nk_command header;
    short x, y;
    unsigned short w, h;
    struct nk_color left;
    struct nk_color top;
    struct nk_color bottom;
    struct nk_color right;
};

struct nk_command_triangle {
    struct nk_command header;
    unsigned short line_thickness;
    struct nk_vec2i a;
    struct nk_vec2i b;
    struct nk_vec2i c;
    struct nk_color color;
};

struct nk_command_triangle_filled {
    struct nk_command header;
    struct nk_vec2i a;
    struct nk_vec2i b;
    struct nk_vec2i c;
    struct nk_color color;
};

struct nk_command_circle {
    struct nk_command header;
    short x, y;
    unsigned short line_thickness;
    unsigned short w, h;
    struct nk_color color;
};

struct nk_command_circle_filled {
    struct nk_command header;
    short x, y;
    unsigned short w, h;
    struct nk_color color;
};

struct nk_command_arc {
    struct nk_command header;
    short cx, cy;
    unsigned short r;
    unsigned short line_thickness;
    float a[2];
    struct nk_color color;
};

struct nk_command_arc_filled {
    struct nk_command header;
    short cx, cy;
    unsigned short r;
    float a[2];
    struct nk_color color;
};

struct nk_command_polygon {
    struct nk_command header;
    struct nk_color color;
    unsigned short line_thickness;
    unsigned short point_count;
    struct nk_vec2i points[1];
};

struct nk_command_polygon_filled {
    struct nk_command header;
    struct nk_color color;
    unsigned short point_count;
    struct nk_vec2i points[1];
};

struct nk_command_polyline {
    struct nk_command header;
    struct nk_color color;
    unsigned short line_thickness;
    unsigned short point_count;
    struct nk_vec2i points[1];
};

struct nk_command_image {
    struct nk_command header;
    short x, y;
    unsigned short w, h;
    struct nk_image img;
};

struct nk_command_text {
    struct nk_command header;
    const struct nk_user_font *font;
    struct nk_color background;
    struct nk_color foreground;
    short x, y;
    unsigned short w, h;
    float height;
    int length;
    char string[1];
};

enum nk_command_clipping {
    NK_CLIPPING_OFF = nk_false,
    NK_CLIPPING_ON = nk_true
};

struct nk_command_buffer {
    struct nk_buffer *base;
    struct nk_rect clip;
    int use_clipping;
    nk_handle userdata;
    nk_size begin, end, last;
};

/* shape outlines */
NK_API void nk_stroke_line(struct nk_command_buffer *b, float x0, float y0, float x1, float y1, float line_thickness, struct nk_color);
NK_API void nk_stroke_curve(struct nk_command_buffer*, float, float, float, float, float, float, float, float, float line_thickness, struct nk_color);
NK_API void nk_stroke_rect(struct nk_command_buffer*, struct nk_rect, float rounding, float line_thickness, struct nk_color);
NK_API void nk_stroke_circle(struct nk_command_buffer*, struct nk_rect, float line_thickness, struct nk_color);
NK_API void nk_stroke_arc(struct nk_command_buffer*, float cx, float cy, float radius, float a_min, float a_max, float line_thickness, struct nk_color);
NK_API void nk_stroke_triangle(struct nk_command_buffer*, float, float, float, float, float, float, float line_thichness, struct nk_color);
NK_API void nk_stroke_polyline(struct nk_command_buffer*, float *points, int point_count, float line_thickness, struct nk_color col);
NK_API void nk_stroke_polygon(struct nk_command_buffer*, float*, int point_count, float line_thickness, struct nk_color);

/* filled shades */
NK_API void nk_fill_rect(struct nk_command_buffer*, struct nk_rect, float rounding, struct nk_color);
NK_API void nk_fill_rect_multi_color(struct nk_command_buffer*, struct nk_rect, struct nk_color left, struct nk_color top, struct nk_color right, struct nk_color bottom);
NK_API void nk_fill_circle(struct nk_command_buffer*, struct nk_rect, struct nk_color);
NK_API void nk_fill_arc(struct nk_command_buffer*, float cx, float cy, float radius, float a_min, float a_max, struct nk_color);
NK_API void nk_fill_triangle(struct nk_command_buffer*, float x0, float y0, float x1, float y1, float x2, float y2, struct nk_color);
NK_API void nk_fill_polygon(struct nk_command_buffer*, float*, int point_count, struct nk_color);

/* misc */
NK_API void nk_push_scissor(struct nk_command_buffer*, struct nk_rect);
NK_API void nk_draw_image(struct nk_command_buffer*, struct nk_rect, const struct nk_image*);
NK_API void nk_draw_text(struct nk_command_buffer*, struct nk_rect, const char *text, int len, const struct nk_user_font*, struct nk_color, struct nk_color);
NK_API const struct nk_command* nk__next(struct nk_context*, const struct nk_command*);
NK_API const struct nk_command* nk__begin(struct nk_context*);

/* ===============================================================
 *
 *                          INPUT
 *
 * ===============================================================*/
struct nk_mouse_button {
    int down;
    unsigned int clicked;
    struct nk_vec2 clicked_pos;
};

struct nk_mouse {
    struct nk_mouse_button buttons[NK_BUTTON_MAX];
    struct nk_vec2 pos;
    struct nk_vec2 prev;
    struct nk_vec2 delta;
    float scroll_delta;
    unsigned char grab;
    unsigned char grabbed;
    unsigned char ungrab;
};

struct nk_key {
    int down;
    unsigned int clicked;
};

struct nk_keyboard {
    struct nk_key keys[NK_KEY_MAX];
    char text[NK_INPUT_MAX];
    int text_len;
};

struct nk_input {
    struct nk_keyboard keyboard;
    struct nk_mouse mouse;
};

NK_API int nk_input_has_mouse_click(const struct nk_input*, enum nk_buttons);
NK_API int nk_input_has_mouse_click_in_rect(const struct nk_input*, enum nk_buttons, struct nk_rect);
NK_API int nk_input_has_mouse_click_down_in_rect(const struct nk_input*, enum nk_buttons, struct nk_rect, int down);
NK_API int nk_input_is_mouse_click_in_rect(const struct nk_input*, enum nk_buttons, struct nk_rect);
NK_API int nk_input_is_mouse_click_down_in_rect(const struct nk_input *i, enum nk_buttons id, struct nk_rect b, int down);
NK_API int nk_input_any_mouse_click_in_rect(const struct nk_input*, struct nk_rect);
NK_API int nk_input_is_mouse_prev_hovering_rect(const struct nk_input*, struct nk_rect);
NK_API int nk_input_is_mouse_hovering_rect(const struct nk_input*, struct nk_rect);
NK_API int nk_input_mouse_clicked(const struct nk_input*, enum nk_buttons, struct nk_rect);
NK_API int nk_input_is_mouse_down(const struct nk_input*, enum nk_buttons);
NK_API int nk_input_is_mouse_pressed(const struct nk_input*, enum nk_buttons);
NK_API int nk_input_is_mouse_released(const struct nk_input*, enum nk_buttons);
NK_API int nk_input_is_key_pressed(const struct nk_input*, enum nk_keys);
NK_API int nk_input_is_key_released(const struct nk_input*, enum nk_keys);
NK_API int nk_input_is_key_down(const struct nk_input*, enum nk_keys);


/* ===============================================================
 *
 *                          DRAW LIST
 *
 * ===============================================================*/
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
/*  The optional vertex buffer draw list provides a 2D drawing context
    with antialiasing functionality which takes basic filled or outlined shapes
    or a path and outputs vertexes, elements and draw commands.
    The actual draw list API is not required to be used directly while using this
    library since converting the default library draw command output is done by
    just calling `nk_convert` but I decided to still make this library accessible
    since it can be useful.

    The draw list is based on a path buffering and polygon and polyline
    rendering API which allows a lot of ways to draw 2D content to screen.
    In fact it is probably more powerful than needed but allows even more crazy
    things than this library provides by default.
*/
typedef unsigned short nk_draw_index;
typedef nk_uint nk_draw_vertex_color;

enum nk_draw_list_stroke {
    NK_STROKE_OPEN = nk_false,
    /* build up path has no connection back to the beginning */
    NK_STROKE_CLOSED = nk_true
    /* build up path has a connection back to the beginning */
};

struct nk_draw_vertex {
    struct nk_vec2 position;
    struct nk_vec2 uv;
    nk_draw_vertex_color col;
};

struct nk_draw_command {
    unsigned int elem_count;
    /* number of elements in the current draw batch */
    struct nk_rect clip_rect;
    /* current screen clipping rectangle */
    nk_handle texture;
    /* current texture to set */
#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_handle userdata;
#endif
};

struct nk_draw_list {
    float global_alpha;
    enum nk_anti_aliasing shape_AA;
    enum nk_anti_aliasing line_AA;
    struct nk_draw_null_texture null;
    struct nk_rect clip_rect;
    struct nk_buffer *buffer;
    struct nk_buffer *vertices;
    struct nk_buffer *elements;
    unsigned int element_count;
    unsigned int vertex_count;
    nk_size cmd_offset;
    unsigned int cmd_count;
    unsigned int path_count;
    unsigned int path_offset;
    struct nk_vec2 circle_vtx[12];
#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_handle userdata;
#endif
};

/* draw list */
NK_API void nk_draw_list_init(struct nk_draw_list*);
NK_API void nk_draw_list_setup(struct nk_draw_list*, float global_alpha, enum nk_anti_aliasing, enum nk_anti_aliasing, struct nk_draw_null_texture, struct nk_buffer *cmds, struct nk_buffer *vert, struct nk_buffer *elem);
NK_API void nk_draw_list_clear(struct nk_draw_list*);

/* drawing */
#define nk_draw_list_foreach(cmd, can, b) for((cmd)=nk__draw_list_begin(can, b); (cmd)!=0; (cmd)=nk__draw_list_next(cmd, b, can))
NK_API const struct nk_draw_command* nk__draw_list_begin(const struct nk_draw_list*, const struct nk_buffer*);
NK_API const struct nk_draw_command* nk__draw_list_next(const struct nk_draw_command*, const struct nk_buffer*, const struct nk_draw_list*);
NK_API const struct nk_draw_command* nk__draw_begin(const struct nk_context*, const struct nk_buffer*);
NK_API const struct nk_draw_command* nk__draw_next(const struct nk_draw_command*, const struct nk_buffer*, const struct nk_context*);

/* path */
NK_API void nk_draw_list_path_clear(struct nk_draw_list*);
NK_API void nk_draw_list_path_line_to(struct nk_draw_list *list, struct nk_vec2 pos);
NK_API void nk_draw_list_path_arc_to_fast(struct nk_draw_list*, struct nk_vec2 center, float radius, int a_min, int a_max);
NK_API void nk_draw_list_path_arc_to(struct nk_draw_list*, struct nk_vec2 center, float radius, float a_min, float a_max, unsigned int segments);
NK_API void nk_draw_list_path_rect_to(struct nk_draw_list*, struct nk_vec2 a, struct nk_vec2 b, float rounding);
NK_API void nk_draw_list_path_curve_to(struct nk_draw_list*, struct nk_vec2 p2, struct nk_vec2 p3, struct nk_vec2 p4, unsigned int num_segments);
NK_API void nk_draw_list_path_fill(struct nk_draw_list*, struct nk_color);
NK_API void nk_draw_list_path_stroke(struct nk_draw_list*, struct nk_color, enum nk_draw_list_stroke closed, float thickness);

/* stroke */
NK_API void nk_draw_list_stroke_line(struct nk_draw_list*, struct nk_vec2 a, struct nk_vec2 b, struct nk_color, float thickness);
NK_API void nk_draw_list_stroke_rect(struct nk_draw_list*, struct nk_rect rect, struct nk_color, float rounding, float thickness);
NK_API void nk_draw_list_stroke_triangle(struct nk_draw_list*, struct nk_vec2 a, struct nk_vec2 b, struct nk_vec2 c, struct nk_color, float thickness);
NK_API void nk_draw_list_stroke_circle(struct nk_draw_list*, struct nk_vec2 center, float radius, struct nk_color, unsigned int segs, float thickness);
NK_API void nk_draw_list_stroke_curve(struct nk_draw_list*, struct nk_vec2 p0, struct nk_vec2 cp0, struct nk_vec2 cp1, struct nk_vec2 p1, struct nk_color, unsigned int segments, float thickness);
NK_API void nk_draw_list_stroke_poly_line(struct nk_draw_list*, const struct nk_vec2 *pnts, const unsigned int cnt, struct nk_color, enum nk_draw_list_stroke, float thickness, enum nk_anti_aliasing);
/* fill */
NK_API void nk_draw_list_fill_rect(struct nk_draw_list*, struct nk_rect rect, struct nk_color, float rounding);
NK_API void nk_draw_list_fill_rect_multi_color(struct nk_draw_list *list, struct nk_rect rect, struct nk_color left, struct nk_color top, struct nk_color right, struct nk_color bottom);
NK_API void nk_draw_list_fill_triangle(struct nk_draw_list*, struct nk_vec2 a, struct nk_vec2 b, struct nk_vec2 c, struct nk_color);
NK_API void nk_draw_list_fill_circle(struct nk_draw_list*, struct nk_vec2 center, float radius, struct nk_color col, unsigned int segs);
NK_API void nk_draw_list_fill_poly_convex(struct nk_draw_list*, const struct nk_vec2 *points, const unsigned int count, struct nk_color, enum nk_anti_aliasing);

/* misc */
NK_API void nk_draw_list_add_image(struct nk_draw_list*, struct nk_image texture, struct nk_rect rect, struct nk_color);
NK_API void nk_draw_list_add_text(struct nk_draw_list*, const struct nk_user_font*, struct nk_rect, const char *text, int len, float font_height, struct nk_color);
#ifdef NK_INCLUDE_COMMAND_USERDATA
NK_API void nk_draw_list_push_userdata(struct nk_draw_list*, nk_handle userdata);
#endif

#endif

/* ===============================================================
 *
 *                          GUI
 *
 * ===============================================================*/
enum nk_style_item_type {
    NK_STYLE_ITEM_COLOR,
    NK_STYLE_ITEM_IMAGE
};

union nk_style_item_data {
    struct nk_image image;
    struct nk_color color;
};

struct nk_style_item {
    enum nk_style_item_type type;
    union nk_style_item_data data;
};

struct nk_style_text {
    struct nk_color color;
    struct nk_vec2 padding;
};

struct nk_style_button;
struct nk_style_custom_button_drawing {
    void(*button_text)(struct nk_command_buffer*,
        const struct nk_rect *background, const struct nk_rect*,
        nk_flags state, const struct nk_style_button*,
        const char*, int len, nk_flags text_alignment,
        const struct nk_user_font*);
    void(*button_symbol)(struct nk_command_buffer*,
        const struct nk_rect *background, const struct nk_rect*,
        nk_flags state, const struct nk_style_button*,
        enum nk_symbol_type, const struct nk_user_font*);
    void(*button_image)(struct nk_command_buffer*,
        const struct nk_rect *background, const struct nk_rect*,
        nk_flags state, const struct nk_style_button*,
        const struct nk_image *img);
    void(*button_text_symbol)(struct nk_command_buffer*,
        const struct nk_rect *background, const struct nk_rect*,
        const struct nk_rect *symbol, nk_flags state,
        const struct nk_style_button*,
        const char *text, int len, enum nk_symbol_type,
        const struct nk_user_font*);
    void(*button_text_image)(struct nk_command_buffer*,
        const struct nk_rect *background, const struct nk_rect*,
        const struct nk_rect *image, nk_flags state,
        const struct nk_style_button*,
        const char *text, int len, const struct nk_user_font*,
        const struct nk_image *img);
};

struct nk_style_button {
    /* background */
    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    /* text */
    struct nk_color text_background;
    struct nk_color text_normal;
    struct nk_color text_hover;
    struct nk_color text_active;
    nk_flags text_alignment;

    /* properties */
    float border;
    float rounding;
    struct nk_vec2 padding;
    struct nk_vec2 image_padding;
    struct nk_vec2 touch_padding;

    /* optional user callbacks */
    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle userdata);
    struct nk_style_custom_button_drawing draw;
    void(*draw_end)(struct nk_command_buffer*, nk_handle userdata);
};

struct nk_style_toggle;
union nk_style_custom_toggle_drawing {
    void(*radio)(struct nk_command_buffer*, nk_flags state,
        const struct nk_style_toggle *toggle, int active,
        const struct nk_rect *label, const struct nk_rect *selector,
        const struct nk_rect *cursor, const char *string, int len,
        const struct nk_user_font *font);
    void(*checkbox)(struct nk_command_buffer*, nk_flags state,
        const struct nk_style_toggle *toggle, int active,
        const struct nk_rect *label, const struct nk_rect *selector,
        const struct nk_rect *cursor, const char *string, int len,
        const struct nk_user_font *font);
};

struct nk_style_toggle {
    /* background */
    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;

    /* cursor */
    struct nk_style_item cursor_normal;
    struct nk_style_item cursor_hover;

    /* text */
    struct nk_color text_normal;
    struct nk_color text_hover;
    struct nk_color text_active;
    struct nk_color text_background;
    nk_flags text_alignment;

    /* properties */
    struct nk_vec2 padding;
    struct nk_vec2 touch_padding;

    /* optional user callbacks */
    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    union nk_style_custom_toggle_drawing draw;
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_selectable {
    /* background (inactive) */
    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item pressed;

    /* background (active) */
    struct nk_style_item normal_active;
    struct nk_style_item hover_active;
    struct nk_style_item pressed_active;

    /* text color (inactive) */
    struct nk_color text_normal;
    struct nk_color text_hover;
    struct nk_color text_pressed;

    /* text color (active) */
    struct nk_color text_normal_active;
    struct nk_color text_hover_active;
    struct nk_color text_pressed_active;
    struct nk_color text_background;
    nk_flags text_alignment;

    /* properties */
    float rounding;
    struct nk_vec2 padding;
    struct nk_vec2 touch_padding;

    /* optional user callbacks */
    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    void(*draw)(struct nk_command_buffer*,
        nk_flags state, const struct nk_style_selectable*, int active,
        const struct nk_rect*, const char *string, int len,
        nk_flags align, const struct nk_user_font*);
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_slider {
    /* background */
    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    /* background bar */
    struct nk_color bar_normal;
    struct nk_color bar_hover;
    struct nk_color bar_active;
    struct nk_color bar_filled;

    /* cursor */
    struct nk_style_item cursor_normal;
    struct nk_style_item cursor_hover;
    struct nk_style_item cursor_active;

    /* properties */
    float border;
    float rounding;
    float bar_height;
    struct nk_vec2 padding;
    struct nk_vec2 spacing;
    struct nk_vec2 cursor_size;

    /* optional buttons */
    int show_buttons;
    struct nk_style_button inc_button;
    struct nk_style_button dec_button;
    enum nk_symbol_type inc_symbol;
    enum nk_symbol_type dec_symbol;

    /* optional user callbacks */
    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    void(*draw)(struct nk_command_buffer*, nk_flags state,
        const struct nk_style_slider*, const struct nk_rect *bar,
        const struct nk_rect *cursor, float min, float value, float max);
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_progress {
    /* background */
    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;

    /* cursor */
    struct nk_style_item cursor_normal;
    struct nk_style_item cursor_hover;
    struct nk_style_item cursor_active;

    /* properties */
    float rounding;
    struct nk_vec2 padding;

    /* optional user callbacks */
    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    void(*draw)(struct nk_command_buffer*, nk_flags state,
        const struct nk_style_progress*, const struct nk_rect *bounds,
        const struct nk_rect *cursor, nk_size value, nk_size max);
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_scrollbar {
    /* background */
    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    /* cursor */
    struct nk_style_item cursor_normal;
    struct nk_style_item cursor_hover;
    struct nk_style_item cursor_active;

    /* properties */
    float border;
    float rounding;
    struct nk_vec2 padding;

    /* optional buttons */
    int show_buttons;
    struct nk_style_button inc_button;
    struct nk_style_button dec_button;
    enum nk_symbol_type inc_symbol;
    enum nk_symbol_type dec_symbol;

    /* optional user callbacks */
    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    void(*draw)(struct nk_command_buffer*, nk_flags state,
        const struct nk_style_scrollbar*, const struct nk_rect *scroll,
        const struct nk_rect *cursor);
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_edit {
    /* background */
    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;
    struct nk_style_scrollbar scrollbar;

    /* cursor  */
    struct nk_color cursor_normal;
    struct nk_color cursor_hover;
    struct nk_color cursor_text_normal;
    struct nk_color cursor_text_hover;

    /* text (unselected) */
    struct nk_color text_normal;
    struct nk_color text_hover;
    struct nk_color text_active;

    /* text (selected) */
    struct nk_color selected_normal;
    struct nk_color selected_hover;
    struct nk_color selected_text_normal;
    struct nk_color selected_text_hover;

    /* properties */
    float border;
    float rounding;
    float cursor_size;
    struct nk_vec2 scrollbar_size;
    struct nk_vec2 padding;
    float row_padding;
};

struct nk_style_property {
    /* background */
    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    /* text */
    struct nk_color label_normal;
    struct nk_color label_hover;
    struct nk_color label_active;

    /* symbols */
    enum nk_symbol_type sym_left;
    enum nk_symbol_type sym_right;

    /* properties */
    float border;
    float rounding;
    struct nk_vec2 padding;

    struct nk_style_edit edit;
    struct nk_style_button inc_button;
    struct nk_style_button dec_button;

    /* optional user callbacks */
    nk_handle userdata;
    void(*draw_begin)(struct nk_command_buffer*, nk_handle);
    void(*draw)(struct nk_command_buffer*, const struct nk_style_property*,
        const struct nk_rect*, const struct nk_rect *label, nk_flags state,
        const char *name, int len, const struct nk_user_font*);
    void(*draw_end)(struct nk_command_buffer*, nk_handle);
};

struct nk_style_chart {
    /* colors */
    struct nk_style_item background;
    struct nk_color border_color;
    struct nk_color selected_color;
    struct nk_color color;

    /* properties */
    float border;
    float rounding;
    struct nk_vec2 padding;
};

struct nk_style_combo {
    /* background */
    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;
    struct nk_color border_color;

    /* label */
    struct nk_color label_normal;
    struct nk_color label_hover;
    struct nk_color label_active;

    /* symbol */
    struct nk_color symbol_normal;
    struct nk_color symbol_hover;
    struct nk_color symbol_active;

    /* button */
    struct nk_style_button button;
    enum nk_symbol_type sym_normal;
    enum nk_symbol_type sym_hover;
    enum nk_symbol_type sym_active;

    /* properties */
    float border;
    float rounding;
    struct nk_vec2 content_padding;
    struct nk_vec2 button_padding;
    struct nk_vec2 spacing;
};

struct nk_style_tab {
    /* background */
    struct nk_style_item background;
    struct nk_color border_color;
    struct nk_color text;

    /* button */
    struct nk_style_button tab_button;
    struct nk_style_button node_button;
    enum nk_symbol_type sym_minimize;
    enum nk_symbol_type sym_maximize;

    /* properties */
    float border;
    float rounding;
    struct nk_vec2 padding;
    struct nk_vec2 spacing;
};

enum nk_style_header_align {
    NK_HEADER_LEFT,
    NK_HEADER_RIGHT
};

struct nk_style_window_header {
    /* background */
    struct nk_style_item normal;
    struct nk_style_item hover;
    struct nk_style_item active;

    /* button */
    struct nk_style_button close_button;
    struct nk_style_button minimize_button;
    enum nk_symbol_type close_symbol;
    enum nk_symbol_type minimize_symbol;
    enum nk_symbol_type maximize_symbol;

    /* title */
    struct nk_color label_normal;
    struct nk_color label_hover;
    struct nk_color label_active;

    /* properties */
    enum nk_style_header_align align;
    struct nk_vec2 padding;
    struct nk_vec2 label_padding;
    struct nk_vec2 spacing;
};

struct nk_style_window {
    struct nk_style_window_header header;
    struct nk_style_item fixed_background;
    struct nk_color background;

    struct nk_color border_color;
    struct nk_color combo_border_color;
    struct nk_color contextual_border_color;
    struct nk_color menu_border_color;
    struct nk_color group_border_color;
    struct nk_color tooltip_border_color;

    struct nk_style_item scaler;
    struct nk_vec2 footer_padding;

    float border;
    float combo_border;
    float contextual_border;
    float menu_border;
    float group_border;
    float tooltip_border;

    float rounding;
    struct nk_vec2 scaler_size;
    struct nk_vec2 padding;
    struct nk_vec2 spacing;
    struct nk_vec2 scrollbar_size;
    struct nk_vec2 min_size;
};

struct nk_style {
    struct nk_user_font font;
    struct nk_style_text text;
    struct nk_style_button button;
    struct nk_style_button contextual_button;
    struct nk_style_button menu_button;
    struct nk_style_toggle option;
    struct nk_style_toggle checkbox;
    struct nk_style_selectable selectable;
    struct nk_style_slider slider;
    struct nk_style_progress progress;
    struct nk_style_property property;
    struct nk_style_edit edit;
    struct nk_style_chart chart;
    struct nk_style_scrollbar scrollh;
    struct nk_style_scrollbar scrollv;
    struct nk_style_tab tab;
    struct nk_style_combo combo;
    struct nk_style_window window;
};

NK_API struct nk_style_item nk_style_item_image(struct nk_image img);
NK_API struct nk_style_item nk_style_item_color(struct nk_color);
NK_API struct nk_style_item nk_style_item_hide(void);

/*==============================================================
 *                          PANEL
 * =============================================================*/
#ifndef NK_CHART_MAX_SLOT
#define NK_CHART_MAX_SLOT 4
#endif

struct nk_chart_slot {
    enum nk_chart_type type;
    float min, max, range;
    int count;
    struct nk_vec2 last;
    int index;

};

struct nk_chart {
    struct nk_chart_slot slots[NK_CHART_MAX_SLOT];
    int slot;
    float x, y, w, h;
};

struct nk_row_layout {
    int type;
    int index;
    float height;
    int columns;
    const float *ratio;
    float item_width, item_height;
    float item_offset;
    float filled;
    struct nk_rect item;
    int tree_depth;
};

struct nk_popup_buffer {
    nk_size begin;
    nk_size parent;
    nk_size last;
    nk_size end;
    int active;
};

struct nk_menu_state {
    float x, y, w, h;
    struct nk_scroll offset;
};

struct nk_panel {
    nk_flags flags;
    struct nk_rect bounds;
    struct nk_scroll *offset;
    float at_x, at_y, max_x;
    float width, height;
    float footer_h;
    float header_h;
    float border;
    struct nk_rect clip;
    struct nk_menu_state menu;
    struct nk_row_layout row;
    struct nk_chart chart;
    struct nk_popup_buffer popup_buffer;
    struct nk_command_buffer *buffer;
    struct nk_panel *parent;
};

/*==============================================================
 *                          WINDOW
 * =============================================================*/
struct nk_table;

enum nk_window_flags {
    NK_WINDOW_PRIVATE       = NK_FLAG(9),
    /* dummy flag which mark the beginning of the private window flag part */
    NK_WINDOW_ROM           = NK_FLAG(10),
    /* sets the window into a read only mode and does not allow input changes */
    NK_WINDOW_HIDDEN        = NK_FLAG(11),
    /* Hides the window and stops any window interaction and drawing can be set
     * by user input or by closing the window */
    NK_WINDOW_MINIMIZED     = NK_FLAG(12),
    /* marks the window as minimized */
    NK_WINDOW_SUB           = NK_FLAG(13),
    /* Marks the window as subwindow of another window*/
    NK_WINDOW_GROUP         = NK_FLAG(14),
    /* Marks the window as window widget group */
    NK_WINDOW_POPUP         = NK_FLAG(15),
    /* Marks the window as a popup window */
    NK_WINDOW_NONBLOCK      = NK_FLAG(16),
    /* Marks the window as a nonblock popup window */
    NK_WINDOW_CONTEXTUAL    = NK_FLAG(17),
    /* Marks the window as a combo box or menu */
    NK_WINDOW_COMBO         = NK_FLAG(18),
    /* Marks the window as a combo box */
    NK_WINDOW_MENU          = NK_FLAG(19),
    /* Marks the window as a menu */
    NK_WINDOW_TOOLTIP       = NK_FLAG(20),
    /* Marks the window as a menu */
    NK_WINDOW_REMOVE_ROM    = NK_FLAG(21)
    /* Removes the read only mode at the end of the window */
};

struct nk_popup_state {
    struct nk_window *win;
    enum nk_window_flags type;
    nk_hash name;
    int active;
    unsigned combo_count;
    unsigned con_count, con_old;
    unsigned active_con;
};

struct nk_edit_state {
    nk_hash name;
    unsigned int seq;
    unsigned int old;
    int active, prev;
    int cursor;
    int sel_start;
    int sel_end;
    struct nk_scroll scrollbar;
    unsigned char mode;
    unsigned char single_line;
};

struct nk_property_state {
    int active, prev;
    char buffer[NK_MAX_NUMBER_BUFFER];
    int length;
    int cursor;
    nk_hash name;
    unsigned int seq;
    unsigned int old;
    int state;
};

struct nk_scaling_state {
    struct nk_vec2 start_size;
    int active;
};

struct nk_window {
    unsigned int seq;
    nk_hash name;
    nk_flags flags;
    struct nk_rect bounds;
    struct nk_scroll scrollbar;
    struct nk_command_buffer buffer;
    struct nk_panel *layout;

    /* persistent widget state */
    struct nk_property_state property;
    struct nk_popup_state popup;
    struct nk_edit_state edit;
    struct nk_scaling_state scaling;

    struct nk_table *tables;
    unsigned short table_count;
    unsigned short table_size;

    /* window list hooks */
    struct nk_window *next;
    struct nk_window *prev;
    struct nk_window *parent;
};

/*==============================================================
 *                          CONTEXT
 * =============================================================*/
struct nk_page_element;
struct nk_context {
/* public: can be accessed freely */
    struct nk_input input;
    struct nk_style style;
    struct nk_buffer memory;
    struct nk_clipboard clip;
    nk_flags last_widget_state;

/* private:
    should only be accessed if you
    know what you are doing */
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    struct nk_draw_list draw_list;
#endif
#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_handle userdata;
#endif

    /* text editor objects are quite big because they have a internal
     * undo/redo stack. It therefore does not make sense to have one for
     * each window for temporary use cases, so I only provide *one* instance
     * for all windows. This works because the content is cleared anyway */
    struct nk_text_edit text_edit;

    /* windows */
    int build;
    void *pool;
    struct nk_window *begin;
    struct nk_window *end;
    struct nk_window *active;
    struct nk_window *current;
    struct nk_page_element *freelist;
    unsigned int count;
    unsigned int seq;
};

#ifdef __cplusplus
}
#endif
#endif /* NK_H_ */

/*
 * ==============================================================
 *
 *                          IMPLEMENTATION
 *
 * ===============================================================
 */
#ifdef NK_IMPLEMENTATION

#ifndef NK_POOL_DEFAULT_CAPACITY
#define NK_POOL_DEFAULT_CAPACITY 16
#endif

#ifndef NK_DEFAULT_COMMAND_BUFFER_SIZE
#define NK_DEFAULT_COMMAND_BUFFER_SIZE (4*1024)
#endif

#ifndef NK_BUFFER_DEFAULT_INITIAL_SIZE
#define NK_BUFFER_DEFAULT_INITIAL_SIZE (4*1024)
#endif

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
#include <stdlib.h> /* malloc, free */
#endif
#ifdef NK_INCLUDE_STANDARD_IO
#include <stdio.h> /* fopen, fclose,... */
#include <stdarg.h>
#endif

#ifndef NK_ASSERT
#include <assert.h>
#define NK_ASSERT(expr) assert(expr)
#endif

#ifndef NK_MEMSET
#define NK_MEMSET nk_memset
#endif
#ifndef NK_MEMCPY
#define NK_MEMCPY nk_memcopy
#endif
#ifndef NK_SQRT
#define NK_SQRT nk_sqrt
#endif
#ifndef NK_SIN
#define NK_SIN nk_sin
#endif
#ifndef NK_COS
#define NK_COS nk_cos
#endif

/* ==============================================================
 *                          MATH
 * =============================================================== */
#define NK_MIN(a,b) ((a) < (b) ? (a) : (b))
#define NK_MAX(a,b) ((a) < (b) ? (b) : (a))
#define NK_CLAMP(i,v,x) (NK_MAX(NK_MIN(v,x), i))

#define NK_PI 3.141592654f
#define NK_UTF_INVALID 0xFFFD
#define NK_MAX_FLOAT_PRECISION 2

#define NK_UNUSED(x) ((void)(x))
#define NK_SATURATE(x) (NK_MAX(0, NK_MIN(1.0f, x)))
#define NK_LEN(a) (sizeof(a)/sizeof(a)[0])
#define NK_ABS(a) (((a) < 0) ? -(a) : (a))
#define NK_BETWEEN(x, a, b) ((a) <= (x) && (x) <= (b))
#define NK_INBOX(px, py, x, y, w, h)\
    (NK_BETWEEN(px,x,x+w) && NK_BETWEEN(py,y,y+h))
#define NK_INTERSECT(x0, y0, w0, h0, x1, y1, w1, h1) \
    (!(((x1 > (x0 + w0)) || ((x1 + w1) < x0) || (y1 > (y0 + h0)) || (y1 + h1) < y0)))
#define NK_CONTAINS(x, y, w, h, bx, by, bw, bh)\
    (NK_INBOX(x,y, bx, by, bw, bh) && NK_INBOX(x+w,y+h, bx, by, bw, bh))

#define nk_vec2_sub(a, b) nk_vec2((a).x - (b).x, (a).y - (b).y)
#define nk_vec2_add(a, b) nk_vec2((a).x + (b).x, (a).y + (b).y)
#define nk_vec2_len_sqr(a) ((a).x*(a).x+(a).y*(a).y)
#define nk_vec2_muls(a, t) nk_vec2((a).x * (t), (a).y * (t))

#define nk_ptr_add(t, p, i) ((t*)((void*)((nk_byte*)(p) + (i))))
#define nk_ptr_add_const(t, p, i) ((const t*)((const void*)((const nk_byte*)(p) + (i))))
#define nk_zero_struct(s) nk_zero(&s, sizeof(s))

/* ==============================================================
 *                          ALIGNMENT
 * =============================================================== */
/* Pointer to Integer type conversion for pointer alignment */
#if defined(__PTRDIFF_TYPE__) /* This case should work for GCC*/
# define NK_UINT_TO_PTR(x) ((void*)(__PTRDIFF_TYPE__)(x))
# define NK_PTR_TO_UINT(x) ((nk_size)(__PTRDIFF_TYPE__)(x))
#elif !defined(__GNUC__) /* works for compilers other than LLVM */
# define NK_UINT_TO_PTR(x) ((void*)&((char*)0)[x])
# define NK_PTR_TO_UINT(x) ((nk_size)(((char*)x)-(char*)0))
#elif defined(NK_USE_FIXED_TYPES) /* used if we have <stdint.h> */
# define NK_UINT_TO_PTR(x) ((void*)(uintptr_t)(x))
# define NK_PTR_TO_UINT(x) ((uintptr_t)(x))
#else /* generates warning but works */
# define NK_UINT_TO_PTR(x) ((void*)(x))
# define NK_PTR_TO_UINT(x) ((nk_size)(x))
#endif

#define NK_ALIGN_PTR(x, mask)\
    (NK_UINT_TO_PTR((NK_PTR_TO_UINT((nk_byte*)(x) + (mask-1)) & ~(mask-1))))
#define NK_ALIGN_PTR_BACK(x, mask)\
    (NK_UINT_TO_PTR((NK_PTR_TO_UINT((nk_byte*)(x)) & ~(mask-1))))

#define NK_OFFSETOF(st,m) ((nk_ptr)&(((st*)0)->m))
#define NK_CONTAINER_OF(ptr,type,member)\
    (type*)((void*)((char*)(1 ? (ptr): &((type*)0)->member) - NK_OFFSETOF(type, member)))

#ifdef __cplusplus
template<typename T> struct nk_alignof;
template<typename T, int size_diff> struct nk_helper{enum {value = size_diff};};
template<typename T> struct nk_helper<T,0>{enum {value = nk_alignof<T>::value};};
template<typename T> struct nk_alignof{struct Big {T x; char c;}; enum {
    diff = sizeof(Big) - sizeof(T), value = nk_helper<Big, diff>::value};};
#define NK_ALIGNOF(t) (nk_alignof<t>::value);
#else
#define NK_ALIGNOF(t) ((char*)(&((struct {char c; t _h;}*)0)->_h) - (char*)0)
#endif

/* make sure correct type size */
typedef int nk__check_size[(sizeof(nk_size) >= sizeof(void*)) ? 1 : -1];
typedef int nk__check_ptr[(sizeof(nk_ptr) == sizeof(void*)) ? 1 : -1];
typedef int nk__check_flags[(sizeof(nk_flags) >= 4) ? 1 : -1];
typedef int nk__check_rune[(sizeof(nk_rune) >= 4) ? 1 : -1];
typedef int nk__check_ushort[(sizeof(nk_ushort) == 2) ? 1 : -1];
typedef int nk__check_short[(sizeof(nk_short) == 2) ? 1 : -1];
typedef int nk__check_uint[(sizeof(nk_uint) == 4) ? 1 : -1];
typedef int nk__check_int[(sizeof(nk_int) == 4) ? 1 : -1];
typedef int nk__check_byte[(sizeof(nk_byte) == 1) ? 1 : -1];

NK_GLOBAL const struct nk_rect nk_null_rect = {-8192.0f, -8192.0f, 16384, 16384};
NK_GLOBAL const float NK_FLOAT_PRECISION = 0.00000000000001f;
/*
 * ==============================================================
 *
 *                          MATH
 *
 * ===============================================================
 */
/*  Since nuklear is supposed to work on all systems providing floating point
    math without any dependencies I also had to implement my own math functions
    for sqrt, sin and cos. Since the actual highly accurate implementations for
    the standard library functions are quite complex and I do not need high
    precision for my use cases I use approximations.

    Sqrt
    ----
    For square root nuklear uses the famous fast inverse square root:
    https://en.wikipedia.org/wiki/Fast_inverse_square_root with
    slightly tweaked magic constant. While on todays hardware it is
    probably not faster it is still fast and accurate enough for
    nuklear's use cases. IMPORTANT: this requires float format IEEE 754

    Sine/Cosine
    -----------
    All constants inside both function are generated Remez's minimax
    approximations for value range 0...2*PI. The reason why I decided to
    approximate exactly that range is that nuklear only needs sine and
    cosine to generate circles which only requires that exact range.
    In addition I used Remez instead of Taylor for additional precision:
    www.lolengine.net/blog/2011/12/21/better-function-approximatations.

    The tool I used to generate constants for both sine and cosine
    (it can actually approximate a lot more functions) can be
    found here: www.lolengine.net/wiki/oss/lolremez
*/
NK_INTERN float
nk_inv_sqrt(float number)
{
    float x2;
    const float threehalfs = 1.5f;
    union {nk_uint i; float f;} conv = {0};
    conv.f = number;
    x2 = number * 0.5f;
    conv.i = 0x5f375A84 - (conv.i >> 1);
    conv.f = conv.f * (threehalfs - (x2 * conv.f * conv.f));
    return conv.f;
}

NK_INTERN float
nk_sqrt(float x)
{
    return x * nk_inv_sqrt(x);
}

NK_INTERN float
nk_sin(float x)
{
    NK_STORAGE const float a0 = +1.91059300966915117e-31f;
    NK_STORAGE const float a1 = +1.00086760103908896f;
    NK_STORAGE const float a2 = -1.21276126894734565e-2f;
    NK_STORAGE const float a3 = -1.38078780785773762e-1f;
    NK_STORAGE const float a4 = -2.67353392911981221e-2f;
    NK_STORAGE const float a5 = +2.08026600266304389e-2f;
    NK_STORAGE const float a6 = -3.03996055049204407e-3f;
    NK_STORAGE const float a7 = +1.38235642404333740e-4f;
    return a0 + x*(a1 + x*(a2 + x*(a3 + x*(a4 + x*(a5 + x*(a6 + x*a7))))));
}

NK_INTERN float
nk_cos(float x)
{
    NK_STORAGE const float a0 = +1.00238601909309722f;
    NK_STORAGE const float a1 = -3.81919947353040024e-2f;
    NK_STORAGE const float a2 = -3.94382342128062756e-1f;
    NK_STORAGE const float a3 = -1.18134036025221444e-1f;
    NK_STORAGE const float a4 = +1.07123798512170878e-1f;
    NK_STORAGE const float a5 = -1.86637164165180873e-2f;
    NK_STORAGE const float a6 = +9.90140908664079833e-4f;
    NK_STORAGE const float a7 = -5.23022132118824778e-14f;
    return a0 + x*(a1 + x*(a2 + x*(a3 + x*(a4 + x*(a5 + x*(a6 + x*a7))))));
}

NK_INTERN nk_uint
nk_round_up_pow2(nk_uint v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

NK_API struct nk_rect
nk_get_null_rect(void)
{
    return nk_null_rect;
}

NK_API struct nk_rect
nk_rect(float x, float y, float w, float h)
{
    struct nk_rect r;
    r.x = x, r.y = y;
    r.w = w, r.h = h;
    return r;
}

NK_API struct nk_rect
nk_recti(int x, int y, int w, int h)
{
    struct nk_rect r;
    r.x = (float)x;
    r.y = (float)y;
    r.w = (float)w;
    r.h = (float)h;
    return r;
}

NK_API struct nk_rect
nk_recta(struct nk_vec2 pos, struct nk_vec2 size)
{
    return nk_rect(pos.x, pos.y, size.x, size.y);
}

NK_API struct nk_rect
nk_rectv(const float *r)
{
    return nk_rect(r[0], r[1], r[2], r[3]);
}

NK_API struct nk_rect
nk_rectiv(const int *r)
{
    return nk_recti(r[0], r[1], r[2], r[3]);
}

NK_API struct nk_vec2
nk_rect_pos(struct nk_rect r)
{
    struct nk_vec2 ret;
    ret.x = r.x; ret.y = r.y;
    return ret;
}

NK_API struct nk_vec2
nk_rect_size(struct nk_rect r)
{
    struct nk_vec2 ret;
    ret.x = r.w; ret.y = r.h;
    return ret;
}

NK_INTERN struct nk_rect
nk_shrink_rect(struct nk_rect r, float amount)
{
    struct nk_rect res;
    r.w = NK_MAX(r.w, 2 * amount);
    r.h = NK_MAX(r.h, 2 * amount);
    res.x = r.x + amount;
    res.y = r.y + amount;
    res.w = r.w - 2 * amount;
    res.h = r.h - 2 * amount;
    return res;
}

NK_INTERN struct nk_rect
nk_pad_rect(struct nk_rect r, struct nk_vec2 pad)
{
    r.w = NK_MAX(r.w, 2 * pad.x);
    r.h = NK_MAX(r.h, 2 * pad.y);
    r.x += pad.x; r.y += pad.y;
    r.w -= 2 * pad.x;
    r.h -= 2 * pad.y;
    return r;
}

NK_API struct nk_vec2
nk_vec2(float x, float y)
{
    struct nk_vec2 ret;
    ret.x = x; ret.y = y;
    return ret;
}

NK_API struct nk_vec2
nk_vec2i(int x, int y)
{
    struct nk_vec2 ret;
    ret.x = (float)x;
    ret.y = (float)y;
    return ret;
}

NK_API struct nk_vec2
nk_vec2v(const float *v)
{
    return nk_vec2(v[0], v[1]);
}

NK_API struct nk_vec2
nk_vec2iv(const int *v)
{
    return nk_vec2i(v[0], v[1]);
}

/*
 * ==============================================================
 *
 *                          UTIL
 *
 * ===============================================================
 */
NK_INTERN int nk_str_match_here(const char *regexp, const char *text);
NK_INTERN int nk_str_match_star(int c, const char *regexp, const char *text);
NK_INTERN int nk_is_lower(int c) {return (c >= 'a' && c <= 'z') || (c >= 0xE0 && c <= 0xFF);}
NK_INTERN int nk_is_upper(int c){return (c >= 'A' && c <= 'Z') || (c >= 0xC0 && c <= 0xDF);}
NK_INTERN int nk_to_upper(int c) {return (c >= 'a' && c <= 'z') ? (c - ('a' - 'A')) : c;}
NK_INTERN int nk_to_lower(int c) {return (c >= 'A' && c <= 'Z') ? (c - ('a' + 'A')) : c;}

NK_INTERN void*
nk_memcopy(void *dst0, const void *src0, nk_size length)
{
    nk_ptr t;
    char *dst = (char*)dst0;
    const char *src = (const char*)src0;
    if (length == 0 || dst == src)
        goto done;

    #define nk_word int
    #define nk_wsize sizeof(nk_word)
    #define nk_wmask (nk_wsize-1)
    #define NK_TLOOP(s) if (t) NK_TLOOP1(s)
    #define NK_TLOOP1(s) do { s; } while (--t)

    if (dst < src) {
        t = (nk_ptr)src; /* only need low bits */
        if ((t | (nk_ptr)dst) & nk_wmask) {
            if ((t ^ (nk_ptr)dst) & nk_wmask || length < nk_wsize)
                t = length;
            else
                t = nk_wsize - (t & nk_wmask);
            length -= t;
            NK_TLOOP1(*dst++ = *src++);
        }
        t = length / nk_wsize;
        NK_TLOOP(*(nk_word*)(void*)dst = *(const nk_word*)(const void*)src;
            src += nk_wsize; dst += nk_wsize);
        t = length & nk_wmask;
        NK_TLOOP(*dst++ = *src++);
    } else {
        src += length;
        dst += length;
        t = (nk_ptr)src;
        if ((t | (nk_ptr)dst) & nk_wmask) {
            if ((t ^ (nk_ptr)dst) & nk_wmask || length <= nk_wsize)
                t = length;
            else
                t &= nk_wmask;
            length -= t;
            NK_TLOOP1(*--dst = *--src);
        }
        t = length / nk_wsize;
        NK_TLOOP(src -= nk_wsize; dst -= nk_wsize;
            *(nk_word*)(void*)dst = *(const nk_word*)(const void*)src);
        t = length & nk_wmask;
        NK_TLOOP(*--dst = *--src);
    }
    #undef nk_word
    #undef nk_wsize
    #undef nk_wmask
    #undef NK_TLOOP
    #undef NK_TLOOP1
done:
    return (dst0);
}

NK_INTERN void
nk_memset(void *ptr, int c0, nk_size size)
{
    #define nk_word unsigned
    #define nk_wsize sizeof(nk_word)
    #define nk_wmask (nk_wsize - 1)
    nk_byte *dst = (nk_byte*)ptr;
    unsigned c = 0;
    nk_size t = 0;

    if ((c = (nk_byte)c0) != 0) {
        c = (c << 8) | c; /* at least 16-bits  */
        if (sizeof(unsigned int) > 2)
            c = (c << 16) | c; /* at least 32-bits*/
    }

    /* too small of a word count */
    dst = (nk_byte*)ptr;
    if (size < 3 * nk_wsize) {
        while (size--) *dst++ = (nk_byte)c0;
        return;
    }

    /* align destination */
    if ((t = NK_PTR_TO_UINT(dst) & nk_wmask) != 0) {
        t = nk_wsize -t;
        size -= t;
        do {
            *dst++ = (nk_byte)c0;
        } while (--t != 0);
    }

    /* fill word */
    t = size / nk_wsize;
    do {
        *(nk_word*)((void*)dst) = c;
        dst += nk_wsize;
    } while (--t != 0);

    /* fill trailing bytes */
    t = (size & nk_wmask);
    if (t != 0) {
        do {
            *dst++ = (nk_byte)c0;
        } while (--t != 0);
    }

    #undef nk_word
    #undef nk_wsize
    #undef nk_wmask
}

NK_INTERN void
nk_zero(void *ptr, nk_size size)
{
    NK_ASSERT(ptr);
    NK_MEMSET(ptr, 0, size);
}

NK_API int
nk_strlen(const char *str)
{
    int siz = 0;
    NK_ASSERT(str);
    while (str && *str++ != '\0') siz++;
    return siz;
}

NK_API int
nk_strtof(float *number, const char *buffer)
{
    float m;
    float neg = 1.0f;
    const char *p = buffer;
    float floatvalue = 0;

    NK_ASSERT(number);
    NK_ASSERT(buffer);
    if (!number || !buffer) return 0;
    *number = 0;

    /* skip whitespace */
    while (*p && *p == ' ') p++;
    if (*p == '-') {
        neg = -1.0f;
        p++;
    }

    while( *p && *p != '.' && *p != 'e' ) {
        floatvalue = floatvalue * 10.0f + (float) (*p - '0');
        p++;
    }

    if ( *p == '.' ) {
        p++;
        for(m = 0.1f; *p && *p != 'e'; p++ ) {
            floatvalue = floatvalue + (float) (*p - '0') * m;
            m *= 0.1f;
        }
    }
    if ( *p == 'e' ) {
        int i, pow, div;
        p++;
        if ( *p == '-' ) {
            div = nk_true;
            p++;
        } else if ( *p == '+' ) {
            div = nk_false;
            p++;
        } else div = nk_false;

        for ( pow = 0; *p; p++ )
            pow = pow * 10 + (int) (*p - '0');

        for ( m = 1.0, i = 0; i < pow; i++ )
            m *= 10.0f;

        if ( div )
            floatvalue /= m;
        else floatvalue *= m;
    }
    *number = floatvalue * neg;
    return 1;
}

NK_API int
nk_stricmp(const char *s1, const char *s2)
{
    nk_int c1,c2,d;
    do {
        c1 = *s1++;
        c2 = *s2++;
        d = c1 - c2;
        while (d) {
            if (c1 <= 'Z' && c1 >= 'A') {
                d += ('a' - 'A');
                if (!d) break;
            }
            if (c2 <= 'Z' && c2 >= 'A') {
                d -= ('a' - 'A');
                if (!d) break;
            }
            return ((d >= 0) << 1) - 1;
        }
    } while (c1);
    return 0;
}

NK_API int
nk_stricmpn(const char *s1, const char *s2, int n)
{
    int c1,c2,d;
    NK_ASSERT(n >= 0);
    do {
        c1 = *s1++;
        c2 = *s2++;
        if (!n--) return 0;

        d = c1 - c2;
        while (d) {
            if (c1 <= 'Z' && c1 >= 'A') {
                d += ('a' - 'A');
                if (!d) break;
            }
            if (c2 <= 'Z' && c2 >= 'A') {
                d -= ('a' - 'A');
                if (!d) break;
            }
            return ((d >= 0) << 1) - 1;
        }
    } while (c1);
    return 0;
}

NK_INTERN int
nk_str_match_here(const char *regexp, const char *text)
{
    if (regexp[0] == '\0')
        return 1;
    if (regexp[1] == '*')
        return nk_str_match_star(regexp[0], regexp+2, text);
    if (regexp[0] == '$' && regexp[1] == '\0')
        return *text == '\0';
    if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
        return nk_str_match_here(regexp+1, text+1);
    return 0;
}

NK_INTERN int
nk_str_match_star(int c, const char *regexp, const char *text)
{
    do {/* a '* matches zero or more instances */
        if (nk_str_match_here(regexp, text))
            return 1;
    } while (*text != '\0' && (*text++ == c || c == '.'));
    return 0;
}

NK_API int
nk_strfilter(const char *text, const char *regexp)
{
    /*
    c    matches any literal character c
    .    matches any single character
    ^    matches the beginning of the input string
    $    matches the end of the input string
    *    matches zero or more occurrences of the previous character*/
    if (regexp[0] == '^')
        return nk_str_match_here(regexp+1, text);
    do {    /* must look even if string is empty */
        if (nk_str_match_here(regexp, text))
            return 1;
    } while (*text++ != '\0');
    return 0;
}

NK_API int
nk_strmatch_fuzzy_text(const char *str, int str_len,
    const char *pattern, int *out_score)
{
    /* Returns true if each character in pattern is found sequentially within str
     * if found then outScore is also set. Score value has no intrinsic meaning.
     * Range varies with pattern. Can only compare scores with same search pattern. */

    /* ------- scores --------- */
    /* bonus for adjacent matches */
    #define NK_ADJACENCY_BONUS 5
    /* bonus if match occurs after a separator */
    #define NK_SEPARATOR_BONUS 10
    /* bonus if match is uppercase and prev is lower */
    #define NK_CAMEL_BONUS 10
    /* penalty applied for every letter in str before the first match */
    #define NK_LEADING_LETTER_PENALTY (-3)
    /* maximum penalty for leading letters */
    #define NK_MAX_LEADING_LETTER_PENALTY (-9)
    /* penalty for every letter that doesn't matter */
    #define NK_UNMATCHED_LETTER_PENALTY (-1)


    /* loop variables */
    int score = 0;
    char const * pattern_iter = pattern;
    int str_iter = 0;
    int prev_matched = nk_false;
    int prev_lower = nk_false;
    /* true so if first letter match gets separator bonus*/
    int prev_separator = nk_true;

    /* use "best" matched letter if multiple string letters match the pattern */
    char const * best_letter = 0;
    int best_letter_score = 0;

    /* loop over strings */
    NK_ASSERT(str);
    NK_ASSERT(pattern);
    if (!str || !str_len || !pattern) return 0;
    while (str_iter < str_len)
    {
        const char pattern_letter = *pattern_iter;
        const char str_letter = str[str_iter];

        int next_match = *pattern_iter != '\0' &&
            nk_to_lower(pattern_letter) == nk_to_lower(str_letter);
        int rematch = best_letter && nk_to_lower(*best_letter) == nk_to_lower(str_letter);

        int advanced = next_match && best_letter;
        int pattern_repeat = best_letter && *pattern_iter != '\0';
        pattern_repeat = pattern_repeat &&
            nk_to_lower(*best_letter) == nk_to_lower(pattern_letter);

        if (advanced || pattern_repeat) {
            score += best_letter_score;
            best_letter = 0;
            best_letter_score = 0;
        }

        if (next_match || rematch)
        {
            int new_score = 0;
            /* Apply penalty for each letter before the first pattern match */
            if (pattern_iter == pattern)
            {
                int count = (int)(&str[str_iter] - str);
                int penalty = NK_LEADING_LETTER_PENALTY * count;
                if (penalty < NK_MAX_LEADING_LETTER_PENALTY)
                    penalty = NK_MAX_LEADING_LETTER_PENALTY;

                score += penalty;
            }

            /* apply bonus for consecutive bonuses */
            if (prev_matched)
                new_score += NK_ADJACENCY_BONUS;

            /* apply bonus for matches after a separator */
            if (prev_separator)
                new_score += NK_SEPARATOR_BONUS;

            /* apply bonus across camel case boundaries */
            if (prev_lower && nk_is_upper(str_letter))
                new_score += NK_CAMEL_BONUS;

            /* update pattern iter IFF the next pattern letter was matched */
            if (next_match)
                ++pattern_iter;

            /* update best letter in str which may be for a "next" letter or a rematch */
            if (new_score >= best_letter_score)
            {
                /* apply penalty for now skipped letter */
                if (best_letter != 0)
                    score += NK_UNMATCHED_LETTER_PENALTY;

                best_letter = &str[str_iter];
                best_letter_score = new_score;
            }

            prev_matched = nk_true;
        }
        else
        {
            score += NK_UNMATCHED_LETTER_PENALTY;
            prev_matched = nk_false;
        }

        /* separators should be more easily defined */
        prev_lower = nk_is_lower(str_letter) != 0;
        prev_separator = str_letter == '_' || str_letter == ' ';

        ++str_iter;
    }

    /* apply score for last match */
    if (best_letter)
        score += best_letter_score;

    /* did not match full pattern */
    if (*pattern_iter != '\0')
        return nk_false;

    if (out_score)
        *out_score = score;
    return nk_true;
}

NK_API int
nk_strmatch_fuzzy_string(char const *str, char const *pattern, int *out_score)
{return nk_strmatch_fuzzy_text(str, nk_strlen(str), pattern, out_score);}

#ifdef NK_INCLUDE_STANDARD_IO
NK_API int
nk_strfmt(char *buf, int buf_size, const char *fmt,...)
{
    int w;
    va_list args;
    va_start(args, fmt);
    w = vsnprintf(buf, (nk_size)buf_size, fmt, args);
    va_end(args);
    buf[buf_size-1] = 0;
    return (w == -1) ?(int)buf_size:w;
}

NK_INTERN int
nk_strfmtv(char *buf, int buf_size, const char *fmt, va_list args)
{
    int w = vsnprintf(buf, (nk_size)buf_size, fmt, args);
    buf[buf_size-1] = 0;
    return (w == -1) ? (int)buf_size:w;
}
#endif

NK_INTERN int
nk_string_float_limit(char *string, int prec)
{
    int dot = 0;
    char *c = string;
    while (*c) {
        if (*c == '.') {
            dot = 1;
            c++;
            continue;
        }
        if (dot == (prec+1)) {
            *c = 0;
            break;
        }
        if (dot > 0) dot++;
        c++;
    }
    return (int)(c - string);
}

NK_INTERN float
nk_pow(float x, int n)
{
    /*  check the sign of n */
    float r = 1;
    int plus = n >= 0;
    n = (plus) ? n : -n;
    while (n > 0) {
        if ((n & 1) == 1)
            r *= x;
        n /= 2;
        x *= x;
    }
    return plus ? r : 1.0f / r;
}

NK_INTERN int
nk_ifloor(float x)
{
    x = (float)((int)x - ((x < 0.0) ? 1 : 0));
    return (int)x;
}

NK_INTERN int
nk_iceil(float x)
{
    if (x >= 0) {
        int i = (int)x;
        return i;
    } else {
        int t = (int)x;
        float r = x - (float)t;
        return (r > 0.0f) ? t+1: t;
    }
}

NK_INTERN int
nk_log10(float n)
{
    int neg;
    int ret;
    int exp = 0;

    neg = (n < 0) ? 1 : 0;
    ret = (neg) ? (int)-n : (int)n;
    while ((ret / 10) > 0) {
        ret /= 10;
        exp++;
    }
    if (neg) exp = -exp;
    return exp;
}

NK_INTERN int
nk_ftos(char *s, float n)
{
    int useExp = 0;
    int digit = 0, m = 0, m1 = 0;
    char *c = s;
    int neg = 0;

    if (n == 0.0f) {
        s[0] = '0'; s[1] = '\0';
        return 1;
    }

    neg = (n < 0);
    if (neg) n = -n;

    /* calculate magnitude */
    m = nk_log10(n);
    useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
    if (neg) *(c++) = '-';

    /* set up for scientific notation */
    if (useExp) {
        if (m < 0)
           m -= 1;
        n = n / nk_pow(10.0, m);
        m1 = m;
        m = 0;
    }
    if (m < 1.0) {
        m = 0;
    }

    /* convert the number */
    while (n > NK_FLOAT_PRECISION || m >= 0) {
        float weight = nk_pow(10.0, m);
        if (weight > 0) {
            float t = (float)n / weight;
            digit = nk_ifloor(t);
            n -= ((float)digit * weight);
            *(c++) = (char)('0' + (char)digit);
        }
        if (m == 0 && n > 0)
            *(c++) = '.';
        m--;
    }

    if (useExp) {
        /* convert the exponent */
        int i, j;
        *(c++) = 'e';
        if (m1 > 0) {
            *(c++) = '+';
        } else {
            *(c++) = '-';
            m1 = -m1;
        }
        m = 0;
        while (m1 > 0) {
            *(c++) = (char)('0' + (char)(m1 % 10));
            m1 /= 10;
            m++;
        }
        c -= m;
        for (i = 0, j = m-1; i<j; i++, j--) {
            /* swap without temporary */
            c[i] ^= c[j];
            c[j] ^= c[i];
            c[i] ^= c[j];
        }
        c += m;
    }
    *(c) = '\0';
    return (int)(c - s);
}

NK_API nk_hash
nk_murmur_hash(const void * key, int len, nk_hash seed)
{
    /* 32-Bit MurmurHash3: https://code.google.com/p/smhasher/wiki/MurmurHash3*/
    #define NK_ROTL(x,r) ((x) << (r) | ((x) >> (32 - r)))
    union {const nk_uint *i; const nk_byte *b;} conv = {0};
    const nk_byte *data = (const nk_byte*)key;
    const int nblocks = len/4;
    nk_uint h1 = seed;
    const nk_uint c1 = 0xcc9e2d51;
    const nk_uint c2 = 0x1b873593;
    const nk_byte *tail;
    const nk_uint *blocks;
    nk_uint k1;
    int i;

    /* body */
    if (!key) return 0;
    conv.b = (data + nblocks*4);
    blocks = (const nk_uint*)conv.i;
    for (i = -nblocks; i; ++i) {
        k1 = blocks[i];
        k1 *= c1;
        k1 = NK_ROTL(k1,15);
        k1 *= c2;

        h1 ^= k1;
        h1 = NK_ROTL(h1,13);
        h1 = h1*5+0xe6546b64;
    }

    /* tail */
    tail = (const nk_byte*)(data + nblocks*4);
    k1 = 0;
    switch (len & 3) {
    case 3: k1 ^= (nk_uint)(tail[2] << 16);
    case 2: k1 ^= (nk_uint)(tail[1] << 8u);
    case 1: k1 ^= tail[0];
            k1 *= c1;
            k1 = NK_ROTL(k1,15);
            k1 *= c2;
            h1 ^= k1;
    default: break;
    }

    /* finalization */
    h1 ^= (nk_uint)len;
    /* fmix32 */
    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

    #undef NK_ROTL
    return h1;
}

#ifdef NK_INCLUDE_STANDARD_IO
NK_INTERN char*
nk_file_load(const char* path, nk_size* siz, struct nk_allocator *alloc)
{
    char *buf;
    FILE *fd;
    long ret;

    NK_ASSERT(path);
    NK_ASSERT(siz);
    NK_ASSERT(alloc);
    if (!path || !siz || !alloc)
        return 0;

    fd = fopen(path, "rb");
    if (!fd) return 0;
    fseek(fd, 0, SEEK_END);
    ret = ftell(fd);
    if (ret < 0) {
        fclose(fd);
        return 0;
    }
    *siz = (nk_size)ret;
    fseek(fd, 0, SEEK_SET);
    buf = (char*)alloc->alloc(alloc->userdata,0, *siz);
    NK_ASSERT(buf);
    if (!buf) {
        fclose(fd);
        return 0;
    }
    *siz = (nk_size)fread(buf, *siz, 1, fd);
    fclose(fd);
    return buf;
}
#endif

/*
 * ==============================================================
 *
 *                          COLOR
 *
 * ===============================================================
 */
NK_INTERN int
nk_parse_hex(const char *p, int length)
{
    int i = 0;
    int len = 0;
    while (len < length) {
        i <<= 4;
        if (p[len] >= 'a' && p[len] <= 'f')
            i += ((p[len] - 'a') + 10);
        else if (p[len] >= 'A' && p[len] <= 'F') {
            i += ((p[len] - 'A') + 10);
        } else i += (p[len] - '0');
        len++;
    }
    return i;
}

NK_API struct nk_color
nk_rgba(int r, int g, int b, int a)
{
    struct nk_color ret;
    ret.r = (nk_byte)NK_CLAMP(0, r, 255);
    ret.g = (nk_byte)NK_CLAMP(0, g, 255);
    ret.b = (nk_byte)NK_CLAMP(0, b, 255);
    ret.a = (nk_byte)NK_CLAMP(0, a, 255);
    return ret;
}

NK_API struct nk_color
nk_rgb_hex(const char *rgb)
{
    struct nk_color col;
    const char *c = rgb;
    if (*c == '#') c++;
    col.r = (nk_byte)nk_parse_hex(c, 2);
    col.g = (nk_byte)nk_parse_hex(c+2, 2);
    col.b = (nk_byte)nk_parse_hex(c+4, 2);
    col.a = 255;
    return col;
}

NK_API struct nk_color
nk_rgba_hex(const char *rgb)
{
    struct nk_color col;
    const char *c = rgb;
    if (*c == '#') c++;
    col.r = (nk_byte)nk_parse_hex(c, 2);
    col.g = (nk_byte)nk_parse_hex(c+2, 2);
    col.b = (nk_byte)nk_parse_hex(c+4, 2);
    col.a = (nk_byte)nk_parse_hex(c+6, 2);
    return col;
}

NK_API void
nk_color_hex_rgba(char *output, struct nk_color col)
{
    #define NK_TO_HEX(i) ((i) <= 9 ? '0' + (i): 'A' - 10 + (i))
    output[0] = (char)NK_TO_HEX((col.r & 0x0F));
    output[1] = (char)NK_TO_HEX((col.r & 0xF0) >> 4);
    output[2] = (char)NK_TO_HEX((col.g & 0x0F));
    output[3] = (char)NK_TO_HEX((col.g & 0xF0) >> 4);
    output[4] = (char)NK_TO_HEX((col.b & 0x0F));
    output[5] = (char)NK_TO_HEX((col.b & 0xF0) >> 4);
    output[6] = (char)NK_TO_HEX((col.a & 0x0F));
    output[7] = (char)NK_TO_HEX((col.a & 0xF0) >> 4);
    output[8] = '\0';
    #undef NK_TO_HEX
}

NK_API void
nk_color_hex_rgb(char *output, struct nk_color col)
{
    #define NK_TO_HEX(i) ((i) <= 9 ? '0' + (i): 'A' - 10 + (i))
    output[0] = (char)NK_TO_HEX((col.r & 0x0F));
    output[1] = (char)NK_TO_HEX((col.r & 0xF0) >> 4);
    output[2] = (char)NK_TO_HEX((col.g & 0x0F));
    output[3] = (char)NK_TO_HEX((col.g & 0xF0) >> 4);
    output[4] = (char)NK_TO_HEX((col.b & 0x0F));
    output[5] = (char)NK_TO_HEX((col.b & 0xF0) >> 4);
    output[6] = '\0';
    #undef NK_TO_HEX
}

NK_API struct nk_color
nk_rgba_iv(const int *c)
{
    return nk_rgba(c[0], c[1], c[2], c[3]);
}

NK_API struct nk_color
nk_rgba_bv(const nk_byte *c)
{
    return nk_rgba(c[0], c[1], c[2], c[3]);
}

NK_API struct nk_color
nk_rgb(int r, int g, int b)
{
    struct nk_color ret;
    ret.r =(nk_byte)NK_CLAMP(0, r, 255);
    ret.g =(nk_byte)NK_CLAMP(0, g, 255);
    ret.b =(nk_byte)NK_CLAMP(0, b, 255);
    ret.a =(nk_byte)255;
    return ret;
}

NK_API struct nk_color
nk_rgb_iv(const int *c)
{
    return nk_rgb(c[0], c[1], c[2]);
}

NK_API struct nk_color
nk_rgb_bv(const nk_byte* c)
{
    return nk_rgb(c[0], c[1], c[2]);
}

NK_API struct nk_color
nk_rgba_u32(nk_uint in)
{
    struct nk_color ret;
    ret.r = (in & 0xFF);
    ret.g = ((in >> 8) & 0xFF);
    ret.b = ((in >> 16) & 0xFF);
    ret.a = (nk_byte)((in >> 24) & 0xFF);
    return ret;
}

NK_API struct nk_color
nk_rgba_f(float r, float g, float b, float a)
{
    struct nk_color ret;
    ret.r = (nk_byte)(NK_SATURATE(r) * 255.0f);
    ret.g = (nk_byte)(NK_SATURATE(g) * 255.0f);
    ret.b = (nk_byte)(NK_SATURATE(b) * 255.0f);
    ret.a = (nk_byte)(NK_SATURATE(a) * 255.0f);
    return ret;
}

NK_API struct nk_color
nk_rgba_fv(const float *c)
{
    return nk_rgba_f(c[0], c[1], c[2], c[3]);
}

NK_API struct nk_color
nk_rgb_f(float r, float g, float b)
{
    struct nk_color ret;
    ret.r = (nk_byte)(NK_SATURATE(r) * 255.0f);
    ret.g = (nk_byte)(NK_SATURATE(g) * 255.0f);
    ret.b = (nk_byte)(NK_SATURATE(b) * 255.0f);
    ret.a = 255;
    return ret;
}

NK_API struct nk_color
nk_rgb_fv(const float *c)
{
    return nk_rgb_f(c[0], c[1], c[2]);
}

NK_API struct nk_color
nk_hsv(int h, int s, int v)
{
    return nk_hsva(h, s, v, 255);
}

NK_API struct nk_color
nk_hsv_iv(const int *c)
{
    return nk_hsv(c[0], c[1], c[2]);
}

NK_API struct nk_color
nk_hsv_bv(const nk_byte *c)
{
    return nk_hsv(c[0], c[1], c[2]);
}

NK_API struct nk_color
nk_hsv_f(float h, float s, float v)
{
    return nk_hsva_f(h, s, v, 1.0f);
}

NK_API struct nk_color
nk_hsv_fv(const float *c)
{
    return nk_hsv_f(c[0], c[1], c[2]);
}

NK_API struct nk_color
nk_hsva(int h, int s, int v, int a)
{
    float hf = ((float)NK_CLAMP(0, h, 255)) / 255.0f;
    float sf = ((float)NK_CLAMP(0, s, 255)) / 255.0f;
    float vf = ((float)NK_CLAMP(0, v, 255)) / 255.0f;
    float af = ((float)NK_CLAMP(0, a, 255)) / 255.0f;
    return nk_hsva_f(hf, sf, vf, af);
}

NK_API struct nk_color
nk_hsva_iv(const int *c)
{
    return nk_hsva(c[0], c[1], c[2], c[3]);
}

NK_API struct nk_color
nk_hsva_bv(const nk_byte *c)
{
    return nk_hsva(c[0], c[1], c[2], c[3]);
}

NK_API struct nk_color
nk_hsva_f(float h, float s, float v, float a)
{
    struct nk_colorf {float r,g,b;} out = {0,0,0};
    float p, q, t, f;
    int i;

    if (s <= 0.0f) {
        out.r = v; out.g = v; out.b = v;
        return nk_rgb_f(out.r, out.g, out.b);
    }

    h = h / (60.0f/360.0f);
    i = (int)h;
    f = h - (float)i;
    p = v * (1.0f - s);
    q = v * (1.0f - (s * f));
    t = v * (1.0f - s * (1.0f - f));

    switch (i) {
    case 0: out.r = v; out.g = t; out.b = p; break;
    case 1: out.r = q; out.g = v; out.b = p; break;
    case 2: out.r = p; out.g = v; out.b = t; break;
    case 3: out.r = p; out.g = q; out.b = v; break;
    case 4: out.r = t; out.g = p; out.b = v; break;
    case 5: default: out.r = v; out.g = p; out.b = q; break;
    }
    return nk_rgba_f(out.r, out.g, out.b, a);
}

NK_API struct nk_color
nk_hsva_fv(const float *c)
{
    return nk_hsva_f(c[0], c[1], c[2], c[3]);
}

NK_API nk_uint
nk_color_u32(struct nk_color in)
{
    nk_uint out = (nk_uint)in.r;
    out |= ((nk_uint)in.g << 8);
    out |= ((nk_uint)in.b << 16);
    out |= ((nk_uint)in.a << 24);
    return out;
}

NK_API void
nk_color_f(float *r, float *g, float *b, float *a, struct nk_color in)
{
    NK_STORAGE const float s = 1.0f/255.0f;
    *r = (float)in.r * s;
    *g = (float)in.g * s;
    *b = (float)in.b * s;
    *a = (float)in.a * s;
}

NK_API void
nk_color_fv(float *c, struct nk_color in)
{
    nk_color_f(&c[0], &c[1], &c[2], &c[3], in);
}

NK_API void
nk_color_hsv_f(float *out_h, float *out_s, float *out_v, struct nk_color in)
{
    float a;
    nk_color_hsva_f(out_h, out_s, out_v, &a, in);
}

NK_API void
nk_color_hsv_fv(float *out, struct nk_color in)
{
    float a;
    nk_color_hsva_f(&out[0], &out[1], &out[2], &a, in);
}

NK_API void
nk_color_hsva_f(float *out_h, float *out_s,
    float *out_v, float *out_a, struct nk_color in)
{
    float chroma;
    float K = 0.0f;
    float r,g,b,a;

    nk_color_f(&r,&g,&b,&a, in);
    if (g < b) {
        const float t = g; g = b; b = t;
        K = -1.f;
    }
    if (r < g) {
        const float t = r; r = g; g = t;
        K = -2.f/6.0f - K;
    }
    chroma = r - ((g < b) ? g: b);
    *out_h = NK_ABS(K + (g - b)/(6.0f * chroma + 1e-20f));
    *out_s = chroma / (r + 1e-20f);
    *out_v = r;
    *out_a = (float)in.a / 255.0f;
}

NK_API void
nk_color_hsva_fv(float *out, struct nk_color in)
{
    nk_color_hsva_f(&out[0], &out[1], &out[2], &out[3], in);
}

NK_API void
nk_color_hsva_i(int *out_h, int *out_s, int *out_v,
                int *out_a, struct nk_color in)
{
    float h,s,v,a;
    nk_color_hsva_f(&h, &s, &v, &a, in);
    *out_h = (nk_byte)(h * 255.0f);
    *out_s = (nk_byte)(s * 255.0f);
    *out_v = (nk_byte)(v * 255.0f);
    *out_a = (nk_byte)(a * 255.0f);
}

NK_API void
nk_color_hsva_iv(int *out, struct nk_color in)
{
    nk_color_hsva_i(&out[0], &out[1], &out[2], &out[3], in);
}

NK_API void
nk_color_hsva_bv(nk_byte *out, struct nk_color in)
{
    int tmp[4];
    nk_color_hsva_i(&tmp[0], &tmp[1], &tmp[2], &tmp[3], in);
    out[0] = (nk_byte)tmp[0];
    out[1] = (nk_byte)tmp[1];
    out[2] = (nk_byte)tmp[2];
    out[3] = (nk_byte)tmp[3];
}

NK_API void
nk_color_hsva_b(nk_byte *h, nk_byte *s, nk_byte *v, nk_byte *a, struct nk_color in)
{
    int tmp[4];
    nk_color_hsva_i(&tmp[0], &tmp[1], &tmp[2], &tmp[3], in);
    *h = (nk_byte)tmp[0];
    *s = (nk_byte)tmp[1];
    *v = (nk_byte)tmp[2];
    *a = (nk_byte)tmp[3];
}

NK_API void
nk_color_hsv_i(int *out_h, int *out_s, int *out_v, struct nk_color in)
{
    int a;
    nk_color_hsva_i(out_h, out_s, out_v, &a, in);
}

NK_API void
nk_color_hsv_b(nk_byte *out_h, nk_byte *out_s, nk_byte *out_v, struct nk_color in)
{
    int tmp[4];
    nk_color_hsva_i(&tmp[0], &tmp[1], &tmp[2], &tmp[3], in);
    *out_h = (nk_byte)tmp[0];
    *out_s = (nk_byte)tmp[1];
    *out_v = (nk_byte)tmp[2];
}

NK_API void
nk_color_hsv_iv(int *out, struct nk_color in)
{
    nk_color_hsv_i(&out[0], &out[1], &out[2], in);
}

NK_API void
nk_color_hsv_bv(nk_byte *out, struct nk_color in)
{
    int tmp[4];
    nk_color_hsv_i(&tmp[0], &tmp[1], &tmp[2], in);
    out[0] = (nk_byte)tmp[0];
    out[1] = (nk_byte)tmp[1];
    out[2] = (nk_byte)tmp[2];
}
/*
 * ==============================================================
 *
 *                          IMAGE
 *
 * ===============================================================
 */
NK_API nk_handle
nk_handle_ptr(void *ptr)
{
    nk_handle handle = {0};
    handle.ptr = ptr;
    return handle;
}

NK_API nk_handle
nk_handle_id(int id)
{
    nk_handle handle;
    nk_zero_struct(handle);
    handle.id = id;
    return handle;
}

NK_API struct nk_image
nk_subimage_ptr(void *ptr, unsigned short w, unsigned short h, struct nk_rect r)
{
    struct nk_image s;
    nk_zero(&s, sizeof(s));
    s.handle.ptr = ptr;
    s.w = w; s.h = h;
    s.region[0] = (unsigned short)r.x;
    s.region[1] = (unsigned short)r.y;
    s.region[2] = (unsigned short)r.w;
    s.region[3] = (unsigned short)r.h;
    return s;
}

NK_API struct nk_image
nk_subimage_id(int id, unsigned short w, unsigned short h, struct nk_rect r)
{
    struct nk_image s;
    nk_zero(&s, sizeof(s));
    s.handle.id = id;
    s.w = w; s.h = h;
    s.region[0] = (unsigned short)r.x;
    s.region[1] = (unsigned short)r.y;
    s.region[2] = (unsigned short)r.w;
    s.region[3] = (unsigned short)r.h;
    return s;
}

NK_API struct nk_image
nk_image_ptr(void *ptr)
{
    struct nk_image s;
    nk_zero(&s, sizeof(s));
    NK_ASSERT(ptr);
    s.handle.ptr = ptr;
    s.w = 0; s.h = 0;
    s.region[0] = 0;
    s.region[1] = 0;
    s.region[2] = 0;
    s.region[3] = 0;
    return s;
}

NK_API struct nk_image
nk_image_id(int id)
{
    struct nk_image s;
    nk_zero(&s, sizeof(s));
    s.handle.id = id;
    s.w = 0; s.h = 0;
    s.region[0] = 0;
    s.region[1] = 0;
    s.region[2] = 0;
    s.region[3] = 0;
    return s;
}

NK_API int
nk_image_is_subimage(const struct nk_image* img)
{
    NK_ASSERT(img);
    return !(img->w == 0 && img->h == 0);
}

NK_INTERN void
nk_unify(struct nk_rect *clip, const struct nk_rect *a, float x0, float y0,
    float x1, float y1)
{
    NK_ASSERT(a);
    NK_ASSERT(clip);
    clip->x = NK_MAX(a->x, x0);
    clip->y = NK_MAX(a->y, y0);
    clip->w = NK_MIN(a->x + a->w, x1) - clip->x;
    clip->h = NK_MIN(a->y + a->h, y1) - clip->y;
    clip->w = NK_MAX(0, clip->w);
    clip->h = NK_MAX(0, clip->h);
}

NK_API void
nk_triangle_from_direction(struct nk_vec2 *result, struct nk_rect r,
    float pad_x, float pad_y, enum nk_heading direction)
{
    float w_half, h_half;
    NK_ASSERT(result);

    r.w = NK_MAX(2 * pad_x, r.w);
    r.h = NK_MAX(2 * pad_y, r.h);
    r.w = r.w - 2 * pad_x;
    r.h = r.h - 2 * pad_y;

    r.x = r.x + pad_x;
    r.y = r.y + pad_y;

    w_half = r.w / 2.0f;
    h_half = r.h / 2.0f;

    if (direction == NK_UP) {
        result[0] = nk_vec2(r.x + w_half, r.y);
        result[1] = nk_vec2(r.x + r.w, r.y + r.h);
        result[2] = nk_vec2(r.x, r.y + r.h);
    } else if (direction == NK_RIGHT) {
        result[0] = nk_vec2(r.x, r.y);
        result[1] = nk_vec2(r.x + r.w, r.y + h_half);
        result[2] = nk_vec2(r.x, r.y + r.h);
    } else if (direction == NK_DOWN) {
        result[0] = nk_vec2(r.x, r.y);
        result[1] = nk_vec2(r.x + r.w, r.y);
        result[2] = nk_vec2(r.x + w_half, r.y + r.h);
    } else {
        result[0] = nk_vec2(r.x, r.y + h_half);
        result[1] = nk_vec2(r.x + r.w, r.y);
        result[2] = nk_vec2(r.x + r.w, r.y + r.h);
    }
}

NK_INTERN int
nk_text_clamp(const struct nk_user_font *font, const char *text,
    int text_len, float space, int *glyphs, float *text_width)
{
    int glyph_len = 0;
    float last_width = 0;
    nk_rune unicode = 0;
    float width = 0;
    int len = 0;
    int g = 0;

    glyph_len = nk_utf_decode(text, &unicode, text_len);
    while (glyph_len && (width < space) && (len < text_len)) {
        float s;
        len += glyph_len;
        s = font->width(font->userdata, font->height, text, len);

        last_width = width;
        width = s;
        glyph_len = nk_utf_decode(&text[len], &unicode, text_len - len);
        g++;
    }

    *glyphs = g;
    *text_width = last_width;
    return len;
}

enum {NK_DO_NOT_STOP_ON_NEW_LINE, NK_STOP_ON_NEW_LINE};
NK_INTERN struct nk_vec2
nk_text_calculate_text_bounds(const struct nk_user_font *font,
    const char *begin, int byte_len, float row_height, const char **remaining,
    struct nk_vec2 *out_offset, int *glyphs, int op)
{
    float line_height = row_height;
    struct nk_vec2 text_size = nk_vec2(0,0);
    float line_width = 0.0f;

    float glyph_width;
    int glyph_len = 0;
    nk_rune unicode = 0;
    int text_len = 0;
    if (!begin || byte_len <= 0 || !font)
        return nk_vec2(0,row_height);

    glyph_len = nk_utf_decode(begin, &unicode, byte_len);
    if (!glyph_len) return text_size;
    glyph_width = font->width(font->userdata, font->height, begin, glyph_len);

    *glyphs = 0;
    while ((text_len < byte_len) && glyph_len) {
        if (unicode == '\n') {
            text_size.x = NK_MAX(text_size.x, line_width);
            text_size.y += line_height;
            line_width = 0;
            *glyphs+=1;
            if (op == NK_STOP_ON_NEW_LINE)
                break;

            text_len++;
            glyph_len = nk_utf_decode(begin + text_len, &unicode, byte_len-text_len);
            continue;
        }

        if (unicode == '\r') {
            text_len++;
            *glyphs+=1;
            glyph_len = nk_utf_decode(begin + text_len, &unicode, byte_len-text_len);
            continue;
        }

        *glyphs = *glyphs + 1;
        text_len += glyph_len;
        line_width += (float)glyph_width;
        glyph_width = font->width(font->userdata, font->height, begin+text_len, glyph_len);
        glyph_len = nk_utf_decode(begin + text_len, &unicode, byte_len-text_len);
        continue;
    }

    if (text_size.x < line_width)
        text_size.x = line_width;
    if (out_offset)
        *out_offset = nk_vec2(line_width, text_size.y + line_height);
    if (line_width > 0 || text_size.y == 0.0f)
        text_size.y += line_height;
    if (remaining)
        *remaining = begin+text_len;
    return text_size;
}

/* ==============================================================
 *
 *                          UTF-8
 *
 * ===============================================================*/
NK_GLOBAL const nk_byte nk_utfbyte[NK_UTF_SIZE+1] = {0x80, 0, 0xC0, 0xE0, 0xF0};
NK_GLOBAL const nk_byte nk_utfmask[NK_UTF_SIZE+1] = {0xC0, 0x80, 0xE0, 0xF0, 0xF8};
NK_GLOBAL const nk_uint nk_utfmin[NK_UTF_SIZE+1] = {0, 0, 0x80, 0x800, 0x10000};
NK_GLOBAL const nk_uint nk_utfmax[NK_UTF_SIZE+1] = {0x10FFFF, 0x7F, 0x7FF, 0xFFFF, 0x10FFFF};

NK_INTERN int
nk_utf_validate(nk_rune *u, int i)
{
    NK_ASSERT(u);
    if (!u) return 0;
    if (!NK_BETWEEN(*u, nk_utfmin[i], nk_utfmax[i]) ||
         NK_BETWEEN(*u, 0xD800, 0xDFFF))
            *u = NK_UTF_INVALID;
    for (i = 1; *u > nk_utfmax[i]; ++i);
    return i;
}

NK_INTERN nk_rune
nk_utf_decode_byte(char c, int *i)
{
    NK_ASSERT(i);
    if (!i) return 0;
    for(*i = 0; *i < (int)NK_LEN(nk_utfmask); ++(*i)) {
        if (((nk_byte)c & nk_utfmask[*i]) == nk_utfbyte[*i])
            return (nk_byte)(c & ~nk_utfmask[*i]);
    }
    return 0;
}

NK_API int
nk_utf_decode(const char *c, nk_rune *u, int clen)
{
    int i, j, len, type=0;
    nk_rune udecoded;

    NK_ASSERT(c);
    NK_ASSERT(u);

    if (!c || !u) return 0;
    if (!clen) return 0;
    *u = NK_UTF_INVALID;

    udecoded = nk_utf_decode_byte(c[0], &len);
    if (!NK_BETWEEN(len, 1, NK_UTF_SIZE))
        return 1;

    for (i = 1, j = 1; i < clen && j < len; ++i, ++j) {
        udecoded = (udecoded << 6) | nk_utf_decode_byte(c[i], &type);
        if (type != 0)
            return j;
    }
    if (j < len)
        return 0;
    *u = udecoded;
    nk_utf_validate(u, len);
    return len;
}

NK_INTERN char
nk_utf_encode_byte(nk_rune u, int i)
{
    return (char)((nk_utfbyte[i]) | ((nk_byte)u & ~nk_utfmask[i]));
}

NK_API int
nk_utf_encode(nk_rune u, char *c, int clen)
{
    int len, i;
    len = nk_utf_validate(&u, 0);
    if (clen < len || !len || len > NK_UTF_SIZE)
        return 0;

    for (i = len - 1; i != 0; --i) {
        c[i] = nk_utf_encode_byte(u, 0);
        u >>= 6;
    }
    c[0] = nk_utf_encode_byte(u, len);
    return len;
}

NK_API int
nk_utf_len(const char *str, int len)
{
    const char *text;
    int glyphs = 0;
    int text_len;
    int glyph_len;
    int src_len = 0;
    nk_rune unicode;

    NK_ASSERT(str);
    if (!str || !len) return 0;

    text = str;
    text_len = len;
    glyph_len = nk_utf_decode(text, &unicode, text_len);
    while (glyph_len && src_len < len) {
        glyphs++;
        src_len = src_len + glyph_len;
        glyph_len = nk_utf_decode(text + src_len, &unicode, text_len - src_len);
    }
    return glyphs;
}

NK_API const char*
nk_utf_at(const char *buffer, int length, int index,
    nk_rune *unicode, int *len)
{
    int i = 0;
    int src_len = 0;
    int glyph_len = 0;
    const char *text;
    int text_len;

    NK_ASSERT(buffer);
    NK_ASSERT(unicode);
    NK_ASSERT(len);

    if (!buffer || !unicode || !len) return 0;
    if (index < 0) {
        *unicode = NK_UTF_INVALID;
        *len = 0;
        return 0;
    }

    text = buffer;
    text_len = length;
    glyph_len = nk_utf_decode(text, unicode, text_len);
    while (glyph_len) {
        if (i == index) {
            *len = glyph_len;
            break;
        }

        i++;
        src_len = src_len + glyph_len;
        glyph_len = nk_utf_decode(text + src_len, unicode, text_len - src_len);
    }
    if (i != index) return 0;
    return buffer + src_len;
}

/* ==============================================================
 *
 *                          BUFFER
 *
 * ===============================================================*/
#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_INTERN void* nk_malloc(nk_handle unused, void *old,nk_size size)
{NK_UNUSED(unused); NK_UNUSED(old); return malloc(size);}
NK_INTERN void nk_mfree(nk_handle unused, void *ptr)
{NK_UNUSED(unused); free(ptr);}

NK_API void
nk_buffer_init_default(struct nk_buffer *buffer)
{
    struct nk_allocator alloc;
    alloc.userdata.ptr = 0;
    alloc.alloc = nk_malloc;
    alloc.free = nk_mfree;
    nk_buffer_init(buffer, &alloc, NK_BUFFER_DEFAULT_INITIAL_SIZE);
}
#endif

NK_API void
nk_buffer_init(struct nk_buffer *b, const struct nk_allocator *a,
    nk_size initial_size)
{
    NK_ASSERT(b);
    NK_ASSERT(a);
    NK_ASSERT(initial_size);
    if (!b || !a || !initial_size) return;

    nk_zero(b, sizeof(*b));
    b->type = NK_BUFFER_DYNAMIC;
    b->memory.ptr = a->alloc(a->userdata,0, initial_size);
    b->memory.size = initial_size;
    b->size = initial_size;
    b->grow_factor = 2.0f;
    b->pool = *a;
}

NK_API void
nk_buffer_init_fixed(struct nk_buffer *b, void *m, nk_size size)
{
    NK_ASSERT(b);
    NK_ASSERT(m);
    NK_ASSERT(size);
    if (!b || !m || !size) return;

    nk_zero(b, sizeof(*b));
    b->type = NK_BUFFER_FIXED;
    b->memory.ptr = m;
    b->memory.size = size;
    b->size = size;
}

NK_INTERN void*
nk_buffer_align(void *unaligned, nk_size align, nk_size *alignment,
    enum nk_buffer_allocation_type type)
{
    void *memory = 0;
    switch (type) {
    default:
    case NK_BUFFER_MAX:
    case NK_BUFFER_FRONT:
        if (align) {
            memory = NK_ALIGN_PTR(unaligned, align);
            *alignment = (nk_size)((nk_byte*)memory - (nk_byte*)unaligned);
        } else {
            memory = unaligned;
            *alignment = 0;
        }
        break;
    case NK_BUFFER_BACK:
        if (align) {
            memory = NK_ALIGN_PTR_BACK(unaligned, align);
            *alignment = (nk_size)((nk_byte*)unaligned - (nk_byte*)memory);
        } else {
            memory = unaligned;
            *alignment = 0;
        }
        break;
    }
    return memory;
}

NK_INTERN void*
nk_buffer_realloc(struct nk_buffer *b, nk_size capacity, nk_size *size)
{
    void *temp;
    nk_size buffer_size;

    NK_ASSERT(b);
    NK_ASSERT(size);
    if (!b || !size || !b->pool.alloc || !b->pool.free)
        return 0;

    buffer_size = b->memory.size;
    temp = b->pool.alloc(b->pool.userdata, b->memory.ptr, capacity);
    NK_ASSERT(temp);
    if (!temp) return 0;

    *size = capacity;
    if (temp != b->memory.ptr) {
        NK_MEMCPY(temp, b->memory.ptr, buffer_size);
        b->pool.free(b->pool.userdata, b->memory.ptr);
    }

    if (b->size == buffer_size) {
        /* no back buffer so just set correct size */
        b->size = capacity;
        return temp;
    } else {
        /* copy back buffer to the end of the new buffer */
        void *dst, *src;
        nk_size back_size;
        back_size = buffer_size - b->size;
        dst = nk_ptr_add(void, temp, capacity - back_size);
        src = nk_ptr_add(void, temp, b->size);
        NK_MEMCPY(dst, src, back_size);
        b->size = capacity - back_size;
    }
    return temp;
}

NK_INTERN void*
nk_buffer_alloc(struct nk_buffer *b, enum nk_buffer_allocation_type type,
    nk_size size, nk_size align)
{
    int full;
    nk_size alignment;
    void *unaligned;
    void *memory;

    NK_ASSERT(b);
    NK_ASSERT(size);
    if (!b || !size) return 0;
    b->needed += size;

    /* calculate total size with needed alignment + size */
    if (type == NK_BUFFER_FRONT)
        unaligned = nk_ptr_add(void, b->memory.ptr, b->allocated);
    else unaligned = nk_ptr_add(void, b->memory.ptr, b->size - size);
    memory = nk_buffer_align(unaligned, align, &alignment, type);

    /* check if buffer has enough memory*/
    if (type == NK_BUFFER_FRONT)
        full = ((b->allocated + size + alignment) > b->size);
    else full = ((b->size - (size + alignment)) <= b->allocated);

    if (full) {
        nk_size capacity;
        NK_ASSERT(b->type == NK_BUFFER_DYNAMIC);
        NK_ASSERT(b->pool.alloc && b->pool.free);
        if (b->type != NK_BUFFER_DYNAMIC || !b->pool.alloc || !b->pool.free)
            return 0;

        /* buffer is full so allocate bigger buffer if dynamic */
        capacity = (nk_size)((float)b->memory.size * b->grow_factor);
        capacity = NK_MAX(capacity, nk_round_up_pow2((nk_uint)(b->allocated + size)));
        b->memory.ptr = nk_buffer_realloc(b, capacity, &b->memory.size);
        if (!b->memory.ptr) return 0;

        /* align newly allocated pointer */
        if (type == NK_BUFFER_FRONT)
            unaligned = nk_ptr_add(void, b->memory.ptr, b->allocated);
        else unaligned = nk_ptr_add(void, b->memory.ptr, b->size);
        memory = nk_buffer_align(unaligned, align, &alignment, type);
    }

    if (type == NK_BUFFER_FRONT)
        b->allocated += size + alignment;
    else b->size -= (size + alignment);
    b->needed += alignment;
    b->calls++;
    return memory;
}

NK_API void
nk_buffer_push(struct nk_buffer *b, enum nk_buffer_allocation_type type,
    void *memory, nk_size size, nk_size align)
{
    void *mem = nk_buffer_alloc(b, type, size, align);
    if (!mem) return;
    NK_MEMCPY(mem, memory, size);
}

NK_API void
nk_buffer_mark(struct nk_buffer *buffer, enum nk_buffer_allocation_type type)
{
    NK_ASSERT(buffer);
    if (!buffer) return;
    buffer->marker[type].active = nk_true;
    if (type == NK_BUFFER_BACK)
        buffer->marker[type].offset = buffer->size;
    else buffer->marker[type].offset = buffer->allocated;
}

NK_API void
nk_buffer_reset(struct nk_buffer *buffer, enum nk_buffer_allocation_type type)
{
    NK_ASSERT(buffer);
    if (!buffer) return;
    if (type == NK_BUFFER_BACK) {
        /* reset back buffer either back to marker or empty */
        buffer->needed -= (buffer->memory.size - buffer->marker[type].offset);
        if (buffer->marker[type].active)
            buffer->size = buffer->marker[type].offset;
        else buffer->size = buffer->memory.size;
        buffer->marker[type].active = nk_false;
    } else {
        /* reset front buffer either back to back marker or empty */
        buffer->needed -= (buffer->allocated - buffer->marker[type].offset);
        if (buffer->marker[type].active)
            buffer->allocated = buffer->marker[type].offset;
        else buffer->allocated = 0;
        buffer->marker[type].active = nk_false;
    }
}

NK_API void
nk_buffer_clear(struct nk_buffer *b)
{
    NK_ASSERT(b);
    if (!b) return;
    b->allocated = 0;
    b->size = b->memory.size;
    b->calls = 0;
    b->needed = 0;
}

NK_API void
nk_buffer_free(struct nk_buffer *b)
{
    NK_ASSERT(b);
    if (!b || !b->memory.ptr) return;
    if (b->type == NK_BUFFER_FIXED) return;
    if (!b->pool.free) return;
    NK_ASSERT(b->pool.free);
    b->pool.free(b->pool.userdata, b->memory.ptr);
}

NK_API void
nk_buffer_info(struct nk_memory_status *s, struct nk_buffer *b)
{
    NK_ASSERT(b);
    NK_ASSERT(s);
    if (!s || !b) return;
    s->allocated = b->allocated;
    s->size =  b->memory.size;
    s->needed = b->needed;
    s->memory = b->memory.ptr;
    s->calls = b->calls;
}

NK_API void*
nk_buffer_memory(struct nk_buffer *buffer)
{
    NK_ASSERT(buffer);
    if (!buffer) return 0;
    return buffer->memory.ptr;
}

NK_API const void*
nk_buffer_memory_const(const struct nk_buffer *buffer)
{
    NK_ASSERT(buffer);
    if (!buffer) return 0;
    return buffer->memory.ptr;
}

NK_API nk_size
nk_buffer_total(struct nk_buffer *buffer)
{
    NK_ASSERT(buffer);
    if (!buffer) return 0;
    return buffer->memory.size;
}

/*
 * ==============================================================
 *
 *                          STRING
 *
 * ===============================================================
 */
#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void
nk_str_init_default(struct nk_str *str)
{
    struct nk_allocator alloc;
    alloc.userdata.ptr = 0;
    alloc.alloc = nk_malloc;
    alloc.free = nk_mfree;
    nk_buffer_init(&str->buffer, &alloc, 32);
    str->len = 0;
}
#endif

NK_API void
nk_str_init(struct nk_str *str, const struct nk_allocator *alloc, nk_size size)
{
    nk_buffer_init(&str->buffer, alloc, size);
    str->len = 0;
}

NK_API void
nk_str_init_fixed(struct nk_str *str, void *memory, nk_size size)
{
    nk_buffer_init_fixed(&str->buffer, memory, size);
    str->len = 0;
}

NK_API int
nk_str_append_text_char(struct nk_str *s, const char *str, int len)
{
    char *mem;
    NK_ASSERT(s);
    NK_ASSERT(str);
    if (!s || !str || !len) return 0;
    mem = (char*)nk_buffer_alloc(&s->buffer, NK_BUFFER_FRONT, (nk_size)len * sizeof(char), 0);
    if (!mem) return 0;
    NK_MEMCPY(mem, str, (nk_size)len * sizeof(char));
    s->len += nk_utf_len(str, len);
    return len;
}

NK_API int
nk_str_append_str_char(struct nk_str *s, const char *str)
{
    return nk_str_append_text_char(s, str, nk_strlen(str));
}

NK_API int
nk_str_append_text_utf8(struct nk_str *str, const char *text, int len)
{
    int i = 0;
    int byte_len = 0;
    nk_rune unicode;
    if (!str || !text || !len) return 0;
    for (i = 0; i < len; ++i)
        byte_len += nk_utf_decode(text+byte_len, &unicode, 4);
    nk_str_append_text_char(str, text, byte_len);
    return len;
}

NK_API int
nk_str_append_str_utf8(struct nk_str *str, const char *text)
{
    int runes = 0;
    int byte_len = 0;
    int num_runes = 0;
    int glyph_len = 0;
    nk_rune unicode;
    if (!str || !text) return 0;

    glyph_len = byte_len = nk_utf_decode(text+byte_len, &unicode, 4);
    while (unicode != '\0' && glyph_len) {
        glyph_len = nk_utf_decode(text+byte_len, &unicode, 4);
        byte_len += glyph_len;
        num_runes++;
    }
    nk_str_append_text_char(str, text, byte_len);
    return runes;
}

NK_API int
nk_str_append_text_runes(struct nk_str *str, const nk_rune *text, int len)
{
    int i = 0;
    int byte_len = 0;
    nk_glyph glyph;

    NK_ASSERT(str);
    if (!str || !text || !len) return 0;
    for (i = 0; i < len; ++i) {
        byte_len = nk_utf_encode(text[i], glyph, NK_UTF_SIZE);
        if (!byte_len) break;
        nk_str_append_text_char(str, glyph, byte_len);
    }
    return len;
}

NK_API int
nk_str_append_str_runes(struct nk_str *str, const nk_rune *runes)
{
    int i = 0;
    nk_glyph glyph;
    int byte_len;
    NK_ASSERT(str);
    if (!str || !runes) return 0;
    while (runes[i] != '\0') {
        byte_len = nk_utf_encode(runes[i], glyph, NK_UTF_SIZE);
        nk_str_append_text_char(str, glyph, byte_len);
        i++;
    }
    return i;
}

NK_API int
nk_str_insert_at_char(struct nk_str *s, int pos, const char *str, int len)
{
    int i;
    void *mem;
    char *src;
    char *dst;

    int copylen;
    NK_ASSERT(s);
    NK_ASSERT(str);
    NK_ASSERT(len >= 0);
    if (!s || !str || !len || (nk_size)pos > s->buffer.allocated) return 0;
    if ((s->buffer.allocated + (nk_size)len >= s->buffer.memory.size) &&
        (s->buffer.type == NK_BUFFER_FIXED)) return 0;

    copylen = (int)s->buffer.allocated - pos;
    if (!copylen) {
        nk_str_append_text_char(s, str, len);
        return 1;
    }
    mem = nk_buffer_alloc(&s->buffer, NK_BUFFER_FRONT, (nk_size)len * sizeof(char), 0);
    if (!mem) return 0;

    /* memmove */
    NK_ASSERT(((int)pos + (int)len + ((int)copylen - 1)) >= 0);
    NK_ASSERT(((int)pos + ((int)copylen - 1)) >= 0);
    dst = nk_ptr_add(char, s->buffer.memory.ptr, pos + len + (copylen - 1));
    src = nk_ptr_add(char, s->buffer.memory.ptr, pos + (copylen-1));
    for (i = 0; i < copylen; ++i) *dst-- = *src--;
    mem = nk_ptr_add(void, s->buffer.memory.ptr, pos);
    NK_MEMCPY(mem, str, (nk_size)len * sizeof(char));
    s->len = nk_utf_len((char *)s->buffer.memory.ptr, (int)s->buffer.allocated);
    return 1;
}

NK_API int
nk_str_insert_at_rune(struct nk_str *str, int pos, const char *cstr, int len)
{
    int glyph_len;
    nk_rune unicode;
    const char *begin;
    const char *buffer;

    NK_ASSERT(str);
    NK_ASSERT(cstr);
    NK_ASSERT(len);
    if (!str || !cstr || !len) return 0;
    begin = nk_str_at_rune(str, pos, &unicode, &glyph_len);
    buffer = nk_str_get_const(str);
    if (!begin) return 0;
    return nk_str_insert_text_char(str, (int)(begin - buffer), cstr, len);
}

NK_API int nk_str_insert_text_char(struct nk_str *str, int pos, const char *text, int len)
{return nk_str_insert_at_char(str, pos, text, len);}

NK_API int nk_str_insert_str_char(struct nk_str *str, int pos, const char *text)
{return nk_str_insert_at_char(str, pos, text, nk_strlen(text));}

NK_API int
nk_str_insert_text_utf8(struct nk_str *str, int pos, const char *text, int len)
{
    int i = 0;
    int byte_len = 0;
    nk_rune unicode;

    NK_ASSERT(str);
    NK_ASSERT(text);
    if (!str || !text || !len) return 0;
    for (i = 0; i < len; ++i)
        byte_len += nk_utf_decode(text+byte_len, &unicode, 4);
    nk_str_insert_at_rune(str, pos, text, byte_len);
    return len;
}

NK_API int
nk_str_insert_str_utf8(struct nk_str *str, int pos, const char *text)
{
    int runes = 0;
    int byte_len = 0;
    int num_runes = 0;
    int glyph_len = 0;
    nk_rune unicode;
    if (!str || !text) return 0;

    glyph_len = byte_len = nk_utf_decode(text+byte_len, &unicode, 4);
    while (unicode != '\0' && glyph_len) {
        glyph_len = nk_utf_decode(text+byte_len, &unicode, 4);
        byte_len += glyph_len;
        num_runes++;
    }
    nk_str_insert_at_rune(str, pos, text, byte_len);
    return runes;
}

NK_API int
nk_str_insert_text_runes(struct nk_str *str, int pos, const nk_rune *runes, int len)
{
    int i = 0;
    int byte_len = 0;
    nk_glyph glyph;

    NK_ASSERT(str);
    if (!str || !runes || !len) return 0;
    for (i = 0; i < len; ++i) {
        byte_len = nk_utf_encode(runes[i], glyph, NK_UTF_SIZE);
        if (!byte_len) break;
        nk_str_insert_at_rune(str, pos+i, glyph, byte_len);
    }
    return len;
}

NK_API int
nk_str_insert_str_runes(struct nk_str *str, int pos, const nk_rune *runes)
{
    int i = 0;
    nk_glyph glyph;
    int byte_len;
    NK_ASSERT(str);
    if (!str || !runes) return 0;
    while (runes[i] != '\0') {
        byte_len = nk_utf_encode(runes[i], glyph, NK_UTF_SIZE);
        nk_str_insert_at_rune(str, pos+i, glyph, byte_len);
        i++;
    }
    return i;
}

NK_API void
nk_str_remove_chars(struct nk_str *s, int len)
{
    NK_ASSERT(s);
    NK_ASSERT(len >= 0);
    if (!s || len < 0 || (nk_size)len > s->buffer.allocated) return;
    NK_ASSERT(((int)s->buffer.allocated - (int)len) >= 0);
    s->buffer.allocated -= (nk_size)len;
    s->len = nk_utf_len((char *)s->buffer.memory.ptr, (int)s->buffer.allocated);
}

NK_API void
nk_str_remove_runes(struct nk_str *str, int len)
{
    int index;
    const char *begin;
    const char *end;
    nk_rune unicode;

    NK_ASSERT(str);
    NK_ASSERT(len >= 0);
    if (!str || len < 0) return;
    if (len >= str->len) {
        str->len = 0;
        return;
    }

    index = str->len - len;
    begin = nk_str_at_rune(str, index, &unicode, &len);
    end = (const char*)str->buffer.memory.ptr + str->buffer.allocated;
    nk_str_remove_chars(str, (int)(end-begin)+1);
}

NK_API void
nk_str_delete_chars(struct nk_str *s, int pos, int len)
{
    NK_ASSERT(s);
    if (!s || !len || (nk_size)pos > s->buffer.allocated ||
        (nk_size)(pos + len) > s->buffer.allocated) return;

    if ((nk_size)(pos + len) < s->buffer.allocated) {
        /* memmove */
        char *dst = nk_ptr_add(char, s->buffer.memory.ptr, pos);
        char *src = nk_ptr_add(char, s->buffer.memory.ptr, pos + len);
        NK_MEMCPY(dst, src, s->buffer.allocated - (nk_size)(pos + len));
        NK_ASSERT(((int)s->buffer.allocated - (int)len) >= 0);
        s->buffer.allocated -= (nk_size)len;
    } else nk_str_remove_chars(s, len);
    s->len = nk_utf_len((char *)s->buffer.memory.ptr, (int)s->buffer.allocated);
}

NK_API void
nk_str_delete_runes(struct nk_str *s, int pos, int len)
{
    char *temp;
    nk_rune unicode;
    char *begin;
    char *end;
    int unused;

    NK_ASSERT(s);
    NK_ASSERT(s->len >= pos + len);
    if (s->len < pos + len)
        len = NK_CLAMP(0, (s->len - pos), s->len);
    if (!len) return;

    temp = (char *)s->buffer.memory.ptr;
    begin = nk_str_at_rune(s, pos, &unicode, &unused);
    if (!begin) return;
    s->buffer.memory.ptr = begin;
    end = nk_str_at_rune(s, len, &unicode, &unused);
    s->buffer.memory.ptr = temp;
    if (!end) return;
    nk_str_delete_chars(s, (int)(begin - temp), (int)(end - begin));
}

NK_API char*
nk_str_at_char(struct nk_str *s, int pos)
{
    NK_ASSERT(s);
    if (!s || pos > (int)s->buffer.allocated) return 0;
    return nk_ptr_add(char, s->buffer.memory.ptr, pos);
}

NK_API char*
nk_str_at_rune(struct nk_str *str, int pos, nk_rune *unicode, int *len)
{
    int i = 0;
    int src_len = 0;
    int glyph_len = 0;
    char *text;
    int text_len;

    NK_ASSERT(str);
    NK_ASSERT(unicode);
    NK_ASSERT(len);

    if (!str || !unicode || !len) return 0;
    if (pos < 0) {
        *unicode = 0;
        *len = 0;
        return 0;
    }

    text = (char*)str->buffer.memory.ptr;
    text_len = (int)str->buffer.allocated;
    glyph_len = nk_utf_decode(text, unicode, text_len);
    while (glyph_len) {
        if (i == pos) {
            *len = glyph_len;
            break;
        }

        i+= glyph_len;
        src_len = src_len + glyph_len;
        glyph_len = nk_utf_decode(text + src_len, unicode, text_len - src_len);
    }
    if (i != pos) return 0;
    return text + src_len;
}

NK_API const char*
nk_str_at_char_const(const struct nk_str *s, int pos)
{
    NK_ASSERT(s);
    if (!s || pos > (int)s->buffer.allocated) return 0;
    return nk_ptr_add(char, s->buffer.memory.ptr, pos);
}

NK_API const char*
nk_str_at_const(const struct nk_str *str, int pos, nk_rune *unicode, int *len)
{
    int i = 0;
    int src_len = 0;
    int glyph_len = 0;
    char *text;
    int text_len;

    NK_ASSERT(str);
    NK_ASSERT(unicode);
    NK_ASSERT(len);

    if (!str || !unicode || !len) return 0;
    if (pos < 0) {
        *unicode = 0;
        *len = 0;
        return 0;
    }

    text = (char*)str->buffer.memory.ptr;
    text_len = (int)str->buffer.allocated;
    glyph_len = nk_utf_decode(text, unicode, text_len);
    while (glyph_len) {
        if (i == pos) {
            *len = glyph_len;
            break;
        }

        i++;
        src_len = src_len + glyph_len;
        glyph_len = nk_utf_decode(text + src_len, unicode, text_len - src_len);
    }
    if (i != pos) return 0;
    return text + src_len;
}

NK_API nk_rune
nk_str_rune_at(const struct nk_str *str, int pos)
{
    int len;
    nk_rune unicode = 0;
    nk_str_at_const(str, pos, &unicode, &len);
    return unicode;
}

NK_API char*
nk_str_get(struct nk_str *s)
{
    NK_ASSERT(s);
    if (!s || !s->len || !s->buffer.allocated) return 0;
    return (char*)s->buffer.memory.ptr;
}

NK_API const char*
nk_str_get_const(const struct nk_str *s)
{
    NK_ASSERT(s);
    if (!s || !s->len || !s->buffer.allocated) return 0;
    return (const char*)s->buffer.memory.ptr;
}

NK_API int
nk_str_len(struct nk_str *s)
{
    NK_ASSERT(s);
    if (!s || !s->len || !s->buffer.allocated) return 0;
    return s->len;
}

NK_API int
nk_str_len_char(struct nk_str *s)
{
    NK_ASSERT(s);
    if (!s || !s->len || !s->buffer.allocated) return 0;
    return (int)s->buffer.allocated;
}

NK_API void
nk_str_clear(struct nk_str *str)
{
    NK_ASSERT(str);
    nk_buffer_clear(&str->buffer);
    str->len = 0;
}

NK_API void
nk_str_free(struct nk_str *str)
{
    NK_ASSERT(str);
    nk_buffer_free(&str->buffer);
    str->len = 0;
}

/*
 * ==============================================================
 *
 *                      Command buffer
 *
 * ===============================================================
*/
NK_INTERN void
nk_command_buffer_init(struct nk_command_buffer *cmdbuf,
    struct nk_buffer *buffer, enum nk_command_clipping clip)
{
    NK_ASSERT(cmdbuf);
    NK_ASSERT(buffer);
    if (!cmdbuf || !buffer) return;
    cmdbuf->base = buffer;
    cmdbuf->use_clipping = clip;
    cmdbuf->begin = buffer->allocated;
    cmdbuf->end = buffer->allocated;
    cmdbuf->last = buffer->allocated;
}

NK_INTERN void
nk_command_buffer_reset(struct nk_command_buffer *buffer)
{
    NK_ASSERT(buffer);
    if (!buffer) return;
    buffer->begin = 0;
    buffer->end = 0;
    buffer->last = 0;
    buffer->clip = nk_null_rect;
#ifdef NK_INCLUDE_COMMAND_USERDATA
    buffer->userdata.ptr = 0;
#endif
}

NK_INTERN void*
nk_command_buffer_push(struct nk_command_buffer* b,
    enum nk_command_type t, nk_size size)
{
    NK_STORAGE const nk_size align = NK_ALIGNOF(struct nk_command);
    struct nk_command *cmd;
    nk_size alignment;
    void *unaligned;
    void *memory;

    NK_ASSERT(b);
    NK_ASSERT(b->base);
    if (!b) return 0;

    cmd = (struct nk_command*)nk_buffer_alloc(b->base,NK_BUFFER_FRONT,size,align);
    if (!cmd) return 0;

    /* make sure the offset to the next command is aligned */
    b->last = (nk_size)((nk_byte*)cmd - (nk_byte*)b->base->memory.ptr);
    unaligned = (nk_byte*)cmd + size;
    memory = NK_ALIGN_PTR(unaligned, align);
    alignment = (nk_size)((nk_byte*)memory - (nk_byte*)unaligned);

    cmd->type = t;
    cmd->next = b->base->allocated + alignment;
#ifdef NK_INCLUDE_COMMAND_USERDATA
    cmd->userdata = b->userdata;
#endif
    b->end = cmd->next;
    return cmd;
}

NK_API void
nk_push_scissor(struct nk_command_buffer *b, struct nk_rect r)
{
    struct nk_command_scissor *cmd;
    NK_ASSERT(b);
    if (!b) return;

    b->clip.x = r.x;
    b->clip.y = r.y;
    b->clip.w = r.w;
    b->clip.h = r.h;
    cmd = (struct nk_command_scissor*)
        nk_command_buffer_push(b, NK_COMMAND_SCISSOR, sizeof(*cmd));

    if (!cmd) return;
    cmd->x = (short)r.x;
    cmd->y = (short)r.y;
    cmd->w = (unsigned short)NK_MAX(0, r.w);
    cmd->h = (unsigned short)NK_MAX(0, r.h);
}

NK_API void
nk_stroke_line(struct nk_command_buffer *b, float x0, float y0,
    float x1, float y1, float line_thickness, struct nk_color c)
{
    struct nk_command_line *cmd;
    NK_ASSERT(b);
    if (!b) return;
    cmd = (struct nk_command_line*)
        nk_command_buffer_push(b, NK_COMMAND_LINE, sizeof(*cmd));
    if (!cmd) return;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->begin.x = (short)x0;
    cmd->begin.y = (short)y0;
    cmd->end.x = (short)x1;
    cmd->end.y = (short)y1;
    cmd->color = c;
}

NK_API void
nk_stroke_curve(struct nk_command_buffer *b, float ax, float ay,
    float ctrl0x, float ctrl0y, float ctrl1x, float ctrl1y,
    float bx, float by, float line_thickness, struct nk_color col)
{
    struct nk_command_curve *cmd;
    NK_ASSERT(b);
    if (!b || col.a == 0) return;

    cmd = (struct nk_command_curve*)
        nk_command_buffer_push(b, NK_COMMAND_CURVE, sizeof(*cmd));
    if (!cmd) return;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->begin.x = (short)ax;
    cmd->begin.y = (short)ay;
    cmd->ctrl[0].x = (short)ctrl0x;
    cmd->ctrl[0].y = (short)ctrl0y;
    cmd->ctrl[1].x = (short)ctrl1x;
    cmd->ctrl[1].y = (short)ctrl1y;
    cmd->end.x = (short)bx;
    cmd->end.y = (short)by;
    cmd->color = col;
}

NK_API void
nk_stroke_rect(struct nk_command_buffer *b, struct nk_rect rect,
    float rounding, float line_thickness, struct nk_color c)
{
    struct nk_command_rect *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INTERSECT(rect.x, rect.y, rect.w, rect.h,
            clip->x, clip->y, clip->w, clip->h)) return;
    }

    cmd = (struct nk_command_rect*)
        nk_command_buffer_push(b, NK_COMMAND_RECT, sizeof(*cmd));
    if (!cmd) return;
    cmd->rounding = (unsigned short)rounding;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->x = (short)rect.x;
    cmd->y = (short)rect.y;
    cmd->w = (unsigned short)NK_MAX(0, rect.w);
    cmd->h = (unsigned short)NK_MAX(0, rect.h);
    cmd->color = c;
}

NK_API void
nk_fill_rect(struct nk_command_buffer *b, struct nk_rect rect,
    float rounding, struct nk_color c)
{
    struct nk_command_rect_filled *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INTERSECT(rect.x, rect.y, rect.w, rect.h,
            clip->x, clip->y, clip->w, clip->h)) return;
    }

    cmd = (struct nk_command_rect_filled*)
        nk_command_buffer_push(b, NK_COMMAND_RECT_FILLED, sizeof(*cmd));
    if (!cmd) return;
    cmd->rounding = (unsigned short)rounding;
    cmd->x = (short)rect.x;
    cmd->y = (short)rect.y;
    cmd->w = (unsigned short)NK_MAX(0, rect.w);
    cmd->h = (unsigned short)NK_MAX(0, rect.h);
    cmd->color = c;
}

NK_API void
nk_fill_rect_multi_color(struct nk_command_buffer *b, struct nk_rect rect,
    struct nk_color left, struct nk_color top, struct nk_color right,
    struct nk_color bottom)
{
    struct nk_command_rect_multi_color *cmd;
    NK_ASSERT(b);
    if (!b) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INTERSECT(rect.x, rect.y, rect.w, rect.h,
            clip->x, clip->y, clip->w, clip->h)) return;
    }

    cmd = (struct nk_command_rect_multi_color*)
        nk_command_buffer_push(b, NK_COMMAND_RECT_MULTI_COLOR, sizeof(*cmd));
    if (!cmd) return;
    cmd->x = (short)rect.x;
    cmd->y = (short)rect.y;
    cmd->w = (unsigned short)NK_MAX(0, rect.w);
    cmd->h = (unsigned short)NK_MAX(0, rect.h);
    cmd->left = left;
    cmd->top = top;
    cmd->right = right;
    cmd->bottom = bottom;
}

NK_API void
nk_stroke_circle(struct nk_command_buffer *b, struct nk_rect r,
    float line_thickness, struct nk_color c)
{
    struct nk_command_circle *cmd;
    if (!b || c.a == 0) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INTERSECT(r.x, r.y, r.w, r.h, clip->x, clip->y, clip->w, clip->h))
            return;
    }

    cmd = (struct nk_command_circle*)
        nk_command_buffer_push(b, NK_COMMAND_CIRCLE, sizeof(*cmd));
    if (!cmd) return;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->x = (short)r.x;
    cmd->y = (short)r.y;
    cmd->w = (unsigned short)NK_MAX(r.w, 0);
    cmd->h = (unsigned short)NK_MAX(r.h, 0);
    cmd->color = c;
}

NK_API void
nk_fill_circle(struct nk_command_buffer *b, struct nk_rect r, struct nk_color c)
{
    struct nk_command_circle_filled *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INTERSECT(r.x, r.y, r.w, r.h, clip->x, clip->y, clip->w, clip->h))
            return;
    }

    cmd = (struct nk_command_circle_filled*)
        nk_command_buffer_push(b, NK_COMMAND_CIRCLE_FILLED, sizeof(*cmd));
    if (!cmd) return;
    cmd->x = (short)r.x;
    cmd->y = (short)r.y;
    cmd->w = (unsigned short)NK_MAX(r.w, 0);
    cmd->h = (unsigned short)NK_MAX(r.h, 0);
    cmd->color = c;
}

NK_API void
nk_stroke_arc(struct nk_command_buffer *b, float cx, float cy, float radius,
    float a_min, float a_max, float line_thickness, struct nk_color c)
{
    struct nk_command_arc *cmd;
    if (!b || c.a == 0) return;
    cmd = (struct nk_command_arc*)
        nk_command_buffer_push(b, NK_COMMAND_ARC, sizeof(*cmd));
    if (!cmd) return;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->cx = (short)cx;
    cmd->cy = (short)cy;
    cmd->r = (unsigned short)radius;
    cmd->a[0] = a_min;
    cmd->a[1] = a_max;
    cmd->color = c;
}

NK_API void
nk_fill_arc(struct nk_command_buffer *b, float cx, float cy, float radius,
    float a_min, float a_max, struct nk_color c)
{
    struct nk_command_arc_filled *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0) return;
    cmd = (struct nk_command_arc_filled*)
        nk_command_buffer_push(b, NK_COMMAND_ARC_FILLED, sizeof(*cmd));
    if (!cmd) return;
    cmd->cx = (short)cx;
    cmd->cy = (short)cy;
    cmd->r = (unsigned short)radius;
    cmd->a[0] = a_min;
    cmd->a[1] = a_max;
    cmd->color = c;
}

NK_API void
nk_stroke_triangle(struct nk_command_buffer *b, float x0, float y0, float x1,
    float y1, float x2, float y2, float line_thickness, struct nk_color c)
{
    struct nk_command_triangle *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INBOX(x0, y0, clip->x, clip->y, clip->w, clip->h) &&
            !NK_INBOX(x1, y1, clip->x, clip->y, clip->w, clip->h) &&
            !NK_INBOX(x2, y2, clip->x, clip->y, clip->w, clip->h))
            return;
    }

    cmd = (struct nk_command_triangle*)
        nk_command_buffer_push(b, NK_COMMAND_TRIANGLE, sizeof(*cmd));
    if (!cmd) return;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->a.x = (short)x0;
    cmd->a.y = (short)y0;
    cmd->b.x = (short)x1;
    cmd->b.y = (short)y1;
    cmd->c.x = (short)x2;
    cmd->c.y = (short)y2;
    cmd->color = c;
}

NK_API void
nk_fill_triangle(struct nk_command_buffer *b, float x0, float y0, float x1,
    float y1, float x2, float y2, struct nk_color c)
{
    struct nk_command_triangle_filled *cmd;
    NK_ASSERT(b);
    if (!b || c.a == 0) return;
    if (!b) return;
    if (b->use_clipping) {
        const struct nk_rect *clip = &b->clip;
        if (!NK_INBOX(x0, y0, clip->x, clip->y, clip->w, clip->h) &&
            !NK_INBOX(x1, y1, clip->x, clip->y, clip->w, clip->h) &&
            !NK_INBOX(x2, y2, clip->x, clip->y, clip->w, clip->h))
            return;
    }

    cmd = (struct nk_command_triangle_filled*)
        nk_command_buffer_push(b, NK_COMMAND_TRIANGLE_FILLED, sizeof(*cmd));
    if (!cmd) return;
    cmd->a.x = (short)x0;
    cmd->a.y = (short)y0;
    cmd->b.x = (short)x1;
    cmd->b.y = (short)y1;
    cmd->c.x = (short)x2;
    cmd->c.y = (short)y2;
    cmd->color = c;
}

NK_API void
nk_stroke_polygon(struct nk_command_buffer *b,  float *points, int point_count,
    float line_thickness, struct nk_color col)
{
    int i;
    nk_size size = 0;
    struct nk_command_polygon *cmd;

    NK_ASSERT(b);
    if (!b || col.a == 0) return;
    size = sizeof(*cmd) + sizeof(short) * 2 * (nk_size)point_count;
    cmd = (struct nk_command_polygon*) nk_command_buffer_push(b, NK_COMMAND_POLYGON, size);
    if (!cmd) return;
    cmd->line_thickness = (unsigned short)line_thickness;
    cmd->color = col;
    cmd->point_count = (unsigned short)point_count;
    for (i = 0; i < point_count; ++i) {
        cmd->points[i].x = (short)points[i*2];
        cmd->points[i].y = (short)points[i*2+1];
    }
}

NK_API void
nk_fill_polygon(struct nk_command_buffer *b, float *points, int point_count,
    struct nk_color col)
{
    int i;
    nk_size size = 0;
    struct nk_command_polygon_filled *cmd;

    NK_ASSERT(b);
    if (!b || col.a == 0) return;
    size = sizeof(*cmd) + sizeof(short) * 2 * (nk_size)point_count;
    cmd = (struct nk_command_polygon_filled*)
        nk_command_buffer_push(b, NK_COMMAND_POLYGON_FILLED, size);
    if (!cmd) return;
    cmd->color = col;
    cmd->point_count = (unsigned short)point_count;
    for (i = 0; i < point_count; ++i) {
        cmd->points[i].x = (short)points[i*2];
        cmd->points[i].y = (short)points[i*2+1];
    }
}

NK_API void
nk_stroke_polyline(struct nk_command_buffer *b, float *points, int point_count,
    float line_thickness, struct nk_color col)
{
    int i;
    nk_size size = 0;
    struct nk_command_polyline *cmd;

    NK_ASSERT(b);
    if (!b || col.a == 0) return;
    size = sizeof(*cmd) + sizeof(short) * 2 * (nk_size)point_count;
    cmd = (struct nk_command_polyline*) nk_command_buffer_push(b, NK_COMMAND_POLYLINE, size);
    if (!cmd) return;
    cmd->color = col;
    cmd->point_count = (unsigned short)point_count;
    cmd->line_thickness = (unsigned short)line_thickness;
    for (i = 0; i < point_count; ++i) {
        cmd->points[i].x = (short)points[i*2];
        cmd->points[i].y = (short)points[i*2+1];
    }
}

NK_API void
nk_draw_image(struct nk_command_buffer *b, struct nk_rect r,
    const struct nk_image *img)
{
    struct nk_command_image *cmd;
    NK_ASSERT(b);
    if (!b) return;
    if (b->use_clipping) {
        const struct nk_rect *c = &b->clip;
        if (!NK_INTERSECT(r.x, r.y, r.w, r.h, c->x, c->y, c->w, c->h))
            return;
    }

    cmd = (struct nk_command_image*)
        nk_command_buffer_push(b, NK_COMMAND_IMAGE, sizeof(*cmd));
    if (!cmd) return;
    cmd->x = (short)r.x;
    cmd->y = (short)r.y;
    cmd->w = (unsigned short)NK_MAX(0, r.w);
    cmd->h = (unsigned short)NK_MAX(0, r.h);
    cmd->img = *img;
}

NK_API void
nk_draw_text(struct nk_command_buffer *b, struct nk_rect r,
    const char *string, int length, const struct nk_user_font *font,
    struct nk_color bg, struct nk_color fg)
{
    float text_width = 0;
    struct nk_command_text *cmd;

    NK_ASSERT(b);
    NK_ASSERT(font);
    if (!b || !string || !length || (bg.a == 0 && fg.a == 0)) return;
    if (b->use_clipping) {
        const struct nk_rect *c = &b->clip;
        if (!NK_INTERSECT(r.x, r.y, r.w, r.h, c->x, c->y, c->w, c->h))
            return;
    }

    /* make sure text fits inside bounds */
    text_width = font->width(font->userdata, font->height, string, length);
    if (text_width > r.w){
        float txt_width = (float)text_width;
        int glyphs = 0;
        length = nk_text_clamp(font, string, length,
                    r.w, &glyphs, &txt_width);
    }

    if (!length) return;
    cmd = (struct nk_command_text*)
        nk_command_buffer_push(b, NK_COMMAND_TEXT, sizeof(*cmd) + (nk_size)(length + 1));
    if (!cmd) return;
    cmd->x = (short)r.x;
    cmd->y = (short)r.y;
    cmd->w = (unsigned short)r.w;
    cmd->h = (unsigned short)r.h;
    cmd->background = bg;
    cmd->foreground = fg;
    cmd->font = font;
    cmd->length = length;
    cmd->height = font->height;
    NK_MEMCPY(cmd->string, string, (nk_size)length);
    cmd->string[length] = '\0';
}

/* ==============================================================
 *
 *                          DRAW LIST
 *
 * ===============================================================*/
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
NK_API void
nk_draw_list_init(struct nk_draw_list *list)
{
    nk_size i = 0;
    nk_zero(list, sizeof(*list));
    for (i = 0; i < NK_LEN(list->circle_vtx); ++i) {
        const float a = ((float)i / (float)NK_LEN(list->circle_vtx)) * 2 * NK_PI;
        list->circle_vtx[i].x = (float)NK_COS(a);
        list->circle_vtx[i].y = (float)NK_SIN(a);
    }
}

NK_API void
nk_draw_list_setup(struct nk_draw_list *canvas, float global_alpha,
    enum nk_anti_aliasing line_AA, enum nk_anti_aliasing shape_AA,
    struct nk_draw_null_texture null, struct nk_buffer *cmds,
    struct nk_buffer *vertices, struct nk_buffer *elements)
{
    canvas->null = null;
    canvas->clip_rect = nk_null_rect;
    canvas->vertices = vertices;
    canvas->elements = elements;
    canvas->buffer = cmds;
    canvas->line_AA = line_AA;
    canvas->shape_AA = shape_AA;
    canvas->global_alpha = global_alpha;
}

NK_API const struct nk_draw_command*
nk__draw_list_begin(const struct nk_draw_list *canvas, const struct nk_buffer *buffer)
{
    nk_byte *memory;
    nk_size offset;
    const struct nk_draw_command *cmd;

    NK_ASSERT(buffer);
    if (!buffer || !buffer->size || !canvas->cmd_count)
        return 0;

    memory = (nk_byte*)buffer->memory.ptr;
    offset = buffer->memory.size - canvas->cmd_offset;
    cmd = nk_ptr_add(const struct nk_draw_command, memory, offset);
    return cmd;
}

NK_API const struct nk_draw_command*
nk__draw_list_next(const struct nk_draw_command *cmd,
    const struct nk_buffer *buffer, const struct nk_draw_list *canvas)
{
    nk_byte *memory;
    nk_size size;
    nk_size offset;
    const struct nk_draw_command *end;

    NK_ASSERT(buffer);
    NK_ASSERT(canvas);
    if (!cmd || !buffer || !canvas)
        return 0;

    memory = (nk_byte*)buffer->memory.ptr;
    size = buffer->memory.size;
    offset = size - canvas->cmd_offset;
    end = nk_ptr_add(const struct nk_draw_command, memory, offset);
    end -= (canvas->cmd_count-1);

    if (cmd <= end) return 0;
    return (cmd-1);
}

NK_API void
nk_draw_list_clear(struct nk_draw_list *list)
{
    NK_ASSERT(list);
    if (!list) return;
    if (list->buffer)
        nk_buffer_clear(list->buffer);
    if (list->elements)
        nk_buffer_clear(list->vertices);
    if (list->vertices)
        nk_buffer_clear(list->elements);

    list->element_count = 0;
    list->vertex_count = 0;
    list->cmd_offset = 0;
    list->cmd_count = 0;
    list->path_count = 0;
    list->vertices = 0;
    list->elements = 0;
    list->clip_rect = nk_null_rect;
}

NK_INTERN struct nk_vec2*
nk_draw_list_alloc_path(struct nk_draw_list *list, int count)
{
    struct nk_vec2 *points;
    NK_STORAGE const nk_size point_align = NK_ALIGNOF(struct nk_vec2);
    NK_STORAGE const nk_size point_size = sizeof(struct nk_vec2);
    points = (struct nk_vec2*)
        nk_buffer_alloc(list->buffer, NK_BUFFER_FRONT,
                        point_size * (nk_size)count, point_align);

    if (!points) return 0;
    if (!list->path_offset) {
        void *memory = nk_buffer_memory(list->buffer);
        list->path_offset = (unsigned int)((nk_byte*)points - (nk_byte*)memory);
    }
    list->path_count += (unsigned int)count;
    return points;
}

NK_INTERN struct nk_vec2
nk_draw_list_path_last(struct nk_draw_list *list)
{
    void *memory;
    struct nk_vec2 *point;
    NK_ASSERT(list->path_count);
    memory = nk_buffer_memory(list->buffer);
    point = nk_ptr_add(struct nk_vec2, memory, list->path_offset);
    point += (list->path_count-1);
    return *point;
}

NK_INTERN struct nk_draw_command*
nk_draw_list_push_command(struct nk_draw_list *list, struct nk_rect clip,
    nk_handle texture)
{
    NK_STORAGE const nk_size cmd_align = NK_ALIGNOF(struct nk_draw_command);
    NK_STORAGE const nk_size cmd_size = sizeof(struct nk_draw_command);
    struct nk_draw_command *cmd;

    NK_ASSERT(list);
    cmd = (struct nk_draw_command*)
        nk_buffer_alloc(list->buffer, NK_BUFFER_BACK, cmd_size, cmd_align);

    if (!cmd) return 0;
    if (!list->cmd_count) {
        nk_byte *memory = (nk_byte*)nk_buffer_memory(list->buffer);
        nk_size total = nk_buffer_total(list->buffer);
        memory = nk_ptr_add(nk_byte, memory, total);
        list->cmd_offset = (nk_size)(memory - (nk_byte*)cmd);
    }

    cmd->elem_count = 0;
    cmd->clip_rect = clip;
    cmd->texture = texture;

    list->cmd_count++;
    list->clip_rect = clip;
    return cmd;
}

NK_INTERN struct nk_draw_command*
nk_draw_list_command_last(struct nk_draw_list *list)
{
    void *memory;
    nk_size size;
    struct nk_draw_command *cmd;
    NK_ASSERT(list->cmd_count);

    memory = nk_buffer_memory(list->buffer);
    size = nk_buffer_total(list->buffer);
    cmd = nk_ptr_add(struct nk_draw_command, memory, size - list->cmd_offset);
    return (cmd - (list->cmd_count-1));
}

NK_INTERN void
nk_draw_list_add_clip(struct nk_draw_list *list, struct nk_rect rect)
{
    NK_ASSERT(list);
    if (!list) return;
    if (!list->cmd_count) {
        nk_draw_list_push_command(list, rect, list->null.texture);
    } else {
        struct nk_draw_command *prev = nk_draw_list_command_last(list);
        if (prev->elem_count == 0)
            prev->clip_rect = rect;
        nk_draw_list_push_command(list, rect, prev->texture);
    }
}

NK_INTERN void
nk_draw_list_push_image(struct nk_draw_list *list, nk_handle texture)
{
    NK_ASSERT(list);
    if (!list) return;
    if (!list->cmd_count) {
        nk_draw_list_push_command(list, nk_null_rect, texture);
    } else {
        struct nk_draw_command *prev = nk_draw_list_command_last(list);
        if (prev->elem_count == 0)
            prev->texture = texture;
        else if (prev->texture.id != texture.id)
            nk_draw_list_push_command(list, prev->clip_rect, texture);
    }
}

#ifdef NK_INCLUDE_COMMAND_USERDATA
NK_API void
nk_draw_list_push_userdata(struct nk_draw_list *list, nk_handle userdata)
{
    NK_ASSERT(list);
    if (!list) return;
    if (!list->cmd_count) {
        struct nk_draw_command *prev;
        nk_draw_list_push_command(list, nk_null_rect, list->null.texture);
        prev = nk_draw_list_command_last(list);
        prev->userdata = userdata;
    } else {
        struct nk_draw_command *prev = nk_draw_list_command_last(list);
        if (prev->elem_count == 0) {
            prev->userdata = userdata;
        } else if (prev->userdata.ptr != userdata.ptr) {
            nk_draw_list_push_command(list, prev->clip_rect, prev->texture);
            prev = nk_draw_list_command_last(list);
            prev->userdata = userdata;
        }
    }
}
#endif

NK_INTERN struct nk_draw_vertex*
nk_draw_list_alloc_vertices(struct nk_draw_list *list, nk_size count)
{
    struct nk_draw_vertex *vtx;
    NK_STORAGE const nk_size vtx_align = NK_ALIGNOF(struct nk_draw_vertex);
    NK_STORAGE const nk_size vtx_size = sizeof(struct nk_draw_vertex);
    NK_ASSERT(list);
    if (!list) return 0;

    vtx = (struct nk_draw_vertex*)
        nk_buffer_alloc(list->vertices, NK_BUFFER_FRONT, vtx_size*count, vtx_align);
    if (!vtx) return 0;
    list->vertex_count += (unsigned int)count;
    return vtx;
}

NK_INTERN nk_draw_index*
nk_draw_list_alloc_elements(struct nk_draw_list *list, nk_size count)
{
    nk_draw_index *ids;
    struct nk_draw_command *cmd;
    NK_STORAGE const nk_size elem_align = NK_ALIGNOF(nk_draw_index);
    NK_STORAGE const nk_size elem_size = sizeof(nk_draw_index);
    NK_ASSERT(list);
    if (!list) return 0;

    ids = (nk_draw_index*)
        nk_buffer_alloc(list->elements, NK_BUFFER_FRONT, elem_size*count, elem_align);
    if (!ids) return 0;
    cmd = nk_draw_list_command_last(list);
    list->element_count += (unsigned int)count;
    cmd->elem_count += (unsigned int)count;
    return ids;
}

NK_INTERN struct nk_draw_vertex
nk_draw_vertex(struct nk_vec2 pos, struct nk_vec2 uv, nk_draw_vertex_color col)
{
    struct nk_draw_vertex out;
    out.position = pos;
    out.uv = uv;
    out.col = col;
    return out;
}

NK_API void
nk_draw_list_stroke_poly_line(struct nk_draw_list *list, const struct nk_vec2 *points,
    const unsigned int points_count, struct nk_color color, enum nk_draw_list_stroke closed,
    float thickness, enum nk_anti_aliasing aliasing)
{
    nk_size count;
    int thick_line;
    nk_draw_vertex_color col;
    NK_ASSERT(list);
    if (!list || points_count < 2) return;

    color.a = (nk_byte)((float)color.a * list->global_alpha);
    col = nk_color_u32(color);
    count = points_count;
    if (!closed) count = points_count-1;
    thick_line = thickness > 1.0f;

#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_draw_list_push_userdata(list, list->userdata);
#endif

    if (aliasing == NK_ANTI_ALIASING_ON) {
        /* ANTI-ALIASED STROKE */
        const float AA_SIZE = 1.0f;
        NK_STORAGE const nk_size pnt_align = NK_ALIGNOF(struct nk_vec2);
        NK_STORAGE const nk_size pnt_size = sizeof(struct nk_vec2);
        const nk_draw_vertex_color col_trans = col & 0x00ffffff;

        /* allocate vertices and elements  */
        nk_size i1 = 0;
        nk_size vertex_offset;
        nk_size index = list->vertex_count;
        const nk_size idx_count = (thick_line) ?  (count * 18) : (count * 12);
        const nk_size vtx_count = (thick_line) ? (points_count * 4): (points_count *3);
        struct nk_draw_vertex *vtx = nk_draw_list_alloc_vertices(list, vtx_count);
        nk_draw_index *ids = nk_draw_list_alloc_elements(list, idx_count);

        nk_size size;
        struct nk_vec2 *normals, *temp;
        NK_ASSERT(vtx && ids);
        if (!vtx || !ids) return;

        /* temporary allocate normals + points */
        vertex_offset = (nk_size)((nk_byte*)vtx - (nk_byte*)list->vertices->memory.ptr);
        nk_buffer_mark(list->vertices, NK_BUFFER_FRONT);
        size = pnt_size * ((thick_line) ? 5 : 3) * points_count;
        normals = (struct nk_vec2*)
            nk_buffer_alloc(list->vertices, NK_BUFFER_FRONT, size, pnt_align);
        NK_ASSERT(normals);
        if (!normals) return;
        vtx = (struct nk_draw_vertex*)(void*)((nk_byte*)list->vertices->memory.ptr + vertex_offset);
        temp = normals + points_count;

        /* calculate normals */
        for (i1 = 0; i1 < count; ++i1) {
            const nk_size i2 = ((i1 + 1) == points_count) ? 0 : (i1 + 1);
            struct nk_vec2 diff = nk_vec2_sub(points[i2], points[i1]);
            float len;

            /* vec2 inverted length  */
            len = nk_vec2_len_sqr(diff);
            if (len != 0.0f)
                len = nk_inv_sqrt(len);
            else len = 1.0f;

            diff = nk_vec2_muls(diff, len);
            normals[i1].x = diff.y;
            normals[i1].y = -diff.x;
        }

        if (!closed)
            normals[points_count-1] = normals[points_count-2];

        if (!thick_line) {
            nk_size idx1, i;
            if (!closed) {
                struct nk_vec2 d;
                temp[0] = nk_vec2_add(points[0], nk_vec2_muls(normals[0], AA_SIZE));
                temp[1] = nk_vec2_sub(points[0], nk_vec2_muls(normals[0], AA_SIZE));
                d = nk_vec2_muls(normals[points_count-1], AA_SIZE);
                temp[(points_count-1) * 2 + 0] = nk_vec2_add(points[points_count-1], d);
                temp[(points_count-1) * 2 + 1] = nk_vec2_sub(points[points_count-1], d);
            }

            /* fill elements */
            idx1 = index;
            for (i1 = 0; i1 < count; i1++) {
                struct nk_vec2 dm;
                float dmr2;
                nk_size i2 = ((i1 + 1) == points_count) ? 0 : (i1 + 1);
                nk_size idx2 = ((i1+1) == points_count) ? index: (idx1 + 3);

                /* average normals */
                dm = nk_vec2_muls(nk_vec2_add(normals[i1], normals[i2]), 0.5f);
                dmr2 = dm.x * dm.x + dm.y* dm.y;
                if (dmr2 > 0.000001f) {
                    float scale = 1.0f/dmr2;
                    scale = NK_MIN(100.0f, scale);
                    dm = nk_vec2_muls(dm, scale);
                }

                dm = nk_vec2_muls(dm, AA_SIZE);
                temp[i2*2+0] = nk_vec2_add(points[i2], dm);
                temp[i2*2+1] = nk_vec2_sub(points[i2], dm);

                ids[0] = (nk_draw_index)(idx2 + 0); ids[1] = (nk_draw_index)(idx1+0);
                ids[2] = (nk_draw_index)(idx1 + 2); ids[3] = (nk_draw_index)(idx1+2);
                ids[4] = (nk_draw_index)(idx2 + 2); ids[5] = (nk_draw_index)(idx2+0);
                ids[6] = (nk_draw_index)(idx2 + 1); ids[7] = (nk_draw_index)(idx1+1);
                ids[8] = (nk_draw_index)(idx1 + 0); ids[9] = (nk_draw_index)(idx1+0);
                ids[10]= (nk_draw_index)(idx2 + 0); ids[11]= (nk_draw_index)(idx2+1);
                ids += 12;
                idx1 = idx2;
            }

            /* fill vertices */
            for (i = 0; i < points_count; ++i) {
                const struct nk_vec2 uv = list->null.uv;
                vtx[0] = nk_draw_vertex(points[i], uv, col);
                vtx[1] = nk_draw_vertex(temp[i*2+0], uv, col_trans);
                vtx[2] = nk_draw_vertex(temp[i*2+1], uv, col_trans);
                vtx += 3;
            }
        } else {
            nk_size idx1, i;
            const float half_inner_thickness = (thickness - AA_SIZE) * 0.5f;
            if (!closed) {
                struct nk_vec2 d1 = nk_vec2_muls(normals[0], half_inner_thickness + AA_SIZE);
                struct nk_vec2 d2 = nk_vec2_muls(normals[0], half_inner_thickness);

                temp[0] = nk_vec2_add(points[0], d1);
                temp[1] = nk_vec2_add(points[0], d2);
                temp[2] = nk_vec2_sub(points[0], d2);
                temp[3] = nk_vec2_sub(points[0], d1);

                d1 = nk_vec2_muls(normals[points_count-1], half_inner_thickness + AA_SIZE);
                d2 = nk_vec2_muls(normals[points_count-1], half_inner_thickness);

                temp[(points_count-1)*4+0] = nk_vec2_add(points[points_count-1], d1);
                temp[(points_count-1)*4+1] = nk_vec2_add(points[points_count-1], d2);
                temp[(points_count-1)*4+2] = nk_vec2_sub(points[points_count-1], d2);
                temp[(points_count-1)*4+3] = nk_vec2_sub(points[points_count-1], d1);
            }

            /* add all elements */
            idx1 = index;
            for (i1 = 0; i1 < count; ++i1) {
                struct nk_vec2 dm_out, dm_in;
                const nk_size i2 = ((i1+1) == points_count) ? 0: (i1 + 1);
                nk_size idx2 = ((i1+1) == points_count) ? index: (idx1 + 4);

                /* average normals */
                struct nk_vec2 dm = nk_vec2_muls(nk_vec2_add(normals[i1], normals[i2]), 0.5f);
                float dmr2 = dm.x * dm.x + dm.y* dm.y;
                if (dmr2 > 0.000001f) {
                    float scale = 1.0f/dmr2;
                    scale = NK_MIN(100.0f, scale);
                    dm = nk_vec2_muls(dm, scale);
                }

                dm_out = nk_vec2_muls(dm, ((half_inner_thickness) + AA_SIZE));
                dm_in = nk_vec2_muls(dm, half_inner_thickness);
                temp[i2*4+0] = nk_vec2_add(points[i2], dm_out);
                temp[i2*4+1] = nk_vec2_add(points[i2], dm_in);
                temp[i2*4+2] = nk_vec2_sub(points[i2], dm_in);
                temp[i2*4+3] = nk_vec2_sub(points[i2], dm_out);

                /* add indexes */
                ids[0] = (nk_draw_index)(idx2 + 1); ids[1] = (nk_draw_index)(idx1+1);
                ids[2] = (nk_draw_index)(idx1 + 2); ids[3] = (nk_draw_index)(idx1+2);
                ids[4] = (nk_draw_index)(idx2 + 2); ids[5] = (nk_draw_index)(idx2+1);
                ids[6] = (nk_draw_index)(idx2 + 1); ids[7] = (nk_draw_index)(idx1+1);
                ids[8] = (nk_draw_index)(idx1 + 0); ids[9] = (nk_draw_index)(idx1+0);
                ids[10]= (nk_draw_index)(idx2 + 0); ids[11] = (nk_draw_index)(idx2+1);
                ids[12]= (nk_draw_index)(idx2 + 2); ids[13] = (nk_draw_index)(idx1+2);
                ids[14]= (nk_draw_index)(idx1 + 3); ids[15] = (nk_draw_index)(idx1+3);
                ids[16]= (nk_draw_index)(idx2 + 3); ids[17] = (nk_draw_index)(idx2+2);
                ids += 18;
                idx1 = idx2;
            }

            /* add vertices */
            for (i = 0; i < points_count; ++i) {
                const struct nk_vec2 uv = list->null.uv;
                vtx[0] = nk_draw_vertex(temp[i*4+0], uv, col_trans);
                vtx[1] = nk_draw_vertex(temp[i*4+1], uv, col);
                vtx[2] = nk_draw_vertex(temp[i*4+2], uv, col);
                vtx[3] = nk_draw_vertex(temp[i*4+3], uv, col_trans);
                vtx += 4;
            }
        }

        /* free temporary normals + points */
        nk_buffer_reset(list->vertices, NK_BUFFER_FRONT);
    } else {
        /* NON ANTI-ALIASED STROKE */
        nk_size i1 = 0;
        nk_size idx = list->vertex_count;
        const nk_size idx_count = count * 6;
        const nk_size vtx_count = count * 4;
        struct nk_draw_vertex *vtx = nk_draw_list_alloc_vertices(list, vtx_count);
        nk_draw_index *ids = nk_draw_list_alloc_elements(list, idx_count);
        if (!vtx || !ids) return;

        for (i1 = 0; i1 < count; ++i1) {
            float dx, dy;
            const struct nk_vec2 uv = list->null.uv;
            const nk_size i2 = ((i1+1) == points_count) ? 0 : i1 + 1;
            const struct nk_vec2 p1 = points[i1];
            const struct nk_vec2 p2 = points[i2];
            struct nk_vec2 diff = nk_vec2_sub(p2, p1);
            float len;

            /* vec2 inverted length  */
            len = nk_vec2_len_sqr(diff);
            if (len != 0.0f)
                len = nk_inv_sqrt(len);
            else len = 1.0f;
            diff = nk_vec2_muls(diff, len);

            /* add vertices */
            dx = diff.x * (thickness * 0.5f);
            dy = diff.y * (thickness * 0.5f);

            vtx[0] = nk_draw_vertex(nk_vec2(p1.x + dy, p1.y - dx), uv, col);
            vtx[1] = nk_draw_vertex(nk_vec2(p2.x + dy, p2.y - dx), uv, col);
            vtx[2] = nk_draw_vertex(nk_vec2(p2.x - dy, p2.y + dx), uv, col);
            vtx[3] = nk_draw_vertex(nk_vec2(p1.x - dy, p1.y + dx), uv, col);
            vtx += 4;

            ids[0] = (nk_draw_index)(idx+0); ids[1] = (nk_draw_index)(idx+1);
            ids[2] = (nk_draw_index)(idx+2); ids[3] = (nk_draw_index)(idx+0);
            ids[4] = (nk_draw_index)(idx+2); ids[5] = (nk_draw_index)(idx+3);
            ids += 6;
            idx += 4;
        }
    }
}

NK_API void
nk_draw_list_fill_poly_convex(struct nk_draw_list *list,
    const struct nk_vec2 *points, const unsigned int points_count,
    struct nk_color color, enum nk_anti_aliasing aliasing)
{
    NK_STORAGE const nk_size pnt_align = NK_ALIGNOF(struct nk_vec2);
    NK_STORAGE const nk_size pnt_size = sizeof(struct nk_vec2);
    nk_draw_vertex_color col;
    NK_ASSERT(list);
    if (!list || points_count < 3) return;

#ifdef NK_INCLUDE_COMMAND_USERDATA
    nk_draw_list_push_userdata(list, list->userdata);
#endif

    color.a = (nk_byte)((float)color.a * list->global_alpha);
    col = nk_color_u32(color);
    if (aliasing == NK_ANTI_ALIASING_ON) {
        nk_size i = 0;
        nk_size i0 = 0;
        nk_size i1 = 0;

        const float AA_SIZE = 1.0f;
        nk_size vertex_offset = 0;
        const nk_draw_vertex_color col_trans = col & 0x00ffffff;
        nk_size index = list->vertex_count;
        const nk_size idx_count = (points_count-2)*3 + points_count*6;
        const nk_size vtx_count = (points_count*2);
        struct nk_draw_vertex *vtx = nk_draw_list_alloc_vertices(list, vtx_count);
        nk_draw_index *ids = nk_draw_list_alloc_elements(list, idx_count);

        unsigned int vtx_inner_idx = (unsigned int)(index + 0);
        unsigned int vtx_outer_idx = (unsigned int)(index + 1);
        struct nk_vec2 *normals = 0;
        nk_size size = 0;
        if (!vtx || !ids) return;

        /* temporary allocate normals */
        vertex_offset = (nk_size)((nk_byte*)vtx - (nk_byte*)list->vertices->memory.ptr);
        nk_buffer_mark(list->vertices, NK_BUFFER_FRONT);
        size = pnt_size * points_count;
        normals = (struct nk_vec2*)
            nk_buffer_alloc(list->vertices, NK_BUFFER_FRONT, size, pnt_align);
        NK_ASSERT(normals);
        if (!normals) return;
        vtx = (struct nk_draw_vertex*)(void*)((nk_byte*)list->vertices->memory.ptr + vertex_offset);

        /* add elements */
        for (i = 2; i < points_count; i++) {
            ids[0] = (nk_draw_index)(vtx_inner_idx);
            ids[1] = (nk_draw_index)(vtx_inner_idx + ((i-1) << 1));
            ids[2] = (nk_draw_index)(vtx_inner_idx + (i << 1));
            ids += 3;
        }

        /* compute normals */
        for (i0 = points_count-1, i1 = 0; i1 < points_count; i0 = i1++) {
            struct nk_vec2 p0 = points[i0];
            struct nk_vec2 p1 = points[i1];
            struct nk_vec2 diff = nk_vec2_sub(p1, p0);

            /* vec2 inverted length  */
            float len = nk_vec2_len_sqr(diff);
            if (len != 0.0f)
                len = nk_inv_sqrt(len);
            else len = 1.0f;
            diff = nk_vec2_muls(diff, len);

            normals[i0].x = diff.y;
            normals[i0].y = -diff.x;
        }

        /* add vertices + indexes */
        for (i0 = points_count-1, i1 = 0; i1 < points_count; i0 = i1++) {
            const struct nk_vec2 uv = list->null.uv;
            struct nk_vec2 n0 = normals[i0];
            struct nk_vec2 n1 = normals[i1];
            struct nk_vec2 dm = nk_vec2_muls(nk_vec2_add(n0, n1), 0.5f);

            float dmr2 = dm.x*dm.x + dm.y*dm.y;
            if (dmr2 > 0.000001f) {
                float scale = 1.0f / dmr2;
                scale = NK_MIN(scale, 100.0f);
                dm = nk_vec2_muls(dm, scale);
            }
            dm = nk_vec2_muls(dm, AA_SIZE * 0.5f);

            /* add vertices */
            vtx[0] = nk_draw_vertex(nk_vec2_sub(points[i1], dm), uv, col);
            vtx[1] = nk_draw_vertex(nk_vec2_add(points[i1], dm), uv, col_trans);
            vtx += 2;

            /* add indexes */
            ids[0] = (nk_draw_index)(vtx_inner_idx+(i1<<1));
            ids[1] = (nk_draw_index)(vtx_inner_idx+(i0<<1));
            ids[2] = (nk_draw_index)(vtx_outer_idx+(i0<<1));
            ids[3] = (nk_draw_index)(vtx_outer_idx+(i0<<1));
            ids[4] = (nk_draw_index)(vtx_outer_idx+(i1<<1));
            ids[5] = (nk_draw_index)(vtx_inner_idx+(i1<<1));
            ids += 6;
        }
        /* free temporary normals + points */
        nk_buffer_reset(list->vertices, NK_BUFFER_FRONT);
    } else {
        nk_size i = 0;
        nk_size index = list->vertex_count;
        const nk_size idx_count = (points_count-2)*3;
        const nk_size vtx_count = points_count;
        struct nk_draw_vertex *vtx = nk_draw_list_alloc_vertices(list, vtx_count);
        nk_draw_index *ids = nk_draw_list_alloc_elements(list, idx_count);
        if (!vtx || !ids) return;
        for (i = 0; i < vtx_count; ++i) {
            vtx[0] = nk_draw_vertex(points[i], list->null.uv, col);
            vtx++;
        }
        for (i = 2; i < points_count; ++i) {
            ids[0] = (nk_draw_index)index;
            ids[1] = (nk_draw_index)(index+ i - 1);
            ids[2] = (nk_draw_index)(index+i);
            ids += 3;
        }
    }
}

NK_API void
nk_draw_list_path_clear(struct nk_draw_list *list)
{
    NK_ASSERT(list);
    if (!list) return;
    nk_buffer_reset(list->buffer, NK_BUFFER_FRONT);
    list->path_count = 0;
    list->path_offset = 0;
}

NK_API void
nk_draw_list_path_line_to(struct nk_draw_list *list, struct nk_vec2 pos)
{
    struct nk_vec2 *points = 0;
    struct nk_draw_command *cmd = 0;
    NK_ASSERT(list);
    if (!list) return;
    if (!list->cmd_count)
        nk_draw_list_add_clip(list, nk_null_rect);

    cmd = nk_draw_list_command_last(list);
    if (cmd && cmd->texture.ptr != list->null.texture.ptr)
        nk_draw_list_push_image(list, list->null.texture);

    points = nk_draw_list_alloc_path(list, 1);
    if (!points) return;
    points[0] = pos;
}

NK_API void
nk_draw_list_path_arc_to_fast(struct nk_draw_list *list, struct nk_vec2 center,
    float radius, int a_min, int a_max)
{
    NK_ASSERT(list);
    if (!list) return;
    if (a_min <= a_max) {
        int a = 0;
        for (a = a_min; a <= a_max; a++) {
            const struct nk_vec2 c = list->circle_vtx[(nk_size)a % NK_LEN(list->circle_vtx)];
            const float x = center.x + c.x * radius;
            const float y = center.y + c.y * radius;
            nk_draw_list_path_line_to(list, nk_vec2(x, y));
        }
    }
}

NK_API void
nk_draw_list_path_arc_to(struct nk_draw_list *list, struct nk_vec2 center,
    float radius, float a_min, float a_max, unsigned int segments)
{
    unsigned int i = 0;
    NK_ASSERT(list);
    if (!list) return;
    if (radius == 0.0f) return;
    for (i = 0; i <= segments; ++i) {
        const float a = a_min + ((float)i / ((float)segments) * (a_max - a_min));
        const float x = center.x + (float)NK_COS(a) * radius;
        const float y = center.y + (float)NK_SIN(a) * radius;
        nk_draw_list_path_line_to(list, nk_vec2(x, y));
    }
}

NK_API void
nk_draw_list_path_rect_to(struct nk_draw_list *list, struct nk_vec2 a,
    struct nk_vec2 b, float rounding)
{
    float r;
    NK_ASSERT(list);
    if (!list) return;
    r = rounding;
    r = NK_MIN(r, ((b.x-a.x) < 0) ? -(b.x-a.x): (b.x-a.x));
    r = NK_MIN(r, ((b.y-a.y) < 0) ? -(b.y-a.y): (b.y-a.y));

    if (r == 0.0f) {
        nk_draw_list_path_line_to(list, a);
        nk_draw_list_path_line_to(list, nk_vec2(b.x,a.y));
        nk_draw_list_path_line_to(list, b);
        nk_draw_list_path_line_to(list, nk_vec2(a.x,b.y));
    } else {
        nk_draw_list_path_arc_to_fast(list, nk_vec2(a.x + r, a.y + r), r, 6, 9);
        nk_draw_list_path_arc_to_fast(list, nk_vec2(b.x - r, a.y + r), r, 9, 12);
        nk_draw_list_path_arc_to_fast(list, nk_vec2(b.x - r, b.y - r), r, 0, 3);
        nk_draw_list_path_arc_to_fast(list, nk_vec2(a.x + r, b.y - r), r, 3, 6);
    }
}

NK_API void
nk_draw_list_path_curve_to(struct nk_draw_list *list, struct nk_vec2 p2,
    struct nk_vec2 p3, struct nk_vec2 p4, unsigned int num_segments)
{
    unsigned int i_step;
    float t_step;
    struct nk_vec2 p1;

    NK_ASSERT(list);
    NK_ASSERT(list->path_count);
    if (!list || !list->path_count) return;
    num_segments = NK_MAX(num_segments, 1);

    p1 = nk_draw_list_path_last(list);
    t_step = 1.0f/(float)num_segments;
    for (i_step = 1; i_step <= num_segments; ++i_step) {
        float t = t_step * (float)i_step;
        float u = 1.0f - t;
        float w1 = u*u*u;
        float w2 = 3*u*u*t;
        float w3 = 3*u*t*t;
        float w4 = t * t *t;
        float x = w1 * p1.x + w2 * p2.x + w3 * p3.x + w4 * p4.x;
        float y = w1 * p1.y + w2 * p2.y + w3 * p3.y + w4 * p4.y;
        nk_draw_list_path_line_to(list, nk_vec2(x,y));
    }
}

NK_API void
nk_draw_list_path_fill(struct nk_draw_list *list, struct nk_color color)
{
    struct nk_vec2 *points;
    NK_ASSERT(list);
    if (!list) return;
    points = (struct nk_vec2*)nk_buffer_memory(list->buffer);
    nk_draw_list_fill_poly_convex(list, points, list->path_count, color, list->shape_AA);
    nk_draw_list_path_clear(list);
}

NK_API void
nk_draw_list_path_stroke(struct nk_draw_list *list, struct nk_color color,
    enum nk_draw_list_stroke closed, float thickness)
{
    struct nk_vec2 *points;
    NK_ASSERT(list);
    if (!list) return;
    points = (struct nk_vec2*)nk_buffer_memory(list->buffer);
    nk_draw_list_stroke_poly_line(list, points, list->path_count, color,
        closed, thickness, list->line_AA);
    nk_draw_list_path_clear(list);
}

NK_API void
nk_draw_list_stroke_line(struct nk_draw_list *list, struct nk_vec2 a,
    struct nk_vec2 b, struct nk_color col, float thickness)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;
    nk_draw_list_path_line_to(list, nk_vec2_add(a, nk_vec2(0.5f, 0.5f)));
    nk_draw_list_path_line_to(list, nk_vec2_add(b, nk_vec2(0.5f, 0.5f)));
    nk_draw_list_path_stroke(list,  col, NK_STROKE_OPEN, thickness);
}

NK_API void
nk_draw_list_fill_rect(struct nk_draw_list *list, struct nk_rect rect,
    struct nk_color col, float rounding)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;
    nk_draw_list_path_rect_to(list, nk_vec2(rect.x + 0.5f, rect.y + 0.5f),
        nk_vec2(rect.x + rect.w + 0.5f, rect.y + rect.h + 0.5f), rounding);
    nk_draw_list_path_fill(list,  col);
}

NK_API void
nk_draw_list_stroke_rect(struct nk_draw_list *list, struct nk_rect rect,
    struct nk_color col, float rounding, float thickness)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;
    nk_draw_list_path_rect_to(list, nk_vec2(rect.x + 0.5f, rect.y + 0.5f),
        nk_vec2(rect.x + rect.w + 0.5f, rect.y + rect.h + 0.5f), rounding);
    nk_draw_list_path_stroke(list,  col, NK_STROKE_CLOSED, thickness);
}

NK_API void
nk_draw_list_fill_rect_multi_color(struct nk_draw_list *list, struct nk_rect rect,
    struct nk_color left, struct nk_color top, struct nk_color right,
    struct nk_color bottom)
{
    nk_draw_vertex_color col_left = nk_color_u32(left);
    nk_draw_vertex_color col_top = nk_color_u32(top);
    nk_draw_vertex_color col_right = nk_color_u32(right);
    nk_draw_vertex_color col_bottom = nk_color_u32(bottom);

    struct nk_draw_vertex *vtx;
    nk_draw_index *idx;
    nk_draw_index index;
    NK_ASSERT(list);
    if (!list) return;

    nk_draw_list_push_image(list, list->null.texture);
    index = (nk_draw_index)list->vertex_count;
    vtx = nk_draw_list_alloc_vertices(list, 4);
    idx = nk_draw_list_alloc_elements(list, 6);
    if (!vtx || !idx) return;

    idx[0] = (nk_draw_index)(index+0); idx[1] = (nk_draw_index)(index+1);
    idx[2] = (nk_draw_index)(index+2); idx[3] = (nk_draw_index)(index+0);
    idx[4] = (nk_draw_index)(index+2); idx[5] = (nk_draw_index)(index+3);

    vtx[0] = nk_draw_vertex(nk_vec2(rect.x, rect.y), list->null.uv, col_left);
    vtx[1] = nk_draw_vertex(nk_vec2(rect.x + rect.w, rect.y), list->null.uv, col_top);
    vtx[2] = nk_draw_vertex(nk_vec2(rect.x + rect.w, rect.y + rect.h), list->null.uv, col_right);
    vtx[3] = nk_draw_vertex(nk_vec2(rect.x, rect.y + rect.h), list->null.uv, col_bottom);
}

NK_API void
nk_draw_list_fill_triangle(struct nk_draw_list *list, struct nk_vec2 a,
    struct nk_vec2 b, struct nk_vec2 c, struct nk_color col)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;
    nk_draw_list_path_line_to(list, a);
    nk_draw_list_path_line_to(list, b);
    nk_draw_list_path_line_to(list, c);
    nk_draw_list_path_fill(list, col);
}

NK_API void
nk_draw_list_stroke_triangle(struct nk_draw_list *list, struct nk_vec2 a,
    struct nk_vec2 b, struct nk_vec2 c, struct nk_color col, float thickness)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;
    nk_draw_list_path_line_to(list, a);
    nk_draw_list_path_line_to(list, b);
    nk_draw_list_path_line_to(list, c);
    nk_draw_list_path_stroke(list, col, NK_STROKE_CLOSED, thickness);
}

NK_API void
nk_draw_list_fill_circle(struct nk_draw_list *list, struct nk_vec2 center,
    float radius, struct nk_color col, unsigned int segs)
{
    float a_max;
    NK_ASSERT(list);
    if (!list || !col.a) return;
    a_max = NK_PI * 2.0f * ((float)segs - 1.0f) / (float)segs;
    nk_draw_list_path_arc_to(list, center, radius, 0.0f, a_max, segs);
    nk_draw_list_path_fill(list, col);
}

NK_API void
nk_draw_list_stroke_circle(struct nk_draw_list *list, struct nk_vec2 center,
    float radius, struct nk_color col, unsigned int segs, float thickness)
{
    float a_max;
    NK_ASSERT(list);
    if (!list || !col.a) return;
    a_max = NK_PI * 2.0f * ((float)segs - 1.0f) / (float)segs;
    nk_draw_list_path_arc_to(list, center, radius, 0.0f, a_max, segs);
    nk_draw_list_path_stroke(list, col, NK_STROKE_CLOSED, thickness);
}

NK_API void
nk_draw_list_stroke_curve(struct nk_draw_list *list, struct nk_vec2 p0,
    struct nk_vec2 cp0, struct nk_vec2 cp1, struct nk_vec2 p1,
    struct nk_color col, unsigned int segments, float thickness)
{
    NK_ASSERT(list);
    if (!list || !col.a) return;
    nk_draw_list_path_line_to(list, p0);
    nk_draw_list_path_curve_to(list, cp0, cp1, p1, segments);
    nk_draw_list_path_stroke(list, col, NK_STROKE_OPEN, thickness);
}

NK_INTERN void
nk_draw_list_push_rect_uv(struct nk_draw_list *list, struct nk_vec2 a,
    struct nk_vec2 c, struct nk_vec2 uva, struct nk_vec2 uvc,
    struct nk_color color)
{
    nk_draw_vertex_color col = nk_color_u32(color);
    struct nk_draw_vertex *vtx;
    struct nk_vec2 uvb;
    struct nk_vec2 uvd;
    struct nk_vec2 b;
    struct nk_vec2 d;
    nk_draw_index *idx;
    nk_draw_index index;
    NK_ASSERT(list);
    if (!list) return;

    uvb = nk_vec2(uvc.x, uva.y);
    uvd = nk_vec2(uva.x, uvc.y);
    b = nk_vec2(c.x, a.y);
    d = nk_vec2(a.x, c.y);

    index = (nk_draw_index)list->vertex_count;
    vtx = nk_draw_list_alloc_vertices(list, 4);
    idx = nk_draw_list_alloc_elements(list, 6);
    if (!vtx || !idx) return;

    idx[0] = (nk_draw_index)(index+0); idx[1] = (nk_draw_index)(index+1);
    idx[2] = (nk_draw_index)(index+2); idx[3] = (nk_draw_index)(index+0);
    idx[4] = (nk_draw_index)(index+2); idx[5] = (nk_draw_index)(index+3);

    vtx[0] = nk_draw_vertex(a, uva, col);
    vtx[1] = nk_draw_vertex(b, uvb, col);
    vtx[2] = nk_draw_vertex(c, uvc, col);
    vtx[3] = nk_draw_vertex(d, uvd, col);
}

NK_API void
nk_draw_list_add_image(struct nk_draw_list *list, struct nk_image texture,
    struct nk_rect rect, struct nk_color color)
{
    NK_ASSERT(list);
    if (!list) return;
    /* push new command with given texture */
    nk_draw_list_push_image(list, texture.handle);
    if (nk_image_is_subimage(&texture)) {
        /* add region inside of the texture  */
        struct nk_vec2 uv[2];
        uv[0].x = (float)texture.region[0]/(float)texture.w;
        uv[0].y = (float)texture.region[1]/(float)texture.h;
        uv[1].x = (float)(texture.region[0] + texture.region[2])/(float)texture.w;
        uv[1].y = (float)(texture.region[1] + texture.region[3])/(float)texture.h;
        nk_draw_list_push_rect_uv(list, nk_vec2(rect.x, rect.y),
            nk_vec2(rect.x + rect.w, rect.y + rect.h),  uv[0], uv[1], color);
    } else nk_draw_list_push_rect_uv(list, nk_vec2(rect.x, rect.y),
            nk_vec2(rect.x + rect.w, rect.y + rect.h),
            nk_vec2(0.0f, 0.0f), nk_vec2(1.0f, 1.0f),color);
}

NK_API void
nk_draw_list_add_text(struct nk_draw_list *list, const struct nk_user_font *font,
    struct nk_rect rect, const char *text, int len, float font_height,
    struct nk_color fg)
{
    float x = 0;
    int text_len = 0;
    nk_rune unicode = 0;
    nk_rune next = 0;
    int glyph_len = 0;
    int next_glyph_len = 0;
    struct nk_user_font_glyph g;

    NK_ASSERT(list);
    if (!list || !len || !text) return;
    if (rect.x > (list->clip_rect.x + list->clip_rect.w) ||
        rect.y > (list->clip_rect.y + list->clip_rect.h) ||
        rect.x < list->clip_rect.x || rect.y < list->clip_rect.y)
        return;

    nk_draw_list_push_image(list, font->texture);
    x = rect.x;
    glyph_len = text_len = nk_utf_decode(text, &unicode, len);
    if (!glyph_len) return;

    /* draw every glyph image */
    while (text_len <= len && glyph_len) {
        float gx, gy, gh, gw;
        float char_width = 0;
        if (unicode == NK_UTF_INVALID) break;

        /* query currently drawn glyph information */
        next_glyph_len = nk_utf_decode(text + text_len, &next, (int)len - text_len);
        font->query(font->userdata, font_height, &g, unicode,
                    (next == NK_UTF_INVALID) ? '\0' : next);

        /* calculate and draw glyph drawing rectangle and image */
        gx = x + g.offset.x;
        /*gy = rect.y + (rect.h/2) - (font->height/2) + g.offset.y;*/
        gy = rect.y + g.offset.y;
        gw = g.width; gh = g.height;
        char_width = g.xadvance;
        fg.a = (nk_byte)((float)fg.a * list->global_alpha);
        nk_draw_list_push_rect_uv(list, nk_vec2(gx,gy), nk_vec2(gx + gw, gy+ gh),
            g.uv[0], g.uv[1], fg);

        /* offset next glyph */
        text_len += glyph_len;
        x += char_width;
        glyph_len = next_glyph_len;
        unicode = next;
    }
}

NK_API void
nk_convert(struct nk_context *ctx, struct nk_buffer *cmds,
    struct nk_buffer *vertices, struct nk_buffer *elements,
    const struct nk_convert_config *config)
{
    const struct nk_command *cmd;
    NK_ASSERT(ctx);
    NK_ASSERT(cmds);
    NK_ASSERT(vertices);
    NK_ASSERT(elements);
    if (!ctx || !cmds || !vertices || !elements)
        return;

    nk_draw_list_setup(&ctx->draw_list, config->global_alpha, config->line_AA,
        config->shape_AA, config->null, cmds, vertices, elements);
    nk_foreach(cmd, ctx)
    {
#ifdef NK_INCLUDE_COMMAND_USERDATA
        list->userdata = cmd->userdata;
#endif
        switch (cmd->type) {
        case NK_COMMAND_NOP: break;
        case NK_COMMAND_SCISSOR: {
            const struct nk_command_scissor *s = (const struct nk_command_scissor*)cmd;
            nk_draw_list_add_clip(&ctx->draw_list, nk_rect(s->x, s->y, s->w, s->h));
        } break;
        case NK_COMMAND_LINE: {
            const struct nk_command_line *l = (const struct nk_command_line*)cmd;
            nk_draw_list_stroke_line(&ctx->draw_list, nk_vec2(l->begin.x, l->begin.y),
                nk_vec2(l->end.x, l->end.y), l->color, l->line_thickness);
        } break;
        case NK_COMMAND_CURVE: {
            const struct nk_command_curve *q = (const struct nk_command_curve*)cmd;
            nk_draw_list_stroke_curve(&ctx->draw_list, nk_vec2(q->begin.x, q->begin.y),
                nk_vec2(q->ctrl[0].x, q->ctrl[0].y), nk_vec2(q->ctrl[1].x,
                q->ctrl[1].y), nk_vec2(q->end.x, q->end.y), q->color,
                config->curve_segment_count, q->line_thickness);
        } break;
        case NK_COMMAND_RECT: {
            const struct nk_command_rect *r = (const struct nk_command_rect*)cmd;
            nk_draw_list_stroke_rect(&ctx->draw_list, nk_rect(r->x, r->y, r->w, r->h),
                r->color, (float)r->rounding, r->line_thickness);
        } break;
        case NK_COMMAND_RECT_FILLED: {
            const struct nk_command_rect_filled *r = (const struct nk_command_rect_filled*)cmd;
            nk_draw_list_fill_rect(&ctx->draw_list, nk_rect(r->x, r->y, r->w, r->h),
                r->color, (float)r->rounding);
        } break;
        case NK_COMMAND_RECT_MULTI_COLOR: {
            const struct nk_command_rect_multi_color *r = (const struct nk_command_rect_multi_color*)cmd;
            nk_draw_list_fill_rect_multi_color(&ctx->draw_list, nk_rect(r->x, r->y, r->w, r->h),
                r->left, r->top, r->right, r->bottom);
        } break;
        case NK_COMMAND_CIRCLE: {
            const struct nk_command_circle *c = (const struct nk_command_circle*)cmd;
            nk_draw_list_stroke_circle(&ctx->draw_list, nk_vec2((float)c->x + (float)c->w/2,
                (float)c->y + (float)c->h/2), (float)c->w/2, c->color,
                config->circle_segment_count, c->line_thickness);
        } break;
        case NK_COMMAND_CIRCLE_FILLED: {
            const struct nk_command_circle_filled *c = (const struct nk_command_circle_filled *)cmd;
            nk_draw_list_fill_circle(&ctx->draw_list, nk_vec2((float)c->x + (float)c->w/2,
                (float)c->y + (float)c->h/2), (float)c->w/2, c->color,
                config->circle_segment_count);
        } break;
        case NK_COMMAND_ARC: {
            const struct nk_command_arc *c = (const struct nk_command_arc*)cmd;
            nk_draw_list_path_line_to(&ctx->draw_list, nk_vec2(c->cx, c->cy));
            nk_draw_list_path_arc_to(&ctx->draw_list, nk_vec2(c->cx, c->cy), c->r,
                c->a[0], c->a[1], config->arc_segment_count);
            nk_draw_list_path_stroke(&ctx->draw_list, c->color, NK_STROKE_CLOSED, c->line_thickness);
        } break;
        case NK_COMMAND_ARC_FILLED: {
            const struct nk_command_arc_filled *c = (const struct nk_command_arc_filled*)cmd;
            nk_draw_list_path_line_to(&ctx->draw_list, nk_vec2(c->cx, c->cy));
            nk_draw_list_path_arc_to(&ctx->draw_list, nk_vec2(c->cx, c->cy), c->r,
                c->a[0], c->a[1], config->arc_segment_count);
            nk_draw_list_path_fill(&ctx->draw_list, c->color);
        } break;
        case NK_COMMAND_TRIANGLE: {
            const struct nk_command_triangle *t = (const struct nk_command_triangle*)cmd;
            nk_draw_list_stroke_triangle(&ctx->draw_list, nk_vec2(t->a.x, t->a.y),
                nk_vec2(t->b.x, t->b.y), nk_vec2(t->c.x, t->c.y), t->color,
                t->line_thickness);
        } break;
        case NK_COMMAND_TRIANGLE_FILLED: {
            const struct nk_command_triangle_filled *t = (const struct nk_command_triangle_filled*)cmd;
            nk_draw_list_fill_triangle(&ctx->draw_list, nk_vec2(t->a.x, t->a.y),
                nk_vec2(t->b.x, t->b.y), nk_vec2(t->c.x, t->c.y), t->color);
        } break;
        case NK_COMMAND_POLYGON: {
            int i;
            const struct nk_command_polygon*p = (const struct nk_command_polygon*)cmd;
            for (i = 0; i < p->point_count; ++i) {
                struct nk_vec2 pnt = nk_vec2((float)p->points[i].x, (float)p->points[i].y);
                nk_draw_list_path_line_to(&ctx->draw_list, pnt);
            }
            nk_draw_list_path_stroke(&ctx->draw_list, p->color, NK_STROKE_CLOSED, p->line_thickness);
        } break;
        case NK_COMMAND_POLYGON_FILLED: {
            int i;
            const struct nk_command_polygon_filled *p = (const struct nk_command_polygon_filled*)cmd;
            for (i = 0; i < p->point_count; ++i) {
                struct nk_vec2 pnt = nk_vec2((float)p->points[i].x, (float)p->points[i].y);
                nk_draw_list_path_line_to(&ctx->draw_list, pnt);
            }
            nk_draw_list_path_fill(&ctx->draw_list, p->color);
        } break;
        case NK_COMMAND_POLYLINE: {
            int i;
            const struct nk_command_polyline *p = (const struct nk_command_polyline*)cmd;
            for (i = 0; i < p->point_count; ++i) {
                struct nk_vec2 pnt = nk_vec2((float)p->points[i].x, (float)p->points[i].y);
                nk_draw_list_path_line_to(&ctx->draw_list, pnt);
            }
            nk_draw_list_path_stroke(&ctx->draw_list, p->color, NK_STROKE_OPEN, p->line_thickness);
        } break;
        case NK_COMMAND_TEXT: {
            const struct nk_command_text *t = (const struct nk_command_text*)cmd;
            nk_draw_list_add_text(&ctx->draw_list, t->font, nk_rect(t->x, t->y, t->w, t->h),
                t->string, t->length, t->height, t->foreground);
        } break;
        case NK_COMMAND_IMAGE: {
            const struct nk_command_image *i = (const struct nk_command_image*)cmd;
            nk_draw_list_add_image(&ctx->draw_list, i->img, nk_rect(i->x, i->y, i->w, i->h),
                nk_rgb(255, 255, 255));
        } break;
        default: break;
        }
    }
}

NK_API const struct nk_draw_command*
nk__draw_begin(const struct nk_context *ctx,
    const struct nk_buffer *buffer)
{return nk__draw_list_begin(&ctx->draw_list, buffer);}

NK_API const struct nk_draw_command*
nk__draw_next(const struct nk_draw_command *cmd,
    const struct nk_buffer *buffer, const struct nk_context *ctx)
{return nk__draw_list_next(cmd, buffer, &ctx->draw_list);}

#endif

/*
 * ==============================================================
 *
 *                          FONT HANDLING
 *
 * ===============================================================
 */
#ifdef NK_INCLUDE_FONT_BAKING
/* -------------------------------------------------------------
 *
 *                          RECT PACK
 *
 * --------------------------------------------------------------*/
/* stb_rect_pack.h - v0.05 - public domain - rectangle packing */
/* Sean Barrett 2014 */
#define NK_RP__MAXVAL  0xffff
typedef unsigned short nk_rp_coord;

struct nk_rp_rect {
    /* reserved for your use: */
    int id;
    /* input: */
    nk_rp_coord w, h;
    /* output: */
    nk_rp_coord x, y;
    int was_packed;
    /* non-zero if valid packing */
}; /* 16 bytes, nominally */

struct nk_rp_node {
    nk_rp_coord  x,y;
    struct nk_rp_node  *next;
};

struct nk_rp_context {
    int width;
    int height;
    int align;
    int init_mode;
    int heuristic;
    int num_nodes;
    struct nk_rp_node *active_head;
    struct nk_rp_node *free_head;
    struct nk_rp_node extra[2];
    /* we allocate two extra nodes so optimal user-node-count is 'width' not 'width+2' */
};

struct nk_rp__findresult {
    int x,y;
    struct nk_rp_node **prev_link;
};

enum NK_RP_HEURISTIC {
    NK_RP_HEURISTIC_Skyline_default=0,
    NK_RP_HEURISTIC_Skyline_BL_sortHeight = NK_RP_HEURISTIC_Skyline_default,
    NK_RP_HEURISTIC_Skyline_BF_sortHeight
};
enum NK_RP_INIT_STATE{NK_RP__INIT_skyline = 1};

NK_INTERN void
nk_rp_setup_allow_out_of_mem(struct nk_rp_context *context, int allow_out_of_mem)
{
    if (allow_out_of_mem)
        /* if it's ok to run out of memory, then don't bother aligning them; */
        /* this gives better packing, but may fail due to OOM (even though */
        /* the rectangles easily fit). @TODO a smarter approach would be to only */
        /* quantize once we've hit OOM, then we could get rid of this parameter. */
        context->align = 1;
    else {
        /* if it's not ok to run out of memory, then quantize the widths */
        /* so that num_nodes is always enough nodes. */
        /* */
        /* I.e. num_nodes * align >= width */
        /*                  align >= width / num_nodes */
        /*                  align = ceil(width/num_nodes) */
        context->align = (context->width + context->num_nodes-1) / context->num_nodes;
    }
}

NK_INTERN void
nk_rp_init_target(struct nk_rp_context *context, int width, int height,
    struct nk_rp_node *nodes, int num_nodes)
{
    int i;
#ifndef STBRP_LARGE_RECTS
    NK_ASSERT(width <= 0xffff && height <= 0xffff);
#endif

    for (i=0; i < num_nodes-1; ++i)
        nodes[i].next = &nodes[i+1];
    nodes[i].next = 0;
    context->init_mode = NK_RP__INIT_skyline;
    context->heuristic = NK_RP_HEURISTIC_Skyline_default;
    context->free_head = &nodes[0];
    context->active_head = &context->extra[0];
    context->width = width;
    context->height = height;
    context->num_nodes = num_nodes;
    nk_rp_setup_allow_out_of_mem(context, 0);

    /* node 0 is the full width, node 1 is the sentinel (lets us not store width explicitly) */
    context->extra[0].x = 0;
    context->extra[0].y = 0;
    context->extra[0].next = &context->extra[1];
    context->extra[1].x = (nk_rp_coord) width;
    context->extra[1].y = 65535;
    context->extra[1].next = 0;
}

/* find minimum y position if it starts at x1 */
NK_INTERN int
nk_rp__skyline_find_min_y(struct nk_rp_context *c, struct nk_rp_node *first,
    int x0, int width, int *pwaste)
{
    struct nk_rp_node *node = first;
    int x1 = x0 + width;
    int min_y, visited_width, waste_area;
    NK_ASSERT(first->x <= x0);
    NK_UNUSED(c);

    NK_ASSERT(node->next->x > x0);
    /* we ended up handling this in the caller for efficiency */
    NK_ASSERT(node->x <= x0);

    min_y = 0;
    waste_area = 0;
    visited_width = 0;
    while (node->x < x1)
    {
        if (node->y > min_y) {
            /* raise min_y higher. */
            /* we've accounted for all waste up to min_y, */
            /* but we'll now add more waste for everything we've visited */
            waste_area += visited_width * (node->y - min_y);
            min_y = node->y;
            /* the first time through, visited_width might be reduced */
            if (node->x < x0)
            visited_width += node->next->x - x0;
            else
            visited_width += node->next->x - node->x;
        } else {
            /* add waste area */
            int under_width = node->next->x - node->x;
            if (under_width + visited_width > width)
            under_width = width - visited_width;
            waste_area += under_width * (min_y - node->y);
            visited_width += under_width;
        }
        node = node->next;
    }
    *pwaste = waste_area;
    return min_y;
}

NK_INTERN struct nk_rp__findresult
nk_rp__skyline_find_best_pos(struct nk_rp_context *c, int width, int height)
{
    int best_waste = (1<<30), best_x, best_y = (1 << 30);
    struct nk_rp__findresult fr;
    struct nk_rp_node **prev, *node, *tail, **best = 0;

    /* align to multiple of c->align */
    width = (width + c->align - 1);
    width -= width % c->align;
    NK_ASSERT(width % c->align == 0);

    node = c->active_head;
    prev = &c->active_head;
    while (node->x + width <= c->width) {
        int y,waste;
        y = nk_rp__skyline_find_min_y(c, node, node->x, width, &waste);
        /* actually just want to test BL */
        if (c->heuristic == NK_RP_HEURISTIC_Skyline_BL_sortHeight) {
            /* bottom left */
            if (y < best_y) {
            best_y = y;
            best = prev;
            }
        } else {
            /* best-fit */
            if (y + height <= c->height) {
                /* can only use it if it first vertically */
                if (y < best_y || (y == best_y && waste < best_waste)) {
                    best_y = y;
                    best_waste = waste;
                    best = prev;
                }
            }
        }
        prev = &node->next;
        node = node->next;
    }
    best_x = (best == 0) ? 0 : (*best)->x;

    /* if doing best-fit (BF), we also have to try aligning right edge to each node position */
    /* */
    /* e.g, if fitting */
    /* */
    /*     ____________________ */
    /*    |____________________| */
    /* */
    /*            into */
    /* */
    /*   |                         | */
    /*   |             ____________| */
    /*   |____________| */
    /* */
    /* then right-aligned reduces waste, but bottom-left BL is always chooses left-aligned */
    /* */
    /* This makes BF take about 2x the time */
    if (c->heuristic == NK_RP_HEURISTIC_Skyline_BF_sortHeight)
    {
        tail = c->active_head;
        node = c->active_head;
        prev = &c->active_head;
        /* find first node that's admissible */
        while (tail->x < width)
            tail = tail->next;
        while (tail)
        {
            int xpos = tail->x - width;
            int y,waste;
            NK_ASSERT(xpos >= 0);
            /* find the left position that matches this */
            while (node->next->x <= xpos) {
                prev = &node->next;
                node = node->next;
            }
            NK_ASSERT(node->next->x > xpos && node->x <= xpos);
            y = nk_rp__skyline_find_min_y(c, node, xpos, width, &waste);
            if (y + height < c->height) {
                if (y <= best_y) {
                    if (y < best_y || waste < best_waste || (waste==best_waste && xpos < best_x)) {
                        best_x = xpos;
                        NK_ASSERT(y <= best_y);
                        best_y = y;
                        best_waste = waste;
                        best = prev;
                    }
                }
            }
            tail = tail->next;
        }
    }
    fr.prev_link = best;
    fr.x = best_x;
    fr.y = best_y;
    return fr;
}

NK_INTERN struct nk_rp__findresult
nk_rp__skyline_pack_rectangle(struct nk_rp_context *context, int width, int height)
{
    /* find best position according to heuristic */
    struct nk_rp__findresult res = nk_rp__skyline_find_best_pos(context, width, height);
    struct nk_rp_node *node, *cur;

    /* bail if: */
    /*    1. it failed */
    /*    2. the best node doesn't fit (we don't always check this) */
    /*    3. we're out of memory */
    if (res.prev_link == 0 || res.y + height > context->height || context->free_head == 0) {
        res.prev_link = 0;
        return res;
    }

    /* on success, create new node */
    node = context->free_head;
    node->x = (nk_rp_coord) res.x;
    node->y = (nk_rp_coord) (res.y + height);

    context->free_head = node->next;

    /* insert the new node into the right starting point, and */
    /* let 'cur' point to the remaining nodes needing to be */
    /* stitched back in */
    cur = *res.prev_link;
    if (cur->x < res.x) {
        /* preserve the existing one, so start testing with the next one */
        struct nk_rp_node *next = cur->next;
        cur->next = node;
        cur = next;
    } else {
        *res.prev_link = node;
    }

    /* from here, traverse cur and free the nodes, until we get to one */
    /* that shouldn't be freed */
    while (cur->next && cur->next->x <= res.x + width) {
        struct nk_rp_node *next = cur->next;
        /* move the current node to the free list */
        cur->next = context->free_head;
        context->free_head = cur;
        cur = next;
    }
    /* stitch the list back in */
    node->next = cur;

    if (cur->x < res.x + width)
        cur->x = (nk_rp_coord) (res.x + width);
    return res;
}

NK_INTERN int
nk_rect_height_compare(const void *a, const void *b)
{
    const struct nk_rp_rect *p = (const struct nk_rp_rect *) a;
    const struct nk_rp_rect *q = (const struct nk_rp_rect *) b;
    if (p->h > q->h)
        return -1;
    if (p->h < q->h)
        return  1;
    return (p->w > q->w) ? -1 : (p->w < q->w);
}

NK_INTERN int
nk_rect_original_order(const void *a, const void *b)
{
    const struct nk_rp_rect *p = (const struct nk_rp_rect *) a;
    const struct nk_rp_rect *q = (const struct nk_rp_rect *) b;
    return (p->was_packed < q->was_packed) ? -1 : (p->was_packed > q->was_packed);
}

static void
nk_rp_qsort(struct nk_rp_rect *array, unsigned int len, int(*cmp)(const void*,const void*))
{
    /* iterative quick sort */
    #define NK_MAX_SORT_STACK 64
    unsigned right, left = 0, stack[NK_MAX_SORT_STACK], pos = 0;
    unsigned seed = len/2 * 69069+1;
    for (;;) {
        for (; left+1 < len; len++) {
            struct nk_rp_rect pivot, tmp;
            if (pos == NK_MAX_SORT_STACK) len = stack[pos = 0];
            pivot = array[left+seed%(len-left)];
            seed = seed * 69069 + 1;
            stack[pos++] = len;
            for (right = left-1;;) {
                while (cmp(&array[++right], &pivot) < 0);
                while (cmp(&pivot, &array[--len]) < 0);
                if (right >= len) break;
                tmp = array[right];
                array[right] = array[len];
                array[len] = tmp;
            }
        }
        if (pos == 0) break;
        left = len;
        len = stack[--pos];
    }
    #undef NK_MAX_SORT_STACK
}

NK_INTERN void
nk_rp_pack_rects(struct nk_rp_context *context, struct nk_rp_rect *rects, int num_rects)
{
    int i;
    /* we use the 'was_packed' field internally to allow sorting/unsorting */
    for (i=0; i < num_rects; ++i) {
        rects[i].was_packed = i;
    }

    /* sort according to heuristic */
    nk_rp_qsort(rects, (unsigned)num_rects, nk_rect_height_compare);

    for (i=0; i < num_rects; ++i) {
        struct nk_rp__findresult fr = nk_rp__skyline_pack_rectangle(context, rects[i].w, rects[i].h);
        if (fr.prev_link) {
            rects[i].x = (nk_rp_coord) fr.x;
            rects[i].y = (nk_rp_coord) fr.y;
        } else {
            rects[i].x = rects[i].y = NK_RP__MAXVAL;
        }
    }

    /* unsort */
    nk_rp_qsort(rects, (unsigned)num_rects, nk_rect_original_order);

    /* set was_packed flags */
    for (i=0; i < num_rects; ++i)
        rects[i].was_packed = !(rects[i].x == NK_RP__MAXVAL && rects[i].y == NK_RP__MAXVAL);
}

/*
 * ==============================================================
 *
 *                          TRUETYPE
 *
 * ===============================================================
 */
/* stb_truetype.h - v1.07 - public domain */
#define NK_TT_MAX_OVERSAMPLE   8
#define NK_TT__OVER_MASK  (NK_TT_MAX_OVERSAMPLE-1)

struct nk_tt_bakedchar {
    unsigned short x0,y0,x1,y1;
    /* coordinates of bbox in bitmap */
    float xoff,yoff,xadvance;
};

struct nk_tt_aligned_quad{
    float x0,y0,s0,t0; /* top-left */
    float x1,y1,s1,t1; /* bottom-right */
};

struct nk_tt_packedchar {
    unsigned short x0,y0,x1,y1;
    /* coordinates of bbox in bitmap */
    float xoff,yoff,xadvance;
    float xoff2,yoff2;
};

struct nk_tt_pack_range {
    float font_size;
    int first_unicode_codepoint_in_range;
    /* if non-zero, then the chars are continuous, and this is the first codepoint */
    int *array_of_unicode_codepoints;
    /* if non-zero, then this is an array of unicode codepoints */
    int num_chars;
    struct nk_tt_packedchar *chardata_for_range; /* output */
    unsigned char h_oversample, v_oversample;
    /* don't set these, they're used internally */
};

struct nk_tt_pack_context {
    void *pack_info;
    int   width;
    int   height;
    int   stride_in_bytes;
    int   padding;
    unsigned int   h_oversample, v_oversample;
    unsigned char *pixels;
    void  *nodes;
};

struct nk_tt_fontinfo {
    const unsigned char* data; /* pointer to .ttf file */
    int fontstart;/* offset of start of font */
    int numGlyphs;/* number of glyphs, needed for range checking */
    int loca,head,glyf,hhea,hmtx,kern; /* table locations as offset from start of .ttf */
    int index_map; /* a cmap mapping for our chosen character encoding */
    int indexToLocFormat; /* format needed to map from glyph index to glyph */
};

enum {
  NK_TT_vmove=1,
  NK_TT_vline,
  NK_TT_vcurve
};

struct nk_tt_vertex {
    short x,y,cx,cy;
    unsigned char type,padding;
};

struct nk_tt__bitmap{
   int w,h,stride;
   unsigned char *pixels;
};

struct nk_tt__hheap_chunk {
    struct nk_tt__hheap_chunk *next;
};
struct nk_tt__hheap {
    struct nk_allocator alloc;
    struct nk_tt__hheap_chunk *head;
    void   *first_free;
    int    num_remaining_in_head_chunk;
};

struct nk_tt__edge {
    float x0,y0, x1,y1;
    int invert;
};

struct nk_tt__active_edge {
    struct nk_tt__active_edge *next;
    float fx,fdx,fdy;
    float direction;
    float sy;
    float ey;
};
struct nk_tt__point {float x,y;};

#define NK_TT_MACSTYLE_DONTCARE     0
#define NK_TT_MACSTYLE_BOLD         1
#define NK_TT_MACSTYLE_ITALIC       2
#define NK_TT_MACSTYLE_UNDERSCORE   4
#define NK_TT_MACSTYLE_NONE         8
/* <= not same as 0, this makes us check the bitfield is 0 */

enum { /* platformID */
   NK_TT_PLATFORM_ID_UNICODE   =0,
   NK_TT_PLATFORM_ID_MAC       =1,
   NK_TT_PLATFORM_ID_ISO       =2,
   NK_TT_PLATFORM_ID_MICROSOFT =3
};

enum { /* encodingID for NK_TT_PLATFORM_ID_UNICODE */
   NK_TT_UNICODE_EID_UNICODE_1_0    =0,
   NK_TT_UNICODE_EID_UNICODE_1_1    =1,
   NK_TT_UNICODE_EID_ISO_10646      =2,
   NK_TT_UNICODE_EID_UNICODE_2_0_BMP=3,
   NK_TT_UNICODE_EID_UNICODE_2_0_FULL=4
};

enum { /* encodingID for NK_TT_PLATFORM_ID_MICROSOFT */
   NK_TT_MS_EID_SYMBOL        =0,
   NK_TT_MS_EID_UNICODE_BMP   =1,
   NK_TT_MS_EID_SHIFTJIS      =2,
   NK_TT_MS_EID_UNICODE_FULL  =10
};

enum { /* encodingID for NK_TT_PLATFORM_ID_MAC; same as Script Manager codes */
   NK_TT_MAC_EID_ROMAN        =0,   NK_TT_MAC_EID_ARABIC       =4,
   NK_TT_MAC_EID_JAPANESE     =1,   NK_TT_MAC_EID_HEBREW       =5,
   NK_TT_MAC_EID_CHINESE_TRAD =2,   NK_TT_MAC_EID_GREEK        =6,
   NK_TT_MAC_EID_KOREAN       =3,   NK_TT_MAC_EID_RUSSIAN      =7
};

enum { /* languageID for NK_TT_PLATFORM_ID_MICROSOFT; same as LCID... */
       /* problematic because there are e.g. 16 english LCIDs and 16 arabic LCIDs */
   NK_TT_MS_LANG_ENGLISH     =0x0409,   NK_TT_MS_LANG_ITALIAN     =0x0410,
   NK_TT_MS_LANG_CHINESE     =0x0804,   NK_TT_MS_LANG_JAPANESE    =0x0411,
   NK_TT_MS_LANG_DUTCH       =0x0413,   NK_TT_MS_LANG_KOREAN      =0x0412,
   NK_TT_MS_LANG_FRENCH      =0x040c,   NK_TT_MS_LANG_RUSSIAN     =0x0419,
   NK_TT_MS_LANG_GERMAN      =0x0407,   NK_TT_MS_LANG_SPANISH     =0x0409,
   NK_TT_MS_LANG_HEBREW      =0x040d,   NK_TT_MS_LANG_SWEDISH     =0x041D
};

enum { /* languageID for NK_TT_PLATFORM_ID_MAC */
   NK_TT_MAC_LANG_ENGLISH      =0 ,   NK_TT_MAC_LANG_JAPANESE     =11,
   NK_TT_MAC_LANG_ARABIC       =12,   NK_TT_MAC_LANG_KOREAN       =23,
   NK_TT_MAC_LANG_DUTCH        =4 ,   NK_TT_MAC_LANG_RUSSIAN      =32,
   NK_TT_MAC_LANG_FRENCH       =1 ,   NK_TT_MAC_LANG_SPANISH      =6 ,
   NK_TT_MAC_LANG_GERMAN       =2 ,   NK_TT_MAC_LANG_SWEDISH      =5 ,
   NK_TT_MAC_LANG_HEBREW       =10,   NK_TT_MAC_LANG_CHINESE_SIMPLIFIED =33,
   NK_TT_MAC_LANG_ITALIAN      =3 ,   NK_TT_MAC_LANG_CHINESE_TRAD =19
};

#define nk_ttBYTE(p)     (* (const nk_byte *) (p))
#define nk_ttCHAR(p)     (* (const char *) (p))

#if defined(NK_BIGENDIAN) && !defined(NK_ALLOW_UNALIGNED_TRUETYPE)
   #define nk_ttUSHORT(p)   (* (nk_ushort *) (p))
   #define nk_ttSHORT(p)    (* (nk_short *) (p))
   #define nk_ttULONG(p)    (* (nk_uint *) (p))
   #define nk_ttLONG(p)     (* (nk_int *) (p))
#else
    static nk_ushort nk_ttUSHORT(const nk_byte *p) { return (nk_ushort)(p[0]*256 + p[1]); }
    static nk_short nk_ttSHORT(const nk_byte *p)   { return (nk_short)(p[0]*256 + p[1]); }
    static nk_uint nk_ttULONG(const nk_byte *p)  { return (nk_uint)((p[0]<<24) + (p[1]<<16) + (p[2]<<8) + p[3]); }
#endif

#define nk_tt_tag4(p,c0,c1,c2,c3)\
    ((p)[0] == (c0) && (p)[1] == (c1) && (p)[2] == (c2) && (p)[3] == (c3))
#define nk_tt_tag(p,str) nk_tt_tag4(p,str[0],str[1],str[2],str[3])

NK_INTERN int nk_tt_GetGlyphShape(const struct nk_tt_fontinfo *info, struct nk_allocator *alloc,
                                int glyph_index, struct nk_tt_vertex **pvertices);

NK_INTERN nk_uint
nk_tt__find_table(const nk_byte *data, nk_uint fontstart, const char *tag)
{
    /* @OPTIMIZE: binary search */
    nk_int num_tables = nk_ttUSHORT(data+fontstart+4);
    nk_uint tabledir = fontstart + 12;
    nk_int i;
    for (i = 0; i < num_tables; ++i) {
        nk_uint loc = tabledir + (nk_uint)(16*i);
        if (nk_tt_tag(data+loc+0, tag))
            return nk_ttULONG(data+loc+8);
    }
    return 0;
}

NK_INTERN int
nk_tt_InitFont(struct nk_tt_fontinfo *info, const unsigned char *data2, int fontstart)
{
    nk_uint cmap, t;
    nk_int i,numTables;
    const nk_byte *data = (const nk_byte *) data2;

    info->data = data;
    info->fontstart = fontstart;

    cmap = nk_tt__find_table(data, (nk_uint)fontstart, "cmap");       /* required */
    info->loca = (int)nk_tt__find_table(data, (nk_uint)fontstart, "loca"); /* required */
    info->head = (int)nk_tt__find_table(data, (nk_uint)fontstart, "head"); /* required */
    info->glyf = (int)nk_tt__find_table(data, (nk_uint)fontstart, "glyf"); /* required */
    info->hhea = (int)nk_tt__find_table(data, (nk_uint)fontstart, "hhea"); /* required */
    info->hmtx = (int)nk_tt__find_table(data, (nk_uint)fontstart, "hmtx"); /* required */
    info->kern = (int)nk_tt__find_table(data, (nk_uint)fontstart, "kern"); /* not required */
    if (!cmap || !info->loca || !info->head || !info->glyf || !info->hhea || !info->hmtx)
        return 0;

    t = nk_tt__find_table(data, (nk_uint)fontstart, "maxp");
    if (t) info->numGlyphs = nk_ttUSHORT(data+t+4);
    else info->numGlyphs = 0xffff;

    /* find a cmap encoding table we understand *now* to avoid searching */
    /* later. (todo: could make this installable) */
    /* the same regardless of glyph. */
    numTables = nk_ttUSHORT(data + cmap + 2);
    info->index_map = 0;
    for (i=0; i < numTables; ++i)
    {
        nk_uint encoding_record = cmap + 4 + 8 * (nk_uint)i;
        /* find an encoding we understand: */
        switch(nk_ttUSHORT(data+encoding_record)) {
        case NK_TT_PLATFORM_ID_MICROSOFT:
            switch (nk_ttUSHORT(data+encoding_record+2)) {
            case NK_TT_MS_EID_UNICODE_BMP:
            case NK_TT_MS_EID_UNICODE_FULL:
                /* MS/Unicode */
                info->index_map = (int)(cmap + nk_ttULONG(data+encoding_record+4));
                break;
            default: break;
            } break;
        case NK_TT_PLATFORM_ID_UNICODE:
            /* Mac/iOS has these */
            /* all the encodingIDs are unicode, so we don't bother to check it */
            info->index_map = (int)(cmap + nk_ttULONG(data+encoding_record+4));
            break;
        default: break;
        }
    }
    if (info->index_map == 0)
        return 0;
    info->indexToLocFormat = nk_ttUSHORT(data+info->head + 50);
    return 1;
}

NK_INTERN int
nk_tt_FindGlyphIndex(const struct nk_tt_fontinfo *info, int unicode_codepoint)
{
    const nk_byte *data = info->data;
    nk_uint index_map = (nk_uint)info->index_map;

    nk_ushort format = nk_ttUSHORT(data + index_map + 0);
    if (format == 0) { /* apple byte encoding */
        nk_int bytes = nk_ttUSHORT(data + index_map + 2);
        if (unicode_codepoint < bytes-6)
            return nk_ttBYTE(data + index_map + 6 + unicode_codepoint);
        return 0;
    } else if (format == 6) {
        nk_uint first = nk_ttUSHORT(data + index_map + 6);
        nk_uint count = nk_ttUSHORT(data + index_map + 8);
        if ((nk_uint) unicode_codepoint >= first && (nk_uint) unicode_codepoint < first+count)
            return nk_ttUSHORT(data + index_map + 10 + (unicode_codepoint - (int)first)*2);
        return 0;
    } else if (format == 2) {
        NK_ASSERT(0); /* @TODO: high-byte mapping for japanese/chinese/korean */
        return 0;
    } else if (format == 4) { /* standard mapping for windows fonts: binary search collection of ranges */
        nk_ushort segcount = nk_ttUSHORT(data+index_map+6) >> 1;
        nk_ushort searchRange = nk_ttUSHORT(data+index_map+8) >> 1;
        nk_ushort entrySelector = nk_ttUSHORT(data+index_map+10);
        nk_ushort rangeShift = nk_ttUSHORT(data+index_map+12) >> 1;

        /* do a binary search of the segments */
        nk_uint endCount = index_map + 14;
        nk_uint search = endCount;

        if (unicode_codepoint > 0xffff)
            return 0;

        /* they lie from endCount .. endCount + segCount */
        /* but searchRange is the nearest power of two, so... */
        if (unicode_codepoint >= nk_ttUSHORT(data + search + rangeShift*2))
            search += (nk_uint)(rangeShift*2);

        /* now decrement to bias correctly to find smallest */
        search -= 2;
        while (entrySelector) {
            nk_ushort end;
            searchRange >>= 1;
            end = nk_ttUSHORT(data + search + searchRange*2);
            if (unicode_codepoint > end)
                search += (nk_uint)(searchRange*2);
            --entrySelector;
        }
        search += 2;

      {
         nk_ushort offset, start;
         nk_ushort item = (nk_ushort) ((search - endCount) >> 1);

         NK_ASSERT(unicode_codepoint <= nk_ttUSHORT(data + endCount + 2*item));
         start = nk_ttUSHORT(data + index_map + 14 + segcount*2 + 2 + 2*item);
         if (unicode_codepoint < start)
            return 0;

         offset = nk_ttUSHORT(data + index_map + 14 + segcount*6 + 2 + 2*item);
         if (offset == 0)
            return (nk_ushort) (unicode_codepoint + nk_ttSHORT(data + index_map + 14 + segcount*4 + 2 + 2*item));

         return nk_ttUSHORT(data + offset + (unicode_codepoint-start)*2 + index_map + 14 + segcount*6 + 2 + 2*item);
      }
   } else if (format == 12 || format == 13) {
        nk_uint ngroups = nk_ttULONG(data+index_map+12);
        nk_int low,high;
        low = 0; high = (nk_int)ngroups;
        /* Binary search the right group. */
        while (low < high) {
            nk_int mid = low + ((high-low) >> 1); /* rounds down, so low <= mid < high */
            nk_uint start_char = nk_ttULONG(data+index_map+16+mid*12);
            nk_uint end_char = nk_ttULONG(data+index_map+16+mid*12+4);
            if ((nk_uint) unicode_codepoint < start_char)
                high = mid;
            else if ((nk_uint) unicode_codepoint > end_char)
                low = mid+1;
            else {
                nk_uint start_glyph = nk_ttULONG(data+index_map+16+mid*12+8);
                if (format == 12)
                    return (int)start_glyph + (int)unicode_codepoint - (int)start_char;
                else /* format == 13 */
                    return (int)start_glyph;
            }
        }
        return 0; /* not found */
    }
    /* @TODO */
    NK_ASSERT(0);
    return 0;
}

NK_INTERN void
nk_tt_setvertex(struct nk_tt_vertex *v, nk_byte type, nk_int x, nk_int y, nk_int cx, nk_int cy)
{
    v->type = type;
    v->x = (nk_short) x;
    v->y = (nk_short) y;
    v->cx = (nk_short) cx;
    v->cy = (nk_short) cy;
}

NK_INTERN int
nk_tt__GetGlyfOffset(const struct nk_tt_fontinfo *info, int glyph_index)
{
    int g1,g2;
    if (glyph_index >= info->numGlyphs) return -1; /* glyph index out of range */
    if (info->indexToLocFormat >= 2)    return -1; /* unknown index->glyph map format */

    if (info->indexToLocFormat == 0) {
        g1 = info->glyf + nk_ttUSHORT(info->data + info->loca + glyph_index * 2) * 2;
        g2 = info->glyf + nk_ttUSHORT(info->data + info->loca + glyph_index * 2 + 2) * 2;
    } else {
        g1 = info->glyf + (int)nk_ttULONG (info->data + info->loca + glyph_index * 4);
        g2 = info->glyf + (int)nk_ttULONG (info->data + info->loca + glyph_index * 4 + 4);
    }
    return g1==g2 ? -1 : g1; /* if length is 0, return -1 */
}

NK_INTERN int
nk_tt_GetGlyphBox(const struct nk_tt_fontinfo *info, int glyph_index,
    int *x0, int *y0, int *x1, int *y1)
{
    int g = nk_tt__GetGlyfOffset(info, glyph_index);
    if (g < 0) return 0;

    if (x0) *x0 = nk_ttSHORT(info->data + g + 2);
    if (y0) *y0 = nk_ttSHORT(info->data + g + 4);
    if (x1) *x1 = nk_ttSHORT(info->data + g + 6);
    if (y1) *y1 = nk_ttSHORT(info->data + g + 8);
    return 1;
}

NK_INTERN int
stbtt__close_shape(struct nk_tt_vertex *vertices, int num_vertices, int was_off,
    int start_off, nk_int sx, nk_int sy, nk_int scx, nk_int scy, nk_int cx, nk_int cy)
{
   if (start_off) {
      if (was_off)
         nk_tt_setvertex(&vertices[num_vertices++], NK_TT_vcurve, (cx+scx)>>1, (cy+scy)>>1, cx,cy);
      nk_tt_setvertex(&vertices[num_vertices++], NK_TT_vcurve, sx,sy,scx,scy);
   } else {
      if (was_off)
         nk_tt_setvertex(&vertices[num_vertices++], NK_TT_vcurve,sx,sy,cx,cy);
      else
         nk_tt_setvertex(&vertices[num_vertices++], NK_TT_vline,sx,sy,0,0);
   }
   return num_vertices;
}

NK_INTERN int
nk_tt_GetGlyphShape(const struct nk_tt_fontinfo *info, struct nk_allocator *alloc,
    int glyph_index, struct nk_tt_vertex **pvertices)
{
    nk_short numberOfContours;
    const nk_byte *endPtsOfContours;
    const nk_byte *data = info->data;
    struct nk_tt_vertex *vertices=0;
    int num_vertices=0;
    int g = nk_tt__GetGlyfOffset(info, glyph_index);
    *pvertices = 0;

    if (g < 0) return 0;
    numberOfContours = nk_ttSHORT(data + g);
    if (numberOfContours > 0) {
        nk_byte flags=0,flagcount;
        nk_int ins, i,j=0,m,n, next_move, was_off=0, off, start_off=0;
        nk_int x,y,cx,cy,sx,sy, scx,scy;
        const nk_byte *points;
        endPtsOfContours = (data + g + 10);
        ins = nk_ttUSHORT(data + g + 10 + numberOfContours * 2);
        points = data + g + 10 + numberOfContours * 2 + 2 + ins;

        n = 1+nk_ttUSHORT(endPtsOfContours + numberOfContours*2-2);
        m = n + 2*numberOfContours;  /* a loose bound on how many vertices we might need */
        vertices = (struct nk_tt_vertex *)alloc->alloc(alloc->userdata, 0, (nk_size)m * sizeof(vertices[0]));
        if (vertices == 0)
            return 0;

        next_move = 0;
        flagcount=0;

        /* in first pass, we load uninterpreted data into the allocated array */
        /* above, shifted to the end of the array so we won't overwrite it when */
        /* we create our final data starting from the front */
        off = m - n; /* starting offset for uninterpreted data, regardless of how m ends up being calculated */

        /* first load flags */
        for (i=0; i < n; ++i) {
            if (flagcount == 0) {
                flags = *points++;
                if (flags & 8)
                    flagcount = *points++;
            } else --flagcount;
            vertices[off+i].type = flags;
        }

        /* now load x coordinates */
        x=0;
        for (i=0; i < n; ++i) {
            flags = vertices[off+i].type;
            if (flags & 2) {
                nk_short dx = *points++;
                x += (flags & 16) ? dx : -dx; /* ??? */
            } else {
                if (!(flags & 16)) {
                    x = x + (nk_short) (points[0]*256 + points[1]);
                    points += 2;
                }
            }
            vertices[off+i].x = (nk_short) x;
        }

        /* now load y coordinates */
        y=0;
        for (i=0; i < n; ++i) {
            flags = vertices[off+i].type;
            if (flags & 4) {
                nk_short dy = *points++;
                y += (flags & 32) ? dy : -dy; /* ??? */
            } else {
                if (!(flags & 32)) {
                    y = y + (nk_short) (points[0]*256 + points[1]);
                    points += 2;
                }
            }
            vertices[off+i].y = (nk_short) y;
        }

        /* now convert them to our format */
        num_vertices=0;
        sx = sy = cx = cy = scx = scy = 0;
        for (i=0; i < n; ++i)
        {
            flags = vertices[off+i].type;
            x     = (nk_short) vertices[off+i].x;
            y     = (nk_short) vertices[off+i].y;

            if (next_move == i) {
                if (i != 0)
                    num_vertices = stbtt__close_shape(vertices, num_vertices, was_off, start_off, sx,sy,scx,scy,cx,cy);

                /* now start the new one                */
                start_off = !(flags & 1);
                if (start_off) {
                    /* if we start off with an off-curve point, then when we need to find a point on the curve */
                    /* where we can start, and we need to save some state for when we wraparound. */
                    scx = x;
                    scy = y;
                    if (!(vertices[off+i+1].type & 1)) {
                        /* next point is also a curve point, so interpolate an on-point curve */
                        sx = (x + (nk_int) vertices[off+i+1].x) >> 1;
                        sy = (y + (nk_int) vertices[off+i+1].y) >> 1;
                    } else {
                        /* otherwise just use the next point as our start point */
                        sx = (nk_int) vertices[off+i+1].x;
                        sy = (nk_int) vertices[off+i+1].y;
                        ++i; /* we're using point i+1 as the starting point, so skip it */
                    }
                } else {
                    sx = x;
                    sy = y;
                }
                nk_tt_setvertex(&vertices[num_vertices++], NK_TT_vmove,sx,sy,0,0);
                was_off = 0;
                next_move = 1 + nk_ttUSHORT(endPtsOfContours+j*2);
                ++j;
            } else {
                if (!(flags & 1))
                { /* if it's a curve */
                    if (was_off) /* two off-curve control points in a row means interpolate an on-curve midpoint */
                        nk_tt_setvertex(&vertices[num_vertices++], NK_TT_vcurve, (cx+x)>>1, (cy+y)>>1, cx, cy);
                    cx = x;
                    cy = y;
                    was_off = 1;
                } else {
                    if (was_off)
                        nk_tt_setvertex(&vertices[num_vertices++], NK_TT_vcurve, x,y, cx, cy);
                    else nk_tt_setvertex(&vertices[num_vertices++], NK_TT_vline, x,y,0,0);
                    was_off = 0;
                }
            }
        }
        num_vertices = stbtt__close_shape(vertices, num_vertices, was_off, start_off, sx,sy,scx,scy,cx,cy);
    } else if (numberOfContours == -1) {
        /* Compound shapes. */
        int more = 1;
        const nk_byte *comp = data + g + 10;
        num_vertices = 0;
        vertices = 0;

        while (more)
        {
            nk_ushort flags, gidx;
            int comp_num_verts = 0, i;
            struct nk_tt_vertex *comp_verts = 0, *tmp = 0;
            float mtx[6] = {1,0,0,1,0,0}, m, n;

            flags = (nk_ushort)nk_ttSHORT(comp); comp+=2;
            gidx = (nk_ushort)nk_ttSHORT(comp); comp+=2;

            if (flags & 2) { /* XY values */
                if (flags & 1) { /* shorts */
                    mtx[4] = nk_ttSHORT(comp); comp+=2;
                    mtx[5] = nk_ttSHORT(comp); comp+=2;
                } else {
                    mtx[4] = nk_ttCHAR(comp); comp+=1;
                    mtx[5] = nk_ttCHAR(comp); comp+=1;
                }
            } else {
                /* @TODO handle matching point */
                NK_ASSERT(0);
            }
            if (flags & (1<<3)) { /* WE_HAVE_A_SCALE */
                mtx[0] = mtx[3] = nk_ttSHORT(comp)/16384.0f; comp+=2;
                mtx[1] = mtx[2] = 0;
            } else if (flags & (1<<6)) { /* WE_HAVE_AN_X_AND_YSCALE */
                mtx[0] = nk_ttSHORT(comp)/16384.0f; comp+=2;
                mtx[1] = mtx[2] = 0;
                mtx[3] = nk_ttSHORT(comp)/16384.0f; comp+=2;
            } else if (flags & (1<<7)) { /* WE_HAVE_A_TWO_BY_TWO */
                mtx[0] = nk_ttSHORT(comp)/16384.0f; comp+=2;
                mtx[1] = nk_ttSHORT(comp)/16384.0f; comp+=2;
                mtx[2] = nk_ttSHORT(comp)/16384.0f; comp+=2;
                mtx[3] = nk_ttSHORT(comp)/16384.0f; comp+=2;
            }

             /* Find transformation scales. */
            m = (float) NK_SQRT(mtx[0]*mtx[0] + mtx[1]*mtx[1]);
            n = (float) NK_SQRT(mtx[2]*mtx[2] + mtx[3]*mtx[3]);

             /* Get indexed glyph. */
            comp_num_verts = nk_tt_GetGlyphShape(info, alloc, gidx, &comp_verts);
            if (comp_num_verts > 0)
            {
                /* Transform vertices. */
                for (i = 0; i < comp_num_verts; ++i) {
                    struct nk_tt_vertex* v = &comp_verts[i];
                    short x,y;
                    x=v->x; y=v->y;
                    v->x = (short)(m * (mtx[0]*x + mtx[2]*y + mtx[4]));
                    v->y = (short)(n * (mtx[1]*x + mtx[3]*y + mtx[5]));
                    x=v->cx; y=v->cy;
                    v->cx = (short)(m * (mtx[0]*x + mtx[2]*y + mtx[4]));
                    v->cy = (short)(n * (mtx[1]*x + mtx[3]*y + mtx[5]));
                }
                /* Append vertices. */
                tmp = (struct nk_tt_vertex*)alloc->alloc(alloc->userdata, 0,
                    (nk_size)(num_vertices+comp_num_verts)*sizeof(struct nk_tt_vertex));
                if (!tmp) {
                    if (vertices) alloc->free(alloc->userdata, vertices);
                    if (comp_verts) alloc->free(alloc->userdata, comp_verts);
                    return 0;
                }
                if (num_vertices > 0) NK_MEMCPY(tmp, vertices, (nk_size)num_vertices*sizeof(struct nk_tt_vertex));
                NK_MEMCPY(tmp+num_vertices, comp_verts, (nk_size)comp_num_verts*sizeof(struct nk_tt_vertex));
                if (vertices) alloc->free(alloc->userdata,vertices);
                vertices = tmp;
                alloc->free(alloc->userdata,comp_verts);
                num_vertices += comp_num_verts;
            }
            /* More components ? */
            more = flags & (1<<5);
        }
    } else if (numberOfContours < 0) {
        /* @TODO other compound variations? */
        NK_ASSERT(0);
    } else {
        /* numberOfCounters == 0, do nothing */
    }
    *pvertices = vertices;
    return num_vertices;
}

NK_INTERN void
nk_tt_GetGlyphHMetrics(const struct nk_tt_fontinfo *info, int glyph_index,
    int *advanceWidth, int *leftSideBearing)
{
    nk_ushort numOfLongHorMetrics = nk_ttUSHORT(info->data+info->hhea + 34);
    if (glyph_index < numOfLongHorMetrics) {
        if (advanceWidth)
            *advanceWidth    = nk_ttSHORT(info->data + info->hmtx + 4*glyph_index);
        if (leftSideBearing)
            *leftSideBearing = nk_ttSHORT(info->data + info->hmtx + 4*glyph_index + 2);
    } else {
        if (advanceWidth)
            *advanceWidth    = nk_ttSHORT(info->data + info->hmtx + 4*(numOfLongHorMetrics-1));
        if (leftSideBearing)
            *leftSideBearing = nk_ttSHORT(info->data + info->hmtx + 4*numOfLongHorMetrics + 2*(glyph_index - numOfLongHorMetrics));
    }
}

NK_INTERN void
nk_tt_GetFontVMetrics(const struct nk_tt_fontinfo *info,
    int *ascent, int *descent, int *lineGap)
{
   if (ascent ) *ascent  = nk_ttSHORT(info->data+info->hhea + 4);
   if (descent) *descent = nk_ttSHORT(info->data+info->hhea + 6);
   if (lineGap) *lineGap = nk_ttSHORT(info->data+info->hhea + 8);
}

NK_INTERN float
nk_tt_ScaleForPixelHeight(const struct nk_tt_fontinfo *info, float height)
{
   int fheight = nk_ttSHORT(info->data + info->hhea + 4) - nk_ttSHORT(info->data + info->hhea + 6);
   return (float) height / (float)fheight;
}

NK_INTERN float
nk_tt_ScaleForMappingEmToPixels(const struct nk_tt_fontinfo *info, float pixels)
{
   int unitsPerEm = nk_ttUSHORT(info->data + info->head + 18);
   return pixels / (float)unitsPerEm;
}

/*-------------------------------------------------------------
 *            antialiasing software rasterizer
 * --------------------------------------------------------------*/
NK_INTERN void
nk_tt_GetGlyphBitmapBoxSubpixel(const struct nk_tt_fontinfo *font,
    int glyph, float scale_x, float scale_y,float shift_x, float shift_y,
    int *ix0, int *iy0, int *ix1, int *iy1)
{
    int x0,y0,x1,y1;
    if (!nk_tt_GetGlyphBox(font, glyph, &x0,&y0,&x1,&y1)) {
        /* e.g. space character */
        if (ix0) *ix0 = 0;
        if (iy0) *iy0 = 0;
        if (ix1) *ix1 = 0;
        if (iy1) *iy1 = 0;
    } else {
        /* move to integral bboxes (treating pixels as little squares, what pixels get touched)? */
        if (ix0) *ix0 = nk_ifloor((float)x0 * scale_x + shift_x);
        if (iy0) *iy0 = nk_ifloor((float)-y1 * scale_y + shift_y);
        if (ix1) *ix1 = nk_iceil ((float)x1 * scale_x + shift_x);
        if (iy1) *iy1 = nk_iceil ((float)-y0 * scale_y + shift_y);
    }
}

NK_INTERN void
nk_tt_GetGlyphBitmapBox(const struct nk_tt_fontinfo *font, int glyph,
    float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1)
{
   nk_tt_GetGlyphBitmapBoxSubpixel(font, glyph, scale_x, scale_y,0.0f,0.0f, ix0, iy0, ix1, iy1);
}

/*-------------------------------------------------------------
 *                          Rasterizer
 * --------------------------------------------------------------*/
NK_INTERN void*
nk_tt__hheap_alloc(struct nk_tt__hheap *hh, nk_size size)
{
    if (hh->first_free) {
        void *p = hh->first_free;
        hh->first_free = * (void **) p;
        return p;
    } else {
        if (hh->num_remaining_in_head_chunk == 0) {
            int count = (size < 32 ? 2000 : size < 128 ? 800 : 100);
            struct nk_tt__hheap_chunk *c = (struct nk_tt__hheap_chunk *)
                hh->alloc.alloc(hh->alloc.userdata, 0,
                sizeof(struct nk_tt__hheap_chunk) + size * (nk_size)count);
            if (c == 0) return 0;
            c->next = hh->head;
            hh->head = c;
            hh->num_remaining_in_head_chunk = count;
        }
        --hh->num_remaining_in_head_chunk;
        return (char *) (hh->head) + size * (nk_size)hh->num_remaining_in_head_chunk;
    }
}

NK_INTERN void
nk_tt__hheap_free(struct nk_tt__hheap *hh, void *p)
{
    *(void **) p = hh->first_free;
    hh->first_free = p;
}

NK_INTERN void
nk_tt__hheap_cleanup(struct nk_tt__hheap *hh)
{
    struct nk_tt__hheap_chunk *c = hh->head;
    while (c) {
        struct nk_tt__hheap_chunk *n = c->next;
        hh->alloc.free(hh->alloc.userdata, c);
        c = n;
    }
}

NK_INTERN struct nk_tt__active_edge*
nk_tt__new_active(struct nk_tt__hheap *hh, struct nk_tt__edge *e,
    int off_x, float start_point)
{
    struct nk_tt__active_edge *z = (struct nk_tt__active_edge *)
        nk_tt__hheap_alloc(hh, sizeof(*z));
    float dxdy = (e->x1 - e->x0) / (e->y1 - e->y0);
    /*STBTT_assert(e->y0 <= start_point); */
    if (!z) return z;
    z->fdx = dxdy;
    z->fdy = (dxdy != 0) ? (1/dxdy): 0;
    z->fx = e->x0 + dxdy * (start_point - e->y0);
    z->fx -= (float)off_x;
    z->direction = e->invert ? 1.0f : -1.0f;
    z->sy = e->y0;
    z->ey = e->y1;
    z->next = 0;
    return z;
}

NK_INTERN void
nk_tt__handle_clipped_edge(float *scanline, int x, struct nk_tt__active_edge *e,
    float x0, float y0, float x1, float y1)
{
    if (y0 == y1) return;
    NK_ASSERT(y0 < y1);
    NK_ASSERT(e->sy <= e->ey);
    if (y0 > e->ey) return;
    if (y1 < e->sy) return;
    if (y0 < e->sy) {
        x0 += (x1-x0) * (e->sy - y0) / (y1-y0);
        y0 = e->sy;
    }
    if (y1 > e->ey) {
        x1 += (x1-x0) * (e->ey - y1) / (y1-y0);
        y1 = e->ey;
    }

    if (x0 == x) NK_ASSERT(x1 <= x+1);
    else if (x0 == x+1) NK_ASSERT(x1 >= x);
    else if (x0 <= x) NK_ASSERT(x1 <= x);
    else if (x0 >= x+1) NK_ASSERT(x1 >= x+1);
    else NK_ASSERT(x1 >= x && x1 <= x+1);

    if (x0 <= x && x1 <= x)
        scanline[x] += e->direction * (y1-y0);
    else if (x0 >= x+1 && x1 >= x+1);
    else {
        NK_ASSERT(x0 >= x && x0 <= x+1 && x1 >= x && x1 <= x+1);
        /* coverage = 1 - average x position */
        scanline[x] += (float)e->direction * (float)(y1-y0) * (1.0f-((x0-(float)x)+(x1-(float)x))/2.0f);
    }
}

NK_INTERN void
nk_tt__fill_active_edges_new(float *scanline, float *scanline_fill, int len,
    struct nk_tt__active_edge *e, float y_top)
{
    float y_bottom = y_top+1;
    while (e)
    {
        /* brute force every pixel */
        /* compute intersection points with top & bottom */
        NK_ASSERT(e->ey >= y_top);
        if (e->fdx == 0) {
            float x0 = e->fx;
            if (x0 < len) {
                if (x0 >= 0) {
                    nk_tt__handle_clipped_edge(scanline,(int) x0,e, x0,y_top, x0,y_bottom);
                    nk_tt__handle_clipped_edge(scanline_fill-1,(int) x0+1,e, x0,y_top, x0,y_bottom);
                } else {
                    nk_tt__handle_clipped_edge(scanline_fill-1,0,e, x0,y_top, x0,y_bottom);
                }
            }
        } else {
            float x0 = e->fx;
            float dx = e->fdx;
            float xb = x0 + dx;
            float x_top, x_bottom;
            float y0,y1;
            float dy = e->fdy;
            NK_ASSERT(e->sy <= y_bottom && e->ey >= y_top);

            /* compute endpoints of line segment clipped to this scanline (if the */
            /* line segment starts on this scanline. x0 is the intersection of the */
            /* line with y_top, but that may be off the line segment. */
            if (e->sy > y_top) {
                x_top = x0 + dx * (e->sy - y_top);
                y0 = e->sy;
            } else {
                x_top = x0;
                y0 = y_top;
            }

            if (e->ey < y_bottom) {
                x_bottom = x0 + dx * (e->ey - y_top);
                y1 = e->ey;
            } else {
                x_bottom = xb;
                y1 = y_bottom;
            }

            if (x_top >= 0 && x_bottom >= 0 && x_top < len && x_bottom < len)
            {
                /* from here on, we don't have to range check x values */
                if ((int) x_top == (int) x_bottom) {
                    float height;
                    /* simple case, only spans one pixel */
                    int x = (int) x_top;
                    height = y1 - y0;
                    NK_ASSERT(x >= 0 && x < len);
                    scanline[x] += e->direction * (1.0f-(((float)x_top - (float)x) + ((float)x_bottom-(float)x))/2.0f)  * (float)height;
                    scanline_fill[x] += e->direction * (float)height; /* everything right of this pixel is filled */
                } else {
                    int x,x1,x2;
                    float y_crossing, step, sign, area;
                    /* covers 2+ pixels */
                    if (x_top > x_bottom)
                    {
                        /* flip scanline vertically; signed area is the same */
                        float t;
                        y0 = y_bottom - (y0 - y_top);
                        y1 = y_bottom - (y1 - y_top);
                        t = y0, y0 = y1, y1 = t;
                        t = x_bottom, x_bottom = x_top, x_top = t;
                        dx = -dx;
                        dy = -dy;
                        t = x0, x0 = xb, xb = t;
                    }

                    x1 = (int) x_top;
                    x2 = (int) x_bottom;
                    /* compute intersection with y axis at x1+1 */
                    y_crossing = ((float)x1+1 - (float)x0) * (float)dy + (float)y_top;

                    sign = e->direction;
                    /* area of the rectangle covered from y0..y_crossing */
                    area = sign * (y_crossing-y0);
                    /* area of the triangle (x_top,y0), (x+1,y0), (x+1,y_crossing) */
                    scanline[x1] += area * (1.0f-((float)((float)x_top - (float)x1)+(float)(x1+1-x1))/2.0f);

                    step = sign * dy;
                    for (x = x1+1; x < x2; ++x) {
                        scanline[x] += area + step/2;
                        area += step;
                    }
                    y_crossing += (float)dy * (float)(x2 - (x1+1));

                    scanline[x2] += area + sign * (1.0f-((float)(x2-x2)+((float)x_bottom-(float)x2))/2.0f) * (y1-y_crossing);
                    scanline_fill[x2] += sign * (y1-y0);
                }
            }
            else
            {
                /* if edge goes outside of box we're drawing, we require */
                /* clipping logic. since this does not match the intended use */
                /* of this library, we use a different, very slow brute */
                /* force implementation */
                int x;
                for (x=0; x < len; ++x)
                {
                    /* cases: */
                    /* */
                    /* there can be up to two intersections with the pixel. any intersection */
                    /* with left or right edges can be handled by splitting into two (or three) */
                    /* regions. intersections with top & bottom do not necessitate case-wise logic. */
                    /* */
                    /* the old way of doing this found the intersections with the left & right edges, */
                    /* then used some simple logic to produce up to three segments in sorted order */
                    /* from top-to-bottom. however, this had a problem: if an x edge was epsilon */
                    /* across the x border, then the corresponding y position might not be distinct */
                    /* from the other y segment, and it might ignored as an empty segment. to avoid */
                    /* that, we need to explicitly produce segments based on x positions. */

                    /* rename variables to clear pairs */
                    float ya = y_top;
                    float x1 = (float) (x);
                    float x2 = (float) (x+1);
                    float x3 = xb;
                    float y3 = y_bottom;
                    float yb,y2;

                    yb = ((float)x - x0) / dx + y_top;
                    y2 = ((float)x+1 - x0) / dx + y_top;

                    if (x0 < x1 && x3 > x2) {         /* three segments descending down-right */
                        nk_tt__handle_clipped_edge(scanline,x,e, x0,ya, x1,yb);
                        nk_tt__handle_clipped_edge(scanline,x,e, x1,yb, x2,y2);
                        nk_tt__handle_clipped_edge(scanline,x,e, x2,y2, x3,y3);
                    } else if (x3 < x1 && x0 > x2) {  /* three segments descending down-left */
                        nk_tt__handle_clipped_edge(scanline,x,e, x0,ya, x2,y2);
                        nk_tt__handle_clipped_edge(scanline,x,e, x2,y2, x1,yb);
                        nk_tt__handle_clipped_edge(scanline,x,e, x1,yb, x3,y3);
                    } else if (x0 < x1 && x3 > x1) {  /* two segments across x, down-right */
                        nk_tt__handle_clipped_edge(scanline,x,e, x0,ya, x1,yb);
                        nk_tt__handle_clipped_edge(scanline,x,e, x1,yb, x3,y3);
                    } else if (x3 < x1 && x0 > x1) {  /* two segments across x, down-left */
                        nk_tt__handle_clipped_edge(scanline,x,e, x0,ya, x1,yb);
                        nk_tt__handle_clipped_edge(scanline,x,e, x1,yb, x3,y3);
                    } else if (x0 < x2 && x3 > x2) {  /* two segments across x+1, down-right */
                        nk_tt__handle_clipped_edge(scanline,x,e, x0,ya, x2,y2);
                        nk_tt__handle_clipped_edge(scanline,x,e, x2,y2, x3,y3);
                    } else if (x3 < x2 && x0 > x2) {  /* two segments across x+1, down-left */
                        nk_tt__handle_clipped_edge(scanline,x,e, x0,ya, x2,y2);
                        nk_tt__handle_clipped_edge(scanline,x,e, x2,y2, x3,y3);
                    } else {  /* one segment */
                        nk_tt__handle_clipped_edge(scanline,x,e, x0,ya, x3,y3);
                    }
                }
            }
        }
        e = e->next;
    }
}

/* directly AA rasterize edges w/o supersampling */
NK_INTERN void
nk_tt__rasterize_sorted_edges(struct nk_tt__bitmap *result, struct nk_tt__edge *e,
    int n, int vsubsample, int off_x, int off_y, struct nk_allocator *alloc)
{
    struct nk_tt__hheap hh;
    struct nk_tt__active_edge *active = 0;
    int y,j=0, i;
    float scanline_data[129], *scanline, *scanline2;

    NK_UNUSED(vsubsample);
    nk_zero_struct(hh);
    hh.alloc = *alloc;

    if (result->w > 64)
        scanline = (float *) alloc->alloc(alloc->userdata,0, (nk_size)(result->w*2+1) * sizeof(float));
    else scanline = scanline_data;

    scanline2 = scanline + result->w;
    y = off_y;
    e[n].y0 = (float) (off_y + result->h) + 1;

    while (j < result->h)
    {
        /* find center of pixel for this scanline */
        float scan_y_top    = (float)y + 0.0f;
        float scan_y_bottom = (float)y + 1.0f;
        struct nk_tt__active_edge **step = &active;

        NK_MEMSET(scanline , 0, (nk_size)result->w*sizeof(scanline[0]));
        NK_MEMSET(scanline2, 0, (nk_size)(result->w+1)*sizeof(scanline[0]));

        /* update all active edges; */
        /* remove all active edges that terminate before the top of this scanline */
        while (*step) {
            struct nk_tt__active_edge * z = *step;
            if (z->ey <= scan_y_top) {
                *step = z->next; /* delete from list */
                NK_ASSERT(z->direction);
                z->direction = 0;
                nk_tt__hheap_free(&hh, z);
            } else {
                step = &((*step)->next); /* advance through list */
            }
        }

        /* insert all edges that start before the bottom of this scanline */
        while (e->y0 <= scan_y_bottom) {
            if (e->y0 != e->y1) {
                struct nk_tt__active_edge *z = nk_tt__new_active(&hh, e, off_x, scan_y_top);
                if (z != 0) {
                    NK_ASSERT(z->ey >= scan_y_top);
                    /* insert at front */
                    z->next = active;
                    active = z;
                }
            }
            ++e;
        }

        /* now process all active edges */
        if (active)
            nk_tt__fill_active_edges_new(scanline, scanline2+1, result->w, active, scan_y_top);

        {
            float sum = 0;
            for (i=0; i < result->w; ++i) {
                float k;
                int m;
                sum += scanline2[i];
                k = scanline[i] + sum;
                k = (float) NK_ABS(k) * 255.0f + 0.5f;
                m = (int) k;
                if (m > 255) m = 255;
                result->pixels[j*result->stride + i] = (unsigned char) m;
            }
        }
        /* advance all the edges */
        step = &active;
        while (*step) {
            struct nk_tt__active_edge *z = *step;
            z->fx += z->fdx; /* advance to position for current scanline */
            step = &((*step)->next); /* advance through list */
        }
        ++y;
        ++j;
    }
    nk_tt__hheap_cleanup(&hh);
    if (scanline != scanline_data)
        alloc->free(alloc->userdata, scanline);
}

#define NK_TT__COMPARE(a,b)  ((a)->y0 < (b)->y0)
NK_INTERN void
nk_tt__sort_edges_ins_sort(struct nk_tt__edge *p, int n)
{
    int i,j;
    for (i=1; i < n; ++i) {
        struct nk_tt__edge t = p[i], *a = &t;
        j = i;
        while (j > 0) {
            struct nk_tt__edge *b = &p[j-1];
            int c = NK_TT__COMPARE(a,b);
            if (!c) break;
            p[j] = p[j-1];
            --j;
        }
        if (i != j)
            p[j] = t;
    }
}

NK_INTERN void
nk_tt__sort_edges_quicksort(struct nk_tt__edge *p, int n)
{
    /* threshold for transitioning to insertion sort */
    while (n > 12) {
        struct nk_tt__edge t;
        int c01,c12,c,m,i,j;

        /* compute median of three */
        m = n >> 1;
        c01 = NK_TT__COMPARE(&p[0],&p[m]);
        c12 = NK_TT__COMPARE(&p[m],&p[n-1]);

        /* if 0 >= mid >= end, or 0 < mid < end, then use mid */
        if (c01 != c12) {
            /* otherwise, we'll need to swap something else to middle */
            int z;
            c = NK_TT__COMPARE(&p[0],&p[n-1]);
            /* 0>mid && mid<n:  0>n => n; 0<n => 0 */
            /* 0<mid && mid>n:  0>n => 0; 0<n => n */
            z = (c == c12) ? 0 : n-1;
            t = p[z];
            p[z] = p[m];
            p[m] = t;
        }

        /* now p[m] is the median-of-three */
        /* swap it to the beginning so it won't move around */
        t = p[0];
        p[0] = p[m];
        p[m] = t;

        /* partition loop */
        i=1;
        j=n-1;
        for(;;) {
            /* handling of equality is crucial here */
            /* for sentinels & efficiency with duplicates */
            for (;;++i) {
                if (!NK_TT__COMPARE(&p[i], &p[0])) break;
            }
            for (;;--j) {
                if (!NK_TT__COMPARE(&p[0], &p[j])) break;
            }

            /* make sure we haven't crossed */
             if (i >= j) break;
             t = p[i];
             p[i] = p[j];
             p[j] = t;

            ++i;
            --j;

        }

        /* recurse on smaller side, iterate on larger */
        if (j < (n-i)) {
            nk_tt__sort_edges_quicksort(p,j);
            p = p+i;
            n = n-i;
        } else {
            nk_tt__sort_edges_quicksort(p+i, n-i);
            n = j;
        }
    }
}

NK_INTERN void
nk_tt__sort_edges(struct nk_tt__edge *p, int n)
{
   nk_tt__sort_edges_quicksort(p, n);
   nk_tt__sort_edges_ins_sort(p, n);
}

NK_INTERN void
nk_tt__rasterize(struct nk_tt__bitmap *result, struct nk_tt__point *pts,
    int *wcount, int windings, float scale_x, float scale_y,
    float shift_x, float shift_y, int off_x, int off_y, int invert,
    struct nk_allocator *alloc)
{
    float y_scale_inv = invert ? -scale_y : scale_y;
    struct nk_tt__edge *e;
    int n,i,j,k,m;
    int vsubsample = 1;
    /* vsubsample should divide 255 evenly; otherwise we won't reach full opacity */

    /* now we have to blow out the windings into explicit edge lists */
    n = 0;
    for (i=0; i < windings; ++i)
        n += wcount[i];

    e = (struct nk_tt__edge*)
       alloc->alloc(alloc->userdata, 0,(sizeof(*e) * (nk_size)(n+1)));
    if (e == 0) return;
    n = 0;

    m=0;
    for (i=0; i < windings; ++i)
    {
        struct nk_tt__point *p = pts + m;
        m += wcount[i];
        j = wcount[i]-1;
        for (k=0; k < wcount[i]; j=k++) {
            int a=k,b=j;
            /* skip the edge if horizontal */
            if (p[j].y == p[k].y)
                continue;

            /* add edge from j to k to the list */
            e[n].invert = 0;
            if (invert ? p[j].y > p[k].y : p[j].y < p[k].y) {
                e[n].invert = 1;
                a=j,b=k;
            }
            e[n].x0 = p[a].x * scale_x + shift_x;
            e[n].y0 = (p[a].y * y_scale_inv + shift_y) * (float)vsubsample;
            e[n].x1 = p[b].x * scale_x + shift_x;
            e[n].y1 = (p[b].y * y_scale_inv + shift_y) * (float)vsubsample;
            ++n;
        }
    }

    /* now sort the edges by their highest point (should snap to integer, and then by x) */
    /*STBTT_sort(e, n, sizeof(e[0]), stbtt__edge_compare); */
    nk_tt__sort_edges(e, n);
    /* now, traverse the scanlines and find the intersections on each scanline, use xor winding rule */
    nk_tt__rasterize_sorted_edges(result, e, n, vsubsample, off_x, off_y, alloc);
    alloc->free(alloc->userdata, e);
}

NK_INTERN void
nk_tt__add_point(struct nk_tt__point *points, int n, float x, float y)
{
    if (!points) return; /* during first pass, it's unallocated */
    points[n].x = x;
    points[n].y = y;
}

NK_INTERN int
nk_tt__tesselate_curve(struct nk_tt__point *points, int *num_points,
    float x0, float y0, float x1, float y1, float x2, float y2,
    float objspace_flatness_squared, int n)
{
    /* tesselate until threshold p is happy...
     * @TODO warped to compensate for non-linear stretching */
    /* midpoint */
    float mx = (x0 + 2*x1 + x2)/4;
    float my = (y0 + 2*y1 + y2)/4;
    /* versus directly drawn line */
    float dx = (x0+x2)/2 - mx;
    float dy = (y0+y2)/2 - my;
    if (n > 16) /* 65536 segments on one curve better be enough! */
        return 1;

    /* half-pixel error allowed... need to be smaller if AA */
    if (dx*dx+dy*dy > objspace_flatness_squared) {
        nk_tt__tesselate_curve(points, num_points, x0,y0,
            (x0+x1)/2.0f,(y0+y1)/2.0f, mx,my, objspace_flatness_squared,n+1);
        nk_tt__tesselate_curve(points, num_points, mx,my,
            (x1+x2)/2.0f,(y1+y2)/2.0f, x2,y2, objspace_flatness_squared,n+1);
    } else {
        nk_tt__add_point(points, *num_points,x2,y2);
        *num_points = *num_points+1;
    }
    return 1;
}

/* returns number of contours */
NK_INTERN struct nk_tt__point*
nk_tt_FlattenCurves(struct nk_tt_vertex *vertices, int num_verts,
    float objspace_flatness, int **contour_lengths, int *num_contours,
    struct nk_allocator *alloc)
{
    struct nk_tt__point *points=0;
    int num_points=0;
    float objspace_flatness_squared = objspace_flatness * objspace_flatness;
    int i;
    int n=0;
    int start=0;
    int pass;

    /* count how many "moves" there are to get the contour count */
    for (i=0; i < num_verts; ++i)
        if (vertices[i].type == NK_TT_vmove) ++n;

    *num_contours = n;
    if (n == 0) return 0;

    *contour_lengths = (int *)
        alloc->alloc(alloc->userdata,0, (sizeof(**contour_lengths) * (nk_size)n));
    if (*contour_lengths == 0) {
        *num_contours = 0;
        return 0;
    }

    /* make two passes through the points so we don't need to realloc */
    for (pass=0; pass < 2; ++pass)
    {
        float x=0,y=0;
        if (pass == 1) {
            points = (struct nk_tt__point *)
                alloc->alloc(alloc->userdata,0, (nk_size)num_points * sizeof(points[0]));
            if (points == 0) goto error;
        }
        num_points = 0;
        n= -1;

        for (i=0; i < num_verts; ++i)
        {
            switch (vertices[i].type) {
            case NK_TT_vmove:
                /* start the next contour */
                if (n >= 0)
                (*contour_lengths)[n] = num_points - start;
                ++n;
                start = num_points;

                x = vertices[i].x, y = vertices[i].y;
                nk_tt__add_point(points, num_points++, x,y);
                break;
            case NK_TT_vline:
               x = vertices[i].x, y = vertices[i].y;
               nk_tt__add_point(points, num_points++, x, y);
               break;
            case NK_TT_vcurve:
               nk_tt__tesselate_curve(points, &num_points, x,y,
                                        vertices[i].cx, vertices[i].cy,
                                        vertices[i].x,  vertices[i].y,
                                        objspace_flatness_squared, 0);
               x = vertices[i].x, y = vertices[i].y;
               break;
            default: break;
         }
      }
      (*contour_lengths)[n] = num_points - start;
   }
   return points;

error:
   alloc->free(alloc->userdata, points);
   alloc->free(alloc->userdata, *contour_lengths);
   *contour_lengths = 0;
   *num_contours = 0;
   return 0;
}

NK_INTERN void
nk_tt_Rasterize(struct nk_tt__bitmap *result, float flatness_in_pixels,
    struct nk_tt_vertex *vertices, int num_verts,
    float scale_x, float scale_y, float shift_x, float shift_y,
    int x_off, int y_off, int invert, struct nk_allocator *alloc)
{
    float scale = scale_x > scale_y ? scale_y : scale_x;
    int winding_count, *winding_lengths;
    struct nk_tt__point *windings = nk_tt_FlattenCurves(vertices, num_verts,
        flatness_in_pixels / scale, &winding_lengths, &winding_count, alloc);

    NK_ASSERT(alloc);
    if (windings) {
        nk_tt__rasterize(result, windings, winding_lengths, winding_count,
            scale_x, scale_y, shift_x, shift_y, x_off, y_off, invert, alloc);
        alloc->free(alloc->userdata, winding_lengths);
        alloc->free(alloc->userdata, windings);
    }
}

NK_INTERN void
nk_tt_MakeGlyphBitmapSubpixel(const struct nk_tt_fontinfo *info, unsigned char *output,
    int out_w, int out_h, int out_stride, float scale_x, float scale_y,
    float shift_x, float shift_y, int glyph, struct nk_allocator *alloc)
{
    int ix0,iy0;
    struct nk_tt_vertex *vertices;
    int num_verts = nk_tt_GetGlyphShape(info, alloc, glyph, &vertices);
    struct nk_tt__bitmap gbm;

    nk_tt_GetGlyphBitmapBoxSubpixel(info, glyph, scale_x, scale_y, shift_x,
        shift_y, &ix0,&iy0,0,0);
    gbm.pixels = output;
    gbm.w = out_w;
    gbm.h = out_h;
    gbm.stride = out_stride;

    if (gbm.w && gbm.h)
        nk_tt_Rasterize(&gbm, 0.35f, vertices, num_verts, scale_x, scale_y,
            shift_x, shift_y, ix0,iy0, 1, alloc);
    alloc->free(alloc->userdata, vertices);
}

/*-------------------------------------------------------------
 *                          Bitmap baking
 * --------------------------------------------------------------*/
NK_INTERN int
nk_tt_PackBegin(struct nk_tt_pack_context *spc, unsigned char *pixels,
    int pw, int ph, int stride_in_bytes, int padding, struct nk_allocator *alloc)
{
    int num_nodes = pw - padding;
    struct nk_rp_context *context = (struct nk_rp_context *)
        alloc->alloc(alloc->userdata,0, sizeof(*context));
    struct nk_rp_node *nodes = (struct nk_rp_node*)
        alloc->alloc(alloc->userdata,0, (sizeof(*nodes  ) * (nk_size)num_nodes));

    if (context == 0 || nodes == 0) {
        if (context != 0) alloc->free(alloc->userdata, context);
        if (nodes   != 0) alloc->free(alloc->userdata, nodes);
        return 0;
    }

    spc->width = pw;
    spc->height = ph;
    spc->pixels = pixels;
    spc->pack_info = context;
    spc->nodes = nodes;
    spc->padding = padding;
    spc->stride_in_bytes = (stride_in_bytes != 0) ? stride_in_bytes : pw;
    spc->h_oversample = 1;
    spc->v_oversample = 1;

    nk_rp_init_target(context, pw-padding, ph-padding, nodes, num_nodes);
    if (pixels)
        NK_MEMSET(pixels, 0, (nk_size)(pw*ph)); /* background of 0 around pixels */
    return 1;
}

NK_INTERN void
nk_tt_PackEnd(struct nk_tt_pack_context *spc, struct nk_allocator *alloc)
{
    alloc->free(alloc->userdata, spc->nodes);
    alloc->free(alloc->userdata, spc->pack_info);
}

NK_INTERN void
nk_tt_PackSetOversampling(struct nk_tt_pack_context *spc,
    unsigned int h_oversample, unsigned int v_oversample)
{
   NK_ASSERT(h_oversample <= NK_TT_MAX_OVERSAMPLE);
   NK_ASSERT(v_oversample <= NK_TT_MAX_OVERSAMPLE);
   if (h_oversample <= NK_TT_MAX_OVERSAMPLE)
      spc->h_oversample = h_oversample;
   if (v_oversample <= NK_TT_MAX_OVERSAMPLE)
      spc->v_oversample = v_oversample;
}

NK_INTERN void
nk_tt__h_prefilter(unsigned char *pixels, int w, int h, int stride_in_bytes,
    int kernel_width)
{
    unsigned char buffer[NK_TT_MAX_OVERSAMPLE];
    int safe_w = w - kernel_width;
    int j;

    for (j=0; j < h; ++j)
    {
        int i;
        unsigned int total;
        NK_MEMSET(buffer, 0, (nk_size)kernel_width);

        total = 0;

        /* make kernel_width a constant in common cases so compiler can optimize out the divide */
        switch (kernel_width) {
        case 2:
            for (i=0; i <= safe_w; ++i) {
                total += (unsigned int)(pixels[i] - buffer[i & NK_TT__OVER_MASK]);
                buffer[(i+kernel_width) & NK_TT__OVER_MASK] = pixels[i];
                pixels[i] = (unsigned char) (total / 2);
            }
            break;
        case 3:
            for (i=0; i <= safe_w; ++i) {
                total += (unsigned int)(pixels[i] - buffer[i & NK_TT__OVER_MASK]);
                buffer[(i+kernel_width) & NK_TT__OVER_MASK] = pixels[i];
                pixels[i] = (unsigned char) (total / 3);
            }
            break;
        case 4:
            for (i=0; i <= safe_w; ++i) {
                total += (unsigned int)pixels[i] - buffer[i & NK_TT__OVER_MASK];
                buffer[(i+kernel_width) & NK_TT__OVER_MASK] = pixels[i];
                pixels[i] = (unsigned char) (total / 4);
            }
            break;
        case 5:
            for (i=0; i <= safe_w; ++i) {
                total += (unsigned int)(pixels[i] - buffer[i & NK_TT__OVER_MASK]);
                buffer[(i+kernel_width) & NK_TT__OVER_MASK] = pixels[i];
                pixels[i] = (unsigned char) (total / 5);
            }
            break;
        default:
            for (i=0; i <= safe_w; ++i) {
                total += (unsigned int)(pixels[i] - buffer[i & NK_TT__OVER_MASK]);
                buffer[(i+kernel_width) & NK_TT__OVER_MASK] = pixels[i];
                pixels[i] = (unsigned char) (total / (unsigned int)kernel_width);
            }
            break;
        }

        for (; i < w; ++i) {
            NK_ASSERT(pixels[i] == 0);
            total -= (unsigned int)(buffer[i & NK_TT__OVER_MASK]);
            pixels[i] = (unsigned char) (total / (unsigned int)kernel_width);
        }
        pixels += stride_in_bytes;
    }
}

NK_INTERN void
nk_tt__v_prefilter(unsigned char *pixels, int w, int h, int stride_in_bytes,
    int kernel_width)
{
    unsigned char buffer[NK_TT_MAX_OVERSAMPLE];
    int safe_h = h - kernel_width;
    int j;

    for (j=0; j < w; ++j)
    {
        int i;
        unsigned int total;
        NK_MEMSET(buffer, 0, (nk_size)kernel_width);

        total = 0;

        /* make kernel_width a constant in common cases so compiler can optimize out the divide */
        switch (kernel_width) {
        case 2:
            for (i=0; i <= safe_h; ++i) {
                total += (unsigned int)(pixels[i*stride_in_bytes] - buffer[i & NK_TT__OVER_MASK]);
                buffer[(i+kernel_width) & NK_TT__OVER_MASK] = pixels[i*stride_in_bytes];
                pixels[i*stride_in_bytes] = (unsigned char) (total / 2);
            }
            break;
         case 3:
            for (i=0; i <= safe_h; ++i) {
                total += (unsigned int)(pixels[i*stride_in_bytes] - buffer[i & NK_TT__OVER_MASK]);
                buffer[(i+kernel_width) & NK_TT__OVER_MASK] = pixels[i*stride_in_bytes];
                pixels[i*stride_in_bytes] = (unsigned char) (total / 3);
            }
            break;
         case 4:
            for (i=0; i <= safe_h; ++i) {
                total += (unsigned int)(pixels[i*stride_in_bytes] - buffer[i & NK_TT__OVER_MASK]);
                buffer[(i+kernel_width) & NK_TT__OVER_MASK] = pixels[i*stride_in_bytes];
                pixels[i*stride_in_bytes] = (unsigned char) (total / 4);
            }
            break;
         case 5:
            for (i=0; i <= safe_h; ++i) {
                total += (unsigned int)(pixels[i*stride_in_bytes] - buffer[i & NK_TT__OVER_MASK]);
                buffer[(i+kernel_width) & NK_TT__OVER_MASK] = pixels[i*stride_in_bytes];
                pixels[i*stride_in_bytes] = (unsigned char) (total / 5);
            }
            break;
         default:
            for (i=0; i <= safe_h; ++i) {
                total += (unsigned int)(pixels[i*stride_in_bytes] - buffer[i & NK_TT__OVER_MASK]);
                buffer[(i+kernel_width) & NK_TT__OVER_MASK] = pixels[i*stride_in_bytes];
                pixels[i*stride_in_bytes] = (unsigned char) (total / (unsigned int)kernel_width);
            }
            break;
        }

        for (; i < h; ++i) {
            NK_ASSERT(pixels[i*stride_in_bytes] == 0);
            total -= (unsigned int)(buffer[i & NK_TT__OVER_MASK]);
            pixels[i*stride_in_bytes] = (unsigned char) (total / (unsigned int)kernel_width);
        }
        pixels += 1;
    }
}

NK_INTERN float
nk_tt__oversample_shift(int oversample)
{
    if (!oversample)
        return 0.0f;

    /* The prefilter is a box filter of width "oversample", */
    /* which shifts phase by (oversample - 1)/2 pixels in */
    /* oversampled space. We want to shift in the opposite */
    /* direction to counter this. */
    return (float)-(oversample - 1) / (2.0f * (float)oversample);
}

/* rects array must be big enough to accommodate all characters in the given ranges */
NK_INTERN int
nk_tt_PackFontRangesGatherRects(struct nk_tt_pack_context *spc,
    struct nk_tt_fontinfo *info, struct nk_tt_pack_range *ranges,
    int num_ranges, struct nk_rp_rect *rects)
{
    int i,j,k;
    k = 0;

    for (i=0; i < num_ranges; ++i) {
        float fh = ranges[i].font_size;
        float scale = (fh > 0) ? nk_tt_ScaleForPixelHeight(info, fh):
            nk_tt_ScaleForMappingEmToPixels(info, -fh);
        ranges[i].h_oversample = (unsigned char) spc->h_oversample;
        ranges[i].v_oversample = (unsigned char) spc->v_oversample;
        for (j=0; j < ranges[i].num_chars; ++j) {
            int x0,y0,x1,y1;
            int codepoint = ranges[i].first_unicode_codepoint_in_range ?
                ranges[i].first_unicode_codepoint_in_range + j :
                ranges[i].array_of_unicode_codepoints[j];

            int glyph = nk_tt_FindGlyphIndex(info, codepoint);
            nk_tt_GetGlyphBitmapBoxSubpixel(info,glyph, scale * (float)spc->h_oversample,
                scale * (float)spc->v_oversample, 0,0, &x0,&y0,&x1,&y1);
            rects[k].w = (nk_rp_coord) (x1-x0 + spc->padding + (int)spc->h_oversample-1);
            rects[k].h = (nk_rp_coord) (y1-y0 + spc->padding + (int)spc->v_oversample-1);
            ++k;
        }
    }
    return k;
}

NK_INTERN int
nk_tt_PackFontRangesRenderIntoRects(struct nk_tt_pack_context *spc,
    struct nk_tt_fontinfo *info, struct nk_tt_pack_range *ranges,
    int num_ranges, struct nk_rp_rect *rects, struct nk_allocator *alloc)
{
    int i,j,k, return_value = 1;
    /* save current values */
    int old_h_over = (int)spc->h_oversample;
    int old_v_over = (int)spc->v_oversample;
    /* rects array must be big enough to accommodate all characters in the given ranges */

    k = 0;
    for (i=0; i < num_ranges; ++i)
    {
        float fh = ranges[i].font_size;
        float recip_h,recip_v,sub_x,sub_y;
        float scale = fh > 0 ? nk_tt_ScaleForPixelHeight(info, fh):
            nk_tt_ScaleForMappingEmToPixels(info, -fh);

        spc->h_oversample = ranges[i].h_oversample;
        spc->v_oversample = ranges[i].v_oversample;

        recip_h = 1.0f / (float)spc->h_oversample;
        recip_v = 1.0f / (float)spc->v_oversample;

        sub_x = nk_tt__oversample_shift((int)spc->h_oversample);
        sub_y = nk_tt__oversample_shift((int)spc->v_oversample);

        for (j=0; j < ranges[i].num_chars; ++j)
        {
            struct nk_rp_rect *r = &rects[k];
            if (r->was_packed)
            {
                struct nk_tt_packedchar *bc = &ranges[i].chardata_for_range[j];
                int advance, lsb, x0,y0,x1,y1;
                int codepoint = ranges[i].first_unicode_codepoint_in_range ?
                    ranges[i].first_unicode_codepoint_in_range + j :
                    ranges[i].array_of_unicode_codepoints[j];
                int glyph = nk_tt_FindGlyphIndex(info, codepoint);
                nk_rp_coord pad = (nk_rp_coord) spc->padding;

                /* pad on left and top */
                r->x = (nk_rp_coord)((int)r->x + (int)pad);
                r->y = (nk_rp_coord)((int)r->y + (int)pad);
                r->w = (nk_rp_coord)((int)r->w - (int)pad);
                r->h = (nk_rp_coord)((int)r->h - (int)pad);

                nk_tt_GetGlyphHMetrics(info, glyph, &advance, &lsb);
                nk_tt_GetGlyphBitmapBox(info, glyph, scale * (float)spc->h_oversample,
                        (scale * (float)spc->v_oversample), &x0,&y0,&x1,&y1);
                nk_tt_MakeGlyphBitmapSubpixel(info, spc->pixels + r->x + r->y*spc->stride_in_bytes,
                    (int)(r->w - spc->h_oversample+1), (int)(r->h - spc->v_oversample+1),
                    spc->stride_in_bytes, scale * (float)spc->h_oversample,
                    scale * (float)spc->v_oversample, 0,0, glyph, alloc);

                if (spc->h_oversample > 1)
                   nk_tt__h_prefilter(spc->pixels + r->x + r->y*spc->stride_in_bytes,
                        r->w, r->h, spc->stride_in_bytes, (int)spc->h_oversample);

                if (spc->v_oversample > 1)
                   nk_tt__v_prefilter(spc->pixels + r->x + r->y*spc->stride_in_bytes,
                        r->w, r->h, spc->stride_in_bytes, (int)spc->v_oversample);

                bc->x0       = (nk_ushort)  r->x;
                bc->y0       = (nk_ushort)  r->y;
                bc->x1       = (nk_ushort) (r->x + r->w);
                bc->y1       = (nk_ushort) (r->y + r->h);
                bc->xadvance = scale * (float)advance;
                bc->xoff     = (float)  x0 * recip_h + sub_x;
                bc->yoff     = (float)  y0 * recip_v + sub_y;
                bc->xoff2    = ((float)x0 + r->w) * recip_h + sub_x;
                bc->yoff2    = ((float)y0 + r->h) * recip_v + sub_y;
            } else {
                return_value = 0; /* if any fail, report failure */
            }
            ++k;
        }
    }
    /* restore original values */
    spc->h_oversample = (unsigned int)old_h_over;
    spc->v_oversample = (unsigned int)old_v_over;
    return return_value;
}

NK_INTERN void
nk_tt_GetPackedQuad(struct nk_tt_packedchar *chardata, int pw, int ph,
    int char_index, float *xpos, float *ypos, struct nk_tt_aligned_quad *q,
    int align_to_integer)
{
    float ipw = 1.0f / (float)pw, iph = 1.0f / (float)ph;
    struct nk_tt_packedchar *b = (struct nk_tt_packedchar*)(chardata + char_index);
    if (align_to_integer) {
        int tx = nk_ifloor((*xpos + b->xoff) + 0.5f);
        int ty = nk_ifloor((*ypos + b->yoff) + 0.5f);

        float x = (float)tx;
        float y = (float)ty;

        q->x0 = x;
        q->y0 = y;
        q->x1 = x + b->xoff2 - b->xoff;
        q->y1 = y + b->yoff2 - b->yoff;
    } else {
        q->x0 = *xpos + b->xoff;
        q->y0 = *ypos + b->yoff;
        q->x1 = *xpos + b->xoff2;
        q->y1 = *ypos + b->yoff2;
    }
    q->s0 = b->x0 * ipw;
    q->t0 = b->y0 * iph;
    q->s1 = b->x1 * ipw;
    q->t1 = b->y1 * iph;
    *xpos += b->xadvance;
}

/* -------------------------------------------------------------
 *
 *                          FONT BAKING
 *
 * --------------------------------------------------------------*/
struct nk_font_bake_data {
    struct nk_tt_fontinfo info;
    struct nk_rp_rect *rects;
    struct nk_tt_pack_range *ranges;
    nk_rune range_count;
};

struct nk_font_baker {
    struct nk_allocator alloc;
    struct nk_tt_pack_context spc;
    struct nk_font_bake_data *build;
    struct nk_tt_packedchar *packed_chars;
    struct nk_rp_rect *rects;
    struct nk_tt_pack_range *ranges;
};

NK_GLOBAL const nk_size nk_rect_align = NK_ALIGNOF(struct nk_rp_rect);
NK_GLOBAL const nk_size nk_range_align = NK_ALIGNOF(struct nk_tt_pack_range);
NK_GLOBAL const nk_size nk_char_align = NK_ALIGNOF(struct nk_tt_packedchar);
NK_GLOBAL const nk_size nk_build_align = NK_ALIGNOF(struct nk_font_bake_data);
NK_GLOBAL const nk_size nk_baker_align = NK_ALIGNOF(struct nk_font_baker);

NK_INTERN int
nk_range_count(const nk_rune *range)
{
    const nk_rune *iter = range;
    NK_ASSERT(range);
    if (!range) return 0;
    while (*(iter++) != 0);
    return (iter == range) ? 0 : (int)((iter - range)/2);
}

NK_INTERN int
nk_range_glyph_count(const nk_rune *range, int count)
{
    int i = 0;
    int total_glyphs = 0;
    for (i = 0; i < count; ++i) {
        int diff;
        nk_rune f = range[(i*2)+0];
        nk_rune t = range[(i*2)+1];
        NK_ASSERT(t >= f);
        diff = (int)((t - f) + 1);
        total_glyphs += diff;
    }
    return total_glyphs;
}

NK_API const nk_rune*
nk_font_default_glyph_ranges(void)
{
    NK_STORAGE const nk_rune ranges[] = {0x0020, 0x00FF, 0};
    return ranges;
}

NK_API const nk_rune*
nk_font_chinese_glyph_ranges(void)
{
    NK_STORAGE const nk_rune ranges[] = {
        0x0020, 0x00FF,
        0x3000, 0x30FF,
        0x31F0, 0x31FF,
        0xFF00, 0xFFEF,
        0x4e00, 0x9FAF,
        0
    };
    return ranges;
}

NK_API const nk_rune*
nk_font_cyrillic_glyph_ranges(void)
{
    NK_STORAGE const nk_rune ranges[] = {
        0x0020, 0x00FF,
        0x0400, 0x052F,
        0x2DE0, 0x2DFF,
        0xA640, 0xA69F,
        0
    };
    return ranges;
}

NK_API const nk_rune*
nk_font_korean_glyph_ranges(void)
{
    NK_STORAGE const nk_rune ranges[] = {
        0x0020, 0x00FF,
        0x3131, 0x3163,
        0xAC00, 0xD79D,
        0
    };
    return ranges;
}

NK_API void
nk_font_bake_memory(nk_size *temp, int *glyph_count,
    struct nk_font_config *config, int count)
{
    int i;
    int range_count = 0;
    int total_range_count = 0;
    NK_ASSERT(config);
    NK_ASSERT(glyph_count);
    if (!config) {
        *temp = 0;
        *glyph_count = 0;
        return;
    }

    *glyph_count = 0;
    if (!config->range)
        config->range = nk_font_default_glyph_ranges();
    for (i = 0; i < count; ++i) {
        range_count = nk_range_count(config[i].range);
        total_range_count += range_count;
        *glyph_count += nk_range_glyph_count(config[i].range, range_count);
    }

    *temp = (nk_size)*glyph_count * sizeof(struct nk_rp_rect);
    *temp += (nk_size)total_range_count * sizeof(struct nk_tt_pack_range);
    *temp += (nk_size)*glyph_count * sizeof(struct nk_tt_packedchar);
    *temp += (nk_size)count * sizeof(struct nk_font_bake_data);
    *temp += sizeof(struct nk_font_baker);
    *temp += nk_rect_align + nk_range_align + nk_char_align;
    *temp += nk_build_align + nk_baker_align;
}

NK_INTERN struct nk_font_baker*
nk_font_baker(void *memory, int glyph_count, int count, struct nk_allocator *alloc)
{
    struct nk_font_baker *baker;
    if (!memory) return 0;
    /* setup baker inside a memory block  */
    baker = (struct nk_font_baker*)NK_ALIGN_PTR(memory, nk_baker_align);
    baker->build = (struct nk_font_bake_data*)NK_ALIGN_PTR((baker + 1), nk_build_align);
    baker->packed_chars = (struct nk_tt_packedchar*)NK_ALIGN_PTR((baker->build + count), nk_char_align);
    baker->rects = (struct nk_rp_rect*)NK_ALIGN_PTR((baker->packed_chars + glyph_count), nk_rect_align);
    baker->ranges = (struct nk_tt_pack_range*)NK_ALIGN_PTR((baker->rects + glyph_count), nk_range_align);
    baker->alloc = *alloc;
    return baker;
}

NK_API int
nk_font_bake_pack(nk_size *image_memory, int *width, int *height,
    struct nk_recti *custom, void *temp, nk_size temp_size,
    const struct nk_font_config *config, int count,
    struct nk_allocator *alloc)
{
    NK_STORAGE const nk_size max_height = 1024 * 32;
    struct nk_font_baker* baker;
    int total_glyph_count = 0;
    int total_range_count = 0;
    int range_count = 0;
    int i = 0;

    NK_ASSERT(image_memory);
    NK_ASSERT(width);
    NK_ASSERT(height);
    NK_ASSERT(config);
    NK_ASSERT(temp);
    NK_ASSERT(temp_size);
    NK_ASSERT(count);
    NK_ASSERT(alloc);
    if (!image_memory || !width || !height || !config || !temp ||
        !temp_size || !count) return nk_false;

    for (i = 0; i < count; ++i) {
        range_count = nk_range_count(config[i].range);
        total_range_count += range_count;
        total_glyph_count += nk_range_glyph_count(config[i].range, range_count);
    }

    /* setup font baker from temporary memory */
    nk_zero(temp, temp_size);
    baker = nk_font_baker(temp, total_glyph_count, count, alloc);
    if (!baker) return nk_false;
    for (i = 0; i < count; ++i) {
        const struct nk_font_config *cfg = &config[i];
        if (!nk_tt_InitFont(&baker->build[i].info, (const unsigned char*)cfg->ttf_blob, 0))
            return nk_false;
    }

    *height = 0;
    *width = (total_glyph_count > 1000) ? 1024 : 512;
    nk_tt_PackBegin(&baker->spc, 0, (int)*width, (int)max_height, 0, 1, alloc);
    {
        int input_i = 0;
        int range_n = 0;
        int rect_n = 0;
        int char_n = 0;

        /* pack custom user data first so it will be in the upper left corner*/
        if (custom) {
            struct nk_rp_rect custom_space;
            nk_zero(&custom_space, sizeof(custom_space));
            custom_space.w = (nk_rp_coord)((custom->w * 2) + 1);
            custom_space.h = (nk_rp_coord)(custom->h + 1);

            nk_tt_PackSetOversampling(&baker->spc, 1, 1);
            nk_rp_pack_rects((struct nk_rp_context*)baker->spc.pack_info, &custom_space, 1);
            *height = NK_MAX(*height, (int)(custom_space.y + custom_space.h));

            custom->x = (short)custom_space.x;
            custom->y = (short)custom_space.y;
            custom->w = (short)custom_space.w;
            custom->h = (short)custom_space.h;
        }

        /* first font pass: pack all glyphs */
        for (input_i = 0; input_i < count; input_i++) {
            int n = 0;
            const nk_rune *in_range;
            const struct nk_font_config *cfg = &config[input_i];
            struct nk_font_bake_data *tmp = &baker->build[input_i];
            int glyph_count;

            /* count glyphs + ranges in current font */
            glyph_count = 0; range_count = 0;
            for (in_range = cfg->range; in_range[0] && in_range[1]; in_range += 2) {
                glyph_count += (int)(in_range[1] - in_range[0]) + 1;
                range_count++;
            }

            /* setup ranges  */
            tmp->ranges = baker->ranges + range_n;
            tmp->range_count = (nk_rune)range_count;
            range_n += range_count;
            for (i = 0; i < range_count; ++i) {
                in_range = &cfg->range[i * 2];
                tmp->ranges[i].font_size = cfg->size;
                tmp->ranges[i].first_unicode_codepoint_in_range = (int)in_range[0];
                tmp->ranges[i].num_chars = (int)(in_range[1]- in_range[0]) + 1;
                tmp->ranges[i].chardata_for_range = baker->packed_chars + char_n;
                char_n += tmp->ranges[i].num_chars;
            }

            /* pack */
            tmp->rects = baker->rects + rect_n;
            rect_n += glyph_count;
            nk_tt_PackSetOversampling(&baker->spc, cfg->oversample_h, cfg->oversample_v);
            n = nk_tt_PackFontRangesGatherRects(&baker->spc, &tmp->info,
                tmp->ranges, (int)tmp->range_count, tmp->rects);
            nk_rp_pack_rects((struct nk_rp_context*)baker->spc.pack_info, tmp->rects, (int)n);

            /* texture height */
            for (i = 0; i < n; ++i) {
                if (tmp->rects[i].was_packed)
                    *height = NK_MAX(*height, tmp->rects[i].y + tmp->rects[i].h);
            }
        }
        NK_ASSERT(rect_n == total_glyph_count);
        NK_ASSERT(char_n == total_glyph_count);
        NK_ASSERT(range_n == total_range_count);
    }
    *height = (int)nk_round_up_pow2((nk_uint)*height);
    *image_memory = (nk_size)(*width) * (nk_size)(*height);
    return nk_true;
}

NK_API void
nk_font_bake(void *image_memory, int width, int height,
    void *temp, nk_size temp_size, struct nk_font_glyph *glyphs,
    int glyphs_count, const struct nk_font_config *config, int font_count)
{
    int input_i = 0;
    struct nk_font_baker* baker;
    nk_rune glyph_n = 0;

    NK_ASSERT(image_memory);
    NK_ASSERT(width);
    NK_ASSERT(height);
    NK_ASSERT(config);
    NK_ASSERT(temp);
    NK_ASSERT(temp_size);
    NK_ASSERT(font_count);
    NK_ASSERT(glyphs_count);
    if (!image_memory || !width || !height || !config || !temp ||
        !temp_size || !font_count || !glyphs || !glyphs_count)
        return;

    /* second font pass: render glyphs */
    baker = (struct nk_font_baker*)NK_ALIGN_PTR(temp, nk_baker_align);
    nk_zero(image_memory, (nk_size)((nk_size)width * (nk_size)height));
    baker->spc.pixels = (unsigned char*)image_memory;
    baker->spc.height = (int)height;
    for (input_i = 0; input_i < font_count; ++input_i) {
        const struct nk_font_config *cfg = &config[input_i];
        struct nk_font_bake_data *tmp = &baker->build[input_i];
        nk_tt_PackSetOversampling(&baker->spc, cfg->oversample_h, cfg->oversample_v);
        nk_tt_PackFontRangesRenderIntoRects(&baker->spc, &tmp->info, tmp->ranges,
            (int)tmp->range_count, tmp->rects, &baker->alloc);
    }
    nk_tt_PackEnd(&baker->spc, &baker->alloc);

    /* third pass: setup font and glyphs */
    for (input_i = 0; input_i < font_count; ++input_i)
    {
        nk_size i = 0;
        int char_idx = 0;
        nk_rune glyph_count = 0;
        const struct nk_font_config *cfg = &config[input_i];
        struct nk_font_bake_data *tmp = &baker->build[input_i];
        struct nk_baked_font *dst_font = cfg->font;

        float font_scale = nk_tt_ScaleForPixelHeight(&tmp->info, cfg->size);
        int unscaled_ascent, unscaled_descent, unscaled_line_gap;
        nk_tt_GetFontVMetrics(&tmp->info, &unscaled_ascent, &unscaled_descent,
                                &unscaled_line_gap);

        /* fill baked font */
        if (!cfg->merge_mode) {
            dst_font->ranges = cfg->range;
            dst_font->height = cfg->size;
            dst_font->ascent = ((float)unscaled_ascent * font_scale);
            dst_font->descent = ((float)unscaled_descent * font_scale);
            dst_font->glyph_offset = glyph_n;
        }

        /* fill own baked font glyph array */
        for (i = 0; i < tmp->range_count; ++i)
        {
            struct nk_tt_pack_range *range = &tmp->ranges[i];
            for (char_idx = 0; char_idx < range->num_chars; char_idx++)
            {
                nk_rune codepoint = 0;
                float dummy_x = 0, dummy_y = 0;
                struct nk_tt_aligned_quad q;
                struct nk_font_glyph *glyph;

                /* query glyph bounds from stb_truetype */
                const struct nk_tt_packedchar *pc = &range->chardata_for_range[char_idx];
                glyph_count++;
                if (!pc->x0 && !pc->x1 && !pc->y0 && !pc->y1) continue;
                codepoint = (nk_rune)(range->first_unicode_codepoint_in_range + char_idx);
                nk_tt_GetPackedQuad(range->chardata_for_range, (int)width,
                    (int)height, char_idx, &dummy_x, &dummy_y, &q, 0);

                /* fill own glyph type with data */
                glyph = &glyphs[dst_font->glyph_offset + (unsigned int)char_idx];
                glyph->codepoint = codepoint;
                glyph->x0 = q.x0; glyph->y0 = q.y0;
                glyph->x1 = q.x1; glyph->y1 = q.y1;
                glyph->y0 += (dst_font->ascent + 0.5f);
                glyph->y1 += (dst_font->ascent + 0.5f);
                glyph->w = glyph->x1 - glyph->x0 + 0.5f;
                glyph->h = glyph->y1 - glyph->y0;

                if (cfg->coord_type == NK_COORD_PIXEL) {
                    glyph->u0 = q.s0 * (float)width;
                    glyph->v0 = q.t0 * (float)height;
                    glyph->u1 = q.s1 * (float)width;
                    glyph->v1 = q.t1 * (float)height;
                } else {
                    glyph->u0 = q.s0;
                    glyph->v0 = q.t0;
                    glyph->u1 = q.s1;
                    glyph->v1 = q.t1;
                }
                glyph->xadvance = (pc->xadvance + cfg->spacing.x);
                if (cfg->pixel_snap)
                    glyph->xadvance = (float)(int)(glyph->xadvance + 0.5f);
            }
        }
        dst_font->glyph_count = glyph_count;
        glyph_n += dst_font->glyph_count;
    }
}

NK_API void
nk_font_bake_custom_data(void *img_memory, int img_width, int img_height,
    struct nk_recti img_dst, const char *texture_data_mask, int tex_width,
    int tex_height, char white, char black)
{
    nk_byte *pixels;
    int y = 0;
    int x = 0;
    int n = 0;

    NK_ASSERT(img_memory);
    NK_ASSERT(img_width);
    NK_ASSERT(img_height);
    NK_ASSERT(texture_data_mask);
    NK_UNUSED(tex_height);
    if (!img_memory || !img_width || !img_height || !texture_data_mask)
        return;

    pixels = (nk_byte*)img_memory;
    for (y = 0, n = 0; y < tex_height; ++y) {
        for (x = 0; x < tex_width; ++x, ++n) {
            const int off0 = ((img_dst.x + x) + (img_dst.y + y) * img_width);
            const int off1 = off0 + 1 + tex_width;
            pixels[off0] = (texture_data_mask[n] == white) ? 0xFF : 0x00;
            pixels[off1] = (texture_data_mask[n] == black) ? 0xFF : 0x00;
        }
    }
}

NK_API void
nk_font_bake_convert(void *out_memory, int img_width, int img_height,
    const void *in_memory)
{
    int n = 0;
    const nk_byte *src;
    nk_rune *dst;

    NK_ASSERT(out_memory);
    NK_ASSERT(in_memory);
    NK_ASSERT(img_width);
    NK_ASSERT(img_height);
    if (!out_memory || !in_memory || !img_height || !img_width) return;

    dst = (nk_rune*)out_memory;
    src = (const nk_byte*)in_memory;
    for (n = (int)(img_width * img_height); n > 0; n--)
        *dst++ = ((nk_rune)(*src++) << 24) | 0x00FFFFFF;
}

/* -------------------------------------------------------------
 *
 *                          FONT
 *
 * --------------------------------------------------------------*/
NK_INTERN float
nk_font_text_width(nk_handle handle, float height, const char *text, int len)
{
    nk_rune unicode;
    int text_len  = 0;
    float text_width = 0;
    int glyph_len = 0;
    float scale = 0;

    struct nk_font *font = (struct nk_font*)handle.ptr;
    NK_ASSERT(font);
    NK_ASSERT(font->glyphs);
    if (!font || !text || !len)
        return 0;

    scale = height/font->info.height;
    glyph_len = text_len = nk_utf_decode(text, &unicode, (int)len);
    if (!glyph_len) return 0;
    while (text_len <= (int)len && glyph_len) {
        const struct nk_font_glyph *g;
        if (unicode == NK_UTF_INVALID) break;

        /* query currently drawn glyph information */
        g = nk_font_find_glyph(font, unicode);
        text_width += g->xadvance * scale;

        /* offset next glyph */
        glyph_len = nk_utf_decode(text + text_len, &unicode, (int)len - text_len);
        text_len += glyph_len;
    }
    return text_width;
}

#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
NK_INTERN void
nk_font_query_font_glyph(nk_handle handle, float height,
    struct nk_user_font_glyph *glyph, nk_rune codepoint, nk_rune next_codepoint)
{
    float scale;
    const struct nk_font_glyph *g;
    struct nk_font *font;

    NK_ASSERT(glyph);
    NK_UNUSED(next_codepoint);

    font = (struct nk_font*)handle.ptr;
    NK_ASSERT(font);
    NK_ASSERT(font->glyphs);
    if (!font || !glyph)
        return;

    scale = height/font->info.height;
    g = nk_font_find_glyph(font, codepoint);
    glyph->width = (g->x1 - g->x0) * scale;
    glyph->height = (g->y1 - g->y0) * scale;
    glyph->offset = nk_vec2(g->x0 * scale, g->y0 * scale);
    glyph->xadvance = (g->xadvance * scale);
    glyph->uv[0] = nk_vec2(g->u0, g->v0);
    glyph->uv[1] = nk_vec2(g->u1, g->v1);
}
#endif

NK_API const struct nk_font_glyph*
nk_font_find_glyph(struct nk_font *font, nk_rune unicode)
{
    int i = 0;
    int count;
    int total_glyphs = 0;
    const struct nk_font_glyph *glyph = 0;
    NK_ASSERT(font);
    NK_ASSERT(font->glyphs);

    glyph = font->fallback;
    count = nk_range_count(font->info.ranges);
    for (i = 0; i < count; ++i) {
        int diff;
        nk_rune f = font->info.ranges[(i*2)+0];
        nk_rune t = font->info.ranges[(i*2)+1];
        diff = (int)((t - f) + 1);
        if (unicode >= f && unicode <= t)
            return &font->glyphs[((nk_rune)total_glyphs + (unicode - f))];
        total_glyphs += diff;
    }
    return glyph;
}

NK_API void
nk_font_init(struct nk_font *font, float pixel_height,
    nk_rune fallback_codepoint, struct nk_font_glyph *glyphs,
    const struct nk_baked_font *baked_font, nk_handle atlas)
{
    struct nk_baked_font baked;
    NK_ASSERT(font);
    NK_ASSERT(glyphs);
    NK_ASSERT(baked_font);
    if (!font || !glyphs || !baked_font)
        return;

    baked = *baked_font;
    nk_zero(font, sizeof(*font));
    font->info = baked;
    font->scale = (float)pixel_height / (float)font->info.height;
    font->glyphs = &glyphs[baked_font->glyph_offset];
    font->texture = atlas;
    font->fallback_codepoint = fallback_codepoint;
    font->fallback = nk_font_find_glyph(font, fallback_codepoint);

    font->handle.height = font->info.height * font->scale;
    font->handle.width = nk_font_text_width;
    font->handle.userdata.ptr = font;
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    font->handle.query = nk_font_query_font_glyph;
    font->handle.texture = font->texture;
#endif
}

/* ---------------------------------------------------------------------------
 *
 *                          DEFAULT FONT
 *
 * ProggyClean.ttf
 * Copyright (c) 2004, 2005 Tristan Grimmer
 * MIT license (see License.txt in http://www.upperbounds.net/download/ProggyClean.ttf.zip)
 * Download and more information at http://upperbounds.net
 *-----------------------------------------------------------------------------*/
#ifdef NK_INCLUDE_DEFAULT_FONT

 #ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverlength-strings"
#elif defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverlength-strings"
#endif

NK_GLOBAL const char nk_proggy_clean_ttf_compressed_data_base85[11980+1] =
    "7])#######hV0qs'/###[),##/l:$#Q6>##5[n42>c-TH`->>#/e>11NNV=Bv(*:.F?uu#(gRU.o0XGH`$vhLG1hxt9?W`#,5LsCp#-i>.r$<$6pD>Lb';9Crc6tgXmKVeU2cD4Eo3R/"
    "2*>]b(MC;$jPfY.;h^`IWM9<Lh2TlS+f-s$o6Q<BWH`YiU.xfLq$N;$0iR/GX:U(jcW2p/W*q?-qmnUCI;jHSAiFWM.R*kU@C=GH?a9wp8f$e.-4^Qg1)Q-GL(lf(r/7GrRgwV%MS=C#"
    "`8ND>Qo#t'X#(v#Y9w0#1D$CIf;W'#pWUPXOuxXuU(H9M(1<q-UE31#^-V'8IRUo7Qf./L>=Ke$$'5F%)]0^#0X@U.a<r:QLtFsLcL6##lOj)#.Y5<-R&KgLwqJfLgN&;Q?gI^#DY2uL"
    "i@^rMl9t=cWq6##weg>$FBjVQTSDgEKnIS7EM9>ZY9w0#L;>>#Mx&4Mvt//L[MkA#W@lK.N'[0#7RL_&#w+F%HtG9M#XL`N&.,GM4Pg;-<nLENhvx>-VsM.M0rJfLH2eTM`*oJMHRC`N"
    "kfimM2J,W-jXS:)r0wK#@Fge$U>`w'N7G#$#fB#$E^$#:9:hk+eOe--6x)F7*E%?76%^GMHePW-Z5l'&GiF#$956:rS?dA#fiK:)Yr+`&#0j@'DbG&#^$PG.Ll+DNa<XCMKEV*N)LN/N"
    "*b=%Q6pia-Xg8I$<MR&,VdJe$<(7G;Ckl'&hF;;$<_=X(b.RS%%)###MPBuuE1V:v&cX&#2m#(&cV]`k9OhLMbn%s$G2,B$BfD3X*sp5#l,$R#]x_X1xKX%b5U*[r5iMfUo9U`N99hG)"
    "tm+/Us9pG)XPu`<0s-)WTt(gCRxIg(%6sfh=ktMKn3j)<6<b5Sk_/0(^]AaN#(p/L>&VZ>1i%h1S9u5o@YaaW$e+b<TWFn/Z:Oh(Cx2$lNEoN^e)#CFY@@I;BOQ*sRwZtZxRcU7uW6CX"
    "ow0i(?$Q[cjOd[P4d)]>ROPOpxTO7Stwi1::iB1q)C_=dV26J;2,]7op$]uQr@_V7$q^%lQwtuHY]=DX,n3L#0PHDO4f9>dC@O>HBuKPpP*E,N+b3L#lpR/MrTEH.IAQk.a>D[.e;mc."
    "x]Ip.PH^'/aqUO/$1WxLoW0[iLA<QT;5HKD+@qQ'NQ(3_PLhE48R.qAPSwQ0/WK?Z,[x?-J;jQTWA0X@KJ(_Y8N-:/M74:/-ZpKrUss?d#dZq]DAbkU*JqkL+nwX@@47`5>w=4h(9.`G"
    "CRUxHPeR`5Mjol(dUWxZa(>STrPkrJiWx`5U7F#.g*jrohGg`cg:lSTvEY/EV_7H4Q9[Z%cnv;JQYZ5q.l7Zeas:HOIZOB?G<Nald$qs]@]L<J7bR*>gv:[7MI2k).'2($5FNP&EQ(,)"
    "U]W]+fh18.vsai00);D3@4ku5P?DP8aJt+;qUM]=+b'8@;mViBKx0DE[-auGl8:PJ&Dj+M6OC]O^((##]`0i)drT;-7X`=-H3[igUnPG-NZlo.#k@h#=Ork$m>a>$-?Tm$UV(?#P6YY#"
    "'/###xe7q.73rI3*pP/$1>s9)W,JrM7SN]'/4C#v$U`0#V.[0>xQsH$fEmPMgY2u7Kh(G%siIfLSoS+MK2eTM$=5,M8p`A.;_R%#u[K#$x4AG8.kK/HSB==-'Ie/QTtG?-.*^N-4B/ZM"
    "_3YlQC7(p7q)&](`6_c)$/*JL(L-^(]$wIM`dPtOdGA,U3:w2M-0<q-]L_?^)1vw'.,MRsqVr.L;aN&#/EgJ)PBc[-f>+WomX2u7lqM2iEumMTcsF?-aT=Z-97UEnXglEn1K-bnEO`gu"
    "Ft(c%=;Am_Qs@jLooI&NX;]0#j4#F14;gl8-GQpgwhrq8'=l_f-b49'UOqkLu7-##oDY2L(te+Mch&gLYtJ,MEtJfLh'x'M=$CS-ZZ%P]8bZ>#S?YY#%Q&q'3^Fw&?D)UDNrocM3A76/"
    "/oL?#h7gl85[qW/NDOk%16ij;+:1a'iNIdb-ou8.P*w,v5#EI$TWS>Pot-R*H'-SEpA:g)f+O$%%`kA#G=8RMmG1&O`>to8bC]T&$,n.LoO>29sp3dt-52U%VM#q7'DHpg+#Z9%H[K<L"
    "%a2E-grWVM3@2=-k22tL]4$##6We'8UJCKE[d_=%wI;'6X-GsLX4j^SgJ$##R*w,vP3wK#iiW&#*h^D&R?jp7+/u&#(AP##XU8c$fSYW-J95_-Dp[g9wcO&#M-h1OcJlc-*vpw0xUX&#"
    "OQFKNX@QI'IoPp7nb,QU//MQ&ZDkKP)X<WSVL(68uVl&#c'[0#(s1X&xm$Y%B7*K:eDA323j998GXbA#pwMs-jgD$9QISB-A_(aN4xoFM^@C58D0+Q+q3n0#3U1InDjF682-SjMXJK)("
    "h$hxua_K]ul92%'BOU&#BRRh-slg8KDlr:%L71Ka:.A;%YULjDPmL<LYs8i#XwJOYaKPKc1h:'9Ke,g)b),78=I39B;xiY$bgGw-&.Zi9InXDuYa%G*f2Bq7mn9^#p1vv%#(Wi-;/Z5h"
    "o;#2:;%d&#x9v68C5g?ntX0X)pT`;%pB3q7mgGN)3%(P8nTd5L7GeA-GL@+%J3u2:(Yf>et`e;)f#Km8&+DC$I46>#Kr]]u-[=99tts1.qb#q72g1WJO81q+eN'03'eM>&1XxY-caEnO"
    "j%2n8)),?ILR5^.Ibn<-X-Mq7[a82Lq:F&#ce+S9wsCK*x`569E8ew'He]h:sI[2LM$[guka3ZRd6:t%IG:;$%YiJ:Nq=?eAw;/:nnDq0(CYcMpG)qLN4$##&J<j$UpK<Q4a1]MupW^-"
    "sj_$%[HK%'F####QRZJ::Y3EGl4'@%FkiAOg#p[##O`gukTfBHagL<LHw%q&OV0##F=6/:chIm0@eCP8X]:kFI%hl8hgO@RcBhS-@Qb$%+m=hPDLg*%K8ln(wcf3/'DW-$.lR?n[nCH-"
    "eXOONTJlh:.RYF%3'p6sq:UIMA945&^HFS87@$EP2iG<-lCO$%c`uKGD3rC$x0BL8aFn--`ke%#HMP'vh1/R&O_J9'um,.<tx[@%wsJk&bUT2`0uMv7gg#qp/ij.L56'hl;.s5CUrxjO"
    "M7-##.l+Au'A&O:-T72L]P`&=;ctp'XScX*rU.>-XTt,%OVU4)S1+R-#dg0/Nn?Ku1^0f$B*P:Rowwm-`0PKjYDDM'3]d39VZHEl4,.j']Pk-M.h^&:0FACm$maq-&sgw0t7/6(^xtk%"
    "LuH88Fj-ekm>GA#_>568x6(OFRl-IZp`&b,_P'$M<Jnq79VsJW/mWS*PUiq76;]/NM_>hLbxfc$mj`,O;&%W2m`Zh:/)Uetw:aJ%]K9h:TcF]u_-Sj9,VK3M.*'&0D[Ca]J9gp8,kAW]"
    "%(?A%R$f<->Zts'^kn=-^@c4%-pY6qI%J%1IGxfLU9CP8cbPlXv);C=b),<2mOvP8up,UVf3839acAWAW-W?#ao/^#%KYo8fRULNd2.>%m]UK:n%r$'sw]J;5pAoO_#2mO3n,'=H5(et"
    "Hg*`+RLgv>=4U8guD$I%D:W>-r5V*%j*W:Kvej.Lp$<M-SGZ':+Q_k+uvOSLiEo(<aD/K<CCc`'Lx>'?;++O'>()jLR-^u68PHm8ZFWe+ej8h:9r6L*0//c&iH&R8pRbA#Kjm%upV1g:"
    "a_#Ur7FuA#(tRh#.Y5K+@?3<-8m0$PEn;J:rh6?I6uG<-`wMU'ircp0LaE_OtlMb&1#6T.#FDKu#1Lw%u%+GM+X'e?YLfjM[VO0MbuFp7;>Q&#WIo)0@F%q7c#4XAXN-U&VB<HFF*qL("
    "$/V,;(kXZejWO`<[5??ewY(*9=%wDc;,u<'9t3W-(H1th3+G]ucQ]kLs7df($/*JL]@*t7Bu_G3_7mp7<iaQjO@.kLg;x3B0lqp7Hf,^Ze7-##@/c58Mo(3;knp0%)A7?-W+eI'o8)b<"
    "nKnw'Ho8C=Y>pqB>0ie&jhZ[?iLR@@_AvA-iQC(=ksRZRVp7`.=+NpBC%rh&3]R:8XDmE5^V8O(x<<aG/1N$#FX$0V5Y6x'aErI3I$7x%E`v<-BY,)%-?Psf*l?%C3.mM(=/M0:JxG'?"
    "7WhH%o'a<-80g0NBxoO(GH<dM]n.+%q@jH?f.UsJ2Ggs&4<-e47&Kl+f//9@`b+?.TeN_&B8Ss?v;^Trk;f#YvJkl&w$]>-+k?'(<S:68tq*WoDfZu';mM?8X[ma8W%*`-=;D.(nc7/;"
    ")g:T1=^J$&BRV(-lTmNB6xqB[@0*o.erM*<SWF]u2=st-*(6v>^](H.aREZSi,#1:[IXaZFOm<-ui#qUq2$##Ri;u75OK#(RtaW-K-F`S+cF]uN`-KMQ%rP/Xri.LRcB##=YL3BgM/3M"
    "D?@f&1'BW-)Ju<L25gl8uhVm1hL$##*8###'A3/LkKW+(^rWX?5W_8g)a(m&K8P>#bmmWCMkk&#TR`C,5d>g)F;t,4:@_l8G/5h4vUd%&%950:VXD'QdWoY-F$BtUwmfe$YqL'8(PWX("
    "P?^@Po3$##`MSs?DWBZ/S>+4%>fX,VWv/w'KD`LP5IbH;rTV>n3cEK8U#bX]l-/V+^lj3;vlMb&[5YQ8#pekX9JP3XUC72L,,?+Ni&co7ApnO*5NK,((W-i:$,kp'UDAO(G0Sq7MVjJs"
    "bIu)'Z,*[>br5fX^:FPAWr-m2KgL<LUN098kTF&#lvo58=/vjDo;.;)Ka*hLR#/k=rKbxuV`>Q_nN6'8uTG&#1T5g)uLv:873UpTLgH+#FgpH'_o1780Ph8KmxQJ8#H72L4@768@Tm&Q"
    "h4CB/5OvmA&,Q&QbUoi$a_%3M01H)4x7I^&KQVgtFnV+;[Pc>[m4k//,]1?#`VY[Jr*3&&slRfLiVZJ:]?=K3Sw=[$=uRB?3xk48@aeg<Z'<$#4H)6,>e0jT6'N#(q%.O=?2S]u*(m<-"
    "V8J'(1)G][68hW$5'q[GC&5j`TE?m'esFGNRM)j,ffZ?-qx8;->g4t*:CIP/[Qap7/9'#(1sao7w-.qNUdkJ)tCF&#B^;xGvn2r9FEPFFFcL@.iFNkTve$m%#QvQS8U@)2Z+3K:AKM5i"
    "sZ88+dKQ)W6>J%CL<KE>`.d*(B`-n8D9oK<Up]c$X$(,)M8Zt7/[rdkqTgl-0cuGMv'?>-XV1q['-5k'cAZ69e;D_?$ZPP&s^+7])$*$#@QYi9,5P&#9r+$%CE=68>K8r0=dSC%%(@p7"
    ".m7jilQ02'0-VWAg<a/''3u.=4L$Y)6k/K:_[3=&jvL<L0C/2'v:^;-DIBW,B4E68:kZ;%?8(Q8BH=kO65BW?xSG&#@uU,DS*,?.+(o(#1vCS8#CHF>TlGW'b)Tq7VT9q^*^$$.:&N@@"
    "$&)WHtPm*5_rO0&e%K&#-30j(E4#'Zb.o/(Tpm$>K'f@[PvFl,hfINTNU6u'0pao7%XUp9]5.>%h`8_=VYbxuel.NTSsJfLacFu3B'lQSu/m6-Oqem8T+oE--$0a/k]uj9EwsG>%veR*"
    "hv^BFpQj:K'#SJ,sB-'#](j.Lg92rTw-*n%@/;39rrJF,l#qV%OrtBeC6/,;qB3ebNW[?,Hqj2L.1NP&GjUR=1D8QaS3Up&@*9wP?+lo7b?@%'k4`p0Z$22%K3+iCZj?XJN4Nm&+YF]u"
    "@-W$U%VEQ/,,>>#)D<h#`)h0:<Q6909ua+&VU%n2:cG3FJ-%@Bj-DgLr`Hw&HAKjKjseK</xKT*)B,N9X3]krc12t'pgTV(Lv-tL[xg_%=M_q7a^x?7Ubd>#%8cY#YZ?=,`Wdxu/ae&#"
    "w6)R89tI#6@s'(6Bf7a&?S=^ZI_kS&ai`&=tE72L_D,;^R)7[$s<Eh#c&)q.MXI%#v9ROa5FZO%sF7q7Nwb&#ptUJ:aqJe$Sl68%.D###EC><?-aF&#RNQv>o8lKN%5/$(vdfq7+ebA#"
    "u1p]ovUKW&Y%q]'>$1@-[xfn$7ZTp7mM,G,Ko7a&Gu%G[RMxJs[0MM%wci.LFDK)(<c`Q8N)jEIF*+?P2a8g%)$q]o2aH8C&<SibC/q,(e:v;-b#6[$NtDZ84Je2KNvB#$P5?tQ3nt(0"
    "d=j.LQf./Ll33+(;q3L-w=8dX$#WF&uIJ@-bfI>%:_i2B5CsR8&9Z&#=mPEnm0f`<&c)QL5uJ#%u%lJj+D-r;BoF&#4DoS97h5g)E#o:&S4weDF,9^Hoe`h*L+_a*NrLW-1pG_&2UdB8"
    "6e%B/:=>)N4xeW.*wft-;$'58-ESqr<b?UI(_%@[P46>#U`'6AQ]m&6/`Z>#S?YY#Vc;r7U2&326d=w&H####?TZ`*4?&.MK?LP8Vxg>$[QXc%QJv92.(Db*B)gb*BM9dM*hJMAo*c&#"
    "b0v=Pjer]$gG&JXDf->'StvU7505l9$AFvgYRI^&<^b68?j#q9QX4SM'RO#&sL1IM.rJfLUAj221]d##DW=m83u5;'bYx,*Sl0hL(W;;$doB&O/TQ:(Z^xBdLjL<Lni;''X.`$#8+1GD"
    ":k$YUWsbn8ogh6rxZ2Z9]%nd+>V#*8U_72Lh+2Q8Cj0i:6hp&$C/:p(HK>T8Y[gHQ4`4)'$Ab(Nof%V'8hL&#<NEdtg(n'=S1A(Q1/I&4([%dM`,Iu'1:_hL>SfD07&6D<fp8dHM7/g+"
    "tlPN9J*rKaPct&?'uBCem^jn%9_K)<,C5K3s=5g&GmJb*[SYq7K;TRLGCsM-$$;S%:Y@r7AK0pprpL<Lrh,q7e/%KWK:50I^+m'vi`3?%Zp+<-d+$L-Sv:@.o19n$s0&39;kn;S%BSq*"
    "$3WoJSCLweV[aZ'MQIjO<7;X-X;&+dMLvu#^UsGEC9WEc[X(wI7#2.(F0jV*eZf<-Qv3J-c+J5AlrB#$p(H68LvEA'q3n0#m,[`*8Ft)FcYgEud]CWfm68,(aLA$@EFTgLXoBq/UPlp7"
    ":d[/;r_ix=:TF`S5H-b<LI&HY(K=h#)]Lk$K14lVfm:x$H<3^Ql<M`$OhapBnkup'D#L$Pb_`N*g]2e;X/Dtg,bsj&K#2[-:iYr'_wgH)NUIR8a1n#S?Yej'h8^58UbZd+^FKD*T@;6A"
    "7aQC[K8d-(v6GI$x:T<&'Gp5Uf>@M.*J:;$-rv29'M]8qMv-tLp,'886iaC=Hb*YJoKJ,(j%K=H`K.v9HggqBIiZu'QvBT.#=)0ukruV&.)3=(^1`o*Pj4<-<aN((^7('#Z0wK#5GX@7"
    "u][`*S^43933A4rl][`*O4CgLEl]v$1Q3AeF37dbXk,.)vj#x'd`;qgbQR%FW,2(?LO=s%Sc68%NP'##Aotl8x=BE#j1UD([3$M(]UI2LX3RpKN@;/#f'f/&_mt&F)XdF<9t4)Qa.*kT"
    "LwQ'(TTB9.xH'>#MJ+gLq9-##@HuZPN0]u:h7.T..G:;$/Usj(T7`Q8tT72LnYl<-qx8;-HV7Q-&Xdx%1a,hC=0u+HlsV>nuIQL-5<N?)NBS)QN*_I,?&)2'IM%L3I)X((e/dl2&8'<M"
    ":^#M*Q+[T.Xri.LYS3v%fF`68h;b-X[/En'CR.q7E)p'/kle2HM,u;^%OKC-N+Ll%F9CF<Nf'^#t2L,;27W:0O@6##U6W7:$rJfLWHj$#)woqBefIZ.PK<b*t7ed;p*_m;4ExK#h@&]>"
    "_>@kXQtMacfD.m-VAb8;IReM3$wf0''hra*so568'Ip&vRs849'MRYSp%:t:h5qSgwpEr$B>Q,;s(C#$)`svQuF$##-D,##,g68@2[T;.XSdN9Qe)rpt._K-#5wF)sP'##p#C0c%-Gb%"
    "hd+<-j'Ai*x&&HMkT]C'OSl##5RG[JXaHN;d'uA#x._U;.`PU@(Z3dt4r152@:v,'R.Sj'w#0<-;kPI)FfJ&#AYJ&#//)>-k=m=*XnK$>=)72L]0I%>.G690a:$##<,);?;72#?x9+d;"
    "^V'9;jY@;)br#q^YQpx:X#Te$Z^'=-=bGhLf:D6&bNwZ9-ZD#n^9HhLMr5G;']d&6'wYmTFmL<LD)F^%[tC'8;+9E#C$g%#5Y>q9wI>P(9mI[>kC-ekLC/R&CH+s'B;K-M6$EB%is00:"
    "+A4[7xks.LrNk0&E)wILYF@2L'0Nb$+pv<(2.768/FrY&h$^3i&@+G%JT'<-,v`3;_)I9M^AE]CN?Cl2AZg+%4iTpT3<n-&%H%b<FDj2M<hH=&Eh<2Len$b*aTX=-8QxN)k11IM1c^j%"
    "9s<L<NFSo)B?+<-(GxsF,^-Eh@$4dXhN$+#rxK8'je'D7k`e;)2pYwPA'_p9&@^18ml1^[@g4t*[JOa*[=Qp7(qJ_oOL^('7fB&Hq-:sf,sNj8xq^>$U4O]GKx'm9)b@p7YsvK3w^YR-"
    "CdQ*:Ir<($u&)#(&?L9Rg3H)4fiEp^iI9O8KnTj,]H?D*r7'M;PwZ9K0E^k&-cpI;.p/6_vwoFMV<->#%Xi.LxVnrU(4&8/P+:hLSKj$#U%]49t'I:rgMi'FL@a:0Y-uA[39',(vbma*"
    "hU%<-SRF`Tt:542R_VV$p@[p8DV[A,?1839FWdF<TddF<9Ah-6&9tWoDlh]&1SpGMq>Ti1O*H&#(AL8[_P%.M>v^-))qOT*F5Cq0`Ye%+$B6i:7@0IX<N+T+0MlMBPQ*Vj>SsD<U4JHY"
    "8kD2)2fU/M#$e.)T4,_=8hLim[&);?UkK'-x?'(:siIfL<$pFM`i<?%W(mGDHM%>iWP,##P`%/L<eXi:@Z9C.7o=@(pXdAO/NLQ8lPl+HPOQa8wD8=^GlPa8TKI1CjhsCTSLJM'/Wl>-"
    "S(qw%sf/@%#B6;/U7K]uZbi^Oc^2n<bhPmUkMw>%t<)'mEVE''n`WnJra$^TKvX5B>;_aSEK',(hwa0:i4G?.Bci.(X[?b*($,=-n<.Q%`(X=?+@Am*Js0&=3bh8K]mL<LoNs'6,'85`"
    "0?t/'_U59@]ddF<#LdF<eWdF<OuN/45rY<-L@&#+fm>69=Lb,OcZV/);TTm8VI;?%OtJ<(b4mq7M6:u?KRdF<gR@2L=FNU-<b[(9c/ML3m;Z[$oF3g)GAWqpARc=<ROu7cL5l;-[A]%/"
    "+fsd;l#SafT/f*W]0=O'$(Tb<[)*@e775R-:Yob%g*>l*:xP?Yb.5)%w_I?7uk5JC+FS(m#i'k.'a0i)9<7b'fs'59hq$*5Uhv##pi^8+hIEBF`nvo`;'l0.^S1<-wUK2/Coh58KKhLj"
    "M=SO*rfO`+qC`W-On.=AJ56>>i2@2LH6A:&5q`?9I3@@'04&p2/LVa*T-4<-i3;M9UvZd+N7>b*eIwg:CC)c<>nO&#<IGe;__.thjZl<%w(Wk2xmp4Q@I#I9,DF]u7-P=.-_:YJ]aS@V"
    "?6*C()dOp7:WL,b&3Rg/.cmM9&r^>$(>.Z-I&J(Q0Hd5Q%7Co-b`-c<N(6r@ip+AurK<m86QIth*#v;-OBqi+L7wDE-Ir8K['m+DDSLwK&/.?-V%U_%3:qKNu$_b*B-kp7NaD'QdWQPK"
    "Yq[@>P)hI;*_F]u`Rb[.j8_Q/<&>uu+VsH$sM9TA%?)(vmJ80),P7E>)tjD%2L=-t#fK[%`v=Q8<FfNkgg^oIbah*#8/Qt$F&:K*-(N/'+1vMB,u()-a.VUU*#[e%gAAO(S>WlA2);Sa"
    ">gXm8YB`1d@K#n]76-a$U,mF<fX]idqd)<3,]J7JmW4`6]uks=4-72L(jEk+:bJ0M^q-8Dm_Z?0olP1C9Sa&H[d&c$ooQUj]Exd*3ZM@-WGW2%s',B-_M%>%Ul:#/'xoFM9QX-$.QN'>"
    "[%$Z$uF6pA6Ki2O5:8w*vP1<-1`[G,)-m#>0`P&#eb#.3i)rtB61(o'$?X3B</R90;eZ]%Ncq;-Tl]#F>2Qft^ae_5tKL9MUe9b*sLEQ95C&`=G?@Mj=wh*'3E>=-<)Gt*Iw)'QG:`@I"
    "wOf7&]1i'S01B+Ev/Nac#9S;=;YQpg_6U`*kVY39xK,[/6Aj7:'1Bm-_1EYfa1+o&o4hp7KN_Q(OlIo@S%;jVdn0'1<Vc52=u`3^o-n1'g4v58Hj&6_t7$##?M)c<$bgQ_'SY((-xkA#"
    "Y(,p'H9rIVY-b,'%bCPF7.J<Up^,(dU1VY*5#WkTU>h19w,WQhLI)3S#f$2(eb,jr*b;3Vw]*7NH%$c4Vs,eD9>XW8?N]o+(*pgC%/72LV-u<Hp,3@e^9UB1J+ak9-TN/mhKPg+AJYd$"
    "MlvAF_jCK*.O-^(63adMT->W%iewS8W6m2rtCpo'RS1R84=@paTKt)>=%&1[)*vp'u+x,VrwN;&]kuO9JDbg=pO$J*.jVe;u'm0dr9l,<*wMK*Oe=g8lV_KEBFkO'oU]^=[-792#ok,)"
    "i]lR8qQ2oA8wcRCZ^7w/Njh;?.stX?Q1>S1q4Bn$)K1<-rGdO'$Wr.Lc.CG)$/*JL4tNR/,SVO3,aUw'DJN:)Ss;wGn9A32ijw%FL+Z0Fn.U9;reSq)bmI32U==5ALuG&#Vf1398/pVo"
    "1*c-(aY168o<`JsSbk-,1N;$>0:OUas(3:8Z972LSfF8eb=c-;>SPw7.6hn3m`9^Xkn(r.qS[0;T%&Qc=+STRxX'q1BNk3&*eu2;&8q$&x>Q#Q7^Tf+6<(d%ZVmj2bDi%.3L2n+4W'$P"
    "iDDG)g,r%+?,$@?uou5tSe2aN_AQU*<h`e-GI7)?OK2A.d7_c)?wQ5AS@DL3r#7fSkgl6-++D:'A,uq7SvlB$pcpH'q3n0#_%dY#xCpr-l<F0NR@-##FEV6NTF6##$l84N1w?AO>'IAO"
    "URQ##V^Fv-XFbGM7Fl(N<3DhLGF%q.1rC$#:T__&Pi68%0xi_&[qFJ(77j_&JWoF.V735&T,[R*:xFR*K5>>#`bW-?4Ne_&6Ne_&6Ne_&n`kr-#GJcM6X;uM6X;uM(.a..^2TkL%oR(#"
    ";u.T%fAr%4tJ8&><1=GHZ_+m9/#H1F^R#SC#*N=BA9(D?v[UiFY>>^8p,KKF.W]L29uLkLlu/+4T<XoIB&hx=T1PcDaB&;HH+-AFr?(m9HZV)FKS8JCw;SD=6[^/DZUL`EUDf]GGlG&>"
    "w$)F./^n3+rlo+DB;5sIYGNk+i1t-69Jg--0pao7Sm#K)pdHW&;LuDNH@H>#/X-TI(;P>#,Gc>#0Su>#4`1?#8lC?#<xU?#@.i?#D:%@#HF7@#LRI@#P_[@#Tkn@#Xw*A#]-=A#a9OA#"
    "d<F&#*;G##.GY##2Sl##6`($#:l:$#>xL$#B.`$#F:r$#JF.%#NR@%#R_R%#Vke%#Zww%#_-4&#3^Rh%Sflr-k'MS.o?.5/sWel/wpEM0%3'/1)K^f1-d>G21&v(35>V`39V7A4=onx4"
    "A1OY5EI0;6Ibgr6M$HS7Q<)58C5w,;WoA*#[%T*#`1g*#d=#+#hI5+#lUG+#pbY+#tnl+#x$),#&1;,#*=M,#.I`,#2Ur,#6b.-#;w[H#iQtA#m^0B#qjBB#uvTB##-hB#'9$C#+E6C#"
    "/QHC#3^ZC#7jmC#;v)D#?,<D#C8ND#GDaD#KPsD#O]/E#g1A5#KA*1#gC17#MGd;#8(02#L-d3#rWM4#Hga1#,<w0#T.j<#O#'2#CYN1#qa^:#_4m3#o@/=#eG8=#t8J5#`+78#4uI-#"
    "m3B2#SB[8#Q0@8#i[*9#iOn8#1Nm;#^sN9#qh<9#:=x-#P;K2#$%X9#bC+.#Rg;<#mN=.#MTF.#RZO.#2?)4#Y#(/#[)1/#b;L/#dAU/#0Sv;#lY$0#n`-0#sf60#(F24#wrH0#%/e0#"
    "TmD<#%JSMFove:CTBEXI:<eh2g)B,3h2^G3i;#d3jD>)4kMYD4lVu`4m`:&5niUA5@(A5BA1]PBB:xlBCC=2CDLXMCEUtiCf&0g2'tN?PGT4CPGT4CPGT4CPGT4CPGT4CPGT4CPGT4CP"
    "GT4CPGT4CPGT4CPGT4CPGT4CPGT4CP-qekC`.9kEg^+F$kwViFJTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5KTB&5o,^<-28ZI'O?;xp"
    "O?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xpO?;xp;7q-#lLYI:xvD=#";

#ifdef __clang__
#pragma clang diagnostic pop
#elif defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#endif /* NK_INCLUDE_DEFAULT_FONT */

NK_INTERN unsigned int
nk_decompress_length(unsigned char *input)
{
    return (unsigned int)((input[8] << 24) + (input[9] << 16) + (input[10] << 8) + input[11]);
}

NK_GLOBAL unsigned char *nk__barrier;
NK_GLOBAL unsigned char *nk__barrier2;
NK_GLOBAL unsigned char *nk__barrier3;
NK_GLOBAL unsigned char *nk__barrier4;
NK_GLOBAL unsigned char *nk__dout;

NK_INTERN void
nk__match(unsigned char *data, unsigned int length)
{
    /* INVERSE of memmove... write each byte before copying the next...*/
    NK_ASSERT (nk__dout + length <= nk__barrier);
    if (nk__dout + length > nk__barrier) { nk__dout += length; return; }
    if (data < nk__barrier4) { nk__dout = nk__barrier+1; return; }
    while (length--) *nk__dout++ = *data++;
}

NK_INTERN void
nk__lit(unsigned char *data, unsigned int length)
{
    NK_ASSERT (nk__dout + length <= nk__barrier);
    if (nk__dout + length > nk__barrier) { nk__dout += length; return; }
    if (data < nk__barrier2) { nk__dout = nk__barrier+1; return; }
    NK_MEMCPY(nk__dout, data, length);
    nk__dout += length;
}

#define nk__in2(x)   ((i[x] << 8) + i[(x)+1])
#define nk__in3(x)   ((i[x] << 16) + nk__in2((x)+1))
#define nk__in4(x)   ((i[x] << 24) + nk__in3((x)+1))

NK_INTERN unsigned char*
nk_decompress_token(unsigned char *i)
{
    if (*i >= 0x20) { /* use fewer if's for cases that expand small */
        if (*i >= 0x80)       nk__match(nk__dout-i[1]-1, (unsigned int)i[0] - 0x80 + 1), i += 2;
        else if (*i >= 0x40)  nk__match(nk__dout-(nk__in2(0) - 0x4000 + 1), (unsigned int)i[2]+1), i += 3;
        else /* *i >= 0x20 */ nk__lit(i+1, (unsigned int)i[0] - 0x20 + 1), i += 1 + (i[0] - 0x20 + 1);
    } else { /* more ifs for cases that expand large, since overhead is amortized */
        if (*i >= 0x18)       nk__match(nk__dout-(unsigned int)(nk__in3(0) - 0x180000 + 1), (unsigned int)i[3]+1), i += 4;
        else if (*i >= 0x10)  nk__match(nk__dout-(unsigned int)(nk__in3(0) - 0x100000 + 1), (unsigned int)nk__in2(3)+1), i += 5;
        else if (*i >= 0x08)  nk__lit(i+2, (unsigned int)nk__in2(0) - 0x0800 + 1), i += 2 + (nk__in2(0) - 0x0800 + 1);
        else if (*i == 0x07)  nk__lit(i+3, (unsigned int)nk__in2(1) + 1), i += 3 + (nk__in2(1) + 1);
        else if (*i == 0x06)  nk__match(nk__dout-(unsigned int)(nk__in3(1)+1), i[4]+1u), i += 5;
        else if (*i == 0x04)  nk__match(nk__dout-(unsigned int)(nk__in3(1)+1), (unsigned int)nk__in2(4)+1u), i += 6;
    }
    return i;
}

NK_INTERN unsigned int
nk_adler32(unsigned int adler32, unsigned char *buffer, unsigned int buflen)
{
    const unsigned long ADLER_MOD = 65521;
    unsigned long s1 = adler32 & 0xffff, s2 = adler32 >> 16;
    unsigned long blocklen, i;

    blocklen = buflen % 5552;
    while (buflen) {
        for (i=0; i + 7 < blocklen; i += 8) {
            s1 += buffer[0], s2 += s1;
            s1 += buffer[1], s2 += s1;
            s1 += buffer[2], s2 += s1;
            s1 += buffer[3], s2 += s1;
            s1 += buffer[4], s2 += s1;
            s1 += buffer[5], s2 += s1;
            s1 += buffer[6], s2 += s1;
            s1 += buffer[7], s2 += s1;

            buffer += 8;
        }

        for (; i < blocklen; ++i)
            s1 += *buffer++, s2 += s1;

        s1 %= ADLER_MOD, s2 %= ADLER_MOD;
        buflen -= (unsigned int)blocklen;
        blocklen = 5552;
    }
    return (unsigned int)(s2 << 16) + (unsigned int)s1;
}

NK_INTERN unsigned int
nk_decompress(unsigned char *output, unsigned char *i, unsigned int length)
{
    unsigned int olen;
    if (nk__in4(0) != 0x57bC0000) return 0;
    if (nk__in4(4) != 0)          return 0; /* error! stream is > 4GB */
    olen = nk_decompress_length(i);
    nk__barrier2 = i;
    nk__barrier3 = i+length;
    nk__barrier = output + olen;
    nk__barrier4 = output;
    i += 16;

    nk__dout = output;
    for (;;) {
        unsigned char *old_i = i;
        i = nk_decompress_token(i);
        if (i == old_i) {
            if (*i == 0x05 && i[1] == 0xfa) {
                NK_ASSERT(nk__dout == output + olen);
                if (nk__dout != output + olen) return 0;
                if (nk_adler32(1, output, olen) != (unsigned int) nk__in4(2))
                    return 0;
                return olen;
            } else {
                NK_ASSERT(0); /* NOTREACHED */
                return 0;
            }
        }
        NK_ASSERT(nk__dout <= output + olen);
        if (nk__dout > output + olen)
            return 0;
    }
}

NK_INTERN unsigned int
nk_decode_85_byte(char c)
{ return (unsigned int)((c >= '\\') ? c-36 : c-35); }

NK_INTERN void
nk_decode_85(unsigned char* dst, const unsigned char* src)
{
    while (*src)
    {
        unsigned int tmp =
            nk_decode_85_byte((char)src[0]) +
            85 * (nk_decode_85_byte((char)src[1]) +
            85 * (nk_decode_85_byte((char)src[2]) +
            85 * (nk_decode_85_byte((char)src[3]) +
            85 * nk_decode_85_byte((char)src[4]))));

        /* we can't assume little-endianess. */
        dst[0] = (unsigned char)((tmp >> 0) & 0xFF);
        dst[1] = (unsigned char)((tmp >> 8) & 0xFF);
        dst[2] = (unsigned char)((tmp >> 16) & 0xFF);
        dst[3] = (unsigned char)((tmp >> 24) & 0xFF);

        src += 5;
        dst += 4;
    }
}

/* -------------------------------------------------------------
 *
 *                          FONT ATLAS
 *
 * --------------------------------------------------------------*/
NK_API struct nk_font_config
nk_font_config(float pixel_height)
{
    struct nk_font_config cfg;
    nk_zero_struct(cfg);
    cfg.ttf_blob = 0;
    cfg.ttf_size = 0;
    cfg.ttf_data_owned_by_atlas = 0;
    cfg.size = pixel_height;
    cfg.oversample_h = 3;
    cfg.oversample_v = 1;
    cfg.pixel_snap = 0;
    cfg.coord_type = NK_COORD_UV;
    cfg.spacing = nk_vec2(0,0);
    cfg.range = nk_font_default_glyph_ranges();
    cfg.fallback_glyph = '?';
    cfg.font = 0;
    cfg.merge_mode = 0;
    return cfg;
}

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void
nk_font_atlas_init_default(struct nk_font_atlas *atlas)
{
    NK_ASSERT(atlas);
    if (!atlas) return;
    nk_zero_struct(*atlas);
    atlas->alloc.userdata.ptr = 0;
    atlas->alloc.alloc = nk_malloc;
    atlas->alloc.free = nk_mfree;
}
#endif

NK_API void
nk_font_atlas_init(struct nk_font_atlas *atlas, struct nk_allocator *alloc)
{
    NK_ASSERT(atlas);
    NK_ASSERT(alloc);
    if (!atlas || !alloc) return;
    nk_zero_struct(*atlas);
    atlas->alloc = *alloc;
}

NK_API void
nk_font_atlas_begin(struct nk_font_atlas *atlas)
{
    NK_ASSERT(atlas);
    NK_ASSERT(atlas->alloc.alloc && atlas->alloc.free);
    if (!atlas || !atlas->alloc.alloc || !atlas->alloc.free) return;
    if (atlas->glyphs) {
        atlas->alloc.free(atlas->alloc.userdata, atlas->glyphs);
        atlas->glyphs = 0;
    }
    if (atlas->pixel) {
        atlas->alloc.free(atlas->alloc.userdata, atlas->pixel);
        atlas->pixel = 0;
    }
}

NK_API struct nk_font*
nk_font_atlas_add(struct nk_font_atlas *atlas, const struct nk_font_config *config)
{
    struct nk_font *font = 0;
    NK_ASSERT(atlas);
    NK_ASSERT(config);
    NK_ASSERT(atlas->alloc.alloc);
    NK_ASSERT(atlas->alloc.free);
    NK_ASSERT(config->ttf_blob);
    NK_ASSERT(config->ttf_size);
    NK_ASSERT(config->size > 0.0f);
    if (!atlas || !config || !config->ttf_blob || !config->ttf_size || config->size <= 0.0f||
        !atlas->alloc.alloc || !atlas->alloc.free)
        return 0;

    /* allocate new font */
    if (!config->merge_mode) {
        font = (struct nk_font*)atlas->alloc.alloc(atlas->alloc.userdata,0, sizeof(struct nk_font));
        NK_ASSERT(font);
        if (!font) return 0;
    } else {
        NK_ASSERT(atlas->font_num);
        font = atlas->fonts[atlas->font_num-1];
    }

    /* make sure enough memory */
    if (!atlas->config || atlas->font_num >= atlas->font_cap) {
        void *tmp_font, *tmp_config;
        atlas->font_cap = (!atlas->config) ? 32: (int)((float)atlas->font_cap * 2.7f);
        tmp_font = atlas->alloc.alloc(atlas->alloc.userdata,0,
                        ((nk_size)atlas->font_cap * sizeof(struct nk_font*)));
        tmp_config = atlas->alloc.alloc(atlas->alloc.userdata,0,
                        ((nk_size)atlas->font_cap * sizeof(struct nk_font_config)));

        if (!atlas->config) {
            atlas->fonts = (struct nk_font**)tmp_font;
            atlas->config = (struct nk_font_config*)tmp_config;
        } else {
            /* realloc */
            NK_MEMCPY(tmp_font, atlas->fonts,
                sizeof(struct nk_font*) * (nk_size)atlas->font_num);
            NK_MEMCPY(tmp_config, atlas->config,
                sizeof(struct nk_font_config) * (nk_size)atlas->font_num);

            atlas->alloc.free(atlas->alloc.userdata, atlas->fonts);
            atlas->alloc.free(atlas->alloc.userdata, atlas->config);

            atlas->fonts = (struct nk_font**)tmp_font;
            atlas->config = (struct nk_font_config*)tmp_config;
        }
    }

    /* add font and font config into atlas */
    atlas->config[atlas->font_num] = *config;
    if (!config->merge_mode) {
        atlas->fonts[atlas->font_num] = font;
        atlas->config[atlas->font_num].font = &font->info;
    }

    /* create own copy of .TTF font blob */
    if (!config->ttf_data_owned_by_atlas) {
        struct nk_font_config *c = &atlas->config[atlas->font_num];
        c->ttf_blob = atlas->alloc.alloc(atlas->alloc.userdata,0, c->ttf_size);
        NK_ASSERT(c->ttf_blob);
        if (!c->ttf_blob) {
            atlas->font_num++;
            return 0;
        }
        NK_MEMCPY(c->ttf_blob, config->ttf_blob, c->ttf_size);
        c->ttf_data_owned_by_atlas = 1;
    }
    atlas->font_num++;
    return font;
}

NK_API struct nk_font*
nk_font_atlas_add_from_memory(struct nk_font_atlas *atlas, void *memory,
    nk_size size, float height, const struct nk_font_config *config)
{
    struct nk_font_config cfg;
    NK_ASSERT(memory);
    NK_ASSERT(size);
    NK_ASSERT(atlas);
    NK_ASSERT(atlas->alloc.alloc);
    NK_ASSERT(atlas->alloc.free);
    if (!atlas || !atlas->alloc.alloc || !atlas->alloc.free || !memory || !size)
        return 0;

    cfg = (config) ? *config: nk_font_config(height);
    cfg.ttf_blob = memory;
    cfg.ttf_size = size;
    cfg.size = height;
    cfg.ttf_data_owned_by_atlas = 0;
    return nk_font_atlas_add(atlas, &cfg);
}

#ifdef NK_INCLUDE_STANDARD_IO
NK_API struct nk_font*
nk_font_atlas_add_from_file(struct nk_font_atlas *atlas, const char *file_path,
    float height, const struct nk_font_config *config)
{
    nk_size size;
    char *memory;
    struct nk_font_config cfg;

    NK_ASSERT(atlas);
    NK_ASSERT(atlas->alloc.alloc);
    NK_ASSERT(atlas->alloc.free);
    if (!atlas || !file_path) return 0;
    memory = nk_file_load(file_path, &size, &atlas->alloc);
    if (!memory) return 0;

    cfg = (config) ? *config: nk_font_config(height);
    cfg.ttf_blob = memory;
    cfg.ttf_size = size;
    cfg.size = height;
    cfg.ttf_data_owned_by_atlas = 1;
    return nk_font_atlas_add(atlas, &cfg);
}
#endif

NK_API struct nk_font*
nk_font_atlas_add_compressed(struct nk_font_atlas *atlas,
    void *compressed_data, nk_size compressed_size, float height,
    const struct nk_font_config *config)
{
    unsigned int decompressed_size;
    void *decompressed_data;
    struct nk_font_config cfg;

    NK_ASSERT(compressed_data);
    NK_ASSERT(compressed_size);
    NK_ASSERT(atlas);
    NK_ASSERT(atlas->alloc.alloc);
    NK_ASSERT(atlas->alloc.free);
    if (!atlas || !compressed_data || !atlas->alloc.alloc || !atlas->alloc.free)
        return 0;

    decompressed_size = nk_decompress_length((unsigned char*)compressed_data);
    decompressed_data = atlas->alloc.alloc(atlas->alloc.userdata,0,decompressed_size);
    NK_ASSERT(decompressed_data);
    if (!decompressed_data) return 0;
    nk_decompress((unsigned char*)decompressed_data, (unsigned char*)compressed_data,
        (unsigned int)compressed_size);

    cfg = (config) ? *config: nk_font_config(height);
    cfg.ttf_blob = decompressed_data;
    cfg.ttf_size = decompressed_size;
    cfg.size = height;
    cfg.ttf_data_owned_by_atlas = 1;
    return nk_font_atlas_add(atlas, &cfg);
}

NK_API struct nk_font*
nk_font_atlas_add_compressed_base85(struct nk_font_atlas *atlas,
    const char *data_base85, float height, const struct nk_font_config *config)
{
    int compressed_size;
    void *compressed_data;
    struct nk_font *font;

    NK_ASSERT(data_base85);
    NK_ASSERT(atlas);
    NK_ASSERT(atlas->alloc.alloc);
    NK_ASSERT(atlas->alloc.free);
    if (!atlas || !data_base85 || !atlas->alloc.alloc || !atlas->alloc.free)
        return 0;

    compressed_size = (((int)nk_strlen(data_base85) + 4) / 5) * 4;
    compressed_data = atlas->alloc.alloc(atlas->alloc.userdata,0, (nk_size)compressed_size);
    NK_ASSERT(compressed_data);
    if (!compressed_data) return 0;
    nk_decode_85((unsigned char*)compressed_data, (const unsigned char*)data_base85);
    font = nk_font_atlas_add_compressed(atlas, compressed_data,
                    (nk_size)compressed_size, height, config);
    atlas->alloc.free(atlas->alloc.userdata, compressed_data);
    return font;
}

#ifdef NK_INCLUDE_DEFAULT_FONT
NK_API struct nk_font*
nk_font_atlas_add_default(struct nk_font_atlas *atlas,
    float pixel_height, const struct nk_font_config *config)
{
    NK_ASSERT(atlas);
    NK_ASSERT(atlas->alloc.alloc);
    NK_ASSERT(atlas->alloc.free);
    return nk_font_atlas_add_compressed_base85(atlas,
        nk_proggy_clean_ttf_compressed_data_base85, pixel_height, config);
}
#endif

NK_API const void*
nk_font_atlas_bake(struct nk_font_atlas *atlas, int *width, int *height,
    enum nk_font_atlas_format fmt)
{
    int i = 0;
    void *tmp = 0;
    nk_size tmp_size, img_size;

    NK_ASSERT(width);
    NK_ASSERT(height);
    NK_ASSERT(atlas);
    NK_ASSERT(atlas->alloc.alloc);
    NK_ASSERT(atlas->alloc.free);
    if (!atlas || !width || !height || !atlas->alloc.alloc || !atlas->alloc.free)
        return 0;

#ifdef NK_INCLUDE_DEFAULT_FONT
    /* no font added so just use default font */
    if (!atlas->font_num)
        atlas->default_font = nk_font_atlas_add_default(atlas, 13.0f, 0);
#endif
    NK_ASSERT(atlas->font_num);
    if (!atlas->font_num) return 0;

    /* allocate temporary memory required for the baking process */
    nk_font_bake_memory(&tmp_size, &atlas->glyph_count, atlas->config, atlas->font_num);
    tmp = atlas->alloc.alloc(atlas->alloc.userdata,0, tmp_size);
    NK_ASSERT(tmp);
    if (!tmp) goto failed;

    /* allocate glyph memory for all fonts */
    atlas->glyphs = (struct nk_font_glyph*)
        atlas->alloc.alloc(atlas->alloc.userdata,0,
                sizeof(struct nk_font_glyph) * (nk_size)atlas->glyph_count);
    NK_ASSERT(atlas->glyphs);
    if (!atlas->glyphs)
        goto failed;

    /* pack all glyphs into a tight fit space */
    atlas->custom.w = 2; atlas->custom.h = 2;
    if (!nk_font_bake_pack(&img_size, width, height, &atlas->custom, tmp, tmp_size,
        atlas->config, atlas->font_num, &atlas->alloc))
        goto failed;

    /* allocate memory for the baked image font atlas */
    atlas->pixel = atlas->alloc.alloc(atlas->alloc.userdata,0, img_size);
    NK_ASSERT(atlas->pixel);
    if (!atlas->pixel)
        goto failed;

    /* bake glyphs and custom white pixel into image */
    {const char *custom_data = "....";
    nk_font_bake(atlas->pixel, *width, *height, tmp, tmp_size, atlas->glyphs,
        atlas->glyph_count, atlas->config, atlas->font_num);
    nk_font_bake_custom_data(atlas->pixel, *width, *height, atlas->custom,
            custom_data, 2, 2, '.', 'X');}

    /* convert alpha8 image into rgba32 image */
    if (fmt == NK_FONT_ATLAS_RGBA32) {
        void *img_rgba = atlas->alloc.alloc(atlas->alloc.userdata,0,
                            (nk_size)(*width * *height * 4));
        NK_ASSERT(img_rgba);
        if (!img_rgba) goto failed;
        nk_font_bake_convert(img_rgba, *width, *height, atlas->pixel);
        atlas->alloc.free(atlas->alloc.userdata, atlas->pixel);
        atlas->pixel = img_rgba;
    }
    atlas->tex_width = *width;
    atlas->tex_height = *height;

    /* initialize each font */
    for (i = 0; i < atlas->font_num; ++i) {
        nk_font_init(atlas->fonts[i], atlas->config[i].size,
            atlas->config[i].fallback_glyph, atlas->glyphs,
            atlas->config[i].font, nk_handle_ptr(0));
    }

    /* free temporary memory */
    atlas->alloc.free(atlas->alloc.userdata, tmp);
    return atlas->pixel;

failed:
    /* error so cleanup all memory */
    if (tmp) atlas->alloc.free(atlas->alloc.userdata, tmp);
    if (atlas->glyphs) {
        atlas->alloc.free(atlas->alloc.userdata, atlas->glyphs);
        atlas->glyphs = 0;
    }
    if (atlas->pixel) {
        atlas->alloc.free(atlas->alloc.userdata, atlas->pixel);
        atlas->pixel = 0;
    }
    return 0;
}

NK_API void
nk_font_atlas_end(struct nk_font_atlas *atlas, nk_handle texture,
    struct nk_draw_null_texture *null)
{
    int i = 0;
    NK_ASSERT(atlas);
    if (!atlas) {
        if (!null) return;
        null->texture = texture;
        null->uv = nk_vec2(0.5f,0.5f);
    }
    if (null) {
        null->texture = texture;
        null->uv = nk_vec2((atlas->custom.x + 0.5f)/(float)atlas->tex_width,
            (atlas->custom.y + 0.5f)/(float)atlas->tex_height);
    }
    for (i = 0; i < atlas->font_num; ++i) {
        atlas->fonts[i]->texture = texture;
        atlas->fonts[i]->handle.texture = texture;
    }

    atlas->alloc.free(atlas->alloc.userdata, atlas->pixel);
    atlas->pixel = 0;
    atlas->tex_width = 0;
    atlas->tex_height = 0;
    atlas->custom.x = 0;
    atlas->custom.y = 0;
    atlas->custom.w = 0;
    atlas->custom.h = 0;
}

NK_API void
nk_font_atlas_clear(struct nk_font_atlas *atlas)
{
    int i = 0;
    NK_ASSERT(atlas);
    NK_ASSERT(atlas->alloc.alloc);
    NK_ASSERT(atlas->alloc.free);
    if (!atlas || !atlas->alloc.alloc || !atlas->alloc.free)
        return;

    if (atlas->fonts) {
        for (i = 0; i < atlas->font_num; ++i)
            atlas->alloc.free(atlas->alloc.userdata, atlas->fonts[i]);
        atlas->alloc.free(atlas->alloc.userdata, atlas->fonts);
    }
    if (atlas->config) {
        for (i = 0; i < atlas->font_num; ++i)
            atlas->alloc.free(atlas->alloc.userdata, atlas->config[i].ttf_blob);
        atlas->alloc.free(atlas->alloc.userdata, atlas->config);
    }
    if (atlas->glyphs)
        atlas->alloc.free(atlas->alloc.userdata, atlas->glyphs);
    if (atlas->pixel)
        atlas->alloc.free(atlas->alloc.userdata, atlas->pixel);
    nk_zero_struct(*atlas);
}
#endif
/* ==============================================================
 *
 *                          INPUT
 *
 * ===============================================================*/
NK_API void
nk_input_begin(struct nk_context *ctx)
{
    int i;
    struct nk_input *in;
    NK_ASSERT(ctx);
    if (!ctx) return;

    in = &ctx->input;
    for (i = 0; i < NK_BUTTON_MAX; ++i)
        in->mouse.buttons[i].clicked = 0;
    in->keyboard.text_len = 0;
    in->mouse.scroll_delta = 0;
    in->mouse.prev.x = in->mouse.pos.x;
    in->mouse.prev.y = in->mouse.pos.y;
    in->mouse.delta.x = 0;
    in->mouse.delta.y = 0;
    for (i = 0; i < NK_KEY_MAX; i++)
        in->keyboard.keys[i].clicked = 0;
}

NK_API void
nk_input_end(struct nk_context *ctx)
{
    struct nk_input *in;
    NK_ASSERT(ctx);
    if (!ctx) return;
    in = &ctx->input;
    if (in->mouse.grab)
        in->mouse.grab = 0;
    if (in->mouse.ungrab) {
        in->mouse.grabbed = 0;
        in->mouse.ungrab = 0;
        in->mouse.grab = 0;
    }
    if (in->mouse.grabbed) {
        in->mouse.pos.x = in->mouse.prev.x;
        in->mouse.pos.y = in->mouse.prev.y;
    }
}

NK_API void
nk_input_motion(struct nk_context *ctx, int x, int y)
{
    struct nk_input *in;
    NK_ASSERT(ctx);
    if (!ctx) return;
    in = &ctx->input;
    in->mouse.pos.x = (float)x;
    in->mouse.pos.y = (float)y;
    in->mouse.delta = nk_vec2_sub(in->mouse.pos, in->mouse.prev);
}

NK_API void
nk_input_key(struct nk_context *ctx, enum nk_keys key, int down)
{
    struct nk_input *in;
    NK_ASSERT(ctx);
    if (!ctx) return;
    in = &ctx->input;
    if (in->keyboard.keys[key].down == down) return;
    in->keyboard.keys[key].down = down;
    in->keyboard.keys[key].clicked++;
}

NK_API void
nk_input_button(struct nk_context *ctx, enum nk_buttons id, int x, int y, int down)
{
    struct nk_mouse_button *btn;
    struct nk_input *in;
    NK_ASSERT(ctx);
    if (!ctx) return;
    in = &ctx->input;
    if (in->mouse.buttons[id].down == down) return;

    btn = &in->mouse.buttons[id];
    btn->clicked_pos.x = (float)x;
    btn->clicked_pos.y = (float)y;
    btn->down = down;
    btn->clicked++;
}

NK_API void
nk_input_scroll(struct nk_context *ctx, float y)
{
    NK_ASSERT(ctx);
    if (!ctx) return;
    ctx->input.mouse.scroll_delta += y;
}

NK_API void
nk_input_glyph(struct nk_context *ctx, const nk_glyph glyph)
{
    int len = 0;
    nk_rune unicode;

    struct nk_input *in;
    NK_ASSERT(ctx);
    if (!ctx) return;
    in = &ctx->input;

    len = nk_utf_decode(glyph, &unicode, NK_UTF_SIZE);
    if (len && ((in->keyboard.text_len + len) < NK_INPUT_MAX)) {
        nk_utf_encode(unicode, &in->keyboard.text[in->keyboard.text_len],
            NK_INPUT_MAX - in->keyboard.text_len);
        in->keyboard.text_len += len;
    }
}

NK_API void
nk_input_char(struct nk_context *ctx, char c)
{
    nk_glyph glyph;
    NK_ASSERT(ctx);
    if (!ctx) return;
    glyph[0] = c;
    nk_input_glyph(ctx, glyph);
}

NK_API void
nk_input_unicode(struct nk_context *ctx, nk_rune unicode)
{
    nk_glyph rune;
    NK_ASSERT(ctx);
    if (!ctx) return;
    nk_utf_encode(unicode, rune, NK_UTF_SIZE);
    nk_input_glyph(ctx, rune);
}

NK_API int
nk_input_has_mouse_click(const struct nk_input *i, enum nk_buttons id)
{
    const struct nk_mouse_button *btn;
    if (!i) return nk_false;
    btn = &i->mouse.buttons[id];
    return (btn->clicked && btn->down == nk_false) ? nk_true : nk_false;
}

NK_API int
nk_input_has_mouse_click_in_rect(const struct nk_input *i, enum nk_buttons id,
    struct nk_rect b)
{
    const struct nk_mouse_button *btn;
    if (!i) return nk_false;
    btn = &i->mouse.buttons[id];
    if (!NK_INBOX(btn->clicked_pos.x,btn->clicked_pos.y,b.x,b.y,b.w,b.h))
        return nk_false;
    return nk_true;
}

NK_API int
nk_input_has_mouse_click_down_in_rect(const struct nk_input *i, enum nk_buttons id,
    struct nk_rect b, int down)
{
    const struct nk_mouse_button *btn;
    if (!i) return nk_false;
    btn = &i->mouse.buttons[id];
    return nk_input_has_mouse_click_in_rect(i, id, b) && (btn->down == down);
}

NK_API int
nk_input_is_mouse_click_in_rect(const struct nk_input *i, enum nk_buttons id,
    struct nk_rect b)
{
    const struct nk_mouse_button *btn;
    if (!i) return nk_false;
    btn = &i->mouse.buttons[id];
    return (nk_input_has_mouse_click_down_in_rect(i, id, b, nk_false) &&
            btn->clicked) ? nk_true : nk_false;
}

NK_API int
nk_input_is_mouse_click_down_in_rect(const struct nk_input *i, enum nk_buttons id,
    struct nk_rect b, int down)
{
    const struct nk_mouse_button *btn;
    if (!i) return nk_false;
    btn = &i->mouse.buttons[id];
    return (nk_input_has_mouse_click_down_in_rect(i, id, b, down) &&
            btn->clicked) ? nk_true : nk_false;
}

NK_API int
nk_input_any_mouse_click_in_rect(const struct nk_input *in, struct nk_rect b)
{
    int i, down = 0;
    for (i = 0; i < NK_BUTTON_MAX; ++i)
        down = down || nk_input_is_mouse_click_in_rect(in, (enum nk_buttons)i, b);
    return down;
}

NK_API int
nk_input_is_mouse_hovering_rect(const struct nk_input *i, struct nk_rect rect)
{
    if (!i) return nk_false;
    return NK_INBOX(i->mouse.pos.x, i->mouse.pos.y, rect.x, rect.y, rect.w, rect.h);
}

NK_API int
nk_input_is_mouse_prev_hovering_rect(const struct nk_input *i, struct nk_rect rect)
{
    if (!i) return nk_false;
    return NK_INBOX(i->mouse.prev.x, i->mouse.prev.y, rect.x, rect.y, rect.w, rect.h);
}

NK_API int
nk_input_mouse_clicked(const struct nk_input *i, enum nk_buttons id, struct nk_rect rect)
{
    if (!i) return nk_false;
    if (!nk_input_is_mouse_hovering_rect(i, rect)) return nk_false;
    return nk_input_is_mouse_click_in_rect(i, id, rect);
}

NK_API int
nk_input_is_mouse_down(const struct nk_input *i, enum nk_buttons id)
{
    if (!i) return nk_false;
    return i->mouse.buttons[id].down;
}

NK_API int
nk_input_is_mouse_pressed(const struct nk_input *i, enum nk_buttons id)
{
    const struct nk_mouse_button *b;
    if (!i) return nk_false;
    b = &i->mouse.buttons[id];
    if (b->down && b->clicked)
        return nk_true;
    return nk_false;
}

NK_API int
nk_input_is_mouse_released(const struct nk_input *i, enum nk_buttons id)
{
    if (!i) return nk_false;
    return (!i->mouse.buttons[id].down && i->mouse.buttons[id].clicked);
}

NK_API int
nk_input_is_key_pressed(const struct nk_input *i, enum nk_keys key)
{
    const struct nk_key *k;
    if (!i) return nk_false;
    k = &i->keyboard.keys[key];
    if (k->down && k->clicked)
        return nk_true;
    return nk_false;
}

NK_API int
nk_input_is_key_released(const struct nk_input *i, enum nk_keys key)
{
    const struct nk_key *k;
    if (!i) return nk_false;
    k = &i->keyboard.keys[key];
    if (!k->down && k->clicked)
        return nk_true;
    return nk_false;
}

NK_API int
nk_input_is_key_down(const struct nk_input *i, enum nk_keys key)
{
    const struct nk_key *k;
    if (!i) return nk_false;
    k = &i->keyboard.keys[key];
    if (k->down) return nk_true;
    return nk_false;
}

/*
 * ==============================================================
 *
 *                          TEXT EDITOR
 *
 * ===============================================================
 */
/* stb_textedit.h - v1.8  - public domain - Sean Barrett */
struct nk_text_find {
   float x,y;    /* position of n'th character */
   float height; /* height of line */
   int first_char, length; /* first char of row, and length */
   int prev_first;  /*_ first char of previous row */
};

struct nk_text_edit_row {
   float x0,x1;
   /* starting x location, end x location (allows for align=right, etc) */
   float baseline_y_delta;
   /* position of baseline relative to previous row's baseline*/
   float ymin,ymax;
   /* height of row above and below baseline */
   int num_chars;
};

/* forward declarations */
NK_INTERN void nk_textedit_makeundo_delete(struct nk_text_edit*, int, int);
NK_INTERN void nk_textedit_makeundo_insert(struct nk_text_edit*, int, int);
NK_INTERN void nk_textedit_makeundo_replace(struct nk_text_edit*, int, int, int);
#define NK_TEXT_HAS_SELECTION(s)   ((s)->select_start != (s)->select_end)

NK_INTERN float
nk_textedit_get_width(const struct nk_text_edit *edit, int line_start, int char_id,
    const struct nk_user_font *font)
{
    int len = 0;
    nk_rune unicode = 0;
    const char *str = nk_str_at_const(&edit->string, line_start + char_id, &unicode, &len);
    return font->width(font->userdata, font->height, str, len);
}

NK_INTERN void
nk_textedit_layout_row(struct nk_text_edit_row *r, struct nk_text_edit *edit,
    int line_start_id, float row_height, const struct nk_user_font *font)
{
    int l;
    int glyphs = 0;
    nk_rune unicode;
    const char *remaining;
    int len = nk_str_len_char(&edit->string);
    const char *end = nk_str_get_const(&edit->string) + len;
    const char *text = nk_str_at_const(&edit->string, line_start_id, &unicode, &l);
    const struct nk_vec2 size = nk_text_calculate_text_bounds(font,
        text, (int)(end - text), row_height, &remaining, 0, &glyphs, NK_STOP_ON_NEW_LINE);

    r->x0 = 0.0f;
    r->x1 = size.x;
    r->baseline_y_delta = size.y;
    r->ymin = 0.0f;
    r->ymax = size.y;
    r->num_chars = glyphs;
}

NK_INTERN int
nk_textedit_locate_coord(struct nk_text_edit *edit, float x, float y,
    const struct nk_user_font *font, float row_height)
{
    struct nk_text_edit_row r;
    int n = edit->string.len;
    float base_y = 0, prev_x;
    int i=0, k;

    r.x0 = r.x1 = 0;
    r.ymin = r.ymax = 0;
    r.num_chars = 0;

    /* search rows to find one that straddles 'y' */
    while (i < n) {
        nk_textedit_layout_row(&r, edit, i, row_height, font);
        if (r.num_chars <= 0)
            return n;

        if (i==0 && y < base_y + r.ymin)
            return 0;

        if (y < base_y + r.ymax)
            break;

        i += r.num_chars;
        base_y += r.baseline_y_delta;
    }

    /* below all text, return 'after' last character */
    if (i >= n)
        return n;

    /* check if it's before the beginning of the line */
    if (x < r.x0)
        return i;

    /* check if it's before the end of the line */
    if (x < r.x1) {
        /* search characters in row for one that straddles 'x' */
        k = i;
        prev_x = r.x0;
        for (i=0; i < r.num_chars; ++i) {
            float w = nk_textedit_get_width(edit, k, i, font);
            if (x < prev_x+w) {
                if (x < prev_x+w/2)
                    return k+i;
                else return k+i+1;
            }
            prev_x += w;
        }
        /* shouldn't happen, but if it does, fall through to end-of-line case */
    }

    /* if the last character is a newline, return that.
     * otherwise return 'after' the last character */
    if (nk_str_rune_at(&edit->string, i+r.num_chars-1) == '\n')
        return i+r.num_chars-1;
    else return i+r.num_chars;
}

NK_INTERN void
nk_textedit_click(struct nk_text_edit *state, float x, float y,
    const struct nk_user_font *font, float row_height)
{
    /* API click: on mouse down, move the cursor to the clicked location,
     * and reset the selection */
    state->cursor = nk_textedit_locate_coord(state, x, y, font, row_height);
    state->select_start = state->cursor;
    state->select_end = state->cursor;
    state->has_preferred_x = 0;
}

NK_INTERN void
nk_textedit_drag(struct nk_text_edit *state, float x, float y,
    const struct nk_user_font *font, float row_height)
{
    /* API drag: on mouse drag, move the cursor and selection endpoint
     * to the clicked location */
    int p = nk_textedit_locate_coord(state, x, y, font, row_height);
    if (state->select_start == state->select_end)
        state->select_start = state->cursor;
    state->cursor = state->select_end = p;
}

NK_INTERN void
nk_textedit_find_charpos(struct nk_text_find *find, struct nk_text_edit *state,
    int n, int single_line, const struct nk_user_font *font, float row_height)
{
    /* find the x/y location of a character, and remember info about the previous
     * row in case we get a move-up event (for page up, we'll have to rescan) */
    struct nk_text_edit_row r;
    int prev_start = 0;
    int z = state->string.len;
    int i=0, first;

    if (n == z) {
        /* if it's at the end, then find the last line -- simpler than trying to
        explicitly handle this case in the regular code */
        if (single_line) {
            nk_textedit_layout_row(&r, state, 0, row_height, font);
            find->y = 0;
            find->first_char = 0;
            find->length = z;
            find->height = r.ymax - r.ymin;
            find->x = r.x1;
        } else {
            find->y = 0;
            find->x = 0;
            find->height = 1;

            while (i < z) {
                nk_textedit_layout_row(&r, state, i, row_height, font);
                prev_start = i;
                i += r.num_chars;
            }

            find->first_char = i;
            find->length = 0;
            find->prev_first = prev_start;
        }
        return;
    }

    /* search rows to find the one that straddles character n */
    find->y = 0;

    for(;;) {
        nk_textedit_layout_row(&r, state, i, row_height, font);
        if (n < i + r.num_chars) break;
        prev_start = i;
        i += r.num_chars;
        find->y += r.baseline_y_delta;
    }

    find->first_char = first = i;
    find->length = r.num_chars;
    find->height = r.ymax - r.ymin;
    find->prev_first = prev_start;

    /* now scan to find xpos */
    find->x = r.x0;
    for (i=0; first+i < n; ++i)
        find->x += nk_textedit_get_width(state, first, i, font);
}

NK_INTERN void
nk_textedit_clamp(struct nk_text_edit *state)
{
    /* make the selection/cursor state valid if client altered the string */
    int n = state->string.len;
    if (NK_TEXT_HAS_SELECTION(state)) {
        if (state->select_start > n) state->select_start = n;
        if (state->select_end   > n) state->select_end = n;
        /* if clamping forced them to be equal, move the cursor to match */
        if (state->select_start == state->select_end)
            state->cursor = state->select_start;
    }
    if (state->cursor > n) state->cursor = n;
}

NK_API void
nk_textedit_delete(struct nk_text_edit *state, int where, int len)
{
    /* delete characters while updating undo */
    nk_textedit_makeundo_delete(state, where, len);
    nk_str_delete_runes(&state->string, where, len);
    state->has_preferred_x = 0;
}

NK_API void
nk_textedit_delete_selection(struct nk_text_edit *state)
{
    /* delete the section */
    nk_textedit_clamp(state);
    if (NK_TEXT_HAS_SELECTION(state)) {
        if (state->select_start < state->select_end) {
            nk_textedit_delete(state, state->select_start,
                state->select_end - state->select_start);
            state->select_end = state->cursor = state->select_start;
        } else {
            nk_textedit_delete(state, state->select_end,
                state->select_start - state->select_end);
            state->select_start = state->cursor = state->select_end;
        }
        state->has_preferred_x = 0;
    }
}

NK_INTERN void
nk_textedit_sortselection(struct nk_text_edit *state)
{
    /* canonicalize the selection so start <= end */
    if (state->select_end < state->select_start) {
        int temp = state->select_end;
        state->select_end = state->select_start;
        state->select_start = temp;
    }
}

NK_INTERN void
nk_textedit_move_to_first(struct nk_text_edit *state)
{
    /* move cursor to first character of selection */
    if (NK_TEXT_HAS_SELECTION(state)) {
        nk_textedit_sortselection(state);
        state->cursor = state->select_start;
        state->select_end = state->select_start;
        state->has_preferred_x = 0;
    }
}

NK_INTERN void
nk_textedit_move_to_last(struct nk_text_edit *state)
{
    /* move cursor to last character of selection */
    if (NK_TEXT_HAS_SELECTION(state)) {
        nk_textedit_sortselection(state);
        nk_textedit_clamp(state);
        state->cursor = state->select_end;
        state->select_start = state->select_end;
        state->has_preferred_x = 0;
    }
}

NK_INTERN int
nk_is_word_boundary( struct nk_text_edit *state, int idx)
{
    int len;
    nk_rune c;
    if (idx <= 0) return 1;
    if (!nk_str_at_rune(&state->string, idx, &c, &len)) return 1;
    return (c == ' ' || c == '\t' ||c == 0x3000 || c == ',' || c == ';' ||
            c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' ||
            c == '|');
}

NK_INTERN int
nk_textedit_move_to_word_previous(struct nk_text_edit *state)
{
   int c = state->cursor - 1;
   while( c >= 0 && !nk_is_word_boundary(state, c))
      --c;

   if( c < 0 )
      c = 0;

   return c;
}

NK_INTERN int
nk_textedit_move_to_word_next(struct nk_text_edit *state)
{
   const int len = state->string.len;
   int c = state->cursor+1;
   while( c < len && !nk_is_word_boundary(state, c))
      ++c;

   if( c > len )
      c = len;

   return c;
}

NK_INTERN void
nk_textedit_prep_selection_at_cursor(struct nk_text_edit *state)
{
    /* update selection and cursor to match each other */
    if (!NK_TEXT_HAS_SELECTION(state))
        state->select_start = state->select_end = state->cursor;
    else state->cursor = state->select_end;
}

NK_API int
nk_textedit_cut(struct nk_text_edit *state)
{
    /* API cut: delete selection */
    if (NK_TEXT_HAS_SELECTION(state)) {
        nk_textedit_delete_selection(state); /* implicitly clamps */
        state->has_preferred_x = 0;
        return 1;
    }
   return 0;
}

NK_API int
nk_textedit_paste(struct nk_text_edit *state, char const *ctext, int len)
{
    /* API paste: replace existing selection with passed-in text */
    int glyphs;
    const char *text = (const char *) ctext;
    /* if there's a selection, the paste should delete it */
    nk_textedit_clamp(state);
    nk_textedit_delete_selection(state);
    /* try to insert the characters */
    glyphs = nk_utf_len(ctext, len);
    if (nk_str_insert_text_char(&state->string, state->cursor, text, len)) {
        nk_textedit_makeundo_insert(state, state->cursor, glyphs);
        state->cursor += len;
        state->has_preferred_x = 0;
        return 1;
    }
    /* remove the undo since we didn't actually insert the characters */
    if (state->undo.undo_point)
        --state->undo.undo_point;
    return 0;
}

NK_API void
nk_textedit_text(struct nk_text_edit *state, const char *text, int total_len)
{
    nk_rune unicode;
    int glyph_len;
    int text_len = 0;

    NK_ASSERT(state);
    NK_ASSERT(text);
    if (!text || !total_len || state->mode == NK_TEXT_EDIT_MODE_VIEW) return;

    glyph_len = nk_utf_decode(text, &unicode, total_len);
    if (!glyph_len) return;
    while ((text_len < total_len) && glyph_len)
    {
        /* can't add newline in single-line mode */
        if (unicode == '\n' && state->single_line)
            break;

        /* filter incoming text */
        if (state->filter && !state->filter(state, unicode)) {
            glyph_len = nk_utf_decode(text + text_len, &unicode, total_len-text_len);
            text_len += glyph_len;
            continue;
        }

        if (!NK_TEXT_HAS_SELECTION(state) &&
            state->cursor < state->string.len)
        {
            if (state->mode == NK_TEXT_EDIT_MODE_REPLACE) {
                nk_textedit_makeundo_replace(state, state->cursor, 1, 1);
                nk_str_delete_runes(&state->string, state->cursor, 1);
            }
            if (nk_str_insert_text_char(&state->string, state->cursor,
                                        text+text_len, glyph_len))
            {
                ++state->cursor;
                state->has_preferred_x = 0;
            }
        } else {
            nk_textedit_delete_selection(state); /* implicitly clamps */
            if (nk_str_insert_text_char(&state->string, state->cursor,
                                        text+text_len, glyph_len))
            {
                nk_textedit_makeundo_insert(state, state->cursor, 1);
                ++state->cursor;
                state->has_preferred_x = 0;
            }
        }
        glyph_len = nk_utf_decode(text + text_len, &unicode, total_len-text_len);
        text_len += glyph_len;
    }
}

NK_INTERN void
nk_textedit_key(struct nk_text_edit *state, enum nk_keys key, int shift_mod,
    const struct nk_user_font *font, float row_height)
{
retry:
    switch (key)
    {
    case NK_KEY_NONE:
    case NK_KEY_CTRL:
    case NK_KEY_ENTER:
    case NK_KEY_SHIFT:
    case NK_KEY_TAB:
    case NK_KEY_COPY:
    case NK_KEY_CUT:
    case NK_KEY_PASTE:
    case NK_KEY_MAX:
    default: break;
    case NK_KEY_TEXT_UNDO:
         nk_textedit_undo(state);
         state->has_preferred_x = 0;
         break;

    case NK_KEY_TEXT_REDO:
        nk_textedit_redo(state);
        state->has_preferred_x = 0;
        break;

    case NK_KEY_TEXT_INSERT_MODE:
        if (state->mode == NK_TEXT_EDIT_MODE_VIEW)
            state->mode = NK_TEXT_EDIT_MODE_INSERT;
        break;
    case NK_KEY_TEXT_REPLACE_MODE:
        if (state->mode == NK_TEXT_EDIT_MODE_VIEW)
            state->mode = NK_TEXT_EDIT_MODE_REPLACE;
        break;
    case NK_KEY_TEXT_RESET_MODE:
        if (state->mode == NK_TEXT_EDIT_MODE_INSERT ||
            state->mode == NK_TEXT_EDIT_MODE_REPLACE)
            state->mode = NK_TEXT_EDIT_MODE_VIEW;
        break;

    case NK_KEY_LEFT:
        if (shift_mod) {
            nk_textedit_clamp(state);
            nk_textedit_prep_selection_at_cursor(state);
            /* move selection left */
            if (state->select_end > 0)
                --state->select_end;
            state->cursor = state->select_end;
            state->has_preferred_x = 0;
        } else {
            /* if currently there's a selection,
             * move cursor to start of selection */
            if (NK_TEXT_HAS_SELECTION(state))
                nk_textedit_move_to_first(state);
            else if (state->cursor > 0)
               --state->cursor;
            state->has_preferred_x = 0;
        } break;

    case NK_KEY_RIGHT:
        if (shift_mod) {
            nk_textedit_prep_selection_at_cursor(state);
            /* move selection right */
            ++state->select_end;
            nk_textedit_clamp(state);
            state->cursor = state->select_end;
            state->has_preferred_x = 0;
        } else {
            /* if currently there's a selection,
             * move cursor to end of selection */
            if (NK_TEXT_HAS_SELECTION(state))
                nk_textedit_move_to_last(state);
            else ++state->cursor;
            nk_textedit_clamp(state);
            state->has_preferred_x = 0;
        } break;

    case NK_KEY_TEXT_WORD_LEFT:
        if (shift_mod) {
            if( !NK_TEXT_HAS_SELECTION( state ) )
            nk_textedit_prep_selection_at_cursor(state);
            state->cursor = nk_textedit_move_to_word_previous(state);
            state->select_end = state->cursor;
            nk_textedit_clamp(state );
        } else {
            if (NK_TEXT_HAS_SELECTION(state))
                nk_textedit_move_to_first(state);
            else {
                state->cursor = nk_textedit_move_to_word_previous(state);
                nk_textedit_clamp(state );
            }
        } break;

    case NK_KEY_TEXT_WORD_RIGHT:
        if (shift_mod) {
            if( !NK_TEXT_HAS_SELECTION( state ) )
                nk_textedit_prep_selection_at_cursor(state);
            state->cursor = nk_textedit_move_to_word_next(state);
            state->select_end = state->cursor;
            nk_textedit_clamp(state);
        } else {
            if (NK_TEXT_HAS_SELECTION(state))
                nk_textedit_move_to_last(state);
            else {
                state->cursor = nk_textedit_move_to_word_next(state);
                nk_textedit_clamp(state );
            }
        } break;

    case NK_KEY_DOWN: {
        struct nk_text_find find;
        struct nk_text_edit_row row;
        int i, sel = shift_mod;

        if (state->single_line) {
            /* on windows, up&down in single-line behave like left&right */
            key = NK_KEY_RIGHT;
            goto retry;
        }

        if (sel)
            nk_textedit_prep_selection_at_cursor(state);
        else if (NK_TEXT_HAS_SELECTION(state))
            nk_textedit_move_to_last(state);

        /* compute current position of cursor point */
        nk_textedit_clamp(state);
        nk_textedit_find_charpos(&find, state, state->cursor, state->single_line,
            font, row_height);

        /* now find character position down a row */
        if (find.length)
        {
            float x;
            float goal_x = state->has_preferred_x ? state->preferred_x : find.x;
            int start = find.first_char + find.length;

            state->cursor = start;
            nk_textedit_layout_row(&row, state, state->cursor, row_height, font);
            x = row.x0;

            for (i=0; i < row.num_chars; ++i) {
                float dx = nk_textedit_get_width(state, start, i, font);
                x += dx;
                if (x > goal_x)
                    break;
                ++state->cursor;
            }
            nk_textedit_clamp(state);

            state->has_preferred_x = 1;
            state->preferred_x = goal_x;
            if (sel)
                state->select_end = state->cursor;
        }
    } break;

    case NK_KEY_UP: {
        struct nk_text_find find;
        struct nk_text_edit_row row;
        int i, sel = shift_mod;

        if (state->single_line) {
            /* on windows, up&down become left&right */
            key = NK_KEY_LEFT;
            goto retry;
        }

        if (sel)
            nk_textedit_prep_selection_at_cursor(state);
        else if (NK_TEXT_HAS_SELECTION(state))
            nk_textedit_move_to_first(state);

         /* compute current position of cursor point */
         nk_textedit_clamp(state);
         nk_textedit_find_charpos(&find, state, state->cursor, state->single_line,
                font, row_height);

         /* can only go up if there's a previous row */
         if (find.prev_first != find.first_char) {
            /* now find character position up a row */
            float x;
            float goal_x = state->has_preferred_x ? state->preferred_x : find.x;

            state->cursor = find.prev_first;
            nk_textedit_layout_row(&row, state, state->cursor, row_height, font);
            x = row.x0;

            for (i=0; i < row.num_chars; ++i) {
                float dx = nk_textedit_get_width(state, find.prev_first, i, font);
                x += dx;
                if (x > goal_x)
                    break;
                ++state->cursor;
            }
            nk_textedit_clamp(state);

            state->has_preferred_x = 1;
            state->preferred_x = goal_x;
            if (sel) state->select_end = state->cursor;
         }
      } break;

    case NK_KEY_DEL:
         if (NK_TEXT_HAS_SELECTION(state))
            nk_textedit_delete_selection(state);
         else {
            int n = state->string.len;
            if (state->cursor < n)
                nk_textedit_delete(state, state->cursor, 1);
         }
         state->has_preferred_x = 0;
         break;

    case NK_KEY_BACKSPACE:
         if (NK_TEXT_HAS_SELECTION(state))
            nk_textedit_delete_selection(state);
         else {
            nk_textedit_clamp(state);
            if (state->cursor > 0) {
                nk_textedit_delete(state, state->cursor-1, 1);
                --state->cursor;
            }
         }
         state->has_preferred_x = 0;
         break;

    case NK_KEY_TEXT_START:
         if (shift_mod) {
            nk_textedit_prep_selection_at_cursor(state);
            state->cursor = state->select_end = 0;
            state->has_preferred_x = 0;
         } else {
            state->cursor = state->select_start = state->select_end = 0;
            state->has_preferred_x = 0;
         }
         break;

    case NK_KEY_TEXT_END:
         if (shift_mod) {
            nk_textedit_prep_selection_at_cursor(state);
            state->cursor = state->select_end = state->string.len;
            state->has_preferred_x = 0;
         } else {
            state->cursor = state->string.len;
            state->select_start = state->select_end = 0;
            state->has_preferred_x = 0;
         }
         break;

    case NK_KEY_TEXT_LINE_START: {
        if (shift_mod) {
            struct nk_text_find find;
           nk_textedit_clamp(state);
            nk_textedit_prep_selection_at_cursor(state);
            if (state->string.len && state->cursor == state->string.len)
                --state->cursor;
            nk_textedit_find_charpos(&find, state,state->cursor, state->single_line,
                font, row_height);
            state->cursor = state->select_end = find.first_char;
            state->has_preferred_x = 0;
        } else {
            struct nk_text_find find;
            if (state->string.len && state->cursor == state->string.len)
                --state->cursor;
            nk_textedit_clamp(state);
            nk_textedit_move_to_first(state);
            nk_textedit_find_charpos(&find, state, state->cursor, state->single_line,
                font, row_height);
            state->cursor = find.first_char;
            state->has_preferred_x = 0;
        }
      } break;

    case NK_KEY_TEXT_LINE_END: {
        if (shift_mod) {
            struct nk_text_find find;
            nk_textedit_clamp(state);
            nk_textedit_prep_selection_at_cursor(state);
            nk_textedit_find_charpos(&find, state, state->cursor, state->single_line,
                font, row_height);
            state->has_preferred_x = 0;
            state->cursor = find.first_char + find.length;
            if (find.length > 0 && nk_str_rune_at(&state->string, state->cursor-1) == '\n')
                --state->cursor;
            state->select_end = state->cursor;
        } else {
            struct nk_text_find find;
            nk_textedit_clamp(state);
            nk_textedit_move_to_first(state);
            nk_textedit_find_charpos(&find, state, state->cursor, state->single_line,
                font, row_height);

            state->has_preferred_x = 0;
            state->cursor = find.first_char + find.length;
            if (find.length > 0 && nk_str_rune_at(&state->string, state->cursor-1) == '\n')
                --state->cursor;
        }} break;
    }
}

NK_INTERN void
nk_textedit_flush_redo(struct nk_text_undo_state *state)
{
    state->redo_point = NK_TEXTEDIT_UNDOSTATECOUNT;
    state->redo_char_point = NK_TEXTEDIT_UNDOCHARCOUNT;
}

NK_INTERN void
nk_textedit_discard_undo(struct nk_text_undo_state *state)
{
    /* discard the oldest entry in the undo list */
    if (state->undo_point > 0) {
        /* if the 0th undo state has characters, clean those up */
        if (state->undo_rec[0].char_storage >= 0) {
            int n = state->undo_rec[0].insert_length, i;
            /* delete n characters from all other records */
            state->undo_char_point = (short)(state->undo_char_point - n);
            NK_MEMCPY(state->undo_char, state->undo_char + n,
                (nk_size)state->undo_char_point*sizeof(nk_rune));
            for (i=0; i < state->undo_point; ++i) {
                if (state->undo_rec[i].char_storage >= 0)
                state->undo_rec[i].char_storage = (short)
                    (state->undo_rec[i].char_storage - n);
            }
        }
        --state->undo_point;
        NK_MEMCPY(state->undo_rec, state->undo_rec+1,
            (nk_size)((nk_size)state->undo_point * sizeof(state->undo_rec[0])));
    }
}

NK_INTERN void
nk_textedit_discard_redo(struct nk_text_undo_state *state)
{
/*  discard the oldest entry in the redo list--it's bad if this
    ever happens, but because undo & redo have to store the actual
    characters in different cases, the redo character buffer can
    fill up even though the undo buffer didn't */
    nk_size num;
    int k = NK_TEXTEDIT_UNDOSTATECOUNT-1;
    if (state->redo_point <= k) {
        /* if the k'th undo state has characters, clean those up */
        if (state->undo_rec[k].char_storage >= 0) {
            int n = state->undo_rec[k].insert_length, i;
            /* delete n characters from all other records */
            state->redo_char_point = (short)(state->redo_char_point + n);
            num = (nk_size)(NK_TEXTEDIT_UNDOSTATECOUNT - state->redo_char_point);
            NK_MEMCPY(state->undo_char + state->redo_char_point,
                state->undo_char + state->redo_char_point-n, num * sizeof(char));
            for (i = state->redo_point; i < k; ++i) {
                if (state->undo_rec[i].char_storage >= 0) {
                    state->undo_rec[i].char_storage = (short)
                        (state->undo_rec[i].char_storage + n);
                }
            }
        }
        ++state->redo_point;
        num = (nk_size)(NK_TEXTEDIT_UNDOSTATECOUNT - state->redo_point);
        if (num) NK_MEMCPY(state->undo_rec + state->redo_point-1,
            state->undo_rec + state->redo_point, num * sizeof(state->undo_rec[0]));
    }
}

NK_INTERN struct nk_text_undo_record*
nk_textedit_create_undo_record(struct nk_text_undo_state *state, int numchars)
{
    /* any time we create a new undo record, we discard redo*/
    nk_textedit_flush_redo(state);

    /* if we have no free records, we have to make room,
     * by sliding the existing records down */
    if (state->undo_point == NK_TEXTEDIT_UNDOSTATECOUNT)
        nk_textedit_discard_undo(state);

    /* if the characters to store won't possibly fit in the buffer,
     * we can't undo */
    if (numchars > NK_TEXTEDIT_UNDOCHARCOUNT) {
        state->undo_point = 0;
        state->undo_char_point = 0;
        return 0;
    }

    /* if we don't have enough free characters in the buffer,
     * we have to make room */
    while (state->undo_char_point + numchars > NK_TEXTEDIT_UNDOCHARCOUNT)
        nk_textedit_discard_undo(state);
    return &state->undo_rec[state->undo_point++];
}

NK_INTERN nk_rune*
nk_textedit_createundo(struct nk_text_undo_state *state, int pos,
    int insert_len, int delete_len)
{
    struct nk_text_undo_record *r = nk_textedit_create_undo_record(state, insert_len);
    if (r == 0)
        return 0;

    r->where = pos;
    r->insert_length = (short) insert_len;
    r->delete_length = (short) delete_len;

    if (insert_len == 0) {
        r->char_storage = -1;
        return 0;
    } else {
        r->char_storage = state->undo_char_point;
        state->undo_char_point = (short)(state->undo_char_point +  insert_len);
        return &state->undo_char[r->char_storage];
    }
}

NK_API void
nk_textedit_undo(struct nk_text_edit *state)
{
    struct nk_text_undo_state *s = &state->undo;
    struct nk_text_undo_record u, *r;
    if (s->undo_point == 0)
        return;

    /* we need to do two things: apply the undo record, and create a redo record */
    u = s->undo_rec[s->undo_point-1];
    r = &s->undo_rec[s->redo_point-1];
    r->char_storage = -1;

    r->insert_length = u.delete_length;
    r->delete_length = u.insert_length;
    r->where = u.where;

    if (u.delete_length)
    {
       /*   if the undo record says to delete characters, then the redo record will
            need to re-insert the characters that get deleted, so we need to store
            them.
            there are three cases:
                - there's enough room to store the characters
                - characters stored for *redoing* don't leave room for redo
                - characters stored for *undoing* don't leave room for redo
            if the last is true, we have to bail */
        if (s->undo_char_point + u.delete_length >= NK_TEXTEDIT_UNDOCHARCOUNT) {
            /* the undo records take up too much character space; there's no space
            * to store the redo characters */
            r->insert_length = 0;
        } else {
            int i;
            /* there's definitely room to store the characters eventually */
            while (s->undo_char_point + u.delete_length > s->redo_char_point) {
                /* there's currently not enough room, so discard a redo record */
                nk_textedit_discard_redo(s);
                /* should never happen: */
                if (s->redo_point == NK_TEXTEDIT_UNDOSTATECOUNT)
                    return;
            }

            r = &s->undo_rec[s->redo_point-1];
            r->char_storage = (short)(s->redo_char_point - u.delete_length);
            s->redo_char_point = (short)(s->redo_char_point -  u.delete_length);

            /* now save the characters */
            for (i=0; i < u.delete_length; ++i)
                s->undo_char[r->char_storage + i] =
                    nk_str_rune_at(&state->string, u.where + i);
        }
        /* now we can carry out the deletion */
        nk_str_delete_runes(&state->string, u.where, u.delete_length);
    }

    /* check type of recorded action: */
    if (u.insert_length) {
        /* easy case: was a deletion, so we need to insert n characters */
        nk_str_insert_text_runes(&state->string, u.where,
            &s->undo_char[u.char_storage], u.insert_length);
        s->undo_char_point = (short)(s->undo_char_point - u.insert_length);
    }
    state->cursor = (short)(u.where + u.insert_length);

    s->undo_point--;
    s->redo_point--;
}

NK_API void
nk_textedit_redo(struct nk_text_edit *state)
{
    struct nk_text_undo_state *s = &state->undo;
    struct nk_text_undo_record *u, r;
    if (s->redo_point == NK_TEXTEDIT_UNDOSTATECOUNT)
        return;

    /* we need to do two things: apply the redo record, and create an undo record */
    u = &s->undo_rec[s->undo_point];
    r = s->undo_rec[s->redo_point];

    /* we KNOW there must be room for the undo record, because the redo record
    was derived from an undo record */
    u->delete_length = r.insert_length;
    u->insert_length = r.delete_length;
    u->where = r.where;
    u->char_storage = -1;

    if (r.delete_length) {
        /* the redo record requires us to delete characters, so the undo record
        needs to store the characters */
        if (s->undo_char_point + u->insert_length > s->redo_char_point) {
            u->insert_length = 0;
            u->delete_length = 0;
        } else {
            int i;
            u->char_storage = s->undo_char_point;
            s->undo_char_point = (short)(s->undo_char_point + u->insert_length);

            /* now save the characters */
            for (i=0; i < u->insert_length; ++i) {
                s->undo_char[u->char_storage + i] =
                    nk_str_rune_at(&state->string, u->where + i);
            }
        }
        nk_str_delete_runes(&state->string, r.where, r.delete_length);
    }

    if (r.insert_length) {
        /* easy case: need to insert n characters */
        nk_str_insert_text_runes(&state->string, r.where,
            &s->undo_char[r.char_storage], r.insert_length);
    }
    state->cursor = r.where + r.insert_length;

    s->undo_point++;
    s->redo_point++;
}

NK_INTERN void
nk_textedit_makeundo_insert(struct nk_text_edit *state, int where, int length)
{
    nk_textedit_createundo(&state->undo, where, 0, length);
}

NK_INTERN void
nk_textedit_makeundo_delete(struct nk_text_edit *state, int where, int length)
{
    int i;
    nk_rune *p = nk_textedit_createundo(&state->undo, where, length, 0);
    if (p) {
        for (i=0; i < length; ++i)
            p[i] = nk_str_rune_at(&state->string, where+i);
    }
}

NK_INTERN void
nk_textedit_makeundo_replace(struct nk_text_edit *state, int where,
    int old_length, int new_length)
{
    int i;
    nk_rune *p = nk_textedit_createundo(&state->undo, where, old_length, new_length);
    if (p) {
        for (i=0; i < old_length; ++i)
            p[i] = nk_str_rune_at(&state->string, where+i);
    }
}

NK_INTERN void
nk_textedit_clear_state(struct nk_text_edit *state, enum nk_text_edit_type type,
    nk_filter filter)
{
    /* reset the state to default */
   state->undo.undo_point = 0;
   state->undo.undo_char_point = 0;
   state->undo.redo_point = NK_TEXTEDIT_UNDOSTATECOUNT;
   state->undo.redo_char_point = NK_TEXTEDIT_UNDOCHARCOUNT;
   state->select_end = state->select_start = 0;
   state->cursor = 0;
   state->has_preferred_x = 0;
   state->preferred_x = 0;
   state->cursor_at_end_of_line = 0;
   state->initialized = 1;
   state->single_line = (unsigned char)(type == NK_TEXT_EDIT_SINGLE_LINE);
   state->mode = NK_TEXT_EDIT_MODE_VIEW;
   state->filter = filter;
}

NK_API void
nk_textedit_init_fixed(struct nk_text_edit *state, void *memory, nk_size size)
{
    NK_ASSERT(state);
    NK_ASSERT(memory);
    if (!state || !memory || !size) return;
    nk_textedit_clear_state(state, NK_TEXT_EDIT_SINGLE_LINE, 0);
    nk_str_init_fixed(&state->string, memory, size);
}

NK_API void
nk_textedit_init(struct nk_text_edit *state, struct nk_allocator *alloc, nk_size size)
{
    NK_ASSERT(state);
    NK_ASSERT(alloc);
    if (!state || !alloc) return;
    nk_textedit_clear_state(state, NK_TEXT_EDIT_SINGLE_LINE, 0);
    nk_str_init(&state->string, alloc, size);
}

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API void
nk_textedit_init_default(struct nk_text_edit *state)
{
    NK_ASSERT(state);
    if (!state) return;
    nk_textedit_clear_state(state, NK_TEXT_EDIT_SINGLE_LINE, 0);
    nk_str_init_default(&state->string);
}
#endif

NK_API void
nk_textedit_select_all(struct nk_text_edit *state)
{
    NK_ASSERT(state);
    state->select_start = 0;
    state->select_end = state->string.len;
}

NK_API void
nk_textedit_free(struct nk_text_edit *state)
{
    NK_ASSERT(state);
    if (!state) return;
    nk_str_free(&state->string);
}

/* ===============================================================
 *
 *                          TEXT WIDGET
 *
 * ===============================================================*/
#define nk_widget_state_reset(s)\
    if ((*(s)) & NK_WIDGET_STATE_MODIFIED)\
        (*(s)) = NK_WIDGET_STATE_INACTIVE|NK_WIDGET_STATE_MODIFIED;\
    else (*(s)) = NK_WIDGET_STATE_INACTIVE;

struct nk_text {
    struct nk_vec2 padding;
    struct nk_color background;
    struct nk_color text;
};

NK_INTERN void
nk_widget_text(struct nk_command_buffer *o, struct nk_rect b,
    const char *string, int len, const struct nk_text *t,
    nk_flags a, const struct nk_user_font *f)
{
    struct nk_rect label;
    float text_width;

    NK_ASSERT(o);
    NK_ASSERT(t);
    if (!o || !t) return;

    b.h = NK_MAX(b.h, 2 * t->padding.y);
    label.x = 0; label.w = 0;
    label.y = b.y + t->padding.y;
    label.h = b.h - 2 * t->padding.y;

    text_width = f->width(f->userdata, f->height, (const char*)string, len);
    text_width += (2.0f * t->padding.x);

    /* align in x-axis */
    if (a & NK_TEXT_ALIGN_LEFT) {
        label.x = b.x + t->padding.x;
        label.w = NK_MAX(0, b.w - 2 * t->padding.x);
    } else if (a & NK_TEXT_ALIGN_CENTERED) {
        label.w = NK_MAX(1, 2 * t->padding.x + (float)text_width);
        label.x = (b.x + t->padding.x + ((b.w - 2 * t->padding.x) - label.w) / 2);
        label.x = NK_MAX(b.x + t->padding.x, label.x);
        label.w = NK_MIN(b.x + b.w, label.x + label.w);
        if (label.w >= label.x) label.w -= label.x;
    } else if (a & NK_TEXT_ALIGN_RIGHT) {
        label.x = NK_MAX(b.x + t->padding.x, (b.x + b.w) - (2 * t->padding.x + (float)text_width));
        label.w = (float)text_width + 2 * t->padding.x;
    } else return;

    /* align in y-axis */
    if (a & NK_TEXT_ALIGN_MIDDLE) {
        label.y = b.y + b.h/2.0f - (float)f->height/2.0f;
        label.h = b.h - (b.h/2.0f + f->height/2.0f);
    } else if (a & NK_TEXT_ALIGN_BOTTOM) {
        label.y = b.y + b.h - f->height;
        label.h = f->height;
    }
    nk_draw_text(o, label, (const char*)string,
        len, f, t->background, t->text);
}

NK_INTERN void
nk_widget_text_wrap(struct nk_command_buffer *o, struct nk_rect b,
    const char *string, int len, const struct nk_text *t,
    const struct nk_user_font *f)
{
    float width;
    int glyphs = 0;
    int fitting = 0;
    int done = 0;
    struct nk_rect line;
    struct nk_text text;

    NK_ASSERT(o);
    NK_ASSERT(t);
    if (!o || !t) return;

    text.padding = nk_vec2(0,0);
    text.background = t->background;
    text.text = t->text;

    b.w = NK_MAX(b.w, 2 * t->padding.x);
    b.h = NK_MAX(b.h, 2 * t->padding.y);
    b.h = b.h - 2 * t->padding.y;

    line.x = b.x + t->padding.x;
    line.y = b.y + t->padding.y;
    line.w = b.w - 2 * t->padding.x;
    line.h = 2 * t->padding.y + f->height;

    fitting = nk_text_clamp(f, string, len, line.w, &glyphs, &width);
    while (done < len) {
        if (!fitting || line.y + line.h >= (b.y + b.h)) break;
        nk_widget_text(o, line, &string[done], fitting, &text, NK_TEXT_LEFT, f);
        done += fitting;
        line.y += f->height + 2 * t->padding.y;
        fitting = nk_text_clamp(f, &string[done], len - done,
                                line.w, &glyphs, &width);
    }
}

/* ===============================================================
 *
 *                          BUTTON
 *
 * ===============================================================*/
NK_INTERN void
nk_draw_symbol(struct nk_command_buffer *out, enum nk_symbol_type type,
    struct nk_rect content, struct nk_color background, struct nk_color foreground,
    float border_width, const struct nk_user_font *font)
{
    switch (type) {
    case NK_SYMBOL_X:
    case NK_SYMBOL_UNDERSCORE:
    case NK_SYMBOL_PLUS:
    case NK_SYMBOL_MINUS: {
        /* single character text symbol */
        const char *X = (type == NK_SYMBOL_X) ? "x":
            (type == NK_SYMBOL_UNDERSCORE) ? "_":
            (type == NK_SYMBOL_PLUS) ? "+": "-";
        struct nk_text text;
        text.padding = nk_vec2(0,0);
        text.background = background;
        text.text = foreground;
        nk_widget_text(out, content, X, 1, &text, NK_TEXT_CENTERED, font);
    } break;
    case NK_SYMBOL_CIRCLE:
    case NK_SYMBOL_CIRCLE_FILLED:
    case NK_SYMBOL_RECT:
    case NK_SYMBOL_RECT_FILLED: {
        /* simple empty/filled shapes */
        if (type == NK_SYMBOL_RECT || type == NK_SYMBOL_RECT_FILLED) {
            nk_fill_rect(out, content,  0, foreground);
            if (type == NK_SYMBOL_RECT_FILLED)
                nk_fill_rect(out, nk_shrink_rect(content, border_width), 0, background);
        } else {
            nk_fill_circle(out, content, foreground);
            if (type == NK_SYMBOL_CIRCLE_FILLED)
                nk_fill_circle(out, nk_shrink_rect(content, 1), background);
        }
    } break;
    case NK_SYMBOL_TRIANGLE_UP:
    case NK_SYMBOL_TRIANGLE_DOWN:
    case NK_SYMBOL_TRIANGLE_LEFT:
    case NK_SYMBOL_TRIANGLE_RIGHT: {
        enum nk_heading heading;
        struct nk_vec2 points[3];
        heading = (type == NK_SYMBOL_TRIANGLE_RIGHT) ? NK_RIGHT :
            (type == NK_SYMBOL_TRIANGLE_LEFT) ? NK_LEFT:
            (type == NK_SYMBOL_TRIANGLE_UP) ? NK_UP: NK_DOWN;
        nk_triangle_from_direction(points, content, 0, 0, heading);
        nk_fill_triangle(out, points[0].x, points[0].y, points[1].x, points[1].y,
            points[2].x, points[2].y, foreground);
    } break;
    default:
    case NK_SYMBOL_NONE:
    case NK_SYMBOL_MAX: break;
    }
}

NK_INTERN int
nk_button_behavior(nk_flags *state, struct nk_rect r,
    const struct nk_input *i, enum nk_button_behavior behavior)
{
    int ret = 0;
    nk_widget_state_reset(state);
    if (!i) return 0;
    if (nk_input_is_mouse_hovering_rect(i, r)) {
        *state = NK_WIDGET_STATE_HOVERED;
        if (nk_input_is_mouse_down(i, NK_BUTTON_LEFT))
            *state = NK_WIDGET_STATE_ACTIVE;
        if (nk_input_has_mouse_click_in_rect(i, NK_BUTTON_LEFT, r)) {
            ret = (behavior != NK_BUTTON_DEFAULT) ?
                nk_input_is_mouse_down(i, NK_BUTTON_LEFT):
#ifdef NK_BUTTON_TRIGGER_ON_RELEASE
                nk_input_is_mouse_released(i, NK_BUTTON_LEFT);
#else
                nk_input_is_mouse_pressed(i, NK_BUTTON_LEFT);
#endif
        }
    }
    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(i, r))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(i, r))
        *state |= NK_WIDGET_STATE_LEFT;
    return ret;
}

NK_INTERN const struct nk_style_item*
nk_draw_button(struct nk_command_buffer *out,
    const struct nk_rect *bounds, nk_flags state,
    const struct nk_style_button *style)
{
    const struct nk_style_item *background;
    if (state & NK_WIDGET_STATE_HOVER)
        background = &style->hover;
    else if (state & NK_WIDGET_STATE_ACTIVED)
        background = &style->active;
    else background = &style->normal;

    if (background->type == NK_STYLE_ITEM_IMAGE) {
        nk_draw_image(out, *bounds, &background->data.image);
    } else {
        nk_fill_rect(out, *bounds, style->rounding, style->border_color);
        nk_fill_rect(out, nk_shrink_rect(*bounds, style->border), style->rounding,
                    background->data.color);
    }
    return background;
}

NK_INTERN int
nk_do_button(nk_flags *state, struct nk_command_buffer *out, struct nk_rect r,
    const struct nk_style_button *style, const struct nk_input *in,
    enum nk_button_behavior behavior, struct nk_rect *content)
{
    struct nk_rect bounds;
    NK_ASSERT(style);
    NK_ASSERT(state);
    NK_ASSERT(out);
    if (!out || !style)
        return nk_false;

    /* calculate button content space */
    content->x = r.x + style->padding.x + style->border;
    content->y = r.y + style->padding.y + style->border;
    content->w = r.w - 2 * style->padding.x + style->border;
    content->h = r.h - 2 * style->padding.y + style->border;

    /* execute button behavior */
    bounds.x = r.x - style->touch_padding.x;
    bounds.y = r.y - style->touch_padding.y;
    bounds.w = r.w + 2 * style->touch_padding.x;
    bounds.h = r.h + 2 * style->touch_padding.y;
    return nk_button_behavior(state, bounds, in, behavior);
}

NK_INTERN void
nk_draw_button_text(struct nk_command_buffer *out,
    const struct nk_rect *bounds, const struct nk_rect *content, nk_flags state,
    const struct nk_style_button *style, const char *txt, int len,
    nk_flags text_alignment, const struct nk_user_font *font)
{
    struct nk_text text;
    const struct nk_style_item *background;
    background = nk_draw_button(out, bounds, state, style);

    /* select correct colors/images */
    if (background->type == NK_STYLE_ITEM_COLOR)
        text.background = background->data.color;
    else text.background = style->text_background;
    if (state & NK_WIDGET_STATE_HOVER)
        text.text = style->text_hover;
    else if (state & NK_WIDGET_STATE_ACTIVED)
        text.text = style->text_active;
    else text.text = style->text_normal;

    text.padding = nk_vec2(0,0);
    nk_widget_text(out, *content, txt, len, &text, text_alignment, font);
}

NK_INTERN int
nk_do_button_text(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    const char *string, int len, nk_flags align, enum nk_button_behavior behavior,
    const struct nk_style_button *style, const struct nk_input *in,
    const struct nk_user_font *font)
{
    struct nk_rect content;
    int ret = nk_false;

    NK_ASSERT(state);
    NK_ASSERT(style);
    NK_ASSERT(out);
    NK_ASSERT(string);
    NK_ASSERT(font);
    if (!out || !style || !font || !string)
        return nk_false;

    ret = nk_do_button(state, out, bounds, style, in, behavior, &content);
    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (style->draw.button_text)
        style->draw.button_text(out, &bounds, &content, *state, style,
                                string, len, align, font);
    else nk_draw_button_text(out, &bounds, &content, *state, style,
                            string, len, align, font);
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return ret;
}

NK_INTERN void
nk_draw_button_symbol(struct nk_command_buffer *out,
    const struct nk_rect *bounds, const struct nk_rect *content,
    nk_flags state, const struct nk_style_button *style,
    enum nk_symbol_type type, const struct nk_user_font *font)
{
    struct nk_color sym, bg;
    const struct nk_style_item *background;

    /* select correct colors/images */
    background = nk_draw_button(out, bounds, state, style);
    if (background->type == NK_STYLE_ITEM_COLOR)
        bg = background->data.color;
    else bg = style->text_background;

    if (state & NK_WIDGET_STATE_HOVER)
        sym = style->text_hover;
    else if (state & NK_WIDGET_STATE_ACTIVED)
        sym = style->text_active;
    else sym = style->text_normal;
    nk_draw_symbol(out, type, *content, bg, sym, 1, font);
}

NK_INTERN int
nk_do_button_symbol(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    enum nk_symbol_type symbol, enum nk_button_behavior behavior,
    const struct nk_style_button *style, const struct nk_input *in,
    const struct nk_user_font *font)
{
    int ret;
    struct nk_rect content;

    NK_ASSERT(state);
    NK_ASSERT(style);
    NK_ASSERT(font);
    NK_ASSERT(out);
    if (!out || !style || !font || !state)
        return nk_false;

    ret = nk_do_button(state, out, bounds, style, in, behavior, &content);
    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (style->draw.button_symbol)
        style->draw.button_symbol(out, &bounds, &content, *state, style, symbol, font);
    else nk_draw_button_symbol(out, &bounds, &content, *state, style, symbol, font);
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return ret;
}

NK_INTERN void
nk_draw_button_image(struct nk_command_buffer *out,
    const struct nk_rect *bounds, const struct nk_rect *content,
    nk_flags state, const struct nk_style_button *style, const struct nk_image *img)
{
    nk_draw_button(out, bounds, state, style);
    nk_draw_image(out, *content, img);
}

NK_INTERN int
nk_do_button_image(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    struct nk_image img, enum nk_button_behavior b,
    const struct nk_style_button *style, const struct nk_input *in)
{
    int ret;
    struct nk_rect content;

    NK_ASSERT(state);
    NK_ASSERT(style);
    NK_ASSERT(out);
    if (!out || !style || !state)
        return nk_false;

    ret = nk_do_button(state, out, bounds, style, in, b, &content);
    content.x += style->image_padding.x;
    content.y += style->image_padding.y;
    content.w -= 2 * style->image_padding.x;
    content.h -= 2 * style->image_padding.y;

    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (style->draw.button_image)
        style->draw.button_image(out, &bounds, &content, *state, style, &img);
    else nk_draw_button_image(out, &bounds, &content, *state, style, &img);
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return ret;
}

NK_INTERN void
nk_draw_button_text_symbol(struct nk_command_buffer *out,
    const struct nk_rect *bounds, const struct nk_rect *label,
    const struct nk_rect *symbol, nk_flags state, const struct nk_style_button *style,
    const char *str, int len, enum nk_symbol_type type,
    const struct nk_user_font *font)
{
    struct nk_color sym;
    struct nk_text text;
    const struct nk_style_item *background;

    /* select correct background colors/images */
    background = nk_draw_button(out, bounds, state, style);
    if (background->type == NK_STYLE_ITEM_COLOR)
        text.background = background->data.color;
    else text.background = style->text_background;

    /* select correct text colors */
    if (state & NK_WIDGET_STATE_HOVER) {
        sym = style->text_hover;
        text.text = style->text_hover;
    } else if (state & NK_WIDGET_STATE_ACTIVED) {
        sym = style->text_active;
        text.text = style->text_active;
    } else {
        sym = style->text_normal;
        text.text = style->text_normal;
    }

    text.padding = nk_vec2(0,0);
    nk_draw_symbol(out, type, *symbol, style->text_background, sym, 0, font);
    nk_widget_text(out, *label, str, len, &text, NK_TEXT_CENTERED, font);
}

NK_INTERN int
nk_do_button_text_symbol(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    enum nk_symbol_type symbol, const char *str, int len, nk_flags align,
    enum nk_button_behavior behavior, const struct nk_style_button *style,
    const struct nk_user_font *font, const struct nk_input *in)
{
    int ret;
    struct nk_rect tri = {0,0,0,0};
    struct nk_rect content;

    NK_ASSERT(style);
    NK_ASSERT(out);
    NK_ASSERT(font);
    if (!out || !style || !font)
        return nk_false;

    ret = nk_do_button(state, out, bounds, style, in, behavior, &content);
    tri.y = content.y + (content.h/2) - font->height/2;
    tri.w = font->height; tri.h = font->height;
    if (align & NK_TEXT_ALIGN_LEFT) {
        tri.x = (content.x + content.w) - (2 * style->padding.x + tri.w);
        tri.x = NK_MAX(tri.x, 0);
    } else tri.x = content.x + 2 * style->padding.x;

    /* draw button */
    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (style->draw.button_text_symbol)
        style->draw.button_text_symbol(out, &bounds, &content, &tri,
                                    *state, style, str, len, symbol, font);
    else nk_draw_button_text_symbol(out, &bounds, &content, &tri,
                                    *state, style, str, len, symbol, font);
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return ret;
}

NK_INTERN void
nk_draw_button_text_image(struct nk_command_buffer *out,
    const struct nk_rect *bounds, const struct nk_rect *label,
    const struct nk_rect *image, nk_flags state, const struct nk_style_button *style,
    const char *str, int len, const struct nk_user_font *font,
    const struct nk_image *img)
{
    struct nk_text text;
    const struct nk_style_item *background;
    background = nk_draw_button(out, bounds, state, style);

    /* select correct colors */
    if (background->type == NK_STYLE_ITEM_COLOR)
        text.background = background->data.color;
    else text.background = style->text_background;
    if (state & NK_WIDGET_STATE_HOVER)
        text.text = style->text_hover;
    else if (state & NK_WIDGET_STATE_ACTIVED)
        text.text = style->text_active;
    else text.text = style->text_normal;

    text.padding = nk_vec2(0,0);
    nk_widget_text(out, *label, str, len, &text, NK_TEXT_CENTERED, font);
    nk_draw_image(out, *image, img);
}

NK_INTERN int
nk_do_button_text_image(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    struct nk_image img, const char* str, int len, nk_flags align,
    enum nk_button_behavior behavior, const struct nk_style_button *style,
    const struct nk_user_font *font, const struct nk_input *in)
{
    int ret;
    struct nk_rect icon;
    struct nk_rect content;

    NK_ASSERT(style);
    NK_ASSERT(state);
    NK_ASSERT(font);
    NK_ASSERT(out);
    if (!out || !font || !style || !str)
        return nk_false;

    ret = nk_do_button(state, out, bounds, style, in, behavior, &content);
    icon.y = bounds.y + style->padding.y;
    icon.w = icon.h = bounds.h - 2 * style->padding.y;
    if (align & NK_TEXT_ALIGN_LEFT) {
        icon.x = (bounds.x + bounds.w) - (2 * style->padding.x + icon.w);
        icon.x = NK_MAX(icon.x, 0);
    } else icon.x = bounds.x + 2 * style->padding.x;

    icon.x += style->image_padding.x;
    icon.y += style->image_padding.y;
    icon.w -= 2 * style->image_padding.x;
    icon.h -= 2 * style->image_padding.y;

    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (style->draw.button_text_image)
        style->draw.button_text_image(out, &bounds, &content, &icon,
                                    *state, style, str, len, font, &img);
    else nk_draw_button_text_image(out, &bounds, &content, &icon,
                                    *state, style, str, len, font, &img);
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return ret;
}

/* ===============================================================
 *
 *                          TOGGLE
 *
 * ===============================================================*/
enum nk_toggle_type {
    NK_TOGGLE_CHECK,
    NK_TOGGLE_OPTION
};

NK_INTERN int
nk_toggle_behavior(const struct nk_input *in, struct nk_rect select,
    nk_flags *state, int active)
{
    nk_widget_state_reset(state);
    if (nk_button_behavior(state, select, in, NK_BUTTON_DEFAULT)) {
        *state = NK_WIDGET_STATE_ACTIVE;
        active = !active;
    }
    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(in, select))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, select))
        *state |= NK_WIDGET_STATE_LEFT;
    return active;
}

NK_INTERN void
nk_draw_checkbox(struct nk_command_buffer *out,
    nk_flags state, const struct nk_style_toggle *style, int active,
    const struct nk_rect *label, const struct nk_rect *selector,
    const struct nk_rect *cursors, const char *string, int len,
    const struct nk_user_font *font)
{
    const struct nk_style_item *background;
    const struct nk_style_item *cursor;
    struct nk_text text;

    /* select correct colors/images */
    if (state & NK_WIDGET_STATE_HOVER) {
        background = &style->hover;
        cursor = &style->cursor_hover;
        text.text = style->text_hover;
    } else if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->hover;
        cursor = &style->cursor_hover;
        text.text = style->text_active;
    } else {
        background = &style->normal;
        cursor = &style->cursor_normal;
        text.text = style->text_normal;
    }

    /* draw background and cursor */
    if (background->type == NK_STYLE_ITEM_IMAGE)
        nk_draw_image(out, *selector, &background->data.image);
    else nk_fill_rect(out, *selector, 0, background->data.color);
    if (active) {
        if (cursor->type == NK_STYLE_ITEM_IMAGE)
            nk_draw_image(out, *cursors, &cursor->data.image);
        else nk_fill_rect(out, *cursors, 0, cursor->data.color);
    }

    text.padding.x = 0;
    text.padding.y = 0;
    text.background = style->text_background;
    nk_widget_text(out, *label, string, len, &text, NK_TEXT_LEFT, font);
}

NK_INTERN void
nk_draw_option(struct nk_command_buffer *out,
    nk_flags state, const struct nk_style_toggle *style, int active,
    const struct nk_rect *label, const struct nk_rect *selector,
    const struct nk_rect *cursors, const char *string, int len,
    const struct nk_user_font *font)
{
    const struct nk_style_item *background;
    const struct nk_style_item *cursor;
    struct nk_text text;

    /* select correct colors/images */
    if (state & NK_WIDGET_STATE_HOVER) {
        background = &style->hover;
        cursor = &style->cursor_hover;
        text.text = style->text_hover;
    } else if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->hover;
        cursor = &style->cursor_hover;
        text.text = style->text_active;
    } else {
        background = &style->normal;
        cursor = &style->cursor_normal;
        text.text = style->text_normal;
    }

    /* draw background and cursor */
    if (background->type == NK_STYLE_ITEM_IMAGE)
        nk_draw_image(out, *selector, &background->data.image);
    else nk_fill_circle(out, *selector, background->data.color);
    if (active) {
        if (cursor->type == NK_STYLE_ITEM_IMAGE)
            nk_draw_image(out, *cursors, &cursor->data.image);
        else nk_fill_circle(out, *cursors, cursor->data.color);
    }

    text.padding.x = 0;
    text.padding.y = 0;
    text.background = style->text_background;
    nk_widget_text(out, *label, string, len, &text, NK_TEXT_LEFT, font);
}

NK_INTERN int
nk_do_toggle(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect r,
    int *active, const char *str, int len, enum nk_toggle_type type,
    const struct nk_style_toggle *style, const struct nk_input *in,
    const struct nk_user_font *font)
{
    int was_active;
    struct nk_rect bounds;
    struct nk_rect select;
    struct nk_rect cursor;
    struct nk_rect label;
    float cursor_pad;

    NK_ASSERT(style);
    NK_ASSERT(out);
    NK_ASSERT(font);
    if (!out || !style || !font || !active)
        return 0;

    r.w = NK_MAX(r.w, font->height + 2 * style->padding.x);
    r.h = NK_MAX(r.h, font->height + 2 * style->padding.y);

    /* add additional touch padding for touch screen devices */
    bounds.x = r.x - style->touch_padding.x;
    bounds.y = r.y - style->touch_padding.y;
    bounds.w = r.w + 2 * style->touch_padding.x;
    bounds.h = r.h + 2 * style->touch_padding.y;

    /* calculate the selector space */
    select.w = NK_MIN(r.h, font->height + style->padding.y);
    select.h = select.w;
    select.x = r.x + style->padding.x;
    select.y = (r.y + style->padding.y + (select.w / 2)) - (font->height / 2);
    cursor_pad = (type == NK_TOGGLE_OPTION) ?
        (float)(int)(select.w / 4):
        (float)(int)(select.h / 6);

    /* calculate the bounds of the cursor inside the selector */
    select.h = NK_MAX(select.w, cursor_pad * 2);
    cursor.h = select.h - cursor_pad * 2;
    cursor.w = cursor.h;
    cursor.x = select.x + cursor_pad;
    cursor.y = select.y + cursor_pad;

    /* label behind the selector */
    label.x = r.x + select.w + style->padding.x * 2;
    label.y = select.y;
    label.w = NK_MAX(r.x + r.w, label.x + style->padding.x);
    label.w -= (label.x + style->padding.x);
    label.h = select.w;

    /* update selector */
    was_active = *active;
    *active = nk_toggle_behavior(in, bounds, state, *active);

    /* draw selector */
    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (type == NK_TOGGLE_CHECK) {
        if (style->draw.checkbox)
            style->draw.checkbox(out, *state,
                style, *active, &label, &select, &cursor, str, len, font);
        else nk_draw_checkbox(out, *state, style, *active, &label,
                &select, &cursor, str, len, font);
    } else {
        if (style->draw.radio)
            style->draw.radio(out, *state, style,
                *active, &label, &select, &cursor, str, len, font);
        else nk_draw_option(out, *state, style, *active, &label,
            &select, &cursor, str, len, font);
    }
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return (was_active != *active);
}

/* ===============================================================
 *
 *                          SELECTABLE
 *
 * ===============================================================*/
NK_INTERN void
nk_draw_selectable(struct nk_command_buffer *out,
    nk_flags state, const struct nk_style_selectable *style, int active,
    const struct nk_rect *bounds, const char *string, int len,
    nk_flags align, const struct nk_user_font *font)
{
    const struct nk_style_item *background;
    struct nk_text text;
    text.padding = style->padding;

    /* select correct colors/images */
    if (!active) {
        if (state & NK_WIDGET_STATE_ACTIVED) {
            background = &style->pressed;
            text.text = style->text_pressed;
        } else if (state & NK_WIDGET_STATE_HOVER) {
            background = &style->hover;
            text.text = style->text_hover;
        } else {
            background = &style->normal;
            text.text = style->text_normal;
        }
    } else {
        if (state & NK_WIDGET_STATE_ACTIVED) {
            background = &style->pressed_active;
            text.text = style->text_pressed_active;
        } else if (state & NK_WIDGET_STATE_HOVER) {
            background = &style->hover_active;
            text.text = style->text_hover_active;
        } else {
            background = &style->normal_active;
            text.text = style->text_normal_active;
        }
    }

    /* draw selectable background and text */
    if (background->type == NK_STYLE_ITEM_IMAGE) {
        nk_draw_image(out, *bounds, &background->data.image);
        text.background = nk_rgba(0,0,0,0);
    } else {
        nk_fill_rect(out, *bounds, style->rounding, background->data.color);
        text.background = background->data.color;
    }
    nk_widget_text(out, *bounds, string, len, &text, align, font);
}

NK_INTERN int
nk_do_selectable(nk_flags *state, struct nk_command_buffer *out,
    struct nk_rect bounds, const char *str, int len, nk_flags align, int *value,
    const struct nk_style_selectable *style, const struct nk_input *in,
    const struct nk_user_font *font)
{
    int old_value;
    struct nk_rect touch;

    NK_ASSERT(state);
    NK_ASSERT(out);
    NK_ASSERT(str);
    NK_ASSERT(len);
    NK_ASSERT(value);
    NK_ASSERT(style);
    NK_ASSERT(font);

    if (!state || !out || !str || !len || !value || !style || !font) return 0;
    old_value = *value;

    /* remove padding */
    touch.x = bounds.x - style->touch_padding.x;
    touch.y = bounds.y - style->touch_padding.y;
    touch.w = bounds.w + style->touch_padding.x * 2;
    touch.h = bounds.h + style->touch_padding.y * 2;

    /* update button */
    if (nk_button_behavior(state, touch, in, NK_BUTTON_DEFAULT))
        *value = !(*value);

    /* draw selectable */
    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (style->draw)
        style->draw(out, *state, style, *value, &bounds,
            str, len, align, font);
    else nk_draw_selectable(out, *state, style, *value, &bounds,
            str, len, align, font);
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return old_value != *value;
}

/* ===============================================================
 *
 *                          SLIDER
 *
 * ===============================================================*/
NK_INTERN float
nk_slider_behavior(nk_flags *state, struct nk_rect *cursor,
    struct nk_input *in, const struct nk_style_slider *style,
    struct nk_rect bounds, float slider_min, float slider_max, float slider_value,
    float slider_step, float slider_steps)
{
    int left_mouse_down;
    int left_mouse_click_in_cursor;
    struct nk_rect visual_cursor;

    float bar_y = (bounds.y + cursor->h/2) - cursor->h/8;
    float bar_h = bounds.h/6;

    /* calculate visual cursor */
    visual_cursor.h = style->cursor_size.y;
    visual_cursor.w = style->cursor_size.x;
    visual_cursor.y = (bar_y + bar_h/2.0f) - visual_cursor.h/2.0f;
    visual_cursor.x = (slider_value <= slider_min) ? cursor->x: (slider_value >= slider_max) ?
        ((bounds.x + bounds.w) - cursor->w): cursor->x - (cursor->w/2);

    /* check if visual cursor is being dragged */
    nk_widget_state_reset(state);
    left_mouse_down = in && in->mouse.buttons[NK_BUTTON_LEFT].down;
    left_mouse_click_in_cursor = in && nk_input_has_mouse_click_down_in_rect(in,
            NK_BUTTON_LEFT, visual_cursor, nk_true);

    if (left_mouse_down && left_mouse_click_in_cursor)
    {
        const float d = in->mouse.pos.x - (cursor->x + cursor->w / 2.0f);
        const float pxstep = (bounds.w - (2 * style->padding.x)) / slider_steps;

        /* only update value if the next slider step is reached */
        *state = NK_WIDGET_STATE_ACTIVE;
        if (NK_ABS(d) >= pxstep) {
            float ratio = 0;
            const float steps = (float)((int)(NK_ABS(d) / pxstep));
            slider_value += (d > 0) ? (slider_step*steps) : -(slider_step*steps);
            slider_value = NK_CLAMP(slider_min, slider_value, slider_max);
            ratio = (slider_value - slider_min)/slider_step;
            cursor->x = bounds.x + (cursor->w * ratio);
            in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.x = cursor->x + cursor->w/2.0f;
        }
    }

    /* slider widget state */
    if (nk_input_is_mouse_hovering_rect(in, bounds))
        *state = NK_WIDGET_STATE_HOVERED;
    if (*state & NK_WIDGET_STATE_HOVER &&
        !nk_input_is_mouse_prev_hovering_rect(in, bounds))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, bounds))
        *state |= NK_WIDGET_STATE_LEFT;
    return slider_value;
}

NK_INTERN void
nk_draw_slider(struct nk_command_buffer *out, nk_flags state,
    const struct nk_style_slider *style, const struct nk_rect *bounds,
    const struct nk_rect *virtual_cursor, float min, float value, float max)
{
    struct nk_rect fill;
    struct nk_rect bar;
    struct nk_rect scursor;
    const struct nk_style_item *background;

    /* select correct slider images/colors */
    struct nk_color bar_color;
    const struct nk_style_item *cursor;
    if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->active;
        bar_color = style->bar_active;
        cursor = &style->cursor_active;
    } else if (state & NK_WIDGET_STATE_HOVER) {
        background = &style->hover;
        bar_color = style->bar_hover;
        cursor = &style->cursor_hover;
    } else {
        background = &style->normal;
        bar_color = style->bar_normal;
        cursor = &style->cursor_normal;
    }

    /* calculate slider background bar */
    bar.x = bounds->x;
    bar.y = (bounds->y + virtual_cursor->h/2) - virtual_cursor->h/8;
    bar.w = bounds->w;
    bar.h = bounds->h/6;

    /* resize virtual cursor to given size */
    scursor.h = style->cursor_size.y;
    scursor.w = style->cursor_size.x;
    scursor.y = (bar.y + bar.h/2.0f) - scursor.h/2.0f;
    scursor.x = (value <= min) ? virtual_cursor->x: (value >= max) ?
        ((bar.x + bar.w) - virtual_cursor->w):
        virtual_cursor->x - (virtual_cursor->w/2);

    /* filled background bar style */
    fill.w = (scursor.x + (scursor.w/2.0f)) - bar.x;
    fill.x = bar.x;
    fill.y = bar.y;
    fill.h = bar.h;

    /* draw background */
    if (background->type == NK_STYLE_ITEM_IMAGE) {
        nk_draw_image(out, *bounds, &background->data.image);
    } else {
        nk_fill_rect(out, *bounds, style->rounding, style->border_color);
        nk_fill_rect(out, nk_shrink_rect(*bounds, style->border), style->rounding,
            background->data.color);
    }

    /* draw slider bar */
    nk_fill_rect(out, bar, style->rounding, bar_color);
    nk_fill_rect(out, fill, style->rounding, style->bar_filled);

    /* draw cursor */
    if (cursor->type == NK_STYLE_ITEM_IMAGE)
        nk_draw_image(out, scursor, &cursor->data.image);
    else nk_fill_circle(out, scursor, cursor->data.color);
}

NK_INTERN float
nk_do_slider(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    float min, float val, float max, float step,
    const struct nk_style_slider *style, struct nk_input *in,
    const struct nk_user_font *font)
{
    float slider_range;
    float slider_min;
    float slider_max;
    float slider_value;
    float slider_steps;
    float cursor_offset;
    struct nk_rect cursor;

    NK_ASSERT(style);
    NK_ASSERT(out);
    if (!out || !style)
        return 0;

    /* remove padding from slider bounds */
    bounds.x = bounds.x + style->padding.x;
    bounds.y = bounds.y + style->padding.y;
    bounds.h = NK_MAX(bounds.h, 2 * style->padding.y);
    bounds.w = NK_MAX(bounds.w, 1 + bounds.h + 2 * style->padding.x);
    bounds.h -= 2 * style->padding.y;
    bounds.w -= 2 * style->padding.y;

    /* optional buttons */
    if (style->show_buttons) {
        nk_flags ws;
        struct nk_rect button;
        button.y = bounds.y;
        button.w = bounds.h;
        button.h = bounds.h;

        /* decrement button */
        button.x = bounds.x;
        if (nk_do_button_symbol(&ws, out, button, style->dec_symbol, NK_BUTTON_DEFAULT,
            &style->dec_button, in, font))
            val -= step;

        /* increment button */
        button.x = (bounds.x + bounds.w) - button.w;
        if (nk_do_button_symbol(&ws, out, button, style->inc_symbol, NK_BUTTON_DEFAULT,
            &style->inc_button, in, font))
            val += step;

        bounds.x = bounds.x + button.w + style->spacing.x;
        bounds.w = bounds.w - (2 * button.w + 2 * style->spacing.x);
    }

    /* make sure the provided values are correct */
    slider_max = NK_MAX(min, max);
    slider_min = NK_MIN(min, max);
    slider_value = NK_CLAMP(slider_min, val, slider_max);
    slider_range = slider_max - slider_min;
    slider_steps = slider_range / step;

    /* calculate slider virtual cursor bounds */
    cursor_offset = (slider_value - slider_min) / step;
    cursor.h = bounds.h;
    cursor.w = bounds.w / (slider_steps + 1);
    cursor.x = bounds.x + (cursor.w * cursor_offset);
    cursor.y = bounds.y;
    slider_value = nk_slider_behavior(state, &cursor, in, style, bounds,
                        slider_min, slider_max, slider_value, step, slider_steps);

    /* draw slider */
    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (style->draw)
        style->draw(out, *state, style, &bounds, &cursor,
            slider_min, slider_value, slider_max);
    else nk_draw_slider(out, *state, style, &bounds, &cursor,
        slider_min, slider_value, slider_max);
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return slider_value;
}

/* ===============================================================
 *
 *                          PROGRESSBAR
 *
 * ===============================================================*/
NK_INTERN nk_size
nk_progress_behavior(nk_flags *state, const struct nk_input *in,
    struct nk_rect r, nk_size max, nk_size value, int modifiable)
{
    nk_widget_state_reset(state);
    if (in && modifiable && nk_input_is_mouse_hovering_rect(in, r)) {
        int left_mouse_down = in->mouse.buttons[NK_BUTTON_LEFT].down;
        int left_mouse_click_in_cursor = nk_input_has_mouse_click_down_in_rect(in,
            NK_BUTTON_LEFT, r, nk_true);

        if (left_mouse_down && left_mouse_click_in_cursor) {
            float ratio = NK_MAX(0, (float)(in->mouse.pos.x - r.x)) / (float)r.w;
            value = (nk_size)NK_MAX(0,((float)max * ratio));
            *state = NK_WIDGET_STATE_ACTIVE;
        } else *state = NK_WIDGET_STATE_HOVERED;
    }

    /* set progressbar widget state */
    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(in, r))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, r))
        *state |= NK_WIDGET_STATE_LEFT;

    if (!max) return value;
    value = NK_MIN(value, max);
    return value;
}

NK_INTERN void
nk_draw_progress(struct nk_command_buffer *out, nk_flags state,
    const struct nk_style_progress *style, const struct nk_rect *bounds,
    const struct nk_rect *scursor, nk_size value, nk_size max)
{
    const struct nk_style_item *background;
    const struct nk_style_item *cursor;

    NK_UNUSED(max);
    NK_UNUSED(value);

    /* select correct colors/images to draw */
    if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->active;
        cursor = &style->cursor_active;
    } else if (state & NK_WIDGET_STATE_HOVER){
        background = &style->hover;
        cursor = &style->cursor_hover;
    } else {
        background = &style->normal;
        cursor = &style->cursor_normal;
    }

    /* draw background */
    if (background->type == NK_STYLE_ITEM_IMAGE)
        nk_draw_image(out, *bounds, &background->data.image);
    else nk_fill_rect(out, *bounds, style->rounding, background->data.color);

    /* draw cursor */
    if (cursor->type == NK_STYLE_ITEM_IMAGE)
        nk_draw_image(out, *scursor, &cursor->data.image);
    else nk_fill_rect(out, *scursor, style->rounding, cursor->data.color);
}

NK_INTERN nk_size
nk_do_progress(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect bounds,
    nk_size value, nk_size max, int modifiable,
    const struct nk_style_progress *style, const struct nk_input *in)
{
    float prog_scale;
    nk_size prog_value;
    struct nk_rect cursor;

    NK_ASSERT(style);
    NK_ASSERT(out);
    if (!out || !style) return 0;

    /* calculate progressbar cursor */
    cursor.w = NK_MAX(bounds.w, 2 * style->padding.x);
    cursor.h = NK_MAX(bounds.h, 2 * style->padding.y);
    cursor = nk_pad_rect(bounds, nk_vec2(style->padding.x, style->padding.y));
    prog_scale = (float)value / (float)max;
    cursor.w = (bounds.w - 2) * prog_scale;

    /* update progressbar */
    prog_value = NK_MIN(value, max);
    prog_value = nk_progress_behavior(state, in, bounds, max, prog_value, modifiable);

    /* draw progressbar */
    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (style->draw)
        style->draw(out, *state, style, &bounds, &cursor, value, max);
    else nk_draw_progress(out, *state, style, &bounds, &cursor, value, max);
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return prog_value;
}

/* ===============================================================
 *
 *                          SCROLLBAR
 *
 * ===============================================================*/
NK_INTERN float
nk_scrollbar_behavior(nk_flags *state, struct nk_input *in,
    int has_scrolling, struct nk_rect scroll,
    struct nk_rect cursor, float scroll_offset,
    float target, float scroll_step, enum nk_orientation o)
{
    int left_mouse_down;
    int left_mouse_click_in_cursor;

    nk_widget_state_reset(state);
    if (!in) return scroll_offset;

    left_mouse_down = in->mouse.buttons[NK_BUTTON_LEFT].down;
    left_mouse_click_in_cursor = nk_input_has_mouse_click_down_in_rect(in,
        NK_BUTTON_LEFT, cursor, nk_true);
    if (nk_input_is_mouse_hovering_rect(in, scroll))
        *state = NK_WIDGET_STATE_HOVERED;

    if (left_mouse_down && left_mouse_click_in_cursor) {
        /* update cursor by mouse dragging */
        float pixel, delta;
        *state = NK_WIDGET_STATE_ACTIVE;
        if (o == NK_VERTICAL) {
            float cursor_y;
            pixel = in->mouse.delta.y;
            delta = (pixel / scroll.h) * target;
            scroll_offset = NK_CLAMP(0, scroll_offset + delta, target - scroll.h);
            cursor_y = scroll.y + ((scroll_offset/target) * scroll.h);
            in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.y = cursor_y + cursor.h/2.0f;
        } else {
            float cursor_x;
            pixel = in->mouse.delta.x;
            delta = (pixel / scroll.w) * target;
            scroll_offset = NK_CLAMP(0, scroll_offset + delta, target - scroll.w);
            cursor_x = scroll.x + ((scroll_offset/target) * scroll.w);
            in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.x = cursor_x + cursor.w/2.0f;
        }
    } else if (has_scrolling && ((in->mouse.scroll_delta<0) ||
            (in->mouse.scroll_delta>0))) {
        /* update cursor by mouse scrolling */
        scroll_offset = scroll_offset + scroll_step * (-in->mouse.scroll_delta);
        if (o == NK_VERTICAL)
            scroll_offset = NK_CLAMP(0, scroll_offset, target - scroll.h);
        else scroll_offset = NK_CLAMP(0, scroll_offset, target - scroll.w);
    }
    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(in, scroll))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, scroll))
        *state |= NK_WIDGET_STATE_LEFT;
    return scroll_offset;
}

NK_INTERN void
nk_draw_scrollbar(struct nk_command_buffer *out, nk_flags state,
    const struct nk_style_scrollbar *style, const struct nk_rect *bounds,
    const struct nk_rect *scroll)
{
    const struct nk_style_item *background;
    const struct nk_style_item *cursor;

    /* select correct colors/images to draw */
    if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->active;
        cursor = &style->cursor_active;
    } else if (state & NK_WIDGET_STATE_HOVER) {
        background = &style->hover;
        cursor = &style->cursor_hover;
    } else {
        background = &style->normal;
        cursor = &style->cursor_normal;
    }

    /* draw background */
    if (background->type == NK_STYLE_ITEM_COLOR) {
        nk_fill_rect(out, *bounds, style->rounding, style->border_color);
        nk_fill_rect(out, nk_shrink_rect(*bounds,style->border),
            style->rounding, background->data.color);
    } else {
        nk_draw_image(out, *bounds, &background->data.image);
    }

    /* draw cursor */
    if (cursor->type == NK_STYLE_ITEM_IMAGE)
        nk_draw_image(out, *scroll, &cursor->data.image);
    else nk_fill_rect(out, *scroll, style->rounding, cursor->data.color);
}

NK_INTERN float
nk_do_scrollbarv(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect scroll, int has_scrolling,
    float offset, float target, float step, float button_pixel_inc,
    const struct nk_style_scrollbar *style, struct nk_input *in,
    const struct nk_user_font *font)
{
    struct nk_rect cursor;
    float scroll_step;
    float scroll_offset;
    float scroll_off;
    float scroll_ratio;

    NK_ASSERT(out);
    NK_ASSERT(style);
    NK_ASSERT(state);
    if (!out || !style) return 0;

    scroll.w = NK_MAX(scroll.w, 1);
    scroll.h = NK_MAX(scroll.h, 2 * scroll.w);
    if (target <= scroll.h) return 0;

    /* optional scrollbar buttons */
    if (style->show_buttons) {
        nk_flags ws;
        float scroll_h;
        struct nk_rect button;
        button.x = scroll.x;
        button.w = scroll.w;
        button.h = scroll.w;

        scroll_h = scroll.h - 2 * button.h;
        scroll_step = NK_MIN(step, button_pixel_inc);

        /* decrement button */
        button.y = scroll.y;
        if (nk_do_button_symbol(&ws, out, button, style->dec_symbol,
            NK_BUTTON_REPEATER, &style->dec_button, in, font))
            offset = offset - scroll_step;

        /* increment button */
        button.y = scroll.y + scroll.h - button.h;
        if (nk_do_button_symbol(&ws, out, button, style->inc_symbol,
            NK_BUTTON_REPEATER, &style->inc_button, in, font))
            offset = offset + scroll_step;

        scroll.y = scroll.y + button.h;
        scroll.h = scroll_h;
    }

    /* calculate scrollbar constants */
    scroll_step = NK_MIN(step, scroll.h);
    scroll_offset = NK_CLAMP(0, offset, target - scroll.h);
    scroll_ratio = scroll.h / target;
    scroll_off = scroll_offset / target;

    /* calculate scrollbar cursor bounds */
    cursor.h = (scroll_ratio * scroll.h - 2);
    cursor.y = scroll.y + (scroll_off * scroll.h) + 1;
    cursor.w = scroll.w - 2;
    cursor.x = scroll.x + 1;

    /* update scrollbar */
    scroll_offset = nk_scrollbar_behavior(state, in, has_scrolling, scroll, cursor,
        scroll_offset, target, scroll_step, NK_VERTICAL);
    scroll_off = scroll_offset / target;
    cursor.y = scroll.y + (scroll_off * scroll.h);

    /* draw scrollbar */
    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (style->draw)
        style->draw(out, *state, style, &scroll, &cursor);
    else nk_draw_scrollbar(out, *state, style, &scroll, &cursor);
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return scroll_offset;
}

NK_INTERN float
nk_do_scrollbarh(nk_flags *state,
    struct nk_command_buffer *out, struct nk_rect scroll, int has_scrolling,
    float offset, float target, float step, float button_pixel_inc,
    const struct nk_style_scrollbar *style, struct nk_input *in,
    const struct nk_user_font *font)
{
    struct nk_rect cursor;
    float scroll_step;
    float scroll_offset;
    float scroll_off;
    float scroll_ratio;

    NK_ASSERT(out);
    NK_ASSERT(style);
    if (!out || !style) return 0;

    /* scrollbar background */
    scroll.h = NK_MAX(scroll.h, 1);
    scroll.w = NK_MAX(scroll.w, 2 * scroll.h);
    if (target <= scroll.w) return 0;

    /* optional scrollbar buttons */
    if (style->show_buttons) {
        nk_flags ws;
        float scroll_w;
        struct nk_rect button;
        button.y = scroll.y;
        button.w = scroll.h;
        button.h = scroll.h;

        scroll_w = scroll.w - 2 * button.w;
        scroll_step = NK_MIN(step, button_pixel_inc);

        /* decrement button */
        button.x = scroll.x;
        if (nk_do_button_symbol(&ws, out, button, style->dec_symbol,
            NK_BUTTON_REPEATER, &style->dec_button, in, font))
            offset = offset - scroll_step;

        /* increment button */
        button.x = scroll.x + scroll.w - button.w;
        if (nk_do_button_symbol(&ws, out, button, style->inc_symbol,
            NK_BUTTON_REPEATER, &style->inc_button, in, font))
            offset = offset + scroll_step;

        scroll.x = scroll.x + button.w;
        scroll.w = scroll_w;
    }

    /* calculate scrollbar constants */
    scroll_step = NK_MIN(step, scroll.w);
    scroll_offset = NK_CLAMP(0, offset, target - scroll.w);
    scroll_ratio = scroll.w / target;
    scroll_off = scroll_offset / target;

    /* calculate cursor bounds */
    cursor.w = scroll_ratio * scroll.w - 2;
    cursor.x = scroll.x + (scroll_off * scroll.w) + 1;
    cursor.h = scroll.h - 2;
    cursor.y = scroll.y + 1;

    /* update scrollbar */
    scroll_offset = nk_scrollbar_behavior(state, in, has_scrolling, scroll, cursor,
        scroll_offset, target, scroll_step, NK_HORIZONTAL);
    scroll_off = scroll_offset / target;
    cursor.x = scroll.x + (scroll_off * scroll.w);

    /* draw scrollbar */
    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (style->draw)
        style->draw(out, *state, style, &scroll, &cursor);
    else nk_draw_scrollbar(out, *state, style, &scroll, &cursor);
    if (style->draw_end)
        style->draw_end(out, style->userdata);
    return scroll_offset;
}

/* ===============================================================
 *
 *                          FILTER
 *
 * ===============================================================*/
NK_API int nk_filter_default(const struct nk_text_edit *box, nk_rune unicode)
{(void)unicode;NK_UNUSED(box);return nk_true;}

NK_API int
nk_filter_ascii(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if (unicode > 128) return nk_false;
    else return nk_true;
}

NK_API int
nk_filter_float(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if ((unicode < '0' || unicode > '9') && unicode != '.' && unicode != '-')
        return nk_false;
    else return nk_true;
}

NK_API int
nk_filter_decimal(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if ((unicode < '0' || unicode > '9') && unicode != '-')
        return nk_false;
    else return nk_true;
}

NK_API int
nk_filter_hex(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if ((unicode < '0' || unicode > '9') &&
        (unicode < 'a' || unicode > 'f') &&
        (unicode < 'A' || unicode > 'F'))
        return nk_false;
    else return nk_true;
}

NK_API int
nk_filter_oct(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if (unicode < '0' || unicode > '7')
        return nk_false;
    else return nk_true;
}

NK_API int
nk_filter_binary(const struct nk_text_edit *box, nk_rune unicode)
{
    NK_UNUSED(box);
    if (unicode != '0' && unicode != '1')
        return nk_false;
    else return nk_true;
}

/* ===============================================================
 *
 *                          EDIT
 *
 * ===============================================================*/
NK_INTERN void
nk_edit_draw_text(struct nk_command_buffer *out,
    const struct nk_style_edit *style, float pos_x, float pos_y,
    float x_offset, const char *text, int byte_len, float row_height,
    const struct nk_user_font *font, struct nk_color background,
    struct nk_color foreground, int is_selected)
{
    NK_ASSERT(out);
    NK_ASSERT(font);
    NK_ASSERT(style);
    if (!text || !byte_len || !out || !style) return;

    {int glyph_len = 0;
    nk_rune unicode = 0;
    int text_len = 0;
    float line_width = 0;
    float glyph_width;
    const char *line = text;
    float line_offset = 0;
    int line_count = 0;

    struct nk_text txt;
    txt.padding = nk_vec2(0,0);
    txt.background = background;
    txt.text = foreground;

    glyph_len = nk_utf_decode(text+text_len, &unicode, byte_len-text_len);
    if (!glyph_len) return;
    while ((text_len < byte_len) && glyph_len)
    {
        if (unicode == '\n') {
            /* new line sepeator so draw previous line */
            struct nk_rect label;
            label.y = pos_y + line_offset;
            label.h = row_height;
            label.w = line_width;
            label.x = pos_x;
            if (!line_count)
                label.x += x_offset;

            if (is_selected) /* selection needs to draw different background color */
                nk_fill_rect(out, label, 0, background);
            nk_widget_text(out, label, line, (int)((text + text_len) - line),
                &txt, NK_TEXT_CENTERED, font);

            text_len++;
            line_count++;
            line_width = 0;
            line = text + text_len;
            line_offset += row_height;
            glyph_len = nk_utf_decode(text + text_len, &unicode, (int)(byte_len-text_len));
            continue;
        }
        if (unicode == '\r') {
            text_len++;
            glyph_len = nk_utf_decode(text + text_len, &unicode, byte_len-text_len);
            continue;
        }
        glyph_width = font->width(font->userdata, font->height, text+text_len, glyph_len);
        line_width += (float)glyph_width;
        text_len += glyph_len;
        glyph_len = nk_utf_decode(text + text_len, &unicode, byte_len-text_len);
        continue;
    }
    if (line_width > 0) {
        /* draw last line */
        struct nk_rect label;
        label.y = pos_y + line_offset;
        label.h = row_height;
        label.w = line_width;
        label.x = pos_x;
        if (!line_count)
            label.x += x_offset;

        if (is_selected)
            nk_fill_rect(out, label, 0, background);
        nk_widget_text(out, label, line, (int)((text + text_len) - line),
            &txt, NK_TEXT_LEFT, font);
    }}
}

NK_INTERN nk_flags
nk_do_edit(nk_flags *state, struct nk_command_buffer *out,
    struct nk_rect bounds, nk_flags flags, nk_filter filter,
    struct nk_text_edit *edit, const struct nk_style_edit *style,
    struct nk_input *in, const struct nk_user_font *font)
{
    struct nk_rect area;
    nk_flags ret = 0;
    float row_height;
    char prev_state = 0;
    char is_hovered = 0;
    char select_all = 0;
    char cursor_follow = 0;

    NK_ASSERT(state);
    NK_ASSERT(out);
    NK_ASSERT(style);
    if (!state || !out || !style)
        return ret;

    /* visible text area calculation */
    area.x = bounds.x + style->padding.x + style->border;
    area.y = bounds.y + style->padding.y + style->border;
    area.w = bounds.w - (2.0f * style->padding.x + 2 * style->border);
    area.h = bounds.h - (2.0f * style->padding.y + 2 * style->border);
    if (flags & NK_EDIT_MULTILINE)
        area.h = area.h - style->scrollbar_size.y;
    row_height = (flags & NK_EDIT_MULTILINE)? font->height + style->row_padding: area.h;

    /* update edit state */
    prev_state = (char)edit->active;
    is_hovered = (char)nk_input_is_mouse_hovering_rect(in, bounds);
    if (in && in->mouse.buttons[NK_BUTTON_LEFT].clicked && in->mouse.buttons[NK_BUTTON_LEFT].down) {
        edit->active = NK_INBOX(in->mouse.pos.x, in->mouse.pos.y,
                                bounds.x, bounds.y, bounds.w, bounds.h);
    }

    /* (de)activate text editor */
    if (!prev_state && edit->active) {
        const enum nk_text_edit_type type = (flags & NK_EDIT_MULTILINE) ?
            NK_TEXT_EDIT_MULTI_LINE: NK_TEXT_EDIT_SINGLE_LINE;
        nk_textedit_clear_state(edit, type, filter);
        if (flags & NK_EDIT_ALWAYS_INSERT_MODE)
            edit->mode = NK_TEXT_EDIT_MODE_INSERT;
        if (flags & NK_EDIT_AUTO_SELECT)
            select_all = nk_true;
    } else if (!edit->active) edit->mode = NK_TEXT_EDIT_MODE_VIEW;

    ret = (edit->active) ? NK_EDIT_ACTIVE: NK_EDIT_INACTIVE;
    if (prev_state != edit->active)
        ret |= (edit->active) ? NK_EDIT_ACTIVATED: NK_EDIT_DEACTIVATED;

    /* handle user input */
    if (edit->active && in && !(flags & NK_EDIT_READ_ONLY))
    {
        int shift_mod = in->keyboard.keys[NK_KEY_SHIFT].down;
        const float mouse_x = (in->mouse.pos.x - area.x) + edit->scrollbar.x;
        const float mouse_y = (!(flags & NK_EDIT_MULTILINE)) ?
            (in->mouse.pos.y - (area.y + area.h * 0.5f)) + edit->scrollbar.y:
            (in->mouse.pos.y - area.y) + edit->scrollbar.y;

        /* mouse click handler */
        if (select_all) {
            nk_textedit_select_all(edit);
        } else if (is_hovered && in->mouse.buttons[NK_BUTTON_LEFT].down &&
            in->mouse.buttons[NK_BUTTON_LEFT].clicked) {
            nk_textedit_click(edit, mouse_x, mouse_y, font, row_height);
        } else if (is_hovered && in->mouse.buttons[NK_BUTTON_LEFT].down &&
            (in->mouse.delta.x != 0.0f || in->mouse.delta.y != 0.0f)) {
            nk_textedit_drag(edit, mouse_x, mouse_y, font, row_height);
            cursor_follow = nk_true;
        } else if (is_hovered && in->mouse.buttons[NK_BUTTON_RIGHT].clicked &&
            in->mouse.buttons[NK_BUTTON_RIGHT].down) {
            nk_textedit_key(edit, NK_KEY_TEXT_WORD_LEFT, nk_false, font, row_height);
            nk_textedit_key(edit, NK_KEY_TEXT_WORD_RIGHT, nk_true, font, row_height);
            cursor_follow = nk_true;
        }

        {int i; /* keyboard input */
        int old_mode = edit->mode;
        for (i = 0; i < NK_KEY_MAX; ++i) {
            /* special case */
            if (i == NK_KEY_ENTER || i == NK_KEY_TAB) continue; /* special case */
            if (nk_input_is_key_pressed(in, (enum nk_keys)i)) {
                nk_textedit_key(edit, (enum nk_keys)i, shift_mod, font, row_height);
                cursor_follow = nk_true;
            }
        }
        if (old_mode != edit->mode) {
            in->keyboard.text_len = 0;
        }}

        /* text input */
        edit->filter = filter;
        if (in->keyboard.text_len) {
            nk_textedit_text(edit, in->keyboard.text, in->keyboard.text_len);
            cursor_follow = nk_true;
            in->keyboard.text_len = 0;
        }

        /* enter key handler */
        if (nk_input_is_key_pressed(in, NK_KEY_ENTER)) {
            cursor_follow = nk_true;
            if (flags & NK_EDIT_CTRL_ENTER_NEWLINE && shift_mod) {
                nk_textedit_text(edit, "\n", 1);
            } else if (flags & NK_EDIT_SIG_ENTER) {
                ret = NK_EDIT_INACTIVE;
                ret |= NK_EDIT_DEACTIVATED;
                ret |= NK_EDIT_COMMITED;
                edit->active = 0;
            } else nk_textedit_text(edit, "\n", 1);
        }

        /* cut & copy handler */
        {int copy= nk_input_is_key_pressed(in, NK_KEY_COPY);
        int cut = nk_input_is_key_pressed(in, NK_KEY_CUT);
        if ((copy || cut) && (flags & NK_EDIT_CLIPBOARD))
        {
            int glyph_len;
            nk_rune unicode;
            const char *text;
            int b = edit->select_start;
            int e = edit->select_end;

            int begin = NK_MIN(b, e);
            int end = NK_MAX(b, e);
            text = nk_str_at_const(&edit->string, begin, &unicode, &glyph_len);
            if (edit->clip.copy)
                edit->clip.copy(edit->clip.userdata, text, end - begin);
            if (cut){
                nk_textedit_cut(edit);
                cursor_follow = nk_true;
            }
        }}

        /* paste handler */
        {int paste = nk_input_is_key_pressed(in, NK_KEY_PASTE);
        if (paste && (flags & NK_EDIT_CLIPBOARD) && edit->clip.paste) {
            edit->clip.paste(edit->clip.userdata, edit);
            cursor_follow = nk_true;
        }}

        /* tab handler */
        {int tab = nk_input_is_key_pressed(in, NK_KEY_TAB);
        if (tab && (flags & NK_EDIT_ALLOW_TAB)) {
            nk_textedit_text(edit, "    ", 4);
            cursor_follow = nk_true;
        }}
    }

    /* set widget state */
    if (edit->active)
        *state = NK_WIDGET_STATE_ACTIVE;
    else nk_widget_state_reset(state);

    if (is_hovered)
        *state |= NK_WIDGET_STATE_HOVERED;

    /* DRAW EDIT */
    {struct nk_rect clip;
    struct nk_rect old_clip = out->clip;
    const char *text = nk_str_get_const(&edit->string);
    int len = nk_str_len_char(&edit->string);

    {/* select background colors/images  */
    const struct nk_style_item *background;
    if (*state & NK_WIDGET_STATE_ACTIVED)
        background = &style->active;
    else if (*state & NK_WIDGET_STATE_HOVER)
        background = &style->hover;
    else background = &style->normal;

    /* draw background frame */
    if (background->type == NK_STYLE_ITEM_COLOR) {
        nk_fill_rect(out, bounds, style->rounding, style->border_color);
        nk_fill_rect(out, nk_shrink_rect(bounds,style->border),
            style->rounding, background->data.color);
    } else nk_draw_image(out, bounds, &background->data.image);}

    area.w -= style->cursor_size;
    nk_unify(&clip, &old_clip, area.x, area.y, area.x + area.w, area.y + area.h);
    nk_push_scissor(out, clip);
    if (edit->active)
    {
        int total_lines = 1;
        struct nk_vec2 text_size = nk_vec2(0,0);

        /* text pointer positions */
        const char *cursor_ptr = 0;
        const char *select_begin_ptr = 0;
        const char *select_end_ptr = 0;

        /* 2D pixel positions */
        struct nk_vec2 cursor_pos = nk_vec2(0,0);
        struct nk_vec2 selection_offset_start = nk_vec2(0,0);
        struct nk_vec2 selection_offset_end = nk_vec2(0,0);

        int selection_begin = NK_MIN(edit->select_start, edit->select_end);
        int selection_end = NK_MAX(edit->select_start, edit->select_end);

        /* calculate total line count + total space + cursor/selection position */
        float line_width = 0.0f;
        if (text && len)
        {
            /* utf8 encoding */
            float glyph_width;
            int glyph_len = 0;
            nk_rune unicode = 0;
            int text_len = 0;
            int glyphs = 0;
            int row_begin = 0;

            glyph_len = nk_utf_decode(text, &unicode, len);
            glyph_width = font->width(font->userdata, font->height, text, glyph_len);
            line_width = 0;

            /* iterate all lines */
            while ((text_len < len) && glyph_len)
            {
                /* set cursor 2D position and line */
                if (!cursor_ptr && glyphs == edit->cursor)
                {
                    int glyph_offset;
                    struct nk_vec2 out_offset;
                    struct nk_vec2 row_size;
                    const char *remaining;

                    /* calculate 2d position */
                    cursor_pos.y = (float)(total_lines-1) * row_height;
                    row_size = nk_text_calculate_text_bounds(font, text+row_begin,
                                text_len-row_begin, row_height, &remaining,
                                &out_offset, &glyph_offset, NK_STOP_ON_NEW_LINE);
                    cursor_pos.x = row_size.x;
                    cursor_ptr = text + text_len;
                }

                /* set start selection 2D position and line */
                if (!select_begin_ptr && edit->select_start != edit->select_end &&
                    glyphs == selection_begin)
                {
                    int glyph_offset;
                    struct nk_vec2 out_offset;
                    struct nk_vec2 row_size;
                    const char *remaining;

                    /* calculate 2d position */
                    selection_offset_start.y = (float)(total_lines-1) * row_height;
                    row_size = nk_text_calculate_text_bounds(font, text+row_begin,
                                text_len-row_begin, row_height, &remaining,
                                &out_offset, &glyph_offset, NK_STOP_ON_NEW_LINE);
                    selection_offset_start.x = row_size.x;
                    select_begin_ptr = text + text_len;
                }

                /* set end selection 2D position and line */
                if (!select_end_ptr && edit->select_start != edit->select_end &&
                    glyphs == selection_end)
                {
                    int glyph_offset;
                    struct nk_vec2 out_offset;
                    struct nk_vec2 row_size;
                    const char *remaining;

                    /* calculate 2d position */
                    selection_offset_end.y = (float)(total_lines-1) * row_height;
                    row_size = nk_text_calculate_text_bounds(font, text+row_begin,
                                text_len-row_begin, row_height, &remaining,
                                &out_offset, &glyph_offset, NK_STOP_ON_NEW_LINE);
                    selection_offset_end.x = row_size.x;
                    select_end_ptr = text + text_len;
                }
                if (unicode == '\n') {
                    text_size.x = NK_MAX(text_size.x, line_width);
                    total_lines++;
                    line_width = 0;
                    text_len++;
                    glyphs++;
                    row_begin = text_len;
                    glyph_len = nk_utf_decode(text + text_len, &unicode, len-text_len);
                    continue;
                }

                glyphs++;
                text_len += glyph_len;
                line_width += (float)glyph_width;

                glyph_width = font->width(font->userdata, font->height,
                    text+text_len, glyph_len);
                glyph_len = nk_utf_decode(text + text_len, &unicode, len-text_len);
                continue;
            }
            text_size.y = (float)total_lines * row_height;

            /* handle case if cursor is at end of text buffer */
            if (!cursor_ptr && edit->cursor == edit->string.len) {
                cursor_pos.x = line_width;
                cursor_pos.y = text_size.y - row_height;
            }
        }
        {
            /* scrollbar */
            if (cursor_follow)
            {
                /* update scrollbar to follow cursor */
                if (!(flags & NK_EDIT_NO_HORIZONTAL_SCROLL)) {
                    /* horizontal scroll */
                    const float scroll_increment = area.w * 0.25f;
                    if (cursor_pos.x < edit->scrollbar.x)
                        edit->scrollbar.x = (float)(int)NK_MAX(0.0f, cursor_pos.x - scroll_increment);
                    if (cursor_pos.x >= edit->scrollbar.x + area.w)
                        edit->scrollbar.x = (float)(int)NK_MAX(0.0f, cursor_pos.x);
                } else edit->scrollbar.x = 0;

                if (flags & NK_EDIT_MULTILINE) {
                    /* vertical scroll */
                    if (cursor_pos.y < edit->scrollbar.y)
                        edit->scrollbar.y = NK_MAX(0.0f, cursor_pos.y - row_height);
                    if (cursor_pos.y >= edit->scrollbar.y + area.h)
                        edit->scrollbar.y = edit->scrollbar.y + row_height;
                } else edit->scrollbar.y = 0;
            }

            /* scrollbar widget */
            {nk_flags ws;
            struct nk_rect scroll;
            float scroll_target;
            float scroll_offset;
            float scroll_step;
            float scroll_inc;

            scroll.x = (bounds.x + bounds.w) - style->scrollbar_size.x;
            scroll.y = bounds.y;
            scroll.w = style->scrollbar_size.x;
            scroll.h = bounds.h;

            scroll_offset = edit->scrollbar.y;
            scroll_step = scroll.h * 0.10f;
            scroll_inc = scroll.h * 0.01f;
            scroll_target = text_size.y;
            edit->scrollbar.y = nk_do_scrollbarv(&ws, out, bounds, 0,
                    scroll_offset, scroll_target, scroll_step, scroll_inc,
                    &style->scrollbar, in, font);}
        }

        /* draw text */
        {struct nk_color background_color;
        struct nk_color text_color;
        struct nk_color sel_background_color;
        struct nk_color sel_text_color;
        struct nk_color cursor_color;
        struct nk_color cursor_text_color;
        const struct nk_style_item *background;

        /* select correct colors to draw */
        if (*state & NK_WIDGET_STATE_ACTIVED) {
            background = &style->active;
            text_color = style->text_active;
            sel_text_color = style->selected_text_hover;
            sel_background_color = style->selected_hover;
            cursor_color = style->cursor_hover;
            cursor_text_color = style->cursor_text_hover;
        } else if (*state & NK_WIDGET_STATE_HOVER) {
            background = &style->hover;
            text_color = style->text_hover;
            sel_text_color = style->selected_text_hover;
            sel_background_color = style->selected_hover;
            cursor_text_color = style->cursor_text_hover;
            cursor_color = style->cursor_hover;
        } else {
            background = &style->normal;
            text_color = style->text_normal;
            sel_text_color = style->selected_text_normal;
            sel_background_color = style->selected_normal;
            cursor_color = style->cursor_normal;
            cursor_text_color = style->cursor_text_normal;
        }
        if (background->type == NK_STYLE_ITEM_IMAGE)
            background_color = nk_rgba(0,0,0,0);
        else background_color = background->data.color;


        if (edit->select_start == edit->select_end) {
            /* no selection so just draw the complete text */
            const char *begin = nk_str_get_const(&edit->string);
            int l = nk_str_len_char(&edit->string);
            nk_edit_draw_text(out, style, area.x - edit->scrollbar.x,
                area.y - edit->scrollbar.y, 0, begin, l, row_height, font, 
                background_color, text_color, nk_false);
        } else {
            /* edit has selection so draw 1-3 text chunks */
            if (edit->select_start != edit->select_end && selection_begin > 0){
                /* draw unselected text before selection */
                const char *begin = nk_str_get_const(&edit->string);
                NK_ASSERT(select_begin_ptr);
                nk_edit_draw_text(out, style, area.x - edit->scrollbar.x,
                    area.y - edit->scrollbar.y, 0, begin, (int)(select_begin_ptr - begin),
                    row_height, font, background_color, text_color, nk_false);
            }
            if (edit->select_start != edit->select_end) {
                /* draw selected text */
                NK_ASSERT(select_begin_ptr);
                if (!select_end_ptr) {
                    const char *begin = nk_str_get_const(&edit->string);
                    select_end_ptr = begin + nk_str_len_char(&edit->string);
                }
                nk_edit_draw_text(out, style,
                    area.x - edit->scrollbar.x,
                    area.y + selection_offset_start.y - edit->scrollbar.y,
                    selection_offset_start.x,
                    select_begin_ptr, (int)(select_end_ptr - select_begin_ptr),
                    row_height, font, sel_background_color, sel_text_color, nk_true);
            }
            if ((edit->select_start != edit->select_end &&
                selection_end < edit->string.len))
            {
                /* draw unselected text after selected text */
                const char *begin = select_end_ptr;
                const char *end = nk_str_get_const(&edit->string) +
                                    nk_str_len_char(&edit->string);
                NK_ASSERT(select_end_ptr);
                nk_edit_draw_text(out, style,
                    area.x - edit->scrollbar.x,
                    area.y + selection_offset_end.y - edit->scrollbar.y,
                    selection_offset_end.x,
                    begin, (int)(end - begin), row_height, font,
                    background_color, text_color, nk_true);
            }
        }

        /* cursor */
        if (edit->select_start == edit->select_end)
        {
            if (edit->cursor >= nk_str_len(&edit->string) ||
                (cursor_ptr && *cursor_ptr == '\n')) {
                /* draw cursor at end of line */
                struct nk_rect cursor;
                cursor.w = style->cursor_size;
                cursor.h = font->height;
                cursor.x = area.x + cursor_pos.x - edit->scrollbar.x;
                cursor.y = area.y + cursor_pos.y + row_height/2.0f - cursor.h/2.0f;
                cursor.y -= edit->scrollbar.y;
                nk_fill_rect(out, cursor, 0, cursor_color);
            } else {
                /* draw cursor inside text */
                int glyph_len;
                struct nk_rect label;
                struct nk_text txt;

                nk_rune unicode;
                NK_ASSERT(cursor_ptr);
                glyph_len = nk_utf_decode(cursor_ptr, &unicode, 4);

                label.x = area.x + cursor_pos.x - edit->scrollbar.x;
                label.y = area.y + cursor_pos.y - edit->scrollbar.y;
                label.w = font->width(font->userdata, font->height, cursor_ptr, glyph_len);
                label.h = row_height;

                txt.padding = nk_vec2(0,0);
                txt.background = cursor_color;
                txt.text = cursor_text_color;
                nk_fill_rect(out, label, 0, cursor_color);
                nk_widget_text(out, label, cursor_ptr, glyph_len, &txt, NK_TEXT_LEFT, font);
            }
        }}
    } else {
        /* not active so just draw text */
        int l = nk_str_len(&edit->string);
        const char *begin = nk_str_get_const(&edit->string);

        const struct nk_style_item *background;
        struct nk_color background_color;
        struct nk_color text_color;
        if (*state & NK_WIDGET_STATE_ACTIVED) {
            background = &style->active;
            text_color = style->text_active;
        } else if (*state & NK_WIDGET_STATE_HOVER) {
            background = &style->hover;
            text_color = style->text_hover;
        } else {
            background = &style->normal;
            text_color = style->text_normal;
        }
        if (background->type == NK_STYLE_ITEM_IMAGE)
            background_color = nk_rgba(0,0,0,0);
        else background_color = background->data.color;
        nk_edit_draw_text(out, style, area.x - edit->scrollbar.x,
            area.y - edit->scrollbar.y, 0, begin, l, row_height, font,
            background_color, text_color, nk_false);
    }
    nk_push_scissor(out, old_clip);}
    return ret;
}

/* ===============================================================
 *
 *                          PROPERTY
 *
 * ===============================================================*/
enum nk_property_status {
    NK_PROPERTY_DEFAULT,
    NK_PROPERTY_EDIT,
    NK_PROPERTY_DRAG
};

enum nk_property_filter {
    NK_FILTER_INT,
    NK_FILTER_FLOAT
};

NK_INTERN float
nk_drag_behavior(nk_flags *state, const struct nk_input *in,
    struct nk_rect drag, float min, float val, float max, float inc_per_pixel)
{
    int left_mouse_down = in && in->mouse.buttons[NK_BUTTON_LEFT].down;
    int left_mouse_click_in_cursor = in &&
        nk_input_has_mouse_click_down_in_rect(in, NK_BUTTON_LEFT, drag, nk_true);

    nk_widget_state_reset(state);
    if (nk_input_is_mouse_hovering_rect(in, drag))
        *state = NK_WIDGET_STATE_HOVERED;

    if (left_mouse_down && left_mouse_click_in_cursor) {
        float delta, pixels;
        pixels = in->mouse.delta.x;
        delta = pixels * inc_per_pixel;
        val += delta;
        val = NK_CLAMP(min, val, max);
        *state = NK_WIDGET_STATE_ACTIVE;
    }
    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(in, drag))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, drag))
        *state |= NK_WIDGET_STATE_LEFT;
    return val;
}

NK_INTERN float
nk_property_behavior(nk_flags *ws, const struct nk_input *in,
    struct nk_rect property,  struct nk_rect label, struct nk_rect edit,
    struct nk_rect empty, int *state, float min, float value, float max,
    float step, float inc_per_pixel)
{
    NK_UNUSED(step);
    if (in && *state == NK_PROPERTY_DEFAULT) {
        if (nk_button_behavior(ws, edit, in, NK_BUTTON_DEFAULT))
            *state = NK_PROPERTY_EDIT;
        else if (nk_input_is_mouse_click_down_in_rect(in, NK_BUTTON_LEFT, label, nk_true))
            *state = NK_PROPERTY_DRAG;
        else if (nk_input_is_mouse_click_down_in_rect(in, NK_BUTTON_LEFT, empty, nk_true))
            *state = NK_PROPERTY_DRAG;
    }
    if (*state == NK_PROPERTY_DRAG) {
        value = nk_drag_behavior(ws, in, property, min, value, max, inc_per_pixel);
        if (!(*ws & NK_WIDGET_STATE_ACTIVED)) *state = NK_PROPERTY_DEFAULT;
    }
    return value;
}

NK_INTERN void
nk_draw_property(struct nk_command_buffer *out, const struct nk_style_property *style,
    const struct nk_rect *bounds, const struct nk_rect *label, nk_flags state,
    const char *name, int len, const struct nk_user_font *font)
{
    struct nk_text text;
    const struct nk_style_item *background;

    /* select correct background and text color */
    if (state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->active;
        text.text = style->label_active;
    } else if (state & NK_WIDGET_STATE_HOVER) {
        background = &style->hover;
        text.text = style->label_hover;
    } else {
        background = &style->normal;
        text.text = style->label_normal;
    }

    /* draw background */
    if (background->type == NK_STYLE_ITEM_IMAGE) {
        nk_draw_image(out, *bounds, &background->data.image);
        text.background = nk_rgba(0,0,0,0);
    } else {
        text.background = background->data.color;
        nk_fill_rect(out, *bounds, style->rounding, style->border_color);
        nk_fill_rect(out, nk_shrink_rect(*bounds,style->border),
            style->rounding, background->data.color);
    }

    /* draw label */
    text.padding = nk_vec2(0,0);
    nk_widget_text(out, *label, name, len, &text, NK_TEXT_CENTERED, font);
}

NK_INTERN float
nk_do_property(nk_flags *ws,
    struct nk_command_buffer *out, struct nk_rect property,
    const char *name, float min, float val, float max,
    float step, float inc_per_pixel, char *buffer, int *len,
    int *state, int *cursor, const struct nk_style_property *style,
    enum nk_property_filter filter, struct nk_input *in,
    const struct nk_user_font *font, struct nk_text_edit *text_edit)
{
    const nk_filter filters[] = {
        nk_filter_decimal,
        nk_filter_float
    };
    int active, old;
    int num_len, name_len;
    char string[NK_MAX_NUMBER_BUFFER];
    float size;

    float property_min;
    float property_max;
    float property_value;

    char *dst = 0;
    int *length;

    struct nk_rect left;
    struct nk_rect right;
    struct nk_rect label;
    struct nk_rect edit;
    struct nk_rect empty;

    /* make sure the provided values are correct */
    property_max = NK_MAX(min, max);
    property_min = NK_MIN(min, max);
    property_value = NK_CLAMP(property_min, val, property_max);

    /* left decrement button */
    left.h = font->height/2;
    left.w = left.h;
    left.x = property.x + style->border + style->padding.x;
    left.y = property.y + style->border + property.h/2.0f - left.h/2;

    /* text label */
    name_len = nk_strlen(name);
    size = font->width(font->userdata, font->height, name, name_len);
    label.x = left.x + left.w + style->padding.x;
    label.w = (float)size + 2 * style->padding.x;
    label.y = property.y + style->border + style->padding.y;
    label.h = property.h - (2 * style->border + 2 * style->padding.y);

    /* right increment button */
    right.y = left.y;
    right.w = left.w;
    right.h = left.h;
    right.x = property.x + property.w - (right.w + style->padding.x);

    /* edit */
    if (*state == NK_PROPERTY_EDIT) {
        size = font->width(font->userdata, font->height, buffer, *len);
        size += style->edit.cursor_size;
        length = len;
        dst = buffer;
    } else {
        nk_ftos(string, property_value);
        num_len = nk_string_float_limit(string, NK_MAX_FLOAT_PRECISION);
        size = font->width(font->userdata, font->height, string, num_len);
        dst = string;
        length = &num_len;
    }
    edit.w =  (float)size + 2 * style->padding.x;
    edit.w = NK_MIN(edit.w, right.x - (label.x + label.w));
    edit.x = right.x - (edit.w + style->padding.x);
    edit.y = property.y + style->border;
    edit.h = property.h - (2 * style->border);

    /* empty left space activator */
    empty.w = edit.x - (label.x + label.w);
    empty.x = label.x + label.w;
    empty.y = property.y;
    empty.h = property.h;

    /* update property */
    old = (*state == NK_PROPERTY_EDIT);
    property_value = nk_property_behavior(ws, in, property, label, edit, empty,
                        state, property_min, property_value, property_max,
                        step, inc_per_pixel);

    /* draw property */
    if (style->draw_begin)
        style->draw_begin(out, style->userdata);
    if (style->draw)
        style->draw(out, style, &property, &label, *ws, name, name_len, font);
    else nk_draw_property(out, style, &property, &label, *ws, name, name_len, font);
    if (style->draw_end)
        style->draw_end(out, style->userdata);

    /* execute right and left button  */
    if (nk_do_button_symbol(ws, out, left, style->sym_left, NK_BUTTON_DEFAULT,
        &style->dec_button, in, font))
        property_value = NK_CLAMP(min, property_value - step, max);
    if (nk_do_button_symbol(ws, out, right, style->sym_right, NK_BUTTON_DEFAULT,
        &style->inc_button, in, font))
        property_value = NK_CLAMP(min, property_value + step, max);

    active = (*state == NK_PROPERTY_EDIT);
    if (old != NK_PROPERTY_EDIT && active) {
        /* property has been activated so setup buffer */
        NK_MEMCPY(buffer, dst, (nk_size)*length);
        *cursor = nk_utf_len(buffer, *length);
        *len = *length;
        length = len;
        dst = buffer;
    }
    {
        /* execute and run text edit field */
        nk_textedit_clear_state(text_edit, NK_TEXT_EDIT_SINGLE_LINE, filters[filter]);
        text_edit->active = (unsigned char)active;
        text_edit->string.len = *length;
        text_edit->cursor = NK_CLAMP(0, *cursor, *length);
        text_edit->string.buffer.allocated = (nk_size)*length;
        text_edit->string.buffer.memory.size = NK_MAX_NUMBER_BUFFER;
        text_edit->string.buffer.memory.ptr = dst;
        text_edit->string.buffer.size = NK_MAX_NUMBER_BUFFER;
        text_edit->mode = NK_TEXT_EDIT_MODE_INSERT;
        nk_do_edit(ws, out, edit, NK_EDIT_ALWAYS_INSERT_MODE, filters[filter],
            text_edit, &style->edit, (*state == NK_PROPERTY_EDIT) ? in: 0, font);

        *length = text_edit->string.len;
        active = text_edit->active;
        *cursor = text_edit->cursor;
    }
    if (active && nk_input_is_key_pressed(in, NK_KEY_ENTER))
        active = !active;

    if (old && !active) {
        /* property is now not active so convert edit text to value*/
        *state = NK_PROPERTY_DEFAULT;
        buffer[*len] = '\0';
        nk_string_float_limit(buffer, NK_MAX_FLOAT_PRECISION);
        nk_strtof(&property_value, buffer);
        property_value = NK_CLAMP(min, property_value, max);
    }
    return property_value;
}
/* ===============================================================
 *
 *                          COLOR PICKER
 *
 * ===============================================================*/
NK_INTERN int
nk_color_picker_behavior(nk_flags *state,
    const struct nk_rect *bounds, const struct nk_rect *matrix,
    const struct nk_rect *hue_bar, const struct nk_rect *alpha_bar,
    struct nk_color *color, const struct nk_input *in)
{
    float hsva[4];
    int value_changed = 0;
    int hsv_changed = 0;

    NK_ASSERT(state);
    NK_ASSERT(matrix);
    NK_ASSERT(hue_bar);
    NK_ASSERT(color);

    /* color matrix */
    nk_color_hsva_fv(hsva, *color);
    if (nk_button_behavior(state, *matrix, in, NK_BUTTON_REPEATER)) {
        hsva[1] = NK_SATURATE((in->mouse.pos.x - matrix->x) / (matrix->w-1));
        hsva[2] = 1.0f - NK_SATURATE((in->mouse.pos.y - matrix->y) / (matrix->h-1));
        value_changed = hsv_changed = 1;
    }

    /* hue bar */
    if (nk_button_behavior(state, *hue_bar, in, NK_BUTTON_REPEATER)) {
        hsva[0] = NK_SATURATE((in->mouse.pos.y - hue_bar->y) / (hue_bar->h-1));
        value_changed = hsv_changed = 1;
    }

    /* alpha bar */
    if (alpha_bar) {
        if (nk_button_behavior(state, *alpha_bar, in, NK_BUTTON_REPEATER)) {
            hsva[3] = 1.0f - NK_SATURATE((in->mouse.pos.y - alpha_bar->y) / (alpha_bar->h-1));
            value_changed = 1;
        }
    }

    nk_widget_state_reset(state);
    if (hsv_changed) {
        *color = nk_hsva_fv(hsva);
        *state = NK_WIDGET_STATE_ACTIVE;
    }
    if (value_changed) {
        color->a = (nk_byte)(hsva[3] * 255.0f);
        *state = NK_WIDGET_STATE_ACTIVE;
    }

    /* set color picker widget state */
    if (nk_input_is_mouse_hovering_rect(in, *bounds))
        *state = NK_WIDGET_STATE_HOVERED;
    if (*state & NK_WIDGET_STATE_HOVER && !nk_input_is_mouse_prev_hovering_rect(in, *bounds))
        *state |= NK_WIDGET_STATE_ENTERED;
    else if (nk_input_is_mouse_prev_hovering_rect(in, *bounds))
        *state |= NK_WIDGET_STATE_LEFT;
    return value_changed;
}

NK_INTERN void
nk_draw_color_picker(struct nk_command_buffer *o, const struct nk_rect *matrix,
    const struct nk_rect *hue_bar, const struct nk_rect *alpha_bar,
    struct nk_color color)
{
    NK_STORAGE const struct nk_color black = {0,0,0,255};
    NK_STORAGE const struct nk_color white = {255, 255, 255, 255};
    NK_STORAGE const struct nk_color black_trans = {0,0,0,0};

    const float crosshair_size = 7.0f;
    struct nk_color temp;
    float hsva[4];
    float line_y;
    int i;

    NK_ASSERT(o);
    NK_ASSERT(matrix);
    NK_ASSERT(hue_bar);
    NK_ASSERT(alpha_bar);

    /* draw hue bar */
    nk_color_hsv_fv(hsva, color);
    for (i = 0; i < 6; ++i) {
        NK_GLOBAL const struct nk_color hue_colors[] = {
            {255, 0, 0, 255}, {255,255,0,255}, {0,255,0,255}, {0, 255,255,255},
            {0,0,255,255}, {255, 0, 255, 255}, {255, 0, 0, 255}};
        nk_fill_rect_multi_color(o,
            nk_rect(hue_bar->x, hue_bar->y + (float)i * (hue_bar->h/6.0f) + 0.5f,
                hue_bar->w, (hue_bar->h/6.0f) + 0.5f), hue_colors[i], hue_colors[i],
                hue_colors[i+1], hue_colors[i+1]);
    }
    line_y = (float)(int)(hue_bar->y + hsva[0] * matrix->h + 0.5f);
    nk_stroke_line(o, hue_bar->x-1, line_y, hue_bar->x + hue_bar->w + 2,
        line_y, 1, nk_rgb(255,255,255));

    /* draw alpha bar */
    if (alpha_bar) {
        float alpha = NK_SATURATE((float)color.a/255.0f);
        line_y = (float)(int)(alpha_bar->y +  (1.0f - alpha) * matrix->h + 0.5f);

        nk_fill_rect_multi_color(o, *alpha_bar, white, white, black, black);
        nk_stroke_line(o, alpha_bar->x-1, line_y, alpha_bar->x + alpha_bar->w + 2,
            line_y, 1, nk_rgb(255,255,255));
    }

    /* draw color matrix */
    temp = nk_hsv_f(hsva[0], 1.0f, 1.0f);
    nk_fill_rect_multi_color(o, *matrix, white, temp, temp, white);
    nk_fill_rect_multi_color(o, *matrix, black_trans, black_trans, black, black);

    /* draw cross-hair */
    {struct nk_vec2 p; float S = hsva[1]; float V = hsva[2];
    p.x = (float)(int)(matrix->x + S * matrix->w + 0.5f);
    p.y = (float)(int)(matrix->y + (1.0f - V) * matrix->h + 0.5f);
    nk_stroke_line(o, p.x - crosshair_size, p.y, p.x-2, p.y, 1.0f, white);
    nk_stroke_line(o, p.x + crosshair_size, p.y, p.x+2, p.y, 1.0f, white);
    nk_stroke_line(o, p.x, p.y + crosshair_size, p.x, p.y+2, 1.0f, nk_rgb(255,255,255));
    nk_stroke_line(o, p.x, p.y - crosshair_size, p.x, p.y-2, 1.0f, nk_rgb(255,255,255));}
}

NK_INTERN int
nk_do_color_picker(nk_flags *state,
    struct nk_command_buffer *out, struct nk_color *color,
    enum nk_color_format fmt, struct nk_rect bounds,
    struct nk_vec2 padding, const struct nk_input *in,
    const struct nk_user_font *font)
{
    int ret = 0;
    struct nk_rect matrix;
    struct nk_rect hue_bar;
    struct nk_rect alpha_bar;
    float bar_w;

    NK_ASSERT(out);
    NK_ASSERT(color);
    NK_ASSERT(state);
    NK_ASSERT(font);
    if (!out || !color || !state || !font)
        return ret;

    bar_w = font->height;
    bounds.x += padding.x;
    bounds.y += padding.x;
    bounds.w -= 2 * padding.x;
    bounds.h -= 2 * padding.y;

    matrix.x = bounds.x;
    matrix.y = bounds.y;
    matrix.h = bounds.h;
    matrix.w = bounds.w - (3 * padding.x + 2 * bar_w);

    hue_bar.w = bar_w;
    hue_bar.y = bounds.y;
    hue_bar.h = matrix.h;
    hue_bar.x = matrix.x + matrix.w + padding.x;

    alpha_bar.x = hue_bar.x + hue_bar.w + padding.x;
    alpha_bar.y = bounds.y;
    alpha_bar.w = bar_w;
    alpha_bar.h = matrix.h;

    ret = nk_color_picker_behavior(state, &bounds, &matrix, &hue_bar,
        (fmt == NK_RGBA) ? &alpha_bar:0, color, in);
    nk_draw_color_picker(out, &matrix, &hue_bar, (fmt == NK_RGBA) ? &alpha_bar:0, *color);
    return ret;
}

/* ==============================================================
 *
 *                          STYLE
 *
 * ===============================================================*/
NK_API void nk_style_default(struct nk_context *ctx){nk_style_from_table(ctx, 0);}
#define NK_COLOR_MAP(NK_COLOR)\
    NK_COLOR(NK_COLOR_TEXT,                 175,175,175,255) \
    NK_COLOR(NK_COLOR_WINDOW,               45, 45, 45, 255) \
    NK_COLOR(NK_COLOR_HEADER,               40, 40, 40, 255) \
    NK_COLOR(NK_COLOR_BORDER,               65, 65, 65, 255) \
    NK_COLOR(NK_COLOR_BUTTON,               50, 50, 50, 255) \
    NK_COLOR(NK_COLOR_BUTTON_HOVER,         40, 40, 40, 255) \
    NK_COLOR(NK_COLOR_BUTTON_ACTIVE,        35, 35, 35, 255) \
    NK_COLOR(NK_COLOR_TOGGLE,               100,100,100,255) \
    NK_COLOR(NK_COLOR_TOGGLE_HOVER,         120,120,120,255) \
    NK_COLOR(NK_COLOR_TOGGLE_CURSOR,        45, 45, 45, 255) \
    NK_COLOR(NK_COLOR_SELECT,               45, 45, 45, 255) \
    NK_COLOR(NK_COLOR_SELECT_ACTIVE,        35, 35, 35,255) \
    NK_COLOR(NK_COLOR_SLIDER,               38, 38, 38, 255) \
    NK_COLOR(NK_COLOR_SLIDER_CURSOR,        100,100,100,255) \
    NK_COLOR(NK_COLOR_SLIDER_CURSOR_HOVER,  120,120,120,255) \
    NK_COLOR(NK_COLOR_SLIDER_CURSOR_ACTIVE, 150,150,150,255) \
    NK_COLOR(NK_COLOR_PROPERTY,             38, 38, 38, 255) \
    NK_COLOR(NK_COLOR_EDIT,                 38, 38, 38, 255)  \
    NK_COLOR(NK_COLOR_EDIT_CURSOR,          175,175,175,255) \
    NK_COLOR(NK_COLOR_COMBO,                45, 45, 45, 255) \
    NK_COLOR(NK_COLOR_CHART,                120,120,120,255) \
    NK_COLOR(NK_COLOR_CHART_COLOR,          45, 45, 45, 255) \
    NK_COLOR(NK_COLOR_CHART_COLOR_HIGHLIGHT,255, 0,  0, 255) \
    NK_COLOR(NK_COLOR_SCROLLBAR,            40, 40, 40, 255) \
    NK_COLOR(NK_COLOR_SCROLLBAR_CURSOR,     100,100,100,255) \
    NK_COLOR(NK_COLOR_SCROLLBAR_CURSOR_HOVER,120,120,120,255) \
    NK_COLOR(NK_COLOR_SCROLLBAR_CURSOR_ACTIVE,150,150,150,255) \
    NK_COLOR(NK_COLOR_TAB_HEADER,           40, 40, 40,255)

NK_GLOBAL const struct nk_color
nk_default_color_style[NK_COLOR_COUNT] = {
#define NK_COLOR(a,b,c,d,e) {b,c,d,e},
NK_COLOR_MAP(NK_COLOR)
#undef NK_COLOR
};

NK_GLOBAL const char *nk_color_names[NK_COLOR_COUNT] = {
#define NK_COLOR(a,b,c,d,e) #a,
NK_COLOR_MAP(NK_COLOR)
#undef NK_COLOR
};

NK_API const char *nk_style_color_name(enum nk_style_colors c)
{return nk_color_names[c];}

NK_API struct nk_style_item nk_style_item_image(struct nk_image img)
{struct nk_style_item i; i.type = NK_STYLE_ITEM_IMAGE; i.data.image = img; return i;}

NK_API struct nk_style_item nk_style_item_color(struct nk_color col)
{struct nk_style_item i; i.type = NK_STYLE_ITEM_COLOR; i.data.color = col; return i;}

NK_API struct nk_style_item nk_style_item_hide(void)
{struct nk_style_item i; i.type = NK_STYLE_ITEM_COLOR; i.data.color = nk_rgba(0,0,0,0); return i;}

NK_API void
nk_style_from_table(struct nk_context *ctx, const struct nk_color *table)
{
    struct nk_style *style;
    struct nk_style_text *text;
    struct nk_style_button *button;
    struct nk_style_toggle *toggle;
    struct nk_style_selectable *select;
    struct nk_style_slider *slider;
    struct nk_style_progress *prog;
    struct nk_style_scrollbar *scroll;
    struct nk_style_edit *edit;
    struct nk_style_property *property;
    struct nk_style_combo *combo;
    struct nk_style_chart *chart;
    struct nk_style_tab *tab;
    struct nk_style_window *win;

    NK_ASSERT(ctx);
    if (!ctx) return;
    style = &ctx->style;
    table = (!table) ? nk_default_color_style: table;

    /* default text */
    text = &style->text;
    text->color = table[NK_COLOR_TEXT];
    text->padding = nk_vec2(4,4);

    /* default button */
    button = &style->button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_BUTTON]);
    button->hover           = nk_style_item_color(table[NK_COLOR_BUTTON_HOVER]);
    button->active          = nk_style_item_color(table[NK_COLOR_BUTTON_ACTIVE]);
    button->border_color    = table[NK_COLOR_BORDER];
    button->text_background = table[NK_COLOR_BUTTON];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(4.0f,4.0f);
    button->image_padding   = nk_vec2(0.0f,0.0f);
    button->touch_padding   = nk_vec2(0.0f, 0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 1.0f;
    button->rounding        = 4.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    /* contextual button */
    button = &style->contextual_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->hover           = nk_style_item_color(table[NK_COLOR_BUTTON_HOVER]);
    button->active          = nk_style_item_color(table[NK_COLOR_BUTTON_ACTIVE]);
    button->border_color    = table[NK_COLOR_WINDOW];
    button->text_background = table[NK_COLOR_WINDOW];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(4.0f,4.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    /* menu button */
    button = &style->menu_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->hover           = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->active          = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->border_color    = table[NK_COLOR_WINDOW];
    button->text_background = table[NK_COLOR_WINDOW];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(4.0f,4.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 1.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    /* checkbox toggle */
    toggle = &style->checkbox;
    nk_zero_struct(*toggle);
    toggle->normal          = nk_style_item_color(table[NK_COLOR_TOGGLE]);
    toggle->hover           = nk_style_item_color(table[NK_COLOR_TOGGLE_HOVER]);
    toggle->active          = nk_style_item_color(table[NK_COLOR_TOGGLE_HOVER]);
    toggle->cursor_normal   = nk_style_item_color(table[NK_COLOR_TOGGLE_CURSOR]);
    toggle->cursor_hover    = nk_style_item_color(table[NK_COLOR_TOGGLE_CURSOR]);
    toggle->userdata        = nk_handle_ptr(0);
    toggle->text_background = table[NK_COLOR_WINDOW];
    toggle->text_normal     = table[NK_COLOR_TEXT];
    toggle->text_hover      = table[NK_COLOR_TEXT];
    toggle->text_active     = table[NK_COLOR_TEXT];
    toggle->padding         = nk_vec2(4.0f, 4.0f);
    toggle->touch_padding   = nk_vec2(0,0);

    /* option toggle */
    toggle = &style->option;
    nk_zero_struct(*toggle);
    toggle->normal          = nk_style_item_color(table[NK_COLOR_TOGGLE]);
    toggle->hover           = nk_style_item_color(table[NK_COLOR_TOGGLE_HOVER]);
    toggle->active          = nk_style_item_color(table[NK_COLOR_TOGGLE_HOVER]);
    toggle->cursor_normal   = nk_style_item_color(table[NK_COLOR_TOGGLE_CURSOR]);
    toggle->cursor_hover    = nk_style_item_color(table[NK_COLOR_TOGGLE_CURSOR]);
    toggle->userdata        = nk_handle_ptr(0);
    toggle->text_background = table[NK_COLOR_WINDOW];
    toggle->text_normal     = table[NK_COLOR_TEXT];
    toggle->text_hover      = table[NK_COLOR_TEXT];
    toggle->text_active     = table[NK_COLOR_TEXT];
    toggle->padding         = nk_vec2(4.0f, 4.0f);
    toggle->touch_padding   = nk_vec2(0,0);

    /* selectable */
    select = &style->selectable;
    nk_zero_struct(*select);
    select->normal          = nk_style_item_color(table[NK_COLOR_SELECT]);
    select->hover           = nk_style_item_color(table[NK_COLOR_SELECT]);
    select->pressed         = nk_style_item_color(table[NK_COLOR_SELECT]);
    select->normal_active   = nk_style_item_color(table[NK_COLOR_SELECT_ACTIVE]);
    select->hover_active    = nk_style_item_color(table[NK_COLOR_SELECT_ACTIVE]);
    select->pressed_active  = nk_style_item_color(table[NK_COLOR_SELECT_ACTIVE]);
    select->text_normal     = table[NK_COLOR_TEXT];
    select->text_hover      = table[NK_COLOR_TEXT];
    select->text_pressed    = table[NK_COLOR_TEXT];
    select->text_normal_active  = table[NK_COLOR_TEXT];
    select->text_hover_active   = table[NK_COLOR_TEXT];
    select->text_pressed_active = table[NK_COLOR_TEXT];
    select->padding         = nk_vec2(4.0f,4.0f);
    select->touch_padding   = nk_vec2(0,0);
    select->userdata        = nk_handle_ptr(0);
    select->rounding        = 0.0f;
    select->draw_begin      = 0;
    select->draw            = 0;
    select->draw_end        = 0;

    /* slider */
    slider = &style->slider;
    nk_zero_struct(*slider);
    slider->normal          = nk_style_item_hide();
    slider->hover           = nk_style_item_hide();
    slider->active          = nk_style_item_hide();
    slider->bar_normal      = table[NK_COLOR_SLIDER];
    slider->bar_hover       = table[NK_COLOR_SLIDER];
    slider->bar_active      = table[NK_COLOR_SLIDER];
    slider->bar_filled      = table[NK_COLOR_SLIDER_CURSOR];
    slider->cursor_normal   = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR]);
    slider->cursor_hover    = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR_HOVER]);
    slider->cursor_active   = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR_ACTIVE]);
    slider->inc_symbol      = NK_SYMBOL_TRIANGLE_RIGHT;
    slider->dec_symbol      = NK_SYMBOL_TRIANGLE_LEFT;
    slider->cursor_size     = nk_vec2(16,16);
    slider->padding         = nk_vec2(4,4);
    slider->spacing         = nk_vec2(4,4);
    slider->userdata        = nk_handle_ptr(0);
    slider->show_buttons    = nk_false;
    slider->bar_height      = 8;
    slider->rounding        = 0;
    slider->draw_begin      = 0;
    slider->draw            = 0;
    slider->draw_end        = 0;

    /* slider buttons */
    button = &style->slider.inc_button;
    button->normal          = nk_style_item_color(nk_rgb(40,40,40));
    button->hover           = nk_style_item_color(nk_rgb(42,42,42));
    button->active          = nk_style_item_color(nk_rgb(44,44,44));
    button->border_color    = nk_rgb(65,65,65);
    button->text_background = nk_rgb(40,40,40);
    button->text_normal     = nk_rgb(175,175,175);
    button->text_hover      = nk_rgb(175,175,175);
    button->text_active     = nk_rgb(175,175,175);
    button->padding         = nk_vec2(8.0f,8.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 1.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;
    style->slider.dec_button = style->slider.inc_button;

    /* progressbar */
    prog = &style->progress;
    nk_zero_struct(*prog);
    prog->normal            = nk_style_item_color(table[NK_COLOR_SLIDER]);
    prog->hover             = nk_style_item_color(table[NK_COLOR_SLIDER]);
    prog->active            = nk_style_item_color(table[NK_COLOR_SLIDER]);
    prog->cursor_normal     = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR]);
    prog->cursor_hover      = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR_HOVER]);
    prog->cursor_active     = nk_style_item_color(table[NK_COLOR_SLIDER_CURSOR_ACTIVE]);
    prog->userdata          = nk_handle_ptr(0);
    prog->padding           = nk_vec2(4,4);
    prog->rounding          = 0;
    prog->draw_begin        = 0;
    prog->draw              = 0;
    prog->draw_end          = 0;

    /* scrollbars */
    scroll = &style->scrollh;
    nk_zero_struct(*scroll);
    scroll->normal          = nk_style_item_color(table[NK_COLOR_SCROLLBAR]);
    scroll->hover           = nk_style_item_color(table[NK_COLOR_SCROLLBAR]);
    scroll->active          = nk_style_item_color(table[NK_COLOR_SCROLLBAR]);
    scroll->cursor_normal   = nk_style_item_color(table[NK_COLOR_SCROLLBAR_CURSOR]);
    scroll->cursor_hover    = nk_style_item_color(table[NK_COLOR_SCROLLBAR_CURSOR_HOVER]);
    scroll->cursor_active   = nk_style_item_color(table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE]);
    scroll->dec_symbol      = NK_SYMBOL_CIRCLE_FILLED;
    scroll->inc_symbol      = NK_SYMBOL_CIRCLE_FILLED;
    scroll->userdata        = nk_handle_ptr(0);
    scroll->border_color    = nk_rgb(65,65,65);
    scroll->padding         = nk_vec2(4,4);
    scroll->show_buttons    = nk_false;
    scroll->border          = 0;
    scroll->rounding        = 0;
    scroll->draw_begin      = 0;
    scroll->draw            = 0;
    scroll->draw_end        = 0;
    style->scrollv = style->scrollh;

    /* scrollbars buttons */
    button = &style->scrollh.inc_button;
    button->normal          = nk_style_item_color(nk_rgb(40,40,40));
    button->hover           = nk_style_item_color(nk_rgb(42,42,42));
    button->active          = nk_style_item_color(nk_rgb(44,44,44));
    button->border_color    = nk_rgb(65,65,65);
    button->text_background = nk_rgb(40,40,40);
    button->text_normal     = nk_rgb(175,175,175);
    button->text_hover      = nk_rgb(175,175,175);
    button->text_active     = nk_rgb(175,175,175);
    button->padding         = nk_vec2(4.0f,4.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 1.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;
    style->scrollh.dec_button = style->scrollh.inc_button;
    style->scrollv.inc_button = style->scrollh.inc_button;
    style->scrollv.dec_button = style->scrollh.inc_button;

    /* edit */
    edit = &style->edit;
    nk_zero_struct(*edit);
    edit->normal            = nk_style_item_color(table[NK_COLOR_EDIT]);
    edit->hover             = nk_style_item_color(table[NK_COLOR_EDIT]);
    edit->active            = nk_style_item_color(table[NK_COLOR_EDIT]);
    edit->cursor_normal     = table[NK_COLOR_TEXT];
    edit->cursor_hover      = table[NK_COLOR_TEXT];
    edit->cursor_text_normal= table[NK_COLOR_EDIT];
    edit->cursor_text_hover = table[NK_COLOR_EDIT];
    edit->border_color      = table[NK_COLOR_BORDER];
    edit->text_normal       = table[NK_COLOR_TEXT];
    edit->text_hover        = table[NK_COLOR_TEXT];
    edit->text_active       = table[NK_COLOR_TEXT];
    edit->selected_normal   = table[NK_COLOR_TEXT];
    edit->selected_hover    = table[NK_COLOR_TEXT];
    edit->selected_text_normal  = table[NK_COLOR_EDIT];
    edit->selected_text_hover   = table[NK_COLOR_EDIT];
    edit->row_padding       = 2;
    edit->padding           = nk_vec2(4,4);
    edit->cursor_size       = 4;
    edit->border            = 1;
    edit->rounding          = 0;

    /* property */
    property = &style->property;
    nk_zero_struct(*property);
    property->normal        = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    property->hover         = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    property->active        = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    property->border_color  = table[NK_COLOR_BORDER];
    property->label_normal  = table[NK_COLOR_TEXT];
    property->label_hover   = table[NK_COLOR_TEXT];
    property->label_active  = table[NK_COLOR_TEXT];
    property->sym_left      = NK_SYMBOL_TRIANGLE_LEFT;
    property->sym_right     = NK_SYMBOL_TRIANGLE_RIGHT;
    property->userdata      = nk_handle_ptr(0);
    property->padding       = nk_vec2(4,4);
    property->border        = 1;
    property->rounding      = 10;
    property->draw_begin    = 0;
    property->draw          = 0;
    property->draw_end      = 0;

    /* property buttons */
    button = &style->property.dec_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    button->hover           = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    button->active          = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_PROPERTY];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(0.0f,0.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;
    style->property.inc_button = style->property.dec_button;

    /* property edit */
    edit = &style->property.edit;
    nk_zero_struct(*edit);
    edit->normal            = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    edit->hover             = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    edit->active            = nk_style_item_color(table[NK_COLOR_PROPERTY]);
    edit->border_color      = nk_rgba(0,0,0,0);
    edit->cursor_normal     = table[NK_COLOR_TEXT];
    edit->cursor_hover      = table[NK_COLOR_TEXT];
    edit->cursor_text_normal= table[NK_COLOR_EDIT];
    edit->cursor_text_hover = table[NK_COLOR_EDIT];
    edit->text_normal       = table[NK_COLOR_TEXT];
    edit->text_hover        = table[NK_COLOR_TEXT];
    edit->text_active       = table[NK_COLOR_TEXT];
    edit->selected_normal   = table[NK_COLOR_TEXT];
    edit->selected_hover    = table[NK_COLOR_TEXT];
    edit->selected_text_normal  = table[NK_COLOR_EDIT];
    edit->selected_text_hover   = table[NK_COLOR_EDIT];
    edit->padding           = nk_vec2(0,0);
    edit->cursor_size       = 8;
    edit->border            = 0;
    edit->rounding          = 0;

    /* chart */
    chart = &style->chart;
    nk_zero_struct(*chart);
    chart->background       = nk_style_item_color(table[NK_COLOR_CHART]);
    chart->border_color     = table[NK_COLOR_BORDER];
    chart->selected_color   = table[NK_COLOR_CHART_COLOR_HIGHLIGHT];
    chart->color            = table[NK_COLOR_CHART_COLOR];
    chart->padding          = nk_vec2(4,4);
    chart->border           = 0;
    chart->rounding         = 0;

    /* combo */
    combo = &style->combo;
    combo->normal           = nk_style_item_color(table[NK_COLOR_COMBO]);
    combo->hover            = nk_style_item_color(table[NK_COLOR_COMBO]);
    combo->active           = nk_style_item_color(table[NK_COLOR_COMBO]);
    combo->border_color     = table[NK_COLOR_BORDER];
    combo->label_normal     = table[NK_COLOR_TEXT];
    combo->label_hover      = table[NK_COLOR_TEXT];
    combo->label_active     = table[NK_COLOR_TEXT];
    combo->sym_normal       = NK_SYMBOL_TRIANGLE_DOWN;
    combo->sym_hover        = NK_SYMBOL_TRIANGLE_DOWN;
    combo->sym_active       = NK_SYMBOL_TRIANGLE_DOWN;
    combo->content_padding  = nk_vec2(4,4);
    combo->button_padding   = nk_vec2(0,4);
    combo->spacing          = nk_vec2(4,0);
    combo->border           = 1;
    combo->rounding         = 0;

    /* combo button */
    button = &style->combo.button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_COMBO]);
    button->hover           = nk_style_item_color(table[NK_COLOR_COMBO]);
    button->active          = nk_style_item_color(table[NK_COLOR_COMBO]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_COMBO];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(2.0f,2.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    /* tab */
    tab = &style->tab;
    tab->background         = nk_style_item_color(table[NK_COLOR_TAB_HEADER]);
    tab->border_color       = table[NK_COLOR_BORDER];
    tab->text               = table[NK_COLOR_TEXT];
    tab->sym_minimize       = NK_SYMBOL_TRIANGLE_DOWN;
    tab->sym_maximize       = NK_SYMBOL_TRIANGLE_RIGHT;
    tab->padding            = nk_vec2(4,4);
    tab->spacing            = nk_vec2(4,4);
    tab->border             = 1;
    tab->rounding           = 0;

    /* tab button */
    button = &style->tab.tab_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_TAB_HEADER]);
    button->hover           = nk_style_item_color(table[NK_COLOR_TAB_HEADER]);
    button->active          = nk_style_item_color(table[NK_COLOR_TAB_HEADER]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_TAB_HEADER];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(2.0f,2.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    /* node button */
    button = &style->tab.node_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->hover           = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->active          = nk_style_item_color(table[NK_COLOR_WINDOW]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_TAB_HEADER];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(2.0f,2.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    /* window header */
    win = &style->window;
    win->header.align = NK_HEADER_RIGHT;
    win->header.close_symbol = NK_SYMBOL_X;
    win->header.minimize_symbol = NK_SYMBOL_MINUS;
    win->header.maximize_symbol = NK_SYMBOL_PLUS;
    win->header.normal = nk_style_item_color(table[NK_COLOR_HEADER]);
    win->header.hover = nk_style_item_color(table[NK_COLOR_HEADER]);
    win->header.active = nk_style_item_color(table[NK_COLOR_HEADER]);
    win->header.label_normal = table[NK_COLOR_TEXT];
    win->header.label_hover = table[NK_COLOR_TEXT];
    win->header.label_active = table[NK_COLOR_TEXT];
    win->header.label_padding = nk_vec2(4,4);
    win->header.padding = nk_vec2(4,4);
    win->header.spacing = nk_vec2(0,0);

    /* window header close button */
    button = &style->window.header.close_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->hover           = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->active          = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_HEADER];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(0.0f,0.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    /* window header minimize button */
    button = &style->window.header.minimize_button;
    nk_zero_struct(*button);
    button->normal          = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->hover           = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->active          = nk_style_item_color(table[NK_COLOR_HEADER]);
    button->border_color    = nk_rgba(0,0,0,0);
    button->text_background = table[NK_COLOR_HEADER];
    button->text_normal     = table[NK_COLOR_TEXT];
    button->text_hover      = table[NK_COLOR_TEXT];
    button->text_active     = table[NK_COLOR_TEXT];
    button->padding         = nk_vec2(0.0f,0.0f);
    button->touch_padding   = nk_vec2(0.0f,0.0f);
    button->userdata        = nk_handle_ptr(0);
    button->text_alignment  = NK_TEXT_CENTERED;
    button->border          = 0.0f;
    button->rounding        = 0.0f;
    button->draw_begin      = 0;
    button->draw_end        = 0;

    /* window */
    win->background = table[NK_COLOR_WINDOW];
    win->fixed_background = nk_style_item_color(table[NK_COLOR_WINDOW]);
    win->border_color = table[NK_COLOR_BORDER];
    win->combo_border_color = table[NK_COLOR_BORDER];
    win->contextual_border_color = table[NK_COLOR_BORDER];
    win->menu_border_color = table[NK_COLOR_BORDER];
    win->group_border_color = table[NK_COLOR_BORDER];
    win->tooltip_border_color = table[NK_COLOR_BORDER];
    win->scaler = nk_style_item_color(table[NK_COLOR_TEXT]);
    win->footer_padding = nk_vec2(4,4);
    win->rounding = 0.0f;
    win->scaler_size = nk_vec2(16,16);
    win->padding = nk_vec2(8,8);
    win->spacing = nk_vec2(4,4);
    win->scrollbar_size = nk_vec2(10,10);
    win->min_size = nk_vec2(64,64);
    win->combo_border = 1.0f;
    win->contextual_border = 1.0f;
    win->menu_border = 1.0f;
    win->group_border = 1.0f;
    win->tooltip_border = 1.0f;
    win->border = 2.0f;
}

NK_API void
nk_style_set_font(struct nk_context *ctx, const struct nk_user_font *font)
{
    struct nk_style *style;
    NK_ASSERT(ctx);
    if (!ctx) return;
    style = &ctx->style;
    style->font = *font;
}

/* ===============================================================
 *
 *                          POOL
 *
 * ===============================================================*/
#define NK_VALUE_PAGE_CAPACITY ((sizeof(struct nk_window) / sizeof(nk_uint)) / 2)
struct nk_table {
    unsigned int seq;
    nk_hash keys[NK_VALUE_PAGE_CAPACITY];
    nk_uint values[NK_VALUE_PAGE_CAPACITY];
    struct nk_table *next, *prev;
};

union nk_page_data {
    struct nk_table tbl;
    struct nk_window win;
};

struct nk_page_element {
    union nk_page_data data;
    struct nk_page_element *next;
    struct nk_page_element *prev;
};

struct nk_page {
    unsigned size;
    struct nk_page *next;
    struct nk_page_element win[1];
};

struct nk_pool {
    struct nk_allocator alloc;
    enum nk_allocation_type type;
    unsigned int page_count;
    struct nk_page *pages;
    struct nk_page_element *freelist;
    unsigned capacity;
    nk_size size;
    nk_size cap;
};

NK_INTERN void
nk_pool_init(struct nk_pool *pool, struct nk_allocator *alloc,
            unsigned int capacity)
{
    nk_zero(pool, sizeof(*pool));
    pool->alloc = *alloc;
    pool->capacity = capacity;
    pool->pages = 0;
    pool->type = NK_BUFFER_DYNAMIC;
}

NK_INTERN void
nk_pool_free(struct nk_pool *pool)
{
    struct nk_page *next;
    struct nk_page *iter = pool->pages;
    if (!pool) return;
    if (pool->type == NK_BUFFER_FIXED) return;
    while (iter) {
        next = iter->next;
        pool->alloc.free(pool->alloc.userdata, iter);
        iter = next;
    }
}

NK_INTERN void
nk_pool_init_fixed(struct nk_pool *pool, void *memory, nk_size size)
{
    nk_zero(pool, sizeof(*pool));
    NK_ASSERT(size >= sizeof(struct nk_page));
    if (size < sizeof(struct nk_page)) return;
    pool->capacity = (unsigned)(size - sizeof(struct nk_page)) / sizeof(struct nk_page_element);
    pool->pages = (struct nk_page*)memory;
    pool->type = NK_BUFFER_FIXED;
    pool->size = size;
}

NK_INTERN struct nk_page_element*
nk_pool_alloc(struct nk_pool *pool)
{
    if (!pool->pages || pool->pages->size >= pool->capacity) {
        /* allocate new page */
        struct nk_page *page;
        if (pool->type == NK_BUFFER_FIXED) {
            if (!pool->pages) {
                NK_ASSERT(pool->pages);
                return 0;
            }
            NK_ASSERT(pool->pages->size < pool->capacity);
            return 0;
        } else {
            nk_size size = sizeof(struct nk_page);
            size += NK_POOL_DEFAULT_CAPACITY * sizeof(union nk_page_data);
            page = (struct nk_page*)pool->alloc.alloc(pool->alloc.userdata,0, size);
            page->size = 0;
            page->next = pool->pages;
            pool->pages = page;
        }
    }
    return &pool->pages->win[pool->pages->size++];
}

/* ===============================================================
 *
 *                          CONTEXT
 *
 * ===============================================================*/
NK_INTERN void* nk_create_window(struct nk_context *ctx);
NK_INTERN void nk_remove_window(struct nk_context*, struct nk_window*);
NK_INTERN void nk_free_window(struct nk_context *ctx, struct nk_window *win);
NK_INTERN void nk_free_table(struct nk_context *ctx, struct nk_table *tbl);
NK_INTERN void nk_remove_table(struct nk_window *win, struct nk_table *tbl);

NK_INTERN void
nk_setup(struct nk_context *ctx, const struct nk_user_font *font)
{
    NK_ASSERT(ctx);
    if (!ctx) return;

    nk_zero_struct(*ctx);
    nk_style_default(ctx);
    if (font) ctx->style.font = *font;
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    nk_draw_list_init(&ctx->draw_list);
#endif
}

#ifdef NK_INCLUDE_DEFAULT_ALLOCATOR
NK_API int
nk_init_default(struct nk_context *ctx, const struct nk_user_font *font)
{
    struct nk_allocator alloc;
    alloc.userdata.ptr = 0;
    alloc.alloc = nk_malloc;
    alloc.free = nk_mfree;
    return nk_init(ctx, &alloc, font);
}
#endif

NK_API int
nk_init_fixed(struct nk_context *ctx, void *memory, nk_size size,
    const struct nk_user_font *font)
{
    NK_ASSERT(memory);
    if (!memory) return 0;
    nk_setup(ctx, font);
    nk_buffer_init_fixed(&ctx->memory, memory, size);
    ctx->pool = 0;
    return 1;
}

NK_API int
nk_init_custom(struct nk_context *ctx, struct nk_buffer *cmds,
    struct nk_buffer *pool, const struct nk_user_font *font)
{
    NK_ASSERT(cmds);
    NK_ASSERT(pool);
    if (!cmds || !pool) return 0;
    nk_setup(ctx, font);
    ctx->memory = *cmds;
    if (pool->type == NK_BUFFER_FIXED) {
        /* take memory from buffer and alloc fixed pool */
        void *memory = pool->memory.ptr;
        nk_size size = pool->memory.size;
        ctx->pool = memory;
        NK_ASSERT(size > sizeof(struct nk_pool));
        size -= sizeof(struct nk_pool);
        nk_pool_init_fixed((struct nk_pool*)ctx->pool,
            (void*)((nk_byte*)ctx->pool+sizeof(struct nk_pool)), size);
    } else {
        /* create dynamic pool from buffer allocator */
        struct nk_allocator *alloc = &pool->pool;
        ctx->pool = alloc->alloc(alloc->userdata,0, sizeof(struct nk_pool));
        nk_pool_init((struct nk_pool*)ctx->pool, alloc, NK_POOL_DEFAULT_CAPACITY);
    }
    return 1;
}

NK_API int
nk_init(struct nk_context *ctx, struct nk_allocator *alloc,
    const struct nk_user_font *font)
{
    NK_ASSERT(alloc);
    if (!alloc) return 0;
    nk_setup(ctx, font);
    nk_buffer_init(&ctx->memory, alloc, NK_DEFAULT_COMMAND_BUFFER_SIZE);
    ctx->pool = alloc->alloc(alloc->userdata,0, sizeof(struct nk_pool));
    nk_pool_init((struct nk_pool*)ctx->pool, alloc, NK_POOL_DEFAULT_CAPACITY);
    return 1;
}

#ifdef NK_INCLUDE_COMMAND_USERDATA
NK_API void
nk_set_user_data(struct nk_context *ctx, nk_handle handle)
{
    if (!ctx) return;
    ctx->userdata = handle;
    if (ctx->current)
        ctx->current->buffer.userdata = handle;
}
#endif

NK_API void
nk_free(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    if (!ctx) return;
    nk_buffer_free(&ctx->memory);
    if (ctx->pool) {
        struct nk_pool *pool = (struct nk_pool*)ctx->pool;
        nk_pool_free(pool);
        pool->alloc.free(pool->alloc.userdata, pool);
    }

    nk_zero(&ctx->input, sizeof(ctx->input));
    nk_zero(&ctx->style, sizeof(ctx->style));
    nk_zero(&ctx->memory, sizeof(ctx->memory));

    ctx->seq = 0;
    ctx->pool = 0;
    ctx->build = 0;
    ctx->begin = 0;
    ctx->end = 0;
    ctx->active = 0;
    ctx->current = 0;
    ctx->freelist = 0;
    ctx->count = 0;
}

NK_API void
nk_clear(struct nk_context *ctx)
{
    struct nk_window *iter;
    struct nk_window *next;
    NK_ASSERT(ctx);

    if (!ctx) return;
    if (ctx->pool)
        nk_buffer_clear(&ctx->memory);
    else nk_buffer_reset(&ctx->memory, NK_BUFFER_FRONT);

    ctx->build = 0;
    ctx->memory.calls = 0;
    ctx->last_widget_state = 0;
#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    nk_draw_list_clear(&ctx->draw_list);
#endif

    /* garbage collector */
    iter = ctx->begin;
    while (iter) {
        /* make sure minimized windows do not get removed */
        if (iter->flags & NK_WINDOW_MINIMIZED) {
            iter = iter->next;
            continue;
        }

        /* free unused popup windows */
        if (iter->popup.win && iter->popup.win->seq != ctx->seq) {
            nk_free_window(ctx, iter->popup.win);
            iter->popup.win = 0;
        }

        {struct nk_table *n, *it = iter->tables;
        while (it) {
            /* remove unused window state tables */
            n = it->next;
            if (it->seq != ctx->seq) {
                nk_remove_table(iter, it);
                nk_zero(it, sizeof(union nk_page_data));
                nk_free_table(ctx, it);
                if (it == iter->tables)
                    iter->tables = n;
            }
            it = n;
        }}

        /* window itself is not used anymore so free */
        if (iter->seq != ctx->seq || iter->flags & NK_WINDOW_HIDDEN) {
            next = iter->next;
            nk_remove_window(ctx, iter);
            nk_free_window(ctx, iter);
            iter = next;
        } else iter = iter->next;
    }
    ctx->seq++;
}

/* ----------------------------------------------------------------
 *
 *                          BUFFERING
 *
 * ---------------------------------------------------------------*/
NK_INTERN void
nk_start(struct nk_context *ctx, struct nk_window *win)
{
    NK_ASSERT(ctx);
    NK_ASSERT(win);
    if (!ctx || !win) return;
    win->buffer.begin = ctx->memory.allocated;
    win->buffer.end = win->buffer.begin;
    win->buffer.last = win->buffer.begin;
    win->buffer.clip = nk_null_rect;
}

NK_INTERN void
nk_start_popup(struct nk_context *ctx, struct nk_window *win)
{
    struct nk_popup_buffer *buf;
    struct nk_panel *iter;
    NK_ASSERT(ctx);
    NK_ASSERT(win);
    if (!ctx || !win) return;

    /* make sure to use the correct popup buffer*/
    iter = win->layout;
    while (iter->parent)
        iter = iter->parent;

    /* save buffer fill state for popup */
    buf = &iter->popup_buffer;
    buf->begin = win->buffer.end;
    buf->end = win->buffer.end;
    buf->parent = win->buffer.last;
    buf->last = buf->begin;
    buf->active = nk_true;
}

NK_INTERN void
nk_finish_popup(struct nk_context *ctx, struct nk_window *win)
{
    struct nk_popup_buffer *buf;
    struct nk_panel *iter;
    NK_ASSERT(ctx);
    NK_ASSERT(win);
    if (!ctx || !win) return;

    /* make sure to use the correct popup buffer*/
    iter = win->layout;
    while (iter->parent)
        iter = iter->parent;

    buf = &iter->popup_buffer;
    buf->last = win->buffer.last;
    buf->end = win->buffer.end;
}

NK_INTERN void
nk_finish(struct nk_context *ctx, struct nk_window *win)
{
    struct nk_popup_buffer *buf;
    struct nk_command *parent_last;
    struct nk_command *sublast;
    struct nk_command *last;
    void *memory;

    NK_ASSERT(ctx);
    NK_ASSERT(win);
    if (!ctx || !win) return;
    win->buffer.end = ctx->memory.allocated;
    if (!win->layout->popup_buffer.active) return;

    /* from here this case is for popup windows */
    buf = &win->layout->popup_buffer;
    memory = ctx->memory.memory.ptr;

    /* redirect the sub-window buffer to the end of the window command buffer */
    parent_last = nk_ptr_add(struct nk_command, memory, buf->parent);
    sublast = nk_ptr_add(struct nk_command, memory, buf->last);
    last = nk_ptr_add(struct nk_command, memory, win->buffer.last);

    parent_last->next = buf->end;
    sublast->next = last->next;
    last->next = buf->begin;
    win->buffer.last = buf->last;
    win->buffer.end = buf->end;
    buf->active = nk_false;
}

NK_INTERN void
nk_build(struct nk_context *ctx)
{
    struct nk_window *iter;
    struct nk_window *next;
    struct nk_command *cmd;
    nk_byte *buffer;

    iter = ctx->begin;
    buffer = (nk_byte*)ctx->memory.memory.ptr;
    while (iter != 0) {
        next = iter->next;
        if (iter->buffer.last == iter->buffer.begin || (iter->flags & NK_WINDOW_HIDDEN)) {
            iter = next;
            continue;
        }
        cmd = nk_ptr_add(struct nk_command, buffer, iter->buffer.last);
        while (next && ((next->buffer.last == next->buffer.begin) ||
            (next->flags & NK_WINDOW_HIDDEN)))
            next = next->next; /* skip empty command buffers */

        if (next) {
            cmd->next = next->buffer.begin;
        } else cmd->next = ctx->memory.allocated;
        iter = next;
    }
}

NK_API const struct nk_command*
nk__begin(struct nk_context *ctx)
{
    struct nk_window *iter;
    nk_byte *buffer;
    NK_ASSERT(ctx);
    if (!ctx) return 0;
    if (!ctx->count) return 0;

    /* build one command list out of all windows */
    buffer = (nk_byte*)ctx->memory.memory.ptr;
    if (!ctx->build) {
        nk_build(ctx);
        ctx->build = nk_true;
    }

    iter = ctx->begin;
    while (iter && ((iter->buffer.begin == iter->buffer.end) || (iter->flags & NK_WINDOW_HIDDEN)))
        iter = iter->next;
    if (!iter) return 0;
    return nk_ptr_add_const(struct nk_command, buffer, iter->buffer.begin);
}

NK_API const struct nk_command*
nk__next(struct nk_context *ctx, const struct nk_command *cmd)
{
    nk_byte *buffer;
    const struct nk_command *next;
    NK_ASSERT(ctx);
    if (!ctx || !cmd || !ctx->count) return 0;
    if (cmd->next >= ctx->memory.allocated) return 0;
    buffer = (nk_byte*)ctx->memory.memory.ptr;
    next = nk_ptr_add_const(struct nk_command, buffer, cmd->next);
    return next;
}
/* ----------------------------------------------------------------
 *
 *                          PAGE ELEMENT
 *
 * ---------------------------------------------------------------*/
NK_INTERN struct nk_page_element*
nk_create_page_element(struct nk_context *ctx)
{
    struct nk_page_element *elem;
    if (ctx->freelist) {
        /* unlink page element from free list */
        elem = ctx->freelist;
        ctx->freelist = elem->next;
    } else if (ctx->pool) {
        /* allocate page element from memory pool */
        elem = nk_pool_alloc((struct nk_pool*)ctx->pool);
        NK_ASSERT(elem);
        if (!elem) return 0;
    } else {
        /* allocate new page element from the back of the fixed size memory buffer */
        NK_STORAGE const nk_size size = sizeof(struct nk_page_element);
        NK_STORAGE const nk_size align = NK_ALIGNOF(struct nk_page_element);
        elem = (struct nk_page_element*)nk_buffer_alloc(&ctx->memory, NK_BUFFER_BACK, size, align);
        NK_ASSERT(elem);
        if (!elem) return 0;
    }
    nk_zero_struct(*elem);
    elem->next = 0;
    elem->prev = 0;
    return elem;
}

NK_INTERN void
nk_free_page_element(struct nk_context *ctx, struct nk_page_element *elem)
{
    /* link table into freelist */
    if (!ctx->freelist) {
        ctx->freelist = elem;
    } else {
        elem->next = ctx->freelist;
        ctx->freelist = elem;
    }
}

/* ----------------------------------------------------------------
 *
 *                          TABLES
 *
 * ---------------------------------------------------------------*/
NK_INTERN struct nk_table*
nk_create_table(struct nk_context *ctx)
{
    struct nk_page_element *elem = nk_create_page_element(ctx);
    if (!elem) return 0;
    return &elem->data.tbl;
}

NK_INTERN void
nk_free_table(struct nk_context *ctx, struct nk_table *tbl)
{
    union nk_page_data *pd = NK_CONTAINER_OF(tbl, union nk_page_data, tbl);
    struct nk_page_element *pe = NK_CONTAINER_OF(pd, struct nk_page_element, data);
    nk_free_page_element(ctx, pe);
}

NK_INTERN void
nk_push_table(struct nk_window *win, struct nk_table *tbl)
{
    if (!win->tables) {
        win->tables = tbl;
        tbl->next = 0;
        tbl->prev = 0;
        win->table_count = 1;
        win->table_size = 1;
        return;
    }
    win->tables->prev = tbl;
    tbl->next = win->tables;
    tbl->prev = 0;
    win->tables = tbl;
    win->table_count++;
    win->table_size = 0;
}

NK_INTERN void
nk_remove_table(struct nk_window *win, struct nk_table *tbl)
{
    if (win->tables == tbl)
        win->tables = tbl->next;
    if (tbl->next)
        tbl->next->prev = tbl->prev;
    if (tbl->prev)
        tbl->prev->next = tbl->next;
    tbl->next = 0;
    tbl->prev = 0;
}

NK_INTERN nk_uint*
nk_add_value(struct nk_context *ctx, struct nk_window *win,
            nk_hash name, nk_uint value)
{
    if (!win->tables || win->table_size == NK_VALUE_PAGE_CAPACITY) {
        struct nk_table *tbl = nk_create_table(ctx);
        nk_push_table(win, tbl);
    }
    win->tables->seq = win->seq;
    win->tables->keys[win->table_size] = name;
    win->tables->values[win->table_size] = value;
    return &win->tables->values[win->table_size++];
}

NK_INTERN nk_uint*
nk_find_value(struct nk_window *win, nk_hash name)
{
    unsigned short size = win->table_size;
    struct nk_table *iter = win->tables;
    while (iter) {
        unsigned short i = 0;
        for (i = 0; i < size; ++i) {
            if (iter->keys[i] == name) {
                iter->seq = win->seq;
                return &iter->values[i];
            }
        }
        size = NK_VALUE_PAGE_CAPACITY;
        iter = iter->next;
    }
    return 0;
}

/* ----------------------------------------------------------------
 *
 *                          WINDOW
 *
 * ---------------------------------------------------------------*/
NK_INTERN int nk_panel_begin(struct nk_context *ctx, const char *title);
NK_INTERN void nk_panel_end(struct nk_context *ctx);

NK_INTERN void*
nk_create_window(struct nk_context *ctx)
{
    struct nk_page_element *elem = nk_create_page_element(ctx);
    if (!elem) return 0;
    elem->data.win.seq = ctx->seq;
    return &elem->data.win;
}

NK_INTERN void
nk_free_window(struct nk_context *ctx, struct nk_window *win)
{
    /* unlink windows from list */
    struct nk_table *n, *it = win->tables;
    if (win->popup.win) {
        nk_free_window(ctx, win->popup.win);
        win->popup.win = 0;
    }
    win->next = 0;
    win->prev = 0;

    while (it) {
        /*free window state tables */
        n = it->next;
        nk_remove_table(win, it);
        nk_free_table(ctx, it);
        if (it == win->tables)
            win->tables = n;
        it = n;
    }

    /* link windows into freelist */
    {union nk_page_data *pd = NK_CONTAINER_OF(win, union nk_page_data, win);
    struct nk_page_element *pe = NK_CONTAINER_OF(pd, struct nk_page_element, data);
    nk_free_page_element(ctx, pe);}
}

NK_INTERN struct nk_window*
nk_find_window(struct nk_context *ctx, nk_hash hash)
{
    struct nk_window *iter;
    iter = ctx->begin;
    while (iter) {
        NK_ASSERT(iter != iter->next);
        if (iter->name == hash)
            return iter;
        iter = iter->next;
    }
    return 0;
}

NK_INTERN void
nk_insert_window(struct nk_context *ctx, struct nk_window *win)
{
    const struct nk_window *iter;
    struct nk_window *end;
    NK_ASSERT(ctx);
    NK_ASSERT(win);
    if (!win || !ctx) return;

    iter = ctx->begin;
    while (iter) {
        NK_ASSERT(iter != iter->next);
        NK_ASSERT(iter != win);
        if (iter == win) return;
        iter = iter->next;
    }

    if (!ctx->begin) {
        win->next = 0;
        win->prev = 0;
        ctx->begin = win;
        ctx->end = win;
        ctx->count = 1;
        return;
    }

    end = ctx->end;
    end->flags |= NK_WINDOW_ROM;
    end->next = win;
    win->prev = ctx->end;
    win->next = 0;
    ctx->end = win;
    ctx->count++;

    ctx->active = ctx->end;
    ctx->end->flags &= ~(nk_flags)NK_WINDOW_ROM;
}

NK_INTERN void
nk_remove_window(struct nk_context *ctx, struct nk_window *win)
{
    if (win == ctx->begin || win == ctx->end) {
        if (win == ctx->begin) {
            ctx->begin = win->next;
            if (win->next)
                win->next->prev = 0;
        }
        if (win == ctx->end) {
            ctx->end = win->prev;
            if (win->prev)
                win->prev->next = 0;
        }
    } else {
        if (win->next)
            win->next->prev = win->prev;
        if (win->prev)
            win->prev->next = win->next;
    }
    if (win == ctx->active || !ctx->active) {
        ctx->active = ctx->end;
        if (ctx->end)
            ctx->end->flags &= ~(nk_flags)NK_WINDOW_ROM;
    }
    win->next = 0;
    win->prev = 0;
    ctx->count--;
}

NK_API int
nk_begin(struct nk_context *ctx, struct nk_panel *layout, const char *title,
    struct nk_rect bounds, nk_flags flags)
{
    struct nk_window *win;
    struct nk_style *style;
    nk_hash title_hash;
    int title_len;
    int ret = 0;

    NK_ASSERT(ctx);
    NK_ASSERT(!ctx->current && "if this triggers you missed a `nk_end` call");
    if (!ctx || ctx->current || !title)
        return 0;

    /* find or create window */
    style = &ctx->style;
    title_len = (int)nk_strlen(title);
    title_hash = nk_murmur_hash(title, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash);
    if (!win) {
        /* create new window */
        win = (struct nk_window*)nk_create_window(ctx);
        NK_ASSERT(win);
        if (!win) return 0;
        nk_insert_window(ctx, win);
        nk_command_buffer_init(&win->buffer, &ctx->memory, NK_CLIPPING_ON);

        win->flags = flags;
        win->bounds = bounds;
        win->name = title_hash;
        win->popup.win = 0;
        if (!ctx->active)
            ctx->active = win;
    } else {
        /* update public window flags */
        win->flags &= ~(nk_flags)(NK_WINDOW_PRIVATE-1);
        win->flags |= flags;
        win->seq++;
        if (!ctx->active)
            ctx->active = win;
    }
    if (win->flags & NK_WINDOW_HIDDEN) {
        ctx->current = win;
        return 0;
    }

    /* window overlapping */
    if (!(win->flags & NK_WINDOW_SUB) && !(win->flags & NK_WINDOW_HIDDEN))
    {
        int inpanel, ishovered;
        const struct nk_window *iter = win;
        float h = ctx->style.font.height + 2 * style->window.header.padding.y;

        /* activate window if hovered and no other window is overlapping this window */
        nk_start(ctx, win);
        inpanel = nk_input_has_mouse_click_down_in_rect(&ctx->input, NK_BUTTON_LEFT, win->bounds, nk_true);
        ishovered = nk_input_is_mouse_hovering_rect(&ctx->input, win->bounds);
        if ((win != ctx->active) && ishovered) {
            iter = win->next;
            while (iter) {
                if (!(iter->flags & NK_WINDOW_MINIMIZED)) {
                    if (NK_INTERSECT(win->bounds.x, win->bounds.y, win->bounds.w, win->bounds.h,
                        iter->bounds.x, iter->bounds.y, iter->bounds.w, iter->bounds.h) &&
                        !(iter->flags & NK_WINDOW_HIDDEN))
                        break;
                } else {
                    if (NK_INTERSECT(win->bounds.x, win->bounds.y, win->bounds.w, win->bounds.h,
                        iter->bounds.x, iter->bounds.y, iter->bounds.w, h) &&
                        !(iter->flags & NK_WINDOW_HIDDEN))
                        break;
                }
                if (iter->popup.win && iter->popup.active && !(iter->flags & NK_WINDOW_HIDDEN) &&
                    NK_INTERSECT(win->bounds.x, win->bounds.y, win->bounds.w, win->bounds.h,
                    iter->popup.win->bounds.x, iter->popup.win->bounds.y,
                    iter->popup.win->bounds.w, iter->popup.win->bounds.h))
                    break;
                iter = iter->next;
            }
        }

        /* activate window if clicked */
        if (iter && inpanel && (win != ctx->end)) {
            iter = win->next;
            while (iter) {
                /* try to find a panel with higher priority in the same position */
                if (!(iter->flags & NK_WINDOW_MINIMIZED)) {
                    if (NK_INBOX(ctx->input.mouse.pos.x, ctx->input.mouse.pos.y, iter->bounds.x,
                        iter->bounds.y, iter->bounds.w, iter->bounds.h) &&
                        !(iter->flags & NK_WINDOW_HIDDEN))
                        break;
                } else {
                    if (NK_INBOX(ctx->input.mouse.pos.x, ctx->input.mouse.pos.y, iter->bounds.x,
                        iter->bounds.y, iter->bounds.w, h) &&
                        !(iter->flags & NK_WINDOW_HIDDEN))
                        break;
                }
                if (iter->popup.win && iter->popup.active && !(iter->flags & NK_WINDOW_HIDDEN) &&
                    NK_INTERSECT(win->bounds.x, win->bounds.y, win->bounds.w, win->bounds.h,
                    iter->popup.win->bounds.x, iter->popup.win->bounds.y,
                    iter->popup.win->bounds.w, iter->popup.win->bounds.h))
                    break;
                iter = iter->next;
            }
        }

        if (!iter && ctx->end != win) {
            /* current window is active in that position so transfer to top
             * at the highest priority in stack */
            nk_remove_window(ctx, win);
            nk_insert_window(ctx, win);

            win->flags &= ~(nk_flags)NK_WINDOW_ROM;
            ctx->active = win;
        }
        if (ctx->end != win)
            win->flags |= NK_WINDOW_ROM;
    }

    win->layout = layout;
    ctx->current = win;
    ret = nk_panel_begin(ctx, title);
    layout->offset = &win->scrollbar;
    return ret;
}

NK_API void
nk_end(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current) return;
    if (ctx->current->flags & NK_WINDOW_HIDDEN) {
        ctx->current = 0;
        return;
    }
    nk_panel_end(ctx);
    ctx->current = 0;
}

NK_API struct nk_rect
nk_window_get_bounds(const struct nk_context *ctx)
{
    NK_ASSERT(ctx); NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return nk_rect(0,0,0,0);
    return ctx->current->bounds;
}

NK_API struct nk_vec2
nk_window_get_position(const struct nk_context *ctx)
{
    NK_ASSERT(ctx); NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return nk_vec2(0,0);
    return nk_vec2(ctx->current->bounds.x, ctx->current->bounds.y);
}

NK_API struct nk_vec2
nk_window_get_size(const struct nk_context *ctx)
{
    NK_ASSERT(ctx); NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return nk_vec2(0,0);
    return nk_vec2(ctx->current->bounds.w, ctx->current->bounds.h);
}

NK_API float
nk_window_get_width(const struct nk_context *ctx)
{
    NK_ASSERT(ctx); NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return 0;
    return ctx->current->bounds.w;
}

NK_API float
nk_window_get_height(const struct nk_context *ctx)
{
    NK_ASSERT(ctx); NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return 0;
    return ctx->current->bounds.h;
}

NK_API struct nk_rect
nk_window_get_content_region(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return nk_rect(0,0,0,0);
    return ctx->current->layout->clip;
}

NK_API struct nk_vec2
nk_window_get_content_region_min(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current) return nk_vec2(0,0);
    return nk_vec2(ctx->current->layout->clip.x, ctx->current->layout->clip.y);
}

NK_API struct nk_vec2
nk_window_get_content_region_max(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current) return nk_vec2(0,0);
    return nk_vec2(ctx->current->layout->clip.x + ctx->current->layout->clip.w,
        ctx->current->layout->clip.y + ctx->current->layout->clip.h);
}

NK_API struct nk_vec2
nk_window_get_content_region_size(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current) return nk_vec2(0,0);
    return nk_vec2(ctx->current->layout->clip.w, ctx->current->layout->clip.h);
}

NK_API struct nk_command_buffer*
nk_window_get_canvas(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current) return 0;
    return &ctx->current->buffer;
}

NK_API struct nk_panel*
nk_window_get_panel(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return 0;
    return ctx->current->layout;
}

NK_API int
nk_window_has_focus(const struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current) return 0;
    return ctx->current == ctx->active;
}

NK_API int
nk_window_is_hovered(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return 0;
    return nk_input_is_mouse_hovering_rect(&ctx->input, ctx->current->bounds);
}

NK_API int
nk_window_is_any_hovered(struct nk_context *ctx)
{
    struct nk_window *iter;
    NK_ASSERT(ctx);
    if (!ctx) return 0;
    iter = ctx->begin;
    while (iter) {
        /* check if window is being hovered */
        if (iter->flags & NK_WINDOW_MINIMIZED) {
            struct nk_rect header = iter->bounds;
            header.h = ctx->style.font.height + 2 * ctx->style.window.header.padding.y;
            if (nk_input_is_mouse_hovering_rect(&ctx->input, header))
                return 1;
        } else if (nk_input_is_mouse_hovering_rect(&ctx->input, iter->bounds)) {
            return 1;
        }
        /* check if window is being hovered */
        if (iter->popup.active && nk_input_is_mouse_hovering_rect(&ctx->input, iter->popup.win->bounds))
            return 1;
        iter = iter->next;
    }
    return 0;
}

NK_API int
nk_item_is_any_active(struct nk_context *ctx)
{
    int any_hovered = nk_window_is_any_hovered(ctx);
    int any_active = (ctx->last_widget_state & NK_WIDGET_STATE_MODIFIED);
    return any_hovered || any_active;
}

NK_API int
nk_window_is_collapsed(struct nk_context *ctx, const char *name)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return 0;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash);
    if (!win) return 0;
    return win->flags & NK_WINDOW_MINIMIZED;
}

NK_API int
nk_window_is_closed(struct nk_context *ctx, const char *name)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return 1;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash);
    if (!win) return 1;
    return (win->flags & NK_WINDOW_HIDDEN);
}

NK_API int
nk_window_is_active(struct nk_context *ctx, const char *name)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return 0;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash);
    if (!win) return 0;
    return win == ctx->active;
}

NK_API struct nk_window*
nk_window_find(struct nk_context *ctx, const char *name)
{
    int title_len;
    nk_hash title_hash;
    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    return nk_find_window(ctx, title_hash);
}

NK_API void
nk_window_close(struct nk_context *ctx, const char *name)
{
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return;
    win = nk_window_find(ctx, name);
    if (!win) return;
    NK_ASSERT(ctx->current != win && "You cannot close a currently active window");
    if (ctx->current == win) return;
    win->flags |= NK_WINDOW_HIDDEN;
}

NK_API void
nk_window_set_bounds(struct nk_context *ctx, struct nk_rect bounds)
{
    NK_ASSERT(ctx); NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return;
    ctx->current->bounds = bounds;
}

NK_API void
nk_window_set_position(struct nk_context *ctx, struct nk_vec2 pos)
{
    NK_ASSERT(ctx); NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return;
    ctx->current->bounds.x = pos.x;
    ctx->current->bounds.y = pos.y;
}

NK_API void
nk_window_set_size(struct nk_context *ctx, struct nk_vec2 size)
{
    NK_ASSERT(ctx); NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current) return;
    ctx->current->bounds.w = size.x;
    ctx->current->bounds.h = size.y;
}

NK_API void
nk_window_collapse(struct nk_context *ctx, const char *name,
                    enum nk_collapse_states c)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash);
    if (!win) return;
    if (c == NK_MINIMIZED)
        win->flags |= NK_WINDOW_MINIMIZED;
    else win->flags &= ~(nk_flags)NK_WINDOW_MINIMIZED;
}

NK_API void
nk_window_collapse_if(struct nk_context *ctx, const char *name,
    enum nk_collapse_states c, int cond)
{
    NK_ASSERT(ctx);
    if (!ctx || !cond) return;
    nk_window_collapse(ctx, name, c);
}

NK_API void
nk_window_show(struct nk_context *ctx, const char *name, enum nk_show_states s)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash);
    if (!win) return;
    if (s == NK_HIDDEN)
        win->flags |= NK_WINDOW_HIDDEN;
    else win->flags &= ~(nk_flags)NK_WINDOW_HIDDEN;
}

NK_API void
nk_window_show_if(struct nk_context *ctx, const char *name,
    enum nk_show_states s, int cond)
{
    NK_ASSERT(ctx);
    if (!ctx || !cond) return;
    nk_window_show(ctx, name, s);
}

NK_API void
nk_window_set_focus(struct nk_context *ctx, const char *name)
{
    int title_len;
    nk_hash title_hash;
    struct nk_window *win;
    NK_ASSERT(ctx);
    if (!ctx) return;

    title_len = (int)nk_strlen(name);
    title_hash = nk_murmur_hash(name, (int)title_len, NK_WINDOW_TITLE);
    win = nk_find_window(ctx, title_hash);
    if (win && ctx->end != win) {
        nk_remove_window(ctx, win);
        nk_insert_window(ctx, win);
    }
    ctx->active = win;
}

/*----------------------------------------------------------------
 *
 *                          PANEL
 *
 * --------------------------------------------------------------*/
static int
nk_window_has_header(struct nk_window *win, const char *title)
{
    /* window header state */
    int active = 0;
    active = (win->flags & (NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE));
    active = active || (win->flags & NK_WINDOW_TITLE);
    active = active && !(win->flags & NK_WINDOW_HIDDEN) && title;
    return active;
}

NK_INTERN int
nk_panel_begin(struct nk_context *ctx, const char *title)
{
    struct nk_input *in;
    struct nk_window *win;
    struct nk_panel *layout;
    struct nk_command_buffer *out;
    const struct nk_style *style;
    const struct nk_user_font *font;

    int header_active = 0;
    struct nk_vec2 scrollbar_size;
    struct nk_vec2 item_spacing;
    struct nk_vec2 window_padding;
    struct nk_vec2 scaler_size;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    style = &ctx->style;
    font = &style->font;
    in = &ctx->input;
    win = ctx->current;
    layout = win->layout;

    /* cache style data */
    scrollbar_size = style->window.scrollbar_size;
    window_padding = style->window.padding;
    item_spacing = style->window.spacing;
    scaler_size = style->window.scaler_size;

    /* check arguments */
    nk_zero(layout, sizeof(*layout));
    if (win->flags & NK_WINDOW_HIDDEN)
        return 0;

#ifdef NK_INCLUDE_COMMAND_USERDATA
    win->buffer.userdata = ctx->userdata;
#endif

    /* window dragging */
    if ((win->flags & NK_WINDOW_MOVABLE) && !(win->flags & NK_WINDOW_ROM)) {
        int left_mouse_down;
        int left_mouse_click_in_cursor;
        struct nk_rect move;
        move.x = win->bounds.x;
        move.y = win->bounds.y;
        move.w = win->bounds.w;

        move.h = layout->header_h;
        if (nk_window_has_header(win, title)) {
            move.h = font->height + 2.0f * style->window.header.padding.y;
            move.h += 2.0f * style->window.header.label_padding.y;
        } else move.h = window_padding.y + item_spacing.y;

        /*incursor = nk_input_is_mouse_prev_hovering_rect(in, move);*/
        left_mouse_down = in->mouse.buttons[NK_BUTTON_LEFT].down;
        left_mouse_click_in_cursor = nk_input_has_mouse_click_down_in_rect(in,
            NK_BUTTON_LEFT, move, nk_true);

        if (left_mouse_down && left_mouse_click_in_cursor) {
            win->bounds.x = win->bounds.x + in->mouse.delta.x;
            win->bounds.y = win->bounds.y + in->mouse.delta.y;
            in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.x += in->mouse.delta.x;
            in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos.y += in->mouse.delta.y;
        }
    }

    /* panel space with border */
    if (win->flags & NK_WINDOW_BORDER) {
        if (!(win->flags & NK_WINDOW_SUB))
            layout->bounds = nk_shrink_rect(win->bounds, style->window.border);
        else if (win->flags & NK_WINDOW_COMBO)
            layout->bounds = nk_shrink_rect(win->bounds, style->window.combo_border);
        else if (win->flags & NK_WINDOW_CONTEXTUAL)
            layout->bounds = nk_shrink_rect(win->bounds, style->window.contextual_border);
        else if (win->flags & NK_WINDOW_MENU)
            layout->bounds = nk_shrink_rect(win->bounds, style->window.menu_border);
        else if (win->flags & NK_WINDOW_GROUP)
            layout->bounds = nk_shrink_rect(win->bounds, style->window.group_border);
        else if (win->flags & NK_WINDOW_TOOLTIP)
            layout->bounds = nk_shrink_rect(win->bounds, style->window.tooltip_border);
        else layout->bounds = nk_shrink_rect(win->bounds, style->window.border);
    } else layout->bounds = win->bounds;

    /* setup panel */
    layout->border = layout->bounds.x - win->bounds.x;
    layout->at_x = layout->bounds.x;
    layout->at_y = layout->bounds.y;
    layout->width = layout->bounds.w;
    layout->height = layout->bounds.h;
    layout->max_x = 0;
    layout->row.index = 0;
    layout->row.columns = 0;
    layout->row.height = 0;
    layout->row.ratio = 0;
    layout->row.item_width = 0;
    layout->row.tree_depth = 0;
    layout->flags = win->flags;
    out = &win->buffer;

    /* calculate window header */
    if (win->flags & NK_WINDOW_MINIMIZED) {
        layout->header_h = 0;
        layout->row.height = 0;
    } else {
        layout->header_h = 0;
        layout->row.height = item_spacing.y + window_padding.y;
    }

    /* calculate window footer height */
    if (!(win->flags & NK_WINDOW_NONBLOCK) &&
        (!(win->flags & NK_WINDOW_NO_SCROLLBAR) || (win->flags & NK_WINDOW_SCALABLE)))
        layout->footer_h = scaler_size.y + style->window.footer_padding.y;
    else layout->footer_h = 0;

    /* calculate the window size */
    if (!(win->flags & NK_WINDOW_NO_SCROLLBAR))
        layout->width = layout->bounds.w - scrollbar_size.x;
    layout->height = layout->bounds.h - (layout->header_h + item_spacing.y + window_padding.y);
    layout->height -= layout->footer_h;

    /* window header */
    header_active = nk_window_has_header(win, title);
    if (header_active)
    {
        struct nk_rect header;
        struct nk_rect button;
        struct nk_text text;
        const struct nk_style_item *background = 0;

        /* calculate header bounds */
        header.x = layout->bounds.x;
        header.y = layout->bounds.y;
        header.w = layout->bounds.w;

        /* calculate correct header height */
        layout->header_h = font->height + 2.0f * style->window.header.padding.y;
        layout->header_h += 2.0f * style->window.header.label_padding.y;
        layout->row.height += layout->header_h;
        header.h = layout->header_h + 0.5f;

        /* update window height */
        layout->height = layout->bounds.h - (header.h + 2 * item_spacing.y);
        layout->height -= layout->footer_h;

        /* select correct header background and text color */
        if (ctx->active == win) {
            background = &style->window.header.active;
            text.text = style->window.header.label_active;
        } else if (nk_input_is_mouse_hovering_rect(&ctx->input, header)) {
            background = &style->window.header.hover;
            text.text = style->window.header.label_hover;
        } else {
            background = &style->window.header.normal;
            text.text = style->window.header.label_normal;
        }

        /* draw header background */
        if (background->type == NK_STYLE_ITEM_IMAGE) {
            text.background = nk_rgba(0,0,0,0);
            nk_draw_image(&win->buffer, header, &background->data.image);
        } else {
            text.background = background->data.color;
            nk_fill_rect(out, nk_rect(layout->bounds.x, layout->bounds.y,
                layout->bounds.w, layout->header_h), 0, background->data.color);
        }

        /* window close button */
        button.y = header.y + style->window.header.padding.y;
        button.h = layout->header_h - 2 * style->window.header.padding.y;
        button.w = button.h;
        if (win->flags & NK_WINDOW_CLOSABLE) {
            nk_flags ws = 0;
            if (style->window.header.align == NK_HEADER_RIGHT) {
                button.x = (header.w + header.x) - (button.w + style->window.header.padding.x);
                header.w -= button.w + style->window.header.spacing.x + style->window.header.padding.x;
            } else {
                button.x = header.x + style->window.header.padding.x;
                header.x += button.w + style->window.header.spacing.x + style->window.header.padding.x;
            }
            if (nk_do_button_symbol(&ws, &win->buffer, button,
                style->window.header.close_symbol, NK_BUTTON_DEFAULT,
                &style->window.header.close_button, in, &style->font))
                layout->flags |= NK_WINDOW_HIDDEN;
        }

        /* window minimize button */
        if (win->flags & NK_WINDOW_MINIMIZABLE) {
            nk_flags ws = 0;
            if (style->window.header.align == NK_HEADER_RIGHT) {
                button.x = (header.w + header.x) - button.w;
                if (!(win->flags & NK_WINDOW_CLOSABLE)) {
                    button.x -= style->window.header.padding.x;
                    header.w -= style->window.header.padding.x;
                }
                header.w -= button.w + style->window.header.spacing.x;
            } else {
                button.x = header.x;
                header.x += button.w + style->window.header.spacing.x + style->window.header.padding.x;
            }
            if (nk_do_button_symbol(&ws, &win->buffer, button,
                (layout->flags & NK_WINDOW_MINIMIZED)?
                style->window.header.maximize_symbol:
                style->window.header.minimize_symbol,
                NK_BUTTON_DEFAULT, &style->window.header.minimize_button, in, &style->font))
                layout->flags = (layout->flags & NK_WINDOW_MINIMIZED) ?
                    layout->flags & (nk_flags)~NK_WINDOW_MINIMIZED:
                    layout->flags | NK_WINDOW_MINIMIZED;
        }
        {
            /* window header title */
            int text_len = nk_strlen(title);
            struct nk_rect label = {0,0,0,0};
            float t = font->width(font->userdata, font->height, title, text_len);

            label.x = header.x + style->window.header.padding.x;
            label.x += style->window.header.label_padding.x;
            label.y = header.y + style->window.header.label_padding.y;
            label.h = font->height + 2 * style->window.header.label_padding.y;
            label.w = t + 2 * style->window.header.spacing.x;
            text.padding = nk_vec2(0,0);
            nk_widget_text(out, label,(const char*)title, text_len, &text,
                NK_TEXT_LEFT, font);
        }
    }

    /* fix header height for transition between minimized and maximized window state */
    if (win->flags & NK_WINDOW_MINIMIZED && !(layout->flags & NK_WINDOW_MINIMIZED))
        layout->row.height += 2 * item_spacing.y + style->window.border;

    if (layout->flags & NK_WINDOW_MINIMIZED) {
        /* draw window background if minimized */
        layout->row.height = 0;
        nk_fill_rect(out, nk_rect(layout->bounds.x, layout->bounds.y,
            layout->bounds.w, layout->row.height), 0, style->window.background);
    } else if (!(layout->flags & NK_WINDOW_DYNAMIC)) {
        /* draw fixed window body */
        struct nk_rect body = layout->bounds;
        if (header_active) {
            body.y += layout->header_h - 0.5f;
            body.h -= layout->header_h;
        }
        if (style->window.fixed_background.type == NK_STYLE_ITEM_IMAGE)
            nk_draw_image(out, body, &style->window.fixed_background.data.image);
        else nk_fill_rect(out, body, 0, style->window.fixed_background.data.color);
    } else {
        /* draw dynamic window body */
        nk_fill_rect(out, nk_rect(layout->bounds.x, layout->bounds.y,
            layout->bounds.w, layout->row.height + window_padding.y), 0,
            style->window.background);
    }
    {
        /* calculate and set the window clipping rectangle*/
        struct nk_rect clip;
        if (!(win->flags & NK_WINDOW_DYNAMIC)) {
            layout->clip.x = layout->bounds.x + window_padding.x;
            layout->clip.w = layout->width - 2 * window_padding.x;
        } else {
            layout->clip.x = layout->bounds.x;
            layout->clip.w = layout->width;
        }

        layout->clip.h = layout->bounds.h - (layout->footer_h + layout->header_h);
        layout->clip.h -= (2.0f * window_padding.y);
        layout->clip.y = layout->bounds.y;

        /* combo box and menu do not have header space */
        if (!(win->flags & NK_WINDOW_COMBO) && !(win->flags & NK_WINDOW_MENU))
            layout->clip.y += layout->header_h;

        nk_unify(&clip, &win->buffer.clip, layout->clip.x, layout->clip.y,
            layout->clip.x + layout->clip.w, layout->clip.y + layout->clip.h);
        nk_push_scissor(out, clip);
        layout->clip = clip;

        win->buffer.clip.x = layout->bounds.x;
        win->buffer.clip.w = layout->width;
        if (!(win->flags & NK_WINDOW_NO_SCROLLBAR))
            win->buffer.clip.w += scrollbar_size.x;
    }
    return !(layout->flags & NK_WINDOW_HIDDEN) && !(layout->flags & NK_WINDOW_MINIMIZED);
}

NK_INTERN void
nk_panel_end(struct nk_context *ctx)
{
    struct nk_input *in;
    struct nk_window *window;
    struct nk_panel *layout;
    const struct nk_style *style;
    struct nk_command_buffer *out;

    struct nk_vec2 scrollbar_size;
    struct nk_vec2 scaler_size;
    struct nk_vec2 item_spacing;
    struct nk_vec2 window_padding;
    struct nk_rect footer = {0,0,0,0};

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    window = ctx->current;
    layout = window->layout;
    style = &ctx->style;
    out = &window->buffer;
    in = (layout->flags & NK_WINDOW_ROM) ? 0 :&ctx->input;
    if (!(layout->flags & NK_WINDOW_SUB))
        nk_push_scissor(out, nk_null_rect);

    /* cache configuration data */
    item_spacing = style->window.spacing;
    window_padding = style->window.padding;
    scrollbar_size = style->window.scrollbar_size;
    scaler_size = style->window.scaler_size;

    /* update the current cursor Y-position to point over the last added widget */
    layout->at_y += layout->row.height;

    /* draw footer and fill empty spaces inside a dynamically growing panel */
    if (layout->flags & NK_WINDOW_DYNAMIC && !(layout->flags & NK_WINDOW_MINIMIZED)) {
        layout->height = layout->at_y - layout->bounds.y;
        layout->height = NK_MIN(layout->height, layout->bounds.h);

        if ((layout->offset->x == 0) || (layout->flags & NK_WINDOW_NO_SCROLLBAR)) {
            /* special case for dynamic windows without horizontal scrollbar
             * or hidden scrollbars */
            footer.x = window->bounds.x;
            footer.y = window->bounds.y + layout->height + item_spacing.y;
            footer.w = window->bounds.w + scrollbar_size.x;
            layout->footer_h = 0;
            footer.h = 0;

            if ((layout->offset->x == 0) && !(layout->flags & NK_WINDOW_NO_SCROLLBAR)) {
                /* special case for windows like combobox, menu require draw call
                 * to fill the empty scrollbar background */
                struct nk_rect bounds;
                bounds.x = layout->bounds.x + layout->width;
                bounds.y = layout->clip.y;
                bounds.w = scrollbar_size.x;
                bounds.h = layout->height;
                nk_fill_rect(out, bounds, 0, style->window.background);
            }
        } else {
            /* dynamic window with visible scrollbars and therefore bigger footer */
            footer.x = window->bounds.x;
            footer.w = window->bounds.w + scrollbar_size.x;
            footer.h = layout->footer_h;
            if ((layout->flags & NK_WINDOW_COMBO) || (layout->flags & NK_WINDOW_MENU) ||
                (layout->flags & NK_WINDOW_CONTEXTUAL))
                footer.y = window->bounds.y + layout->height;
            else footer.y = window->bounds.y + layout->height + layout->footer_h;
            nk_fill_rect(out, footer, 0, style->window.background);

            if (!(layout->flags & NK_WINDOW_COMBO) && !(layout->flags & NK_WINDOW_MENU)) {
                /* fill empty scrollbar space */
                struct nk_rect bounds;
                bounds.x = layout->bounds.x;
                bounds.y = window->bounds.y + layout->height;
                bounds.w = layout->bounds.w;
                bounds.h = layout->row.height;
                nk_fill_rect(out, bounds, 0, style->window.background);
            }
        }
    }

    /* scrollbars */
    if (!(layout->flags & NK_WINDOW_NO_SCROLLBAR) && !(layout->flags & NK_WINDOW_MINIMIZED))
    {
        struct nk_rect bounds;
        int scroll_has_scrolling;
        float scroll_target;
        float scroll_offset;
        float scroll_step;
        float scroll_inc;
        {
            /* vertical scrollbar */
            nk_flags state = 0;
            bounds.x = layout->bounds.x + layout->width;
            bounds.y = layout->clip.y;
            bounds.w = scrollbar_size.y;
            bounds.h = layout->clip.h;
            if (layout->flags & NK_WINDOW_BORDER) bounds.h -= 1;

            scroll_offset = layout->offset->y;
            scroll_step = layout->clip.h * 0.10f;
            scroll_inc = layout->clip.h * 0.01f;
            scroll_target = (float)(int)(layout->at_y - layout->clip.y);
            scroll_has_scrolling = (window == ctx->active);
            scroll_offset = nk_do_scrollbarv(&state, out, bounds, scroll_has_scrolling,
                    scroll_offset, scroll_target, scroll_step, scroll_inc,
                    &ctx->style.scrollv, in, &style->font);
            layout->offset->y = (unsigned short)scroll_offset;
        }
        {
            /* horizontal scrollbar */
            nk_flags state = 0;
            bounds.x = layout->bounds.x + window_padding.x;
            if (layout->flags & NK_WINDOW_SUB) {
                bounds.h = scrollbar_size.x;
                bounds.y = (layout->flags & NK_WINDOW_BORDER) ?
                            layout->bounds.y + 1 : layout->bounds.y;
                bounds.y += layout->header_h + layout->menu.h + layout->height;
                bounds.w = layout->clip.w;
            } else if (layout->flags & NK_WINDOW_DYNAMIC) {
                bounds.h = NK_MIN(scrollbar_size.x, layout->footer_h);
                bounds.w = layout->bounds.w;
                bounds.y = footer.y;
            } else {
                bounds.h = NK_MIN(scrollbar_size.x, layout->footer_h);
                bounds.y = layout->bounds.y + window->bounds.h;
                bounds.y -= NK_MAX(layout->footer_h, scrollbar_size.x);
                bounds.w = layout->width - 2 * window_padding.x;
            }
            scroll_offset = layout->offset->x;
            scroll_target = (float)(int)(layout->max_x - bounds.x);
            scroll_step = layout->max_x * 0.05f;
            scroll_inc = layout->max_x * 0.005f;
            scroll_has_scrolling = nk_false;
            scroll_offset = nk_do_scrollbarh(&state, out, bounds, scroll_has_scrolling,
                    scroll_offset, scroll_target, scroll_step, scroll_inc,
                    &ctx->style.scrollh, in, &style->font);
            layout->offset->x = (unsigned short)scroll_offset;
        }
    }

    /* scaler */
    if ((layout->flags & NK_WINDOW_SCALABLE) && in && !(layout->flags & NK_WINDOW_MINIMIZED)) {
        /* calculate scaler bounds */
        const struct nk_style_item *scaler;
        float scaler_w = NK_MAX(0, scaler_size.x - window_padding.x);
        float scaler_h = NK_MAX(0, scaler_size.y - window_padding.y);
        float scaler_x = (layout->bounds.x + layout->bounds.w) - (window_padding.x + scaler_w);
        float scaler_y;

        if (layout->flags & NK_WINDOW_DYNAMIC)
            scaler_y = footer.y + layout->footer_h - scaler_size.y;
        else scaler_y = layout->bounds.y + layout->bounds.h - scaler_size.y;

        /* draw scaler */
        scaler = &style->window.scaler;
        if (scaler->type == NK_STYLE_ITEM_IMAGE) {
            nk_draw_image(out, nk_rect(scaler_x, scaler_y, scaler_w, scaler_h),
                &scaler->data.image);
        } else {
            nk_fill_triangle(out, scaler_x + scaler_w, scaler_y, scaler_x + scaler_w,
                scaler_y + scaler_h, scaler_x, scaler_y + scaler_h, scaler->data.color);
        }

        /* do window scaling */
        if (!(window->flags & NK_WINDOW_ROM)) {
            struct nk_vec2 delta;
            float prev_x = in->mouse.prev.x;
            float prev_y = in->mouse.prev.y;
            struct nk_vec2 window_size = style->window.min_size;
            int incursor = NK_INBOX(prev_x,prev_y,scaler_x,scaler_y,scaler_w,scaler_h);

            if (nk_input_is_mouse_down(in, NK_BUTTON_LEFT) &&
                (incursor || window->scaling.active == nk_true))
            {
                if(window->scaling.active == nk_false)
                    window->scaling.start_size = nk_rect_size(window->bounds);
                window->scaling.active = nk_true;

                if (!in || !in->mouse.buttons[NK_BUTTON_LEFT].down)
                    delta = nk_vec2(0,0);
                else delta = nk_vec2_sub(in->mouse.pos, in->mouse.buttons[NK_BUTTON_LEFT].clicked_pos);
                window->bounds.w = NK_MAX(window_size.x, window->scaling.start_size.x + delta.x);

                /* dragging in y-direction is only possible if static window */
                if (!(layout->flags & NK_WINDOW_DYNAMIC))
                    window->bounds.h = NK_MAX(window->scaling.start_size.y + delta.y, window_size.y);
            } else window->scaling.active = nk_false;
        }
    }

    /* window border */
    if (layout->flags & NK_WINDOW_BORDER)
    {
        const float padding_y = (layout->flags & NK_WINDOW_MINIMIZED) ?
            2.0f*style->window.border + window->bounds.y + layout->header_h:
            (layout->flags & NK_WINDOW_DYNAMIC)?
            layout->footer_h + footer.y:
            layout->bounds.y + layout->bounds.h;

        /* select correct border color */
        struct nk_color border;
        if (!(layout->flags & NK_WINDOW_SUB))
            border = style->window.border_color;
        else if (layout->flags & NK_WINDOW_COMBO)
            border = style->window.combo_border_color;
        else if (layout->flags & NK_WINDOW_CONTEXTUAL)
            border = style->window.contextual_border_color;
        else if (layout->flags & NK_WINDOW_MENU)
            border = style->window.menu_border_color;
        else if (layout->flags & NK_WINDOW_GROUP)
            border = style->window.group_border_color;
        else if (layout->flags & NK_WINDOW_TOOLTIP)
            border = style->window.tooltip_border_color;
        else border = style->window.border_color;

        /* draw border between header and window body */
        if (window->flags & NK_WINDOW_BORDER_HEADER)
            nk_stroke_line(out, window->bounds.x + layout->border/2.0f,
                window->bounds.y + layout->header_h - layout->border,
                window->bounds.x + window->bounds.w - layout->border,
                window->bounds.y + layout->header_h - layout->border,
                layout->border, border);

        /* draw border top */
        nk_stroke_line(out, window->bounds.x + layout->border/2.0f,
            window->bounds.y + layout->border/2.0f,
            window->bounds.x + window->bounds.w - layout->border,
            window->bounds.y + layout->border/2.0f,
            layout->border, border);

        /* draw bottom border */
        nk_stroke_line(out, window->bounds.x + layout->border/2.0f,
            padding_y - layout->border,
            window->bounds.x + window->bounds.w - layout->border,
            padding_y - layout->border,
            layout->border, border);

        /* draw left border */
        nk_stroke_line(out, window->bounds.x + layout->border/2.0f,
            window->bounds.y + layout->border/2.0f, window->bounds.x + layout->border/2.0f,
            padding_y - layout->border, layout->border, border);

        /* draw right border */
        nk_stroke_line(out, window->bounds.x + window->bounds.w - layout->border,
            window->bounds.y + layout->border/2.0f,
            window->bounds.x + window->bounds.w - layout->border,
            padding_y - layout->border, layout->border, border);
    }

    if (!(window->flags & NK_WINDOW_SUB)) {
        /* window is hidden so clear command buffer  */
        if (layout->flags & NK_WINDOW_HIDDEN)
            nk_command_buffer_reset(&window->buffer);
        /* window is visible and not tab */
        else nk_finish(ctx, window);
    }

    /* NK_WINDOW_REMOVE_ROM flag was set so remove NK_WINDOW_ROM */
    if (layout->flags & NK_WINDOW_REMOVE_ROM) {
        layout->flags &= ~(nk_flags)NK_WINDOW_ROM;
        layout->flags &= ~(nk_flags)NK_WINDOW_REMOVE_ROM;
    }
    window->flags = layout->flags;

    /* property garbage collector */
    if (window->property.active && window->property.old != window->property.seq &&
        window->property.active == window->property.prev) {
        nk_zero(&window->property, sizeof(window->property));
    } else {
        window->property.old = window->property.seq;
        window->property.prev = window->property.active;
        window->property.seq = 0;
    }

    /* edit garbage collector */
    if (window->edit.active && window->edit.old != window->edit.seq &&
        window->edit.active == window->edit.prev) {
        nk_zero(&window->edit, sizeof(window->edit));
    } else {
        window->edit.old = window->edit.seq;
        window->edit.prev = window->edit.active;
        window->edit.seq = 0;
    }

    /* contextual garbage collector */
    if (window->popup.active_con && window->popup.con_old != window->popup.con_count) {
        window->popup.con_count = 0;
        window->popup.con_old = 0;
        window->popup.active_con = 0;
    } else {
        window->popup.con_old = window->popup.con_count;
        window->popup.con_count = 0;
    }
    window->popup.combo_count = 0;
    /* helper to make sure you have a 'nk_tree_push'
     * for every 'nk_tree_pop' */
    NK_ASSERT(!layout->row.tree_depth);
}

NK_API void
nk_menubar_begin(struct nk_context *ctx)
{
    struct nk_panel *layout;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    layout = ctx->current->layout;
    if (layout->flags & NK_WINDOW_HIDDEN || layout->flags & NK_WINDOW_MINIMIZED)
        return;

    layout->menu.x = layout->at_x;
    layout->menu.y = layout->bounds.y + layout->header_h;
    layout->menu.w = layout->width;
    layout->menu.offset = *layout->offset;
    layout->offset->y = 0;
}

NK_API void
nk_menubar_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *layout;
    struct nk_command_buffer *out;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    if (!ctx || layout->flags & NK_WINDOW_HIDDEN || layout->flags & NK_WINDOW_MINIMIZED)
        return;

    out = &win->buffer;
    layout->menu.h = layout->at_y - layout->menu.y;
    layout->clip.y = layout->bounds.y + layout->header_h + layout->menu.h + layout->row.height;
    layout->height -= layout->menu.h;
    *layout->offset = layout->menu.offset;
    layout->clip.h -= layout->menu.h + layout->row.height;
    layout->at_y = layout->menu.y + layout->menu.h;
    nk_push_scissor(out, layout->clip);
}
/* -------------------------------------------------------------
 *
 *                          LAYOUT
 *
 * --------------------------------------------------------------*/
#define NK_LAYOUT_DYNAMIC_FIXED     0
#define NK_LAYOUT_DYNAMIC_ROW       1
#define NK_LAYOUT_DYNAMIC_FREE      2
#define NK_LAYOUT_DYNAMIC           3
#define NK_LAYOUT_STATIC_FIXED      4
#define NK_LAYOUT_STATIC_ROW        5
#define NK_LAYOUT_STATIC_FREE       6
#define NK_LAYOUT_STATIC            7

NK_INTERN void
nk_panel_layout(const struct nk_context *ctx, struct nk_window *win,
    float height, int cols)
{
    struct nk_panel *layout;
    const struct nk_style *style;
    struct nk_command_buffer *out;

    struct nk_vec2 item_spacing;
    struct nk_vec2 panel_padding;
    struct nk_color color;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    /* prefetch some configuration data */
    layout = win->layout;
    style = &ctx->style;
    out = &win->buffer;
    color = style->window.background;
    item_spacing = style->window.spacing;
    panel_padding = style->window.padding;

    /* update the current row and set the current row layout */
    layout->row.index = 0;
    layout->at_y += layout->row.height;
    layout->row.columns = cols;
    layout->row.height = height + item_spacing.y;
    layout->row.item_offset = 0;
    if (layout->flags & NK_WINDOW_DYNAMIC)
        nk_fill_rect(out,  nk_rect(layout->bounds.x, layout->at_y,
            layout->bounds.w, height + panel_padding.y), 0, color);
}

NK_INTERN void
nk_row_layout(struct nk_context *ctx, enum nk_layout_format fmt,
    float height, int cols, int width)
{
    /* update the current row and set the current row layout */
    struct nk_window *win;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    nk_panel_layout(ctx, win, height, cols);
    if (fmt == NK_DYNAMIC)
        win->layout->row.type = NK_LAYOUT_DYNAMIC_FIXED;
    else win->layout->row.type = NK_LAYOUT_STATIC_FIXED;

    win->layout->row.item_width = (float)width;
    win->layout->row.ratio = 0;
    win->layout->row.item_offset = 0;
    win->layout->row.filled = 0;
}

NK_API void
nk_layout_row_dynamic(struct nk_context *ctx, float height, int cols)
{
    nk_row_layout(ctx, NK_DYNAMIC, height, cols, 0);
}

NK_API void
nk_layout_row_static(struct nk_context *ctx, float height, int item_width, int cols)
{
    nk_row_layout(ctx, NK_STATIC, height, cols, item_width);
}

NK_API void
nk_layout_row_begin(struct nk_context *ctx, enum nk_layout_format fmt,
    float row_height, int cols)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;

    nk_panel_layout(ctx, win, row_height, cols);
    if (fmt == NK_DYNAMIC)
        layout->row.type = NK_LAYOUT_DYNAMIC_ROW;
    else layout->row.type = NK_LAYOUT_STATIC_ROW;

    layout->row.ratio = 0;
    layout->row.item_width = 0;
    layout->row.item_offset = 0;
    layout->row.filled = 0;
    layout->row.columns = cols;
}

NK_API void
nk_layout_row_push(struct nk_context *ctx, float ratio_or_width)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;

    if (layout->row.type == NK_LAYOUT_DYNAMIC_ROW) {
        float ratio = ratio_or_width;
        if ((ratio + layout->row.filled) > 1.0f) return;
        if (ratio > 0.0f)
            layout->row.item_width = NK_SATURATE(ratio);
        else layout->row.item_width = 1.0f - layout->row.filled;
    } else layout->row.item_width = ratio_or_width;
}

NK_API void
nk_layout_row_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    layout->row.item_width = 0;
    layout->row.item_offset = 0;
}

NK_API void
nk_layout_row(struct nk_context *ctx, enum nk_layout_format fmt,
    float height, int cols, const float *ratio)
{
    int i;
    int n_undef = 0;
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    nk_panel_layout(ctx, win, height, cols);
    if (fmt == NK_DYNAMIC) {
        /* calculate width of undefined widget ratios */
        float r = 0;
        layout->row.ratio = ratio;
        for (i = 0; i < cols; ++i) {
            if (ratio[i] < 0.0f)
                n_undef++;
            else r += ratio[i];
        }
        r = NK_SATURATE(1.0f - r);
        layout->row.type = NK_LAYOUT_DYNAMIC;
        layout->row.item_width = (r > 0 && n_undef > 0) ? (r / (float)n_undef):0;
    } else {
        layout->row.ratio = ratio;
        layout->row.type = NK_LAYOUT_STATIC;
        layout->row.item_width = 0;
        layout->row.item_offset = 0;
    }
    layout->row.item_offset = 0;
    layout->row.filled = 0;
}

NK_API void
nk_layout_space_begin(struct nk_context *ctx, enum nk_layout_format fmt,
    float height, int widget_count)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    nk_panel_layout(ctx, win, height, widget_count);
    if (fmt == NK_STATIC)
        layout->row.type = NK_LAYOUT_STATIC_FREE;
    else layout->row.type = NK_LAYOUT_DYNAMIC_FREE;

    layout->row.ratio = 0;
    layout->row.item_width = 0;
    layout->row.item_offset = 0;
    layout->row.filled = 0;
}

NK_API void
nk_layout_space_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    layout->row.item_width = 0;
    layout->row.item_height = 0;
    layout->row.item_offset = 0;
    nk_zero(&layout->row.item, sizeof(layout->row.item));
}

NK_API void
nk_layout_space_push(struct nk_context *ctx, struct nk_rect rect)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    layout->row.item = rect;
}

NK_API struct nk_rect
nk_layout_space_bounds(struct nk_context *ctx)
{
    struct nk_rect ret;
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    win = ctx->current;
    layout = win->layout;

    ret.x = layout->clip.x;
    ret.y = layout->clip.y;
    ret.w = layout->clip.w;
    ret.h = layout->row.height;
    return ret;
}

NK_API struct nk_vec2
nk_layout_space_to_screen(struct nk_context *ctx, struct nk_vec2 ret)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    win = ctx->current;
    layout = win->layout;

    ret.x += layout->at_x - layout->offset->x;
    ret.y += layout->at_y - layout->offset->y;
    return ret;
}

NK_API struct nk_vec2
nk_layout_space_to_local(struct nk_context *ctx, struct nk_vec2 ret)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    win = ctx->current;
    layout = win->layout;

    ret.x += -layout->at_x + layout->offset->x;
    ret.y += -layout->at_y + layout->offset->y;
    return ret;
}

NK_API struct nk_rect
nk_layout_space_rect_to_screen(struct nk_context *ctx, struct nk_rect ret)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    win = ctx->current;
    layout = win->layout;

    ret.x += layout->at_x - layout->offset->x;
    ret.y += layout->at_y - layout->offset->y;
    return ret;
}

NK_API struct nk_rect
nk_layout_space_rect_to_local(struct nk_context *ctx, struct nk_rect ret)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    win = ctx->current;
    layout = win->layout;

    ret.x += -layout->at_x + layout->offset->x;
    ret.y += -layout->at_y + layout->offset->y;
    return ret;
}

NK_INTERN void
nk_panel_alloc_row(const struct nk_context *ctx, struct nk_window *win)
{
    struct nk_panel *layout = win->layout;
    struct nk_vec2 spacing = ctx->style.window.spacing;
    const float row_height = layout->row.height - spacing.y;
    nk_panel_layout(ctx, win, row_height, layout->row.columns);
}

NK_INTERN void
nk_layout_widget_space(struct nk_rect *bounds, const struct nk_context *ctx,
    struct nk_window *win, int modify)
{
    struct nk_panel *layout;
    float item_offset = 0;
    float item_width = 0;
    float item_spacing = 0;

    float panel_padding;
    float panel_spacing;
    float panel_space;

    struct nk_vec2 spacing;
    struct nk_vec2 padding;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    NK_ASSERT(bounds);

    /* cache some configuration data */
    spacing = ctx->style.window.spacing;
    padding = ctx->style.window.padding;

    /* calculate the usable panel space */
    panel_padding = 2 * padding.x;
    panel_spacing = (float)(layout->row.columns - 1) * spacing.x;
    panel_space  = layout->width - panel_padding - panel_spacing;

    /* calculate the width of one item inside the current layout space */
    switch (layout->row.type) {
    case NK_LAYOUT_DYNAMIC_FIXED: {
        /* scaling fixed size widgets item width */
        item_width = panel_space / (float)layout->row.columns;
        item_offset = (float)layout->row.index * item_width;
        item_spacing = (float)layout->row.index * spacing.x;
    } break;
    case NK_LAYOUT_DYNAMIC_ROW: {
        /* scaling single ratio widget width */
        item_width = layout->row.item_width * panel_space;
        item_offset = layout->row.item_offset;
        item_spacing = (float)layout->row.index * spacing.x;

        if (modify) {
            layout->row.item_offset += item_width + spacing.x;
            layout->row.filled += layout->row.item_width;
            layout->row.index = 0;
        }
    } break;
    case NK_LAYOUT_DYNAMIC_FREE: {
        /* panel width depended free widget placing */
        bounds->x = layout->at_x + (layout->width * layout->row.item.x);
        bounds->x -= layout->offset->x;
        bounds->y = layout->at_y + (layout->row.height * layout->row.item.y);
        bounds->y -= layout->offset->y;
        bounds->w = layout->width  * layout->row.item.w;
        bounds->h = layout->row.height * layout->row.item.h;
        return;
    };
    case NK_LAYOUT_DYNAMIC: {
        /* scaling arrays of panel width ratios for every widget */
        float ratio;
        NK_ASSERT(layout->row.ratio);
        ratio = (layout->row.ratio[layout->row.index] < 0) ?
            layout->row.item_width : layout->row.ratio[layout->row.index];

        item_spacing = (float)layout->row.index * spacing.x;
        item_width = (ratio * panel_space);
        item_offset = layout->row.item_offset;
        if (modify) {
            layout->row.item_offset += item_width;
            layout->row.filled += ratio;
        }
    } break;
    case NK_LAYOUT_STATIC_FIXED: {
        /* non-scaling fixed widgets item width */
        item_width = layout->row.item_width;
        item_offset = (float)layout->row.index * item_width;
        item_spacing = (float)layout->row.index * spacing.x;
    } break;
    case NK_LAYOUT_STATIC_ROW: {
        /* scaling single ratio widget width */
        item_width = layout->row.item_width;
        item_offset = layout->row.item_offset;
        item_spacing = (float)layout->row.index * spacing.x;
        if (modify) {
            layout->row.item_offset += item_width;
            layout->row.index = 0;
        }
    } break;
    case NK_LAYOUT_STATIC_FREE: {
        /* free widget placing */
        bounds->x = layout->at_x + layout->row.item.x;
        bounds->w = layout->row.item.w;
        if (((bounds->x + bounds->w) > layout->max_x) && modify)
            layout->max_x = (bounds->x + bounds->w);
        bounds->x -= layout->offset->x;
        bounds->y = layout->at_y + layout->row.item.y;
        bounds->y -= layout->offset->y;
        bounds->h = layout->row.item.h;
        return;
    };
    case NK_LAYOUT_STATIC: {
        /* non-scaling array of panel pixel width for every widget */
        item_spacing = (float)layout->row.index * spacing.x;
        item_width = layout->row.ratio[layout->row.index];
        item_offset = layout->row.item_offset;
        if (modify) layout->row.item_offset += item_width;
    } break;
    default: NK_ASSERT(0); break;
    };

    /* set the bounds of the newly allocated widget */
    bounds->w = item_width;
    bounds->h = layout->row.height - spacing.y;
    bounds->y = layout->at_y - layout->offset->y;
    bounds->x = layout->at_x + item_offset + item_spacing + padding.x;
    if (((bounds->x + bounds->w) > layout->max_x) && modify)
        layout->max_x = bounds->x + bounds->w;
    bounds->x -= layout->offset->x;
}

NK_INTERN void
nk_panel_alloc_space(struct nk_rect *bounds, const struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    /* check if the end of the row has been hit and begin new row if so */
    win = ctx->current;
    layout = win->layout;
    if (layout->row.index >= layout->row.columns)
        nk_panel_alloc_row(ctx, win);

    /* calculate widget position and size */
    nk_layout_widget_space(bounds, ctx, win, nk_true);
    layout->row.index++;
}

NK_INTERN void
nk_layout_peek(struct nk_rect *bounds, struct nk_context *ctx)
{
    float y;
    int index;
    struct nk_window *win;
    struct nk_panel *layout;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    y = layout->at_y;
    index = layout->row.index;
    if (layout->row.index >= layout->row.columns) {
        layout->at_y += layout->row.height;
        layout->row.index = 0;
    }
    nk_layout_widget_space(bounds, ctx, win, nk_false);
    layout->at_y = y;
    layout->row.index = index;
}

NK_API int
nk_tree_push_hashed(struct nk_context *ctx, enum nk_tree_type type,
    const char *title, enum nk_collapse_states initial_state,
    const char *hash, int len, int line)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_style *style;
    struct nk_command_buffer *out;
    const struct nk_input *in;

    struct nk_vec2 item_spacing;
    struct nk_vec2 panel_padding;
    struct nk_rect header = {0,0,0,0};
    struct nk_rect sym = {0,0,0,0};
    struct nk_text text;

    nk_flags ws = 0;
    int title_len = 0;
    nk_hash title_hash = 0;
    nk_uint *state = 0;
    enum nk_widget_layout_states widget_state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    /* cache some data */
    win = ctx->current;
    layout = win->layout;
    out = &win->buffer;
    style = &ctx->style;

    item_spacing = style->window.spacing;
    panel_padding = style->window.padding;

    /* calculate header bounds and draw background */
    nk_layout_row_dynamic(ctx, style->font.height + 2 * style->tab.padding.y, 1);
    widget_state = nk_widget(&header, ctx);
    if (type == NK_TREE_TAB) {
        const struct nk_style_item *background = &style->tab.background;
        if (background->type == NK_STYLE_ITEM_IMAGE) {
            nk_draw_image(out, header, &background->data.image);
            text.background = nk_rgba(0,0,0,0);
        } else {
            text.background = background->data.color;
            nk_fill_rect(out, header, 0, style->tab.border_color);
            nk_fill_rect(out, nk_shrink_rect(header, style->tab.border),
                style->tab.rounding, background->data.color);
        }
    } else text.background = style->window.background;

    /* find or create tab persistent state (open/closed) */
    title_len = (int)nk_strlen(title);
    title_hash = nk_murmur_hash(title, (int)title_len, (nk_hash)type);
    if (hash) title_hash += nk_murmur_hash(hash, len, (nk_hash)line);
    state = nk_find_value(win, title_hash);
    if (!state) {
        state = nk_add_value(ctx, win, title_hash, 0);
        *state = initial_state;
    }

    /* update node state */
    in = (!(layout->flags & NK_WINDOW_ROM)) ? &ctx->input: 0;
    in = (in && widget_state == NK_WIDGET_VALID) ? &ctx->input : 0;
    if (nk_button_behavior(&ws, header, in, NK_BUTTON_DEFAULT))
        *state = (*state == NK_MAXIMIZED) ? NK_MINIMIZED : NK_MAXIMIZED;

    {
        /* calculate the triangle bounds */
        sym.w = sym.h = style->font.height;
        sym.y = header.y + style->tab.padding.y;
        sym.x = header.x + panel_padding.x + style->tab.padding.x;

        /* calculate the triangle points and draw triangle */
        nk_do_button_symbol(&ws, &win->buffer, sym,
            (*state == NK_MAXIMIZED)? style->tab.sym_minimize: style->tab.sym_maximize,
            NK_BUTTON_DEFAULT, (type == NK_TREE_TAB)?
            &style->tab.tab_button: &style->tab.node_button,
            in, &style->font);

        /* calculate the space the icon occupied */
        sym.w = style->font.height + 2 * style->tab.spacing.x;
    }
    {
        /* draw node label */
        struct nk_rect label;
        header.w = NK_MAX(header.w, sym.w + item_spacing.y + panel_padding.x);
        label.x = sym.x + sym.w + item_spacing.x;
        label.y = sym.y;
        label.w = header.w - (sym.w + item_spacing.y + panel_padding.x);
        label.h = style->font.height;

        text.text = style->tab.text;
        text.padding = nk_vec2(0,0);
        nk_widget_text(out, label, title, nk_strlen(title), &text,
            NK_TEXT_LEFT, &style->font);
    }

    /* increase x-axis cursor widget position pointer */
    if (*state == NK_MAXIMIZED) {
        layout->at_x = header.x + layout->offset->x;
        layout->width = NK_MAX(layout->width, 2 * panel_padding.x);
        layout->width -= 2 * panel_padding.x;
        layout->row.tree_depth++;
        return nk_true;
    } else return nk_false;
}

NK_API void
nk_tree_pop(struct nk_context *ctx)
{
    struct nk_vec2 panel_padding;
    struct nk_window *win = 0;
    struct nk_panel *layout = 0;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    win = ctx->current;
    layout = win->layout;
    panel_padding = ctx->style.window.padding;
    layout->at_x -= panel_padding.x;
    layout->width += 2 * panel_padding.x;
    NK_ASSERT(layout->row.tree_depth);
    layout->row.tree_depth--;
}
/*----------------------------------------------------------------
 *
 *                          WIDGETS
 *
 * --------------------------------------------------------------*/
NK_API struct nk_rect
nk_widget_bounds(struct nk_context *ctx)
{
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return nk_rect(0,0,0,0);
    nk_layout_peek(&bounds, ctx);
    return bounds;
}

NK_API struct nk_vec2
nk_widget_position(struct nk_context *ctx)
{
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return nk_vec2(0,0);

    nk_layout_peek(&bounds, ctx);
    return nk_vec2(bounds.x, bounds.y);
}

NK_API struct nk_vec2
nk_widget_size(struct nk_context *ctx)
{
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return nk_vec2(0,0);

    nk_layout_peek(&bounds, ctx);
    return nk_vec2(bounds.w, bounds.h);
}

NK_API int
nk_widget_is_hovered(struct nk_context *ctx)
{
    int ret;
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return 0;

    nk_layout_peek(&bounds, ctx);
    ret = (ctx->active == ctx->current);
    ret = ret && nk_input_is_mouse_hovering_rect(&ctx->input, bounds);
    return ret;
}

NK_API int
nk_widget_is_mouse_clicked(struct nk_context *ctx, enum nk_buttons btn)
{
    int ret;
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return 0;

    nk_layout_peek(&bounds, ctx);
    ret = (ctx->active == ctx->current);
    ret = ret && nk_input_mouse_clicked(&ctx->input, btn, bounds);
    return ret;
}

NK_API int
nk_widget_has_mouse_click_down(struct nk_context *ctx, enum nk_buttons btn, int down)
{
    int ret;
    struct nk_rect bounds;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return 0;

    nk_layout_peek(&bounds, ctx);
    ret = (ctx->active == ctx->current);
    ret = ret && nk_input_has_mouse_click_down_in_rect(&ctx->input, btn, bounds, down);
    return ret;
}

NK_API enum nk_widget_layout_states
nk_widget(struct nk_rect *bounds, const struct nk_context *ctx)
{
    struct nk_rect *c = 0;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return NK_WIDGET_INVALID;

    /* allocate space  and check if the widget needs to be updated and drawn */
    nk_panel_alloc_space(bounds, ctx);
    c = &ctx->current->layout->clip;
    if (!NK_INTERSECT(c->x, c->y, c->w, c->h, bounds->x, bounds->y, bounds->w, bounds->h))
        return NK_WIDGET_INVALID;
    if (!NK_CONTAINS(bounds->x, bounds->y, bounds->w, bounds->h, c->x, c->y, c->w, c->h))
        return NK_WIDGET_ROM;
    return NK_WIDGET_VALID;
}

NK_API enum nk_widget_layout_states
nk_widget_fitting(struct nk_rect *bounds, struct nk_context *ctx,
    struct nk_vec2 item_padding)
{
    /* update the bounds to stand without padding  */
    struct nk_window *win;
    struct nk_style *style;
    struct nk_panel *layout;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return NK_WIDGET_INVALID;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;
    state = nk_widget(bounds, ctx);
    if (layout->row.index == 1) {
        bounds->w += style->window.padding.x;
        bounds->x -= style->window.padding.x;
    } else bounds->x -= item_padding.x;

    if (layout->row.index == layout->row.columns)
        bounds->w += style->window.padding.x;
    else bounds->w += item_padding.x;
    return state;
}

/*----------------------------------------------------------------
 *
 *                          MISC
 *
 * --------------------------------------------------------------*/
NK_API void
nk_spacing(struct nk_context *ctx, int cols)
{
    struct nk_window *win;
    struct nk_panel *layout;
    struct nk_rect nil;
    int i, index, rows;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    /* spacing over row boundaries */
    win = ctx->current;
    layout = win->layout;
    index = (layout->row.index + cols) % layout->row.columns;
    rows = (layout->row.index + cols) / layout->row.columns;
    if (rows) {
        for (i = 0; i < rows; ++i)
            nk_panel_alloc_row(ctx, win);
        cols = index;
    }

    /* non table layout need to allocate space */
    if (layout->row.type != NK_LAYOUT_DYNAMIC_FIXED &&
        layout->row.type != NK_LAYOUT_STATIC_FIXED) {
        for (i = 0; i < cols; ++i)
            nk_panel_alloc_space(&nil, ctx);
    }
    layout->row.index = index;
}

/*----------------------------------------------------------------
 *
 *                          TEXT
 *
 * --------------------------------------------------------------*/
NK_API void
nk_text_colored(struct nk_context *ctx, const char *str, int len,
    nk_flags alignment, struct nk_color color)
{
    struct nk_window *win;
    const struct nk_style *style;

    struct nk_vec2 item_padding;
    struct nk_rect bounds;
    struct nk_text text;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) return;

    win = ctx->current;
    style = &ctx->style;
    nk_panel_alloc_space(&bounds, ctx);
    item_padding = style->text.padding;

    text.padding.x = item_padding.x;
    text.padding.y = item_padding.y;
    text.background = style->window.background;
    text.text = color;
    nk_widget_text(&win->buffer, bounds, str, len, &text, alignment, &style->font);
}

NK_API void
nk_text_wrap_colored(struct nk_context *ctx, const char *str,
    int len, struct nk_color color)
{
    struct nk_window *win;
    const struct nk_style *style;

    struct nk_vec2 item_padding;
    struct nk_rect bounds;
    struct nk_text text;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) return;

    win = ctx->current;
    style = &ctx->style;
    nk_panel_alloc_space(&bounds, ctx);
    item_padding = style->text.padding;

    text.padding.x = item_padding.x;
    text.padding.y = item_padding.y;
    text.background = style->window.background;
    text.text = color;
    nk_widget_text_wrap(&win->buffer, bounds, str, len, &text, &style->font);
}

#ifdef NK_INCLUDE_STANDARD_IO
NK_API void
nk_labelf_colored(struct nk_context *ctx, nk_flags flags,
    struct nk_color color, const char *fmt, ...)
{
    char buf[256];
    va_list args;
    va_start(args, fmt);
    nk_strfmtv(buf, NK_LEN(buf), fmt, args);
    nk_label_colored(ctx, buf, flags, color);
    va_end(args);
}

NK_API void
nk_labelf_colored_wrap(struct nk_context *ctx, struct nk_color color,
    const char *fmt, ...)
{
    char buf[256];
    va_list args;
    va_start(args, fmt);
    nk_strfmtv(buf, NK_LEN(buf), fmt, args);
    nk_label_colored_wrap(ctx, buf, color);
    va_end(args);
}

NK_API void
nk_labelf(struct nk_context *ctx, nk_flags flags, const char *fmt, ...)
{
    char buf[256];
    va_list args;
    va_start(args, fmt);
    nk_strfmtv(buf, NK_LEN(buf), fmt, args);
    nk_label(ctx, buf, flags);
    va_end(args);
}

NK_API void
nk_labelf_wrap(struct nk_context *ctx, const char *fmt,...)
{
    char buf[256];
    va_list args;
    va_start(args, fmt);
    nk_strfmtv(buf, NK_LEN(buf), fmt, args);
    nk_label_wrap(ctx, buf);
    va_end(args);
}

NK_API void
nk_value_bool(struct nk_context *ctx, const char *prefix, int value)
{nk_labelf(ctx, NK_TEXT_LEFT, "%s: %s", prefix, ((value) ? "true": "false"));}

NK_API void
nk_value_int(struct nk_context *ctx, const char *prefix, int value)
{nk_labelf(ctx, NK_TEXT_LEFT, "%s: %d", prefix, value);}

NK_API void
nk_value_uint(struct nk_context *ctx, const char *prefix, unsigned int value)
{nk_labelf(ctx, NK_TEXT_LEFT, "%s: %u", prefix, value);}

NK_API void
nk_value_float(struct nk_context *ctx, const char *prefix, float value)
{nk_labelf(ctx, NK_TEXT_LEFT, "%s: %.3f", prefix, value);}

NK_API void
nk_value_color_byte(struct nk_context *ctx, const char *p, struct nk_color c)
{nk_labelf(ctx, NK_TEXT_LEFT, "%s: (%c, %c, %c, %c)", p, c.r, c.g, c.b, c.a);}

NK_API void
nk_value_color_float(struct nk_context *ctx, const char *p, struct nk_color color)
{
    float c[4]; nk_color_fv(c, color);
    nk_labelf(ctx, NK_TEXT_LEFT, "%s: (%.2f, %.2f, %.2f, %.2f)",
        p, c[0], c[1], c[2], c[3]);
}

NK_API void
nk_value_color_hex(struct nk_context *ctx, const char *prefix, struct nk_color color)
{
    char hex[16];
    nk_color_hex_rgba(hex, color);
    nk_labelf(ctx, NK_TEXT_LEFT, "%s: %s", prefix, hex);
}
#endif

NK_API void
nk_text(struct nk_context *ctx, const char *str, int len, nk_flags alignment)
{
    NK_ASSERT(ctx);
    if (!ctx) return;
    nk_text_colored(ctx, str, len, alignment, ctx->style.text.color);
}

NK_API void
nk_text_wrap(struct nk_context *ctx, const char *str, int len)
{
    NK_ASSERT(ctx);
    if (!ctx) return;
    nk_text_wrap_colored(ctx, str, len, ctx->style.text.color);
}

NK_API void
nk_label(struct nk_context *ctx, const char *str, nk_flags alignment)
{nk_text(ctx, str, nk_strlen(str), alignment);}

NK_API void
nk_label_colored(struct nk_context *ctx, const char *str, nk_flags align,
    struct nk_color color)
{nk_text_colored(ctx, str, nk_strlen(str), align, color);}

NK_API void
nk_label_wrap(struct nk_context *ctx, const char *str)
{nk_text_wrap(ctx, str, nk_strlen(str));}

NK_API void
nk_label_colored_wrap(struct nk_context *ctx, const char *str, struct nk_color color)
{nk_text_wrap_colored(ctx, str, nk_strlen(str), color);}

NK_API void
nk_image(struct nk_context *ctx, struct nk_image img)
{
    struct nk_window *win;
    struct nk_rect bounds;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) return;

    win = ctx->current;
    if (!nk_widget(&bounds, ctx)) return;
    nk_draw_image(&win->buffer, bounds, &img);
}

/*----------------------------------------------------------------
 *
 *                          BUTTON
 *
 * --------------------------------------------------------------*/
NK_API int
nk_button_text(struct nk_context *ctx, const char *title, int len,
    enum nk_button_behavior behavior)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) return 0;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;
    state = nk_widget(&bounds, ctx);

    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_button_text(&ctx->last_widget_state, &win->buffer, bounds,
                    title, len, style->button.text_alignment, behavior,
                    &style->button, in, &style->font);
}

NK_API int nk_button_label(struct nk_context *ctx, const char *title,
    enum nk_button_behavior behavior)
{return nk_button_text(ctx, title, nk_strlen(title), behavior);}

NK_API int
nk_button_color(struct nk_context *ctx, struct nk_color color,
    enum nk_button_behavior behavior)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    struct nk_style_button button;

    int ret = 0;
    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;

    button = ctx->style.button;
    button.normal = nk_style_item_color(color);
    button.hover = nk_style_item_color(color);
    button.active = nk_style_item_color(color);
    button.padding = nk_vec2(0,0);
    ret = nk_do_button(&ctx->last_widget_state, &win->buffer, bounds,
                &button, in, behavior, &bounds);
    nk_draw_button(&win->buffer, &bounds, ctx->last_widget_state, &button);
    return ret;
}

NK_API int
nk_button_symbol(struct nk_context *ctx, enum nk_symbol_type symbol,
    enum nk_button_behavior behavior)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_button_symbol(&ctx->last_widget_state, &win->buffer, bounds,
            symbol, behavior, &style->button, in, &style->font);
}

NK_API int
nk_button_image(struct nk_context *ctx, struct nk_image img,
    enum nk_button_behavior behavior)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_button_image(&ctx->last_widget_state, &win->buffer, bounds,
                img, behavior, &style->button, in);
}

NK_API int
nk_button_symbol_text(struct nk_context *ctx, enum nk_symbol_type symbol,
    const char* text, int len, nk_flags align, enum nk_button_behavior behavior)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_button_text_symbol(&ctx->last_widget_state, &win->buffer, bounds,
                symbol, text, len, align, behavior, &style->button, &style->font, in);
}

NK_API int nk_button_symbol_label(struct nk_context *ctx, enum nk_symbol_type symbol,
    const char *label, nk_flags align, enum nk_button_behavior behavior)
{return nk_button_symbol_text(ctx, symbol, label, nk_strlen(label), align, behavior);}

NK_API int
nk_button_image_text(struct nk_context *ctx, struct nk_image img,
    const char *text, int len, nk_flags align, enum nk_button_behavior behavior)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;

    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_button_text_image(&ctx->last_widget_state, &win->buffer,
            bounds, img, text, len, align, behavior, &style->button, &style->font, in);
}

NK_API int nk_button_image_label(struct nk_context *ctx, struct nk_image img,
    const char *label, nk_flags align, enum nk_button_behavior behavior)
{return nk_button_image_text(ctx, img, label, nk_strlen(label), align, behavior);}

/*----------------------------------------------------------------
 *
 *                          SELECTABLE
 *
 * --------------------------------------------------------------*/
NK_API int
nk_selectable_text(struct nk_context *ctx, const char *str, int len,
    nk_flags align, int *value)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    enum nk_widget_layout_states state;
    struct nk_rect bounds;

    NK_ASSERT(ctx);
    NK_ASSERT(value);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !value)
        return 0;

    win = ctx->current;
    layout = win->layout;
    style = &ctx->style;
    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_selectable(&ctx->last_widget_state, &win->buffer, bounds,
                str, len, align, value, &style->selectable, in, &style->font);
}

NK_API int nk_select_text(struct nk_context *ctx, const char *str, int len,
    nk_flags align, int value)
{nk_selectable_text(ctx, str, len, align, &value);return value;}

NK_API int nk_selectable_label(struct nk_context *ctx, const char *str, nk_flags align, int *value)
{return nk_selectable_text(ctx, str, nk_strlen(str), align, value);}

NK_API int nk_select_label(struct nk_context *ctx, const char *str, nk_flags align, int value)
{nk_selectable_text(ctx, str, nk_strlen(str), align, &value);return value;}

/*----------------------------------------------------------------
 *
 *                          CHECKBOX
 *
 * --------------------------------------------------------------*/
NK_API int
nk_check_text(struct nk_context *ctx, const char *text, int len, int active)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return active;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;
    state = nk_widget(&bounds, ctx);
    if (!state) return active;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    nk_do_toggle(&ctx->last_widget_state, &win->buffer, bounds, &active,
        text, len, NK_TOGGLE_CHECK, &style->checkbox, in, &style->font);
    return active;
}

NK_API unsigned int
nk_check_flags_text(struct nk_context *ctx, const char *text, int len,
    unsigned int flags, unsigned int value)
{
    int old_active;
    NK_ASSERT(ctx);
    NK_ASSERT(text);
    if (!ctx || !text) return flags;
    old_active = (int)((flags & value) & value);
    if (nk_check_text(ctx, text, len, old_active))
        flags |= value;
    else flags &= ~value;
    return flags;
}

NK_API int
nk_checkbox_text(struct nk_context *ctx, const char *text, int len, int *active)
{
    int old_val;
    NK_ASSERT(ctx);
    NK_ASSERT(text);
    NK_ASSERT(active);
    if (!ctx || !text || !active) return 0;
    old_val = *active;
    *active = nk_check_text(ctx, text, len, *active);
    return old_val != *active;
}

NK_API int
nk_checkbox_flags_text(struct nk_context *ctx, const char *text, int len,
    unsigned int *flags, unsigned int value)
{
    int active;
    NK_ASSERT(ctx);
    NK_ASSERT(text);
    NK_ASSERT(flags);
    if (!ctx || !text || !flags) return 0;
    active = (int)((*flags & value) & value);
    if (nk_checkbox_text(ctx, text, len, &active)) {
        if (active) *flags |= value;
        else *flags &= ~value;
        return 1;
    }
    return 0;
}

NK_API int nk_check_label(struct nk_context *ctx, const char *label, int active)
{return nk_check_text(ctx, label, nk_strlen(label), active);}

NK_API unsigned int nk_check_flags_label(struct nk_context *ctx, const char *label,
    unsigned int flags, unsigned int value)
{return nk_check_flags_text(ctx, label, nk_strlen(label), flags, value);}

NK_API int nk_checkbox_label(struct nk_context *ctx, const char *label, int *active)
{return nk_checkbox_text(ctx, label, nk_strlen(label), active);}

NK_API int nk_checkbox_flags_label(struct nk_context *ctx, const char *label,
    unsigned int *flags, unsigned int value)
{return nk_checkbox_flags_text(ctx, label, nk_strlen(label), flags, value);}

/*----------------------------------------------------------------
 *
 *                          OPTION
 *
 * --------------------------------------------------------------*/
NK_API int
nk_option_text(struct nk_context *ctx, const char *text, int len, int is_active)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return is_active;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;
    state = nk_widget(&bounds, ctx);
    if (!state) return state;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    nk_do_toggle(&ctx->last_widget_state, &win->buffer, bounds, &is_active,
        text, len, NK_TOGGLE_OPTION, &style->option, in, &style->font);
    return is_active;
}

NK_API int
nk_radio_text(struct nk_context *ctx, const char *text, int len, int *active)
{
    int old_value;
    NK_ASSERT(ctx);
    NK_ASSERT(text);
    NK_ASSERT(active);
    if (!ctx || !text || !active) return 0;
    old_value = *active;
    *active = nk_option_text(ctx, text, len, old_value);
    return old_value != *active;
}

NK_API int
nk_option_label(struct nk_context *ctx, const char *label, int active)
{return nk_option_text(ctx, label, nk_strlen(label), active);}

NK_API int
nk_radio_label(struct nk_context *ctx, const char *label, int *active)
{return nk_radio_text(ctx, label, nk_strlen(label), active);}

/*----------------------------------------------------------------
 *
 *                          SLIDER
 *
 * --------------------------------------------------------------*/
NK_API int
nk_slider_float(struct nk_context *ctx, float min_value, float *value, float max_value,
    float value_step)
{
    struct nk_window *win;
    struct nk_panel *layout;
    struct nk_input *in;
    const struct nk_style *style;

    int ret = 0;
    float old_value;
    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    NK_ASSERT(value);
    if (!ctx || !ctx->current || !ctx->current->layout || !value)
        return ret;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;
    state = nk_widget(&bounds, ctx);
    if (!state) return ret;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;

    old_value = *value;
    *value = nk_do_slider(&ctx->last_widget_state, &win->buffer, bounds, min_value,
                old_value, max_value, value_step, &style->slider, in, &style->font);
    return (old_value > *value || old_value < *value);
}

NK_API float
nk_slide_float(struct nk_context *ctx, float min, float val, float max, float step)
{
    nk_slider_float(ctx, min, &val, max, step); return val;
}

NK_API int
nk_slide_int(struct nk_context *ctx, int min, int val, int max, int step)
{
    float value = (float)val;
    nk_slider_float(ctx, (float)min, &value, (float)max, (float)step);
    return (int)value;
}

NK_API int
nk_slider_int(struct nk_context *ctx, int min, int *val, int max, int step)
{
    int ret;
    float value = (float)*val;
    ret = nk_slider_float(ctx, (float)min, &value, (float)max, (float)step);
    *val =  (int)value;
    return ret;
}

/*----------------------------------------------------------------
 *
 *                          PROGRESSBAR
 *
 * --------------------------------------------------------------*/
NK_API int
nk_progress(struct nk_context *ctx, nk_size *cur, nk_size max, int is_modifyable)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_style *style;
    const struct nk_input *in;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;
    nk_size old_value;

    NK_ASSERT(ctx);
    NK_ASSERT(cur);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !cur)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    layout = win->layout;
    state = nk_widget(&bounds, ctx);
    if (!state) return 0;

    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    old_value = *cur;
    *cur = nk_do_progress(&ctx->last_widget_state, &win->buffer, bounds,
            *cur, max, is_modifyable, &style->progress, in);
    return (*cur != old_value);
}

NK_API nk_size nk_prog(struct nk_context *ctx, nk_size cur, nk_size max, int modifyable)
{nk_progress(ctx, &cur, max, modifyable);return cur;}

/*----------------------------------------------------------------
 *
 *                          EDIT
 *
 * --------------------------------------------------------------*/
NK_API nk_flags
nk_edit_string(struct nk_context *ctx, nk_flags flags,
    char *memory, int *len, int max, nk_filter filter)
{
    nk_hash hash;
    nk_flags state;
    struct nk_text_edit *edit;
    struct nk_window *win;

    NK_ASSERT(ctx);
    NK_ASSERT(memory);
    NK_ASSERT(len);
    if (!ctx || !memory || !len)
        return 0;

    filter = (!filter) ? nk_filter_default: filter;
    win = ctx->current;
    hash = win->edit.seq;
    edit = &ctx->text_edit;
    nk_textedit_clear_state(&ctx->text_edit, (flags & NK_EDIT_MULTILINE)?
        NK_TEXT_EDIT_MULTI_LINE: NK_TEXT_EDIT_SINGLE_LINE, filter);

    if (win->edit.active && hash == win->edit.name) {
        if (flags & NK_EDIT_NO_CURSOR)
            edit->cursor = nk_utf_len(memory, *len);
        else edit->cursor = win->edit.cursor;
        if (!(flags & NK_EDIT_SELECTABLE)) {
            edit->select_start = win->edit.cursor;
            edit->select_end = win->edit.cursor;
        } else {
            edit->select_start = win->edit.sel_start;
            edit->select_end = win->edit.sel_end;
        }
        edit->mode = win->edit.mode;
        edit->scrollbar.x = (float)win->edit.scrollbar.x;
        edit->scrollbar.y = (float)win->edit.scrollbar.y;
        edit->active = nk_true;
    } else edit->active = nk_false;

    max = NK_MAX(1, max);
    *len = NK_MIN(*len, max-1);
    nk_str_init_fixed(&edit->string, memory, (nk_size)max);
    edit->string.buffer.allocated = (nk_size)*len;
    edit->string.len = nk_utf_len(memory, *len);
    state = nk_edit_buffer(ctx, flags, edit, filter);
    *len = (int)edit->string.buffer.allocated;

    if (edit->active) {
        win->edit.cursor = edit->cursor;
        win->edit.sel_start = edit->select_start;
        win->edit.sel_end = edit->select_end;
        win->edit.mode = edit->mode;
        win->edit.scrollbar.x = (unsigned short)edit->scrollbar.x;
        win->edit.scrollbar.y = (unsigned short)edit->scrollbar.y;
    }
    return state;
}

NK_API nk_flags
nk_edit_buffer(struct nk_context *ctx, nk_flags flags,
    struct nk_text_edit *edit, nk_filter filter)
{
    struct nk_window *win;
    struct nk_style *style;
    struct nk_input *in;

    enum nk_widget_layout_states state;
    struct nk_rect bounds;

    nk_flags ret_flags = 0;
    unsigned char prev_state;
    nk_hash hash;

    /* make sure correct values */
    NK_ASSERT(ctx);
    NK_ASSERT(edit);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    state = nk_widget(&bounds, ctx);
    if (!state) return state;
    in = (win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;

    /* check if edit is currently hot item */
    hash = win->edit.seq++;
    if (win->edit.active && hash == win->edit.name) {
        if (flags & NK_EDIT_NO_CURSOR)
            edit->cursor = edit->string.len;
        if (!(flags & NK_EDIT_SELECTABLE)) {
            edit->select_start = edit->cursor;
            edit->select_end = edit->cursor;
        }
        if (flags & NK_EDIT_CLIPBOARD)
            edit->clip = ctx->clip;
    }

    filter = (!filter) ? nk_filter_default: filter;
    prev_state = (unsigned char)edit->active;
    in = (flags & NK_EDIT_READ_ONLY) ? 0: in;
    ret_flags = nk_do_edit(&ctx->last_widget_state, &win->buffer, bounds, flags,
                    filter, edit, &style->edit, in, &style->font);

    if (edit->active && prev_state != edit->active) {
        /* current edit is now hot */
        win->edit.active = nk_true;
        win->edit.name = hash;
    } else if (prev_state && !edit->active) {
        /* current edit is now cold */
        win->edit.active = nk_false;
    }
    return ret_flags;
}

/*----------------------------------------------------------------
 *
 *                          PROPERTY
 *
 * --------------------------------------------------------------*/
NK_INTERN float
nk_property(struct nk_context *ctx, const char *name, float min, float val,
    float max, float step, float inc_per_pixel, const enum nk_property_filter filter)
{
    struct nk_window *win;
    struct nk_panel *layout;
    struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states s;

    int *state = 0;
    nk_hash hash = 0;
    char *buffer = 0;
    int *len = 0;
    int *cursor = 0;
    int old_state;

    char dummy_buffer[NK_MAX_NUMBER_BUFFER];
    int dummy_state = NK_PROPERTY_DEFAULT;
    int dummy_length = 0;
    int dummy_cursor = 0;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return val;

    win = ctx->current;
    layout = win->layout;
    style = &ctx->style;
    s = nk_widget(&bounds, ctx);
    if (!s) return val;
    in = (s == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;

    /* calculate hash from name */
    if (name[0] == '#') {
        hash = nk_murmur_hash(name, (int)nk_strlen(name), win->property.seq++);
        name++; /* special number hash */
    } else hash = nk_murmur_hash(name, (int)nk_strlen(name), 42);

    /* check if property is currently hot item */
    if (win->property.active && hash == win->property.name) {
        buffer = win->property.buffer;
        len = &win->property.length;
        cursor = &win->property.cursor;
        state = &win->property.state;
    } else {
        buffer = dummy_buffer;
        len = &dummy_length;
        cursor = &dummy_cursor;
        state = &dummy_state;
    }

    /* execute property widget */
    old_state = *state;
    val = nk_do_property(&ctx->last_widget_state, &win->buffer, bounds, name,
        min, val, max, step, inc_per_pixel, buffer, len, state, cursor,
        &style->property, filter, in, &style->font, &ctx->text_edit);

    if (in && *state != NK_PROPERTY_DEFAULT && !win->property.active) {
        /* current property is now hot */
        win->property.active = 1;
        NK_MEMCPY(win->property.buffer, buffer, (nk_size)*len);
        win->property.length = *len;
        win->property.cursor = *cursor;
        win->property.state = *state;
        win->property.name = hash;
        if (*state == NK_PROPERTY_DRAG) {
            ctx->input.mouse.grab = nk_true;
            ctx->input.mouse.grabbed = nk_true;
        }
    }

    /* check if previously active property is now inactive */
    if (*state == NK_PROPERTY_DEFAULT && old_state != NK_PROPERTY_DEFAULT) {
        if (old_state == NK_PROPERTY_DRAG) {
            ctx->input.mouse.grab = nk_false;
            ctx->input.mouse.grabbed = nk_false;
            ctx->input.mouse.ungrab = nk_true;
        }
        win->property.active = 0;
    }
    return val;
}

NK_API void
nk_property_float(struct nk_context *ctx, const char *name,
    float min, float *val, float max, float step, float inc_per_pixel)
{
    NK_ASSERT(ctx);
    NK_ASSERT(name);
    NK_ASSERT(val);
    if (!ctx || !ctx->current || !name || !val) return;
    *val = nk_property(ctx, name, min, *val, max, step, inc_per_pixel, NK_FILTER_FLOAT);
}

NK_API void
nk_property_int(struct nk_context *ctx, const char *name,
    int min, int *val, int max, int step, int inc_per_pixel)
{
    float value;
    NK_ASSERT(ctx);
    NK_ASSERT(name);
    NK_ASSERT(val);
    if (!ctx || !ctx->current || !name || !val) return;
    value = nk_property(ctx, name, (float)min, (float)*val, (float)max, (float)step,
        (float)inc_per_pixel, NK_FILTER_FLOAT);
    *val = (int)value;
}

NK_API float
nk_propertyf(struct nk_context *ctx, const char *name, float min,
    float val, float max, float step, float inc_per_pixel)
{
    NK_ASSERT(ctx);
    NK_ASSERT(name);
    if (!ctx || !ctx->current || !name) return val;
    return nk_property(ctx, name, min, val, max, step, inc_per_pixel, NK_FILTER_FLOAT);
}

NK_API int
nk_propertyi(struct nk_context *ctx, const char *name, int min, int val,
    int max, int step, int inc_per_pixel)
{
    float value;
    NK_ASSERT(ctx);
    NK_ASSERT(name);
    if (!ctx || !ctx->current || !name) return val;
    value = nk_property(ctx, name, (float)min, (float)val, (float)max, (float)step,
        (float)inc_per_pixel, NK_FILTER_FLOAT);
    return (int)value;
}

/*----------------------------------------------------------------
 *
 *                          COLOR PICKER
 *
 * --------------------------------------------------------------*/
NK_API int
nk_color_pick(struct nk_context * ctx, struct nk_color *color,
    enum nk_color_format fmt)
{
    struct nk_window *win;
    struct nk_panel *layout;
    const struct nk_style *config;
    const struct nk_input *in;

    enum nk_widget_layout_states state;
    struct nk_rect bounds;

    NK_ASSERT(ctx);
    NK_ASSERT(color);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !color)
        return 0;

    win = ctx->current;
    config = &ctx->style;
    layout = win->layout;
    state = nk_widget(&bounds, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    return nk_do_color_picker(&ctx->last_widget_state, &win->buffer, color, fmt, bounds,
                nk_vec2(0,0), in, &config->font);
}

NK_API struct nk_color
nk_color_picker(struct nk_context *ctx, struct nk_color color,
    enum nk_color_format fmt)
{
    nk_color_pick(ctx, &color, fmt);
    return color;
}

/* -------------------------------------------------------------
 *
 *                          CHART
 *
 * --------------------------------------------------------------*/
NK_API int
nk_chart_begin(struct nk_context *ctx, const enum nk_chart_type type,
    int count, float min_value, float max_value)
{
    struct nk_window *win;
    struct nk_chart *chart;
    const struct nk_style *config;
    const struct nk_style_chart *style;

    const struct nk_style_item *background;
    struct nk_rect bounds = {0, 0, 0, 0};

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout) return 0;
    if (!nk_widget(&bounds, ctx)) {
        chart = &ctx->current->layout->chart;
        nk_zero(chart, sizeof(*chart));
        return 0;
    }

    win = ctx->current;
    config = &ctx->style;
    chart = &win->layout->chart;
    style = &config->chart;

    /* setup basic generic chart  */
    nk_zero(chart, sizeof(*chart));
    chart->x = bounds.x + style->padding.x;
    chart->y = bounds.y + style->padding.y;
    chart->w = bounds.w - 2 * style->padding.x;
    chart->h = bounds.h - 2 * style->padding.y;
    chart->w = NK_MAX(chart->w, 2 * style->padding.x);
    chart->h = NK_MAX(chart->h, 2 * style->padding.y);

    /* add first slot into chart */
    {struct nk_chart_slot *slot = &chart->slots[chart->slot++];
    slot->type = type;
    slot->count = count;
    slot->min = NK_MIN(min_value, max_value);
    slot->max = NK_MAX(min_value, max_value);
    slot->range = slot->max - slot->min;}

    /* draw chart background */
    background = &style->background;
    if (background->type == NK_STYLE_ITEM_IMAGE) {
        nk_draw_image(&win->buffer, bounds, &background->data.image);
    } else {
        nk_fill_rect(&win->buffer, bounds, style->rounding, style->border_color);
        nk_fill_rect(&win->buffer, nk_shrink_rect(bounds, style->border),
            style->rounding, style->border_color);
    }
    return 1;
}

NK_API void
nk_chart_add_slot(struct nk_context *ctx, const enum nk_chart_type type,
    int count, float min_value, float max_value)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    NK_ASSERT(ctx->current->layout->chart.slot < NK_CHART_MAX_SLOT);
    if (!ctx || !ctx->current || !ctx->current->layout) return;
    if (ctx->current->layout->chart.slot >= NK_CHART_MAX_SLOT) return;

    /* add another slot into the graph */
    {struct nk_chart *chart = &ctx->current->layout->chart;
    struct nk_chart_slot *slot = &chart->slots[chart->slot++];
    slot->type = type;
    slot->count = count;
    slot->min = NK_MIN(min_value, max_value);
    slot->max = NK_MAX(min_value, max_value);
    slot->range = slot->max - slot->min;}
}

NK_INTERN nk_flags
nk_chart_push_line(struct nk_context *ctx, struct nk_window *win,
    struct nk_chart *g, float value, int slot)
{
    struct nk_panel *layout = win->layout;
    const struct nk_input *i = &ctx->input;
    struct nk_command_buffer *out = &win->buffer;
    struct nk_style_chart *style;

    nk_flags ret = 0;
    struct nk_vec2 cur;
    struct nk_rect bounds;
    struct nk_color color;
    float step;
    float range;
    float ratio;

    NK_ASSERT(slot >= 0 && slot < NK_CHART_MAX_SLOT);
    step = g->w / (float)g->slots[slot].count;
    range = g->slots[slot].max - g->slots[slot].min;
    ratio = (value - g->slots[slot].min) / range;
    style = &ctx->style.chart;

    if (g->slots[slot].index == 0) {
        /* first data point does not have a connection */
        g->slots[slot].last.x = g->x;
        g->slots[slot].last.y = (g->y + g->h) - ratio * (float)g->h;

        bounds.x = g->slots[slot].last.x - 2;
        bounds.y = g->slots[slot].last.y - 2;
        bounds.w = 4;
        bounds.h = 4;

        color = style->color;
        if (!(layout->flags & NK_WINDOW_ROM) &&
            NK_INBOX(i->mouse.pos.x,i->mouse.pos.y, g->slots[slot].last.x-3, g->slots[slot].last.y-3, 6, 6)){
            ret = nk_input_is_mouse_hovering_rect(i, bounds) ? NK_CHART_HOVERING : 0;
            ret |= (i->mouse.buttons[NK_BUTTON_LEFT].down &&
                i->mouse.buttons[NK_BUTTON_LEFT].clicked) ? NK_CHART_CLICKED: 0;
            color = style->selected_color;
        }
        nk_fill_rect(out, bounds, 0, color);
        g->slots[slot].index += 1;
        return ret;
    }

    /* draw a line between the last data point and the new one */
    cur.x = g->x + (float)(step * (float)g->slots[slot].index);
    cur.y = (g->y + g->h) - (ratio * (float)g->h);
    nk_stroke_line(out, g->slots[slot].last.x, g->slots[slot].last.y, cur.x, cur.y, 1.0f, style->color);

    bounds.x = cur.x - 3;
    bounds.y = cur.y - 3;
    bounds.w = 6;
    bounds.h = 6;

    /* user selection of current data point */
    color = style->color;
    if (!(layout->flags & NK_WINDOW_ROM)) {
        if (nk_input_is_mouse_hovering_rect(i, bounds)) {
            ret = NK_CHART_HOVERING;
            ret |= (!i->mouse.buttons[NK_BUTTON_LEFT].down &&
                i->mouse.buttons[NK_BUTTON_LEFT].clicked) ? NK_CHART_CLICKED: 0;
            color = style->selected_color;
        }
    }
    nk_fill_rect(out, nk_rect(cur.x - 2, cur.y - 2, 4, 4), 0, color);

    /* save current data point position */
    g->slots[slot].last.x = cur.x;
    g->slots[slot].last.y = cur.y;
    g->slots[slot].index  += 1;
    return ret;
}

NK_INTERN nk_flags
nk_chart_push_column(const struct nk_context *ctx, struct nk_window *win,
    struct nk_chart *chart, float value, int slot)
{
    struct nk_command_buffer *out = &win->buffer;
    const struct nk_input *in = &ctx->input;
    struct nk_panel *layout = win->layout;
    const struct nk_style_chart *style;

    float ratio;
    nk_flags ret = 0;
    struct nk_color color;
    struct nk_rect item = {0,0,0,0};

    NK_ASSERT(slot >= 0 && slot < NK_CHART_MAX_SLOT);
    if (chart->slots[slot].index  >= chart->slots[slot].count)
        return nk_false;
    if (chart->slots[slot].count) {
        float padding = (float)(chart->slots[slot].count-1);
        item.w = (chart->w - padding) / (float)(chart->slots[slot].count);
    }

    /* calculate bounds of current bar chart entry */
    style = &ctx->style.chart;
    color = style->color;
    item.h = chart->h * NK_ABS((value/chart->slots[slot].range));
    if (value >= 0) {
        ratio = (value + NK_ABS(chart->slots[slot].min)) / NK_ABS(chart->slots[slot].range);
        item.y = (chart->y + chart->h) - chart->h * ratio;
    } else {
        ratio = (value - chart->slots[slot].max) / chart->slots[slot].range;
        item.y = chart->y + (chart->h * NK_ABS(ratio)) - item.h;
    }
    item.x = chart->x + ((float)chart->slots[slot].index * item.w);
    item.x = item.x + ((float)chart->slots[slot].index);

    /* user chart bar selection */
    if (!(layout->flags & NK_WINDOW_ROM) &&
        NK_INBOX(in->mouse.pos.x,in->mouse.pos.y,item.x,item.y,item.w,item.h)) {
        ret = NK_CHART_HOVERING;
        ret |= (!in->mouse.buttons[NK_BUTTON_LEFT].down &&
                in->mouse.buttons[NK_BUTTON_LEFT].clicked) ? NK_CHART_CLICKED: 0;
        color = style->selected_color;
    }
    nk_fill_rect(out, item, 0, color);
    chart->slots[slot].index += 1;
    return ret;
}

NK_API nk_flags
nk_chart_push_slot(struct nk_context *ctx, float value, int slot)
{
    nk_flags flags;
    struct nk_window *win;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(slot >= 0 && slot < NK_CHART_MAX_SLOT);
    NK_ASSERT(slot < ctx->current->layout->chart.slot);
    if (!ctx || !ctx->current || slot >= NK_CHART_MAX_SLOT) return nk_false;
    if (slot >= ctx->current->layout->chart.slot) return nk_false;

    win = ctx->current;
    if (win->layout->chart.slot < slot) return nk_false;
    switch (win->layout->chart.slots[slot].type) {
    case NK_CHART_LINES:
        flags = nk_chart_push_line(ctx, win, &win->layout->chart, value, slot); break;
    case NK_CHART_COLUMN:
        flags = nk_chart_push_column(ctx, win, &win->layout->chart, value, slot); break;
    default:
    case NK_CHART_MAX:
        flags = 0;
    }
    return flags;
}

NK_API nk_flags
nk_chart_push(struct nk_context *ctx, float value)
{return nk_chart_push_slot(ctx, value, 0);}

NK_API void
nk_chart_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_chart *chart;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return;

    win = ctx->current;
    chart = &win->layout->chart;
    memset(chart, 0, sizeof(*chart));
    return;
}

NK_API void
nk_plot(struct nk_context *ctx, enum nk_chart_type type, const float *values,
    int count, int offset)
{
    int i = 0;
    float min_value;
    float max_value;

    NK_ASSERT(ctx);
    NK_ASSERT(values);
    if (!ctx || !values || !count) return;

    min_value = values[offset];
    max_value = values[offset];
    for (i = 0; i < count; ++i) {
        min_value = NK_MIN(values[i + offset], min_value);
        max_value = NK_MAX(values[i + offset], max_value);
    }
    nk_chart_begin(ctx, type, count, min_value, max_value);
    for (i = 0; i < count; ++i)
        nk_chart_push(ctx, values[i + offset]);
    nk_chart_end(ctx);
}

NK_API void
nk_plot_function(struct nk_context *ctx, enum nk_chart_type type, void *userdata,
    float(*value_getter)(void* user, int index), int count, int offset)
{
    int i = 0;
    float min_value;
    float max_value;

    NK_ASSERT(ctx);
    NK_ASSERT(value_getter);
    if (!ctx || !value_getter || !count) return;

    max_value = min_value = value_getter(userdata, offset);
    for (i = 0; i < count; ++i) {
        float value = value_getter(userdata, i + offset);
        min_value = NK_MIN(value, min_value);
        max_value = NK_MAX(value, max_value);
    }
    nk_chart_begin(ctx, type, count, min_value, max_value);
    for (i = 0; i < count; ++i)
        nk_chart_push(ctx, value_getter(userdata, i + offset));
    nk_chart_end(ctx);
}

/* -------------------------------------------------------------
 *
 *                          GROUP
 *
 * --------------------------------------------------------------*/
NK_API int
nk_group_begin(struct nk_context *ctx, struct nk_panel *layout, const char *title,
    nk_flags flags)
{
    struct nk_window *win;
    const struct nk_rect *c;
    union {struct nk_scroll *s; nk_uint *i;} value;
    struct nk_window panel;
    struct nk_rect bounds;
    nk_hash title_hash;
    int title_len;

    NK_ASSERT(ctx);
    NK_ASSERT(title);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !title)
        return 0;

    /* allocate space for the group panel inside the panel */
    win = ctx->current;
    c = &win->layout->clip;
    nk_panel_alloc_space(&bounds, ctx);
    nk_zero(layout, sizeof(*layout));

    /* find persistent group scrollbar value */
    title_len = (int)nk_strlen(title);
    title_hash = nk_murmur_hash(title, (int)title_len, NK_WINDOW_SUB);
    value.i = nk_find_value(win, title_hash);
    if (!value.i) {
        value.i = nk_add_value(ctx, win, title_hash, 0);
        *value.i = 0;
    }
    if (!NK_INTERSECT(c->x, c->y, c->w, c->h, bounds.x, bounds.y, bounds.w, bounds.h) &&
        !(flags & NK_WINDOW_MOVABLE)) {
        return 0;
    }

    flags |= NK_WINDOW_SUB;
    if (win->flags & NK_WINDOW_ROM)
        flags |= NK_WINDOW_ROM;

    /* initialize a fake window to create the layout from */
    nk_zero(&panel, sizeof(panel));
    panel.bounds = bounds;
    panel.flags = flags;
    panel.scrollbar.x = (unsigned short)value.s->x;
    panel.scrollbar.y = (unsigned short)value.s->y;
    panel.buffer = win->buffer;
    panel.layout = layout;
    ctx->current = &panel;
    nk_panel_begin(ctx, (flags & NK_WINDOW_TITLE) ? title: 0);

    win->buffer = panel.buffer;
    win->buffer.clip = layout->clip;
    layout->offset = value.s;
    layout->parent = win->layout;
    win->layout = layout;
    ctx->current = win;
    return 1;
}

NK_API void
nk_group_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_panel *parent;
    struct nk_panel *g;

    struct nk_rect clip;
    struct nk_window pan;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return;

    /* make sure nk_group_begin was called correctly */
    NK_ASSERT(ctx->current);
    win = ctx->current;
    NK_ASSERT(win->layout);
    g = win->layout;
    NK_ASSERT(g->parent);
    parent = g->parent;

    /* dummy window */
    nk_zero_struct(pan);
    pan.bounds = g->bounds;
    pan.scrollbar.x = (unsigned short)g->offset->x;
    pan.scrollbar.y = (unsigned short)g->offset->y;
    pan.flags = g->flags|NK_WINDOW_SUB;
    pan.buffer = win->buffer;
    pan.layout = g;
    ctx->current = &pan;

    /* make sure group has correct clipping rectangle */
    nk_unify(&clip, &parent->clip,
        g->bounds.x, g->clip.y - g->header_h,
        g->bounds.x + g->bounds.w+1,
        g->bounds.y + g->bounds.h + 1);
    nk_push_scissor(&pan.buffer, clip);
    nk_end(ctx);

    win->buffer = pan.buffer;
    nk_push_scissor(&win->buffer, parent->clip);
    ctx->current = win;
    win->layout = parent;
    return;
}

/* --------------------------------------------------------------
 *
 *                          POPUP
 *
 * --------------------------------------------------------------*/
NK_API int
nk_popup_begin(struct nk_context *ctx, struct nk_panel *layout,
    enum nk_popup_type type, const char *title, nk_flags flags, struct nk_rect rect)
{
    struct nk_window *popup;
    struct nk_window *win;

    int title_len;
    nk_hash title_hash;
    nk_size allocated;

    NK_ASSERT(ctx);
    NK_ASSERT(title);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    NK_ASSERT(!(win->flags & NK_WINDOW_POPUP));
    title_len = (int)nk_strlen(title);
    title_hash = nk_murmur_hash(title, (int)title_len, NK_WINDOW_POPUP);

    popup = win->popup.win;
    if (!popup) {
        popup = (struct nk_window*)nk_create_window(ctx);
        win->popup.win = popup;
        win->popup.active = 0;
    }

    /* make sure we have to correct popup */
    if (win->popup.name != title_hash) {
        if (!win->popup.active) {
            nk_zero(popup, sizeof(*popup));
            win->popup.name = title_hash;
            win->popup.active = 1;
        } else return 0;
    }

    /* popup position is local to window */
    ctx->current = popup;
    rect.x += win->layout->clip.x;
    rect.y += win->layout->clip.y;

    /* setup popup data */
    popup->parent = win;
    popup->bounds = rect;
    popup->seq = ctx->seq;
    popup->layout = layout;
    popup->flags = flags;
    popup->flags |= NK_WINDOW_BORDER|NK_WINDOW_SUB|NK_WINDOW_POPUP;
    if (type == NK_POPUP_DYNAMIC)
        popup->flags |= NK_WINDOW_DYNAMIC;

    popup->buffer = win->buffer;
    nk_start_popup(ctx, win);
    allocated = ctx->memory.allocated;
    nk_push_scissor(&popup->buffer, nk_null_rect);

    if (nk_panel_begin(ctx, title)) {
        /* popup is running therefore invalidate parent window  */
        win->layout->flags |= NK_WINDOW_ROM;
        win->layout->flags &= ~(nk_flags)NK_WINDOW_REMOVE_ROM;
        win->popup.active = 1;
        layout->offset = &popup->scrollbar;
        return 1;
    } else {
        /* popup was closed/is invalid so cleanup */
        win->layout->flags |= NK_WINDOW_REMOVE_ROM;
        win->layout->popup_buffer.active = 0;
        win->popup.active = 0;
        ctx->memory.allocated = allocated;
        ctx->current = win;
        return 0;
    }
}

NK_INTERN int
nk_nonblock_begin(struct nk_panel *layout, struct nk_context *ctx,
    nk_flags flags, struct nk_rect body, struct nk_rect header)
{
    struct nk_window *popup;
    struct nk_window *win;
    int is_active = nk_true;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    /* popups cannot have popups */
    win = ctx->current;
    NK_ASSERT(!(win->flags & NK_WINDOW_POPUP));
    popup = win->popup.win;
    if (!popup) {
        /* create window for nonblocking popup */
        popup = (struct nk_window*)nk_create_window(ctx);
        win->popup.win = popup;
        nk_command_buffer_init(&popup->buffer, &ctx->memory, NK_CLIPPING_ON);
    } else {
        /* check if user clicked outside the popup and close if so */
        int clicked, in_body, in_header;
        clicked = nk_input_has_mouse_click(&ctx->input, NK_BUTTON_LEFT);
        in_body = nk_input_is_mouse_click_in_rect(&ctx->input, NK_BUTTON_LEFT, body);
        in_header = nk_input_is_mouse_click_in_rect(&ctx->input, NK_BUTTON_LEFT, header);

        if (clicked && !in_body && !in_header)
            is_active = nk_false;
    }

    if (!is_active) {
        win->layout->flags |= NK_WINDOW_REMOVE_ROM;
        return is_active;
    }

    popup->bounds = body;
    popup->parent = win;
    popup->layout = layout;
    popup->flags = flags;
    popup->flags |= NK_WINDOW_BORDER|NK_WINDOW_POPUP;
    popup->flags |= NK_WINDOW_DYNAMIC|NK_WINDOW_SUB;
    popup->flags |= NK_WINDOW_NONBLOCK;
    popup->seq = ctx->seq;
    win->popup.active = 1;

    nk_start_popup(ctx, win);
    popup->buffer = win->buffer;
    nk_push_scissor(&popup->buffer, nk_null_rect);
    ctx->current = popup;

    nk_panel_begin(ctx, 0);
    win->buffer = popup->buffer;
    win->layout->flags |= NK_WINDOW_ROM;
    layout->offset = &popup->scrollbar;
    return is_active;
}

NK_API void
nk_popup_close(struct nk_context *ctx)
{
    struct nk_window *popup;
    NK_ASSERT(ctx);
    if (!ctx || !ctx->current) return;

    popup = ctx->current;
    NK_ASSERT(popup->parent);
    NK_ASSERT(popup->flags & NK_WINDOW_POPUP);
    popup->flags |= NK_WINDOW_HIDDEN;
}

NK_API void
nk_popup_end(struct nk_context *ctx)
{
    struct nk_window *win;
    struct nk_window *popup;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    popup = ctx->current;
    if (!popup->parent) return;
    win = popup->parent;
    if (popup->flags & NK_WINDOW_HIDDEN) {
        win->layout->flags |= NK_WINDOW_REMOVE_ROM;
        win->popup.active = 0;
    }
    nk_push_scissor(&popup->buffer, nk_null_rect);
    nk_end(ctx);

    win->buffer = popup->buffer;
    nk_finish_popup(ctx, win);
    ctx->current = win;
    nk_push_scissor(&win->buffer, win->layout->clip);
}
/* -------------------------------------------------------------
 *
 *                          TOOLTIP
 *
 * -------------------------------------------------------------- */
NK_API int
nk_tooltip_begin(struct nk_context *ctx, struct nk_panel *layout, float width)
{
    struct nk_window *win;
    const struct nk_input *in;
    struct nk_rect bounds;
    int ret;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    /* make sure that no nonblocking popup is currently active */
    win = ctx->current;
    in = &ctx->input;
    if (win->popup.win && (win->popup.win->flags & NK_WINDOW_NONBLOCK))
        return 0;

    bounds.w = width;
    bounds.h = nk_null_rect.h;
    bounds.x = (in->mouse.pos.x + 1) - win->layout->clip.x;
    bounds.y = (in->mouse.pos.y + 1) - win->layout->clip.y;

    ret = nk_popup_begin(ctx, layout, NK_POPUP_DYNAMIC,
        "__##Tooltip##__", NK_WINDOW_NO_SCROLLBAR|NK_WINDOW_TOOLTIP|NK_WINDOW_BORDER, bounds);
    if (ret) win->layout->flags &= ~(nk_flags)NK_WINDOW_ROM;
    return ret;
}

NK_API void
nk_tooltip_end(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    if (!ctx || !ctx->current)
        return;
    nk_popup_close(ctx);
    nk_popup_end(ctx);
}

NK_API void
nk_tooltip(struct nk_context *ctx, const char *text)
{
    const struct nk_style *style;
    struct nk_vec2 padding;
    struct nk_panel layout;

    int text_len;
    float text_width;
    float text_height;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    NK_ASSERT(text);
    if (!ctx || !ctx->current || !ctx->current->layout || !text)
        return;

    /* fetch configuration data */
    style = &ctx->style;
    padding = style->window.padding;

    /* calculate size of the text and tooltip */
    text_len = nk_strlen(text);
    text_width = style->font.width(style->font.userdata,
                    style->font.height, text, text_len);
    text_width += (4 * padding.x);
    text_height = (style->font.height + 2 * padding.y);

    /* execute tooltip and fill with text */
    if (nk_tooltip_begin(ctx, &layout, (float)text_width)) {
        nk_layout_row_dynamic(ctx, (float)text_height, 1);
        nk_text(ctx, text, text_len, NK_TEXT_LEFT);
        nk_tooltip_end(ctx);
    }
}
/* -------------------------------------------------------------
 *
 *                          CONTEXTUAL
 *
 * -------------------------------------------------------------- */
NK_API int
nk_contextual_begin(struct nk_context *ctx, struct nk_panel *layout,
    nk_flags flags, struct nk_vec2 size, struct nk_rect trigger_bounds)
{
    struct nk_window *win;
    struct nk_window *popup;
    struct nk_rect body;

    NK_STORAGE const struct nk_rect null_rect = {0,0,0,0};
    int is_clicked = 0;
    int is_active = 0;
    int is_open = 0;
    int ret = 0;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    ++win->popup.con_count;

    /* check if currently active contextual is active */
    popup = win->popup.win;
    is_open = (popup && (popup->flags & NK_WINDOW_CONTEXTUAL) && win->popup.type == NK_WINDOW_CONTEXTUAL);
    is_clicked = nk_input_mouse_clicked(&ctx->input, NK_BUTTON_RIGHT, trigger_bounds);
    if (win->popup.active_con && win->popup.con_count != win->popup.active_con)
        return 0;
    if ((is_clicked && is_open && !is_active) || (!is_open && !is_active && !is_clicked))
        return 0;

    /* calculate contextual position on click */
    win->popup.active_con = win->popup.con_count;
    if (is_clicked) {
        body.x = ctx->input.mouse.pos.x;
        body.y = ctx->input.mouse.pos.y;
    } else {
        body.x = popup->bounds.x;
        body.y = popup->bounds.y;
    }
    body.w = size.x;
    body.h = size.y;

    /* start nonblocking contextual popup */
    ret = nk_nonblock_begin(layout, ctx,
            flags|NK_WINDOW_CONTEXTUAL|NK_WINDOW_NO_SCROLLBAR, body, null_rect);
    if (ret) win->popup.type = NK_WINDOW_CONTEXTUAL;
    else {
        win->popup.active_con = 0;
        win->popup.win->flags = 0;
    }
    return ret;
}

NK_API int
nk_contextual_item_text(struct nk_context *ctx, const char *text, int len,
    nk_flags alignment)
{
    struct nk_window *win;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    state = nk_widget_fitting(&bounds, ctx, style->contextual_button.padding);
    if (!state) return nk_false;

    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text(&ctx->last_widget_state, &win->buffer, bounds,
        text, len, alignment, NK_BUTTON_DEFAULT, &style->contextual_button, in, &style->font)) {
        nk_contextual_close(ctx);
        return nk_true;
    }
    return nk_false;
}

NK_API int nk_contextual_item_label(struct nk_context *ctx, const char *label, nk_flags align)
{return nk_contextual_item_text(ctx, label, nk_strlen(label), align);}

NK_API int
nk_contextual_item_image_text(struct nk_context *ctx, struct nk_image img,
    const char *text, int len, nk_flags align)
{
    struct nk_window *win;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    state = nk_widget_fitting(&bounds, ctx, style->contextual_button.padding);
    if (!state) return nk_false;

    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text_image(&ctx->last_widget_state, &win->buffer, bounds,
        img, text, len, align, NK_BUTTON_DEFAULT, &style->contextual_button, &style->font, in)){
        nk_contextual_close(ctx);
        return nk_true;
    }
    return nk_false;
}

NK_API int nk_contextual_item_image_label(struct nk_context *ctx, struct nk_image img,
    const char *label, nk_flags align)
{return nk_contextual_item_image_text(ctx, img, label, nk_strlen(label), align);}

NK_API int
nk_contextual_item_symbol_text(struct nk_context *ctx, enum nk_symbol_type symbol,
    const char *text, int len, nk_flags align)
{
    struct nk_window *win;
    const struct nk_input *in;
    const struct nk_style *style;

    struct nk_rect bounds;
    enum nk_widget_layout_states state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    state = nk_widget_fitting(&bounds, ctx, style->contextual_button.padding);
    if (!state) return nk_false;

    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text_symbol(&ctx->last_widget_state, &win->buffer, bounds,
        symbol, text, len, align, NK_BUTTON_DEFAULT, &style->contextual_button, &style->font, in)) {
        nk_contextual_close(ctx);
        return nk_true;
    }
    return nk_false;
}

NK_API int nk_contextual_item_symbol_label(struct nk_context *ctx, enum nk_symbol_type symbol,
    const char *text, nk_flags align)
{return nk_contextual_item_symbol_text(ctx, symbol, text, nk_strlen(text), align);}

NK_API void
nk_contextual_close(struct nk_context *ctx)
{
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return;

    if (!ctx->current)
        return;
    nk_popup_close(ctx);
}

NK_API void
nk_contextual_end(struct nk_context *ctx)
{
    struct nk_window *popup;
    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    popup = ctx->current;
    NK_ASSERT(popup->parent);
    if (popup->flags & NK_WINDOW_HIDDEN)
        popup->seq = 0;
    nk_popup_end(ctx);
    return;
}
/* -------------------------------------------------------------
 *
 *                          COMBO
 *
 * --------------------------------------------------------------*/
NK_INTERN int
nk_combo_begin(struct nk_panel *layout, struct nk_context *ctx, struct nk_window *win,
    int height, int is_clicked, struct nk_rect header)
{
    struct nk_window *popup;
    int is_open = 0;
    int is_active = 0;
    struct nk_rect body;
    nk_hash hash;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    popup = win->popup.win;
    body.x = header.x;
    body.w = header.w;
    body.y = header.y + header.h-1;
    body.h = (float)height;

    hash = win->popup.combo_count++;
    is_open = (popup && (popup->flags & NK_WINDOW_COMBO));
    is_active = (popup && (win->popup.name == hash) && win->popup.type == NK_WINDOW_COMBO);
    if ((is_clicked && is_open && !is_active) || (is_open && !is_active) ||
        (!is_open && !is_active && !is_clicked)) return 0;
    if (!nk_nonblock_begin(layout, ctx, NK_WINDOW_COMBO,
            body, (is_clicked && is_open)?nk_rect(0,0,0,0):header)) return 0;

    win->popup.type = NK_WINDOW_COMBO;
    win->popup.name = hash;
    return 1;
}

NK_API int
nk_combo_begin_text(struct nk_context *ctx, struct nk_panel *layout,
    const char *selected, int len, int height)
{
    const struct nk_input *in;
    struct nk_window *win;
    struct nk_style *style;

    enum nk_widget_layout_states s;
    int is_clicked = nk_false;
    struct nk_rect header;

    const struct nk_style_item *background;
    struct nk_text text;

    NK_ASSERT(ctx);
    NK_ASSERT(selected);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout || !selected)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (s == NK_WIDGET_INVALID)
        return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    /* draw combo box header background and border */
    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->combo.active;
        text.text = style->combo.label_active;
    } else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER) {
        background = &style->combo.hover;
        text.text = style->combo.label_hover;
    } else {
        background = &style->combo.normal;
        text.text = style->combo.label_normal;
    }
    if (background->type == NK_STYLE_ITEM_IMAGE) {
        text.background = nk_rgba(0,0,0,0);
        nk_draw_image(&win->buffer, header, &background->data.image);
    } else {
        text.background = background->data.color;
        nk_fill_rect(&win->buffer, header, style->combo.rounding, style->combo.border_color);
        nk_fill_rect(&win->buffer, nk_shrink_rect(header, 1), style->combo.rounding,
            background->data.color);
    }
    {
        /* print currently selected text item */
        struct nk_rect label;
        struct nk_rect button;
        struct nk_rect content;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else sym = style->combo.sym_normal;

        /* calculate button */
        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.x;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;

        /* draw selected label */
        text.padding = nk_vec2(0,0);
        label.x = header.x + style->combo.content_padding.x;
        label.y = header.y + style->combo.content_padding.y;
        label.w = button.x - (style->combo.content_padding.x + style->combo.spacing.x) - label.x;;
        label.h = header.h - 2 * style->combo.content_padding.y;
        nk_widget_text(&win->buffer, label, selected, len, &text,
            NK_TEXT_LEFT, &ctx->style.font);

        /* draw open/close button */
        nk_draw_button_symbol(&win->buffer, &button, &content, ctx->last_widget_state,
            &ctx->style.combo.button, sym, &style->font);
    }
    return nk_combo_begin(layout, ctx, win, height, is_clicked, header);
}

NK_API int nk_combo_begin_label(struct nk_context *ctx, struct nk_panel *layout,
    const char *selected, int max_height)
{return nk_combo_begin_text(ctx, layout, selected, nk_strlen(selected), max_height);}

NK_API int
nk_combo_begin_color(struct nk_context *ctx, struct nk_panel *layout,
    struct nk_color color, int height)
{
    struct nk_window *win;
    struct nk_style *style;
    const struct nk_input *in;

    struct nk_rect header;
    int is_clicked = nk_false;
    enum nk_widget_layout_states s;
    const struct nk_style_item *background;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (s == NK_WIDGET_INVALID)
        return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    /* draw combo box header background and border */
    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED)
        background = &style->combo.active;
    else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
        background = &style->combo.hover;
    else background = &style->combo.normal;

    if (background->type == NK_STYLE_ITEM_IMAGE) {
        nk_draw_image(&win->buffer, header, &background->data.image);
    } else {
        nk_fill_rect(&win->buffer, header, 0, style->combo.border_color);
        nk_fill_rect(&win->buffer, nk_shrink_rect(header, 1), 0,
            background->data.color);
    }
    {
        struct nk_rect content;
        struct nk_rect button;
        struct nk_rect bounds;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else sym = style->combo.sym_normal;

        /* calculate button */
        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.x;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;

        /* draw color */
        bounds.h = header.h - 4 * style->combo.content_padding.y;
        bounds.y = header.y + 2 * style->combo.content_padding.y;
        bounds.x = header.x + 2 * style->combo.content_padding.x;
        bounds.w = (button.x - (style->combo.content_padding.x + style->combo.spacing.x)) - bounds.x;
        nk_fill_rect(&win->buffer, bounds, 0, color);

        /* draw open/close button */
        nk_draw_button_symbol(&win->buffer, &button, &content, ctx->last_widget_state,
            &ctx->style.combo.button, sym, &style->font);
    }
    return nk_combo_begin(layout, ctx, win, height, is_clicked, header);
}

NK_API int
nk_combo_begin_symbol(struct nk_context *ctx, struct nk_panel *layout,
    enum nk_symbol_type symbol, int height)
{
    struct nk_window *win;
    struct nk_style *style;
    const struct nk_input *in;

    struct nk_rect header;
    int is_clicked = nk_false;
    enum nk_widget_layout_states s;
    const struct nk_style_item *background;
    struct nk_color sym_background;
    struct nk_color symbol_color;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (s == NK_WIDGET_INVALID)
        return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    /* draw combo box header background and border */
    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->combo.active;
        symbol_color = style->combo.symbol_active;
    } else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER) {
        background = &style->combo.hover;
        symbol_color = style->combo.symbol_hover;
    } else {
        background = &style->combo.normal;
        symbol_color = style->combo.symbol_hover;
    }

    if (background->type == NK_STYLE_ITEM_IMAGE) {
        sym_background = nk_rgba(0,0,0,0);
        nk_draw_image(&win->buffer, header, &background->data.image);
    } else {
        sym_background = background->data.color;
        nk_fill_rect(&win->buffer, header, 0, style->combo.border_color);
        nk_fill_rect(&win->buffer, nk_shrink_rect(header, 1), 0,
            background->data.color);
    }
    {
        struct nk_rect bounds = {0,0,0,0};
        struct nk_rect content;
        struct nk_rect button;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else sym = style->combo.sym_normal;

        /* calculate button */
        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.y;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;

        /* draw symbol */
        bounds.h = header.h - 2 * style->combo.content_padding.y;
        bounds.y = header.y + style->combo.content_padding.y;
        bounds.x = header.x + style->combo.content_padding.x;
        bounds.w = (button.x - style->combo.content_padding.y) - bounds.x;
        nk_draw_symbol(&win->buffer, symbol, bounds, sym_background, symbol_color,
            1.0f, &style->font);

        /* draw open/close button */
        nk_draw_button_symbol(&win->buffer, &bounds, &content, ctx->last_widget_state,
            &ctx->style.combo.button, sym, &style->font);
    }
    return nk_combo_begin(layout, ctx, win, height, is_clicked, header);
}

NK_API int
nk_combo_begin_symbol_text(struct nk_context *ctx, struct nk_panel *layout,
    const char *selected, int len, enum nk_symbol_type symbol, int height)
{
    struct nk_window *win;
    struct nk_style *style;
    struct nk_input *in;

    struct nk_rect header;
    int is_clicked = nk_false;
    enum nk_widget_layout_states s;
    const struct nk_style_item *background;
    struct nk_color symbol_color;
    struct nk_text text;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (!s) return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    /* draw combo box header background and border */
    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->combo.active;
        symbol_color = style->combo.symbol_active;
        text.text = style->combo.label_active;
    } else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER) {
        background = &style->combo.hover;
        symbol_color = style->combo.symbol_hover;
        text.text = style->combo.label_hover;
    } else {
        background = &style->combo.normal;
        symbol_color = style->combo.symbol_normal;
        text.text = style->combo.label_normal;
    }
    if (background->type == NK_STYLE_ITEM_IMAGE) {
        text.background = nk_rgba(0,0,0,0);
        nk_draw_image(&win->buffer, header, &background->data.image);
    } else {
        text.background = background->data.color;
        nk_fill_rect(&win->buffer, header, 0, style->combo.border_color);
        nk_fill_rect(&win->buffer, nk_shrink_rect(header, 1), 0,
            background->data.color);
    }
    {
        struct nk_rect content;
        struct nk_rect button;
        struct nk_rect label;
        struct nk_rect image;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else sym = style->combo.sym_normal;

        /* calculate button */
        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.x;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;
        nk_draw_button_symbol(&win->buffer, &button, &content, ctx->last_widget_state,
            &ctx->style.combo.button, sym, &style->font);

        /* draw symbol */
        image.x = header.x + style->combo.content_padding.x;
        image.y = header.y + style->combo.content_padding.y;
        image.h = header.h - 2 * style->combo.content_padding.y;
        image.w = image.h;
        nk_draw_symbol(&win->buffer, symbol, image, text.background, symbol_color,
            1.0f, &style->font);

        /* draw label */
        text.padding = nk_vec2(0,0);
        label.x = image.x + image.w + style->combo.spacing.x + style->combo.content_padding.x;
        label.y = header.y + style->combo.content_padding.y;
        label.w = (button.x - style->combo.content_padding.x) - label.x;
        label.h = header.h - 2 * style->combo.content_padding.y;
        nk_widget_text(&win->buffer, label, selected, len, &text, NK_TEXT_LEFT, &style->font);
    }
    return nk_combo_begin(layout, ctx, win, height, is_clicked, header);
}

NK_API int
nk_combo_begin_image(struct nk_context *ctx, struct nk_panel *layout,
    struct nk_image img, int height)
{
    struct nk_window *win;
    struct nk_style *style;
    const struct nk_input *in;

    struct nk_rect header;
    int is_clicked = nk_false;
    enum nk_widget_layout_states s;
    const struct nk_style_item *background;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (s == NK_WIDGET_INVALID)
        return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    /* draw combo box header background and border */
    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED)
        background = &style->combo.active;
    else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
        background = &style->combo.hover;
    else background = &style->combo.normal;

    if (background->type == NK_STYLE_ITEM_IMAGE) {
        nk_draw_image(&win->buffer, header, &background->data.image);
    } else {
        nk_fill_rect(&win->buffer, header, 0, style->combo.border_color);
        nk_fill_rect(&win->buffer, nk_shrink_rect(header, 1), 0,
            background->data.color);
    }
    {
        struct nk_rect bounds = {0,0,0,0};
        struct nk_rect content;
        struct nk_rect button;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else sym = style->combo.sym_normal;

        /* calculate button */
        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.y;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;

        /* draw image */
        bounds.h = header.h - 2 * style->combo.content_padding.y;
        bounds.y = header.y + style->combo.content_padding.y;
        bounds.x = header.x + style->combo.content_padding.x;
        bounds.w = (button.x - style->combo.content_padding.y) - bounds.x;
        nk_draw_image(&win->buffer, bounds, &img);

        /* draw open/close button */
        nk_draw_button_symbol(&win->buffer, &bounds, &content, ctx->last_widget_state,
            &ctx->style.combo.button, sym, &style->font);
    }
    return nk_combo_begin(layout, ctx, win, height, is_clicked, header);
}

NK_API int
nk_combo_begin_image_text(struct nk_context *ctx, struct nk_panel *layout,
    const char *selected, int len, struct nk_image img, int height)
{
    struct nk_window *win;
    struct nk_style *style;
    struct nk_input *in;

    struct nk_rect header;
    int is_clicked = nk_false;
    enum nk_widget_layout_states s;
    const struct nk_style_item *background;
    struct nk_text text;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    style = &ctx->style;
    s = nk_widget(&header, ctx);
    if (!s) return 0;

    in = (win->layout->flags & NK_WINDOW_ROM || s == NK_WIDGET_ROM)? 0: &ctx->input;
    if (nk_button_behavior(&ctx->last_widget_state, header, in, NK_BUTTON_DEFAULT))
        is_clicked = nk_true;

    /* draw combo box header background and border */
    if (ctx->last_widget_state & NK_WIDGET_STATE_ACTIVED) {
        background = &style->combo.active;
        text.text = style->combo.label_active;
    } else if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER) {
        background = &style->combo.hover;
        text.text = style->combo.label_hover;
    } else {
        background = &style->combo.normal;
        text.text = style->combo.label_normal;
    }
    if (background->type == NK_STYLE_ITEM_IMAGE) {
        text.background = nk_rgba(0,0,0,0);
        nk_draw_image(&win->buffer, header, &background->data.image);
    } else {
        text.background = background->data.color;
        nk_fill_rect(&win->buffer, header, 0, style->combo.border_color);
        nk_fill_rect(&win->buffer, nk_shrink_rect(header, 1), 0,
            background->data.color);
    }
    {
        struct nk_rect content;
        struct nk_rect button;
        struct nk_rect label;
        struct nk_rect image;

        enum nk_symbol_type sym;
        if (ctx->last_widget_state & NK_WIDGET_STATE_HOVER)
            sym = style->combo.sym_hover;
        else if (is_clicked)
            sym = style->combo.sym_active;
        else sym = style->combo.sym_normal;

        /* calculate button */
        button.w = header.h - 2 * style->combo.button_padding.y;
        button.x = (header.x + header.w - header.h) - style->combo.button_padding.x;
        button.y = header.y + style->combo.button_padding.y;
        button.h = button.w;

        content.x = button.x + style->combo.button.padding.x;
        content.y = button.y + style->combo.button.padding.y;
        content.w = button.w - 2 * style->combo.button.padding.x;
        content.h = button.h - 2 * style->combo.button.padding.y;
        nk_draw_button_symbol(&win->buffer, &button, &content, ctx->last_widget_state,
            &ctx->style.combo.button, sym, &style->font);

        /* draw image */
        image.x = header.x + style->combo.content_padding.x;
        image.y = header.y + style->combo.content_padding.y;
        image.h = header.h - 2 * style->combo.content_padding.y;
        image.w = image.h;
        nk_draw_image(&win->buffer, image, &img);

        /* draw label */
        text.padding = nk_vec2(0,0);
        label.x = image.x + image.w + style->combo.spacing.x + style->combo.content_padding.x;
        label.y = header.y + style->combo.content_padding.y;
        label.w = (button.x - style->combo.content_padding.x) - label.x;
        label.h = header.h - 2 * style->combo.content_padding.y;
        nk_widget_text(&win->buffer, label, selected, len, &text, NK_TEXT_LEFT, &style->font);
    }
    return nk_combo_begin(layout, ctx, win, height, is_clicked, header);
}

NK_API int nk_combo_begin_symbol_label(struct nk_context *ctx, struct nk_panel *layout,
    const char *selected, enum nk_symbol_type type, int height)
{return nk_combo_begin_symbol_text(ctx, layout, selected, nk_strlen(selected), type, height);}

NK_API int nk_combo_begin_image_label(struct nk_context *ctx, struct nk_panel *layout,
    const char *selected, struct nk_image img, int height)
{return nk_combo_begin_image_text(ctx, layout, selected, nk_strlen(selected), img, height);}

NK_API int nk_combo_item_text(struct nk_context *ctx, const char *text, int len,nk_flags align)
{return nk_contextual_item_text(ctx, text, len, align);}

NK_API int nk_combo_item_label(struct nk_context *ctx, const char *label, nk_flags align)
{return nk_contextual_item_label(ctx, label, align);}

NK_API int nk_combo_item_image_text(struct nk_context *ctx, struct nk_image img, const char *text,
    int len, nk_flags alignment)
{return nk_contextual_item_image_text(ctx, img, text, len, alignment);}

NK_API int nk_combo_item_image_label(struct nk_context *ctx, struct nk_image img,
    const char *text, nk_flags alignment)
{return nk_contextual_item_image_label(ctx, img, text, alignment);}

NK_API int nk_combo_item_symbol_text(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *text, int len, nk_flags alignment)
{return nk_contextual_item_symbol_text(ctx, sym, text, len, alignment);}

NK_API int nk_combo_item_symbol_label(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *label, nk_flags alignment)
{return nk_contextual_item_symbol_label(ctx, sym, label, alignment);}

NK_API void nk_combo_end(struct nk_context *ctx)
{nk_contextual_end(ctx);}

NK_API void nk_combo_close(struct nk_context *ctx)
{nk_contextual_close(ctx);}

NK_API int
nk_combo(struct nk_context *ctx, const char **items, int count,
    int selected, int item_height)
{
    int i = 0;
    int max_height;
    struct nk_panel combo;
    float item_padding;
    float window_padding;

    NK_ASSERT(ctx);
    NK_ASSERT(items);
    if (!ctx || !items ||!count)
        return selected;

    item_padding = ctx->style.combo.button_padding.y;
    window_padding = ctx->style.window.padding.y;
    max_height = (count+1) * item_height + (int)item_padding * 3 + (int)window_padding * 2;
    if (nk_combo_begin_label(ctx, &combo, items[selected], max_height)) {
        nk_layout_row_dynamic(ctx, (float)item_height, 1);
        for (i = 0; i < count; ++i) {
            if (nk_combo_item_label(ctx, items[i], NK_TEXT_LEFT))
                selected = i;
        }
        nk_combo_end(ctx);
    }
    return selected;
}

NK_API int
nk_combo_separator(struct nk_context *ctx, const char *items_separated_by_separator,
    int separator, int selected, int count, int item_height)
{
    int i;
    int max_height;
    struct nk_panel combo;
    float item_padding;
    float window_padding;
    const char *current_item;
    const char *iter;
    int length = 0;

    NK_ASSERT(ctx);
    NK_ASSERT(items_separated_by_separator);
    if (!ctx || !items_separated_by_separator)
        return selected;

    /* calculate popup window */
    item_padding = ctx->style.combo.content_padding.y;
    window_padding = ctx->style.window.padding.y;
    max_height = (count+1) * item_height + (int)item_padding * 3 + (int)window_padding * 2;

    /* find selected item */
    current_item = items_separated_by_separator;
    for (i = 0; i < selected; ++i) {
        iter = current_item;
        while (*iter != separator) iter++;
        length = (int)(iter - current_item);
        current_item = iter + 1;
    }

    if (nk_combo_begin_text(ctx, &combo, current_item, length, max_height)) {
        current_item = items_separated_by_separator;
        nk_layout_row_dynamic(ctx, (float)item_height, 1);
        for (i = 0; i < count; ++i) {
            iter = current_item;
            while (*iter != separator) iter++;
            length = (int)(iter - current_item);
            if (nk_combo_item_text(ctx, current_item, length, NK_TEXT_LEFT))
                selected = i;
            current_item = current_item + length + 1;
        }
        nk_combo_end(ctx);
    }
    return selected;
}

NK_API int
nk_combo_string(struct nk_context *ctx, const char *items_separated_by_zeros,
    int selected, int count, int item_height)
{return nk_combo_separator(ctx, items_separated_by_zeros, '\0', selected, count, item_height);}

NK_API int
nk_combo_callback(struct nk_context *ctx, void(*item_getter)(void*, int, const char**),
    void *userdata, int selected, int count, int item_height)
{
    int i;
    int max_height;
    struct nk_panel combo;
    float item_padding;
    float window_padding;
    const char *item;

    NK_ASSERT(ctx);
    NK_ASSERT(item_getter);
    if (!ctx || !item_getter)
        return selected;

    /* calculate popup window */
    item_padding = ctx->style.combo.content_padding.y;
    window_padding = ctx->style.window.padding.y;
    max_height = (count+1) * item_height + (int)item_padding * 3 + (int)window_padding * 2;

    item_getter(userdata, selected, &item);
    if (nk_combo_begin_label(ctx, &combo, item, max_height)) {
        nk_layout_row_dynamic(ctx, (float)item_height, 1);
        for (i = 0; i < count; ++i) {
            item_getter(userdata, i, &item);
            if (nk_combo_item_label(ctx, item, NK_TEXT_LEFT))
                selected = i;
        }
        nk_combo_end(ctx);
    }
    return selected;
}

NK_API void nk_combobox(struct nk_context *ctx, const char **items, int count,
    int *selected, int item_height)
{*selected = nk_combo(ctx, items, count, *selected, item_height);}

NK_API void nk_combobox_string(struct nk_context *ctx, const char *items_separated_by_zeros,
    int *selected, int count, int item_height)
{*selected = nk_combo_string(ctx, items_separated_by_zeros, *selected, count, item_height);}

NK_API void nk_combobox_separator(struct nk_context *ctx, const char *items_separated_by_separator,
    int separator,int *selected, int count, int item_height)
{*selected = nk_combo_separator(ctx, items_separated_by_separator, separator,
    *selected, count, item_height);}

NK_API void nk_combobox_callback(struct nk_context *ctx,
    void(*item_getter)(void* data, int id, const char **out_text),
    void *userdata, int *selected, int count, int item_height)
{*selected = nk_combo_callback(ctx, item_getter, userdata,  *selected, count, item_height);}

/*
 * -------------------------------------------------------------
 *
 *                          MENU
 *
 * --------------------------------------------------------------
 */
NK_INTERN int
nk_menu_begin(struct nk_panel *layout, struct nk_context *ctx, struct nk_window *win,
    const char *id, int is_clicked, struct nk_rect header, float width)
{
    int is_open = 0;
    int is_active = 0;
    struct nk_rect body;
    struct nk_window *popup;
    nk_hash hash = nk_murmur_hash(id, (int)nk_strlen(id), NK_WINDOW_MENU);

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    body.x = header.x;
    body.w = width;
    body.y = header.y + header.h;
    body.h = nk_null_rect.h;

    popup = win->popup.win;
    is_open = (popup && (popup->flags & NK_WINDOW_MENU));
    is_active = (popup && (win->popup.name == hash) && win->popup.type == NK_WINDOW_MENU);
    if ((is_clicked && is_open && !is_active) || (is_open && !is_active) ||
        (!is_open && !is_active && !is_clicked)) return 0;
    if (!nk_nonblock_begin(layout, ctx, NK_WINDOW_MENU|NK_WINDOW_NO_SCROLLBAR, body, header))
        return 0;
    win->popup.type = NK_WINDOW_MENU;
    win->popup.name = hash;
    return 1;
}

NK_API int
nk_menu_begin_text(struct nk_context *ctx, struct nk_panel *layout,
    const char *title, int len, nk_flags align, float width)
{
    struct nk_window *win;
    const struct nk_input *in;
    struct nk_rect header;
    int is_clicked = nk_false;
    nk_flags state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    state = nk_widget(&header, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || win->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text(&ctx->last_widget_state, &win->buffer, header,
        title, len, align, NK_BUTTON_DEFAULT, &ctx->style.menu_button, in, &ctx->style.font))
        is_clicked = nk_true;
    return nk_menu_begin(layout, ctx, win, title, is_clicked, header, width);
}

NK_API int nk_menu_begin_label(struct nk_context *ctx, struct nk_panel *layout,
    const char *text, nk_flags align, float width)
{return nk_menu_begin_text(ctx, layout, text, nk_strlen(text), align, width);}

NK_API int
nk_menu_begin_image(struct nk_context *ctx, struct nk_panel *layout,
    const char *id, struct nk_image img, float width)
{
    struct nk_window *win;
    struct nk_rect header;
    const struct nk_input *in;
    int is_clicked = nk_false;
    nk_flags state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    state = nk_widget(&header, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_image(&ctx->last_widget_state, &win->buffer, header,
        img, NK_BUTTON_DEFAULT, &ctx->style.menu_button, in))
        is_clicked = nk_true;
    return nk_menu_begin(layout, ctx, win, id, is_clicked, header, width);
}

NK_API int
nk_menu_begin_symbol(struct nk_context *ctx, struct nk_panel *layout,
    const char *id, enum nk_symbol_type sym, float width)
{
    struct nk_window *win;
    const struct nk_input *in;
    struct nk_rect header;
    int is_clicked = nk_false;
    nk_flags state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    state = nk_widget(&header, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_symbol(&ctx->last_widget_state,  &win->buffer, header,
        sym, NK_BUTTON_DEFAULT, &ctx->style.menu_button, in, &ctx->style.font))
        is_clicked = nk_true;
    return nk_menu_begin(layout, ctx, win, id, is_clicked, header, width);
}

NK_API int
nk_menu_begin_image_text(struct nk_context *ctx, struct nk_panel *layout,
    const char *title, int len, nk_flags align, struct nk_image img, float width)
{
    struct nk_window *win;
    struct nk_rect header;
    const struct nk_input *in;
    int is_clicked = nk_false;
    nk_flags state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    state = nk_widget(&header, ctx);
    if (!state) return 0;
    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text_image(&ctx->last_widget_state, &win->buffer,
        header, img, title, len, align, NK_BUTTON_DEFAULT, &ctx->style.menu_button,
        &ctx->style.font, in))
        is_clicked = nk_true;
    return nk_menu_begin(layout, ctx, win, title, is_clicked, header, width);
}

NK_API int nk_menu_begin_image_label(struct nk_context *ctx, struct nk_panel *layout,
    const char *title, nk_flags align, struct nk_image img, float width)
{return nk_menu_begin_image_text(ctx, layout, title, nk_strlen(title), align, img, width);}

NK_API int
nk_menu_begin_symbol_text(struct nk_context *ctx, struct nk_panel *layout,
    const char *title, int size, nk_flags align, enum nk_symbol_type sym, float width)
{
    struct nk_window *win;
    struct nk_rect header;
    const struct nk_input *in;
    int is_clicked = nk_false;
    nk_flags state;

    NK_ASSERT(ctx);
    NK_ASSERT(ctx->current);
    NK_ASSERT(ctx->current->layout);
    if (!ctx || !ctx->current || !ctx->current->layout)
        return 0;

    win = ctx->current;
    state = nk_widget(&header, ctx);
    if (!state) return 0;

    in = (state == NK_WIDGET_ROM || win->layout->flags & NK_WINDOW_ROM) ? 0 : &ctx->input;
    if (nk_do_button_text_symbol(&ctx->last_widget_state, &win->buffer,
        header, sym, title, size, align, NK_BUTTON_DEFAULT, &ctx->style.menu_button,
        &ctx->style.font, in)) is_clicked = nk_true;
    return nk_menu_begin(layout, ctx, win, title, is_clicked, header, width);
}

NK_API int nk_menu_begin_symbol_label(struct nk_context *ctx, struct nk_panel *layout,
    const char *title, nk_flags align, enum nk_symbol_type sym, float width)
{return nk_menu_begin_symbol_text(ctx, layout, title, nk_strlen(title), align,sym, width);}

NK_API int nk_menu_item_text(struct nk_context *ctx, const char *title, int len, nk_flags align)
{return nk_contextual_item_text(ctx, title, len, align);}

NK_API int nk_menu_item_label(struct nk_context *ctx, const char *label, nk_flags align)
{return nk_contextual_item_label(ctx, label, align);}

NK_API int nk_menu_item_image_label(struct nk_context *ctx, struct nk_image img,
    const char *label, nk_flags align)
{return nk_contextual_item_image_label(ctx, img, label, align);}

NK_API int nk_menu_item_image_text(struct nk_context *ctx, struct nk_image img,
    const char *text, int len, nk_flags align)
{return nk_contextual_item_image_text(ctx, img, text, len, align);}

NK_API int nk_menu_item_symbol_text(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *text, int len, nk_flags align)
{return nk_contextual_item_symbol_text(ctx, sym, text, len, align);}

NK_API int nk_menu_item_symbol_label(struct nk_context *ctx, enum nk_symbol_type sym,
    const char *label, nk_flags align)
{return nk_contextual_item_symbol_label(ctx, sym, label, align);}

NK_API void nk_menu_close(struct nk_context *ctx)
{nk_contextual_close(ctx);}

NK_API void
nk_menu_end(struct nk_context *ctx)
{nk_contextual_end(ctx);}

#endif
