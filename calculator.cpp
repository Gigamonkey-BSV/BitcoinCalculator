
#include <Diophant/replace.hpp>
#include <Diophant/machine.hpp>
#include <Diophant/parse/parser.hpp>
#include <data/io/log.hpp>

using namespace data;

maybe<std::string> read_user_input () {
    std::string input;
    std::cout << "\n input: ";
    if (!std::getline (std::cin, input)) return {};
    return {input};
}

int main (int args, char **arg) {
    log::init ()->min_level (log::normal);

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
                auto ee = machine.evaluate (Diophant::read_line (*input));
                if (ee.Expression != Diophant::expression {})
                    std::cout << "\n result: " << ee.Expression << std::endl;
                machine = ee.Machine;
            } catch (Diophant::parse_error &e) {
                std::cout << "Parse error: " << e.what () << "!" << std::endl;
            } catch (data::exception &e) {
                std::cout << "Exception: " << e.what () << "!" << std::endl;
            }
        }
    } catch (std::exception &e) {
        std::cout << "Unknown exception: " << e.what () << "!" << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown error!" << std::endl;
        return 1;
    }

    return 0;
}

