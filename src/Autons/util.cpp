#include "main.h"



std::string get_last_word(std::string text) {
  std::string word = "";
  for (int i = text.length() - 1; i >= 0; i--) {
    if (text[i] != ' ') {
      word += text[i];
    } else {
      std::reverse(word.begin(), word.end());
      return word;
    }
  }
  std::reverse(word.begin(), word.end());
  return word;
}
std::string get_rest_of_the_word(std::string text, int position) {
    std::string word = "";
  for (int i = position; i < text.length(); i++) {
    if (text[i] != ' ' && text[i] != '\n') {
      word += text[i];
    } else {
      return word;
    }
  }
  return word;
}

void print_to_screen(std::string text, int line) {
    int CurrAutoLine = line;
    std::vector<string> texts = {};
    std::string temp = "";

    for (int i = 0; i < text.length(); i++) { 
        if (text[i] != '\n' && temp.length() + 1 > 32) {
            auto last_word = get_last_word(temp);
            if (last_word == temp) {
                texts.push_back(temp);
                temp = text[i];
            } else {
                int size = last_word.length();

                auto rest_of_word = get_rest_of_the_word(text, i);
                temp.erase(temp.length() - size, size);
                texts.push_back(temp);
                last_word += rest_of_word;
                i += rest_of_word.length();
                temp = last_word;
                if (i >= text.length() - 1) {
                    texts.push_back(temp);
                    break;
                }
        
            }
    }
    if (i >= text.length() - 1) {
      temp += text[i];
      texts.push_back(temp);
      temp = "";
      break;
    } else if (text[i] == '\n') {
      texts.push_back(temp);
      temp = "";
    } else {
      temp += text[i];
    }
  }
  for (auto i : texts) {
    if (CurrAutoLine > 7) {
      pros::lcd::clear();
      pros::lcd::set_text(line, "Out of Bounds. Print Line is too far down");
      return;
    }
    pros::lcd::clear_line(CurrAutoLine);
    pros::lcd::set_text(CurrAutoLine, i);
    CurrAutoLine++;
  }
}               

namespace as
{
  AutonSelector auton_selector{};
/*void update_auto_sd() {
  // If no SD card, return
  if (!util::IS_SD_CARD) return;

  FILE* usd_file_write = fopen("/usd/auto.txt", "w");
  std::string cp_str = std::to_string(auton_selector.current_auton_page);
  char const* cp_c = cp_str.c_str();
  fputs(cp_c, usd_file_write);
  fclose(usd_file_write);
}

/*void init_auton_selector() {
  // If no SD card, return
  if (!ez::util::IS_SD_CARD) return;

  FILE* as_usd_file_read;
  // If file exists...
  if ((as_usd_file_read = fopen("/usd/auto.txt", "r"))) {
    char l_buf[5];
    fread(l_buf, 1, 5, as_usd_file_read);
    as::auton_selector.current_auton_page = std::stof(l_buf);
    fclose(as_usd_file_read);
  }
  // If file doesn't exist, create file
  else {
    update_auto_sd();  // Writing to a file that doesn't exist creates the file
    printf("Created auto.txt\n");
  }

  if (as::auton_selector.current_auton_page > as::auton_selector.auton_count - 1 || as::auton_selector.current_auton_page < 0) {
    as::auton_selector.current_auton_page = 0;
    as::update_auto_sd();
  }
}*/
void page_up() {
  if (auton_selector.current_auton_page == auton_selector.auton_count - 1)
    auton_selector.current_auton_page = 0;
  else
    auton_selector.current_auton_page++;
  //update_auto_sd();
  auton_selector.print_selected_auton();
}

void page_down() {
  if (auton_selector.current_auton_page == 0)
    auton_selector.current_auton_page = auton_selector.auton_count - 1;
  else
    auton_selector.current_auton_page--;
  //update_auto_sd();
  auton_selector.print_selected_auton();
}

void initialize() {
  // Initialize auto selector and LLEMU
  pros::lcd::initialize();
  //as::init_auton_selector();

  // Callbacks for auto selector
  as::auton_selector.print_selected_auton();
  pros::lcd::register_btn0_cb(as::page_down);
  pros::lcd::register_btn2_cb(as::page_up);
}

} // namespace as

