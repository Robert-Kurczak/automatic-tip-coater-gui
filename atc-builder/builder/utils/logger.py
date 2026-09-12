"""
Logger defining common messages formatting
"""

class Logger:
    """
    Logger defining common messages formatting
    """

    def log_info(self, message, end="\n"):
        """
        Logs non-critical info
        """

        bold_font_start = "\x1b[1;39;49m"
        bold_font_stop = "\x1b[0m"

        print(bold_font_start + message + bold_font_stop, end=end)

    def log_error(self, message, end="\n"):
        """
        Logs critical errors
        """

        red_color_start = "\x1b[1;31;49m"
        red_color_stop = "\x1b[0m"

        print(red_color_start + message + red_color_stop, end=end)

    def log_success(self, message, end="\n"):
        """
        Logs success
        """

        green_color_start = "\x1b[1;32;49m"
        green_color_end = "\x1b[0m"

        print(green_color_start + message + green_color_end, end=end)
