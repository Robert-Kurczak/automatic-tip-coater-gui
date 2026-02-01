# Relative location of the TouchGFX framework from root of application
touchgfx_path := ../Middlewares/ST/touchgfx

# Location of the TouchGFX Environment
touchgfx_env := file:///C:/TouchGFX/4.26.0/env
# Optional additional compiler flags
user_cflags := -std=gnu++20 -DUSE_BPP=16 -DDEBUG_BUILD -Wformat-truncation=0 -Wfatal-errors
linker_options := -no-pie
