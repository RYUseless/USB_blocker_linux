#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <locale>

using namespace std;
namespace fs = std::filesystem;

void vypisUsbProducts() {
    const fs::path usbDevicesPath{"/sys/bus/usb/devices"};

    if (!fs::exists(usbDevicesPath) || !fs::is_directory(usbDevicesPath)) {
        cerr << "Adresar " << usbDevicesPath << " neexistuje nebo neni adresar.\n";
        return;
    }

    for (const auto& entry : fs::directory_iterator(usbDevicesPath)) {
        if (!entry.is_directory())
            continue;

        string poleso[3] = {"product", "serial", "authorized"};
        size_t poleso_len = sizeof(poleso) / sizeof(poleso[0]);
        int counter = 0;

        // get all connected USB devices :)
        while ( counter < poleso_len){
            fs::path productFile = entry.path() / poleso[counter];
                if (fs::exists(productFile)) {
                    ifstream infile(productFile);
                    if (infile) {
                        string line;
                        getline(infile, line);

                        if (line.compare(0, 4, "xHCI") == 0 || line.empty() || line == ""){
                            break;
                        }
                        // pouze prvni run z dvou, prijde mi to efektivnejsi nez porovnavat value z pole se stringem
                        if (counter == 0){
                            cout << "=== Detected USB device ===" << "\n";
                        }
                        cout << poleso[counter] << ": "<< entry.path().filename().string() << ": " << line << "\n";
                    }
                }
            counter += 1;
        }
    }
}

#include <iostream>
#include <string>

// Pokud to dáváš do svého projektu, smaž tyto using
using std::string; using std::cout; using std::endl;

void tui_prints() {
    const string top_left = u8"\u250C";    // ┌
    const string top_right = u8"\u2510";   // ┐ 
    const string bottom_left = u8"\u2514"; // └
    const string bottom_right = u8"\u2518"; // ┘
    const string horizontal = u8"\u2500";  // ─
    const string vertical = u8"\u2502";    // │
    const string left_join = u8"\u251C";    // ├ 
    const string right_join = u8"\u2524";   // ┤
    const string top_join = u8"\u252C";     // ┬
    const string bottom_join = u8"\u2534";  // ┴ 
    const string cross_join = u8"\u253C";   // ┼

    const string header_1 = "Username";
    const string header_2 = "USB name";
    const string header_3 = "Serial Num";
    const string *pole_addrs[3] = {&header_1, &header_2, &header_3};

    int max_widths[3] = {10, 12, 12};  // max délky buňky (bez paddingu) – můžeš upravit
    int padding = 3;

    // 1) Horní okraj
    cout << top_left;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < max_widths[i] + 2 * padding; j++) cout << horizontal;
        if (i == 2) cout << top_right;
        else cout << top_join;
    }
    cout << endl;

    // 2) Header řádek
    cout << vertical;
    for (int i = 0; i < 3; i++) {
        string text = *pole_addrs[i];
        // Oříznout do šířky
        if ((int)text.length() > max_widths[i])
            text = text.substr(0, max_widths[i]);
        int left_pad = padding;
        int right_pad = max_widths[i] - (int)text.length() + padding;
        for (int j = 0; j < left_pad; j++) cout << ' ';
        cout << text;
        for (int j = 0; j < right_pad; j++) cout << ' ';
        cout << vertical;
    }
    cout << endl;

    // 3) Oddělovací řádek
    cout << left_join;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < max_widths[i] + 2 * padding; j++) cout << horizontal;
        if (i == 2) cout << right_join;
        else cout << cross_join;
    }
    cout << endl;

    // 4) Prázdná řádka s dělením na buňky (vizuálně ok)
    
    /*
    for (int pr = 0; pr < 2; ++pr) { // můžeš vložit více prázdných řádků
        ... aka ten for loop + 2x cout co jest dole
    }
    */

     cout << vertical;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < max_widths[i] + 2 * padding; j++) cout << ' ';
            cout << vertical;
        }
        cout << endl;

    // 5) Spodní okraj
    cout << bottom_left;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < max_widths[i] + 2 * padding; j++) cout << horizontal;
        if (i == 2) cout << bottom_right;
        else cout << bottom_join;
    }
    cout << endl;
}

void draw_tui(){
    //values tabulky:

}



int main() {
    // main infosky about usb devices
    //vypisUsbProducts();

    // tui hovadzina:
    tui_prints();

    return 0;
}


