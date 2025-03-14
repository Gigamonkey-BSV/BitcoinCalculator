
#include <replace.hpp>
#include <machine.hpp>
#include <parse.hpp>

using namespace data;

maybe<std::string> read_user_input () {
    std::string input;
    std::cout << "\n input: ";
    if (!std::getline (std::cin, input)) return {};
    return {input};
}

int main (int args, char **arg) {

    // TODO detect whether we are in interactive mode.
    // right now this is only interactive mode.

    auto machine = Diophant::initialize ();

    try {
        while (true) {
            maybe<std::string> input = read_user_input ();
            if (!bool (input)) break;
            if (input->empty ()) continue;

            // for each input line, attempt to construct an expression
            // out of it and then evaluate it.
            try {
                auto mm = read_line (machine, *input);
                if (mm.valid ()) std::cout << "\n result: " << machine.Last << std::endl;
                machine = mm;
            } catch (data::exception &e) {
                std::cout << "Exception caught: " << e.what () << "!" << std::endl;
            }
        }
    } catch (std::exception &e) {
        std::cout << "Unknown exception caught: " << e.what () << "!" << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown type caught!" << std::endl;
        return 1;
    }

    return 0;
}

