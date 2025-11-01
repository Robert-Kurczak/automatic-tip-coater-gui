def log_info(message):
    bold_font_start = "\x1b[1;39;49m"
    bold_font_stop = "\x1b[0m"

    print(bold_font_start + message + bold_font_stop)

def log_error(message):
    red_color_start = "\x1b[1;31;49m"
    red_color_stop = "\x1b[0m"

    print(red_color_start + message + red_color_stop)

def log_success(message):
    green_color_start = "\x1b[1;32;49m"
    green_color_end = "\x1b[0m"

    print(green_color_start + message + green_color_end)
